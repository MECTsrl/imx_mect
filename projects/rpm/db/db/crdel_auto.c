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
 * PUBLIC: int __crdel_fileopen_log __P((DB_ENV *, DB_TXN *, DB_LSN *,
 * PUBLIC:      u_int32_t, const DBT *, u_int32_t));
 */
int
__crdel_fileopen_log(dbenv, txnid, ret_lsnp, flags,
	name, mode)
	DB_ENV *dbenv;
	DB_TXN *txnid;
	DB_LSN *ret_lsnp;
	u_int32_t flags;
	const DBT *name;
	u_int32_t mode;
{
	DBT logrec;
	DB_LSN *lsnp, null_lsn;
	u_int32_t zero;
	u_int32_t uinttmp;
	u_int32_t rectype, txn_num;
	int ret;
	u_int8_t *bp;

	rectype = DB_crdel_fileopen;
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
	    + sizeof(u_int32_t) + (name == NULL ? 0 : name->size)
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

	uinttmp = (u_int32_t)mode;
	memcpy(bp, &uinttmp, sizeof(uinttmp));
	bp += sizeof(uinttmp);

	DB_ASSERT((u_int32_t)(bp - (u_int8_t *)logrec.data) == logrec.size);
	ret = dbenv->log_put(dbenv, ret_lsnp, (DBT *)&logrec, flags);
	if (txnid != NULL && ret == 0)
		txnid->last_lsn = *ret_lsnp;
#ifdef LOG_DIAGNOSTIC
	if (ret != 0)
		(void)__crdel_fileopen_print(dbenv,
		    (DBT *)&logrec, ret_lsnp, NULL, NULL);
#endif
	__os_free(dbenv, logrec.data, logrec.size);
	return (ret);
}

/*
 * PUBLIC: int __crdel_fileopen_getpgnos __P((DB_ENV *, DBT *, DB_LSN *,
 * PUBLIC:      db_recops, void *));
 */
int
__crdel_fileopen_getpgnos(dbenv, rec, lsnp, notused1, summary)
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
 * PUBLIC: int __crdel_fileopen_print __P((DB_ENV *, DBT *, DB_LSN *,
 * PUBLIC:      db_recops, void *));
 */
int
__crdel_fileopen_print(dbenv, dbtp, lsnp, notused2, notused3)
	DB_ENV *dbenv;
	DBT *dbtp;
	DB_LSN *lsnp;
	db_recops notused2;
	void *notused3;
{
	__crdel_fileopen_args *argp;
	u_int32_t i;
	u_int ch;
	int ret;

	notused2 = DB_TXN_ABORT;
	notused3 = NULL;

	if ((ret = __crdel_fileopen_read(dbenv, dbtp->data, &argp)) != 0)
		return (ret);
	(void)printf(
	    "[%lu][%lu]crdel_fileopen: rec: %lu txnid %lx prevlsn [%lu][%lu]\n",
	    (u_long)lsnp->file,
	    (u_long)lsnp->offset,
	    (u_long)argp->type,
	    (u_long)argp->txnid->txnid,
	    (u_long)argp->prev_lsn.file,
	    (u_long)argp->prev_lsn.offset);
	(void)printf("\tname: ");
	for (i = 0; i < argp->name.size; i++) {
		ch = ((u_int8_t *)argp->name.data)[i];
		if (isprint(ch) || ch == 0xa)
			(void)putchar(ch);
		else
			(void)printf("%#x ", ch);
	}
	(void)printf("\n");
	(void)printf("\tmode: %o\n", argp->mode);
	(void)printf("\n");
	__os_free(dbenv, argp, 0);
	return (0);
}

/*
 * PUBLIC: int __crdel_fileopen_read __P((DB_ENV *, void *,
 * PUBLIC:      __crdel_fileopen_args **));
 */
int
__crdel_fileopen_read(dbenv, recbuf, argpp)
	DB_ENV *dbenv;
	void *recbuf;
	__crdel_fileopen_args **argpp;
{
	__crdel_fileopen_args *argp;
	int ret;
	u_int32_t uinttmp;
	u_int8_t *bp;

	ret = __os_malloc(dbenv, sizeof(__crdel_fileopen_args) +
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

	memset(&argp->name, 0, sizeof(argp->name));
	memcpy(&argp->name.size, bp, sizeof(u_int32_t));
	bp += sizeof(u_int32_t);
	argp->name.data = bp;
	bp += argp->name.size;

	memcpy(&uinttmp, bp, sizeof(uinttmp));
	argp->mode = (u_int32_t)uinttmp;
	bp += sizeof(uinttmp);

	*argpp = argp;
	return (0);
}

/*
 * PUBLIC: int __crdel_metasub_log __P((DB_ENV *, DB_TXN *, DB_LSN *,
 * PUBLIC:      u_int32_t, int32_t, db_pgno_t, const DBT *, DB_LSN *));
 */
int
__crdel_metasub_log(dbenv, txnid, ret_lsnp, flags,
	fileid, pgno, page, lsn)
	DB_ENV *dbenv;
	DB_TXN *txnid;
	DB_LSN *ret_lsnp;
	u_int32_t flags;
	int32_t fileid;
	db_pgno_t pgno;
	const DBT *page;
	DB_LSN * lsn;
{
	DBT logrec;
	DB_LSN *lsnp, null_lsn;
	u_int32_t zero;
	u_int32_t uinttmp;
	u_int32_t rectype, txn_num;
	int ret;
	u_int8_t *bp;

	rectype = DB_crdel_metasub;
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
	    + sizeof(u_int32_t)
	    + sizeof(u_int32_t) + (page == NULL ? 0 : page->size)
	    + sizeof(*lsn);
	if ((ret = __os_malloc(dbenv, logrec.size, &logrec.data)) != 0)
		return (ret);

	bp = logrec.data;

	memcpy(bp, &rectype, sizeof(rectype));
	bp += sizeof(rectype);

	memcpy(bp, &txn_num, sizeof(txn_num));
	bp += sizeof(txn_num);

	memcpy(bp, lsnp, sizeof(DB_LSN));
	bp += sizeof(DB_LSN);

	uinttmp = (u_int32_t)fileid;
	memcpy(bp, &uinttmp, sizeof(uinttmp));
	bp += sizeof(uinttmp);

	uinttmp = (u_int32_t)pgno;
	memcpy(bp, &uinttmp, sizeof(uinttmp));
	bp += sizeof(uinttmp);

	if (page == NULL) {
		zero = 0;
		memcpy(bp, &zero, sizeof(u_int32_t));
		bp += sizeof(u_int32_t);
	} else {
		memcpy(bp, &page->size, sizeof(page->size));
		bp += sizeof(page->size);
		memcpy(bp, page->data, page->size);
		bp += page->size;
	}

	if (lsn != NULL)
		memcpy(bp, lsn, sizeof(*lsn));
	else
		memset(bp, 0, sizeof(*lsn));
	bp += sizeof(*lsn);

	DB_ASSERT((u_int32_t)(bp - (u_int8_t *)logrec.data) == logrec.size);
	ret = dbenv->log_put(dbenv, ret_lsnp, (DBT *)&logrec, flags);
	if (txnid != NULL && ret == 0)
		txnid->last_lsn = *ret_lsnp;
#ifdef LOG_DIAGNOSTIC
	if (ret != 0)
		(void)__crdel_metasub_print(dbenv,
		    (DBT *)&logrec, ret_lsnp, NULL, NULL);
#endif
	__os_free(dbenv, logrec.data, logrec.size);
	return (ret);
}

/*
 * PUBLIC: int __crdel_metasub_getpgnos __P((DB_ENV *, DBT *, DB_LSN *,
 * PUBLIC:      db_recops, void *));
 */
int
__crdel_metasub_getpgnos(dbenv, rec, lsnp, notused1, summary)
	DB_ENV *dbenv;
	DBT *rec;
	DB_LSN *lsnp;
	db_recops notused1;
	void *summary;
{
	DB *dbp;
	TXN_RECS *t;
	__crdel_metasub_args *argp;
	u_int32_t ret;

	COMPQUIET(notused1, DB_TXN_ABORT);

	argp = NULL;
	t = (TXN_RECS *)summary;

	if ((ret = __crdel_metasub_read(dbenv, rec->data, &argp)) != 0)
		return (ret);

	if ((ret = __db_fileid_to_db(dbenv, &dbp, argp->fileid, 0)) != 0)
		goto err;

	if ((ret = __rep_check_alloc(dbenv, t, 1)) != 0)
		goto err;

	t->array[t->npages].flags = 0;
	t->array[t->npages].fid = argp->fileid;
	t->array[t->npages].lsn = *lsnp;
	t->array[t->npages].pgdesc.pgno = argp->pgno;
	t->array[t->npages].pgdesc.type = DB_PAGE_LOCK;
	memcpy(t->array[t->npages].pgdesc.fileid, dbp->fileid,
	    DB_FILE_ID_LEN);
	t->npages++;

err:	if (argp != NULL)
		__os_free(dbenv, argp, sizeof(__crdel_metasub_args));
	return (ret);
}

/*
 * PUBLIC: int __crdel_metasub_print __P((DB_ENV *, DBT *, DB_LSN *, db_recops,
 * PUBLIC:      void *));
 */
int
__crdel_metasub_print(dbenv, dbtp, lsnp, notused2, notused3)
	DB_ENV *dbenv;
	DBT *dbtp;
	DB_LSN *lsnp;
	db_recops notused2;
	void *notused3;
{
	__crdel_metasub_args *argp;
	u_int32_t i;
	u_int ch;
	int ret;

	notused2 = DB_TXN_ABORT;
	notused3 = NULL;

	if ((ret = __crdel_metasub_read(dbenv, dbtp->data, &argp)) != 0)
		return (ret);
	(void)printf(
	    "[%lu][%lu]crdel_metasub: rec: %lu txnid %lx prevlsn [%lu][%lu]\n",
	    (u_long)lsnp->file,
	    (u_long)lsnp->offset,
	    (u_long)argp->type,
	    (u_long)argp->txnid->txnid,
	    (u_long)argp->prev_lsn.file,
	    (u_long)argp->prev_lsn.offset);
	(void)printf("\tfileid: %ld\n", (long)argp->fileid);
	(void)printf("\tpgno: %lu\n", (u_long)argp->pgno);
	(void)printf("\tpage: ");
	for (i = 0; i < argp->page.size; i++) {
		ch = ((u_int8_t *)argp->page.data)[i];
		if (isprint(ch) || ch == 0xa)
			(void)putchar(ch);
		else
			(void)printf("%#x ", ch);
	}
	(void)printf("\n");
	(void)printf("\tlsn: [%lu][%lu]\n",
	    (u_long)argp->lsn.file, (u_long)argp->lsn.offset);
	(void)printf("\n");
	__os_free(dbenv, argp, 0);
	return (0);
}

/*
 * PUBLIC: int __crdel_metasub_read __P((DB_ENV *, void *,
 * PUBLIC:      __crdel_metasub_args **));
 */
int
__crdel_metasub_read(dbenv, recbuf, argpp)
	DB_ENV *dbenv;
	void *recbuf;
	__crdel_metasub_args **argpp;
{
	__crdel_metasub_args *argp;
	int ret;
	u_int32_t uinttmp;
	u_int8_t *bp;

	ret = __os_malloc(dbenv, sizeof(__crdel_metasub_args) +
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
	argp->fileid = (int32_t)uinttmp;
	bp += sizeof(uinttmp);

	memcpy(&uinttmp, bp, sizeof(uinttmp));
	argp->pgno = (db_pgno_t)uinttmp;
	bp += sizeof(uinttmp);

	memset(&argp->page, 0, sizeof(argp->page));
	memcpy(&argp->page.size, bp, sizeof(u_int32_t));
	bp += sizeof(u_int32_t);
	argp->page.data = bp;
	bp += argp->page.size;

	memcpy(&argp->lsn, bp,  sizeof(argp->lsn));
	bp += sizeof(argp->lsn);

	*argpp = argp;
	return (0);
}

/*
 * PUBLIC: int __crdel_metapage_log __P((DB_ENV *, DB_TXN *, DB_LSN *,
 * PUBLIC:      u_int32_t, int32_t, const DBT *, db_pgno_t, const DBT *));
 */
int
__crdel_metapage_log(dbenv, txnid, ret_lsnp, flags,
	fileid, name, pgno, page)
	DB_ENV *dbenv;
	DB_TXN *txnid;
	DB_LSN *ret_lsnp;
	u_int32_t flags;
	int32_t fileid;
	const DBT *name;
	db_pgno_t pgno;
	const DBT *page;
{
	DBT logrec;
	DB_LSN *lsnp, null_lsn;
	u_int32_t zero;
	u_int32_t uinttmp;
	u_int32_t rectype, txn_num;
	int ret;
	u_int8_t *bp;

	rectype = DB_crdel_metapage;
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
	    + sizeof(u_int32_t)
	    + sizeof(u_int32_t) + (page == NULL ? 0 : page->size);
	if ((ret = __os_malloc(dbenv, logrec.size, &logrec.data)) != 0)
		return (ret);

	bp = logrec.data;

	memcpy(bp, &rectype, sizeof(rectype));
	bp += sizeof(rectype);

	memcpy(bp, &txn_num, sizeof(txn_num));
	bp += sizeof(txn_num);

	memcpy(bp, lsnp, sizeof(DB_LSN));
	bp += sizeof(DB_LSN);

	uinttmp = (u_int32_t)fileid;
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

	uinttmp = (u_int32_t)pgno;
	memcpy(bp, &uinttmp, sizeof(uinttmp));
	bp += sizeof(uinttmp);

	if (page == NULL) {
		zero = 0;
		memcpy(bp, &zero, sizeof(u_int32_t));
		bp += sizeof(u_int32_t);
	} else {
		memcpy(bp, &page->size, sizeof(page->size));
		bp += sizeof(page->size);
		memcpy(bp, page->data, page->size);
		bp += page->size;
	}

	DB_ASSERT((u_int32_t)(bp - (u_int8_t *)logrec.data) == logrec.size);
	ret = dbenv->log_put(dbenv, ret_lsnp, (DBT *)&logrec, flags);
	if (txnid != NULL && ret == 0)
		txnid->last_lsn = *ret_lsnp;
#ifdef LOG_DIAGNOSTIC
	if (ret != 0)
		(void)__crdel_metapage_print(dbenv,
		    (DBT *)&logrec, ret_lsnp, NULL, NULL);
#endif
	__os_free(dbenv, logrec.data, logrec.size);
	return (ret);
}

/*
 * PUBLIC: int __crdel_metapage_getpgnos __P((DB_ENV *, DBT *, DB_LSN *,
 * PUBLIC:      db_recops, void *));
 */
int
__crdel_metapage_getpgnos(dbenv, rec, lsnp, notused1, summary)
	DB_ENV *dbenv;
	DBT *rec;
	DB_LSN *lsnp;
	db_recops notused1;
	void *summary;
{
	DB *dbp;
	TXN_RECS *t;
	__crdel_metapage_args *argp;
	u_int32_t ret;

	COMPQUIET(notused1, DB_TXN_ABORT);

	argp = NULL;
	t = (TXN_RECS *)summary;

	if ((ret = __crdel_metapage_read(dbenv, rec->data, &argp)) != 0)
		return (ret);

	if ((ret = __db_fileid_to_db(dbenv, &dbp, argp->fileid, 0)) != 0)
		goto err;

	if ((ret = __rep_check_alloc(dbenv, t, 1)) != 0)
		goto err;

	t->array[t->npages].flags = 0;
	t->array[t->npages].fid = argp->fileid;
	t->array[t->npages].lsn = *lsnp;
	t->array[t->npages].pgdesc.pgno = argp->pgno;
	t->array[t->npages].pgdesc.type = DB_PAGE_LOCK;
	memcpy(t->array[t->npages].pgdesc.fileid, dbp->fileid,
	    DB_FILE_ID_LEN);
	t->npages++;

err:	if (argp != NULL)
		__os_free(dbenv, argp, sizeof(__crdel_metapage_args));
	return (ret);
}

/*
 * PUBLIC: int __crdel_metapage_print __P((DB_ENV *, DBT *, DB_LSN *,
 * PUBLIC:      db_recops, void *));
 */
int
__crdel_metapage_print(dbenv, dbtp, lsnp, notused2, notused3)
	DB_ENV *dbenv;
	DBT *dbtp;
	DB_LSN *lsnp;
	db_recops notused2;
	void *notused3;
{
	__crdel_metapage_args *argp;
	u_int32_t i;
	u_int ch;
	int ret;

	notused2 = DB_TXN_ABORT;
	notused3 = NULL;

	if ((ret = __crdel_metapage_read(dbenv, dbtp->data, &argp)) != 0)
		return (ret);
	(void)printf(
	    "[%lu][%lu]crdel_metapage: rec: %lu txnid %lx prevlsn [%lu][%lu]\n",
	    (u_long)lsnp->file,
	    (u_long)lsnp->offset,
	    (u_long)argp->type,
	    (u_long)argp->txnid->txnid,
	    (u_long)argp->prev_lsn.file,
	    (u_long)argp->prev_lsn.offset);
	(void)printf("\tfileid: %ld\n", (long)argp->fileid);
	(void)printf("\tname: ");
	for (i = 0; i < argp->name.size; i++) {
		ch = ((u_int8_t *)argp->name.data)[i];
		if (isprint(ch) || ch == 0xa)
			(void)putchar(ch);
		else
			(void)printf("%#x ", ch);
	}
	(void)printf("\n");
	(void)printf("\tpgno: %lu\n", (u_long)argp->pgno);
	(void)printf("\tpage: ");
	for (i = 0; i < argp->page.size; i++) {
		ch = ((u_int8_t *)argp->page.data)[i];
		if (isprint(ch) || ch == 0xa)
			(void)putchar(ch);
		else
			(void)printf("%#x ", ch);
	}
	(void)printf("\n");
	(void)printf("\n");
	__os_free(dbenv, argp, 0);
	return (0);
}

/*
 * PUBLIC: int __crdel_metapage_read __P((DB_ENV *, void *,
 * PUBLIC:      __crdel_metapage_args **));
 */
int
__crdel_metapage_read(dbenv, recbuf, argpp)
	DB_ENV *dbenv;
	void *recbuf;
	__crdel_metapage_args **argpp;
{
	__crdel_metapage_args *argp;
	int ret;
	u_int32_t uinttmp;
	u_int8_t *bp;

	ret = __os_malloc(dbenv, sizeof(__crdel_metapage_args) +
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
	argp->fileid = (int32_t)uinttmp;
	bp += sizeof(uinttmp);

	memset(&argp->name, 0, sizeof(argp->name));
	memcpy(&argp->name.size, bp, sizeof(u_int32_t));
	bp += sizeof(u_int32_t);
	argp->name.data = bp;
	bp += argp->name.size;

	memcpy(&uinttmp, bp, sizeof(uinttmp));
	argp->pgno = (db_pgno_t)uinttmp;
	bp += sizeof(uinttmp);

	memset(&argp->page, 0, sizeof(argp->page));
	memcpy(&argp->page.size, bp, sizeof(u_int32_t));
	bp += sizeof(u_int32_t);
	argp->page.data = bp;
	bp += argp->page.size;

	*argpp = argp;
	return (0);
}

/*
 * PUBLIC: int __crdel_rename_log __P((DB_ENV *, DB_TXN *, DB_LSN *, u_int32_t,
 * PUBLIC:      int32_t, const DBT *, const DBT *));
 */
int
__crdel_rename_log(dbenv, txnid, ret_lsnp, flags,
	fileid, name, newname)
	DB_ENV *dbenv;
	DB_TXN *txnid;
	DB_LSN *ret_lsnp;
	u_int32_t flags;
	int32_t fileid;
	const DBT *name;
	const DBT *newname;
{
	DBT logrec;
	DB_LSN *lsnp, null_lsn;
	u_int32_t zero;
	u_int32_t uinttmp;
	u_int32_t rectype, txn_num;
	int ret;
	u_int8_t *bp;

	rectype = DB_crdel_rename;
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
	    + sizeof(u_int32_t) + (newname == NULL ? 0 : newname->size);
	if ((ret = __os_malloc(dbenv, logrec.size, &logrec.data)) != 0)
		return (ret);

	bp = logrec.data;

	memcpy(bp, &rectype, sizeof(rectype));
	bp += sizeof(rectype);

	memcpy(bp, &txn_num, sizeof(txn_num));
	bp += sizeof(txn_num);

	memcpy(bp, lsnp, sizeof(DB_LSN));
	bp += sizeof(DB_LSN);

	uinttmp = (u_int32_t)fileid;
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

	if (newname == NULL) {
		zero = 0;
		memcpy(bp, &zero, sizeof(u_int32_t));
		bp += sizeof(u_int32_t);
	} else {
		memcpy(bp, &newname->size, sizeof(newname->size));
		bp += sizeof(newname->size);
		memcpy(bp, newname->data, newname->size);
		bp += newname->size;
	}

	DB_ASSERT((u_int32_t)(bp - (u_int8_t *)logrec.data) == logrec.size);
	ret = dbenv->log_put(dbenv, ret_lsnp, (DBT *)&logrec, flags);
	if (txnid != NULL && ret == 0)
		txnid->last_lsn = *ret_lsnp;
#ifdef LOG_DIAGNOSTIC
	if (ret != 0)
		(void)__crdel_rename_print(dbenv,
		    (DBT *)&logrec, ret_lsnp, NULL, NULL);
#endif
	__os_free(dbenv, logrec.data, logrec.size);
	return (ret);
}

/*
 * PUBLIC: int __crdel_rename_getpgnos __P((DB_ENV *, DBT *, DB_LSN *,
 * PUBLIC:      db_recops, void *));
 */
int
__crdel_rename_getpgnos(dbenv, rec, lsnp, notused1, summary)
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
 * PUBLIC: int __crdel_rename_print __P((DB_ENV *, DBT *, DB_LSN *, db_recops,
 * PUBLIC:      void *));
 */
int
__crdel_rename_print(dbenv, dbtp, lsnp, notused2, notused3)
	DB_ENV *dbenv;
	DBT *dbtp;
	DB_LSN *lsnp;
	db_recops notused2;
	void *notused3;
{
	__crdel_rename_args *argp;
	u_int32_t i;
	u_int ch;
	int ret;

	notused2 = DB_TXN_ABORT;
	notused3 = NULL;

	if ((ret = __crdel_rename_read(dbenv, dbtp->data, &argp)) != 0)
		return (ret);
	(void)printf(
	    "[%lu][%lu]crdel_rename: rec: %lu txnid %lx prevlsn [%lu][%lu]\n",
	    (u_long)lsnp->file,
	    (u_long)lsnp->offset,
	    (u_long)argp->type,
	    (u_long)argp->txnid->txnid,
	    (u_long)argp->prev_lsn.file,
	    (u_long)argp->prev_lsn.offset);
	(void)printf("\tfileid: %ld\n", (long)argp->fileid);
	(void)printf("\tname: ");
	for (i = 0; i < argp->name.size; i++) {
		ch = ((u_int8_t *)argp->name.data)[i];
		if (isprint(ch) || ch == 0xa)
			(void)putchar(ch);
		else
			(void)printf("%#x ", ch);
	}
	(void)printf("\n");
	(void)printf("\tnewname: ");
	for (i = 0; i < argp->newname.size; i++) {
		ch = ((u_int8_t *)argp->newname.data)[i];
		if (isprint(ch) || ch == 0xa)
			(void)putchar(ch);
		else
			(void)printf("%#x ", ch);
	}
	(void)printf("\n");
	(void)printf("\n");
	__os_free(dbenv, argp, 0);
	return (0);
}

/*
 * PUBLIC: int __crdel_rename_read __P((DB_ENV *, void *,
 * PUBLIC:      __crdel_rename_args **));
 */
int
__crdel_rename_read(dbenv, recbuf, argpp)
	DB_ENV *dbenv;
	void *recbuf;
	__crdel_rename_args **argpp;
{
	__crdel_rename_args *argp;
	int ret;
	u_int32_t uinttmp;
	u_int8_t *bp;

	ret = __os_malloc(dbenv, sizeof(__crdel_rename_args) +
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
	argp->fileid = (int32_t)uinttmp;
	bp += sizeof(uinttmp);

	memset(&argp->name, 0, sizeof(argp->name));
	memcpy(&argp->name.size, bp, sizeof(u_int32_t));
	bp += sizeof(u_int32_t);
	argp->name.data = bp;
	bp += argp->name.size;

	memset(&argp->newname, 0, sizeof(argp->newname));
	memcpy(&argp->newname.size, bp, sizeof(u_int32_t));
	bp += sizeof(u_int32_t);
	argp->newname.data = bp;
	bp += argp->newname.size;

	*argpp = argp;
	return (0);
}

/*
 * PUBLIC: int __crdel_delete_log __P((DB_ENV *, DB_TXN *, DB_LSN *, u_int32_t,
 * PUBLIC:      int32_t, const DBT *));
 */
int
__crdel_delete_log(dbenv, txnid, ret_lsnp, flags,
	fileid, name)
	DB_ENV *dbenv;
	DB_TXN *txnid;
	DB_LSN *ret_lsnp;
	u_int32_t flags;
	int32_t fileid;
	const DBT *name;
{
	DBT logrec;
	DB_LSN *lsnp, null_lsn;
	u_int32_t zero;
	u_int32_t uinttmp;
	u_int32_t rectype, txn_num;
	int ret;
	u_int8_t *bp;

	rectype = DB_crdel_delete;
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
	    + sizeof(u_int32_t) + (name == NULL ? 0 : name->size);
	if ((ret = __os_malloc(dbenv, logrec.size, &logrec.data)) != 0)
		return (ret);

	bp = logrec.data;

	memcpy(bp, &rectype, sizeof(rectype));
	bp += sizeof(rectype);

	memcpy(bp, &txn_num, sizeof(txn_num));
	bp += sizeof(txn_num);

	memcpy(bp, lsnp, sizeof(DB_LSN));
	bp += sizeof(DB_LSN);

	uinttmp = (u_int32_t)fileid;
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

	DB_ASSERT((u_int32_t)(bp - (u_int8_t *)logrec.data) == logrec.size);
	ret = dbenv->log_put(dbenv, ret_lsnp, (DBT *)&logrec, flags);
	if (txnid != NULL && ret == 0)
		txnid->last_lsn = *ret_lsnp;
#ifdef LOG_DIAGNOSTIC
	if (ret != 0)
		(void)__crdel_delete_print(dbenv,
		    (DBT *)&logrec, ret_lsnp, NULL, NULL);
#endif
	__os_free(dbenv, logrec.data, logrec.size);
	return (ret);
}

/*
 * PUBLIC: int __crdel_delete_getpgnos __P((DB_ENV *, DBT *, DB_LSN *,
 * PUBLIC:      db_recops, void *));
 */
int
__crdel_delete_getpgnos(dbenv, rec, lsnp, notused1, summary)
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
 * PUBLIC: int __crdel_delete_print __P((DB_ENV *, DBT *, DB_LSN *, db_recops,
 * PUBLIC:      void *));
 */
int
__crdel_delete_print(dbenv, dbtp, lsnp, notused2, notused3)
	DB_ENV *dbenv;
	DBT *dbtp;
	DB_LSN *lsnp;
	db_recops notused2;
	void *notused3;
{
	__crdel_delete_args *argp;
	u_int32_t i;
	u_int ch;
	int ret;

	notused2 = DB_TXN_ABORT;
	notused3 = NULL;

	if ((ret = __crdel_delete_read(dbenv, dbtp->data, &argp)) != 0)
		return (ret);
	(void)printf(
	    "[%lu][%lu]crdel_delete: rec: %lu txnid %lx prevlsn [%lu][%lu]\n",
	    (u_long)lsnp->file,
	    (u_long)lsnp->offset,
	    (u_long)argp->type,
	    (u_long)argp->txnid->txnid,
	    (u_long)argp->prev_lsn.file,
	    (u_long)argp->prev_lsn.offset);
	(void)printf("\tfileid: %ld\n", (long)argp->fileid);
	(void)printf("\tname: ");
	for (i = 0; i < argp->name.size; i++) {
		ch = ((u_int8_t *)argp->name.data)[i];
		if (isprint(ch) || ch == 0xa)
			(void)putchar(ch);
		else
			(void)printf("%#x ", ch);
	}
	(void)printf("\n");
	(void)printf("\n");
	__os_free(dbenv, argp, 0);
	return (0);
}

/*
 * PUBLIC: int __crdel_delete_read __P((DB_ENV *, void *,
 * PUBLIC:      __crdel_delete_args **));
 */
int
__crdel_delete_read(dbenv, recbuf, argpp)
	DB_ENV *dbenv;
	void *recbuf;
	__crdel_delete_args **argpp;
{
	__crdel_delete_args *argp;
	int ret;
	u_int32_t uinttmp;
	u_int8_t *bp;

	ret = __os_malloc(dbenv, sizeof(__crdel_delete_args) +
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
	argp->fileid = (int32_t)uinttmp;
	bp += sizeof(uinttmp);

	memset(&argp->name, 0, sizeof(argp->name));
	memcpy(&argp->name.size, bp, sizeof(u_int32_t));
	bp += sizeof(u_int32_t);
	argp->name.data = bp;
	bp += argp->name.size;

	*argpp = argp;
	return (0);
}

/*
 * PUBLIC: int __crdel_init_print __P((DB_ENV *, int (***)(DB_ENV *, DBT *,
 * PUBLIC:      DB_LSN *, db_recops, void *), size_t *));
 */
int
__crdel_init_print(dbenv, dtabp, dtabsizep)
	DB_ENV *dbenv;
	int (***dtabp)__P((DB_ENV *, DBT *, DB_LSN *, db_recops, void *));
	size_t *dtabsizep;
{
	int ret;

	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __crdel_fileopen_print, DB_crdel_fileopen)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __crdel_metasub_print, DB_crdel_metasub)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __crdel_metapage_print, DB_crdel_metapage)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __crdel_rename_print, DB_crdel_rename)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __crdel_delete_print, DB_crdel_delete)) != 0)
		return (ret);
	return (0);
}

/*
 * PUBLIC: int __crdel_init_getpgnos __P((DB_ENV *, int (***)(DB_ENV *, DBT *,
 * PUBLIC:      DB_LSN *, db_recops, void *), size_t *));
 */
int
__crdel_init_getpgnos(dbenv, dtabp, dtabsizep)
	DB_ENV *dbenv;
	int (***dtabp)__P((DB_ENV *, DBT *, DB_LSN *, db_recops, void *));
	size_t *dtabsizep;
{
	int ret;

	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __crdel_fileopen_getpgnos, DB_crdel_fileopen)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __crdel_metasub_getpgnos, DB_crdel_metasub)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __crdel_metapage_getpgnos, DB_crdel_metapage)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __crdel_rename_getpgnos, DB_crdel_rename)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, dtabp, dtabsizep,
	    __crdel_delete_getpgnos, DB_crdel_delete)) != 0)
		return (ret);
	return (0);
}

/*
 * PUBLIC: int __crdel_init_recover __P((DB_ENV *));
 */
int
__crdel_init_recover(dbenv)
	DB_ENV *dbenv;
{
	int ret;

	if ((ret = __db_add_recovery(dbenv, &dbenv->dtab, &dbenv->dtab_size,
	    __crdel_fileopen_recover, DB_crdel_fileopen)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, &dbenv->dtab, &dbenv->dtab_size,
	    __crdel_metasub_recover, DB_crdel_metasub)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, &dbenv->dtab, &dbenv->dtab_size,
	    __crdel_metapage_recover, DB_crdel_metapage)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, &dbenv->dtab, &dbenv->dtab_size,
	    __crdel_rename_recover, DB_crdel_rename)) != 0)
		return (ret);
	if ((ret = __db_add_recovery(dbenv, &dbenv->dtab, &dbenv->dtab_size,
	    __crdel_delete_recover, DB_crdel_delete)) != 0)
		return (ret);
	return (0);
}
