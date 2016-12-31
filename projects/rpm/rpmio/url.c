/*@-type@*/ /* LCL: function typedefs */
/** \ingroup rpmio
 * \file rpmio/url.c
 */

#include "system.h"

#include <netinet/in.h>

#include <rpmmacro.h>
#include <rpmmessages.h>
#include <rpmio_internal.h>

#include "debug.h"

/*@access FD_t@*/		/* XXX compared with NULL */
/*@access urlinfo@*/

#ifndef	IPPORT_FTP
#define	IPPORT_FTP	21
#endif
#ifndef	IPPORT_HTTP
#define	IPPORT_HTTP	80
#endif

/**
 */
/*@unchecked@*/
int _url_iobuf_size = RPMURL_IOBUF_SIZE;

/**
 */
/*@unchecked@*/
int _url_debug = 0;

#define	URLDBG(_f, _m, _x)	if ((_url_debug | (_f)) & (_m)) fprintf _x

#define URLDBGIO(_f, _x)	URLDBG((_f), RPMURL_DEBUG_IO, _x)
#define URLDBGREFS(_f, _x)	URLDBG((_f), RPMURL_DEBUG_REFS, _x)

/**
 */
/*@unchecked@*/
/*@only@*/ /*@null@*/
urlinfo *_url_cache = NULL;

/**
 */
/*@unchecked@*/
int _url_count = 0;

/**
 * Wrapper to free(3), hides const compilation noise, permit NULL, return NULL.
 * @param p		memory to free
 * @retval		NULL always
 */
/*@unused@*/ static inline /*@null@*/ void *
_free(/*@only@*/ /*@null@*/ const void * p) /*@modifies p@*/
{
    if (p != NULL)	free((void *)p);
    return NULL;
}

urlinfo XurlLink(urlinfo u, const char *msg, const char *file, unsigned line)
{
    URLSANE(u);
    u->nrefs++;
/*@-modfilesys@*/
URLDBGREFS(0, (stderr, "--> url %p ++ %d %s at %s:%u\n", u, u->nrefs, msg, file, line));
/*@=modfilesys@*/
    /*@-refcounttrans@*/ return u; /*@=refcounttrans@*/
}

urlinfo XurlNew(const char *msg, const char *file, unsigned line)
{
    urlinfo u;
    if ((u = xmalloc(sizeof(*u))) == NULL)
	return NULL;
    memset(u, 0, sizeof(*u));
    u->proxyp = -1;
    u->port = -1;
    u->urltype = URL_IS_UNKNOWN;
    u->ctrl = NULL;
    u->data = NULL;
    u->bufAlloced = 0;
    u->buf = NULL;
    u->httpHasRange = 1;
    u->httpVersion = 0;
    u->nrefs = 0;
    u->magic = URLMAGIC;
    return XurlLink(u, msg, file, line);
}

urlinfo XurlFree(urlinfo u, const char *msg, const char *file, unsigned line)
{
    int xx;

    URLSANE(u);
URLDBGREFS(0, (stderr, "--> url %p -- %d %s at %s:%u\n", u, u->nrefs, msg, file, line));
    if (--u->nrefs > 0)
	/*@-refcounttrans -retalias@*/ return u; /*@=refcounttrans =retalias@*/
    if (u->ctrl) {
#ifndef	NOTYET
	void * fp = fdGetFp(u->ctrl);
	/*@-branchstate@*/
	if (fp) {
	    fdPush(u->ctrl, fpio, fp, -1);   /* Push fpio onto stack */
	    (void) Fclose(u->ctrl);
	} else if (fdio->_fileno(u->ctrl) >= 0)
	    xx = fdio->close(u->ctrl);
	/*@=branchstate@*/
#else
	(void) Fclose(u->ctrl);
#endif

	u->ctrl = fdio->_fdderef(u->ctrl, "persist ctrl (urlFree)", file, line);
	/*@-usereleased@*/
	if (u->ctrl)
	    fprintf(stderr, _("warning: u %p ctrl %p nrefs != 0 (%s %s)\n"),
			u, u->ctrl, (u->host ? u->host : ""),
			(u->service ? u->service : ""));
	/*@=usereleased@*/
    }
    if (u->data) {
#ifndef	NOTYET
	void * fp = fdGetFp(u->data);
	if (fp) {
	    fdPush(u->data, fpio, fp, -1);   /* Push fpio onto stack */
	    (void) Fclose(u->data);
	} else if (fdio->_fileno(u->data) >= 0)
	    xx = fdio->close(u->data);
#else
	(void) Fclose(u->ctrl);
#endif

	u->data = fdio->_fdderef(u->data, "persist data (urlFree)", file, line);
	/*@-usereleased@*/
	if (u->data)
	    fprintf(stderr, _("warning: u %p data %p nrefs != 0 (%s %s)\n"),
			u, u->data, (u->host ? u->host : ""),
			(u->service ? u->service : ""));
	/*@=usereleased@*/
    }
    u->buf = _free(u->buf);
    u->url = _free(u->url);
    u->service = _free((void *)u->service);
    u->user = _free((void *)u->user);
    u->password = _free((void *)u->password);
    u->host = _free((void *)u->host);
    u->portstr = _free((void *)u->portstr);
    u->proxyu = _free((void *)u->proxyu);
    u->proxyh = _free((void *)u->proxyh);

    /*@-refcounttrans@*/ u = _free(u); /*@-refcounttrans@*/
    return NULL;
}

void urlFreeCache(void)
{
    if (_url_cache) {
	int i;
	for (i = 0; i < _url_count; i++) {
	    if (_url_cache[i] == NULL) continue;
	    _url_cache[i] = urlFree(_url_cache[i], "_url_cache");
	    if (_url_cache[i])
		fprintf(stderr,
			_("warning: _url_cache[%d] %p nrefs(%d) != 1 (%s %s)\n"),
			i, _url_cache[i], _url_cache[i]->nrefs,
			(_url_cache[i]->host ? _url_cache[i]->host : ""),
			(_url_cache[i]->service ? _url_cache[i]->service : ""));
	}
    }
    _url_cache = _free(_url_cache);
    _url_count = 0;
}

static int urlStrcmp(/*@null@*/ const char * str1, /*@null@*/ const char * str2)
	/*@*/
{
    if (str1 && str2)
	/*@-nullpass@*/		/* LCL: 2nd arg claims to be NULL */
	return strcmp(str1, str2);
	/*@=nullpass@*/
    if (str1 != str2)
	return -1;
    return 0;
}

/*@-mods@*/
static void urlFind(/*@null@*/ /*@in@*/ /*@out@*/ urlinfo * uret, int mustAsk)
	/*@globals rpmGlobalMacroContext,
		fileSystem@*/
	/*@modifies *uret, rpmGlobalMacroContext,
		fileSystem @*/
{
    urlinfo u;
    int ucx;
    int i = 0;

    if (uret == NULL)
	return;

    u = *uret;
    URLSANE(u);

    ucx = -1;
    for (i = 0; i < _url_count; i++) {
	urlinfo ou = NULL;
	if (_url_cache == NULL || (ou = _url_cache[i]) == NULL) {
	    if (ucx < 0)
		ucx = i;
	    continue;
	}

	/* Check for cache-miss condition. A cache miss is
	 *    a) both items are not NULL and don't compare.
	 *    b) either of the items is not NULL.
	 */
	if (urlStrcmp(u->service, ou->service))
	    continue;
    	if (urlStrcmp(u->host, ou->host))
	    continue;
	if (urlStrcmp(u->user, ou->user))
	    continue;
	if (urlStrcmp(u->portstr, ou->portstr))
	    continue;
	break;	/* Found item in cache */
    }

    if (i == _url_count) {
	if (ucx < 0) {
	    ucx = _url_count++;
	    _url_cache = xrealloc(_url_cache, sizeof(*_url_cache) * _url_count);
	}
	if (_url_cache)		/* XXX always true */
	    _url_cache[ucx] = urlLink(u, "_url_cache (miss)");
	u = urlFree(u, "urlSplit (urlFind miss)");
    } else {
	ucx = i;
	u = urlFree(u, "urlSplit (urlFind hit)");
    }

    /* This URL is now cached. */

    if (_url_cache)		/* XXX always true */
	u = urlLink(_url_cache[ucx], "_url_cache");
    *uret = u;
    /*@-usereleased@*/
    u = urlFree(u, "_url_cache (urlFind)");
    /*@=usereleased@*/

    /* Zap proxy host and port in case they have been reset */
    u->proxyp = -1;
    u->proxyh = _free(u->proxyh);

    /* Perform one-time FTP initialization */
    if (u->urltype == URL_IS_FTP) {

	if (mustAsk || (u->user != NULL && u->password == NULL)) {
	    const char * host = (u->host ? u->host : "");
	    const char * user = (u->user ? u->user : "");
	    char * prompt;
	    prompt = alloca(strlen(host) + strlen(user) + 256);
	    sprintf(prompt, _("Password for %s@%s: "), user, host);
	    u->password = _free(u->password);
	    u->password = /*@-unrecog@*/ getpass(prompt) /*@=unrecog@*/;
	    u->password = xstrdup(u->password);	/* XXX xstrdup has side effects. */
	}

	if (u->proxyh == NULL) {
	    const char *proxy = rpmExpand("%{_ftpproxy}", NULL);
	    if (proxy && *proxy != '%') {
		/*@observer@*/ const char * host = (u->host ? u->host : "");
		const char *uu = (u->user ? u->user : "anonymous");
		char *nu = xmalloc(strlen(uu) + sizeof("@") + strlen(host));
		(void) stpcpy( stpcpy( stpcpy(nu, uu), "@"), host);
		u->proxyu = nu;
		u->proxyh = xstrdup(proxy);
	    }
	    proxy = _free(proxy);
	}

	if (u->proxyp < 0) {
	    const char *proxy = rpmExpand("%{_ftpport}", NULL);
	    if (proxy && *proxy != '%') {
		char *end;
		int port = strtol(proxy, &end, 0);
		if (!(end && *end == '\0')) {
		    fprintf(stderr, _("error: %sport must be a number\n"),
			(u->service ? u->service : ""));
		    return;
		}
		u->proxyp = port;
	    }
	    proxy = _free(proxy);
	}
    }

    /* Perform one-time HTTP initialization */
    if (u->urltype == URL_IS_HTTP) {

	if (u->proxyh == NULL) {
	    const char *proxy = rpmExpand("%{_httpproxy}", NULL);
	    if (proxy && *proxy != '%')
		u->proxyh = xstrdup(proxy);
	    proxy = _free(proxy);
	}

	if (u->proxyp < 0) {
	    const char *proxy = rpmExpand("%{_httpport}", NULL);
	    if (proxy && *proxy != '%') {
		char *end;
		int port = strtol(proxy, &end, 0);
		if (!(end && *end == '\0')) {
		    fprintf(stderr, _("error: %sport must be a number\n"),
			(u->service ? u->service : ""));
		    return;
		}
		u->proxyp = port;
	    }
	    proxy = _free(proxy);
	}

    }

    return;
}
/*@=mods@*/

/**
 */
/*@observer@*/ /*@unchecked@*/
static struct urlstring {
/*@observer@*/ /*@null@*/ const char * leadin;
    urltype	ret;
} urlstrings[] = {
    { "file://",	URL_IS_PATH },
    { "ftp://",		URL_IS_FTP },
    { "http://",	URL_IS_HTTP },
    { "-",		URL_IS_DASH },
    { NULL,		URL_IS_UNKNOWN }
};

urltype urlIsURL(const char * url)
{
    struct urlstring *us;

    if (url && *url) {
	for (us = urlstrings; us->leadin != NULL; us++) {
	    if (strncmp(url, us->leadin, strlen(us->leadin)))
		continue;
	    return us->ret;
	}
    }

    return URL_IS_UNKNOWN;
}

/* Return path portion of url (or pointer to NUL if url == NULL) */
urltype urlPath(const char * url, const char ** pathp)
{
    const char *path;
    int urltype;

    path = url;
    urltype = urlIsURL(url);
    /*@-branchstate@*/
    switch (urltype) {
    case URL_IS_FTP:
	url += sizeof("ftp://") - 1;
	path = strchr(url, '/');
	if (path == NULL) path = url + strlen(url);
	break;
    case URL_IS_HTTP:
    case URL_IS_PATH:
	url += sizeof("file://") - 1;
	path = strchr(url, '/');
	if (path == NULL) path = url + strlen(url);
	break;
    case URL_IS_UNKNOWN:
	if (path == NULL) path = "";
	break;
    case URL_IS_DASH:
	path = "";
	break;
    }
    /*@=branchstate@*/
    if (pathp)
	/*@-observertrans@*/
	*pathp = path;
	/*@=observertrans@*/
    return urltype;
}

/*
 * Split URL into components. The URL can look like
 *	service://user:password@host:port/path
 */
/*@-modfilesys@*/
int urlSplit(const char * url, urlinfo *uret)
{
    urlinfo u;
    char *myurl;
    char *s, *se, *f, *fe;

    if (uret == NULL)
	return -1;
    if ((u = urlNew("urlSplit")) == NULL)
	return -1;

    if ((se = s = myurl = xstrdup(url)) == NULL) {
	u = urlFree(u, "urlSplit (error #1)");
	return -1;
    }

    u->url = xstrdup(url);
    u->urltype = urlIsURL(url);

    while (1) {
	/* Point to end of next item */
	while (*se && *se != '/') se++;
	/* Item was service. Save service and go for the rest ...*/
    	if (*se && (se != s) && se[-1] == ':' && se[0] == '/' && se[1] == '/') {
		se[-1] = '\0';
	    u->service = xstrdup(s);
	    se += 2;	/* skip over "//" */
	    s = se++;
	    continue;
	}
	
	/* Item was everything-but-path. Continue parse on rest */
	*se = '\0';
	break;
    }

    /* Look for ...@host... */
    fe = f = s;
    while (*fe && *fe != '@') fe++;
    /*@-branchstate@*/
    if (*fe == '@') {
	s = fe + 1;
	*fe = '\0';
    	/* Look for user:password@host... */
	while (fe > f && *fe != ':') fe--;
	if (*fe == ':') {
	    *fe++ = '\0';
	    u->password = xstrdup(fe);
	}
	u->user = xstrdup(f);
    }
    /*@=branchstate@*/

    /* Look for ...host:port */
    fe = f = s;
    while (*fe && *fe != ':') fe++;
    if (*fe == ':') {
	*fe++ = '\0';
	u->portstr = xstrdup(fe);
	if (u->portstr != NULL && u->portstr[0] != '\0') {
	    char *end;
	    u->port = strtol(u->portstr, &end, 0);
	    if (!(end && *end == '\0')) {
		rpmMessage(RPMMESS_ERROR, _("url port must be a number\n"));
		myurl = _free(myurl);
		u = urlFree(u, "urlSplit (error #3)");
		return -1;
	    }
	}
    }
    u->host = xstrdup(f);

    if (u->port < 0 && u->service != NULL) {
	struct servent *serv;
	/*@-unrecog -multithreaded -moduncon @*/
	serv = getservbyname(u->service, "tcp");
	/*@=unrecog =multithreaded =moduncon @*/
	if (serv != NULL)
	    u->port = ntohs(serv->s_port);
	else if (u->urltype == URL_IS_FTP)
	    u->port = IPPORT_FTP;
	else if (u->urltype == URL_IS_HTTP)
	    u->port = IPPORT_HTTP;
    }

    myurl = _free(myurl);
    if (uret) {
	*uret = u;
/*@-globs -mods @*/ /* FIX: rpmGlobalMacroContext not in <rpmlib.h> */
	urlFind(uret, 0);
/*@=globs =mods @*/
    }
    return 0;
}
/*@=modfilesys@*/

int urlGetFile(const char * url, const char * dest)
{
    int rc;
    FD_t sfd = NULL;
    FD_t tfd = NULL;
    const char * sfuPath = NULL;
    int urlType = urlPath(url, &sfuPath);

    if (*sfuPath == '\0')
	return FTPERR_UNKNOWN;
	
    sfd = Fopen(url, "r.ufdio");
    if (sfd == NULL || Ferror(sfd)) {
	rpmMessage(RPMMESS_DEBUG, _("failed to open %s: %s\n"), url, Fstrerror(sfd));
	rc = FTPERR_UNKNOWN;
	goto exit;
    }

    if (dest == NULL) {
	if ((dest = strrchr(sfuPath, '/')) != NULL)
	    dest++;
	else
	    dest = sfuPath;
    }

    if (dest == NULL)
	return FTPERR_UNKNOWN;

    tfd = Fopen(dest, "w.ufdio");
if (_url_debug)
fprintf(stderr, "*** urlGetFile sfd %p %s tfd %p %s\n", sfd, url, (tfd ? tfd : NULL), dest);
    if (tfd == NULL || Ferror(tfd)) {
	/* XXX Fstrerror */
	rpmMessage(RPMMESS_DEBUG, _("failed to create %s: %s\n"), dest, Fstrerror(tfd));
	rc = FTPERR_UNKNOWN;
	goto exit;
    }

    switch (urlType) {
    case URL_IS_FTP:
    case URL_IS_HTTP:
    case URL_IS_PATH:
    case URL_IS_DASH:
    case URL_IS_UNKNOWN:
	if ((rc = ufdGetFile(sfd, tfd))) {
	    (void) Unlink(dest);
	    /* XXX FIXME: sfd possibly closed by copyData */
	    /*@-usereleased@*/ (void) Fclose(sfd) /*@=usereleased@*/ ;
	}
	sfd = NULL;	/* XXX Fclose(sfd) done by ufdGetFile */
	break;
    default:
	rc = FTPERR_UNKNOWN;
	break;
    }

exit:
    if (tfd)
	(void) Fclose(tfd);
    if (sfd)
	(void) Fclose(sfd);

    return rc;
}
/*@=type@*/
