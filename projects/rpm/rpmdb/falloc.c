/** \ingroup rpmio db1
 * \file rpmdb/falloc.c
 * 
 * The entire file space is thus divided into blocks with a "struct fablock"
 * at the header of each. The size fields doubly link this block list.
 *
 * There is an additional free list weaved through the block list, which 
 * keeps new allocations fast.
 *
 * Much of this was inspired by Knuth vol 1.
 *
 */

#include "system.h"
#include <rpmio_internal.h>
#include <rpmmessages.h>
#include <rpmerr.h>
#include "falloc.h"
#include "debug.h"

/** \ingroup db1
 */
#define FA_MAGIC      0x02050920

struct faFileHeader {
    unsigned int magic;
    unsigned int firstFree;
};

struct faHeader {
    unsigned int size;				
    unsigned int freeNext; /* offset of the next free block, 0 if none */
    unsigned int freePrev; 
    unsigned int isFree;

    /* note that the u16's appear last for alignment/space reasons */
};

struct faFooter {
    unsigned int size;
    unsigned int isFree; 
} ;

/* =============================================================== */
/*@-nullassign@*/
static struct FDIO_s fadio_s = {
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  fadOpen, NULL, NULL,	NULL, NULL, NULL, NULL, NULL, NULL
};
/*@=nullassign@*/
FDIO_t fadio = /*@-compmempass@*/ &fadio_s /*@=compmempass@*/ ;
/* =============================================================== */

/**
 * pread(2) clone.
 */
static
ssize_t Pread(FD_t fd, void * buf, size_t count, _libio_off_t offset)
	/*@globals fileSystem @*/
	/*@modifies fd, *buf, fileSystem @*/
{
    if (Fseek(fd, offset, SEEK_SET) < 0)
	return -1;
    /*@-sizeoftype@*/
    return Fread(buf, sizeof(char), count, fd);
    /*@=sizeoftype@*/
}

/**
 * pwrite(2) clone.
 */
static
ssize_t Pwrite(FD_t fd, const void * buf, size_t count, _libio_off_t offset)
	/*@globals fileSystem @*/
	/*@modifies fd, fileSystem @*/
{
    if (Fseek(fd, offset, SEEK_SET) < 0)
	return -1;
    /*@-sizeoftype@*/
    return Fwrite(buf, sizeof(char), count, fd);
    /*@=sizeoftype@*/
}

/* flags are the same as for open(2) - NULL returned on error */
FD_t fadOpen(const char * path, int flags, mode_t perms)
{
    struct faFileHeader newHdr;
    FD_t fd;

    if (flags & O_WRONLY)
	return NULL;

    /*@-type@*/ /* FIX: cast? */
    fd = ufdio->_open(path, flags, perms);
    /*@=type@*/
    if (Ferror(fd))
	/* XXX Fstrerror */
	return NULL;

    /*@-modobserver -observertrans -mods @*/
    memcpy(fadio, fdio, sizeof(*fadio));
    fadio->_open = fadOpen;
    /*@=modobserver =observertrans =mods @*/

    fdSetIo(fd, fadio);
    fadSetFirstFree(fd, 0);
    fadSetFileSize(fd, Fseek(fd, 0, SEEK_END));

    /* is this file brand new? */
    if (fadGetFileSize(fd) == 0) {
	newHdr.magic = FA_MAGIC;
	newHdr.firstFree = 0;
	/*@-sizeoftype@*/
	if (Fwrite(&newHdr, sizeof(char), sizeof(newHdr), fd) != sizeof(newHdr)) {
	    (void) Fclose(fd);
	    return NULL;
	}
	/*@=sizeoftype@*/
	fadSetFirstFree(fd, 0);
	fadSetFileSize(fd, sizeof(newHdr));
    } else {
	memset(&newHdr, 0, sizeof(newHdr));
	if (Pread(fd, &newHdr, sizeof(newHdr), 0) != sizeof(newHdr)) {
	    (void) Fclose(fd);
	    return NULL;
	}
	if (newHdr.magic != FA_MAGIC) {
	    (void) Fclose(fd);
	    return NULL;
	}
	fadSetFirstFree(fd, newHdr.firstFree);
	fadSetFileSize(fd, Fseek(fd, 0, SEEK_END));

	if (fadGetFileSize(fd) < 0) {
	    (void) Fclose(fd);
	    return NULL;
	}
    }

    /*@-refcounttrans@*/ return fd /*@=refcounttrans@*/ ;
}

/* returns 0 on failure */
unsigned int fadAlloc(FD_t fd, unsigned int size)
{
    unsigned int nextFreeBlock;
    unsigned int newBlockOffset;
    unsigned int footerOffset;
    int failed = 0;
    struct faFileHeader faHeader;
    struct faHeader header, origHeader;
    struct faHeader * restoreHeader = NULL;
    struct faHeader nextFreeHeader, origNextFreeHeader;
    struct faHeader * restoreNextHeader = NULL;
    struct faHeader prevFreeHeader, origPrevFreeHeader;
    struct faHeader * restorePrevHeader = NULL;
    struct faFooter footer, origFooter;
    struct faFooter * restoreFooter = NULL;
    int updateHeader = 0;

    memset(&header, 0, sizeof(header));

    /* our internal idea of size includes overhead */
    /*@-sizeoftype@*/
    size += sizeof(struct faHeader) + sizeof(struct faFooter);
    /*@=sizeoftype@*/

    /* Make sure they are allocing multiples of 64 bytes. It'll keep
       things less fragmented that way */
    (size % 64) ? size += (64 - (size % 64)) : 0;

    /* find a block via first fit - see Knuth vol 1 for why */
    /* XXX this could be optimized a bit still */

    nextFreeBlock = fadGetFirstFree(fd);
    newBlockOffset = 0;

    while (nextFreeBlock && !newBlockOffset) {
	if (Pread(fd, &header, sizeof(header), nextFreeBlock) != sizeof(header)) return 0;

/* XXX W2DO? exit(EXIT_FAILURE) forces the user to discover rpm --rebuilddb */
	if (!header.isFree) {
	    rpmError(RPMERR_FREELIST, _("free list corrupt (%u)- please run\n"
			"\t\"rpm --rebuilddb\"\n"
			"More information is available from http://www.rpm.org "
			"or the rpm-list@redhat.com mailing list\n"
			"if \"rpm --rebuilddb\" fails to correct the problem.\n"),
			nextFreeBlock);

	    exit(EXIT_FAILURE);
	    /*@notreached@*/
	}

	if (header.size >= size) {
	    newBlockOffset = nextFreeBlock;
	} else {
	    nextFreeBlock = header.freeNext;
	}
    }

    if (newBlockOffset) {
	/* header should still be good from the search */
	origHeader = header;

	footerOffset = newBlockOffset + header.size - sizeof(footer);

	if (Pread(fd, &footer, sizeof(footer), footerOffset) != sizeof(footer)) 
	    return 0;
	origFooter = footer;

	/* should we split this block into two? */
	/* XXX implement fragment creation here */

	footer.isFree = header.isFree = 0;

	/* remove it from the free list before */
	if (newBlockOffset == fadGetFirstFree(fd)) {
	    faHeader.magic = FA_MAGIC;
	    faHeader.firstFree = header.freeNext;
	    fadSetFirstFree(fd, header.freeNext);
	    updateHeader = 1;
	} else {
	    if (Pread(fd, &prevFreeHeader, sizeof(prevFreeHeader),
			header.freePrev) != sizeof(prevFreeHeader)) 
		return 0;
	    origPrevFreeHeader = prevFreeHeader;

	    prevFreeHeader.freeNext = header.freeNext;
	}

	/* and after */
	if (header.freeNext) {
	    if (Pread(fd, &nextFreeHeader, sizeof(nextFreeHeader),
			header.freeNext) != sizeof(nextFreeHeader)) 
		return 0;
	    origNextFreeHeader = nextFreeHeader;

	    nextFreeHeader.freePrev = header.freePrev;
	}

	/* if any of these fail, try and restore everything before leaving */
	if (updateHeader) {
	    if (Pwrite(fd, &faHeader, sizeof(faHeader), 0) !=
			     sizeof(faHeader)) 
		return 0;
	} else {
	    if (Pwrite(fd, &prevFreeHeader, sizeof(prevFreeHeader),
			header.freePrev) != sizeof(prevFreeHeader))
		return 0;
	    restorePrevHeader = &origPrevFreeHeader;
	}

	if (header.freeNext) {
	    if (Pwrite(fd, &nextFreeHeader, sizeof(nextFreeHeader),
			header.freeNext) != sizeof(nextFreeHeader))
		return 0;

	    restoreNextHeader = &origNextFreeHeader;
	}

	if (!failed) {
	    if (Pwrite(fd, &header, sizeof(header), newBlockOffset) !=
			 sizeof(header)) {
		failed = 1;
		restoreHeader = &origHeader;
	    }
	}

	if (!failed) {
	    if (Pwrite(fd, &footer, sizeof(footer),
			footerOffset) != sizeof(footer)) {
		failed = 1;
		restoreFooter = &origFooter;
	    }
	}

	if (failed) {
	    if (updateHeader) {
		faHeader.firstFree = newBlockOffset;
		fadSetFirstFree(fd, newBlockOffset);
	        (void)Pwrite(fd, &faHeader, sizeof(faHeader), 0);
	    } 

	    if (restorePrevHeader)
	    	(void)Pwrite(fd, restorePrevHeader, sizeof(*restorePrevHeader),
				header.freePrev);

	    if (restoreNextHeader)
	    	(void)Pwrite(fd, restoreNextHeader, sizeof(*restoreNextHeader),
				header.freeNext);

	    if (restoreHeader)
	    	(void)Pwrite(fd, restoreHeader, sizeof(header),
				newBlockOffset);

	    if (restoreFooter)
	    	(void)Pwrite(fd, restoreFooter, sizeof(footer),
				footerOffset);

	    return 0;
	}
    } else {
	char * space;

	/* make a new block */
	newBlockOffset = fadGetFileSize(fd);
	footerOffset = newBlockOffset + size - sizeof(footer);

	space = alloca(size);
	if (space == NULL) return 0;
	memset(space, 0, size);

	footer.isFree = header.isFree = 0;
	footer.size = header.size = size;
	header.freePrev = header.freeNext = 0;

	/* reserve all space up front */
	/* XXX TODO: check max. no. of bytes to write */
	if (Pwrite(fd, space, size, newBlockOffset) != size)
	    return 0;

	if (Pwrite(fd, &header, sizeof(header), newBlockOffset) != sizeof(header))
	    return 0;

	if (Pwrite(fd, &footer, sizeof(footer), footerOffset) != sizeof(footer))
	    return 0;

	fadSetFileSize(fd, fadGetFileSize(fd) + size);
    }
    
    return newBlockOffset + sizeof(header); 
}

void fadFree(FD_t fd, unsigned int offset)
{
    struct faHeader header;
    struct faFooter footer;
    int footerOffset;
    int prevFreeOffset, nextFreeOffset;
    struct faHeader prevFreeHeader, nextFreeHeader;
    struct faFileHeader faHeader;

    /* any errors cause this to die, and thus result in lost space in the
       database. which is at least better then corruption */

    offset -= sizeof(header);

    /* find out where in the (sorted) free list to put this */
    prevFreeOffset = fadGetFirstFree(fd);

    if (!prevFreeOffset || (prevFreeOffset > offset)) {
	nextFreeOffset = fadGetFirstFree(fd);
	prevFreeOffset = 0;
    } else {
	memset(&prevFreeHeader, 0, sizeof(prevFreeHeader));
	if (Pread(fd, &prevFreeHeader, sizeof(prevFreeHeader),
			prevFreeOffset) != sizeof(prevFreeHeader))
	    return;

	while (prevFreeHeader.freeNext && prevFreeHeader.freeNext < offset) {
	    prevFreeOffset = prevFreeHeader.freeNext;
	    if (Pread(fd, &prevFreeHeader, sizeof(prevFreeHeader),
			prevFreeOffset) != sizeof(prevFreeHeader))
		return;
	} 

	nextFreeOffset = prevFreeHeader.freeNext;
    }

    if (nextFreeOffset) {
	memset(&nextFreeHeader, 0, sizeof(nextFreeHeader));
	if (Pread(fd, &nextFreeHeader, sizeof(nextFreeHeader),
			nextFreeOffset) != sizeof(nextFreeHeader))
	    return;
    }

    memset(&header, 0, sizeof(header));
    if (Pread(fd, &header, sizeof(header), offset) != sizeof(header))
	return;

    footerOffset = offset + header.size - sizeof(footer);

    memset(&footer, 0, sizeof(footer));
    if (Pread(fd, &footer, sizeof(footer), footerOffset) != sizeof(footer))
	return;

    header.isFree = 1;
    header.freeNext = nextFreeOffset;
    header.freePrev = prevFreeOffset;
    footer.isFree = 1;

    /* XXX TODO: set max. no. of bytes to write */
    (void)Pwrite(fd, &header, sizeof(header), offset);

    (void)Pwrite(fd, &footer, sizeof(footer), footerOffset);

    if (nextFreeOffset) {
	nextFreeHeader.freePrev = offset;
	if (Pwrite(fd, &nextFreeHeader, sizeof(nextFreeHeader),
			nextFreeOffset) != sizeof(nextFreeHeader))
	    return;
    }

    if (prevFreeOffset) {
	prevFreeHeader.freeNext = offset;
	if (Pwrite(fd, &prevFreeHeader, sizeof(prevFreeHeader),
			prevFreeOffset) != sizeof(prevFreeHeader))
	    return;
    } else {
	fadSetFirstFree(fd, offset);

	faHeader.magic = FA_MAGIC;
	faHeader.firstFree = fadGetFirstFree(fd);

	/* XXX TODO: set max. no. of bytes to write */
	if (Pwrite(fd, &faHeader, sizeof(faHeader), 0) != sizeof(faHeader))
	    return;
    }
}

static int fadSanity(FD_t fd, int offset, const struct faHeader * fh, int printit)
	/*@*/
{
    int rc = 0;

    /*@-sizeoftype@*/
    /* Check size range and alignment. */
    if (!(fh->size > 0 && fh->size <= 0x00200000 && (fh->size & 0x3f) == 0))
	rc |= 0x1;

    /* Check forward link range, alignment and offset. */
    if (fh->freeNext &&
	!(	fh->freeNext > sizeof(struct faFileHeader) &&
		fh->freeNext < fadGetFileSize(fd) &&
		(fh->freeNext & 0x3f) == sizeof(struct faFileHeader)) )
	rc |= 0x2;

    /* Check backward link range, alignment and offset. */
    if (fh->freePrev &&
	!(	fh->freePrev > sizeof(struct faFileHeader) &&
		fh->freePrev < fadGetFileSize(fd) &&
		(fh->freePrev & 0x3f) == sizeof(struct faFileHeader)) )
	rc |= 0x4;
    /*@=sizeoftype@*/

    /* Check that only the isFree bit is (possibly) set. */
    if (fh->isFree & ~1)
	rc |= 0x8;

    if (printit && rc) {
	rpmMessage(RPMMESS_DEBUG,
    "offset %d(0x%08x) rc %d: size 0x%08x next %d(0x%08x) prev %d(0x%08x) isFree 0x%08x\n",
		offset, (unsigned) offset, rc,
		(unsigned) fh->size,
		(int) fh->freeNext, fh->freeNext,
		(int) fh->freePrev, fh->freePrev,
		(unsigned) fh->isFree);
    }
    return rc;
}

int fadFirstOffset(FD_t fd)
{
    return fadNextOffset(fd, 0);
}

int fadNextOffset(FD_t fd, unsigned int lastoff)
{
    struct faHeader header;
    int offset;

    /*@-sizeoftype@*/
    offset = (lastoff)
	? (lastoff - sizeof(header))
	: sizeof(struct faFileHeader);
    /*@=sizeoftype@*/

    if (offset >= fadGetFileSize(fd))
	return 0;

    memset(&header, 0, sizeof(header));
    if (Pread(fd, &header, sizeof(header), offset) != sizeof(header))
	return 0;

    if (!lastoff && header.isFree == 0)
	return (offset + sizeof(header));

    /*
     * XXX Try to reconnect at next record found. This isn't perfect
     * XXX but handles many common db1 corruption problems.
     */
    if (fadSanity(fd, offset, &header, 0)) {
	struct faHeader myheader;
	int o = offset;

	memset(&myheader, 0, sizeof(myheader));
	do {
	    o += 0x40;	/* XXX allocation chunks are padded to 64b */
	    if (o >= fadGetFileSize(fd))
		return 0;
	    if (Pread(fd, &myheader, sizeof(myheader), o) != sizeof(header))
		return 0;
	} while (fadSanity(fd, o, &myheader, 0));
	return (o + sizeof(header));
    }

    do {
	offset += header.size;
	if (offset >= fadGetFileSize(fd))
	    return 0;

	if (Pread(fd, &header, sizeof(header), offset) != sizeof(header))
	    return 0;

    } while (header.isFree == 1);

    /* Sanity check this to make sure we're not going in loops */
    offset += sizeof(header);
    if (offset <= lastoff)
	return 0;	/* XXX used to return -1 */

    return offset;
}
