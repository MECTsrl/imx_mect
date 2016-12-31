/* Do not edit: automatically built by gen_rec.awk. */
#include "db_config.h"

#ifndef NO_SYSTEM_INCLUDES
#include <sys/types.h>

#include <ctype.h>
#include <string.h>
#endif

#include "db_int.h"
#include "db_page.h"
#include "db_dispatch.h"
#include "db_am.h"
#include "log.h"
#include "rep.h"
#include "txn.h"

/*
 * PUBLIC: int __log_register_log __P((DB_ENV *, DB_TXN *, DB_LSN *, u_int32_t,
 * PUBLIC:      u_int32_t, const DBT *, const DBT *, int32_t, DBTYPE, db_pgno_t));
 */
int
__log_register_log(dbenv, txnid, ret_lsnp, flags,
	opcode, name, uid, fileid, ftype, meta_pgno)
	DB_ENV *dbenv;
	DB_TXN *txnid;
	DB_LSN *ret_lsnp;
	u_int32_t flags;
	u_int32_t opcode;
	const DBT *name;
	const DBT *uid;
	int32_t fileid;
	DBTYPE ftype;
	db_pgno_t meta_pgno;
{
	DBT logrec;
	DB_LSN *lsnp, null_lsn;
	u_int32_t zero;
	u_int32_t uinttmp;
	u_int32_t rectype, txn_num;
	int ret;
	u_int8_t *bp;

	rectype = DB_log_register;
	if (txnid != NULL &&
	    TAILQ_FIRST(&txnid->kids) != NULL &&
	    (ret = __txn_activekids(dbenv, rectype, txnid)) != 0)
		return (ret);
	txn_num = txnid == NULL ? 0 : txnid->txnid;
	if (txnid == NULL) {
		ZERO_LSN(null_lsn);
		lsnp = &null_lsn;
	} else
		lsnp = &txnid->last_lsn;
	logrec.size = sizeof(rectype) + sizeof(txn_num) + sizeof(DB_LSN)
	    + sizeof(u_int32_t)
	    + sizeof(u_int32_t) + (name == NULL ? 0 : name->size)
	    + sizeof(u_int32_t) + (uid == NULL ? 0 : uid->size)
	    + sizeof(u_int32_t)
	    + sizeof(u_int32_t)
	    + sizeof(u_int32_t);
	if ((ret = __os_malloc(dbenv, logrec.size, &logrec.data)) != 0)
		return (ret);

	bp = logrec.data;

	memcpy(bp, &rectype, sizeof(rectype));
	bp += sizeof(rectype);

	memcpy(bp, &txn_num, sizeof(txn_num));
	bp += sizeof(txn_num);

	memcpy(bp, lsnp, sizeof(DB_LSN));
	bp += sizeof(DB_LSN);

	uinttmp = (u_int32_t)opcode;
	memcpy(bp, &uinttmp, sizeof(uinttmp));
	bp += sizeof(uinttmp);

	if (name == NULL) {
		zero = 0;
		memcpy(bp, &zero, sizeof(u_int32_t));
		bp += sizeof(u_int32_t);
	} else {
		memcpy(bp, &name->size, sizeof(name->size));
		bp += sizeof(name->size);
		memcpy(bp, name->data, name->size);
		bp += name->size;
	}

	if (uid == NULL) {
		zero = 0;
		memcpy(bp, &zero, sizeof(u_int32_t));
		bp += sizeof(u_int32_t);
	} else {
		memcpy(bp, &uid->size, sizeof(uid->size));
		bp += sizeof(uid->size);
		memcpy(bp, uid->data, uid->size);
		bp += uid->size;
	}

	uinttmp = (u_int32_t)fileid;
	memcpy(bp, &uinttmp, sizeof(uinttmp));
	bp += sizeof(uinttmp);

	uinttmp = (u_int32_t)ftype;
	memcpy(bp, &uinttmp, sizeof(uinttmp));
	bp += sizeof(uinttmp);

	uinttmp = (u_int32_t)meta_pgno;
	memcpy(bp, &uinttmp, sizeof(uinttmp));
	bp += sizeof(uinttmp);

	DB_ASSERT((u_int32_t)(bp - (u_int8_t *)logrec.data) == logrec.size);
	ret = __log_put_int(dbenv, ret_lsnp, (DBT *)&logrec, flags);
	if (txnid != NULL && ret == 0)
		txnid->last_lsn = *ret_lsnp;
#ifdef LOG_DIAGNOSTIC
	if (ret != 0)
		(void)__log_register_print(dbenv,
		    (DBT *)&logrec, ret_lsnp, NULL, NULL);
#endif
	__os_free(dbenv, logrec.data, logrec.size);
	return (ret);
}

/*
 * PUBLIC: int __log_register_getpgnos __P((DB_ENV *, DBT *, DB_LSN *,
 * PUBLIC:      db_recops, void *));
 */
int
__log_register_getpgnos(dbenv, rec, lsnp, notused1, summary)
	DB_ENV *dbenv;
	DBT *rec;
	DB_LSN *lsnp;
	db_recops notused1;
	void *summary;
{
	TXN_RECS *t;
	int ret;
	COMPQUIET(rec, NULL);
	COMPQUIET(notused1, DB_TXN_ABORT);

	t = (TXN_RECS *)summary;

	if ((ret = __rep_check_alloc(dbenv, t, 1)) != 0)
		return (ret);

	t->array[t->npages].flags = LSN_PAGE_NOLOCK;
	t->array[t->npages].lsn = *lsnp;
	t->array[t->npages].fid = DB_LOGFILEID_INVALID;
	memset(&t->array[t->npages].pgdesc, 0,
	    sizeof(t->array[t->npages].pgdesc));

	t->npages++;

	return (0);
}

/*
 * PUBLIC: int __log_register_print __P((DB_ENV *, DBT *, DB_LSN *, db_recops,
 * PUBLIC:      void *));
 */
int
__log_register_print(dbenv, dbtp, lsnp, notused2, notused3)
	DB_ENV *dbenv;
	DBT *dbtp;
	DB_LSN *lsnp;
	db_recops notused2;
	void *notused3;
{
	__log_register_args *argp;
	u_int32_t i;
	u_int ch;
	int ret;

	notused2 = DB_TXN_ABORT;
	notused3 = NULL;

	if ((ret = __log_register_read(dbenv, dbtp->data, &argp)) != 0)
		return (ret);
	(void)printf(
	    "[%lu][%lu]log_register: rec: %lu txnid %lx prevlsn [%lu][%lu]\n",
	    (u_long)lsnp->file,
	    (u_long)lsnp->offset,
	    (u_long)argp->type,
	    (u_long)argp->txnid->txnid,
	    (u_long)argp->prev_lsn.file,
	    (u_long)argp->prev_lsn.offset);
	(void)printf("\topcode: %lu\n", (u_long)argp->opcode);
	(void)printf("\tname: ");
	for (i = 0; i < argp->name.size; i++) {
		ch = ((u_int8_t *)argp->name.data)[i];
		if (isprint(ch) || ch == 0xa)
			(void)putchar(ch);
		else
			(void)printf("%#x ", ch);
	}
	(void)printf("\n");
	(void)printf("\tuid: ");
	for (i = 0; i < argp->uid.size; i++) {
		ch = ((u_int8_t *)argp->uid.data)[i];
		if (isprint(ch) || ch == 0xa)
			(void)putchar(ch);
		else
			(void)printf("%#x ", ch);
	}
	(void)printf("\n");
	(void)printf("\tfileid: %ld\n", (long)argp->fileid);
	(void)printf("\tftype: 0x%lx\n", (u_long)argp->ftype);
	(void)printf("\tmeta_pgno: %lu\n", (u_long)argp->meta_pgno);
	(void)printf("\n");
	__os_free(dbenv, argp, 0);
	return (0);
}

/*
 * PUBLIC: int __log_register_read __P((DB_ENV *, void *,
 * PUBLIC:      __log_register_args **));
 */
int
__log_register_read(dbenv, recbuf, argpp)
	DB_ENV *dbenv;
	void *recbuf;
	__log_register_args **argpp;
{
	__log_register_args *argp;
	int ret;
	u_int32_t uinttmp;
	u_int8_t *bp;

	ret = __os_malloc(dbenv, sizeof(__log_register_args) +
	    sizeof(DB_TXN), &argp);
	if (ret != 0)
		return (ret);
	argp->txnid = (DB_TXN *)&argp[1];

	bp = recbuf;
	memcpy(&argp->type, bp, sizeof(argp->type));
	bp += sizeof(argp->type);

	memcpy(&argp->txnid->txnid,  bp, sizeof(argp->txnid->txnid));
	bp += sizeof(argp->txnid->txnid);

	memcpy(&argp->prev_lsn, bp, sizeof(DB_LSN));
	bp += sizeof(DB_LSN);

	memcpy(&uinttmp, bp, sizeof(uinttmp));
	argp->opcode = (u_int32_t)uinttmp;
	bp += sizeof(uinttmp);

	memset(&argp->name, 0, sizeof(argp->name));
	memcpy(&argp->name.size, bp, sizeof(u_int32_t));
	bp += sizeof(u_int32_t);
	argp->name.data = bp;
	bp += argp->name.size;

	memset(&argp->uid, 0, sizeof(argp->uid));
	memcpy(&argp->uid.size, bp, sizeof(u_int32_t));
	bp += sizeof(u_int32_t);
	argp->uid.data = bp;
	bp += argp->uid.size;

	memcpy(&uinttmp, bp, sizeof(uinttmp));
	argp->fileid = (int32_t)uinttmp;
	bp += sizeof(uinttmp);

	memcpy(&uinttmp, bp, sizeof(uinttmp));
	argp->ftype = (DBTYPE)uinttmp;
	bp += sizeof(uinttmp);

	memcpy(&uinttmp, bp, sizeof(uinttmp));
	argp->meta_pgno = (db_pgno_t)uinttmp;
	bp += sizeof(uinttmp);

	*argpp = argp;
	return (0);
}

/*
 * PUBLIC: int __log_init_print __P((DB_ENV *, int (***)(DB_ENV *, DBT *,
 * PUBLIC:      DB_LSN *, db_recops, void *), size_t *));
 */
int
__log_init_print(dbenv, dtabp, dtabsizep)
	DB_ENV *dbenv;
	int (***dtabp)__P((DB_ENV *, DBT *, DB_LSN *, db_recops, void *));
	size_t *dtabsizep;
{
	int ret;

	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __log_register_print, DB_log_register)) != 0)
		return (ret);
	return (0);
}

/*
 * PUBLIC: int __log_init_getpgnos __P((DB_ENV *, int (***)(DB_ENV *, DBT *,
 * PUBLIC:      DB_LSN *, db_recops, void *), size_t *));
 */
int
__log_init_getpgnos(dbenv, dtabp, dtabsizep)
	DB_ENV *dbenv;
	int (***dtabp)__P((DB_ENV *, DBT *, DB_LSN *, db_recops, void *));
	size_t *dtabsizep;
{
	int ret;

	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __log_register_getpgnos, DB_log_register)) != 0)
		return (ret);
	return (0);
}

/*
 * PUBLIC: int __log_init_recover __P((DB_ENV *));
 */
int
__log_init_recover(dbenv)
	DB_ENV *dbenv;
{
	int ret;

	if ((ret = __db_add_recovery(dbenv, &dbenv->dtab, &dbenv->dtab_size,
	    __log_register_recover, DB_log_register)) != 0)
		return (ret);
	return (0);
}
