// DO NOT EDIT: automatically built by dist/s_java.

package com.sleepycat.db;

class DbConstants
{
    static final int DB_AFTER = 1;
    static final int DB_AGGRESSIVE = 0x000001;
    static final int DB_APPEND = 2;
    static final int DB_ARCH_ABS = 0x001;
    static final int DB_ARCH_DATA = 0x002;
    static final int DB_ARCH_LOG = 0x004;
    static final int DB_BEFORE = 3;
    static final int DB_CACHED_COUNTS = 4;
    static final int DB_CDB_ALLDB = 0x000400;
    static final int DB_CHECKPOINT = 5;
    static final int DB_CLIENT = 0x000400;
    static final int DB_CONSUME = 7;
    static final int DB_CONSUME_WAIT = 8;
    static final int DB_CREATE = 0x000001;
    static final int DB_CURLSN = 9;
    static final int DB_CURRENT = 10;
    static final int DB_CXX_NO_EXCEPTIONS = 0x000002;
    static final int DB_DBT_MALLOC = 0x004;
    static final int DB_DBT_PARTIAL = 0x008;
    static final int DB_DBT_REALLOC = 0x010;
    static final int DB_DBT_USERMEM = 0x020;
    static final int DB_DIRTY_READ = 0x01000000;
    static final int DB_DUP = 0x000001;
    static final int DB_DUPSORT = 0x000002;
    static final int DB_EID_BROADCAST = -1;
    static final int DB_EID_INVALID = -2;
    static final int DB_EXCL = 0x000400;
    static final int DB_FAST_STAT = 11;
    static final int DB_FIRST = 12;
    static final int DB_FLUSH = 0x02000000;
    static final int DB_FORCE = 0x000004;
    static final int DB_GET_BOTH = 13;
    static final int DB_GET_BOTH_RANGE = 15;
    static final int DB_GET_RECNO = 16;
    static final int DB_INIT_CDB = 0x000400;
    static final int DB_INIT_LOCK = 0x000800;
    static final int DB_INIT_LOG = 0x001000;
    static final int DB_INIT_MPOOL = 0x002000;
    static final int DB_INIT_TXN = 0x004000;
    static final int DB_JOINENV = 0x008000;
    static final int DB_JOIN_ITEM = 17;
    static final int DB_JOIN_NOSORT = 0x000001;
    static final int DB_KEYFIRST = 18;
    static final int DB_KEYLAST = 19;
    static final int DB_LAST = 20;
    static final int DB_LOCKDOWN = 0x010000;
    static final int DB_LOCK_DEFAULT = 1;
    static final int DB_LOCK_EXPIRE = 2;
    static final int DB_LOCK_GET = 1;
    static final int DB_LOCK_GET_TIMEOUT = 2;
    static final int DB_LOCK_IREAD = 5;
    static final int DB_LOCK_IWR = 6;
    static final int DB_LOCK_IWRITE = 4;
    static final int DB_LOCK_MAXLOCKS = 3;
    static final int DB_LOCK_MINLOCKS = 4;
    static final int DB_LOCK_MINWRITE = 5;
    static final int DB_LOCK_NOWAIT = 0x002;
    static final int DB_LOCK_OLDEST = 6;
    static final int DB_LOCK_PUT = 4;
    static final int DB_LOCK_PUT_ALL = 5;
    static final int DB_LOCK_PUT_OBJ = 6;
    static final int DB_LOCK_RANDOM = 7;
    static final int DB_LOCK_READ = 1;
    static final int DB_LOCK_TIMEOUT = 8;
    static final int DB_LOCK_WRITE = 2;
    static final int DB_LOCK_YOUNGEST = 8;
    static final int DB_MULTIPLE = 0x04000000;
    static final int DB_MULTIPLE_KEY = 0x08000000;
    static final int DB_NEXT = 21;
    static final int DB_NEXT_DUP = 22;
    static final int DB_NEXT_NODUP = 23;
    static final int DB_NODUPDATA = 24;
    static final int DB_NOLOCKING = 0x001000;
    static final int DB_NOMMAP = 0x000008;
    static final int DB_NOORDERCHK = 0x000002;
    static final int DB_NOOVERWRITE = 25;
    static final int DB_NOPANIC = 0x002000;
    static final int DB_NOSYNC = 26;
    static final int DB_ODDFILESIZE = 0x000400;
    static final int DB_ORDERCHKONLY = 0x000004;
    static final int DB_PANIC_ENVIRONMENT = 0x004000;
    static final int DB_POSITION = 27;
    static final int DB_PREV = 29;
    static final int DB_PREV_NODUP = 30;
    static final int DB_PRIVATE = 0x020000;
    static final int DB_RDONLY = 0x000010;
    static final int DB_RECNUM = 0x000004;
    static final int DB_RECORDCOUNT = 31;
    static final int DB_RECOVER = 0x000020;
    static final int DB_RECOVER_FATAL = 0x040000;
    static final int DB_REGION_INIT = 0x008000;
    static final int DB_RENUMBER = 0x000008;
    static final int DB_REP_CLIENT = 0x001;
    static final int DB_REP_LOGSONLY = 0x002;
    static final int DB_REP_MASTER = 0x004;
    static final int DB_REP_PERMANENT = 0x0001;
    static final int DB_REP_UNAVAIL = -30982;
    static final int DB_REVSPLITOFF = 0x000010;
    static final int DB_RMW = 0x10000000;
    static final int DB_SALVAGE = 0x000020;
    static final int DB_SET = 32;
    static final int DB_SET_LOCK_TIMEOUT = 33;
    static final int DB_SET_RANGE = 34;
    static final int DB_SET_RECNO = 35;
    static final int DB_SET_TXN_TIMEOUT = 37;
    static final int DB_SNAPSHOT = 0x000020;
    static final int DB_STAT_CLEAR = 0x000001;
    static final int DB_SYSTEM_MEM = 0x080000;
    static final int DB_THREAD = 0x000040;
    static final int DB_TRUNCATE = 0x002000;
    static final int DB_TXN_NOSYNC = 0x000080;
    static final int DB_TXN_NOWAIT = 0x000400;
    static final int DB_TXN_SYNC = 0x000800;
    static final int DB_UPGRADE = 0x000400;
    static final int DB_USE_ENVIRON = 0x000100;
    static final int DB_USE_ENVIRON_ROOT = 0x000200;
    static final int DB_VERB_CHKPOINT = 0x0001;
    static final int DB_VERB_DEADLOCK = 0x0002;
    static final int DB_VERB_RECOVERY = 0x0004;
    static final int DB_VERB_REPLICATION = 0x0008;
    static final int DB_VERB_WAITSFOR = 0x0010;
    static final int DB_VERIFY = 0x000800;
    static final int DB_VERSION_MAJOR = 4;
    static final int DB_VERSION_MINOR = 0;
    static final int DB_VERSION_PATCH = 14;
    static final int DB_WRITECURSOR = 39;
    static final int DB_XA_CREATE = 0x000400;
    static final int DB_XIDDATASIZE = 128;
    static final int DB_YIELDCPU = 0x010000;
}

// end of DbConstants.java