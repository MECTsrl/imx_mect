/** \ingroup rpmcli
 * \file lib/rpminstall.c
 */

#include "system.h"

#include <rpmcli.h>

#include "manifest.h"
#include "misc.h"	/* XXX for rpmGlob() */
#include "debug.h"

/*@access rpmTransactionSet @*/	/* XXX compared with NULL */
/*@access rpmProblemSet @*/	/* XXX compared with NULL */
/*@access Header @*/		/* XXX compared with NULL */
/*@access rpmdb @*/		/* XXX compared with NULL */
/*@access FD_t @*/		/* XXX compared with NULL */
/*@access IDTX @*/
/*@access IDT @*/

/*@unchecked@*/
static int hashesPrinted = 0;

/*@unchecked@*/
int packagesTotal = 0;
/*@unchecked@*/
static int progressTotal = 0;
/*@unchecked@*/
static int progressCurrent = 0;

/**
 */
static void printHash(const unsigned long amount, const unsigned long total)
	/*@globals hashesPrinted, progressCurrent, fileSystem @*/
	/*@modifies hashesPrinted, progressCurrent, fileSystem @*/
{
    int hashesNeeded;
    int hashesTotal = 50;

    if (isatty (STDOUT_FILENO))
	hashesTotal = 44;

    if (hashesPrinted != hashesTotal) {
	hashesNeeded = hashesTotal * (total ? (((float) amount) / total) : 1);
	while (hashesNeeded > hashesPrinted) {
	    if (isatty (STDOUT_FILENO)) {
		int i;
		for (i = 0; i < hashesPrinted; i++) (void) putchar ('#');
		for (; i < hashesTotal; i++) (void) putchar (' ');
		fprintf(stdout, "(%3d%%)",
			(int)(100 * (total ? (((float) amount) / total) : 1)));
		for (i = 0; i < (hashesTotal + 6); i++) (void) putchar ('\b');
	    } else
		fprintf(stdout, "#");

	    hashesPrinted++;
	}
	(void) fflush(stdout);
	hashesPrinted = hashesNeeded;

	if (hashesPrinted == hashesTotal) {
	    int i;
	    progressCurrent++;
	    if (isatty(STDOUT_FILENO)) {
	        for (i = 1; i < hashesPrinted; i++) (void) putchar ('#');
		fprintf(stdout, " [%3d%%]", (int)(100 * (progressTotal ?
			(((float) progressCurrent) / progressTotal) : 1)));
	    }
	    fprintf(stdout, "\n");
	}
	(void) fflush(stdout);
    }
}

void * rpmShowProgress(/*@null@*/ const void * arg,
			const rpmCallbackType what,
			const unsigned long amount,
			const unsigned long total,
			/*@null@*/ const void * pkgKey,
			/*@null@*/ void * data)
	/*@globals hashesPrinted, progressCurrent, progressTotal,
		fileSystem @*/
	/*@modifies hashesPrinted, progressCurrent, progressTotal,
		fileSystem @*/
{
    /*@-castexpose@*/
    Header h = (Header) arg;
    /*@=castexpose@*/
    char * s;
    int flags = (int) ((long)data);
    void * rc = NULL;
    const char * filename = pkgKey;
    static FD_t fd = NULL;

    switch (what) {
    case RPMCALLBACK_INST_OPEN_FILE:
	if (filename == NULL || filename[0] == '\0')
	    return NULL;
	fd = Fopen(filename, "r.ufdio");
	if (fd)
	    fd = fdLink(fd, "persist (showProgress)");
	return fd;
	/*@notreached@*/ break;

    case RPMCALLBACK_INST_CLOSE_FILE:
	fd = fdFree(fd, "persist (showProgress)");
	if (fd) {
	    (void) Fclose(fd);
	    fd = NULL;
	}
	break;

    case RPMCALLBACK_INST_START:
	hashesPrinted = 0;
	if (h == NULL || !(flags & INSTALL_LABEL))
	    break;
	if (flags & INSTALL_HASH) {
	    s = headerSprintf(h, "%{NAME}",
				rpmTagTable, rpmHeaderFormats, NULL);
	    if (isatty (STDOUT_FILENO))
		fprintf(stdout, "%4d:%-23.23s", progressCurrent + 1, s);
	    else
		fprintf(stdout, "%-28.28s", s);
	    (void) fflush(stdout);
	    s = _free(s);
	} else {
	    s = headerSprintf(h, "%{NAME}-%{VERSION}-%{RELEASE}",
				  rpmTagTable, rpmHeaderFormats, NULL);
	    fprintf(stdout, "%s\n", s);
	    (void) fflush(stdout);
	    s = _free(s);
	}
	break;

    case RPMCALLBACK_TRANS_PROGRESS:
    case RPMCALLBACK_INST_PROGRESS:
	if (flags & INSTALL_PERCENT)
	    fprintf(stdout, "%%%% %f\n", (double) (total
				? ((((float) amount) / total) * 100)
				: 100.0));
	else if (flags & INSTALL_HASH)
	    printHash(amount, total);
	(void) fflush(stdout);
	break;

    case RPMCALLBACK_TRANS_START:
	hashesPrinted = 0;
	progressTotal = 1;
	progressCurrent = 0;
	if (!(flags & INSTALL_LABEL))
	    break;
	if (flags & INSTALL_HASH)
	    fprintf(stdout, "%-28s", _("Preparing..."));
	else
	    fprintf(stdout, "%s\n", _("Preparing packages for installation..."));
	(void) fflush(stdout);
	break;

    case RPMCALLBACK_TRANS_STOP:
	if (flags & INSTALL_HASH)
	    printHash(1, 1);	/* Fixes "preparing..." progress bar */
	progressTotal = packagesTotal;
	progressCurrent = 0;
	break;

    case RPMCALLBACK_UNINST_PROGRESS:
    case RPMCALLBACK_UNINST_START:
    case RPMCALLBACK_UNINST_STOP:
    case RPMCALLBACK_UNPACK_ERROR:
    case RPMCALLBACK_CPIO_ERROR:
    default:
	/* ignore */
	break;
    }

    return rc;
}	

typedef /*@only@*/ /*@null@*/ const char * str_t;

struct rpmEIU {
/*@only@*/ rpmTransactionSet ts;
/*@only@*/ /*@null@*/ rpmdb db;
    Header h;
    FD_t fd;
    int numFailed;
    int numPkgs;
/*@only@*/ str_t * pkgURL;
/*@dependent@*/ /*@null@*/ str_t * fnp;
/*@only@*/ char * pkgState;
    int prevx;
    int pkgx;
    int numRPMS;
    int numSRPMS;
/*@only@*/ /*@null@*/ str_t * sourceURL;
    int isSource;
    int argc;
/*@only@*/ /*@null@*/ str_t * argv;
/*@temp@*/ rpmRelocation * relocations;
    rpmRC rpmrc;
};

/** @todo Generalize --freshen policies. */
int rpmInstall(const char * rootdir, const char ** fileArgv,
		rpmtransFlags transFlags,
		rpmInstallInterfaceFlags interfaceFlags,
		rpmprobFilterFlags probFilter,
		rpmRelocation * relocations)
{
    struct rpmEIU * eiu = alloca(sizeof(*eiu));
    int notifyFlags = interfaceFlags | (rpmIsVerbose() ? INSTALL_LABEL : 0 );
    /*@only@*/ /*@null@*/ const char * fileURL = NULL;
    int stopInstall = 0;
    const char ** av = NULL;
    int ac = 0;
    int rc;
    int xx;
    int i;

    if (fileArgv == NULL) return 0;

    memset(eiu, 0, sizeof(*eiu));
    eiu->numPkgs = 0;
    eiu->prevx = 0;
    eiu->pkgx = 0;

    if ((eiu->relocations = relocations) != NULL) {
	while (eiu->relocations->oldPath)
	    eiu->relocations++;
	if (eiu->relocations->newPath == NULL)
	    eiu->relocations = NULL;
    }

    /* Build fully globbed list of arguments in argv[argc]. */
    /*@-branchstate@*/
    /*@-temptrans@*/
    for (eiu->fnp = fileArgv; *eiu->fnp != NULL; eiu->fnp++) {
    /*@=temptrans@*/
	av = _free(av);	ac = 0;
	rc = rpmGlob(*eiu->fnp, &ac, &av);
	if (rc || ac == 0) continue;

	eiu->argv = xrealloc(eiu->argv, (eiu->argc+ac+1) * sizeof(*eiu->argv));
	memcpy(eiu->argv+eiu->argc, av, ac * sizeof(*av));
	eiu->argc += ac;
	eiu->argv[eiu->argc] = NULL;
    }
    /*@=branchstate@*/
    av = _free(av);	ac = 0;

restart:
    /* Allocate sufficient storage for next set of args. */
    if (eiu->pkgx >= eiu->numPkgs) {
	eiu->numPkgs = eiu->pkgx + eiu->argc;
	eiu->pkgURL = xrealloc(eiu->pkgURL,
			(eiu->numPkgs + 1) * sizeof(*eiu->pkgURL));
	memset(eiu->pkgURL + eiu->pkgx, 0,
			((eiu->argc + 1) * sizeof(*eiu->pkgURL)));
	eiu->pkgState = xrealloc(eiu->pkgState,
			(eiu->numPkgs + 1) * sizeof(*eiu->pkgState));
	memset(eiu->pkgState + eiu->pkgx, 0,
			((eiu->argc + 1) * sizeof(*eiu->pkgState)));
    }

    /* Retrieve next set of args, cache on local storage. */
    for (i = 0; i < eiu->argc; i++) {
	fileURL = _free(fileURL);
	fileURL = eiu->argv[i];
	eiu->argv[i] = NULL;

	switch (urlIsURL(fileURL)) {
	case URL_IS_FTP:
	case URL_IS_HTTP:
	{   const char *tfn;

	    if (rpmIsVerbose())
		fprintf(stdout, _("Retrieving %s\n"), fileURL);

	    {	char tfnbuf[64];
		strcpy(tfnbuf, "rpm-xfer.XXXXXX");
		(void) mktemp(tfnbuf);
		tfn = rpmGenPath(rootdir, "%{_tmppath}/", tfnbuf);
	    }

	    /* XXX undefined %{name}/%{version}/%{release} here */
	    /* XXX %{_tmpdir} does not exist */
	    rpmMessage(RPMMESS_DEBUG, _(" ... as %s\n"), tfn);
	    rc = urlGetFile(fileURL, tfn);
	    if (rc < 0) {
		rpmMessage(RPMMESS_ERROR,
			_("skipping %s - transfer failed - %s\n"),
			fileURL, ftpStrerror(rc));
		eiu->numFailed++;
		eiu->pkgURL[eiu->pkgx] = NULL;
		tfn = _free(tfn);
		/*@switchbreak@*/ break;
	    }
	    eiu->pkgState[eiu->pkgx] = 1;
	    eiu->pkgURL[eiu->pkgx] = tfn;
	    eiu->pkgx++;
	}   /*@switchbreak@*/ break;
	case URL_IS_PATH:
	default:
	    eiu->pkgURL[eiu->pkgx] = fileURL;
	    fileURL = NULL;
	    eiu->pkgx++;
	    /*@switchbreak@*/ break;
	}
    }
    fileURL = _free(fileURL);

    if (eiu->numFailed) goto exit;

    /* Continue processing file arguments, building transaction set. */
    for (eiu->fnp = eiu->pkgURL+eiu->prevx;
	 *eiu->fnp != NULL;
	 eiu->fnp++, eiu->prevx++)
    {
	const char * fileName;

	rpmMessage(RPMMESS_DEBUG, "============== %s\n", *eiu->fnp);
	(void) urlPath(*eiu->fnp, &fileName);

	/* Try to read the header from a package file. */
	eiu->fd = Fopen(*eiu->fnp, "r.ufdio");
	if (eiu->fd == NULL || Ferror(eiu->fd)) {
	    rpmError(RPMERR_OPEN, _("open of %s failed: %s\n"), *eiu->fnp,
			Fstrerror(eiu->fd));
	    if (eiu->fd) {
		xx = Fclose(eiu->fd);
		eiu->fd = NULL;
	    }
	    eiu->numFailed++; *eiu->fnp = NULL;
	    continue;
	}

	/*@-mustmod@*/	/* LCL: segfault */
	eiu->rpmrc = rpmReadPackageHeader(eiu->fd, &eiu->h,
				&eiu->isSource, NULL, NULL);
	/*@=mustmod@*/
	xx = Fclose(eiu->fd);
	eiu->fd = NULL;

	if (eiu->rpmrc == RPMRC_FAIL || eiu->rpmrc == RPMRC_SHORTREAD) {
	    eiu->numFailed++; *eiu->fnp = NULL;
	    continue;
	}

	if (eiu->isSource &&
		(eiu->rpmrc == RPMRC_OK || eiu->rpmrc == RPMRC_BADSIZE))
	{
	    rpmMessage(RPMMESS_DEBUG, "\tadded source package [%d]\n",
		eiu->numSRPMS);
	    eiu->sourceURL = xrealloc(eiu->sourceURL,
				(eiu->numSRPMS + 2) * sizeof(*eiu->sourceURL));
	    eiu->sourceURL[eiu->numSRPMS] = *eiu->fnp;
	    *eiu->fnp = NULL;
	    eiu->numSRPMS++;
	    eiu->sourceURL[eiu->numSRPMS] = NULL;
	    continue;
	}

	if (eiu->rpmrc == RPMRC_OK || eiu->rpmrc == RPMRC_BADSIZE) {
	    if (eiu->db == NULL) {
		int mode = (transFlags & RPMTRANS_FLAG_TEST)
				? O_RDONLY : (O_RDWR | O_CREAT);

		if (rpmdbOpen(rootdir, &eiu->db, mode, 0644)) {
		    const char *dn;
		    dn = rpmGetPath( (rootdir ? rootdir : ""),
					"%{_dbpath}", NULL);
		    rpmMessage(RPMMESS_ERROR,
				_("cannot open Packages database in %s\n"), dn);
		    dn = _free(dn);
		    eiu->numFailed++; *eiu->fnp = NULL;
		    break;
		}
		/*@-onlytrans@*/
		eiu->ts = rpmtransCreateSet(eiu->db, rootdir);
		/*@=onlytrans@*/
	    }

	    if (eiu->relocations) {
		const char ** paths;
		int pft;
		int c;

		if (headerGetEntry(eiu->h, RPMTAG_PREFIXES, &pft,
				       (void **) &paths, &c) && (c == 1)) {
		    eiu->relocations->oldPath = xstrdup(paths[0]);
		    paths = headerFreeData(paths, pft);
		} else {
		    const char * name;
		    xx = headerNVR(eiu->h, &name, NULL, NULL);
		    rpmMessage(RPMMESS_ERROR,
			       _("package %s is not relocateable\n"), name);
		    eiu->numFailed++;
		    goto exit;
		    /*@notreached@*/
		}
	    }

	    /* On --freshen, verify package is installed and newer */
	    if (interfaceFlags & INSTALL_FRESHEN) {
		rpmdbMatchIterator mi;
		const char * name;
		Header oldH;
		int count;

		xx = headerNVR(eiu->h, &name, NULL, NULL);
		/*@-onlytrans@*/
		mi = rpmdbInitIterator(eiu->db, RPMTAG_NAME, name, 0);
		/*@=onlytrans@*/
		count = rpmdbGetIteratorCount(mi);
		while ((oldH = rpmdbNextIterator(mi)) != NULL) {
		    if (rpmVersionCompare(oldH, eiu->h) < 0)
			/*@innercontinue@*/ continue;
		    /* same or newer package already installed */
		    count = 0;
		    /*@innerbreak@*/ break;
		}
		mi = rpmdbFreeIterator(mi);
		if (count == 0) {
		    eiu->h = headerFree(eiu->h);
		    continue;
		}
		/* Package is newer than those currently installed. */
	    }

	    rc = rpmtransAddPackage(eiu->ts, eiu->h, NULL, fileName,
			       (interfaceFlags & INSTALL_UPGRADE) != 0,
			       relocations);
	    /* XXX reference held by transaction set */
	    eiu->h = headerFree(eiu->h);
	    if (eiu->relocations)
		eiu->relocations->oldPath = _free(eiu->relocations->oldPath);

	    switch(rc) {
	    case 0:
		rpmMessage(RPMMESS_DEBUG, "\tadded binary package [%d]\n",
			eiu->numRPMS);
		/*@switchbreak@*/ break;
	    case 1:
		rpmMessage(RPMMESS_ERROR,
			    _("error reading from file %s\n"), *eiu->fnp);
		eiu->numFailed++;
		goto exit;
		/*@notreached@*/ /*@switchbreak@*/ break;
	    case 2:
		rpmMessage(RPMMESS_ERROR,
			    _("file %s requires a newer version of RPM\n"),
			    *eiu->fnp);
		eiu->numFailed++;
		goto exit;
		/*@notreached@*/ /*@switchbreak@*/ break;
	    }

	    eiu->numRPMS++;
	    continue;
	}

	if (eiu->rpmrc != RPMRC_BADMAGIC) {
	    rpmMessage(RPMMESS_ERROR, _("%s cannot be installed\n"), *eiu->fnp);
	    eiu->numFailed++; *eiu->fnp = NULL;
	    break;
	}

	/* Try to read a package manifest. */
	eiu->fd = Fopen(*eiu->fnp, "r.fpio");
	if (eiu->fd == NULL || Ferror(eiu->fd)) {
	    rpmError(RPMERR_OPEN, _("open of %s failed: %s\n"), *eiu->fnp,
			Fstrerror(eiu->fd));
	    if (eiu->fd) {
		xx = Fclose(eiu->fd);
		eiu->fd = NULL;
	    }
	    eiu->numFailed++; *eiu->fnp = NULL;
	    break;
	}

	/* Read list of packages from manifest. */
	rc = rpmReadPackageManifest(eiu->fd, &eiu->argc, &eiu->argv);
	if (rc)
	    rpmError(RPMERR_MANIFEST, _("%s: read manifest failed: %s\n"),
			*eiu->fnp, Fstrerror(eiu->fd));
	xx = Fclose(eiu->fd);
	eiu->fd = NULL;

	/* If successful, restart the query loop. */
	if (rc == 0) {
	    eiu->prevx++;
	    goto restart;
	}

	eiu->numFailed++; *eiu->fnp = NULL;
	break;
    }

    rpmMessage(RPMMESS_DEBUG, _("found %d source and %d binary packages\n"),
		eiu->numSRPMS, eiu->numRPMS);

    if (eiu->numFailed) goto exit;

    if (eiu->numRPMS && !(interfaceFlags & INSTALL_NODEPS)) {
	rpmDependencyConflict conflicts;
	int numConflicts;

	if (rpmdepCheck(eiu->ts, &conflicts, &numConflicts)) {
	    eiu->numFailed = eiu->numPkgs;
	    stopInstall = 1;
	}

	/*@-branchstate@*/
	if (!stopInstall && conflicts) {
	    rpmMessage(RPMMESS_ERROR, _("failed dependencies:\n"));
	    printDepProblems(stderr, conflicts, numConflicts);
	    conflicts = rpmdepFreeConflicts(conflicts, numConflicts);
	    eiu->numFailed = eiu->numPkgs;
	    stopInstall = 1;
	}
	/*@=branchstate@*/
    }

    if (eiu->numRPMS && !(interfaceFlags & INSTALL_NOORDER)) {
	if (rpmdepOrder(eiu->ts)) {
	    eiu->numFailed = eiu->numPkgs;
	    stopInstall = 1;
	}
    }

    if (eiu->numRPMS && !stopInstall) {
	rpmProblemSet probs = NULL;

	packagesTotal = eiu->numRPMS + eiu->numSRPMS;

	rpmMessage(RPMMESS_DEBUG, _("installing binary packages\n"));
	rc = rpmRunTransactions(eiu->ts, rpmShowProgress,
			(void *) ((long)notifyFlags),
		 	NULL, &probs, transFlags, probFilter);

	if (rc < 0) {
	    eiu->numFailed += eiu->numRPMS;
	} else if (rc > 0) {
	    eiu->numFailed += rc;
	    rpmProblemSetPrint(stderr, probs);
	}

	if (probs != NULL) rpmProblemSetFree(probs);
    }

    if (eiu->numSRPMS && !stopInstall) {
	if (eiu->sourceURL != NULL)
	for (i = 0; i < eiu->numSRPMS; i++) {
	    if (eiu->sourceURL[i] == NULL) continue;
	    eiu->fd = Fopen(eiu->sourceURL[i], "r.ufdio");
	    if (eiu->fd == NULL || Ferror(eiu->fd)) {
		rpmMessage(RPMMESS_ERROR, _("cannot open file %s: %s\n"),
			   eiu->sourceURL[i], Fstrerror(eiu->fd));
		if (eiu->fd) {
		    xx = Fclose(eiu->fd);
		    eiu->fd = NULL;
		}
		continue;
	    }

	    if (!(transFlags & RPMTRANS_FLAG_TEST)) {
		eiu->rpmrc = rpmInstallSourcePackage(rootdir, eiu->fd, NULL,
			rpmShowProgress, (void *) ((long)notifyFlags), NULL);
		if (eiu->rpmrc != RPMRC_OK) eiu->numFailed++;
	    }

	    xx = Fclose(eiu->fd);
	    eiu->fd = NULL;
	}
    }

exit:
    eiu->ts = rpmtransFree(eiu->ts);
    if (eiu->pkgURL != NULL)
    for (i = 0; i < eiu->numPkgs; i++) {
	if (eiu->pkgURL[i] == NULL) continue;
	if (eiu->pkgState[i] == 1)
	    (void) Unlink(eiu->pkgURL[i]);
	eiu->pkgURL[i] = _free(eiu->pkgURL[i]);
    }
    eiu->pkgState = _free(eiu->pkgState);
    eiu->pkgURL = _free(eiu->pkgURL);
    eiu->argv = _free(eiu->argv);
    if (eiu->db != NULL) {
	xx = rpmdbClose(eiu->db);
	eiu->db = NULL;
    }
    return eiu->numFailed;
}

int rpmErase(const char * rootdir, const char ** argv,
		rpmtransFlags transFlags,
		rpmEraseInterfaceFlags interfaceFlags)
{
    rpmdb db;
    int mode;
    int count;
    const char ** arg;
    int numFailed = 0;
    rpmTransactionSet ts;
    rpmDependencyConflict conflicts;
    int numConflicts;
    int stopUninstall = 0;
    int numPackages = 0;
    rpmProblemSet probs;

    if (argv == NULL) return 0;

    if (transFlags & RPMTRANS_FLAG_TEST)
	mode = O_RDONLY;
    else
	mode = O_RDWR | O_EXCL;
	
    if (rpmdbOpen(rootdir, &db, mode, 0644)) {
	const char *dn;
	dn = rpmGetPath( (rootdir ? rootdir : ""), "%{_dbpath}", NULL);
	rpmMessage(RPMMESS_ERROR, _("cannot open %s/packages.rpm\n"), dn);
	dn = _free(dn);
	return -1;
    }

    ts = rpmtransCreateSet(db, rootdir);
    for (arg = argv; *arg; arg++) {
	rpmdbMatchIterator mi;

	/* XXX HACK to get rpmdbFindByLabel out of the API */
	mi = rpmdbInitIterator(db, RPMDBI_LABEL, *arg, 0);
	count = rpmdbGetIteratorCount(mi);
	if (count <= 0) {
	    rpmMessage(RPMMESS_ERROR, _("package %s is not installed\n"), *arg);
	    numFailed++;
	} else if (!(count == 1 || (interfaceFlags & UNINSTALL_ALLMATCHES))) {
	    rpmMessage(RPMMESS_ERROR, _("\"%s\" specifies multiple packages\n"),
			*arg);
	    numFailed++;
	} else {
	    Header h;	/* XXX iterator owns the reference */
	    while ((h = rpmdbNextIterator(mi)) != NULL) {
		unsigned int recOffset = rpmdbGetIteratorOffset(mi);
		if (recOffset) {
		    (void) rpmtransRemovePackage(ts, recOffset);
		    numPackages++;
		}
	    }
	}
	mi = rpmdbFreeIterator(mi);
    }

    if (!(interfaceFlags & UNINSTALL_NODEPS)) {
	if (rpmdepCheck(ts, &conflicts, &numConflicts)) {
	    numFailed = numPackages;
	    stopUninstall = 1;
	}

	/*@-branchstate@*/
	if (!stopUninstall && conflicts) {
	    rpmMessage(RPMMESS_ERROR, _("removing these packages would break "
			      "dependencies:\n"));
	    printDepProblems(stderr, conflicts, numConflicts);
	    conflicts = rpmdepFreeConflicts(conflicts, numConflicts);
	    numFailed += numPackages;
	    stopUninstall = 1;
	}
	/*@=branchstate@*/
    }

    if (!stopUninstall) {
	transFlags |= RPMTRANS_FLAG_REVERSE;
	numFailed += rpmRunTransactions(ts, NULL, NULL, NULL, &probs,
					transFlags, 0);
    }

    ts = rpmtransFree(ts);
    (void) rpmdbClose(db);

    return numFailed;
}

int rpmInstallSource(const char * rootdir, const char * arg,
		const char ** specFile, char ** cookie)
{
    FD_t fd;
    int rc;

    fd = Fopen(arg, "r.ufdio");
    if (fd == NULL || Ferror(fd)) {
	rpmMessage(RPMMESS_ERROR, _("cannot open %s: %s\n"), arg, Fstrerror(fd));
	if (fd) (void) Fclose(fd);
	return 1;
    }

    if (rpmIsVerbose())
	fprintf(stdout, _("Installing %s\n"), arg);

    {
	/*@-mayaliasunique@*/
	rpmRC rpmrc = rpmInstallSourcePackage(rootdir, fd, specFile, NULL, NULL,
				 cookie);
	/*@=mayaliasunique@*/
	rc = (rpmrc == RPMRC_OK ? 0 : 1);
    }
    if (rc != 0) {
	rpmMessage(RPMMESS_ERROR, _("%s cannot be installed\n"), arg);
	/*@-unqualifiedtrans@*/
	if (specFile && *specFile)
	    *specFile = _free(*specFile);
	if (cookie && *cookie)
	    *cookie = _free(*cookie);
	/*@=unqualifiedtrans@*/
    }

    (void) Fclose(fd);

    return rc;
}

/*@unchecked@*/
static int reverse = -1;

/**
 */
static int IDTintcmp(const void * a, const void * b)
	/*@*/
{
    /*@-castexpose@*/
    IDT ap = (IDT)a;
    IDT bp = (IDT)b;
    /*@=castexpose@*/
    int rc = ((int)ap->val.u32 - (int)bp->val.u32);

    if (rc)
	return ( reverse * rc );
    return ( strcmp(ap->n, bp->n) );
}

IDTX IDTXfree(IDTX idtx)
{
    if (idtx) {
	int i;
	if (idtx->idt)
	for (i = 0; i < idtx->nidt; i++) {
	    IDT idt = idtx->idt + i;
	    idt->h = headerFree(idt->h);
	    idt->key = _free(idt->key);
	}
	idtx->idt = _free(idtx->idt);
	idtx = _free(idtx);
    }
    return NULL;
}

IDTX IDTXnew(void)
{
    IDTX idtx = xcalloc(1, sizeof(*idtx));
    idtx->delta = 10;
    idtx->size = sizeof(*((IDT)0));
    return idtx;
}

IDTX IDTXgrow(IDTX idtx, int need)
{
    if (need < 0) return NULL;
    if (idtx == NULL)
	idtx = IDTXnew();
    if (need == 0) return idtx;

    if ((idtx->nidt + need) > idtx->alloced) {
	while (need > 0) {
	    idtx->alloced += idtx->delta;
	    need -= idtx->delta;
	}
	idtx->idt = xrealloc(idtx->idt, (idtx->alloced * idtx->size) );
    }
    return idtx;
}

IDTX IDTXsort(IDTX idtx)
{
    if (idtx != NULL && idtx->idt != NULL && idtx->nidt > 0)
	qsort(idtx->idt, idtx->nidt, idtx->size, IDTintcmp);
    return idtx;
}

IDTX IDTXload(rpmdb db, rpmTag tag)
{
    IDTX idtx = NULL;
    rpmdbMatchIterator mi;
    HGE_t hge = (HGE_t) headerGetEntry;
    Header h;

    mi = rpmdbInitIterator(db, tag, NULL, 0);
    /*@-branchstate@*/
    while ((h = rpmdbNextIterator(mi)) != NULL) {
	rpmTagType type = RPM_NULL_TYPE;
	int_32 count = 0;
	int_32 * tidp;

	tidp = NULL;
	if (!hge(h, tag, &type, (void **)&tidp, &count) || tidp == NULL)
	    continue;

	if (type == RPM_INT32_TYPE && (*tidp == 0 || *tidp == -1))
	    continue;

	idtx = IDTXgrow(idtx, 1);
	if (idtx == NULL)
	    continue;
	if (idtx->idt == NULL)
	    continue;

	{   IDT idt;
	    /*@-nullderef@*/
	    idt = idtx->idt + idtx->nidt;
	    /*@=nullderef@*/
	    idt->h = headerLink(h);
	    (void) headerNVR(idt->h, &idt->n, &idt->v, &idt->r);
	    idt->key = NULL;
	    idt->instance = rpmdbGetIteratorOffset(mi);
	    idt->val.u32 = *tidp;
	}
	idtx->nidt++;
    }
    /*@=branchstate@*/
    mi = rpmdbFreeIterator(mi);

    return IDTXsort(idtx);
}

IDTX IDTXglob(const char * globstr, rpmTag tag)
{
    IDTX idtx = NULL;
    HGE_t hge = (HGE_t) headerGetEntry;
    Header h;
    int_32 * tidp;
    FD_t fd;
    const char ** av = NULL;
    int ac = 0;
    int rc;
    int i;

    av = NULL;	ac = 0;
    rc = rpmGlob(globstr, &ac, &av);

    if (rc == 0)
    for (i = 0; i < ac; i++) {
	rpmTagType type;
	int_32 count;
	int isSource;
	rpmRC rpmrc;

	fd = Fopen(av[i], "r.ufdio");
	if (fd == NULL || Ferror(fd)) {
            rpmError(RPMERR_OPEN, _("open of %s failed: %s\n"), av[i],
                        Fstrerror(fd));
	    if (fd) (void) Fclose(fd);
	    continue;
	}

	/*@-mustmod@*/	/* LCL: segfault */
	rpmrc = rpmReadPackageHeader(fd, &h, &isSource, NULL, NULL);
	/*@=mustmod@*/
	if (rpmrc != RPMRC_OK || isSource) {
	    (void) Fclose(fd);
	    continue;
	}

	tidp = NULL;
	/*@-branchstate@*/
	if (hge(h, tag, &type, (void **) &tidp, &count) && tidp) {

	    idtx = IDTXgrow(idtx, 1);
	    if (idtx == NULL || idtx->idt == NULL) {
		h = headerFree(h);
		(void) Fclose(fd);
		continue;
	    }
	    {	IDT idt;
		idt = idtx->idt + idtx->nidt;
		idt->h = headerLink(h);
		(void) headerNVR(idt->h, &idt->n, &idt->v, &idt->r);
		idt->key = xstrdup(av[i]);
		idt->instance = 0;
		idt->val.u32 = *tidp;
	    }
	    idtx->nidt++;
	}
	/*@=branchstate@*/

	h = headerFree(h);
	(void) Fclose(fd);
    }

    for (i = 0; i < ac; i++)
	av[i] = _free(av[i]);
    av = _free(av);	ac = 0;

    return IDTXsort(idtx);
}

int rpmRollback(struct rpmInstallArguments_s * ia, const char ** argv)
{
    rpmdb db = NULL;
    rpmTransactionSet ts = NULL;
    rpmDependencyConflict conflicts = NULL;
    int numConflicts = 0;
    rpmProblemSet probs = NULL;
    IDTX itids = NULL;
    IDTX rtids = NULL;
    unsigned thistid = 0xffffffff;
    unsigned prevtid;
    time_t tid;
    IDT rp;
    int nrids = 0;
    IDT ip;
    int niids = 0;
    int packagesIn;
    int packagesOut;
    int rc;
    int i;
    int ifmask= (INSTALL_UPGRADE|INSTALL_FRESHEN|INSTALL_INSTALL|INSTALL_ERASE);

    if (argv != NULL && *argv != NULL) {
	rc = -1;
	goto exit;
    }

    rc = rpmdbOpen(ia->rootdir, &db, O_RDWR, 0644);
    if (rc != 0)
	goto exit;

    itids = IDTXload(db, RPMTAG_INSTALLTID);
    if (itids != NULL) {
	ip = itids->idt;
	niids = itids->nidt;
    } else {
	ip = NULL;
	niids = 0;
    }

    {	const char * globstr = rpmExpand("%{_repackage_dir}/*.rpm", NULL);
	if (globstr == NULL || *globstr == '%') {
	    globstr = _free(globstr);
	    rc = -1;
	    goto exit;
	}
	rtids = IDTXglob(globstr, RPMTAG_REMOVETID);
	if (rtids != NULL) {
	    rp = rtids->idt;
	    nrids = rtids->nidt;
	} else {
	    rp = NULL;
	    nrids = 0;
	}
	globstr = _free(globstr);
    }

    /* Run transactions until rollback goal is achieved. */
    do {
	prevtid = thistid;
	rc = 0;
	packagesTotal = 0;
	packagesIn = 0;
	packagesOut = 0;
	ia->installInterfaceFlags &= ~ifmask;

	/* Find larger of the remaining install/erase transaction id's. */
	thistid = 0;
	if (ip != NULL && ip->val.u32 > thistid)
	    thistid = ip->val.u32;
	if (rp != NULL && rp->val.u32 > thistid)
	    thistid = rp->val.u32;

	/* If we've achieved the rollback goal, then we're done. */
	if (thistid == 0 || thistid < ia->rbtid)
	    break;

	ts = rpmtransCreateSet(db, ia->rootdir);

	/* Install the previously erased packages for this transaction. */
	while (rp != NULL && rp->val.u32 == thistid) {

	    rpmMessage(RPMMESS_DEBUG, "\t+++ %s-%s-%s\t(from %s)\n", rp->n, rp->v, rp->r, basename(rp->key));

	    if (!(ia->installInterfaceFlags & ifmask))
		ia->installInterfaceFlags |= INSTALL_INSTALL;

	    rc = rpmtransAddPackage(ts, rp->h, NULL, rp->key,
			(ia->installInterfaceFlags & INSTALL_UPGRADE) != 0,
			ia->relocations);
	    if (rc != 0)
		goto exit;

	    packagesTotal++;
	    packagesIn++;

#ifdef	NOTYET
	    rp->h = headerFree(rp->h);
#endif
	    nrids--;
	    if (nrids > 0)
		rp++;
	    else
		rp = NULL;
	}

	/*
	 * XXX OK, let's prevent disaster right here, as rollbacks will merrily
	 * XXX erase everything in order to achieve the desired goal.
	 */
	if (packagesIn == 0)
	    break;

	/* Erase the previously installed packages for this transaction. */
	while (ip != NULL && ip->val.u32 == thistid) {

	    rpmMessage(RPMMESS_DEBUG,
			"\t--- %s-%s-%s\t(from rpmdb instance #%u)\n", ip->n, ip->v, ip->r, ip->instance);

	    if (!(ia->installInterfaceFlags & ifmask))
		ia->installInterfaceFlags |= INSTALL_ERASE;

	    rc = rpmtransRemovePackage(ts, ip->instance);
	    if (rc != 0)
		goto exit;

	    packagesTotal++;
	    packagesOut++;

#ifdef	NOTYET
	    ip->instance = 0;
#endif
	    niids--;
	    if (niids > 0)
		ip++;
	    else
		ip = NULL;
	}

	/* Anything to do? */
	if (packagesTotal <= 0)
	    break;

	tid = (time_t)thistid;
	rpmMessage(RPMMESS_DEBUG, _("rollback (+%d,-%d) packages to %s"),
			packagesIn, packagesOut, ctime(&tid));

	conflicts = NULL;
	numConflicts = 0;
	rc = rpmdepCheck(ts, &conflicts, &numConflicts);
	if (rc != 0) {
	    rpmMessage(RPMMESS_ERROR, _("failed dependencies:\n"));
	    printDepProblems(stderr, conflicts, numConflicts);
	    conflicts = rpmdepFreeConflicts(conflicts, numConflicts);
	    goto exit;
	}

	rc = rpmdepOrder(ts);
	if (rc != 0)
	    goto exit;

	probs = NULL;
	rc = rpmRunTransactions(ts,  rpmShowProgress,
		(void *) ((long)ia->installInterfaceFlags),
		NULL, &probs, ia->transFlags,
		(ia->probFilter|RPMPROB_FILTER_OLDPACKAGE));
	if (rc > 0) {
	    rpmProblemSetPrint(stderr, probs);
	    if (probs != NULL) rpmProblemSetFree(probs);
	    probs = NULL;
	}
	if (rc)
	    goto exit;

	ts = rpmtransFree(ts);

	/* Clean up after successful rollback. */
	if (!rpmIsDebug())
	for (i = 0; i < rtids->nidt; i++) {
	    IDT rrp = rtids->idt + i;
	    if (rrp->val.u32 != thistid)
		continue;
	    (void) unlink(rrp->key);
	}

    } while (1);

exit:
    ts = rpmtransFree(ts);

    if (db != NULL) (void) rpmdbClose(db);

    rtids = IDTXfree(rtids);
    itids = IDTXfree(itids);

    return rc;
}
