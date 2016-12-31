/** \ingroup header
 * \file lib/package.c
 */

#include "system.h"

#include <netinet/in.h>

#include <rpmlib.h>

#include "misc.h"
#include "rpmlead.h"
#include "signature.h"
#include "debug.h"

#define	alloca_strdup(_s)	strcpy(alloca(strlen(_s)+1), (_s))

/*@access Header@*/		/* XXX compared with NULL */

void headerMergeLegacySigs(Header h, const Header sig)
{
    HFD_t hfd = (HFD_t) headerFreeData;
    HAE_t hae = (HAE_t) headerAddEntry;
    HeaderIterator hi;
    int_32 tag, type, count;
    const void * ptr;
    int xx;

    /*@-mods@*/ /* FIX: undocumented modification of sig */
    for (hi = headerInitIterator(sig);
    /*@=mods@*/
        headerNextIterator(hi, &tag, &type, &ptr, &count);
        ptr = hfd(ptr, type))
    {
	switch (tag) {
	case RPMSIGTAG_SIZE:
	    tag = RPMTAG_SIGSIZE;
	    /*@switchbreak@*/ break;
	case RPMSIGTAG_LEMD5_1:
	    tag = RPMTAG_SIGLEMD5_1;
	    /*@switchbreak@*/ break;
	case RPMSIGTAG_PGP:
	    tag = RPMTAG_SIGPGP;
	    /*@switchbreak@*/ break;
	case RPMSIGTAG_LEMD5_2:
	    tag = RPMTAG_SIGLEMD5_2;
	    /*@switchbreak@*/ break;
	case RPMSIGTAG_MD5:
	    tag = RPMTAG_SIGMD5;
	    /*@switchbreak@*/ break;
	case RPMSIGTAG_GPG:
	    tag = RPMTAG_SIGGPG;
	    /*@switchbreak@*/ break;
	case RPMSIGTAG_PGP5:
	    tag = RPMTAG_SIGPGP5;
	    /*@switchbreak@*/ break;
	case RPMSIGTAG_PAYLOADSIZE:
	    tag = RPMTAG_ARCHIVESIZE;
	    /*@switchbreak@*/ break;
	case RPMSIGTAG_SHA1:
	case RPMSIGTAG_DSA:
	case RPMSIGTAG_RSA:
	default:
	    if (!(tag >= HEADER_SIGBASE && tag < HEADER_TAGBASE))
		continue;
	    /*@switchbreak@*/ break;
	}
	if (ptr == NULL) continue;	/* XXX can't happen */
	if (!headerIsEntry(h, tag))
	    xx = hae(h, tag, type, ptr, count);
    }
    hi = headerFreeIterator(hi);
}

Header headerRegenSigHeader(const Header h)
{
    HFD_t hfd = (HFD_t) headerFreeData;
    Header sig = rpmNewSignature();
    HeaderIterator hi;
    int_32 tag, stag, type, count;
    const void * ptr;
    int xx;

    /*@-mods@*/ /* FIX: undocumented modification of h */
    for (hi = headerInitIterator(h);
    /*@=mods@*/
        headerNextIterator(hi, &tag, &type, &ptr, &count);
        ptr = hfd(ptr, type))
    {
	switch (tag) {
	case RPMTAG_SIGSIZE:
	    stag = RPMSIGTAG_SIZE;
	    /*@switchbreak@*/ break;
	case RPMTAG_SIGLEMD5_1:
	    stag = RPMSIGTAG_LEMD5_1;
	    /*@switchbreak@*/ break;
	case RPMTAG_SIGPGP:
	    stag = RPMSIGTAG_PGP;
	    /*@switchbreak@*/ break;
	case RPMTAG_SIGLEMD5_2:
	    stag = RPMSIGTAG_LEMD5_2;
	    /*@switchbreak@*/ break;
	case RPMTAG_SIGMD5:
	    stag = RPMSIGTAG_MD5;
	    /*@switchbreak@*/ break;
	case RPMTAG_SIGGPG:
	    stag = RPMSIGTAG_GPG;
	    /*@switchbreak@*/ break;
	case RPMTAG_SIGPGP5:
	    stag = RPMSIGTAG_PGP5;
	    /*@switchbreak@*/ break;
	case RPMTAG_ARCHIVESIZE:
	    stag = RPMSIGTAG_PAYLOADSIZE;
	    /*@switchbreak@*/ break;
	case RPMTAG_SHA1HEADER:
	case RPMTAG_DSAHEADER:
	case RPMTAG_RSAHEADER:
	default:
	    if (!(tag >= HEADER_SIGBASE && tag < HEADER_TAGBASE))
		continue;
	    stag = tag;
	    /*@switchbreak@*/ break;
	}
	if (ptr == NULL) continue;	/* XXX can't happen */
	if (!headerIsEntry(sig, stag))
	    xx = headerAddEntry(sig, stag, type, ptr, count);
    }
    hi = headerFreeIterator(hi);
    return sig;
}

/**
 * Retrieve package components from file handle.
 * @param fd		file handle
 * @param leadPtr	address of lead (or NULL)
 * @param sigs		address of signatures (or NULL)
 * @param hdrPtr	address of header (or NULL)
 * @return		rpmRC return code
 */
static rpmRC readPackageHeaders(FD_t fd,
		/*@null@*/ /*@out@*/ struct rpmlead * leadPtr, 
		/*@null@*/ /*@out@*/ Header * sigs,
		/*@null@*/ /*@out@*/ Header * hdrPtr)
	/*@modifies fd, *leadPtr, *sigs, *hdrPtr @*/
{
    Header hdrBlock;
    struct rpmlead leadBlock;
    Header * hdr = NULL;
    struct rpmlead * lead;
    char * defaultPrefix;
    struct stat sb;
    rpmRC rc;

    hdr = hdrPtr ? hdrPtr : &hdrBlock;
    lead = leadPtr ? leadPtr : &leadBlock;

    memset(&sb, 0, sizeof(sb));
    (void) fstat(Fileno(fd), &sb);
    /* if fd points to a socket, pipe, etc, sb.st_size is *always* zero */
    if (S_ISREG(sb.st_mode) && sb.st_size < sizeof(*lead)) return 1;

    if (readLead(fd, lead))
	return RPMRC_FAIL;

    if (lead->magic[0] != RPMLEAD_MAGIC0 || lead->magic[1] != RPMLEAD_MAGIC1 ||
	lead->magic[2] != RPMLEAD_MAGIC2 || lead->magic[3] != RPMLEAD_MAGIC3) {
	return RPMRC_BADMAGIC;
    }

    switch (lead->major) {
    case 1:
	rpmError(RPMERR_NEWPACKAGE,
	    _("packaging version 1 is not supported by this version of RPM\n"));
	return RPMRC_FAIL;
	/*@notreached@*/ break;
    case 2:
    case 3:
    case 4:
	rc = rpmReadSignature(fd, sigs, lead->signature_type);
	if (rc == RPMRC_FAIL)
	    return rc;
	*hdr = headerRead(fd, (lead->major >= 3)
			  ? HEADER_MAGIC_YES : HEADER_MAGIC_NO);
	if (*hdr == NULL) {
	    if (sigs != NULL)
		*sigs = rpmFreeSignature(*sigs);
	    return RPMRC_FAIL;
	}

	/*
	 * We don't use these entries (and rpm >= 2 never has) and they are
	 * pretty misleading. Let's just get rid of them so they don't confuse
	 * anyone.
	 */
	if (headerIsEntry(*hdr, RPMTAG_FILEUSERNAME))
	    (void) headerRemoveEntry(*hdr, RPMTAG_FILEUIDS);
	if (headerIsEntry(*hdr, RPMTAG_FILEGROUPNAME))
	    (void) headerRemoveEntry(*hdr, RPMTAG_FILEGIDS);

	/*
	 * We switched the way we do relocateable packages. We fix some of
	 * it up here, though the install code still has to be a bit 
	 * careful. This fixup makes queries give the new values though,
	 * which is quite handy.
	 */
	if (headerGetEntry(*hdr, RPMTAG_DEFAULTPREFIX, NULL,
			   (void **) &defaultPrefix, NULL))
	{
	    defaultPrefix =
		stripTrailingChar(alloca_strdup(defaultPrefix), '/');
	    (void) headerAddEntry(*hdr, RPMTAG_PREFIXES, RPM_STRING_ARRAY_TYPE,
			   &defaultPrefix, 1); 
	}

	/*
	 * The file list was moved to a more compressed format which not
	 * only saves memory (nice), but gives fingerprinting a nice, fat
	 * speed boost (very nice). Go ahead and convert old headers to
	 * the new style (this is a noop for new headers).
	 */
	if (lead->major < 4)
	    compressFilelist(*hdr);

    /* XXX binary rpms always have RPMTAG_SOURCERPM, source rpms do not */
        if (lead->type == RPMLEAD_SOURCE) {
	    int_32 one = 1;
	    if (!headerIsEntry(*hdr, RPMTAG_SOURCEPACKAGE))
	    	(void)headerAddEntry(*hdr, RPMTAG_SOURCEPACKAGE, RPM_INT32_TYPE,
				&one, 1);
	} else if (lead->major < 4) {
	    /* Retrofit "Provide: name = EVR" for binary packages. */
	    providePackageNVR(*hdr);
	}
	break;

    default:
	rpmError(RPMERR_NEWPACKAGE, _("only packaging with major numbers <= 4 "
		"is supported by this version of RPM\n"));
	return RPMRC_FAIL;
	/*@notreached@*/ break;
    } 

    if (hdrPtr == NULL)
	*hdr = headerFree(*hdr);
    
    return RPMRC_OK;
}

rpmRC rpmReadPackageInfo(FD_t fd, Header * sigp, Header * hdrp)
{
    rpmRC rc = readPackageHeaders(fd, NULL, sigp, hdrp);
    if (rc != RPMRC_OK)
	return rc;
    if (hdrp == NULL || sigp == NULL)
	return rc;
    if (*hdrp && *sigp)
	headerMergeLegacySigs(*hdrp, *sigp);
    return rc;
}

rpmRC rpmReadPackageHeader(FD_t fd, Header * hdrp, int * isSource, int * major,
		  int * minor)
{
    struct rpmlead lead;
    Header sig = NULL;
    rpmRC rc = readPackageHeaders(fd, &lead, &sig, hdrp);

    if (rc != RPMRC_OK)
	goto exit;

    if (hdrp && *hdrp && sig) {
	headerMergeLegacySigs(*hdrp, sig);
	sig = rpmFreeSignature(sig);
    }
   
    if (isSource) *isSource = lead.type == RPMLEAD_SOURCE;
    /*@-mods@*/
    if (major) *major = lead.major;
    if (minor) *minor = lead.minor;
    /*@=mods@*/
   
exit:
    return rc;
}
