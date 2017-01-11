/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 1999-2001
 *	Sleepycat Software.  All rights reserved.
 */

#include "db_config.h"

#ifndef lint
static const char revid[] = "Id: tcl_db_pkg.c,v 11.106 2001/11/16 16:19:54 bostic Exp ";
#endif /* not lint */

#ifndef NO_SYSTEM_INCLUDES
#include <sys/types.h>

#include <stdlib.h>
#include <string.h>
#include <tcl.h>
#endif

#define	DB_DBM_HSEARCH 1

#include "db_int.h"
#include "db_page.h"
#include "hash.h"
#include "tcl_db.h"

/* XXX we must declare global data in just one place */
DBTCL_GLOBAL __dbtcl_global;

/*
 * Prototypes for procedures defined later in this file:
 */
static int	berkdb_Cmd __P((ClientData, Tcl_Interp *, int,
    Tcl_Obj * CONST*));
static int	bdb_EnvOpen __P((Tcl_Interp *, int, Tcl_Obj * CONST*,
    DBTCL_INFO *, DB_ENV **));
static int	bdb_DbOpen __P((Tcl_Interp *, int, Tcl_Obj * CONST*,
    DBTCL_INFO *, DB **));
static int	bdb_DbRemove __P((Tcl_Interp *, int, Tcl_Obj * CONST*));
static int	bdb_DbRename __P((Tcl_Interp *, int, Tcl_Obj * CONST*));
static int	bdb_DbUpgrade __P((Tcl_Interp *, int, Tcl_Obj * CONST*));
static int	bdb_DbVerify __P((Tcl_Interp *, int, Tcl_Obj * CONST*));
static int	bdb_Version __P((Tcl_Interp *, int, Tcl_Obj * CONST*));
static int	bdb_Handles __P((Tcl_Interp *, int, Tcl_Obj * CONST*));

static int	tcl_bt_compare __P((DB *, const DBT *, const DBT *));
static int	tcl_compare_callback __P((DB *, const DBT *, const DBT *,
    Tcl_Obj *, char *));
static int	tcl_dup_compare __P((DB *, const DBT *, const DBT *));
static u_int32_t tcl_h_hash __P((DB *, const void *, u_int32_t));
static int	tcl_rep_send __P((DB_ENV *,
    const DBT *, const DBT *, int, u_int32_t));

/*
 * Db_tcl_Init --
 *
 * This is a package initialization procedure, which is called by Tcl when
 * this package is to be added to an interpreter.  The name is based on the
 * name of the shared library, currently libdb_tcl-X.Y.so, which Tcl uses
 * to determine the name of this function.
 */
int
Db_tcl_Init(interp)
	Tcl_Interp *interp;		/* Interpreter in which the package is
					 * to be made available. */
{
	int code;

	code = Tcl_PkgProvide(interp, "Db_tcl", "1.0");
	if (code != TCL_OK)
		return (code);

	Tcl_CreateObjCommand(interp, "berkdb", (Tcl_ObjCmdProc *)berkdb_Cmd,
	    (ClientData)0, NULL);
	/*
	 * Create shared global debugging variables
	 */
	Tcl_LinkVar(interp, "__debug_on", (char *)&__debug_on, TCL_LINK_INT);
	Tcl_LinkVar(interp, "__debug_print", (char *)&__debug_print,
	    TCL_LINK_INT);
	Tcl_LinkVar(interp, "__debug_stop", (char *)&__debug_stop,
	    TCL_LINK_INT);
	Tcl_LinkVar(interp, "__debug_test", (char *)&__debug_test,
	    TCL_LINK_INT);
	LIST_INIT(&__db_infohead);
	return (TCL_OK);
}

/*
 * berkdb_cmd --
 *	Implements the "berkdb" command.
 *	This command supports three sub commands:
 *	berkdb version - Returns a list {major minor patch}
 *	berkdb env - Creates a new DB_ENV and returns a binding
 *	  to a new command of the form dbenvX, where X is an
 *	  integer starting at 0 (dbenv0, dbenv1, ...)
 *	berkdb open - Creates a new DB (optionally within
 *	  the given environment.  Returns a binding to a new
 *	  command of the form dbX, where X is an integer
 *	  starting at 0 (db0, db1, ...)
 */
static int
berkdb_Cmd(notused, interp, objc, objv)
	ClientData notused;		/* Not used. */
	Tcl_Interp *interp;		/* Interpreter */
	int objc;			/* How many arguments? */
	Tcl_Obj *CONST objv[];		/* The argument objects */
{
	static char *berkdbcmds[] = {
		"dbremove",
		"dbrename",
		"dbverify",
		"env",
		"envremove",
		"handles",
		"open",
		"upgrade",
		"version",
		/* All below are compatibility functions */
		"hcreate",	"hsearch",	"hdestroy",
		"dbminit",	"fetch",	"store",
		"delete",	"firstkey",	"nextkey",
		"ndbm_open",	"dbmclose",
		/* All below are convenience functions */
		"rand",		"random_int",	"srand",
		"debug_check",
		NULL
	};
	/*
	 * All commands enums below ending in X are compatibility
	 */
	enum berkdbcmds {
		BDB_DBREMOVE,
		BDB_DBRENAME,
		BDB_DBVERIFY,
		BDB_ENV,
		BDB_ENVREMOVE,
		BDB_HANDLES,
		BDB_OPEN,
		BDB_UPGRADE,
		BDB_VERSION,
		BDB_HCREATEX,	BDB_HSEARCHX,	BDB_HDESTROYX,
		BDB_DBMINITX,	BDB_FETCHX,	BDB_STOREX,
		BDB_DELETEX,	BDB_FIRSTKEYX,	BDB_NEXTKEYX,
		BDB_NDBMOPENX,	BDB_DBMCLOSEX,
		BDB_RANDX,	BDB_RAND_INTX,	BDB_SRANDX,
		BDB_DBGCKX
	};
	static int env_id = 0;
	static int db_id = 0;
	static int ndbm_id = 0;

	DB *dbp;
	DBM *ndbmp;
	DBTCL_INFO *ip;
	DB_ENV *envp;
	Tcl_Obj *res;
	int cmdindex, result;
	char newname[MSG_SIZE];

	COMPQUIET(notused, NULL);

	Tcl_ResetResult(interp);
	memset(newname, 0, MSG_SIZE);
	result = TCL_OK;
	if (objc <= 1) {
		Tcl_WrongNumArgs(interp, 1, objv, "command cmdargs");
		return (TCL_ERROR);
	}

	/*
	 * Get the command name index from the object based on the berkdbcmds
	 * defined above.
	 */
	if (Tcl_GetIndexFromObj(interp,
	    objv[1], berkdbcmds, "command", TCL_EXACT, &cmdindex) != TCL_OK)
		return (IS_HELP(objv[1]));
	res = NULL;
	switch ((enum berkdbcmds)cmdindex) {
	case BDB_VERSION:
		_debug_check();
		result = bdb_Version(interp, objc, objv);
		break;
	case BDB_HANDLES:
		result = bdb_Handles(interp, objc, objv);
		break;
	case BDB_ENV:
		snprintf(newname, sizeof(newname), "env%d", env_id);
		ip = _NewInfo(interp, NULL, newname, I_ENV);
		if (ip != NULL) {
			result = bdb_EnvOpen(interp, objc, objv, ip, &envp);
			if (result == TCL_OK && envp != NULL) {
				env_id++;
				Tcl_CreateObjCommand(interp, newname,
				    (Tcl_ObjCmdProc *)env_Cmd,
				    (ClientData)envp, NULL);
				/* Use ip->i_name - newname is overwritten */
				res =
				    Tcl_NewStringObj(newname, strlen(newname));
				_SetInfoData(ip, envp);
			} else
				_DeleteInfo(ip);
		} else {
			Tcl_SetResult(interp, "Could not set up info",
			    TCL_STATIC);
			result = TCL_ERROR;
		}
		break;
	case BDB_DBREMOVE:
		result = bdb_DbRemove(interp, objc, objv);
		break;
	case BDB_DBRENAME:
		result = bdb_DbRename(interp, objc, objv);
		break;
	case BDB_UPGRADE:
		result = bdb_DbUpgrade(interp, objc, objv);
		break;
	case BDB_DBVERIFY:
		result = bdb_DbVerify(interp, objc, objv);
		break;
	case BDB_ENVREMOVE:
		result = tcl_EnvRemove(interp, objc, objv, NULL, NULL);
		break;
	case BDB_OPEN:
		snprintf(newname, sizeof(newname), "db%d", db_id);
		ip = _NewInfo(interp, NULL, newname, I_DB);
		if (ip != NULL) {
			result = bdb_DbOpen(interp, objc, objv, ip, &dbp);
			if (result == TCL_OK && dbp != NULL) {
				db_id++;
				Tcl_CreateObjCommand(interp, newname,
				    (Tcl_ObjCmdProc *)db_Cmd,
				    (ClientData)dbp, NULL);
				/* Use ip->i_name - newname is overwritten */
				res =
				    Tcl_NewStringObj(newname, strlen(newname));
				_SetInfoData(ip, dbp);
			} else
				_DeleteInfo(ip);
		} else {
			Tcl_SetResult(interp, "Could not set up info",
			    TCL_STATIC);
			result = TCL_ERROR;
		}
		break;
	case BDB_HCREATEX:
	case BDB_HSEARCHX:
	case BDB_HDESTROYX:
		result = bdb_HCommand(interp, objc, objv);
		break;
	case BDB_DBMINITX:
	case BDB_DBMCLOSEX:
	case BDB_FETCHX:
	case BDB_STOREX:
	case BDB_DELETEX:
	case BDB_FIRSTKEYX:
	case BDB_NEXTKEYX:
		result = bdb_DbmCommand(interp, objc, objv, DBTCL_DBM, NULL);
		break;
	case BDB_NDBMOPENX:
		snprintf(newname, sizeof(newname), "ndbm%d", ndbm_id);
		ip = _NewInfo(interp, NULL, newname, I_NDBM);
		if (ip != NULL) {
			result = bdb_NdbmOpen(interp, objc, objv, &ndbmp);
			if (result == TCL_OK) {
				ndbm_id++;
				Tcl_CreateObjCommand(interp, newname,
				    (Tcl_ObjCmdProc *)ndbm_Cmd,
				    (ClientData)ndbmp, NULL);
				/* Use ip->i_name - newname is overwritten */
				res =
				    Tcl_NewStringObj(newname, strlen(newname));
				_SetInfoData(ip, ndbmp);
			} else
				_DeleteInfo(ip);
		} else {
			Tcl_SetResult(interp, "Could not set up info",
			    TCL_STATIC);
			result = TCL_ERROR;
		}
		break;
	case BDB_RANDX:
	case BDB_RAND_INTX:
	case BDB_SRANDX:
		result = bdb_RandCommand(interp, objc, objv);
		break;
	case BDB_DBGCKX:
		_debug_check();
		res = Tcl_NewIntObj(0);
		break;
	}
	/*
	 * For each different arg call different function to create
	 * new commands (or if version, get/return it).
	 */
	if (result == TCL_OK && res != NULL)
		Tcl_SetObjResult(interp, res);
	return (result);
}

/*
 * bdb_EnvOpen -
 *	Implements the environment open command.
 *	There are many, many options to the open command.
 *	Here is the general flow:
 *
 *	1.  Call db_env_create to create the env handle.
 *	2.  Parse args tracking options.
 *	3.  Make any pre-open setup calls necessary.
 *	4.  Call DB_ENV->open to open the env.
 *	5.  Return env widget handle to user.
 */
static int
bdb_EnvOpen(interp, objc, objv, ip, env)
	Tcl_Interp *interp;		/* Interpreter */
	int objc;			/* How many arguments? */
	Tcl_Obj *CONST objv[];		/* The argument objects */
	DBTCL_INFO *ip;			/* Our internal info */
	DB_ENV **env;			/* Environment pointer */
{
	static char *envopen[] = {
		"-cachesize",
		"-cdb",
		"-cdb_alldb",
		"-client_timeout",
		"-create",
		"-data_dir",
		"-errfile",
		"-errpfx",
		"-home",
		"-lock",
		"-lock_conflict",
		"-lock_detect",
		"-lock_max",
		"-lock_max_locks",
		"-lock_max_lockers",
		"-lock_max_objects",
		"-lock_timeout",
		"-log",
		"-log_buffer",
		"-log_dir",
		"-log_max",
		"-log_regionmax",
		"-mmapsize",
		"-mode",
		"-nommap",
		"-private",
		"-recover",
		"-recover_fatal",
		"-region_init",
		"-rep_client",
		"-rep_master",
		"-rep_transport",
		"-server",
		"-server_timeout",
		"-shm_key",
		"-system_mem",
		"-tmp_dir",
		"-txn",
		"-txn_max",
		"-txn_timeout",
		"-txn_timestamp",
		"-use_environ",
		"-use_environ_root",
		"-verbose",
		NULL
	};
	/*
	 * !!!
	 * These have to be in the same order as the above,
	 * which is close to but not quite alphabetical.
	 */
	enum envopen {
		ENV_CACHESIZE,
		ENV_CDB,
		ENV_CDB_ALLDB,
		ENV_CLIENT_TO,
		ENV_CREATE,
		ENV_DATA_DIR,
		ENV_ERRFILE,
		ENV_ERRPFX,
		ENV_HOME,
		ENV_LOCK,
		ENV_CONFLICT,
		ENV_DETECT,
		ENV_LOCK_MAX,
		ENV_LOCK_MAX_LOCKS,
		ENV_LOCK_MAX_LOCKERS,
		ENV_LOCK_MAX_OBJECTS,
		ENV_LOCK_TIMEOUT,
		ENV_LOG,
		ENV_LOG_BUFFER,
		ENV_LOG_DIR,
		ENV_LOG_MAX,
		ENV_LOG_REGIONMAX,
		ENV_MMAPSIZE,
		ENV_MODE,
		ENV_NOMMAP,
		ENV_PRIVATE,
		ENV_RECOVER,
		ENV_RECOVER_FATAL,
		ENV_REGION_INIT,
		ENV_REP_CLIENT,
		ENV_REP_MASTER,
		ENV_REP_TRANSPORT,
		ENV_SERVER,
		ENV_SERVER_TO,
		ENV_SHM_KEY,
		ENV_SYSTEM_MEM,
		ENV_TMP_DIR,
		ENV_TXN,
		ENV_TXN_MAX,
		ENV_TXN_TIMEOUT,
		ENV_TXN_TIME,
		ENV_USE_ENVIRON,
		ENV_USE_ENVIRON_ROOT,
		ENV_VERBOSE
	};
	Tcl_Obj **myobjv, **myobjv1;
	time_t time;
	u_int32_t detect, gbytes, bytes, ncaches, logbufset, logmaxset;
	u_int32_t open_flags, set_flag, size, uintarg;
	u_int8_t *conflicts;
	int i, intarg, j;
	int mode, myobjc, nmodes, optindex, rep_client, rep_eid, rep_master;
	int result, ret, temp;
	long client_to, server_to, shm;
	char *arg, *home, *server;

	result = TCL_OK;
	rep_client = rep_eid = rep_master = 0;
	mode = 0;
	set_flag = 0;
	home = NULL;

	/*
	 * XXX
	 * If/when our Tcl interface becomes thread-safe, we should enable
	 * DB_THREAD here.
	 *
	 * Historically, a key stumbling block was the log_get interface,
	 * which could only do relative operations in a non-threaded
	 * environment.  This is no longer an issue, thanks to log cursors,
	 * but we need to look at making sure DBTCL_INFO structs
	 * are safe to share across threads (they're not mutex-protected)
	 * before we declare the Tcl interface thread-safe.  Meanwhile,
	 * there's no strong reason to enable DB_THREAD.
	 */
	open_flags = DB_JOINENV;
	logmaxset = logbufset = 0;

	if (objc <= 2) {
		Tcl_WrongNumArgs(interp, 2, objv, "?args?");
		return (TCL_ERROR);
	}

	/*
	 * Server code must go before the call to db_env_create.
	 */
	server = NULL;
	server_to = client_to = 0;
	i = 2;
	while (i < objc) {
		if (Tcl_GetIndexFromObj(interp, objv[i++], envopen, "option",
		    TCL_EXACT, &optindex) != TCL_OK) {
			Tcl_ResetResult(interp);
			continue;
		}
		switch ((enum envopen)optindex) {
		case ENV_SERVER:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-server hostname");
				result = TCL_ERROR;
				break;
			}
			server = Tcl_GetStringFromObj(objv[i++], NULL);
			break;
		case ENV_SERVER_TO:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-server_to secs");
				result = TCL_ERROR;
				break;
			}
			result = Tcl_GetLongFromObj(interp, objv[i++],
			    &server_to);
			break;
		case ENV_CLIENT_TO:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-client_to secs");
				result = TCL_ERROR;
				break;
			}
			result = Tcl_GetLongFromObj(interp, objv[i++],
			    &client_to);
			break;
		default:
			break;
		}
	}
	if (server != NULL) {
		ret = db_env_create(env, DB_CLIENT);
		if (ret)
			return (_ReturnSetup(interp, ret, "db_env_create"));
		(*env)->set_errpfx((*env), ip->i_name);
		(*env)->set_errcall((*env), _ErrorFunc);
		if ((ret = (*env)->set_rpc_server((*env), NULL, server,
		    client_to, server_to, 0)) != 0) {
			result = TCL_ERROR;
			goto error;
		}
	} else {
		/*
		 * Create the environment handle before parsing the args
		 * since we'll be modifying the environment as we parse.
		 */
		ret = db_env_create(env, 0);
		if (ret)
			return (_ReturnSetup(interp, ret, "db_env_create"));
		(*env)->set_errpfx((*env), ip->i_name);
		(*env)->set_errcall((*env), _ErrorFunc);
	}

	/* Hang our info pointer on the env handle, so we can do callbacks. */
	(*env)->app_private = ip;

	/*
	 * Get the command name index from the object based on the bdbcmds
	 * defined above.
	 */
	i = 2;
	while (i < objc) {
		if (Tcl_GetIndexFromObj(interp, objv[i], envopen, "option",
		    TCL_EXACT, &optindex) != TCL_OK) {
			result = IS_HELP(objv[i]);
			goto error;
		}
		i++;
		switch ((enum envopen)optindex) {
		case ENV_SERVER:
		case ENV_SERVER_TO:
		case ENV_CLIENT_TO:
			/*
			 * Already handled these, skip them and their arg.
			 */
			i++;
			break;
		case ENV_CDB:
			FLD_SET(open_flags, DB_INIT_CDB | DB_INIT_MPOOL);
			FLD_CLR(open_flags, DB_JOINENV);
			break;
		case ENV_CDB_ALLDB:
			FLD_SET(set_flag, DB_CDB_ALLDB);
			break;
		case ENV_LOCK:
			FLD_SET(open_flags, DB_INIT_LOCK | DB_INIT_MPOOL);
			FLD_CLR(open_flags, DB_JOINENV);
			break;
		case ENV_LOG:
			FLD_SET(open_flags, DB_INIT_LOG | DB_INIT_MPOOL);
			FLD_CLR(open_flags, DB_JOINENV);
			break;
		case ENV_TXN:
			FLD_SET(open_flags, DB_INIT_LOCK |
			    DB_INIT_LOG | DB_INIT_MPOOL | DB_INIT_TXN);
			FLD_CLR(open_flags, DB_JOINENV);
			/* Make sure we have an arg to check against! */
			if (i < objc) {
				arg = Tcl_GetStringFromObj(objv[i], NULL);
				if (strcmp(arg, "nosync") == 0) {
					FLD_SET(set_flag, DB_TXN_NOSYNC);
					i++;
				}
			}
			break;
		case ENV_CREATE:
			FLD_SET(open_flags, DB_CREATE | DB_INIT_MPOOL);
			FLD_CLR(open_flags, DB_JOINENV);
			break;
		case ENV_HOME:
			/* Make sure we have an arg to check against! */
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-home dir?");
				result = TCL_ERROR;
				break;
			}
			home = Tcl_GetStringFromObj(objv[i++], NULL);
			break;
		case ENV_MODE:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-mode mode?");
				result = TCL_ERROR;
				break;
			}
			/*
			 * Don't need to check result here because
			 * if TCL_ERROR, the error message is already
			 * set up, and we'll bail out below.  If ok,
			 * the mode is set and we go on.
			 */
			result = Tcl_GetIntFromObj(interp, objv[i++], &mode);
			break;
		case ENV_NOMMAP:
			FLD_SET(set_flag, DB_NOMMAP);
			break;
		case ENV_PRIVATE:
			FLD_SET(open_flags, DB_PRIVATE | DB_INIT_MPOOL);
			FLD_CLR(open_flags, DB_JOINENV);
			break;
		case ENV_RECOVER:
			FLD_SET(open_flags, DB_RECOVER);
			break;
		case ENV_RECOVER_FATAL:
			FLD_SET(open_flags, DB_RECOVER_FATAL);
			break;
		case ENV_REP_CLIENT:
			rep_client = 1;
			break;
		case ENV_REP_MASTER:
			rep_master = 1;
			break;
		case ENV_REP_TRANSPORT:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-rep_transport {envid sendproc}");
				result = TCL_ERROR;
				break;
			}

			/*
			 * Store the objects containing the machine ID
			 * and the procedure name.  We don't need to crack
			 * the send procedure out now, but we do convert the
			 * machine ID to an int, since set_rep_transport needs
			 * it.  Even so, it'll be easier later to deal with
			 * the Tcl_Obj *, so we save that, not the int.
			 *
			 * Note that we Tcl_IncrRefCount both objects
			 * independently;  Tcl is free to discard the list
			 * that they're bundled into.
			 */
			result = Tcl_ListObjGetElements(interp, objv[i++],
			    &myobjc, &myobjv);
			if (myobjc != 2) {
				Tcl_SetResult(interp,
				    "List must be {envid sendproc}",
				    TCL_STATIC);
				result = TCL_ERROR;
				break;
			}

			/*
			 * Check that the machine ID is an int.  Note that
			 * we do want to use GetIntFromObj;  the machine
			 * ID is explicitly an int, not a u_int32_t.
			 */
			ip->i_rep_eid = myobjv[0];
			Tcl_IncrRefCount(ip->i_rep_eid);
			result = Tcl_GetIntFromObj(interp,
			    ip->i_rep_eid, &intarg);
			if (result != TCL_OK)
				break;

			ip->i_rep_send = myobjv[1];
			Tcl_IncrRefCount(ip->i_rep_send);
			_debug_check();
			ret = (*env)->set_rep_transport(*env,
			    intarg, tcl_rep_send);
			result = _ReturnSetup(interp, ret, "set_rep_transport");
			break;
		case ENV_SYSTEM_MEM:
			FLD_SET(open_flags, DB_SYSTEM_MEM);
			break;
		case ENV_USE_ENVIRON_ROOT:
			FLD_SET(open_flags, DB_USE_ENVIRON_ROOT);
			break;
		case ENV_USE_ENVIRON:
			FLD_SET(open_flags, DB_USE_ENVIRON);
			break;
		case ENV_VERBOSE:
			result = Tcl_ListObjGetElements(interp, objv[i],
			    &myobjc, &myobjv);
			if (result == TCL_OK)
				i++;
			else
				break;
			if (myobjc != 2) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-verbose {which on|off}?");
				result = TCL_ERROR;
				break;
			}
			result = tcl_EnvVerbose(interp, *env,
			    myobjv[0], myobjv[1]);
			break;
		case ENV_REGION_INIT:
			_debug_check();
			ret = (*env)->set_flags(*env, DB_REGION_INIT, 1);
			result = _ReturnSetup(interp, ret, "region_init");
			break;
		case ENV_CACHESIZE:
			result = Tcl_ListObjGetElements(interp, objv[i],
			    &myobjc, &myobjv);
			if (result == TCL_OK)
				i++;
			else
				break;
			if (myobjc != 3) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-cachesize {gbytes bytes ncaches}?");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, myobjv[0], &gbytes);
			if (result != TCL_OK)
				break;
			result = _GetUInt32(interp, myobjv[1], &bytes);
			if (result != TCL_OK)
				break;
			result = _GetUInt32(interp, myobjv[2], &ncaches);
			if (result != TCL_OK)
				break;
			_debug_check();
			ret = (*env)->set_cachesize(*env, gbytes, bytes,
			    ncaches);
			result = _ReturnSetup(interp, ret, "set_cachesize");
			break;
		case ENV_MMAPSIZE:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-mmapsize size?");
				result = TCL_ERROR;
				break;
			}
			result = Tcl_GetIntFromObj(interp, objv[i++], &intarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*env)->set_mp_mmapsize(*env,
				    (size_t)intarg);
				result = _ReturnSetup(interp, ret, "mmapsize");
			}
			break;
		case ENV_SHM_KEY:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-shm_key key?");
				result = TCL_ERROR;
				break;
			}
			result = Tcl_GetLongFromObj(interp, objv[i++], &shm);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*env)->set_shm_key(*env, shm);
				result = _ReturnSetup(interp, ret, "shm_key");
			}
			break;
		case ENV_LOG_MAX:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-log_max max?");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, objv[i++], &uintarg);
			if (result == TCL_OK && logbufset) {
				_debug_check();
				ret = (*env)->set_lg_max(*env, uintarg);
				result = _ReturnSetup(interp, ret, "log_max");
				logbufset = 0;
			} else
				logmaxset = uintarg;
			break;
		case ENV_LOG_REGIONMAX:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-log_regionmax size?");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, objv[i++], &uintarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*env)->set_lg_regionmax(*env, uintarg);
				result =
				    _ReturnSetup(interp, ret, "log_regionmax");
			}
			break;
		case ENV_LOG_BUFFER:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-log_buffer size?");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, objv[i++], &uintarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*env)->set_lg_bsize(*env, uintarg);
				result = _ReturnSetup(interp, ret, "log_bsize");
				logbufset = 1;
				if (logmaxset) {
					_debug_check();
					ret = (*env)->set_lg_max(*env,
					    logmaxset);
					result = _ReturnSetup(interp, ret,
					    "log_max");
					logmaxset = 0;
					logbufset = 0;
				}
			}
			break;
		case ENV_CONFLICT:
			/*
			 * Get conflict list.  List is:
			 * {nmodes {matrix}}
			 *
			 * Where matrix must be nmodes*nmodes big.
			 * Set up conflicts array to pass.
			 */
			result = Tcl_ListObjGetElements(interp, objv[i],
			    &myobjc, &myobjv);
			if (result == TCL_OK)
				i++;
			else
				break;
			if (myobjc != 2) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-lock_conflict {nmodes {matrix}}?");
				result = TCL_ERROR;
				break;
			}
			result = Tcl_GetIntFromObj(interp, myobjv[0], &nmodes);
			if (result != TCL_OK)
				break;
			result = Tcl_ListObjGetElements(interp, myobjv[1],
			    &myobjc, &myobjv1);
			if (myobjc != (nmodes * nmodes)) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-lock_conflict {nmodes {matrix}}?");
				result = TCL_ERROR;
				break;
			}
			size = sizeof(u_int8_t) * nmodes*nmodes;
			ret = __os_malloc(*env, size, &conflicts);
			if (ret != 0) {
				result = TCL_ERROR;
				break;
			}
			for (j = 0; j < myobjc; j++) {
				result = Tcl_GetIntFromObj(interp, myobjv1[j],
				    &temp);
				conflicts[j] = temp;
				if (result != TCL_OK) {
					__os_free(NULL, conflicts, size);
					break;
				}
			}
			_debug_check();
			ret = (*env)->set_lk_conflicts(*env,
			    (u_int8_t *)conflicts, nmodes);
			__os_free(NULL, conflicts, size);
			result = _ReturnSetup(interp, ret, "set_lk_conflicts");
			break;
		case ENV_DETECT:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-lock_detect policy?");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			if (strcmp(arg, "default") == 0)
				detect = DB_LOCK_DEFAULT;
			else if (strcmp(arg, "expire") == 0)
				detect = DB_LOCK_EXPIRE;
			else if (strcmp(arg, "maxlocks") == 0)
				detect = DB_LOCK_MAXLOCKS;
			else if (strcmp(arg, "minlocks") == 0)
				detect = DB_LOCK_MINLOCKS;
			else if (strcmp(arg, "minwrites") == 0)
				detect = DB_LOCK_MINWRITE;
			else if (strcmp(arg, "oldest") == 0)
				detect = DB_LOCK_OLDEST;
			else if (strcmp(arg, "youngest") == 0)
				detect = DB_LOCK_YOUNGEST;
			else if (strcmp(arg, "random") == 0)
				detect = DB_LOCK_RANDOM;
			else {
				Tcl_AddErrorInfo(interp,
				    "lock_detect: illegal policy");
				result = TCL_ERROR;
				break;
			}
			_debug_check();
			ret = (*env)->set_lk_detect(*env, detect);
			result = _ReturnSetup(interp, ret, "lock_detect");
			break;
		case ENV_LOCK_MAX:
		case ENV_LOCK_MAX_LOCKS:
		case ENV_LOCK_MAX_LOCKERS:
		case ENV_LOCK_MAX_OBJECTS:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-lock_max max?");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, objv[i++], &uintarg);
			if (result == TCL_OK) {
				_debug_check();
				switch ((enum envopen)optindex) {
				case ENV_LOCK_MAX:
					ret = (*env)->set_lk_max(*env,
					    uintarg);
					break;
				case ENV_LOCK_MAX_LOCKS:
					ret = (*env)->set_lk_max_locks(*env,
					    uintarg);
					break;
				case ENV_LOCK_MAX_LOCKERS:
					ret = (*env)->set_lk_max_lockers(*env,
					    uintarg);
					break;
				case ENV_LOCK_MAX_OBJECTS:
					ret = (*env)->set_lk_max_objects(*env,
					    uintarg);
					break;
				default:
					break;
				}
				result = _ReturnSetup(interp, ret, "lock_max");
			}
			break;
		case ENV_TXN_MAX:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-txn_max max?");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, objv[i++], &uintarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*env)->set_tx_max(*env, uintarg);
				result = _ReturnSetup(interp, ret, "txn_max");
			}
			break;
		case ENV_TXN_TIME:
		case ENV_TXN_TIMEOUT:
		case ENV_LOCK_TIMEOUT:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-txn_timestamp time?");
				result = TCL_ERROR;
				break;
			}
			result = Tcl_GetLongFromObj(interp, objv[i++],
			    (long *)&time);
			if (result == TCL_OK) {
				_debug_check();
				if (optindex == ENV_TXN_TIME)
					ret = (*env)->
					    set_tx_timestamp(*env, &time);
				else
					ret = (*env)->set_timeout(*env,
					    (db_timeout_t) time,
					    optindex == ENV_TXN_TIMEOUT ?
					    DB_SET_TXN_TIMEOUT :
					    DB_SET_LOCK_TIMEOUT);
				result = _ReturnSetup(interp, ret,
				    "txn_timestamp");
			}
			break;
		case ENV_ERRFILE:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-errfile file");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			/*
			 * If the user already set one, close it.
			 */
			if (ip->i_err != NULL)
				fclose(ip->i_err);
			ip->i_err = fopen(arg, "a");
			if (ip->i_err != NULL) {
				_debug_check();
				(*env)->set_errfile(*env, ip->i_err);
			}
			break;
		case ENV_ERRPFX:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-errpfx prefix");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			/*
			 * If the user already set one, free it.
			 */
			if (ip->i_errpfx != NULL)
				__os_freestr(NULL, ip->i_errpfx);
			if ((ret =
			    __os_strdup(*env, arg, &ip->i_errpfx)) != 0) {
				result = _ReturnSetup(interp, ret,
				    "__os_strdup");
				break;
			}
			if (ip->i_errpfx != NULL) {
				_debug_check();
				(*env)->set_errpfx(*env, ip->i_errpfx);
			}
			break;
		case ENV_DATA_DIR:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-data_dir dir");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			_debug_check();
			ret = (*env)->set_data_dir(*env, arg);
			result = _ReturnSetup(interp, ret, "set_data_dir");
			break;
		case ENV_LOG_DIR:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-log_dir dir");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			_debug_check();
			ret = (*env)->set_lg_dir(*env, arg);
			result = _ReturnSetup(interp, ret, "set_lg_dir");
			break;
		case ENV_TMP_DIR:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-tmp_dir dir");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			_debug_check();
			ret = (*env)->set_tmp_dir(*env, arg);
			result = _ReturnSetup(interp, ret, "set_tmp_dir");
			break;
		}
		/*
		 * If, at any time, parsing the args we get an error,
		 * bail out and return.
		 */
		if (result != TCL_OK)
			goto error;
	}

	/* We can't be both a replication client and a master. */
	if (rep_client && rep_master) {
		Tcl_SetResult(interp,
		    "Cannot be both a replication client and a master.\n",
		    TCL_STATIC);
		result = TCL_ERROR;
		goto error;
	}

	/*
	 * We have to check this here.  We want to set the log buffer
	 * size first, if it is specified.  So if the user did so,
	 * then we took care of it above.  But, if we get out here and
	 * logmaxset is non-zero, then they set the log_max without
	 * resetting the log buffer size, so we now have to do the
	 * call to set_lg_max, since we didn't do it above.
	 */
	if (logmaxset) {
		_debug_check();
		ret = (*env)->set_lg_max(*env, (u_int32_t)logmaxset);
		result = _ReturnSetup(interp, ret, "log_max");
	}

	if (result != TCL_OK)
		goto error;

	if (set_flag) {
		ret = (*env)->set_flags(*env, set_flag, 1);
		result = _ReturnSetup(interp, ret, "set_flags");
		if (result == TCL_ERROR)
			goto error;
		/*
		 * If we are successful, clear the result so that the
		 * return from set_flags isn't part of the result.
		 */
		Tcl_ResetResult(interp);
	}
	/*
	 * When we get here, we have already parsed all of our args
	 * and made all our calls to set up the environment.  Everything
	 * is okay so far, no errors, if we get here.
	 *
	 * Now open the environment.
	 */
	_debug_check();
	ret = (*env)->open(*env, home, open_flags, mode);
	result = _ReturnSetup(interp, ret, "env open");

	/*
	 * We already checked above that rep_master and rep_client aren't
	 * both specified.
	 */
	if (result == TCL_OK && (rep_master || rep_client)) {
		ret = (*env)->rep_start(*env, NULL,
		    rep_master ? DB_REP_MASTER : DB_REP_CLIENT);
		result = _ReturnSetup(interp, ret, "rep_start");
	}

error:
	if (result == TCL_ERROR) {
		if (ip->i_err) {
			fclose(ip->i_err);
			ip->i_err = NULL;
		}
		(void)(*env)->close(*env, 0);
		*env = NULL;
	}
	return (result);
}

/*
 * bdb_DbOpen --
 *	Implements the "db_create/db_open" command.
 *	There are many, many options to the open command.
 *	Here is the general flow:
 *
 *	0.  Preparse args to determine if we have -env.
 *	1.  Call db_create to create the db handle.
 *	2.  Parse args tracking options.
 *	3.  Make any pre-open setup calls necessary.
 *	4.  Call DB->open to open the database.
 *	5.  Return db widget handle to user.
 */
static int
bdb_DbOpen(interp, objc, objv, ip, dbp)
	Tcl_Interp *interp;		/* Interpreter */
	int objc;			/* How many arguments? */
	Tcl_Obj *CONST objv[];		/* The argument objects */
	DBTCL_INFO *ip;			/* Our internal info */
	DB **dbp;			/* DB handle */
{
	static char *bdbenvopen[] = {
		"-env",	NULL
	};
	enum bdbenvopen {
		TCL_DB_ENV0
	};
	static char *bdbopen[] = {
		"-btcompare",
		"-btree",
		"-cachesize",
		"-create",
		"-delim",
		"-dirty",
		"-dup",
		"-dupcompare",
		"-dupsort",
		"-env",
		"-errfile",
		"-errpfx",
		"-excl",
		"-extent",
		"-ffactor",
		"-hash",
		"-hashproc",
		"-len",
		"-lorder",
		"-minkey",
		"-mode",
		"-nelem",
		"-nommap",
		"-pad",
		"-pagesize",
		"-queue",
		"-rdonly",
		"-recno",
		"-recnum",
		"-renumber",
		"-revsplitoff",
		"-snapshot",
		"-source",
		"-truncate",
		"-test",
		"-unknown",
		"--",
		NULL
	};
	enum bdbopen {
		TCL_DB_BTCOMPARE,
		TCL_DB_BTREE,
		TCL_DB_CACHESIZE,
		TCL_DB_CREATE,
		TCL_DB_DELIM,
		TCL_DB_DIRTY,
		TCL_DB_DUP,
		TCL_DB_DUPCOMPARE,
		TCL_DB_DUPSORT,
		TCL_DB_ENV,
		TCL_DB_ERRFILE,
		TCL_DB_ERRPFX,
		TCL_DB_EXCL,
		TCL_DB_EXTENT,
		TCL_DB_FFACTOR,
		TCL_DB_HASH,
		TCL_DB_HASHPROC,
		TCL_DB_LEN,
		TCL_DB_LORDER,
		TCL_DB_MINKEY,
		TCL_DB_MODE,
		TCL_DB_NELEM,
		TCL_DB_NOMMAP,
		TCL_DB_PAD,
		TCL_DB_PAGESIZE,
		TCL_DB_QUEUE,
		TCL_DB_RDONLY,
		TCL_DB_RECNO,
		TCL_DB_RECNUM,
		TCL_DB_RENUMBER,
		TCL_DB_REVSPLIT,
		TCL_DB_SNAPSHOT,
		TCL_DB_SOURCE,
		TCL_DB_TRUNCATE,
		TCL_DB_TEST,
		TCL_DB_UNKNOWN,
		TCL_DB_ENDARG
	};

	DBTCL_INFO *envip, *errip;
	DBTYPE type;
	DB_ENV *envp;
	Tcl_Obj **myobjv;
	u_int32_t gbytes, bytes, ncaches, open_flags, uintarg;
	int endarg, i, intarg, mode, myobjc;
	int optindex, result, ret, set_err, set_flag, set_pfx, subdblen;
	u_char *subdbtmp;
	char *arg, *db, *subdb;

	type = DB_UNKNOWN;
	endarg = mode = set_err = set_flag = set_pfx = 0;
	result = TCL_OK;
	subdbtmp = NULL;
	db = subdb = NULL;

	/*
	 * XXX
	 * If/when our Tcl interface becomes thread-safe, we should enable
	 * DB_THREAD here.  See comment in bdb_EnvOpen().
	 */
	open_flags = 0;
	envp = NULL;

	if (objc < 2) {
		Tcl_WrongNumArgs(interp, 2, objv, "?args?");
		return (TCL_ERROR);
	}

	/*
	 * We must first parse for the environment flag, since that
	 * is needed for db_create.  Then create the db handle.
	 */
	i = 2;
	while (i < objc) {
		if (Tcl_GetIndexFromObj(interp, objv[i++], bdbenvopen,
		    "option", TCL_EXACT, &optindex) != TCL_OK) {
			/*
			 * Reset the result so we don't get
			 * an errant error message if there is another error.
			 */
			Tcl_ResetResult(interp);
			continue;
		}
		switch ((enum bdbenvopen)optindex) {
		case TCL_DB_ENV0:
			arg = Tcl_GetStringFromObj(objv[i], NULL);
			envp = NAME_TO_ENV(arg);
			if (envp == NULL) {
				Tcl_SetResult(interp,
				    "db open: illegal environment", TCL_STATIC);
				return (TCL_ERROR);
			}
		}
		break;
	}

	/*
	 * Create the db handle before parsing the args
	 * since we'll be modifying the database options as we parse.
	 */
	ret = db_create(dbp, envp, 0);
	if (ret)
		return (_ReturnSetup(interp, ret, "db_create"));

	/* Hang our info pointer on the DB handle, so we can do callbacks. */
	(*dbp)->cj_internal = ip;

	/*
	 * XXX Remove restriction when err stuff is not tied to env.
	 *
	 * The DB->set_err* functions actually overwrite in the
	 * environment.  So, if we are explicitly using an env,
	 * don't overwrite what we have already set up.  If we are
	 * not using one, then we set up since we get a private
	 * default env.
	 */
	/* XXX  - remove this conditional if/when err is not tied to env */
	if (envp == NULL) {
		(*dbp)->set_errpfx((*dbp), ip->i_name);
		(*dbp)->set_errcall((*dbp), _ErrorFunc);
	}
	envip = _PtrToInfo(envp); /* XXX */
	/*
	 * If we are using an env, we keep track of err info in the env's ip.
	 * Otherwise use the DB's ip.
	 */
	if (envip)
		errip = envip;
	else
		errip = ip;
	/*
	 * Get the option name index from the object based on the args
	 * defined above.
	 */
	i = 2;
	while (i < objc) {
		if (Tcl_GetIndexFromObj(interp, objv[i], bdbopen, "option",
		    TCL_EXACT, &optindex) != TCL_OK) {
			arg = Tcl_GetStringFromObj(objv[i], NULL);
			if (arg[0] == '-') {
				result = IS_HELP(objv[i]);
				goto error;
			} else
				Tcl_ResetResult(interp);
			break;
		}
		i++;
		switch ((enum bdbopen)optindex) {
		case TCL_DB_ENV:
			/*
			 * Already parsed this, skip it and the env pointer.
			 */
			i++;
			continue;
		case TCL_DB_BTREE:
			if (type != DB_UNKNOWN) {
				Tcl_SetResult(interp,
				    "Too many DB types specified", TCL_STATIC);
				result = TCL_ERROR;
				goto error;
			}
			type = DB_BTREE;
			break;
		case TCL_DB_HASH:
			if (type != DB_UNKNOWN) {
				Tcl_SetResult(interp,
				    "Too many DB types specified", TCL_STATIC);
				result = TCL_ERROR;
				goto error;
			}
			type = DB_HASH;
			break;
		case TCL_DB_RECNO:
			if (type != DB_UNKNOWN) {
				Tcl_SetResult(interp,
				    "Too many DB types specified", TCL_STATIC);
				result = TCL_ERROR;
				goto error;
			}
			type = DB_RECNO;
			break;
		case TCL_DB_QUEUE:
			if (type != DB_UNKNOWN) {
				Tcl_SetResult(interp,
				    "Too many DB types specified", TCL_STATIC);
				result = TCL_ERROR;
				goto error;
			}
			type = DB_QUEUE;
			break;
		case TCL_DB_UNKNOWN:
			if (type != DB_UNKNOWN) {
				Tcl_SetResult(interp,
				    "Too many DB types specified", TCL_STATIC);
				result = TCL_ERROR;
				goto error;
			}
			break;
		case TCL_DB_CREATE:
			open_flags |= DB_CREATE;
			break;
		case TCL_DB_DIRTY:
			open_flags |= DB_DIRTY_READ;
			break;
		case TCL_DB_EXCL:
			open_flags |= DB_EXCL;
			break;
		case TCL_DB_RDONLY:
			open_flags |= DB_RDONLY;
			break;
		case TCL_DB_TRUNCATE:
			open_flags |= DB_TRUNCATE;
			break;
		case TCL_DB_TEST:
			(*dbp)->set_h_hash(*dbp, __ham_test);
			break;
		case TCL_DB_MODE:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-mode mode?");
				result = TCL_ERROR;
				break;
			}
			/*
			 * Don't need to check result here because
			 * if TCL_ERROR, the error message is already
			 * set up, and we'll bail out below.  If ok,
			 * the mode is set and we go on.
			 */
			result = Tcl_GetIntFromObj(interp, objv[i++], &mode);
			break;
		case TCL_DB_NOMMAP:
			open_flags |= DB_NOMMAP;
			break;
		case TCL_DB_DUP:
			set_flag |= DB_DUP;
			break;
		case TCL_DB_DUPSORT:
			set_flag |= DB_DUPSORT;
			break;
		case TCL_DB_RECNUM:
			set_flag |= DB_RECNUM;
			break;
		case TCL_DB_RENUMBER:
			set_flag |= DB_RENUMBER;
			break;
		case TCL_DB_REVSPLIT:
			set_flag |= DB_REVSPLITOFF;
			break;
		case TCL_DB_SNAPSHOT:
			set_flag |= DB_SNAPSHOT;
			break;
		case TCL_DB_FFACTOR:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-ffactor density");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, objv[i++], &uintarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*dbp)->set_h_ffactor(*dbp, uintarg);
				result = _ReturnSetup(interp, ret,
				    "set_h_ffactor");
			}
			break;
		case TCL_DB_NELEM:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-nelem nelem");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, objv[i++], &uintarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*dbp)->set_h_nelem(*dbp, uintarg);
				result = _ReturnSetup(interp, ret,
				    "set_h_nelem");
			}
			break;
		case TCL_DB_LORDER:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-lorder 1234|4321");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, objv[i++], &uintarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*dbp)->set_lorder(*dbp, uintarg);
				result = _ReturnSetup(interp, ret,
				    "set_lorder");
			}
			break;
		case TCL_DB_BTCOMPARE:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-btcompare compareproc");
				result = TCL_ERROR;
				break;
			}

			/*
			 * Store the object containing the procedure name.
			 * We don't need to crack it out now--we'll want
			 * to bundle it up to pass into Tcl_EvalObjv anyway.
			 * Tcl's object refcounting will--I hope--take care
			 * of the memory management here.
			 */
			ip->i_btcompare = objv[i++];
			Tcl_IncrRefCount(ip->i_btcompare);
			_debug_check();
			ret = (*dbp)->set_bt_compare(*dbp, tcl_bt_compare);
			result = _ReturnSetup(interp, ret, "set_bt_compare");
			break;
		case TCL_DB_DUPCOMPARE:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-dupcompare compareproc");
				result = TCL_ERROR;
				break;
			}

			/*
			 * Store the object containing the procedure name.
			 * See TCL_DB_BTCOMPARE.
			 */
			ip->i_dupcompare = objv[i++];
			Tcl_IncrRefCount(ip->i_dupcompare);
			_debug_check();
			ret = (*dbp)->set_dup_compare(*dbp, tcl_dup_compare);
			result = _ReturnSetup(interp, ret, "set_dup_compare");
			break;
		case TCL_DB_DELIM:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-delim delim");
				result = TCL_ERROR;
				break;
			}
			result = Tcl_GetIntFromObj(interp, objv[i++], &intarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*dbp)->set_re_delim(*dbp, intarg);
				result = _ReturnSetup(interp, ret,
				    "set_re_delim");
			}
			break;
		case TCL_DB_HASHPROC:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-hashproc hashproc");
				result = TCL_ERROR;
				break;
			}

			/*
			 * Store the object containing the procedure name.
			 * See TCL_DB_BTCOMPARE.
			 */
			ip->i_hashproc = objv[i++];
			Tcl_IncrRefCount(ip->i_hashproc);
			_debug_check();
			ret = (*dbp)->set_h_hash(*dbp, tcl_h_hash);
			result = _ReturnSetup(interp, ret, "set_h_hash");
			break;
		case TCL_DB_LEN:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-len length");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, objv[i++], &uintarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*dbp)->set_re_len(*dbp, uintarg);
				result = _ReturnSetup(interp, ret,
				    "set_re_len");
			}
			break;
		case TCL_DB_PAD:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-pad pad");
				result = TCL_ERROR;
				break;
			}
			result = Tcl_GetIntFromObj(interp, objv[i++], &intarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*dbp)->set_re_pad(*dbp, intarg);
				result = _ReturnSetup(interp, ret,
				    "set_re_pad");
			}
			break;
		case TCL_DB_SOURCE:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-source file");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			_debug_check();
			ret = (*dbp)->set_re_source(*dbp, arg);
			result = _ReturnSetup(interp, ret, "set_re_source");
			break;
		case TCL_DB_EXTENT:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-extent size");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, objv[i++], &uintarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*dbp)->set_q_extentsize(*dbp, uintarg);
				result = _ReturnSetup(interp, ret,
				    "set_q_extentsize");
			}
			break;
		case TCL_DB_MINKEY:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-minkey minkey");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, objv[i++], &uintarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*dbp)->set_bt_minkey(*dbp, uintarg);
				result = _ReturnSetup(interp, ret,
				    "set_bt_minkey");
			}
			break;
		case TCL_DB_CACHESIZE:
			result = Tcl_ListObjGetElements(interp, objv[i++],
			    &myobjc, &myobjv);
			if (result != TCL_OK)
				break;
			if (myobjc != 3) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-cachesize {gbytes bytes ncaches}?");
				result = TCL_ERROR;
				break;
			}
			result = _GetUInt32(interp, myobjv[0], &gbytes);
			if (result != TCL_OK)
				break;
			result = _GetUInt32(interp, myobjv[1], &bytes);
			if (result != TCL_OK)
				break;
			result = _GetUInt32(interp, myobjv[2], &ncaches);
			if (result != TCL_OK)
				break;
			_debug_check();
			ret = (*dbp)->set_cachesize(*dbp, gbytes, bytes,
			    ncaches);
			result = _ReturnSetup(interp, ret,
			    "set_cachesize");
			break;
		case TCL_DB_PAGESIZE:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "?-pagesize size?");
				result = TCL_ERROR;
				break;
			}
			result = Tcl_GetIntFromObj(interp, objv[i++], &intarg);
			if (result == TCL_OK) {
				_debug_check();
				ret = (*dbp)->set_pagesize(*dbp,
				    (size_t)intarg);
				result = _ReturnSetup(interp, ret,
				    "set pagesize");
			}
			break;
		case TCL_DB_ERRFILE:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-errfile file");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			/*
			 * If the user already set one, close it.
			 */
			if (errip->i_err != NULL)
				fclose(errip->i_err);
			errip->i_err = fopen(arg, "a");
			if (errip->i_err != NULL) {
				_debug_check();
				(*dbp)->set_errfile(*dbp, errip->i_err);
				set_err = 1;
			}
			break;
		case TCL_DB_ERRPFX:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-errpfx prefix");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			/*
			 * If the user already set one, free it.
			 */
			if (errip->i_errpfx != NULL)
				__os_freestr(NULL, errip->i_errpfx);
			if ((ret = __os_strdup((*dbp)->dbenv,
			    arg, &errip->i_errpfx)) != 0) {
				result = _ReturnSetup(interp, ret,
				    "__os_strdup");
				break;
			}
			if (errip->i_errpfx != NULL) {
				_debug_check();
				(*dbp)->set_errpfx(*dbp, errip->i_errpfx);
				set_pfx = 1;
			}
			break;
		case TCL_DB_ENDARG:
			endarg = 1;
			break;
		} /* switch */

		/*
		 * If, at any time, parsing the args we get an error,
		 * bail out and return.
		 */
		if (result != TCL_OK)
			goto error;
		if (endarg)
			break;
	}
	if (result != TCL_OK)
		goto error;

	/*
	 * Any args we have left, (better be 0, 1 or 2 left) are
	 * file names.  If we have 0, then an in-memory db.  If
	 * there is 1, a db name, if 2 a db and subdb name.
	 */
	if (i != objc) {
		/*
		 * Dbs must be NULL terminated file names, but subdbs can
		 * be anything.  Use Strings for the db name and byte
		 * arrays for the subdb.
		 */
		db = Tcl_GetStringFromObj(objv[i++], NULL);
		if (i != objc) {
			subdbtmp =
			    Tcl_GetByteArrayFromObj(objv[i++], &subdblen);
			if ((ret = __os_malloc(envp,
			   subdblen + 1, &subdb)) != 0) {
				Tcl_SetResult(interp, db_strerror(ret),
				    TCL_STATIC);
				return (0);
			}
			memcpy(subdb, subdbtmp, subdblen);
			subdb[subdblen] = '\0';
		}
	}
	if (set_flag) {
		ret = (*dbp)->set_flags(*dbp, set_flag);
		result = _ReturnSetup(interp, ret, "set_flags");
		if (result == TCL_ERROR)
			goto error;
		/*
		 * If we are successful, clear the result so that the
		 * return from set_flags isn't part of the result.
		 */
		Tcl_ResetResult(interp);
	}

	/*
	 * When we get here, we have already parsed all of our args and made
	 * all our calls to set up the database.  Everything is okay so far,
	 * no errors, if we get here.
	 */
	_debug_check();

	/* Open the database. */
	ret = (*dbp)->open(*dbp, db, subdb, type, open_flags, mode);
	result = _ReturnSetup(interp, ret, "db open");

error:
	if (subdb)
		__os_free(envp, subdb, subdblen + 1);
	if (result == TCL_ERROR) {
		/*
		 * If we opened and set up the error file in the environment
		 * on this open, but we failed for some other reason, clean
		 * up and close the file.
		 *
		 * XXX when err stuff isn't tied to env, change to use ip,
		 * instead of envip.  Also, set_err is irrelevant when that
		 * happens.  It will just read:
		 * if (ip->i_err)
		 *	fclose(ip->i_err);
		 */
		if (set_err && errip && errip->i_err != NULL) {
			fclose(errip->i_err);
			errip->i_err = NULL;
		}
		if (set_pfx && errip && errip->i_errpfx != NULL) {
			__os_freestr(envp, errip->i_errpfx);
			errip->i_errpfx = NULL;
		}
		(void)(*dbp)->close(*dbp, 0);
		*dbp = NULL;
	}
	return (result);
}

/*
 * bdb_DbRemove --
 *	Implements the DB->remove command.
 */
static int
bdb_DbRemove(interp, objc, objv)
	Tcl_Interp *interp;		/* Interpreter */
	int objc;			/* How many arguments? */
	Tcl_Obj *CONST objv[];		/* The argument objects */
{
	static char *bdbrem[] = {
		"-env",	"--",	NULL
	};
	enum bdbrem {
		TCL_DBREM_ENV,
		TCL_DBREM_ENDARG
	};
	DB_ENV *envp;
	DB *dbp;
	int endarg, i, optindex, result, ret, subdblen;
	u_char *subdbtmp;
	char *arg, *db, *subdb;

	envp = NULL;
	dbp = NULL;
	result = TCL_OK;
	subdbtmp = NULL;
	db = subdb = NULL;
	endarg = 0;

	if (objc < 2) {
		Tcl_WrongNumArgs(interp, 2, objv, "?args? filename ?database?");
		return (TCL_ERROR);
	}

	/*
	 * We must first parse for the environment flag, since that
	 * is needed for db_create.  Then create the db handle.
	 */
	i = 2;
	while (i < objc) {
		if (Tcl_GetIndexFromObj(interp, objv[i], bdbrem,
		    "option", TCL_EXACT, &optindex) != TCL_OK) {
			arg = Tcl_GetStringFromObj(objv[i], NULL);
			if (arg[0] == '-') {
				result = IS_HELP(objv[i]);
				goto error;
			} else
				Tcl_ResetResult(interp);
			break;
		}
		i++;
		switch ((enum bdbrem)optindex) {
		case TCL_DBREM_ENV:
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			envp = NAME_TO_ENV(arg);
			if (envp == NULL) {
				Tcl_SetResult(interp,
				    "db remove: illegal environment",
				    TCL_STATIC);
				return (TCL_ERROR);
			}
			break;
		case TCL_DBREM_ENDARG:
			endarg = 1;
			break;
		}
		/*
		 * If, at any time, parsing the args we get an error,
		 * bail out and return.
		 */
		if (result != TCL_OK)
			goto error;
		if (endarg)
			break;
	}
	if (result != TCL_OK)
		goto error;
	/*
	 * Any args we have left, (better be 1 or 2 left) are
	 * file names. If there is 1, a db name, if 2 a db and subdb name.
	 */
	if ((i != (objc - 1)) || (i != (objc - 2))) {
		/*
		 * Dbs must be NULL terminated file names, but subdbs can
		 * be anything.  Use Strings for the db name and byte
		 * arrays for the subdb.
		 */
		db = Tcl_GetStringFromObj(objv[i++], NULL);
		if (i != objc) {
			subdbtmp =
			    Tcl_GetByteArrayFromObj(objv[i++], &subdblen);
			if ((ret = __os_malloc(envp, subdblen + 1,
			    &subdb)) != 0) { Tcl_SetResult(interp,
				    db_strerror(ret), TCL_STATIC);
				return (0);
			}
			memcpy(subdb, subdbtmp, subdblen);
			subdb[subdblen] = '\0';
		}
	} else {
		Tcl_WrongNumArgs(interp, 2, objv, "?args? filename ?database?");
		result = TCL_ERROR;
		goto error;
	}
	ret = db_create(&dbp, envp, 0);
	if (ret) {
		result = _ReturnSetup(interp, ret, "db_create");
		goto error;
	}
	/*
	 * No matter what, we NULL out dbp after this call.
	 */
	ret = dbp->remove(dbp, db, subdb, 0);
	result = _ReturnSetup(interp, ret, "db remove");
	dbp = NULL;
error:
	if (subdb)
		__os_free(envp, subdb, subdblen + 1);
	if (result == TCL_ERROR && dbp)
		(void)dbp->close(dbp, 0);
	return (result);
}

/*
 * bdb_DbRename --
 *	Implements the DB->rename command.
 */
static int
bdb_DbRename(interp, objc, objv)
	Tcl_Interp *interp;		/* Interpreter */
	int objc;			/* How many arguments? */
	Tcl_Obj *CONST objv[];		/* The argument objects */
{
	static char *bdbmv[] = {
		"-env",	"--",	NULL
	};
	enum bdbmv {
		TCL_DBMV_ENV,
		TCL_DBMV_ENDARG
	};
	DB_ENV *envp;
	DB *dbp;
	int endarg, i, newlen, optindex, result, ret, subdblen;
	u_char *subdbtmp;
	char *arg, *db, *newname, *subdb;

	envp = NULL;
	dbp = NULL;
	result = TCL_OK;
	subdbtmp = NULL;
	db = newname = subdb = NULL;
	endarg = 0;

	if (objc < 2) {
		Tcl_WrongNumArgs(interp,
			3, objv, "?args? filename ?database? ?newname?");
		return (TCL_ERROR);
	}

	/*
	 * We must first parse for the environment flag, since that
	 * is needed for db_create.  Then create the db handle.
	 */
	i = 2;
	while (i < objc) {
		if (Tcl_GetIndexFromObj(interp, objv[i], bdbmv,
		    "option", TCL_EXACT, &optindex) != TCL_OK) {
			arg = Tcl_GetStringFromObj(objv[i], NULL);
			if (arg[0] == '-') {
				result = IS_HELP(objv[i]);
				goto error;
			} else
				Tcl_ResetResult(interp);
			break;
		}
		i++;
		switch ((enum bdbmv)optindex) {
		case TCL_DBMV_ENV:
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			envp = NAME_TO_ENV(arg);
			if (envp == NULL) {
				Tcl_SetResult(interp,
				    "db rename: illegal environment",
				    TCL_STATIC);
				return (TCL_ERROR);
			}
			break;
		case TCL_DBMV_ENDARG:
			endarg = 1;
			break;
		}
		/*
		 * If, at any time, parsing the args we get an error,
		 * bail out and return.
		 */
		if (result != TCL_OK)
			goto error;
		if (endarg)
			break;
	}
	if (result != TCL_OK)
		goto error;
	/*
	 * Any args we have left, (better be 2 or 3 left) are
	 * file names. If there is 2, a file name, if 3 a file and db name.
	 */
	if ((i != (objc - 2)) || (i != (objc - 3))) {
		/*
		 * Dbs must be NULL terminated file names, but subdbs can
		 * be anything.  Use Strings for the db name and byte
		 * arrays for the subdb.
		 */
		db = Tcl_GetStringFromObj(objv[i++], NULL);
		if (i == objc - 2) {
			subdbtmp =
			    Tcl_GetByteArrayFromObj(objv[i++], &subdblen);
			if ((ret = __os_malloc(envp, subdblen + 1,
			    &subdb)) != 0) {
				Tcl_SetResult(interp,
				    db_strerror(ret), TCL_STATIC);
				return (0);
			}
			memcpy(subdb, subdbtmp, subdblen);
			subdb[subdblen] = '\0';
		}
		subdbtmp =
		    Tcl_GetByteArrayFromObj(objv[i++], &newlen);
		if ((ret = __os_malloc(envp, newlen + 1,
		    &newname)) != 0) {
			Tcl_SetResult(interp,
			    db_strerror(ret), TCL_STATIC);
			return (0);
		}
		memcpy(newname, subdbtmp, newlen);
		newname[newlen] = '\0';
	} else {
		Tcl_WrongNumArgs(interp, 3, objv, "?args? filename ?database? ?newname?");
		result = TCL_ERROR;
		goto error;
	}
	ret = db_create(&dbp, envp, 0);
	if (ret) {
		result = _ReturnSetup(interp, ret, "db_create");
		goto error;
	}
	/*
	 * No matter what, we NULL out dbp after this call.
	 */
	ret = dbp->rename(dbp, db, subdb, newname, 0);
	result = _ReturnSetup(interp, ret, "db rename");
	dbp = NULL;
error:
	if (subdb)
		__os_free(envp, subdb, subdblen + 1);
	if (newname)
		__os_free(envp, newname, newlen + 1);
	if (result == TCL_ERROR && dbp)
		(void)dbp->close(dbp, 0);
	return (result);
}

/*
 * bdb_DbVerify --
 *	Implements the DB->verify command.
 */
static int
bdb_DbVerify(interp, objc, objv)
	Tcl_Interp *interp;		/* Interpreter */
	int objc;			/* How many arguments? */
	Tcl_Obj *CONST objv[];		/* The argument objects */
{
	static char *bdbverify[] = {
		"-env",	"-errfile", "-errpfx", "--", NULL
	};
	enum bdbvrfy {
		TCL_DBVRFY_ENV,
		TCL_DBVRFY_ERRFILE,
		TCL_DBVRFY_ERRPFX,
		TCL_DBVRFY_ENDARG
	};
	DB_ENV *envp;
	DB *dbp;
	FILE *errf;
	u_int32_t flags;
	int endarg, i, optindex, result, ret;
	char *arg, *db, *errpfx;

	envp = NULL;
	dbp = NULL;
	result = TCL_OK;
	db = errpfx = NULL;
	errf = NULL;
	flags = endarg = 0;

	if (objc < 2) {
		Tcl_WrongNumArgs(interp, 2, objv, "?args? filename");
		return (TCL_ERROR);
	}

	/*
	 * We must first parse for the environment flag, since that
	 * is needed for db_create.  Then create the db handle.
	 */
	i = 2;
	while (i < objc) {
		if (Tcl_GetIndexFromObj(interp, objv[i], bdbverify,
		    "option", TCL_EXACT, &optindex) != TCL_OK) {
			arg = Tcl_GetStringFromObj(objv[i], NULL);
			if (arg[0] == '-') {
				result = IS_HELP(objv[i]);
				goto error;
			} else
				Tcl_ResetResult(interp);
			break;
		}
		i++;
		switch ((enum bdbvrfy)optindex) {
		case TCL_DBVRFY_ENV:
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			envp = NAME_TO_ENV(arg);
			if (envp == NULL) {
				Tcl_SetResult(interp,
				    "db verify: illegal environment",
				    TCL_STATIC);
				result = TCL_ERROR;
				break;
			}
			break;
		case TCL_DBVRFY_ERRFILE:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-errfile file");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			/*
			 * If the user already set one, close it.
			 */
			if (errf != NULL)
				fclose(errf);
			errf = fopen(arg, "a");
			break;
		case TCL_DBVRFY_ERRPFX:
			if (i >= objc) {
				Tcl_WrongNumArgs(interp, 2, objv,
				    "-errpfx prefix");
				result = TCL_ERROR;
				break;
			}
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			/*
			 * If the user already set one, free it.
			 */
			if (errpfx != NULL)
				__os_freestr(envp, errpfx);
			if ((ret = __os_strdup(NULL, arg, &errpfx)) != 0) {
				result = _ReturnSetup(interp, ret,
				    "__os_strdup");
				break;
			}
			break;
		case TCL_DBVRFY_ENDARG:
			endarg = 1;
			break;
		}
		/*
		 * If, at any time, parsing the args we get an error,
		 * bail out and return.
		 */
		if (result != TCL_OK)
			goto error;
		if (endarg)
			break;
	}
	if (result != TCL_OK)
		goto error;
	/*
	 * The remaining arg is the db filename.
	 */
	if (i == (objc - 1))
		db = Tcl_GetStringFromObj(objv[i++], NULL);
	else {
		Tcl_WrongNumArgs(interp, 2, objv, "?args? filename");
		result = TCL_ERROR;
		goto error;
	}
	ret = db_create(&dbp, envp, 0);
	if (ret) {
		result = _ReturnSetup(interp, ret, "db_create");
		goto error;
	}

	if (errf != NULL)
		dbp->set_errfile(dbp, errf);
	if (errpfx != NULL)
		dbp->set_errpfx(dbp, errpfx);

	ret = dbp->verify(dbp, db, NULL, NULL, flags);
	result = _ReturnSetup(interp, ret, "db verify");
error:
	if (errf != NULL)
		fclose(errf);
	if (errpfx != NULL)
		__os_freestr(envp, errpfx);
	if (dbp)
		(void)dbp->close(dbp, 0);
	return (result);
}

/*
 * bdb_Version --
 *	Implements the version command.
 */
static int
bdb_Version(interp, objc, objv)
	Tcl_Interp *interp;		/* Interpreter */
	int objc;			/* How many arguments? */
	Tcl_Obj *CONST objv[];		/* The argument objects */
{
	static char *bdbver[] = {
		"-string", NULL
	};
	enum bdbver {
		TCL_VERSTRING
	};
	int i, optindex, maj, min, patch, result, string, verobjc;
	char *arg, *v;
	Tcl_Obj *res, *verobjv[3];

	result = TCL_OK;
	string = 0;

	if (objc < 2) {
		Tcl_WrongNumArgs(interp, 2, objv, "?args?");
		return (TCL_ERROR);
	}

	/*
	 * We must first parse for the environment flag, since that
	 * is needed for db_create.  Then create the db handle.
	 */
	i = 2;
	while (i < objc) {
		if (Tcl_GetIndexFromObj(interp, objv[i], bdbver,
		    "option", TCL_EXACT, &optindex) != TCL_OK) {
			arg = Tcl_GetStringFromObj(objv[i], NULL);
			if (arg[0] == '-') {
				result = IS_HELP(objv[i]);
				goto error;
			} else
				Tcl_ResetResult(interp);
			break;
		}
		i++;
		switch ((enum bdbver)optindex) {
		case TCL_VERSTRING:
			string = 1;
			break;
		}
		/*
		 * If, at any time, parsing the args we get an error,
		 * bail out and return.
		 */
		if (result != TCL_OK)
			goto error;
	}
	if (result != TCL_OK)
		goto error;

	v = db_version(&maj, &min, &patch);
	if (string)
		res = Tcl_NewStringObj(v, strlen(v));
	else {
		verobjc = 3;
		verobjv[0] = Tcl_NewIntObj(maj);
		verobjv[1] = Tcl_NewIntObj(min);
		verobjv[2] = Tcl_NewIntObj(patch);
		res = Tcl_NewListObj(verobjc, verobjv);
	}
	Tcl_SetObjResult(interp, res);
error:
	return (result);
}

/*
 * bdb_Handles --
 *	Implements the handles command.
 */
static int
bdb_Handles(interp, objc, objv)
	Tcl_Interp *interp;		/* Interpreter */
	int objc;			/* How many arguments? */
	Tcl_Obj *CONST objv[];		/* The argument objects */
{
	DBTCL_INFO *p;
	Tcl_Obj *res, *handle;

	/*
	 * No args.  Error if we have some
	 */
	if (objc != 2) {
		Tcl_WrongNumArgs(interp, 2, objv, "");
		return (TCL_ERROR);
	}
	res = Tcl_NewListObj(0, NULL);

	for (p = LIST_FIRST(&__db_infohead); p != NULL;
	    p = LIST_NEXT(p, entries)) {
		handle = Tcl_NewStringObj(p->i_name, strlen(p->i_name));
		if (Tcl_ListObjAppendElement(interp, res, handle) != TCL_OK)
			return (TCL_ERROR);
	}
	Tcl_SetObjResult(interp, res);
	return (TCL_OK);
}

/*
 * bdb_DbUpgrade --
 *	Implements the DB->upgrade command.
 */
static int
bdb_DbUpgrade(interp, objc, objv)
	Tcl_Interp *interp;		/* Interpreter */
	int objc;			/* How many arguments? */
	Tcl_Obj *CONST objv[];		/* The argument objects */
{
	static char *bdbupg[] = {
		"-dupsort", "-env", "--", NULL
	};
	enum bdbupg {
		TCL_DBUPG_DUPSORT,
		TCL_DBUPG_ENV,
		TCL_DBUPG_ENDARG
	};
	DB_ENV *envp;
	DB *dbp;
	u_int32_t flags;
	int endarg, i, optindex, result, ret;
	char *arg, *db;

	envp = NULL;
	dbp = NULL;
	result = TCL_OK;
	db = NULL;
	flags = endarg = 0;

	if (objc < 2) {
		Tcl_WrongNumArgs(interp, 2, objv, "?args? filename");
		return (TCL_ERROR);
	}

	i = 2;
	while (i < objc) {
		if (Tcl_GetIndexFromObj(interp, objv[i], bdbupg,
		    "option", TCL_EXACT, &optindex) != TCL_OK) {
			arg = Tcl_GetStringFromObj(objv[i], NULL);
			if (arg[0] == '-') {
				result = IS_HELP(objv[i]);
				goto error;
			} else
				Tcl_ResetResult(interp);
			break;
		}
		i++;
		switch ((enum bdbupg)optindex) {
		case TCL_DBUPG_DUPSORT:
			flags |= DB_DUPSORT;
			break;
		case TCL_DBUPG_ENV:
			arg = Tcl_GetStringFromObj(objv[i++], NULL);
			envp = NAME_TO_ENV(arg);
			if (envp == NULL) {
				Tcl_SetResult(interp,
				    "db upgrade: illegal environment",
				    TCL_STATIC);
				return (TCL_ERROR);
			}
			break;
		case TCL_DBUPG_ENDARG:
			endarg = 1;
			break;
		}
		/*
		 * If, at any time, parsing the args we get an error,
		 * bail out and return.
		 */
		if (result != TCL_OK)
			goto error;
		if (endarg)
			break;
	}
	if (result != TCL_OK)
		goto error;
	/*
	 * The remaining arg is the db filename.
	 */
	if (i == (objc - 1))
		db = Tcl_GetStringFromObj(objv[i++], NULL);
	else {
		Tcl_WrongNumArgs(interp, 2, objv, "?args? filename");
		result = TCL_ERROR;
		goto error;
	}
	ret = db_create(&dbp, envp, 0);
	if (ret) {
		result = _ReturnSetup(interp, ret, "db_create");
		goto error;
	}

	ret = dbp->upgrade(dbp, db, flags);
	result = _ReturnSetup(interp, ret, "db upgrade");
error:
	if (dbp)
		(void)dbp->close(dbp, 0);
	return (result);
}

/*
 * tcl_bt_compare and tcl_dup_compare --
 *	These two are basically identical internally, so may as well
 * share code.  The only differences are the name used in error
 * reporting and the Tcl_Obj representing their respective procs.
 */
static int
tcl_bt_compare(dbp, dbta, dbtb)
	DB *dbp;
	const DBT *dbta, *dbtb;
{
	return (tcl_compare_callback(dbp, dbta, dbtb,
	    ((DBTCL_INFO *)dbp->cj_internal)->i_btcompare, "bt_compare"));
}

static int
tcl_dup_compare(dbp, dbta, dbtb)
	DB *dbp;
	const DBT *dbta, *dbtb;
{
	return (tcl_compare_callback(dbp, dbta, dbtb,
	    ((DBTCL_INFO *)dbp->cj_internal)->i_dupcompare, "dup_compare"));
}

/*
 * tcl_compare_callback --
 *	Tcl callback for set_bt_compare and set_dup_compare. What this
 * function does is stuff the data fields of the two DBTs into Tcl ByteArray
 * objects, then call the procedure stored in ip->i_btcompare on the two
 * objects.  Then we return that procedure's result as the comparison.
 */
static int
tcl_compare_callback(dbp, dbta, dbtb, procobj, errname)
	DB *dbp;
	const DBT *dbta, *dbtb;
	Tcl_Obj *procobj;
	char *errname;
{
	DBTCL_INFO *ip;
	Tcl_Interp *interp;
	Tcl_Obj *a, *b, *resobj, *objv[3];
	int result, cmp;

	ip = (DBTCL_INFO *)dbp->cj_internal;
	interp = ip->i_interp;
	objv[0] = procobj;

	/*
	 * Create two ByteArray objects, with the two data we've been passed.
	 * This will involve a copy, which is unpleasantly slow, but there's
	 * little we can do to avoid this (I think).
	 */
	a = Tcl_NewByteArrayObj(dbta->data, dbta->size);
	Tcl_IncrRefCount(a);
	b = Tcl_NewByteArrayObj(dbtb->data, dbtb->size);
	Tcl_IncrRefCount(b);

	objv[1] = a;
	objv[2] = b;

	result = Tcl_EvalObjv(interp, 3, objv, 0);
	if (result != TCL_OK) {
		/*
		 * XXX
		 * If this or the next Tcl call fails, we're doomed.
		 * There's no way to return an error from comparison functions,
		 * no way to determine what the correct sort order is, and
		 * so no way to avoid corrupting the database if we proceed.
		 * We could play some games stashing return values on the
		 * DB handle, but it's not worth the trouble--no one with
		 * any sense is going to be using this other than for testing,
		 * and failure typically means that the bt_compare proc
		 * had a syntax error in it or something similarly dumb.
		 *
		 * So, drop core.  If we're not running with diagnostic
		 * mode, panic--and always return a negative number. :-)
		 */
panic:		__db_err(dbp->dbenv, "Tcl %s callback failed", errname);
		DB_ASSERT(0);
		return (__db_panic(dbp->dbenv, DB_RUNRECOVERY));
	}

	resobj = Tcl_GetObjResult(interp);
	result = Tcl_GetIntFromObj(interp, resobj, &cmp);
	if (result != TCL_OK)
		goto panic;

	Tcl_DecrRefCount(a);
	Tcl_DecrRefCount(b);
	return (cmp);
}

/*
 * tcl_h_hash --
 *	Tcl callback for the hashing function.  See tcl_compare_callback--
 * this works much the same way, only we're given a buffer and a length
 * instead of two DBTs.
 */
static u_int32_t
tcl_h_hash(dbp, buf, len)
	DB *dbp;
	const void *buf;
	u_int32_t len;
{
	DBTCL_INFO *ip;
	Tcl_Interp *interp;
	Tcl_Obj *objv[2];
	int result, hval;

	ip = (DBTCL_INFO *)dbp->cj_internal;
	interp = ip->i_interp;
	objv[0] = ip->i_hashproc;

	/*
	 * Create a ByteArray for the buffer.
	 */
	objv[1] = Tcl_NewByteArrayObj((void *)buf, len);
	Tcl_IncrRefCount(objv[1]);
	result = Tcl_EvalObjv(interp, 2, objv, 0);
	if (result != TCL_OK) {
		/*
		 * XXX
		 * We drop core on error.  See the comment in
		 * tcl_compare_callback.
		 */
panic:		__db_err(dbp->dbenv, "Tcl h_hash callback failed");
		DB_ASSERT(0);
		return (__db_panic(dbp->dbenv, DB_RUNRECOVERY));
	}

	result = Tcl_GetIntFromObj(interp, Tcl_GetObjResult(interp), &hval);
	if (result != TCL_OK)
		goto panic;

	Tcl_DecrRefCount(objv[1]);
	return (hval);
}

/*
 * tcl_rep_send --
 *	Replication send callback.
 */
static int
tcl_rep_send(dbenv, rec, control, eid, flags)
	DB_ENV *dbenv;
	const DBT *rec, *control;
	int eid;
	u_int32_t flags;
{
	DBTCL_INFO *ip;
	Tcl_Interp *interp;
	Tcl_Obj *eid_o, *rec_o, *control_o, *resobj, *objv[5];
	int result, ret;

	COMPQUIET(flags, 0);

	ip = (DBTCL_INFO *)dbenv->app_private;
	interp = ip->i_interp;
	objv[0] = ip->i_rep_send;

	rec_o = Tcl_NewByteArrayObj(rec->data, rec->size);
	Tcl_IncrRefCount(rec_o);

	control_o = Tcl_NewByteArrayObj(control->data, control->size);
	Tcl_IncrRefCount(control_o);

	eid_o = Tcl_NewIntObj(eid);
	Tcl_IncrRefCount(eid_o);

	/* XXX ordering */
	objv[2] = rec_o;
	objv[1] = control_o;
	objv[3] = ip->i_rep_eid;	/* From ID */
	objv[4] = eid_o;		/* To ID */

	result = Tcl_EvalObjv(interp, 5, objv, 0);
	if (result != TCL_OK) {
		/*
		 * XXX
		 * This probably isn't the right error behavior, but
		 * this error should only happen if the Tcl callback is
		 * somehow invalid, which is a fatal scripting bug.
		 */
err:		__db_err(dbenv, "Tcl rep_send failure");
		return (EINVAL);
	}

	resobj = Tcl_GetObjResult(interp);
	result = Tcl_GetIntFromObj(interp, resobj, &ret);
	if (result != TCL_OK)
		goto err;

	Tcl_DecrRefCount(rec_o);
	Tcl_DecrRefCount(control_o);
	Tcl_DecrRefCount(eid_o);

	return (ret);
}
