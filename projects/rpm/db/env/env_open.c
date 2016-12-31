/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 1996-2001
 *	Sleepycat Software.  All rights reserved.
 */

#include "db_config.h"

#ifndef lint
static const char revid[] = "Id: env_open.c,v 11.72 2001/10/12 18:18:59 sue Exp ";
#endif /* not lint */

#ifndef NO_SYSTEM_INCLUDES
#include <sys/types.h>

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#endif

#include "db_int.h"
#include "db_page.h"
#include "db_shash.h"
#include "btree.h"
#include "hash.h"
#include "lock.h"
#include "log.h"
#include "mp.h"
#include "qam.h"
#include "rep.h"
#include "txn.h"
#include "rep_ext.h"
#include "clib_ext.h"

static int __db_parse __P((DB_ENV *, char *));
static int __db_tmp_open __P((DB_ENV *, u_int32_t, char *, DB_FH *));
static int __dbenv_config __P((DB_ENV *, const char *, u_int32_t));
static int __dbenv_iremove __P((DB_ENV *, const char *, u_int32_t));
static int __dbenv_refresh __P((DB_ENV *));

/*
 * db_version --
 *	Return version information.
 *
 * EXTERN: char *db_version __P((int *, int *, int *));
 */
char *
db_version(majverp, minverp, patchp)
	int *majverp, *minverp, *patchp;
{
	if (majverp != NULL)
		*majverp = DB_VERSION_MAJOR;
	if (minverp != NULL)
		*minverp = DB_VERSION_MINOR;
	if (patchp != NULL)
		*patchp = DB_VERSION_PATCH;
	return ((char *)DB_VERSION_STRING);
}

/*
 * __dbenv_open --
 *	Initialize an environment.
 *
 * PUBLIC: int __dbenv_open __P((DB_ENV *, const char *, u_int32_t, int));
 */
int
__dbenv_open(dbenv, db_home, flags, mode)
	DB_ENV *dbenv;
	const char *db_home;
	u_int32_t flags;
	int mode;
{
	DB_MPOOL *dbmp;
	int ret;
	u_int32_t init_flags;

#undef	OKFLAGS
#define	OKFLAGS								\
	DB_CREATE | DB_INIT_CDB | DB_INIT_LOCK | DB_INIT_LOG |		\
	DB_INIT_MPOOL | DB_INIT_TXN | DB_JOINENV | DB_LOCKDOWN |	\
	DB_PRIVATE | DB_RECOVER | DB_RECOVER_FATAL | DB_SYSTEM_MEM |	\
	DB_THREAD | DB_USE_ENVIRON | DB_USE_ENVIRON_ROOT
#undef	OKFLAGS_CDB
#define	OKFLAGS_CDB							\
	DB_CREATE | DB_INIT_CDB | DB_INIT_MPOOL | DB_LOCKDOWN |		\
	DB_PRIVATE | DB_SYSTEM_MEM | DB_THREAD |			\
	DB_USE_ENVIRON | DB_USE_ENVIRON_ROOT

	/*
	 * Flags saved in the init_flags field of the environment, representing
	 * flags to DB_ENV->set_flags and DB_ENV->open that need to be set.
	 */
#define	DB_INITENV_CDB		0x0001	/* DB_INIT_CDB */
#define	DB_INITENV_CDB_ALLDB	0x0002	/* DB_INIT_CDB_ALLDB */
#define	DB_INITENV_LOCK		0x0004	/* DB_INIT_LOCK */
#define	DB_INITENV_LOG		0x0008	/* DB_INIT_LOG */
#define	DB_INITENV_MPOOL	0x0010	/* DB_INIT_MPOOL */
#define	DB_INITENV_TXN		0x0020	/* DB_INIT_TXN */

	if ((ret = __db_fchk(dbenv, "DB_ENV->open", flags, OKFLAGS)) != 0)
		return (ret);
	if (LF_ISSET(DB_INIT_CDB) &&
	    (ret = __db_fchk(dbenv, "DB_ENV->open", flags, OKFLAGS_CDB)) != 0)
		return (ret);
	if ((ret = __db_fcchk(dbenv,
	    "DB_ENV->open", flags, DB_PRIVATE, DB_SYSTEM_MEM)) != 0)
		return (ret);
	if ((ret = __db_fcchk(dbenv,
	    "DB_ENV->open", flags, DB_RECOVER, DB_RECOVER_FATAL)) != 0)
		return (ret);
	if ((ret = __db_fcchk(dbenv, "DB_ENV->open", flags, DB_JOINENV,
	    DB_CREATE | DB_INIT_LOCK | DB_INIT_LOG | DB_INIT_MPOOL |
	    DB_INIT_TXN | DB_PRIVATE)) != 0)
		return (ret);

	/*
	 * If we're doing recovery, destroy the environment so that we create
	 * all the regions from scratch.  I'd like to reuse already created
	 * regions, but that's hard.  We would have to create the environment
	 * region from scratch, at least, as we have no way of knowing if its
	 * linked lists are corrupted.
	 *
	 * I suppose we could set flags while modifying those links, but that
	 * is going to be difficult to get right.  The major concern I have
	 * is if the application stomps the environment with a rogue pointer.
	 * We have no way of detecting that, and we could be forced into a
	 * situation where we start up and then crash, repeatedly.
	 *
	 * Note that we do not check any flags like DB_PRIVATE before calling
	 * remove.  We don't care if the current environment was private or
	 * not, we just want to nail any files that are left-over for whatever
	 * reason, from whatever session.
	 *
	 * There's a nasty bug here, caused by our created DB_ENV handle not
	 * having any of the configuration information that the application
	 * may have set in the handle it passed us.  For example, it may
	 * have set an error FILE, and error messages from DB_ENV->remove
	 * won't be passed to that callback.  Nobody has thought of a good
	 * solution, so we copy the information and hope that it's enough.
	 * The dance to use the application's DB_ENV in the remove call is
	 * so we don't surprise some callback function by giving it a memory
	 * reference it's never seen before.
	 */
	if (LF_ISSET(DB_RECOVER | DB_RECOVER_FATAL)) {
		DB_ENV tmp, *rm_dbenv;

		if ((ret = db_env_create(&rm_dbenv, 0)) != 0)
			return (ret);
		tmp = *dbenv;
		*dbenv = *rm_dbenv;
		dbenv->db_errfile = tmp.db_errfile;
		dbenv->db_errpfx = tmp.db_errpfx;
		dbenv->db_errcall = tmp.db_errcall;
		dbenv->db_feedback = tmp.db_feedback;
		dbenv->db_paniccall = tmp.db_paniccall;
		dbenv->db_tmp_dir = tmp.db_tmp_dir;
		dbenv->verbose = tmp.verbose;
		dbenv->app_private = tmp.app_private;
		dbenv->cj_internal = tmp.cj_internal;
		ret = __dbenv_iremove(dbenv, db_home, DB_FORCE);

		/*
		 * Copy our saved handle back into the user's memory, discard
		 * our allocated handle.  We save the user's app_private field
		 * it's improbable, but if we called a callback function and
		 * the user changed the app_private field, we should preserve
		 * the value.
		 */
		tmp.app_private = dbenv->app_private;
		*dbenv = tmp;
		rm_dbenv->close(rm_dbenv, 0);

		if (ret != 0)
			return (ret);
	}

	/* Initialize the DB_ENV structure. */
	if ((ret = __dbenv_config(dbenv, db_home, flags)) != 0)
		goto err;

	/* Convert the DB_ENV->open flags to internal flags. */
	if (LF_ISSET(DB_CREATE))
		F_SET(dbenv, DB_ENV_CREATE);
	if (LF_ISSET(DB_LOCKDOWN))
		F_SET(dbenv, DB_ENV_LOCKDOWN);
	if (LF_ISSET(DB_PRIVATE))
		F_SET(dbenv, DB_ENV_PRIVATE);
	if (LF_ISSET(DB_SYSTEM_MEM))
		F_SET(dbenv, DB_ENV_SYSTEM_MEM);
	if (LF_ISSET(DB_THREAD))
		F_SET(dbenv, DB_ENV_THREAD);

	/* Default permissions are read-write for both owner and group. */
	dbenv->db_mode = mode == 0 ? __db_omode("rwrw--") : mode;

	/*
	 * Create/join the environment.  We pass in the flags that
	 * will be of interest to an environment joining later;  if
	 * we're not the ones to do the create, we
	 * pull out whatever has been stored, if we don't do a create.
	 */
	init_flags = 0;
	init_flags |= (LF_ISSET(DB_INIT_CDB) ? DB_INITENV_CDB : 0);
	init_flags |= (LF_ISSET(DB_INIT_LOCK) ? DB_INITENV_LOCK : 0);
	init_flags |= (LF_ISSET(DB_INIT_LOG) ? DB_INITENV_LOG : 0);
	init_flags |= (LF_ISSET(DB_INIT_MPOOL) ? DB_INITENV_MPOOL : 0);
	init_flags |= (LF_ISSET(DB_INIT_TXN) ? DB_INITENV_TXN : 0);
	init_flags |=
	    (F_ISSET(dbenv, DB_ENV_CDB_ALLDB) ? DB_INITENV_CDB_ALLDB : 0);

	if ((ret = __db_e_attach(dbenv, &init_flags)) != 0)
		goto err;

	/*
	 * __db_e_attach will return the saved init_flags field, which
	 * contains the DB_INIT_* flags used when we were created.
	 */
	if (LF_ISSET(DB_JOINENV)) {
		LF_CLR(DB_JOINENV);

		LF_SET((init_flags & DB_INITENV_CDB) ? DB_INIT_CDB : 0);
		LF_SET((init_flags & DB_INITENV_LOCK) ? DB_INIT_LOCK : 0);
		LF_SET((init_flags & DB_INITENV_LOG) ? DB_INIT_LOG : 0);
		LF_SET((init_flags & DB_INITENV_MPOOL) ? DB_INIT_MPOOL : 0);
		LF_SET((init_flags & DB_INITENV_TXN) ? DB_INIT_TXN : 0);

		if (LF_ISSET(DB_INITENV_CDB_ALLDB) &&
		    (ret = dbenv->set_flags(dbenv, DB_CDB_ALLDB, 1)) != 0)
			goto err;
	}

	/* Initialize for CDB product. */
	if (LF_ISSET(DB_INIT_CDB)) {
		LF_SET(DB_INIT_LOCK);
		F_SET(dbenv, DB_ENV_CDB);
	}

	/*
	 * Initialize the subsystems.  Transactions imply logging but do not
	 * imply locking.  While almost all applications want both locking
	 * and logging, it would not be unreasonable for a single threaded
	 * process to want transactions for atomicity guarantees, but not
	 * necessarily need concurrency.
	 */
	if (LF_ISSET(DB_INIT_MPOOL))
		if ((ret = __memp_open(dbenv)) != 0)
			goto err;
	if (LF_ISSET(DB_INIT_LOG | DB_INIT_TXN))
		if ((ret = __log_open(dbenv)) != 0)
			goto err;
	if (LF_ISSET(DB_INIT_LOCK))
		if ((ret = __lock_open(dbenv)) != 0)
			goto err;
	if (LF_ISSET(DB_INIT_TXN)) {
		if ((ret = __txn_open(dbenv)) != 0)
			goto err;

		/*
		 * If the application is running with transactions, initialize
		 * the function tables.
		 */
		if ((ret = __bam_init_recover(dbenv)) != 0)
			goto err;
		if ((ret = __crdel_init_recover(dbenv)) != 0)
			goto err;
		if ((ret = __db_init_recover(dbenv)) != 0)
			goto err;
		if ((ret = __ham_init_recover(dbenv)) != 0)
			goto err;
		if ((ret = __log_init_recover(dbenv)) != 0)
			goto err;
		if ((ret = __qam_init_recover(dbenv)) != 0)
			goto err;
		if ((ret = __txn_init_recover(dbenv)) != 0)
			goto err;

		/*
		 * If the application specified their own recovery
		 * initialization function, call it.
		 */
		if (dbenv->db_recovery_init != NULL &&
		    (ret = dbenv->db_recovery_init(dbenv)) != 0)
			goto err;

		/* Perform recovery for any previous run. */
		if (LF_ISSET(DB_RECOVER | DB_RECOVER_FATAL) &&
		    (ret = __db_apprec(dbenv, NULL,
		    LF_ISSET(DB_RECOVER | DB_RECOVER_FATAL))) != 0)
			goto err;
	}

	/* Initialize the replication area just in case. */
	if ((ret = __rep_region_init(dbenv)) != 0)
		goto err;

	/*
	 * Initialize the DB list, and its mutex as necessary.  If the env
	 * handle isn't free-threaded we don't need a mutex because there
	 * will never be more than a single DB handle on the list.  If the
	 * mpool wasn't initialized, then we can't ever open a DB handle.
	 *
	 * !!!
	 * This must come after the __memp_open call above because if we are
	 * recording mutexes for system resources, we will do it in the mpool
	 * region for environments and db handles.  So, the mpool region must
	 * already be initialized.
	 */
	LIST_INIT(&dbenv->dblist);
	if (F_ISSET(dbenv, DB_ENV_THREAD) && LF_ISSET(DB_INIT_MPOOL)) {
		dbmp = dbenv->mp_handle;
		if ((ret = __db_mutex_alloc(
		    dbenv, dbmp->reginfo, 0, &dbenv->dblist_mutexp)) != 0)
			return (ret);
		if ((ret = __db_shmutex_init(dbenv, dbenv->dblist_mutexp,
		    0, MUTEX_THREAD, &dbmp->reginfo[0],
		    (REGMAINT *)R_ADDR(&dbmp->reginfo[0],
		    ((MPOOL *)dbmp->reginfo->primary)->maint_off))) != 0) {
			__db_mutex_free(dbenv, dbmp->reginfo,
			    dbenv->dblist_mutexp);
			return (ret);
		}
	}

	return (0);

err:	(void)__dbenv_refresh(dbenv);
	return (ret);
}

/*
 * __dbenv_remove --
 *	Discard an environment.
 *
 * PUBLIC: int __dbenv_remove __P((DB_ENV *, const char *, u_int32_t));
 */
int
__dbenv_remove(dbenv, db_home, flags)
	DB_ENV *dbenv;
	const char *db_home;
	u_int32_t flags;
{
	int ret, t_ret;

	ret = __dbenv_iremove(dbenv, db_home, flags);
	t_ret = dbenv->close(dbenv, 0);

	return (ret == 0 ? t_ret : ret);
}

/*
 * __dbenv_iremove --
 *	Discard an environment, internal version.
 */
static int
__dbenv_iremove(dbenv, db_home, flags)
	DB_ENV *dbenv;
	const char *db_home;
	u_int32_t flags;
{
	int ret;

#undef	OKFLAGS
#define	OKFLAGS								\
	DB_FORCE | DB_USE_ENVIRON | DB_USE_ENVIRON_ROOT

	/* Validate arguments. */
	if ((ret = __db_fchk(dbenv, "DB_ENV->remove", flags, OKFLAGS)) != 0)
		return (ret);

	/*
	 * A hard-to-debug error is calling DB_ENV->remove after open.  That's
	 * not legal.  You have to close the original, already opened handle
	 * and then allocate a new DB_ENV handle to use for DB_ENV->remove.
	 */
	if (F_ISSET(dbenv, DB_ENV_OPEN_CALLED)) {
		__db_err(dbenv,
		    "DB_ENV handle opened, not usable for remove method.");
		return (EINVAL);
	}

	/* Initialize the DB_ENV structure. */
	if ((ret = __dbenv_config(dbenv, db_home, flags)) != 0)
		return (ret);

	/* Remove the environment. */
	return (__db_e_remove(dbenv, LF_ISSET(DB_FORCE) ? 1 : 0));
}

/*
 * __dbenv_config --
 *	Initialize the DB_ENV structure.
 */
static int
__dbenv_config(dbenv, db_home, flags)
	DB_ENV *dbenv;
	const char *db_home;
	u_int32_t flags;
{
	FILE *fp;
	int ret;
	char *lp, buf[MAXPATHLEN * 2];

	/* Set the database home. */
	if ((ret = __db_home(dbenv, db_home, flags)) != 0)
		return (ret);

	/*
	 * Parse the config file.
	 *
	 * !!!
	 * Don't use sprintf(3)/snprintf(3) -- the former is dangerous, and
	 * the latter isn't standard, and we're manipulating strings handed
	 * us by the application.
	 */
	if (dbenv->db_home != NULL) {
#define	CONFIG_NAME	"/DB_CONFIG"
		if (strlen(dbenv->db_home) +
		    strlen(CONFIG_NAME) + 1 > sizeof(buf)) {
			ret = ENAMETOOLONG;
			return (ret);
		}
		(void)strcpy(buf, dbenv->db_home);
		(void)strcat(buf, CONFIG_NAME);
		if ((fp = fopen(buf, "r")) != NULL) {
			while (fgets(buf, sizeof(buf), fp) != NULL) {
				if ((lp = strchr(buf, '\n')) == NULL) {
					__db_err(dbenv,
					    "%s: line too long", CONFIG_NAME);
					(void)fclose(fp);
					ret = EINVAL;
					return (ret);
				}
				*lp = '\0';
				if (buf[0] == '\0' ||
				    buf[0] == '#' || isspace((int)buf[0]))
					continue;

				if ((ret = __db_parse(dbenv, buf)) != 0) {
					(void)fclose(fp);
					return (ret);
				}
			}
			(void)fclose(fp);
		}
	}

	/* Set up the tmp directory path. */
	if (dbenv->db_tmp_dir == NULL && (ret = __os_tmpdir(dbenv, flags)) != 0)
		return (ret);

	/*
	 * The locking file descriptor is rarely on.  Set the fd to -1, not
	 * because it's ever tested, but to make sure we catch mistakes.
	 */
	if ((ret =
	    __os_calloc(dbenv,
		1, sizeof(*dbenv->lockfhp), &dbenv->lockfhp)) != 0)
		return (ret);
	dbenv->lockfhp->fd = -1;

	/*
	 * Flag that the DB_ENV structure has been initialized.  Note, this
	 * must be set before calling into the subsystems as it's used during
	 * file naming.
	 */
	F_SET(dbenv, DB_ENV_OPEN_CALLED);

	return (0);
}

/*
 * __dbenv_close --
 *	DB_ENV destructor.
 *
 * PUBLIC: int __dbenv_close __P((DB_ENV *, u_int32_t));
 */
int
__dbenv_close(dbenv, flags)
	DB_ENV *dbenv;
	u_int32_t flags;
{
	char **p;
	int ret, t_ret;

	COMPQUIET(flags, 0);

	PANIC_CHECK(dbenv);
	ret = 0;

	/*
	 * Before checking the reference count, we have to see if we
	 * were in the middle of restoring transactions and need to
	 * close the open files.
	 */
	if (TXN_ON(dbenv))
		__txn_preclose(dbenv);

	if (dbenv->rep_handle != NULL)
		__rep_preclose(dbenv);

	if (dbenv->db_ref != 0) {
		__db_err(dbenv,
		    "Database handles open during environment close");
		ret = EINVAL;
	}

	/*
	 * Detach from the regions and undo the allocations done by
	 * DB_ENV->open.
	 */
	if ((t_ret = __dbenv_refresh(dbenv)) != 0 && ret == 0)
		ret = t_ret;

	/* Do per-subsystem destruction. */
	__lock_dbenv_close(dbenv); /* void */
	if ((t_ret = __rep_dbenv_close(dbenv)) != 0 && ret == 0)
		ret = t_ret;

	/* Release any string-based configuration parameters we've copied. */
	if (dbenv->db_log_dir != NULL)
		__os_freestr(dbenv, dbenv->db_log_dir);
	if (dbenv->db_tmp_dir != NULL)
		__os_freestr(dbenv, dbenv->db_tmp_dir);
	if (dbenv->db_data_dir != NULL) {
		for (p = dbenv->db_data_dir; *p != NULL; ++p)
			__os_freestr(dbenv, *p);
		__os_free(dbenv, dbenv->db_data_dir,
		    dbenv->data_cnt * sizeof(char **));
	}

	/* Discard the structure if we allocated it. */
	if (!F_ISSET(dbenv, DB_ENV_USER_ALLOC)) {
		memset(dbenv, CLEAR_BYTE, sizeof(DB_ENV));
		__os_free(NULL, dbenv, sizeof(DB_ENV));
	}

	return (ret);
}

/*
 * __dbenv_refresh --
 *	Refresh the DB_ENV structure, releasing resources allocated by
 * DB_ENV->open, and returning it to the state it was in just before
 * open was called.  (Note that this means that any state set by
 * pre-open configuration functions must be preserved.)
 */
static int
__dbenv_refresh(dbenv)
	DB_ENV *dbenv;
{
	DB_MPOOL *dbmp;
	int ret, t_ret;

	ret = 0;

	/*
	 * Discard DB list and its mutex.
	 *
	 * !!!
	 * This must be done before we close the mpool region because we
	 * may have allocated the DB handle mutex in the mpool region.
	 */
	LIST_INIT(&dbenv->dblist);
	if (dbenv->dblist_mutexp != NULL) {
		dbmp = dbenv->mp_handle;
		__db_mutex_free(dbenv, dbmp->reginfo, dbenv->dblist_mutexp);
	}

	/*
	 * Close subsystems, in the reverse order they were opened (txn
	 * must be first, it may want to discard locks and flush the log).
	 *
	 * !!!
	 * Note that these functions, like all of __dbenv_refresh, only undo
	 * the effects of __dbenv_open.  Functions that undo work done by
	 * db_env_create or by a configurator function should go in
	 * __dbenv_close.
	 */
	if (TXN_ON(dbenv)) {
		if ((t_ret = __txn_dbenv_refresh(dbenv)) != 0 && ret == 0)
			ret = t_ret;
	}

	if (LOCKING_ON(dbenv)) {
		if ((t_ret = __lock_dbenv_refresh(dbenv)) != 0 && ret == 0)
			ret = t_ret;
	}

	if (LOGGING_ON(dbenv)) {
		if ((t_ret = __log_dbenv_refresh(dbenv)) != 0 && ret == 0)
			ret = t_ret;
	}

	if (MPOOL_ON(dbenv)) {
		if ((t_ret = __memp_dbenv_refresh(dbenv)) != 0 && ret == 0)
			ret = t_ret;
	}

	/* Detach from the region. */
	if (dbenv->reginfo != NULL) {
		if ((t_ret = __db_e_detach(dbenv, 0)) != 0 && ret == 0)
			ret = t_ret;
		/*
		 * !!!
		 * Don't free dbenv->reginfo or set the reference to NULL,
		 * that was done by __db_e_detach().
		 */
	}

	/* Undo changes and allocations done by __dbenv_open. */
	if (dbenv->db_home != NULL) {
		__os_freestr(dbenv, dbenv->db_home);
		dbenv->db_home = NULL;
	}

	dbenv->db_mode = 0;

	if (dbenv->lockfhp != NULL) {
		__os_free(dbenv, dbenv->lockfhp, sizeof(*dbenv->lockfhp));
		dbenv->lockfhp = NULL;
	}

	if (dbenv->dtab != NULL) {
		__os_free(dbenv, dbenv->dtab,
		    dbenv->dtab_size * sizeof(dbenv->dtab[0]));
		dbenv->dtab = NULL;
		dbenv->dtab_size = 0;
	}

	F_CLR(dbenv, ~(DB_ENV_STANDALONE | DB_ENV_USER_ALLOC));

	return (ret);
}

#define	DB_ADDSTR(add) {						\
	if ((add) != NULL) {						\
		/* If leading slash, start over. */			\
		if (__os_abspath(add)) {				\
			p = str;					\
			slash = 0;					\
		}							\
		/* Append to the current string. */			\
		len = strlen(add);					\
		if (slash)						\
			*p++ = PATH_SEPARATOR[0];			\
		memcpy(p, add, len);					\
		p += len;						\
		slash = strchr(PATH_SEPARATOR, p[-1]) == NULL;		\
	}								\
}

/*
 * __db_appname --
 *	Given an optional DB environment, directory and file name and type
 *	of call, build a path based on the DB_ENV->open rules, and return
 *	it in allocated space.
 *
 * PUBLIC: int __db_appname __P((DB_ENV *, APPNAME,
 * PUBLIC:    const char *, const char *, u_int32_t, DB_FH *, char **));
 */
int
__db_appname(dbenv, appname, dir, file, tmp_oflags, fhp, namep)
	DB_ENV *dbenv;
	APPNAME appname;
	const char *dir, *file;
	u_int32_t tmp_oflags;
	DB_FH *fhp;
	char **namep;
{
	DB_ENV etmp;
	size_t len, str_len;
	int data_entry, ret, slash, tmp_create, tmp_free;
	const char *a, *b, *c;
	char *p, *str;

	a = b = c = NULL;
	data_entry = -1;
	tmp_create = tmp_free = 0;

	/*
	 * We don't return a name when creating temporary files, just a
	 * file handle.  Default to an error now.
	 */
	if (fhp != NULL)
		F_CLR(fhp, DB_FH_VALID);
	if (namep != NULL)
		*namep = NULL;

	/*
	 * Absolute path names are never modified.  If the file is an absolute
	 * path, we're done.  If the directory is, simply append the file and
	 * return.
	 */
	if (file != NULL && __os_abspath(file))
		return (__os_strdup(dbenv, file, namep));
	if (dir != NULL && __os_abspath(dir)) {
		a = dir;
		goto done;
	}

	/*
	 * DB_ENV  DIR	   APPNAME	   RESULT
	 * -------------------------------------------
	 * null	   null	   none		   <tmp>/file
	 * null	   set	   none		   DIR/file
	 * set	   null	   none		   DB_HOME/file
	 * set	   set	   none		   DB_HOME/DIR/file
	 *
	 * DB_ENV  FILE	   APPNAME	   RESULT
	 * -------------------------------------------
	 * null	   null	   DB_APP_DATA	   <tmp>/<create>
	 * null	   set	   DB_APP_DATA	   ./file
	 * set	   null	   DB_APP_DATA	   <tmp>/<create>
	 * set	   set	   DB_APP_DATA	   DB_HOME/DB_DATA_DIR/file
	 *
	 * DB_ENV  DIR	   APPNAME	   RESULT
	 * -------------------------------------------
	 * null	   null	   DB_APP_LOG	   <tmp>/file
	 * null	   set	   DB_APP_LOG	   DIR/file
	 * set	   null	   DB_APP_LOG	   DB_HOME/DB_LOG_DIR/file
	 * set	   set	   DB_APP_LOG	   DB_HOME/DB_LOG_DIR/DIR/file
	 *
	 * DB_ENV	   APPNAME	   RESULT
	 * -------------------------------------------
	 * null		   DB_APP_TMP*	   <tmp>/<create>
	 * set		   DB_APP_TMP*	   DB_HOME/DB_TMP_DIR/<create>
	 */
retry:	switch (appname) {
	case DB_APP_NONE:
		if (dbenv == NULL || !F_ISSET(dbenv, DB_ENV_OPEN_CALLED)) {
			if (dir == NULL)
				goto tmp;
			a = dir;
		} else {
			a = dbenv->db_home;
			b = dir;
		}
		break;
	case DB_APP_DATA:
		if (dir != NULL) {
			__db_err(dbenv,
			    "DB_APP_DATA: illegal directory specification");
			return (EINVAL);
		}

		if (file == NULL) {
			tmp_create = 1;
			goto tmp;
		}
		if (dbenv != NULL && F_ISSET(dbenv, DB_ENV_OPEN_CALLED)) {
			a = dbenv->db_home;
			if (dbenv->db_data_dir != NULL &&
			    (b = dbenv->db_data_dir[++data_entry]) == NULL) {
				data_entry = -1;
				b = dbenv->db_data_dir[0];
			}
		}
		break;
	case DB_APP_LOG:
		if (dbenv == NULL || !F_ISSET(dbenv, DB_ENV_OPEN_CALLED)) {
			if (dir == NULL)
				goto tmp;
			a = dir;
		} else {
			a = dbenv->db_home;
			b = dbenv->db_log_dir;
			c = dir;
		}
		break;
	case DB_APP_TMP:
		if (dir != NULL || file != NULL) {
			__db_err(dbenv,
		    "DB_APP_TMP: illegal directory or file specification");
			return (EINVAL);
		}

		tmp_create = 1;
		if (dbenv == NULL || !F_ISSET(dbenv, DB_ENV_OPEN_CALLED))
			goto tmp;
		else {
			a = dbenv->db_home;
			b = dbenv->db_tmp_dir;
		}
		break;
	}

	/* Reference a file from the appropriate temporary directory. */
	if (0) {
tmp:		if (dbenv == NULL || !F_ISSET(dbenv, DB_ENV_OPEN_CALLED)) {
			memset(&etmp, 0, sizeof(etmp));
			if ((ret = __os_tmpdir(&etmp, DB_USE_ENVIRON)) != 0)
				return (ret);
			tmp_free = 1;
			a = etmp.db_tmp_dir;
		} else
			a = dbenv->db_tmp_dir;
	}

done:	len =
	    (a == NULL ? 0 : strlen(a) + 1) +
	    (b == NULL ? 0 : strlen(b) + 1) +
	    (c == NULL ? 0 : strlen(c) + 1) +
	    (file == NULL ? 0 : strlen(file) + 1);

	/*
	 * Allocate space to hold the current path information, as well as any
	 * temporary space that we're going to need to create a temporary file
	 * name.
	 */
#define	DB_TRAIL	"BDBXXXXXX"
	str_len = len + sizeof(DB_TRAIL) + 10;
	if ((ret = __os_malloc(dbenv, str_len, &str)) != 0) {
		if (tmp_free)
			__os_freestr(dbenv, etmp.db_tmp_dir);
		return (ret);
	}

	slash = 0;
	p = str;
	DB_ADDSTR(a);
	DB_ADDSTR(b);
	DB_ADDSTR(file);
	*p = '\0';

	/* Discard any space allocated to find the temp directory. */
	if (tmp_free) {
		__os_freestr(dbenv, etmp.db_tmp_dir);
		tmp_free = 0;
	}

	/*
	 * If we're opening a data file, see if it exists.  If it does,
	 * return it, otherwise, try and find another one to open.
	 */
	if (data_entry != -1 && __os_exists(str, NULL) != 0) {
		__os_free(dbenv, str, str_len);
		a = b = c = NULL;
		goto retry;
	}

	/* Create the file if so requested. */
	if (tmp_create &&
	    (ret = __db_tmp_open(dbenv, tmp_oflags, str, fhp)) != 0) {
		__os_free(dbenv, str, str_len);
		return (ret);
	}

	if (namep == NULL)
		__os_free(dbenv, str, str_len);
	else
		*namep = str;
	return (0);
}

/*
 * __db_home --
 *	Find the database home.
 *
 * PUBLIC:	int __db_home __P((DB_ENV *, const char *, u_int32_t));
 */
int
__db_home(dbenv, db_home, flags)
	DB_ENV *dbenv;
	const char *db_home;
	u_int32_t flags;
{
	const char *p;

	/*
	 * Use db_home by default, this allows utilities to reasonably
	 * override the environment either explicitly or by using a -h
	 * option.  Otherwise, use the environment if it's permitted
	 * and initialized.
	 */
	if ((p = db_home) == NULL &&
	    (LF_ISSET(DB_USE_ENVIRON) ||
	    (LF_ISSET(DB_USE_ENVIRON_ROOT) && __os_isroot())) &&
	    (p = getenv("DB_HOME")) != NULL && p[0] == '\0') {
		__db_err(dbenv, "illegal DB_HOME environment variable");
		return (EINVAL);
	}

	return (p == NULL ? 0 : __os_strdup(dbenv, p, &dbenv->db_home));
}

#define	__DB_OVFL(v, max)						\
	if (v > max) {							\
		__v = v;						\
		__max = max;						\
		goto toobig;						\
	}

/*
 * __db_parse --
 *	Parse a single NAME VALUE pair.
 */
static int
__db_parse(dbenv, s)
	DB_ENV *dbenv;
	char *s;
{
	u_long __max, __v, v1, v2, v3;
	u_int32_t flags;
	char *name, *p, *value, v4;

	/*
	 * !!!
	 * The value of 40 is hard-coded into format arguments to sscanf
	 * below, it can't be changed here without changing it there, too.
	 */
	char arg[40];

	/*
	 * Name/value pairs are parsed as two white-space separated strings.
	 * Leading and trailing white-space is trimmed from the value, but
	 * it may contain embedded white-space.  Note: we use the isspace(3)
	 * macro because it's more portable, but that means that you can use
	 * characters like form-feed to separate the strings.
	 */
	name = s;
	for (p = name; *p != '\0' && !isspace((int)*p); ++p)
		;
	if (*p == '\0' || p == name)
		goto illegal;
	*p = '\0';
	for (++p; isspace((int)*p); ++p)
		;
	if (*p == '\0')
		goto illegal;
	value = p;
	for (++p; *p != '\0'; ++p)
		;
	for (--p; isspace((int)*p); --p)
		;
	++p;
	if (p == value) {
illegal:	__db_err(dbenv, "mis-formatted name-value pair: %s", s);
		return (EINVAL);
	}
	*p = '\0';

	if (!strcasecmp(name, "set_cachesize")) {
		if (sscanf(value, "%lu %lu %lu %c", &v1, &v2, &v3, &v4) != 3)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		__DB_OVFL(v2, UINT32_T_MAX);
		__DB_OVFL(v3, 10000);
		return (dbenv->set_cachesize(
		    dbenv, (u_int32_t)v1, (u_int32_t)v2, (int)v3));
	}

	if (!strcasecmp(name, "set_data_dir") ||
	    !strcasecmp(name, "db_data_dir"))		/* Compatibility. */
		return (dbenv->set_data_dir(dbenv, value));

	if (!strcasecmp(name, "set_flags")) {
		if (sscanf(value, "%40s %c", arg, &v4) != 1)
			goto badarg;

		if (!strcasecmp(value, "db_cdb_alldb"))
			return (dbenv->set_flags(dbenv, DB_CDB_ALLDB, 1));
		if (!strcasecmp(value, "db_nolocking"))
			return (dbenv->set_flags(dbenv, DB_NOLOCKING, 1));
		if (!strcasecmp(value, "db_nommap"))
			return (dbenv->set_flags(dbenv, DB_NOMMAP, 1));
		if (!strcasecmp(value, "db_nopanic"))
			return (dbenv->set_flags(dbenv, DB_NOPANIC, 1));
		if (!strcasecmp(value, "db_region_init"))
			return (dbenv->set_flags(dbenv, DB_REGION_INIT, 1));
		if (!strcasecmp(value, "db_txn_nosync"))
			return (dbenv->set_flags(dbenv, DB_TXN_NOSYNC, 1));
		if (!strcasecmp(value, "db_yieldcpu"))
			return (dbenv->set_flags(dbenv, DB_YIELDCPU, 1));
		goto badarg;
	}

	if (!strcasecmp(name, "set_lg_bsize")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_lg_bsize(dbenv, (u_int32_t)v1));
	}

	if (!strcasecmp(name, "set_lg_max")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_lg_max(dbenv, (u_int32_t)v1));
	}

	if (!strcasecmp(name, "set_lg_regionmax")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_lg_regionmax(dbenv, (u_int32_t)v1));
	}

	if (!strcasecmp(name, "set_lg_dir") ||
	    !strcasecmp(name, "db_log_dir"))		/* Compatibility. */
		return (dbenv->set_lg_dir(dbenv, value));

	if (!strcasecmp(name, "set_lk_detect")) {
		if (sscanf(value, "%40s %c", arg, &v4) != 1)
			goto badarg;
		if (!strcasecmp(value, "db_lock_default"))
			flags = DB_LOCK_DEFAULT;
		else if (!strcasecmp(value, "db_lock_expire"))
			flags = DB_LOCK_EXPIRE;
		else if (!strcasecmp(value, "db_lock_maxlocks"))
			flags = DB_LOCK_MAXLOCKS;
		else if (!strcasecmp(value, "db_lock_minlocks"))
			flags = DB_LOCK_MINLOCKS;
		else if (!strcasecmp(value, "db_lock_minwrite"))
			flags = DB_LOCK_MINWRITE;
		else if (!strcasecmp(value, "db_lock_oldest"))
			flags = DB_LOCK_OLDEST;
		else if (!strcasecmp(value, "db_lock_random"))
			flags = DB_LOCK_RANDOM;
		else if (!strcasecmp(value, "db_lock_youngest"))
			flags = DB_LOCK_YOUNGEST;
		else
			goto badarg;
		return (dbenv->set_lk_detect(dbenv, flags));
	}

	if (!strcasecmp(name, "set_lk_max")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_lk_max(dbenv, (u_int32_t)v1));
	}

	if (!strcasecmp(name, "set_lk_max_locks")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_lk_max_locks(dbenv, (u_int32_t)v1));
	}

	if (!strcasecmp(name, "set_lk_max_lockers")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_lk_max_lockers(dbenv, (u_int32_t)v1));
	}

	if (!strcasecmp(name, "set_lk_max_objects")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_lk_max_objects(dbenv, (u_int32_t)v1));
	}

	if (!strcasecmp(name, "set_lock_timeout")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_timeout(
		    dbenv, (u_int32_t)v1, DB_SET_LOCK_TIMEOUT));
	}

	if (!strcasecmp(name, "set_mp_mmapsize")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_mp_mmapsize(dbenv, (u_int32_t)v1));
	}

	if (!strcasecmp(name, "set_region_init")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1 || v1 != 1)
			goto badarg;
		return (dbenv->set_flags(
		    dbenv, DB_REGION_INIT, v1 == 0 ? 0 : 1));
	}

	if (!strcasecmp(name, "set_shm_key")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		return (dbenv->set_shm_key(dbenv, (long)v1));
	}

	if (!strcasecmp(name, "set_tas_spins")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_tas_spins(dbenv, (u_int32_t)v1));
	}

	if (!strcasecmp(name, "set_tmp_dir") ||
	    !strcasecmp(name, "db_tmp_dir"))		/* Compatibility.*/
		return (dbenv->set_tmp_dir(dbenv, value));

	if (!strcasecmp(name, "set_tx_max")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_tx_max(dbenv, (u_int32_t)v1));
	}

	if (!strcasecmp(name, "set_txn_timeout")) {
		if (sscanf(value, "%lu %c", &v1, &v4) != 1)
			goto badarg;
		__DB_OVFL(v1, UINT32_T_MAX);
		return (dbenv->set_timeout(
		    dbenv, (u_int32_t)v1, DB_SET_TXN_TIMEOUT));
	}

	if (!strcasecmp(name, "set_verbose")) {
		if (sscanf(value, "%40s %c", arg, &v4) != 1)
			goto badarg;

		if (!strcasecmp(value, "db_verb_chkpoint"))
			flags = DB_VERB_CHKPOINT;
		else if (!strcasecmp(value, "db_verb_deadlock"))
			flags = DB_VERB_DEADLOCK;
		else if (!strcasecmp(value, "db_verb_recovery"))
			flags = DB_VERB_RECOVERY;
		else if (!strcasecmp(value, "db_verb_waitsfor"))
			flags = DB_VERB_WAITSFOR;
		else
			goto badarg;
		return (dbenv->set_verbose(dbenv, flags, 1));
	}

	__db_err(dbenv, "unrecognized name-value pair: %s", s);
	return (EINVAL);

badarg:	__db_err(dbenv, "incorrect arguments for name-value pair: %s", s);
	return (EINVAL);

toobig:	__db_err(dbenv,
	    "%s: %lu larger than maximum value %lu", s, __v, __max);
	return (EINVAL);
}

/*
 * __db_tmp_open --
 *	Create a temporary file.
 */
static int
__db_tmp_open(dbenv, tmp_oflags, path, fhp)
	DB_ENV *dbenv;
	u_int32_t tmp_oflags;
	char *path;
	DB_FH *fhp;
{
	u_long pid;
	int mode, isdir, ret;
	const char *p;
	char *trv;

	/*
	 * Check the target directory; if you have six X's and it doesn't
	 * exist, this runs for a *very* long time.
	 */
	if ((ret = __os_exists(path, &isdir)) != 0) {
		__db_err(dbenv, "%s: %s", path, db_strerror(ret));
		return (ret);
	}
	if (!isdir) {
		__db_err(dbenv, "%s: %s", path, db_strerror(EINVAL));
		return (EINVAL);
	}

	/* Build the path. */
	for (trv = path; *trv != '\0'; ++trv)
		;
	*trv = PATH_SEPARATOR[0];
	for (p = DB_TRAIL; (*++trv = *p) != '\0'; ++p)
		;

	/*
	 * Replace the X's with the process ID.  Pid should be a pid_t,
	 * but we use unsigned long for portability.
	 */
	for (pid = getpid(); *--trv == 'X'; pid /= 10)
		switch (pid % 10) {
		case 0: *trv = '0'; break;
		case 1: *trv = '1'; break;
		case 2: *trv = '2'; break;
		case 3: *trv = '3'; break;
		case 4: *trv = '4'; break;
		case 5: *trv = '5'; break;
		case 6: *trv = '6'; break;
		case 7: *trv = '7'; break;
		case 8: *trv = '8'; break;
		case 9: *trv = '9'; break;
		}
	++trv;

	/* Set up open flags and mode. */
	mode = __db_omode("rw----");

	/* Loop, trying to open a file. */
	for (;;) {
		if ((ret = __os_open(dbenv, path,
		    tmp_oflags | DB_OSO_CREATE | DB_OSO_EXCL, mode, fhp)) == 0)
			return (0);

		/*
		 * !!!:
		 * If we don't get an EEXIST error, then there's something
		 * seriously wrong.  Unfortunately, if the implementation
		 * doesn't return EEXIST for O_CREAT and O_EXCL regardless
		 * of other possible errors, we've lost.
		 */
		if (ret != EEXIST) {
			__db_err(dbenv,
			    "tmp_open: %s: %s", path, db_strerror(ret));
			return (ret);
		}

		/*
		 * Tricky little algorithm for backward compatibility.
		 * Assumes sequential ordering of lower-case characters.
		 */
		for (;;) {
			if (*trv == '\0')
				return (EINVAL);
			if (*trv == 'z')
				*trv++ = 'a';
			else {
				if (isdigit((int)*trv))
					*trv = 'a';
				else
					++*trv;
				break;
			}
		}
	}
	/* NOTREACHED */
}
