/*@-mods@*/
/**
 * \file lib/fs.c
 */

#include "system.h"
#include <rpmlib.h>
#include <rpmmacro.h>	/* XXX for rpmGetPath */
#include "debug.h"

/*@-usereleased -onlytrans@*/

struct fsinfo {
/*@only@*/ const char * mntPoint;	/*!< path to mount point. */
    dev_t dev;				/*!< devno for mount point. */
    int rdonly;				/*!< is mount point read only? */
};

/*@unchecked@*/
/*@only@*/ /*@null@*/ static struct fsinfo * filesystems = NULL;
/*@unchecked@*/
/*@only@*/ /*@null@*/ static const char ** fsnames = NULL;
/*@unchecked@*/
static int numFilesystems = 0;

void freeFilesystems(void)
{
    if (filesystems) {
	int i;
	for (i = 0; i < numFilesystems; i++)
	    filesystems[i].mntPoint = _free(filesystems[i].mntPoint);
	filesystems = _free(filesystems);
    }
    if (fsnames) {
#if 0	/* XXX leak/segfault on exit of "rpm -qp --qf '%{#fsnames}' pkg" */
	free(fsnames);
#endif
	fsnames = NULL;
    }
    numFilesystems = 0;
}

#if HAVE_MNTCTL

/* modeled after sample code from Till Bubeck */

#include <sys/mntctl.h>
#include <sys/vmount.h>

/* 
 * There is NO mntctl prototype in any header file of AIX 3.2.5! 
 * So we have to declare it by ourself...
 */
int mntctl(int command, int size, char *buffer);

/**
 * Get information for mounted file systems.
 * @todo determine rdonly for non-linux file systems.
 * @return		0 on success, 1 on error
 */
static int getFilesystemList(void)
	/*@*/
{
    int size;
    void * buf;
    struct vmount * vm;
    struct stat sb;
    int rdonly = 0;
    int num;
    int fsnameLength;
    int i;

    num = mntctl(MCTL_QUERY, sizeof(size), (char *) &size);
    if (num < 0) {
	rpmError(RPMERR_MTAB, _("mntctl() failed to return size: %s\n"), 
		 strerror(errno));
	return 1;
    }

    /*
     * Double the needed size, so that even when the user mounts a 
     * filesystem between the previous and the next call to mntctl
     * the buffer still is large enough.
     */
    size *= 2;

    buf = alloca(size);
    num = mntctl(MCTL_QUERY, size, buf);
    if ( num <= 0 ) {
        rpmError(RPMERR_MTAB, _("mntctl() failed to return mount points: %s\n"), 
		 strerror(errno));
	return 1;
    }

    numFilesystems = num;

    filesystems = xcalloc((numFilesystems + 1), sizeof(*filesystems));
    fsnames = xcalloc((numFilesystems + 1), sizeof(char *));
    
    for (vm = buf, i = 0; i < num; i++) {
	char *fsn;
	fsnameLength = vm->vmt_data[VMT_STUB].vmt_size;
	fsn = xmalloc(fsnameLength + 1);
	strncpy(fsn, (char *)vm + vm->vmt_data[VMT_STUB].vmt_off, 
		fsnameLength);

	filesystems[i].mntPoint = fsnames[i] = fsn;
	
	if (stat(filesystems[i].mntPoint, &sb)) {
	    rpmError(RPMERR_STAT, _("failed to stat %s: %s\n"), fsnames[i],
			strerror(errno));

	    freeFilesystems();
	    return 1;
	}
	
	filesystems[i].dev = sb.st_dev;
	filesystems[i].rdonly = rdonly;

	/* goto the next vmount structure: */
	vm = (struct vmount *)((char *)vm + vm->vmt_length);
    }

    filesystems[i].mntPoint = NULL;
    fsnames[i]              = NULL;

    return 0;
}

#else	/* HAVE_MNTCTL */

/**
 * Get information for mounted file systems.
 * @todo determine rdonly for non-linux file systems.
 * @return		0 on success, 1 on error
 */
static int getFilesystemList(void)
	/*@globals fileSystem, internalState@*/
	/*@modifies fileSystem, internalState@*/
{
    int numAlloced = 10;
    struct stat sb;
    int i;
    const char * mntdir;
    int rdonly = 0;

#   if GETMNTENT_ONE || GETMNTENT_TWO
    our_mntent item;
    FILE * mtab;

	mtab = fopen(MOUNTED, "r");
	if (!mtab) {
	    rpmError(RPMERR_MTAB, _("failed to open %s: %s\n"), MOUNTED, 
		     strerror(errno));
	    return 1;
	}
#   elif HAVE_GETMNTINFO_R
    struct statfs * mounts = NULL;
    int mntCount = 0, bufSize = 0, flags = MNT_NOWAIT;
    int nextMount = 0;

	getmntinfo_r(&mounts, flags, &mntCount, &bufSize);
#   endif

    filesystems = xcalloc((numAlloced + 1), sizeof(*filesystems));	/* XXX memory leak */

    numFilesystems = 0;
    while (1) {
#	if GETMNTENT_ONE
	    /* this is Linux */
	    /*@-modunconnomods -moduncon @*/
	    our_mntent * itemptr = getmntent(mtab);
	    if (!itemptr) break;
	    item = *itemptr;	/* structure assignment */
	    mntdir = item.our_mntdir;
#if defined(MNTOPT_RO)
	    /*@-compdef@*/
	    if (hasmntopt(itemptr, MNTOPT_RO) != NULL)
		rdonly = 1;
	    /*@=compdef@*/
#endif
	    /*@=modunconnomods =moduncon @*/
#	elif GETMNTENT_TWO
	    /* Solaris, maybe others */
	    if (getmntent(mtab, &item)) break;
	    mntdir = item.our_mntdir;
#	elif HAVE_GETMNTINFO_R
	    if (nextMount == mntCount) break;
	    mntdir = mounts[nextMount++].f_mntonname;
#	endif

	if (stat(mntdir, &sb)) {
	    rpmError(RPMERR_STAT, _("failed to stat %s: %s\n"), mntdir,
			strerror(errno));

	    freeFilesystems();
	    return 1;
	}

	numFilesystems++;
	if ((numFilesystems + 1) == numAlloced) {
	    numAlloced += 10;
	    filesystems = xrealloc(filesystems, 
				  sizeof(*filesystems) * (numAlloced + 1));
	}

	filesystems[numFilesystems-1].dev = sb.st_dev;
	filesystems[numFilesystems-1].mntPoint = xstrdup(mntdir);
	filesystems[numFilesystems-1].rdonly = rdonly;
    }

#   if GETMNTENT_ONE || GETMNTENT_TWO
	(void) fclose(mtab);
#   elif HAVE_GETMNTINFO_R
	mounts = _free(mounts);
#   endif

    filesystems[numFilesystems].dev = 0;
    filesystems[numFilesystems].mntPoint = NULL;
    filesystems[numFilesystems].rdonly = 0;

    fsnames = xcalloc((numFilesystems + 1), sizeof(*fsnames));
    for (i = 0; i < numFilesystems; i++)
	fsnames[i] = filesystems[i].mntPoint;
    fsnames[numFilesystems] = NULL;

    return 0; 
}
#endif	/* HAVE_MNTCTL */

int rpmGetFilesystemList(const char *** listptr, int * num)
{
    if (!fsnames) 
	if (getFilesystemList())
	    return 1;

    if (listptr) *listptr = fsnames;
    if (num) *num = numFilesystems;

    return 0;
}

int rpmGetFilesystemUsage(const char ** fileList, int_32 * fssizes, int numFiles,
			  uint_32 ** usagesPtr, /*@unused@*/ int flags)
{
    int_32 * usages;
    int i, len, j;
    char * buf, * dirName;
    char * chptr;
    int maxLen;
    char * lastDir;
    const char * sourceDir;
    int lastfs = 0;
    int lastDev = -1;		/* I hope nobody uses -1 for a st_dev */
    struct stat sb;

    if (!fsnames) 
	if (getFilesystemList())
	    return 1;

    usages = xcalloc(numFilesystems, sizeof(usages));

    sourceDir = rpmGetPath("%{_sourcedir}", NULL);

    maxLen = strlen(sourceDir);
    for (i = 0; i < numFiles; i++) {
	len = strlen(fileList[i]);
	if (maxLen < len) maxLen = len;
    }
    
    buf = alloca(maxLen + 1);
    lastDir = alloca(maxLen + 1);
    dirName = alloca(maxLen + 1);
    *lastDir = '\0';

    /* cut off last filename */
    for (i = 0; i < numFiles; i++) {
	if (*fileList[i] == '/') {
	    strcpy(buf, fileList[i]);
	    chptr = buf + strlen(buf) - 1;
	    while (*chptr != '/') chptr--;
	    if (chptr == buf)
		buf[1] = '\0';
	    else
		*chptr-- = '\0';
	} else {
	    /* this should only happen for source packages (gulp) */
	    strcpy(buf,  sourceDir);
	}

	if (strcmp(lastDir, buf)) {
	    strcpy(dirName, buf);
	    chptr = dirName + strlen(dirName) - 1;
	    while (stat(dirName, &sb)) {
		if (errno != ENOENT) {
		    rpmError(RPMERR_STAT, _("failed to stat %s: %s\n"), buf,
				strerror(errno));
		    sourceDir = _free(sourceDir);
		    usages = _free(usages);
		    return 1;
		}

		/* cut off last directory part, because it was not found. */
		while (*chptr != '/') chptr--;

		if (chptr == dirName)
		    dirName[1] = '\0';
		else
		    *chptr-- = '\0';
	    }

	    if (lastDev != sb.st_dev) {
		for (j = 0; j < numFilesystems; j++)
		    if (filesystems && filesystems[j].dev == sb.st_dev)
			/*@innerbreak@*/ break;

		if (j == numFilesystems) {
		    rpmError(RPMERR_BADDEV, 
				_("file %s is on an unknown device\n"), buf);
		    sourceDir = _free(sourceDir);
		    usages = _free(usages);
		    return 1;
		}

		lastfs = j;
		lastDev = sb.st_dev;
	    }
	}

	strcpy(lastDir, buf);
	usages[lastfs] += fssizes[i];
    }

    sourceDir = _free(sourceDir);

    /*@-branchstate@*/
    if (usagesPtr)
	*usagesPtr = usages;
    else
	usages = _free(usages);
    /*@=branchstate@*/

    return 0;
}
/*@=usereleased =onlytrans@*/
/*@=mods@*/
