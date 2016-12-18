/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END_OF_INPUT = 258,
     CLOSE_SYM = 259,
     HANDLER_SYM = 260,
     LAST_SYM = 261,
     NEXT_SYM = 262,
     PREV_SYM = 263,
     DIV_SYM = 264,
     EQ = 265,
     EQUAL_SYM = 266,
     SOUNDS_SYM = 267,
     GE = 268,
     GT_SYM = 269,
     LE = 270,
     LT = 271,
     NE = 272,
     IS = 273,
     MOD_SYM = 274,
     SHIFT_LEFT = 275,
     SHIFT_RIGHT = 276,
     SET_VAR = 277,
     ABORT_SYM = 278,
     ADD = 279,
     AFTER_SYM = 280,
     ALTER = 281,
     ANALYZE_SYM = 282,
     ANY_SYM = 283,
     AVG_SYM = 284,
     BEGIN_SYM = 285,
     BINLOG_SYM = 286,
     CHANGE = 287,
     CLIENT_SYM = 288,
     COMMENT_SYM = 289,
     COMMIT_SYM = 290,
     CONSISTENT_SYM = 291,
     COUNT_SYM = 292,
     CREATE = 293,
     CROSS = 294,
     CUBE_SYM = 295,
     DELETE_SYM = 296,
     DUAL_SYM = 297,
     DO_SYM = 298,
     DROP = 299,
     EVENTS_SYM = 300,
     EXECUTE_SYM = 301,
     EXPANSION_SYM = 302,
     FLUSH_SYM = 303,
     HELP_SYM = 304,
     INSERT = 305,
     RELAY_THREAD = 306,
     KILL_SYM = 307,
     LOAD = 308,
     LOCKS_SYM = 309,
     LOCK_SYM = 310,
     MASTER_SYM = 311,
     MAX_SYM = 312,
     MIN_SYM = 313,
     NONE_SYM = 314,
     OPTIMIZE = 315,
     PURGE = 316,
     REPAIR = 317,
     REPLICATION = 318,
     RESET_SYM = 319,
     ROLLBACK_SYM = 320,
     ROLLUP_SYM = 321,
     SAVEPOINT_SYM = 322,
     SELECT_SYM = 323,
     SHOW = 324,
     SLAVE = 325,
     SNAPSHOT_SYM = 326,
     SQL_THREAD = 327,
     START_SYM = 328,
     STD_SYM = 329,
     VARIANCE_SYM = 330,
     STOP_SYM = 331,
     SUM_SYM = 332,
     ADDDATE_SYM = 333,
     SUPER_SYM = 334,
     TRUNCATE_SYM = 335,
     UNLOCK_SYM = 336,
     UNTIL_SYM = 337,
     UPDATE_SYM = 338,
     ACTION = 339,
     AGGREGATE_SYM = 340,
     ALL = 341,
     AND_SYM = 342,
     AS = 343,
     ASC = 344,
     AUTO_INC = 345,
     AVG_ROW_LENGTH = 346,
     BACKUP_SYM = 347,
     BERKELEY_DB_SYM = 348,
     BINARY = 349,
     BIT_SYM = 350,
     BOOL_SYM = 351,
     BOOLEAN_SYM = 352,
     BOTH = 353,
     BTREE_SYM = 354,
     BY = 355,
     BYTE_SYM = 356,
     CACHE_SYM = 357,
     CASCADE = 358,
     CAST_SYM = 359,
     CHARSET = 360,
     CHECKSUM_SYM = 361,
     CHECK_SYM = 362,
     COMMITTED_SYM = 363,
     COLLATE_SYM = 364,
     COLLATION_SYM = 365,
     COLUMNS = 366,
     COLUMN_SYM = 367,
     CONCURRENT = 368,
     CONSTRAINT = 369,
     CONVERT_SYM = 370,
     CURRENT_USER = 371,
     DATABASES = 372,
     DATA_SYM = 373,
     DEFAULT = 374,
     DELAYED_SYM = 375,
     DELAY_KEY_WRITE_SYM = 376,
     DESC = 377,
     DESCRIBE = 378,
     DES_KEY_FILE = 379,
     DISABLE_SYM = 380,
     DISCARD = 381,
     DISTINCT = 382,
     DUPLICATE_SYM = 383,
     DYNAMIC_SYM = 384,
     ENABLE_SYM = 385,
     ENCLOSED = 386,
     ESCAPED = 387,
     DIRECTORY_SYM = 388,
     ESCAPE_SYM = 389,
     EXISTS = 390,
     EXTENDED_SYM = 391,
     FALSE_SYM = 392,
     FILE_SYM = 393,
     FIRST_SYM = 394,
     FIXED_SYM = 395,
     FLOAT_NUM = 396,
     FORCE_SYM = 397,
     FOREIGN = 398,
     FROM = 399,
     FULL = 400,
     FULLTEXT_SYM = 401,
     GLOBAL_SYM = 402,
     GRANT = 403,
     GRANTS = 404,
     GREATEST_SYM = 405,
     GROUP = 406,
     HAVING = 407,
     HASH_SYM = 408,
     HEX_NUM = 409,
     HIGH_PRIORITY = 410,
     HOSTS_SYM = 411,
     IDENT = 412,
     IDENT_QUOTED = 413,
     IGNORE_SYM = 414,
     IMPORT = 415,
     INDEX_SYM = 416,
     INDEXES = 417,
     INFILE = 418,
     INNER_SYM = 419,
     INNOBASE_SYM = 420,
     INTO = 421,
     IN_SYM = 422,
     ISOLATION = 423,
     JOIN_SYM = 424,
     KEYS = 425,
     KEY_SYM = 426,
     LEADING = 427,
     LEAST_SYM = 428,
     LEAVES = 429,
     LEVEL_SYM = 430,
     LEX_HOSTNAME = 431,
     LIKE = 432,
     LINES = 433,
     LOCAL_SYM = 434,
     LOG_SYM = 435,
     LOGS_SYM = 436,
     LONG_NUM = 437,
     LONG_SYM = 438,
     LOW_PRIORITY = 439,
     MASTER_HOST_SYM = 440,
     MASTER_USER_SYM = 441,
     MASTER_LOG_FILE_SYM = 442,
     MASTER_LOG_POS_SYM = 443,
     MASTER_PASSWORD_SYM = 444,
     MASTER_PORT_SYM = 445,
     MASTER_CONNECT_RETRY_SYM = 446,
     MASTER_SERVER_ID_SYM = 447,
     MASTER_SSL_SYM = 448,
     MASTER_SSL_CA_SYM = 449,
     MASTER_SSL_CAPATH_SYM = 450,
     MASTER_SSL_CERT_SYM = 451,
     MASTER_SSL_CIPHER_SYM = 452,
     MASTER_SSL_KEY_SYM = 453,
     RELAY_LOG_FILE_SYM = 454,
     RELAY_LOG_POS_SYM = 455,
     MATCH = 456,
     MAX_ROWS = 457,
     MAX_CONNECTIONS_PER_HOUR = 458,
     MAX_QUERIES_PER_HOUR = 459,
     MAX_UPDATES_PER_HOUR = 460,
     MEDIUM_SYM = 461,
     MIN_ROWS = 462,
     NAMES_SYM = 463,
     NATIONAL_SYM = 464,
     NATURAL = 465,
     NDBCLUSTER_SYM = 466,
     NEW_SYM = 467,
     NCHAR_SYM = 468,
     NCHAR_STRING = 469,
     NVARCHAR_SYM = 470,
     NOT = 471,
     NO_SYM = 472,
     NULL_SYM = 473,
     NUM = 474,
     OFFSET_SYM = 475,
     ON = 476,
     ONE_SHOT_SYM = 477,
     OPEN_SYM = 478,
     OPTION = 479,
     OPTIONALLY = 480,
     OR_SYM = 481,
     OR_OR_CONCAT = 482,
     ORDER_SYM = 483,
     OUTER = 484,
     OUTFILE = 485,
     DUMPFILE = 486,
     PACK_KEYS_SYM = 487,
     PARTIAL = 488,
     PRIMARY_SYM = 489,
     PRIVILEGES = 490,
     PROCESS = 491,
     PROCESSLIST_SYM = 492,
     QUERY_SYM = 493,
     RAID_0_SYM = 494,
     RAID_STRIPED_SYM = 495,
     RAID_TYPE = 496,
     RAID_CHUNKS = 497,
     RAID_CHUNKSIZE = 498,
     READ_SYM = 499,
     REAL_NUM = 500,
     REFERENCES = 501,
     REGEXP = 502,
     RELOAD = 503,
     RENAME = 504,
     REPEATABLE_SYM = 505,
     REQUIRE_SYM = 506,
     RESOURCES = 507,
     RESTORE_SYM = 508,
     RESTRICT = 509,
     REVOKE = 510,
     ROWS_SYM = 511,
     ROW_FORMAT_SYM = 512,
     ROW_SYM = 513,
     RTREE_SYM = 514,
     SET = 515,
     SEPARATOR_SYM = 516,
     SERIAL_SYM = 517,
     SERIALIZABLE_SYM = 518,
     SESSION_SYM = 519,
     SIMPLE_SYM = 520,
     SHUTDOWN = 521,
     SPATIAL_SYM = 522,
     SSL_SYM = 523,
     STARTING = 524,
     STATUS_SYM = 525,
     STORAGE_SYM = 526,
     STRAIGHT_JOIN = 527,
     SUBJECT_SYM = 528,
     TABLES = 529,
     TABLE_SYM = 530,
     TABLESPACE = 531,
     TEMPORARY = 532,
     TERMINATED = 533,
     TEXT_STRING = 534,
     TO_SYM = 535,
     TRAILING = 536,
     TRANSACTION_SYM = 537,
     TRUE_SYM = 538,
     TYPE_SYM = 539,
     TYPES_SYM = 540,
     FUNC_ARG0 = 541,
     FUNC_ARG1 = 542,
     FUNC_ARG2 = 543,
     FUNC_ARG3 = 544,
     UDF_RETURNS_SYM = 545,
     UDF_SONAME_SYM = 546,
     UDF_SYM = 547,
     UNCOMMITTED_SYM = 548,
     UNDERSCORE_CHARSET = 549,
     UNICODE_SYM = 550,
     UNION_SYM = 551,
     UNIQUE_SYM = 552,
     USAGE = 553,
     USE_FRM = 554,
     USE_SYM = 555,
     USING = 556,
     VALUE_SYM = 557,
     VALUES = 558,
     VARIABLES = 559,
     WHERE = 560,
     WITH = 561,
     WRITE_SYM = 562,
     NO_WRITE_TO_BINLOG = 563,
     X509_SYM = 564,
     XOR = 565,
     COMPRESSED_SYM = 566,
     ERRORS = 567,
     WARNINGS = 568,
     ASCII_SYM = 569,
     BIGINT = 570,
     BLOB_SYM = 571,
     CHAR_SYM = 572,
     CHANGED = 573,
     COALESCE = 574,
     DATETIME = 575,
     DATE_SYM = 576,
     DECIMAL_SYM = 577,
     DOUBLE_SYM = 578,
     ENUM = 579,
     FAST_SYM = 580,
     FLOAT_SYM = 581,
     GEOMETRY_SYM = 582,
     INT_SYM = 583,
     LIMIT = 584,
     LONGBLOB = 585,
     LONGTEXT = 586,
     MEDIUMBLOB = 587,
     MEDIUMINT = 588,
     MEDIUMTEXT = 589,
     NUMERIC_SYM = 590,
     PRECISION = 591,
     PREPARE_SYM = 592,
     DEALLOCATE_SYM = 593,
     QUICK = 594,
     REAL = 595,
     SIGNED_SYM = 596,
     SMALLINT = 597,
     STRING_SYM = 598,
     TEXT_SYM = 599,
     TIMESTAMP = 600,
     TIME_SYM = 601,
     TINYBLOB = 602,
     TINYINT = 603,
     TINYTEXT = 604,
     ULONGLONG_NUM = 605,
     UNSIGNED = 606,
     VARBINARY = 607,
     VARCHAR = 608,
     VARYING = 609,
     ZEROFILL = 610,
     AGAINST = 611,
     ATAN = 612,
     BETWEEN_SYM = 613,
     BIT_AND = 614,
     BIT_OR = 615,
     BIT_XOR = 616,
     CASE_SYM = 617,
     CONCAT = 618,
     CONCAT_WS = 619,
     CONVERT_TZ_SYM = 620,
     CURDATE = 621,
     CURTIME = 622,
     DATABASE = 623,
     DATE_ADD_INTERVAL = 624,
     DATE_SUB_INTERVAL = 625,
     DAY_HOUR_SYM = 626,
     DAY_MICROSECOND_SYM = 627,
     DAY_MINUTE_SYM = 628,
     DAY_SECOND_SYM = 629,
     DAY_SYM = 630,
     DECODE_SYM = 631,
     DES_ENCRYPT_SYM = 632,
     DES_DECRYPT_SYM = 633,
     ELSE = 634,
     ELT_FUNC = 635,
     ENCODE_SYM = 636,
     ENGINE_SYM = 637,
     ENGINES_SYM = 638,
     ENCRYPT = 639,
     EXPORT_SET = 640,
     EXTRACT_SYM = 641,
     FIELD_FUNC = 642,
     FORMAT_SYM = 643,
     FOR_SYM = 644,
     FROM_UNIXTIME = 645,
     GEOMCOLLFROMTEXT = 646,
     GEOMFROMTEXT = 647,
     GEOMFROMWKB = 648,
     GEOMETRYCOLLECTION = 649,
     GROUP_CONCAT_SYM = 650,
     GROUP_UNIQUE_USERS = 651,
     GET_FORMAT = 652,
     HOUR_MICROSECOND_SYM = 653,
     HOUR_MINUTE_SYM = 654,
     HOUR_SECOND_SYM = 655,
     HOUR_SYM = 656,
     IDENTIFIED_SYM = 657,
     IF = 658,
     INSERT_METHOD = 659,
     INTERVAL_SYM = 660,
     LAST_INSERT_ID = 661,
     LEFT = 662,
     LINEFROMTEXT = 663,
     LINESTRING = 664,
     LOCATE = 665,
     MAKE_SET_SYM = 666,
     MASTER_POS_WAIT = 667,
     MICROSECOND_SYM = 668,
     MINUTE_MICROSECOND_SYM = 669,
     MINUTE_SECOND_SYM = 670,
     MINUTE_SYM = 671,
     MODE_SYM = 672,
     MODIFY_SYM = 673,
     MONTH_SYM = 674,
     MLINEFROMTEXT = 675,
     MPOINTFROMTEXT = 676,
     MPOLYFROMTEXT = 677,
     MULTILINESTRING = 678,
     MULTIPOINT = 679,
     MULTIPOLYGON = 680,
     NOW_SYM = 681,
     OLD_PASSWORD = 682,
     PASSWORD = 683,
     POINTFROMTEXT = 684,
     POINT_SYM = 685,
     POLYFROMTEXT = 686,
     POLYGON = 687,
     POSITION_SYM = 688,
     PROCEDURE = 689,
     RAND = 690,
     REPLACE = 691,
     RIGHT = 692,
     ROUND = 693,
     SECOND_SYM = 694,
     SECOND_MICROSECOND_SYM = 695,
     SHARE_SYM = 696,
     SUBDATE_SYM = 697,
     SUBSTRING = 698,
     SUBSTRING_INDEX = 699,
     TRIM = 700,
     UDA_CHAR_SUM = 701,
     UDA_FLOAT_SUM = 702,
     UDA_INT_SUM = 703,
     UDF_CHAR_FUNC = 704,
     UDF_FLOAT_FUNC = 705,
     UDF_INT_FUNC = 706,
     UNIQUE_USERS = 707,
     UNIX_TIMESTAMP = 708,
     USER = 709,
     UTC_DATE_SYM = 710,
     UTC_TIME_SYM = 711,
     UTC_TIMESTAMP_SYM = 712,
     WEEK_SYM = 713,
     WHEN_SYM = 714,
     WORK_SYM = 715,
     YEAR_MONTH_SYM = 716,
     YEAR_SYM = 717,
     YEARWEEK = 718,
     BENCHMARK_SYM = 719,
     END = 720,
     THEN_SYM = 721,
     SQL_BIG_RESULT = 722,
     SQL_CACHE_SYM = 723,
     SQL_CALC_FOUND_ROWS = 724,
     SQL_NO_CACHE_SYM = 725,
     SQL_SMALL_RESULT = 726,
     SQL_BUFFER_RESULT = 727,
     ISSUER_SYM = 728,
     CIPHER_SYM = 729,
     BEFORE_SYM = 730,
     NEG = 731
   };
#endif
#define END_OF_INPUT 258
#define CLOSE_SYM 259
#define HANDLER_SYM 260
#define LAST_SYM 261
#define NEXT_SYM 262
#define PREV_SYM 263
#define DIV_SYM 264
#define EQ 265
#define EQUAL_SYM 266
#define SOUNDS_SYM 267
#define GE 268
#define GT_SYM 269
#define LE 270
#define LT 271
#define NE 272
#define IS 273
#define MOD_SYM 274
#define SHIFT_LEFT 275
#define SHIFT_RIGHT 276
#define SET_VAR 277
#define ABORT_SYM 278
#define ADD 279
#define AFTER_SYM 280
#define ALTER 281
#define ANALYZE_SYM 282
#define ANY_SYM 283
#define AVG_SYM 284
#define BEGIN_SYM 285
#define BINLOG_SYM 286
#define CHANGE 287
#define CLIENT_SYM 288
#define COMMENT_SYM 289
#define COMMIT_SYM 290
#define CONSISTENT_SYM 291
#define COUNT_SYM 292
#define CREATE 293
#define CROSS 294
#define CUBE_SYM 295
#define DELETE_SYM 296
#define DUAL_SYM 297
#define DO_SYM 298
#define DROP 299
#define EVENTS_SYM 300
#define EXECUTE_SYM 301
#define EXPANSION_SYM 302
#define FLUSH_SYM 303
#define HELP_SYM 304
#define INSERT 305
#define RELAY_THREAD 306
#define KILL_SYM 307
#define LOAD 308
#define LOCKS_SYM 309
#define LOCK_SYM 310
#define MASTER_SYM 311
#define MAX_SYM 312
#define MIN_SYM 313
#define NONE_SYM 314
#define OPTIMIZE 315
#define PURGE 316
#define REPAIR 317
#define REPLICATION 318
#define RESET_SYM 319
#define ROLLBACK_SYM 320
#define ROLLUP_SYM 321
#define SAVEPOINT_SYM 322
#define SELECT_SYM 323
#define SHOW 324
#define SLAVE 325
#define SNAPSHOT_SYM 326
#define SQL_THREAD 327
#define START_SYM 328
#define STD_SYM 329
#define VARIANCE_SYM 330
#define STOP_SYM 331
#define SUM_SYM 332
#define ADDDATE_SYM 333
#define SUPER_SYM 334
#define TRUNCATE_SYM 335
#define UNLOCK_SYM 336
#define UNTIL_SYM 337
#define UPDATE_SYM 338
#define ACTION 339
#define AGGREGATE_SYM 340
#define ALL 341
#define AND_SYM 342
#define AS 343
#define ASC 344
#define AUTO_INC 345
#define AVG_ROW_LENGTH 346
#define BACKUP_SYM 347
#define BERKELEY_DB_SYM 348
#define BINARY 349
#define BIT_SYM 350
#define BOOL_SYM 351
#define BOOLEAN_SYM 352
#define BOTH 353
#define BTREE_SYM 354
#define BY 355
#define BYTE_SYM 356
#define CACHE_SYM 357
#define CASCADE 358
#define CAST_SYM 359
#define CHARSET 360
#define CHECKSUM_SYM 361
#define CHECK_SYM 362
#define COMMITTED_SYM 363
#define COLLATE_SYM 364
#define COLLATION_SYM 365
#define COLUMNS 366
#define COLUMN_SYM 367
#define CONCURRENT 368
#define CONSTRAINT 369
#define CONVERT_SYM 370
#define CURRENT_USER 371
#define DATABASES 372
#define DATA_SYM 373
#define DEFAULT 374
#define DELAYED_SYM 375
#define DELAY_KEY_WRITE_SYM 376
#define DESC 377
#define DESCRIBE 378
#define DES_KEY_FILE 379
#define DISABLE_SYM 380
#define DISCARD 381
#define DISTINCT 382
#define DUPLICATE_SYM 383
#define DYNAMIC_SYM 384
#define ENABLE_SYM 385
#define ENCLOSED 386
#define ESCAPED 387
#define DIRECTORY_SYM 388
#define ESCAPE_SYM 389
#define EXISTS 390
#define EXTENDED_SYM 391
#define FALSE_SYM 392
#define FILE_SYM 393
#define FIRST_SYM 394
#define FIXED_SYM 395
#define FLOAT_NUM 396
#define FORCE_SYM 397
#define FOREIGN 398
#define FROM 399
#define FULL 400
#define FULLTEXT_SYM 401
#define GLOBAL_SYM 402
#define GRANT 403
#define GRANTS 404
#define GREATEST_SYM 405
#define GROUP 406
#define HAVING 407
#define HASH_SYM 408
#define HEX_NUM 409
#define HIGH_PRIORITY 410
#define HOSTS_SYM 411
#define IDENT 412
#define IDENT_QUOTED 413
#define IGNORE_SYM 414
#define IMPORT 415
#define INDEX_SYM 416
#define INDEXES 417
#define INFILE 418
#define INNER_SYM 419
#define INNOBASE_SYM 420
#define INTO 421
#define IN_SYM 422
#define ISOLATION 423
#define JOIN_SYM 424
#define KEYS 425
#define KEY_SYM 426
#define LEADING 427
#define LEAST_SYM 428
#define LEAVES 429
#define LEVEL_SYM 430
#define LEX_HOSTNAME 431
#define LIKE 432
#define LINES 433
#define LOCAL_SYM 434
#define LOG_SYM 435
#define LOGS_SYM 436
#define LONG_NUM 437
#define LONG_SYM 438
#define LOW_PRIORITY 439
#define MASTER_HOST_SYM 440
#define MASTER_USER_SYM 441
#define MASTER_LOG_FILE_SYM 442
#define MASTER_LOG_POS_SYM 443
#define MASTER_PASSWORD_SYM 444
#define MASTER_PORT_SYM 445
#define MASTER_CONNECT_RETRY_SYM 446
#define MASTER_SERVER_ID_SYM 447
#define MASTER_SSL_SYM 448
#define MASTER_SSL_CA_SYM 449
#define MASTER_SSL_CAPATH_SYM 450
#define MASTER_SSL_CERT_SYM 451
#define MASTER_SSL_CIPHER_SYM 452
#define MASTER_SSL_KEY_SYM 453
#define RELAY_LOG_FILE_SYM 454
#define RELAY_LOG_POS_SYM 455
#define MATCH 456
#define MAX_ROWS 457
#define MAX_CONNECTIONS_PER_HOUR 458
#define MAX_QUERIES_PER_HOUR 459
#define MAX_UPDATES_PER_HOUR 460
#define MEDIUM_SYM 461
#define MIN_ROWS 462
#define NAMES_SYM 463
#define NATIONAL_SYM 464
#define NATURAL 465
#define NDBCLUSTER_SYM 466
#define NEW_SYM 467
#define NCHAR_SYM 468
#define NCHAR_STRING 469
#define NVARCHAR_SYM 470
#define NOT 471
#define NO_SYM 472
#define NULL_SYM 473
#define NUM 474
#define OFFSET_SYM 475
#define ON 476
#define ONE_SHOT_SYM 477
#define OPEN_SYM 478
#define OPTION 479
#define OPTIONALLY 480
#define OR_SYM 481
#define OR_OR_CONCAT 482
#define ORDER_SYM 483
#define OUTER 484
#define OUTFILE 485
#define DUMPFILE 486
#define PACK_KEYS_SYM 487
#define PARTIAL 488
#define PRIMARY_SYM 489
#define PRIVILEGES 490
#define PROCESS 491
#define PROCESSLIST_SYM 492
#define QUERY_SYM 493
#define RAID_0_SYM 494
#define RAID_STRIPED_SYM 495
#define RAID_TYPE 496
#define RAID_CHUNKS 497
#define RAID_CHUNKSIZE 498
#define READ_SYM 499
#define REAL_NUM 500
#define REFERENCES 501
#define REGEXP 502
#define RELOAD 503
#define RENAME 504
#define REPEATABLE_SYM 505
#define REQUIRE_SYM 506
#define RESOURCES 507
#define RESTORE_SYM 508
#define RESTRICT 509
#define REVOKE 510
#define ROWS_SYM 511
#define ROW_FORMAT_SYM 512
#define ROW_SYM 513
#define RTREE_SYM 514
#define SET 515
#define SEPARATOR_SYM 516
#define SERIAL_SYM 517
#define SERIALIZABLE_SYM 518
#define SESSION_SYM 519
#define SIMPLE_SYM 520
#define SHUTDOWN 521
#define SPATIAL_SYM 522
#define SSL_SYM 523
#define STARTING 524
#define STATUS_SYM 525
#define STORAGE_SYM 526
#define STRAIGHT_JOIN 527
#define SUBJECT_SYM 528
#define TABLES 529
#define TABLE_SYM 530
#define TABLESPACE 531
#define TEMPORARY 532
#define TERMINATED 533
#define TEXT_STRING 534
#define TO_SYM 535
#define TRAILING 536
#define TRANSACTION_SYM 537
#define TRUE_SYM 538
#define TYPE_SYM 539
#define TYPES_SYM 540
#define FUNC_ARG0 541
#define FUNC_ARG1 542
#define FUNC_ARG2 543
#define FUNC_ARG3 544
#define UDF_RETURNS_SYM 545
#define UDF_SONAME_SYM 546
#define UDF_SYM 547
#define UNCOMMITTED_SYM 548
#define UNDERSCORE_CHARSET 549
#define UNICODE_SYM 550
#define UNION_SYM 551
#define UNIQUE_SYM 552
#define USAGE 553
#define USE_FRM 554
#define USE_SYM 555
#define USING 556
#define VALUE_SYM 557
#define VALUES 558
#define VARIABLES 559
#define WHERE 560
#define WITH 561
#define WRITE_SYM 562
#define NO_WRITE_TO_BINLOG 563
#define X509_SYM 564
#define XOR 565
#define COMPRESSED_SYM 566
#define ERRORS 567
#define WARNINGS 568
#define ASCII_SYM 569
#define BIGINT 570
#define BLOB_SYM 571
#define CHAR_SYM 572
#define CHANGED 573
#define COALESCE 574
#define DATETIME 575
#define DATE_SYM 576
#define DECIMAL_SYM 577
#define DOUBLE_SYM 578
#define ENUM 579
#define FAST_SYM 580
#define FLOAT_SYM 581
#define GEOMETRY_SYM 582
#define INT_SYM 583
#define LIMIT 584
#define LONGBLOB 585
#define LONGTEXT 586
#define MEDIUMBLOB 587
#define MEDIUMINT 588
#define MEDIUMTEXT 589
#define NUMERIC_SYM 590
#define PRECISION 591
#define PREPARE_SYM 592
#define DEALLOCATE_SYM 593
#define QUICK 594
#define REAL 595
#define SIGNED_SYM 596
#define SMALLINT 597
#define STRING_SYM 598
#define TEXT_SYM 599
#define TIMESTAMP 600
#define TIME_SYM 601
#define TINYBLOB 602
#define TINYINT 603
#define TINYTEXT 604
#define ULONGLONG_NUM 605
#define UNSIGNED 606
#define VARBINARY 607
#define VARCHAR 608
#define VARYING 609
#define ZEROFILL 610
#define AGAINST 611
#define ATAN 612
#define BETWEEN_SYM 613
#define BIT_AND 614
#define BIT_OR 615
#define BIT_XOR 616
#define CASE_SYM 617
#define CONCAT 618
#define CONCAT_WS 619
#define CONVERT_TZ_SYM 620
#define CURDATE 621
#define CURTIME 622
#define DATABASE 623
#define DATE_ADD_INTERVAL 624
#define DATE_SUB_INTERVAL 625
#define DAY_HOUR_SYM 626
#define DAY_MICROSECOND_SYM 627
#define DAY_MINUTE_SYM 628
#define DAY_SECOND_SYM 629
#define DAY_SYM 630
#define DECODE_SYM 631
#define DES_ENCRYPT_SYM 632
#define DES_DECRYPT_SYM 633
#define ELSE 634
#define ELT_FUNC 635
#define ENCODE_SYM 636
#define ENGINE_SYM 637
#define ENGINES_SYM 638
#define ENCRYPT 639
#define EXPORT_SET 640
#define EXTRACT_SYM 641
#define FIELD_FUNC 642
#define FORMAT_SYM 643
#define FOR_SYM 644
#define FROM_UNIXTIME 645
#define GEOMCOLLFROMTEXT 646
#define GEOMFROMTEXT 647
#define GEOMFROMWKB 648
#define GEOMETRYCOLLECTION 649
#define GROUP_CONCAT_SYM 650
#define GROUP_UNIQUE_USERS 651
#define GET_FORMAT 652
#define HOUR_MICROSECOND_SYM 653
#define HOUR_MINUTE_SYM 654
#define HOUR_SECOND_SYM 655
#define HOUR_SYM 656
#define IDENTIFIED_SYM 657
#define IF 658
#define INSERT_METHOD 659
#define INTERVAL_SYM 660
#define LAST_INSERT_ID 661
#define LEFT 662
#define LINEFROMTEXT 663
#define LINESTRING 664
#define LOCATE 665
#define MAKE_SET_SYM 666
#define MASTER_POS_WAIT 667
#define MICROSECOND_SYM 668
#define MINUTE_MICROSECOND_SYM 669
#define MINUTE_SECOND_SYM 670
#define MINUTE_SYM 671
#define MODE_SYM 672
#define MODIFY_SYM 673
#define MONTH_SYM 674
#define MLINEFROMTEXT 675
#define MPOINTFROMTEXT 676
#define MPOLYFROMTEXT 677
#define MULTILINESTRING 678
#define MULTIPOINT 679
#define MULTIPOLYGON 680
#define NOW_SYM 681
#define OLD_PASSWORD 682
#define PASSWORD 683
#define POINTFROMTEXT 684
#define POINT_SYM 685
#define POLYFROMTEXT 686
#define POLYGON 687
#define POSITION_SYM 688
#define PROCEDURE 689
#define RAND 690
#define REPLACE 691
#define RIGHT 692
#define ROUND 693
#define SECOND_SYM 694
#define SECOND_MICROSECOND_SYM 695
#define SHARE_SYM 696
#define SUBDATE_SYM 697
#define SUBSTRING 698
#define SUBSTRING_INDEX 699
#define TRIM 700
#define UDA_CHAR_SUM 701
#define UDA_FLOAT_SUM 702
#define UDA_INT_SUM 703
#define UDF_CHAR_FUNC 704
#define UDF_FLOAT_FUNC 705
#define UDF_INT_FUNC 706
#define UNIQUE_USERS 707
#define UNIX_TIMESTAMP 708
#define USER 709
#define UTC_DATE_SYM 710
#define UTC_TIME_SYM 711
#define UTC_TIMESTAMP_SYM 712
#define WEEK_SYM 713
#define WHEN_SYM 714
#define WORK_SYM 715
#define YEAR_MONTH_SYM 716
#define YEAR_SYM 717
#define YEARWEEK 718
#define BENCHMARK_SYM 719
#define END 720
#define THEN_SYM 721
#define SQL_BIG_RESULT 722
#define SQL_CACHE_SYM 723
#define SQL_CALC_FOUND_ROWS 724
#define SQL_NO_CACHE_SYM 725
#define SQL_SMALL_RESULT 726
#define SQL_BUFFER_RESULT 727
#define ISSUER_SYM 728
#define CIPHER_SYM 729
#define BEFORE_SYM 730
#define NEG 731




/* Copy the first part of user declarations.  */
#line 19 "sql_yacc.yy"

/* thd is passed as an arg to yyparse(), and subsequently to yylex().
** The type will be void*, so it must be  cast to (THD*) when used.
** Use the YYTHD macro for this.
*/
#define YYPARSE_PARAM yythd
#define YYLEX_PARAM yythd
#define YYTHD ((THD *)yythd)

#define MYSQL_YACC
#define YYINITDEPTH 100
#define YYMAXDEPTH 3200				/* Because of 64K stack */
#define Lex (YYTHD->lex)
#define Select Lex->current_select
#include "mysql_priv.h"
#include "slave.h"
#include "lex_symbol.h"
#include "item_create.h"
#include <myisam.h>
#include <myisammrg.h>

int yylex(void *yylval, void *yythd);

#define yyoverflow(A,B,C,D,E,F) {ulong val= *(F); if(my_yyoverflow((B), (D), &val)) { yyerror((char*) (A)); return 2; } else { *(F)= (YYSIZE_T)val; }}

#define WARN_DEPRECATED(A,B) \
  push_warning_printf(((THD *)yythd), MYSQL_ERROR::WARN_LEVEL_WARN, \
		      ER_WARN_DEPRECATED_SYNTAX, \
		      ER(ER_WARN_DEPRECATED_SYNTAX), (A), (B)); 

inline Item *or_or_concat(THD *thd, Item* A, Item* B)
{
  return (thd->variables.sql_mode & MODE_PIPES_AS_CONCAT ?
          (Item*) new Item_func_concat(A,B) : (Item*) new Item_cond_or(A,B));
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 56 "sql_yacc.yy"
typedef union YYSTYPE {
  int  num;
  ulong ulong_num;
  ulonglong ulonglong_number;
  LEX_STRING lex_str;
  LEX_STRING *lex_str_ptr;
  LEX_SYMBOL symbol;
  Table_ident *table;
  char *simple_string;
  Item *item;
  Item_num *item_num;
  List<Item> *item_list;
  List<String> *string_list;
  String *string;
  key_part_spec *key_part;
  TABLE_LIST *table_list;
  udf_func *udf;
  LEX_USER *lex_user;
  struct sys_var_with_base variable;
  Key::Keytype key_type;
  enum ha_key_alg key_alg;
  enum db_type db_type;
  enum row_type row_type;
  enum ha_rkey_function ha_rkey_mode;
  enum enum_tx_isolation tx_isolation;
  enum Cast_target cast_type;
  enum Item_udftype udf_type;
  CHARSET_INFO *charset;
  thr_lock_type lock_type;
  interval_type interval;
  timestamp_type date_time_type;
  st_select_lex *select_lex;
  chooser_compare_func_creator boolfunc2creator;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 1101 "sql_yacc.cc"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 91 "sql_yacc.yy"

bool my_yyoverflow(short **a, YYSTYPE **b, ulong *yystacksize);


/* Line 214 of yacc.c.  */
#line 1116 "sql_yacc.cc"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  548
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   38574

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  495
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  493
/* YYNRULES -- Number of rules. */
#define YYNRULES  1672
/* YYNRULES -- Number of states. */
#define YYNSTATES  3102

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   731

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned short yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   489,     2,     2,     2,   482,   477,     2,
     486,   487,   480,   479,   488,   478,   493,   481,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   494,   492,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   483,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   490,   476,   491,   484,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   485
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    34,    36,    38,
      40,    42,    44,    46,    48,    50,    52,    54,    56,    58,
      60,    62,    64,    66,    68,    70,    72,    74,    76,    78,
      80,    82,    84,    86,    88,    90,    92,    94,    96,    98,
     102,   104,   106,   111,   113,   116,   117,   122,   123,   126,
     130,   132,   135,   138,   139,   145,   147,   151,   155,   159,
     163,   167,   171,   175,   179,   183,   187,   191,   195,   197,
     201,   205,   209,   213,   214,   222,   223,   235,   236,   243,
     244,   254,   257,   260,   263,   268,   273,   274,   279,   280,
     281,   287,   288,   296,   297,   298,   305,   306,   308,   309,
     311,   313,   316,   318,   320,   321,   323,   325,   328,   330,
     331,   335,   336,   338,   340,   343,   345,   348,   352,   356,
     360,   364,   368,   372,   376,   380,   384,   388,   392,   396,
     400,   404,   408,   412,   416,   422,   424,   426,   430,   435,
     440,   445,   450,   452,   454,   456,   458,   460,   462,   464,
     466,   468,   470,   472,   474,   477,   478,   480,   482,   484,
     486,   488,   492,   494,   496,   499,   502,   509,   517,   526,
     529,   532,   533,   535,   538,   539,   541,   544,   545,   550,
     554,   558,   562,   565,   567,   569,   575,   578,   583,   585,
     590,   592,   598,   603,   608,   612,   614,   616,   619,   621,
     623,   626,   628,   630,   632,   635,   639,   642,   646,   649,
     652,   656,   660,   664,   665,   672,   673,   680,   683,   685,
     687,   689,   691,   693,   695,   697,   699,   701,   703,   705,
     708,   711,   713,   716,   718,   721,   725,   728,   730,   732,
     734,   736,   738,   740,   742,   745,   746,   750,   752,   758,
     759,   761,   764,   766,   768,   770,   772,   773,   777,   778,
     780,   781,   783,   786,   788,   790,   793,   796,   801,   803,
     807,   810,   812,   815,   818,   820,   823,   826,   828,   831,
     833,   835,   837,   839,   841,   843,   845,   847,   849,   851,
     852,   855,   857,   859,   860,   862,   863,   865,   867,   869,
     872,   873,   875,   876,   881,   883,   888,   892,   894,   895,
     897,   900,   902,   906,   910,   913,   916,   919,   921,   923,
     926,   929,   932,   934,   937,   940,   943,   946,   948,   950,
     951,   953,   955,   957,   959,   960,   962,   964,   966,   967,
     970,   973,   975,   977,   979,   984,   987,   989,   994,   995,
     997,   998,  1001,  1003,  1007,  1008,  1015,  1016,  1022,  1023,
    1025,  1026,  1029,  1032,  1034,  1038,  1041,  1045,  1048,  1053,
    1054,  1061,  1062,  1063,  1072,  1077,  1082,  1086,  1090,  1093,
    1096,  1103,  1109,  1113,  1119,  1121,  1123,  1124,  1126,  1127,
    1129,  1130,  1132,  1134,  1135,  1138,  1140,  1141,  1143,  1145,
    1147,  1148,  1154,  1158,  1159,  1165,  1169,  1173,  1174,  1178,
    1179,  1182,  1184,  1188,  1189,  1191,  1193,  1194,  1197,  1199,
    1203,  1204,  1211,  1212,  1219,  1220,  1226,  1227,  1229,  1231,
    1232,  1239,  1240,  1242,  1244,  1247,  1249,  1251,  1253,  1254,
    1261,  1262,  1268,  1269,  1271,  1273,  1276,  1278,  1280,  1282,
    1284,  1286,  1287,  1294,  1295,  1297,  1299,  1300,  1305,  1307,
    1311,  1315,  1321,  1323,  1327,  1330,  1332,  1334,  1335,  1342,
    1344,  1348,  1352,  1353,  1356,  1357,  1362,  1363,  1366,  1368,
    1371,  1376,  1379,  1383,  1384,  1388,  1389,  1390,  1397,  1399,
    1401,  1403,  1406,  1409,  1418,  1422,  1423,  1425,  1428,  1430,
    1432,  1434,  1436,  1438,  1440,  1442,  1444,  1446,  1448,  1450,
    1451,  1454,  1459,  1463,  1465,  1467,  1472,  1473,  1474,  1476,
    1478,  1479,  1482,  1485,  1487,  1489,  1490,  1493,  1495,  1497,
    1499,  1501,  1503,  1505,  1507,  1509,  1511,  1513,  1519,  1526,
    1530,  1535,  1541,  1548,  1552,  1556,  1560,  1564,  1569,  1574,
    1580,  1584,  1589,  1593,  1598,  1602,  1606,  1611,  1615,  1619,
    1623,  1627,  1631,  1635,  1639,  1643,  1647,  1651,  1655,  1659,
    1664,  1669,  1675,  1682,  1686,  1690,  1694,  1698,  1703,  1708,
    1714,  1718,  1723,  1727,  1732,  1736,  1740,  1745,  1749,  1753,
    1757,  1761,  1765,  1769,  1773,  1777,  1781,  1785,  1789,  1793,
    1798,  1803,  1805,  1811,  1818,  1822,  1827,  1833,  1840,  1844,
    1848,  1852,  1857,  1862,  1868,  1872,  1877,  1881,  1886,  1890,
    1894,  1899,  1903,  1907,  1911,  1915,  1919,  1923,  1927,  1931,
    1935,  1939,  1943,  1947,  1952,  1957,  1959,  1962,  1964,  1968,
    1970,  1972,  1977,  1980,  1986,  1988,  1991,  1994,  1997,  2000,
    2003,  2007,  2013,  2020,  2023,  2025,  2030,  2038,  2043,  2046,
    2053,  2060,  2067,  2074,  2079,  2084,  2088,  2093,  2100,  2109,
    2116,  2125,  2130,  2137,  2142,  2147,  2152,  2157,  2162,  2169,
    2178,  2181,  2184,  2189,  2192,  2200,  2208,  2212,  2217,  2222,
    2229,  2236,  2241,  2248,  2255,  2262,  2267,  2274,  2279,  2286,
    2295,  2306,  2319,  2326,  2331,  2338,  2345,  2347,  2354,  2359,
    2368,  2379,  2384,  2386,  2390,  2395,  2402,  2409,  2418,  2425,
    2432,  2437,  2444,  2451,  2460,  2465,  2470,  2477,  2482,  2485,
    2490,  2495,  2500,  2507,  2512,  2516,  2525,  2532,  2537,  2544,
    2551,  2560,  2565,  2574,  2581,  2590,  2597,  2606,  2611,  2616,
    2623,  2628,  2636,  2644,  2652,  2659,  2666,  2673,  2680,  2687,
    2692,  2697,  2702,  2707,  2712,  2717,  2728,  2732,  2737,  2741,
    2744,  2747,  2750,  2755,  2762,  2767,  2772,  2779,  2786,  2793,
    2798,  2805,  2810,  2817,  2822,  2827,  2832,  2837,  2844,  2849,
    2856,  2861,  2868,  2873,  2878,  2885,  2890,  2897,  2902,  2909,
    2914,  2919,  2926,  2931,  2938,  2939,  2943,  2947,  2948,  2950,
    2955,  2960,  2965,  2970,  2976,  2981,  2982,  2983,  2991,  3002,
    3007,  3012,  3017,  3022,  3027,  3028,  3037,  3038,  3040,  3041,
    3044,  3045,  3047,  3048,  3052,  3055,  3059,  3062,  3064,  3067,
    3069,  3072,  3074,  3076,  3078,  3079,  3082,  3084,  3088,  3090,
    3094,  3095,  3098,  3100,  3104,  3105,  3107,  3108,  3111,  3112,
    3115,  3119,  3125,  3127,  3131,  3135,  3139,  3145,  3146,  3155,
    3163,  3164,  3175,  3182,  3190,  3191,  3202,  3209,  3214,  3216,
    3219,  3222,  3223,  3228,  3239,  3245,  3249,  3252,  3256,  3257,
    3258,  3264,  3265,  3267,  3268,  3271,  3274,  3277,  3278,  3284,
    3285,  3287,  3291,  3293,  3295,  3297,  3301,  3303,  3305,  3307,
    3309,  3311,  3313,  3315,  3317,  3319,  3321,  3323,  3325,  3327,
    3329,  3331,  3333,  3335,  3337,  3339,  3341,  3343,  3345,  3346,
    3348,  3350,  3351,  3354,  3355,  3357,  3358,  3359,  3363,  3364,
    3365,  3369,  3372,  3373,  3374,  3379,  3384,  3387,  3388,  3391,
    3394,  3395,  3397,  3398,  3403,  3408,  3411,  3412,  3414,  3416,
    3417,  3419,  3420,  3422,  3425,  3427,  3431,  3435,  3436,  3439,
    3441,  3443,  3445,  3447,  3449,  3451,  3453,  3455,  3457,  3459,
    3460,  3461,  3468,  3469,  3471,  3475,  3477,  3480,  3481,  3484,
    3488,  3490,  3493,  3494,  3501,  3505,  3508,  3509,  3513,  3520,
    3521,  3528,  3533,  3537,  3538,  3543,  3545,  3549,  3551,  3552,
    3555,  3556,  3558,  3559,  3560,  3569,  3570,  3571,  3572,  3580,
    3581,  3583,  3585,  3587,  3589,  3591,  3594,  3596,  3598,  3600,
    3604,  3609,  3610,  3614,  3615,  3619,  3622,  3626,  3628,  3631,
    3634,  3635,  3639,  3640,  3646,  3650,  3652,  3656,  3658,  3662,
    3664,  3666,  3667,  3669,  3670,  3675,  3676,  3678,  3682,  3684,
    3686,  3688,  3689,  3690,  3697,  3698,  3699,  3711,  3715,  3717,
    3721,  3725,  3727,  3731,  3732,  3734,  3735,  3740,  3741,  3748,
    3749,  3755,  3756,  3763,  3765,  3769,  3773,  3779,  3780,  3783,
    3784,  3787,  3789,  3791,  3793,  3797,  3798,  3800,  3801,  3805,
    3808,  3812,  3817,  3822,  3823,  3828,  3835,  3852,  3855,  3858,
    3859,  3866,  3871,  3874,  3877,  3880,  3882,  3888,  3894,  3897,
    3900,  3903,  3906,  3909,  3913,  3916,  3919,  3922,  3924,  3926,
    3930,  3935,  3939,  3942,  3945,  3947,  3949,  3951,  3953,  3954,
    3956,  3957,  3960,  3961,  3964,  3965,  3967,  3969,  3971,  3972,
    3975,  3976,  3979,  3980,  3985,  3986,  3991,  3993,  3995,  3996,
    3998,  3999,  4001,  4003,  4004,  4009,  4013,  4015,  4016,  4020,
    4025,  4028,  4030,  4032,  4034,  4036,  4038,  4040,  4042,  4044,
    4045,  4047,  4048,  4052,  4056,  4058,  4060,  4062,  4065,  4066,
    4070,  4074,  4077,  4080,  4083,  4086,  4087,  4103,  4109,  4114,
    4115,  4117,  4118,  4120,  4122,  4123,  4125,  4127,  4128,  4131,
    4134,  4136,  4140,  4145,  4149,  4153,  4154,  4157,  4160,  4162,
    4166,  4170,  4171,  4175,  4177,  4179,  4182,  4185,  4187,  4189,
    4191,  4193,  4196,  4199,  4201,  4203,  4205,  4207,  4209,  4211,
    4214,  4217,  4220,  4223,  4225,  4227,  4229,  4231,  4233,  4235,
    4237,  4241,  4247,  4249,  4251,  4255,  4260,  4266,  4268,  4272,
    4275,  4277,  4281,  4284,  4286,  4288,  4290,  4292,  4294,  4296,
    4298,  4300,  4302,  4304,  4306,  4310,  4313,  4315,  4317,  4319,
    4321,  4323,  4325,  4327,  4329,  4331,  4333,  4335,  4337,  4339,
    4341,  4343,  4345,  4347,  4349,  4351,  4353,  4355,  4357,  4359,
    4361,  4363,  4365,  4367,  4369,  4371,  4373,  4375,  4377,  4379,
    4381,  4383,  4385,  4387,  4389,  4391,  4393,  4395,  4397,  4399,
    4401,  4403,  4405,  4407,  4409,  4411,  4413,  4415,  4417,  4419,
    4421,  4423,  4425,  4427,  4429,  4431,  4433,  4435,  4437,  4439,
    4441,  4443,  4445,  4447,  4449,  4451,  4453,  4455,  4457,  4459,
    4461,  4463,  4465,  4467,  4469,  4471,  4473,  4475,  4477,  4479,
    4481,  4483,  4485,  4487,  4489,  4491,  4493,  4495,  4497,  4499,
    4501,  4503,  4505,  4507,  4509,  4511,  4513,  4515,  4517,  4519,
    4521,  4523,  4525,  4527,  4529,  4531,  4533,  4535,  4537,  4539,
    4541,  4543,  4545,  4547,  4549,  4551,  4553,  4555,  4557,  4559,
    4561,  4563,  4565,  4567,  4569,  4571,  4573,  4575,  4577,  4579,
    4581,  4583,  4585,  4587,  4589,  4591,  4593,  4595,  4597,  4599,
    4601,  4603,  4605,  4607,  4609,  4611,  4613,  4615,  4617,  4619,
    4621,  4623,  4625,  4627,  4629,  4631,  4633,  4635,  4637,  4639,
    4641,  4643,  4645,  4647,  4649,  4651,  4653,  4655,  4657,  4659,
    4661,  4663,  4665,  4667,  4669,  4671,  4673,  4675,  4677,  4679,
    4681,  4683,  4685,  4687,  4689,  4691,  4693,  4695,  4697,  4699,
    4701,  4703,  4705,  4707,  4709,  4711,  4713,  4715,  4717,  4719,
    4721,  4723,  4725,  4727,  4729,  4731,  4732,  4737,  4738,  4740,
    4742,  4746,  4749,  4752,  4754,  4756,  4758,  4760,  4761,  4763,
    4764,  4766,  4768,  4770,  4771,  4774,  4777,  4780,  4784,  4789,
    4794,  4801,  4804,  4808,  4812,  4818,  4820,  4824,  4828,  4831,
    4834,  4837,  4839,  4841,  4846,  4851,  4853,  4855,  4857,  4859,
    4861,  4862,  4867,  4869,  4871,  4873,  4877,  4881,  4883,  4885,
    4888,  4891,  4894,  4899,  4903,  4904,  4912,  4914,  4917,  4919,
    4921,  4923,  4925,  4927,  4929,  4930,  4936,  4938,  4940,  4942,
    4944,  4946,  4947,  4951,  4957,  4965,  4966,  4976,  4978,  4981,
    4982,  4984,  4986,  4990,  4991,  4995,  4996,  5000,  5001,  5005,
    5006,  5010,  5012,  5014,  5016,  5018,  5020,  5022,  5024,  5026,
    5028,  5030,  5032,  5035,  5038,  5040,  5044,  5047,  5050,  5053,
    5054,  5056,  5060,  5062,  5065,  5068,  5071,  5073,  5077,  5081,
    5083,  5085,  5089,  5094,  5100,  5102,  5103,  5107,  5111,  5113,
    5115,  5116,  5119,  5122,  5125,  5128,  5129,  5132,  5135,  5137,
    5140,  5143,  5146,  5149,  5150,  5154,  5155,  5157,  5159,  5161,
    5166,  5169,  5170,  5172,  5173,  5178,  5180,  5182,  5183,  5184,
    5187,  5190,  5192,  5193,  5195,  5197,  5201,  5203,  5207,  5209,
    5213,  5215,  5218
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     496,     0,    -1,     3,    -1,   497,     3,    -1,   611,    -1,
     649,    -1,   639,    -1,   966,    -1,   508,    -1,   651,    -1,
     641,    -1,   969,    -1,   513,    -1,   498,    -1,   830,    -1,
     857,    -1,   783,    -1,   785,    -1,   502,    -1,   863,    -1,
     943,    -1,   933,    -1,   507,    -1,   792,    -1,   877,    -1,
     879,    -1,   926,    -1,   656,    -1,   663,    -1,   667,    -1,
     500,    -1,   873,    -1,   659,    -1,   644,    -1,   795,    -1,
     869,    -1,   637,    -1,   940,    -1,   970,    -1,   971,    -1,
     675,    -1,   911,    -1,   843,    -1,   626,    -1,   629,    -1,
     841,    -1,   932,    -1,   822,    -1,   878,    -1,   499,   337,
     907,    -1,   338,    -1,    44,    -1,   337,   907,   144,   501,
      -1,   905,    -1,   492,   908,    -1,    -1,    46,   907,   503,
     504,    -1,    -1,   301,   505,    -1,   505,   488,   506,    -1,
     506,    -1,   492,   908,    -1,    49,   908,    -1,    -1,    32,
      56,   280,   509,   510,    -1,   511,    -1,   510,   488,   511,
      -1,   185,    10,   905,    -1,   186,    10,   905,    -1,   189,
      10,   905,    -1,   190,    10,   770,    -1,   191,    10,   770,
      -1,   193,    10,   770,    -1,   194,    10,   905,    -1,   195,
      10,   905,    -1,   196,    10,   905,    -1,   197,    10,   905,
      -1,   198,    10,   905,    -1,   512,    -1,   187,    10,   905,
      -1,   188,    10,   771,    -1,   199,    10,   905,    -1,   200,
      10,   770,    -1,    -1,    38,   531,   275,   534,   902,   514,
     518,    -1,    -1,    38,   603,   161,   907,   604,   221,   902,
     515,   486,   606,   487,    -1,    -1,    38,   368,   534,   907,
     516,   528,    -1,    -1,    38,   546,   292,   904,   517,   290,
     547,   291,   905,    -1,   486,   519,    -1,   535,   521,    -1,
     177,   902,    -1,   486,   177,   902,   487,    -1,   548,   487,
     535,   521,    -1,    -1,   524,   487,   520,   975,    -1,    -1,
      -1,   883,   527,   524,   522,   972,    -1,    -1,   883,   527,
     486,   524,   487,   523,   975,    -1,    -1,    -1,    68,   525,
     685,   689,   526,   545,    -1,    -1,    88,    -1,    -1,   529,
      -1,   530,    -1,   529,   530,    -1,   540,    -1,   539,    -1,
      -1,   532,    -1,   533,    -1,   533,   532,    -1,   277,    -1,
      -1,   403,   216,   135,    -1,    -1,   537,    -1,   538,    -1,
     538,   536,    -1,   538,    -1,   538,   537,    -1,   538,   488,
     537,    -1,   382,   814,   541,    -1,   284,   814,   541,    -1,
     202,   814,   771,    -1,   207,   814,   771,    -1,    91,   814,
     770,    -1,   428,   814,   905,    -1,    34,   814,   905,    -1,
      90,   814,   771,    -1,   232,   814,   770,    -1,   232,   814,
     119,    -1,   106,   814,   770,    -1,   121,   814,   770,    -1,
     257,   814,   542,    -1,   241,   814,   543,    -1,   242,   814,
     770,    -1,   243,   814,   770,    -1,   296,   814,   486,   788,
     487,    -1,   539,    -1,   540,    -1,   404,   814,   544,    -1,
     118,   133,   814,   905,    -1,   161,   133,   814,   905,    -1,
     587,   579,   814,   581,    -1,   587,   109,   814,   586,    -1,
     908,    -1,   119,    -1,   140,    -1,   129,    -1,   311,    -1,
     240,    -1,   239,    -1,   770,    -1,   217,    -1,   139,    -1,
       6,    -1,   766,    -1,   684,   688,    -1,    -1,    85,    -1,
     343,    -1,   340,    -1,   328,    -1,   549,    -1,   548,   488,
     549,    -1,   550,    -1,   551,    -1,   556,   552,    -1,   556,
     590,    -1,   598,   608,   604,   486,   606,   487,    -1,   554,
     599,   608,   604,   486,   606,   487,    -1,   554,   143,   171,
     608,   486,   606,   487,   590,    -1,   555,   552,    -1,   554,
     553,    -1,    -1,   553,    -1,   107,   696,    -1,    -1,   555,
      -1,   114,   608,    -1,    -1,   901,   557,   558,   575,    -1,
     566,   573,   570,    -1,   567,   574,   570,    -1,   326,   568,
     570,    -1,    95,   573,    -1,    96,    -1,    97,    -1,   562,
     486,   219,   487,   588,    -1,   562,   588,    -1,   563,   486,
     219,   487,    -1,   563,    -1,    94,   486,   219,   487,    -1,
      94,    -1,   564,   486,   219,   487,   588,    -1,   565,   486,
     219,   487,    -1,   352,   486,   219,   487,    -1,   462,   573,
     570,    -1,   321,    -1,   346,    -1,   345,   573,    -1,   320,
      -1,   347,    -1,   316,   573,    -1,   561,    -1,   332,    -1,
     330,    -1,   183,   352,    -1,   183,   564,   588,    -1,   349,
     588,    -1,   344,   573,   588,    -1,   334,   588,    -1,   331,
     588,    -1,   322,   568,   570,    -1,   335,   568,   570,    -1,
     140,   568,   570,    -1,    -1,   324,   559,   486,   610,   487,
     588,    -1,    -1,   260,   560,   486,   610,   487,   588,    -1,
     183,   588,    -1,   262,    -1,   327,    -1,   394,    -1,   430,
      -1,   424,    -1,   409,    -1,   423,    -1,   432,    -1,   425,
      -1,   317,    -1,   213,    -1,   209,   317,    -1,   562,   354,
      -1,   353,    -1,   209,   353,    -1,   215,    -1,   213,   353,
      -1,   209,   317,   354,    -1,   213,   354,    -1,   328,    -1,
     348,    -1,   342,    -1,   333,    -1,   315,    -1,   340,    -1,
     323,    -1,   323,   336,    -1,    -1,   486,   219,   487,    -1,
     569,    -1,   486,   219,   488,   219,   487,    -1,    -1,   571,
      -1,   571,   572,    -1,   572,    -1,   341,    -1,   351,    -1,
     355,    -1,    -1,   486,   219,   487,    -1,    -1,   569,    -1,
      -1,   576,    -1,   576,   577,    -1,   577,    -1,   218,    -1,
     216,   218,    -1,   119,   578,    -1,   221,    83,   426,   695,
      -1,    90,    -1,   262,   119,   302,    -1,   589,   171,    -1,
     297,    -1,   297,   171,    -1,    34,   905,    -1,    94,    -1,
     109,   584,    -1,   426,   695,    -1,   894,    -1,   317,   260,
      -1,   105,    -1,   908,    -1,    94,    -1,   580,    -1,   119,
      -1,   908,    -1,    94,    -1,   582,    -1,   119,    -1,   908,
      -1,    -1,   109,   586,    -1,   584,    -1,   119,    -1,    -1,
     119,    -1,    -1,   314,    -1,   101,    -1,   295,    -1,   579,
     580,    -1,    -1,   234,    -1,    -1,   246,   902,   591,   592,
      -1,   594,    -1,   486,   593,   487,   594,    -1,   593,   488,
     907,    -1,   907,    -1,    -1,   595,    -1,   595,   596,    -1,
     596,    -1,   221,    41,   597,    -1,   221,    83,   597,    -1,
     201,   145,    -1,   201,   233,    -1,   201,   265,    -1,   254,
      -1,   103,    -1,   260,   218,    -1,   217,    84,    -1,   260,
     119,    -1,   600,    -1,   146,   601,    -1,   267,   601,    -1,
     234,   171,    -1,   297,   601,    -1,   171,    -1,   161,    -1,
      -1,   600,    -1,   170,    -1,   161,    -1,   162,    -1,    -1,
     297,    -1,   146,    -1,   267,    -1,    -1,   301,   605,    -1,
     284,   605,    -1,    99,    -1,   259,    -1,   153,    -1,   606,
     488,   607,   764,    -1,   607,   764,    -1,   907,    -1,   907,
     486,   219,   487,    -1,    -1,   901,    -1,    -1,   493,   907,
      -1,   892,    -1,   610,   488,   892,    -1,    -1,    26,   622,
     275,   902,   612,   615,    -1,    -1,    26,   368,   614,   613,
     528,    -1,    -1,   907,    -1,    -1,   126,   276,    -1,   160,
     276,    -1,   617,    -1,   615,   488,   617,    -1,    24,   621,
      -1,   616,   550,   624,    -1,    24,   551,    -1,   616,   486,
     548,   487,    -1,    -1,    32,   621,   901,   618,   556,   624,
      -1,    -1,    -1,   418,   621,   901,   619,   558,   575,   620,
     624,    -1,    44,   621,   901,   623,    -1,    44,   143,   171,
     608,    -1,    44,   234,   171,    -1,    44,   600,   901,    -1,
     125,   170,    -1,   130,   170,    -1,    26,   621,   901,   260,
     119,   894,    -1,    26,   621,   901,    44,   119,    -1,   249,
     625,   902,    -1,   115,   280,   579,   581,   585,    -1,   536,
      -1,   761,    -1,    -1,   112,    -1,    -1,   159,    -1,    -1,
     254,    -1,   103,    -1,    -1,    25,   907,    -1,   139,    -1,
      -1,   280,    -1,    10,    -1,    88,    -1,    -1,    73,    70,
     631,   627,   635,    -1,    76,    70,   631,    -1,    -1,    70,
      73,   631,   628,   635,    -1,    70,    76,   631,    -1,    73,
     282,   630,    -1,    -1,   306,    36,    71,    -1,    -1,   632,
     633,    -1,   634,    -1,   633,   488,   634,    -1,    -1,    72,
      -1,    51,    -1,    -1,    82,   636,    -1,   512,    -1,   636,
     488,   512,    -1,    -1,   253,   928,   638,   788,   144,   905,
      -1,    -1,    92,   928,   640,   788,   280,   905,    -1,    -1,
     106,   928,   642,   788,   643,    -1,    -1,   339,    -1,   136,
      -1,    -1,    62,   658,   928,   645,   788,   646,    -1,    -1,
     647,    -1,   648,    -1,   648,   647,    -1,   339,    -1,   136,
      -1,   299,    -1,    -1,    27,   658,   928,   650,   788,   653,
      -1,    -1,   107,   928,   652,   788,   653,    -1,    -1,   654,
      -1,   655,    -1,   655,   654,    -1,   339,    -1,   325,    -1,
     206,    -1,   136,    -1,   318,    -1,    -1,    60,   658,   928,
     657,   788,   653,    -1,    -1,   308,    -1,   179,    -1,    -1,
     249,   928,   660,   661,    -1,   662,    -1,   661,   488,   662,
      -1,   902,   280,   902,    -1,   102,   161,   664,   167,   666,
      -1,   665,    -1,   664,   488,   665,    -1,   902,   671,    -1,
     907,    -1,   119,    -1,    -1,    53,   161,   166,   102,   668,
     669,    -1,   670,    -1,   669,   488,   670,    -1,   902,   671,
     674,    -1,    -1,   672,   673,    -1,    -1,   601,   486,   745,
     487,    -1,    -1,   159,   174,    -1,   676,    -1,    68,   678,
      -1,   486,   677,   487,   975,    -1,    68,   680,    -1,   486,
     677,   487,    -1,    -1,   680,   679,   972,    -1,    -1,    -1,
     681,   685,   689,   682,   683,   688,    -1,   766,    -1,   781,
      -1,   684,    -1,   781,   684,    -1,   684,   781,    -1,   144,
     729,   752,   757,   754,   760,   766,   772,    -1,   144,    42,
     766,    -1,    -1,   686,    -1,   686,   687,    -1,   687,    -1,
     272,    -1,   155,    -1,   127,    -1,   471,    -1,   467,    -1,
     472,    -1,   469,    -1,   470,    -1,   468,    -1,    86,    -1,
      -1,   389,    83,    -1,    55,   167,   441,   417,    -1,   689,
     488,   690,    -1,   690,    -1,   480,    -1,   691,   693,   692,
     694,    -1,    -1,    -1,   898,    -1,   696,    -1,    -1,    88,
     907,    -1,    88,   905,    -1,   907,    -1,   905,    -1,    -1,
     486,   487,    -1,   699,    -1,   703,    -1,    10,    -1,    13,
      -1,    14,    -1,    15,    -1,    16,    -1,    17,    -1,    86,
      -1,    28,    -1,   696,   167,   486,   717,   487,    -1,   696,
     216,   167,   486,   717,   487,    -1,   696,   167,   984,    -1,
     696,   216,   167,   984,    -1,   696,   358,   701,    87,   696,
      -1,   696,   216,   358,   701,    87,   696,    -1,   696,   227,
     696,    -1,   696,   226,   696,    -1,   696,   310,   696,    -1,
     696,    87,   696,    -1,   696,    12,   177,   696,    -1,   696,
     177,   703,   756,    -1,   696,   216,   177,   703,   756,    -1,
     696,   247,   696,    -1,   696,   216,   247,   696,    -1,   696,
      18,   218,    -1,   696,    18,   216,   218,    -1,   696,    11,
     696,    -1,   696,   697,   696,    -1,   696,   697,   698,   984,
      -1,   696,    20,   696,    -1,   696,    21,   696,    -1,   696,
     479,   696,    -1,   696,   478,   696,    -1,   696,   480,   696,
      -1,   696,   481,   696,    -1,   696,     9,   696,    -1,   696,
      19,   696,    -1,   696,   476,   696,    -1,   696,   483,   696,
      -1,   696,   477,   696,    -1,   696,   482,   696,    -1,   696,
     479,   702,   747,    -1,   696,   478,   702,   747,    -1,   700,
     358,   701,    87,   696,    -1,   700,   216,   358,   701,    87,
     696,    -1,   700,   227,   696,    -1,   700,   226,   696,    -1,
     700,   310,   696,    -1,   700,    87,   696,    -1,   700,    12,
     177,   696,    -1,   700,   177,   703,   756,    -1,   700,   216,
     177,   703,   756,    -1,   700,   247,   696,    -1,   700,   216,
     247,   696,    -1,   700,    18,   218,    -1,   700,    18,   216,
     218,    -1,   700,    11,   696,    -1,   700,   697,   696,    -1,
     700,   697,   698,   984,    -1,   700,    20,   696,    -1,   700,
      21,   696,    -1,   700,   479,   696,    -1,   700,   478,   696,
      -1,   700,   480,   696,    -1,   700,   481,   696,    -1,   700,
       9,   696,    -1,   700,   476,   696,    -1,   700,   483,   696,
      -1,   700,   477,   696,    -1,   700,   482,   696,    -1,   700,
      19,   696,    -1,   700,   479,   702,   747,    -1,   700,   478,
     702,   747,    -1,   703,    -1,   701,   167,   486,   717,   487,
      -1,   701,   216,   167,   486,   717,   487,    -1,   701,   167,
     984,    -1,   701,   216,   167,   984,    -1,   701,   358,   701,
      87,   696,    -1,   701,   216,   358,   701,    87,   696,    -1,
     701,   227,   696,    -1,   701,   226,   696,    -1,   701,   310,
     696,    -1,   701,    12,   177,   696,    -1,   701,   177,   703,
     756,    -1,   701,   216,   177,   703,   756,    -1,   701,   247,
     696,    -1,   701,   216,   247,   696,    -1,   701,    18,   218,
      -1,   701,    18,   216,   218,    -1,   701,    11,   696,    -1,
     701,   697,   696,    -1,   701,   697,   698,   984,    -1,   701,
      20,   696,    -1,   701,    21,   696,    -1,   701,   479,   696,
      -1,   701,   478,   696,    -1,   701,   480,   696,    -1,   701,
     481,   696,    -1,   701,     9,   696,    -1,   701,   476,   696,
      -1,   701,   483,   696,    -1,   701,   477,   696,    -1,   701,
     482,   696,    -1,   701,    19,   696,    -1,   701,   479,   702,
     747,    -1,   701,   478,   702,   747,    -1,   703,    -1,   405,
     696,    -1,   900,    -1,   703,   109,   908,    -1,   895,    -1,
     893,    -1,   492,   908,    22,   696,    -1,   492,   908,    -1,
     492,   492,   919,   908,   609,    -1,   707,    -1,   479,   696,
      -1,   478,   696,    -1,   484,   696,    -1,   216,   696,    -1,
     489,   696,    -1,   486,   696,   487,    -1,   486,   696,   488,
     717,   487,    -1,   258,   486,   696,   488,   717,   487,    -1,
     135,   982,    -1,   980,    -1,   490,   907,   696,   491,    -1,
     201,   720,   356,   486,   696,   705,   487,    -1,   314,   486,
     696,   487,    -1,    94,   696,    -1,   104,   486,   696,    88,
     716,   487,    -1,   362,   724,   459,   726,   725,   465,    -1,
     115,   486,   696,   488,   716,   487,    -1,   115,   486,   696,
     301,   580,   487,    -1,   119,   486,   900,   487,    -1,   303,
     486,   900,   487,    -1,   286,   486,   487,    -1,   287,   486,
     696,   487,    -1,   288,   486,   696,   488,   696,   487,    -1,
     289,   486,   696,   488,   696,   488,   696,   487,    -1,    78,
     486,   696,   488,   696,   487,    -1,    78,   486,   696,   488,
     405,   696,   747,   487,    -1,   357,   486,   696,   487,    -1,
     357,   486,   696,   488,   696,   487,    -1,   317,   486,   717,
     487,    -1,   105,   486,   696,   487,    -1,   319,   486,   717,
     487,    -1,   110,   486,   696,   487,    -1,   363,   486,   717,
     487,    -1,   364,   486,   696,   488,   717,   487,    -1,   365,
     486,   696,   488,   696,   488,   696,   487,    -1,   366,   695,
      -1,   367,   695,    -1,   367,   486,   696,   487,    -1,   116,
     695,    -1,   369,   486,   696,   488,   702,   747,   487,    -1,
     370,   486,   696,   488,   702,   747,   487,    -1,   368,   486,
     487,    -1,   321,   486,   696,   487,    -1,   375,   486,   696,
     487,    -1,   380,   486,   696,   488,   717,   487,    -1,   411,
     486,   696,   488,   717,   487,    -1,   384,   486,   696,   487,
      -1,   384,   486,   696,   488,   696,   487,    -1,   376,   486,
     696,   488,   906,   487,    -1,   381,   486,   696,   488,   906,
     487,    -1,   378,   486,   696,   487,    -1,   378,   486,   696,
     488,   696,   487,    -1,   377,   486,   696,   487,    -1,   377,
     486,   696,   488,   696,   487,    -1,   385,   486,   696,   488,
     696,   488,   696,   487,    -1,   385,   486,   696,   488,   696,
     488,   696,   488,   696,   487,    -1,   385,   486,   696,   488,
     696,   488,   696,   488,   696,   488,   696,   487,    -1,   388,
     486,   696,   488,   219,   487,    -1,   390,   486,   696,   487,
      -1,   390,   486,   696,   488,   696,   487,    -1,   387,   486,
     696,   488,   717,   487,    -1,   704,    -1,   397,   486,   748,
     488,   696,   487,    -1,   401,   486,   696,   487,    -1,   403,
     486,   696,   488,   696,   488,   696,   487,    -1,    50,   486,
     696,   488,   696,   488,   696,   488,   696,   487,    -1,   702,
     747,   479,   696,    -1,   702,    -1,   406,   486,   487,    -1,
     406,   486,   696,   487,    -1,   407,   486,   696,   488,   696,
     487,    -1,   410,   486,   696,   488,   696,   487,    -1,   410,
     486,   696,   488,   696,   488,   696,   487,    -1,   150,   486,
     696,   488,   717,   487,    -1,   173,   486,   696,   488,   717,
     487,    -1,   180,   486,   696,   487,    -1,   180,   486,   696,
     488,   696,   487,    -1,   412,   486,   696,   488,   696,   487,
      -1,   412,   486,   696,   488,   696,   488,   696,   487,    -1,
     413,   486,   696,   487,    -1,   416,   486,   696,   487,    -1,
      19,   486,   696,   488,   696,   487,    -1,   419,   486,   696,
     487,    -1,   426,   695,    -1,   426,   486,   696,   487,    -1,
     428,   486,   696,   487,    -1,   427,   486,   696,   487,    -1,
     433,   486,   700,   167,   696,   487,    -1,   435,   486,   696,
     487,    -1,   435,   486,   487,    -1,   436,   486,   696,   488,
     696,   488,   696,   487,    -1,   437,   486,   696,   488,   696,
     487,    -1,   438,   486,   696,   487,    -1,   438,   486,   696,
     488,   696,   487,    -1,   442,   486,   696,   488,   696,   487,
      -1,   442,   486,   696,   488,   405,   696,   747,   487,    -1,
     439,   486,   696,   487,    -1,   443,   486,   696,   488,   696,
     488,   696,   487,    -1,   443,   486,   696,   488,   696,   487,
      -1,   443,   486,   696,   144,   696,   389,   696,   487,    -1,
     443,   486,   696,   144,   696,   487,    -1,   444,   486,   696,
     488,   696,   488,   696,   487,    -1,   346,   486,   696,   487,
      -1,   345,   486,   696,   487,    -1,   345,   486,   696,   488,
     696,   487,    -1,   445,   486,   696,   487,    -1,   445,   486,
     172,   696,   144,   696,   487,    -1,   445,   486,   281,   696,
     144,   696,   487,    -1,   445,   486,    98,   696,   144,   696,
     487,    -1,   445,   486,   172,   144,   696,   487,    -1,   445,
     486,   281,   144,   696,   487,    -1,   445,   486,    98,   144,
     696,   487,    -1,   445,   486,   696,   144,   696,   487,    -1,
      80,   486,   696,   488,   696,   487,    -1,   446,   486,   706,
     487,    -1,   447,   486,   706,   487,    -1,   448,   486,   706,
     487,    -1,   449,   486,   706,   487,    -1,   450,   486,   706,
     487,    -1,   451,   486,   706,   487,    -1,   452,   486,   891,
     488,   219,   488,   219,   488,   717,   487,    -1,   453,   486,
     487,    -1,   453,   486,   696,   487,    -1,   454,   486,   487,
      -1,   455,   695,    -1,   456,   695,    -1,   457,   695,    -1,
     458,   486,   696,   487,    -1,   458,   486,   696,   488,   696,
     487,    -1,   462,   486,   696,   487,    -1,   463,   486,   696,
     487,    -1,   463,   486,   696,   488,   696,   487,    -1,   464,
     486,   770,   488,   696,   487,    -1,   386,   486,   747,   144,
     696,   487,    -1,   392,   486,   696,   487,    -1,   392,   486,
     696,   488,   696,   487,    -1,   393,   486,   696,   487,    -1,
     393,   486,   696,   488,   696,   487,    -1,   394,   486,   717,
     487,    -1,   409,   486,   717,   487,    -1,   423,   486,   717,
     487,    -1,   420,   486,   696,   487,    -1,   420,   486,   696,
     488,   696,   487,    -1,   421,   486,   696,   487,    -1,   421,
     486,   696,   488,   696,   487,    -1,   422,   486,   696,   487,
      -1,   422,   486,   696,   488,   696,   487,    -1,   424,   486,
     717,   487,    -1,   425,   486,   717,   487,    -1,   430,   486,
     696,   488,   696,   487,    -1,   429,   486,   696,   487,    -1,
     429,   486,   696,   488,   696,   487,    -1,   431,   486,   696,
     487,    -1,   431,   486,   696,   488,   696,   487,    -1,   432,
     486,   717,   487,    -1,   391,   486,   696,   487,    -1,   391,
     486,   696,   488,   696,   487,    -1,   408,   486,   696,   487,
      -1,   408,   486,   696,   488,   696,   487,    -1,    -1,   306,
     238,    47,    -1,   167,    97,   417,    -1,    -1,   717,    -1,
      29,   486,   714,   487,    -1,   359,   486,   714,   487,    -1,
     360,   486,   714,   487,    -1,   361,   486,   714,   487,    -1,
      37,   486,   751,   480,   487,    -1,    37,   486,   714,   487,
      -1,    -1,    -1,    37,   486,   127,   708,   717,   709,   487,
      -1,   396,   486,   891,   488,   219,   488,   219,   488,   714,
     487,    -1,    58,   486,   714,   487,    -1,    57,   486,   714,
     487,    -1,    74,   486,   714,   487,    -1,    75,   486,   714,
     487,    -1,    77,   486,   714,   487,    -1,    -1,   395,   486,
     711,   710,   717,   713,   712,   487,    -1,    -1,   127,    -1,
      -1,   261,   892,    -1,    -1,   761,    -1,    -1,   751,   715,
     696,    -1,    94,   573,    -1,   317,   573,   588,    -1,   213,
     573,    -1,   341,    -1,   341,   328,    -1,   351,    -1,   351,
     328,    -1,   321,    -1,   346,    -1,   320,    -1,    -1,   718,
     719,    -1,   696,    -1,   719,   488,   696,    -1,   721,    -1,
     486,   721,   487,    -1,    -1,   722,   723,    -1,   900,    -1,
     723,   488,   900,    -1,    -1,   696,    -1,    -1,   379,   696,
      -1,    -1,   727,   728,    -1,   696,   466,   696,    -1,   728,
     459,   696,   466,   696,    -1,   734,    -1,   729,   488,   729,
      -1,   729,   733,   729,    -1,   729,   272,   729,    -1,   729,
     733,   729,   221,   696,    -1,    -1,   729,   733,   729,   301,
     730,   486,   746,   487,    -1,   729,   407,   740,   169,   729,
     221,   696,    -1,    -1,   729,   407,   740,   169,   729,   731,
     301,   486,   746,   487,    -1,   729,   210,   407,   740,   169,
     729,    -1,   729,   437,   740,   169,   729,   221,   696,    -1,
      -1,   729,   437,   740,   169,   729,   732,   301,   486,   746,
     487,    -1,   729,   210,   437,   740,   169,   729,    -1,   729,
     210,   169,   729,    -1,   169,    -1,   164,   169,    -1,    39,
     169,    -1,    -1,   735,   902,   750,   741,    -1,   490,   907,
     734,   407,   229,   169,   734,   221,   696,   491,    -1,   486,
     736,   975,   487,   750,    -1,   486,   729,   487,    -1,    68,
     737,    -1,   486,   736,   487,    -1,    -1,    -1,   738,   685,
     689,   739,   545,    -1,    -1,   229,    -1,    -1,   300,   742,
      -1,   142,   742,    -1,   159,   742,    -1,    -1,   600,   743,
     486,   744,   487,    -1,    -1,   745,    -1,   745,   488,   907,
      -1,   907,    -1,   234,    -1,   907,    -1,   746,   488,   907,
      -1,   371,    -1,   372,    -1,   373,    -1,   374,    -1,   375,
      -1,   398,    -1,   399,    -1,   400,    -1,   401,    -1,   413,
      -1,   414,    -1,   415,    -1,   416,    -1,   419,    -1,   440,
      -1,   439,    -1,   461,    -1,   462,    -1,   321,    -1,   346,
      -1,   320,    -1,   345,    -1,    -1,    88,    -1,    10,    -1,
      -1,   749,   907,    -1,    -1,    86,    -1,    -1,    -1,   305,
     753,   696,    -1,    -1,    -1,   152,   755,   696,    -1,   134,
     703,    -1,    -1,    -1,   151,   100,   758,   759,    -1,   758,
     488,   899,   764,    -1,   899,   764,    -1,    -1,   306,    40,
      -1,   306,    66,    -1,    -1,   761,    -1,    -1,   228,   100,
     762,   763,    -1,   763,   488,   899,   764,    -1,   899,   764,
      -1,    -1,    89,    -1,   122,    -1,    -1,   767,    -1,    -1,
     767,    -1,   329,   768,    -1,   770,    -1,   770,   488,   770,
      -1,   770,   220,   770,    -1,    -1,   329,   771,    -1,   219,
      -1,   182,    -1,   350,    -1,   245,    -1,   141,    -1,   219,
      -1,   350,    -1,   182,    -1,   245,    -1,   141,    -1,    -1,
      -1,   434,   907,   773,   486,   774,   487,    -1,    -1,   775,
      -1,   775,   488,   776,    -1,   776,    -1,   691,   696,    -1,
      -1,   778,   779,    -1,   779,   488,   780,    -1,   780,    -1,
     492,   908,    -1,    -1,   166,   230,   905,   782,   884,   887,
      -1,   166,   231,   905,    -1,   166,   777,    -1,    -1,    43,
     784,   717,    -1,    44,   791,   928,   790,   788,   623,    -1,
      -1,    44,   161,   907,   221,   902,   786,    -1,    44,   368,
     790,   907,    -1,    44,   292,   904,    -1,    -1,    44,   454,
     787,   957,    -1,   789,    -1,   788,   488,   789,    -1,   902,
      -1,    -1,   403,   135,    -1,    -1,   277,    -1,    -1,    -1,
      50,   793,   799,   622,   801,   794,   803,   820,    -1,    -1,
      -1,    -1,   436,   796,   800,   801,   797,   803,   798,    -1,
      -1,   184,    -1,   120,    -1,   155,    -1,   829,    -1,   120,
      -1,   166,   802,    -1,   802,    -1,   789,    -1,   807,    -1,
     486,   487,   807,    -1,   486,   806,   487,   807,    -1,    -1,
     260,   804,   811,    -1,    -1,   486,   806,   487,    -1,   486,
     487,    -1,   806,   488,   897,    -1,   897,    -1,   303,   810,
      -1,   302,   810,    -1,    -1,   524,   808,   972,    -1,    -1,
     486,   524,   487,   809,   975,    -1,   810,   488,   815,    -1,
     815,    -1,   811,   488,   812,    -1,   812,    -1,   900,   813,
     819,    -1,    10,    -1,    22,    -1,    -1,   813,    -1,    -1,
     486,   816,   817,   487,    -1,    -1,   818,    -1,   818,   488,
     819,    -1,   819,    -1,   696,    -1,   119,    -1,    -1,    -1,
     221,   128,   821,   171,    83,   827,    -1,    -1,    -1,    83,
     823,   829,   622,   729,   260,   825,   824,   752,   760,   769,
      -1,   825,   488,   826,    -1,   826,    -1,   900,   813,   819,
      -1,   827,   488,   828,    -1,   828,    -1,   900,   813,   819,
      -1,    -1,   184,    -1,    -1,    41,   831,   839,   832,    -1,
      -1,   144,   902,   833,   752,   760,   769,    -1,    -1,   836,
     834,   144,   729,   752,    -1,    -1,   144,   836,   835,   301,
     729,   752,    -1,   837,    -1,   836,   488,   837,    -1,   907,
     838,   750,    -1,   907,   493,   907,   838,   750,    -1,    -1,
     493,   480,    -1,    -1,   840,   839,    -1,   339,    -1,   184,
      -1,   159,    -1,    80,   842,   789,    -1,    -1,   275,    -1,
      -1,    69,   844,   845,    -1,   117,   852,    -1,   274,   851,
     852,    -1,   275,   270,   851,   852,    -1,   223,   274,   851,
     852,    -1,    -1,   382,   541,   846,   848,    -1,   853,   111,
     854,   902,   851,   852,    -1,   212,    56,   389,    70,   306,
     187,    10,   905,    87,   188,    10,   771,    87,   192,    10,
     770,    -1,   849,   181,    -1,    70,   156,    -1,    -1,    31,
      45,   855,   856,   847,   765,    -1,   602,   854,   902,   851,
      -1,   112,   285,    -1,   275,   285,    -1,   850,   383,    -1,
     235,    -1,    37,   486,   480,   487,   313,    -1,    37,   486,
     480,   487,   312,    -1,   313,   765,    -1,   312,   765,    -1,
     270,   852,    -1,   165,   270,    -1,   853,   237,    -1,   918,
     304,   852,    -1,   579,   852,    -1,   110,   852,    -1,    93,
     181,    -1,   181,    -1,   149,    -1,   149,   389,   909,    -1,
      38,   368,   534,   907,    -1,    38,   275,   902,    -1,    56,
     270,    -1,    70,   270,    -1,   270,    -1,   181,    -1,    56,
      -1,    94,    -1,    -1,   271,    -1,    -1,   854,   907,    -1,
      -1,   177,   905,    -1,    -1,   145,    -1,   144,    -1,   167,
      -1,    -1,   167,   905,    -1,    -1,   144,   771,    -1,    -1,
     860,   902,   858,   862,    -1,    -1,   860,   861,   859,   675,
      -1,   122,    -1,   123,    -1,    -1,   136,    -1,    -1,   892,
      -1,   907,    -1,    -1,    48,   658,   864,   865,    -1,   865,
     488,   866,    -1,   866,    -1,    -1,   928,   867,   868,    -1,
     274,   306,   244,    55,    -1,   238,   102,    -1,   156,    -1,
     235,    -1,   181,    -1,   270,    -1,    70,    -1,    56,    -1,
     124,    -1,   252,    -1,    -1,   788,    -1,    -1,    64,   870,
     871,    -1,   871,   488,   872,    -1,   872,    -1,    70,    -1,
      56,    -1,   238,   102,    -1,    -1,    61,   874,   875,    -1,
     849,   181,   876,    -1,   280,   905,    -1,   475,   696,    -1,
      52,   696,    -1,   300,   907,    -1,    -1,    53,   118,   882,
     881,   163,   905,   880,   883,   166,   275,   902,   884,   887,
     890,   805,    -1,    53,   275,   902,   144,    56,    -1,    53,
     118,   144,    56,    -1,    -1,   179,    -1,    -1,   113,    -1,
     184,    -1,    -1,   436,    -1,   159,    -1,    -1,   111,   885,
      -1,   885,   886,    -1,   886,    -1,   278,   100,   892,    -1,
     225,   131,   100,   892,    -1,   131,   100,   892,    -1,   132,
     100,   892,    -1,    -1,   178,   888,    -1,   888,   889,    -1,
     889,    -1,   278,   100,   892,    -1,   269,   100,   892,    -1,
      -1,   159,   219,   178,    -1,   906,    -1,   214,    -1,   294,
     279,    -1,   891,   906,    -1,   906,    -1,   154,    -1,   494,
      -1,   895,    -1,   479,   896,    -1,   478,   896,    -1,   891,
      -1,   896,    -1,   218,    -1,   137,    -1,   283,    -1,   154,
      -1,   294,   154,    -1,   321,   891,    -1,   346,   891,    -1,
     345,   891,    -1,   219,    -1,   182,    -1,   350,    -1,   245,
      -1,   141,    -1,   900,    -1,   898,    -1,   907,   493,   480,
      -1,   907,   493,   907,   493,   480,    -1,   696,    -1,   907,
      -1,   907,   493,   907,    -1,   493,   907,   493,   907,    -1,
     907,   493,   907,   493,   907,    -1,   907,    -1,   907,   493,
     907,    -1,   493,   907,    -1,   907,    -1,   907,   493,   907,
      -1,   493,   907,    -1,   907,    -1,   157,    -1,   158,    -1,
     279,    -1,   279,    -1,   904,    -1,   910,    -1,   907,    -1,
     905,    -1,   176,    -1,   908,    -1,   908,   492,   908,    -1,
     116,   695,    -1,    84,    -1,    78,    -1,    25,    -1,   356,
      -1,    85,    -1,    28,    -1,   314,    -1,    90,    -1,    91,
      -1,    29,    -1,    92,    -1,    30,    -1,    93,    -1,    31,
      -1,    95,    -1,    96,    -1,    97,    -1,   101,    -1,    99,
      -1,   102,    -1,   318,    -1,   105,    -1,   106,    -1,   474,
      -1,    33,    -1,     4,    -1,   110,    -1,    34,    -1,   108,
      -1,    35,    -1,   311,    -1,   113,    -1,    36,    -1,    40,
      -1,   118,    -1,   320,    -1,   321,    -1,   375,    -1,   338,
      -1,   121,    -1,   124,    -1,   133,    -1,   126,    -1,    43,
      -1,   231,    -1,   128,    -1,   129,    -1,   465,    -1,   324,
      -1,   382,    -1,   383,    -1,   312,    -1,   134,    -1,    45,
      -1,    46,    -1,    47,    -1,   136,    -1,   325,    -1,   125,
      -1,   130,    -1,   145,    -1,   138,    -1,   139,    -1,   140,
      -1,    48,    -1,   327,    -1,   394,    -1,   397,    -1,   149,
      -1,   147,    -1,     5,    -1,   153,    -1,    49,    -1,   156,
      -1,   401,    -1,   402,    -1,   160,    -1,   162,    -1,   168,
      -1,   473,    -1,   165,    -1,   404,    -1,    51,    -1,     6,
      -1,   174,    -1,   175,    -1,   409,    -1,   179,    -1,    54,
      -1,   181,    -1,   202,    -1,    56,    -1,   185,    -1,   190,
      -1,   187,    -1,   188,    -1,   186,    -1,   189,    -1,   192,
      -1,   191,    -1,   193,    -1,   194,    -1,   195,    -1,   196,
      -1,   197,    -1,   198,    -1,   203,    -1,   204,    -1,   205,
      -1,   206,    -1,   413,    -1,   416,    -1,   207,    -1,   418,
      -1,   417,    -1,   419,    -1,   423,    -1,   424,    -1,   425,
      -1,   208,    -1,   209,    -1,   213,    -1,   211,    -1,     7,
      -1,   212,    -1,   217,    -1,    59,    -1,   215,    -1,   220,
      -1,   427,    -1,   222,    -1,   223,    -1,   232,    -1,   233,
      -1,   428,    -1,   430,    -1,   432,    -1,   337,    -1,     8,
      -1,   236,    -1,   237,    -1,   238,    -1,   339,    -1,   239,
      -1,   242,    -1,   243,    -1,   240,    -1,   241,    -1,   199,
      -1,   200,    -1,   248,    -1,    62,    -1,   250,    -1,    63,
      -1,    64,    -1,   252,    -1,   253,    -1,    65,    -1,    66,
      -1,   256,    -1,   257,    -1,   258,    -1,   259,    -1,    67,
      -1,   439,    -1,   262,    -1,   263,    -1,   264,    -1,   341,
      -1,   265,    -1,   441,    -1,   266,    -1,    70,    -1,    71,
      -1,    12,    -1,   468,    -1,   472,    -1,   470,    -1,    72,
      -1,    73,    -1,   270,    -1,    76,    -1,   271,    -1,   343,
      -1,   442,    -1,   273,    -1,    79,    -1,   276,    -1,   277,
      -1,   344,    -1,   282,    -1,    80,    -1,   345,    -1,   346,
      -1,   284,    -1,   285,    -1,   290,    -1,   292,    -1,   293,
      -1,   295,    -1,    82,    -1,   454,    -1,   299,    -1,   304,
      -1,   302,    -1,   313,    -1,   460,    -1,   309,    -1,   462,
      -1,    -1,   260,   913,   912,   914,    -1,    -1,   224,    -1,
     915,    -1,   914,   488,   915,    -1,   916,   920,    -1,   917,
     921,    -1,   917,    -1,   147,    -1,   179,    -1,   264,    -1,
      -1,   222,    -1,    -1,   147,    -1,   179,    -1,   264,    -1,
      -1,   147,   493,    -1,   179,   493,    -1,   264,   493,    -1,
     922,   813,   925,    -1,   282,   168,   175,   923,    -1,   492,
     908,   813,   696,    -1,   492,   492,   919,   922,   813,   925,
      -1,   579,   583,    -1,   208,   581,   585,    -1,   428,   813,
     924,    -1,   428,   389,   909,   813,   924,    -1,   907,    -1,
     907,   493,   907,    -1,   119,   493,   907,    -1,   244,   293,
      -1,   244,   108,    -1,   250,   244,    -1,   263,    -1,   279,
      -1,   428,   486,   279,   487,    -1,   427,   486,   279,   487,
      -1,   696,    -1,   119,    -1,   221,    -1,    86,    -1,    94,
      -1,    -1,    55,   928,   927,   929,    -1,   275,    -1,   274,
      -1,   930,    -1,   929,   488,   930,    -1,   902,   750,   931,
      -1,   244,    -1,   307,    -1,   184,   307,    -1,   244,   179,
      -1,    81,   928,    -1,     5,   902,   223,   750,    -1,     5,
     903,     4,    -1,    -1,     5,   903,   244,   934,   935,   752,
     766,    -1,   936,    -1,   907,   937,    -1,   139,    -1,     7,
      -1,   139,    -1,     7,    -1,     8,    -1,     6,    -1,    -1,
     939,   938,   486,   818,   487,    -1,    10,    -1,    13,    -1,
      15,    -1,    14,    -1,    16,    -1,    -1,   255,   941,   942,
      -1,   945,   221,   956,   144,   957,    -1,    86,   946,   488,
     148,   224,   144,   957,    -1,    -1,   148,   944,   945,   221,
     956,   280,   957,   962,   963,    -1,   947,    -1,    86,   946,
      -1,    -1,   235,    -1,   948,    -1,   947,   488,   948,    -1,
      -1,    68,   949,   959,    -1,    -1,    50,   950,   959,    -1,
      -1,    83,   951,   959,    -1,    -1,   246,   952,   959,    -1,
      41,    -1,   298,    -1,   161,    -1,    26,    -1,    38,    -1,
      44,    -1,    46,    -1,   248,    -1,   266,    -1,   236,    -1,
     138,    -1,   148,   224,    -1,    69,   117,    -1,    79,    -1,
      38,   277,   274,    -1,    55,   274,    -1,    63,    70,    -1,
      63,    33,    -1,    -1,    87,    -1,   955,   953,   954,    -1,
     955,    -1,   273,   279,    -1,   473,   279,    -1,   474,   279,
      -1,   480,    -1,   907,   493,   480,    -1,   480,   493,   480,
      -1,   902,    -1,   958,    -1,   957,   488,   958,    -1,   909,
     402,   100,   279,    -1,   909,   402,   100,   428,   279,    -1,
     909,    -1,    -1,   486,   960,   487,    -1,   960,   488,   961,
      -1,   961,    -1,   907,    -1,    -1,   251,   954,    -1,   251,
     268,    -1,   251,   309,    -1,   251,    59,    -1,    -1,   306,
     964,    -1,   964,   965,    -1,   965,    -1,   148,   224,    -1,
     204,   770,    -1,   205,   770,    -1,   203,   770,    -1,    -1,
      30,   967,   968,    -1,    -1,   460,    -1,    35,    -1,    65,
      -1,    65,   280,    67,   907,    -1,    67,   907,    -1,    -1,
     973,    -1,    -1,   296,   979,   974,   676,    -1,   973,    -1,
     976,    -1,    -1,    -1,   977,   978,    -1,   761,   765,    -1,
     767,    -1,    -1,   127,    -1,    86,    -1,   986,   981,   987,
      -1,   678,    -1,   986,   983,   987,    -1,   678,    -1,   986,
     985,   987,    -1,   678,    -1,   486,    68,    -1,   487,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   744,   744,   758,   761,   762,   763,   764,   765,   766,
     767,   768,   769,   770,   771,   772,   773,   774,   775,   776,
     777,   778,   779,   780,   781,   782,   783,   784,   785,   786,
     787,   788,   789,   790,   791,   792,   793,   794,   795,   796,
     797,   798,   799,   800,   801,   802,   803,   804,   805,   809,
     823,   824,   829,   843,   850,   860,   859,   875,   877,   881,
     882,   885,   897,   908,   907,   918,   919,   922,   927,   932,
     937,   942,   946,   951,   955,   959,   963,   967,   972,   976,
     980,   996,  1000,  1012,  1011,  1035,  1034,  1054,  1053,  1066,
    1065,  1081,  1082,  1083,  1089,  1098,  1099,  1099,  1103,  1105,
    1104,  1107,  1106,  1112,  1124,  1111,  1132,  1133,  1136,  1137,
    1140,  1141,  1144,  1145,  1148,  1149,  1152,  1153,  1156,  1159,
    1160,  1162,  1164,  1167,  1168,  1171,  1172,  1173,  1176,  1177,
    1178,  1179,  1180,  1181,  1182,  1183,  1184,  1185,  1186,  1187,
    1188,  1189,  1190,  1191,  1192,  1205,  1206,  1207,  1208,  1210,
    1213,  1230,  1246,  1256,  1257,  1258,  1259,  1262,  1263,  1264,
    1267,  1268,  1269,  1272,  1273,  1276,  1277,  1280,  1281,  1282,
    1285,  1286,  1290,  1291,  1295,  1296,  1303,  1309,  1317,  1331,
    1335,  1341,  1343,  1347,  1351,  1352,  1356,  1361,  1360,  1382,
    1383,  1384,  1385,  1387,  1389,  1391,  1393,  1395,  1398,  1401,
    1404,  1407,  1409,  1412,  1415,  1416,  1417,  1418,  1431,  1432,
    1434,  1436,  1448,  1450,  1452,  1454,  1455,  1456,  1457,  1458,
    1459,  1461,  1463,  1465,  1465,  1467,  1467,  1469,  1470,  1479,
    1480,  1481,  1482,  1483,  1484,  1485,  1486,  1490,  1494,  1495,
    1499,  1500,  1504,  1505,  1506,  1507,  1508,  1512,  1513,  1514,
    1515,  1516,  1519,  1521,  1522,  1526,  1527,  1528,  1531,  1538,
    1539,  1542,  1543,  1546,  1547,  1548,  1551,  1552,  1555,  1556,
    1559,  1560,  1563,  1564,  1567,  1568,  1569,  1570,  1572,  1573,
    1579,  1585,  1591,  1597,  1598,  1599,  1615,  1616,  1620,  1621,
    1625,  1633,  1637,  1638,  1642,  1651,  1655,  1656,  1659,  1669,
    1670,  1674,  1675,  1678,  1679,  1682,  1683,  1684,  1685,  1693,
    1695,  1697,  1702,  1701,  1713,  1714,  1717,  1718,  1722,  1723,
    1726,  1727,  1730,  1731,  1732,  1733,  1734,  1737,  1738,  1739,
    1740,  1741,  1744,  1745,  1746,  1758,  1759,  1762,  1763,  1766,
    1767,  1771,  1772,  1773,  1776,  1777,  1778,  1779,  1792,  1793,
    1794,  1797,  1798,  1802,  1805,  1806,  1809,  1810,  1825,  1826,
    1829,  1830,  1833,  1834,  1842,  1841,  1867,  1866,  1880,  1881,
    1884,  1885,  1886,  1887,  1888,  1891,  1899,  1900,  1906,  1908,
    1907,  1916,  1926,  1915,  1938,  1946,  1947,  1955,  1963,  1964,
    1965,  1972,  1980,  1993,  2014,  2020,  2028,  2029,  2032,  2033,
    2037,  2038,  2039,  2042,  2043,  2044,  2047,  2048,  2049,  2050,
    2058,  2057,  2068,  2076,  2075,  2085,  2095,  2103,  2104,  2111,
    2111,  2117,  2118,  2122,  2123,  2124,  2128,  2129,  2145,  2146,
    2151,  2150,  2161,  2160,  2171,  2170,  2180,  2181,  2182,  2187,
    2186,  2198,  2199,  2202,  2203,  2206,  2207,  2208,  2212,  2211,
    2224,  2223,  2234,  2235,  2238,  2239,  2242,  2243,  2244,  2245,
    2246,  2250,  2249,  2261,  2262,  2263,  2268,  2267,  2276,  2277,
    2280,  2292,  2301,  2302,  2305,  2318,  2319,  2324,  2323,  2333,
    2334,  2337,  2350,  2350,  2360,  2361,  2370,  2371,  2380,  2390,
    2392,  2395,  2415,  2419,  2418,  2438,  2446,  2438,  2452,  2453,
    2454,  2455,  2456,  2459,  2461,  2468,  2470,  2473,  2474,  2477,
    2478,  2484,  2493,  2494,  2495,  2501,  2507,  2508,  2512,  2523,
    2525,  2531,  2541,  2542,  2543,  2553,  2564,  2567,  2570,  2571,
    2574,  2575,  2576,  2577,  2578,  2582,  2583,  2587,  2588,  2591,
    2592,  2593,  2594,  2595,  2596,  2599,  2600,  2605,  2607,  2609,
    2611,  2615,  2617,  2619,  2620,  2621,  2622,  2623,  2628,  2630,
    2632,  2633,  2635,  2636,  2637,  2638,  2639,  2643,  2644,  2645,
    2646,  2647,  2648,  2649,  2650,  2651,  2652,  2653,  2654,  2655,
    2657,  2663,  2665,  2667,  2668,  2669,  2670,  2671,  2676,  2678,
    2680,  2681,  2683,  2684,  2685,  2686,  2687,  2691,  2692,  2693,
    2694,  2695,  2696,  2697,  2698,  2699,  2700,  2701,  2702,  2703,
    2705,  2707,  2711,  2713,  2715,  2717,  2721,  2723,  2725,  2726,
    2727,  2728,  2733,  2735,  2737,  2738,  2740,  2741,  2742,  2743,
    2744,  2748,  2749,  2750,  2751,  2752,  2753,  2754,  2755,  2756,
    2757,  2758,  2759,  2760,  2762,  2764,  2767,  2771,  2772,  2779,
    2780,  2781,  2786,  2791,  2802,  2803,  2804,  2805,  2806,  2810,
    2814,  2815,  2820,  2825,  2826,  2827,  2828,  2832,  2833,  2837,
    2843,  2845,  2851,  2853,  2855,  2857,  2868,  2879,  2890,  2901,
    2903,  2905,  2907,  2909,  2911,  2913,  2915,  2917,  2919,  2921,
    2926,  2928,  2930,  2935,  2937,  2939,  2941,  2946,  2948,  2950,
    2952,  2954,  2959,  2960,  2962,  2964,  2966,  2968,  2970,  2972,
    2974,  2976,  2978,  2980,  2982,  2986,  2988,  2998,  3000,  3002,
    3004,  3006,  3009,  3018,  3023,  3028,  3030,  3032,  3034,  3036,
    3038,  3040,  3042,  3047,  3052,  3054,  3056,  3058,  3060,  3062,
    3064,  3070,  3072,  3074,  3076,  3078,  3080,  3082,  3084,  3085,
    3087,  3089,  3091,  3093,  3095,  3097,  3099,  3101,  3103,  3105,
    3107,  3109,  3111,  3113,  3115,  3117,  3119,  3121,  3123,  3125,
    3132,  3139,  3146,  3153,  3160,  3167,  3171,  3176,  3178,  3180,
    3182,  3184,  3186,  3191,  3193,  3195,  3197,  3199,  3204,  3208,
    3210,  3212,  3214,  3216,  3220,  3223,  3226,  3228,  3230,  3232,
    3234,  3236,  3238,  3241,  3244,  3246,  3248,  3250,  3252,  3254,
    3257,  3259,  3261,  3263,  3268,  3269,  3270,  3274,  3275,  3278,
    3280,  3282,  3284,  3286,  3288,  3291,  3293,  3290,  3296,  3298,
    3300,  3302,  3304,  3306,  3309,  3308,  3320,  3321,  3324,  3325,
    3330,  3333,  3345,  3344,  3360,  3361,  3362,  3363,  3364,  3365,
    3366,  3367,  3368,  3369,  3373,  3373,  3378,  3379,  3382,  3383,
    3386,  3386,  3391,  3392,  3395,  3396,  3399,  3400,  3403,  3403,
    3408,  3414,  3422,  3423,  3424,  3425,  3427,  3431,  3429,  3439,
    3442,  3441,  3449,  3455,  3458,  3457,  3465,  3471,  3475,  3476,
    3477,  3481,  3481,  3497,  3499,  3511,  3514,  3515,  3531,  3549,
    3531,  3556,  3557,  3560,  3561,  3567,  3574,  3582,  3582,  3588,
    3589,  3593,  3597,  3601,  3607,  3616,  3624,  3625,  3626,  3627,
    3628,  3629,  3630,  3631,  3632,  3633,  3634,  3635,  3636,  3637,
    3638,  3639,  3640,  3641,  3645,  3646,  3647,  3648,  3651,  3653,
    3654,  3657,  3658,  3661,  3663,  3667,  3669,  3668,  3682,  3685,
    3684,  3699,  3701,  3711,  3713,  3716,  3718,  3722,  3723,  3736,
    3753,  3755,  3759,  3758,  3773,  3775,  3779,  3780,  3781,  3786,
    3792,  3796,  3797,  3801,  3805,  3812,  3819,  3831,  3835,  3843,
    3844,  3845,  3846,  3847,  3851,  3852,  3853,  3854,  3855,  3858,
    3861,  3860,  3881,  3882,  3885,  3886,  3889,  3901,  3901,  3911,
    3912,  3915,  3925,  3924,  3933,  3945,  3956,  3955,  3972,  3979,
    3979,  3990,  3997,  4004,  4003,  4015,  4016,  4019,  4027,  4028,
    4032,  4033,  4041,  4051,  4040,  4061,  4069,  4074,  4060,  4079,
    4080,  4081,  4082,  4086,  4087,  4090,  4091,  4094,  4103,  4104,
    4105,  4107,  4106,  4116,  4117,  4118,  4121,  4122,  4125,  4126,
    4127,  4127,  4128,  4128,  4132,  4133,  4136,  4138,  4141,  4149,
    4150,  4154,  4155,  4160,  4159,  4172,  4173,  4176,  4181,  4189,
    4190,  4193,  4195,  4195,  4203,  4212,  4202,  4233,  4234,  4237,
    4244,  4245,  4248,  4257,  4258,  4264,  4263,  4277,  4276,  4285,
    4284,  4288,  4287,  4294,  4295,  4298,  4304,  4315,  4316,  4320,
    4321,  4324,  4325,  4326,  4329,  4338,  4340,  4345,  4344,  4355,
    4357,  4363,  4370,  4377,  4376,  4379,  4387,  4397,  4401,  4406,
    4405,  4410,  4418,  4423,  4429,  4434,  4439,  4441,  4443,  4445,
    4447,  4449,  4451,  4453,  4459,  4461,  4463,  4465,  4467,  4490,
    4497,  4503,  4509,  4513,  4519,  4530,  4543,  4544,  4546,  4548,
    4551,  4552,  4554,  4556,  4561,  4562,  4565,  4566,  4569,  4570,
    4573,  4574,  4580,  4579,  4590,  4589,  4599,  4600,  4603,  4604,
    4608,  4609,  4610,  4618,  4617,  4628,  4629,  4632,  4632,  4633,
    4634,  4635,  4636,  4637,  4638,  4639,  4640,  4641,  4642,  4645,
    4646,  4650,  4649,  4658,  4659,  4662,  4663,  4664,  4668,  4667,
    4676,  4680,  4685,  4706,  4720,  4730,  4729,  4748,  4756,  4762,
    4763,  4766,  4767,  4768,  4772,  4773,  4774,  4776,  4778,  4781,
    4782,  4785,  4790,  4797,  4802,  4808,  4810,  4813,  4814,  4817,
    4822,  4828,  4830,  4839,  4844,  4846,  4848,  4853,  4855,  4869,
    4892,  4893,  4894,  4903,  4904,  4905,  4907,  4908,  4909,  4910,
    4924,  4925,  4926,  4929,  4930,  4931,  4932,  4933,  4941,  4942,
    4945,  4950,  4960,  4963,  4971,  4987,  5003,  5026,  5027,  5028,
    5031,  5032,  5033,  5037,  5041,  5042,  5067,  5079,  5092,  5093,
    5102,  5103,  5104,  5107,  5116,  5123,  5145,  5146,  5147,  5148,
    5149,  5150,  5151,  5152,  5153,  5154,  5155,  5156,  5157,  5158,
    5159,  5160,  5161,  5162,  5163,  5164,  5165,  5166,  5167,  5168,
    5169,  5170,  5171,  5172,  5173,  5174,  5175,  5176,  5177,  5178,
    5179,  5180,  5181,  5182,  5183,  5184,  5185,  5186,  5187,  5188,
    5189,  5190,  5191,  5192,  5193,  5194,  5195,  5196,  5197,  5198,
    5199,  5200,  5201,  5202,  5203,  5204,  5205,  5206,  5207,  5208,
    5209,  5210,  5211,  5212,  5213,  5214,  5215,  5216,  5217,  5218,
    5219,  5220,  5221,  5222,  5223,  5224,  5225,  5226,  5227,  5228,
    5229,  5230,  5231,  5232,  5233,  5234,  5235,  5236,  5237,  5238,
    5239,  5240,  5241,  5242,  5243,  5244,  5245,  5246,  5247,  5248,
    5249,  5250,  5251,  5252,  5253,  5254,  5255,  5256,  5257,  5258,
    5259,  5260,  5261,  5262,  5263,  5264,  5265,  5266,  5267,  5268,
    5269,  5270,  5271,  5272,  5273,  5274,  5275,  5276,  5277,  5278,
    5279,  5280,  5281,  5282,  5283,  5284,  5285,  5286,  5287,  5288,
    5289,  5290,  5291,  5292,  5293,  5294,  5295,  5296,  5297,  5298,
    5299,  5300,  5301,  5302,  5303,  5304,  5305,  5306,  5307,  5308,
    5309,  5310,  5311,  5312,  5313,  5314,  5315,  5316,  5317,  5318,
    5319,  5320,  5321,  5322,  5323,  5324,  5325,  5326,  5327,  5328,
    5329,  5330,  5331,  5332,  5333,  5334,  5335,  5336,  5337,  5338,
    5339,  5340,  5341,  5342,  5343,  5344,  5345,  5346,  5347,  5348,
    5349,  5350,  5351,  5352,  5353,  5360,  5359,  5373,  5374,  5377,
    5378,  5381,  5382,  5386,  5387,  5388,  5389,  5393,  5394,  5398,
    5399,  5400,  5401,  5405,  5406,  5407,  5408,  5412,  5418,  5432,
    5436,  5442,  5449,  5462,  5472,  5479,  5494,  5509,  5523,  5524,
    5525,  5526,  5530,  5531,  5538,  5547,  5548,  5549,  5550,  5551,
    5559,  5558,  5567,  5568,  5571,  5572,  5575,  5583,  5584,  5585,
    5586,  5590,  5599,  5606,  5614,  5613,  5627,  5628,  5632,  5633,
    5637,  5638,  5639,  5640,  5642,  5641,  5652,  5653,  5654,  5655,
    5656,  5663,  5662,  5679,  5682,  5690,  5689,  5707,  5708,  5711,
    5713,  5717,  5718,  5721,  5721,  5722,  5722,  5723,  5723,  5724,
    5724,  5725,  5726,  5727,  5728,  5729,  5730,  5731,  5732,  5733,
    5734,  5735,  5736,  5737,  5738,  5739,  5740,  5741,  5742,  5747,
    5748,  5752,  5753,  5757,  5767,  5777,  5790,  5802,  5814,  5826,
    5838,  5839,  5848,  5873,  5875,  5882,  5886,  5889,  5890,  5893,
    5914,  5915,  5919,  5923,  5927,  5934,  5935,  5938,  5939,  5943,
    5944,  5949,  5954,  5962,  5962,  5966,  5967,  5971,  5974,  5978,
    5984,  5996,  5997,  6002,  6001,  6027,  6028,  6032,  6034,  6034,
    6058,  6059,  6063,  6064,  6065,  6069,  6076,  6083,  6090,  6097,
    6104,  6110,  6125
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "END_OF_INPUT", "CLOSE_SYM",
  "HANDLER_SYM", "LAST_SYM", "NEXT_SYM", "PREV_SYM", "DIV_SYM", "EQ",
  "EQUAL_SYM", "SOUNDS_SYM", "GE", "GT_SYM", "LE", "LT", "NE", "IS",
  "MOD_SYM", "SHIFT_LEFT", "SHIFT_RIGHT", "SET_VAR", "ABORT_SYM", "ADD",
  "AFTER_SYM", "ALTER", "ANALYZE_SYM", "ANY_SYM", "AVG_SYM", "BEGIN_SYM",
  "BINLOG_SYM", "CHANGE", "CLIENT_SYM", "COMMENT_SYM", "COMMIT_SYM",
  "CONSISTENT_SYM", "COUNT_SYM", "CREATE", "CROSS", "CUBE_SYM",
  "DELETE_SYM", "DUAL_SYM", "DO_SYM", "DROP", "EVENTS_SYM", "EXECUTE_SYM",
  "EXPANSION_SYM", "FLUSH_SYM", "HELP_SYM", "INSERT", "RELAY_THREAD",
  "KILL_SYM", "LOAD", "LOCKS_SYM", "LOCK_SYM", "MASTER_SYM", "MAX_SYM",
  "MIN_SYM", "NONE_SYM", "OPTIMIZE", "PURGE", "REPAIR", "REPLICATION",
  "RESET_SYM", "ROLLBACK_SYM", "ROLLUP_SYM", "SAVEPOINT_SYM", "SELECT_SYM",
  "SHOW", "SLAVE", "SNAPSHOT_SYM", "SQL_THREAD", "START_SYM", "STD_SYM",
  "VARIANCE_SYM", "STOP_SYM", "SUM_SYM", "ADDDATE_SYM", "SUPER_SYM",
  "TRUNCATE_SYM", "UNLOCK_SYM", "UNTIL_SYM", "UPDATE_SYM", "ACTION",
  "AGGREGATE_SYM", "ALL", "AND_SYM", "AS", "ASC", "AUTO_INC",
  "AVG_ROW_LENGTH", "BACKUP_SYM", "BERKELEY_DB_SYM", "BINARY", "BIT_SYM",
  "BOOL_SYM", "BOOLEAN_SYM", "BOTH", "BTREE_SYM", "BY", "BYTE_SYM",
  "CACHE_SYM", "CASCADE", "CAST_SYM", "CHARSET", "CHECKSUM_SYM",
  "CHECK_SYM", "COMMITTED_SYM", "COLLATE_SYM", "COLLATION_SYM", "COLUMNS",
  "COLUMN_SYM", "CONCURRENT", "CONSTRAINT", "CONVERT_SYM", "CURRENT_USER",
  "DATABASES", "DATA_SYM", "DEFAULT", "DELAYED_SYM", "DELAY_KEY_WRITE_SYM",
  "DESC", "DESCRIBE", "DES_KEY_FILE", "DISABLE_SYM", "DISCARD", "DISTINCT",
  "DUPLICATE_SYM", "DYNAMIC_SYM", "ENABLE_SYM", "ENCLOSED", "ESCAPED",
  "DIRECTORY_SYM", "ESCAPE_SYM", "EXISTS", "EXTENDED_SYM", "FALSE_SYM",
  "FILE_SYM", "FIRST_SYM", "FIXED_SYM", "FLOAT_NUM", "FORCE_SYM",
  "FOREIGN", "FROM", "FULL", "FULLTEXT_SYM", "GLOBAL_SYM", "GRANT",
  "GRANTS", "GREATEST_SYM", "GROUP", "HAVING", "HASH_SYM", "HEX_NUM",
  "HIGH_PRIORITY", "HOSTS_SYM", "IDENT", "IDENT_QUOTED", "IGNORE_SYM",
  "IMPORT", "INDEX_SYM", "INDEXES", "INFILE", "INNER_SYM", "INNOBASE_SYM",
  "INTO", "IN_SYM", "ISOLATION", "JOIN_SYM", "KEYS", "KEY_SYM", "LEADING",
  "LEAST_SYM", "LEAVES", "LEVEL_SYM", "LEX_HOSTNAME", "LIKE", "LINES",
  "LOCAL_SYM", "LOG_SYM", "LOGS_SYM", "LONG_NUM", "LONG_SYM",
  "LOW_PRIORITY", "MASTER_HOST_SYM", "MASTER_USER_SYM",
  "MASTER_LOG_FILE_SYM", "MASTER_LOG_POS_SYM", "MASTER_PASSWORD_SYM",
  "MASTER_PORT_SYM", "MASTER_CONNECT_RETRY_SYM", "MASTER_SERVER_ID_SYM",
  "MASTER_SSL_SYM", "MASTER_SSL_CA_SYM", "MASTER_SSL_CAPATH_SYM",
  "MASTER_SSL_CERT_SYM", "MASTER_SSL_CIPHER_SYM", "MASTER_SSL_KEY_SYM",
  "RELAY_LOG_FILE_SYM", "RELAY_LOG_POS_SYM", "MATCH", "MAX_ROWS",
  "MAX_CONNECTIONS_PER_HOUR", "MAX_QUERIES_PER_HOUR",
  "MAX_UPDATES_PER_HOUR", "MEDIUM_SYM", "MIN_ROWS", "NAMES_SYM",
  "NATIONAL_SYM", "NATURAL", "NDBCLUSTER_SYM", "NEW_SYM", "NCHAR_SYM",
  "NCHAR_STRING", "NVARCHAR_SYM", "NOT", "NO_SYM", "NULL_SYM", "NUM",
  "OFFSET_SYM", "ON", "ONE_SHOT_SYM", "OPEN_SYM", "OPTION", "OPTIONALLY",
  "OR_SYM", "OR_OR_CONCAT", "ORDER_SYM", "OUTER", "OUTFILE", "DUMPFILE",
  "PACK_KEYS_SYM", "PARTIAL", "PRIMARY_SYM", "PRIVILEGES", "PROCESS",
  "PROCESSLIST_SYM", "QUERY_SYM", "RAID_0_SYM", "RAID_STRIPED_SYM",
  "RAID_TYPE", "RAID_CHUNKS", "RAID_CHUNKSIZE", "READ_SYM", "REAL_NUM",
  "REFERENCES", "REGEXP", "RELOAD", "RENAME", "REPEATABLE_SYM",
  "REQUIRE_SYM", "RESOURCES", "RESTORE_SYM", "RESTRICT", "REVOKE",
  "ROWS_SYM", "ROW_FORMAT_SYM", "ROW_SYM", "RTREE_SYM", "SET",
  "SEPARATOR_SYM", "SERIAL_SYM", "SERIALIZABLE_SYM", "SESSION_SYM",
  "SIMPLE_SYM", "SHUTDOWN", "SPATIAL_SYM", "SSL_SYM", "STARTING",
  "STATUS_SYM", "STORAGE_SYM", "STRAIGHT_JOIN", "SUBJECT_SYM", "TABLES",
  "TABLE_SYM", "TABLESPACE", "TEMPORARY", "TERMINATED", "TEXT_STRING",
  "TO_SYM", "TRAILING", "TRANSACTION_SYM", "TRUE_SYM", "TYPE_SYM",
  "TYPES_SYM", "FUNC_ARG0", "FUNC_ARG1", "FUNC_ARG2", "FUNC_ARG3",
  "UDF_RETURNS_SYM", "UDF_SONAME_SYM", "UDF_SYM", "UNCOMMITTED_SYM",
  "UNDERSCORE_CHARSET", "UNICODE_SYM", "UNION_SYM", "UNIQUE_SYM", "USAGE",
  "USE_FRM", "USE_SYM", "USING", "VALUE_SYM", "VALUES", "VARIABLES",
  "WHERE", "WITH", "WRITE_SYM", "NO_WRITE_TO_BINLOG", "X509_SYM", "XOR",
  "COMPRESSED_SYM", "ERRORS", "WARNINGS", "ASCII_SYM", "BIGINT",
  "BLOB_SYM", "CHAR_SYM", "CHANGED", "COALESCE", "DATETIME", "DATE_SYM",
  "DECIMAL_SYM", "DOUBLE_SYM", "ENUM", "FAST_SYM", "FLOAT_SYM",
  "GEOMETRY_SYM", "INT_SYM", "LIMIT", "LONGBLOB", "LONGTEXT", "MEDIUMBLOB",
  "MEDIUMINT", "MEDIUMTEXT", "NUMERIC_SYM", "PRECISION", "PREPARE_SYM",
  "DEALLOCATE_SYM", "QUICK", "REAL", "SIGNED_SYM", "SMALLINT",
  "STRING_SYM", "TEXT_SYM", "TIMESTAMP", "TIME_SYM", "TINYBLOB", "TINYINT",
  "TINYTEXT", "ULONGLONG_NUM", "UNSIGNED", "VARBINARY", "VARCHAR",
  "VARYING", "ZEROFILL", "AGAINST", "ATAN", "BETWEEN_SYM", "BIT_AND",
  "BIT_OR", "BIT_XOR", "CASE_SYM", "CONCAT", "CONCAT_WS", "CONVERT_TZ_SYM",
  "CURDATE", "CURTIME", "DATABASE", "DATE_ADD_INTERVAL",
  "DATE_SUB_INTERVAL", "DAY_HOUR_SYM", "DAY_MICROSECOND_SYM",
  "DAY_MINUTE_SYM", "DAY_SECOND_SYM", "DAY_SYM", "DECODE_SYM",
  "DES_ENCRYPT_SYM", "DES_DECRYPT_SYM", "ELSE", "ELT_FUNC", "ENCODE_SYM",
  "ENGINE_SYM", "ENGINES_SYM", "ENCRYPT", "EXPORT_SET", "EXTRACT_SYM",
  "FIELD_FUNC", "FORMAT_SYM", "FOR_SYM", "FROM_UNIXTIME",
  "GEOMCOLLFROMTEXT", "GEOMFROMTEXT", "GEOMFROMWKB", "GEOMETRYCOLLECTION",
  "GROUP_CONCAT_SYM", "GROUP_UNIQUE_USERS", "GET_FORMAT",
  "HOUR_MICROSECOND_SYM", "HOUR_MINUTE_SYM", "HOUR_SECOND_SYM", "HOUR_SYM",
  "IDENTIFIED_SYM", "IF", "INSERT_METHOD", "INTERVAL_SYM",
  "LAST_INSERT_ID", "LEFT", "LINEFROMTEXT", "LINESTRING", "LOCATE",
  "MAKE_SET_SYM", "MASTER_POS_WAIT", "MICROSECOND_SYM",
  "MINUTE_MICROSECOND_SYM", "MINUTE_SECOND_SYM", "MINUTE_SYM", "MODE_SYM",
  "MODIFY_SYM", "MONTH_SYM", "MLINEFROMTEXT", "MPOINTFROMTEXT",
  "MPOLYFROMTEXT", "MULTILINESTRING", "MULTIPOINT", "MULTIPOLYGON",
  "NOW_SYM", "OLD_PASSWORD", "PASSWORD", "POINTFROMTEXT", "POINT_SYM",
  "POLYFROMTEXT", "POLYGON", "POSITION_SYM", "PROCEDURE", "RAND",
  "REPLACE", "RIGHT", "ROUND", "SECOND_SYM", "SECOND_MICROSECOND_SYM",
  "SHARE_SYM", "SUBDATE_SYM", "SUBSTRING", "SUBSTRING_INDEX", "TRIM",
  "UDA_CHAR_SUM", "UDA_FLOAT_SUM", "UDA_INT_SUM", "UDF_CHAR_FUNC",
  "UDF_FLOAT_FUNC", "UDF_INT_FUNC", "UNIQUE_USERS", "UNIX_TIMESTAMP",
  "USER", "UTC_DATE_SYM", "UTC_TIME_SYM", "UTC_TIMESTAMP_SYM", "WEEK_SYM",
  "WHEN_SYM", "WORK_SYM", "YEAR_MONTH_SYM", "YEAR_SYM", "YEARWEEK",
  "BENCHMARK_SYM", "END", "THEN_SYM", "SQL_BIG_RESULT", "SQL_CACHE_SYM",
  "SQL_CALC_FOUND_ROWS", "SQL_NO_CACHE_SYM", "SQL_SMALL_RESULT",
  "SQL_BUFFER_RESULT", "ISSUER_SYM", "CIPHER_SYM", "BEFORE_SYM", "'|'",
  "'&'", "'-'", "'+'", "'*'", "'/'", "'%'", "'^'", "'~'", "NEG", "'('",
  "')'", "','", "'!'", "'{'", "'}'", "'@'", "'.'", "'?'", "$accept",
  "query", "verb_clause", "deallocate", "deallocate_or_drop", "prepare",
  "prepare_src", "execute", "@1", "execute_using", "execute_var_list",
  "execute_var_ident", "help", "change", "@2", "master_defs", "master_def",
  "master_file_def", "create", "@3", "@4", "@5", "@6", "create2",
  "create2a", "@7", "create3", "@8", "@9", "create_select", "@10", "@11",
  "opt_as", "opt_create_database_options", "create_database_options",
  "create_database_option", "opt_table_options", "table_options",
  "table_option", "opt_if_not_exists", "opt_create_table_options",
  "create_table_options_space_separated", "create_table_options",
  "create_table_option", "default_charset", "default_collation",
  "storage_engines", "row_types", "raid_types", "merge_insert_types",
  "opt_select_from", "udf_func_type", "udf_type", "field_list",
  "field_list_item", "column_def", "key_def", "opt_check_constraint",
  "check_constraint", "opt_constraint", "constraint", "field_spec", "@12",
  "type", "@13", "@14", "spatial_type", "char", "nchar", "varchar",
  "nvarchar", "int_type", "real_type", "float_options", "precision",
  "field_options", "field_opt_list", "field_option", "opt_len",
  "opt_precision", "opt_attribute", "opt_attribute_list", "attribute",
  "now_or_signed_literal", "charset", "charset_name",
  "charset_name_or_default", "old_or_new_charset_name",
  "old_or_new_charset_name_or_default", "collation_name", "opt_collate",
  "collation_name_or_default", "opt_default", "opt_binary", "opt_primary",
  "references", "@15", "opt_ref_list", "ref_list", "opt_on_delete",
  "opt_on_delete_list", "opt_on_delete_item", "delete_option", "key_type",
  "constraint_key_type", "key_or_index", "opt_key_or_index",
  "keys_or_index", "opt_unique_or_fulltext", "key_alg",
  "opt_btree_or_rtree", "key_list", "key_part", "opt_ident",
  "opt_component", "string_list", "alter", "@16", "@17", "ident_or_empty",
  "alter_list", "add_column", "alter_list_item", "@18", "@19", "@20",
  "opt_column", "opt_ignore", "opt_restrict", "opt_place", "opt_to",
  "slave", "@21", "@22", "start", "start_transaction_opts",
  "slave_thread_opts", "@23", "slave_thread_opt_list", "slave_thread_opt",
  "slave_until", "slave_until_opts", "restore", "@24", "backup", "@25",
  "checksum", "@26", "opt_checksum_type", "repair", "@27",
  "opt_mi_repair_type", "mi_repair_types", "mi_repair_type", "analyze",
  "@28", "check", "@29", "opt_mi_check_type", "mi_check_types",
  "mi_check_type", "optimize", "@30", "opt_no_write_to_binlog", "rename",
  "@31", "table_to_table_list", "table_to_table", "keycache",
  "keycache_list", "assign_to_keycache", "key_cache_name", "preload",
  "@32", "preload_list", "preload_keys", "cache_keys_spec", "@33",
  "cache_key_list_or_empty", "opt_ignore_leaves", "select", "select_init",
  "select_paren", "select_init2", "@34", "select_part2", "@35", "@36",
  "select_into", "select_from", "select_options", "select_option_list",
  "select_option", "select_lock_type", "select_item_list", "select_item",
  "remember_name", "remember_end", "select_item2", "select_alias",
  "optional_braces", "expr", "comp_op", "all_or_any", "expr_expr",
  "no_in_expr", "no_and_expr", "interval_expr", "simple_expr",
  "geometry_function", "fulltext_options", "udf_expr_list", "sum_expr",
  "@37", "@38", "@39", "opt_distinct", "opt_gconcat_separator",
  "opt_gorder_clause", "in_sum_expr", "@40", "cast_type", "expr_list",
  "@41", "expr_list2", "ident_list_arg", "ident_list", "@42",
  "ident_list2", "opt_expr", "opt_else", "when_list", "@43", "when_list2",
  "join_table_list", "@44", "@45", "@46", "normal_join", "join_table",
  "@47", "select_derived", "select_derived2", "@48", "@49", "opt_outer",
  "opt_key_definition", "key_usage_list", "@50", "key_list_or_empty",
  "key_usage_list2", "using_list", "interval", "date_time_type",
  "table_alias", "opt_table_alias", "opt_all", "where_clause", "@51",
  "having_clause", "@52", "opt_escape", "group_clause", "group_list",
  "olap_opt", "opt_order_clause", "order_clause", "@53", "order_list",
  "order_dir", "opt_limit_clause_init", "opt_limit_clause", "limit_clause",
  "limit_options", "delete_limit_clause", "ULONG_NUM", "ulonglong_num",
  "procedure_clause", "@54", "procedure_list", "procedure_list2",
  "procedure_item", "select_var_list_init", "@55", "select_var_list",
  "select_var_ident", "into", "@56", "do", "@57", "drop", "@58", "@59",
  "table_list", "table_name", "if_exists", "opt_temporary", "insert",
  "@60", "@61", "replace", "@62", "@63", "@64", "insert_lock_option",
  "replace_lock_option", "insert2", "insert_table", "insert_field_spec",
  "@65", "opt_field_spec", "fields", "insert_values", "@66", "@67",
  "values_list", "ident_eq_list", "ident_eq_value", "equal", "opt_equal",
  "no_braces", "@68", "opt_values", "values", "expr_or_default",
  "opt_insert_update", "@69", "update", "@70", "@71", "update_list",
  "update_elem", "insert_update_list", "insert_update_elem",
  "opt_low_priority", "delete", "@72", "single_multi", "@73", "@74", "@75",
  "table_wild_list", "table_wild_one", "opt_wild", "opt_delete_options",
  "opt_delete_option", "truncate", "opt_table_sym", "show", "@76",
  "show_param", "@77", "@78", "show_engine_param", "master_or_binary",
  "opt_storage", "opt_db", "wild", "opt_full", "from_or_in", "binlog_in",
  "binlog_from", "describe", "@79", "@80", "describe_command",
  "opt_extended_describe", "opt_describe_column", "flush", "@81",
  "flush_options", "flush_option", "@82", "opt_table_list", "reset", "@83",
  "reset_options", "reset_option", "purge", "@84", "purge_options",
  "purge_option", "kill", "use", "load", "@85", "opt_local",
  "load_data_lock", "opt_duplicate", "opt_field_term", "field_term_list",
  "field_term", "opt_line_term", "line_term_list", "line_term",
  "opt_ignore_lines", "text_literal", "text_string", "param_marker",
  "signed_literal", "literal", "NUM_literal", "insert_ident", "table_wild",
  "order_ident", "simple_ident", "field_ident", "table_ident",
  "table_ident_nodb", "IDENT_sys", "TEXT_STRING_sys",
  "TEXT_STRING_literal", "ident", "ident_or_text", "user", "keyword",
  "set", "@86", "opt_option", "option_value_list", "option_value_ext",
  "option_type_ext", "option_type", "opt_var_type", "opt_var_ident_type",
  "sys_option_value", "option_value", "internal_variable_name",
  "isolation_types", "text_or_password", "set_expr_or_default", "lock",
  "@87", "table_or_tables", "table_lock_list", "table_lock", "lock_option",
  "unlock", "handler", "@88", "handler_read_or_scan",
  "handler_scan_function", "handler_rkey_function", "@89",
  "handler_rkey_mode", "revoke", "@90", "revoke_command", "grant", "@91",
  "grant_privileges", "opt_privileges", "grant_privilege_list",
  "grant_privilege", "@92", "@93", "@94", "@95", "opt_and", "require_list",
  "require_list_element", "opt_table", "user_list", "grant_user",
  "opt_column_list", "column_list", "column_list_id", "require_clause",
  "grant_options", "grant_option_list", "grant_option", "begin", "@96",
  "opt_work", "commit", "rollback", "savepoint", "union_clause",
  "union_list", "@97", "union_opt", "optional_order_or_limit", "@98",
  "order_or_limit", "union_option", "singlerow_subselect",
  "singlerow_subselect_init", "exists_subselect", "exists_subselect_init",
  "in_subselect", "in_subselect_init", "subselect_start", "subselect_end", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,   636,   637,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
     655,   656,   657,   658,   659,   660,   661,   662,   663,   664,
     665,   666,   667,   668,   669,   670,   671,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   700,   701,   702,   703,   704,
     705,   706,   707,   708,   709,   710,   711,   712,   713,   714,
     715,   716,   717,   718,   719,   720,   721,   722,   723,   724,
     725,   726,   727,   728,   729,   730,   124,    38,    45,    43,
      42,    47,    37,    94,   126,   731,    40,    41,    44,    33,
     123,   125,    64,    46,    63
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned short yyr1[] =
{
       0,   495,   496,   496,   497,   497,   497,   497,   497,   497,
     497,   497,   497,   497,   497,   497,   497,   497,   497,   497,
     497,   497,   497,   497,   497,   497,   497,   497,   497,   497,
     497,   497,   497,   497,   497,   497,   497,   497,   497,   497,
     497,   497,   497,   497,   497,   497,   497,   497,   497,   498,
     499,   499,   500,   501,   501,   503,   502,   504,   504,   505,
     505,   506,   507,   509,   508,   510,   510,   511,   511,   511,
     511,   511,   511,   511,   511,   511,   511,   511,   511,   512,
     512,   512,   512,   514,   513,   515,   513,   516,   513,   517,
     513,   518,   518,   518,   518,   519,   520,   519,   521,   522,
     521,   523,   521,   525,   526,   524,   527,   527,   528,   528,
     529,   529,   530,   530,   531,   531,   532,   532,   533,   534,
     534,   535,   535,   536,   536,   537,   537,   537,   538,   538,
     538,   538,   538,   538,   538,   538,   538,   538,   538,   538,
     538,   538,   538,   538,   538,   538,   538,   538,   538,   538,
     539,   540,   541,   542,   542,   542,   542,   543,   543,   543,
     544,   544,   544,   545,   545,   546,   546,   547,   547,   547,
     548,   548,   549,   549,   550,   550,   551,   551,   551,   551,
     551,   552,   552,   553,   554,   554,   555,   557,   556,   558,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   559,   558,   560,   558,   558,   558,   561,
     561,   561,   561,   561,   561,   561,   561,   562,   563,   563,
     564,   564,   565,   565,   565,   565,   565,   566,   566,   566,
     566,   566,   567,   567,   567,   568,   568,   568,   569,   570,
     570,   571,   571,   572,   572,   572,   573,   573,   574,   574,
     575,   575,   576,   576,   577,   577,   577,   577,   577,   577,
     577,   577,   577,   577,   577,   577,   578,   578,   579,   579,
     580,   580,   581,   581,   582,   582,   583,   583,   584,   585,
     585,   586,   586,   587,   587,   588,   588,   588,   588,   588,
     589,   589,   591,   590,   592,   592,   593,   593,   594,   594,
     595,   595,   596,   596,   596,   596,   596,   597,   597,   597,
     597,   597,   598,   598,   598,   599,   599,   600,   600,   601,
     601,   602,   602,   602,   603,   603,   603,   603,   604,   604,
     604,   605,   605,   605,   606,   606,   607,   607,   608,   608,
     609,   609,   610,   610,   612,   611,   613,   611,   614,   614,
     615,   615,   615,   615,   615,   616,   617,   617,   617,   618,
     617,   619,   620,   617,   617,   617,   617,   617,   617,   617,
     617,   617,   617,   617,   617,   617,   621,   621,   622,   622,
     623,   623,   623,   624,   624,   624,   625,   625,   625,   625,
     627,   626,   626,   628,   626,   626,   629,   630,   630,   632,
     631,   633,   633,   634,   634,   634,   635,   635,   636,   636,
     638,   637,   640,   639,   642,   641,   643,   643,   643,   645,
     644,   646,   646,   647,   647,   648,   648,   648,   650,   649,
     652,   651,   653,   653,   654,   654,   655,   655,   655,   655,
     655,   657,   656,   658,   658,   658,   660,   659,   661,   661,
     662,   663,   664,   664,   665,   666,   666,   668,   667,   669,
     669,   670,   672,   671,   673,   673,   674,   674,   675,   676,
     676,   677,   677,   679,   678,   681,   682,   680,   683,   683,
     683,   683,   683,   684,   684,   685,   685,   686,   686,   687,
     687,   687,   687,   687,   687,   687,   687,   687,   687,   688,
     688,   688,   689,   689,   689,   690,   691,   692,   693,   693,
     694,   694,   694,   694,   694,   695,   695,   696,   696,   697,
     697,   697,   697,   697,   697,   698,   698,   699,   699,   699,
     699,   699,   699,   699,   699,   699,   699,   699,   699,   699,
     699,   699,   699,   699,   699,   699,   699,   699,   699,   699,
     699,   699,   699,   699,   699,   699,   699,   699,   699,   699,
     699,   700,   700,   700,   700,   700,   700,   700,   700,   700,
     700,   700,   700,   700,   700,   700,   700,   700,   700,   700,
     700,   700,   700,   700,   700,   700,   700,   700,   700,   700,
     700,   700,   701,   701,   701,   701,   701,   701,   701,   701,
     701,   701,   701,   701,   701,   701,   701,   701,   701,   701,
     701,   701,   701,   701,   701,   701,   701,   701,   701,   701,
     701,   701,   701,   701,   701,   701,   702,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   703,
     703,   703,   703,   703,   703,   703,   703,   703,   703,   704,
     704,   704,   704,   704,   704,   704,   704,   704,   704,   704,
     704,   704,   704,   704,   704,   704,   704,   704,   704,   704,
     704,   704,   704,   704,   705,   705,   705,   706,   706,   707,
     707,   707,   707,   707,   707,   708,   709,   707,   707,   707,
     707,   707,   707,   707,   710,   707,   711,   711,   712,   712,
     713,   713,   715,   714,   716,   716,   716,   716,   716,   716,
     716,   716,   716,   716,   718,   717,   719,   719,   720,   720,
     722,   721,   723,   723,   724,   724,   725,   725,   727,   726,
     728,   728,   729,   729,   729,   729,   729,   730,   729,   729,
     731,   729,   729,   729,   732,   729,   729,   729,   733,   733,
     733,   735,   734,   734,   734,   734,   736,   736,   738,   739,
     737,   740,   740,   741,   741,   741,   741,   743,   742,   744,
     744,   745,   745,   745,   746,   746,   747,   747,   747,   747,
     747,   747,   747,   747,   747,   747,   747,   747,   747,   747,
     747,   747,   747,   747,   748,   748,   748,   748,   749,   749,
     749,   750,   750,   751,   751,   752,   753,   752,   754,   755,
     754,   756,   756,   757,   757,   758,   758,   759,   759,   759,
     760,   760,   762,   761,   763,   763,   764,   764,   764,   765,
     765,   766,   766,   767,   768,   768,   768,   769,   769,   770,
     770,   770,   770,   770,   771,   771,   771,   771,   771,   772,
     773,   772,   774,   774,   775,   775,   776,   778,   777,   779,
     779,   780,   782,   781,   781,   781,   784,   783,   785,   786,
     785,   785,   785,   787,   785,   788,   788,   789,   790,   790,
     791,   791,   793,   794,   792,   796,   797,   798,   795,   799,
     799,   799,   799,   800,   800,   801,   801,   802,   803,   803,
     803,   804,   803,   805,   805,   805,   806,   806,   807,   807,
     808,   807,   809,   807,   810,   810,   811,   811,   812,   813,
     813,   814,   814,   816,   815,   817,   817,   818,   818,   819,
     819,   820,   821,   820,   823,   824,   822,   825,   825,   826,
     827,   827,   828,   829,   829,   831,   830,   833,   832,   834,
     832,   835,   832,   836,   836,   837,   837,   838,   838,   839,
     839,   840,   840,   840,   841,   842,   842,   844,   843,   845,
     845,   845,   845,   846,   845,   845,   845,   845,   845,   847,
     845,   845,   845,   845,   845,   845,   845,   845,   845,   845,
     845,   845,   845,   845,   845,   845,   845,   845,   845,   845,
     845,   845,   845,   845,   848,   848,   849,   849,   850,   850,
     851,   851,   852,   852,   853,   853,   854,   854,   855,   855,
     856,   856,   858,   857,   859,   857,   860,   860,   861,   861,
     862,   862,   862,   864,   863,   865,   865,   867,   866,   866,
     866,   866,   866,   866,   866,   866,   866,   866,   866,   868,
     868,   870,   869,   871,   871,   872,   872,   872,   874,   873,
     875,   876,   876,   877,   878,   880,   879,   879,   879,   881,
     881,   882,   882,   882,   883,   883,   883,   884,   884,   885,
     885,   886,   886,   886,   886,   887,   887,   888,   888,   889,
     889,   890,   890,   891,   891,   891,   891,   892,   892,   893,
     894,   894,   894,   895,   895,   895,   895,   895,   895,   895,
     895,   895,   895,   896,   896,   896,   896,   896,   897,   897,
     898,   898,   899,   900,   900,   900,   900,   901,   901,   901,
     902,   902,   902,   903,   904,   904,   905,   906,   907,   907,
     908,   908,   908,   909,   909,   909,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   910,   910,   910,   910,   910,
     910,   910,   910,   910,   910,   912,   911,   913,   913,   914,
     914,   915,   915,   916,   916,   916,   916,   917,   917,   918,
     918,   918,   918,   919,   919,   919,   919,   920,   920,   921,
     921,   921,   921,   921,   921,   922,   922,   922,   923,   923,
     923,   923,   924,   924,   924,   925,   925,   925,   925,   925,
     927,   926,   928,   928,   929,   929,   930,   931,   931,   931,
     931,   932,   933,   933,   934,   933,   935,   935,   936,   936,
     937,   937,   937,   937,   938,   937,   939,   939,   939,   939,
     939,   941,   940,   942,   942,   944,   943,   945,   945,   946,
     946,   947,   947,   949,   948,   950,   948,   951,   948,   952,
     948,   948,   948,   948,   948,   948,   948,   948,   948,   948,
     948,   948,   948,   948,   948,   948,   948,   948,   948,   953,
     953,   954,   954,   955,   955,   955,   956,   956,   956,   956,
     957,   957,   958,   958,   958,   959,   959,   960,   960,   961,
     962,   962,   962,   962,   962,   963,   963,   964,   964,   965,
     965,   965,   965,   967,   966,   968,   968,   969,   970,   970,
     971,   972,   972,   974,   973,   975,   975,   976,   977,   976,
     978,   978,   979,   979,   979,   980,   981,   982,   983,   984,
     985,   986,   987
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     4,     1,     2,     0,     4,     0,     2,     3,
       1,     2,     2,     0,     5,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     0,     7,     0,    11,     0,     6,     0,
       9,     2,     2,     2,     4,     4,     0,     4,     0,     0,
       5,     0,     7,     0,     0,     6,     0,     1,     0,     1,
       1,     2,     1,     1,     0,     1,     1,     2,     1,     0,
       3,     0,     1,     1,     2,     1,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     5,     1,     1,     3,     4,     4,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     0,     1,     1,     1,     1,
       1,     3,     1,     1,     2,     2,     6,     7,     8,     2,
       2,     0,     1,     2,     0,     1,     2,     0,     4,     3,
       3,     3,     2,     1,     1,     5,     2,     4,     1,     4,
       1,     5,     4,     4,     3,     1,     1,     2,     1,     1,
       2,     1,     1,     1,     2,     3,     2,     3,     2,     2,
       3,     3,     3,     0,     6,     0,     6,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     2,     1,     2,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     2,     0,     3,     1,     5,     0,
       1,     2,     1,     1,     1,     1,     0,     3,     0,     1,
       0,     1,     2,     1,     1,     2,     2,     4,     1,     3,
       2,     1,     2,     2,     1,     2,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       2,     1,     1,     0,     1,     0,     1,     1,     1,     2,
       0,     1,     0,     4,     1,     4,     3,     1,     0,     1,
       2,     1,     3,     3,     2,     2,     2,     1,     1,     2,
       2,     2,     1,     2,     2,     2,     2,     1,     1,     0,
       1,     1,     1,     1,     0,     1,     1,     1,     0,     2,
       2,     1,     1,     1,     4,     2,     1,     4,     0,     1,
       0,     2,     1,     3,     0,     6,     0,     5,     0,     1,
       0,     2,     2,     1,     3,     2,     3,     2,     4,     0,
       6,     0,     0,     8,     4,     4,     3,     3,     2,     2,
       6,     5,     3,     5,     1,     1,     0,     1,     0,     1,
       0,     1,     1,     0,     2,     1,     0,     1,     1,     1,
       0,     5,     3,     0,     5,     3,     3,     0,     3,     0,
       2,     1,     3,     0,     1,     1,     0,     2,     1,     3,
       0,     6,     0,     6,     0,     5,     0,     1,     1,     0,
       6,     0,     1,     1,     2,     1,     1,     1,     0,     6,
       0,     5,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     0,     6,     0,     1,     1,     0,     4,     1,     3,
       3,     5,     1,     3,     2,     1,     1,     0,     6,     1,
       3,     3,     0,     2,     0,     4,     0,     2,     1,     2,
       4,     2,     3,     0,     3,     0,     0,     6,     1,     1,
       1,     2,     2,     8,     3,     0,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       2,     4,     3,     1,     1,     4,     0,     0,     1,     1,
       0,     2,     2,     1,     1,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     6,     3,
       4,     5,     6,     3,     3,     3,     3,     4,     4,     5,
       3,     4,     3,     4,     3,     3,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       4,     5,     6,     3,     3,     3,     3,     4,     4,     5,
       3,     4,     3,     4,     3,     3,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       4,     1,     5,     6,     3,     4,     5,     6,     3,     3,
       3,     4,     4,     5,     3,     4,     3,     4,     3,     3,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     4,     1,     2,     1,     3,     1,
       1,     4,     2,     5,     1,     2,     2,     2,     2,     2,
       3,     5,     6,     2,     1,     4,     7,     4,     2,     6,
       6,     6,     6,     4,     4,     3,     4,     6,     8,     6,
       8,     4,     6,     4,     4,     4,     4,     4,     6,     8,
       2,     2,     4,     2,     7,     7,     3,     4,     4,     6,
       6,     4,     6,     6,     6,     4,     6,     4,     6,     8,
      10,    12,     6,     4,     6,     6,     1,     6,     4,     8,
      10,     4,     1,     3,     4,     6,     6,     8,     6,     6,
       4,     6,     6,     8,     4,     4,     6,     4,     2,     4,
       4,     4,     6,     4,     3,     8,     6,     4,     6,     6,
       8,     4,     8,     6,     8,     6,     8,     4,     4,     6,
       4,     7,     7,     7,     6,     6,     6,     6,     6,     4,
       4,     4,     4,     4,     4,    10,     3,     4,     3,     2,
       2,     2,     4,     6,     4,     4,     6,     6,     6,     4,
       6,     4,     6,     4,     4,     4,     4,     6,     4,     6,
       4,     6,     4,     4,     6,     4,     6,     4,     6,     4,
       4,     6,     4,     6,     0,     3,     3,     0,     1,     4,
       4,     4,     4,     5,     4,     0,     0,     7,    10,     4,
       4,     4,     4,     4,     0,     8,     0,     1,     0,     2,
       0,     1,     0,     3,     2,     3,     2,     1,     2,     1,
       2,     1,     1,     1,     0,     2,     1,     3,     1,     3,
       0,     2,     1,     3,     0,     1,     0,     2,     0,     2,
       3,     5,     1,     3,     3,     3,     5,     0,     8,     7,
       0,    10,     6,     7,     0,    10,     6,     4,     1,     2,
       2,     0,     4,    10,     5,     3,     2,     3,     0,     0,
       5,     0,     1,     0,     2,     2,     2,     0,     5,     0,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       1,     0,     2,     0,     1,     0,     0,     3,     0,     0,
       3,     2,     0,     0,     4,     4,     2,     0,     2,     2,
       0,     1,     0,     4,     4,     2,     0,     1,     1,     0,
       1,     0,     1,     2,     1,     3,     3,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       0,     6,     0,     1,     3,     1,     2,     0,     2,     3,
       1,     2,     0,     6,     3,     2,     0,     3,     6,     0,
       6,     4,     3,     0,     4,     1,     3,     1,     0,     2,
       0,     1,     0,     0,     8,     0,     0,     0,     7,     0,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     3,
       4,     0,     3,     0,     3,     2,     3,     1,     2,     2,
       0,     3,     0,     5,     3,     1,     3,     1,     3,     1,
       1,     0,     1,     0,     4,     0,     1,     3,     1,     1,
       1,     0,     0,     6,     0,     0,    11,     3,     1,     3,
       3,     1,     3,     0,     1,     0,     4,     0,     6,     0,
       5,     0,     6,     1,     3,     3,     5,     0,     2,     0,
       2,     1,     1,     1,     3,     0,     1,     0,     3,     2,
       3,     4,     4,     0,     4,     6,    16,     2,     2,     0,
       6,     4,     2,     2,     2,     1,     5,     5,     2,     2,
       2,     2,     2,     3,     2,     2,     2,     1,     1,     3,
       4,     3,     2,     2,     1,     1,     1,     1,     0,     1,
       0,     2,     0,     2,     0,     1,     1,     1,     0,     2,
       0,     2,     0,     4,     0,     4,     1,     1,     0,     1,
       0,     1,     1,     0,     4,     3,     1,     0,     3,     4,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     0,     3,     3,     1,     1,     1,     2,     0,     3,
       3,     2,     2,     2,     2,     0,    15,     5,     4,     0,
       1,     0,     1,     1,     0,     1,     1,     0,     2,     2,
       1,     3,     4,     3,     3,     0,     2,     2,     1,     3,
       3,     0,     3,     1,     1,     2,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     1,     1,     3,     4,     5,     1,     3,     2,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     1,     1,
       3,     2,     2,     1,     1,     1,     1,     0,     1,     0,
       1,     1,     1,     0,     2,     2,     2,     3,     4,     4,
       6,     2,     3,     3,     5,     1,     3,     3,     2,     2,
       2,     1,     1,     4,     4,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     3,     3,     1,     1,     2,
       2,     2,     4,     3,     0,     7,     1,     2,     1,     1,
       1,     1,     1,     1,     0,     5,     1,     1,     1,     1,
       1,     0,     3,     5,     7,     0,     9,     1,     2,     0,
       1,     1,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     3,     2,     2,     2,     0,
       1,     3,     1,     2,     2,     2,     1,     3,     3,     1,
       1,     3,     4,     5,     1,     0,     3,     3,     1,     1,
       0,     2,     2,     2,     2,     0,     2,     2,     1,     2,
       2,     2,     2,     0,     3,     0,     1,     1,     1,     4,
       2,     0,     1,     0,     4,     1,     1,     0,     0,     2,
       2,     1,     0,     1,     1,     3,     1,     3,     1,     3,
       1,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short yydefact[] =
{
       0,     2,     0,   398,   463,  1643,     0,  1647,   114,  1085,
    1006,  1020,     0,   463,     0,  1022,     0,     0,     0,   463,
    1198,   463,  1191,  1648,     0,   495,  1107,     0,     0,     0,
    1105,     0,  1074,     0,     0,     0,     0,  1166,  1167,  1575,
       0,     0,  1571,  1497,     0,     0,    50,  1025,     0,     0,
       0,    13,     0,    30,    18,    22,     8,    12,     4,    43,
      44,    36,     6,    10,    33,     5,     9,    27,    32,    28,
      29,    40,   488,    16,    17,    23,    34,    47,    14,    45,
      42,    15,  1168,    19,    35,    31,    24,    48,    25,    41,
      26,    46,    21,    37,    20,     7,    11,    38,    39,  1311,
    1356,  1369,  1409,  1424,  1460,  1288,  1291,  1295,  1297,  1299,
    1310,  1313,  1315,  1318,  1319,  1329,  1339,  1340,  1341,  1350,
    1358,  1368,  1374,  1377,  1412,  1437,  1439,  1440,  1443,  1444,
    1449,  1458,  1459,  1464,  1465,  1467,  1287,  1472,  1477,  1486,
    1286,  1290,  1293,  1294,  1296,  1298,  1300,  1301,  1302,  1304,
    1303,  1305,  1307,  1308,  1314,  1312,  1317,  1320,  1325,  1326,
    1344,  1328,  1331,  1332,  1345,  1327,  1338,  1342,  1347,  1348,
    1349,  1346,  1355,  1354,  1357,  1359,  1274,  1275,  1362,  1363,
    1366,  1364,  1370,  1371,  1373,  1375,  1378,  1382,  1380,  1381,
    1383,  1379,  1385,  1384,  1386,  1387,  1388,  1389,  1390,  1391,
    1434,  1435,  1376,  1392,  1393,  1394,  1395,  1398,  1405,  1406,
    1408,  1410,  1407,  1413,  1411,  1414,  1416,  1417,  1330,  1418,
    1419,  1425,  1426,  1427,  1429,  1432,  1433,  1430,  1431,  1436,
    1438,  1441,  1442,  1445,  1446,  1447,  1448,  1451,  1452,  1453,
    1455,  1457,  1466,  1468,  1471,  1473,  1474,  1476,  1480,  1481,
    1482,  1483,  1484,  1485,  1488,  1490,  1489,  1493,  1316,  1337,
    1491,  1292,  1306,  1321,  1322,  1334,  1343,  1351,  1423,  1324,
    1428,  1454,  1469,  1475,  1478,  1479,  1289,  1323,  1335,  1336,
    1352,  1353,  1360,  1361,  1367,  1372,  1396,  1397,  1400,  1399,
    1401,  1402,  1403,  1404,  1415,  1420,  1421,  1422,  1450,  1456,
    1470,  1487,  1492,  1494,  1333,  1461,  1463,  1462,  1365,  1309,
       0,     0,     0,  1278,  1273,  1279,   399,   368,     0,   465,
     464,     0,  1645,     0,   166,   346,   347,   118,   345,   119,
       0,   115,   116,     0,     0,  1099,   854,     0,  1021,     0,
    1018,  1013,     0,    55,  1173,  1282,  1276,  1281,  1280,    62,
    1029,     0,  1295,     0,     0,     0,     0,     0,     0,     0,
    1287,  1477,     0,     0,  1307,  1312,     0,   535,     0,     0,
    1246,  1257,     0,  1248,     0,     0,  1254,   860,  1234,     0,
    1245,  1253,  1256,  1447,  1277,  1247,     0,     0,     0,     0,
       0,     0,  1292,     0,     0,  1322,  1478,  1479,  1255,     0,
       0,     0,     0,   864,     0,     0,     0,   535,   535,     0,
       0,     0,  1323,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1352,     0,     0,
    1353,  1360,     0,     0,     0,     0,     0,  1372,     0,     0,
       0,  1396,  1397,  1401,     0,     0,     0,  1402,  1403,  1404,
     535,  1415,  1420,     0,  1421,     0,  1422,     0,     0,     0,
       0,     0,  1450,  1470,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1487,   535,   535,   535,     0,
    1494,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1239,  1203,   537,   722,   538,   716,   654,  1243,   650,
     649,  1244,   647,  1233,  1263,   664,   495,  1211,     0,     0,
    1543,  1542,  1540,     0,     0,     0,     0,     0,  1650,   489,
     493,   505,  1154,   419,   419,   419,   417,   419,  1106,     0,
    1551,  1083,   432,     0,   434,   450,     0,   466,   430,     0,
    1498,  1495,  1204,     0,  1083,   495,     0,     0,     1,     3,
       0,  1342,  1164,  1162,  1270,  1272,   938,  1553,  1554,     0,
     366,   369,     0,   448,  1646,  1644,    63,     0,     0,   119,
     117,     0,     0,  1103,  1102,  1101,     0,  1099,  1007,     0,
       0,  1012,     0,     0,     0,  1018,    57,     0,  1031,  1032,
    1030,   398,     0,   943,   943,     0,   943,   943,   943,   943,
     943,     0,     0,   668,     0,     0,     0,     0,     0,   693,
       0,     0,   663,   495,     0,     0,     0,   860,     0,   858,
       0,   658,     0,     0,     0,     0,     0,  1249,  1235,     0,
       0,   854,   854,     0,     0,  1250,     0,  1252,     0,  1251,
       0,   943,   943,   943,   865,     0,   854,     0,     0,   690,
       0,   691,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     854,   836,     0,     0,     0,     0,   646,     0,     0,     0,
     854,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     854,   854,   854,     0,   738,     0,     0,     0,     0,     0,
     854,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   854,   854,   854,   854,   854,   854,     0,     0,     0,
     779,   780,   781,     0,     0,     0,     0,   656,   655,   657,
    1671,     0,   659,     0,  1513,   652,     0,     0,   539,     0,
       0,   540,   541,   542,   543,   544,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   916,   917,
     918,   919,   920,   921,   922,   923,   924,   925,   926,   927,
     928,   929,   931,   930,   932,   933,     0,     0,  1236,     0,
    1666,     0,  1212,     0,  1213,  1209,     0,     0,     0,   461,
    1146,  1147,     0,  1199,   439,  1196,  1195,     0,  1192,  1194,
       0,  1651,   518,   511,   510,   509,   513,   517,   515,   516,
     512,   514,   526,   506,   508,     0,     0,     0,  1146,     0,
       0,   289,  1152,     0,  1152,  1155,  1510,  1138,   342,   343,
       0,   341,  1511,  1137,     0,     0,  1125,  1512,  1152,  1149,
    1150,     0,   969,   969,     0,     0,  1152,     0,  1108,     0,
       0,     0,     0,   413,   423,   415,   410,     0,   416,   412,
    1104,  1017,  1084,   398,     0,     0,   472,   482,     0,     0,
    1594,  1595,  1591,  1596,  1597,  1585,     0,     0,  1583,     0,
    1604,  1587,  1579,  1601,     0,  1593,  1600,  1589,  1598,  1599,
    1592,     0,  1577,  1581,     0,     0,  1579,  1572,     0,  1507,
       0,  1034,     0,  1033,   491,     0,  1657,    49,     0,  1170,
     940,   939,     0,  1552,     0,  1271,   303,   364,     0,     0,
       0,    87,     0,    89,   348,     0,  1086,  1089,  1093,  1097,
    1100,   856,   855,     0,  1019,  1011,   535,  1283,  1624,  1014,
    1620,     0,     0,    56,  1186,  1185,  1187,  1181,  1183,  1182,
       0,  1188,  1184,  1543,  1174,  1176,  1177,     0,     0,   944,
       0,   842,   825,     0,   842,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   536,     0,  1668,
       0,     0,     0,     0,     0,     0,   861,   862,     0,   675,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   868,     0,     0,     0,     0,   696,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   837,   834,
       0,   936,   934,   937,   935,     0,     0,     0,   723,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   611,   744,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   818,     0,
       0,     0,     0,     0,     0,   776,     0,   778,     0,     0,
       0,   983,   980,   979,   982,   981,     0,   660,   854,     0,
       0,     0,     0,     0,     0,     0,   573,   564,     0,     0,
     562,   574,   567,   568,   556,   854,   549,   495,   952,     0,
       0,     0,     0,   554,   553,   560,   555,     0,   645,   575,
     577,   570,   722,   569,   722,   571,   572,   578,   576,  1291,
     545,   565,     0,     0,   648,  1264,  1672,  1665,  1208,  1210,
       0,   477,     0,   938,  1541,  1544,     0,     0,     0,  1197,
       0,  1649,  1662,   494,  1652,   524,   496,   523,     0,   507,
    1158,     0,     0,   119,  1142,  1118,  1143,  1136,     0,  1135,
    1122,  1109,     0,  1131,     0,  1150,  1130,  1156,  1157,  1152,
       0,  1150,  1123,     0,  1129,   970,  1128,   288,  1113,   152,
    1134,     0,  1117,  1124,     0,  1132,  1152,   426,   425,   424,
     420,   421,   426,     0,   891,     0,  1015,     0,     0,   474,
     484,   436,   452,     0,  1625,  1606,  1608,  1607,  1625,  1603,
    1625,  1580,  1578,  1602,  1625,     0,     0,   467,   468,     0,
       0,  1578,     0,  1504,  1505,  1508,  1506,  1496,  1499,     0,
    1503,     0,    52,    53,     0,  1037,  1026,  1036,   492,  1655,
     490,  1656,     0,  1165,  1238,  1163,  1171,  1237,  1172,   942,
    1409,  1348,     0,   945,  1556,   304,   367,   303,   110,   113,
     112,     0,   303,   452,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
      65,    78,   120,   303,    83,     0,     0,     0,     0,  1091,
    1087,  1097,     0,     0,     0,   938,     0,  1009,  1285,     0,
       0,     0,   400,     0,    58,    60,  1180,     0,     0,  1189,
    1023,     0,   819,     0,   854,   824,     0,     0,   830,   829,
     831,   832,   833,     0,     0,     0,   684,   686,     0,     0,
     673,  1667,   854,   854,   730,     0,   859,     0,     0,   854,
     676,     0,     0,   674,   667,   683,   685,   697,   758,     0,
     757,   681,     0,   820,   821,   822,   866,     0,   687,   854,
       0,   692,     0,     0,   698,     0,   707,     0,   705,     0,
     854,     0,   701,     0,     0,     0,   854,     0,   713,     0,
     810,     0,   789,     0,   791,     0,   793,   854,     0,     0,
     718,     0,   724,     0,   812,     0,   794,     0,   854,     0,
     734,   735,   737,   796,     0,   798,     0,   800,     0,   795,
     802,   803,   739,   741,   740,   805,     0,     0,   807,     0,
     809,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   743,     0,     0,   747,
       0,   751,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   760,   769,   770,   771,   772,   773,   774,
       0,   777,   782,     0,   784,   785,     0,     0,     0,   665,
    1514,  1515,  1516,   360,   651,  1265,   557,   563,     0,  1670,
       0,     0,   558,   854,   550,   952,   561,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   580,   579,   566,   721,     0,     0,     0,
    1207,     0,     0,   452,     0,     0,  1200,   441,  1193,  1664,
    1663,  1653,   526,   971,   527,   529,   528,  1263,     0,  1160,
       0,  1141,     0,  1153,  1139,     0,  1152,  1110,  1151,  1152,
     973,   974,     0,  1150,     0,  1133,     0,   414,   423,   411,
     418,   891,     0,     0,   872,     0,     0,     0,   476,   471,
     475,   473,   338,   337,   340,     0,   483,   438,   437,   435,
     459,   458,   460,   457,   456,   451,   453,   454,  1605,     0,
    1586,  1584,  1588,  1590,  1616,  1619,  1270,     0,  1582,     0,
       0,     0,     0,     0,  1507,     0,  1476,  1525,  1501,     0,
       0,     0,     0,     0,  1502,    54,  1035,     0,     0,   969,
    1661,  1659,  1563,  1561,  1562,  1566,  1567,  1569,  1568,  1570,
    1560,  1557,  1564,   946,   971,   111,  1061,  1061,   396,   396,
     396,  1061,   396,  1061,  1061,  1061,     0,     0,  1061,     0,
       0,     0,     0,     0,  1061,  1061,  1061,  1061,  1061,  1061,
     406,  1061,  1061,  1061,  1061,  1061,   396,  1061,   394,   303,
     145,   146,   365,     0,   373,   395,   449,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    88,   121,     0,   351,   353,   352,   350,
     349,     0,     0,   945,     0,  1094,   891,  1098,  1097,  1095,
     857,  1010,  1284,     0,  1621,   402,   401,  1008,    61,     0,
       0,  1175,  1190,  1178,     0,     0,   843,   826,   823,     0,
       0,     0,     0,   266,   266,   266,   853,   851,   847,   852,
     849,     0,   291,     0,   290,     0,     0,     0,     0,   814,
     863,     0,     0,     0,     0,     0,     0,     0,     0,   869,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   840,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   603,   594,     0,     0,   592,   608,   597,
     598,   586,     0,   952,     0,     0,     0,   584,   583,   590,
     585,     0,   604,   606,   600,   722,   599,   722,   601,   602,
     607,   605,   595,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   661,     0,   653,   547,  1669,   951,     0,
     559,     0,   637,   628,     0,     0,   626,   642,   631,   632,
     551,   854,   614,   952,     0,     0,     0,     0,   619,   618,
     624,   620,     0,   638,   640,   634,   722,   633,   722,   635,
     636,   641,   639,   629,     0,  1266,  1205,   478,   479,   482,
       0,  1547,  1548,  1546,  1545,   462,  1201,  1202,   446,   447,
     445,   440,   442,   443,     0,   522,   891,   997,   519,   500,
     498,   972,   499,   530,     0,  1159,     0,  1119,     0,  1140,
       0,  1112,  1111,     0,     0,  1145,  1144,  1114,  1121,  1150,
     428,   427,   422,   898,   891,     0,  1658,   891,     0,     0,
     888,     0,     0,   891,   901,   901,   891,   891,   938,   433,
    1016,     0,   455,  1629,     0,  1628,     0,     0,     0,   469,
     470,   431,     0,     0,  1500,     0,     0,     0,  1059,  1060,
       0,   293,   292,   299,     0,     0,  1513,     0,   295,   297,
     296,  1521,   294,   103,  1041,     0,     0,     0,  1050,  1027,
    1038,   962,  1660,     0,     0,  1555,  1062,     0,     0,   397,
     358,   339,   339,   377,     0,   181,   358,   332,   375,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1061,     0,   388,   371,   389,   372,  1061,     0,     0,     0,
       0,     0,     0,   408,   409,   407,     0,     0,     0,     0,
       0,     0,     0,     0,   124,   303,   184,     0,   403,   181,
     187,  1267,    67,    68,    79,   988,   986,   984,   987,   985,
      80,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      81,    82,    66,     0,   184,    84,  1214,   122,   125,   169,
     168,   167,     0,    85,   891,   960,  1097,   945,     0,   938,
    1622,     0,    59,  1179,  1071,   736,     0,     0,   646,   679,
     768,     0,   844,   846,   305,   848,   850,   669,   672,   671,
     728,   729,   731,     0,     0,     0,   662,   677,     0,   759,
     682,   867,   670,     0,     0,   688,     0,     0,     0,   703,
     708,   706,   699,   704,   702,     0,   788,   715,   712,   714,
     811,   790,   792,   838,   841,     0,   717,     0,   725,   813,
     726,     0,   700,   732,     0,   797,   799,   801,   806,   804,
     808,   587,   593,   742,   588,   952,   591,     0,     0,   610,
     609,   596,     0,   746,   748,   646,   749,     0,   755,   753,
       0,     0,   766,     0,   764,     0,   765,     0,   767,     0,
     783,   786,   787,   361,   548,   552,   621,   627,     0,   622,
     854,   615,   952,   625,     0,     0,   644,   643,   630,  1214,
       0,   486,  1549,  1550,   444,  1654,   971,   945,     0,     0,
    1005,     0,     0,     0,   497,   502,   501,     0,   525,   534,
     533,  1260,  1264,  1161,   969,  1127,  1126,     0,   976,   975,
    1152,     0,   896,   505,  1658,   895,     0,     0,   890,   889,
     891,   901,   901,  1075,  1078,     0,   875,   902,     0,     0,
     873,   874,   903,   913,     0,   912,  1626,     0,  1618,  1617,
    1630,     0,  1573,  1527,     0,  1526,  1538,  1539,  1536,  1537,
    1535,  1517,     0,  1522,     0,  1532,     0,     0,  1523,     0,
       0,   505,     0,  1063,  1049,  1055,  1048,     0,     0,     0,
    1047,  1259,  1258,  1651,  1028,     0,     0,   947,   302,   301,
     151,   298,   150,   186,   359,   333,   334,     0,     0,     0,
     339,   180,   358,   179,   182,   348,     0,   379,   134,   358,
     386,   387,   400,   135,   132,   138,     0,     0,   139,     0,
     130,   131,   137,   136,   158,   157,   141,   159,   142,   143,
     392,   153,   155,   154,   156,   140,   129,     0,   128,   162,
     161,   160,   147,   381,   133,   374,     0,   170,   172,   173,
    1269,     0,   405,   376,     0,   174,   175,     0,     0,    93,
       0,    91,     0,     0,  1216,  1215,    92,   106,   303,   126,
       0,     0,   945,   977,   961,  1090,  1096,  1623,     0,  1024,
     827,     0,     0,     0,   307,   308,   306,     0,   845,     0,
       0,   666,     0,   870,     0,     0,   694,   695,     0,     0,
       0,     0,     0,     0,     0,   589,     0,   581,     0,     0,
       0,     0,     0,   763,   761,   762,     0,   612,     0,   623,
       0,   616,     0,   480,     0,   481,   504,   953,  1002,  1004,
       0,   998,  1000,     0,   520,   532,   531,     0,  1120,     0,
    1115,   429,   526,   897,   938,     0,   887,     0,     0,     0,
     945,     0,   891,   891,     0,   877,     0,     0,     0,   892,
     485,     0,  1627,     0,  1635,     0,     0,     0,  1531,  1518,
     300,     0,     0,     0,     0,  1519,   526,  1042,  1057,     0,
    1065,     0,     0,  1039,  1052,     0,     0,  1051,  1262,   963,
     966,  1070,  1069,     0,  1068,   183,   358,   335,   336,   348,
       0,     0,     0,     0,   385,   384,   299,   148,   149,     0,
       0,   378,   184,   404,   312,   200,   266,   193,   194,   255,
     305,     0,   238,   243,   225,   228,   251,   266,   237,   208,
     205,   255,   253,   223,   255,   229,   247,   213,   305,   212,
     250,   305,   255,   252,   249,   266,   266,   206,   209,   248,
     305,     0,   241,   230,   233,   234,   232,   236,   231,   235,
     266,   270,   211,   305,   198,     0,     0,   266,   268,  1268,
       0,    96,   121,   107,     0,   127,    90,     0,  1092,     0,
    1088,  1072,     0,   680,   267,   309,   816,   815,   678,     0,
     689,   709,     0,   839,   835,   943,   719,   727,   733,   582,
     745,   750,   754,   752,   756,   854,   613,   617,     0,   487,
       0,   948,  1217,  1001,     0,     0,  1261,     0,   899,   894,
       0,   891,   891,  1077,   960,  1079,   880,   884,   876,     0,
     907,   905,   906,   904,   911,  1634,  1632,     0,  1633,     0,
       0,  1631,  1609,     0,  1576,  1574,  1529,  1528,  1530,  1524,
       0,     0,     0,   104,     0,     0,     0,  1066,  1054,  1657,
    1040,  1046,     0,   967,   968,   965,  1565,     0,     0,     0,
       0,   391,     0,   403,   393,   144,   270,   171,   318,     0,
     192,     0,   259,   257,   237,   214,     0,   305,   227,   239,
     242,   244,   246,     0,   210,   259,   254,     0,   259,   219,
     218,   259,   305,   207,   216,     0,   259,     0,   278,   284,
       0,     0,     0,   274,     0,   311,     0,   281,   188,   271,
     273,     0,   240,     0,   196,     0,     0,     0,   259,     0,
     269,   259,    94,  1658,  1214,     0,    99,     0,   966,   356,
     978,     0,     0,   871,     0,     0,     0,     0,     0,   949,
     960,     0,  1225,   999,   521,     0,   971,   891,   882,   886,
     977,     0,     0,     0,     0,     0,     0,  1613,  1614,  1615,
    1610,     0,     0,     0,     0,     0,  1636,  1638,  1534,  1533,
    1520,   971,  1056,  1058,  1064,  1053,   966,  1067,     0,     0,
       0,     0,     0,     0,     0,     0,   390,  1240,   380,   382,
       0,     0,     0,   313,   314,   319,   321,     0,     0,   263,
     264,   265,   222,   260,   262,   215,   245,     0,   220,     0,
     191,   221,   217,     0,   204,   283,   285,   535,   276,   287,
     275,     0,     0,   282,   272,   280,     0,     0,     0,     0,
     189,     0,   190,    97,    95,     0,  1651,    86,     0,   355,
       0,     0,   720,   710,     0,   828,   775,  1217,   957,   966,
       0,   971,     0,     0,     0,     0,  1218,  1220,     0,  1003,
       0,   900,   519,   163,     0,  1076,   879,     0,   883,     0,
       0,   914,   909,  1611,  1639,  1642,  1640,  1641,  1637,   105,
     964,     0,     0,   176,  1242,  1241,   403,   324,   325,   326,
       0,     0,     0,   317,   320,   199,   256,     0,   261,     0,
     362,     0,   203,   286,   535,   279,   305,   197,   305,   202,
     101,   100,   966,     0,     0,     0,  1225,     0,     0,   954,
     956,   950,   989,     0,     0,     0,     0,  1219,     0,     0,
    1226,  1228,     0,   164,     0,     0,     0,   878,     0,     0,
     910,     0,   177,   383,   328,     0,   327,     0,   322,   323,
     318,     0,     0,   305,     0,   305,   277,   195,   201,  1658,
     354,   357,  1073,  1081,     0,   711,  1231,   958,   959,   966,
       0,   503,  1223,  1224,     0,  1221,     0,     0,  1227,     0,
       0,     0,     0,   915,   908,   178,   330,   331,   329,   315,
     316,   258,   226,   363,   224,   102,     0,     0,     0,  1043,
     955,   990,  1222,  1230,  1229,     0,   893,   881,   885,  1080,
    1082,     0,     0,  1206,     0,     0,  1232,  1045,     0,   526,
       0,  1044,     0,     0,   993,   995,     0,   996,   991,   526,
    1116,   994
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    49,    50,    51,    52,    53,  1262,    54,   586,   953,
    1334,  1335,    55,    56,   929,  1309,  1310,  1311,    57,  1734,
    2431,  1313,  1315,  2115,  2421,  2793,  2426,  2906,  3029,  2028,
    2331,  2841,  2634,  1286,  1287,  1288,   330,   331,   332,   568,
    2116,  1708,  2117,  2118,  1710,  1711,  1208,  2395,  2386,  2402,
    2931,   333,  2122,  2406,  2407,  2408,  2409,  2363,  2364,  2044,
    2045,  2089,  2417,  2621,  2757,  2753,  2622,  2623,  2624,  2625,
    2626,  2627,  2628,  2742,  2743,  2872,  2873,  2874,  2142,  2791,
    2778,  2779,  2780,  2888,  2447,  2012,  2013,  2020,  2021,  2349,
    2323,  2350,  1291,  2448,  2781,  2416,  2738,  2863,  2962,  2864,
    2865,  2866,  3018,  2046,  2362,  1614,  1615,   857,   334,  1318,
    1739,  2797,  2798,  2353,  1885,  2969,    58,  1292,   926,   560,
    1712,  1713,  1714,  2563,  2570,  2956,  2048,   318,  1757,  2413,
    2076,    59,  1222,  1217,    60,   868,   863,   864,  1220,  1221,
    1597,  1971,    61,   905,    62,   874,    63,   878,  1619,    64,
    1168,  1941,  1942,  1943,    65,   928,    66,   879,  1625,  1626,
    1627,    67,  1166,   321,    68,   904,  1247,  1248,    69,   875,
     876,  1609,    70,  1559,  1927,  1928,  1229,  1230,  1616,  2485,
      71,    72,   547,   519,   811,   520,   521,  1573,  1948,  2932,
     822,   823,   824,  2264,  1176,  1177,  1178,  1953,  1574,  2268,
     609,  2552,   767,  1152,   493,  1072,  1137,   494,   495,   496,
    2155,  1087,   497,  1344,  2136,  1417,  1039,  2460,  2183,   970,
    1343,  1781,  1088,   579,   942,   618,   619,   620,   996,   645,
    1797,  1386,  1387,  1799,  1975,  2689,  2822,  2824,  1987,  1604,
    1605,  1976,  2282,  2283,  2816,  2298,  2519,  2691,  2826,  3009,
    2304,  2940,   786,  1045,   922,   923,   971,  1674,  2034,  2810,
    2920,  1522,  2671,  2918,  2989,  2433,  2434,  2345,  2549,  2725,
    1204,  2933,  1951,  1590,  2640,  1106,  2100,  3041,  3084,  3093,
    3094,  3095,  2260,  2261,  2491,  2492,  1952,  2672,    73,   336,
      74,  1751,   584,  1225,  1226,   583,   342,    75,   350,  1764,
      76,   544,  1657,  2344,   591,   912,  1266,  1267,  2029,  2332,
    3083,  2339,  2030,  2343,  2719,  2334,  2537,  2538,  2036,  2037,
    2335,  2540,  2716,  2553,  2554,  2439,  2801,    77,   531,  2510,
    2293,  2294,  3032,  3033,   873,    78,   335,   936,  1743,  1323,
    1742,   937,   938,  1325,   576,   577,    79,   529,    80,   522,
     858,  1592,  2274,  1967,   802,   860,  1199,  1189,   861,  1200,
    1579,  1957,    81,   919,   918,    82,   552,  1275,    83,   587,
     964,   965,  1339,  1763,    84,   516,   808,   809,    85,   514,
     803,  1566,    86,    87,    88,  2249,  1160,   795,  2427,  2812,
    2926,  2927,  2929,  3000,  3001,  3069,   498,  2970,   499,  2856,
     500,   501,  2340,  2341,  2550,   502,  2090,   871,   312,   313,
     347,   503,   504,   947,   948,   315,    89,   909,   541,  1257,
    1258,  1259,  1260,   862,  1113,  1648,  1654,  1649,  2529,  2328,
    2321,    90,   798,   966,  1164,  1165,  1933,    91,    92,   924,
    1283,  1284,  1671,  2033,  1672,    93,   539,   907,    94,   536,
     901,  1242,   902,   903,  1238,  1234,  1240,  1244,  2831,  2701,
    2702,  1637,   949,   950,  1630,  1994,  1995,  2524,  2704,  2836,
    2837,    95,   322,   565,    96,    97,    98,  1173,  1269,  1944,
    2286,  1271,  1272,  1661,  1571,   505,   791,   612,   990,  1126,
    1520,   506,  1157
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -2603
static const int yypact[] =
{
    1767, -2603, 15530,    62,    16, -2603,   302, -2603,   770, -2603,
   -2603,   -15, 37386,    16, 33327, -2603, 10329,   603,   761,    16,
   -2603,    16, -2603,   415, 37386, -2603, -2603,   633,    95,   263,
     253,   761, -2603,   761,   580,   761,   761, -2603, -2603, -2603,
     761,   761, -2603,   533, 37386, 37386, -2603, -2603,    30,   784,
     791, -2603,   501, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, 15981, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   37386,   639,   153, -2603,   -76, -2603, -2603, 37386,   604, -2603,
   -2603,   761,   425,   667, -2603, -2603, -2603, -2603, -2603,   574,
     719, -2603,   724,   735,   857,   412, -2603, 37386, -2603,   849,
     638, -2603,   761, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
     750,   562,   566,   571,   575,   588,   592,   613,   620,   630,
     634,   643, 10329,   645,   653,   662,   669,   675,   677,   693,
   -2603, -2603,   696, -2603,   701,   703, -2603,   710, -2603, 10329,
   -2603, -2603, -2603,   725, -2603, -2603,   729,   737,   747,   749,
      88,   763,   766,   772,   775,    72,   286,   289, -2603,   783,
     788,   794,   797, 10329,   806,   812,   814,   675,   822,   824,
     828,   829,   831,   832,   833,   837,   838,   840,   842,   844,
     846,   848,   850,   852,   856,   861,   862,   863,   867,   868,
     873,   874,   875, 10329,   876,   880,   881,   882,   883,   885,
     888,   891,   892,   893,   895,   905,   908,   910,   913,   914,
     915,   916,   917,   918,   920,   921,   922,   925,   929,   930,
     933,   936,   937,   938,   939,   940,   943,   945,   946,   947,
     950,   951,   952,   966,   967,   968,   675,   675,   675,   969,
     970,   972,   973, 10329, 10329, 10329,  5910, 10329, 37386, 17334,
   37386, -2603, 30214, -2603,  1571,   957, -2603, -2603,   923, -2603,
   -2603, -2603, -2603, -2603,   619, -2603, -2603,   463,   919, 15530,
   -2603, -2603, -2603,   761,   258,   761,   222,  1058, -2603, -2603,
   -2603,   682,  3703, -2603, -2603, -2603,   887, -2603, -2603, 15530,
   -2603,  1053, -2603, 15530, -2603, -2603,  2113, -2603, -2603,  2874,
   -2603, -2603, -2603,  1096,   687, -2603,    30,   760, -2603, -2603,
   37386,    51, -2603, -2603,   847, -2603,   251, -2603, -2603, 37386,
   -2603, -2603, 15530, -2603, -2603, -2603, -2603,  1038, 37386,   574,
   -2603,   849, 37386, -2603, -2603, -2603, 34680,   412, -2603, 10329,
    1092, -2603,  1200, 37386, 31974,   638,  1042,  1160, -2603, -2603,
   -2603,  1180, 10329,  1269,   190, 10329,  1269,  1269,  1269,  1269,
    1269, 10329, 10329,   220, 10329, 10329, 10329, 10329,   900, -2603,
   16432,  1312, -2603, -2603, 10329, 10329, 10329, -2603,  1106, -2603,
   16432,   220, 10329,   978, 10329, 10329, 10329, -2603, -2603, 16432,
   10329, -2603, -2603,  1187, 10329,   923, 10329,   923, 10329,   923,
   10329,  1269,  1269,  1269, 30214,  1008, -2603, 10329, 10329, -2603,
    6401, -2603,   981, 10329, 10329, 10329, 10329, 10329, 10329, 10329,
   10329, 10329, 10329,  1571, 10329, 10329, 10329, 10329, 10329, 10329,
   -2603,  1343,    31,   676, 10329, 10329, 30214,  6892, 10329, 10329,
   -2603, 10329, 10329, 10329, 10329, 10329, 10329, 10329, 10329, 10329,
   -2603, -2603, -2603,  6401, -2603, 10329, 10329, 10329, 10329, 10329,
   -2603, 10329,  7383, 10329, 10329, 10329, 10329, 10329, 10329, 10329,
    4928,   989,   989,   989,   989,   989,   989,    31,  7874,   990,
   -2603, -2603, -2603, 10329, 10329, 10329,   827,   220,   220,   220,
   -2603,  2320,   220, 10329,   556,  1463,   993, 10329, -2603, 10329,
    1310, -2603, -2603, -2603, -2603, -2603,   357, 10329, 10329, 10329,
   10329,  1002, 10329,   424, 10329, 10329, 10329, 10329, 10329, 10329,
   10329, 10329, 10329, 10329, 10329, 10329, 10329,  8365, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603,  1010, 33327, -2603, 37386,
   -2603,  1003, -2603,  1435, -2603,  1313,  1392,  1352, 15530, -2603,
   -2603, -2603,  1316, -2603, -2603, -2603, -2603,  1396,  1012, -2603,
   37386,  1206, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603,  1023,   682, -2603,  1459,  1019,   -12,  1237,    78,
    1331, -2603,  1338,  1233,  1338, -2603, -2603,  1130, -2603, -2603,
    1250, -2603, -2603, -2603,  1466,  1247, -2603, -2603,  1338, -2603,
     716,   582,  1194,  1194,  1265, 33327,  1338,   716, -2603,  1345,
    1144,   125,  1224, -2603,   277, -2603, -2603,  1493, -2603, -2603,
   -2603, -2603, -2603,  1180, 15530,   -42, -2603, -2603, 15530, 15530,
   -2603,  1253, -2603, -2603, -2603, -2603,  1258,   219, -2603,  1416,
   -2603, -2603,  1301, -2603,  1315, -2603, -2603, -2603, -2603, -2603,
   -2603,  1322,  1046, -2603, 15530, 15530,  1301, -2603,  1324,   853,
     -85, -2603, 13666, -2603, -2603,  1059,   748, -2603,    52, 33778,
   -2603, -2603, 37386, -2603, 37837, -2603,   599, -2603, 15530,  2019,
    1412, -2603, 15530, -2603,   482, 15530, -2603,  1061, -2603,  1057,
   -2603, 30214,  1066, 15530, -2603, -2603,   675,  1067,  1162,  1074,
   -2603, 15530,  1073, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
    1464, -2603, -2603,  1261,  1080, -2603, -2603, 13666, 18758, -2603,
    1082, -2603, -2603,  1084,  1093, 18805,  1087,  1089,  1090,  1091,
    1097, 18858, 18903, 29721, 21849, 21878,  2761, -2603,  1099, -2603,
    1003, 19078, 19176,  2774,  1100,  1102,  1103, -2603, 19255, -2603,
   21896, 19302, 19353,  1107, 21930,  1109,  1111, 21975,  2801, 22214,
    2865,  1112,  1114,  1115, -2603,  1119, 19400, 19575, 22247, -2603,
   19621, 19673, 22260, 19755,  3198,  3483, 19800, 19941,  3548, 20075,
    1431, 20117, 20160,  3562,  3575,  3600,  3627,  1121, -2603, -2603,
     -41, -2603, -2603, -2603, -2603,  1105, 22293, 20294, -2603, 22532,
   20435,  3935,  1122, 20477, 20514, 20569, 22568, 22611, 22624,  4080,
    4120,  4221,  1123,  1124,  1125, 22666, 22941, 22974,  4264, 20611,
    4359,  1126, 30260,   957, -2603, 23053, 20794, 20850, 18133, 23115,
   20886, 18269, 20929,  8856,  9347,  9838, 21657,  1127, -2603,  1128,
    1129,  1131,  1132,  1133,   -13, -2603, 23160, -2603, 18307, 23295,
   18320, -2603, -2603, -2603, -2603, -2603,  1134, -2603, -2603,   196,
    1086,  1136,  1137, 33327, 10329, 37386,    84,   248, 10329,  1372,
   -2603,    84,   234,   234, 19434,  1312, -2603, -2603,   162,  1138,
   10329, 10329, 10329,  4442,  4442,   248,  4442, 30306,   957,   178,
     210,   184,  1571,   184,  1571,    84,    84,    84,   220,  1145,
   -2603,   248,   693, 10329, -2603,  1139, -2603, -2603, -2603, -2603,
    1460, -2603,  1577,   652,  1146, -2603, 15530,   -54, 15530, -2603,
     222, -2603,   193, -2603, -2603, -2603,  1147, -2603, 10329, -2603,
    1469,  1159, 15530,   574, -2603, -2603, -2603, -2603,  1361, -2603,
   -2603, -2603, 31974, -2603,  1252,   716, -2603, -2603, -2603,  1338,
   37386,   716, -2603,   827, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, 15530, -2603, -2603,   716, -2603,  1338,  1561, -2603, -2603,
    1165, -2603,  1561,  1576,   458,  -113, -2603, 35131, 15530, -2603,
     -18,    65,   419,  1380,  1172, -2603, -2603, -2603,  1172, -2603,
    1172, -2603, -2603, -2603,  1172, 14117,  1629,  1171, -2603,  1381,
     -40,  1176, 14117, -2603, -2603, -2603, -2603,  1177, -2603, 35582,
     136, 33327, -2603, -2603, 15530, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603,   457, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
     130,   132,  1465,  1355, -2603, -2603, -2603,   626, -2603, -2603,
   -2603,   197,  1267,   419,  1656,  1658,  1659,  1662,  1664,  1666,
    1668,  1670,  1672,  1673,  1677,  1678,  1679,  1681,  1683,  1208,
   -2603, -2603, -2603,   599, -2603,  1404,   442,   442,  1478,  1061,
   -2603,    91, 37386,  1556, 27826,    81, 10329, -2603, -2603, 33327,
    1602, 31974,     5, 33327,  1216, -2603, -2603,  1461,  1160, 15530,
   -2603, 10329, -2603, 10329, -2603, -2603,  1219, 10329, -2603, -2603,
   -2603, -2603, -2603, 10820, 10329,   699, -2603, -2603, 32425,   699,
   -2603, -2603, -2603, -2603, -2603, 10329, -2603, 10329, 16432, -2603,
   -2603, 10329, 10329, -2603, -2603, -2603, -2603, -2603, -2603, 10329,
   -2603, -2603, 10329, -2603, -2603, -2603,  1328, 10329, -2603, -2603,
   10329, -2603,  1304,  1304, -2603,   923, -2603, 10329, -2603, 10329,
   -2603,   923, -2603, 10329, 10329, 10329, -2603,  1491, -2603, 10329,
   -2603, 10329, -2603, 10329, -2603, 10329, -2603, -2603,  1494, 10329,
   -2603, 10329, -2603, 10329, -2603, 10329, -2603, 10329, -2603, 10329,
   -2603, -2603, -2603, -2603, 10329, -2603, 10329, -2603, 10329, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, 10329, 10329, -2603, 10329,
   -2603, 10329, 10329,  1540,   744, 10329, 10329, 10329, 10329, 10329,
   10329,   507, 10329, 10329, 10329, 10329, 10329, 10329, 10329, 10329,
   10329, 10329, 10329, 10329, 10329,  8365, -2603, 10329, 10329, -2603,
   10329, -2603, 11311, 10329, 10329, 10329, 10329, 29763, 10329, 29806,
   10329, 29828, 10329, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
    1499, -2603, -2603, 10329, -2603, -2603, 10329, 10329,  1232, -2603,
   -2603, -2603, -2603,  1227, 30214, -2603,   248, -2603,  1234, -2603,
    1003, 10329, -2603,  1312, -2603,   162,   248, 30394, 10329, 10329,
    1545,   903, 10329, 10329, 10329, 10329,  1238, 10329,   650, 10329,
   10329, 10329, 10329, 10329, 10329, 10329, 10329, 10329, 10329, 10329,
   10329, 10329,  8365, -2603, -2603, -2603,   184, 37386,  1361, 15530,
   -2603,   622, 15530,   419,  1361, 10329, -2603,    56, -2603, -2603,
   -2603, -2603, -2603,   147, -2603, 30214, -2603,  1230,  1361,  1581,
    1242, -2603, 37386, -2603, -2603,  1660,  1338, -2603, -2603,  1338,
   -2603,   -59,   430,   716, 15530, -2603,   894, -2603,   277, -2603,
   -2603,    29, 37386,    71, -2603, 15530,  1361, 15530, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603,  1245, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603,   414, -2603, 37386,
   -2603, -2603, -2603, -2603,  1239, -2603,  1240,  1454, -2603, 15530,
   15530,  1361,  1587,  1592,   853,  1244,  1570,  1248, -2603,   901,
   31072,   112, 17785, 31523, -2603, -2603, -2603,    43,  1643,  1194,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603,  1194, -2603,   901,   901,  1117,  1632,
    1632,   901,   998,   901,   901,   901,  1467,  1612,   901,  1578,
    1470,  1579,  1474,  1618,   901,   901,   901,   901,   901,   901,
     160,   901,   901,   901,   901,   901,  1632,   901, -2603,  1299,
   -2603, -2603,  1266, 14588, -2603, -2603, -2603,  1361,  1361,  1361,
     851,  1361,   827,   827,   827,  1361,  1361,  1361,  1361,  1361,
    1361,   827,  2019, -2603, 38081,   728, -2603, -2603, -2603, -2603,
   -2603, 15530,  1455,  1355, 27826, -2603,   458, -2603,  1268, -2603,
   30214, -2603, -2603,   -90, -2603, -2603, -2603, -2603, -2603,  1073,
    1703, -2603,  1271, -2603,    43, 23339, 30214, -2603, -2603, 21168,
   10329, 23384, 23477,  1274,  1274,  1274, -2603, -2603,  1434, -2603,
    1437,  1276, -2603,  1279, -2603,  1281,  1282,  1284, 23563, 29862,
   -2603,  1286, 23656, 21203, 23669, 23701, 10329,  1309, 29907,  1317,
    1288, 21247,  1571,  1571,  1291, 23977, 24066,  1292,  1293, 24079,
   21284, 24103,  1294,  1296, 24196, 24464, 24477, 24504,  1557,  1298,
   24517, 21302, 24605, 24785, 18354,  1297, 18372, 24874, 24887, 25004,
   25272, 25285, 25312,    84,   248, 10329,  1573, -2603,    84,   234,
     234, 19434, 25325,   162, 10329, 10329, 10329,  4442,  4442,   248,
    4442, 30436,   178,   210,   184,  1571,   184,  1571,    84,    84,
      84,   220,   248,   693, 21523, 25367, 25413, 10329, 25686,   163,
   18406, 21570, 25699, 10329, 25812, 10329, 26051, 10329, 26070,  1307,
   26084, 26097, 26179, -2603, 37386, -2603, -2603, -2603,   957,  1302,
   -2603, 10329,    84,   248, 10329,  1574, -2603,    84,   234,   234,
   19434,  1312, -2603,   162,  1314, 10329, 10329, 10329,  4442,  4442,
     248,  4442, 30500,   178,   210,   184,  1571,   184,  1571,    84,
      84,    84,   220,   248,   693, -2603, -2603,  1308, -2603, -2603,
    1496,  1619, -2603, -2603, -2603, -2603, -2603, 30214, -2603, -2603,
   -2603, -2603, -2603,   399,    52, -2603,    44,   860,    45,  1638,
   -2603, -2603,  1663, 34229, 28297, -2603,   851, -2603,   790, -2603,
    1500, -2603, -2603,   827,   827, -2603, -2603, -2603, -2603,   716,
   -2603,  1321, -2603, -2603,    29,    75,   -38,   458,  1649,  1652,
   -2603,    59, 16432,   458,  1583,  1583,   458,   458,   217, -2603,
   -2603, 36033, -2603, -2603,   649, -2603,  1344, 28768, 31974, -2603,
   -2603, -2603,  1599, 31974, -2603, 37386,  1650, 37386, -2603, -2603,
    5419, -2603, -2603,  1717, 31974,   342,   556,   901, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603,  1353,  1353, 13195, -2603, -2603,
   -2603, -2603, -2603,  1356, 10329, -2603, -2603, 32876, 31072, -2603,
   16883,   462,   462, -2603,   706,   821, 16883, -2603, -2603, 16883,
   16883,  1361,  1667,  1674, 16883, 16883,   851,   827,   827,    97,
     901,   827, -2603, -2603, -2603, -2603,   901,   851,   851,   754,
     820,   827,   827, -2603, -2603, -2603, 15530,   460, 33327,  1358,
   33327,   245, 16883,  1361, -2603, 27307, 12744, 37386,   597,   111,
   -2603,  1337, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, 15530, 12293, -2603,    90, -2603,  2026, -2603,
   -2603, -2603,  1550, -2603,   458,  1557,   104,   538,  1366,    81,
   -2603,  1572, -2603, -2603,  1628, -2603,  1365, 10329, 29587, -2603,
   -2603,  1634, -2603, -2603,   618, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603,    -7,  1616,  1368, -2603, -2603, 10329, -2603,
   -2603, 30214, -2603, 10329, 10329, -2603, 10329,  1369,  1370, -2603,
   -2603, -2603, -2603, -2603, -2603, 10329, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603,  1597, -2603,  1641, -2603, 10329, -2603, -2603,
   -2603, 10329, -2603, -2603, 10329, -2603, -2603, -2603, -2603, -2603,
   -2603,   248, -2603, -2603, -2603,   162,   248, 30581, 10329, -2603,
   -2603, -2603, 10329, -2603, -2603, 29587, -2603, 10329, -2603, -2603,
   10329, 10329, -2603, 26196, -2603, 26420, -2603, 26454, -2603,  1642,
   -2603, -2603, -2603, -2603, -2603, 19434,   248, -2603,  1375, -2603,
    1312, -2603,   162,   248, 30613, 10329, -2603, -2603, -2603,   -30,
   15530,  1704, -2603, -2603, -2603, -2603,  1194,   538,  1361,  1361,
   -2603,  1374,  1697,  1784, -2603, -2603, -2603, 36484, -2603, -2603,
   -2603, -2603,  1377, -2603,  1194, -2603, -2603,  1684, -2603, -2603,
    1338,   894, -2603,   682,    38, -2603,  1389,  1471, -2603, -2603,
     458,  1583,  1583,  1391, -2603,   901,   484, -2603,  1699,  1711,
     484,   326,   476, -2603,   656, -2603, -2603, 37386, -2603, -2603,
     -47,  1737,  1074, -2603,   767, -2603, -2603, 10329,   677, -2603,
   30214, -2603, 32876, -2603,   901, -2603,  1397,  1398, -2603, 36935,
   10329,   682, 16432, -2603,  1399, -2603,  1399,    34,  1405,   659,
   -2603, -2603, -2603,  1206, -2603, 10329, 11802, 30214, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, 10329,  1720,  1722,
     462, -2603, 16883, -2603, -2603,   482,   118, -2603, -2603, 16883,
   -2603, -2603,   134, -2603, -2603, -2603, 31072,  1361, -2603,  1361,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, 15530, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603,   680, -2603, -2603, -2603,
   -2603, 37386, -2603, -2603, 15530, -2603, -2603, 38112, 37386, -2603,
   15530, -2603,  1409,   704, -2603, -2603, -2603,  1806,  2892, -2603,
    1361,  1411,   538,  1569, -2603, -2603, -2603, -2603,  1771, -2603,
   -2603, 21610,  1413,  1414, -2603, -2603, -2603, 32425, -2603,  1485,
    1857, -2603, 26595, 30214, 30086, 26693, -2603, -2603, 18679,   389,
    1418,  1426, 26739, 26775, 26837, -2603, 10329, 19434, 26867,  1429,
   26963, 27145, 27188, -2603, -2603, -2603,  1436, -2603,  1432, -2603,
   10329, 19434,  1751, -2603,  1744, -2603, -2603,  1772, -2603, -2603,
   33327,  1438, -2603,  1481, -2603, -2603, -2603, 29239, -2603,  1915,
   -2603, -2603,  1023, -2603,   976,  1700,   484,  1759,  1761, 16432,
    1355, 11802,   458,   458, 10329, -2603,   462,   462,   462, -2603,
   -2603, 37386, -2603,   531,  1625, 31974,    92,  1688, -2603, -2603,
   -2603,   342,  1654,  1655,   901, 30214,  1023,  1447, -2603,   901,
   11802,  1353,  1868, -2603, -2603,    34, 16432, -2603, 30214,  1449,
     201,   677, 30214,   707, -2603, 30214, 16883, -2603, -2603,   482,
    1452,  1820,  1822, 16883, -2603, -2603,  1717, -2603, -2603,   712,
   38112, -2603, 12744, -2603, -2603,  1462,  1274, -2603, -2603,  1468,
     781,   296,   854, -2603, -2603, -2603, -2603,  1274, -2603, -2603,
   -2603,  1468,  1611, -2603,  1468, -2603, -2603, -2603,   618, -2603,
   -2603,   618,  1468, -2603, -2603,  1274,  1274, -2603, -2603, -2603,
     618,  1472, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
    1274,   944, -2603,    47,  1473,  1475,  1476,  1274,  1477, -2603,
    1479, -2603, 27399, -2603,    53, -2603, -2603, 37386, -2603,   851,
   -2603, -2603, 10329, -2603, -2603, -2603, -2603, -2603, -2603, 10329,
   -2603, -2603, 10329, -2603, -2603,  1269, -2603, -2603, -2603, 19434,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, 19434,  1675, -2603,
    1849,  1801,  1844, -2603,  1374,  1539, -2603,  1361,  1147, -2603,
    1788,   458,   458, -2603,  1557, -2603,   591,   647, 30214,  1482,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603,  1686, -2603,  1694,
    1695, -2603,   168,   809, -2603,  1074, -2603, -2603, -2603, -2603,
    1480,  1488,  5419,  1147, 16432, 11802,  1489,  1490, -2603,   748,
   -2603, -2603, 10329, -2603, -2603, -2603, -2603, 11802,  1495,  1497,
   37386, -2603,  1877,   597, -2603, -2603,   944, -2603,   -35,  1741,
   -2603,  1760,   732, -2603,  1265, -2603,  1626,   618, -2603,  1637,
   -2603, -2603, -2603,  1502, -2603,   732, -2603,  1506,   732, -2603,
   -2603,   732,   618, -2603, -2603,  1763,   732,  1361, -2603, -2603,
   33327,  1407,  1775, -2603,  1911, -2603,  1878,  1827, -2603,   944,
   -2603,  1828, -2603,  1783, -2603,  1785,  1787,  1789,   732,  1790,
   -2603,   732, -2603,   135,    90,  1868, -2603,   726,   201,  1521,
   -2603,  1842, 27280, 30214, 18723,  1528,  1530, 15530, 10329, -2603,
    1557,   483,  1841, -2603, -2603,  1934,    89,   458,   484,   484,
    1569, 10329,  1723, 10329,  1725, 37386,  1537, -2603, -2603, -2603,
   -2603,   143,  1804,   827,   827,   827,   809, -2603, -2603, -2603,
   -2603,    89, -2603, -2603, -2603, -2603,   201, -2603, 37386, 37386,
     730,    31,    31,    31,   869,   869, -2603, -2603, -2603, -2603,
     487,   233, 37386, -2603, -2603,   683, -2603,  1547,   733, -2603,
   -2603, -2603, -2603,   732, -2603, -2603, -2603,   389, -2603,   389,
   -2603, -2603, -2603,  1552, -2603, -2603, -2603,   675, -2603, -2603,
   -2603,  1614,  1735, -2603, -2603, -2603,  1554,  1555,  1558,  1559,
   -2603,  1562, -2603, -2603, -2603,  1564,  1206, -2603, 37386, -2603,
    1824,  1966, -2603, -2603, 10329, -2603, -2603,  1844,   255,   201,
   10329,  1194,  1954,  1955,  1925,  1957,   483, -2603,   668, -2603,
    1870, -2603,    45, -2603,  1840, -2603, 30214,  1580, 30214,  1582,
     740, -2603, 36033, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603,   751,   758, -2603, -2603, -2603,   597, -2603, -2603, -2603,
     664,   664,   768, -2603, -2603, -2603, -2603,  1843, -2603,   777,
   -2603,   779, -2603, -2603,   675, -2603,   618, -2603,   618, -2603,
   -2603, -2603,   201,  1584, 16432, 27366,  1841,   586, 10329, -2603,
   -2603, 30214,  1630,   389,   389,  1963,   389, -2603,  1965,  1969,
     668, -2603,  2063, -2603, 10329, 37386, 37386, -2603, 37386,  1588,
    1589,  1833, -2603, -2603, -2603,  1997, -2603,   156, -2603, -2603,
     683, 37386,  1595,   618,   389,   618, -2603, -2603, -2603,   135,
   -2603, -2603,  1598, -2603,   901, -2603,  1924, -2603, -2603,   201,
   37386, -2603, -2603, -2603,   389, -2603,   389,   389, -2603,   851,
    1430,   798,   802, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, 16432, 11802,  1873,  1607,
   -2603, -2603, -2603, -2603, -2603,  2007, -2603, -2603, -2603, -2603,
   -2603,  1919, 15059, -2603,  1615,  1906, -2603, -2603,   807,  1620,
    2092, -2603, 10329,  1622,  1627, -2603,   827, 30214, -2603, -2603,
   -2603, -2603
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603,   344, -2603, -2603, -2603, -2603,   374, -1539, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603,  -684, -2603, -2603, -1954,
   -2603, -2603, -2603,   800, -2603,   834, -2603,  1782, -2603,  -502,
    -513,   411, -2017, -1237,  -803,  -789,  -954, -2603, -2603, -2603,
    -718, -2603, -2603,    11,  -446,   416,   449,    39,    86, -2603,
   -2603,  -430, -2603,  -436, -2603, -2603, -2603,  -443, -2603,  -438,
   -2603, -2603, -2603, -1502,  -485, -1479, -2603,  -727, -1712, -2603,
    -588, -2603,  -630, -2603,  -501, -1317, -1906, -2603, -2603,  -620,
    -414,  -169, -2603, -2474, -2603,  -856, -2603, -2603, -2603,  -862,
   -2603,  -704,  -799, -2603, -2603, -1629, -1818, -2603, -2603, -2068,
     855, -2099,  -744, -1964, -2603,  -713, -2603, -2603, -2603, -2603,
   -2603, -2603,    80, -2603, -2603, -2603,  -781,  -465,  -205, -2602,
   -2603, -2603, -2603, -2603, -2603, -2603,  -226, -2603, -2603,   572,
     953, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603,   226, -2603, -2603, -2603, -2603, -2603, -1105,   546,
   -2603, -2603, -2603,  1088, -2603, -2603, -2603,   535, -2603, -2603,
     949, -2603, -2603, -2603, -2603,   -72,   250, -2603, -2603, -2603,
    1262,   239,  1639,  -445, -2603,  1644, -2603, -2603, -2603, -1443,
   -2036, -2603,  1363,  -748, -2215,   616, -2308, -2603, -2603, -2603,
    -406,  1984, -1022, -1211, -2603, -2603, -1051,  -696,  -663, -2603,
   -2603,   459, -2603, -2603, -2603, -2603, -2603, -2603, -2603,  -566,
   -2603,   835,  -320, -2603, -2603, -2603,  1585, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -1168, -2603, -2603, -2603, -2603, -1925,
   -2603,   216, -2603, -2603, -2603, -1705, -2603, -1221, -2603, -2603,
    -751, -1702,  -645, -2603, -2603, -1134,  1601, -1685, -2603, -2603,
   -2603, -1440, -2603, -2603, -2603, -2076, -1224, -2603, -2603, -2528,
    -813, -1546,  -817, -2603,  -627, -1119, -1917, -2603, -2603, -2603,
   -2603,  -902, -2603, -2603, -2603,  -474,   252, -2603, -2603, -2603,
   -2603, -2603, -2603,  -859,  -484,  1635, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603,  1254,   960,   447, -2603,
   -2603,  -857, -2152, -2603, -2603,   200, -2603,  -483, -1625,  -714,
    -312, -2603, -2603,  -310, -2433, -2603, -2603, -2603, -2603, -2603,
   -2603,  -277, -2603,  -832,  1691, -2603, -2603, -2603, -2603, -2603,
   -2603,  1303,   924, -1632,  1665, -2603, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603,  1714, -2603, -1141,  -797, -2603,  -758,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
   -2603,   899, -2603, -2603, -2603, -2603, -2603,  1069, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,    -9,  -676,
   -2603,  -683,  -742, -2603,  -755, -2603,  -388,  -906, -2603,  -524,
   -2467, -1548,  -297,  1072, -2395,  -606, -1937,    23, -2603,  -184,
    -895,  -495,    -2,    -8, -1145, -2603, -2603, -2603, -2603, -2603,
     608, -2603, -2603, -2603,   238, -2603, -2603,   -74, -2603,  -275,
    -455, -2603, -2603,   123, -2603,   697, -2603, -2603, -2603, -2603,
   -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603,
    1721,  1357, -2603,  1016, -2603, -2603, -2603, -2603, -2603,  -567,
   -2603,  1014, -1915,   941,  -215, -2603,   -37, -2603, -2603, -2603,
    -565, -2603, -2603, -2603, -2603, -2603, -2603, -2269,  -806, -2603,
    -905, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -2603, -1065,
   -2603,  -352,  -911
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1659
static const short yytable[] =
{
     314,   649,   651,   788,   988,  1174,   349,   635,   637,   639,
     343,  1270,   348,  1276,   997,  1263,   578,   613,  1030,  1231,
    1232,   856,   518,  1003,  2010,   311,  2015,  1950,   973,  1561,
     976,   977,   978,   979,   980,  1205,  1205,  1191,  1073,  2273,
    1206,  1783,   542,   543,   694,   870,  1250,  1584,  1659,  2047,
    1475,  1196,  2287,  2054,  1586,  1709,  1603,  1970,  2125,  1210,
    1589,   790,  2143,  2144,  1524,  1142,  1144,   932,  1715,  1293,
     720,   721,   722,  2338,  2547,  1011,  1012,  1013,  2685,  1361,
     554,  1527,  2365,  2310,  1591,  1890,  2256,  1555,  2312,  1128,
    2449,   920,  1332,   -98, -1270,  1138,   740,  1973,   545,  1211,
    2262,  2429,  2023,  2354,  1641,   553,  2748, -1271,  1755,  2354,
    1978,  2023,  2366,  2367,  1978,  1552,  2129,  2371,  2372, -1169,
      25,  2023,  2008,  1289,  2759,  1227,   967,  2760,  2035,  2424,
    1949,  2858,  2352, -1559,  2009, -1558,  2764,  1290, -1657,  2373,
     788,   512,   788,  1612,   788,  2403,   337, -1270,  2444,  2784,
    2380,  2381,   831,  1613,   530,   581,   532,   557,   534,   535,
    2422,  1963,  2561,   537,   538,   525,  2860,  1606,   989,   921,
    2073, -1612,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,  2543,  2861,   737,  1716,  2130,
     740,  1749,  1938,   737,   346,   319,   740,   747,   748,   749,
    2706,  1617,   831,   747,  2523,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,  2357,   737,
    -941,   316,   740,  2355,  2356,  -941,  1564,   920,  2290,   747,
     748,   749,   740,  1946,  1185,  1979,  1214,  1755,   384,  1979,
    1980,   831,   627,   737,  1980,   378,   740,  2502,  2074,  2424,
     750,  2399,  1236,   747,  -941,  2830,  -941,   737,  1172,  1756,
     740,   920,   338,  1182,  1863,  2857,   384,   747,   748,   749,
    2909,   787,  -941,  2875,  2960,  3057,   969,   339,   805,  1569,
    2299,  1981,  2843,   750,  1040,  1981,   378,  2678,  2882,  1237,
    2723,  1946,   806,  1583,  2847,  2536,  1521,  2560,   865,   866,
     753,   869,   831,  2024,  2857,   921,  1676,  1563,   555,  1567,
     384,  1005,  1006,  1947,   800,   561,  2961,   972,  2950, -1270,
    1570,  2713,   -51,  2724,   320,   633,  1015,  2846,  1218,  1094,
     751,  1982, -1271,   527,  1172,   580,  2025,  2026,  2131,   921,
     752,  1924,  2445,  1983,  1650,  2025,  2026,  1983,  1186,  1219,
    1037,   384,   801,   340,  3013,  1939,  1183,  2414,   323,  -941,
    1052,  2446,  1215,   751,   854,  1978,   633,   628,  -941,  -941,
    1062,  1063,  1064,   752,  3058,  1607,  -941,   526,  2562,   753,
    1071,  -941,  -941,  -941,  2400,  2707,  -941,   933,  1756,   754,
     755,  2990,  2330,  2720,   753,  1940, -1270,   558,  2559,  1127,
     753,  2782,  1587,  2204,  1618,  2564,  2425,  1261,  1224, -1271,
     756,  2635,   753,  2919,   854,  1851,  2697,   559,  1203,  1595,
   -1270,  1565,   754,   755,  1277,  2354,   753,  -941,  1265,  1964,
     317,  1172,  2354, -1271,  2263, -1559,   753, -1558,  -941,   341,
    2075,  1331,  2435,   756,   563,  -941,  1228,  1418,  1607, -1657,
     753,  2862,  1968,   854,  3030,  1660,  1594,  2047,  1935, -1559,
     807, -1558,  2401,  2239,   753,   585,  2291,  1525,  -339,  1138,
    2566,  1902,  1709,   757, -1612,  1500,  1203,  -941,  1984,  1125,
    1762,   735,  1984,  1265,  1289,  2047,   733,   348,   736,  -941,
    1979,  2729,  1912,  1607,  2129,  1980,  2292,  1553,  1290,  1554,
     378,  2014,  3027,   378,  3028,  1552,   757,   554,  1985,  2266,
    1289,  3070,  1985,  -941,   854,  1974,   546,  -941,  -941,  1602,
    2542,   758,  -941,  1978,  1290,  2503,  2425,   554,   528,  2027,
    1601,   554,   797,  2783,  1602,  1938,  1981, -1169,    48,  2795,
    1328,  1736,  2558,  1274,  1607,   788,  -941,  2514,   917,  3062,
    1620,  3064,  2217,  1607,   758,  1620,   877,   925,   634,  1986,
     554,  2987,  2285,  1986,  1651,   384,   931,   766,   384,  -941,
     934,   573,  2487,  1119,   939,  1120,   792,  1978,  2127,  2391,
     633,   945,   348,   633,  1744,   927,  2507,  2508,  2338,  2392,
    2695,  1129,  2728,  3039,  2184,  1737,   574,  2128,  1983,   788,
    2393,  1130,  -108,  2102,  2103,  2104,  -941,   793,  2820,  1887,
    2705,  1965,  2111,  2749,  2922,  2923,  2699,  2700,  2516,  2354,
    1621,  2325,  2411,  1612,  -941,  1621,  3037,  2515,  1652,  -109,
    1978,  2850,  2957,  1613,  3080,  2517,   799,  2981,   804,   759,
     760,   761,   762,   763,   764,   765,   766,   794,  1979,  2750,
    2218,  -941,  3038,  1980,  -941,   760,   761,   762,   763,   764,
     765,   766,   920,  1926,   763,   764,   765,   766,   384,  1936,
    2511,  1131,   759,   760,   761,   762,   763,   764,   765,   766,
    2796,  1582,  1519,  1955,  1844,  1658,  1978,  1509,   761,   762,
     763,   764,   765,   766,  1981,   517,  1802,  1803,  1939,  2531,
    1966,  1738,  1979,  1110,  -941,  -941,   523,  1980,  2924,   524,
    2486,  1989,   761,   762,   763,   764,   765,   766,  1285,  2444,
    2958,   507,  2800,   831,   759,   760,   761,   762,   763,   764,
     765,   766,  1622,  1984,  2921,  1111,  2412,  1622,  1940,  1623,
     921,   533,  2501,  2988,  1623,  1285,  2001,  2638,  1981,  2951,
    2952,   575,  2959,  1624,  1845,  1979,  1983,   540,  1624,  1653,
    1980,  2925,  1790,  1985,   508,  2465,  1316,  3014,   812,  2326,
    2327,  2394,   636,  1855,  1857,   638,  2518,  1127,  2257,  1154,
    1265,  3092,  1132,  1317,   548,   348,  1203,  1155,  1508,  1961,
    1677,  3092,  1962,  1773,   549,  2207,   554,  1843,  2211,  2696,
    1127,  1981,  2479,  1138,  2697,  1518,  1930,   911,  1171,   813,
    1983,  1979,  2821,  2357,  1986,  2296,  1980,  1904,  2300,  2301,
    1112,  1163,  2092,  2093,  2094,  2684,  2101,  1905,  2280,  1552,
    2105,  2106,  2107,  2108,  2109,  2110,  -941,   814,   550,  2241,
    2698,  2905,  1205,  1673,  2278,  2279,  2032,  1209,  1709,  2358,
    1916,  1918,  1201,   348,  2302,   324,  2244,  1981,  1888,  2248,
    1197,  1715,   556,  1983,  2740,  1846,  1931,  1202,  2823,  2324,
     588,   872,   554,  2382,  1903,  2754,   554,   554,   509,   562,
    1138,  3015,  2444,  1198,  2860,   564,   831,  2690,  2690,  2690,
    1552,  1984,  2934,  2762,  2763,  1101,  -941,  1906,  2049,  2050,
    1804,  2055,   554,   554,  2861,   589,  1808,  1607,  2766,  2712,
     554,  2008,  1774,  2445,  2715,  2788,   325,  1278,  3016,  1983,
    1279,  1985,  1282,  2009,  3017,  2082,   554,  1249,  2357,  1932,
     554,  -344,  2446,  1321,   590,   854,  1102,  2998,  2374,  2375,
    2359,   554,  2378,  2047,  1601,  1984,  2999,   566,  1602,   554,
    2383,  2387,  2388,  2389,   815,  1314,  2432,  2832,  1320,  -941,
    1836,  1101,  1837,  2038,  -185,   554,  1327,  2051,  1101,  2056,
    2057,  2058,  1986,  1103,  2061,  1985, -1658,   567,  2767,  -941,
    2067,  2068,  2069,  2070,  2071,  2072,   920,  2077,  2078,  2079,
    2080,  2081,  2095,  2083,   569,  2436,  1041,  1042,  1984,  1104,
    1253,   327,  1102,  2360,  2699,  2700,   176,   177,  1907,  1102,
     371,  2526,  2833,  2834,  2835,  -941,  1775,  2527,   572,  1776,
    1777,  1043,  1044,  1631,  1767,  1632,  1986,   571,  1985,  1633,
    2528,  -941,  1254,  2096,  2768,   510,   511,   326,  2769,  1103,
    1778,   582,  1786,  1787,  1172,  1779,  1103,   327,   592,  1791,
    1780,   376,   593,  2770,  1984,  -185,  2119,   594,  2269,  2384,
    2385,   595,  -165,  2771,   921,  1104,   787,   328,  2120,  1800,
    2097,  2121,  1104,  2869,   596,  1255,  2445, -1658,   597,  1986,
    1807,  1296,  1297,  2870,  1985,   796,  1812,  2871,   381,  2755,
    2258,  2259,  2758,  1307,  1308,  2446,  2098,  1818,  2744,   598,
    2761,   344,  2275,  2276,  1105,  1513,   599,   513,  1825,   515,
    2039,   348,   789,  1515,   382,  -310,   600,  1256,  -185,  1895,
     601,  1896,  2506,  1990,  2396,   810,  2398,  -941,  -941,   602,
    2645,   604,  3075,  2745,  2612,  1986,  2306,  2307,   329,   605,
    -941,  2052,  -941,  2520,  2521,  -941,  2545,  2546,   606,   816,
     817,   818,   819,   820,   821,   607,  2368,  2167,  2168,  1612,
    2772,   608,  2773,   610,   554,  2774,   554,  2571,  2572,  1613,
    1105,  1089,  1090,  1091,  1092,  1093,  1577,  1105,  2775,   611,
     554,  2205,   614,  1138,  1127,  1552,  -941,   615,  2404,   616,
     348,  2632,  2572,   867,  2726,  2727,   617,  -941,  1588,  2735,
    1607,  2099,   384,  1889,  -941,  1581,  2776,  2751,  2752,   554,
    2209,   622,  2210,  2907,  2908,   623,   954,  2953,  2908,   398,
    2966,  2967,  1552,   624,  -184,  1610,   554,  3007,  3008,  2039,
     955,  2040,  2053,   625,  1593,   626,  -941,   872,  3011,  2908,
     910,  2777,  2242,  1636,  1138,  3012,  2908,   916,  -941,   629,
    1636,   877,   630,  1655,   930,  3020,  3021,  1647,   631,   348,
    -184,   632,   554,  2041,  3023,  3024,  3025,  3024,  1635,   640,
    -370,  2246,  -941,  2247,   641,  1635,  2878,  -941,  1612,  2880,
     642,  -941,  2881,   643,   956,  3077,  3008,  2884,  1613,  3078,
    3008,  1678,   646,  1679,  3091,  2546,  2692,  2693,   647,  1680,
     648,  1681,  -123,  3051,  3052,  -941,  2954,  2955,   650,  2900,
     652,  1682,  2902,   943,   653,   654,   957,   655,   656,   657,
     939,  1752,  1748,   658,   659,  1758,   660,   348,   661,   348,
     662,   348,   663,  1681,   664,   944,   665,   554,   666,   316,
     559,   958,   667,   952,  2686,  2687,  2377,   668,   669,   670,
    1784,  -184,  2379,   671,   672,   969,   348,  1683,  1684,   673,
     674,   675,   677,  2488,  2489,  -941,   678,   679,   680,   681,
    2679,   682,  2495,  1685,   683,  2992,  2295,   684,   685,   686,
     730,   687,  1686,  -941,  2042,  1687,  1285,   987,  1688,  1683,
    1684,   688,  1689,  1690,   689,   959,   690,  1691,   960,   691,
     692,   693,   695,   696,   697,  1685,   698,   699,   700,  3067,
    -941,   701,   961,  -941,  -184,   702,   703,  1687,  1285,   704,
    1688,  2342,   705,   706,   707,   708,   709,  1692,  1693,   710,
     962,   711,   712,   713,   963,   511,   714,   715,   716,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   717,   718,   719,   723,   724,  1205,   725,   726,
    1693,  2498,   995,  -941,  -941,   999,   628,  1014,  1019,  1694,
    1038,  1662,  1663,  1664,  1695,  1665,  -817,  1097,  1666,  1667,
    1668,  1669,  2567,  2500,  2568,  1114,  1115,  1118,  1125,  1153,
    1156,  1158,  1159,  2442,  1161,  1658,  1162,  1167,  1169,  1696,
    1170,  1694,  1172,  1175,  1180,  1181,  1695,  1184,  1697,  1698,
    1699,  1127,  1187,  2818,  2819,  1188,  1700,   750,  1190,  1192,
    1193,  1195,  1194,  1203,  1701,  1207,  1212,  1213,  1216,  1223,
    1233,  1696,  1235,  1239,  1246,  2636,  1241,  1174,  2569,  1243,
    1697,  1698,  1699,  1245,   370,  1252,  1268,  1312,   371,  1322,
    1324,  1702,  1127,  2653,  1326,  1925,  1701,   554,  2376,  1329,
     554,   373,  1331,  1703,  1330,  1333,  1336,  1337,  1338,  1342,
    2469,  1345,  1127,  1346,  1348,  1405,  1349,  1350,  1351,  1510,
    1959,  2238,  1929,  1702,  1352,  1163,  1360,  1366,  1367,   376,
    1517,  1368,   554,  1419,  1373,  1703,  1375,   751,  1376,  1383,
    1977,  1384,  1385,   554,  1670,   554,  1388,   752,  1416,  1426,
    1439,  1440,  1441,  1450,  1494,  1495,  1496,  1969,  1497,  1498,
    1499,   378,  1507,  1558,  1523,   380,   381,  1993,  1988,  1511,
    1512,  -546,  1557,  1560,  1562,  1572,  1578,   554,   554,  1580,
     346,  1585,  1784,  1596,  2017,  2022,   753,  1600,   348,  1704,
     348,   348,   382,  1598,  1628,   880,   754,   755,  1629,  1639,
    1673,  1640,  1249,  2000,  1642,  1644,  1717,   881,  1718,  1719,
     882,  1705,  1720,   883,  1721,   884,  1722,   756,  1723,   885,
    1724,  1704,  1725,  1726,   886,  1706,   384,  1727,  1728,  1729,
     385,  1730,   887,  1731,  1735,  1707,  1732,   888,   889,  1741,
    1746,   390,  1753,  1705,  1759,  1760,  1768,  1796,   890,   433,
    1813,  2091,   891,  1819,  2945,  2946,  2947,  1835,  1879,  1883,
    1884,  1886,  1894,  1954,  1901,  1956,  2539,  1707,  2851,  1958,
    1960,  1991,  1996,  1997,  1998,  2002,  2003,  2005,  2006,   554,
     757,  2007,  2126,  2031,  2039,  2060,  2063,  2059,  2062,  2064,
    2065,  2066,  2852,  2853,  2085,  -370,  2124,   398,  2133,  1607,
    2141,  2128,  2145,  2147,  2123,  2146,  2148,   893,  2149,  2150,
       1,  2151,     2,  2156,  2162,  2165,  2164,   894,  2169,  2172,
    2173,  2177,  2815,  2178,  2192,  1658,  2185,  -123,   758,  2234,
     895,  2202,  2237,     3,     4,  2229,  2250,     5,  2253,     6,
    2240,  1127,     7,  2252,  1947,     8,  2277,  1946,     9,  2281,
      10,    11,  2297,    12,  2845,    13,    14,    15,  2288,    16,
      17,  2289,    18,  2311,  2308,  2314,  2322,    19,    20,    21,
    2418,    22,    23,  2887,    24,    25,    26,    27,  2369,  2333,
      28,  2430,  2346,    29,  2397,  2370,  1747,    30,    31,  2438,
      32,  2437,  2440,  2443,  2450,  2451,  2456,  2457,  2459,    33,
    2461,  2476,  2477,  2484,  2493,   896,  2490,  2494,  2512,    34,
    2497,  2499,  2885,    35,    36,   897,  2504,   898,  2505,  2509,
    2513,  2525,  2233,  2532,  2533,  2854,  2855,  2541,  2903,    37,
      38,  2556,  2544,  2557,  2633,   899,  2631,  2637,  2639,  2641,
    2643,  2644,  2646,  2295,  2647,  2654,   759,   760,   761,   762,
     763,   764,   765,   766,  2655,    39,  2661,  2668,  2669,  2666,
    2478,  3076,  2675,  2670,  2665,  2677,  2674,   900,  2681,  2680,
    2682,  2703,  2708,  2710,  2711,  2714,  2023,  2722,  2730,  2731,
    2342,  2732,   768,   769,   770,   771,   772,  2756,  2739,  2808,
    2807,  2270,  2272,  2809,  2741,  2811,  2814,  2817,  2765,  2785,
    2867,  2786,  2787,  2789,  1277,  2827,  2792,  2838,  2825,   773,
     774,   775,   776,  2828,  2829,  2839,  2844,  3100,  2727,  2868,
    2782,  2848,  2883,  2849,   777,   778,   779,   780,  2877,  2305,
     781,  2876,  2879,  2890,  2891,   925,   348,  2892,  2893,  2895,
     492,   348,  2896,  2313,  2897,  2315,  2898,  2910,  2899,  2901,
     782,   783,   348,  2911,   370,  2915,    40,  2916,   371,  2928,
      41,  2930,    42,  2942,  2937,  1577,  2939,    43,  2944,  2351,
    1784,   373,   784,   785,  2965,   348,   348,  2975,  2091,  2972,
    2974,  2976,  2977,  2983,  2091,  2978,  2979,  2091,  2091,  2984,
    2967,  2980,  2091,  2091,  2993,  2994,  2995,  2996,  3002,   376,
    1681,  3004,  3022,  3044,  3040,  3046,  3005,    44,  3006,  3047,
    1209,  3031,  1209,  3049,   554,  3054,   348,  2521,   348,  2414,
    2091,  3056,  3061,  3068,  2091,  2410,  3066,  3042,  3043,  2805,
    3045,   378,  3081,  3082,  3085,   380,   381,  3086,  3090,  2390,
    1174,  3089,  3096,  2132,    45,    46,  2112,  -992,  2539,  3098,
    2904,   554,  2091,  1733,   570,  3099,  1683,  1684,  3063,  2794,
    2084,  1675,   382,  2949,  3065,  2423,  2737,  2043,  2415,  2088,
    2361,  -303,  1685,  2733,  2736,  -303,  2419,  2746,  3072,   880,
    3073,  3074,  2747,  2790,  1687,  1285,  2968,  1688,  2859,  2894,
    2886,   881,  2734,  2530,   882,  3055,   384,   883,  3059,   884,
     385,  2964,  3019,   885,  2982,  2405,  2971,  2565,   886,  2254,
    1972,   390,  1740,  1992,  1999,  1599,   887,  1611,  2483,  2251,
    1273,   888,   889,  2255,  3003,   915,  1179,  1693,  1945,   914,
    2284,  3010,   890,  2935,  1785,   974,   891,  3101,  2851,   892,
    2813,  2265,   994,    47,  1294,  1295,  1296,  1297,  1298,  1299,
    1300,  2134,  1301,  1302,  1303,  1304,  1305,  1306,  1307,  1308,
     951,  1340,  2852,  2853,  1656,  3088,  2336,   398,  1694,  2718,
    2717,  2842,  2683,  1695,  3079,   913,   859,  1761,  1319,  1568,
    2482,  2986,   940,  2997,  3036,  3048,  1745,  2889,   554,  2721,
    1576,   893,  2004,    48,  2329,  2534,  2709,  2840,  1696,  1934,
     908,   894,  1638,  1251,  2943,  2496,  1643,  1697,  1698,  1699,
    2522,  2948,  1754,  1929,   895,     0,     0,     0,     0,     0,
       0,     0,     0,  1701,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1993,     0,     0,     0,     0,
    1702,     0,     0,     0,  2351,     0,     0,     0,     0,     0,
     348,     0,  1703,     0,     0,     0,     0,  1647,     0,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,     0,  -303,     0,  2806,   603,     0,     0,   896,
       0,     0,     0,     0,     0,  2854,  2855,     0,     0,   897,
    2091,   898,     0,   621,     0,     0,     0,  2091,  1784,     0,
       0,     0,     0,     0,   348,     0,     0,     0,  3034,   899,
       0,     0,  1277,     0,  1277,     0,     0,   644,     0,     0,
       0,     0,     0,     0,     0,   554,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   750,  1704,  2573,
       0,   900,   554,     0,     0,     0,  2629,   676,   554,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1705,     0,     0,     0,     0,     0,     0,  2574,     0,  1784,
       0,     0,     0,  2630,     0,   348,     0,     0,     0,     0,
       0,     0,     0,     0,  1707,     0,     0,     0,     0,     0,
    3034,     0,     0,   635,   637,   639,     0,   727,   728,   729,
     731,   732,     0,     0,     0,     0,  2342,     0,     0,     0,
       0,  2973,  2673,     0,     0,     0,     0,   751,   348,     0,
       0,     0,     0,     0,     0,  1925,     0,   752,  1277,  1277,
       0,  1277,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2428,     0,     0,     0,     0,  2694,
       0,     0,     0,   348,     0,     0,     0,     0,     0,  1277,
       0,     0,     0,     0,     0,     0,   753,     0,     0,     0,
       0,     0,     0,     0,  1577,     0,   754,   755,     0,  1277,
       0,  1277,  1277,     0,  2091,     0,     0,     0,     0,     0,
       0,  2091,     0,   941,     0,     0,     0,   756,  3026,     0,
    2091,     0,     0,     0,     0,     0,   968,     0,     0,   975,
       0,     0,     0,     0,     0,   981,   982,     0,   983,   984,
     985,   986,     0,     0,     0,     0,     0,     0,   991,   992,
     993,     0,     0,     0,     0,     0,   998,     0,  1000,  1001,
    1002,     0,     0,     0,  1004,     0,     0,     0,  1007,     0,
    1008,     0,  1009,     0,  1010,     0,     0,     0,     0,     0,
     757,  1016,  1017,     0,  1018,  2799,     0,  1020,  1021,  1022,
    1023,  1024,  1025,  1026,  1027,  1028,  1029,     0,  1031,  1032,
    1033,  1034,  1035,  1036,     0,     0,     0,     0,  1046,  1047,
       0,  1049,  1050,  1051,     0,  1053,  1054,  1055,  1056,  1057,
    1058,  1059,  1060,  1061,     0,     0,     0,  1065,   758,  1066,
    1067,  1068,  1069,  1070,     0,     0,  1075,  1076,  1077,  1078,
    1079,  1080,  1081,  1082,  1086,     0,     0,     0,     0,     0,
       0,     0,  1096,     0,     0,     0,     0,  1098,  1099,  1100,
       0,     0,     0,     0,     0,     0,     0,  1109,     0,     0,
       0,  1116,     0,  1117,     0,     0,     0,     0,  2799,     0,
       0,  1121,  1122,  1123,  1124,     0,     0,     0,  1133,  1134,
    1135,  1136,     0,  1139,  1140,  1141,  1143,  1145,  1146,  1147,
    1148,  1151,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2351,     0,     0,     0,     0,     0,   348,     0,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,   759,   760,   761,   762,
     763,   764,   765,   766,     0,   554,     0,  1107,  1108,     0,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,  2941,     0,     0,     0,     0,     0,     0,
    2917,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2799,  2799,   750,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2963,   750,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,   750,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     880,     0,     0,     0,     0,     0,  2799,     0,     0,     0,
       0,     0,   881,     0,     0,   882,     0,     0,   883,     0,
     884,     0,     0,     0,   885,     0,  1681,     0,   751,   886,
       0,     0,     0,     0,     0,     0,     0,   887,   752,     0,
    2305,   751,   888,   889,     0,     0,     0,     0,     0,     0,
       0,   752,   750,   890,     0,     0,     0,   891,     0,     0,
     906,     0,     0,     0,     0,     0,     0,     0,   751,     0,
       0,     0,     0,     0,     0,     0,     0,   753,   752,     0,
       0,     0,  1683,  1684,     0,     0,     0,   754,   755,     0,
     753,     0,     0,     0,     0,     0,     0,     0,  1685,     0,
     754,   755,     0,  2941,  2941,     0,  3053,     0,   756,     0,
    1687,  1285,   893,  1688,     0,     0,     0,   753,     0,  3060,
       0,   756,   894,     0,     0,     0,     0,   754,   755,     0,
       0,     0,   751,     0,     0,   895,     0,     0,  3071,     0,
       0,     0,   752,     0,     0,     0,     0,     0,   756,     0,
       0,     0,     0,  1693,     0,     0,     0,     0,     0,     0,
       0,     0,  1358,     0,     0,     0,     0,  1487,  1489,  1491,
       0,   757,     0,     0,     0,     0,     0,     0,     0,     0,
    1577,   753,     0,     0,   757,     0,     0,     0,     0,     0,
       0,   754,   755,     0,  1694,     0,     0,     0,  1514,  1695,
       0,     0,  1516,     0,     0,     0,     0,     0,     0,     0,
     896,   757,   756,     0,     0,  1526,     0,     0,     0,   758,
     897,     0,   898,     0,  1696,     0,     0,     0,     0,     0,
       0,     0,   758,  1697,  1698,  1699,     0,  1556,     0,     0,
     899,     0,     0,     0,     0,     0,     0,     0,     0,  1701,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   758,
       0,     0,  1575,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   900,     0,     0,   757,  1702,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1703,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
       0,     0,     0,   758,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   759,   760,   761,
     762,   763,   764,   765,   766,     0,     0,     0,     0,  1359,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
       0,  1364,  1365,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1704,     0,     0,   759,   760,   761,
     762,   763,   764,   765,   766,   750,     0,     0,  1378,  1379,
       0,     0,     0,     0,     0,     0,  1705,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1750,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1707,     0,     0,     0,     0,  1765,     0,  1766,     0,     0,
       0,  1769,     0,     0,     0,     0,     0,  1771,  1772,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,  1788,
       0,  1789,  1381,  1382,     0,  1792,  1793,     0,     0,     0,
       0,     0,     0,  1794,     0,   751,  1795,     0,     0,     0,
       0,  1798,     0,     0,  1801,   752,     0,     0,     0,     0,
       0,  1805,     0,  1806,     0,     0,     0,  1809,  1810,  1811,
       0,     0,     0,  1814,     0,  1815,     0,  1816,     0,  1817,
       0,     0,     0,  1820,     0,  1821,     0,  1822,     0,  1823,
       0,  1824,     0,  1826,   753,     0,     0,     0,  1827,     0,
    1828,     0,  1829,     0,   754,   755,     0,     0,     0,     0,
    1830,  1831,     0,  1832,     0,  1833,  1834,     0,     0,  1838,
    1839,  1840,  1841,  1842,     0,   756,  1847,  1848,  1849,  1850,
       0,  1852,  1853,  1854,  1856,  1858,  1859,  1860,  1861,  1862,
       0,  1864,  1865,     0,  1866,     0,  1868,  1869,  1870,  1871,
    1872,     0,  1874,     0,  1876,     0,  1878,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1880,     0,     0,
    1881,  1882,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,   757,     0,
       0,     0,  1892,  1893,     0,     0,  1897,  1898,  1899,  1900,
       0,     0,     0,  1908,  1909,  1910,  1911,     0,  1913,  1914,
    1915,  1917,  1919,  1920,  1921,  1922,  1923,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1937,
       0,     0,     0,     0,     0,     0,   758,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
     750,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   750,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,   750,
     751,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     752,     0,   750,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   759,   760,   761,   762,   763,   764,
     765,   766,     0,     0,     0,  1396,  1397,   750,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   753,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   754,
     755,     0,     0,     0,   750,   751,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   752,     0,     0,     0,   751,
     756,     0,     0,     0,   825,     0,     0,     0,     0,   752,
     826,   827,   751,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   752,     0,  2138,     0,     0,     0,     0,   828,
       0,     0,     0,     0,   753,     0,     0,   751,     0,     0,
       0,     0,     0,   829,   754,   755,     0,   752,   753,     0,
    2161,     0,     0,     0,     0,     0,     0,     0,   754,   755,
       0,   753,     0,   757,   751,   756,   830,   801,     0,     0,
       0,   754,   755,     0,   752,     0,     0,     0,   831,   756,
       0,     0,     0,   832,     0,   833,   753,     0,     0,  2201,
     834,     0,   756,     0,     0,     0,   754,   755,     0,  2206,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   758,     0,   753,     0,     0,     0,   756,   835,     0,
     836,  2215,   837,   754,   755,     0,     0,  2223,   757,  2225,
       0,  2227,     0,     0,   838,   839,     0,     0,   840,     0,
       0,     0,   757,   841,   756,  2235,     0,     0,  2236,     0,
       0,     0,   842,     0,   843,   757,     0,     0,     0,     0,
    2243,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   758,     0,     0,     0,
     757,     0,     0,     0,     0,   844,     0,     0,     0,     0,
     758,     0,     0,     0,     0,     0,   845,     0,     0,     0,
       0,     0,     0,   758,     0,     0,     0,   757,   846,     0,
       0,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,   758,   759,
     760,   761,   762,   763,   764,   765,   766,   847,     0,     0,
    1398,  1399,     0,   848,   849,     0,     0,   850,   851,     0,
       0,     0,     0,     0,     0,   758,     0,     0,     0,     0,
       0,     0,     0,     0,  2320,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0, -1509,     0,     0,
       0,     0,     0,     0,     0,   852,   853,     0,  2347,     0,
     854,     0,   750,     0,   759,   760,   761,   762,   763,   764,
     765,   766,     0,     0,     0,  1402,  1403,     0,   759,   760,
     761,   762,   763,   764,   765,   766,     0,     0,     0,  1408,
    1409,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,     0,  1410,  1411,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,     0,   855, -1148,  1412,  1413,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   751,   759,   760,   761,   762,   763,   764,   765,
     766,     0,   752,     0,  1414,  1415,     0,     0,     0,     0,
       0,  2441,     0,     0,     0,     0,     0,     0,     0,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,  2452,     0,     0,     0,     0,  2453,  2454,     0,
    2455,   753,     0,     0,     0,     0,     0,     0,     0,  2458,
       0,   754,   755,     0,     0,     0,     0,   750,     0,     0,
       0,  2462,     0,     0,     0,  2463,     0,     0,  2464,     0,
       0,     0,   756,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2467,     0,     0,     0,  2468,     0,     0,     0,
       0,  2470,     0,     0,  2471,  2472,     0,   750,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2481,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,     0,     0,   757,     0,   751,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   752,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,   751,     0,     0,
       0,     0,     0,   758,     0,     0,   753,   752,     0,     0,
       0,   603,     0,     0,     0,     0,   754,   755,   750,     0,
       0,     0,     0,     0,  2535,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   756,     0,  2548,
       0,     0,     0,     0,     0,     0,   753,     0,     0,     0,
       0,  2555,     0,     0,     0,     0,   754,   755,     0,     0,
       0,   750,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   756,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,     0,     0,     0,     0,     0,     0,   751,     0,
     757,     0,     0,     0,     0,     0,     0,     0,   752,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,     0,  1424,  1425,     0,     0,     0,     0,     0,     0,
     757,   751,     0,     0,     0,     0,     0,   753,   758,     0,
       0,   752,     0,     0,     0,     0,   750,   754,   755,     0,
    2659,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,  2667,     0,     0,     0,   756,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   758,     0,
     753,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     754,   755,     0,     0,     0,     0,     0,     0,  2688,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   756,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   751,     0,     0,   750,
       0,   757,     0,     0,     0,     0,   752,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,     0,     0,     0,  1433,  1434,     0,
       0,     0,     0,     0,   757,   753,     0,     0,     0,   758,
       0,     0,     0,     0,     0,   754,   755,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,     0,     0,   756,  1435,  1436,   751,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   752,
       0,     0,   758,     0,     0,     0,  2802,     0,     0,     0,
       0,     0,     0,  2803,     0,     0,  2804,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   753,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   757,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   756,
       0,     0,     0,     0,     0,     0,  2320,   759,   760,   761,
     762,   763,   764,   765,   766,     0,  2548,     0,  1437,  1438,
       0,     0,     0,     0,     0,     0,     0,   758,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
       0,  1445,  1446,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2548,     0,     0,     0,     0,     0,     0,     0,
     758,     0,     0,     0,     0,  2936,     0,  2938,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   759,   760,   761,   762,   763,
     764,   765,   766,     0,     0,     0,  1448,  1449,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2985,     0,
       0,     0,     0,     0,  2991,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   759,   760,
     761,   762,   763,   764,   765,   766,     0,     0,     0,     0,
       0,     0,    99,   100,   101,   102,   103,     0,     0,     0,
     104,     0,     0,     0,     0,     0,     0,   351,     0,     0,
       0,     0,     0,   105,     0,     0,   106,   352,   108,   109,
       0,   110,   111,   112,   113,   353,     0,     0,   114,     0,
       0,   115,  2548,   116,   117,   118,   119,   120,   354,   121,
       0,     0,   122,     0,   123,   355,   356,   124,  3050,     0,
     125,   126,   127,   128,   129,   130,     0,     0,   131,   132,
     133,   134,   357,   358,   135,   359,   360,   137,   361,     0,
     139,     0,   140,   141,     0,     0,     0,     0,   142,   143,
     144,   145,   362,   146,   147,   148,  1083,   149,     0,   150,
     151,     0,   363,   364,   153,     0,   154,     0,   365,     0,
       0,   156,     0,   366,   367,     0,   157,   368,     0,   158,
       0,     0,   159,   160,   161,     0,   162,   163,   164,     0,
       0,   165,   166,   369,   167,   370,   168,   169,   170,   371,
       0,     0,     0,   171,     0,   172,  3097,   173,   372,     0,
       0,   174,   373,     0,   175,   176,   177,     0,   178,     0,
     179,     0,     0,   180,     0,     0,   181,     0,     0,     0,
    1084,   374,   182,   183,     0,     0,     0,   184,   375,   185,
     376,     0,     0,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   377,
     202,   203,   204,   205,   206,   207,   208,   209,     0,   210,
     211,   212,   378,   213,   379,   214,   380,   381,   215,     0,
     216,   217,     0,     0,     0,     0,     0,     0,     0,   218,
     219,   220,     0,     0,   221,   222,   223,   224,   225,   226,
     227,   228,     0,   382,     0,     0,   229,     0,   230,     0,
     231,   232,     0,     0,   233,   234,   383,   236,     0,     0,
     237,   238,   239,   240,   241,     0,     0,     0,   242,   243,
       0,   244,     0,     0,   245,   246,     0,   384,     0,  1085,
     247,   385,   248,   249,   386,   387,   388,   389,   250,     0,
     251,   252,   390,   253,     0,     0,     0,   254,     0,     0,
     255,   391,   256,     0,     0,     0,     0,   257,     0,   258,
     259,   260,   392,     0,     0,   393,   262,   394,   263,   395,
       0,     0,   265,   266,     0,   267,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   268,   269,   270,     0,   271,
       0,   272,   273,   396,   397,     0,     0,     0,   398,     0,
       0,     0,     0,     0,   276,   399,     0,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,     0,
       0,     0,     0,   412,   413,   414,   415,     0,   416,   417,
     278,   279,   418,   419,   420,   421,   422,     0,   423,   424,
     425,   426,   427,   428,   429,   430,     0,     0,     0,   431,
     283,   432,   284,   433,   434,   435,   436,   437,   438,   439,
     440,   441,     0,     0,   442,   288,   289,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,     0,   458,   459,   460,   461,   462,     0,   299,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   477,   478,   479,     0,   302,     0,
     480,   481,   482,   304,     0,     0,   305,     0,   306,     0,
     307,   308,   309,     0,     0,     0,   483,   484,     0,     0,
       0,     0,   485,     0,   486,     0,     0,   487,   488,     0,
     489,   490,   491,    99,   100,   101,   102,   103,     0,     0,
       0,   104,     0,     0,     0,     0,     0,     0,   351,     0,
       0,     0,     0,     0,   105,     0,     0,   106,   352,   108,
     109,     0,   110,   111,   112,   113,   353,     0,     0,   114,
       0,     0,   115,     0,   116,   117,   118,   119,   120,   354,
     121,     0,     0,   122,     0,   123,   355,   356,   124,     0,
       0,   125,   126,   127,   128,   129,   130,     0,     0,   131,
     132,   133,   134,   357,   358,   135,   359,   360,   137,   361,
       0,   139,     0,   140,   141,  2316,     0,     0,     0,   142,
     143,   144,   145,  2317,   146,   147,   148,     0,   149,     0,
     150,   151,     0,   363,   364,   153,     0,   154,     0,   365,
       0,     0,   156,     0,   366,   367,     0,   157,  2318,     0,
     158,     0,     0,   159,   160,   161,     0,   162,   163,   164,
       0,     0,   165,   166,   369,   167,   370,   168,   169,   170,
     371,     0,     0,     0,   171,     0,   172,     0,   173,   372,
       0,     0,   174,   373,     0,   175,   176,   177,     0,   178,
       0,   179,     0,     0,   180,     0,     0,   181,     0,     0,
       0,     0,   374,   182,   183,     0,     0,     0,   184,   375,
     185,   376,     0,     0,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     377,   202,   203,   204,   205,   206,   207,   208,   209,     0,
     210,   211,   212,   378,   213,   379,   214,   380,   381,   215,
    2319,   216,   217,     0,     0,     0,     0,     0,     0,     0,
     218,   219,   220,     0,     0,   221,   222,   223,   224,   225,
     226,   227,   228,     0,   382,     0,     0,   229,     0,   230,
       0,   231,   232,     0,     0,   233,   234,   383,   236,     0,
       0,   237,   238,   239,   240,   241,     0,     0,     0,   242,
     243,     0,   244,     0,     0,   245,   246,     0,   384,     0,
       0,   247,   385,   248,   249,   386,   387,   388,   389,   250,
       0,   251,   252,   390,   253,     0,     0,     0,   254,     0,
       0,   255,   391,   256,     0,     0,     0,     0,   257,     0,
     258,   259,   260,   392,     0,     0,   393,   262,   394,   263,
     395,     0,     0,   265,   266,     0,   267,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   268,   269,   270,     0,
     271,     0,   272,   273,   396,   397,     0,     0,     0,   398,
       0,     0,     0,     0,     0,   276,   399,     0,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
       0,     0,     0,     0,   412,   413,   414,   415,     0,   416,
     417,   278,   279,   418,   419,   420,   421,   422,     0,   423,
     424,   425,   426,   427,   428,   429,   430,     0,     0,     0,
     431,   283,   432,   284,   433,   434,   435,   436,   437,   438,
     439,   440,   441,     0,     0,   442,   288,   289,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,     0,   458,   459,   460,   461,   462,     0,
     299,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,     0,   302,
       0,   480,   481,   482,   304,     0,     0,   305,     0,   306,
       0,   307,   308,   309,     0,     0,     0,   483,   484,     0,
       0,     0,     0,   485,     0,   486,     0,     0,   487,   488,
       0,   489,   490,   491,    99,   100,   101,   102,   103,     0,
       0,     0,   104,     0,     0,     0,     0,     0,     0,   351,
       0,     0,     0,     0,     0,   105,     0,     0,   106,   352,
     108,   109,     0,   110,   111,   112,   113,   353,     0,     0,
     114,     0,     0,   115,     0,   116,   117,   118,   119,   120,
     354,   121,     0,     0,   122,     0,   123,   355,   356,   124,
       0,     0,   125,   126,   127,   128,   129,   130,   730,     0,
     131,   132,   133,   134,   357,   358,   135,   359,   360,   137,
     361,     0,   139,     0,   140,   141,     0,     0,     0,     0,
     142,   143,   144,   145,   362,   146,   147,   148,     0,   149,
       0,   150,   151,     0,   363,   364,   153,     0,   154,     0,
     365,     0,     0,   156,     0,   366,   367,     0,   157,   368,
       0,   158,     0,     0,   159,   160,   161,     0,   162,   163,
     164,     0,     0,   165,   166,   369,   167,   370,   168,   169,
     170,   371,     0,     0,     0,   171,     0,   172,     0,   173,
     372,     0,     0,   174,   373,     0,   175,   176,   177,     0,
     178,     0,   179,     0,     0,   180,     0,     0,   181,     0,
       0,     0,     0,   374,   182,   183,     0,     0,     0,   184,
     375,   185,   376,     0,     0,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   377,   202,   203,   204,   205,   206,   207,   208,   209,
       0,   210,   211,   212,   378,   213,   379,   214,   380,   381,
     215,     0,   216,   217,     0,     0,     0,     0,     0,     0,
       0,   218,   219,   220,     0,     0,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   382,     0,     0,   229,     0,
     230,     0,   231,   232,     0,     0,   233,   234,   383,   236,
       0,     0,   237,   238,   239,   240,   241,     0,     0,     0,
     242,   243,     0,   244,     0,     0,   245,   246,     0,   384,
       0,     0,   247,   385,   248,   249,   386,   387,   388,   389,
     250,     0,   251,   252,   390,   253,     0,     0,     0,   254,
       0,     0,   255,   391,   256,     0,     0,     0,     0,   257,
       0,   258,   259,   260,   392,     0,     0,   393,   262,   394,
     263,   395,     0,     0,   265,   266,     0,   267,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   268,   269,   270,
       0,   271,     0,   272,   273,   396,   397,     0,     0,     0,
     398,     0,     0,     0,     0,     0,   276,   399,     0,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,     0,     0,     0,     0,   412,   413,   414,   415,     0,
     416,   417,   278,   279,   418,   419,   420,   421,   422,     0,
     423,   424,   425,   426,   427,   428,   429,   430,     0,     0,
       0,   431,   283,   432,   284,   433,   434,   435,   436,   437,
     438,   439,   440,   441,     0,     0,   442,   288,   289,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,     0,   458,   459,   460,   461,   462,
       0,   299,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,     0,
     302,     0,   480,   481,   482,   304,     0,     0,   305,     0,
     306,     0,   307,   308,   309,     0,     0,     0,   483,   484,
       0,     0,     0,     0,   485,     0,   486,     0,     0,   487,
     488,     0,   489,   490,   491,    99,   100,   101,   102,   103,
       0,     0,     0,   104,     0,     0,     0,     0,     0,     0,
     351,     0,     0,     0,     0,     0,   105,     0,     0,   106,
     352,   108,   109,     0,   110,   111,   112,   113,   353,     0,
       0,   114,     0,     0,   115,     0,   116,   117,   118,   119,
     120,   354,   121,     0,     0,   122,     0,   123,   355,   356,
     124,     0,     0,   125,   126,   127,   128,   129,   130,     0,
       0,   131,   132,   133,   134,   357,   358,   135,   359,   360,
     137,   361,     0,   139,     0,   140,   141,     0,     0,     0,
       0,   142,   143,   144,   145,   362,   146,   147,   148,     0,
     149,     0,   150,   151,     0,   363,   364,   153,     0,   154,
       0,   365,     0,     0,   156,     0,   366,   367,     0,   157,
     368,     0,   158,     0,     0,   159,   160,   161,     0,   162,
     163,   164,     0,     0,   165,   166,   369,   167,   370,   168,
     169,   170,   371,     0,     0,     0,   171,     0,   172,     0,
     173,   372,     0,     0,   174,   373,     0,   175,   176,   177,
       0,   178,     0,   179,     0,     0,   180,     0,     0,   181,
       0,     0,     0,     0,   374,   182,   183,     0,     0,     0,
     184,   375,   185,   376,     0,     0,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   377,   202,   203,   204,   205,   206,   207,   208,
     209,     0,   210,   211,   212,   378,   213,   379,   214,   380,
     381,   215,     0,   216,   217,     0,     0,     0,     0,     0,
       0,     0,   218,   219,   220,     0,     0,   221,   222,   223,
     224,   225,   226,   227,   228,     0,   382,     0,     0,   229,
       0,   230,     0,   231,   232,     0,     0,   233,   234,   383,
     236,     0,     0,   237,   238,   239,   240,   241,     0,     0,
       0,   242,   243,     0,   244,     0,     0,   245,   246,     0,
     384,     0,     0,   247,   385,   248,   249,   386,   387,   388,
     389,   250,     0,   251,   252,   390,   253,     0,     0,     0,
     254,     0,     0,   255,   391,   256,     0,     0,     0,     0,
     257,     0,   258,   259,   260,   392,     0,     0,   393,   262,
     394,   263,   395,     0,     0,   265,   266,     0,   267,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   268,   269,
     270,     0,   271,     0,   272,   273,   396,   397,     0,     0,
       0,   398,     0,     0,     0,     0,     0,   276,   399,     0,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,     0,     0,     0,     0,   412,   413,   414,   415,
       0,   416,   417,   278,   279,   418,   419,   420,   421,   422,
       0,   423,   424,   425,   426,   427,   428,   429,   430,     0,
       0,     0,   431,   283,   432,   284,   433,   434,   435,   436,
     437,   438,   439,   440,   441,     0,     0,   442,   288,   289,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,     0,   458,   459,   460,   461,
     462,     0,   299,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
       0,   302,     0,   480,   481,   482,   304,     0,     0,   305,
       0,   306,     0,   307,   308,   309,     0,     0,     0,   483,
     484,     0,     0,     0,     0,   485,     0,   486,   987,     0,
     487,   488,     0,   489,   490,   491,    99,   100,   101,   102,
     103,     0,     0,     0,   104,     0,     0,     0,     0,     0,
       0,   351,     0,     0,     0,     0,     0,   105,     0,     0,
     106,   352,   108,   109,     0,   110,   111,   112,   113,   353,
       0,     0,   114,     0,     0,   115,     0,   116,   117,   118,
     119,   120,   354,   121,     0,     0,   122,     0,   123,   355,
     356,   124,     0,     0,   125,   126,   127,   128,   129,   130,
       0,     0,   131,   132,   133,   134,   357,   358,   135,   359,
     360,   137,   361,     0,   139,     0,   140,   141,     0,     0,
       0,     0,   142,   143,   144,   145,   362,   146,   147,   148,
       0,   149,     0,   150,   151,     0,   363,   364,   153,     0,
     154,     0,   365,     0,     0,   156,     0,   366,   367,     0,
     157,   368,     0,   158,     0,     0,   159,   160,   161,     0,
     162,   163,   164,     0,     0,   165,   166,   369,   167,   370,
     168,   169,   170,   371,     0,     0,     0,   171,     0,   172,
       0,   173,   372,     0,     0,   174,   373,     0,   175,   176,
     177,     0,   178,     0,   179,     0,     0,   180,     0,     0,
     181,     0,     0,     0,     0,   374,   182,   183,     0,     0,
       0,   184,   375,   185,   376,     0,     0,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   377,   202,   203,   204,   205,   206,   207,
     208,   209,     0,   210,   211,   212,   378,   213,   379,   214,
     380,   381,   215,     0,   216,   217,     0,     0,     0,     0,
       0,     0,     0,   218,   219,   220,     0,     0,   221,   222,
     223,   224,   225,   226,   227,   228,     0,   382,     0,     0,
     229,     0,   230,     0,   231,   232,     0,     0,   233,   234,
     383,   236,     0,     0,   237,   238,   239,   240,   241,     0,
       0,     0,   242,   243,     0,   244,     0,     0,   245,   246,
       0,   384,     0,     0,   247,   385,   248,   249,   386,   387,
     388,   389,   250,     0,   251,   252,   390,   253,     0,     0,
       0,   254,     0,     0,   255,   391,   256,     0,     0,     0,
       0,   257,     0,   258,   259,   260,   392,     0,     0,   393,
     262,   394,   263,   395,     0,     0,   265,   266,     0,   267,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
     269,   270,     0,   271,     0,   272,   273,   396,   397,     0,
       0,     0,   398,     0,     0,     0,     0,     0,   276,   399,
       0,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,     0,     0,     0,     0,   412,   413,   414,
     415,     0,   416,   417,   278,   279,   418,   419,   420,   421,
     422,     0,   423,   424,   425,   426,   427,   428,   429,   430,
       0,     0,     0,   431,   283,   432,   284,   433,   434,   435,
     436,   437,   438,   439,   440,   441,     0,     0,   442,   288,
     289,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,     0,   458,   459,   460,
     461,   462,     0,   299,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,     0,   302,     0,   480,   481,   482,   304,     0,     0,
     305,     0,   306,     0,   307,   308,   309,     0,     0,     0,
     483,   484,     0,     0,     0,     0,   485,     0,   486,  1048,
       0,   487,   488,     0,   489,   490,   491,    99,   100,   101,
     102,   103,     0,     0,     0,   104,     0,     0,     0,     0,
       0,     0,   351,     0,     0,     0,     0,     0,   105,     0,
       0,   106,   352,   108,   109,     0,   110,   111,   112,   113,
     353,     0,     0,   114,     0,     0,   115,     0,   116,   117,
     118,   119,   120,   354,   121,     0,     0,   122,     0,   123,
     355,   356,   124,     0,     0,   125,   126,   127,   128,   129,
     130,     0,     0,   131,   132,   133,   134,   357,   358,   135,
     359,   360,   137,   361,     0,   139,     0,   140,   141,     0,
       0,     0,     0,   142,   143,   144,   145,   362,   146,   147,
     148,     0,   149,     0,   150,   151,     0,   363,   364,   153,
       0,   154,     0,   365,     0,     0,   156,     0,   366,   367,
       0,   157,   368,     0,   158,     0,     0,   159,   160,   161,
       0,   162,   163,   164,     0,     0,   165,   166,   369,   167,
     370,   168,   169,   170,   371,     0,     0,     0,   171,     0,
     172,     0,   173,   372,     0,     0,   174,   373,     0,   175,
     176,   177,     0,   178,     0,   179,     0,     0,   180,     0,
       0,   181,     0,     0,     0,     0,   374,   182,   183,     0,
       0,     0,   184,   375,   185,   376,     0,     0,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   377,   202,   203,   204,   205,   206,
     207,   208,   209,     0,   210,   211,   212,   378,   213,   379,
     214,   380,   381,   215,     0,   216,   217,     0,     0,     0,
       0,     0,     0,     0,   218,   219,   220,     0,     0,   221,
     222,   223,   224,   225,   226,   227,   228,     0,   382,     0,
       0,   229,     0,   230,     0,   231,   232,     0,     0,   233,
     234,   383,   236,     0,     0,   237,   238,   239,   240,   241,
       0,     0,     0,   242,   243,     0,   244,     0,     0,   245,
     246,     0,   384,     0,     0,   247,   385,   248,   249,   386,
     387,   388,   389,   250,     0,   251,   252,   390,   253,     0,
       0,     0,   254,     0,     0,   255,   391,   256,     0,     0,
       0,     0,   257,     0,   258,   259,   260,   392,     0,     0,
     393,   262,   394,   263,   395,     0,     0,   265,   266,     0,
     267,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     268,   269,   270,     0,   271,     0,   272,   273,   396,   397,
       0,     0,     0,   398,     0,     0,     0,     0,     0,   276,
     399,     0,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,     0,     0,     0,     0,   412,   413,
     414,   415,     0,   416,   417,   278,   279,   418,   419,   420,
     421,   422,     0,   423,   424,   425,   426,   427,   428,   429,
     430,     0,     0,     0,   431,   283,   432,   284,   433,   434,
     435,   436,   437,   438,   439,   440,   441,     0,     0,   442,
     288,   289,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,     0,   458,   459,
     460,   461,   462,     0,   299,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,     0,   302,     0,   480,   481,   482,   304,     0,
       0,   305,     0,   306,     0,   307,   308,   309,     0,     0,
       0,   483,   484,     0,     0,     0,     0,   485,     0,   486,
    1074,     0,   487,   488,     0,   489,   490,   491,    99,   100,
     101,   102,   103,     0,     0,     0,   104,     0,     0,     0,
       0,     0,     0,   351,     0,     0,     0,     0,     0,   105,
       0,     0,   106,   352,   108,   109,     0,   110,   111,   112,
     113,   353,     0,     0,   114,     0,     0,   115,     0,   116,
     117,   118,   119,   120,   354,   121,     0,     0,   122,     0,
     123,   355,   356,   124,     0,     0,   125,   126,   127,   128,
     129,   130,     0,     0,   131,   132,   133,   134,   357,   358,
     135,   359,   360,   137,   361,     0,   139,     0,   140,   141,
       0,     0,     0,     0,   142,   143,   144,   145,   362,   146,
     147,   148,     0,   149,     0,   150,   151,     0,   363,   364,
     153,     0,   154,     0,   365,     0,     0,   156,     0,   366,
     367,     0,   157,   368,     0,   158,     0,     0,   159,   160,
     161,     0,   162,   163,   164,     0,     0,   165,   166,   369,
     167,   370,   168,   169,   170,   371,     0,     0,     0,   171,
       0,   172,     0,   173,   372,     0,     0,   174,   373,     0,
     175,   176,   177,     0,   178,     0,   179,     0,     0,   180,
       0,     0,   181,     0,     0,     0,     0,   374,   182,   183,
       0,     0,     0,   184,   375,   185,   376,     0,     0,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   377,   202,   203,   204,   205,
     206,   207,   208,   209,     0,   210,   211,   212,   378,   213,
     379,   214,   380,   381,   215,     0,   216,   217,     0,     0,
       0,     0,     0,     0,     0,   218,   219,   220,     0,     0,
     221,   222,   223,   224,   225,   226,   227,   228,     0,   382,
       0,     0,   229,     0,   230,     0,   231,   232,     0,     0,
     233,   234,   383,   236,     0,     0,   237,   238,   239,   240,
     241,     0,     0,     0,   242,   243,     0,   244,     0,     0,
     245,   246,     0,   384,     0,     0,   247,   385,   248,   249,
     386,   387,   388,   389,   250,     0,   251,   252,   390,   253,
       0,     0,     0,   254,     0,     0,   255,   391,   256,     0,
       0,     0,     0,   257,     0,   258,   259,   260,   392,     0,
       0,   393,   262,   394,   263,   395,     0,     0,   265,   266,
       0,   267,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,   269,   270,     0,   271,     0,   272,   273,   396,
     397,     0,     0,     0,   398,     0,     0,     0,     0,     0,
     276,   399,     0,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,     0,     0,     0,     0,   412,
     413,   414,   415,     0,   416,   417,   278,   279,   418,   419,
     420,   421,   422,     0,   423,   424,   425,   426,   427,   428,
     429,   430,     0,     0,     0,   431,   283,   432,   284,   433,
     434,   435,   436,   437,   438,   439,   440,   441,     0,     0,
     442,   288,   289,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,     0,   458,
     459,   460,   461,   462,     0,   299,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,     0,   302,     0,   480,   481,   482,   304,
       0,     0,   305,     0,   306,     0,   307,   308,   309,     0,
       0,     0,   483,   484,     0,     0,     0,     0,   485,     0,
     486,  1095,     0,   487,   488,     0,   489,   490,   491,    99,
     100,   101,   102,   103,     0,     0,     0,   104,     0,     0,
       0,     0,     0,     0,   351,     0,     0,     0,     0,     0,
     105,     0,     0,  1149,   352,   108,   109,     0,   110,   111,
     112,   113,   353,     0,     0,   114,     0,     0,   115,     0,
     116,   117,   118,   119,   120,   354,   121,     0,     0,   122,
       0,   123,   355,   356,   124,     0,     0,   125,   126,   127,
     128,   129,   130,     0,     0,   131,   132,   133,   134,   357,
     358,   135,   359,   360,   137,   361,     0,   139,     0,   140,
     141,  1150,     0,     0,     0,   142,   143,   144,   145,   362,
     146,   147,   148,     0,   149,     0,   150,   151,     0,   363,
     364,   153,     0,   154,     0,   365,     0,     0,   156,     0,
     366,   367,     0,   157,   368,     0,   158,     0,     0,   159,
     160,   161,     0,   162,   163,   164,     0,     0,   165,   166,
     369,   167,   370,   168,   169,   170,   371,     0,     0,     0,
     171,     0,   172,     0,   173,   372,     0,     0,   174,   373,
       0,   175,   176,   177,     0,   178,     0,   179,     0,     0,
     180,     0,     0,   181,     0,     0,     0,     0,   374,   182,
     183,     0,     0,     0,   184,   375,   185,   376,     0,     0,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   377,   202,   203,   204,
     205,   206,   207,   208,   209,     0,   210,   211,   212,   378,
     213,   379,   214,   380,   381,   215,     0,   216,   217,     0,
       0,     0,     0,     0,     0,     0,   218,   219,   220,     0,
       0,   221,   222,   223,   224,   225,   226,   227,   228,     0,
     382,     0,     0,   229,     0,   230,     0,   231,   232,     0,
       0,   233,   234,   383,   236,     0,     0,   237,   238,   239,
     240,   241,     0,     0,     0,   242,   243,     0,   244,     0,
       0,   245,   246,     0,   384,     0,     0,   247,   385,   248,
     249,   386,   387,   388,   389,   250,     0,   251,   252,   390,
     253,     0,     0,     0,   254,     0,     0,   255,   391,   256,
       0,     0,     0,     0,   257,     0,   258,   259,   260,   392,
       0,     0,   393,   262,   394,   263,   395,     0,     0,   265,
     266,     0,   267,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   268,   269,   270,     0,   271,     0,   272,   273,
     396,   397,     0,     0,     0,   398,     0,     0,     0,     0,
       0,   276,   399,     0,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,     0,     0,     0,     0,
     412,   413,   414,   415,     0,   416,   417,   278,   279,   418,
     419,   420,   421,   422,     0,   423,   424,   425,   426,   427,
     428,   429,   430,     0,     0,     0,   431,   283,   432,   284,
     433,   434,   435,   436,   437,   438,   439,   440,   441,     0,
       0,   442,   288,   289,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   456,   457,     0,
     458,   459,   460,   461,   462,     0,   299,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,     0,   302,     0,   480,   481,   482,
     304,     0,     0,   305,     0,   306,     0,   307,   308,   309,
       0,     0,     0,   483,   484,     0,     0,     0,     0,   485,
       0,   486,     0,     0,   487,   488,     0,   489,   490,   491,
      99,   100,   101,   102,   103,     0,     0,     0,   104,     0,
       0,     0,     0,     0,     0,   351,     0,     0,     0,     0,
       0,   105,     0,     0,   106,   352,   108,   109,     0,   110,
     111,   112,   113,   353,     0,     0,   114,     0,     0,   115,
       0,   116,   117,   118,   119,   120,   354,   121,     0,     0,
     122,     0,   123,   355,   356,   124,     0,     0,   125,   126,
     127,   128,   129,   130,     0,     0,   131,   132,   133,   134,
     357,   358,   135,   359,   360,   137,   361,     0,   139,     0,
     140,   141,     0,     0,     0,     0,   142,   143,   144,   145,
     362,   146,   147,   148,     0,   149,     0,   150,   151,     0,
     363,   364,   153,     0,   154,     0,   365,     0,     0,   156,
       0,   366,   367,     0,   157,   368,     0,   158,     0,     0,
     159,   160,   161,     0,   162,   163,   164,     0,     0,   165,
     166,   369,   167,   370,   168,   169,   170,   371,     0,     0,
    1486,   171,     0,   172,     0,   173,   372,     0,     0,   174,
     373,     0,   175,   176,   177,     0,   178,     0,   179,     0,
       0,   180,     0,     0,   181,     0,     0,     0,     0,   374,
     182,   183,     0,     0,     0,   184,   375,   185,   376,     0,
       0,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   377,   202,   203,
     204,   205,   206,   207,   208,   209,     0,   210,   211,   212,
     378,   213,   379,   214,   380,   381,   215,     0,   216,   217,
       0,     0,     0,     0,     0,     0,     0,   218,   219,   220,
       0,     0,   221,   222,   223,   224,   225,   226,   227,   228,
       0,   382,     0,     0,   229,     0,   230,     0,   231,   232,
       0,     0,   233,   234,   383,   236,     0,     0,   237,   238,
     239,   240,   241,     0,     0,     0,   242,   243,     0,   244,
       0,     0,   245,   246,     0,   384,     0,     0,   247,   385,
     248,   249,   386,   387,   388,   389,   250,     0,   251,   252,
     390,   253,     0,     0,     0,   254,     0,     0,   255,   391,
     256,     0,     0,     0,     0,   257,     0,   258,   259,   260,
     392,     0,     0,   393,   262,   394,   263,   395,     0,     0,
     265,   266,     0,   267,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   268,   269,   270,     0,   271,     0,   272,
     273,   396,   397,     0,     0,     0,   398,     0,     0,     0,
       0,     0,   276,   399,     0,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,     0,     0,     0,
       0,   412,   413,   414,   415,     0,   416,   417,   278,   279,
     418,   419,   420,   421,   422,     0,   423,   424,   425,   426,
     427,   428,   429,   430,     0,     0,     0,   431,   283,   432,
     284,   433,   434,   435,   436,   437,   438,   439,   440,   441,
       0,     0,   442,   288,   289,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
       0,   458,   459,   460,   461,   462,     0,   299,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,     0,   302,     0,   480,   481,
     482,   304,     0,     0,   305,     0,   306,     0,   307,   308,
     309,     0,     0,     0,   483,   484,     0,     0,     0,     0,
     485,     0,   486,     0,     0,   487,   488,     0,   489,   490,
     491,    99,   100,   101,   102,   103,     0,     0,     0,   104,
       0,     0,     0,     0,     0,     0,   351,     0,     0,     0,
       0,     0,   105,     0,     0,   106,   352,   108,   109,     0,
     110,   111,   112,   113,   353,     0,     0,   114,     0,     0,
     115,     0,   116,   117,   118,   119,   120,   354,   121,     0,
       0,   122,     0,   123,   355,   356,   124,     0,     0,   125,
     126,   127,   128,   129,   130,     0,     0,   131,   132,   133,
     134,   357,   358,   135,   359,   360,   137,   361,     0,   139,
       0,   140,   141,     0,     0,     0,     0,   142,   143,   144,
     145,   362,   146,   147,   148,     0,   149,     0,   150,   151,
       0,   363,   364,   153,     0,   154,     0,   365,     0,     0,
     156,     0,   366,   367,     0,   157,   368,     0,   158,     0,
       0,   159,   160,   161,     0,   162,   163,   164,     0,     0,
     165,   166,   369,   167,   370,   168,   169,   170,   371,     0,
       0,  1488,   171,     0,   172,     0,   173,   372,     0,     0,
     174,   373,     0,   175,   176,   177,     0,   178,     0,   179,
       0,     0,   180,     0,     0,   181,     0,     0,     0,     0,
     374,   182,   183,     0,     0,     0,   184,   375,   185,   376,
       0,     0,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   377,   202,
     203,   204,   205,   206,   207,   208,   209,     0,   210,   211,
     212,   378,   213,   379,   214,   380,   381,   215,     0,   216,
     217,     0,     0,     0,     0,     0,     0,     0,   218,   219,
     220,     0,     0,   221,   222,   223,   224,   225,   226,   227,
     228,     0,   382,     0,     0,   229,     0,   230,     0,   231,
     232,     0,     0,   233,   234,   383,   236,     0,     0,   237,
     238,   239,   240,   241,     0,     0,     0,   242,   243,     0,
     244,     0,     0,   245,   246,     0,   384,     0,     0,   247,
     385,   248,   249,   386,   387,   388,   389,   250,     0,   251,
     252,   390,   253,     0,     0,     0,   254,     0,     0,   255,
     391,   256,     0,     0,     0,     0,   257,     0,   258,   259,
     260,   392,     0,     0,   393,   262,   394,   263,   395,     0,
       0,   265,   266,     0,   267,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   268,   269,   270,     0,   271,     0,
     272,   273,   396,   397,     0,     0,     0,   398,     0,     0,
       0,     0,     0,   276,   399,     0,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,     0,     0,
       0,     0,   412,   413,   414,   415,     0,   416,   417,   278,
     279,   418,   419,   420,   421,   422,     0,   423,   424,   425,
     426,   427,   428,   429,   430,     0,     0,     0,   431,   283,
     432,   284,   433,   434,   435,   436,   437,   438,   439,   440,
     441,     0,     0,   442,   288,   289,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,     0,   458,   459,   460,   461,   462,     0,   299,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,     0,   302,     0,   480,
     481,   482,   304,     0,     0,   305,     0,   306,     0,   307,
     308,   309,     0,     0,     0,   483,   484,     0,     0,     0,
       0,   485,     0,   486,     0,     0,   487,   488,     0,   489,
     490,   491,    99,   100,   101,   102,   103,     0,     0,     0,
     104,     0,     0,     0,     0,     0,     0,   351,     0,     0,
       0,     0,     0,   105,     0,     0,   106,   352,   108,   109,
       0,   110,   111,   112,   113,   353,     0,     0,   114,     0,
       0,   115,     0,   116,   117,   118,   119,   120,   354,   121,
       0,     0,   122,     0,   123,   355,   356,   124,     0,     0,
     125,   126,   127,   128,   129,   130,     0,     0,   131,   132,
     133,   134,   357,   358,   135,   359,   360,   137,   361,     0,
     139,     0,   140,   141,     0,     0,     0,     0,   142,   143,
     144,   145,   362,   146,   147,   148,     0,   149,     0,   150,
     151,     0,   363,   364,   153,     0,   154,     0,   365,     0,
       0,   156,     0,   366,   367,     0,   157,   368,     0,   158,
       0,     0,   159,   160,   161,     0,   162,   163,   164,     0,
       0,   165,   166,   369,   167,   370,   168,   169,   170,   371,
       0,     0,  1490,   171,     0,   172,     0,   173,   372,     0,
       0,   174,   373,     0,   175,   176,   177,     0,   178,     0,
     179,     0,     0,   180,     0,     0,   181,     0,     0,     0,
       0,   374,   182,   183,     0,     0,     0,   184,   375,   185,
     376,     0,     0,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   377,
     202,   203,   204,   205,   206,   207,   208,   209,     0,   210,
     211,   212,   378,   213,   379,   214,   380,   381,   215,     0,
     216,   217,     0,     0,     0,     0,     0,     0,     0,   218,
     219,   220,     0,     0,   221,   222,   223,   224,   225,   226,
     227,   228,     0,   382,     0,     0,   229,     0,   230,     0,
     231,   232,     0,     0,   233,   234,   383,   236,     0,     0,
     237,   238,   239,   240,   241,     0,     0,     0,   242,   243,
       0,   244,     0,     0,   245,   246,     0,   384,     0,     0,
     247,   385,   248,   249,   386,   387,   388,   389,   250,     0,
     251,   252,   390,   253,     0,     0,     0,   254,     0,     0,
     255,   391,   256,     0,     0,     0,     0,   257,     0,   258,
     259,   260,   392,     0,     0,   393,   262,   394,   263,   395,
       0,     0,   265,   266,     0,   267,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   268,   269,   270,     0,   271,
       0,   272,   273,   396,   397,     0,     0,     0,   398,     0,
       0,     0,     0,     0,   276,   399,     0,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,     0,
       0,     0,     0,   412,   413,   414,   415,     0,   416,   417,
     278,   279,   418,   419,   420,   421,   422,     0,   423,   424,
     425,   426,   427,   428,   429,   430,     0,     0,     0,   431,
     283,   432,   284,   433,   434,   435,   436,   437,   438,   439,
     440,   441,     0,     0,   442,   288,   289,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,     0,   458,   459,   460,   461,   462,     0,   299,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   477,   478,   479,     0,   302,     0,
     480,   481,   482,   304,     0,     0,   305,     0,   306,     0,
     307,   308,   309,     0,     0,     0,   483,   484,     0,     0,
       0,     0,   485,     0,   486,     0,     0,   487,   488,     0,
     489,   490,   491,    99,   100,   101,   102,   103,     0,     0,
       0,   104,     0,     0,     0,     0,     0,     0,   351,     0,
       0,     0,     0,     0,   105,     0,     0,   106,   352,   108,
     109,     0,   110,   111,   112,   113,   353,     0,     0,   114,
       0,     0,   115,     0,   116,   117,   118,   119,   120,   354,
     121,     0,     0,   122,     0,   123,   355,   356,   124,     0,
       0,   125,   126,   127,   128,   129,   130,     0,     0,   131,
     132,   133,   134,   357,   358,   135,   359,   360,   137,   361,
       0,   139,     0,   140,   141,     0,     0,     0,     0,   142,
     143,   144,   145,   362,   146,   147,   148,     0,   149,     0,
     150,   151,     0,   363,   364,   153,     0,   154,     0,   365,
       0,     0,   156,     0,   366,   367,     0,   157,   368,     0,
     158,     0,     0,   159,   160,   161,     0,   162,   163,   164,
       0,     0,   165,   166,   369,   167,   370,   168,   169,   170,
     371,     0,     0,     0,   171,     0,   172,     0,   173,   372,
       0,     0,   174,   373,     0,   175,   176,   177,     0,   178,
       0,   179,     0,     0,   180,     0,     0,   181,     0,     0,
       0,     0,   374,   182,   183,     0,     0,     0,   184,   375,
     185,   376,     0,     0,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     377,   202,   203,   204,   205,   206,   207,   208,   209,     0,
     210,   211,   212,   378,   213,   379,   214,   380,   381,   215,
       0,   216,   217,     0,     0,     0,     0,     0,     0,     0,
     218,   219,   220,     0,     0,   221,   222,   223,   224,   225,
     226,   227,   228,     0,   382,     0,     0,   229,     0,   230,
       0,   231,   232,     0,     0,   233,   234,   383,   236,     0,
       0,   237,   238,   239,   240,   241,     0,     0,     0,   242,
     243,     0,   244,     0,     0,   245,   246,     0,   384,     0,
       0,   247,   385,   248,   249,   386,   387,   388,   389,   250,
       0,   251,   252,   390,   253,     0,     0,     0,   254,     0,
       0,   255,   391,   256,     0,     0,     0,     0,   257,     0,
     258,   259,   260,   392,     0,     0,   393,   262,   394,   263,
     395,     0,     0,   265,   266,     0,   267,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   268,   269,   270,     0,
     271,     0,   272,   273,   396,   397,     0,     0,     0,   398,
       0,     0,     0,     0,     0,   276,   399,     0,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
       0,     0,     0,     0,   412,   413,   414,   415,     0,   416,
     417,   278,   279,   418,   419,   420,   421,   422,     0,   423,
     424,   425,   426,   427,   428,   429,   430,     0,     0,     0,
     431,   283,   432,   284,   433,   434,   435,   436,   437,   438,
     439,   440,   441,     0,     0,   442,   288,   289,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,     0,   458,   459,   460,   461,   462,     0,
     299,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,     0,   302,
       0,   480,   481,   482,   304,     0,     0,   305,     0,   306,
       0,   307,   308,   309,     0,     0,     0,   483,   484,     0,
       0,     0,     0,   485,     0,   486,     0,     0,   487,   488,
       0,   489,   490,   491,    99,   100,   101,   102,   103,     0,
       0,     0,   104,     0,     0,     0,     0,     0,     0,   351,
       0,     0,     0,     0,     0,   105,     0,     0,   106,   352,
     108,   109,     0,   110,   111,   112,   113,   353,     0,     0,
     114,     0,     0,   115,     0,   116,   117,   118,   119,   120,
     354,   121,     0,     0,   122,     0,   123,   355,   356,   124,
       0,     0,   125,   126,   127,   128,   129,   130,     0,     0,
     131,   132,   133,   134,   357,   358,   135,   359,   360,   137,
     361,     0,   139,     0,   140,   141,     0,     0,     0,     0,
     142,   143,   144,   145,   362,   146,   147,   148,     0,   149,
       0,   150,   151,     0,   363,   364,   153,     0,   154,     0,
     365,     0,     0,   156,     0,   366,   367,     0,   157,   368,
       0,   158,     0,     0,   159,   160,   161,     0,   162,   163,
     164,     0,     0,   165,   166,   369,   167,   370,   168,   169,
     170,   371,     0,     0,     0,   171,     0,   172,     0,   173,
     372,     0,     0,   174,   373,     0,   175,   176,   177,     0,
     178,     0,   179,     0,     0,   180,     0,     0,   181,     0,
       0,     0,     0,   374,   182,   183,     0,     0,     0,   184,
     375,   185,   376,     0,     0,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   377,   202,   203,   204,   205,   206,   207,   208,   209,
       0,   210,   211,   212,   378,   213,   379,   214,   380,   381,
     215,     0,   216,   217,     0,     0,     0,     0,     0,     0,
       0,   218,   219,   220,     0,     0,   221,   222,   223,   224,
     225,   226,   227,   228,     0,   382,     0,     0,   229,     0,
     230,     0,   231,   232,     0,     0,   233,   234,   383,   236,
       0,     0,   237,   238,   239,   240,   241,     0,     0,     0,
     242,   243,     0,   244,     0,     0,   245,   246,     0,   384,
       0,     0,   247,   385,   248,   249,   386,   387,   388,   389,
     250,     0,   251,   252,   390,   253,     0,     0,     0,   254,
       0,     0,   255,   391,   256,     0,     0,     0,     0,   257,
       0,   258,   259,   260,   392,     0,     0,   393,   262,   394,
     263,   395,     0,     0,   265,   266,     0,   267,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   268,   269,   270,
       0,   271,     0,   272,   273,   396,   397,     0,     0,     0,
     398,     0,     0,     0,     0,     0,   276,   399,     0,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,     0,     0,     0,     0,   412,   413,   414,   415,     0,
     416,   417,   278,   279,   418,   419,   420,   421,   422,     0,
     423,   424,   425,   426,   427,   428,   429,   430,     0,     0,
       0,   431,   283,   432,   284,  1770,   434,   435,   436,   437,
     438,   439,   440,   441,     0,     0,   442,   288,   289,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,     0,   458,   459,   460,   461,   462,
       0,   299,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,     0,
     302,     0,   480,   481,   482,   304,     0,     0,   305,     0,
     306,     0,   307,   308,   309,     0,     0,     0,   483,   484,
       0,     0,     0,     0,   485,     0,   486,     0,     0,   487,
     488,     0,   489,   490,   491,    99,   100,   101,   102,   103,
       0,     0,     0,   104,     0,     0,     0,     0,     0,     0,
     351,     0,     0,     0,     0,     0,   105,     0,     0,   106,
     352,   108,   109,     0,   110,   111,   112,   113,   353,     0,
       0,   114,     0,     0,   115,     0,   116,   117,   118,   119,
     120,   354,   121,     0,     0,   122,     0,   123,   355,   356,
     124,     0,     0,   125,   126,   127,   128,   129,   130,     0,
       0,   131,   132,   133,   134,   357,   358,   135,   359,   360,
     137,   361,     0,   139,     0,   140,   141,     0,     0,     0,
       0,   142,   143,   144,   145,   362,   146,   147,   148,     0,
     149,     0,   150,   151,     0,   363,   364,   153,     0,   154,
       0,   365,     0,     0,   156,     0,   366,   367,     0,   157,
     368,     0,   158,     0,     0,   159,   160,   161,     0,   162,
     163,   164,     0,     0,   165,   166,   369,   167,   370,   168,
     169,   170,   371,     0,     0,     0,   171,     0,   172,     0,
     173,   372,     0,     0,   174,   373,     0,   175,   176,   177,
       0,   178,     0,   179,     0,     0,   180,     0,     0,   181,
       0,     0,     0,     0,   374,   182,   183,     0,     0,     0,
     184,   375,   185,   376,     0,     0,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   377,   202,   203,   204,   205,   206,   207,   208,
     209,     0,   210,   211,   212,   378,   213,   379,   214,   380,
     381,   215,     0,   216,   217,     0,     0,     0,     0,     0,
       0,     0,   218,   219,   220,     0,     0,   221,   222,   223,
     224,   225,   226,   227,   228,     0,   382,     0,     0,   229,
       0,   230,     0,   231,   232,     0,     0,   233,   234,   383,
     236,     0,     0,   237,   238,   239,   240,   241,     0,     0,
       0,   242,   243,     0,   244,     0,     0,   245,   246,     0,
     384,     0,     0,   247,   385,   248,   249,   386,   387,   388,
     389,   250,     0,   251,   252,   390,   253,     0,     0,     0,
     254,     0,     0,   255,   391,   256,     0,     0,     0,     0,
     257,     0,   258,   259,   260,   392,     0,     0,   393,   262,
     394,   263,   395,     0,     0,   265,   266,     0,   267,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   268,   269,
     270,     0,   271,     0,   272,   273,   396,   397,     0,     0,
       0,   398,     0,     0,     0,     0,     0,   276,   399,     0,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,     0,     0,     0,     0,   412,   413,   414,   415,
       0,   416,   417,   278,   279,   418,   419,   420,   421,   422,
       0,   423,   424,   425,   426,   427,   428,   429,   430,     0,
       0,     0,   431,   283,   432,   284,  1867,   434,   435,   436,
     437,   438,   439,   440,   441,     0,     0,   442,   288,   289,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,     0,   458,   459,   460,   461,
     462,     0,   299,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
       0,   302,     0,   480,   481,   482,   304,     0,     0,   305,
       0,   306,     0,   307,   308,   309,     0,     0,     0,   483,
     484,     0,     0,     0,     0,   485,     0,   486,     0,     0,
     487,   488,     0,   489,   490,   491,    99,   100,   101,   102,
     103,     0,     0,     0,   104,     0,     0,     0,     0,     0,
       0,   351,     0,     0,     0,     0,     0,   105,     0,     0,
     106,   352,   108,   109,     0,   110,   111,   112,   113,   353,
       0,     0,   114,     0,     0,   115,     0,   116,   117,   118,
     119,   120,   354,   121,     0,     0,   122,     0,   123,   355,
     356,   124,     0,     0,   125,   126,   127,   128,   129,   130,
       0,     0,   131,   132,   133,   134,   357,   358,   135,   359,
     360,   137,   361,     0,   139,     0,   140,   141,     0,     0,
       0,     0,   142,   143,   144,   145,   362,   146,   147,   148,
       0,   149,     0,   150,   151,     0,   363,   364,   153,     0,
     154,     0,   365,     0,     0,   156,     0,   366,   367,     0,
     157,  2551,     0,   158,     0,     0,   159,   160,   161,     0,
     162,   163,   164,     0,     0,   165,   166,   369,   167,   370,
     168,   169,   170,   371,     0,     0,     0,   171,     0,   172,
       0,   173,   372,     0,     0,   174,   373,     0,   175,   176,
     177,     0,   178,     0,   179,     0,     0,   180,     0,     0,
     181,     0,     0,     0,     0,   374,   182,   183,     0,     0,
       0,   184,   375,   185,   376,     0,     0,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   377,   202,   203,   204,   205,   206,   207,
     208,   209,     0,   210,   211,   212,   378,   213,   379,   214,
     380,   381,   215,     0,   216,   217,     0,     0,     0,     0,
       0,     0,     0,   218,   219,   220,     0,     0,   221,   222,
     223,   224,   225,   226,   227,   228,     0,   382,     0,     0,
     229,     0,   230,     0,   231,   232,     0,     0,   233,   234,
     383,   236,     0,     0,   237,   238,   239,   240,   241,     0,
       0,     0,   242,   243,     0,   244,     0,     0,   245,   246,
       0,   384,     0,     0,   247,   385,   248,   249,   386,   387,
     388,   389,   250,     0,   251,   252,   390,   253,     0,     0,
       0,   254,     0,     0,   255,   391,   256,     0,     0,     0,
       0,   257,     0,   258,   259,   260,   392,     0,     0,   393,
     262,   394,   263,   395,     0,     0,   265,   266,     0,   267,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
     269,   270,     0,   271,     0,   272,   273,   396,   397,     0,
       0,     0,   398,     0,     0,     0,     0,     0,   276,   399,
       0,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,     0,     0,     0,     0,   412,   413,   414,
     415,     0,   416,   417,   278,   279,   418,   419,   420,   421,
     422,     0,   423,   424,   425,   426,   427,   428,   429,   430,
       0,     0,     0,   431,   283,   432,   284,   433,   434,   435,
     436,   437,   438,   439,   440,   441,     0,     0,   442,   288,
     289,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,     0,   458,   459,   460,
     461,   462,     0,   299,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,     0,   302,     0,   480,   481,   482,   304,     0,     0,
     305,     0,   306,     0,   307,   308,   309,     0,     0,     0,
     483,   484,     0,     0,     0,     0,   485,     0,   486,     0,
       0,   487,   488,     0,   489,   490,   491,    99,   100,   101,
     102,   103,     0,     0,     0,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,     0,
       0,   106,   107,   108,   109,     0,   110,   111,   112,   113,
       0,     0,     0,   114,     0,     0,   115,     0,   116,   117,
     118,   119,   120,     0,   121,     0,     0,   122,     0,   123,
       0,     0,   124,     0,     0,   125,   126,   127,   128,   129,
     130,  2023,     0,   131,   132,   133,   134,     0,     0,   135,
       0,   136,   137,   138,     0,   139,     0,   140,   141,     0,
       0,     0,     0,   142,   143,   144,   145,     0,   146,   147,
     148,     0,   149,     0,   150,   151,     0,     0,   152,   153,
       0,   154,     0,   155,     0,     0,   156,  2040,     0,     0,
       0,   157,     0,     0,   158,     0,     0,   159,   160,   161,
       0,   162,   163,   164,     0,     0,   165,   166,     0,   167,
       0,   168,   169,   170,     0,     0,     0,     0,   171,  2041,
     172,     0,   173,     0,     0,     0,   174,     0,     0,   175,
     176,   177,     0,   178,  1612,   179,     0,     0,   180,     0,
       0,   181,     0,     0,  1613,     0,     0,   182,   183,     0,
    2420,     0,   184,     0,   185,     0,     0,     0,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,     0,   202,   203,   204,   205,   206,
     207,   208,   209,     0,   210,   211,   212,     0,   213,     0,
     214,     0,     0,   215,     0,   216,   217,     0,     0,     0,
       0,     0,     0,     0,   218,   219,   220,     0,     0,   221,
     222,   223,   224,   225,   226,   227,   228,     0,     0,     0,
       0,   229,     0,   230,     0,   231,   232,     0,     0,   233,
     234,   235,   236,     0,     0,   237,   238,   239,   240,   241,
    2042,     0,     0,   242,   243,     0,   244,     0,     0,   245,
     246,     0,     0,     0,     0,   247,     0,   248,   249,     0,
       0,     0,     0,   250,     0,   251,   252,     0,   253,     0,
       0,     0,   254,     0,     0,   255,     0,   256,     0,     0,
       0,     0,   257,     0,   258,   259,   260,   261,     0,     0,
       0,   262,     0,   263,   264,     0,     0,   265,   266,     0,
     267,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     268,   269,   270,     0,   271,     0,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   276,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   277,     0,
       0,     0,     0,     0,     0,   278,   279,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   280,     0,     0,
     281,     0,     0,     0,   282,   283,     0,   284,     0,     0,
       0,     0,   285,     0,     0,     0,   286,     0,     0,   287,
     288,   289,   290,     0,     0,     0,   291,   292,   293,     0,
     294,   295,     0,   296,     0,   297,     0,     0,     0,     0,
       0,     0,   298,     0,   299,   300,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   301,    99,   100,
     101,   102,   103,   302,     0,   303,   104,     0,   304,     0,
       0,   305,     0,   306,     0,   307,   308,   309,     0,   105,
       0,     0,   106,   107,   108,   109,     0,   110,   111,   112,
     113,     0,     0,     0,   114,     0,  2087,   115,     0,   116,
     117,   118,   119,   120,     0,   121,     0,     0,   122,     0,
     123,     0,     0,   124,     0,     0,   125,   126,   127,   128,
     129,   130,     0,     0,   131,   132,   133,   134,     0,     0,
     135,     0,   136,   137,   138,     0,   139,     0,   140,   141,
       0,     0,     0,     0,   142,   143,   144,   145,     0,   146,
     147,   148,     0,   149,     0,   150,   151,     0,     0,   152,
     153,     0,   154,     0,   155,     0,     0,   156,  2040,     0,
       0,     0,   157,     0,     0,   158,     0,     0,   159,   160,
     161,     0,   162,   163,   164,     0,     0,   165,   166,     0,
     167,     0,   168,   169,   170,     0,     0,     0,     0,   171,
    2041,   172,     0,   173,     0,     0,     0,   174,     0,     0,
     175,   176,   177,     0,   178,  1612,   179,     0,     0,   180,
       0,     0,   181,     0,     0,  1613,     0,     0,   182,   183,
       0,     0,     0,   184,     0,   185,     0,     0,     0,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,     0,   202,   203,   204,   205,
     206,   207,   208,   209,     0,   210,   211,   212,     0,   213,
       0,   214,     0,     0,   215,     0,   216,   217,     0,     0,
       0,     0,     0,     0,     0,   218,   219,   220,     0,     0,
     221,   222,   223,   224,   225,   226,   227,   228,     0,     0,
       0,     0,   229,     0,   230,     0,   231,   232,     0,     0,
     233,   234,   235,   236,     0,     0,   237,   238,   239,   240,
     241,  2042,     0,     0,   242,   243,     0,   244,     0,     0,
     245,   246,     0,     0,     0,     0,   247,     0,   248,   249,
       0,     0,     0,     0,   250,     0,   251,   252,     0,   253,
       0,     0,     0,   254,     0,     0,   255,     0,   256,     0,
       0,     0,     0,   257,     0,   258,   259,   260,   261,     0,
       0,     0,   262,     0,   263,   264,     0,     0,   265,   266,
       0,   267,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,   269,   270,     0,   271,     0,   272,   273,   274,
     275,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   277,
       0,     0,     0,     0,     0,     0,   278,   279,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   280,     0,
       0,   281,     0,     0,     0,   282,   283,     0,   284,     0,
       0,     0,     0,   285,     0,     0,     0,   286,     0,     0,
     287,   288,   289,   290,     0,     0,     0,   291,   292,   293,
       0,   294,   295,     0,   296,     0,   297,     0,     0,     0,
       0,     0,     0,   298,     0,   299,   300,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   301,    99,
     100,   101,   102,   103,   302,     0,   303,   104,     0,   304,
       0,     0,   305,     0,   306,     0,   307,   308,   309,     0,
     105,     0,     0,   106,   107,   108,   109,     0,   110,   111,
     112,   113,     0,     0,     0,   114,     0,  2087,   115,     0,
     116,   117,   118,   119,   120,     0,   121,     0,     0,   122,
       0,   123,     0,     0,   124,     0,     0,   125,   126,   127,
     128,   129,   130,  2023,     0,   131,   132,   133,   134,     0,
       0,   135,     0,   136,   137,   138,     0,   139,     0,   140,
     141,     0,     0,     0,     0,   142,   143,   144,   145,     0,
     146,   147,   148,     0,   149,     0,   150,   151,     0,     0,
     152,   153,     0,   154,     0,   155,     0,     0,   156,     0,
       0,     0,     0,   157,     0,     0,   158,     0,     0,   159,
     160,   161,     0,   162,   163,   164,     0,     0,   165,   166,
       0,   167,     0,   168,   169,   170,     0,     0,     0,     0,
     171,     0,   172,     0,   173,     0,     0,     0,   174,     0,
       0,   175,   176,   177,     0,   178,     0,   179,     0,     0,
     180,     0,     0,   181,     0,     0,     0,     0,     0,   182,
     183,     0,     0,     0,   184,     0,   185,     0,     0,     0,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,     0,   202,   203,   204,
     205,   206,   207,   208,   209,     0,   210,   211,   212,     0,
     213,     0,   214,     0,     0,   215,     0,   216,   217,     0,
       0,     0,     0,     0,     0,     0,   218,   219,   220,     0,
       0,   221,   222,   223,   224,   225,   226,   227,   228,     0,
       0,     0,     0,   229,     0,   230,     0,   231,   232,     0,
       0,   233,   234,   235,   236,     0,     0,   237,   238,   239,
     240,   241,     0,     0,     0,   242,   243,     0,   244,     0,
       0,   245,   246,     0,     0,     0,     0,   247,     0,   248,
     249,     0,     0,     0,     0,   250,     0,   251,   252,     0,
     253,     0,     0,     0,   254,     0,     0,   255,     0,   256,
       0,     0,     0,     0,   257,     0,   258,   259,   260,   261,
       0,     0,     0,   262,     0,   263,   264,     0,     0,   265,
     266,     0,   267,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   268,   269,   270,     0,   271,     0,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   276,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     277,     0,     0,     0,     0,     0,     0,   278,   279,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   280,
       0,     0,   281,     0,     0,     0,   282,   283,     0,   284,
       0,     0,     0,     0,   285,     0,     0,     0,   286,     0,
       0,   287,   288,   289,   290,     0,     0,     0,   291,   292,
     293,     0,   294,   295,     0,   296,     0,   297,     0,     0,
       0,     0,     0,     0,   298,     0,   299,   300,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   301,
       0,     0,     0,     0,     0,   302,     0,   303,     0,     0,
     304,     0,     0,   305,     0,   306,     0,   307,   308,   309,
      99,   100,   101,   102,   103,     0,     0,     0,   104,     0,
       0,     0,  2337,     0,     0,     0,     0,     0,   490,     0,
       0,   105,     0,     0,   106,   107,   108,   109,     0,   110,
     111,   112,   113,     0,     0,     0,   114,     0,     0,   115,
       0,   116,   117,   118,   119,   120,     0,   121,     0,     0,
     122,     0,   123,     0,     0,   124,     0,     0,   125,   126,
     127,   128,   129,   130,     0,     0,   131,   132,   133,   134,
       0,     0,   135,     0,   136,   137,   138,     0,   139,     0,
     140,   141,     0,     0,     0,     0,   142,   143,   144,   145,
       0,   146,   147,   148,     0,   149,     0,   150,   151,     0,
       0,   152,   153,     0,   154,     0,   155,     0,     0,   156,
       0,     0,     0,     0,   157,     0,     0,   158,     0,     0,
     159,   160,   161,     0,   162,   163,   164,     0,     0,   165,
     166,     0,   167,     0,   168,   169,   170,     0,     0,     0,
       0,   171,     0,   172,     0,   173,     0,     0,     0,   174,
       0,     0,   175,   176,   177,     0,   178,     0,   179,     0,
       0,   180,  1264,     0,   181,     0,     0,     0,     0,     0,
     182,   183,     0,     0,     0,   184,     0,   185,     0,     0,
       0,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,     0,   202,   203,
     204,   205,   206,   207,   208,   209,     0,   210,   211,   212,
       0,   213,     0,   214,     0,     0,   215,     0,   216,   217,
       0,     0,     0,     0,     0,     0,     0,   218,   219,   220,
       0,     0,   221,   222,   223,   224,   225,   226,   227,   228,
       0,     0,     0,     0,   229,     0,   230,     0,   231,   232,
       0,     0,   233,   234,   235,   236,     0,     0,   237,   238,
     239,   240,   241,     0,     0,     0,   242,   243,     0,   244,
       0,     0,   245,   246,     0,     0,     0,     0,   247,     0,
     248,   249,     0,     0,     0,     0,   250,     0,   251,   252,
       0,   253,     0,     0,     0,   254,     0,     0,   255,     0,
     256,     0,     0,     0,     0,   257,     0,   258,   259,   260,
     261,     0,     0,     0,   262,     0,   263,   264,     0,     0,
     265,   266,     0,   267,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   268,   269,   270,     0,   271,     0,   272,
     273,   274,   275,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   276,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   277,     0,     0,     0,     0,     0,     0,   278,   279,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     280,     0,     0,   281,     0,     0,     0,   282,   283,     0,
     284,     0,     0,     0,     0,   285,     0,     0,     0,   286,
       0,     0,   287,   288,   289,   290,     0,     0,     0,   291,
     292,   293,     0,   294,   295,     0,   296,     0,   297,     0,
       0,     0,     0,     0,     0,   298,     0,   299,   300,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     301,    99,   100,   101,   102,   103,   302,     0,   303,   104,
       0,   304,     0,     0,   305,     0,   306,     0,   307,   308,
     309,     0,   105,     0,     0,   106,   107,   108,   109,     0,
     110,   111,   112,   113,     0,     0,     0,   114,     0,   310,
     115,     0,   116,   117,   118,   119,   120,     0,   121,     0,
       0,   122,     0,   123,     0,     0,   124,     0,     0,   125,
     126,   127,   128,   129,   130,     0,     0,   131,   132,   133,
     134,     0,     0,   135,     0,   136,   137,   138,     0,   139,
       0,   140,   141,     0,     0,     0,     0,   142,   143,   144,
     145,     0,   146,   147,   148,     0,   149,     0,   150,   151,
       0,     0,   152,   153,     0,   154,     0,   155,     0,     0,
     156,     0,     0,     0,     0,   157,     0,     0,   158,     0,
       0,   159,   160,   161,     0,   162,   163,   164,     0,     0,
     165,   166,     0,   167,     0,   168,   169,   170,     0,     0,
       0,     0,   171,     0,   172,     0,   173,     0,     0,     0,
     174,     0,     0,   175,   176,   177,     0,   178,     0,   179,
       0,     0,   180,     0,     0,   181,     0,     0,     0,     0,
       0,   182,   183,     0,     0,     0,   184,     0,   185,     0,
       0,     0,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,     0,   202,
     203,   204,   205,   206,   207,   208,   209,     0,   210,   211,
     212,     0,   213,     0,   214,     0,     0,   215,     0,   216,
     217,     0,     0,     0,     0,     0,     0,     0,   218,   219,
     220,     0,     0,   221,   222,   223,   224,   225,   226,   227,
     228,     0,     0,     0,     0,   229,     0,   230,     0,   231,
     232,     0,     0,   233,   234,   235,   236,     0,     0,   237,
     238,   239,   240,   241,     0,     0,     0,   242,   243,     0,
     244,     0,     0,   245,   246,     0,     0,     0,     0,   247,
       0,   248,   249,     0,     0,     0,     0,   250,     0,   251,
     252,     0,   253,     0,     0,     0,   254,     0,     0,   255,
       0,   256,     0,     0,     0,     0,   257,     0,   258,   259,
     260,   261,     0,     0,     0,   262,     0,   263,   264,     0,
       0,   265,   266,     0,   267,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   268,   269,   270,     0,   271,     0,
     272,   273,   274,   275,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   276,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   277,     0,     0,     0,     0,     0,     0,   278,
     279,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   280,     0,     0,   281,     0,     0,     0,   282,   283,
       0,   284,     0,     0,     0,     0,   285,     0,     0,     0,
     286,     0,     0,   287,   288,   289,   290,     0,     0,     0,
     291,   292,   293,     0,   294,   295,     0,   296,     0,   297,
       0,     0,     0,     0,     0,     0,   298,     0,   299,   300,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   301,     0,     0,     0,     0,     0,   302,     0,   303,
       0,     0,   304,     0,     0,   305,     0,   306,     0,   307,
     308,   309,    99,   100,   101,   102,   103,  1634,     0,     0,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     310,     0,     0,   105,     0,     0,   106,   107,   108,   109,
       0,   110,   111,   112,   113,     0,     0,     0,   114,     0,
       0,   115,     0,   116,   117,   118,   119,   120,     0,   121,
       0,     0,   122,     0,   123,     0,     0,   124,     0,     0,
     125,   126,   127,   128,   129,   130,     0,     0,   131,   132,
     133,   134,     0,     0,   135,     0,   136,   137,   138,     0,
     139,     0,   140,   141,     0,     0,     0,     0,   142,   143,
     144,   145,     0,   146,   147,   148,     0,   149,     0,   150,
     151,     0,     0,   152,   153,     0,   154,     0,   155,     0,
       0,   156,     0,     0,     0,     0,   157,     0,     0,   158,
       0,     0,   159,   160,   161,     0,   162,   163,   164,     0,
       0,   165,   166,     0,   167,     0,   168,   169,   170,     0,
       0,     0,     0,   171,     0,   172,     0,   173,     0,     0,
       0,   174,     0,     0,   175,   176,   177,     0,   178,     0,
     179,     0,     0,   180,     0,     0,   181,     0,     0,     0,
       0,     0,   182,   183,     0,     0,     0,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,     0,
     202,   203,   204,   205,   206,   207,   208,   209,     0,   210,
     211,   212,     0,   213,     0,   214,     0,     0,   215,     0,
     216,   217,     0,     0,     0,     0,     0,     0,     0,   218,
     219,   220,     0,     0,   221,   222,   223,   224,   225,   226,
     227,   228,     0,     0,     0,     0,   229,     0,   230,     0,
     231,   232,     0,     0,   233,   234,   235,   236,     0,     0,
     237,   238,   239,   240,   241,     0,     0,     0,   242,   243,
       0,   244,     0,     0,   245,   246,     0,     0,     0,     0,
     247,     0,   248,   249,     0,     0,     0,     0,   250,     0,
     251,   252,     0,   253,     0,     0,     0,   254,     0,     0,
     255,     0,   256,     0,     0,     0,     0,   257,     0,   258,
     259,   260,   261,     0,     0,     0,   262,     0,   263,   264,
       0,     0,   265,   266,     0,   267,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   268,   269,   270,     0,   271,
       0,   272,   273,   274,   275,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   276,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   277,     0,     0,     0,     0,     0,     0,
     278,   279,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   280,     0,     0,   281,     0,     0,     0,   282,
     283,     0,   284,     0,     0,     0,     0,   285,     0,     0,
       0,   286,     0,     0,   287,   288,   289,   290,     0,     0,
       0,   291,   292,   293,     0,   294,   295,     0,   296,     0,
     297,     0,     0,     0,     0,     0,     0,   298,     0,   299,
     300,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   301,     0,     0,     0,     0,     0,   302,     0,
     303,     0,     0,   304,     0,     0,   305,     0,   306,     0,
     307,   308,   309,    99,   100,   101,   102,   103,     0,     0,
       0,   104,     0,     0,  2086,     0,     0,     0,     0,     0,
       0,  2087,     0,     0,   105,     0,     0,   106,   107,   108,
     109,     0,   110,   111,   112,   113,     0,     0,     0,   114,
       0,     0,   115,     0,   116,   117,   118,   119,   120,     0,
     121,     0,     0,   122,     0,   123,     0,     0,   124,     0,
       0,   125,   126,   127,   128,   129,   130,     0,     0,   131,
     132,   133,   134,     0,     0,   135,     0,   136,   137,   138,
       0,   139,     0,   140,   141,     0,     0,     0,     0,   142,
     143,   144,   145,     0,   146,   147,   148,     0,   149,     0,
     150,   151,     0,     0,   152,   153,     0,   154,     0,   155,
       0,     0,   156,     0,     0,     0,     0,   157,     0,     0,
     158,     0,     0,   159,   160,   161,     0,   162,   163,   164,
       0,     0,   165,   166,     0,   167,     0,   168,   169,   170,
       0,     0,     0,     0,   171,     0,   172,     0,   173,     0,
       0,     0,   174,     0,     0,   175,   176,   177,     0,   178,
       0,   179,     0,     0,   180,     0,     0,   181,     0,     0,
       0,     0,     0,   182,   183,     0,     0,     0,   184,     0,
     185,     0,     0,     0,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
       0,   202,   203,   204,   205,   206,   207,   208,   209,     0,
     210,   211,   212,     0,   213,     0,   214,     0,     0,   215,
       0,   216,   217,     0,     0,     0,     0,     0,     0,     0,
     218,   219,   220,     0,     0,   221,   222,   223,   224,   225,
     226,   227,   228,     0,     0,     0,     0,   229,     0,   230,
       0,   231,   232,     0,     0,   233,   234,   235,   236,     0,
       0,   237,   238,   239,   240,   241,     0,     0,     0,   242,
     243,     0,   244,     0,     0,   245,   246,     0,     0,     0,
       0,   247,     0,   248,   249,     0,     0,     0,     0,   250,
       0,   251,   252,     0,   253,     0,     0,     0,   254,     0,
       0,   255,     0,   256,     0,     0,     0,     0,   257,     0,
     258,   259,   260,   261,     0,     0,     0,   262,     0,   263,
     264,     0,     0,   265,   266,     0,   267,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   268,   269,   270,     0,
     271,     0,   272,   273,   274,   275,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   277,     0,     0,     0,     0,     0,
       0,   278,   279,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   280,     0,     0,   281,     0,     0,     0,
     282,   283,     0,   284,     0,     0,     0,     0,   285,     0,
       0,     0,   286,     0,     0,   287,   288,   289,   290,     0,
       0,     0,   291,   292,   293,     0,   294,   295,     0,   296,
       0,   297,     0,     0,     0,     0,     0,     0,   298,     0,
     299,   300,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   301,     0,     0,     0,     0,     0,   302,
       0,   303,     0,     0,   304,     0,     0,   305,     0,   306,
       0,   307,   308,   309,    99,   100,   101,   102,   103,     0,
       0,     0,   104,     0,     0,     0,  3087,     0,     0,     0,
       0,     0,   490,     0,     0,   105,     0,     0,   106,   107,
     108,   109,     0,   110,   111,   112,   113,     0,     0,     0,
     114,     0,     0,   115,     0,   116,   117,   118,   119,   120,
       0,   121,     0,     0,   122,     0,   123,     0,     0,   124,
       0,     0,   125,   126,   127,   128,   129,   130,     0,     0,
     131,   132,   133,   134,     0,     0,   135,     0,   136,   137,
     138,     0,   139,     0,   140,   141,     0,     0,     0,     0,
     142,   143,   144,   145,     0,   146,   147,   148,     0,   149,
       0,   150,   151,     0,     0,   152,   153,     0,   154,     0,
     155,     0,     0,   156,     0,     0,     0,     0,   157,     0,
       0,   158,     0,     0,   159,   160,   161,     0,   162,   163,
     164,     0,     0,   165,   166,     0,   167,     0,   168,   169,
     170,     0,     0,     0,     0,   171,     0,   172,     0,   173,
       0,     0,     0,   174,     0,     0,   175,   176,   177,     0,
     178,     0,   179,     0,     0,   180,     0,     0,   181,     0,
       0,     0,     0,     0,   182,   183,     0,     0,     0,   184,
       0,   185,     0,     0,     0,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,     0,   202,   203,   204,   205,   206,   207,   208,   209,
       0,   210,   211,   212,     0,   213,     0,   214,     0,     0,
     215,     0,   216,   217,     0,     0,     0,     0,     0,     0,
       0,   218,   219,   220,     0,     0,   221,   222,   223,   224,
     225,   226,   227,   228,     0,     0,     0,     0,   229,     0,
     230,     0,   231,   232,     0,     0,   233,   234,   235,   236,
       0,     0,   237,   238,   239,   240,   241,     0,     0,     0,
     242,   243,     0,   244,     0,     0,   245,   246,     0,     0,
       0,     0,   247,     0,   248,   249,     0,     0,     0,     0,
     250,     0,   251,   252,     0,   253,     0,     0,     0,   254,
       0,     0,   255,     0,   256,     0,     0,     0,     0,   257,
       0,   258,   259,   260,   261,     0,     0,     0,   262,     0,
     263,   264,     0,     0,   265,   266,     0,   267,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   268,   269,   270,
       0,   271,     0,   272,   273,   274,   275,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   276,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   277,     0,     0,     0,     0,
       0,     0,   278,   279,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   280,     0,     0,   281,     0,     0,
       0,   282,   283,     0,   284,     0,     0,     0,     0,   285,
       0,     0,     0,   286,     0,     0,   287,   288,   289,   290,
       0,     0,     0,   291,   292,   293,     0,   294,   295,     0,
     296,     0,   297,     0,     0,     0,     0,     0,     0,   298,
       0,   299,   300,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   301,    99,   100,   101,   102,   103,
     302,     0,   303,   104,     0,   304,     0,     0,   305,     0,
     306,     0,   307,   308,   309,     0,   105,     0,     0,   106,
     107,   108,   109,     0,   110,   111,   112,   113,     0,     0,
       0,   114,     0,   310,   115,     0,   116,   117,   118,   119,
     120,     0,   121,     0,     0,   122,     0,   123,     0,     0,
     124,     0,     0,   125,   126,   127,   128,   129,   130,     0,
       0,   131,   132,   133,   134,     0,     0,   135,     0,   136,
     137,   138,     0,   139,     0,   140,   141,     0,     0,     0,
       0,   142,   143,   144,   145,     0,   146,   147,   148,     0,
     149,     0,   150,   151,     0,     0,   152,   153,     0,   154,
       0,   155,     0,     0,   156,     0,     0,     0,     0,   157,
       0,     0,   158,     0,     0,   159,   160,   161,     0,   162,
     163,   164,     0,     0,   165,   166,     0,   551,     0,   168,
     169,   170,     0,     0,     0,     0,   171,     0,   172,     0,
     173,     0,     0,     0,   174,     0,     0,   175,   176,   177,
       0,   178,     0,   179,     0,     0,   180,     0,     0,   181,
       0,     0,     0,     0,     0,   182,   183,     0,     0,     0,
     184,     0,   185,     0,     0,     0,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,     0,   202,   203,   204,   205,   206,   207,   208,
     209,     0,   210,   211,   212,     0,   213,     0,   214,     0,
       0,   215,     0,   216,   217,     0,     0,     0,     0,     0,
       0,     0,   218,   219,   220,     0,     0,   221,   222,   223,
     224,   225,   226,   227,   228,     0,     0,     0,     0,   229,
       0,   230,     0,   231,   232,     0,     0,   233,   234,   235,
     236,     0,     0,   237,   238,   239,   240,   241,     0,     0,
       0,   242,   243,     0,   244,     0,     0,   245,   246,     0,
       0,     0,     0,   247,     0,   248,   249,     0,     0,     0,
       0,   250,     0,   251,   252,     0,   253,     0,     0,     0,
     254,     0,     0,   255,     0,   256,     0,     0,     0,     0,
     257,     0,   258,   259,   260,   261,     0,     0,     0,   262,
       0,   263,   264,     0,     0,   265,   266,     0,   267,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   268,   269,
     270,     0,   271,     0,   272,   273,   274,   275,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   276,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   277,     0,     0,     0,
       0,     0,     0,   278,   279,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   280,     0,     0,   281,     0,
       0,     0,   282,   283,     0,   284,     0,     0,     0,     0,
     285,     0,     0,     0,   286,     0,     0,   287,   288,   289,
     290,     0,     0,     0,   291,   292,   293,     0,   294,   295,
       0,   296,     0,   297,     0,     0,     0,     0,     0,     0,
     298,     0,   299,   300,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   301,    99,   100,   101,   102,
     103,   302,     0,   303,   104,     0,   304,     0,     0,   305,
       0,   306,     0,   307,   308,   309,     0,   105,     0,     0,
     106,   107,   108,   109,     0,   110,   111,   112,   113,     0,
       0,     0,   114,     0,   310,   115,     0,   116,   117,   118,
     119,   120,     0,   121,     0,     0,   122,     0,   123,     0,
       0,   124,     0,     0,   125,   126,   127,   128,   129,   130,
       0,     0,   131,   132,   133,   134,     0,     0,   135,     0,
     136,   137,   138,     0,   139,     0,   140,   141,     0,     0,
       0,     0,   142,   143,   144,   145,     0,   146,   147,   148,
       0,   149,     0,   150,   151,     0,     0,   152,   153,     0,
     154,     0,   155,     0,     0,   156,     0,     0,     0,     0,
     157,     0,     0,   158,     0,     0,   159,   160,   161,     0,
     162,   163,   164,     0,     0,   165,   166,     0,   167,     0,
     168,   169,   170,     0,     0,     0,     0,   171,     0,   172,
       0,   173,     0,     0,     0,   174,     0,     0,   175,   176,
     177,     0,   178,     0,   179,     0,     0,   180,     0,     0,
     181,     0,     0,     0,     0,     0,   182,   183,     0,     0,
       0,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,     0,   202,   203,   204,   205,   206,   207,
     208,   209,     0,   210,   211,   212,     0,   213,     0,   214,
       0,     0,   215,     0,   216,   217,     0,     0,     0,     0,
       0,     0,     0,   218,   219,   220,     0,     0,   221,   222,
     223,   224,   225,   226,   227,   228,     0,     0,     0,     0,
     229,     0,   230,     0,   231,   232,     0,     0,   233,   234,
     235,   236,     0,     0,   237,   238,   239,   240,   241,     0,
       0,     0,   242,   243,     0,   244,     0,     0,   245,   246,
       0,     0,     0,     0,   247,     0,   248,   249,     0,     0,
       0,     0,   250,     0,   251,   252,     0,   253,     0,     0,
       0,   254,     0,     0,   255,     0,   256,     0,     0,     0,
       0,   257,     0,   258,   259,   260,   261,     0,     0,     0,
     262,     0,   263,   264,     0,     0,   265,   266,     0,   267,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
     269,   270,     0,   271,     0,   272,   273,   274,   275,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   276,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   277,     0,     0,
       0,     0,     0,     0,   278,   279,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   280,     0,     0,   281,
       0,     0,     0,   282,   283,     0,   284,     0,     0,     0,
       0,   285,     0,     0,     0,   286,     0,     0,   287,   288,
     289,   290,     0,     0,     0,   291,   292,   293,     0,   294,
     295,     0,   296,     0,   297,     0,     0,     0,     0,     0,
       0,   298,     0,   299,   300,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   301,    99,   100,   101,
     102,   103,   302,     0,   303,   104,     0,   304,     0,     0,
     305,     0,   306,     0,   307,   308,   309,     0,   105,     0,
       0,   106,   107,   108,   109,     0,   110,   111,   112,   113,
       0,     0,     0,   114,     0,   490,   115,     0,   116,   117,
     118,   119,   120,     0,   121,     0,     0,   122,     0,   123,
       0,     0,   124,     0,     0,   125,   126,   127,   128,   129,
     130,     0,     0,   131,   132,   133,   134,     0,     0,   135,
       0,   136,   137,   138,     0,   139,     0,   140,   141,     0,
       0,     0,     0,   142,   143,   144,   145,     0,   146,   147,
     148,     0,   149,     0,   150,   151,     0,     0,   152,   153,
       0,   154,     0,   155,     0,     0,   156,     0,     0,     0,
       0,   157,     0,     0,   158,     0,     0,   159,   160,   161,
       0,   162,   163,   164,     0,     0,   165,   166,     0,   167,
       0,   168,   169,   170,     0,     0,     0,     0,   171,     0,
     172,     0,   173,     0,     0,     0,   174,     0,     0,   175,
     176,   177,     0,   178,     0,   179,     0,     0,   180,     0,
       0,   181,     0,     0,     0,     0,     0,   182,   183,     0,
       0,     0,   184,     0,   185,     0,     0,     0,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,     0,   202,   203,   204,   205,   206,
     207,   208,   209,     0,   210,   211,   212,     0,   213,     0,
     214,     0,     0,   215,     0,   216,   217,     0,     0,     0,
       0,     0,     0,     0,   218,   219,   220,     0,     0,   221,
     222,   223,   224,   225,   226,   227,   228,     0,     0,     0,
       0,   229,     0,   230,     0,   231,   232,     0,     0,   233,
     234,   235,   236,     0,     0,   237,   238,   239,   240,   241,
       0,     0,     0,   242,   243,     0,   244,     0,     0,   245,
     246,     0,     0,     0,     0,   247,     0,   248,   249,     0,
       0,     0,     0,   250,     0,   251,   252,     0,   253,     0,
       0,     0,   254,     0,     0,   255,     0,   256,     0,     0,
       0,     0,   257,     0,   258,   259,   260,   261,     0,     0,
       0,   262,     0,   263,   264,     0,     0,   265,   266,     0,
     267,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     268,   269,   270,     0,   271,     0,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   276,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   277,     0,
       0,     0,     0,     0,     0,   278,   279,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   280,     0,     0,
     281,     0,     0,     0,   282,   283,     0,   284,     0,     0,
       0,     0,   285,     0,     0,     0,   286,     0,     0,   287,
     288,   289,   290,     0,     0,     0,   291,   292,   293,     0,
     294,   295,     0,   296,     0,   297,     0,     0,     0,     0,
       0,     0,   298,     0,   299,   300,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   301,    99,   100,
     101,   102,   103,   302,     0,   303,   104,     0,   304,     0,
       0,   305,     0,   306,     0,   307,   308,   309,     0,   105,
       0,     0,   106,   107,   108,   109,     0,   110,   111,   112,
     113,     0,     0,     0,   114,     0,  2087,   115,     0,   116,
     117,   118,   119,   120,     0,   121,     0,     0,   122,     0,
     123,     0,     0,   124,     0,     0,   125,   126,   127,   128,
     129,   130,     0,     0,   131,   132,   133,   134,     0,     0,
     135,     0,   136,   137,   138,     0,   139,     0,   140,   141,
       0,     0,     0,     0,   142,   143,   144,   145,     0,   146,
     147,   148,     0,   149,     0,   150,   151,     0,     0,   152,
     153,     0,   154,     0,   155,     0,     0,   156,     0,     0,
       0,     0,   157,     0,     0,   158,     0,     0,   159,   160,
     161,     0,   162,   163,   164,     0,     0,   165,   166,     0,
     167,     0,   168,   169,   170,     0,     0,     0,     0,   171,
       0,   172,     0,   173,     0,     0,     0,   174,     0,     0,
     175,   176,   177,     0,   178,     0,   179,     0,     0,   180,
       0,     0,   181,     0,     0,     0,     0,     0,   182,   183,
     345,     0,     0,   184,     0,   185,     0,     0,     0,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,     0,   202,   203,   204,   205,
     206,   207,   208,   209,     0,   210,   211,   212,     0,   213,
       0,   214,     0,     0,   215,     0,   216,   217,     0,     0,
       0,     0,     0,     0,     0,   218,   219,   220,     0,     0,
     221,   222,   223,   224,   225,   226,   227,   228,     0,     0,
       0,     0,   229,     0,   230,     0,   231,   232,     0,     0,
     233,   234,   235,   236,     0,     0,   237,   238,   239,   240,
     241,     0,     0,     0,   242,   243,     0,   244,     0,     0,
     245,   246,     0,   346,     0,     0,   247,     0,   248,   249,
       0,     0,     0,     0,   250,     0,   251,   252,     0,   253,
       0,     0,     0,   254,     0,     0,   255,     0,   256,     0,
       0,     0,     0,   257,     0,   258,   259,   260,   261,     0,
       0,     0,   262,     0,   263,   264,     0,     0,   265,   266,
       0,   267,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,   269,   270,     0,   271,     0,   272,   273,   274,
     275,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   277,
       0,     0,     0,     0,     0,     0,   278,   279,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   280,     0,
       0,   281,     0,     0,     0,   282,   283,     0,   284,     0,
       0,     0,     0,   285,     0,     0,     0,   286,     0,     0,
     287,   288,   289,   290,     0,     0,     0,   291,   292,   293,
       0,   294,   295,     0,   296,     0,   297,     0,     0,     0,
       0,     0,     0,   298,     0,   299,   300,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   301,    99,
     100,   101,   102,   103,   302,     0,   303,   104,     0,   304,
       0,     0,   305,     0,   306,     0,   307,   308,   309,     0,
     105,     0,     0,   106,   107,   108,   109,     0,   110,   111,
     112,   113,     0,     0,     0,   114,   734,     0,   115,     0,
     116,   117,   118,   119,   120,     0,   121,     0,     0,   122,
       0,   123,     0,     0,   124,     0,     0,   125,   126,   127,
     128,   129,   130,     0,     0,   131,   132,   133,   134,     0,
       0,   135,     0,   136,   137,   138,     0,   139,     0,   140,
     141,     0,     0,     0,     0,   142,   143,   144,   145,     0,
     146,   147,   148,     0,   149,     0,   150,   151,     0,     0,
     152,   153,     0,   154,     0,   155,     0,     0,   156,     0,
       0,     0,     0,   157,     0,     0,   158,     0,     0,   159,
     160,   161,     0,   162,   163,   164,     0,     0,   165,   166,
       0,   167,     0,   168,   169,   170,     0,     0,     0,     0,
     171,     0,   172,     0,   173,     0,     0,     0,   174,     0,
       0,   175,   176,   177,     0,   178,     0,   179,     0,     0,
     180,     0,     0,   181,     0,     0,     0,     0,     0,   182,
     183,   345,     0,     0,   184,     0,   185,     0,     0,     0,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,     0,   202,   203,   204,
     205,   206,   207,   208,   209,     0,   210,   211,   212,     0,
     213,     0,   214,     0,     0,   215,     0,   216,   217,     0,
       0,     0,     0,     0,     0,     0,   218,   219,   220,     0,
       0,   221,   222,   223,   224,   225,   226,   227,   228,     0,
       0,     0,     0,   229,     0,   230,     0,   231,   232,     0,
       0,   233,   234,   235,   236,     0,     0,   237,   238,   239,
     240,   241,     0,     0,     0,   242,   243,     0,   244,     0,
       0,   245,   246,     0,   346,     0,     0,   247,     0,   248,
     249,     0,     0,     0,     0,   250,     0,   251,   252,     0,
     253,     0,     0,     0,   254,     0,     0,   255,     0,   256,
       0,     0,     0,     0,   257,     0,   258,   259,   260,   261,
       0,     0,     0,   262,     0,   263,   264,     0,     0,   265,
     266,     0,   267,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   268,   269,   270,     0,   271,     0,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   276,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,     0,     0,
     277,     0,     0,     0,     0,     0,     0,   278,   279,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   280,
       0,     0,   281,     0,     0,     0,   282,   283,     0,   284,
       0,     0,     0,     0,   285,     0,     0,     0,   286,     0,
       0,   287,   288,   289,   290,     0,     0,     0,   291,   292,
     293,     0,   294,   295,     0,   296,     0,   297,     0,     0,
     750,     0,     0,     0,   298,     0,   299,   300,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   301,
       0,     0,     0,     0,     0,   302,     0,   303,     0,     0,
     304,     0,     0,   305,     0,   306,     0,   307,   308,   309,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2016,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     751,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     752,     0,     0,     0,     0,     0,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,     0,     0,     0,     0,     0,     0,     0,   753,
       0,     0,     0,     0,     0,     0,   750,     0,     0,   754,
     755,     0,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,     0,     0,     0,
     756,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,   750,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   750,     0,     0,
       0,     0,     0,  1483,     0,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,     0,     0,
       0,     0,     0,     0,     0,     0,   751,     0,     0,     0,
       0,   750,     0,   757,     0,     0,   752,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   750,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   751,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   752,   753,     0,   751,     0,     0,
       0,   758,     0,   750,     0,   754,   755,   752,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   756,     0,     0,     0,
       0,   751,     0,   753,     0,     0,     0,     0,     0,     0,
       0,   752,     0,   754,   755,     0,   753,     0,     0,   751,
       0,     0,     0,     0,     0,     0,   754,   755,     0,   752,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   756,     0,     0,
     753,     0,     0,   751,     0,     0,     0,     0,     0,   757,
     754,   755,     0,   752,     0,     0,     0,     0,   753,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   754,   755,
       0,   756,     0,     0,     0,     0,     0,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,   757,     0,   756,
    1479,  1480,   753,     0,     0,     0,     0,   758,     0,     0,
     757,     0,   754,   755,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   756,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   757,   758,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   758,     0,
       0,     0,   757,     0,     0,     0,     0,     0,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   758,     0,     0,     0,   757,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     758,     0,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,   759,   760,   761,   762,   763,
     764,   765,   766,     0,     0,     0,     0,  1484,     0,     0,
       0,     0,     0,     0,   758,     0,   750,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
       0,     0,     0,   759,   760,   761,   762,   763,   764,   765,
     766,     0,     0,     0,  1502,  1503,   759,   760,   761,   762,
     763,   764,   765,   766,     0,     0,     0,  1505,  1506,     0,
     750,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
       0,  2190,  2191,     0,     0,   750,   751,     0,   759,   760,
     761,   762,   763,   764,   765,   766,   752,     0,     0,  2193,
    2194,     0,     0,     0,     0,     0,     0,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
       0,     0,   759,   760,   761,   762,   763,   764,   765,   766,
     751,     0,   750,  2219,  2220,   753,     0,     0,     0,     0,
     752,     0,     0,     0,     0,   754,   755,     0,     0,     0,
       0,     0,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,   751,   756,     0,     0,     0,
       0,     0,     0,     0,     0,   752,     0,     0,     0,   753,
       0,     0,     0,     0,     0,   750,     0,     0,     0,   754,
     755,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     756,     0,   751,     0,   753,     0,     0,     0,     0,     0,
       0,     0,   752,     0,   754,   755,     0,     0,     0,   757,
     750,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   756,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   753,     0,     0,     0,   751,     0,     0,     0,     0,
       0,   754,   755,   757,     0,   752,     0,   758,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   756,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   757,     0,
     751,     0,     0,     0,   753,     0,     0,     0,     0,     0,
     752,   758,     0,     0,   754,   755,     0,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
       0,     0,     0,     0,     0,   756,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   757,   758,     0,     0,   753,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   754,
     755,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     756,     0,     0,     0,     0,   759,   760,   761,   762,   763,
     764,   765,   766,   758,     0,   750,  2651,  2652,   757,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,     0,   759,
     760,   761,   762,   763,   764,   765,   766,     0,     0,     0,
    2913,  2914,     0,   757,     0,     0,   758,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   759,   760,   761,   762,   763,   764,
     765,   766,     0,     0,     0,   751,  1341,     0,     0,     0,
       0,     0,     0,     0,     0,   752,     0,     0,     0,     0,
       0,   758,     0,   750,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,     0,     0,  1347,   753,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   754,   755,     0,     0,     0,     0,
       0,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,     0,   756,     0,     0,     0,     0,
       0,     0,     0,     0,   759,   760,   761,   762,   763,   764,
     765,   766,   750,   751,     0,     0,  1353,     0,     0,     0,
       0,     0,     0,   752,     0,     0,     0,     0,     0,     0,
       0,     0,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,     0,   757,   750,
       0,  1354,   753,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   754,   755,     0,     0,     0,     0,     0,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   751,   756,     0,     0,     0,     0,     0,     0,
       0,     0,   752,     0,     0,     0,   758,     0,     0,     0,
     750,     0,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   751,
       0,   753,     0,     0,     0,     0,     0,     0,     0,   752,
       0,   754,   755,     0,     0,     0,   757,   750,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   756,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   753,     0,
     751,     0,     0,     0,     0,     0,     0,     0,   754,   755,
     752,     0,     0,     0,   758,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   756,
       0,     0,     0,     0,   759,   760,   761,   762,   763,   764,
     765,   766,     0,     0,     0,   757,  1362,   751,     0,   753,
       0,     0,     0,     0,     0,     0,     0,   752,     0,   754,
     755,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
     756,   751,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   752,   757,   758,     0,     0,   753,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   754,   755,     0,     0,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,     0,     0,     0,     0,   756,     0,     0,
     753,     0,   759,   760,   761,   762,   763,   764,   765,   766,
     758,     0,   750,   757,  1363,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   756,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   750,     0,
     757,   758,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,     0,   751,  1369,     0,     0,     0,     0,     0,     0,
       0,     0,   752,     0,     0,     0,     0,     0,   758,     0,
     750,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,   759,   760,
     761,   762,   763,   764,   765,   766,     0,     0,   751,     0,
    1371,   753,   758,     0,     0,     0,     0,     0,   752,     0,
       0,   754,   755,     0,     0,     0,     0,     0,     0,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   756,     0,     0,     0,     0,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,   753,     0,     0,
     751,  1372,   750,     0,     0,     0,     0,   754,   755,     0,
     752,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   756,     0,
       0,     0,     0,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,     0,   757,     0,   750,  1389,   753,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   754,
     755,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
     756,     0,   751,     0,     0,     0,     0,     0,     0,     0,
       0,   757,   752,   758,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,     0,     0,     0,     0,   751,     0,     0,
       0,   753,     0,     0,     0,     0,     0,   752,     0,   758,
       0,   754,   755,   757,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   756,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   753,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   754,   755,   750,     0,
       0,   758,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   756,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,     0,     0,  1390,     0,   757,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,   759,   760,   761,
     762,   763,   764,   765,   766,     0,     0,     0,   751,  1392,
     757,     0,     0,   758,     0,     0,     0,     0,   752,     0,
       0,     0,     0,     0,     0,     0,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,   753,   758,     0,
       0,  1393,   750,     0,     0,     0,     0,   754,   755,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,     0,     0,     0,     0,     0,     0,   756,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   750,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,     0,   751,  1395,     0,     0,     0,   750,     0,     0,
       0,   757,   752,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,   751,     0,     0,     0,  1400,     0,
       0,   753,     0,     0,   752,     0,     0,     0,     0,   758,
       0,   754,   755,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,     0,     0,     0,
       0,     0,   756,     0,     0,     0,     0,   751,     0,     0,
       0,     0,     0,   753,     0,     0,     0,   752,     0,     0,
       0,     0,     0,   754,   755,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   753,     0,     0,     0,
       0,   750,     0,     0,     0,   757,   754,   755,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   756,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   759,   760,   761,
     762,   763,   764,   765,   766,     0,     0,   757,     0,  1401,
       0,     0,     0,   758,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
       0,   751,     0,     0,     0,     0,     0,     0,     0,     0,
     757,   752,     0,     0,     0,   758,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     753,     0,     0,     0,     0,     0,     0,     0,   758,     0,
     754,   755,   750,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,     0,     0,     0,
       0,   756,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,     0,     0,  1404,   750,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,     0,   759,   760,   761,   762,   763,   764,   765,
     766,   750,   751,     0,   757,  1406,     0,     0,     0,     0,
       0,     0,   752,     0,     0,     0,     0,     0,     0,     0,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,   751,     0,     0,     0,  1407,     0,
       0,   753,   758,     0,   752,     0,   750,     0,     0,     0,
       0,   754,   755,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   751,   756,     0,     0,     0,     0,     0,     0,     0,
       0,   752,     0,   753,     0,     0,     0,     0,   750,     0,
       0,     0,     0,   754,   755,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
     753,     0,     0,     0,     0,     0,   751,     0,     0,     0,
     754,   755,     0,     0,     0,   757,   752,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   756,     0,     0,     0,     0,     0,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,   751,     0,
       0,     0,  1421,     0,     0,   753,     0,   757,   752,     0,
       0,     0,     0,   758,     0,   754,   755,     0,     0,     0,
       0,     0,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,   756,     0,     0,     0,
       0,     0,     0,     0,   757,     0,     0,   753,     0,     0,
       0,     0,     0,     0,     0,   758,     0,   754,   755,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   756,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   758,     0,     0,     0,     0,     0,     0,   757,
       0,   750,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,   757,     0,  1423,     0,     0,     0,   758,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   750,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,     0,   759,   760,   761,   762,   763,   764,   765,
     766,   751,     0,     0,     0,  1427,     0,     0,     0,   758,
       0,   752,     0,   750,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
       0,     0,  1428,     0,     0,     0,     0,     0,     0,     0,
     753,     0,     0,     0,     0,     0,   750,   751,     0,     0,
     754,   755,     0,     0,     0,     0,     0,   752,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   756,     0,     0,     0,   759,   760,   761,   762,   763,
     764,   765,   766,   751,     0,     0,     0,  1429,     0,     0,
       0,     0,     0,   752,     0,     0,   753,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   754,   755,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   759,   760,   761,
     762,   763,   764,   765,   766,     0,   751,   756,     0,  1447,
       0,     0,   753,     0,   757,     0,   752,     0,     0,     0,
       0,     0,   754,   755,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   756,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   753,     0,     0,     0,     0,
       0,     0,   758,     0,     0,   754,   755,     0,     0,     0,
     757,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   756,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
       0,     0,     0,     0,     0,     0,   757,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   758,     0,
       0,     0,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   757,
       0,     0,     0,     0,   758,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   750,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
       0,     0,  1477,     0,     0,     0,     0,   758,     0,     0,
     750,     0,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,     0,     0,     0,
       0,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,   750,   751,     0,     0,  1478,     0,
       0,     0,     0,     0,     0,   752,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   759,   760,   761,   762,   763,   764,   765,   766,
     751,   750,     0,     0,  1482,     0,     0,     0,     0,     0,
     752,     0,     0,     0,   753,     0,     0,     0,     0,   750,
       0,     0,     0,     0,   754,   755,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   759,   760,   761,   762,   763,
     764,   765,   766,     0,   751,   756,     0,  1485,     0,   753,
       0,     0,     0,     0,   752,     0,     0,     0,     0,   754,
     755,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     756,   751,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   752,     0,   753,     0,     0,     0,     0,     0,   751,
       0,     0,     0,   754,   755,     0,     0,     0,   757,   752,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
     753,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     754,   755,     0,   757,     0,     0,     0,     0,   753,     0,
       0,     0,     0,     0,     0,     0,   758,     0,   754,   755,
       0,   756,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,     0,   756,
       0,     0,     0,     0,     0,     0,     0,   757,     0,     0,
       0,   758,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,     0,     0,   757,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   758,     0,     0,     0,     0,
     750,     0,   757,     0,     0,     0,     0,     0,     0,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   758,     0,   759,   760,   761,   762,   763,   764,
     765,   766,     0,     0,     0,     0,  2137,   750,     0,     0,
     758,     0,     0,     0,     0,     0,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,   759,
     760,   761,   762,   763,   764,   765,   766,     0,     0,     0,
     751,  2158,     0,     0,     0,     0,     0,   750,     0,     0,
     752,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   759,   760,   761,   762,   763,   764,   765,
     766,     0,     0,     0,     0,  2166,     0,   751,     0,   753,
       0,     0,     0,     0,   750,     0,     0,   752,     0,   754,
     755,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
     756,     0,  2175,     0,     0,     0,     0,   751,   759,   760,
     761,   762,   763,   764,   765,   766,   753,   752,     0,     0,
    2187,     0,     0,     0,     0,     0,   754,   755,     0,     0,
       0,  1492,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   756,     0,     0,
       0,     0,     0,     0,   751,     0,   753,     0,     0,     0,
       0,     0,     0,   757,   752,     0,   754,   755,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   756,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,     0,   753,     0,     0,     0,     0,     0,     0,
     757,   758,     0,   754,   755,     0,     0,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
       0,     0,     0,     0,   756,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,     0,     0,
     757,     0,     0,     0,     0,     0,     0,     0,   758,     0,
       0,     0,     0,     0,     0,     0,   750,     0,     0,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   750,     0,   757,   758,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   750,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,     0,     0,     0,
       0,  2212,     0,     0,     0,   758,   751,   750,     0,     0,
       0,     0,     0,     0,     0,     0,   752,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   751,   759,   760,   761,   762,
     763,   764,   765,   766,     0,   752,     0,     0,  2221,     0,
       0,     0,   750,   751,     0,   753,     0,     0,     0,     0,
       0,     0,     0,   752,     0,   754,   755,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,   753,     0,   756,   751,  2642,     0,
       0,     0,     0,     0,   754,   755,     0,   752,     0,     0,
       0,     0,   753,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   754,   755,     0,   756,     0,     0,     0,     0,
       0,     0,     0,   759,   760,   761,   762,   763,   764,   765,
     766,     0,   751,   756,  1493,     0,   753,     0,     0,     0,
       0,     0,   752,     0,     0,     0,   754,   755,     0,   757,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   756,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   757,     0,
       0,   753,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   754,   755,     0,     0,     0,   757,   758,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   756,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,   758,     0,     0,     0,
     757,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   758,     0,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,     0,     0,     0,   757,     0,     0,   758,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   750,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   759,   760,   761,   762,   763,
     764,   765,   766,   758,   750,     0,  1356,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   750,     0,     0,
       0,     0,     0,     0,   759,   760,   761,   762,   763,   764,
     765,   766,     0,     0,     0,  1357,     0,     0,     0,     0,
       0,     0,   759,   760,   761,   762,   763,   764,   765,   766,
     750,   751,     0,  1370,     0,     0,     0,     0,     0,     0,
       0,   752,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,   751,     0,     0,  1374,     0,     0,
       0,     0,     0,     0,   752,     0,     0,   751,     0,     0,
     753,     0,     0,     0,     0,     0,     0,   752,     0,     0,
     754,   755,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
     751,   756,  1377,   753,     0,     0,     0,     0,     0,     0,
     752,     0,     0,   754,   755,     0,   753,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   754,   755,     0,     0,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   756,     0,   753,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   754,
     755,     0,     0,     0,   757,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     756,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,     0,     0,     0,   757,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     757,     0,   758,     0,     0,     0,     0,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   757,     0,   758,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   758,   750,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,     0,     0,     0,
       0,   758,     0,     0,     0,   750,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,   750,   751,
       0,  1380,     0,     0,     0,     0,     0,     0,     0,   752,
       0,   750,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   759,   760,   761,   762,   763,   764,   765,
     766,     0,     0,     0,  1391,   751,   759,   760,   761,   762,
     763,   764,   765,   766,     0,   752,     0,  1394,   753,     0,
       0,     0,     0,   750,     0,     0,     0,     0,   754,   755,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,     0,   751,   756,
    1420,     0,     0,     0,   753,     0,     0,     0,   752,     0,
       0,   751,     0,     0,   754,   755,     0,     0,     0,     0,
       0,   752,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   756,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   753,     0,     0,
       0,     0,     0,   751,     0,     0,     0,   754,   755,     0,
     753,     0,   757,   752,     0,     0,     0,     0,     0,     0,
     754,   755,     0,     0,     0,     0,     0,     0,   756,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   756,     0,     0,     0,     0,     0,     0,   757,     0,
       0,     0,   753,     0,     0,     0,     0,     0,     0,     0,
     758,     0,   754,   755,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   756,     0,     0,     0,     0,     0,     0,
       0,   757,     0,     0,     0,     0,   758,     0,     0,     0,
       0,     0,     0,     0,   757,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,     0,     0,     0,     0,     0,     0,   758,
       0,     0,     0,     0,     0,     0,   757,     0,     0,     0,
       0,     0,   758,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   759,   760,
     761,   762,   763,   764,   765,   766,     0,     0,     0,  1422,
       0,     0,     0,     0,   758,     0,     0,     0,   750,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   759,   760,   761,   762,   763,   764,
     765,   766,     0,     0,     0,  1430,     0,     0,     0,     0,
       0,   750,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   759,   760,   761,
     762,   763,   764,   765,   766,     0,     0,     0,  1431,     0,
     759,   760,   761,   762,   763,   764,   765,   766,   751,     0,
       0,  1432,     0,     0,     0,     0,     0,     0,   752,     0,
       0,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
     750,   751,   759,   760,   761,   762,   763,   764,   765,   766,
       0,   752,     0,  1442,     0,     0,     0,   753,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   754,   755,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,     0,     0,     0,     0,     0,     0,   756,     0,
     753,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     754,   755,   750,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     751,   756,     0,     0,     0,     0,     0,     0,     0,     0,
     752,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   750,     0,     0,
       0,   757,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   753,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   754,
     755,     0,   751,     0,   757,     0,     0,     0,     0,     0,
       0,     0,   752,     0,     0,     0,     0,     0,     0,   758,
     756,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   751,     0,     0,
       0,   753,   758,     0,     0,     0,     0,   752,     0,     0,
       0,   754,   755,     0,     0,     0,     0,     0,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,   756,   757,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   753,     0,     0,     0,
       0,     0,   750,     0,     0,     0,   754,   755,     0,     0,
       0,     0,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,   756,     0,     0,
       0,   758,     0,     0,     0,     0,     0,   759,   760,   761,
     762,   763,   764,   765,   766,   757,   750,     0,  1443,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
       0,  1444,   751,     0,     0,     0,     0,     0,     0,     0,
     757,   750,   752,   758,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
       0,     0,     0,     0,     0,     0,   751,     0,     0,     0,
       0,   753,     0,     0,     0,     0,   752,     0,   758,     0,
       0,   754,   755,     0,     0,     0,     0,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,     0,     0,     0,
    1476,     0,   756,     0,     0,     0,     0,     0,     0,     0,
       0,   751,     0,     0,     0,   753,     0,     0,     0,     0,
       0,   752,     0,     0,   750,   754,   755,     0,     0,     0,
       0,     0,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,   756,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
     753,     0,  1481,     0,     0,   757,     0,     0,     0,     0,
     754,   755,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   756,     0,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,   751,     0,     0,  1501,     0,   757,
     750,     0,     0,   758,   752,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,     0,   753,   757,     0,     0,   758,     0,     0,
       0,     0,     0,   754,   755,     0,     0,     0,     0,     0,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,     0,   756,     0,     0,     0,     0,     0,
     751,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     752,     0,   758,   750,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   750,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,   753,
       0,     0,  1504,     0,     0,     0,     0,   757,   750,   754,
     755,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     756,     0,     0,     0,     0,   759,   760,   761,   762,   763,
     764,   765,   766,   751,     0,     0,  2135,     0,     0,     0,
       0,     0,     0,   752,     0,   758,   751,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   752,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,   751,     0,
       0,  2139,   753,   757,     0,     0,     0,     0,   752,     0,
       0,     0,   754,   755,     0,   753,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   754,   755,     0,     0,     0,
       0,     0,     0,   756,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   756,   753,     0,     0,
       0,   758,     0,     0,     0,     0,     0,   754,   755,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   756,     0,
       0,     0,     0,   759,   760,   761,   762,   763,   764,   765,
     766,     0,     0,     0,  2140,     0,   757,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   757,
       0,     0,     0,     0,     0,     0,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   757,     0,     0,   758,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   758,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,     0,     0,     0,
    2152,     0,     0,     0,     0,     0,     0,     0,     0,   758,
       0,     0,     0,     0,   750,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,     0,     0,
       0,     0,   759,   760,   761,   762,   763,   764,   765,   766,
       0,     0,     0,  2157,   751,   759,   760,   761,   762,   763,
     764,   765,   766,   750,   752,     0,  2159,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   750,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   759,   760,   761,
     762,   763,   764,   765,   766,     0,     0,     0,  2160,     0,
     750,     0,     0,   753,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   754,   755,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,     0,     0,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
       0,     0,     0,   751,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   752,     0,     0,   751,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   752,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     751,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     752,     0,   753,   750,     0,     0,     0,   757,     0,     0,
       0,     0,   754,   755,     0,   753,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   754,   755,     0,     0,     0,
       0,     0,     0,   756,     0,     0,     0,     0,     0,   753,
       0,     0,     0,     0,     0,     0,   756,     0,     0,   754,
     755,     0,     0,     0,     0,   758,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     756,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   751,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   752,     0,     0,   757,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   757,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   753,   757,     0,     0,     0,     0,     0,     0,
       0,     0,   754,   755,   758,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   758,     0,     0,
       0,     0,     0,   756,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   759,   760,   761,   762,   763,   764,   765,
     766,   758,     0,     0,  2170,     0,     0,     0,     0,     0,
       0,     0,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
       0,     0,     0,     0,     0,     0,   757,     0,     0,     0,
       0,     0,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
       0,     0,   759,   760,   761,   762,   763,   764,   765,   766,
       0,   750,     0,  2171,   758,   759,   760,   761,   762,   763,
     764,   765,   766,     0,   750,     0,  2174,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,     0,     0,     0,
    2176,   750,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   750,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
       0,   751,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   752,     0,     0,   751,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   752,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   751,   759,   760,   761,   762,   763,   764,   765,   766,
     753,   752,     0,  2179,   751,     0,     0,     0,     0,     0,
     754,   755,   750,   753,   752,     0,     0,     0,     0,     0,
       0,     0,     0,   754,   755,     0,     0,     0,     0,     0,
       0,   756,     0,     0,     0,     0,     0,     0,     0,     0,
     753,     0,     0,     0,   756,     0,     0,     0,     0,     0,
     754,   755,     0,   753,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   754,   755,     0,     0,     0,     0,     0,
       0,   756,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
       0,     0,   751,     0,   757,     0,     0,     0,     0,     0,
       0,     0,   752,     0,     0,     0,     0,   757,     0,     0,
       0,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
       0,     0,     0,     0,   757,     0,     0,     0,     0,     0,
       0,   753,   758,     0,     0,     0,     0,   757,     0,     0,
       0,   754,   755,     0,     0,   758,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   756,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   758,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   750,     0,     0,   758,     0,     0,     0,     0,
       0,     0,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
       0,     0,     0,     0,     0,   757,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
       0,  2180,   751,   759,   760,   761,   762,   763,   764,   765,
     766,   750,   752,   758,  2181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   750,     0,     0,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
       0,  2182,     0,   759,   760,   761,   762,   763,   764,   765,
     766,   753,     0,     0,  2186,     0,     0,     0,     0,     0,
       0,   754,   755,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,     0,     0,     0,
       0,     0,   756,     0,     0,     0,     0,     0,     0,     0,
       0,   751,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   752,     0,     0,   751,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   752,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
     753,   750,  2188,     0,     0,   757,     0,     0,     0,     0,
     754,   755,     0,   753,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   754,   755,     0,     0,     0,     0,     0,
       0,   756,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
       0,     0,     0,   758,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   751,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   752,     0,     0,   757,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   757,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     753,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     754,   755,   758,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   758,     0,     0,     0,     0,
       0,   756,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,     0,  2189,     0,     0,     0,     0,     0,     0,     0,
       0,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
       0,     0,     0,     0,   757,     0,     0,     0,     0,     0,
       0,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,   750,
       0,  2195,   758,   759,   760,   761,   762,   763,   764,   765,
     766,     0,   750,     0,  2196,     0,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   750,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   750,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,     0,   751,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   752,
       0,     0,   751,     0,   750,     0,     0,     0,     0,     0,
       0,     0,   752,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   751,
     759,   760,   761,   762,   763,   764,   765,   766,   753,   752,
       0,  2197,   751,     0,     0,     0,     0,     0,   754,   755,
     750,   753,   752,     0,     0,     0,     0,     0,     0,     0,
       0,   754,   755,     0,     0,     0,     0,     0,     0,   756,
       0,     0,     0,     0,     0,     0,     0,     0,   753,     0,
       0,     0,   756,     0,   751,     0,     0,     0,   754,   755,
       0,   753,     0,     0,   752,     0,     0,     0,     0,     0,
       0,   754,   755,     0,     0,     0,     0,     0,     0,   756,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   756,     0,     0,     0,     0,     0,     0,     0,
     751,     0,   757,   753,     0,     0,     0,     0,     0,     0,
     752,     0,     0,   754,   755,   757,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
       0,     0,   757,     0,     0,     0,     0,     0,     0,   753,
     758,     0,     0,     0,     0,   757,     0,     0,     0,   754,
     755,     0,     0,   758,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     756,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     758,     0,     0,     0,     0,     0,     0,   757,     0,     0,
       0,     0,     0,   758,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,     0,   757,     0,   758,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   759,   760,
     761,   762,   763,   764,   765,   766,     0,     0,     0,  2198,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,   758,  2199,   750,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   750,     0,   759,   760,
     761,   762,   763,   764,   765,   766,     0,     0,     0,  2200,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,     0,  2203,     0,     0,     0,     0,     0,     0,     0,
       0,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   759,   760,   761,   762,   763,   764,   765,
     766,     0,     0,   751,  2213,     0,     0,     0,     0,     0,
       0,     0,     0,   752,     0,     0,   751,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   752,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,     0,     0,   750,
    2214,     0,   753,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   754,   755,     0,   753,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   754,   755,     0,     0,     0,
       0,     0,     0,   756,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   756,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   751,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   752,
       0,     0,     0,     0,     0,     0,   757,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   757,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   753,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   754,   755,
       0,     0,     0,     0,   758,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   758,     0,   756,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,     0,     0,     0,     0,     0,     0,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
       0,     0,   757,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   750,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   750,     0,     0,
       0,     0,   759,   760,   761,   762,   763,   764,   765,   766,
     758,   750,     0,  2216,     0,   759,   760,   761,   762,   763,
     764,   765,   766,     0,   750,     0,  2222,     0,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,     0,     0,     0,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,   751,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   752,     0,
       0,     0,     0,     0,     0,     0,     0,   751,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   752,     0,     0,
       0,   751,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   752,     0,     0,   751,     0,   750,   753,     0,     0,
       0,     0,     0,     0,   752,     0,     0,   754,   755,     0,
       0,     0,     0,   750,     0,     0,   753,     0,   759,   760,
     761,   762,   763,   764,   765,   766,   754,   755,   756,  2224,
     753,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     754,   755,     0,   753,     0,     0,     0,   756,     0,     0,
       0,     0,     0,   754,   755,     0,     0,     0,     0,     0,
       0,   756,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   756,     0,   751,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   752,     0,     0,     0,
       0,   757,     0,   751,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   752,     0,     0,     0,     0,     0,     0,
     757,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   757,   753,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   754,   755,   757,     0,   758,
       0,     0,   753,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   754,   755,     0,     0,   756,     0,   758,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   758,   756,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   758,     0,     0,     0,     0,
       0,     0,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   757,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   757,   750,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   759,   760,   761,
     762,   763,   764,   765,   766,     0,     0,   758,  2226,     0,
       0,   750,     0,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,   758,     0,     0,  2228,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
       0,  2230,     0,   759,   760,   761,   762,   763,   764,   765,
     766,     0,     0,     0,  2231,     0,     0,   751,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   752,     0,     0,
       0,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
       0,   751,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   752,     0,     0,     0,     0,   753,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   754,   755,     0,     0,
       0,     0,     0,     0,     0,   759,   760,   761,   762,   763,
     764,   765,   766,     0,     0,     0,  2232,   756,     0,     0,
     753,     0,   759,   760,   761,   762,   763,   764,   765,   766,
     754,   755,   750,  2473,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   756,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     757,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,     0,   751,     0,   757,     0,     0,     0,     0,     0,
       0,     0,   752,     0,     0,     0,     0,     0,   758,     0,
     750,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   753,   758,     0,     0,     0,     0,     0,     0,     0,
       0,   754,   755,     0,     0,     0,   750,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   756,     0,     0,     0,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
     751,     0,   750,     0,     0,     0,     0,     0,     0,     0,
     752,     0,     0,     0,     0,     0,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
       0,     0,     0,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,     0,   757,   751,  2474,     0,   753,
       0,     0,     0,     0,     0,     0,   752,     0,     0,   754,
     755,     0,     0,     0,   750,     0,     0,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
     756,  2475,   751,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   752,   758,   750,   753,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   754,   755,     0,     0,     0,
       0,     0,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,   756,     0,     0,     0,
       0,   753,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   754,   755,   757,   751,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   752,     0,     0,     0,     0,     0,
       0,     0,   756,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   751,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   752,     0,     0,     0,     0,   757,
     750,   758,     0,   753,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   754,   755,     0,     0,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,     0,  2648,   753,   756,   757,     0,     0,     0,     0,
       0,     0,     0,   754,   755,     0,     0,   758,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     751,     0,     0,   758,     0,     0,     0,     0,     0,     0,
     752,     0,     0,     0,     0,     0,     0,   757,     0,     0,
       0,     0,     0,     0,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,   757,     0,   753,
    2650,     0,     0,     0,     0,     0,     0,     0,     0,   754,
     755,     0,     0,     0,     0,   758,     0,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
     756,     0,     0,     0,     0,   759,   760,   761,   762,   763,
     764,   765,   766,     0,     0,   758,  2656,     0,     0,     0,
       0,     0,   750,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,     0,  2657,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   757,     0,   750,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   751,   759,   760,   761,   762,   763,   764,   765,
     766,   758,   752,     0,  2658,     0,     0,     0,     0,     0,
       0,  1678,     0,  1679,     0,     0,     0,     0,     0,  1680,
       0,  1681,     0,   759,   760,   761,   762,   763,   764,   765,
     766,  1682,     0,     0,  2660,   751,     0,     0,     0,     0,
       0,   753,     0,     0,     0,   752,     0,   750,     0,     0,
       0,   754,   755,     0,     0,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,     0,     0,
       0,     0,   756,     0,     0,     0,     0,  1683,  1684,     0,
       0,     0,     0,     0,   753,     0,     0,     0,     0,     0,
       0,     0,     0,  1685,   754,   755,     0,     0,     0,     0,
       0,     0,  1686,     0,     0,  1687,  1285,     0,  1688,     0,
       0,     0,  1689,  1681,     0,   756,     0,  1691,     0,   759,
     760,   761,   762,   763,   764,   765,   766,   751,     0,     0,
    2662,     0,     0,   750,     0,   757,     0,   752,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1693,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1683,
    1684,     0,     0,     0,     0,     0,   753,     0,   757,     0,
       0,     0,     0,   758,  -303,  1685,   754,   755,  -303,  1694,
       0,     0,     0,     0,  1695,     0,     0,  1687,  1285,     0,
    1688,     0,     0,     0,     0,     0,     0,   756,     0,     0,
       0,     0,     0,   751,     0,  1658,     0,     0,     0,  1696,
       0,     0,     0,   752,     0,     0,   758,     0,  1697,  1698,
    1699,     0,     0,     0,     0,     0,  1700,     0,     0,     0,
    1693,     0,     0,     0,  1701,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   753,     0,     0,     0,     0,     0,     0,     0,
     757,  1702,   754,   755,     0,     0,     0,     0,     0,     0,
       0,  1694,     0,  1703,     0,     0,  1695,     0,     0,     0,
       0,     0,     0,   756,     0,     0,     0,     0,     0,     0,
       0,   759,   760,   761,   762,   763,   764,   765,   766,     0,
       0,  1696,  2663,     0,     0,     0,     0,     0,   758,     0,
    1697,  1698,  1699,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1701,     0,     0,     0,
       0,     0,     0,     0,   759,   760,   761,   762,   763,   764,
     765,   766,     0,     0,     0,  2664,   757,     0,     0,     0,
       0,     0,     0,  1702,     0,     0,     0,     0,     0,  1704,
       0,     0,     0,     0,     0,  1703,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1705,     0,     0,     0,     0,  -303,     0,     0,     0,
       0,     0,     0,     0,   758,  1706,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1707,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   759,   760,   761,   762,
     763,   764,   765,   766,     0,     0,     0,  2912,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1704,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1705,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1707,     0,     0,
      99,   100,   101,   102,   103,     0,     0,     0,   104,     0,
       0,     0,   759,   760,   761,   762,   763,   764,   765,   766,
       0,   105,     0,  3035,   106,   107,   108,   109,     0,   110,
     111,   112,   113,     0,     0,     0,   114,     0,     0,   115,
       0,   116,   117,   118,   119,   120,     0,   121,     0,     0,
     122,     0,   123,     0,     0,   124,     0,     0,   125,   126,
     127,   128,   129,   130,     0,     0,   131,   132,   133,   134,
       0,     0,   135,     0,   136,   137,   138,     0,   139,     0,
     140,   141,     0,     0,     0,     0,   142,   143,   144,   145,
       0,   146,   147,   148,     0,   149,     0,   150,   151,     0,
       0,   152,   153,     0,   154,     0,   155,     0,     0,   156,
       0,     0,     0,     0,   157,     0,     0,   158,     0,     0,
     159,   160,   161,     0,   162,   163,   164,     0,     0,   165,
     166,     0,   167,     0,   168,   169,   170,     0,     0,     0,
       0,   171,     0,   172,     0,   173,     0,     0,     0,   174,
       0,     0,   175,   176,   177,     0,   178,     0,   179,     0,
       0,   180,     0,     0,   181,     0,     0,     0,     0,     0,
     182,   183,     0,     0,     0,   184,     0,   185,     0,     0,
       0,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,     0,   202,   203,
     204,   205,   206,   207,   208,   209,     0,   210,   211,   212,
       0,   213,     0,   214,     0,     0,   215,     0,   216,   217,
       0,     0,     0,     0,     0,     0,     0,   218,   219,   220,
       0,     0,   221,   222,   223,   224,   225,   226,   227,   228,
       0,     0,     0,     0,   229,     0,   230,     0,   231,   232,
       0,     0,   233,   234,   235,   236,     0,     0,   237,   238,
     239,   240,   241,     0,     0,     0,   242,   243,     0,   244,
       0,     0,   245,   246,     0,     0,     0,     0,   247,     0,
     248,   249,     0,     0,     0,     0,   250,     0,   251,   252,
       0,   253,     0,     0,     0,   254,     0,     0,   255,     0,
     256,     0,     0,     0,     0,   257,     0,   258,   259,   260,
     261,     0,     0,     0,   262,     0,   263,   264,     0,     0,
     265,   266,     0,   267,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   268,   269,   270,     0,   271,     0,   272,
     273,   274,   275,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   276,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   277,     0,     0,     0,     0,     0,     0,   278,   279,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     280,     0,     0,   281,     0,     0,     0,   282,   283,     0,
     284,     0,     0,     0,     0,   285,     0,     0,     0,   286,
       0,     0,   287,   288,   289,   290,     0,     0,     0,   291,
     292,   293,     0,   294,   295,     0,   296,     0,   297,     0,
       0,     0,     0,     0,     0,   298,     0,   299,   300,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     301,     0,     0,     0,     0,     0,   302,     0,   303,     0,
       0,   304,     0,     0,   305,     0,   306,     0,   307,   308,
     309,    99,   100,   101,   102,   103,  1747,     0,     0,   104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   105,     0,     0,   106,   107,   108,   109,     0,
     110,   111,   112,   113,     0,     0,     0,   114,     0,     0,
     115,     0,   116,   117,   118,   119,   120,     0,   121,     0,
       0,   122,     0,   123,     0,     0,   124,     0,     0,   125,
     126,   127,   128,   129,   130,     0,     0,   131,   132,   133,
     134,     0,     0,   135,     0,   136,   137,   138,     0,   139,
       0,   140,   141,     0,     0,     0,     0,   142,   143,   144,
     145,     0,   146,   147,   148,     0,   149,     0,   150,   151,
       0,     0,   152,   153,     0,   154,     0,   155,     0,     0,
     156,     0,     0,     0,     0,   157,     0,     0,   158,     0,
       0,   159,   160,   161,     0,   162,   163,   164,     0,     0,
     165,   166,     0,   167,     0,   168,   169,   170,     0,     0,
       0,     0,   171,     0,   172,     0,   173,     0,     0,     0,
     174,     0,     0,   175,   176,   177,     0,   178,     0,   179,
       0,     0,   180,     0,     0,   181,     0,     0,     0,     0,
       0,   182,   183,     0,     0,     0,   184,     0,   185,     0,
       0,     0,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,     0,   202,
     203,   204,   205,   206,   207,   208,   209,     0,   210,   211,
     212,     0,   213,     0,   214,     0,     0,   215,     0,   216,
     217,     0,     0,     0,     0,     0,     0,     0,   218,   219,
     220,     0,     0,   221,   222,   223,   224,   225,   226,   227,
     228,     0,     0,     0,     0,   229,     0,   230,     0,   231,
     232,     0,     0,   233,   234,   235,   236,     0,     0,   237,
     238,   239,   240,   241,     0,     0,     0,   242,   243,     0,
     244,     0,     0,   245,   246,     0,     0,     0,     0,   247,
       0,   248,   249,     0,     0,     0,     0,   250,     0,   251,
     252,     0,   253,     0,     0,     0,   254,     0,     0,   255,
       0,   256,     0,     0,     0,     0,   257,     0,   258,   259,
     260,   261,     0,     0,     0,   262,     0,   263,   264,     0,
       0,   265,   266,     0,   267,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   268,   269,   270,     0,   271,     0,
     272,   273,   274,   275,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   276,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   277,     0,     0,     0,     0,     0,     0,   278,
     279,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   280,     0,     0,   281,     0,     0,     0,   282,   283,
       0,   284,     0,     0,     0,     0,   285,     0,     0,     0,
     286,     0,     0,   287,   288,   289,   290,     0,     0,     0,
     291,   292,   293,     0,   294,   295,     0,   296,     0,   297,
       0,     0,     0,     0,     0,     0,   298,     0,   299,   300,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   301,     0,     0,     0,     0,     0,   302,     0,   303,
       0,     0,   304,     0,     0,   305,     0,   306,     0,   307,
     308,   309,    99,   100,   101,   102,   103,  2271,     0,     0,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   105,     0,     0,   106,   107,   108,   109,
       0,   110,   111,   112,   113,     0,     0,     0,   114,     0,
       0,   115,     0,   116,   117,   118,   119,   120,     0,   121,
       0,     0,   122,     0,   123,     0,     0,   124,     0,     0,
     125,   126,   127,   128,   129,   130,     0,     0,   131,   132,
     133,   134,     0,     0,   135,     0,   136,   137,   138,     0,
     139,     0,   140,   141,     0,     0,     0,     0,   142,   143,
     144,   145,     0,   146,   147,   148,     0,   149,     0,   150,
     151,     0,     0,   152,   153,     0,   154,     0,   155,     0,
       0,   156,     0,     0,     0,     0,   157,     0,     0,   158,
       0,     0,   159,   160,   161,     0,   162,   163,   164,     0,
       0,   165,   166,     0,   167,     0,   168,   169,   170,     0,
       0,     0,     0,   171,     0,   172,     0,   173,     0,     0,
       0,   174,     0,     0,   175,   176,   177,     0,   178,     0,
     179,     0,     0,   180,     0,     0,   181,     0,     0,     0,
       0,     0,   182,   183,     0,     0,     0,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,     0,
     202,   203,   204,   205,   206,   207,   208,   209,     0,   210,
     211,   212,     0,   213,     0,   214,     0,     0,   215,     0,
     216,   217,     0,     0,     0,     0,     0,     0,     0,   218,
     219,   220,     0,     0,   221,   222,   223,   224,   225,   226,
     227,   228,     0,     0,     0,     0,   229,     0,   230,     0,
     231,   232,     0,     0,   233,   234,   235,   236,     0,     0,
     237,   238,   239,   240,   241,     0,     0,     0,   242,   243,
       0,   244,     0,     0,   245,   246,     0,     0,     0,     0,
     247,     0,   248,   249,     0,     0,     0,     0,   250,     0,
     251,   252,     0,   253,     0,     0,     0,   254,     0,     0,
     255,     0,   256,     0,     0,     0,     0,   257,     0,   258,
     259,   260,   261,     0,     0,     0,   262,     0,   263,   264,
       0,     0,   265,   266,     0,   267,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   268,   269,   270,     0,   271,
       0,   272,   273,   274,   275,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   276,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   277,     0,     0,     0,     0,     0,     0,
     278,   279,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   280,     0,     0,   281,     0,     0,     0,   282,
     283,     0,   284,     0,     0,     0,     0,   285,     0,     0,
       0,   286,     0,     0,   287,   288,   289,   290,     0,     0,
       0,   291,   292,   293,     0,   294,   295,     0,   296,     0,
     297,     0,     0,     0,     0,     0,     0,   298,     0,   299,
     300,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   301,     0,     0,     0,     0,     0,   302,     0,
     303,     0,     0,   304,     0,     0,   305,     0,   306,     0,
     307,   308,   309,    99,   100,   101,   102,   103,  2309,     0,
       0,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   105,     0,     0,   106,   107,   108,
     109,     0,   110,   111,   112,   113,     0,     0,     0,   114,
       0,     0,   115,     0,   116,   117,   118,   119,   120,     0,
     121,     0,     0,   122,     0,   123,     0,     0,   124,     0,
       0,   125,   126,   127,   128,   129,   130,     0,     0,   131,
     132,   133,   134,     0,     0,   135,     0,   136,   137,   138,
       0,   139,     0,   140,   141,     0,     0,     0,     0,   142,
     143,   144,   145,     0,   146,   147,   148,     0,   149,     0,
     150,   151,     0,     0,   152,   153,     0,   154,     0,   155,
       0,     0,   156,     0,     0,     0,     0,   157,     0,     0,
     158,     0,     0,   159,   160,   161,     0,   162,   163,   164,
       0,     0,   165,   166,     0,   167,     0,   168,   169,   170,
       0,     0,     0,     0,   171,     0,   172,     0,   173,     0,
       0,     0,   174,     0,     0,   175,   176,   177,     0,   178,
       0,   179,     0,     0,   180,     0,     0,   181,     0,     0,
       0,     0,     0,   182,   183,     0,     0,     0,   184,     0,
     185,     0,     0,     0,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
       0,   202,   203,   204,   205,   206,   207,   208,   209,     0,
     210,   211,   212,     0,   213,     0,   214,     0,     0,   215,
       0,   216,   217,     0,     0,     0,     0,     0,     0,     0,
     218,   219,   220,     0,     0,   221,   222,   223,   224,   225,
     226,   227,   228,     0,     0,     0,     0,   229,     0,   230,
       0,   231,   232,     0,     0,   233,   234,   235,   236,     0,
       0,   237,   238,   239,   240,   241,     0,     0,     0,   242,
     243,     0,   244,     0,     0,   245,   246,     0,     0,     0,
       0,   247,     0,   248,   249,     0,     0,     0,     0,   250,
       0,   251,   252,     0,   253,     0,     0,     0,   254,     0,
       0,   255,     0,   256,     0,     0,     0,     0,   257,     0,
     258,   259,   260,   261,     0,     0,     0,   262,     0,   263,
     264,     0,     0,   265,   266,     0,   267,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   268,   269,   270,     0,
     271,     0,   272,   273,   274,   275,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
       0,     0,     0,     0,   277,     0,     0,     0,     0,     0,
       0,   278,   279,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   280,     0,     0,   281,     0,     0,     0,
     282,   283,     0,   284,     0,     0,     0,     0,   285,     0,
       0,     0,   286,     0,     0,   287,   288,   289,   290,     0,
       0,     0,   291,   292,   293,     0,   294,   295,     0,   296,
       0,   297,     0,     0,   750,     0,     0,     0,   298,     0,
     299,   300,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   301,     0,     0,     0,     0,     0,   302,
       0,   303,     0,     0,   304,     0,     0,   305,     0,   306,
       0,   307,   308,   309,     0,     0,     0,     0,     0,  2676,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   751,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   752,     0,     0,     0,     0,     0,
       0,     0,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   753,     0,     0,     0,     0,   750,  1355,
       0,     0,     0,   754,   755,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,     0,     0,
       0,     0,     0,     0,   756,     0,     0,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
     750,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,     0,     0,     0,     0,   751,     0,
       0,     0,     0,   750,     0,     0,     0,   757,   752,     0,
       0,     0,     0,     0,     0,     0,     0,  1873,     0,     0,
       0,     0,     0,     0,     0,   750,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,     0,
     751,     0,     0,     0,     0,     0,     0,   753,     0,     0,
     752,     0,     0,     0,     0,   758,     0,   754,   755,   750,
    1875,     0,     0,     0,     0,     0,     0,     0,   768,   769,
     770,   771,   772,     0,     0,     0,     0,     0,   756,     0,
       0,     0,  1877,   751,     0,     0,     0,     0,     0,   753,
       0,     0,     0,   752,     0,   773,   774,   775,   776,   754,
     755,     0,     0,     0,   750,   751,     0,     0,     0,     0,
     777,   778,   779,   780,     0,   752,   781,     0,     0,     0,
     756,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   753,     0,     0,     0,   782,   783,     0,  2153,
       0,   757,   754,   755,     0,     0,     0,     0,     0,   752,
       0,     0,     0,     0,   753,     0,     0,     0,   784,   785,
       0,     0,     0,   756,   754,   755,     0,     0,     0,     0,
       0,     0,     0,   759,   760,   761,   762,   763,   764,   765,
     766,     0,     0,   757,   751,   756,     0,     0,   753,   758,
       0,     0,     0,     0,   752,     0,     0,     0,   754,   755,
       0,     0,     0,     0,     0,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,     0,   756,
       0,     0,     0,     0,     0,     0,   757,     0,     0,     0,
       0,   758,     0,   753,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   754,   755,     0,     0,     0,   757,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   758,     0,     0,     0,  2154,     0,
       0,     0,   757,   750,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   758,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   759,   760,   761,
     762,   763,   764,   765,   766,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   757,     0,     0,
     758,     0,     0,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,     0,     0,     0,   759,
     760,   761,   762,   763,   764,   765,   766,     0,     0,     0,
       0,     0,     0,   751,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   752,     0,   758,     0,     0,     0,  1451,
     738,  1452,  1453,   741,   742,   743,   744,   745,  1454,  1455,
    1456,  1457,   759,   760,   761,   762,   763,   764,   765,   766,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   750,   753,     0,   759,   760,   761,   762,   763,   764,
     765,   766,   754,   755,     0,  1528,   738,  1529,  1530,   741,
     742,   743,   744,   745,  1531,  1532,  1533,  1534,     0,     0,
       0,     0,     0,   756,     0,     0,     0,     0,   759,   760,
     761,   762,   763,   764,   765,   766,     0,  1458,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2163,     0,     0,     0,     0,     0,     0,
       0,   751,     0,   759,   760,   761,   762,   763,   764,   765,
     766,   752,     0,  1535,     0,     0,   757,     0,     0,     0,
       0,     0,     0,  1528,   738,  1529,  1530,   741,   742,   743,
     744,   745,  1531,  1532,  1533,  1534,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1459,     0,     0,
     753,     0,     0,     0,     0,     0,     0,  1460,     0,     0,
     754,   755,     0,     0,   758,  1528,   738,  1529,  1530,   741,
     742,   743,   744,   745,  1531,  1532,  1533,  1534,     0,     0,
       0,   756,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1536,     0,     0,  1461,     0,     0,     0,
       0,  1891,     0,  1537,     0,     0,  1462,  1463,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1464,     0,  1528,
     738,  1529,  1530,   741,   742,   743,   744,   745,  1531,  1532,
    1533,  1534,  1538,  2208,   757,     0,     0,     0,     0,     0,
       0,     0,  1539,  1540,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2649,  1541,     0,     0,     0,     0,     0,     0,
       0,  1536,   759,   760,   761,   762,   763,   764,   765,   766,
    1465,  1537,   758,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2245,     0,     0,
    1528,   738,  1529,  1530,   741,   742,   743,   744,   745,  1531,
    1532,  1533,  1534,  1536,     0,     0,     0,     0,     0,     0,
    1538,     0,     0,  1537,     0,     0,  1542,     0,  1466,     0,
    1539,  1540,  1528,   738,  1529,  1530,   741,   742,   743,   744,
     745,  1531,  1532,  1533,  1534,     0,     0,     0,     0,     0,
       0,  1541,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1538,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1539,  1540,  1543,     0,     0,  1536,  2466,     0,
       0,     0,     0,     0,     0,     0,     0,  1537,     0,     0,
       0,     0,     0,  1541,     0,     0,     0,     0,     0,     0,
     759,   760,   761,   762,   763,   764,   765,   766,     0,     0,
    2480,     0,     0,     0,  1542,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1538,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1539,  1540,     0,     0,
       0,     0,     0,     0,     0,     0,  1467,  1468,  1469,  1470,
    1471,  1472,  1473,  1474,     0,     0,  1542,  1541,  1536,     0,
       0,     0,  1543,     0,     0,     0,     0,     0,  1537,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1536,     0,  1544,  1545,  1546,  1547,  1548,  1549,  1550,  1551,
    1537,     0,     0,     0,  1543,     0,     0,  1538,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1539,  1540,     0,
    1542,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1541,  1538,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1539,
    1540,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1543,     0,
    1541,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1544,  1545,  1546,  1547,  1548,  1549,  1550,  1551,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1542,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1544,  1545,  1546,  1547,  1548,  1549,  1550,  1551,
       0,     0,     0,  1542,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1543,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1543,     0,     0,     0,     0,  1544,  1545,  1546,  1547,
    1548,  1549,  1550,  1551,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1544,  1545,  1546,
    1547,  1548,  1549,  1550,  1551,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    99,   100,   101,   102,
     103,     0,     0,     0,   104,     0,     0,     0,     0,  1544,
    1545,  1546,  1547,  1548,  1549,  1550,  1551,   105,     0,     0,
     106,   107,   108,   109,     0,   110,   111,   112,   113,     0,
       0,     0,   114,     0,     0,   115,     0,   116,   117,   118,
     119,   120,     0,   121,     0,     0,   122,     0,   123,     0,
       0,   124,     0,     0,   125,   126,   127,   128,   129,   130,
       0,     0,   131,   132,   133,   134,     0,     0,   135,     0,
     136,   137,   138,     0,   139,     0,   140,   141,     0,     0,
       0,     0,   142,   143,   144,   145,  1782,   146,   147,   148,
       0,   149,     0,   150,   151,     0,     0,   152,   153,     0,
     154,     0,   155,     0,     0,   156,     0,     0,     0,     0,
     157,  2011,     0,   158,     0,     0,   159,   160,   161,     0,
     162,   163,   164,     0,     0,   165,   166,     0,   167,     0,
     168,   169,   170,     0,     0,     0,     0,   171,     0,   172,
       0,   173,     0,     0,     0,   174,     0,     0,   175,   176,
     177,     0,   178,     0,   179,     0,     0,   180,     0,     0,
     181,     0,     0,     0,     0,     0,   182,   183,   345,     0,
       0,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,     0,   202,   203,   204,   205,   206,   207,
     208,   209,     0,   210,   211,   212,     0,   213,     0,   214,
       0,     0,   215,     0,   216,   217,     0,     0,     0,     0,
       0,     0,     0,   218,   219,   220,     0,     0,   221,   222,
     223,   224,   225,   226,   227,   228,     0,     0,     0,     0,
     229,     0,   230,     0,   231,   232,     0,     0,   233,   234,
     235,   236,     0,     0,   237,   238,   239,   240,   241,     0,
       0,     0,   242,   243,     0,   244,     0,     0,   245,   246,
       0,   346,     0,     0,   247,     0,   248,   249,     0,     0,
       0,     0,   250,     0,   251,   252,     0,   253,     0,     0,
       0,   254,     0,     0,   255,     0,   256,     0,     0,     0,
       0,   257,     0,   258,   259,   260,   261,     0,     0,     0,
     262,     0,   263,   264,     0,     0,   265,   266,     0,   267,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
     269,   270,     0,   271,     0,   272,   273,   274,   275,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   276,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   277,     0,     0,
       0,     0,     0,     0,   278,   279,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   280,     0,     0,   281,
       0,     0,     0,   282,   283,     0,   284,     0,     0,     0,
       0,   285,     0,     0,     0,   286,     0,     0,   287,   288,
     289,   290,     0,     0,     0,   291,   292,   293,     0,   294,
     295,     0,   296,     0,   297,     0,     0,     0,     0,     0,
       0,   298,     0,   299,   300,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   301,    99,   100,   101,
     102,   103,   302,     0,   303,   104,     0,   304,     0,     0,
     305,     0,   306,     0,   307,   308,   309,     0,   105,     0,
       0,   106,   107,   108,   109,     0,   110,   111,   112,   113,
       0,     0,     0,   114,     0,     0,   115,     0,   116,   117,
     118,   119,   120,     0,   121,     0,     0,   122,     0,   123,
       0,     0,   124,     0,     0,   125,   126,   127,   128,   129,
     130,     0,     0,   131,   132,   133,   134,     0,     0,   135,
       0,   136,   137,   138,     0,   139,     0,   140,   141,     0,
       0,     0,     0,   142,   143,   144,   145,  2018,   146,   147,
     148,     0,   149,     0,   150,   151,     0,     0,   152,   153,
       0,   154,     0,   155,     0,     0,   156,     0,     0,     0,
       0,   157,  2019,     0,   158,     0,     0,   159,   160,   161,
       0,   162,   163,   164,     0,     0,   165,   166,     0,   167,
       0,   168,   169,   170,     0,     0,     0,     0,   171,     0,
     172,     0,   173,     0,     0,     0,   174,     0,     0,   175,
     176,   177,     0,   178,     0,   179,     0,     0,   180,     0,
       0,   181,     0,     0,     0,     0,     0,   182,   183,   345,
       0,     0,   184,     0,   185,     0,     0,     0,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,     0,   202,   203,   204,   205,   206,
     207,   208,   209,     0,   210,   211,   212,     0,   213,     0,
     214,     0,     0,   215,     0,   216,   217,     0,     0,     0,
       0,     0,     0,     0,   218,   219,   220,     0,     0,   221,
     222,   223,   224,   225,   226,   227,   228,     0,     0,     0,
       0,   229,     0,   230,     0,   231,   232,     0,     0,   233,
     234,   235,   236,     0,     0,   237,   238,   239,   240,   241,
       0,     0,     0,   242,   243,     0,   244,     0,     0,   245,
     246,     0,   346,     0,     0,   247,     0,   248,   249,     0,
       0,     0,     0,   250,     0,   251,   252,     0,   253,     0,
       0,     0,   254,     0,     0,   255,     0,   256,     0,     0,
       0,     0,   257,     0,   258,   259,   260,   261,     0,     0,
       0,   262,     0,   263,   264,     0,     0,   265,   266,     0,
     267,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     268,   269,   270,     0,   271,     0,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   276,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   277,     0,
       0,     0,     0,     0,     0,   278,   279,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   280,     0,     0,
     281,     0,     0,     0,   282,   283,     0,   284,     0,     0,
       0,     0,   285,     0,     0,     0,   286,     0,     0,   287,
     288,   289,   290,     0,     0,     0,   291,   292,   293,     0,
     294,   295,     0,   296,     0,   297,     0,     0,     0,     0,
       0,     0,   298,     0,   299,   300,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   301,    99,   100,
     101,   102,   103,   302,     0,   303,   104,     0,   304,     0,
       0,   305,     0,   306,     0,   307,   308,   309,     0,   105,
       0,     0,   106,   107,   108,   109,     0,   110,   111,   112,
     113,     0,     0,     0,   114,     0,     0,   115,     0,   116,
     117,   118,   119,   120,     0,   121,     0,     0,   122,     0,
     123,     0,     0,   124,     0,     0,   125,   126,   127,   128,
     129,   130,     0,     0,   131,   132,   133,   134,     0,     0,
     135,     0,   136,   137,   138,     0,   139,     0,   140,   141,
       0,     0,     0,     0,   142,   143,   144,   145,     0,   146,
     147,   148,     0,   149,     0,   150,   151,     0,     0,   152,
     153,     0,   154,     0,   155,     0,     0,   156,     0,     0,
     946,     0,   157,     0,     0,   158,     0,     0,   159,   160,
     161,     0,   162,   163,   164,     0,     0,   165,   166,     0,
     167,     0,   168,   169,   170,     0,     0,     0,     0,   171,
       0,   172,     0,   173,     0,     0,     0,   174,     0,     0,
     175,   176,   177,     0,   178,     0,   179,     0,     0,   180,
       0,     0,   181,     0,     0,     0,     0,     0,   182,   183,
     345,     0,     0,   184,     0,   185,     0,     0,     0,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,     0,   202,   203,   204,   205,
     206,   207,   208,   209,     0,   210,   211,   212,     0,   213,
       0,   214,     0,     0,   215,     0,   216,   217,     0,     0,
       0,     0,     0,     0,     0,   218,   219,   220,     0,     0,
     221,   222,   223,   224,   225,   226,   227,   228,     0,     0,
       0,     0,   229,     0,   230,     0,   231,   232,     0,     0,
     233,   234,   235,   236,     0,     0,   237,   238,   239,   240,
     241,     0,     0,     0,   242,   243,     0,   244,     0,     0,
     245,   246,     0,   346,     0,     0,   247,     0,   248,   249,
       0,     0,     0,     0,   250,     0,   251,   252,     0,   253,
       0,     0,     0,   254,     0,     0,   255,     0,   256,     0,
       0,     0,     0,   257,     0,   258,   259,   260,   261,     0,
       0,     0,   262,     0,   263,   264,     0,     0,   265,   266,
       0,   267,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,   269,   270,     0,   271,     0,   272,   273,   274,
     275,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   277,
       0,     0,     0,     0,     0,     0,   278,   279,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   280,     0,
       0,   281,     0,     0,     0,   282,   283,     0,   284,     0,
       0,     0,     0,   285,     0,     0,     0,   286,     0,     0,
     287,   288,   289,   290,     0,     0,     0,   291,   292,   293,
       0,   294,   295,     0,   296,     0,   297,     0,     0,     0,
       0,     0,     0,   298,     0,   299,   300,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   301,    99,
     100,   101,   102,   103,   302,     0,   303,   104,     0,   304,
       0,     0,   305,     0,   306,     0,   307,   308,   309,     0,
     105,     0,     0,   106,   107,   108,   109,     0,   110,   111,
     112,   113,     0,     0,     0,   114,     0,     0,   115,     0,
     116,   117,   118,   119,   120,     0,   121,     0,     0,   122,
       0,   123,     0,     0,   124,     0,     0,   125,   126,   127,
     128,   129,   130,     0,     0,   131,   132,   133,   134,     0,
       0,   135,     0,   136,   137,   138,     0,   139,     0,   140,
     141,     0,     0,     0,     0,   142,   143,   144,   145,  1782,
     146,   147,   148,     0,   149,     0,   150,   151,     0,     0,
     152,   153,     0,   154,     0,   155,     0,     0,   156,     0,
       0,     0,     0,   157,     0,     0,   158,     0,     0,   159,
     160,   161,     0,   162,   163,   164,     0,     0,   165,   166,
       0,   167,     0,   168,   169,   170,     0,     0,     0,     0,
     171,     0,   172,     0,   173,     0,     0,     0,   174,     0,
       0,   175,   176,   177,     0,   178,     0,   179,     0,     0,
     180,     0,     0,   181,     0,     0,     0,     0,     0,   182,
     183,   345,     0,     0,   184,     0,   185,     0,     0,     0,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,     0,   202,   203,   204,
     205,   206,   207,   208,   209,     0,   210,   211,   212,     0,
     213,     0,   214,     0,     0,   215,     0,   216,   217,     0,
       0,     0,     0,     0,     0,     0,   218,   219,   220,     0,
       0,   221,   222,   223,   224,   225,   226,   227,   228,     0,
       0,     0,     0,   229,     0,   230,     0,   231,   232,     0,
       0,   233,   234,   235,   236,     0,     0,   237,   238,   239,
     240,   241,     0,     0,     0,   242,   243,     0,   244,     0,
       0,   245,   246,     0,   346,     0,     0,   247,     0,   248,
     249,     0,     0,     0,     0,   250,     0,   251,   252,     0,
     253,     0,     0,     0,   254,     0,     0,   255,     0,   256,
       0,     0,     0,     0,   257,     0,   258,   259,   260,   261,
       0,     0,     0,   262,     0,   263,   264,     0,     0,   265,
     266,     0,   267,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   268,   269,   270,     0,   271,     0,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   276,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     277,     0,     0,     0,     0,     0,     0,   278,   279,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   280,
       0,     0,   281,     0,     0,     0,   282,   283,     0,   284,
       0,     0,     0,     0,   285,     0,     0,     0,   286,     0,
       0,   287,   288,   289,   290,     0,     0,     0,   291,   292,
     293,     0,   294,   295,     0,   296,     0,   297,     0,     0,
       0,     0,     0,     0,   298,     0,   299,   300,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   301,
      99,   100,   101,   102,   103,   302,     0,   303,   104,     0,
     304,     0,     0,   305,     0,   306,     0,   307,   308,   309,
       0,   105,     0,     0,   106,   107,   108,   109,     0,   110,
     111,   112,   113,     0,     0,     0,   114,     0,     0,   115,
       0,   116,   117,   118,   119,   120,     0,   121,     0,     0,
     122,     0,   123,     0,     0,   124,     0,     0,   125,   126,
     127,   128,   129,   130,     0,     0,   131,   132,   133,   134,
       0,     0,   135,     0,   136,   137,   138,     0,   139,     0,
     140,   141,     0,     0,     0,     0,   142,   143,   144,   145,
       0,   146,   147,   148,     0,   149,     0,   150,   151,     0,
       0,   152,   153,     0,   154,     0,   155,     0,     0,   156,
       0,     0,     0,     0,   157,  2348,     0,   158,     0,     0,
     159,   160,   161,     0,   162,   163,   164,     0,     0,   165,
     166,     0,   167,     0,   168,   169,   170,     0,     0,     0,
       0,   171,     0,   172,     0,   173,     0,     0,     0,   174,
       0,     0,   175,   176,   177,     0,   178,     0,   179,     0,
       0,   180,     0,     0,   181,     0,     0,     0,     0,     0,
     182,   183,   345,     0,     0,   184,     0,   185,     0,     0,
       0,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,     0,   202,   203,
     204,   205,   206,   207,   208,   209,     0,   210,   211,   212,
       0,   213,     0,   214,     0,     0,   215,     0,   216,   217,
       0,     0,     0,     0,     0,     0,     0,   218,   219,   220,
       0,     0,   221,   222,   223,   224,   225,   226,   227,   228,
       0,     0,     0,     0,   229,     0,   230,     0,   231,   232,
       0,     0,   233,   234,   235,   236,     0,     0,   237,   238,
     239,   240,   241,     0,     0,     0,   242,   243,     0,   244,
       0,     0,   245,   246,     0,   346,     0,     0,   247,     0,
     248,   249,     0,     0,     0,     0,   250,     0,   251,   252,
       0,   253,     0,     0,     0,   254,     0,     0,   255,     0,
     256,     0,     0,     0,     0,   257,     0,   258,   259,   260,
     261,     0,     0,     0,   262,     0,   263,   264,     0,     0,
     265,   266,     0,   267,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   268,   269,   270,     0,   271,     0,   272,
     273,   274,   275,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   276,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   277,     0,     0,     0,     0,     0,     0,   278,   279,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     280,     0,     0,   281,     0,     0,     0,   282,   283,     0,
     284,     0,     0,     0,     0,   285,     0,     0,     0,   286,
       0,     0,   287,   288,   289,   290,     0,     0,     0,   291,
     292,   293,     0,   294,   295,     0,   296,     0,   297,     0,
       0,     0,     0,     0,     0,   298,     0,   299,   300,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     301,    99,   100,   101,   102,   103,   302,     0,   303,   104,
       0,   304,     0,     0,   305,     0,   306,     0,   307,   308,
     309,     0,   105,     0,     0,   106,   107,   108,   109,     0,
     110,   111,   112,   113,     0,     0,     0,   114,     0,     0,
     115,     0,   116,   117,   118,   119,   120,     0,   121,     0,
       0,   122,     0,   123,     0,     0,   124,     0,     0,   125,
     126,   127,   128,   129,   130,     0,     0,   131,   132,   133,
     134,     0,     0,   135,     0,   136,   137,   138,     0,   139,
       0,   140,   141,     0,     0,     0,     0,   142,   143,   144,
     145,     0,   146,   147,   148,     0,   149,     0,   150,   151,
       0,     0,   152,   153,     0,   154,     0,   155,     0,     0,
     156,     0,     0,     0,     0,   157,     0,     0,   158,     0,
       0,   159,   160,   161,     0,   162,   163,   164,     0,     0,
     165,   166,     0,   167,     0,   168,   169,   170,     0,     0,
       0,     0,   171,     0,   172,     0,   173,     0,     0,     0,
     174,     0,     0,   175,   176,   177,     0,   178,     0,   179,
       0,     0,   180,     0,     0,   181,     0,     0,     0,     0,
       0,   182,   183,   345,     0,     0,   184,     0,   185,     0,
       0,     0,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,     0,   202,
     203,   204,   205,   206,   207,   208,   209,     0,   210,   211,
     212,     0,   213,     0,   214,     0,     0,   215,     0,   216,
     217,     0,     0,     0,     0,     0,     0,     0,   218,   219,
     220,     0,     0,   221,   222,   223,   224,   225,   226,   227,
     228,     0,     0,     0,     0,   229,     0,   230,     0,   231,
     232,     0,     0,   233,   234,   235,   236,     0,     0,   237,
     238,   239,   240,   241,     0,     0,     0,   242,   243,     0,
     244,     0,     0,   245,   246,     0,   346,     0,     0,   247,
       0,   248,   249,     0,     0,     0,     0,   250,     0,   251,
     252,     0,   253,     0,     0,     0,   254,     0,     0,   255,
       0,   256,     0,     0,     0,     0,   257,     0,   258,   259,
     260,   261,     0,     0,     0,   262,     0,   263,   264,     0,
       0,   265,   266,     0,   267,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   268,   269,   270,     0,   271,     0,
     272,   273,   274,   275,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   276,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   277,     0,     0,     0,     0,     0,     0,   278,
     279,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   280,     0,     0,   281,     0,     0,     0,   282,   283,
       0,   284,     0,     0,     0,     0,   285,     0,     0,     0,
     286,     0,     0,   287,   288,   289,   290,     0,     0,     0,
     291,   292,   293,     0,   294,   295,     0,   296,     0,   297,
       0,     0,     0,     0,     0,     0,   298,     0,   299,   300,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   301,    99,   100,   101,   102,   103,   302,     0,   303,
     104,     0,   304,     0,     0,   305,     0,   306,     0,   307,
     308,   309,     0,   105,     0,     0,   106,   107,   108,   109,
       0,   110,   111,   112,   113,     0,     0,     0,   114,     0,
       0,   115,     0,   116,   117,   118,   119,   120,     0,   121,
       0,     0,   122,     0,   123,     0,     0,   124,     0,     0,
     125,   126,   127,   128,   129,   130,     0,     0,   131,   132,
     133,   134,     0,     0,   135,     0,   136,   137,   138,     0,
     139,     0,   140,   141,     0,     0,     0,     0,   142,   143,
     144,   145,     0,   146,   147,   148,     0,   149,     0,   150,
     151,     0,     0,   152,   153,     0,   154,     0,   155,     0,
       0,   156,     0,     0,     0,     0,   157,     0,     0,   158,
       0,     0,   159,   160,   161,     0,   162,   163,   164,     0,
       0,   165,   166,     0,   167,     0,   168,   169,   170,     0,
       0,     0,     0,   171,     0,   172,     0,   173,     0,     0,
       0,   174,  1274,     0,   175,   176,   177,     0,   178,     0,
     179,     0,     0,   180,     0,     0,   181,     0,     0,     0,
       0,     0,   182,   183,     0,     0,     0,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,     0,
     202,   203,   204,   205,   206,   207,   208,   209,     0,   210,
     211,   212,     0,   213,     0,   214,     0,     0,   215,     0,
     216,   217,     0,     0,     0,     0,     0,     0,     0,   218,
     219,   220,     0,     0,   221,   222,   223,   224,   225,   226,
     227,   228,     0,     0,     0,     0,   229,     0,   230,     0,
     231,   232,     0,     0,   233,   234,   235,   236,     0,     0,
     237,   238,   239,   240,   241,     0,     0,     0,   242,   243,
       0,   244,     0,     0,   245,   246,     0,   384,     0,     0,
     247,     0,   248,   249,     0,     0,     0,     0,   250,     0,
     251,   252,     0,   253,     0,     0,     0,   254,     0,     0,
     255,     0,   256,     0,     0,     0,     0,   257,     0,   258,
     259,   260,   261,     0,     0,     0,   262,     0,   263,   264,
       0,     0,   265,   266,     0,   267,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   268,   269,   270,     0,   271,
       0,   272,   273,   274,   275,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   276,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   277,     0,     0,     0,     0,     0,     0,
     278,   279,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   280,     0,     0,   281,     0,     0,     0,   282,
     283,     0,   284,     0,     0,     0,     0,   285,     0,     0,
       0,   286,     0,     0,   287,   288,   289,   290,     0,     0,
       0,   291,   292,   293,     0,   294,   295,     0,   296,     0,
     297,     0,     0,     0,     0,     0,     0,   298,     0,   299,
     300,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   301,    99,   100,   101,   102,   103,   302,     0,
     303,   104,     0,   304,     0,     0,   305,     0,   306,     0,
     307,   308,   309,     0,   105,     0,     0,   106,   107,   108,
     109,     0,   110,   111,   112,   113,     0,     0,     0,   114,
       0,     0,   115,     0,   116,   117,   118,   119,   120,     0,
     121,     0,     0,   122,     0,   123,     0,     0,   124,     0,
       0,   125,   126,   127,   128,   129,   130,     0,     0,   131,
     132,   133,   134,     0,     0,   135,     0,   136,   137,   138,
       0,   139,     0,   140,   141,     0,     0,  2267,     0,   142,
     143,   144,   145,     0,   146,   147,   148,     0,   149,     0,
     150,   151,     0,     0,   152,   153,     0,   154,     0,   155,
       0,     0,   156,     0,     0,     0,     0,   157,     0,     0,
     158,     0,     0,   159,   160,   161,     0,   162,   163,   164,
       0,     0,   165,   166,     0,   167,     0,   168,   169,   170,
       0,     0,     0,     0,   171,     0,   172,     0,   173,     0,
       0,     0,   174,     0,     0,   175,   176,   177,     0,   178,
       0,   179,     0,     0,   180,     0,     0,   181,     0,     0,
       0,     0,     0,   182,   183,     0,     0,     0,   184,     0,
     185,     0,     0,     0,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
       0,   202,   203,   204,   205,   206,   207,   208,   209,     0,
     210,   211,   212,     0,   213,     0,   214,     0,     0,   215,
       0,   216,   217,     0,     0,     0,     0,     0,     0,     0,
     218,   219,   220,     0,     0,   221,   222,   223,   224,   225,
     226,   227,   228,     0,     0,     0,     0,   229,     0,   230,
       0,   231,   232,     0,     0,   233,   234,   235,   236,     0,
       0,   237,   238,   239,   240,   241,     0,     0,     0,   242,
     243,     0,   244,     0,     0,   245,   246,     0,   346,     0,
       0,   247,     0,   248,   249,     0,     0,     0,     0,   250,
       0,   251,   252,     0,   253,     0,     0,     0,   254,     0,
       0,   255,     0,   256,     0,     0,     0,     0,   257,     0,
     258,   259,   260,   261,     0,     0,     0,   262,     0,   263,
     264,     0,     0,   265,   266,     0,   267,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   268,   269,   270,     0,
     271,     0,   272,   273,   274,   275,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   277,     0,     0,     0,     0,     0,
       0,   278,   279,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   280,     0,     0,   281,     0,     0,     0,
     282,   283,     0,   284,     0,     0,     0,     0,   285,     0,
       0,     0,   286,     0,     0,   287,   288,   289,   290,     0,
       0,     0,   291,   292,   293,     0,   294,   295,     0,   296,
       0,   297,     0,     0,     0,     0,     0,     0,   298,     0,
     299,   300,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   301,    99,   100,   101,   102,   103,   302,
       0,   303,   104,     0,   304,     0,     0,   305,     0,   306,
       0,   307,   308,   309,     0,   105,     0,     0,   106,   107,
     108,   109,     0,   110,   111,   112,   113,     0,     0,     0,
     114,     0,     0,   115,     0,   116,   117,   118,   119,   120,
       0,   121,     0,     0,   122,     0,   123,     0,     0,   124,
       0,     0,   125,   126,   127,   128,   129,   130,     0,     0,
     131,   132,   133,   134,     0,     0,   135,     0,   136,   137,
     138,     0,   139,     0,   140,   141,     0,     0,     0,     0,
     142,   143,   144,   145,     0,   146,   147,   148,     0,   149,
       0,   150,   151,     0,     0,   152,   153,     0,   154,     0,
     155,     0,     0,   156,     0,     0,     0,     0,   157,     0,
       0,   158,     0,     0,   159,   160,   161,     0,   162,   163,
     164,     0,     0,   165,   166,     0,   167,     0,   168,   169,
     170,     0,     0,     0,   935,   171,     0,   172,     0,   173,
       0,     0,     0,   174,     0,     0,   175,   176,   177,     0,
     178,     0,   179,     0,     0,   180,     0,     0,   181,     0,
       0,     0,     0,     0,   182,   183,     0,     0,     0,   184,
       0,   185,     0,     0,     0,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,     0,   202,   203,   204,   205,   206,   207,   208,   209,
       0,   210,   211,   212,     0,   213,     0,   214,     0,     0,
     215,     0,   216,   217,     0,     0,     0,     0,     0,     0,
       0,   218,   219,   220,     0,     0,   221,   222,   223,   224,
     225,   226,   227,   228,     0,     0,     0,     0,   229,     0,
     230,     0,   231,   232,     0,     0,   233,   234,   235,   236,
       0,     0,   237,   238,   239,   240,   241,     0,     0,     0,
     242,   243,     0,   244,     0,     0,   245,   246,     0,     0,
       0,     0,   247,     0,   248,   249,     0,     0,     0,     0,
     250,     0,   251,   252,     0,   253,     0,     0,     0,   254,
       0,     0,   255,     0,   256,     0,     0,     0,     0,   257,
       0,   258,   259,   260,   261,     0,     0,     0,   262,     0,
     263,   264,     0,     0,   265,   266,     0,   267,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   268,   269,   270,
       0,   271,     0,   272,   273,   274,   275,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   276,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   277,     0,     0,     0,     0,
       0,     0,   278,   279,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   280,     0,     0,   281,     0,     0,
       0,   282,   283,     0,   284,     0,     0,     0,     0,   285,
       0,     0,     0,   286,     0,     0,   287,   288,   289,   290,
       0,     0,     0,   291,   292,   293,     0,   294,   295,     0,
     296,     0,   297,     0,     0,     0,     0,     0,     0,   298,
       0,   299,   300,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   301,    99,   100,   101,   102,   103,
     302,     0,   303,   104,     0,   304,     0,     0,   305,     0,
     306,     0,   307,   308,   309,     0,   105,     0,     0,   106,
     107,   108,   109,     0,   110,   111,   112,   113,     0,     0,
       0,   114,     0,     0,   115,     0,   116,   117,   118,   119,
     120,     0,   121,     0,     0,   122,     0,   123,     0,     0,
     124,     0,     0,   125,   126,   127,   128,   129,   130,     0,
       0,   131,   132,   133,   134,     0,     0,   135,     0,   136,
     137,   138,     0,   139,     0,   140,   141,     0,     0,     0,
       0,   142,   143,   144,   145,     0,   146,   147,   148,     0,
     149,     0,   150,   151,     0,     0,   152,   153,     0,   154,
       0,   155,     0,     0,   156,     0,     0,     0,     0,   157,
    1608,     0,   158,     0,     0,   159,   160,   161,     0,   162,
     163,   164,     0,     0,   165,   166,     0,   167,     0,   168,
     169,   170,     0,     0,     0,     0,   171,     0,   172,     0,
     173,     0,     0,     0,   174,     0,     0,   175,   176,   177,
       0,   178,     0,   179,     0,     0,   180,     0,     0,   181,
       0,     0,     0,     0,     0,   182,   183,     0,     0,     0,
     184,     0,   185,     0,     0,     0,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,     0,   202,   203,   204,   205,   206,   207,   208,
     209,     0,   210,   211,   212,     0,   213,     0,   214,     0,
       0,   215,     0,   216,   217,     0,     0,     0,     0,     0,
       0,     0,   218,   219,   220,     0,     0,   221,   222,   223,
     224,   225,   226,   227,   228,     0,     0,     0,     0,   229,
       0,   230,     0,   231,   232,     0,     0,   233,   234,   235,
     236,     0,     0,   237,   238,   239,   240,   241,     0,     0,
       0,   242,   243,     0,   244,     0,     0,   245,   246,     0,
       0,     0,     0,   247,     0,   248,   249,     0,     0,     0,
       0,   250,     0,   251,   252,     0,   253,     0,     0,     0,
     254,     0,     0,   255,     0,   256,     0,     0,     0,     0,
     257,     0,   258,   259,   260,   261,     0,     0,     0,   262,
       0,   263,   264,     0,     0,   265,   266,     0,   267,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   268,   269,
     270,     0,   271,     0,   272,   273,   274,   275,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   276,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   277,     0,     0,     0,
       0,     0,     0,   278,   279,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   280,     0,     0,   281,     0,
       0,     0,   282,   283,     0,   284,     0,     0,     0,     0,
     285,     0,     0,     0,   286,     0,     0,   287,   288,   289,
     290,     0,     0,     0,   291,   292,   293,     0,   294,   295,
       0,   296,     0,   297,     0,     0,     0,     0,     0,     0,
     298,     0,   299,   300,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   301,    99,   100,   101,   102,
     103,   302,     0,   303,   104,     0,   304,     0,     0,   305,
       0,   306,     0,   307,   308,   309,     0,   105,     0,     0,
     106,   107,   108,   109,     0,   110,   111,   112,   113,     0,
       0,     0,   114,     0,     0,   115,     0,   116,   117,   118,
     119,   120,     0,   121,     0,     0,   122,     0,   123,     0,
       0,   124,     0,     0,   125,   126,   127,   128,   129,   130,
       0,     0,   131,   132,   133,   134,     0,     0,   135,     0,
     136,   137,   138,     0,   139,     0,   140,   141,     0,     0,
       0,     0,   142,   143,   144,   145,     0,   146,   147,   148,
       0,   149,     0,   150,   151,     0,     0,   152,   153,     0,
     154,     0,   155,     0,     0,   156,     0,     0,     0,     0,
     157,  1645,     0,   158,     0,     0,   159,   160,   161,     0,
     162,   163,   164,     0,     0,   165,   166,     0,   167,     0,
     168,   169,   170,     0,     0,     0,     0,   171,     0,   172,
       0,   173,     0,     0,     0,   174,     0,     0,   175,   176,
     177,     0,   178,     0,   179,     0,     0,   180,     0,     0,
     181,     0,     0,     0,     0,     0,   182,   183,     0,     0,
       0,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,     0,   202,   203,   204,   205,   206,   207,
     208,   209,     0,   210,   211,   212,     0,   213,     0,   214,
       0,     0,   215,     0,   216,   217,     0,     0,     0,     0,
       0,     0,     0,   218,   219,   220,     0,     0,   221,   222,
     223,   224,   225,   226,   227,   228,     0,     0,     0,     0,
     229,     0,   230,     0,   231,   232,     0,     0,   233,   234,
     235,   236,     0,     0,   237,   238,   239,   240,   241,     0,
       0,     0,   242,   243,     0,   244,     0,     0,   245,   246,
       0,     0,     0,     0,  1646,     0,   248,   249,     0,     0,
       0,     0,   250,     0,   251,   252,     0,   253,     0,     0,
       0,   254,     0,     0,   255,     0,   256,     0,     0,     0,
       0,   257,     0,   258,   259,   260,   261,     0,     0,     0,
     262,     0,   263,   264,     0,     0,   265,   266,     0,   267,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
     269,   270,     0,   271,     0,   272,   273,   274,   275,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   276,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   277,     0,     0,
       0,     0,     0,     0,   278,   279,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   280,     0,     0,   281,
       0,     0,     0,   282,   283,     0,   284,     0,     0,     0,
       0,   285,     0,     0,     0,   286,     0,     0,   287,   288,
     289,   290,     0,     0,     0,   291,   292,   293,     0,   294,
     295,     0,   296,     0,   297,     0,     0,     0,     0,     0,
       0,   298,     0,   299,   300,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   301,    99,   100,   101,
     102,   103,   302,     0,   303,   104,     0,   304,     0,     0,
     305,     0,   306,     0,   307,   308,   309,     0,   105,     0,
       0,   106,   107,   108,   109,     0,   110,   111,   112,   113,
       0,     0,     0,   114,     0,     0,   115,     0,   116,   117,
     118,   119,   120,     0,   121,     0,     0,   122,     0,   123,
       0,     0,   124,     0,     0,   125,   126,   127,   128,   129,
     130,     0,     0,   131,   132,   133,   134,     0,     0,   135,
       0,   136,   137,   138,     0,   139,     0,   140,   141,     0,
       0,     0,     0,   142,   143,   144,   145,     0,   146,   147,
     148,     0,   149,     0,   150,   151,     0,     0,   152,   153,
       0,   154,     0,   155,     0,     0,   156,     0,     0,     0,
       0,   157,     0,     0,   158,     0,     0,   159,   160,   161,
       0,   162,   163,   164,     0,     0,   165,   166,     0,   167,
       0,   168,   169,   170,     0,     0,     0,     0,   171,     0,
     172,     0,   173,     0,     0,     0,   174,     0,     0,   175,
     176,   177,     0,   178,     0,   179,     0,     0,   180,     0,
       0,   181,     0,     0,     0,     0,     0,   182,   183,     0,
       0,     0,   184,     0,   185,     0,     0,     0,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,     0,   202,   203,   204,   205,   206,
     207,   208,   209,     0,   210,   211,   212,     0,   213,     0,
     214,     0,     0,   215,     0,   216,   217,     0,     0,     0,
       0,     0,     0,     0,   218,   219,   220,  2303,     0,   221,
     222,   223,   224,   225,   226,   227,   228,     0,     0,     0,
       0,   229,     0,   230,     0,   231,   232,     0,     0,   233,
     234,   235,   236,     0,     0,   237,   238,   239,   240,   241,
       0,     0,     0,   242,   243,     0,   244,     0,     0,   245,
     246,     0,     0,     0,     0,   247,     0,   248,   249,     0,
       0,     0,     0,   250,     0,   251,   252,     0,   253,     0,
       0,     0,   254,     0,     0,   255,     0,   256,     0,     0,
       0,     0,   257,     0,   258,   259,   260,   261,     0,     0,
       0,   262,     0,   263,   264,     0,     0,   265,   266,     0,
     267,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     268,   269,   270,     0,   271,     0,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   276,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   277,     0,
       0,     0,     0,     0,     0,   278,   279,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   280,     0,     0,
     281,     0,     0,     0,   282,   283,     0,   284,     0,     0,
       0,     0,   285,     0,     0,     0,   286,     0,     0,   287,
     288,   289,   290,     0,     0,     0,   291,   292,   293,     0,
     294,   295,     0,   296,     0,   297,     0,     0,     0,     0,
       0,     0,   298,     0,   299,   300,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   301,    99,   100,
     101,   102,   103,   302,     0,   303,   104,     0,   304,     0,
       0,   305,     0,   306,     0,   307,   308,   309,     0,   105,
       0,     0,   106,   107,   108,   109,     0,   110,   111,   112,
     113,     0,     0,     0,   114,     0,     0,   115,     0,   116,
     117,   118,   119,   120,     0,   121,     0,     0,   122,     0,
     123,     0,     0,   124,     0,     0,   125,   126,   127,   128,
     129,   130,     0,     0,   131,   132,   133,   134,     0,     0,
     135,     0,   136,   137,   138,     0,   139,     0,   140,   141,
       0,     0,     0,     0,   142,   143,   144,   145,     0,   146,
     147,   148,     0,   149,     0,   150,   151,     0,     0,   152,
     153,     0,   154,     0,   155,     0,     0,   156,     0,     0,
       0,     0,   157,     0,     0,   158,     0,     0,   159,   160,
     161,     0,   162,   163,   164,     0,     0,   165,   166,     0,
     167,     0,   168,   169,   170,     0,     0,     0,     0,   171,
       0,   172,     0,   173,     0,     0,     0,   174,     0,     0,
     175,   176,   177,     0,   178,     0,   179,     0,     0,   180,
       0,     0,   181,     0,     0,     0,     0,     0,   182,   183,
       0,     0,     0,   184,     0,   185,     0,     0,     0,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,     0,   202,   203,   204,   205,
     206,   207,   208,   209,     0,   210,   211,   212,     0,   213,
       0,   214,     0,     0,   215,     0,   216,   217,     0,     0,
       0,     0,     0,     0,     0,   218,   219,   220,     0,     0,
     221,   222,   223,   224,   225,   226,   227,   228,     0,     0,
       0,     0,   229,     0,   230,     0,   231,   232,     0,     0,
     233,   234,   235,   236,     0,     0,   237,   238,   239,   240,
     241,     0,     0,     0,   242,   243,     0,   244,     0,     0,
     245,   246,     0,   346,     0,     0,   247,     0,   248,   249,
       0,     0,     0,     0,   250,     0,   251,   252,     0,   253,
       0,     0,     0,   254,     0,     0,   255,     0,   256,     0,
       0,     0,     0,   257,     0,   258,   259,   260,   261,     0,
       0,     0,   262,     0,   263,   264,     0,     0,   265,   266,
       0,   267,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,   269,   270,     0,   271,     0,   272,   273,   274,
     275,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   277,
       0,     0,     0,     0,     0,     0,   278,   279,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   280,     0,
       0,   281,     0,     0,     0,   282,   283,     0,   284,     0,
       0,     0,     0,   285,     0,     0,     0,   286,     0,     0,
     287,   288,   289,   290,     0,     0,     0,   291,   292,   293,
       0,   294,   295,     0,   296,     0,   297,     0,     0,     0,
       0,     0,     0,   298,     0,   299,   300,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   301,    99,
     100,   101,   102,   103,   302,     0,   303,   104,     0,   304,
       0,     0,   305,     0,   306,     0,   307,   308,   309,     0,
     105,     0,     0,   106,   107,   108,   109,     0,   110,   111,
     112,   113,     0,     0,     0,   114,     0,     0,   115,     0,
     116,   117,   118,   119,   120,     0,   121,     0,     0,   122,
       0,   123,     0,     0,   124,     0,     0,   125,   126,   127,
     128,   129,   130,     0,     0,   131,   132,   133,   134,     0,
       0,   135,     0,   136,   137,   138,     0,   139,     0,   140,
     141,     0,     0,     0,     0,   142,   143,   144,   145,     0,
     146,   147,   148,     0,   149,     0,   150,   151,     0,     0,
     152,   153,     0,   154,     0,   155,     0,     0,   156,     0,
       0,     0,     0,   157,  1645,     0,   158,     0,     0,   159,
     160,   161,     0,   162,   163,   164,     0,     0,   165,   166,
       0,   167,     0,   168,   169,   170,     0,     0,     0,     0,
     171,     0,   172,     0,   173,     0,     0,     0,   174,     0,
       0,   175,   176,   177,     0,   178,     0,   179,     0,     0,
     180,     0,     0,   181,     0,     0,     0,     0,     0,   182,
     183,     0,     0,     0,   184,     0,   185,     0,     0,     0,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,     0,   202,   203,   204,
     205,   206,   207,   208,   209,     0,   210,   211,   212,     0,
     213,     0,   214,     0,     0,   215,     0,   216,   217,     0,
       0,     0,     0,     0,     0,     0,   218,   219,   220,     0,
       0,   221,   222,   223,   224,   225,   226,   227,   228,     0,
       0,     0,     0,   229,     0,   230,     0,   231,   232,     0,
       0,   233,   234,   235,   236,     0,     0,   237,   238,   239,
     240,   241,     0,     0,     0,   242,   243,     0,   244,     0,
       0,   245,   246,     0,     0,     0,     0,   247,     0,   248,
     249,     0,     0,     0,     0,   250,     0,   251,   252,     0,
     253,     0,     0,     0,   254,     0,     0,   255,     0,   256,
       0,     0,     0,     0,   257,     0,   258,   259,   260,   261,
       0,     0,     0,   262,     0,   263,   264,     0,     0,   265,
     266,     0,   267,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   268,   269,   270,     0,   271,     0,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   276,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     277,     0,     0,     0,     0,     0,     0,   278,   279,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   280,
       0,     0,   281,     0,     0,     0,   282,   283,     0,   284,
       0,     0,     0,     0,   285,     0,     0,     0,   286,     0,
       0,   287,   288,   289,   290,     0,     0,     0,   291,   292,
     293,     0,   294,   295,     0,   296,     0,   297,     0,     0,
       0,     0,     0,     0,   298,     0,   299,   300,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   301,
      99,   100,   101,   102,   103,   302,     0,   303,   104,     0,
     304,     0,     0,   305,     0,   306,     0,   307,   308,   309,
       0,   105,     0,     0,   106,   107,   108,   109,     0,   110,
     111,   112,   113,     0,     0,     0,   114,     0,     0,   115,
       0,   116,   117,   118,   119,   120,     0,   121,     0,     0,
     122,     0,   123,     0,     0,   124,     0,     0,   125,   126,
     127,   128,   129,   130,     0,     0,   131,   132,   133,   134,
       0,     0,   135,     0,   136,   137,   138,     0,   139,     0,
     140,   141,     0,     0,     0,     0,   142,   143,   144,   145,
       0,   146,   147,   148,     0,   149,     0,   150,   151,     0,
       0,   152,   153,     0,   154,     0,   155,     0,     0,   156,
       0,     0,     0,     0,   157,     0,     0,   158,     0,     0,
     159,   160,   161,     0,   162,   163,   164,     0,     0,   165,
     166,     0,   167,     0,   168,   169,   170,     0,     0,     0,
       0,   171,     0,   172,     0,   173,     0,     0,     0,   174,
       0,     0,   175,   176,   177,     0,   178,     0,   179,     0,
       0,   180,     0,     0,   181,     0,     0,     0,     0,     0,
     182,   183,     0,     0,     0,   184,     0,   185,     0,     0,
       0,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,     0,   202,   203,
     204,   205,   206,   207,   208,   209,     0,   210,   211,   212,
       0,   213,     0,   214,     0,     0,   215,     0,   216,   217,
       0,     0,     0,     0,     0,     0,     0,   218,   219,   220,
       0,     0,   221,   222,   223,   224,   225,   226,   227,   228,
       0,     0,     0,     0,   229,     0,   230,     0,   231,   232,
       0,     0,   233,   234,   235,   236,     0,     0,   237,   238,
     239,   240,   241,     0,     0,     0,   242,   243,     0,   244,
       0,     0,   245,   246,     0,     0,     0,     0,   247,     0,
     248,   249,     0,     0,     0,     0,   250,     0,   251,   252,
       0,   253,     0,     0,     0,   254,     0,     0,   255,     0,
     256,     0,     0,     0,     0,   257,     0,   258,   259,   260,
     261,     0,     0,     0,   262,     0,   263,   264,     0,     0,
     265,   266,     0,   267,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   268,   269,   270,     0,   271,     0,   272,
     273,   274,   275,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   276,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   277,     0,     0,     0,     0,     0,     0,   278,   279,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     280,     0,     0,   281,     0,     0,     0,   282,   283,     0,
     284,     0,     0,     0,     0,   285,     0,     0,     0,   286,
       0,     0,   287,   288,   289,   290,     0,     0,     0,   291,
     292,   293,     0,   294,   295,     0,   296,     0,   297,     0,
       0,     0,     0,     0,     0,   298,     0,   299,   300,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     301,    99,   100,   101,  1280,   103,   302,     0,   303,   104,
       0,   304,     0,     0,   305,     0,   306,     0,   307,   308,
     309,     0,   105,     0,     0,   106,   107,   108,   109,     0,
     110,   111,   112,   113,     0,     0,     0,   114,     0,     0,
     115,     0,   116,   117,   118,   119,   120,     0,   121,     0,
       0,   122,     0,   123,     0,     0,   124,     0,     0,   125,
     126,   127,   128,   129,   130,     0,     0,   131,   132,   133,
     134,     0,     0,   135,     0,   136,   137,   138,     0,   139,
       0,   140,   141,     0,     0,     0,     0,   142,   143,   144,
     145,     0,   146,   147,   148,     0,   149,     0,   150,   151,
       0,     0,   152,   153,     0,   154,     0,   155,     0,     0,
     156,     0,     0,     0,     0,   157,     0,     0,   158,     0,
       0,   159,   160,   161,     0,   162,   163,   164,     0,     0,
     165,   166,     0,   167,     0,   168,  1281,   170,     0,     0,
       0,     0,   171,     0,   172,     0,   173,     0,     0,     0,
     174,     0,     0,   175,   176,   177,     0,   178,     0,   179,
       0,     0,   180,     0,     0,   181,     0,     0,     0,     0,
       0,   182,   183,     0,     0,     0,   184,     0,   185,     0,
       0,     0,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,     0,   202,
     203,   204,   205,   206,   207,   208,   209,     0,   210,   211,
     212,     0,   213,     0,   214,     0,     0,   215,     0,   216,
     217,     0,     0,     0,     0,     0,     0,     0,   218,   219,
     220,     0,     0,   221,   222,   223,   224,   225,   226,   227,
     228,     0,     0,     0,     0,   229,     0,   230,     0,   231,
     232,     0,     0,   233,   234,   235,   236,     0,     0,   237,
     238,   239,   240,   241,     0,     0,     0,   242,   243,     0,
     244,     0,     0,   245,   246,  1681,     0,     0,     0,   247,
       0,   248,   249,     0,     0,     0,     0,   250,     0,   251,
     252,     0,   253,     0,     0,     0,   254,     0,     0,   255,
       0,   256,     0,     0,     0,     0,   257,     0,   258,   259,
     260,   261,     0,     0,     0,   262,     0,   263,   264,     0,
       0,   265,   266,     0,   267,     0,     0,     0,     0,     0,
       0,  1683,  1684,     0,   268,   269,   270,     0,   271,     0,
     272,   273,   274,   275,     0,     0,  -303,  1685,     0,     0,
    -303,     0,     0,   276,     0,     0,     0,     0,     0,  1687,
    1285,     0,  1688,     0,     0,     0,  2575,  2576,  2577,  2578,
       0,     0,   277,     0,     0,     0,     0,     0,     0,   278,
     279,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   280,     0,     0,   281,     0,     0,     0,   282,   283,
       0,   284,  1693,     0,     0,     0,   285,     0,     0,     0,
     286,     0,  2579,   287,   288,   289,   290,     0,  2113,     0,
     291,   292,   293,     0,   294,   295,     0,   296,     0,   297,
       0,     0,     0,     0,     0,     0,   298,     0,   299,   300,
       0,     0,     0,  1694,     0,     0,     0,     0,  1695,     0,
       0,   301,     0,     0,     0,  2580,     0,   302,     0,   303,
       0,     0,   304,     0,     0,   305,     0,   306,     0,   307,
     308,   309,     0,  1696,     0,     0,     0,     0,     0,     0,
       0,  2581,  1697,  1698,  1699,  2582,     0,  2583,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1701,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1702,     0,     0,     0,     0,
       0,     0,  2584,     0,  2585,     0,     0,  1703,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -303,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2586,  2587,  2588,
       0,     0,  2589,  2590,  2591,  2592,  2593,     0,  2594,  2595,
    2596,     0,  2597,  2598,  2599,  2600,  2601,  2602,     0,     0,
       0,     0,  2603,     0,  2604,     0,  2605,  2606,  2607,  2608,
    2609,  2610,     0,  1704,  2611,  2612,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1705,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2613,     0,     0,  1707,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2614,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2615,  2616,  2617,     0,     0,
       0,     0,  2618,     0,  2619,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2114,     0,     0,
       0,     0,     0,     0,  2620
};

static const short yycheck[] =
{
       2,   407,   408,   498,   610,   811,    14,   395,   396,   397,
      12,   916,    14,   919,   620,   910,   336,   369,   663,   878,
     879,   522,    24,   629,  1649,     2,  1651,  1573,   594,  1163,
     596,   597,   598,   599,   600,   852,   853,   834,   701,  1956,
     853,  1358,    44,    45,   450,   529,   905,  1192,  1272,  1678,
    1072,   848,  1977,  1682,  1195,  1292,  1224,  1596,  1743,   856,
    1201,   506,  1774,  1775,  1129,   761,   762,   569,  1292,   928,
     476,   477,   478,  2027,  2343,   641,   642,   643,  2511,   990,
      82,  1132,  2046,  1998,  1203,  1525,    42,  1152,  2003,   752,
      97,    10,   951,     3,     3,   758,    12,    68,    68,   857,
      55,  2118,    68,  2040,   144,    82,  2580,     3,   103,  2046,
      39,    68,  2049,  2050,    39,  1137,  1748,  2054,  2055,    68,
      68,    68,    10,   926,  2598,   167,   591,  2601,  1674,   159,
    1573,  2733,  2038,     3,    22,     3,  2610,   926,     3,  2056,
     635,    18,   637,   161,   639,  2082,   161,   223,   101,  2623,
    2067,  2068,   105,   171,    31,   339,    33,     4,    35,    36,
    2114,   220,    44,    40,    41,    70,   201,   280,   613,    88,
      10,     3,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,  2337,   221,     9,  1293,   279,
      12,  1325,   136,     9,   279,   179,    12,    19,    20,    21,
     108,   136,   105,    19,   251,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,   107,     9,
       3,   159,    12,  2041,  2042,   144,   280,    10,   169,    19,
      20,    21,    12,   144,   156,   164,   111,   103,   279,   164,
     169,   105,   154,     9,   169,   214,    12,  2283,    88,   159,
      87,     6,    33,    19,     3,    87,    39,     9,   296,   254,
      12,    10,   277,   275,  1475,  2732,   279,    19,    20,    21,
    2798,   109,    55,  2747,    41,   119,    86,   292,    56,    86,
    1985,   210,  2715,    87,   672,   210,   214,  2502,  2762,    70,
      89,   144,    70,  1188,  2727,  2331,   134,  2365,   524,   525,
     216,   527,   105,   260,  2771,    88,   109,  1166,   310,  1168,
     279,   631,   632,   166,    56,   317,    83,   127,  2846,   228,
     127,  2536,   337,   122,   308,   294,   646,  2722,    51,   717,
     167,   260,   228,    70,   296,   337,   302,   303,   428,    88,
     177,  1552,   295,   272,   208,   302,   303,   272,   270,    72,
     670,   279,    94,   368,  2956,   299,   368,   246,    56,   142,
     680,   314,   237,   167,   317,    39,   294,   279,   151,   152,
     690,   691,   692,   177,   218,   488,   159,   282,   260,   216,
     700,   164,   301,   166,   139,   293,   169,   571,   254,   226,
     227,  2919,  2017,  2545,   216,   339,   305,   244,  2362,   751,
     216,   354,  1199,  1843,   339,  2369,   436,   492,   873,   305,
     247,  2428,   216,  2808,   317,  1466,   273,   493,   329,  1216,
     329,   475,   226,   227,   919,  2362,   216,   210,   912,   488,
     368,   296,  2369,   329,   389,   305,   216,   305,   221,   454,
     280,   488,  2127,   247,   321,   228,   488,   488,   488,   487,
     216,   486,  1593,   317,  2982,  1272,  1214,  2086,  1563,   329,
     238,   329,   217,  1903,   216,   342,   407,  1130,   486,  1132,
    2376,  1536,  1709,   310,   306,   488,   329,   260,   407,   486,
    1339,   489,   407,   967,  1287,  2114,   488,   489,   490,   272,
     164,  2559,  1543,   488,  2126,   169,   437,  1142,  1287,  1144,
     214,   389,  2976,   214,  2978,  1527,   310,   509,   437,  1952,
    1313,  3039,   437,   296,   317,   486,   486,   300,   301,   490,
     486,   358,   305,    39,  1313,   487,   436,   529,   275,   486,
     486,   533,   509,   486,   490,   136,   210,   486,   486,   486,
     946,    99,  2360,   154,   488,  1040,   329,   221,   550,  3023,
     136,  3025,   389,   488,   358,   136,   533,   559,   486,   488,
     562,   306,   487,   488,   428,   279,   568,   483,   279,   488,
     572,   159,  2257,   216,   576,   218,   113,    39,  1746,   119,
     294,   583,   584,   294,   493,   562,  2291,  2292,  2542,   129,
      59,   167,  2556,  2988,  1818,   153,   184,   493,   272,  1094,
     140,   177,     3,  1722,  1723,  1724,   389,   144,  2684,  1520,
    2525,   181,  1731,   317,   131,   132,   473,   474,   142,  2556,
     206,   279,    25,   161,   407,   206,    40,   301,   492,     3,
      39,  2730,   145,   171,  3067,   159,   513,  2906,   515,   476,
     477,   478,   479,   480,   481,   482,   483,   184,   164,   353,
     487,   434,    66,   169,   437,   477,   478,   479,   480,   481,
     482,   483,    10,  1558,   480,   481,   482,   483,   279,  1564,
    2295,   247,   476,   477,   478,   479,   480,   481,   482,   483,
    2634,  1183,  1127,  1578,   177,   228,    39,   491,   478,   479,
     480,   481,   482,   483,   210,   280,  1392,  1393,   299,  2324,
     270,   259,   164,   147,   487,   488,    73,   169,   225,    76,
    2256,  1606,   478,   479,   480,   481,   482,   483,   119,   101,
     233,   118,  2639,   105,   476,   477,   478,   479,   480,   481,
     482,   483,   318,   407,  2810,   179,   139,   318,   339,   325,
      88,   161,  2281,   488,   325,   119,  1641,  2432,   210,  2848,
    2849,   339,   265,   339,   247,   164,   272,   224,   339,  1260,
     169,   278,  1368,   437,   161,  2205,   284,   103,    86,   427,
     428,   311,   486,  1469,  1470,   486,   300,  1129,  1946,   787,
    1264,  3089,   358,   301,     0,   787,   329,   789,  1108,  1586,
    1291,  3099,  1589,    94,     3,  1846,   798,  1460,  1863,   268,
    1152,   210,  2242,  1466,   273,  1125,   184,   120,   810,   127,
     272,   164,   221,   107,   488,  1983,   169,   167,  1986,  1987,
     264,   798,  1717,  1718,  1719,  2510,  1721,   177,  1969,  1851,
    1725,  1726,  1727,  1728,  1729,  1730,   184,   155,   337,  1904,
     309,  2795,  1659,   305,  1963,  1964,  1659,   855,  2085,   143,
    1546,  1547,   270,   855,  1988,    85,  1907,   210,  1521,  1924,
     144,  2085,   223,   272,  2576,   358,   244,   285,   221,  2014,
     120,   184,   874,   119,  1537,  2587,   878,   879,   275,   275,
    1543,   217,   101,   167,   201,   460,   105,  2516,  2517,  2518,
    1912,   407,  2817,  2605,  2606,   141,   244,   247,  1679,  1680,
    1395,  1682,   904,   905,   221,   155,  1401,   488,  2620,  2534,
     912,    10,   213,   295,  2539,  2627,   146,   919,   254,   272,
     922,   437,   924,    22,   260,  1706,   928,   904,   107,   307,
     932,   161,   314,   935,   184,   317,   182,   269,  2057,  2058,
     234,   943,  2061,  2572,   486,   407,   278,   280,   490,   951,
    2069,  2070,  2071,  2072,   272,   932,  2124,   148,   935,   307,
     216,   141,   218,  1677,   143,   967,   943,  1681,   141,  1683,
    1684,  1685,   488,   219,  1688,   437,   228,   403,    34,     3,
    1694,  1695,  1696,  1697,  1698,  1699,    10,  1701,  1702,  1703,
    1704,  1705,   141,  1707,   275,  2129,   320,   321,   407,   245,
     147,   277,   182,   297,   473,   474,   157,   158,   358,   182,
     141,   244,   203,   204,   205,    39,   317,   250,   161,   320,
     321,   345,   346,  1238,  1344,  1240,   488,   292,   437,  1244,
     263,    55,   179,   182,    90,   274,   275,   267,    94,   219,
     341,   403,  1362,  1363,   296,   346,   219,   277,   486,  1369,
     351,   182,   486,   109,   407,   234,   328,   486,  1953,   239,
     240,   486,   292,   119,    88,   245,   109,   297,   340,  1389,
     219,   343,   245,   341,   486,   222,   295,   329,   486,   488,
    1400,   187,   188,   351,   437,   166,  1406,   355,   219,  2591,
     230,   231,  2594,   199,   200,   314,   245,  1417,   317,   486,
    2602,    13,   312,   313,   350,  1113,   486,    19,  1428,    21,
     112,  1113,   493,  1115,   245,   171,   486,   264,   297,   216,
     486,   218,  2290,  1607,  2078,    67,  2080,   151,   152,   486,
    2447,   486,  3049,   352,   353,   488,   487,   488,   368,   486,
     164,   143,   166,   487,   488,   169,   487,   488,   486,   467,
     468,   469,   470,   471,   472,   486,  2051,  1802,  1803,   161,
     216,   486,   218,   486,  1166,   221,  1168,   487,   488,   171,
     350,   712,   713,   714,   715,   716,  1178,   350,   234,   486,
    1182,  1844,   486,  1846,  1536,  2207,   210,   486,  2083,   486,
    1192,   487,   488,   306,   487,   488,   486,   221,  1200,   487,
     488,   350,   279,  1523,   228,  1182,   262,   353,   354,  1211,
    1855,   486,  1857,   487,   488,   486,    56,   487,   488,   350,
     487,   488,  2244,   486,   107,  1227,  1228,   487,   488,   112,
      70,   114,   234,   486,  1211,   486,   260,   184,   487,   488,
     144,   297,  1905,  1245,  1907,   487,   488,   487,   272,   486,
    1252,  1228,   486,  1261,   216,   487,   488,  1259,   486,  1261,
     143,   486,  1264,   146,   487,   488,   487,   488,  1245,   486,
       3,  1916,   296,  1918,   486,  1252,  2755,   301,   161,  2758,
     486,   305,  2761,   486,   124,   487,   488,  2766,   171,   487,
     488,    24,   486,    26,   487,   488,  2517,  2518,   486,    32,
     486,    34,     3,  3005,  3006,   329,  2854,  2855,   486,  2788,
     486,    44,  2791,   221,   486,   486,   156,   486,   486,   486,
    1322,  1329,  1324,   486,   486,  1333,   486,  1329,   486,  1331,
     486,  1333,   486,    34,   486,   135,   486,  1339,   486,   159,
     493,   181,   486,   301,  2512,  2513,  2060,   486,   486,   486,
    1358,   234,  2066,   486,   486,    86,  1358,    90,    91,   486,
     486,   486,   486,  2258,  2259,   389,   486,   486,   486,   486,
    2504,   486,  2267,   106,   486,  2921,  1982,   486,   486,   486,
      68,   486,   115,   407,   267,   118,   119,   487,   121,    90,
      91,   486,   125,   126,   486,   235,   486,   130,   238,   486,
     486,   486,   486,   486,   486,   106,   486,   486,   486,  3034,
     434,   486,   252,   437,   297,   486,   486,   118,   119,   486,
     121,  2027,   486,   486,   486,   486,   486,   160,   161,   486,
     270,   486,   486,   486,   274,   275,   486,   486,   486,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,   486,   486,   486,   486,   486,  2274,   486,   486,
     161,  2274,   356,   487,   488,   487,   279,   459,   487,   202,
     127,     6,     7,     8,   207,    10,   487,   487,    13,    14,
      15,    16,  2377,  2280,  2379,    22,   493,   177,   486,   479,
     487,    56,   179,  2138,   102,   228,   144,   181,   102,   232,
     488,   202,   296,   480,    45,   486,   207,   270,   241,   242,
     243,  1863,   181,  2681,  2682,   177,   249,    87,   285,   389,
     270,   274,    56,   329,   257,   260,   181,   383,   304,    36,
     277,   232,   274,   117,   488,  2430,   235,  2343,  2397,   224,
     241,   242,   243,   221,   137,   221,   487,   135,   141,   488,
     493,   284,  1904,  2459,   488,  1557,   257,  1559,  2059,   492,
    1562,   154,   488,   296,   402,   492,   102,   306,   488,   487,
    2215,   487,  1924,   480,   487,   144,   487,   487,   487,   493,
    1582,  1901,  1559,   284,   487,  1562,   487,   487,   486,   182,
     218,   488,  1594,   488,   487,   296,   487,   167,   487,   487,
    1602,   487,   487,  1605,   139,  1607,   487,   177,   487,   487,
     487,   487,   487,   487,   487,   487,   487,  1594,   487,   487,
     487,   214,   488,   163,   486,   218,   219,  1629,  1605,   493,
     493,   486,   493,    56,   488,   488,   167,  1639,  1640,   480,
     279,   389,  1650,    82,  1652,  1653,   216,    71,  1650,   382,
    1652,  1653,   245,   488,   274,    26,   226,   227,   486,   488,
     305,   280,  1639,  1640,   488,   488,    10,    38,    10,    10,
      41,   404,    10,    44,    10,    46,    10,   247,    10,    50,
      10,   382,    10,    10,    55,   418,   279,    10,    10,    10,
     283,    10,    63,    10,   290,   428,   488,    68,    69,   221,
     144,   294,   100,   404,   488,   244,   487,   379,    79,   405,
     219,  1713,    83,   219,  2833,  2834,  2835,   177,   219,   487,
     493,   487,   177,   493,   486,   144,  2332,   428,   321,   487,
      70,   486,   493,   493,   280,   148,   144,   493,   168,  1741,
     310,   493,  1744,   100,   112,   133,   276,   280,   170,   170,
     276,   133,   345,   346,   488,   488,   301,   350,    55,   488,
     486,   493,   328,   487,  1741,   328,   487,   138,   487,   487,
       3,   487,     5,   487,   465,   487,   459,   148,   487,   487,
     487,   487,  2677,   487,   487,   228,   488,   488,   358,   487,
     161,   218,   218,    26,    27,   488,   488,    30,   179,    32,
     486,  2153,    35,   307,   166,    38,   306,   144,    41,   488,
      43,    44,   229,    46,  2719,    48,    49,    50,   169,    52,
      53,   169,    55,   224,   480,   175,   109,    60,    61,    62,
     493,    64,    65,   426,    67,    68,    69,    70,   171,   486,
      73,   291,   486,    76,   486,   171,   480,    80,    81,   221,
      83,   279,   487,   219,   238,   487,   487,   487,   261,    92,
     219,   219,   487,   159,   167,   236,   492,    83,   169,   102,
     493,   187,  2767,   106,   107,   246,   487,   248,   407,   488,
     169,   144,  1884,   486,   486,   478,   479,   488,  2793,   122,
     123,   171,   487,   171,    88,   266,   487,   486,   329,   128,
     487,   487,   417,  2509,    47,   487,   476,   477,   478,   479,
     480,   481,   482,   483,   488,   148,   487,   166,   174,   487,
    2240,   491,   441,   151,   488,    10,   488,   298,   169,   229,
     169,   306,   244,   279,   279,   488,    68,   488,   486,   119,
    2546,   119,   371,   372,   373,   374,   375,   336,   486,   100,
     275,  1953,  1954,   152,   486,   111,   417,   169,   486,   486,
     219,   486,   486,   486,  2459,   279,   487,   487,   486,   398,
     399,   400,   401,   279,   279,   487,   487,  3096,   488,   219,
     354,   486,   219,   486,   413,   414,   415,   416,   486,  1991,
     419,   354,   486,   218,    83,  1997,  1998,   119,   171,   171,
      16,  2003,   219,  2005,   219,  2007,   219,   486,   219,   219,
     439,   440,  2014,   171,   137,   487,   249,   487,   141,   178,
     253,    87,   255,   486,   301,  2027,   301,   260,   224,  2037,
    2038,   154,   461,   462,   487,  2037,  2038,   302,  2040,   487,
     426,   487,   487,   219,  2046,   487,   487,  2049,  2050,    83,
     488,   487,  2054,  2055,   100,   100,   131,   100,   188,   182,
      34,   221,   219,   100,   434,   100,   486,   300,   486,   100,
    2078,   487,  2080,    10,  2076,   487,  2078,   488,  2080,   246,
    2082,    84,   487,   159,  2086,  2087,   488,  2993,  2994,  2655,
    2996,   214,   219,   486,    87,   218,   219,   178,   192,  2076,
    2906,   486,    10,  1759,   337,   338,  1732,   487,  2714,   487,
    2794,  2113,  2114,  1313,   332,   488,    90,    91,  3024,  2632,
    1709,  1287,   245,  2841,  3029,  2114,  2572,  1678,  2089,  1713,
    2044,   105,   106,  2563,  2570,   109,  2113,  2580,  3044,    26,
    3046,  3047,  2580,  2628,   118,   119,  2873,   121,  2736,  2779,
    2770,    38,  2566,  2322,    41,  3011,   279,    44,  3020,    46,
     283,  2865,  2961,    50,  2908,  2085,  2879,  2372,    55,  1943,
    1598,   294,  1317,  1627,  1639,  1222,    63,  1228,  2250,  1929,
     918,    68,    69,  1944,  2932,   546,   823,   161,  1572,   545,
    1974,  2942,    79,  2820,  1359,   594,    83,  3099,   321,    86,
    2674,  1949,   617,   436,   185,   186,   187,   188,   189,   190,
     191,  1764,   193,   194,   195,   196,   197,   198,   199,   200,
     585,   967,   345,   346,  1264,  3082,  2026,   350,   202,  2541,
    2540,  2714,  2509,   207,  3066,   544,   522,  1338,   935,  1170,
    2249,  2917,   577,  2926,  2986,  3000,  1322,  2771,  2250,  2546,
    1178,   138,  1644,   486,  2016,  2329,  2531,  2712,   232,  1562,
     539,   148,  1246,   906,  2831,  2267,  1252,   241,   242,   243,
    2307,  2836,  1331,  2250,   161,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   257,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2307,    -1,    -1,    -1,    -1,
     284,    -1,    -1,    -1,  2322,    -1,    -1,    -1,    -1,    -1,
    2322,    -1,   296,    -1,    -1,    -1,    -1,  2329,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,   317,    -1,  2665,   362,    -1,    -1,   236,
      -1,    -1,    -1,    -1,    -1,   478,   479,    -1,    -1,   246,
    2362,   248,    -1,   379,    -1,    -1,    -1,  2369,  2376,    -1,
      -1,    -1,    -1,    -1,  2376,    -1,    -1,    -1,  2984,   266,
      -1,    -1,  2877,    -1,  2879,    -1,    -1,   403,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2397,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,   382,  2411,
      -1,   298,  2414,    -1,    -1,    -1,  2418,   433,  2420,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     404,    -1,    -1,    -1,    -1,    -1,    -1,  2414,    -1,  2447,
      -1,    -1,    -1,  2420,    -1,  2447,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   428,    -1,    -1,    -1,    -1,    -1,
    3066,    -1,    -1,  2851,  2852,  2853,    -1,   483,   484,   485,
     486,   487,    -1,    -1,    -1,    -1,  3082,    -1,    -1,    -1,
      -1,  2887,  2490,    -1,    -1,    -1,    -1,   167,  2490,    -1,
      -1,    -1,    -1,    -1,    -1,  2497,    -1,   177,  2993,  2994,
      -1,  2996,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   488,    -1,    -1,    -1,    -1,  2521,
      -1,    -1,    -1,  2525,    -1,    -1,    -1,    -1,    -1,  3024,
      -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2546,    -1,   226,   227,    -1,  3044,
      -1,  3046,  3047,    -1,  2556,    -1,    -1,    -1,    -1,    -1,
      -1,  2563,    -1,   579,    -1,    -1,    -1,   247,  2974,    -1,
    2572,    -1,    -1,    -1,    -1,    -1,   592,    -1,    -1,   595,
      -1,    -1,    -1,    -1,    -1,   601,   602,    -1,   604,   605,
     606,   607,    -1,    -1,    -1,    -1,    -1,    -1,   614,   615,
     616,    -1,    -1,    -1,    -1,    -1,   622,    -1,   624,   625,
     626,    -1,    -1,    -1,   630,    -1,    -1,    -1,   634,    -1,
     636,    -1,   638,    -1,   640,    -1,    -1,    -1,    -1,    -1,
     310,   647,   648,    -1,   650,  2637,    -1,   653,   654,   655,
     656,   657,   658,   659,   660,   661,   662,    -1,   664,   665,
     666,   667,   668,   669,    -1,    -1,    -1,    -1,   674,   675,
      -1,   677,   678,   679,    -1,   681,   682,   683,   684,   685,
     686,   687,   688,   689,    -1,    -1,    -1,   693,   358,   695,
     696,   697,   698,   699,    -1,    -1,   702,   703,   704,   705,
     706,   707,   708,   709,   710,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   718,    -1,    -1,    -1,    -1,   723,   724,   725,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   733,    -1,    -1,
      -1,   737,    -1,   739,    -1,    -1,    -1,    -1,  2730,    -1,
      -1,   747,   748,   749,   750,    -1,    -1,    -1,   754,   755,
     756,   757,    -1,   759,   760,   761,   762,   763,   764,   765,
     766,   767,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2770,    -1,    -1,    -1,    -1,    -1,  2770,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,  2807,    -1,   487,   488,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,  2825,    -1,    -1,    -1,    -1,    -1,    -1,
    2807,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2848,  2849,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2862,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,  2908,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    44,    -1,
      46,    -1,    -1,    -1,    50,    -1,    34,    -1,   167,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,   177,    -1,
    2942,   167,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    87,    79,    -1,    -1,    -1,    83,    -1,    -1,
      86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   167,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   216,   177,    -1,
      -1,    -1,    90,    91,    -1,    -1,    -1,   226,   227,    -1,
     216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,
     226,   227,    -1,  3005,  3006,    -1,  3008,    -1,   247,    -1,
     118,   119,   138,   121,    -1,    -1,    -1,   216,    -1,  3021,
      -1,   247,   148,    -1,    -1,    -1,    -1,   226,   227,    -1,
      -1,    -1,   167,    -1,    -1,   161,    -1,    -1,  3040,    -1,
      -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,   247,    -1,
      -1,    -1,    -1,   161,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   301,    -1,    -1,    -1,    -1,  1083,  1084,  1085,
      -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    3082,   216,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,   226,   227,    -1,   202,    -1,    -1,    -1,  1114,   207,
      -1,    -1,  1118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     236,   310,   247,    -1,    -1,  1131,    -1,    -1,    -1,   358,
     246,    -1,   248,    -1,   232,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   358,   241,   242,   243,    -1,  1153,    -1,    -1,
     266,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   257,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,
      -1,    -1,  1178,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   298,    -1,    -1,   310,   284,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   296,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,
     479,   480,   481,   482,   483,    -1,    -1,    -1,    -1,   488,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
      -1,   487,   488,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   382,    -1,    -1,   476,   477,   478,
     479,   480,   481,   482,   483,    87,    -1,    -1,   487,   488,
      -1,    -1,    -1,    -1,    -1,    -1,   404,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1326,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     428,    -1,    -1,    -1,    -1,  1341,    -1,  1343,    -1,    -1,
      -1,  1347,    -1,    -1,    -1,    -1,    -1,  1353,  1354,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,  1365,
      -1,  1367,   487,   488,    -1,  1371,  1372,    -1,    -1,    -1,
      -1,    -1,    -1,  1379,    -1,   167,  1382,    -1,    -1,    -1,
      -1,  1387,    -1,    -1,  1390,   177,    -1,    -1,    -1,    -1,
      -1,  1397,    -1,  1399,    -1,    -1,    -1,  1403,  1404,  1405,
      -1,    -1,    -1,  1409,    -1,  1411,    -1,  1413,    -1,  1415,
      -1,    -1,    -1,  1419,    -1,  1421,    -1,  1423,    -1,  1425,
      -1,  1427,    -1,  1429,   216,    -1,    -1,    -1,  1434,    -1,
    1436,    -1,  1438,    -1,   226,   227,    -1,    -1,    -1,    -1,
    1446,  1447,    -1,  1449,    -1,  1451,  1452,    -1,    -1,  1455,
    1456,  1457,  1458,  1459,    -1,   247,  1462,  1463,  1464,  1465,
      -1,  1467,  1468,  1469,  1470,  1471,  1472,  1473,  1474,  1475,
      -1,  1477,  1478,    -1,  1480,    -1,  1482,  1483,  1484,  1485,
    1486,    -1,  1488,    -1,  1490,    -1,  1492,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1503,    -1,    -1,
    1506,  1507,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,   310,    -1,
      -1,    -1,  1528,  1529,    -1,    -1,  1532,  1533,  1534,  1535,
      -1,    -1,    -1,  1539,  1540,  1541,  1542,    -1,  1544,  1545,
    1546,  1547,  1548,  1549,  1550,  1551,  1552,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1565,
      -1,    -1,    -1,    -1,    -1,    -1,   358,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      87,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    87,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    87,
     167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     177,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,   481,
     482,   483,    -1,    -1,    -1,   487,   488,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   216,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,
     227,    -1,    -1,    -1,    87,   167,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,   167,
     247,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,   177,
      37,    38,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,    -1,  1770,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,   216,    -1,    -1,   167,    -1,    -1,
      -1,    -1,    -1,    70,   226,   227,    -1,   177,   216,    -1,
    1796,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,   227,
      -1,   216,    -1,   310,   167,   247,    93,    94,    -1,    -1,
      -1,   226,   227,    -1,   177,    -1,    -1,    -1,   105,   247,
      -1,    -1,    -1,   110,    -1,   112,   216,    -1,    -1,  1835,
     117,    -1,   247,    -1,    -1,    -1,   226,   227,    -1,  1845,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   358,    -1,   216,    -1,    -1,    -1,   247,   145,    -1,
     147,  1867,   149,   226,   227,    -1,    -1,  1873,   310,  1875,
      -1,  1877,    -1,    -1,   161,   162,    -1,    -1,   165,    -1,
      -1,    -1,   310,   170,   247,  1891,    -1,    -1,  1894,    -1,
      -1,    -1,   179,    -1,   181,   310,    -1,    -1,    -1,    -1,
    1906,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,
     310,    -1,    -1,    -1,    -1,   212,    -1,    -1,    -1,    -1,
     358,    -1,    -1,    -1,    -1,    -1,   223,    -1,    -1,    -1,
      -1,    -1,    -1,   358,    -1,    -1,    -1,   310,   235,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,   358,   476,
     477,   478,   479,   480,   481,   482,   483,   264,    -1,    -1,
     487,   488,    -1,   270,   271,    -1,    -1,   274,   275,    -1,
      -1,    -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2010,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   304,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   312,   313,    -1,  2034,    -1,
     317,    -1,    87,    -1,   476,   477,   478,   479,   480,   481,
     482,   483,    -1,    -1,    -1,   487,   488,    -1,   476,   477,
     478,   479,   480,   481,   482,   483,    -1,    -1,    -1,   487,
     488,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,    -1,   487,   488,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,   382,   383,   487,   488,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,   167,   476,   477,   478,   479,   480,   481,   482,
     483,    -1,   177,    -1,   487,   488,    -1,    -1,    -1,    -1,
      -1,  2137,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,  2158,    -1,    -1,    -1,    -1,  2163,  2164,    -1,
    2166,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2175,
      -1,   226,   227,    -1,    -1,    -1,    -1,    87,    -1,    -1,
      -1,  2187,    -1,    -1,    -1,  2191,    -1,    -1,  2194,    -1,
      -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2208,    -1,    -1,    -1,  2212,    -1,    -1,    -1,
      -1,  2217,    -1,    -1,  2220,  2221,    -1,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2245,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,   310,    -1,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,   167,    -1,    -1,
      -1,    -1,    -1,   358,    -1,    -1,   216,   177,    -1,    -1,
      -1,  2317,    -1,    -1,    -1,    -1,   226,   227,    87,    -1,
      -1,    -1,    -1,    -1,  2330,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,  2345,
      -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,
      -1,  2357,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,
      -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   167,    -1,
     310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,    -1,   487,   488,    -1,    -1,    -1,    -1,    -1,    -1,
     310,   167,    -1,    -1,    -1,    -1,    -1,   216,   358,    -1,
      -1,   177,    -1,    -1,    -1,    -1,    87,   226,   227,    -1,
    2466,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,  2480,    -1,    -1,    -1,   247,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,
     216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,   227,    -1,    -1,    -1,    -1,    -1,    -1,  2514,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   167,    -1,    -1,    87,
      -1,   310,    -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,    -1,    -1,   487,   488,    -1,
      -1,    -1,    -1,    -1,   310,   216,    -1,    -1,    -1,   358,
      -1,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,    -1,   247,   487,   488,   167,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,
      -1,    -1,   358,    -1,    -1,    -1,  2642,    -1,    -1,    -1,
      -1,    -1,    -1,  2649,    -1,    -1,  2652,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,
      -1,    -1,    -1,    -1,    -1,    -1,  2712,   476,   477,   478,
     479,   480,   481,   482,   483,    -1,  2722,    -1,   487,   488,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
      -1,   487,   488,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2808,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     358,    -1,    -1,    -1,    -1,  2821,    -1,  2823,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,
     481,   482,   483,    -1,    -1,    -1,   487,   488,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2914,    -1,
      -1,    -1,    -1,    -1,  2920,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,   477,
     478,   479,   480,   481,   482,   483,    -1,    -1,    -1,    -1,
      -1,    -1,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    28,    29,    30,    31,
      -1,    33,    34,    35,    36,    37,    -1,    -1,    40,    -1,
      -1,    43,  2988,    45,    46,    47,    48,    49,    50,    51,
      -1,    -1,    54,    -1,    56,    57,    58,    59,  3004,    -1,
      62,    63,    64,    65,    66,    67,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      82,    -1,    84,    85,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,    -1,   101,
     102,    -1,   104,   105,   106,    -1,   108,    -1,   110,    -1,
      -1,   113,    -1,   115,   116,    -1,   118,   119,    -1,   121,
      -1,    -1,   124,   125,   126,    -1,   128,   129,   130,    -1,
      -1,   133,   134,   135,   136,   137,   138,   139,   140,   141,
      -1,    -1,    -1,   145,    -1,   147,  3092,   149,   150,    -1,
      -1,   153,   154,    -1,   156,   157,   158,    -1,   160,    -1,
     162,    -1,    -1,   165,    -1,    -1,   168,    -1,    -1,    -1,
     172,   173,   174,   175,    -1,    -1,    -1,   179,   180,   181,
     182,    -1,    -1,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,    -1,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,    -1,
     222,   223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,
     232,   233,    -1,    -1,   236,   237,   238,   239,   240,   241,
     242,   243,    -1,   245,    -1,    -1,   248,    -1,   250,    -1,
     252,   253,    -1,    -1,   256,   257,   258,   259,    -1,    -1,
     262,   263,   264,   265,   266,    -1,    -1,    -1,   270,   271,
      -1,   273,    -1,    -1,   276,   277,    -1,   279,    -1,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,    -1,
     292,   293,   294,   295,    -1,    -1,    -1,   299,    -1,    -1,
     302,   303,   304,    -1,    -1,    -1,    -1,   309,    -1,   311,
     312,   313,   314,    -1,    -1,   317,   318,   319,   320,   321,
      -1,    -1,   324,   325,    -1,   327,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   337,   338,   339,    -1,   341,
      -1,   343,   344,   345,   346,    -1,    -1,    -1,   350,    -1,
      -1,    -1,    -1,    -1,   356,   357,    -1,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,    -1,
      -1,    -1,    -1,   375,   376,   377,   378,    -1,   380,   381,
     382,   383,   384,   385,   386,   387,   388,    -1,   390,   391,
     392,   393,   394,   395,   396,   397,    -1,    -1,    -1,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,    -1,    -1,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,    -1,   435,   436,   437,   438,   439,    -1,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,    -1,   460,    -1,
     462,   463,   464,   465,    -1,    -1,   468,    -1,   470,    -1,
     472,   473,   474,    -1,    -1,    -1,   478,   479,    -1,    -1,
      -1,    -1,   484,    -1,   486,    -1,    -1,   489,   490,    -1,
     492,   493,   494,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    -1,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    37,    -1,    -1,    40,
      -1,    -1,    43,    -1,    45,    46,    47,    48,    49,    50,
      51,    -1,    -1,    54,    -1,    56,    57,    58,    59,    -1,
      -1,    62,    63,    64,    65,    66,    67,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      -1,    82,    -1,    84,    85,    86,    -1,    -1,    -1,    90,
      91,    92,    93,    94,    95,    96,    97,    -1,    99,    -1,
     101,   102,    -1,   104,   105,   106,    -1,   108,    -1,   110,
      -1,    -1,   113,    -1,   115,   116,    -1,   118,   119,    -1,
     121,    -1,    -1,   124,   125,   126,    -1,   128,   129,   130,
      -1,    -1,   133,   134,   135,   136,   137,   138,   139,   140,
     141,    -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,
      -1,    -1,   153,   154,    -1,   156,   157,   158,    -1,   160,
      -1,   162,    -1,    -1,   165,    -1,    -1,   168,    -1,    -1,
      -1,    -1,   173,   174,   175,    -1,    -1,    -1,   179,   180,
     181,   182,    -1,    -1,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,    -1,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     231,   232,   233,    -1,    -1,   236,   237,   238,   239,   240,
     241,   242,   243,    -1,   245,    -1,    -1,   248,    -1,   250,
      -1,   252,   253,    -1,    -1,   256,   257,   258,   259,    -1,
      -1,   262,   263,   264,   265,   266,    -1,    -1,    -1,   270,
     271,    -1,   273,    -1,    -1,   276,   277,    -1,   279,    -1,
      -1,   282,   283,   284,   285,   286,   287,   288,   289,   290,
      -1,   292,   293,   294,   295,    -1,    -1,    -1,   299,    -1,
      -1,   302,   303,   304,    -1,    -1,    -1,    -1,   309,    -1,
     311,   312,   313,   314,    -1,    -1,   317,   318,   319,   320,
     321,    -1,    -1,   324,   325,    -1,   327,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   337,   338,   339,    -1,
     341,    -1,   343,   344,   345,   346,    -1,    -1,    -1,   350,
      -1,    -1,    -1,    -1,    -1,   356,   357,    -1,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
      -1,    -1,    -1,    -1,   375,   376,   377,   378,    -1,   380,
     381,   382,   383,   384,   385,   386,   387,   388,    -1,   390,
     391,   392,   393,   394,   395,   396,   397,    -1,    -1,    -1,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,    -1,    -1,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,    -1,   435,   436,   437,   438,   439,    -1,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,    -1,   460,
      -1,   462,   463,   464,   465,    -1,    -1,   468,    -1,   470,
      -1,   472,   473,   474,    -1,    -1,    -1,   478,   479,    -1,
      -1,    -1,    -1,   484,    -1,   486,    -1,    -1,   489,   490,
      -1,   492,   493,   494,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    28,    29,
      30,    31,    -1,    33,    34,    35,    36,    37,    -1,    -1,
      40,    -1,    -1,    43,    -1,    45,    46,    47,    48,    49,
      50,    51,    -1,    -1,    54,    -1,    56,    57,    58,    59,
      -1,    -1,    62,    63,    64,    65,    66,    67,    68,    -1,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    -1,    82,    -1,    84,    85,    -1,    -1,    -1,    -1,
      90,    91,    92,    93,    94,    95,    96,    97,    -1,    99,
      -1,   101,   102,    -1,   104,   105,   106,    -1,   108,    -1,
     110,    -1,    -1,   113,    -1,   115,   116,    -1,   118,   119,
      -1,   121,    -1,    -1,   124,   125,   126,    -1,   128,   129,
     130,    -1,    -1,   133,   134,   135,   136,   137,   138,   139,
     140,   141,    -1,    -1,    -1,   145,    -1,   147,    -1,   149,
     150,    -1,    -1,   153,   154,    -1,   156,   157,   158,    -1,
     160,    -1,   162,    -1,    -1,   165,    -1,    -1,   168,    -1,
      -1,    -1,    -1,   173,   174,   175,    -1,    -1,    -1,   179,
     180,   181,   182,    -1,    -1,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
      -1,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,    -1,   222,   223,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   231,   232,   233,    -1,    -1,   236,   237,   238,   239,
     240,   241,   242,   243,    -1,   245,    -1,    -1,   248,    -1,
     250,    -1,   252,   253,    -1,    -1,   256,   257,   258,   259,
      -1,    -1,   262,   263,   264,   265,   266,    -1,    -1,    -1,
     270,   271,    -1,   273,    -1,    -1,   276,   277,    -1,   279,
      -1,    -1,   282,   283,   284,   285,   286,   287,   288,   289,
     290,    -1,   292,   293,   294,   295,    -1,    -1,    -1,   299,
      -1,    -1,   302,   303,   304,    -1,    -1,    -1,    -1,   309,
      -1,   311,   312,   313,   314,    -1,    -1,   317,   318,   319,
     320,   321,    -1,    -1,   324,   325,    -1,   327,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   338,   339,
      -1,   341,    -1,   343,   344,   345,   346,    -1,    -1,    -1,
     350,    -1,    -1,    -1,    -1,    -1,   356,   357,    -1,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,    -1,    -1,    -1,    -1,   375,   376,   377,   378,    -1,
     380,   381,   382,   383,   384,   385,   386,   387,   388,    -1,
     390,   391,   392,   393,   394,   395,   396,   397,    -1,    -1,
      -1,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,    -1,    -1,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,    -1,   435,   436,   437,   438,   439,
      -1,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,    -1,
     460,    -1,   462,   463,   464,   465,    -1,    -1,   468,    -1,
     470,    -1,   472,   473,   474,    -1,    -1,    -1,   478,   479,
      -1,    -1,    -1,    -1,   484,    -1,   486,    -1,    -1,   489,
     490,    -1,   492,   493,   494,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    37,    -1,
      -1,    40,    -1,    -1,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    -1,    -1,    54,    -1,    56,    57,    58,
      59,    -1,    -1,    62,    63,    64,    65,    66,    67,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    82,    -1,    84,    85,    -1,    -1,    -1,
      -1,    90,    91,    92,    93,    94,    95,    96,    97,    -1,
      99,    -1,   101,   102,    -1,   104,   105,   106,    -1,   108,
      -1,   110,    -1,    -1,   113,    -1,   115,   116,    -1,   118,
     119,    -1,   121,    -1,    -1,   124,   125,   126,    -1,   128,
     129,   130,    -1,    -1,   133,   134,   135,   136,   137,   138,
     139,   140,   141,    -1,    -1,    -1,   145,    -1,   147,    -1,
     149,   150,    -1,    -1,   153,   154,    -1,   156,   157,   158,
      -1,   160,    -1,   162,    -1,    -1,   165,    -1,    -1,   168,
      -1,    -1,    -1,    -1,   173,   174,   175,    -1,    -1,    -1,
     179,   180,   181,   182,    -1,    -1,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,    -1,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,    -1,   222,   223,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   231,   232,   233,    -1,    -1,   236,   237,   238,
     239,   240,   241,   242,   243,    -1,   245,    -1,    -1,   248,
      -1,   250,    -1,   252,   253,    -1,    -1,   256,   257,   258,
     259,    -1,    -1,   262,   263,   264,   265,   266,    -1,    -1,
      -1,   270,   271,    -1,   273,    -1,    -1,   276,   277,    -1,
     279,    -1,    -1,   282,   283,   284,   285,   286,   287,   288,
     289,   290,    -1,   292,   293,   294,   295,    -1,    -1,    -1,
     299,    -1,    -1,   302,   303,   304,    -1,    -1,    -1,    -1,
     309,    -1,   311,   312,   313,   314,    -1,    -1,   317,   318,
     319,   320,   321,    -1,    -1,   324,   325,    -1,   327,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   338,
     339,    -1,   341,    -1,   343,   344,   345,   346,    -1,    -1,
      -1,   350,    -1,    -1,    -1,    -1,    -1,   356,   357,    -1,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,    -1,    -1,    -1,    -1,   375,   376,   377,   378,
      -1,   380,   381,   382,   383,   384,   385,   386,   387,   388,
      -1,   390,   391,   392,   393,   394,   395,   396,   397,    -1,
      -1,    -1,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,   413,    -1,    -1,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   432,   433,    -1,   435,   436,   437,   438,
     439,    -1,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
      -1,   460,    -1,   462,   463,   464,   465,    -1,    -1,   468,
      -1,   470,    -1,   472,   473,   474,    -1,    -1,    -1,   478,
     479,    -1,    -1,    -1,    -1,   484,    -1,   486,   487,    -1,
     489,   490,    -1,   492,   493,   494,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    37,
      -1,    -1,    40,    -1,    -1,    43,    -1,    45,    46,    47,
      48,    49,    50,    51,    -1,    -1,    54,    -1,    56,    57,
      58,    59,    -1,    -1,    62,    63,    64,    65,    66,    67,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    -1,    82,    -1,    84,    85,    -1,    -1,
      -1,    -1,    90,    91,    92,    93,    94,    95,    96,    97,
      -1,    99,    -1,   101,   102,    -1,   104,   105,   106,    -1,
     108,    -1,   110,    -1,    -1,   113,    -1,   115,   116,    -1,
     118,   119,    -1,   121,    -1,    -1,   124,   125,   126,    -1,
     128,   129,   130,    -1,    -1,   133,   134,   135,   136,   137,
     138,   139,   140,   141,    -1,    -1,    -1,   145,    -1,   147,
      -1,   149,   150,    -1,    -1,   153,   154,    -1,   156,   157,
     158,    -1,   160,    -1,   162,    -1,    -1,   165,    -1,    -1,
     168,    -1,    -1,    -1,    -1,   173,   174,   175,    -1,    -1,
      -1,   179,   180,   181,   182,    -1,    -1,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,    -1,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,    -1,   222,   223,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   231,   232,   233,    -1,    -1,   236,   237,
     238,   239,   240,   241,   242,   243,    -1,   245,    -1,    -1,
     248,    -1,   250,    -1,   252,   253,    -1,    -1,   256,   257,
     258,   259,    -1,    -1,   262,   263,   264,   265,   266,    -1,
      -1,    -1,   270,   271,    -1,   273,    -1,    -1,   276,   277,
      -1,   279,    -1,    -1,   282,   283,   284,   285,   286,   287,
     288,   289,   290,    -1,   292,   293,   294,   295,    -1,    -1,
      -1,   299,    -1,    -1,   302,   303,   304,    -1,    -1,    -1,
      -1,   309,    -1,   311,   312,   313,   314,    -1,    -1,   317,
     318,   319,   320,   321,    -1,    -1,   324,   325,    -1,   327,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,
     338,   339,    -1,   341,    -1,   343,   344,   345,   346,    -1,
      -1,    -1,   350,    -1,    -1,    -1,    -1,    -1,   356,   357,
      -1,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,   370,    -1,    -1,    -1,    -1,   375,   376,   377,
     378,    -1,   380,   381,   382,   383,   384,   385,   386,   387,
     388,    -1,   390,   391,   392,   393,   394,   395,   396,   397,
      -1,    -1,    -1,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,    -1,    -1,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,    -1,   435,   436,   437,
     438,   439,    -1,   441,   442,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,    -1,   460,    -1,   462,   463,   464,   465,    -1,    -1,
     468,    -1,   470,    -1,   472,   473,   474,    -1,    -1,    -1,
     478,   479,    -1,    -1,    -1,    -1,   484,    -1,   486,   487,
      -1,   489,   490,    -1,   492,   493,   494,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    28,    29,    30,    31,    -1,    33,    34,    35,    36,
      37,    -1,    -1,    40,    -1,    -1,    43,    -1,    45,    46,
      47,    48,    49,    50,    51,    -1,    -1,    54,    -1,    56,
      57,    58,    59,    -1,    -1,    62,    63,    64,    65,    66,
      67,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    -1,    82,    -1,    84,    85,    -1,
      -1,    -1,    -1,    90,    91,    92,    93,    94,    95,    96,
      97,    -1,    99,    -1,   101,   102,    -1,   104,   105,   106,
      -1,   108,    -1,   110,    -1,    -1,   113,    -1,   115,   116,
      -1,   118,   119,    -1,   121,    -1,    -1,   124,   125,   126,
      -1,   128,   129,   130,    -1,    -1,   133,   134,   135,   136,
     137,   138,   139,   140,   141,    -1,    -1,    -1,   145,    -1,
     147,    -1,   149,   150,    -1,    -1,   153,   154,    -1,   156,
     157,   158,    -1,   160,    -1,   162,    -1,    -1,   165,    -1,
      -1,   168,    -1,    -1,    -1,    -1,   173,   174,   175,    -1,
      -1,    -1,   179,   180,   181,   182,    -1,    -1,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,    -1,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,    -1,   222,   223,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   231,   232,   233,    -1,    -1,   236,
     237,   238,   239,   240,   241,   242,   243,    -1,   245,    -1,
      -1,   248,    -1,   250,    -1,   252,   253,    -1,    -1,   256,
     257,   258,   259,    -1,    -1,   262,   263,   264,   265,   266,
      -1,    -1,    -1,   270,   271,    -1,   273,    -1,    -1,   276,
     277,    -1,   279,    -1,    -1,   282,   283,   284,   285,   286,
     287,   288,   289,   290,    -1,   292,   293,   294,   295,    -1,
      -1,    -1,   299,    -1,    -1,   302,   303,   304,    -1,    -1,
      -1,    -1,   309,    -1,   311,   312,   313,   314,    -1,    -1,
     317,   318,   319,   320,   321,    -1,    -1,   324,   325,    -1,
     327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     337,   338,   339,    -1,   341,    -1,   343,   344,   345,   346,
      -1,    -1,    -1,   350,    -1,    -1,    -1,    -1,    -1,   356,
     357,    -1,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,    -1,    -1,    -1,    -1,   375,   376,
     377,   378,    -1,   380,   381,   382,   383,   384,   385,   386,
     387,   388,    -1,   390,   391,   392,   393,   394,   395,   396,
     397,    -1,    -1,    -1,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,    -1,    -1,   416,
     417,   418,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,    -1,   435,   436,
     437,   438,   439,    -1,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   458,    -1,   460,    -1,   462,   463,   464,   465,    -1,
      -1,   468,    -1,   470,    -1,   472,   473,   474,    -1,    -1,
      -1,   478,   479,    -1,    -1,    -1,    -1,   484,    -1,   486,
     487,    -1,   489,   490,    -1,   492,   493,   494,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    33,    34,    35,
      36,    37,    -1,    -1,    40,    -1,    -1,    43,    -1,    45,
      46,    47,    48,    49,    50,    51,    -1,    -1,    54,    -1,
      56,    57,    58,    59,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    -1,    82,    -1,    84,    85,
      -1,    -1,    -1,    -1,    90,    91,    92,    93,    94,    95,
      96,    97,    -1,    99,    -1,   101,   102,    -1,   104,   105,
     106,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,   115,
     116,    -1,   118,   119,    -1,   121,    -1,    -1,   124,   125,
     126,    -1,   128,   129,   130,    -1,    -1,   133,   134,   135,
     136,   137,   138,   139,   140,   141,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,   150,    -1,    -1,   153,   154,    -1,
     156,   157,   158,    -1,   160,    -1,   162,    -1,    -1,   165,
      -1,    -1,   168,    -1,    -1,    -1,    -1,   173,   174,   175,
      -1,    -1,    -1,   179,   180,   181,   182,    -1,    -1,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,    -1,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,    -1,   222,   223,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   231,   232,   233,    -1,    -1,
     236,   237,   238,   239,   240,   241,   242,   243,    -1,   245,
      -1,    -1,   248,    -1,   250,    -1,   252,   253,    -1,    -1,
     256,   257,   258,   259,    -1,    -1,   262,   263,   264,   265,
     266,    -1,    -1,    -1,   270,   271,    -1,   273,    -1,    -1,
     276,   277,    -1,   279,    -1,    -1,   282,   283,   284,   285,
     286,   287,   288,   289,   290,    -1,   292,   293,   294,   295,
      -1,    -1,    -1,   299,    -1,    -1,   302,   303,   304,    -1,
      -1,    -1,    -1,   309,    -1,   311,   312,   313,   314,    -1,
      -1,   317,   318,   319,   320,   321,    -1,    -1,   324,   325,
      -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   337,   338,   339,    -1,   341,    -1,   343,   344,   345,
     346,    -1,    -1,    -1,   350,    -1,    -1,    -1,    -1,    -1,
     356,   357,    -1,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,    -1,    -1,    -1,    -1,   375,
     376,   377,   378,    -1,   380,   381,   382,   383,   384,   385,
     386,   387,   388,    -1,   390,   391,   392,   393,   394,   395,
     396,   397,    -1,    -1,    -1,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,    -1,    -1,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,    -1,   435,
     436,   437,   438,   439,    -1,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,    -1,   460,    -1,   462,   463,   464,   465,
      -1,    -1,   468,    -1,   470,    -1,   472,   473,   474,    -1,
      -1,    -1,   478,   479,    -1,    -1,    -1,    -1,   484,    -1,
     486,   487,    -1,   489,   490,    -1,   492,   493,   494,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    28,    29,    30,    31,    -1,    33,    34,
      35,    36,    37,    -1,    -1,    40,    -1,    -1,    43,    -1,
      45,    46,    47,    48,    49,    50,    51,    -1,    -1,    54,
      -1,    56,    57,    58,    59,    -1,    -1,    62,    63,    64,
      65,    66,    67,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    82,    -1,    84,
      85,    86,    -1,    -1,    -1,    90,    91,    92,    93,    94,
      95,    96,    97,    -1,    99,    -1,   101,   102,    -1,   104,
     105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,
     115,   116,    -1,   118,   119,    -1,   121,    -1,    -1,   124,
     125,   126,    -1,   128,   129,   130,    -1,    -1,   133,   134,
     135,   136,   137,   138,   139,   140,   141,    -1,    -1,    -1,
     145,    -1,   147,    -1,   149,   150,    -1,    -1,   153,   154,
      -1,   156,   157,   158,    -1,   160,    -1,   162,    -1,    -1,
     165,    -1,    -1,   168,    -1,    -1,    -1,    -1,   173,   174,
     175,    -1,    -1,    -1,   179,   180,   181,   182,    -1,    -1,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,    -1,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,    -1,   222,   223,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   231,   232,   233,    -1,
      -1,   236,   237,   238,   239,   240,   241,   242,   243,    -1,
     245,    -1,    -1,   248,    -1,   250,    -1,   252,   253,    -1,
      -1,   256,   257,   258,   259,    -1,    -1,   262,   263,   264,
     265,   266,    -1,    -1,    -1,   270,   271,    -1,   273,    -1,
      -1,   276,   277,    -1,   279,    -1,    -1,   282,   283,   284,
     285,   286,   287,   288,   289,   290,    -1,   292,   293,   294,
     295,    -1,    -1,    -1,   299,    -1,    -1,   302,   303,   304,
      -1,    -1,    -1,    -1,   309,    -1,   311,   312,   313,   314,
      -1,    -1,   317,   318,   319,   320,   321,    -1,    -1,   324,
     325,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   337,   338,   339,    -1,   341,    -1,   343,   344,
     345,   346,    -1,    -1,    -1,   350,    -1,    -1,    -1,    -1,
      -1,   356,   357,    -1,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,    -1,    -1,    -1,    -1,
     375,   376,   377,   378,    -1,   380,   381,   382,   383,   384,
     385,   386,   387,   388,    -1,   390,   391,   392,   393,   394,
     395,   396,   397,    -1,    -1,    -1,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,    -1,
      -1,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,    -1,
     435,   436,   437,   438,   439,    -1,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,    -1,   460,    -1,   462,   463,   464,
     465,    -1,    -1,   468,    -1,   470,    -1,   472,   473,   474,
      -1,    -1,    -1,   478,   479,    -1,    -1,    -1,    -1,   484,
      -1,   486,    -1,    -1,   489,   490,    -1,   492,   493,   494,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    -1,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    37,    -1,    -1,    40,    -1,    -1,    43,
      -1,    45,    46,    47,    48,    49,    50,    51,    -1,    -1,
      54,    -1,    56,    57,    58,    59,    -1,    -1,    62,    63,
      64,    65,    66,    67,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    -1,    82,    -1,
      84,    85,    -1,    -1,    -1,    -1,    90,    91,    92,    93,
      94,    95,    96,    97,    -1,    99,    -1,   101,   102,    -1,
     104,   105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,
      -1,   115,   116,    -1,   118,   119,    -1,   121,    -1,    -1,
     124,   125,   126,    -1,   128,   129,   130,    -1,    -1,   133,
     134,   135,   136,   137,   138,   139,   140,   141,    -1,    -1,
     144,   145,    -1,   147,    -1,   149,   150,    -1,    -1,   153,
     154,    -1,   156,   157,   158,    -1,   160,    -1,   162,    -1,
      -1,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,   173,
     174,   175,    -1,    -1,    -1,   179,   180,   181,   182,    -1,
      -1,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,    -1,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,    -1,   222,   223,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,   232,   233,
      -1,    -1,   236,   237,   238,   239,   240,   241,   242,   243,
      -1,   245,    -1,    -1,   248,    -1,   250,    -1,   252,   253,
      -1,    -1,   256,   257,   258,   259,    -1,    -1,   262,   263,
     264,   265,   266,    -1,    -1,    -1,   270,   271,    -1,   273,
      -1,    -1,   276,   277,    -1,   279,    -1,    -1,   282,   283,
     284,   285,   286,   287,   288,   289,   290,    -1,   292,   293,
     294,   295,    -1,    -1,    -1,   299,    -1,    -1,   302,   303,
     304,    -1,    -1,    -1,    -1,   309,    -1,   311,   312,   313,
     314,    -1,    -1,   317,   318,   319,   320,   321,    -1,    -1,
     324,   325,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   337,   338,   339,    -1,   341,    -1,   343,
     344,   345,   346,    -1,    -1,    -1,   350,    -1,    -1,    -1,
      -1,    -1,   356,   357,    -1,   359,   360,   361,   362,   363,
     364,   365,   366,   367,   368,   369,   370,    -1,    -1,    -1,
      -1,   375,   376,   377,   378,    -1,   380,   381,   382,   383,
     384,   385,   386,   387,   388,    -1,   390,   391,   392,   393,
     394,   395,   396,   397,    -1,    -1,    -1,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
      -1,    -1,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
      -1,   435,   436,   437,   438,   439,    -1,   441,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,    -1,   460,    -1,   462,   463,
     464,   465,    -1,    -1,   468,    -1,   470,    -1,   472,   473,
     474,    -1,    -1,    -1,   478,   479,    -1,    -1,    -1,    -1,
     484,    -1,   486,    -1,    -1,   489,   490,    -1,   492,   493,
     494,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    37,    -1,    -1,    40,    -1,    -1,
      43,    -1,    45,    46,    47,    48,    49,    50,    51,    -1,
      -1,    54,    -1,    56,    57,    58,    59,    -1,    -1,    62,
      63,    64,    65,    66,    67,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    82,
      -1,    84,    85,    -1,    -1,    -1,    -1,    90,    91,    92,
      93,    94,    95,    96,    97,    -1,    99,    -1,   101,   102,
      -1,   104,   105,   106,    -1,   108,    -1,   110,    -1,    -1,
     113,    -1,   115,   116,    -1,   118,   119,    -1,   121,    -1,
      -1,   124,   125,   126,    -1,   128,   129,   130,    -1,    -1,
     133,   134,   135,   136,   137,   138,   139,   140,   141,    -1,
      -1,   144,   145,    -1,   147,    -1,   149,   150,    -1,    -1,
     153,   154,    -1,   156,   157,   158,    -1,   160,    -1,   162,
      -1,    -1,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,
     173,   174,   175,    -1,    -1,    -1,   179,   180,   181,   182,
      -1,    -1,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,    -1,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,    -1,   222,
     223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,   232,
     233,    -1,    -1,   236,   237,   238,   239,   240,   241,   242,
     243,    -1,   245,    -1,    -1,   248,    -1,   250,    -1,   252,
     253,    -1,    -1,   256,   257,   258,   259,    -1,    -1,   262,
     263,   264,   265,   266,    -1,    -1,    -1,   270,   271,    -1,
     273,    -1,    -1,   276,   277,    -1,   279,    -1,    -1,   282,
     283,   284,   285,   286,   287,   288,   289,   290,    -1,   292,
     293,   294,   295,    -1,    -1,    -1,   299,    -1,    -1,   302,
     303,   304,    -1,    -1,    -1,    -1,   309,    -1,   311,   312,
     313,   314,    -1,    -1,   317,   318,   319,   320,   321,    -1,
      -1,   324,   325,    -1,   327,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   337,   338,   339,    -1,   341,    -1,
     343,   344,   345,   346,    -1,    -1,    -1,   350,    -1,    -1,
      -1,    -1,    -1,   356,   357,    -1,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,    -1,    -1,
      -1,    -1,   375,   376,   377,   378,    -1,   380,   381,   382,
     383,   384,   385,   386,   387,   388,    -1,   390,   391,   392,
     393,   394,   395,   396,   397,    -1,    -1,    -1,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,    -1,    -1,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,    -1,   435,   436,   437,   438,   439,    -1,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,    -1,   460,    -1,   462,
     463,   464,   465,    -1,    -1,   468,    -1,   470,    -1,   472,
     473,   474,    -1,    -1,    -1,   478,   479,    -1,    -1,    -1,
      -1,   484,    -1,   486,    -1,    -1,   489,   490,    -1,   492,
     493,   494,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    28,    29,    30,    31,
      -1,    33,    34,    35,    36,    37,    -1,    -1,    40,    -1,
      -1,    43,    -1,    45,    46,    47,    48,    49,    50,    51,
      -1,    -1,    54,    -1,    56,    57,    58,    59,    -1,    -1,
      62,    63,    64,    65,    66,    67,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      82,    -1,    84,    85,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    94,    95,    96,    97,    -1,    99,    -1,   101,
     102,    -1,   104,   105,   106,    -1,   108,    -1,   110,    -1,
      -1,   113,    -1,   115,   116,    -1,   118,   119,    -1,   121,
      -1,    -1,   124,   125,   126,    -1,   128,   129,   130,    -1,
      -1,   133,   134,   135,   136,   137,   138,   139,   140,   141,
      -1,    -1,   144,   145,    -1,   147,    -1,   149,   150,    -1,
      -1,   153,   154,    -1,   156,   157,   158,    -1,   160,    -1,
     162,    -1,    -1,   165,    -1,    -1,   168,    -1,    -1,    -1,
      -1,   173,   174,   175,    -1,    -1,    -1,   179,   180,   181,
     182,    -1,    -1,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,    -1,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,    -1,
     222,   223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,
     232,   233,    -1,    -1,   236,   237,   238,   239,   240,   241,
     242,   243,    -1,   245,    -1,    -1,   248,    -1,   250,    -1,
     252,   253,    -1,    -1,   256,   257,   258,   259,    -1,    -1,
     262,   263,   264,   265,   266,    -1,    -1,    -1,   270,   271,
      -1,   273,    -1,    -1,   276,   277,    -1,   279,    -1,    -1,
     282,   283,   284,   285,   286,   287,   288,   289,   290,    -1,
     292,   293,   294,   295,    -1,    -1,    -1,   299,    -1,    -1,
     302,   303,   304,    -1,    -1,    -1,    -1,   309,    -1,   311,
     312,   313,   314,    -1,    -1,   317,   318,   319,   320,   321,
      -1,    -1,   324,   325,    -1,   327,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   337,   338,   339,    -1,   341,
      -1,   343,   344,   345,   346,    -1,    -1,    -1,   350,    -1,
      -1,    -1,    -1,    -1,   356,   357,    -1,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,    -1,
      -1,    -1,    -1,   375,   376,   377,   378,    -1,   380,   381,
     382,   383,   384,   385,   386,   387,   388,    -1,   390,   391,
     392,   393,   394,   395,   396,   397,    -1,    -1,    -1,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,    -1,    -1,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,    -1,   435,   436,   437,   438,   439,    -1,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,    -1,   460,    -1,
     462,   463,   464,   465,    -1,    -1,   468,    -1,   470,    -1,
     472,   473,   474,    -1,    -1,    -1,   478,   479,    -1,    -1,
      -1,    -1,   484,    -1,   486,    -1,    -1,   489,   490,    -1,
     492,   493,   494,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    -1,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    37,    -1,    -1,    40,
      -1,    -1,    43,    -1,    45,    46,    47,    48,    49,    50,
      51,    -1,    -1,    54,    -1,    56,    57,    58,    59,    -1,
      -1,    62,    63,    64,    65,    66,    67,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      -1,    82,    -1,    84,    85,    -1,    -1,    -1,    -1,    90,
      91,    92,    93,    94,    95,    96,    97,    -1,    99,    -1,
     101,   102,    -1,   104,   105,   106,    -1,   108,    -1,   110,
      -1,    -1,   113,    -1,   115,   116,    -1,   118,   119,    -1,
     121,    -1,    -1,   124,   125,   126,    -1,   128,   129,   130,
      -1,    -1,   133,   134,   135,   136,   137,   138,   139,   140,
     141,    -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,
      -1,    -1,   153,   154,    -1,   156,   157,   158,    -1,   160,
      -1,   162,    -1,    -1,   165,    -1,    -1,   168,    -1,    -1,
      -1,    -1,   173,   174,   175,    -1,    -1,    -1,   179,   180,
     181,   182,    -1,    -1,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,    -1,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
      -1,   222,   223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     231,   232,   233,    -1,    -1,   236,   237,   238,   239,   240,
     241,   242,   243,    -1,   245,    -1,    -1,   248,    -1,   250,
      -1,   252,   253,    -1,    -1,   256,   257,   258,   259,    -1,
      -1,   262,   263,   264,   265,   266,    -1,    -1,    -1,   270,
     271,    -1,   273,    -1,    -1,   276,   277,    -1,   279,    -1,
      -1,   282,   283,   284,   285,   286,   287,   288,   289,   290,
      -1,   292,   293,   294,   295,    -1,    -1,    -1,   299,    -1,
      -1,   302,   303,   304,    -1,    -1,    -1,    -1,   309,    -1,
     311,   312,   313,   314,    -1,    -1,   317,   318,   319,   320,
     321,    -1,    -1,   324,   325,    -1,   327,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   337,   338,   339,    -1,
     341,    -1,   343,   344,   345,   346,    -1,    -1,    -1,   350,
      -1,    -1,    -1,    -1,    -1,   356,   357,    -1,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
      -1,    -1,    -1,    -1,   375,   376,   377,   378,    -1,   380,
     381,   382,   383,   384,   385,   386,   387,   388,    -1,   390,
     391,   392,   393,   394,   395,   396,   397,    -1,    -1,    -1,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,    -1,    -1,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,    -1,   435,   436,   437,   438,   439,    -1,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,    -1,   460,
      -1,   462,   463,   464,   465,    -1,    -1,   468,    -1,   470,
      -1,   472,   473,   474,    -1,    -1,    -1,   478,   479,    -1,
      -1,    -1,    -1,   484,    -1,   486,    -1,    -1,   489,   490,
      -1,   492,   493,   494,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    28,    29,
      30,    31,    -1,    33,    34,    35,    36,    37,    -1,    -1,
      40,    -1,    -1,    43,    -1,    45,    46,    47,    48,    49,
      50,    51,    -1,    -1,    54,    -1,    56,    57,    58,    59,
      -1,    -1,    62,    63,    64,    65,    66,    67,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    -1,    82,    -1,    84,    85,    -1,    -1,    -1,    -1,
      90,    91,    92,    93,    94,    95,    96,    97,    -1,    99,
      -1,   101,   102,    -1,   104,   105,   106,    -1,   108,    -1,
     110,    -1,    -1,   113,    -1,   115,   116,    -1,   118,   119,
      -1,   121,    -1,    -1,   124,   125,   126,    -1,   128,   129,
     130,    -1,    -1,   133,   134,   135,   136,   137,   138,   139,
     140,   141,    -1,    -1,    -1,   145,    -1,   147,    -1,   149,
     150,    -1,    -1,   153,   154,    -1,   156,   157,   158,    -1,
     160,    -1,   162,    -1,    -1,   165,    -1,    -1,   168,    -1,
      -1,    -1,    -1,   173,   174,   175,    -1,    -1,    -1,   179,
     180,   181,   182,    -1,    -1,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
      -1,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,    -1,   222,   223,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   231,   232,   233,    -1,    -1,   236,   237,   238,   239,
     240,   241,   242,   243,    -1,   245,    -1,    -1,   248,    -1,
     250,    -1,   252,   253,    -1,    -1,   256,   257,   258,   259,
      -1,    -1,   262,   263,   264,   265,   266,    -1,    -1,    -1,
     270,   271,    -1,   273,    -1,    -1,   276,   277,    -1,   279,
      -1,    -1,   282,   283,   284,   285,   286,   287,   288,   289,
     290,    -1,   292,   293,   294,   295,    -1,    -1,    -1,   299,
      -1,    -1,   302,   303,   304,    -1,    -1,    -1,    -1,   309,
      -1,   311,   312,   313,   314,    -1,    -1,   317,   318,   319,
     320,   321,    -1,    -1,   324,   325,    -1,   327,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   338,   339,
      -1,   341,    -1,   343,   344,   345,   346,    -1,    -1,    -1,
     350,    -1,    -1,    -1,    -1,    -1,   356,   357,    -1,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,    -1,    -1,    -1,    -1,   375,   376,   377,   378,    -1,
     380,   381,   382,   383,   384,   385,   386,   387,   388,    -1,
     390,   391,   392,   393,   394,   395,   396,   397,    -1,    -1,
      -1,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,    -1,    -1,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,    -1,   435,   436,   437,   438,   439,
      -1,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,    -1,
     460,    -1,   462,   463,   464,   465,    -1,    -1,   468,    -1,
     470,    -1,   472,   473,   474,    -1,    -1,    -1,   478,   479,
      -1,    -1,    -1,    -1,   484,    -1,   486,    -1,    -1,   489,
     490,    -1,   492,   493,   494,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    37,    -1,
      -1,    40,    -1,    -1,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    -1,    -1,    54,    -1,    56,    57,    58,
      59,    -1,    -1,    62,    63,    64,    65,    66,    67,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    82,    -1,    84,    85,    -1,    -1,    -1,
      -1,    90,    91,    92,    93,    94,    95,    96,    97,    -1,
      99,    -1,   101,   102,    -1,   104,   105,   106,    -1,   108,
      -1,   110,    -1,    -1,   113,    -1,   115,   116,    -1,   118,
     119,    -1,   121,    -1,    -1,   124,   125,   126,    -1,   128,
     129,   130,    -1,    -1,   133,   134,   135,   136,   137,   138,
     139,   140,   141,    -1,    -1,    -1,   145,    -1,   147,    -1,
     149,   150,    -1,    -1,   153,   154,    -1,   156,   157,   158,
      -1,   160,    -1,   162,    -1,    -1,   165,    -1,    -1,   168,
      -1,    -1,    -1,    -1,   173,   174,   175,    -1,    -1,    -1,
     179,   180,   181,   182,    -1,    -1,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,    -1,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,    -1,   222,   223,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   231,   232,   233,    -1,    -1,   236,   237,   238,
     239,   240,   241,   242,   243,    -1,   245,    -1,    -1,   248,
      -1,   250,    -1,   252,   253,    -1,    -1,   256,   257,   258,
     259,    -1,    -1,   262,   263,   264,   265,   266,    -1,    -1,
      -1,   270,   271,    -1,   273,    -1,    -1,   276,   277,    -1,
     279,    -1,    -1,   282,   283,   284,   285,   286,   287,   288,
     289,   290,    -1,   292,   293,   294,   295,    -1,    -1,    -1,
     299,    -1,    -1,   302,   303,   304,    -1,    -1,    -1,    -1,
     309,    -1,   311,   312,   313,   314,    -1,    -1,   317,   318,
     319,   320,   321,    -1,    -1,   324,   325,    -1,   327,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   338,
     339,    -1,   341,    -1,   343,   344,   345,   346,    -1,    -1,
      -1,   350,    -1,    -1,    -1,    -1,    -1,   356,   357,    -1,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,    -1,    -1,    -1,    -1,   375,   376,   377,   378,
      -1,   380,   381,   382,   383,   384,   385,   386,   387,   388,
      -1,   390,   391,   392,   393,   394,   395,   396,   397,    -1,
      -1,    -1,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,   413,    -1,    -1,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   432,   433,    -1,   435,   436,   437,   438,
     439,    -1,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
      -1,   460,    -1,   462,   463,   464,   465,    -1,    -1,   468,
      -1,   470,    -1,   472,   473,   474,    -1,    -1,    -1,   478,
     479,    -1,    -1,    -1,    -1,   484,    -1,   486,    -1,    -1,
     489,   490,    -1,   492,   493,   494,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    37,
      -1,    -1,    40,    -1,    -1,    43,    -1,    45,    46,    47,
      48,    49,    50,    51,    -1,    -1,    54,    -1,    56,    57,
      58,    59,    -1,    -1,    62,    63,    64,    65,    66,    67,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    -1,    82,    -1,    84,    85,    -1,    -1,
      -1,    -1,    90,    91,    92,    93,    94,    95,    96,    97,
      -1,    99,    -1,   101,   102,    -1,   104,   105,   106,    -1,
     108,    -1,   110,    -1,    -1,   113,    -1,   115,   116,    -1,
     118,   119,    -1,   121,    -1,    -1,   124,   125,   126,    -1,
     128,   129,   130,    -1,    -1,   133,   134,   135,   136,   137,
     138,   139,   140,   141,    -1,    -1,    -1,   145,    -1,   147,
      -1,   149,   150,    -1,    -1,   153,   154,    -1,   156,   157,
     158,    -1,   160,    -1,   162,    -1,    -1,   165,    -1,    -1,
     168,    -1,    -1,    -1,    -1,   173,   174,   175,    -1,    -1,
      -1,   179,   180,   181,   182,    -1,    -1,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,    -1,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,    -1,   222,   223,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   231,   232,   233,    -1,    -1,   236,   237,
     238,   239,   240,   241,   242,   243,    -1,   245,    -1,    -1,
     248,    -1,   250,    -1,   252,   253,    -1,    -1,   256,   257,
     258,   259,    -1,    -1,   262,   263,   264,   265,   266,    -1,
      -1,    -1,   270,   271,    -1,   273,    -1,    -1,   276,   277,
      -1,   279,    -1,    -1,   282,   283,   284,   285,   286,   287,
     288,   289,   290,    -1,   292,   293,   294,   295,    -1,    -1,
      -1,   299,    -1,    -1,   302,   303,   304,    -1,    -1,    -1,
      -1,   309,    -1,   311,   312,   313,   314,    -1,    -1,   317,
     318,   319,   320,   321,    -1,    -1,   324,   325,    -1,   327,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,
     338,   339,    -1,   341,    -1,   343,   344,   345,   346,    -1,
      -1,    -1,   350,    -1,    -1,    -1,    -1,    -1,   356,   357,
      -1,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,   370,    -1,    -1,    -1,    -1,   375,   376,   377,
     378,    -1,   380,   381,   382,   383,   384,   385,   386,   387,
     388,    -1,   390,   391,   392,   393,   394,   395,   396,   397,
      -1,    -1,    -1,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,    -1,    -1,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,    -1,   435,   436,   437,
     438,   439,    -1,   441,   442,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,    -1,   460,    -1,   462,   463,   464,   465,    -1,    -1,
     468,    -1,   470,    -1,   472,   473,   474,    -1,    -1,    -1,
     478,   479,    -1,    -1,    -1,    -1,   484,    -1,   486,    -1,
      -1,   489,   490,    -1,   492,   493,   494,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    28,    29,    30,    31,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    45,    46,
      47,    48,    49,    -1,    51,    -1,    -1,    54,    -1,    56,
      -1,    -1,    59,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    -1,    70,    71,    72,    73,    -1,    -1,    76,
      -1,    78,    79,    80,    -1,    82,    -1,    84,    85,    -1,
      -1,    -1,    -1,    90,    91,    92,    93,    -1,    95,    96,
      97,    -1,    99,    -1,   101,   102,    -1,    -1,   105,   106,
      -1,   108,    -1,   110,    -1,    -1,   113,   114,    -1,    -1,
      -1,   118,    -1,    -1,   121,    -1,    -1,   124,   125,   126,
      -1,   128,   129,   130,    -1,    -1,   133,   134,    -1,   136,
      -1,   138,   139,   140,    -1,    -1,    -1,    -1,   145,   146,
     147,    -1,   149,    -1,    -1,    -1,   153,    -1,    -1,   156,
     157,   158,    -1,   160,   161,   162,    -1,    -1,   165,    -1,
      -1,   168,    -1,    -1,   171,    -1,    -1,   174,   175,    -1,
     177,    -1,   179,    -1,   181,    -1,    -1,    -1,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,    -1,   202,   203,   204,   205,   206,
     207,   208,   209,    -1,   211,   212,   213,    -1,   215,    -1,
     217,    -1,    -1,   220,    -1,   222,   223,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   231,   232,   233,    -1,    -1,   236,
     237,   238,   239,   240,   241,   242,   243,    -1,    -1,    -1,
      -1,   248,    -1,   250,    -1,   252,   253,    -1,    -1,   256,
     257,   258,   259,    -1,    -1,   262,   263,   264,   265,   266,
     267,    -1,    -1,   270,   271,    -1,   273,    -1,    -1,   276,
     277,    -1,    -1,    -1,    -1,   282,    -1,   284,   285,    -1,
      -1,    -1,    -1,   290,    -1,   292,   293,    -1,   295,    -1,
      -1,    -1,   299,    -1,    -1,   302,    -1,   304,    -1,    -1,
      -1,    -1,   309,    -1,   311,   312,   313,   314,    -1,    -1,
      -1,   318,    -1,   320,   321,    -1,    -1,   324,   325,    -1,
     327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     337,   338,   339,    -1,   341,    -1,   343,   344,   345,   346,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,
      -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,    -1,
     397,    -1,    -1,    -1,   401,   402,    -1,   404,    -1,    -1,
      -1,    -1,   409,    -1,    -1,    -1,   413,    -1,    -1,   416,
     417,   418,   419,    -1,    -1,    -1,   423,   424,   425,    -1,
     427,   428,    -1,   430,    -1,   432,    -1,    -1,    -1,    -1,
      -1,    -1,   439,    -1,   441,   442,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,     4,     5,
       6,     7,     8,   460,    -1,   462,    12,    -1,   465,    -1,
      -1,   468,    -1,   470,    -1,   472,   473,   474,    -1,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    33,    34,    35,
      36,    -1,    -1,    -1,    40,    -1,   493,    43,    -1,    45,
      46,    47,    48,    49,    -1,    51,    -1,    -1,    54,    -1,
      56,    -1,    -1,    59,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    -1,    70,    71,    72,    73,    -1,    -1,
      76,    -1,    78,    79,    80,    -1,    82,    -1,    84,    85,
      -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,    95,
      96,    97,    -1,    99,    -1,   101,   102,    -1,    -1,   105,
     106,    -1,   108,    -1,   110,    -1,    -1,   113,   114,    -1,
      -1,    -1,   118,    -1,    -1,   121,    -1,    -1,   124,   125,
     126,    -1,   128,   129,   130,    -1,    -1,   133,   134,    -1,
     136,    -1,   138,   139,   140,    -1,    -1,    -1,    -1,   145,
     146,   147,    -1,   149,    -1,    -1,    -1,   153,    -1,    -1,
     156,   157,   158,    -1,   160,   161,   162,    -1,    -1,   165,
      -1,    -1,   168,    -1,    -1,   171,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,    -1,   181,    -1,    -1,    -1,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,    -1,   202,   203,   204,   205,
     206,   207,   208,   209,    -1,   211,   212,   213,    -1,   215,
      -1,   217,    -1,    -1,   220,    -1,   222,   223,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   231,   232,   233,    -1,    -1,
     236,   237,   238,   239,   240,   241,   242,   243,    -1,    -1,
      -1,    -1,   248,    -1,   250,    -1,   252,   253,    -1,    -1,
     256,   257,   258,   259,    -1,    -1,   262,   263,   264,   265,
     266,   267,    -1,    -1,   270,   271,    -1,   273,    -1,    -1,
     276,   277,    -1,    -1,    -1,    -1,   282,    -1,   284,   285,
      -1,    -1,    -1,    -1,   290,    -1,   292,   293,    -1,   295,
      -1,    -1,    -1,   299,    -1,    -1,   302,    -1,   304,    -1,
      -1,    -1,    -1,   309,    -1,   311,   312,   313,   314,    -1,
      -1,    -1,   318,    -1,   320,   321,    -1,    -1,   324,   325,
      -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   337,   338,   339,    -1,   341,    -1,   343,   344,   345,
     346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,
      -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,
      -1,   397,    -1,    -1,    -1,   401,   402,    -1,   404,    -1,
      -1,    -1,    -1,   409,    -1,    -1,    -1,   413,    -1,    -1,
     416,   417,   418,   419,    -1,    -1,    -1,   423,   424,   425,
      -1,   427,   428,    -1,   430,    -1,   432,    -1,    -1,    -1,
      -1,    -1,    -1,   439,    -1,   441,   442,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,     4,
       5,     6,     7,     8,   460,    -1,   462,    12,    -1,   465,
      -1,    -1,   468,    -1,   470,    -1,   472,   473,   474,    -1,
      25,    -1,    -1,    28,    29,    30,    31,    -1,    33,    34,
      35,    36,    -1,    -1,    -1,    40,    -1,   493,    43,    -1,
      45,    46,    47,    48,    49,    -1,    51,    -1,    -1,    54,
      -1,    56,    -1,    -1,    59,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    -1,    70,    71,    72,    73,    -1,
      -1,    76,    -1,    78,    79,    80,    -1,    82,    -1,    84,
      85,    -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,
      95,    96,    97,    -1,    99,    -1,   101,   102,    -1,    -1,
     105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,
      -1,    -1,    -1,   118,    -1,    -1,   121,    -1,    -1,   124,
     125,   126,    -1,   128,   129,   130,    -1,    -1,   133,   134,
      -1,   136,    -1,   138,   139,   140,    -1,    -1,    -1,    -1,
     145,    -1,   147,    -1,   149,    -1,    -1,    -1,   153,    -1,
      -1,   156,   157,   158,    -1,   160,    -1,   162,    -1,    -1,
     165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,   174,
     175,    -1,    -1,    -1,   179,    -1,   181,    -1,    -1,    -1,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,    -1,   202,   203,   204,
     205,   206,   207,   208,   209,    -1,   211,   212,   213,    -1,
     215,    -1,   217,    -1,    -1,   220,    -1,   222,   223,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   231,   232,   233,    -1,
      -1,   236,   237,   238,   239,   240,   241,   242,   243,    -1,
      -1,    -1,    -1,   248,    -1,   250,    -1,   252,   253,    -1,
      -1,   256,   257,   258,   259,    -1,    -1,   262,   263,   264,
     265,   266,    -1,    -1,    -1,   270,   271,    -1,   273,    -1,
      -1,   276,   277,    -1,    -1,    -1,    -1,   282,    -1,   284,
     285,    -1,    -1,    -1,    -1,   290,    -1,   292,   293,    -1,
     295,    -1,    -1,    -1,   299,    -1,    -1,   302,    -1,   304,
      -1,    -1,    -1,    -1,   309,    -1,   311,   312,   313,   314,
      -1,    -1,    -1,   318,    -1,   320,   321,    -1,    -1,   324,
     325,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   337,   338,   339,    -1,   341,    -1,   343,   344,
     345,   346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     375,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,
      -1,    -1,   397,    -1,    -1,    -1,   401,   402,    -1,   404,
      -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,   413,    -1,
      -1,   416,   417,   418,   419,    -1,    -1,    -1,   423,   424,
     425,    -1,   427,   428,    -1,   430,    -1,   432,    -1,    -1,
      -1,    -1,    -1,    -1,   439,    -1,   441,   442,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,
      -1,    -1,    -1,    -1,    -1,   460,    -1,   462,    -1,    -1,
     465,    -1,    -1,   468,    -1,   470,    -1,   472,   473,   474,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,
      -1,    -1,   487,    -1,    -1,    -1,    -1,    -1,   493,    -1,
      -1,    25,    -1,    -1,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,    43,
      -1,    45,    46,    47,    48,    49,    -1,    51,    -1,    -1,
      54,    -1,    56,    -1,    -1,    59,    -1,    -1,    62,    63,
      64,    65,    66,    67,    -1,    -1,    70,    71,    72,    73,
      -1,    -1,    76,    -1,    78,    79,    80,    -1,    82,    -1,
      84,    85,    -1,    -1,    -1,    -1,    90,    91,    92,    93,
      -1,    95,    96,    97,    -1,    99,    -1,   101,   102,    -1,
      -1,   105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,
      -1,    -1,    -1,    -1,   118,    -1,    -1,   121,    -1,    -1,
     124,   125,   126,    -1,   128,   129,   130,    -1,    -1,   133,
     134,    -1,   136,    -1,   138,   139,   140,    -1,    -1,    -1,
      -1,   145,    -1,   147,    -1,   149,    -1,    -1,    -1,   153,
      -1,    -1,   156,   157,   158,    -1,   160,    -1,   162,    -1,
      -1,   165,   166,    -1,   168,    -1,    -1,    -1,    -1,    -1,
     174,   175,    -1,    -1,    -1,   179,    -1,   181,    -1,    -1,
      -1,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,    -1,   202,   203,
     204,   205,   206,   207,   208,   209,    -1,   211,   212,   213,
      -1,   215,    -1,   217,    -1,    -1,   220,    -1,   222,   223,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,   232,   233,
      -1,    -1,   236,   237,   238,   239,   240,   241,   242,   243,
      -1,    -1,    -1,    -1,   248,    -1,   250,    -1,   252,   253,
      -1,    -1,   256,   257,   258,   259,    -1,    -1,   262,   263,
     264,   265,   266,    -1,    -1,    -1,   270,   271,    -1,   273,
      -1,    -1,   276,   277,    -1,    -1,    -1,    -1,   282,    -1,
     284,   285,    -1,    -1,    -1,    -1,   290,    -1,   292,   293,
      -1,   295,    -1,    -1,    -1,   299,    -1,    -1,   302,    -1,
     304,    -1,    -1,    -1,    -1,   309,    -1,   311,   312,   313,
     314,    -1,    -1,    -1,   318,    -1,   320,   321,    -1,    -1,
     324,   325,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   337,   338,   339,    -1,   341,    -1,   343,
     344,   345,   346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     394,    -1,    -1,   397,    -1,    -1,    -1,   401,   402,    -1,
     404,    -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,   413,
      -1,    -1,   416,   417,   418,   419,    -1,    -1,    -1,   423,
     424,   425,    -1,   427,   428,    -1,   430,    -1,   432,    -1,
      -1,    -1,    -1,    -1,    -1,   439,    -1,   441,   442,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     454,     4,     5,     6,     7,     8,   460,    -1,   462,    12,
      -1,   465,    -1,    -1,   468,    -1,   470,    -1,   472,   473,
     474,    -1,    25,    -1,    -1,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,   493,
      43,    -1,    45,    46,    47,    48,    49,    -1,    51,    -1,
      -1,    54,    -1,    56,    -1,    -1,    59,    -1,    -1,    62,
      63,    64,    65,    66,    67,    -1,    -1,    70,    71,    72,
      73,    -1,    -1,    76,    -1,    78,    79,    80,    -1,    82,
      -1,    84,    85,    -1,    -1,    -1,    -1,    90,    91,    92,
      93,    -1,    95,    96,    97,    -1,    99,    -1,   101,   102,
      -1,    -1,   105,   106,    -1,   108,    -1,   110,    -1,    -1,
     113,    -1,    -1,    -1,    -1,   118,    -1,    -1,   121,    -1,
      -1,   124,   125,   126,    -1,   128,   129,   130,    -1,    -1,
     133,   134,    -1,   136,    -1,   138,   139,   140,    -1,    -1,
      -1,    -1,   145,    -1,   147,    -1,   149,    -1,    -1,    -1,
     153,    -1,    -1,   156,   157,   158,    -1,   160,    -1,   162,
      -1,    -1,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,
      -1,   174,   175,    -1,    -1,    -1,   179,    -1,   181,    -1,
      -1,    -1,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,    -1,   202,
     203,   204,   205,   206,   207,   208,   209,    -1,   211,   212,
     213,    -1,   215,    -1,   217,    -1,    -1,   220,    -1,   222,
     223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,   232,
     233,    -1,    -1,   236,   237,   238,   239,   240,   241,   242,
     243,    -1,    -1,    -1,    -1,   248,    -1,   250,    -1,   252,
     253,    -1,    -1,   256,   257,   258,   259,    -1,    -1,   262,
     263,   264,   265,   266,    -1,    -1,    -1,   270,   271,    -1,
     273,    -1,    -1,   276,   277,    -1,    -1,    -1,    -1,   282,
      -1,   284,   285,    -1,    -1,    -1,    -1,   290,    -1,   292,
     293,    -1,   295,    -1,    -1,    -1,   299,    -1,    -1,   302,
      -1,   304,    -1,    -1,    -1,    -1,   309,    -1,   311,   312,
     313,   314,    -1,    -1,    -1,   318,    -1,   320,   321,    -1,
      -1,   324,   325,    -1,   327,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   337,   338,   339,    -1,   341,    -1,
     343,   344,   345,   346,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,   382,
     383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   394,    -1,    -1,   397,    -1,    -1,    -1,   401,   402,
      -1,   404,    -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,
     413,    -1,    -1,   416,   417,   418,   419,    -1,    -1,    -1,
     423,   424,   425,    -1,   427,   428,    -1,   430,    -1,   432,
      -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,   441,   442,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   454,    -1,    -1,    -1,    -1,    -1,   460,    -1,   462,
      -1,    -1,   465,    -1,    -1,   468,    -1,   470,    -1,   472,
     473,   474,     4,     5,     6,     7,     8,   480,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     493,    -1,    -1,    25,    -1,    -1,    28,    29,    30,    31,
      -1,    33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,
      -1,    43,    -1,    45,    46,    47,    48,    49,    -1,    51,
      -1,    -1,    54,    -1,    56,    -1,    -1,    59,    -1,    -1,
      62,    63,    64,    65,    66,    67,    -1,    -1,    70,    71,
      72,    73,    -1,    -1,    76,    -1,    78,    79,    80,    -1,
      82,    -1,    84,    85,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    -1,    95,    96,    97,    -1,    99,    -1,   101,
     102,    -1,    -1,   105,   106,    -1,   108,    -1,   110,    -1,
      -1,   113,    -1,    -1,    -1,    -1,   118,    -1,    -1,   121,
      -1,    -1,   124,   125,   126,    -1,   128,   129,   130,    -1,
      -1,   133,   134,    -1,   136,    -1,   138,   139,   140,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,    -1,    -1,
      -1,   153,    -1,    -1,   156,   157,   158,    -1,   160,    -1,
     162,    -1,    -1,   165,    -1,    -1,   168,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,    -1,   181,
      -1,    -1,    -1,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,    -1,
     202,   203,   204,   205,   206,   207,   208,   209,    -1,   211,
     212,   213,    -1,   215,    -1,   217,    -1,    -1,   220,    -1,
     222,   223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,
     232,   233,    -1,    -1,   236,   237,   238,   239,   240,   241,
     242,   243,    -1,    -1,    -1,    -1,   248,    -1,   250,    -1,
     252,   253,    -1,    -1,   256,   257,   258,   259,    -1,    -1,
     262,   263,   264,   265,   266,    -1,    -1,    -1,   270,   271,
      -1,   273,    -1,    -1,   276,   277,    -1,    -1,    -1,    -1,
     282,    -1,   284,   285,    -1,    -1,    -1,    -1,   290,    -1,
     292,   293,    -1,   295,    -1,    -1,    -1,   299,    -1,    -1,
     302,    -1,   304,    -1,    -1,    -1,    -1,   309,    -1,   311,
     312,   313,   314,    -1,    -1,    -1,   318,    -1,   320,   321,
      -1,    -1,   324,   325,    -1,   327,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   337,   338,   339,    -1,   341,
      -1,   343,   344,   345,   346,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,
     382,   383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   394,    -1,    -1,   397,    -1,    -1,    -1,   401,
     402,    -1,   404,    -1,    -1,    -1,    -1,   409,    -1,    -1,
      -1,   413,    -1,    -1,   416,   417,   418,   419,    -1,    -1,
      -1,   423,   424,   425,    -1,   427,   428,    -1,   430,    -1,
     432,    -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,   441,
     442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   454,    -1,    -1,    -1,    -1,    -1,   460,    -1,
     462,    -1,    -1,   465,    -1,    -1,   468,    -1,   470,    -1,
     472,   473,   474,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    -1,    -1,   486,    -1,    -1,    -1,    -1,    -1,
      -1,   493,    -1,    -1,    25,    -1,    -1,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    -1,    -1,    -1,    40,
      -1,    -1,    43,    -1,    45,    46,    47,    48,    49,    -1,
      51,    -1,    -1,    54,    -1,    56,    -1,    -1,    59,    -1,
      -1,    62,    63,    64,    65,    66,    67,    -1,    -1,    70,
      71,    72,    73,    -1,    -1,    76,    -1,    78,    79,    80,
      -1,    82,    -1,    84,    85,    -1,    -1,    -1,    -1,    90,
      91,    92,    93,    -1,    95,    96,    97,    -1,    99,    -1,
     101,   102,    -1,    -1,   105,   106,    -1,   108,    -1,   110,
      -1,    -1,   113,    -1,    -1,    -1,    -1,   118,    -1,    -1,
     121,    -1,    -1,   124,   125,   126,    -1,   128,   129,   130,
      -1,    -1,   133,   134,    -1,   136,    -1,   138,   139,   140,
      -1,    -1,    -1,    -1,   145,    -1,   147,    -1,   149,    -1,
      -1,    -1,   153,    -1,    -1,   156,   157,   158,    -1,   160,
      -1,   162,    -1,    -1,   165,    -1,    -1,   168,    -1,    -1,
      -1,    -1,    -1,   174,   175,    -1,    -1,    -1,   179,    -1,
     181,    -1,    -1,    -1,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
      -1,   202,   203,   204,   205,   206,   207,   208,   209,    -1,
     211,   212,   213,    -1,   215,    -1,   217,    -1,    -1,   220,
      -1,   222,   223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     231,   232,   233,    -1,    -1,   236,   237,   238,   239,   240,
     241,   242,   243,    -1,    -1,    -1,    -1,   248,    -1,   250,
      -1,   252,   253,    -1,    -1,   256,   257,   258,   259,    -1,
      -1,   262,   263,   264,   265,   266,    -1,    -1,    -1,   270,
     271,    -1,   273,    -1,    -1,   276,   277,    -1,    -1,    -1,
      -1,   282,    -1,   284,   285,    -1,    -1,    -1,    -1,   290,
      -1,   292,   293,    -1,   295,    -1,    -1,    -1,   299,    -1,
      -1,   302,    -1,   304,    -1,    -1,    -1,    -1,   309,    -1,
     311,   312,   313,   314,    -1,    -1,    -1,   318,    -1,   320,
     321,    -1,    -1,   324,   325,    -1,   327,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   337,   338,   339,    -1,
     341,    -1,   343,   344,   345,   346,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   356,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,
      -1,   382,   383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   394,    -1,    -1,   397,    -1,    -1,    -1,
     401,   402,    -1,   404,    -1,    -1,    -1,    -1,   409,    -1,
      -1,    -1,   413,    -1,    -1,   416,   417,   418,   419,    -1,
      -1,    -1,   423,   424,   425,    -1,   427,   428,    -1,   430,
      -1,   432,    -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,
     441,   442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   454,    -1,    -1,    -1,    -1,    -1,   460,
      -1,   462,    -1,    -1,   465,    -1,    -1,   468,    -1,   470,
      -1,   472,   473,   474,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    -1,    -1,    -1,   487,    -1,    -1,    -1,
      -1,    -1,   493,    -1,    -1,    25,    -1,    -1,    28,    29,
      30,    31,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      40,    -1,    -1,    43,    -1,    45,    46,    47,    48,    49,
      -1,    51,    -1,    -1,    54,    -1,    56,    -1,    -1,    59,
      -1,    -1,    62,    63,    64,    65,    66,    67,    -1,    -1,
      70,    71,    72,    73,    -1,    -1,    76,    -1,    78,    79,
      80,    -1,    82,    -1,    84,    85,    -1,    -1,    -1,    -1,
      90,    91,    92,    93,    -1,    95,    96,    97,    -1,    99,
      -1,   101,   102,    -1,    -1,   105,   106,    -1,   108,    -1,
     110,    -1,    -1,   113,    -1,    -1,    -1,    -1,   118,    -1,
      -1,   121,    -1,    -1,   124,   125,   126,    -1,   128,   129,
     130,    -1,    -1,   133,   134,    -1,   136,    -1,   138,   139,
     140,    -1,    -1,    -1,    -1,   145,    -1,   147,    -1,   149,
      -1,    -1,    -1,   153,    -1,    -1,   156,   157,   158,    -1,
     160,    -1,   162,    -1,    -1,   165,    -1,    -1,   168,    -1,
      -1,    -1,    -1,    -1,   174,   175,    -1,    -1,    -1,   179,
      -1,   181,    -1,    -1,    -1,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,    -1,   202,   203,   204,   205,   206,   207,   208,   209,
      -1,   211,   212,   213,    -1,   215,    -1,   217,    -1,    -1,
     220,    -1,   222,   223,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   231,   232,   233,    -1,    -1,   236,   237,   238,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,   248,    -1,
     250,    -1,   252,   253,    -1,    -1,   256,   257,   258,   259,
      -1,    -1,   262,   263,   264,   265,   266,    -1,    -1,    -1,
     270,   271,    -1,   273,    -1,    -1,   276,   277,    -1,    -1,
      -1,    -1,   282,    -1,   284,   285,    -1,    -1,    -1,    -1,
     290,    -1,   292,   293,    -1,   295,    -1,    -1,    -1,   299,
      -1,    -1,   302,    -1,   304,    -1,    -1,    -1,    -1,   309,
      -1,   311,   312,   313,   314,    -1,    -1,    -1,   318,    -1,
     320,   321,    -1,    -1,   324,   325,    -1,   327,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   338,   339,
      -1,   341,    -1,   343,   344,   345,   346,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   356,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   375,    -1,    -1,    -1,    -1,
      -1,    -1,   382,   383,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   394,    -1,    -1,   397,    -1,    -1,
      -1,   401,   402,    -1,   404,    -1,    -1,    -1,    -1,   409,
      -1,    -1,    -1,   413,    -1,    -1,   416,   417,   418,   419,
      -1,    -1,    -1,   423,   424,   425,    -1,   427,   428,    -1,
     430,    -1,   432,    -1,    -1,    -1,    -1,    -1,    -1,   439,
      -1,   441,   442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   454,     4,     5,     6,     7,     8,
     460,    -1,   462,    12,    -1,   465,    -1,    -1,   468,    -1,
     470,    -1,   472,   473,   474,    -1,    25,    -1,    -1,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    -1,    -1,
      -1,    40,    -1,   493,    43,    -1,    45,    46,    47,    48,
      49,    -1,    51,    -1,    -1,    54,    -1,    56,    -1,    -1,
      59,    -1,    -1,    62,    63,    64,    65,    66,    67,    -1,
      -1,    70,    71,    72,    73,    -1,    -1,    76,    -1,    78,
      79,    80,    -1,    82,    -1,    84,    85,    -1,    -1,    -1,
      -1,    90,    91,    92,    93,    -1,    95,    96,    97,    -1,
      99,    -1,   101,   102,    -1,    -1,   105,   106,    -1,   108,
      -1,   110,    -1,    -1,   113,    -1,    -1,    -1,    -1,   118,
      -1,    -1,   121,    -1,    -1,   124,   125,   126,    -1,   128,
     129,   130,    -1,    -1,   133,   134,    -1,   136,    -1,   138,
     139,   140,    -1,    -1,    -1,    -1,   145,    -1,   147,    -1,
     149,    -1,    -1,    -1,   153,    -1,    -1,   156,   157,   158,
      -1,   160,    -1,   162,    -1,    -1,   165,    -1,    -1,   168,
      -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,    -1,
     179,    -1,   181,    -1,    -1,    -1,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,    -1,   202,   203,   204,   205,   206,   207,   208,
     209,    -1,   211,   212,   213,    -1,   215,    -1,   217,    -1,
      -1,   220,    -1,   222,   223,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   231,   232,   233,    -1,    -1,   236,   237,   238,
     239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,   248,
      -1,   250,    -1,   252,   253,    -1,    -1,   256,   257,   258,
     259,    -1,    -1,   262,   263,   264,   265,   266,    -1,    -1,
      -1,   270,   271,    -1,   273,    -1,    -1,   276,   277,    -1,
      -1,    -1,    -1,   282,    -1,   284,   285,    -1,    -1,    -1,
      -1,   290,    -1,   292,   293,    -1,   295,    -1,    -1,    -1,
     299,    -1,    -1,   302,    -1,   304,    -1,    -1,    -1,    -1,
     309,    -1,   311,   312,   313,   314,    -1,    -1,    -1,   318,
      -1,   320,   321,    -1,    -1,   324,   325,    -1,   327,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   338,
     339,    -1,   341,    -1,   343,   344,   345,   346,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,    -1,    -1,
      -1,    -1,    -1,   382,   383,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   394,    -1,    -1,   397,    -1,
      -1,    -1,   401,   402,    -1,   404,    -1,    -1,    -1,    -1,
     409,    -1,    -1,    -1,   413,    -1,    -1,   416,   417,   418,
     419,    -1,    -1,    -1,   423,   424,   425,    -1,   427,   428,
      -1,   430,    -1,   432,    -1,    -1,    -1,    -1,    -1,    -1,
     439,    -1,   441,   442,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   454,     4,     5,     6,     7,
       8,   460,    -1,   462,    12,    -1,   465,    -1,    -1,   468,
      -1,   470,    -1,   472,   473,   474,    -1,    25,    -1,    -1,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    40,    -1,   493,    43,    -1,    45,    46,    47,
      48,    49,    -1,    51,    -1,    -1,    54,    -1,    56,    -1,
      -1,    59,    -1,    -1,    62,    63,    64,    65,    66,    67,
      -1,    -1,    70,    71,    72,    73,    -1,    -1,    76,    -1,
      78,    79,    80,    -1,    82,    -1,    84,    85,    -1,    -1,
      -1,    -1,    90,    91,    92,    93,    -1,    95,    96,    97,
      -1,    99,    -1,   101,   102,    -1,    -1,   105,   106,    -1,
     108,    -1,   110,    -1,    -1,   113,    -1,    -1,    -1,    -1,
     118,    -1,    -1,   121,    -1,    -1,   124,   125,   126,    -1,
     128,   129,   130,    -1,    -1,   133,   134,    -1,   136,    -1,
     138,   139,   140,    -1,    -1,    -1,    -1,   145,    -1,   147,
      -1,   149,    -1,    -1,    -1,   153,    -1,    -1,   156,   157,
     158,    -1,   160,    -1,   162,    -1,    -1,   165,    -1,    -1,
     168,    -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,
      -1,   179,    -1,   181,    -1,    -1,    -1,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,    -1,   202,   203,   204,   205,   206,   207,
     208,   209,    -1,   211,   212,   213,    -1,   215,    -1,   217,
      -1,    -1,   220,    -1,   222,   223,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   231,   232,   233,    -1,    -1,   236,   237,
     238,   239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,
     248,    -1,   250,    -1,   252,   253,    -1,    -1,   256,   257,
     258,   259,    -1,    -1,   262,   263,   264,   265,   266,    -1,
      -1,    -1,   270,   271,    -1,   273,    -1,    -1,   276,   277,
      -1,    -1,    -1,    -1,   282,    -1,   284,   285,    -1,    -1,
      -1,    -1,   290,    -1,   292,   293,    -1,   295,    -1,    -1,
      -1,   299,    -1,    -1,   302,    -1,   304,    -1,    -1,    -1,
      -1,   309,    -1,   311,   312,   313,   314,    -1,    -1,    -1,
     318,    -1,   320,   321,    -1,    -1,   324,   325,    -1,   327,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,
     338,   339,    -1,   341,    -1,   343,   344,   345,   346,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,    -1,
      -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,    -1,   397,
      -1,    -1,    -1,   401,   402,    -1,   404,    -1,    -1,    -1,
      -1,   409,    -1,    -1,    -1,   413,    -1,    -1,   416,   417,
     418,   419,    -1,    -1,    -1,   423,   424,   425,    -1,   427,
     428,    -1,   430,    -1,   432,    -1,    -1,    -1,    -1,    -1,
      -1,   439,    -1,   441,   442,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   454,     4,     5,     6,
       7,     8,   460,    -1,   462,    12,    -1,   465,    -1,    -1,
     468,    -1,   470,    -1,   472,   473,   474,    -1,    25,    -1,
      -1,    28,    29,    30,    31,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    40,    -1,   493,    43,    -1,    45,    46,
      47,    48,    49,    -1,    51,    -1,    -1,    54,    -1,    56,
      -1,    -1,    59,    -1,    -1,    62,    63,    64,    65,    66,
      67,    -1,    -1,    70,    71,    72,    73,    -1,    -1,    76,
      -1,    78,    79,    80,    -1,    82,    -1,    84,    85,    -1,
      -1,    -1,    -1,    90,    91,    92,    93,    -1,    95,    96,
      97,    -1,    99,    -1,   101,   102,    -1,    -1,   105,   106,
      -1,   108,    -1,   110,    -1,    -1,   113,    -1,    -1,    -1,
      -1,   118,    -1,    -1,   121,    -1,    -1,   124,   125,   126,
      -1,   128,   129,   130,    -1,    -1,   133,   134,    -1,   136,
      -1,   138,   139,   140,    -1,    -1,    -1,    -1,   145,    -1,
     147,    -1,   149,    -1,    -1,    -1,   153,    -1,    -1,   156,
     157,   158,    -1,   160,    -1,   162,    -1,    -1,   165,    -1,
      -1,   168,    -1,    -1,    -1,    -1,    -1,   174,   175,    -1,
      -1,    -1,   179,    -1,   181,    -1,    -1,    -1,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,    -1,   202,   203,   204,   205,   206,
     207,   208,   209,    -1,   211,   212,   213,    -1,   215,    -1,
     217,    -1,    -1,   220,    -1,   222,   223,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   231,   232,   233,    -1,    -1,   236,
     237,   238,   239,   240,   241,   242,   243,    -1,    -1,    -1,
      -1,   248,    -1,   250,    -1,   252,   253,    -1,    -1,   256,
     257,   258,   259,    -1,    -1,   262,   263,   264,   265,   266,
      -1,    -1,    -1,   270,   271,    -1,   273,    -1,    -1,   276,
     277,    -1,    -1,    -1,    -1,   282,    -1,   284,   285,    -1,
      -1,    -1,    -1,   290,    -1,   292,   293,    -1,   295,    -1,
      -1,    -1,   299,    -1,    -1,   302,    -1,   304,    -1,    -1,
      -1,    -1,   309,    -1,   311,   312,   313,   314,    -1,    -1,
      -1,   318,    -1,   320,   321,    -1,    -1,   324,   325,    -1,
     327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     337,   338,   339,    -1,   341,    -1,   343,   344,   345,   346,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,
      -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,    -1,
     397,    -1,    -1,    -1,   401,   402,    -1,   404,    -1,    -1,
      -1,    -1,   409,    -1,    -1,    -1,   413,    -1,    -1,   416,
     417,   418,   419,    -1,    -1,    -1,   423,   424,   425,    -1,
     427,   428,    -1,   430,    -1,   432,    -1,    -1,    -1,    -1,
      -1,    -1,   439,    -1,   441,   442,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,     4,     5,
       6,     7,     8,   460,    -1,   462,    12,    -1,   465,    -1,
      -1,   468,    -1,   470,    -1,   472,   473,   474,    -1,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    33,    34,    35,
      36,    -1,    -1,    -1,    40,    -1,   493,    43,    -1,    45,
      46,    47,    48,    49,    -1,    51,    -1,    -1,    54,    -1,
      56,    -1,    -1,    59,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    -1,    70,    71,    72,    73,    -1,    -1,
      76,    -1,    78,    79,    80,    -1,    82,    -1,    84,    85,
      -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,    95,
      96,    97,    -1,    99,    -1,   101,   102,    -1,    -1,   105,
     106,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,    -1,
      -1,    -1,   118,    -1,    -1,   121,    -1,    -1,   124,   125,
     126,    -1,   128,   129,   130,    -1,    -1,   133,   134,    -1,
     136,    -1,   138,   139,   140,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,    -1,    -1,    -1,   153,    -1,    -1,
     156,   157,   158,    -1,   160,    -1,   162,    -1,    -1,   165,
      -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,   174,   175,
     176,    -1,    -1,   179,    -1,   181,    -1,    -1,    -1,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,    -1,   202,   203,   204,   205,
     206,   207,   208,   209,    -1,   211,   212,   213,    -1,   215,
      -1,   217,    -1,    -1,   220,    -1,   222,   223,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   231,   232,   233,    -1,    -1,
     236,   237,   238,   239,   240,   241,   242,   243,    -1,    -1,
      -1,    -1,   248,    -1,   250,    -1,   252,   253,    -1,    -1,
     256,   257,   258,   259,    -1,    -1,   262,   263,   264,   265,
     266,    -1,    -1,    -1,   270,   271,    -1,   273,    -1,    -1,
     276,   277,    -1,   279,    -1,    -1,   282,    -1,   284,   285,
      -1,    -1,    -1,    -1,   290,    -1,   292,   293,    -1,   295,
      -1,    -1,    -1,   299,    -1,    -1,   302,    -1,   304,    -1,
      -1,    -1,    -1,   309,    -1,   311,   312,   313,   314,    -1,
      -1,    -1,   318,    -1,   320,   321,    -1,    -1,   324,   325,
      -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   337,   338,   339,    -1,   341,    -1,   343,   344,   345,
     346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,
      -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,
      -1,   397,    -1,    -1,    -1,   401,   402,    -1,   404,    -1,
      -1,    -1,    -1,   409,    -1,    -1,    -1,   413,    -1,    -1,
     416,   417,   418,   419,    -1,    -1,    -1,   423,   424,   425,
      -1,   427,   428,    -1,   430,    -1,   432,    -1,    -1,    -1,
      -1,    -1,    -1,   439,    -1,   441,   442,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,     4,
       5,     6,     7,     8,   460,    -1,   462,    12,    -1,   465,
      -1,    -1,   468,    -1,   470,    -1,   472,   473,   474,    -1,
      25,    -1,    -1,    28,    29,    30,    31,    -1,    33,    34,
      35,    36,    -1,    -1,    -1,    40,   492,    -1,    43,    -1,
      45,    46,    47,    48,    49,    -1,    51,    -1,    -1,    54,
      -1,    56,    -1,    -1,    59,    -1,    -1,    62,    63,    64,
      65,    66,    67,    -1,    -1,    70,    71,    72,    73,    -1,
      -1,    76,    -1,    78,    79,    80,    -1,    82,    -1,    84,
      85,    -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,
      95,    96,    97,    -1,    99,    -1,   101,   102,    -1,    -1,
     105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,
      -1,    -1,    -1,   118,    -1,    -1,   121,    -1,    -1,   124,
     125,   126,    -1,   128,   129,   130,    -1,    -1,   133,   134,
      -1,   136,    -1,   138,   139,   140,    -1,    -1,    -1,    -1,
     145,    -1,   147,    -1,   149,    -1,    -1,    -1,   153,    -1,
      -1,   156,   157,   158,    -1,   160,    -1,   162,    -1,    -1,
     165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,   174,
     175,   176,    -1,    -1,   179,    -1,   181,    -1,    -1,    -1,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,    -1,   202,   203,   204,
     205,   206,   207,   208,   209,    -1,   211,   212,   213,    -1,
     215,    -1,   217,    -1,    -1,   220,    -1,   222,   223,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   231,   232,   233,    -1,
      -1,   236,   237,   238,   239,   240,   241,   242,   243,    -1,
      -1,    -1,    -1,   248,    -1,   250,    -1,   252,   253,    -1,
      -1,   256,   257,   258,   259,    -1,    -1,   262,   263,   264,
     265,   266,    -1,    -1,    -1,   270,   271,    -1,   273,    -1,
      -1,   276,   277,    -1,   279,    -1,    -1,   282,    -1,   284,
     285,    -1,    -1,    -1,    -1,   290,    -1,   292,   293,    -1,
     295,    -1,    -1,    -1,   299,    -1,    -1,   302,    -1,   304,
      -1,    -1,    -1,    -1,   309,    -1,   311,   312,   313,   314,
      -1,    -1,    -1,   318,    -1,   320,   321,    -1,    -1,   324,
     325,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   337,   338,   339,    -1,   341,    -1,   343,   344,
     345,   346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   356,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
     375,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,
      -1,    -1,   397,    -1,    -1,    -1,   401,   402,    -1,   404,
      -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,   413,    -1,
      -1,   416,   417,   418,   419,    -1,    -1,    -1,   423,   424,
     425,    -1,   427,   428,    -1,   430,    -1,   432,    -1,    -1,
      87,    -1,    -1,    -1,   439,    -1,   441,   442,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,
      -1,    -1,    -1,    -1,    -1,   460,    -1,   462,    -1,    -1,
     465,    -1,    -1,   468,    -1,   470,    -1,   472,   473,   474,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   492,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     177,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   216,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,   226,
     227,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
     247,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,
      -1,    -1,    -1,   144,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   167,    -1,    -1,    -1,
      -1,    87,    -1,   310,    -1,    -1,   177,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   167,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   177,   216,    -1,   167,    -1,    -1,
      -1,   358,    -1,    87,    -1,   226,   227,   177,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,
      -1,   167,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    -1,   226,   227,    -1,   216,    -1,    -1,   167,
      -1,    -1,    -1,    -1,    -1,    -1,   226,   227,    -1,   177,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,
     216,    -1,    -1,   167,    -1,    -1,    -1,    -1,    -1,   310,
     226,   227,    -1,   177,    -1,    -1,    -1,    -1,   216,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,   227,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,   310,    -1,   247,
     487,   488,   216,    -1,    -1,    -1,    -1,   358,    -1,    -1,
     310,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   310,   358,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,
      -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   358,    -1,    -1,    -1,   310,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     358,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,   476,   477,   478,   479,   480,
     481,   482,   483,    -1,    -1,    -1,    -1,   488,    -1,    -1,
      -1,    -1,    -1,    -1,   358,    -1,    87,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,    -1,    -1,    -1,   487,   488,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,    -1,    -1,   487,   488,    -1,
      87,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
      -1,   487,   488,    -1,    -1,    87,   167,    -1,   476,   477,
     478,   479,   480,   481,   482,   483,   177,    -1,    -1,   487,
     488,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,   476,   477,   478,   479,   480,   481,   482,   483,
     167,    -1,    87,   487,   488,   216,    -1,    -1,    -1,    -1,
     177,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,   167,   247,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,   216,
      -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,   226,
     227,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     247,    -1,   167,    -1,   216,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,    -1,   226,   227,    -1,    -1,    -1,   310,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   216,    -1,    -1,    -1,   167,    -1,    -1,    -1,    -1,
      -1,   226,   227,   310,    -1,   177,    -1,   358,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,
     167,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,
     177,   358,    -1,    -1,   226,   227,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   310,   358,    -1,    -1,   216,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,
     227,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     247,    -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,
     481,   482,   483,   358,    -1,    87,   487,   488,   310,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,    -1,    -1,    -1,
     487,   488,    -1,   310,    -1,    -1,   358,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,   481,
     482,   483,    -1,    -1,    -1,   167,   488,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,
      -1,   358,    -1,    87,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,    -1,    -1,   488,   216,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   226,   227,    -1,    -1,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,   247,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,   481,
     482,   483,    87,   167,    -1,    -1,   488,    -1,    -1,    -1,
      -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,    -1,   310,    87,
      -1,   488,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,   167,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,    -1,    -1,    -1,   358,    -1,    -1,    -1,
      87,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   167,
      -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,
      -1,   226,   227,    -1,    -1,    -1,   310,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,
     167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,   227,
     177,    -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,
      -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,   481,
     482,   483,    -1,    -1,    -1,   310,   488,   167,    -1,   216,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,   226,
     227,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
     247,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,   310,   358,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,   247,    -1,    -1,
     216,    -1,   476,   477,   478,   479,   480,   481,   482,   483,
     358,    -1,    87,   310,   488,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   247,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,
     310,   358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,    -1,   167,   488,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,   358,    -1,
      87,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,   476,   477,
     478,   479,   480,   481,   482,   483,    -1,    -1,   167,    -1,
     488,   216,   358,    -1,    -1,    -1,    -1,    -1,   177,    -1,
      -1,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,   247,    -1,    -1,    -1,    -1,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,   216,    -1,    -1,
     167,   488,    87,    -1,    -1,    -1,    -1,   226,   227,    -1,
     177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,   310,    -1,    87,   488,   216,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,
     227,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
     247,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   310,   177,   358,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,   167,    -1,    -1,
      -1,   216,    -1,    -1,    -1,    -1,    -1,   177,    -1,   358,
      -1,   226,   227,   310,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,   227,    87,    -1,
      -1,   358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,    -1,    -1,   488,    -1,   310,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,   476,   477,   478,
     479,   480,   481,   482,   483,    -1,    -1,    -1,   167,   488,
     310,    -1,    -1,   358,    -1,    -1,    -1,    -1,   177,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,   216,   358,    -1,
      -1,   488,    87,    -1,    -1,    -1,    -1,   226,   227,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,    -1,   167,   488,    -1,    -1,    -1,    87,    -1,    -1,
      -1,   310,   177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,   167,    -1,    -1,    -1,   488,    -1,
      -1,   216,    -1,    -1,   177,    -1,    -1,    -1,    -1,   358,
      -1,   226,   227,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,   247,    -1,    -1,    -1,    -1,   167,    -1,    -1,
      -1,    -1,    -1,   216,    -1,    -1,    -1,   177,    -1,    -1,
      -1,    -1,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    87,    -1,    -1,    -1,   310,   226,   227,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,
     479,   480,   481,   482,   483,    -1,    -1,   310,    -1,   488,
      -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     310,   177,    -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,
     226,   227,    87,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,    -1,    -1,   488,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,    87,   167,    -1,   310,   488,    -1,    -1,    -1,    -1,
      -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,   167,    -1,    -1,    -1,   488,    -1,
      -1,   216,   358,    -1,   177,    -1,    87,    -1,    -1,    -1,
      -1,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   167,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    -1,   216,    -1,    -1,    -1,    -1,    87,    -1,
      -1,    -1,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
     216,    -1,    -1,    -1,    -1,    -1,   167,    -1,    -1,    -1,
     226,   227,    -1,    -1,    -1,   310,   177,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,   167,    -1,
      -1,    -1,   488,    -1,    -1,   216,    -1,   310,   177,    -1,
      -1,    -1,    -1,   358,    -1,   226,   227,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,   247,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   310,    -1,    -1,   216,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   358,    -1,   226,   227,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,   358,    -1,    -1,    -1,    -1,    -1,    -1,   310,
      -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,   310,    -1,   488,    -1,    -1,    -1,   358,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,   167,    -1,    -1,    -1,   488,    -1,    -1,    -1,   358,
      -1,   177,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
      -1,    -1,   488,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     216,    -1,    -1,    -1,    -1,    -1,    87,   167,    -1,    -1,
     226,   227,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,   476,   477,   478,   479,   480,
     481,   482,   483,   167,    -1,    -1,    -1,   488,    -1,    -1,
      -1,    -1,    -1,   177,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,
     479,   480,   481,   482,   483,    -1,   167,   247,    -1,   488,
      -1,    -1,   216,    -1,   310,    -1,   177,    -1,    -1,    -1,
      -1,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,
      -1,    -1,   358,    -1,    -1,   226,   227,    -1,    -1,    -1,
     310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   247,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,
      -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    87,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
      -1,    -1,   488,    -1,    -1,    -1,    -1,   358,    -1,    -1,
      87,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,    87,   167,    -1,    -1,   488,    -1,
      -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   476,   477,   478,   479,   480,   481,   482,   483,
     167,    87,    -1,    -1,   488,    -1,    -1,    -1,    -1,    -1,
     177,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    87,
      -1,    -1,    -1,    -1,   226,   227,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,
     481,   482,   483,    -1,   167,   247,    -1,   488,    -1,   216,
      -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,   226,
     227,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     247,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    -1,   216,    -1,    -1,    -1,    -1,    -1,   167,
      -1,    -1,    -1,   226,   227,    -1,    -1,    -1,   310,   177,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
     216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,   227,    -1,   310,    -1,    -1,    -1,    -1,   216,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,   226,   227,
      -1,   247,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,   247,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,
      -1,   358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,
      87,    -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   358,    -1,   476,   477,   478,   479,   480,   481,
     482,   483,    -1,    -1,    -1,    -1,   488,    87,    -1,    -1,
     358,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,   476,
     477,   478,   479,   480,   481,   482,   483,    -1,    -1,    -1,
     167,   488,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,
     177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,    -1,    -1,    -1,    -1,   488,    -1,   167,    -1,   216,
      -1,    -1,    -1,    -1,    87,    -1,    -1,   177,    -1,   226,
     227,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
     247,    -1,   488,    -1,    -1,    -1,    -1,   167,   476,   477,
     478,   479,   480,   481,   482,   483,   216,   177,    -1,    -1,
     488,    -1,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,
      -1,   144,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,
      -1,    -1,    -1,    -1,   167,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,   310,   177,    -1,   226,   227,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,
     310,   358,    -1,   226,   227,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,   247,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
     310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    -1,   310,   358,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    87,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,    -1,    -1,    -1,
      -1,   488,    -1,    -1,    -1,   358,   167,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   167,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,   177,    -1,    -1,   488,    -1,
      -1,    -1,    87,   167,    -1,   216,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   177,    -1,   226,   227,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,   216,    -1,   247,   167,   488,    -1,
      -1,    -1,    -1,    -1,   226,   227,    -1,   177,    -1,    -1,
      -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,   227,    -1,   247,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,    -1,   167,   247,   487,    -1,   216,    -1,    -1,    -1,
      -1,    -1,   177,    -1,    -1,    -1,   226,   227,    -1,   310,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,
      -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   226,   227,    -1,    -1,    -1,   310,   358,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   247,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,   358,    -1,    -1,    -1,
     310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   358,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,   310,    -1,    -1,   358,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    87,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,
     481,   482,   483,   358,    87,    -1,   487,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,
      -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,   481,
     482,   483,    -1,    -1,    -1,   487,    -1,    -1,    -1,    -1,
      -1,    -1,   476,   477,   478,   479,   480,   481,   482,   483,
      87,   167,    -1,   487,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,   167,    -1,    -1,   487,    -1,    -1,
      -1,    -1,    -1,    -1,   177,    -1,    -1,   167,    -1,    -1,
     216,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,
     226,   227,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
     167,   247,   487,   216,    -1,    -1,    -1,    -1,    -1,    -1,
     177,    -1,    -1,   226,   227,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,   216,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,
     227,    -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     247,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,   310,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     310,    -1,   358,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   310,    -1,   358,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,    87,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,   358,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    87,   167,
      -1,   487,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,
      -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,    -1,    -1,    -1,   487,   167,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,   177,    -1,   487,   216,    -1,
      -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,   226,   227,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,    -1,   167,   247,
     487,    -1,    -1,    -1,   216,    -1,    -1,    -1,   177,    -1,
      -1,   167,    -1,    -1,   226,   227,    -1,    -1,    -1,    -1,
      -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,    -1,
      -1,    -1,    -1,   167,    -1,    -1,    -1,   226,   227,    -1,
     216,    -1,   310,   177,    -1,    -1,    -1,    -1,    -1,    -1,
     226,   227,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,
      -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     358,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   310,    -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,   358,
      -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,
      -1,    -1,   358,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,   477,
     478,   479,   480,   481,   482,   483,    -1,    -1,    -1,   487,
      -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,   481,
     482,   483,    -1,    -1,    -1,   487,    -1,    -1,    -1,    -1,
      -1,    87,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,
     479,   480,   481,   482,   483,    -1,    -1,    -1,   487,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,   167,    -1,
      -1,   487,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      87,   167,   476,   477,   478,   479,   480,   481,   482,   483,
      -1,   177,    -1,   487,    -1,    -1,    -1,   216,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,   227,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,
     216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,   227,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     167,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,
      -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   216,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,
     227,    -1,   167,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,   358,
     247,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   167,    -1,    -1,
      -1,   216,   358,    -1,    -1,    -1,    -1,   177,    -1,    -1,
      -1,   226,   227,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,   247,   310,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    87,    -1,    -1,    -1,   226,   227,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,   247,    -1,    -1,
      -1,   358,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,
     479,   480,   481,   482,   483,   310,    87,    -1,   487,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
      -1,   487,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     310,    87,   177,   358,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   167,    -1,    -1,    -1,
      -1,   216,    -1,    -1,    -1,    -1,   177,    -1,   358,    -1,
      -1,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,    -1,    -1,    -1,
     487,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   167,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,
      -1,   177,    -1,    -1,    87,   226,   227,    -1,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,   247,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
     216,    -1,   487,    -1,    -1,   310,    -1,    -1,    -1,    -1,
     226,   227,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,   167,    -1,    -1,   487,    -1,   310,
      87,    -1,    -1,   358,   177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,   216,   310,    -1,    -1,   358,    -1,    -1,
      -1,    -1,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,   247,    -1,    -1,    -1,    -1,    -1,
     167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     177,    -1,   358,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,   216,
      -1,    -1,   487,    -1,    -1,    -1,    -1,   310,    87,   226,
     227,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     247,    -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,
     481,   482,   483,   167,    -1,    -1,   487,    -1,    -1,    -1,
      -1,    -1,    -1,   177,    -1,   358,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,   167,    -1,
      -1,   487,   216,   310,    -1,    -1,    -1,    -1,   177,    -1,
      -1,    -1,   226,   227,    -1,   216,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   247,   216,    -1,    -1,
      -1,   358,    -1,    -1,    -1,    -1,    -1,   226,   227,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,
      -1,    -1,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,    -1,    -1,    -1,   487,    -1,   310,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   310,    -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,    -1,    -1,    -1,
     487,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,
      -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   476,   477,   478,   479,   480,   481,   482,   483,
      -1,    -1,    -1,   487,   167,   476,   477,   478,   479,   480,
     481,   482,   483,    87,   177,    -1,   487,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,
     479,   480,   481,   482,   483,    -1,    -1,    -1,   487,    -1,
      87,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   226,   227,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   177,    -1,    -1,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     177,    -1,   216,    87,    -1,    -1,    -1,   310,    -1,    -1,
      -1,    -1,   226,   227,    -1,   216,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,   216,
      -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,   226,
     227,    -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   177,    -1,    -1,   310,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   216,   310,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,   227,   358,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,   358,    -1,    -1,   487,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,   476,   477,   478,   479,   480,   481,   482,   483,
      -1,    87,    -1,   487,   358,   476,   477,   478,   479,   480,
     481,   482,   483,    -1,    87,    -1,   487,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,    -1,    -1,    -1,
     487,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    -1,    -1,   167,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   167,   476,   477,   478,   479,   480,   481,   482,   483,
     216,   177,    -1,   487,   167,    -1,    -1,    -1,    -1,    -1,
     226,   227,    87,   216,   177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     216,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
     226,   227,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   167,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,    -1,    -1,    -1,    -1,   310,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,   216,   358,    -1,    -1,    -1,    -1,   310,    -1,    -1,
      -1,   226,   227,    -1,    -1,   358,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    87,    -1,    -1,   358,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
      -1,   487,   167,   476,   477,   478,   479,   480,   481,   482,
     483,    87,   177,   358,   487,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
      -1,   487,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,   216,    -1,    -1,   487,    -1,    -1,    -1,    -1,    -1,
      -1,   226,   227,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    -1,    -1,   167,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
     216,    87,   487,    -1,    -1,   310,    -1,    -1,    -1,    -1,
     226,   227,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,   227,   358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,    -1,   487,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    87,
      -1,   487,   358,   476,   477,   478,   479,   480,   481,   482,
     483,    -1,    87,    -1,   487,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,   167,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,
      -1,    -1,   167,    -1,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   167,
     476,   477,   478,   479,   480,   481,   482,   483,   216,   177,
      -1,   487,   167,    -1,    -1,    -1,    -1,    -1,   226,   227,
      87,   216,   177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,   247,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,
      -1,    -1,   247,    -1,   167,    -1,    -1,    -1,   226,   227,
      -1,   216,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,
      -1,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,   247,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     167,    -1,   310,   216,    -1,    -1,    -1,    -1,    -1,    -1,
     177,    -1,    -1,   226,   227,   310,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,   216,
     358,    -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,   226,
     227,    -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     358,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,
      -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,   310,    -1,   358,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,   477,
     478,   479,   480,   481,   482,   483,    -1,    -1,    -1,   487,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,   358,   487,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,   476,   477,
     478,   479,   480,   481,   482,   483,    -1,    -1,    -1,   487,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,    -1,   487,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,    -1,    -1,   167,   487,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   177,    -1,    -1,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,    -1,    -1,    87,
     487,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,   227,    -1,   216,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   167,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,
      -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,   227,
      -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,   247,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,
      -1,    -1,   476,   477,   478,   479,   480,   481,   482,   483,
     358,    87,    -1,   487,    -1,   476,   477,   478,   479,   480,
     481,   482,   483,    -1,    87,    -1,   487,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,   167,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    -1,    -1,   167,    -1,    87,   216,    -1,    -1,
      -1,    -1,    -1,    -1,   177,    -1,    -1,   226,   227,    -1,
      -1,    -1,    -1,    87,    -1,    -1,   216,    -1,   476,   477,
     478,   479,   480,   481,   482,   483,   226,   227,   247,   487,
     216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,   227,    -1,   216,    -1,    -1,    -1,   247,    -1,    -1,
      -1,    -1,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,
      -1,   310,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,
     310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   310,   216,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   226,   227,   310,    -1,   358,
      -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,   227,    -1,    -1,   247,    -1,   358,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,   358,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   310,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,
     479,   480,   481,   482,   483,    -1,    -1,   358,   487,    -1,
      -1,    87,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,   358,    -1,    -1,   487,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
      -1,   487,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,    -1,    -1,    -1,   487,    -1,    -1,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,
     481,   482,   483,    -1,    -1,    -1,   487,   247,    -1,    -1,
     216,    -1,   476,   477,   478,   479,   480,   481,   482,   483,
     226,   227,    87,   487,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   247,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,   167,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,   358,    -1,
      87,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   216,   358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   226,   227,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   247,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
     167,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     177,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,   310,   167,   487,    -1,   216,
      -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,   226,
     227,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
     247,   487,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   177,   358,    87,   216,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,   247,    -1,    -1,    -1,
      -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   226,   227,   310,   167,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   167,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,   310,
      87,   358,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,    -1,   487,   216,   247,   310,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   226,   227,    -1,    -1,   358,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     167,    -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,    -1,
     177,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,   310,    -1,   216,
     487,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,
     227,    -1,    -1,    -1,    -1,   358,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
     247,    -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,
     481,   482,   483,    -1,    -1,   358,   487,    -1,    -1,    -1,
      -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,    -1,   487,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   310,    -1,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   167,   476,   477,   478,   479,   480,   481,   482,
     483,   358,   177,    -1,   487,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    34,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,    44,    -1,    -1,   487,   167,    -1,    -1,    -1,    -1,
      -1,   216,    -1,    -1,    -1,   177,    -1,    87,    -1,    -1,
      -1,   226,   227,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,   247,    -1,    -1,    -1,    -1,    90,    91,    -1,
      -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,   226,   227,    -1,    -1,    -1,    -1,
      -1,    -1,   115,    -1,    -1,   118,   119,    -1,   121,    -1,
      -1,    -1,   125,    34,    -1,   247,    -1,   130,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,   167,    -1,    -1,
     487,    -1,    -1,    87,    -1,   310,    -1,   177,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   161,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,
      91,    -1,    -1,    -1,    -1,    -1,   216,    -1,   310,    -1,
      -1,    -1,    -1,   358,   105,   106,   226,   227,   109,   202,
      -1,    -1,    -1,    -1,   207,    -1,    -1,   118,   119,    -1,
     121,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,
      -1,    -1,    -1,   167,    -1,   228,    -1,    -1,    -1,   232,
      -1,    -1,    -1,   177,    -1,    -1,   358,    -1,   241,   242,
     243,    -1,    -1,    -1,    -1,    -1,   249,    -1,    -1,    -1,
     161,    -1,    -1,    -1,   257,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     310,   284,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   202,    -1,   296,    -1,    -1,   207,    -1,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   476,   477,   478,   479,   480,   481,   482,   483,    -1,
      -1,   232,   487,    -1,    -1,    -1,    -1,    -1,   358,    -1,
     241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   257,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   476,   477,   478,   479,   480,   481,
     482,   483,    -1,    -1,    -1,   487,   310,    -1,    -1,    -1,
      -1,    -1,    -1,   284,    -1,    -1,    -1,    -1,    -1,   382,
      -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   404,    -1,    -1,    -1,    -1,   317,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   358,   418,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   428,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,    -1,    -1,   487,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   382,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   404,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   428,    -1,    -1,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,
      -1,    -1,   476,   477,   478,   479,   480,   481,   482,   483,
      -1,    25,    -1,   487,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,    43,
      -1,    45,    46,    47,    48,    49,    -1,    51,    -1,    -1,
      54,    -1,    56,    -1,    -1,    59,    -1,    -1,    62,    63,
      64,    65,    66,    67,    -1,    -1,    70,    71,    72,    73,
      -1,    -1,    76,    -1,    78,    79,    80,    -1,    82,    -1,
      84,    85,    -1,    -1,    -1,    -1,    90,    91,    92,    93,
      -1,    95,    96,    97,    -1,    99,    -1,   101,   102,    -1,
      -1,   105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,
      -1,    -1,    -1,    -1,   118,    -1,    -1,   121,    -1,    -1,
     124,   125,   126,    -1,   128,   129,   130,    -1,    -1,   133,
     134,    -1,   136,    -1,   138,   139,   140,    -1,    -1,    -1,
      -1,   145,    -1,   147,    -1,   149,    -1,    -1,    -1,   153,
      -1,    -1,   156,   157,   158,    -1,   160,    -1,   162,    -1,
      -1,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,
     174,   175,    -1,    -1,    -1,   179,    -1,   181,    -1,    -1,
      -1,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,    -1,   202,   203,
     204,   205,   206,   207,   208,   209,    -1,   211,   212,   213,
      -1,   215,    -1,   217,    -1,    -1,   220,    -1,   222,   223,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,   232,   233,
      -1,    -1,   236,   237,   238,   239,   240,   241,   242,   243,
      -1,    -1,    -1,    -1,   248,    -1,   250,    -1,   252,   253,
      -1,    -1,   256,   257,   258,   259,    -1,    -1,   262,   263,
     264,   265,   266,    -1,    -1,    -1,   270,   271,    -1,   273,
      -1,    -1,   276,   277,    -1,    -1,    -1,    -1,   282,    -1,
     284,   285,    -1,    -1,    -1,    -1,   290,    -1,   292,   293,
      -1,   295,    -1,    -1,    -1,   299,    -1,    -1,   302,    -1,
     304,    -1,    -1,    -1,    -1,   309,    -1,   311,   312,   313,
     314,    -1,    -1,    -1,   318,    -1,   320,   321,    -1,    -1,
     324,   325,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   337,   338,   339,    -1,   341,    -1,   343,
     344,   345,   346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     394,    -1,    -1,   397,    -1,    -1,    -1,   401,   402,    -1,
     404,    -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,   413,
      -1,    -1,   416,   417,   418,   419,    -1,    -1,    -1,   423,
     424,   425,    -1,   427,   428,    -1,   430,    -1,   432,    -1,
      -1,    -1,    -1,    -1,    -1,   439,    -1,   441,   442,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     454,    -1,    -1,    -1,    -1,    -1,   460,    -1,   462,    -1,
      -1,   465,    -1,    -1,   468,    -1,   470,    -1,   472,   473,
     474,     4,     5,     6,     7,     8,   480,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,
      43,    -1,    45,    46,    47,    48,    49,    -1,    51,    -1,
      -1,    54,    -1,    56,    -1,    -1,    59,    -1,    -1,    62,
      63,    64,    65,    66,    67,    -1,    -1,    70,    71,    72,
      73,    -1,    -1,    76,    -1,    78,    79,    80,    -1,    82,
      -1,    84,    85,    -1,    -1,    -1,    -1,    90,    91,    92,
      93,    -1,    95,    96,    97,    -1,    99,    -1,   101,   102,
      -1,    -1,   105,   106,    -1,   108,    -1,   110,    -1,    -1,
     113,    -1,    -1,    -1,    -1,   118,    -1,    -1,   121,    -1,
      -1,   124,   125,   126,    -1,   128,   129,   130,    -1,    -1,
     133,   134,    -1,   136,    -1,   138,   139,   140,    -1,    -1,
      -1,    -1,   145,    -1,   147,    -1,   149,    -1,    -1,    -1,
     153,    -1,    -1,   156,   157,   158,    -1,   160,    -1,   162,
      -1,    -1,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,
      -1,   174,   175,    -1,    -1,    -1,   179,    -1,   181,    -1,
      -1,    -1,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,    -1,   202,
     203,   204,   205,   206,   207,   208,   209,    -1,   211,   212,
     213,    -1,   215,    -1,   217,    -1,    -1,   220,    -1,   222,
     223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,   232,
     233,    -1,    -1,   236,   237,   238,   239,   240,   241,   242,
     243,    -1,    -1,    -1,    -1,   248,    -1,   250,    -1,   252,
     253,    -1,    -1,   256,   257,   258,   259,    -1,    -1,   262,
     263,   264,   265,   266,    -1,    -1,    -1,   270,   271,    -1,
     273,    -1,    -1,   276,   277,    -1,    -1,    -1,    -1,   282,
      -1,   284,   285,    -1,    -1,    -1,    -1,   290,    -1,   292,
     293,    -1,   295,    -1,    -1,    -1,   299,    -1,    -1,   302,
      -1,   304,    -1,    -1,    -1,    -1,   309,    -1,   311,   312,
     313,   314,    -1,    -1,    -1,   318,    -1,   320,   321,    -1,
      -1,   324,   325,    -1,   327,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   337,   338,   339,    -1,   341,    -1,
     343,   344,   345,   346,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,   382,
     383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   394,    -1,    -1,   397,    -1,    -1,    -1,   401,   402,
      -1,   404,    -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,
     413,    -1,    -1,   416,   417,   418,   419,    -1,    -1,    -1,
     423,   424,   425,    -1,   427,   428,    -1,   430,    -1,   432,
      -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,   441,   442,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   454,    -1,    -1,    -1,    -1,    -1,   460,    -1,   462,
      -1,    -1,   465,    -1,    -1,   468,    -1,   470,    -1,   472,
     473,   474,     4,     5,     6,     7,     8,   480,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    28,    29,    30,    31,
      -1,    33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,
      -1,    43,    -1,    45,    46,    47,    48,    49,    -1,    51,
      -1,    -1,    54,    -1,    56,    -1,    -1,    59,    -1,    -1,
      62,    63,    64,    65,    66,    67,    -1,    -1,    70,    71,
      72,    73,    -1,    -1,    76,    -1,    78,    79,    80,    -1,
      82,    -1,    84,    85,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    -1,    95,    96,    97,    -1,    99,    -1,   101,
     102,    -1,    -1,   105,   106,    -1,   108,    -1,   110,    -1,
      -1,   113,    -1,    -1,    -1,    -1,   118,    -1,    -1,   121,
      -1,    -1,   124,   125,   126,    -1,   128,   129,   130,    -1,
      -1,   133,   134,    -1,   136,    -1,   138,   139,   140,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,    -1,    -1,
      -1,   153,    -1,    -1,   156,   157,   158,    -1,   160,    -1,
     162,    -1,    -1,   165,    -1,    -1,   168,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,    -1,   181,
      -1,    -1,    -1,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,    -1,
     202,   203,   204,   205,   206,   207,   208,   209,    -1,   211,
     212,   213,    -1,   215,    -1,   217,    -1,    -1,   220,    -1,
     222,   223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,
     232,   233,    -1,    -1,   236,   237,   238,   239,   240,   241,
     242,   243,    -1,    -1,    -1,    -1,   248,    -1,   250,    -1,
     252,   253,    -1,    -1,   256,   257,   258,   259,    -1,    -1,
     262,   263,   264,   265,   266,    -1,    -1,    -1,   270,   271,
      -1,   273,    -1,    -1,   276,   277,    -1,    -1,    -1,    -1,
     282,    -1,   284,   285,    -1,    -1,    -1,    -1,   290,    -1,
     292,   293,    -1,   295,    -1,    -1,    -1,   299,    -1,    -1,
     302,    -1,   304,    -1,    -1,    -1,    -1,   309,    -1,   311,
     312,   313,   314,    -1,    -1,    -1,   318,    -1,   320,   321,
      -1,    -1,   324,   325,    -1,   327,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   337,   338,   339,    -1,   341,
      -1,   343,   344,   345,   346,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,
     382,   383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   394,    -1,    -1,   397,    -1,    -1,    -1,   401,
     402,    -1,   404,    -1,    -1,    -1,    -1,   409,    -1,    -1,
      -1,   413,    -1,    -1,   416,   417,   418,   419,    -1,    -1,
      -1,   423,   424,   425,    -1,   427,   428,    -1,   430,    -1,
     432,    -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,   441,
     442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   454,    -1,    -1,    -1,    -1,    -1,   460,    -1,
     462,    -1,    -1,   465,    -1,    -1,   468,    -1,   470,    -1,
     472,   473,   474,     4,     5,     6,     7,     8,   480,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    -1,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    -1,    -1,    -1,    40,
      -1,    -1,    43,    -1,    45,    46,    47,    48,    49,    -1,
      51,    -1,    -1,    54,    -1,    56,    -1,    -1,    59,    -1,
      -1,    62,    63,    64,    65,    66,    67,    -1,    -1,    70,
      71,    72,    73,    -1,    -1,    76,    -1,    78,    79,    80,
      -1,    82,    -1,    84,    85,    -1,    -1,    -1,    -1,    90,
      91,    92,    93,    -1,    95,    96,    97,    -1,    99,    -1,
     101,   102,    -1,    -1,   105,   106,    -1,   108,    -1,   110,
      -1,    -1,   113,    -1,    -1,    -1,    -1,   118,    -1,    -1,
     121,    -1,    -1,   124,   125,   126,    -1,   128,   129,   130,
      -1,    -1,   133,   134,    -1,   136,    -1,   138,   139,   140,
      -1,    -1,    -1,    -1,   145,    -1,   147,    -1,   149,    -1,
      -1,    -1,   153,    -1,    -1,   156,   157,   158,    -1,   160,
      -1,   162,    -1,    -1,   165,    -1,    -1,   168,    -1,    -1,
      -1,    -1,    -1,   174,   175,    -1,    -1,    -1,   179,    -1,
     181,    -1,    -1,    -1,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
      -1,   202,   203,   204,   205,   206,   207,   208,   209,    -1,
     211,   212,   213,    -1,   215,    -1,   217,    -1,    -1,   220,
      -1,   222,   223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     231,   232,   233,    -1,    -1,   236,   237,   238,   239,   240,
     241,   242,   243,    -1,    -1,    -1,    -1,   248,    -1,   250,
      -1,   252,   253,    -1,    -1,   256,   257,   258,   259,    -1,
      -1,   262,   263,   264,   265,   266,    -1,    -1,    -1,   270,
     271,    -1,   273,    -1,    -1,   276,   277,    -1,    -1,    -1,
      -1,   282,    -1,   284,   285,    -1,    -1,    -1,    -1,   290,
      -1,   292,   293,    -1,   295,    -1,    -1,    -1,   299,    -1,
      -1,   302,    -1,   304,    -1,    -1,    -1,    -1,   309,    -1,
     311,   312,   313,   314,    -1,    -1,    -1,   318,    -1,   320,
     321,    -1,    -1,   324,   325,    -1,   327,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   337,   338,   339,    -1,
     341,    -1,   343,   344,   345,   346,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   356,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,
      -1,   382,   383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   394,    -1,    -1,   397,    -1,    -1,    -1,
     401,   402,    -1,   404,    -1,    -1,    -1,    -1,   409,    -1,
      -1,    -1,   413,    -1,    -1,   416,   417,   418,   419,    -1,
      -1,    -1,   423,   424,   425,    -1,   427,   428,    -1,   430,
      -1,   432,    -1,    -1,    87,    -1,    -1,    -1,   439,    -1,
     441,   442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   454,    -1,    -1,    -1,    -1,    -1,   460,
      -1,   462,    -1,    -1,   465,    -1,    -1,   468,    -1,   470,
      -1,   472,   473,   474,    -1,    -1,    -1,    -1,    -1,   480,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   167,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    87,    88,
      -1,    -1,    -1,   226,   227,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,   167,    -1,
      -1,    -1,    -1,    87,    -1,    -1,    -1,   310,   177,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   144,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    87,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
     167,    -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,    -1,
     177,    -1,    -1,    -1,    -1,   358,    -1,   226,   227,    87,
     144,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   371,   372,
     373,   374,   375,    -1,    -1,    -1,    -1,    -1,   247,    -1,
      -1,    -1,   144,   167,    -1,    -1,    -1,    -1,    -1,   216,
      -1,    -1,    -1,   177,    -1,   398,   399,   400,   401,   226,
     227,    -1,    -1,    -1,    87,   167,    -1,    -1,    -1,    -1,
     413,   414,   415,   416,    -1,   177,   419,    -1,    -1,    -1,
     247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   216,    -1,    -1,    -1,   439,   440,    -1,   167,
      -1,   310,   226,   227,    -1,    -1,    -1,    -1,    -1,   177,
      -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,   461,   462,
      -1,    -1,    -1,   247,   226,   227,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,    -1,    -1,   310,   167,   247,    -1,    -1,   216,   358,
      -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,   226,   227,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,   247,
      -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,    -1,
      -1,   358,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   226,   227,    -1,    -1,    -1,   310,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,   306,    -1,
      -1,    -1,   310,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,
     479,   480,   481,   482,   483,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   310,    -1,    -1,
     358,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,    -1,    -1,    -1,
      -1,    -1,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   177,    -1,   358,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,   476,   477,   478,   479,   480,   481,   482,   483,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    87,   216,    -1,   476,   477,   478,   479,   480,   481,
     482,   483,   226,   227,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,   476,   477,
     478,   479,   480,   481,   482,   483,    -1,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   466,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   167,    -1,   476,   477,   478,   479,   480,   481,   482,
     483,   177,    -1,    87,    -1,    -1,   310,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   167,    -1,    -1,
     216,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,
     226,   227,    -1,    -1,   358,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   167,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    87,    -1,   177,    -1,    -1,   226,   227,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,   216,    87,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   466,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   167,   476,   477,   478,   479,   480,   481,   482,   483,
     310,   177,   358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,   167,    -1,    -1,    -1,    -1,    -1,    -1,
     216,    -1,    -1,   177,    -1,    -1,   310,    -1,   358,    -1,
     226,   227,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,   227,   358,    -1,    -1,   167,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
      87,    -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,   227,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,    -1,   310,   247,   167,    -1,
      -1,    -1,   358,    -1,    -1,    -1,    -1,    -1,   177,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     167,    -1,   476,   477,   478,   479,   480,   481,   482,   483,
     177,    -1,    -1,    -1,   358,    -1,    -1,   216,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,   227,    -1,
     310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,   216,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,
     227,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,
     247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     476,   477,   478,   479,   480,   481,   482,   483,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   476,   477,   478,   479,   480,   481,   482,   483,
      -1,    -1,    -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   358,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   358,    -1,    -1,    -1,    -1,   476,   477,   478,   479,
     480,   481,   482,   483,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   476,   477,   478,
     479,   480,   481,   482,   483,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,   476,
     477,   478,   479,   480,   481,   482,   483,    25,    -1,    -1,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    40,    -1,    -1,    43,    -1,    45,    46,    47,
      48,    49,    -1,    51,    -1,    -1,    54,    -1,    56,    -1,
      -1,    59,    -1,    -1,    62,    63,    64,    65,    66,    67,
      -1,    -1,    70,    71,    72,    73,    -1,    -1,    76,    -1,
      78,    79,    80,    -1,    82,    -1,    84,    85,    -1,    -1,
      -1,    -1,    90,    91,    92,    93,    94,    95,    96,    97,
      -1,    99,    -1,   101,   102,    -1,    -1,   105,   106,    -1,
     108,    -1,   110,    -1,    -1,   113,    -1,    -1,    -1,    -1,
     118,   119,    -1,   121,    -1,    -1,   124,   125,   126,    -1,
     128,   129,   130,    -1,    -1,   133,   134,    -1,   136,    -1,
     138,   139,   140,    -1,    -1,    -1,    -1,   145,    -1,   147,
      -1,   149,    -1,    -1,    -1,   153,    -1,    -1,   156,   157,
     158,    -1,   160,    -1,   162,    -1,    -1,   165,    -1,    -1,
     168,    -1,    -1,    -1,    -1,    -1,   174,   175,   176,    -1,
      -1,   179,    -1,   181,    -1,    -1,    -1,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,    -1,   202,   203,   204,   205,   206,   207,
     208,   209,    -1,   211,   212,   213,    -1,   215,    -1,   217,
      -1,    -1,   220,    -1,   222,   223,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   231,   232,   233,    -1,    -1,   236,   237,
     238,   239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,
     248,    -1,   250,    -1,   252,   253,    -1,    -1,   256,   257,
     258,   259,    -1,    -1,   262,   263,   264,   265,   266,    -1,
      -1,    -1,   270,   271,    -1,   273,    -1,    -1,   276,   277,
      -1,   279,    -1,    -1,   282,    -1,   284,   285,    -1,    -1,
      -1,    -1,   290,    -1,   292,   293,    -1,   295,    -1,    -1,
      -1,   299,    -1,    -1,   302,    -1,   304,    -1,    -1,    -1,
      -1,   309,    -1,   311,   312,   313,   314,    -1,    -1,    -1,
     318,    -1,   320,   321,    -1,    -1,   324,   325,    -1,   327,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,
     338,   339,    -1,   341,    -1,   343,   344,   345,   346,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,    -1,
      -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,    -1,   397,
      -1,    -1,    -1,   401,   402,    -1,   404,    -1,    -1,    -1,
      -1,   409,    -1,    -1,    -1,   413,    -1,    -1,   416,   417,
     418,   419,    -1,    -1,    -1,   423,   424,   425,    -1,   427,
     428,    -1,   430,    -1,   432,    -1,    -1,    -1,    -1,    -1,
      -1,   439,    -1,   441,   442,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   454,     4,     5,     6,
       7,     8,   460,    -1,   462,    12,    -1,   465,    -1,    -1,
     468,    -1,   470,    -1,   472,   473,   474,    -1,    25,    -1,
      -1,    28,    29,    30,    31,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    45,    46,
      47,    48,    49,    -1,    51,    -1,    -1,    54,    -1,    56,
      -1,    -1,    59,    -1,    -1,    62,    63,    64,    65,    66,
      67,    -1,    -1,    70,    71,    72,    73,    -1,    -1,    76,
      -1,    78,    79,    80,    -1,    82,    -1,    84,    85,    -1,
      -1,    -1,    -1,    90,    91,    92,    93,    94,    95,    96,
      97,    -1,    99,    -1,   101,   102,    -1,    -1,   105,   106,
      -1,   108,    -1,   110,    -1,    -1,   113,    -1,    -1,    -1,
      -1,   118,   119,    -1,   121,    -1,    -1,   124,   125,   126,
      -1,   128,   129,   130,    -1,    -1,   133,   134,    -1,   136,
      -1,   138,   139,   140,    -1,    -1,    -1,    -1,   145,    -1,
     147,    -1,   149,    -1,    -1,    -1,   153,    -1,    -1,   156,
     157,   158,    -1,   160,    -1,   162,    -1,    -1,   165,    -1,
      -1,   168,    -1,    -1,    -1,    -1,    -1,   174,   175,   176,
      -1,    -1,   179,    -1,   181,    -1,    -1,    -1,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,    -1,   202,   203,   204,   205,   206,
     207,   208,   209,    -1,   211,   212,   213,    -1,   215,    -1,
     217,    -1,    -1,   220,    -1,   222,   223,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   231,   232,   233,    -1,    -1,   236,
     237,   238,   239,   240,   241,   242,   243,    -1,    -1,    -1,
      -1,   248,    -1,   250,    -1,   252,   253,    -1,    -1,   256,
     257,   258,   259,    -1,    -1,   262,   263,   264,   265,   266,
      -1,    -1,    -1,   270,   271,    -1,   273,    -1,    -1,   276,
     277,    -1,   279,    -1,    -1,   282,    -1,   284,   285,    -1,
      -1,    -1,    -1,   290,    -1,   292,   293,    -1,   295,    -1,
      -1,    -1,   299,    -1,    -1,   302,    -1,   304,    -1,    -1,
      -1,    -1,   309,    -1,   311,   312,   313,   314,    -1,    -1,
      -1,   318,    -1,   320,   321,    -1,    -1,   324,   325,    -1,
     327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     337,   338,   339,    -1,   341,    -1,   343,   344,   345,   346,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,
      -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,    -1,
     397,    -1,    -1,    -1,   401,   402,    -1,   404,    -1,    -1,
      -1,    -1,   409,    -1,    -1,    -1,   413,    -1,    -1,   416,
     417,   418,   419,    -1,    -1,    -1,   423,   424,   425,    -1,
     427,   428,    -1,   430,    -1,   432,    -1,    -1,    -1,    -1,
      -1,    -1,   439,    -1,   441,   442,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,     4,     5,
       6,     7,     8,   460,    -1,   462,    12,    -1,   465,    -1,
      -1,   468,    -1,   470,    -1,   472,   473,   474,    -1,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    33,    34,    35,
      36,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    45,
      46,    47,    48,    49,    -1,    51,    -1,    -1,    54,    -1,
      56,    -1,    -1,    59,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    -1,    70,    71,    72,    73,    -1,    -1,
      76,    -1,    78,    79,    80,    -1,    82,    -1,    84,    85,
      -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,    95,
      96,    97,    -1,    99,    -1,   101,   102,    -1,    -1,   105,
     106,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,    -1,
     116,    -1,   118,    -1,    -1,   121,    -1,    -1,   124,   125,
     126,    -1,   128,   129,   130,    -1,    -1,   133,   134,    -1,
     136,    -1,   138,   139,   140,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,    -1,    -1,    -1,   153,    -1,    -1,
     156,   157,   158,    -1,   160,    -1,   162,    -1,    -1,   165,
      -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,   174,   175,
     176,    -1,    -1,   179,    -1,   181,    -1,    -1,    -1,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,    -1,   202,   203,   204,   205,
     206,   207,   208,   209,    -1,   211,   212,   213,    -1,   215,
      -1,   217,    -1,    -1,   220,    -1,   222,   223,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   231,   232,   233,    -1,    -1,
     236,   237,   238,   239,   240,   241,   242,   243,    -1,    -1,
      -1,    -1,   248,    -1,   250,    -1,   252,   253,    -1,    -1,
     256,   257,   258,   259,    -1,    -1,   262,   263,   264,   265,
     266,    -1,    -1,    -1,   270,   271,    -1,   273,    -1,    -1,
     276,   277,    -1,   279,    -1,    -1,   282,    -1,   284,   285,
      -1,    -1,    -1,    -1,   290,    -1,   292,   293,    -1,   295,
      -1,    -1,    -1,   299,    -1,    -1,   302,    -1,   304,    -1,
      -1,    -1,    -1,   309,    -1,   311,   312,   313,   314,    -1,
      -1,    -1,   318,    -1,   320,   321,    -1,    -1,   324,   325,
      -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   337,   338,   339,    -1,   341,    -1,   343,   344,   345,
     346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,
      -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,
      -1,   397,    -1,    -1,    -1,   401,   402,    -1,   404,    -1,
      -1,    -1,    -1,   409,    -1,    -1,    -1,   413,    -1,    -1,
     416,   417,   418,   419,    -1,    -1,    -1,   423,   424,   425,
      -1,   427,   428,    -1,   430,    -1,   432,    -1,    -1,    -1,
      -1,    -1,    -1,   439,    -1,   441,   442,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,     4,
       5,     6,     7,     8,   460,    -1,   462,    12,    -1,   465,
      -1,    -1,   468,    -1,   470,    -1,   472,   473,   474,    -1,
      25,    -1,    -1,    28,    29,    30,    31,    -1,    33,    34,
      35,    36,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      45,    46,    47,    48,    49,    -1,    51,    -1,    -1,    54,
      -1,    56,    -1,    -1,    59,    -1,    -1,    62,    63,    64,
      65,    66,    67,    -1,    -1,    70,    71,    72,    73,    -1,
      -1,    76,    -1,    78,    79,    80,    -1,    82,    -1,    84,
      85,    -1,    -1,    -1,    -1,    90,    91,    92,    93,    94,
      95,    96,    97,    -1,    99,    -1,   101,   102,    -1,    -1,
     105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,
      -1,    -1,    -1,   118,    -1,    -1,   121,    -1,    -1,   124,
     125,   126,    -1,   128,   129,   130,    -1,    -1,   133,   134,
      -1,   136,    -1,   138,   139,   140,    -1,    -1,    -1,    -1,
     145,    -1,   147,    -1,   149,    -1,    -1,    -1,   153,    -1,
      -1,   156,   157,   158,    -1,   160,    -1,   162,    -1,    -1,
     165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,   174,
     175,   176,    -1,    -1,   179,    -1,   181,    -1,    -1,    -1,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,    -1,   202,   203,   204,
     205,   206,   207,   208,   209,    -1,   211,   212,   213,    -1,
     215,    -1,   217,    -1,    -1,   220,    -1,   222,   223,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   231,   232,   233,    -1,
      -1,   236,   237,   238,   239,   240,   241,   242,   243,    -1,
      -1,    -1,    -1,   248,    -1,   250,    -1,   252,   253,    -1,
      -1,   256,   257,   258,   259,    -1,    -1,   262,   263,   264,
     265,   266,    -1,    -1,    -1,   270,   271,    -1,   273,    -1,
      -1,   276,   277,    -1,   279,    -1,    -1,   282,    -1,   284,
     285,    -1,    -1,    -1,    -1,   290,    -1,   292,   293,    -1,
     295,    -1,    -1,    -1,   299,    -1,    -1,   302,    -1,   304,
      -1,    -1,    -1,    -1,   309,    -1,   311,   312,   313,   314,
      -1,    -1,    -1,   318,    -1,   320,   321,    -1,    -1,   324,
     325,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   337,   338,   339,    -1,   341,    -1,   343,   344,
     345,   346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     375,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,
      -1,    -1,   397,    -1,    -1,    -1,   401,   402,    -1,   404,
      -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,   413,    -1,
      -1,   416,   417,   418,   419,    -1,    -1,    -1,   423,   424,
     425,    -1,   427,   428,    -1,   430,    -1,   432,    -1,    -1,
      -1,    -1,    -1,    -1,   439,    -1,   441,   442,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,
       4,     5,     6,     7,     8,   460,    -1,   462,    12,    -1,
     465,    -1,    -1,   468,    -1,   470,    -1,   472,   473,   474,
      -1,    25,    -1,    -1,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,    43,
      -1,    45,    46,    47,    48,    49,    -1,    51,    -1,    -1,
      54,    -1,    56,    -1,    -1,    59,    -1,    -1,    62,    63,
      64,    65,    66,    67,    -1,    -1,    70,    71,    72,    73,
      -1,    -1,    76,    -1,    78,    79,    80,    -1,    82,    -1,
      84,    85,    -1,    -1,    -1,    -1,    90,    91,    92,    93,
      -1,    95,    96,    97,    -1,    99,    -1,   101,   102,    -1,
      -1,   105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,
      -1,    -1,    -1,    -1,   118,   119,    -1,   121,    -1,    -1,
     124,   125,   126,    -1,   128,   129,   130,    -1,    -1,   133,
     134,    -1,   136,    -1,   138,   139,   140,    -1,    -1,    -1,
      -1,   145,    -1,   147,    -1,   149,    -1,    -1,    -1,   153,
      -1,    -1,   156,   157,   158,    -1,   160,    -1,   162,    -1,
      -1,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,
     174,   175,   176,    -1,    -1,   179,    -1,   181,    -1,    -1,
      -1,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,    -1,   202,   203,
     204,   205,   206,   207,   208,   209,    -1,   211,   212,   213,
      -1,   215,    -1,   217,    -1,    -1,   220,    -1,   222,   223,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,   232,   233,
      -1,    -1,   236,   237,   238,   239,   240,   241,   242,   243,
      -1,    -1,    -1,    -1,   248,    -1,   250,    -1,   252,   253,
      -1,    -1,   256,   257,   258,   259,    -1,    -1,   262,   263,
     264,   265,   266,    -1,    -1,    -1,   270,   271,    -1,   273,
      -1,    -1,   276,   277,    -1,   279,    -1,    -1,   282,    -1,
     284,   285,    -1,    -1,    -1,    -1,   290,    -1,   292,   293,
      -1,   295,    -1,    -1,    -1,   299,    -1,    -1,   302,    -1,
     304,    -1,    -1,    -1,    -1,   309,    -1,   311,   312,   313,
     314,    -1,    -1,    -1,   318,    -1,   320,   321,    -1,    -1,
     324,   325,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   337,   338,   339,    -1,   341,    -1,   343,
     344,   345,   346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     394,    -1,    -1,   397,    -1,    -1,    -1,   401,   402,    -1,
     404,    -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,   413,
      -1,    -1,   416,   417,   418,   419,    -1,    -1,    -1,   423,
     424,   425,    -1,   427,   428,    -1,   430,    -1,   432,    -1,
      -1,    -1,    -1,    -1,    -1,   439,    -1,   441,   442,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     454,     4,     5,     6,     7,     8,   460,    -1,   462,    12,
      -1,   465,    -1,    -1,   468,    -1,   470,    -1,   472,   473,
     474,    -1,    25,    -1,    -1,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,
      43,    -1,    45,    46,    47,    48,    49,    -1,    51,    -1,
      -1,    54,    -1,    56,    -1,    -1,    59,    -1,    -1,    62,
      63,    64,    65,    66,    67,    -1,    -1,    70,    71,    72,
      73,    -1,    -1,    76,    -1,    78,    79,    80,    -1,    82,
      -1,    84,    85,    -1,    -1,    -1,    -1,    90,    91,    92,
      93,    -1,    95,    96,    97,    -1,    99,    -1,   101,   102,
      -1,    -1,   105,   106,    -1,   108,    -1,   110,    -1,    -1,
     113,    -1,    -1,    -1,    -1,   118,    -1,    -1,   121,    -1,
      -1,   124,   125,   126,    -1,   128,   129,   130,    -1,    -1,
     133,   134,    -1,   136,    -1,   138,   139,   140,    -1,    -1,
      -1,    -1,   145,    -1,   147,    -1,   149,    -1,    -1,    -1,
     153,    -1,    -1,   156,   157,   158,    -1,   160,    -1,   162,
      -1,    -1,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,
      -1,   174,   175,   176,    -1,    -1,   179,    -1,   181,    -1,
      -1,    -1,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,    -1,   202,
     203,   204,   205,   206,   207,   208,   209,    -1,   211,   212,
     213,    -1,   215,    -1,   217,    -1,    -1,   220,    -1,   222,
     223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,   232,
     233,    -1,    -1,   236,   237,   238,   239,   240,   241,   242,
     243,    -1,    -1,    -1,    -1,   248,    -1,   250,    -1,   252,
     253,    -1,    -1,   256,   257,   258,   259,    -1,    -1,   262,
     263,   264,   265,   266,    -1,    -1,    -1,   270,   271,    -1,
     273,    -1,    -1,   276,   277,    -1,   279,    -1,    -1,   282,
      -1,   284,   285,    -1,    -1,    -1,    -1,   290,    -1,   292,
     293,    -1,   295,    -1,    -1,    -1,   299,    -1,    -1,   302,
      -1,   304,    -1,    -1,    -1,    -1,   309,    -1,   311,   312,
     313,   314,    -1,    -1,    -1,   318,    -1,   320,   321,    -1,
      -1,   324,   325,    -1,   327,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   337,   338,   339,    -1,   341,    -1,
     343,   344,   345,   346,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,   382,
     383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   394,    -1,    -1,   397,    -1,    -1,    -1,   401,   402,
      -1,   404,    -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,
     413,    -1,    -1,   416,   417,   418,   419,    -1,    -1,    -1,
     423,   424,   425,    -1,   427,   428,    -1,   430,    -1,   432,
      -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,   441,   442,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   454,     4,     5,     6,     7,     8,   460,    -1,   462,
      12,    -1,   465,    -1,    -1,   468,    -1,   470,    -1,   472,
     473,   474,    -1,    25,    -1,    -1,    28,    29,    30,    31,
      -1,    33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,
      -1,    43,    -1,    45,    46,    47,    48,    49,    -1,    51,
      -1,    -1,    54,    -1,    56,    -1,    -1,    59,    -1,    -1,
      62,    63,    64,    65,    66,    67,    -1,    -1,    70,    71,
      72,    73,    -1,    -1,    76,    -1,    78,    79,    80,    -1,
      82,    -1,    84,    85,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    -1,    95,    96,    97,    -1,    99,    -1,   101,
     102,    -1,    -1,   105,   106,    -1,   108,    -1,   110,    -1,
      -1,   113,    -1,    -1,    -1,    -1,   118,    -1,    -1,   121,
      -1,    -1,   124,   125,   126,    -1,   128,   129,   130,    -1,
      -1,   133,   134,    -1,   136,    -1,   138,   139,   140,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,    -1,    -1,
      -1,   153,   154,    -1,   156,   157,   158,    -1,   160,    -1,
     162,    -1,    -1,   165,    -1,    -1,   168,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,    -1,   181,
      -1,    -1,    -1,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,    -1,
     202,   203,   204,   205,   206,   207,   208,   209,    -1,   211,
     212,   213,    -1,   215,    -1,   217,    -1,    -1,   220,    -1,
     222,   223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,
     232,   233,    -1,    -1,   236,   237,   238,   239,   240,   241,
     242,   243,    -1,    -1,    -1,    -1,   248,    -1,   250,    -1,
     252,   253,    -1,    -1,   256,   257,   258,   259,    -1,    -1,
     262,   263,   264,   265,   266,    -1,    -1,    -1,   270,   271,
      -1,   273,    -1,    -1,   276,   277,    -1,   279,    -1,    -1,
     282,    -1,   284,   285,    -1,    -1,    -1,    -1,   290,    -1,
     292,   293,    -1,   295,    -1,    -1,    -1,   299,    -1,    -1,
     302,    -1,   304,    -1,    -1,    -1,    -1,   309,    -1,   311,
     312,   313,   314,    -1,    -1,    -1,   318,    -1,   320,   321,
      -1,    -1,   324,   325,    -1,   327,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   337,   338,   339,    -1,   341,
      -1,   343,   344,   345,   346,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,
     382,   383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   394,    -1,    -1,   397,    -1,    -1,    -1,   401,
     402,    -1,   404,    -1,    -1,    -1,    -1,   409,    -1,    -1,
      -1,   413,    -1,    -1,   416,   417,   418,   419,    -1,    -1,
      -1,   423,   424,   425,    -1,   427,   428,    -1,   430,    -1,
     432,    -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,   441,
     442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   454,     4,     5,     6,     7,     8,   460,    -1,
     462,    12,    -1,   465,    -1,    -1,   468,    -1,   470,    -1,
     472,   473,   474,    -1,    25,    -1,    -1,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    -1,    -1,    -1,    40,
      -1,    -1,    43,    -1,    45,    46,    47,    48,    49,    -1,
      51,    -1,    -1,    54,    -1,    56,    -1,    -1,    59,    -1,
      -1,    62,    63,    64,    65,    66,    67,    -1,    -1,    70,
      71,    72,    73,    -1,    -1,    76,    -1,    78,    79,    80,
      -1,    82,    -1,    84,    85,    -1,    -1,    88,    -1,    90,
      91,    92,    93,    -1,    95,    96,    97,    -1,    99,    -1,
     101,   102,    -1,    -1,   105,   106,    -1,   108,    -1,   110,
      -1,    -1,   113,    -1,    -1,    -1,    -1,   118,    -1,    -1,
     121,    -1,    -1,   124,   125,   126,    -1,   128,   129,   130,
      -1,    -1,   133,   134,    -1,   136,    -1,   138,   139,   140,
      -1,    -1,    -1,    -1,   145,    -1,   147,    -1,   149,    -1,
      -1,    -1,   153,    -1,    -1,   156,   157,   158,    -1,   160,
      -1,   162,    -1,    -1,   165,    -1,    -1,   168,    -1,    -1,
      -1,    -1,    -1,   174,   175,    -1,    -1,    -1,   179,    -1,
     181,    -1,    -1,    -1,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
      -1,   202,   203,   204,   205,   206,   207,   208,   209,    -1,
     211,   212,   213,    -1,   215,    -1,   217,    -1,    -1,   220,
      -1,   222,   223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     231,   232,   233,    -1,    -1,   236,   237,   238,   239,   240,
     241,   242,   243,    -1,    -1,    -1,    -1,   248,    -1,   250,
      -1,   252,   253,    -1,    -1,   256,   257,   258,   259,    -1,
      -1,   262,   263,   264,   265,   266,    -1,    -1,    -1,   270,
     271,    -1,   273,    -1,    -1,   276,   277,    -1,   279,    -1,
      -1,   282,    -1,   284,   285,    -1,    -1,    -1,    -1,   290,
      -1,   292,   293,    -1,   295,    -1,    -1,    -1,   299,    -1,
      -1,   302,    -1,   304,    -1,    -1,    -1,    -1,   309,    -1,
     311,   312,   313,   314,    -1,    -1,    -1,   318,    -1,   320,
     321,    -1,    -1,   324,   325,    -1,   327,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   337,   338,   339,    -1,
     341,    -1,   343,   344,   345,   346,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   356,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,
      -1,   382,   383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   394,    -1,    -1,   397,    -1,    -1,    -1,
     401,   402,    -1,   404,    -1,    -1,    -1,    -1,   409,    -1,
      -1,    -1,   413,    -1,    -1,   416,   417,   418,   419,    -1,
      -1,    -1,   423,   424,   425,    -1,   427,   428,    -1,   430,
      -1,   432,    -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,
     441,   442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   454,     4,     5,     6,     7,     8,   460,
      -1,   462,    12,    -1,   465,    -1,    -1,   468,    -1,   470,
      -1,   472,   473,   474,    -1,    25,    -1,    -1,    28,    29,
      30,    31,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      40,    -1,    -1,    43,    -1,    45,    46,    47,    48,    49,
      -1,    51,    -1,    -1,    54,    -1,    56,    -1,    -1,    59,
      -1,    -1,    62,    63,    64,    65,    66,    67,    -1,    -1,
      70,    71,    72,    73,    -1,    -1,    76,    -1,    78,    79,
      80,    -1,    82,    -1,    84,    85,    -1,    -1,    -1,    -1,
      90,    91,    92,    93,    -1,    95,    96,    97,    -1,    99,
      -1,   101,   102,    -1,    -1,   105,   106,    -1,   108,    -1,
     110,    -1,    -1,   113,    -1,    -1,    -1,    -1,   118,    -1,
      -1,   121,    -1,    -1,   124,   125,   126,    -1,   128,   129,
     130,    -1,    -1,   133,   134,    -1,   136,    -1,   138,   139,
     140,    -1,    -1,    -1,   144,   145,    -1,   147,    -1,   149,
      -1,    -1,    -1,   153,    -1,    -1,   156,   157,   158,    -1,
     160,    -1,   162,    -1,    -1,   165,    -1,    -1,   168,    -1,
      -1,    -1,    -1,    -1,   174,   175,    -1,    -1,    -1,   179,
      -1,   181,    -1,    -1,    -1,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,    -1,   202,   203,   204,   205,   206,   207,   208,   209,
      -1,   211,   212,   213,    -1,   215,    -1,   217,    -1,    -1,
     220,    -1,   222,   223,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   231,   232,   233,    -1,    -1,   236,   237,   238,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,   248,    -1,
     250,    -1,   252,   253,    -1,    -1,   256,   257,   258,   259,
      -1,    -1,   262,   263,   264,   265,   266,    -1,    -1,    -1,
     270,   271,    -1,   273,    -1,    -1,   276,   277,    -1,    -1,
      -1,    -1,   282,    -1,   284,   285,    -1,    -1,    -1,    -1,
     290,    -1,   292,   293,    -1,   295,    -1,    -1,    -1,   299,
      -1,    -1,   302,    -1,   304,    -1,    -1,    -1,    -1,   309,
      -1,   311,   312,   313,   314,    -1,    -1,    -1,   318,    -1,
     320,   321,    -1,    -1,   324,   325,    -1,   327,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   338,   339,
      -1,   341,    -1,   343,   344,   345,   346,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   356,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   375,    -1,    -1,    -1,    -1,
      -1,    -1,   382,   383,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   394,    -1,    -1,   397,    -1,    -1,
      -1,   401,   402,    -1,   404,    -1,    -1,    -1,    -1,   409,
      -1,    -1,    -1,   413,    -1,    -1,   416,   417,   418,   419,
      -1,    -1,    -1,   423,   424,   425,    -1,   427,   428,    -1,
     430,    -1,   432,    -1,    -1,    -1,    -1,    -1,    -1,   439,
      -1,   441,   442,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   454,     4,     5,     6,     7,     8,
     460,    -1,   462,    12,    -1,   465,    -1,    -1,   468,    -1,
     470,    -1,   472,   473,   474,    -1,    25,    -1,    -1,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    -1,    -1,
      -1,    40,    -1,    -1,    43,    -1,    45,    46,    47,    48,
      49,    -1,    51,    -1,    -1,    54,    -1,    56,    -1,    -1,
      59,    -1,    -1,    62,    63,    64,    65,    66,    67,    -1,
      -1,    70,    71,    72,    73,    -1,    -1,    76,    -1,    78,
      79,    80,    -1,    82,    -1,    84,    85,    -1,    -1,    -1,
      -1,    90,    91,    92,    93,    -1,    95,    96,    97,    -1,
      99,    -1,   101,   102,    -1,    -1,   105,   106,    -1,   108,
      -1,   110,    -1,    -1,   113,    -1,    -1,    -1,    -1,   118,
     119,    -1,   121,    -1,    -1,   124,   125,   126,    -1,   128,
     129,   130,    -1,    -1,   133,   134,    -1,   136,    -1,   138,
     139,   140,    -1,    -1,    -1,    -1,   145,    -1,   147,    -1,
     149,    -1,    -1,    -1,   153,    -1,    -1,   156,   157,   158,
      -1,   160,    -1,   162,    -1,    -1,   165,    -1,    -1,   168,
      -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,    -1,
     179,    -1,   181,    -1,    -1,    -1,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,    -1,   202,   203,   204,   205,   206,   207,   208,
     209,    -1,   211,   212,   213,    -1,   215,    -1,   217,    -1,
      -1,   220,    -1,   222,   223,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   231,   232,   233,    -1,    -1,   236,   237,   238,
     239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,   248,
      -1,   250,    -1,   252,   253,    -1,    -1,   256,   257,   258,
     259,    -1,    -1,   262,   263,   264,   265,   266,    -1,    -1,
      -1,   270,   271,    -1,   273,    -1,    -1,   276,   277,    -1,
      -1,    -1,    -1,   282,    -1,   284,   285,    -1,    -1,    -1,
      -1,   290,    -1,   292,   293,    -1,   295,    -1,    -1,    -1,
     299,    -1,    -1,   302,    -1,   304,    -1,    -1,    -1,    -1,
     309,    -1,   311,   312,   313,   314,    -1,    -1,    -1,   318,
      -1,   320,   321,    -1,    -1,   324,   325,    -1,   327,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   338,
     339,    -1,   341,    -1,   343,   344,   345,   346,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,    -1,    -1,
      -1,    -1,    -1,   382,   383,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   394,    -1,    -1,   397,    -1,
      -1,    -1,   401,   402,    -1,   404,    -1,    -1,    -1,    -1,
     409,    -1,    -1,    -1,   413,    -1,    -1,   416,   417,   418,
     419,    -1,    -1,    -1,   423,   424,   425,    -1,   427,   428,
      -1,   430,    -1,   432,    -1,    -1,    -1,    -1,    -1,    -1,
     439,    -1,   441,   442,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   454,     4,     5,     6,     7,
       8,   460,    -1,   462,    12,    -1,   465,    -1,    -1,   468,
      -1,   470,    -1,   472,   473,   474,    -1,    25,    -1,    -1,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    40,    -1,    -1,    43,    -1,    45,    46,    47,
      48,    49,    -1,    51,    -1,    -1,    54,    -1,    56,    -1,
      -1,    59,    -1,    -1,    62,    63,    64,    65,    66,    67,
      -1,    -1,    70,    71,    72,    73,    -1,    -1,    76,    -1,
      78,    79,    80,    -1,    82,    -1,    84,    85,    -1,    -1,
      -1,    -1,    90,    91,    92,    93,    -1,    95,    96,    97,
      -1,    99,    -1,   101,   102,    -1,    -1,   105,   106,    -1,
     108,    -1,   110,    -1,    -1,   113,    -1,    -1,    -1,    -1,
     118,   119,    -1,   121,    -1,    -1,   124,   125,   126,    -1,
     128,   129,   130,    -1,    -1,   133,   134,    -1,   136,    -1,
     138,   139,   140,    -1,    -1,    -1,    -1,   145,    -1,   147,
      -1,   149,    -1,    -1,    -1,   153,    -1,    -1,   156,   157,
     158,    -1,   160,    -1,   162,    -1,    -1,   165,    -1,    -1,
     168,    -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,
      -1,   179,    -1,   181,    -1,    -1,    -1,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,    -1,   202,   203,   204,   205,   206,   207,
     208,   209,    -1,   211,   212,   213,    -1,   215,    -1,   217,
      -1,    -1,   220,    -1,   222,   223,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   231,   232,   233,    -1,    -1,   236,   237,
     238,   239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,
     248,    -1,   250,    -1,   252,   253,    -1,    -1,   256,   257,
     258,   259,    -1,    -1,   262,   263,   264,   265,   266,    -1,
      -1,    -1,   270,   271,    -1,   273,    -1,    -1,   276,   277,
      -1,    -1,    -1,    -1,   282,    -1,   284,   285,    -1,    -1,
      -1,    -1,   290,    -1,   292,   293,    -1,   295,    -1,    -1,
      -1,   299,    -1,    -1,   302,    -1,   304,    -1,    -1,    -1,
      -1,   309,    -1,   311,   312,   313,   314,    -1,    -1,    -1,
     318,    -1,   320,   321,    -1,    -1,   324,   325,    -1,   327,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,
     338,   339,    -1,   341,    -1,   343,   344,   345,   346,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,    -1,
      -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,    -1,   397,
      -1,    -1,    -1,   401,   402,    -1,   404,    -1,    -1,    -1,
      -1,   409,    -1,    -1,    -1,   413,    -1,    -1,   416,   417,
     418,   419,    -1,    -1,    -1,   423,   424,   425,    -1,   427,
     428,    -1,   430,    -1,   432,    -1,    -1,    -1,    -1,    -1,
      -1,   439,    -1,   441,   442,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   454,     4,     5,     6,
       7,     8,   460,    -1,   462,    12,    -1,   465,    -1,    -1,
     468,    -1,   470,    -1,   472,   473,   474,    -1,    25,    -1,
      -1,    28,    29,    30,    31,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    45,    46,
      47,    48,    49,    -1,    51,    -1,    -1,    54,    -1,    56,
      -1,    -1,    59,    -1,    -1,    62,    63,    64,    65,    66,
      67,    -1,    -1,    70,    71,    72,    73,    -1,    -1,    76,
      -1,    78,    79,    80,    -1,    82,    -1,    84,    85,    -1,
      -1,    -1,    -1,    90,    91,    92,    93,    -1,    95,    96,
      97,    -1,    99,    -1,   101,   102,    -1,    -1,   105,   106,
      -1,   108,    -1,   110,    -1,    -1,   113,    -1,    -1,    -1,
      -1,   118,    -1,    -1,   121,    -1,    -1,   124,   125,   126,
      -1,   128,   129,   130,    -1,    -1,   133,   134,    -1,   136,
      -1,   138,   139,   140,    -1,    -1,    -1,    -1,   145,    -1,
     147,    -1,   149,    -1,    -1,    -1,   153,    -1,    -1,   156,
     157,   158,    -1,   160,    -1,   162,    -1,    -1,   165,    -1,
      -1,   168,    -1,    -1,    -1,    -1,    -1,   174,   175,    -1,
      -1,    -1,   179,    -1,   181,    -1,    -1,    -1,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,    -1,   202,   203,   204,   205,   206,
     207,   208,   209,    -1,   211,   212,   213,    -1,   215,    -1,
     217,    -1,    -1,   220,    -1,   222,   223,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   231,   232,   233,   234,    -1,   236,
     237,   238,   239,   240,   241,   242,   243,    -1,    -1,    -1,
      -1,   248,    -1,   250,    -1,   252,   253,    -1,    -1,   256,
     257,   258,   259,    -1,    -1,   262,   263,   264,   265,   266,
      -1,    -1,    -1,   270,   271,    -1,   273,    -1,    -1,   276,
     277,    -1,    -1,    -1,    -1,   282,    -1,   284,   285,    -1,
      -1,    -1,    -1,   290,    -1,   292,   293,    -1,   295,    -1,
      -1,    -1,   299,    -1,    -1,   302,    -1,   304,    -1,    -1,
      -1,    -1,   309,    -1,   311,   312,   313,   314,    -1,    -1,
      -1,   318,    -1,   320,   321,    -1,    -1,   324,   325,    -1,
     327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     337,   338,   339,    -1,   341,    -1,   343,   344,   345,   346,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,    -1,
      -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,    -1,
     397,    -1,    -1,    -1,   401,   402,    -1,   404,    -1,    -1,
      -1,    -1,   409,    -1,    -1,    -1,   413,    -1,    -1,   416,
     417,   418,   419,    -1,    -1,    -1,   423,   424,   425,    -1,
     427,   428,    -1,   430,    -1,   432,    -1,    -1,    -1,    -1,
      -1,    -1,   439,    -1,   441,   442,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,     4,     5,
       6,     7,     8,   460,    -1,   462,    12,    -1,   465,    -1,
      -1,   468,    -1,   470,    -1,   472,   473,   474,    -1,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    33,    34,    35,
      36,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    45,
      46,    47,    48,    49,    -1,    51,    -1,    -1,    54,    -1,
      56,    -1,    -1,    59,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    -1,    70,    71,    72,    73,    -1,    -1,
      76,    -1,    78,    79,    80,    -1,    82,    -1,    84,    85,
      -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,    95,
      96,    97,    -1,    99,    -1,   101,   102,    -1,    -1,   105,
     106,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,    -1,
      -1,    -1,   118,    -1,    -1,   121,    -1,    -1,   124,   125,
     126,    -1,   128,   129,   130,    -1,    -1,   133,   134,    -1,
     136,    -1,   138,   139,   140,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,    -1,    -1,    -1,   153,    -1,    -1,
     156,   157,   158,    -1,   160,    -1,   162,    -1,    -1,   165,
      -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,    -1,   181,    -1,    -1,    -1,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,    -1,   202,   203,   204,   205,
     206,   207,   208,   209,    -1,   211,   212,   213,    -1,   215,
      -1,   217,    -1,    -1,   220,    -1,   222,   223,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   231,   232,   233,    -1,    -1,
     236,   237,   238,   239,   240,   241,   242,   243,    -1,    -1,
      -1,    -1,   248,    -1,   250,    -1,   252,   253,    -1,    -1,
     256,   257,   258,   259,    -1,    -1,   262,   263,   264,   265,
     266,    -1,    -1,    -1,   270,   271,    -1,   273,    -1,    -1,
     276,   277,    -1,   279,    -1,    -1,   282,    -1,   284,   285,
      -1,    -1,    -1,    -1,   290,    -1,   292,   293,    -1,   295,
      -1,    -1,    -1,   299,    -1,    -1,   302,    -1,   304,    -1,
      -1,    -1,    -1,   309,    -1,   311,   312,   313,   314,    -1,
      -1,    -1,   318,    -1,   320,   321,    -1,    -1,   324,   325,
      -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   337,   338,   339,    -1,   341,    -1,   343,   344,   345,
     346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   375,
      -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,
      -1,   397,    -1,    -1,    -1,   401,   402,    -1,   404,    -1,
      -1,    -1,    -1,   409,    -1,    -1,    -1,   413,    -1,    -1,
     416,   417,   418,   419,    -1,    -1,    -1,   423,   424,   425,
      -1,   427,   428,    -1,   430,    -1,   432,    -1,    -1,    -1,
      -1,    -1,    -1,   439,    -1,   441,   442,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,     4,
       5,     6,     7,     8,   460,    -1,   462,    12,    -1,   465,
      -1,    -1,   468,    -1,   470,    -1,   472,   473,   474,    -1,
      25,    -1,    -1,    28,    29,    30,    31,    -1,    33,    34,
      35,    36,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      45,    46,    47,    48,    49,    -1,    51,    -1,    -1,    54,
      -1,    56,    -1,    -1,    59,    -1,    -1,    62,    63,    64,
      65,    66,    67,    -1,    -1,    70,    71,    72,    73,    -1,
      -1,    76,    -1,    78,    79,    80,    -1,    82,    -1,    84,
      85,    -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,
      95,    96,    97,    -1,    99,    -1,   101,   102,    -1,    -1,
     105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,
      -1,    -1,    -1,   118,   119,    -1,   121,    -1,    -1,   124,
     125,   126,    -1,   128,   129,   130,    -1,    -1,   133,   134,
      -1,   136,    -1,   138,   139,   140,    -1,    -1,    -1,    -1,
     145,    -1,   147,    -1,   149,    -1,    -1,    -1,   153,    -1,
      -1,   156,   157,   158,    -1,   160,    -1,   162,    -1,    -1,
     165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,   174,
     175,    -1,    -1,    -1,   179,    -1,   181,    -1,    -1,    -1,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,    -1,   202,   203,   204,
     205,   206,   207,   208,   209,    -1,   211,   212,   213,    -1,
     215,    -1,   217,    -1,    -1,   220,    -1,   222,   223,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   231,   232,   233,    -1,
      -1,   236,   237,   238,   239,   240,   241,   242,   243,    -1,
      -1,    -1,    -1,   248,    -1,   250,    -1,   252,   253,    -1,
      -1,   256,   257,   258,   259,    -1,    -1,   262,   263,   264,
     265,   266,    -1,    -1,    -1,   270,   271,    -1,   273,    -1,
      -1,   276,   277,    -1,    -1,    -1,    -1,   282,    -1,   284,
     285,    -1,    -1,    -1,    -1,   290,    -1,   292,   293,    -1,
     295,    -1,    -1,    -1,   299,    -1,    -1,   302,    -1,   304,
      -1,    -1,    -1,    -1,   309,    -1,   311,   312,   313,   314,
      -1,    -1,    -1,   318,    -1,   320,   321,    -1,    -1,   324,
     325,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   337,   338,   339,    -1,   341,    -1,   343,   344,
     345,   346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     375,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   394,
      -1,    -1,   397,    -1,    -1,    -1,   401,   402,    -1,   404,
      -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,   413,    -1,
      -1,   416,   417,   418,   419,    -1,    -1,    -1,   423,   424,
     425,    -1,   427,   428,    -1,   430,    -1,   432,    -1,    -1,
      -1,    -1,    -1,    -1,   439,    -1,   441,   442,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   454,
       4,     5,     6,     7,     8,   460,    -1,   462,    12,    -1,
     465,    -1,    -1,   468,    -1,   470,    -1,   472,   473,   474,
      -1,    25,    -1,    -1,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,    43,
      -1,    45,    46,    47,    48,    49,    -1,    51,    -1,    -1,
      54,    -1,    56,    -1,    -1,    59,    -1,    -1,    62,    63,
      64,    65,    66,    67,    -1,    -1,    70,    71,    72,    73,
      -1,    -1,    76,    -1,    78,    79,    80,    -1,    82,    -1,
      84,    85,    -1,    -1,    -1,    -1,    90,    91,    92,    93,
      -1,    95,    96,    97,    -1,    99,    -1,   101,   102,    -1,
      -1,   105,   106,    -1,   108,    -1,   110,    -1,    -1,   113,
      -1,    -1,    -1,    -1,   118,    -1,    -1,   121,    -1,    -1,
     124,   125,   126,    -1,   128,   129,   130,    -1,    -1,   133,
     134,    -1,   136,    -1,   138,   139,   140,    -1,    -1,    -1,
      -1,   145,    -1,   147,    -1,   149,    -1,    -1,    -1,   153,
      -1,    -1,   156,   157,   158,    -1,   160,    -1,   162,    -1,
      -1,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,
     174,   175,    -1,    -1,    -1,   179,    -1,   181,    -1,    -1,
      -1,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,    -1,   202,   203,
     204,   205,   206,   207,   208,   209,    -1,   211,   212,   213,
      -1,   215,    -1,   217,    -1,    -1,   220,    -1,   222,   223,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,   232,   233,
      -1,    -1,   236,   237,   238,   239,   240,   241,   242,   243,
      -1,    -1,    -1,    -1,   248,    -1,   250,    -1,   252,   253,
      -1,    -1,   256,   257,   258,   259,    -1,    -1,   262,   263,
     264,   265,   266,    -1,    -1,    -1,   270,   271,    -1,   273,
      -1,    -1,   276,   277,    -1,    -1,    -1,    -1,   282,    -1,
     284,   285,    -1,    -1,    -1,    -1,   290,    -1,   292,   293,
      -1,   295,    -1,    -1,    -1,   299,    -1,    -1,   302,    -1,
     304,    -1,    -1,    -1,    -1,   309,    -1,   311,   312,   313,
     314,    -1,    -1,    -1,   318,    -1,   320,   321,    -1,    -1,
     324,   325,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   337,   338,   339,    -1,   341,    -1,   343,
     344,   345,   346,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,   382,   383,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     394,    -1,    -1,   397,    -1,    -1,    -1,   401,   402,    -1,
     404,    -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,   413,
      -1,    -1,   416,   417,   418,   419,    -1,    -1,    -1,   423,
     424,   425,    -1,   427,   428,    -1,   430,    -1,   432,    -1,
      -1,    -1,    -1,    -1,    -1,   439,    -1,   441,   442,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     454,     4,     5,     6,     7,     8,   460,    -1,   462,    12,
      -1,   465,    -1,    -1,   468,    -1,   470,    -1,   472,   473,
     474,    -1,    25,    -1,    -1,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,
      43,    -1,    45,    46,    47,    48,    49,    -1,    51,    -1,
      -1,    54,    -1,    56,    -1,    -1,    59,    -1,    -1,    62,
      63,    64,    65,    66,    67,    -1,    -1,    70,    71,    72,
      73,    -1,    -1,    76,    -1,    78,    79,    80,    -1,    82,
      -1,    84,    85,    -1,    -1,    -1,    -1,    90,    91,    92,
      93,    -1,    95,    96,    97,    -1,    99,    -1,   101,   102,
      -1,    -1,   105,   106,    -1,   108,    -1,   110,    -1,    -1,
     113,    -1,    -1,    -1,    -1,   118,    -1,    -1,   121,    -1,
      -1,   124,   125,   126,    -1,   128,   129,   130,    -1,    -1,
     133,   134,    -1,   136,    -1,   138,   139,   140,    -1,    -1,
      -1,    -1,   145,    -1,   147,    -1,   149,    -1,    -1,    -1,
     153,    -1,    -1,   156,   157,   158,    -1,   160,    -1,   162,
      -1,    -1,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,
      -1,   174,   175,    -1,    -1,    -1,   179,    -1,   181,    -1,
      -1,    -1,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,    -1,   202,
     203,   204,   205,   206,   207,   208,   209,    -1,   211,   212,
     213,    -1,   215,    -1,   217,    -1,    -1,   220,    -1,   222,
     223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231,   232,
     233,    -1,    -1,   236,   237,   238,   239,   240,   241,   242,
     243,    -1,    -1,    -1,    -1,   248,    -1,   250,    -1,   252,
     253,    -1,    -1,   256,   257,   258,   259,    -1,    -1,   262,
     263,   264,   265,   266,    -1,    -1,    -1,   270,   271,    -1,
     273,    -1,    -1,   276,   277,    34,    -1,    -1,    -1,   282,
      -1,   284,   285,    -1,    -1,    -1,    -1,   290,    -1,   292,
     293,    -1,   295,    -1,    -1,    -1,   299,    -1,    -1,   302,
      -1,   304,    -1,    -1,    -1,    -1,   309,    -1,   311,   312,
     313,   314,    -1,    -1,    -1,   318,    -1,   320,   321,    -1,
      -1,   324,   325,    -1,   327,    -1,    -1,    -1,    -1,    -1,
      -1,    90,    91,    -1,   337,   338,   339,    -1,   341,    -1,
     343,   344,   345,   346,    -1,    -1,   105,   106,    -1,    -1,
     109,    -1,    -1,   356,    -1,    -1,    -1,    -1,    -1,   118,
     119,    -1,   121,    -1,    -1,    -1,    94,    95,    96,    97,
      -1,    -1,   375,    -1,    -1,    -1,    -1,    -1,    -1,   382,
     383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   394,    -1,    -1,   397,    -1,    -1,    -1,   401,   402,
      -1,   404,   161,    -1,    -1,    -1,   409,    -1,    -1,    -1,
     413,    -1,   140,   416,   417,   418,   419,    -1,   177,    -1,
     423,   424,   425,    -1,   427,   428,    -1,   430,    -1,   432,
      -1,    -1,    -1,    -1,    -1,    -1,   439,    -1,   441,   442,
      -1,    -1,    -1,   202,    -1,    -1,    -1,    -1,   207,    -1,
      -1,   454,    -1,    -1,    -1,   183,    -1,   460,    -1,   462,
      -1,    -1,   465,    -1,    -1,   468,    -1,   470,    -1,   472,
     473,   474,    -1,   232,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   209,   241,   242,   243,   213,    -1,   215,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   257,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   284,    -1,    -1,    -1,    -1,
      -1,    -1,   260,    -1,   262,    -1,    -1,   296,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   317,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   315,   316,   317,
      -1,    -1,   320,   321,   322,   323,   324,    -1,   326,   327,
     328,    -1,   330,   331,   332,   333,   334,   335,    -1,    -1,
      -1,    -1,   340,    -1,   342,    -1,   344,   345,   346,   347,
     348,   349,    -1,   382,   352,   353,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   404,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   394,    -1,    -1,   428,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   409,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   423,   424,   425,    -1,    -1,
      -1,    -1,   430,    -1,   432,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   486,    -1,    -1,
      -1,    -1,    -1,    -1,   462
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned short yystos[] =
{
       0,     3,     5,    26,    27,    30,    32,    35,    38,    41,
      43,    44,    46,    48,    49,    50,    52,    53,    55,    60,
      61,    62,    64,    65,    67,    68,    69,    70,    73,    76,
      80,    81,    83,    92,   102,   106,   107,   122,   123,   148,
     249,   253,   255,   260,   300,   337,   338,   436,   486,   496,
     497,   498,   499,   500,   502,   507,   508,   513,   611,   626,
     629,   637,   639,   641,   644,   649,   651,   656,   659,   663,
     667,   675,   676,   783,   785,   792,   795,   822,   830,   841,
     843,   857,   860,   863,   869,   873,   877,   878,   879,   911,
     926,   932,   933,   940,   943,   966,   969,   970,   971,     4,
       5,     6,     7,     8,    12,    25,    28,    29,    30,    31,
      33,    34,    35,    36,    40,    43,    45,    46,    47,    48,
      49,    51,    54,    56,    59,    62,    63,    64,    65,    66,
      67,    70,    71,    72,    73,    76,    78,    79,    80,    82,
      84,    85,    90,    91,    92,    93,    95,    96,    97,    99,
     101,   102,   105,   106,   108,   110,   113,   118,   121,   124,
     125,   126,   128,   129,   130,   133,   134,   136,   138,   139,
     140,   145,   147,   149,   153,   156,   157,   158,   160,   162,
     165,   168,   174,   175,   179,   181,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   202,   203,   204,   205,   206,   207,   208,   209,
     211,   212,   213,   215,   217,   220,   222,   223,   231,   232,
     233,   236,   237,   238,   239,   240,   241,   242,   243,   248,
     250,   252,   253,   256,   257,   258,   259,   262,   263,   264,
     265,   266,   270,   271,   273,   276,   277,   282,   284,   285,
     290,   292,   293,   295,   299,   302,   304,   309,   311,   312,
     313,   314,   318,   320,   321,   324,   325,   327,   337,   338,
     339,   341,   343,   344,   345,   346,   356,   375,   382,   383,
     394,   397,   401,   402,   404,   409,   413,   416,   417,   418,
     419,   423,   424,   425,   427,   428,   430,   432,   439,   441,
     442,   454,   460,   462,   465,   468,   470,   472,   473,   474,
     493,   902,   903,   904,   907,   910,   159,   368,   622,   179,
     308,   658,   967,    56,    85,   146,   267,   277,   297,   368,
     531,   532,   533,   546,   603,   831,   784,   161,   277,   292,
     368,   454,   791,   907,   658,   176,   279,   905,   907,   908,
     793,    19,    29,    37,    50,    57,    58,    74,    75,    77,
      78,    80,    94,   104,   105,   110,   115,   116,   119,   135,
     137,   141,   150,   154,   173,   180,   182,   201,   214,   216,
     218,   219,   245,   258,   279,   283,   286,   287,   288,   289,
     294,   303,   314,   317,   319,   321,   345,   346,   350,   357,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   375,   376,   377,   378,   380,   381,   384,   385,
     386,   387,   388,   390,   391,   392,   393,   394,   395,   396,
     397,   401,   403,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   416,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   435,   436,
     437,   438,   439,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
     462,   463,   464,   478,   479,   484,   486,   489,   490,   492,
     493,   494,   696,   699,   702,   703,   704,   707,   891,   893,
     895,   896,   900,   906,   907,   980,   986,   118,   161,   275,
     274,   275,   928,   658,   874,   658,   870,   280,   907,   678,
     680,   681,   844,    73,    76,    70,   282,    70,   275,   842,
     928,   823,   928,   161,   928,   928,   944,   928,   928,   941,
     224,   913,   907,   907,   796,    68,   486,   677,     0,     3,
     337,   136,   861,   902,   907,   907,   223,     4,   244,   493,
     614,   907,   275,   928,   460,   968,   280,   403,   534,   275,
     532,   292,   161,   159,   184,   339,   839,   840,   717,   718,
     907,   904,   403,   790,   787,   928,   503,   864,   120,   155,
     184,   799,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   696,   486,   486,   486,   486,   486,   695,
     486,   486,   982,   986,   486,   486,   486,   486,   720,   721,
     722,   696,   486,   486,   486,   486,   486,   154,   279,   486,
     486,   486,   486,   294,   486,   891,   486,   891,   486,   891,
     486,   486,   486,   486,   696,   724,   486,   486,   486,   695,
     486,   695,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   696,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   695,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     695,   695,   695,   486,   486,   486,   486,   696,   696,   696,
      68,   696,   696,   907,   492,   908,   907,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      87,   167,   177,   216,   226,   227,   247,   310,   358,   476,
     477,   478,   479,   480,   481,   482,   483,   697,   371,   372,
     373,   374,   375,   398,   399,   400,   401,   413,   414,   415,
     416,   419,   439,   440,   461,   462,   747,   109,   906,   493,
     678,   981,   113,   144,   184,   882,   166,   902,   927,   928,
      56,    94,   849,   875,   928,    56,    70,   238,   871,   872,
      67,   679,    86,   127,   155,   272,   467,   468,   469,   470,
     471,   472,   685,   686,   687,    31,    37,    38,    56,    70,
      93,   105,   110,   112,   117,   145,   147,   149,   161,   162,
     165,   170,   179,   181,   212,   223,   235,   264,   270,   271,
     274,   275,   312,   313,   317,   382,   579,   602,   845,   849,
     850,   853,   918,   631,   632,   631,   631,   306,   630,   631,
     789,   902,   184,   829,   640,   664,   665,   902,   642,   652,
      26,    38,    41,    44,    46,    50,    55,    63,    68,    69,
      79,    83,    86,   138,   148,   161,   236,   246,   248,   266,
     298,   945,   947,   948,   660,   638,    86,   942,   945,   912,
     144,   120,   800,   829,   680,   677,   487,   907,   859,   858,
      10,    88,   749,   750,   934,   907,   613,   902,   650,   509,
     216,   907,   534,   904,   907,   144,   832,   836,   837,   907,
     839,   696,   719,   221,   135,   907,   116,   908,   909,   957,
     958,   790,   301,   504,    56,    70,   124,   156,   181,   235,
     238,   252,   270,   274,   865,   866,   928,   622,   696,    86,
     714,   751,   127,   714,   751,   696,   714,   714,   714,   714,
     714,   696,   696,   696,   696,   696,   696,   487,   900,   678,
     983,   696,   696,   696,   721,   356,   723,   900,   696,   487,
     696,   696,   696,   900,   696,   717,   717,   696,   696,   696,
     696,   714,   714,   714,   459,   717,   696,   696,   696,   487,
     696,   696,   696,   696,   696,   696,   696,   696,   696,   696,
     747,   696,   696,   696,   696,   696,   696,   717,   127,   711,
     891,   320,   321,   345,   346,   748,   696,   696,   487,   696,
     696,   696,   717,   696,   696,   696,   696,   696,   696,   696,
     696,   696,   717,   717,   717,   696,   696,   696,   696,   696,
     696,   717,   700,   703,   487,   696,   696,   696,   696,   696,
     696,   696,   696,    98,   172,   281,   696,   706,   717,   706,
     706,   706,   706,   706,   891,   487,   696,   487,   696,   696,
     696,   141,   182,   219,   245,   350,   770,   487,   488,   696,
     147,   179,   264,   919,    22,   493,   696,   696,   177,   216,
     218,   696,   696,   696,   696,   486,   984,   986,   703,   167,
     177,   247,   358,   696,   696,   696,   696,   701,   703,   696,
     696,   696,   702,   696,   702,   696,   696,   696,   696,    28,
      86,   696,   698,   479,   908,   907,   487,   987,    56,   179,
     881,   102,   144,   902,   929,   930,   657,   181,   645,   102,
     488,   907,   296,   972,   973,   480,   689,   690,   691,   687,
      45,   486,   275,   368,   270,   156,   270,   181,   177,   852,
     285,   852,   389,   270,    56,   274,   852,   144,   167,   851,
     854,   270,   285,   329,   765,   767,   765,   260,   541,   908,
     852,   854,   181,   383,   111,   237,   304,   628,    51,    72,
     633,   634,   627,    36,   622,   788,   789,   167,   488,   671,
     672,   788,   788,   277,   950,   274,    33,    70,   949,   117,
     951,   235,   946,   224,   952,   221,   488,   661,   662,   902,
     788,   946,   221,   147,   179,   222,   264,   914,   915,   916,
     917,   492,   501,   905,   166,   789,   801,   802,   487,   973,
     975,   976,   977,   675,   154,   862,   892,   906,   907,   907,
       7,   139,   907,   935,   936,   119,   528,   529,   530,   539,
     540,   587,   612,   788,   185,   186,   187,   188,   189,   190,
     191,   193,   194,   195,   196,   197,   198,   199,   200,   510,
     511,   512,   135,   516,   902,   517,   284,   301,   604,   836,
     902,   907,   488,   834,   493,   838,   488,   902,   695,   492,
     402,   488,   788,   492,   505,   506,   102,   306,   488,   867,
     801,   488,   487,   715,   708,   487,   480,   488,   487,   487,
     487,   487,   487,   488,   488,    88,   487,   487,   301,   488,
     487,   987,   488,   488,   487,   488,   487,   486,   488,   488,
     487,   488,   488,   487,   487,   487,   487,   487,   487,   488,
     487,   487,   488,   487,   487,   487,   726,   727,   487,   488,
     488,   487,   488,   488,   487,   488,   487,   488,   487,   488,
     488,   488,   487,   488,   488,   144,   488,   488,   487,   488,
     487,   488,   487,   488,   487,   488,   487,   710,   488,   488,
     487,   488,   487,   488,   487,   488,   487,   488,   488,   488,
     487,   487,   487,   487,   488,   487,   488,   487,   488,   487,
     487,   487,   487,   487,   487,   487,   488,   488,   487,   488,
     487,     9,    11,    12,    18,    19,    20,    21,    87,   167,
     177,   216,   226,   227,   247,   310,   358,   476,   477,   478,
     479,   480,   481,   482,   483,   697,   487,   488,   488,   487,
     488,   487,   488,   144,   488,   488,   144,   696,   144,   696,
     144,   696,   144,   487,   487,   487,   487,   487,   487,   487,
     488,   487,   487,   488,   487,   487,   488,   488,   717,   491,
     493,   493,   493,   908,   696,   907,   696,   218,   717,   678,
     985,   134,   756,   486,   984,   703,   696,   701,     9,    11,
      12,    18,    19,    20,    21,    87,   167,   177,   216,   226,
     227,   247,   310,   358,   476,   477,   478,   479,   480,   481,
     482,   483,   697,   747,   747,   984,   696,   493,   163,   668,
      56,   750,   488,   788,   280,   475,   876,   788,   872,    86,
     127,   979,   488,   682,   693,   696,   898,   907,   167,   855,
     480,   902,   534,   905,   909,   389,   851,   852,   907,   851,
     768,   770,   846,   902,   854,   852,    82,   635,   488,   635,
      71,   486,   490,   729,   734,   735,   280,   488,   119,   666,
     907,   665,   161,   171,   600,   601,   673,   136,   339,   643,
     136,   206,   318,   325,   339,   653,   654,   655,   274,   486,
     959,   959,   959,   959,   480,   902,   907,   956,   948,   488,
     280,   144,   488,   956,   488,   119,   282,   907,   920,   922,
     208,   428,   492,   579,   921,   908,   802,   797,   228,   761,
     767,   978,     6,     7,     8,    10,    13,    14,    15,    16,
     139,   937,   939,   305,   752,   530,   109,   579,    24,    26,
      32,    34,    44,    90,    91,   106,   115,   118,   121,   125,
     126,   130,   160,   161,   202,   207,   232,   241,   242,   243,
     249,   257,   284,   296,   382,   404,   418,   428,   536,   538,
     539,   540,   615,   616,   617,   761,   653,    10,    10,    10,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,   488,   528,   514,   290,    99,   153,   259,   605,
     605,   221,   835,   833,   493,   837,   144,   480,   907,   750,
     696,   786,   908,   100,   958,   103,   254,   623,   908,   488,
     244,   866,   788,   868,   794,   696,   696,   717,   487,   696,
     405,   696,   696,    94,   213,   317,   320,   321,   341,   346,
     351,   716,    94,   580,   908,   716,   717,   717,   696,   696,
     900,   717,   696,   696,   696,   696,   379,   725,   696,   728,
     717,   696,   702,   702,   906,   696,   696,   717,   906,   696,
     696,   696,   717,   219,   696,   696,   696,   696,   717,   219,
     696,   696,   696,   696,   696,   717,   696,   696,   696,   696,
     696,   696,   696,   696,   696,   177,   216,   218,   696,   696,
     696,   696,   696,   703,   177,   247,   358,   696,   696,   696,
     696,   701,   696,   696,   696,   702,   696,   702,   696,   696,
     696,   696,   696,   698,   696,   696,   696,   405,   696,   696,
     696,   696,   696,   144,   696,   144,   696,   144,   696,   219,
     696,   696,   696,   487,   493,   609,   487,   987,   703,   717,
     756,    87,   696,   696,   177,   216,   218,   696,   696,   696,
     696,   486,   984,   703,   167,   177,   247,   358,   696,   696,
     696,   696,   701,   696,   696,   696,   702,   696,   702,   696,
     696,   696,   696,   696,   698,   907,   905,   669,   670,   902,
     184,   244,   307,   931,   930,   653,   905,   696,   136,   299,
     339,   646,   647,   648,   974,   690,   144,   166,   683,   684,
     766,   767,   781,   692,   493,   905,   144,   856,   487,   907,
      70,   852,   852,   220,   488,   181,   270,   848,   851,   902,
     512,   636,   634,    68,   486,   729,   736,   907,    39,   164,
     169,   210,   260,   272,   407,   437,   488,   733,   902,   905,
     789,   486,   654,   907,   960,   961,   493,   493,   280,   662,
     902,   905,   148,   144,   915,   493,   168,   493,    10,    22,
     813,   119,   580,   581,   389,   813,   492,   908,    94,   119,
     582,   583,   908,    68,   260,   302,   303,   486,   524,   803,
     807,   100,   765,   938,   753,   766,   813,   814,   814,   112,
     114,   146,   267,   551,   554,   555,   598,   600,   621,   621,
     621,   814,   143,   234,   600,   621,   814,   814,   814,   280,
     133,   814,   170,   276,   170,   276,   133,   814,   814,   814,
     814,   814,   814,    10,    88,   280,   625,   814,   814,   814,
     814,   814,   621,   814,   536,   488,   486,   493,   550,   556,
     901,   907,   905,   905,   905,   141,   182,   219,   245,   350,
     771,   905,   770,   770,   770,   905,   905,   905,   905,   905,
     905,   770,   511,   177,   486,   518,   535,   537,   538,   328,
     340,   343,   547,   902,   301,   752,   907,   729,   493,   838,
     279,   428,   506,    55,   803,   487,   709,   488,   696,   487,
     487,   486,   573,   573,   573,   328,   328,   487,   487,   487,
     487,   487,   487,   167,   306,   705,   487,   487,   488,   487,
     487,   696,   465,   466,   459,   487,   488,   747,   747,   487,
     487,   487,   487,   487,   487,   488,   487,   487,   487,   487,
     487,   487,   487,   713,   761,   488,   487,   488,   487,   487,
     487,   488,   487,   487,   488,   487,   487,   487,   487,   487,
     487,   696,   218,   487,   756,   703,   696,   701,    87,   747,
     747,   984,   488,   487,   487,   696,   487,   389,   487,   487,
     488,   488,   487,   696,   487,   696,   487,   696,   487,   488,
     487,   487,   487,   907,   487,   696,   696,   218,   717,   756,
     486,   984,   703,   696,   701,    87,   747,   747,   984,   880,
     488,   671,   307,   179,   647,   676,    42,   729,   230,   231,
     777,   778,    55,   389,   688,   781,   684,    88,   694,   905,
     907,   480,   907,   771,   847,   312,   313,   306,   770,   770,
     851,   488,   737,   738,   736,   487,   975,   734,   169,   169,
     169,   407,   437,   825,   826,   900,   729,   229,   740,   740,
     729,   729,   750,   234,   745,   907,   487,   488,   480,   480,
     957,   224,   957,   907,   175,   907,    86,    94,   119,   221,
     696,   925,   109,   585,   909,   279,   427,   428,   924,   919,
     813,   525,   804,   486,   810,   815,   810,   487,   524,   806,
     897,   898,   900,   808,   798,   762,   486,   696,   119,   584,
     586,   908,   581,   608,   901,   601,   601,   107,   143,   234,
     297,   553,   599,   552,   553,   608,   901,   901,   905,   171,
     171,   901,   901,   771,   770,   770,   579,   814,   770,   814,
     771,   771,   119,   770,   239,   240,   543,   770,   770,   770,
     902,   119,   129,   140,   311,   542,   541,   486,   541,     6,
     139,   217,   544,   901,   905,   617,   548,   549,   550,   551,
     907,    25,   139,   624,   246,   552,   590,   557,   493,   902,
     177,   519,   524,   548,   159,   436,   521,   883,   488,   537,
     291,   515,   729,   760,   761,   752,   750,   279,   221,   820,
     487,   696,   747,   219,   101,   295,   314,   579,   588,    97,
     238,   487,   696,   696,   696,   696,   487,   487,   696,   261,
     712,   219,   696,   696,   696,   756,    87,   696,   696,   747,
     696,   696,   696,   487,   487,   487,   219,   487,   717,   756,
      87,   696,   883,   670,   159,   674,   766,   752,   905,   905,
     492,   779,   780,   167,    83,   905,   907,   493,   765,   187,
     852,   512,   685,   487,   487,   407,   729,   740,   740,   488,
     824,   813,   169,   169,   221,   301,   142,   159,   300,   741,
     487,   488,   961,   251,   962,   144,   244,   250,   263,   923,
     586,   813,   486,   486,   922,   696,   685,   811,   812,   900,
     816,   488,   486,   807,   487,   487,   488,   972,   696,   763,
     899,   119,   696,   818,   819,   696,   171,   171,   601,   608,
     604,    44,   260,   618,   608,   623,   581,   905,   905,   788,
     619,   487,   488,   907,   902,    94,    95,    96,    97,   140,
     183,   209,   213,   215,   260,   262,   315,   316,   317,   320,
     321,   322,   323,   324,   326,   327,   328,   330,   331,   332,
     333,   334,   335,   340,   342,   344,   345,   346,   347,   348,
     349,   352,   353,   394,   409,   423,   424,   425,   430,   432,
     462,   558,   561,   562,   563,   564,   565,   566,   567,   907,
     902,   487,   487,    88,   527,   537,   905,   486,   752,   329,
     769,   128,   488,   487,   487,   580,   417,    47,   487,   466,
     487,   487,   488,   892,   487,   488,   487,   487,   487,   696,
     487,   487,   487,   487,   487,   488,   487,   696,   166,   174,
     151,   757,   782,   908,   488,   441,   480,    10,   689,   750,
     229,   169,   169,   826,   752,   819,   729,   729,   696,   730,
     600,   742,   742,   742,   907,    59,   268,   273,   309,   473,
     474,   954,   955,   306,   963,   957,   108,   293,   244,   924,
     279,   279,   813,   689,   488,   813,   817,   818,   815,   809,
     807,   897,   488,    89,   122,   764,   487,   488,   608,   604,
     486,   119,   119,   556,   585,   487,   558,   549,   591,   486,
     573,   486,   568,   569,   317,   352,   562,   564,   588,   317,
     353,   353,   354,   560,   573,   568,   336,   559,   568,   588,
     588,   568,   573,   573,   588,   486,   573,    34,    90,    94,
     109,   119,   216,   218,   221,   234,   262,   297,   575,   576,
     577,   589,   354,   486,   588,   486,   486,   486,   573,   486,
     569,   574,   487,   520,   535,   486,   524,   606,   607,   907,
     771,   821,   696,   696,   696,   714,   717,   275,   100,   152,
     754,   111,   884,   780,   417,   905,   739,   169,   729,   729,
     760,   221,   731,   221,   732,   486,   743,   279,   279,   279,
      87,   953,   148,   203,   204,   205,   964,   965,   487,   487,
     925,   526,   812,   819,   487,   975,   899,   819,   486,   486,
     606,   321,   345,   346,   478,   479,   894,   895,   624,   575,
     201,   221,   486,   592,   594,   595,   596,   219,   219,   341,
     351,   355,   570,   571,   572,   588,   354,   486,   570,   486,
     570,   570,   588,   219,   570,   905,   584,   426,   578,   894,
     218,    83,   119,   171,   577,   171,   219,   219,   219,   219,
     570,   219,   570,   975,   521,   524,   522,   487,   488,   764,
     486,   171,   487,   487,   488,   487,   487,   902,   758,   899,
     755,   760,   131,   132,   225,   278,   885,   886,   178,   887,
      87,   545,   684,   766,   734,   769,   696,   301,   696,   301,
     746,   907,   486,   954,   224,   770,   770,   770,   965,   545,
     764,   606,   606,   487,   896,   896,   620,   145,   233,   265,
      41,    83,   593,   907,   596,   487,   487,   488,   572,   610,
     892,   610,   487,   695,   426,   302,   487,   487,   487,   487,
     487,   972,   607,   219,    83,   696,   884,   306,   488,   759,
     764,   696,   766,   100,   100,   131,   100,   886,   269,   278,
     888,   889,   188,   688,   221,   486,   486,   487,   488,   744,
     745,   487,   487,   624,   103,   217,   254,   260,   597,   597,
     487,   488,   219,   487,   488,   487,   695,   588,   588,   523,
     764,   487,   827,   828,   900,   487,   887,    40,    66,   899,
     434,   772,   892,   892,   100,   892,   100,   100,   889,    10,
     696,   746,   746,   907,   487,   590,    84,   119,   218,   594,
     907,   487,   588,   892,   588,   975,   488,   813,   159,   890,
     764,   907,   892,   892,   892,   771,   491,   487,   487,   828,
     819,   219,   486,   805,   773,    87,   178,   487,   806,   486,
     192,   487,   691,   774,   775,   776,    10,   696,   487,   488,
     770,   776
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 745 "sql_yacc.yy"
    {
	   THD *thd= YYTHD;
	   if (!thd->bootstrap &&
	      (!(thd->lex->select_lex.options & OPTION_FOUND_COMMENT)))
	   {
	     send_error(thd,ER_EMPTY_QUERY);
	     YYABORT;
	   }
	   else
	   {
	     thd->lex->sql_command= SQLCOM_EMPTY_QUERY;
	   }
	}
    break;

  case 3:
#line 758 "sql_yacc.yy"
    {}
    break;

  case 49:
#line 810 "sql_yacc.yy"
    {
          THD *thd=YYTHD;
          LEX *lex= thd->lex;
          if (thd->command == COM_PREPARE)
          {
            yyerror(ER(ER_SYNTAX_ERROR));
            YYABORT;
          }
          lex->sql_command= SQLCOM_DEALLOCATE_PREPARE;
          lex->prepared_stmt_name= yyvsp[0].lex_str;
        }
    break;

  case 52:
#line 830 "sql_yacc.yy"
    {
          THD *thd=YYTHD;
          LEX *lex= thd->lex;
          if (thd->command == COM_PREPARE)
          {
            yyerror(ER(ER_SYNTAX_ERROR));
            YYABORT;
          }
          lex->sql_command= SQLCOM_PREPARE;
          lex->prepared_stmt_name= yyvsp[-2].lex_str;
        }
    break;

  case 53:
#line 844 "sql_yacc.yy"
    {
          THD *thd=YYTHD;
          LEX *lex= thd->lex;
          lex->prepared_stmt_code= yyvsp[0].lex_str;
          lex->prepared_stmt_code_is_varref= FALSE;
        }
    break;

  case 54:
#line 851 "sql_yacc.yy"
    {
          THD *thd=YYTHD;
          LEX *lex= thd->lex;
          lex->prepared_stmt_code= yyvsp[0].lex_str;
          lex->prepared_stmt_code_is_varref= TRUE;
        }
    break;

  case 55:
#line 860 "sql_yacc.yy"
    {
          THD *thd=YYTHD;
          LEX *lex= thd->lex;
          if (thd->command == COM_PREPARE)
          {
            yyerror(ER(ER_SYNTAX_ERROR));
            YYABORT;
          }
          lex->sql_command= SQLCOM_EXECUTE;
          lex->prepared_stmt_name= yyvsp[0].lex_str;
        }
    break;

  case 56:
#line 872 "sql_yacc.yy"
    {}
    break;

  case 61:
#line 886 "sql_yacc.yy"
    {
          LEX *lex=Lex;
          LEX_STRING *lexstr= (LEX_STRING*)sql_memdup(&yyvsp[0].lex_str, sizeof(LEX_STRING));
          if (!lexstr || lex->prepared_stmt_params.push_back(lexstr))
              YYABORT;
        }
    break;

  case 62:
#line 898 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  lex->sql_command= SQLCOM_HELP;
	  lex->help_arg= yyvsp[0].lex_str.str;
       }
    break;

  case 63:
#line 908 "sql_yacc.yy"
    {
	  LEX *lex = Lex;
	  lex->sql_command = SQLCOM_CHANGE_MASTER;
	  bzero((char*) &lex->mi, sizeof(lex->mi));
        }
    break;

  case 64:
#line 914 "sql_yacc.yy"
    {}
    break;

  case 67:
#line 923 "sql_yacc.yy"
    {
	 Lex->mi.host = yyvsp[0].lex_str.str;
       }
    break;

  case 68:
#line 928 "sql_yacc.yy"
    {
	 Lex->mi.user = yyvsp[0].lex_str.str;
       }
    break;

  case 69:
#line 933 "sql_yacc.yy"
    {
	 Lex->mi.password = yyvsp[0].lex_str.str;
       }
    break;

  case 70:
#line 938 "sql_yacc.yy"
    {
	 Lex->mi.port = yyvsp[0].ulong_num;
       }
    break;

  case 71:
#line 943 "sql_yacc.yy"
    {
	 Lex->mi.connect_retry = yyvsp[0].ulong_num;
       }
    break;

  case 72:
#line 947 "sql_yacc.yy"
    {
           Lex->mi.ssl= yyvsp[0].ulong_num ? 
               LEX_MASTER_INFO::SSL_ENABLE : LEX_MASTER_INFO::SSL_DISABLE;
         }
    break;

  case 73:
#line 952 "sql_yacc.yy"
    {
           Lex->mi.ssl_ca= yyvsp[0].lex_str.str;
         }
    break;

  case 74:
#line 956 "sql_yacc.yy"
    {
           Lex->mi.ssl_capath= yyvsp[0].lex_str.str;
         }
    break;

  case 75:
#line 960 "sql_yacc.yy"
    {
           Lex->mi.ssl_cert= yyvsp[0].lex_str.str;
         }
    break;

  case 76:
#line 964 "sql_yacc.yy"
    {
           Lex->mi.ssl_cipher= yyvsp[0].lex_str.str;
         }
    break;

  case 77:
#line 968 "sql_yacc.yy"
    {
           Lex->mi.ssl_key= yyvsp[0].lex_str.str;
	 }
    break;

  case 79:
#line 977 "sql_yacc.yy"
    {
	 Lex->mi.log_file_name = yyvsp[0].lex_str.str;
       }
    break;

  case 80:
#line 981 "sql_yacc.yy"
    {
           Lex->mi.pos = yyvsp[0].ulonglong_number;
           /* 
              If the user specified a value < BIN_LOG_HEADER_SIZE, adjust it
              instead of causing subsequent errors. 
              We need to do it in this file, because only there we know that 
              MASTER_LOG_POS has been explicitely specified. On the contrary
              in change_master() (sql_repl.cc) we cannot distinguish between 0
              (MASTER_LOG_POS explicitely specified as 0) and 0 (unspecified),
              whereas we want to distinguish (specified 0 means "read the binlog
              from 0" (4 in fact), unspecified means "don't change the position
              (keep the preceding value)").
           */
           Lex->mi.pos = max(BIN_LOG_HEADER_SIZE, Lex->mi.pos);
         }
    break;

  case 81:
#line 997 "sql_yacc.yy"
    {
           Lex->mi.relay_log_name = yyvsp[0].lex_str.str;
         }
    break;

  case 82:
#line 1001 "sql_yacc.yy"
    {
           Lex->mi.relay_log_pos = yyvsp[0].ulong_num;
           /* Adjust if < BIN_LOG_HEADER_SIZE (same comment as Lex->mi.pos) */
           Lex->mi.relay_log_pos = max(BIN_LOG_HEADER_SIZE, Lex->mi.relay_log_pos);
         }
    break;

  case 83:
#line 1012 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  LEX *lex=Lex;
	  lex->sql_command= SQLCOM_CREATE_TABLE;
	  if (!lex->select_lex.add_table_to_list(thd, yyvsp[0].table, NULL,
						 TL_OPTION_UPDATING,
						 (using_update_log ?
						  TL_READ_NO_INSERT:
						  TL_READ)))
	    YYABORT;
	  lex->create_list.empty();
	  lex->key_list.empty();
	  lex->col_list.empty();
	  lex->change=NullS;
	  bzero((char*) &lex->create_info,sizeof(lex->create_info));
	  lex->create_info.options=yyvsp[-3].num | yyvsp[-1].num;
	  lex->create_info.db_type= (enum db_type) lex->thd->variables.table_type;
	  lex->create_info.default_table_charset= NULL;
	  lex->name=0;
	}
    break;

  case 84:
#line 1033 "sql_yacc.yy"
    { Lex->current_select= &Lex->select_lex; }
    break;

  case 85:
#line 1035 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command= SQLCOM_CREATE_INDEX;
	    if (!lex->current_select->add_table_to_list(lex->thd, yyvsp[0].table, NULL,
							TL_OPTION_UPDATING))
	      YYABORT;
	    lex->create_list.empty();
	    lex->key_list.empty();
	    lex->col_list.empty();
	    lex->change=NullS;
	  }
    break;

  case 86:
#line 1047 "sql_yacc.yy"
    {
	    LEX *lex=Lex;

	    lex->key_list.push_back(new Key(yyvsp[-9].key_type,yyvsp[-7].lex_str.str, yyvsp[-6].key_alg, 0, lex->col_list));
	    lex->col_list.empty();
	  }
    break;

  case 87:
#line 1054 "sql_yacc.yy"
    {
             Lex->create_info.default_table_charset= NULL;
             Lex->create_info.used_fields= 0;
          }
    break;

  case 88:
#line 1059 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command=SQLCOM_CREATE_DB;
	    lex->name=yyvsp[-2].lex_str.str;
            lex->create_info.options=yyvsp[-3].num;
	  }
    break;

  case 89:
#line 1066 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command = SQLCOM_CREATE_FUNCTION;
	    lex->udf.name = yyvsp[0].lex_str;
	    lex->udf.type= yyvsp[-2].udf_type;
	  }
    break;

  case 90:
#line 1073 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->udf.returns=(Item_result) yyvsp[-2].num;
	    lex->udf.dl=yyvsp[0].lex_str.str;
	  }
    break;

  case 91:
#line 1081 "sql_yacc.yy"
    {}
    break;

  case 92:
#line 1082 "sql_yacc.yy"
    {}
    break;

  case 93:
#line 1084 "sql_yacc.yy"
    {
            LEX *lex=Lex;
            if (!(lex->name= (char *)yyvsp[0].table))
              YYABORT;
          }
    break;

  case 94:
#line 1090 "sql_yacc.yy"
    {
            LEX *lex=Lex;
            if (!(lex->name= (char *)yyvsp[-1].table))
              YYABORT;
          }
    break;

  case 95:
#line 1098 "sql_yacc.yy"
    {}
    break;

  case 96:
#line 1099 "sql_yacc.yy"
    { Select->set_braces(1);}
    break;

  case 97:
#line 1099 "sql_yacc.yy"
    {}
    break;

  case 98:
#line 1103 "sql_yacc.yy"
    {}
    break;

  case 99:
#line 1105 "sql_yacc.yy"
    { Select->set_braces(0);}
    break;

  case 100:
#line 1105 "sql_yacc.yy"
    {}
    break;

  case 101:
#line 1107 "sql_yacc.yy"
    { Select->set_braces(1);}
    break;

  case 102:
#line 1107 "sql_yacc.yy"
    {}
    break;

  case 103:
#line 1112 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->lock_option= using_update_log ? TL_READ_NO_INSERT : TL_READ;
	    if (lex->sql_command == SQLCOM_INSERT)
	      lex->sql_command= SQLCOM_INSERT_SELECT;
	    else if (lex->sql_command == SQLCOM_REPLACE)
	      lex->sql_command= SQLCOM_REPLACE_SELECT;
	    lex->current_select->table_list.save_and_clear(&lex->save_list);
	    mysql_init_select(lex);
	    lex->current_select->parsing_place= SELECT_LIST;
          }
    break;

  case 104:
#line 1124 "sql_yacc.yy"
    {
	    Select->parsing_place= NO_MATTER;
	  }
    break;

  case 105:
#line 1128 "sql_yacc.yy"
    { Lex->current_select->table_list.push_front(&Lex->save_list); }
    break;

  case 106:
#line 1132 "sql_yacc.yy"
    {}
    break;

  case 107:
#line 1133 "sql_yacc.yy"
    {}
    break;

  case 108:
#line 1136 "sql_yacc.yy"
    {}
    break;

  case 109:
#line 1137 "sql_yacc.yy"
    {}
    break;

  case 110:
#line 1140 "sql_yacc.yy"
    {}
    break;

  case 111:
#line 1141 "sql_yacc.yy"
    {}
    break;

  case 112:
#line 1144 "sql_yacc.yy"
    {}
    break;

  case 113:
#line 1145 "sql_yacc.yy"
    {}
    break;

  case 114:
#line 1148 "sql_yacc.yy"
    { yyval.num= 0; }
    break;

  case 115:
#line 1149 "sql_yacc.yy"
    { yyval.num= yyvsp[0].num;}
    break;

  case 116:
#line 1152 "sql_yacc.yy"
    { yyval.num=yyvsp[0].num; }
    break;

  case 117:
#line 1153 "sql_yacc.yy"
    { yyval.num= yyvsp[-1].num | yyvsp[0].num; }
    break;

  case 118:
#line 1156 "sql_yacc.yy"
    { yyval.num=HA_LEX_CREATE_TMP_TABLE; }
    break;

  case 119:
#line 1159 "sql_yacc.yy"
    { yyval.num= 0; }
    break;

  case 120:
#line 1160 "sql_yacc.yy"
    { yyval.num=HA_LEX_CREATE_IF_NOT_EXISTS; }
    break;

  case 128:
#line 1176 "sql_yacc.yy"
    { Lex->create_info.db_type= yyvsp[0].db_type; }
    break;

  case 129:
#line 1177 "sql_yacc.yy"
    { Lex->create_info.db_type= yyvsp[0].db_type; WARN_DEPRECATED("TYPE=storage_engine","ENGINE=storage_engine"); }
    break;

  case 130:
#line 1178 "sql_yacc.yy"
    { Lex->create_info.max_rows= yyvsp[0].ulonglong_number; Lex->create_info.used_fields|= HA_CREATE_USED_MAX_ROWS;}
    break;

  case 131:
#line 1179 "sql_yacc.yy"
    { Lex->create_info.min_rows= yyvsp[0].ulonglong_number; Lex->create_info.used_fields|= HA_CREATE_USED_MIN_ROWS;}
    break;

  case 132:
#line 1180 "sql_yacc.yy"
    { Lex->create_info.avg_row_length=yyvsp[0].ulong_num; Lex->create_info.used_fields|= HA_CREATE_USED_AVG_ROW_LENGTH;}
    break;

  case 133:
#line 1181 "sql_yacc.yy"
    { Lex->create_info.password=yyvsp[0].lex_str.str; }
    break;

  case 134:
#line 1182 "sql_yacc.yy"
    { Lex->create_info.comment=yyvsp[0].lex_str.str; }
    break;

  case 135:
#line 1183 "sql_yacc.yy"
    { Lex->create_info.auto_increment_value=yyvsp[0].ulonglong_number; Lex->create_info.used_fields|= HA_CREATE_USED_AUTO;}
    break;

  case 136:
#line 1184 "sql_yacc.yy"
    { Lex->create_info.table_options|= yyvsp[0].ulong_num ? HA_OPTION_PACK_KEYS : HA_OPTION_NO_PACK_KEYS; Lex->create_info.used_fields|= HA_CREATE_USED_PACK_KEYS;}
    break;

  case 137:
#line 1185 "sql_yacc.yy"
    { Lex->create_info.table_options&= ~(HA_OPTION_PACK_KEYS | HA_OPTION_NO_PACK_KEYS); Lex->create_info.used_fields|= HA_CREATE_USED_PACK_KEYS;}
    break;

  case 138:
#line 1186 "sql_yacc.yy"
    { Lex->create_info.table_options|= yyvsp[0].ulong_num ? HA_OPTION_CHECKSUM : HA_OPTION_NO_CHECKSUM; }
    break;

  case 139:
#line 1187 "sql_yacc.yy"
    { Lex->create_info.table_options|= yyvsp[0].ulong_num ? HA_OPTION_DELAY_KEY_WRITE : HA_OPTION_NO_DELAY_KEY_WRITE; }
    break;

  case 140:
#line 1188 "sql_yacc.yy"
    { Lex->create_info.row_type= yyvsp[0].row_type; }
    break;

  case 141:
#line 1189 "sql_yacc.yy"
    { Lex->create_info.raid_type= yyvsp[0].ulong_num; Lex->create_info.used_fields|= HA_CREATE_USED_RAID;}
    break;

  case 142:
#line 1190 "sql_yacc.yy"
    { Lex->create_info.raid_chunks= yyvsp[0].ulong_num; Lex->create_info.used_fields|= HA_CREATE_USED_RAID;}
    break;

  case 143:
#line 1191 "sql_yacc.yy"
    { Lex->create_info.raid_chunksize= yyvsp[0].ulong_num*RAID_BLOCK_SIZE; Lex->create_info.used_fields|= HA_CREATE_USED_RAID;}
    break;

  case 144:
#line 1193 "sql_yacc.yy"
    {
	    /* Move the union list to the merge_list */
	    LEX *lex=Lex;
	    TABLE_LIST *table_list= lex->select_lex.get_table_list();
	    lex->create_info.merge_list= lex->select_lex.table_list;
	    lex->create_info.merge_list.elements--;
	    lex->create_info.merge_list.first= (byte*) (table_list->next);
	    lex->select_lex.table_list.elements=1;
	    lex->select_lex.table_list.next= (byte**) &(table_list->next);
	    table_list->next=0;
	    lex->create_info.used_fields|= HA_CREATE_USED_UNION;
	  }
    break;

  case 147:
#line 1207 "sql_yacc.yy"
    { Lex->create_info.merge_insert_method= yyvsp[0].ulong_num; Lex->create_info.used_fields|= HA_CREATE_USED_INSERT_METHOD;}
    break;

  case 148:
#line 1209 "sql_yacc.yy"
    { Lex->create_info.data_file_name= yyvsp[0].lex_str.str; }
    break;

  case 149:
#line 1210 "sql_yacc.yy"
    { Lex->create_info.index_file_name= yyvsp[0].lex_str.str; }
    break;

  case 150:
#line 1214 "sql_yacc.yy"
    {
          HA_CREATE_INFO *cinfo= &Lex->create_info;
          if ((cinfo->used_fields & HA_CREATE_USED_DEFAULT_CHARSET) &&
               cinfo->default_table_charset && yyvsp[0].charset &&
               !my_charset_same(cinfo->default_table_charset,yyvsp[0].charset))
          {
            net_printf(YYTHD, ER_CONFLICTING_DECLARATIONS,
                       "CHARACTER SET ", cinfo->default_table_charset->csname,
                       "CHARACTER SET ", yyvsp[0].charset->csname);
            YYABORT;
          }
	  Lex->create_info.default_table_charset= yyvsp[0].charset;
          Lex->create_info.used_fields|= HA_CREATE_USED_DEFAULT_CHARSET;
        }
    break;

  case 151:
#line 1231 "sql_yacc.yy"
    {
          HA_CREATE_INFO *cinfo= &Lex->create_info;
          if ((cinfo->used_fields & HA_CREATE_USED_DEFAULT_CHARSET) &&
               cinfo->default_table_charset && yyvsp[0].charset &&
               !my_charset_same(cinfo->default_table_charset,yyvsp[0].charset))
            {
              net_printf(YYTHD,ER_COLLATION_CHARSET_MISMATCH,
                         yyvsp[0].charset->name, cinfo->default_table_charset->csname);
              YYABORT;
            }
            Lex->create_info.default_table_charset= yyvsp[0].charset;
            Lex->create_info.used_fields|= HA_CREATE_USED_DEFAULT_CHARSET;
        }
    break;

  case 152:
#line 1247 "sql_yacc.yy"
    {
	  yyval.db_type = ha_resolve_by_name(yyvsp[0].lex_str.str,yyvsp[0].lex_str.length);
	  if (yyval.db_type == DB_TYPE_UNKNOWN) {
	    net_printf(YYTHD, ER_UNKNOWN_STORAGE_ENGINE, yyvsp[0].lex_str.str);
	    YYABORT;
	  }
	}
    break;

  case 153:
#line 1256 "sql_yacc.yy"
    { yyval.row_type= ROW_TYPE_DEFAULT; }
    break;

  case 154:
#line 1257 "sql_yacc.yy"
    { yyval.row_type= ROW_TYPE_FIXED; }
    break;

  case 155:
#line 1258 "sql_yacc.yy"
    { yyval.row_type= ROW_TYPE_DYNAMIC; }
    break;

  case 156:
#line 1259 "sql_yacc.yy"
    { yyval.row_type= ROW_TYPE_COMPRESSED; }
    break;

  case 157:
#line 1262 "sql_yacc.yy"
    { yyval.ulong_num= RAID_TYPE_0; }
    break;

  case 158:
#line 1263 "sql_yacc.yy"
    { yyval.ulong_num= RAID_TYPE_0; }
    break;

  case 159:
#line 1264 "sql_yacc.yy"
    { yyval.ulong_num=yyvsp[0].ulong_num;}
    break;

  case 160:
#line 1267 "sql_yacc.yy"
    { yyval.ulong_num= MERGE_INSERT_DISABLED; }
    break;

  case 161:
#line 1268 "sql_yacc.yy"
    { yyval.ulong_num= MERGE_INSERT_TO_FIRST; }
    break;

  case 162:
#line 1269 "sql_yacc.yy"
    { yyval.ulong_num= MERGE_INSERT_TO_LAST; }
    break;

  case 163:
#line 1272 "sql_yacc.yy"
    {}
    break;

  case 165:
#line 1276 "sql_yacc.yy"
    { yyval.udf_type = UDFTYPE_FUNCTION; }
    break;

  case 166:
#line 1277 "sql_yacc.yy"
    { yyval.udf_type = UDFTYPE_AGGREGATE; }
    break;

  case 167:
#line 1280 "sql_yacc.yy"
    {yyval.num = (int) STRING_RESULT; }
    break;

  case 168:
#line 1281 "sql_yacc.yy"
    {yyval.num = (int) REAL_RESULT; }
    break;

  case 169:
#line 1282 "sql_yacc.yy"
    {yyval.num = (int) INT_RESULT; }
    break;

  case 175:
#line 1297 "sql_yacc.yy"
    {
	    Lex->col_list.empty();		/* Alloced by sql_alloc */
	  }
    break;

  case 176:
#line 1304 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->key_list.push_back(new Key(yyvsp[-5].key_type,yyvsp[-4].simple_string, yyvsp[-3].key_alg, 0, lex->col_list));
	    lex->col_list.empty();		/* Alloced by sql_alloc */
	  }
    break;

  case 177:
#line 1310 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    const char *key_name= yyvsp[-4].simple_string ? yyvsp[-4].simple_string:yyvsp[-6].simple_string;
	    lex->key_list.push_back(new Key(yyvsp[-5].key_type, key_name, yyvsp[-3].key_alg, 0,
				    lex->col_list));
	    lex->col_list.empty();		/* Alloced by sql_alloc */
	  }
    break;

  case 178:
#line 1318 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->key_list.push_back(new foreign_key(yyvsp[-4].simple_string ? yyvsp[-4].simple_string:yyvsp[-7].simple_string, lex->col_list,
				    yyvsp[0].table,
				    lex->ref_list,
				    lex->fk_delete_opt,
				    lex->fk_update_opt,
				    lex->fk_match_option));
	    lex->key_list.push_back(new Key(Key::MULTIPLE, yyvsp[-4].simple_string ? yyvsp[-4].simple_string : yyvsp[-7].simple_string,
					    HA_KEY_ALG_UNDEF, 1,
					    lex->col_list));
	    lex->col_list.empty();		/* Alloced by sql_alloc */
	  }
    break;

  case 179:
#line 1332 "sql_yacc.yy"
    {
	    Lex->col_list.empty();		/* Alloced by sql_alloc */
	  }
    break;

  case 180:
#line 1336 "sql_yacc.yy"
    {
	    Lex->col_list.empty();		/* Alloced by sql_alloc */
	  }
    break;

  case 184:
#line 1351 "sql_yacc.yy"
    { yyval.simple_string=(char*) 0; }
    break;

  case 185:
#line 1352 "sql_yacc.yy"
    { yyval.simple_string= yyvsp[0].simple_string; }
    break;

  case 186:
#line 1356 "sql_yacc.yy"
    { yyval.simple_string=yyvsp[0].simple_string; }
    break;

  case 187:
#line 1361 "sql_yacc.yy"
    {
	   LEX *lex=Lex;
	   lex->length=lex->dec=0; lex->type=0;
	   lex->default_value= lex->on_update_value= 0;
	   lex->comment=0;
	   lex->charset=NULL;
	 }
    break;

  case 188:
#line 1369 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  if (add_field_to_list(lex->thd, yyvsp[-3].lex_str.str,
				(enum enum_field_types) yyvsp[-1].num,
				lex->length,lex->dec,lex->type,
				lex->default_value, lex->on_update_value, 
                                lex->comment,
				lex->change,&lex->interval_list,lex->charset,
				lex->uint_geom_type))
	    YYABORT;
	}
    break;

  case 189:
#line 1382 "sql_yacc.yy"
    { yyval.num=yyvsp[-2].num; }
    break;

  case 190:
#line 1383 "sql_yacc.yy"
    { yyval.num=yyvsp[-2].num; }
    break;

  case 191:
#line 1384 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_FLOAT; }
    break;

  case 192:
#line 1385 "sql_yacc.yy"
    { Lex->length=(char*) "1";
					  yyval.num=FIELD_TYPE_TINY; }
    break;

  case 193:
#line 1387 "sql_yacc.yy"
    { Lex->length=(char*) "1";
					  yyval.num=FIELD_TYPE_TINY; }
    break;

  case 194:
#line 1389 "sql_yacc.yy"
    { Lex->length=(char*) "1";
					  yyval.num=FIELD_TYPE_TINY; }
    break;

  case 195:
#line 1391 "sql_yacc.yy"
    { Lex->length=yyvsp[-2].lex_str.str;
					  yyval.num=FIELD_TYPE_STRING; }
    break;

  case 196:
#line 1393 "sql_yacc.yy"
    { Lex->length=(char*) "1";
					  yyval.num=FIELD_TYPE_STRING; }
    break;

  case 197:
#line 1395 "sql_yacc.yy"
    { Lex->length=yyvsp[-1].lex_str.str;
					  yyval.num=FIELD_TYPE_STRING;
					  Lex->charset=national_charset_info; }
    break;

  case 198:
#line 1398 "sql_yacc.yy"
    { Lex->length=(char*) "1";
					  yyval.num=FIELD_TYPE_STRING;
					  Lex->charset=national_charset_info; }
    break;

  case 199:
#line 1401 "sql_yacc.yy"
    { Lex->length=yyvsp[-1].lex_str.str;
					  Lex->charset=&my_charset_bin;
					  yyval.num=FIELD_TYPE_STRING; }
    break;

  case 200:
#line 1404 "sql_yacc.yy"
    { Lex->length= (char*) "1";
					  Lex->charset=&my_charset_bin;
					  yyval.num=FIELD_TYPE_STRING; }
    break;

  case 201:
#line 1407 "sql_yacc.yy"
    { Lex->length=yyvsp[-2].lex_str.str;
					  yyval.num=FIELD_TYPE_VAR_STRING; }
    break;

  case 202:
#line 1409 "sql_yacc.yy"
    { Lex->length=yyvsp[-1].lex_str.str;
					  yyval.num=FIELD_TYPE_VAR_STRING;
					  Lex->charset=national_charset_info; }
    break;

  case 203:
#line 1412 "sql_yacc.yy"
    { Lex->length=yyvsp[-1].lex_str.str;
					  Lex->charset=&my_charset_bin;
					  yyval.num=FIELD_TYPE_VAR_STRING; }
    break;

  case 204:
#line 1415 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_YEAR; }
    break;

  case 205:
#line 1416 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_DATE; }
    break;

  case 206:
#line 1417 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_TIME; }
    break;

  case 207:
#line 1419 "sql_yacc.yy"
    {
	    if (YYTHD->variables.sql_mode & MODE_MAXDB)
	      yyval.num=FIELD_TYPE_DATETIME;
	    else
            {
              /* 
                Unlike other types TIMESTAMP fields are NOT NULL by default.
              */
              Lex->type|= NOT_NULL_FLAG;
	      yyval.num=FIELD_TYPE_TIMESTAMP;
            }
	   }
    break;

  case 208:
#line 1431 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_DATETIME; }
    break;

  case 209:
#line 1432 "sql_yacc.yy"
    { Lex->charset=&my_charset_bin;
					  yyval.num=FIELD_TYPE_TINY_BLOB; }
    break;

  case 210:
#line 1434 "sql_yacc.yy"
    { Lex->charset=&my_charset_bin;
					  yyval.num=FIELD_TYPE_BLOB; }
    break;

  case 211:
#line 1436 "sql_yacc.yy"
    { 
#ifdef HAVE_SPATIAL
					  Lex->charset=&my_charset_bin;
					  Lex->uint_geom_type= (uint)yyvsp[0].num;
					  yyval.num=FIELD_TYPE_GEOMETRY;
#else
	                                  net_printf(Lex->thd, ER_FEATURE_DISABLED,
			                             sym_group_geom.name,
	                                             sym_group_geom.needed_define);
					  YYABORT;
#endif
					}
    break;

  case 212:
#line 1448 "sql_yacc.yy"
    { Lex->charset=&my_charset_bin;
					  yyval.num=FIELD_TYPE_MEDIUM_BLOB; }
    break;

  case 213:
#line 1450 "sql_yacc.yy"
    { Lex->charset=&my_charset_bin;
					  yyval.num=FIELD_TYPE_LONG_BLOB; }
    break;

  case 214:
#line 1452 "sql_yacc.yy"
    { Lex->charset=&my_charset_bin;
					  yyval.num=FIELD_TYPE_MEDIUM_BLOB; }
    break;

  case 215:
#line 1454 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_MEDIUM_BLOB; }
    break;

  case 216:
#line 1455 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_TINY_BLOB; }
    break;

  case 217:
#line 1456 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_BLOB; }
    break;

  case 218:
#line 1457 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_MEDIUM_BLOB; }
    break;

  case 219:
#line 1458 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_LONG_BLOB; }
    break;

  case 220:
#line 1460 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_DECIMAL;}
    break;

  case 221:
#line 1462 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_DECIMAL;}
    break;

  case 222:
#line 1464 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_DECIMAL;}
    break;

  case 223:
#line 1465 "sql_yacc.yy"
    {Lex->interval_list.empty();}
    break;

  case 224:
#line 1466 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_ENUM; }
    break;

  case 225:
#line 1467 "sql_yacc.yy"
    { Lex->interval_list.empty();}
    break;

  case 226:
#line 1468 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_SET; }
    break;

  case 227:
#line 1469 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_MEDIUM_BLOB; }
    break;

  case 228:
#line 1471 "sql_yacc.yy"
    {
	    yyval.num=FIELD_TYPE_LONGLONG;
	    Lex->type|= (AUTO_INCREMENT_FLAG | NOT_NULL_FLAG | UNSIGNED_FLAG |
		         UNIQUE_FLAG);
	  }
    break;

  case 229:
#line 1479 "sql_yacc.yy"
    { yyval.num= Field::GEOM_GEOMETRY; }
    break;

  case 230:
#line 1480 "sql_yacc.yy"
    { yyval.num= Field::GEOM_GEOMETRYCOLLECTION; }
    break;

  case 231:
#line 1481 "sql_yacc.yy"
    { yyval.num= Field::GEOM_POINT; }
    break;

  case 232:
#line 1482 "sql_yacc.yy"
    { yyval.num= Field::GEOM_MULTIPOINT; }
    break;

  case 233:
#line 1483 "sql_yacc.yy"
    { yyval.num= Field::GEOM_LINESTRING; }
    break;

  case 234:
#line 1484 "sql_yacc.yy"
    { yyval.num= Field::GEOM_MULTILINESTRING; }
    break;

  case 235:
#line 1485 "sql_yacc.yy"
    { yyval.num= Field::GEOM_POLYGON; }
    break;

  case 236:
#line 1486 "sql_yacc.yy"
    { yyval.num= Field::GEOM_MULTIPOLYGON; }
    break;

  case 237:
#line 1490 "sql_yacc.yy"
    {}
    break;

  case 238:
#line 1494 "sql_yacc.yy"
    {}
    break;

  case 239:
#line 1495 "sql_yacc.yy"
    {}
    break;

  case 240:
#line 1499 "sql_yacc.yy"
    {}
    break;

  case 241:
#line 1500 "sql_yacc.yy"
    {}
    break;

  case 242:
#line 1504 "sql_yacc.yy"
    {}
    break;

  case 243:
#line 1505 "sql_yacc.yy"
    {}
    break;

  case 244:
#line 1506 "sql_yacc.yy"
    {}
    break;

  case 245:
#line 1507 "sql_yacc.yy"
    {}
    break;

  case 246:
#line 1508 "sql_yacc.yy"
    {}
    break;

  case 247:
#line 1512 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_LONG; }
    break;

  case 248:
#line 1513 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_TINY; }
    break;

  case 249:
#line 1514 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_SHORT; }
    break;

  case 250:
#line 1515 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_INT24; }
    break;

  case 251:
#line 1516 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_LONGLONG; }
    break;

  case 252:
#line 1519 "sql_yacc.yy"
    { yyval.num= YYTHD->variables.sql_mode & MODE_REAL_AS_FLOAT ?
			      FIELD_TYPE_FLOAT : FIELD_TYPE_DOUBLE; }
    break;

  case 253:
#line 1521 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_DOUBLE; }
    break;

  case 254:
#line 1522 "sql_yacc.yy"
    { yyval.num=FIELD_TYPE_DOUBLE; }
    break;

  case 255:
#line 1526 "sql_yacc.yy"
    {}
    break;

  case 256:
#line 1527 "sql_yacc.yy"
    { Lex->length=yyvsp[-1].lex_str.str; }
    break;

  case 257:
#line 1528 "sql_yacc.yy"
    {}
    break;

  case 258:
#line 1532 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->length=yyvsp[-3].lex_str.str; lex->dec=yyvsp[-1].lex_str.str;
	}
    break;

  case 259:
#line 1538 "sql_yacc.yy"
    {}
    break;

  case 260:
#line 1539 "sql_yacc.yy"
    {}
    break;

  case 261:
#line 1542 "sql_yacc.yy"
    {}
    break;

  case 262:
#line 1543 "sql_yacc.yy"
    {}
    break;

  case 263:
#line 1546 "sql_yacc.yy"
    {}
    break;

  case 264:
#line 1547 "sql_yacc.yy"
    { Lex->type|= UNSIGNED_FLAG;}
    break;

  case 265:
#line 1548 "sql_yacc.yy"
    { Lex->type|= UNSIGNED_FLAG | ZEROFILL_FLAG; }
    break;

  case 266:
#line 1551 "sql_yacc.yy"
    { Lex->length=(char*) 0; }
    break;

  case 267:
#line 1552 "sql_yacc.yy"
    { Lex->length= yyvsp[-1].lex_str.str; }
    break;

  case 268:
#line 1555 "sql_yacc.yy"
    {}
    break;

  case 269:
#line 1556 "sql_yacc.yy"
    {}
    break;

  case 270:
#line 1559 "sql_yacc.yy"
    {}
    break;

  case 271:
#line 1560 "sql_yacc.yy"
    {}
    break;

  case 272:
#line 1563 "sql_yacc.yy"
    {}
    break;

  case 274:
#line 1567 "sql_yacc.yy"
    { Lex->type&= ~ NOT_NULL_FLAG; }
    break;

  case 275:
#line 1568 "sql_yacc.yy"
    { Lex->type|= NOT_NULL_FLAG; }
    break;

  case 276:
#line 1569 "sql_yacc.yy"
    { Lex->default_value=yyvsp[0].item; }
    break;

  case 277:
#line 1571 "sql_yacc.yy"
    { Lex->on_update_value= new Item_func_now_local(); }
    break;

  case 278:
#line 1572 "sql_yacc.yy"
    { Lex->type|= AUTO_INCREMENT_FLAG | NOT_NULL_FLAG; }
    break;

  case 279:
#line 1574 "sql_yacc.yy"
    { 
	    LEX *lex=Lex;
	    lex->type|= AUTO_INCREMENT_FLAG | NOT_NULL_FLAG | UNIQUE_FLAG; 
	    lex->alter_info.flags|= ALTER_ADD_INDEX; 
	  }
    break;

  case 280:
#line 1580 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->type|= PRI_KEY_FLAG | NOT_NULL_FLAG; 
	    lex->alter_info.flags|= ALTER_ADD_INDEX; 
	  }
    break;

  case 281:
#line 1586 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->type|= UNIQUE_FLAG; 
	    lex->alter_info.flags|= ALTER_ADD_INDEX; 
	  }
    break;

  case 282:
#line 1592 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->type|= UNIQUE_KEY_FLAG; 
	    lex->alter_info.flags|= ALTER_ADD_INDEX; 
	  }
    break;

  case 283:
#line 1597 "sql_yacc.yy"
    { Lex->comment= &yyvsp[0].lex_str; }
    break;

  case 284:
#line 1598 "sql_yacc.yy"
    { Lex->type|= BINCMP_FLAG; }
    break;

  case 285:
#line 1600 "sql_yacc.yy"
    {
	    if (Lex->charset && !my_charset_same(Lex->charset,yyvsp[0].charset))
	    {
	      net_printf(YYTHD,ER_COLLATION_CHARSET_MISMATCH,
			 yyvsp[0].charset->name,Lex->charset->csname);
	      YYABORT;
	    }
	    else
	    {
	      Lex->charset=yyvsp[0].charset;
	    }
	  }
    break;

  case 286:
#line 1615 "sql_yacc.yy"
    { yyval.item= new Item_func_now_local(); }
    break;

  case 287:
#line 1616 "sql_yacc.yy"
    { yyval.item=yyvsp[0].item; }
    break;

  case 288:
#line 1620 "sql_yacc.yy"
    {}
    break;

  case 289:
#line 1621 "sql_yacc.yy"
    {}
    break;

  case 290:
#line 1626 "sql_yacc.yy"
    {
	  if (!(yyval.charset=get_charset_by_csname(yyvsp[0].lex_str.str,MY_CS_PRIMARY,MYF(0))))
	  {
	    net_printf(YYTHD,ER_UNKNOWN_CHARACTER_SET,yyvsp[0].lex_str.str);
	    YYABORT;
	  }
	}
    break;

  case 291:
#line 1633 "sql_yacc.yy"
    { yyval.charset= &my_charset_bin; }
    break;

  case 292:
#line 1637 "sql_yacc.yy"
    { yyval.charset=yyvsp[0].charset;   }
    break;

  case 293:
#line 1638 "sql_yacc.yy"
    { yyval.charset=NULL; }
    break;

  case 294:
#line 1643 "sql_yacc.yy"
    {
	  if (!(yyval.charset=get_charset_by_csname(yyvsp[0].lex_str.str,MY_CS_PRIMARY,MYF(0))) &&
	      !(yyval.charset=get_old_charset_by_name(yyvsp[0].lex_str.str)))
	  {
	    net_printf(YYTHD,ER_UNKNOWN_CHARACTER_SET,yyvsp[0].lex_str.str);
	    YYABORT;
	  }
	}
    break;

  case 295:
#line 1651 "sql_yacc.yy"
    { yyval.charset= &my_charset_bin; }
    break;

  case 296:
#line 1655 "sql_yacc.yy"
    { yyval.charset=yyvsp[0].charset;   }
    break;

  case 297:
#line 1656 "sql_yacc.yy"
    { yyval.charset=NULL; }
    break;

  case 298:
#line 1660 "sql_yacc.yy"
    {
	  if (!(yyval.charset=get_charset_by_name(yyvsp[0].lex_str.str,MYF(0))))
	  {
	    net_printf(YYTHD,ER_UNKNOWN_COLLATION,yyvsp[0].lex_str.str);
	    YYABORT;
	  }
	}
    break;

  case 299:
#line 1669 "sql_yacc.yy"
    { yyval.charset=NULL; }
    break;

  case 300:
#line 1670 "sql_yacc.yy"
    { yyval.charset=yyvsp[0].charset; }
    break;

  case 301:
#line 1674 "sql_yacc.yy"
    { yyval.charset=yyvsp[0].charset;   }
    break;

  case 302:
#line 1675 "sql_yacc.yy"
    { yyval.charset=NULL; }
    break;

  case 303:
#line 1678 "sql_yacc.yy"
    {}
    break;

  case 304:
#line 1679 "sql_yacc.yy"
    {}
    break;

  case 305:
#line 1682 "sql_yacc.yy"
    { Lex->charset=NULL; }
    break;

  case 306:
#line 1683 "sql_yacc.yy"
    { Lex->charset=&my_charset_latin1; }
    break;

  case 307:
#line 1684 "sql_yacc.yy"
    { Lex->charset=&my_charset_bin; }
    break;

  case 308:
#line 1686 "sql_yacc.yy"
    {
	  if (!(Lex->charset=get_charset_by_csname("ucs2",MY_CS_PRIMARY,MYF(0))))
	  {
	    net_printf(YYTHD,ER_UNKNOWN_CHARACTER_SET,"ucs2");
	    YYABORT;
	  }
	}
    break;

  case 309:
#line 1693 "sql_yacc.yy"
    { Lex->charset=yyvsp[0].charset; }
    break;

  case 312:
#line 1702 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->fk_delete_opt= lex->fk_update_opt= lex->fk_match_option= 0;
	  lex->ref_list.empty();
	}
    break;

  case 313:
#line 1708 "sql_yacc.yy"
    {
	  yyval.table=yyvsp[-2].table;
	}
    break;

  case 314:
#line 1713 "sql_yacc.yy"
    {}
    break;

  case 315:
#line 1714 "sql_yacc.yy"
    {}
    break;

  case 316:
#line 1717 "sql_yacc.yy"
    { Lex->ref_list.push_back(new key_part_spec(yyvsp[0].lex_str.str)); }
    break;

  case 317:
#line 1718 "sql_yacc.yy"
    { Lex->ref_list.push_back(new key_part_spec(yyvsp[0].lex_str.str)); }
    break;

  case 318:
#line 1722 "sql_yacc.yy"
    {}
    break;

  case 319:
#line 1723 "sql_yacc.yy"
    {}
    break;

  case 320:
#line 1726 "sql_yacc.yy"
    {}
    break;

  case 321:
#line 1727 "sql_yacc.yy"
    {}
    break;

  case 322:
#line 1730 "sql_yacc.yy"
    { Lex->fk_delete_opt= yyvsp[0].num; }
    break;

  case 323:
#line 1731 "sql_yacc.yy"
    { Lex->fk_update_opt= yyvsp[0].num; }
    break;

  case 324:
#line 1732 "sql_yacc.yy"
    { Lex->fk_match_option= foreign_key::FK_MATCH_FULL; }
    break;

  case 325:
#line 1733 "sql_yacc.yy"
    { Lex->fk_match_option= foreign_key::FK_MATCH_PARTIAL; }
    break;

  case 326:
#line 1734 "sql_yacc.yy"
    { Lex->fk_match_option= foreign_key::FK_MATCH_SIMPLE; }
    break;

  case 327:
#line 1737 "sql_yacc.yy"
    { yyval.num= (int) foreign_key::FK_OPTION_RESTRICT; }
    break;

  case 328:
#line 1738 "sql_yacc.yy"
    { yyval.num= (int) foreign_key::FK_OPTION_CASCADE; }
    break;

  case 329:
#line 1739 "sql_yacc.yy"
    { yyval.num= (int) foreign_key::FK_OPTION_SET_NULL; }
    break;

  case 330:
#line 1740 "sql_yacc.yy"
    { yyval.num= (int) foreign_key::FK_OPTION_NO_ACTION; }
    break;

  case 331:
#line 1741 "sql_yacc.yy"
    { yyval.num= (int) foreign_key::FK_OPTION_DEFAULT;  }
    break;

  case 332:
#line 1744 "sql_yacc.yy"
    { yyval.key_type= Key::MULTIPLE; }
    break;

  case 333:
#line 1745 "sql_yacc.yy"
    { yyval.key_type= Key::FULLTEXT; }
    break;

  case 334:
#line 1747 "sql_yacc.yy"
    {
#ifdef HAVE_SPATIAL
	    yyval.key_type= Key::SPATIAL;
#else
	    net_printf(Lex->thd, ER_FEATURE_DISABLED,
		       sym_group_geom.name, sym_group_geom.needed_define);
	    YYABORT;
#endif
	  }
    break;

  case 335:
#line 1758 "sql_yacc.yy"
    { yyval.key_type= Key::PRIMARY; }
    break;

  case 336:
#line 1759 "sql_yacc.yy"
    { yyval.key_type= Key::UNIQUE; }
    break;

  case 337:
#line 1762 "sql_yacc.yy"
    {}
    break;

  case 338:
#line 1763 "sql_yacc.yy"
    {}
    break;

  case 339:
#line 1766 "sql_yacc.yy"
    {}
    break;

  case 341:
#line 1771 "sql_yacc.yy"
    {}
    break;

  case 342:
#line 1772 "sql_yacc.yy"
    {}
    break;

  case 343:
#line 1773 "sql_yacc.yy"
    {}
    break;

  case 344:
#line 1776 "sql_yacc.yy"
    { yyval.key_type= Key::MULTIPLE; }
    break;

  case 345:
#line 1777 "sql_yacc.yy"
    { yyval.key_type= Key::UNIQUE; }
    break;

  case 346:
#line 1778 "sql_yacc.yy"
    { yyval.key_type= Key::FULLTEXT;}
    break;

  case 347:
#line 1780 "sql_yacc.yy"
    {
#ifdef HAVE_SPATIAL
	    yyval.key_type= Key::SPATIAL;
#else
	    net_printf(Lex->thd, ER_FEATURE_DISABLED,
	               sym_group_geom.name, sym_group_geom.needed_define);
	    YYABORT;
#endif
	  }
    break;

  case 348:
#line 1792 "sql_yacc.yy"
    { yyval.key_alg= HA_KEY_ALG_UNDEF; }
    break;

  case 349:
#line 1793 "sql_yacc.yy"
    { yyval.key_alg= yyvsp[0].key_alg; }
    break;

  case 350:
#line 1794 "sql_yacc.yy"
    { yyval.key_alg= yyvsp[0].key_alg; }
    break;

  case 351:
#line 1797 "sql_yacc.yy"
    { yyval.key_alg= HA_KEY_ALG_BTREE; }
    break;

  case 352:
#line 1799 "sql_yacc.yy"
    {
	    yyval.key_alg= HA_KEY_ALG_RTREE;
	  }
    break;

  case 353:
#line 1802 "sql_yacc.yy"
    { yyval.key_alg= HA_KEY_ALG_HASH; }
    break;

  case 354:
#line 1805 "sql_yacc.yy"
    { Lex->col_list.push_back(yyvsp[-1].key_part); }
    break;

  case 355:
#line 1806 "sql_yacc.yy"
    { Lex->col_list.push_back(yyvsp[-1].key_part); }
    break;

  case 356:
#line 1809 "sql_yacc.yy"
    { yyval.key_part=new key_part_spec(yyvsp[0].lex_str.str); }
    break;

  case 357:
#line 1811 "sql_yacc.yy"
    {
          int key_part_len= atoi(yyvsp[-1].lex_str.str);
#if MYSQL_VERSION_ID < 50000
          if (!key_part_len)
          {
            my_printf_error(ER_UNKNOWN_ERROR,
                            "Key part '%s' length cannot be 0",
                            MYF(0), yyvsp[-3].lex_str.str);
          }
#endif
          yyval.key_part=new key_part_spec(yyvsp[-3].lex_str.str,(uint) key_part_len);
        }
    break;

  case 358:
#line 1825 "sql_yacc.yy"
    { yyval.simple_string=(char*) 0; }
    break;

  case 359:
#line 1826 "sql_yacc.yy"
    { yyval.simple_string=yyvsp[0].lex_str.str; }
    break;

  case 360:
#line 1829 "sql_yacc.yy"
    { yyval.lex_str.str= 0; yyval.lex_str.length= 0; }
    break;

  case 361:
#line 1830 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str; }
    break;

  case 362:
#line 1833 "sql_yacc.yy"
    { Lex->interval_list.push_back(yyvsp[0].string); }
    break;

  case 363:
#line 1834 "sql_yacc.yy"
    { Lex->interval_list.push_back(yyvsp[0].string); }
    break;

  case 364:
#line 1842 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  LEX *lex= thd->lex;
	  lex->sql_command= SQLCOM_ALTER_TABLE;
	  lex->name= 0;
	  lex->duplicates= DUP_ERROR; 
	  if (!lex->select_lex.add_table_to_list(thd, yyvsp[0].table, NULL,
						 TL_OPTION_UPDATING))
	    YYABORT;
	  lex->create_list.empty();
	  lex->key_list.empty();
	  lex->col_list.empty();
          lex->select_lex.init_order();
	  lex->select_lex.db=lex->name=0;
	  bzero((char*) &lex->create_info,sizeof(lex->create_info));
	  lex->create_info.db_type= DB_TYPE_DEFAULT;
	  lex->create_info.default_table_charset= NULL;
	  lex->create_info.row_type= ROW_TYPE_NOT_USED;
	  lex->alter_info.reset();          
	  lex->alter_info.is_simple= 1;
	  lex->alter_info.flags= 0;
	}
    break;

  case 365:
#line 1865 "sql_yacc.yy"
    {}
    break;

  case 366:
#line 1867 "sql_yacc.yy"
    {
            Lex->create_info.default_table_charset= NULL;
            Lex->create_info.used_fields= 0;
          }
    break;

  case 367:
#line 1872 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command=SQLCOM_ALTER_DB;
	    lex->name= yyvsp[-2].simple_string;
	  }
    break;

  case 368:
#line 1880 "sql_yacc.yy"
    { yyval.simple_string= 0; }
    break;

  case 369:
#line 1881 "sql_yacc.yy"
    { yyval.simple_string= yyvsp[0].lex_str.str; }
    break;

  case 371:
#line 1885 "sql_yacc.yy"
    { Lex->alter_info.tablespace_op= DISCARD_TABLESPACE; }
    break;

  case 372:
#line 1886 "sql_yacc.yy"
    { Lex->alter_info.tablespace_op= IMPORT_TABLESPACE; }
    break;

  case 375:
#line 1892 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->change=0; 
	  lex->alter_info.flags|= ALTER_ADD_COLUMN; 
	}
    break;

  case 376:
#line 1899 "sql_yacc.yy"
    { Lex->alter_info.is_simple= 0; }
    break;

  case 377:
#line 1901 "sql_yacc.yy"
    { 
	    LEX *lex=Lex;
	    lex->alter_info.is_simple= 0; 
	    lex->alter_info.flags|= ALTER_ADD_INDEX; 
	  }
    break;

  case 378:
#line 1906 "sql_yacc.yy"
    { Lex->alter_info.is_simple= 0; }
    break;

  case 379:
#line 1908 "sql_yacc.yy"
    {
	     LEX *lex=Lex;
	     lex->change= yyvsp[0].lex_str.str; 
	     lex->alter_info.is_simple= 0;
	     lex->alter_info.flags|= ALTER_CHANGE_COLUMN;
	  }
    break;

  case 381:
#line 1916 "sql_yacc.yy"
    {
            LEX *lex=Lex;
            lex->length=lex->dec=0; lex->type=0;
            lex->default_value= lex->on_update_value= 0;
	    lex->comment=0;
	    lex->charset= NULL;
            lex->alter_info.is_simple= 0;
	    lex->alter_info.flags|= ALTER_CHANGE_COLUMN;
          }
    break;

  case 382:
#line 1926 "sql_yacc.yy"
    {
            LEX *lex=Lex;
            if (add_field_to_list(lex->thd,yyvsp[-3].lex_str.str,
                                  (enum enum_field_types) yyvsp[-1].num,
                                  lex->length,lex->dec,lex->type,
                                  lex->default_value, lex->on_update_value,
                                  lex->comment,
				  yyvsp[-3].lex_str.str, &lex->interval_list, lex->charset,
				  lex->uint_geom_type))
	       YYABORT;
          }
    break;

  case 384:
#line 1939 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->alter_info.drop_list.push_back(new Alter_drop(Alter_drop::COLUMN,
	    			                               yyvsp[-1].lex_str.str)); 
	    lex->alter_info.is_simple= 0;
	    lex->alter_info.flags|= ALTER_DROP_COLUMN;
	  }
    break;

  case 385:
#line 1946 "sql_yacc.yy"
    { Lex->alter_info.is_simple= 0; }
    break;

  case 386:
#line 1948 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->alter_info.drop_list.push_back(new Alter_drop(Alter_drop::KEY,
				               primary_key_name));
	    lex->alter_info.is_simple= 0;
	    lex->alter_info.flags|= ALTER_DROP_INDEX;
	  }
    break;

  case 387:
#line 1956 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->alter_info.drop_list.push_back(new Alter_drop(Alter_drop::KEY,
					                       yyvsp[0].lex_str.str));
	    lex->alter_info.is_simple= 0;
	    lex->alter_info.flags|= ALTER_DROP_INDEX;
	  }
    break;

  case 388:
#line 1963 "sql_yacc.yy"
    { Lex->alter_info.keys_onoff= DISABLE; }
    break;

  case 389:
#line 1964 "sql_yacc.yy"
    { Lex->alter_info.keys_onoff= ENABLE; }
    break;

  case 390:
#line 1966 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->alter_info.alter_list.push_back(new Alter_column(yyvsp[-3].lex_str.str,yyvsp[0].item));
	    lex->alter_info.is_simple= 0;
	    lex->alter_info.flags|= ALTER_CHANGE_COLUMN;
	  }
    break;

  case 391:
#line 1973 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->alter_info.alter_list.push_back(new Alter_column(yyvsp[-2].lex_str.str,
                                                                  (Item*) 0));
	    lex->alter_info.is_simple= 0;
	    lex->alter_info.flags|= ALTER_CHANGE_COLUMN;
	  }
    break;

  case 392:
#line 1981 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->select_lex.db=yyvsp[0].table->db.str;
	    lex->name= yyvsp[0].table->table.str;
            if (check_table_name(yyvsp[0].table->table.str,yyvsp[0].table->table.length) ||
                yyvsp[0].table->db.str && check_db_name(yyvsp[0].table->db.str))
            {
              net_printf(lex->thd,ER_WRONG_TABLE_NAME,yyvsp[0].table->table.str);
              YYABORT;
            }
	    lex->alter_info.flags|= ALTER_RENAME;
	  }
    break;

  case 393:
#line 1994 "sql_yacc.yy"
    {
	    if (!yyvsp[-1].charset)
	    {
	      THD *thd= YYTHD;
	      yyvsp[-1].charset= thd->variables.collation_database;
	    }
	    yyvsp[0].charset= yyvsp[0].charset ? yyvsp[0].charset : yyvsp[-1].charset;
	    if (!my_charset_same(yyvsp[-1].charset,yyvsp[0].charset))
	    {
	      net_printf(YYTHD,ER_COLLATION_CHARSET_MISMATCH,
			 yyvsp[0].charset->name,yyvsp[-1].charset->csname);
	      YYABORT;
	    }
	    LEX *lex= Lex;
	    lex->create_info.table_charset= 
	      lex->create_info.default_table_charset= yyvsp[0].charset;
	    lex->create_info.used_fields|= (HA_CREATE_USED_CHARSET |
					    HA_CREATE_USED_DEFAULT_CHARSET);
	    lex->alter_info.is_simple= 0;
	  }
    break;

  case 394:
#line 2015 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->alter_info.is_simple= 0; 
	    lex->alter_info.flags|= ALTER_OPTIONS;
	  }
    break;

  case 395:
#line 2021 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->alter_info.is_simple= 0; 
	    lex->alter_info.flags|= ALTER_ORDER;
	  }
    break;

  case 396:
#line 2028 "sql_yacc.yy"
    {}
    break;

  case 397:
#line 2029 "sql_yacc.yy"
    {}
    break;

  case 398:
#line 2032 "sql_yacc.yy"
    { Lex->ignore= 0;}
    break;

  case 399:
#line 2033 "sql_yacc.yy"
    { Lex->ignore= 1;}
    break;

  case 400:
#line 2037 "sql_yacc.yy"
    {}
    break;

  case 401:
#line 2038 "sql_yacc.yy"
    {}
    break;

  case 402:
#line 2039 "sql_yacc.yy"
    {}
    break;

  case 403:
#line 2042 "sql_yacc.yy"
    {}
    break;

  case 404:
#line 2043 "sql_yacc.yy"
    { store_position_for_column(yyvsp[0].lex_str.str); }
    break;

  case 405:
#line 2044 "sql_yacc.yy"
    { store_position_for_column(first_keyword); }
    break;

  case 406:
#line 2047 "sql_yacc.yy"
    {}
    break;

  case 407:
#line 2048 "sql_yacc.yy"
    {}
    break;

  case 408:
#line 2049 "sql_yacc.yy"
    {}
    break;

  case 409:
#line 2050 "sql_yacc.yy"
    {}
    break;

  case 410:
#line 2058 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
            lex->sql_command = SQLCOM_SLAVE_START;
	    lex->type = 0;
	    /* We'll use mi structure for UNTIL options */
	    bzero((char*) &lex->mi, sizeof(lex->mi));
            /* If you change this code don't forget to update SLAVE START too */
          }
    break;

  case 411:
#line 2067 "sql_yacc.yy"
    {}
    break;

  case 412:
#line 2069 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
            lex->sql_command = SQLCOM_SLAVE_STOP;
	    lex->type = 0;
            /* If you change this code don't forget to update SLAVE STOP too */
          }
    break;

  case 413:
#line 2076 "sql_yacc.yy"
    {
	   LEX *lex=Lex;
           lex->sql_command = SQLCOM_SLAVE_START;
	   lex->type = 0;
	    /* We'll use mi structure for UNTIL options */
	    bzero((char*) &lex->mi, sizeof(lex->mi));
          }
    break;

  case 414:
#line 2084 "sql_yacc.yy"
    {}
    break;

  case 415:
#line 2086 "sql_yacc.yy"
    {
	   LEX *lex=Lex;
           lex->sql_command = SQLCOM_SLAVE_STOP;
	   lex->type = 0;
         }
    break;

  case 416:
#line 2096 "sql_yacc.yy"
    {
           Lex->sql_command = SQLCOM_BEGIN;
           Lex->start_transaction_opt= yyvsp[0].num;
        }
    break;

  case 417:
#line 2103 "sql_yacc.yy"
    { yyval.num = 0; }
    break;

  case 418:
#line 2105 "sql_yacc.yy"
    {
           yyval.num= MYSQL_START_TRANS_OPT_WITH_CONS_SNAPSHOT;
        }
    break;

  case 419:
#line 2111 "sql_yacc.yy"
    { Lex->slave_thd_opt= 0; }
    break;

  case 420:
#line 2113 "sql_yacc.yy"
    {}
    break;

  case 423:
#line 2122 "sql_yacc.yy"
    {}
    break;

  case 424:
#line 2123 "sql_yacc.yy"
    { Lex->slave_thd_opt|=SLAVE_SQL; }
    break;

  case 425:
#line 2124 "sql_yacc.yy"
    { Lex->slave_thd_opt|=SLAVE_IO; }
    break;

  case 426:
#line 2128 "sql_yacc.yy"
    {}
    break;

  case 427:
#line 2130 "sql_yacc.yy"
    {
            LEX *lex=Lex;
            if ((lex->mi.log_file_name || lex->mi.pos) &&
                (lex->mi.relay_log_name || lex->mi.relay_log_pos) ||
                !((lex->mi.log_file_name && lex->mi.pos) ||
                  (lex->mi.relay_log_name && lex->mi.relay_log_pos)))
            {
               send_error(lex->thd, ER_BAD_SLAVE_UNTIL_COND);
               YYABORT;
            }

          }
    break;

  case 430:
#line 2151 "sql_yacc.yy"
    {
	   Lex->sql_command = SQLCOM_RESTORE_TABLE;
	}
    break;

  case 431:
#line 2155 "sql_yacc.yy"
    {
	  Lex->backup_dir = yyvsp[0].lex_str.str;
        }
    break;

  case 432:
#line 2161 "sql_yacc.yy"
    {
	   Lex->sql_command = SQLCOM_BACKUP_TABLE;
	}
    break;

  case 433:
#line 2165 "sql_yacc.yy"
    {
	  Lex->backup_dir = yyvsp[0].lex_str.str;
        }
    break;

  case 434:
#line 2171 "sql_yacc.yy"
    {
	   LEX *lex=Lex;
	   lex->sql_command = SQLCOM_CHECKSUM;
	}
    break;

  case 435:
#line 2176 "sql_yacc.yy"
    {}
    break;

  case 436:
#line 2180 "sql_yacc.yy"
    { Lex->check_opt.flags= 0; }
    break;

  case 437:
#line 2181 "sql_yacc.yy"
    { Lex->check_opt.flags= T_QUICK; }
    break;

  case 438:
#line 2182 "sql_yacc.yy"
    { Lex->check_opt.flags= T_EXTEND; }
    break;

  case 439:
#line 2187 "sql_yacc.yy"
    {
	   LEX *lex=Lex;
	   lex->sql_command = SQLCOM_REPAIR;
           lex->no_write_to_binlog= yyvsp[-1].num;
	   lex->check_opt.init();
	}
    break;

  case 440:
#line 2194 "sql_yacc.yy"
    {}
    break;

  case 441:
#line 2198 "sql_yacc.yy"
    { Lex->check_opt.flags = T_MEDIUM; }
    break;

  case 442:
#line 2199 "sql_yacc.yy"
    {}
    break;

  case 443:
#line 2202 "sql_yacc.yy"
    {}
    break;

  case 444:
#line 2203 "sql_yacc.yy"
    {}
    break;

  case 445:
#line 2206 "sql_yacc.yy"
    { Lex->check_opt.flags|= T_QUICK; }
    break;

  case 446:
#line 2207 "sql_yacc.yy"
    { Lex->check_opt.flags|= T_EXTEND; }
    break;

  case 447:
#line 2208 "sql_yacc.yy"
    { Lex->check_opt.sql_flags|= TT_USEFRM; }
    break;

  case 448:
#line 2212 "sql_yacc.yy"
    {
	   LEX *lex=Lex;
	   lex->sql_command = SQLCOM_ANALYZE;
           lex->no_write_to_binlog= yyvsp[-1].num;
	   lex->check_opt.init();
	}
    break;

  case 449:
#line 2219 "sql_yacc.yy"
    {}
    break;

  case 450:
#line 2224 "sql_yacc.yy"
    {
	   LEX *lex=Lex;
	   lex->sql_command = SQLCOM_CHECK;
	   lex->check_opt.init();
	}
    break;

  case 451:
#line 2230 "sql_yacc.yy"
    {}
    break;

  case 452:
#line 2234 "sql_yacc.yy"
    { Lex->check_opt.flags = T_MEDIUM; }
    break;

  case 453:
#line 2235 "sql_yacc.yy"
    {}
    break;

  case 454:
#line 2238 "sql_yacc.yy"
    {}
    break;

  case 455:
#line 2239 "sql_yacc.yy"
    {}
    break;

  case 456:
#line 2242 "sql_yacc.yy"
    { Lex->check_opt.flags|= T_QUICK; }
    break;

  case 457:
#line 2243 "sql_yacc.yy"
    { Lex->check_opt.flags|= T_FAST; }
    break;

  case 458:
#line 2244 "sql_yacc.yy"
    { Lex->check_opt.flags|= T_MEDIUM; }
    break;

  case 459:
#line 2245 "sql_yacc.yy"
    { Lex->check_opt.flags|= T_EXTEND; }
    break;

  case 460:
#line 2246 "sql_yacc.yy"
    { Lex->check_opt.flags|= T_CHECK_ONLY_CHANGED; }
    break;

  case 461:
#line 2250 "sql_yacc.yy"
    {
	   LEX *lex=Lex;
	   lex->sql_command = SQLCOM_OPTIMIZE;
           lex->no_write_to_binlog= yyvsp[-1].num;
	   lex->check_opt.init();
	}
    break;

  case 462:
#line 2257 "sql_yacc.yy"
    {}
    break;

  case 463:
#line 2261 "sql_yacc.yy"
    { yyval.num= 0; }
    break;

  case 464:
#line 2262 "sql_yacc.yy"
    { yyval.num= 1; }
    break;

  case 465:
#line 2263 "sql_yacc.yy"
    { yyval.num= 1; }
    break;

  case 466:
#line 2268 "sql_yacc.yy"
    {
	   Lex->sql_command=SQLCOM_RENAME_TABLE;
	}
    break;

  case 467:
#line 2272 "sql_yacc.yy"
    {}
    break;

  case 470:
#line 2281 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  SELECT_LEX *sl= lex->current_select;
	  if (!sl->add_table_to_list(lex->thd, yyvsp[-2].table,NULL,TL_OPTION_UPDATING,
				     TL_IGNORE) ||
	      !sl->add_table_to_list(lex->thd, yyvsp[0].table,NULL,TL_OPTION_UPDATING,
				     TL_IGNORE))
	    YYABORT;
	}
    break;

  case 471:
#line 2293 "sql_yacc.yy"
    {
          LEX *lex=Lex;
          lex->sql_command= SQLCOM_ASSIGN_TO_KEYCACHE;
	  lex->name_and_length= yyvsp[0].lex_str;
        }
    break;

  case 474:
#line 2306 "sql_yacc.yy"
    {
          LEX *lex=Lex;
          SELECT_LEX *sel= &lex->select_lex;
          if (!sel->add_table_to_list(lex->thd, yyvsp[-1].table, NULL, 0,
                                      TL_READ,
                                      sel->get_use_index(),
                                      (List<String> *)0))
            YYABORT;
        }
    break;

  case 475:
#line 2318 "sql_yacc.yy"
    { yyval.lex_str= yyvsp[0].lex_str; }
    break;

  case 476:
#line 2319 "sql_yacc.yy"
    { yyval.lex_str = default_key_cache_base; }
    break;

  case 477:
#line 2324 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->sql_command=SQLCOM_PRELOAD_KEYS;
	}
    break;

  case 478:
#line 2329 "sql_yacc.yy"
    {}
    break;

  case 481:
#line 2338 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  SELECT_LEX *sel= &lex->select_lex;
	  if (!sel->add_table_to_list(lex->thd, yyvsp[-2].table, NULL, yyvsp[0].num,
                                      TL_READ,
                                      sel->get_use_index(),
                                      (List<String> *)0))
            YYABORT;
	}
    break;

  case 482:
#line 2350 "sql_yacc.yy"
    { Select->interval_list.empty(); }
    break;

  case 483:
#line 2352 "sql_yacc.yy"
    {
          LEX *lex=Lex;
          SELECT_LEX *sel= &lex->select_lex;
          sel->use_index= sel->interval_list;
        }
    break;

  case 484:
#line 2360 "sql_yacc.yy"
    { Lex->select_lex.use_index_ptr= 0; }
    break;

  case 485:
#line 2362 "sql_yacc.yy"
    {
            SELECT_LEX *sel= &Lex->select_lex;
	    sel->use_index_ptr= &sel->use_index;
	  }
    break;

  case 486:
#line 2370 "sql_yacc.yy"
    { yyval.num= 0; }
    break;

  case 487:
#line 2371 "sql_yacc.yy"
    { yyval.num= TL_OPTION_IGNORE_LEAVES; }
    break;

  case 488:
#line 2381 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  lex->sql_command= SQLCOM_SELECT;
	  lex->select_lex.resolve_mode= SELECT_LEX::SELECT_MODE;
	}
    break;

  case 491:
#line 2396 "sql_yacc.yy"
    {
	    LEX *lex= Lex;
            SELECT_LEX * sel= lex->current_select;
	    if (sel->set_braces(1))
	    {
	      yyerror(ER(ER_SYNTAX_ERROR));
	      YYABORT;
	    }
	  if (sel->linkage == UNION_TYPE &&
	      !sel->master_unit()->first_select()->braces)
	  {
	    yyerror(ER(ER_SYNTAX_ERROR));
	    YYABORT;
	  }
            /* select in braces, can't contain global parameters */
	    if (sel->master_unit()->fake_select_lex)
              sel->master_unit()->global_parameters=
                 sel->master_unit()->fake_select_lex;
          }
    break;

  case 493:
#line 2419 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
          SELECT_LEX * sel= lex->current_select;
          if (lex->current_select->set_braces(0))
	  {
	    yyerror(ER(ER_SYNTAX_ERROR));
	    YYABORT;
	  }
	  if (sel->linkage == UNION_TYPE &&
	      sel->master_unit()->first_select()->braces)
	  {
	    yyerror(ER(ER_SYNTAX_ERROR));
	    YYABORT;
	  }
	}
    break;

  case 495:
#line 2438 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  SELECT_LEX *sel= lex->current_select;
	  if (sel->linkage != UNION_TYPE)
	    mysql_init_select(lex);
	  lex->current_select->parsing_place= SELECT_LIST;
	}
    break;

  case 496:
#line 2446 "sql_yacc.yy"
    {
	  Select->parsing_place= NO_MATTER;
	}
    break;

  case 498:
#line 2452 "sql_yacc.yy"
    {}
    break;

  case 509:
#line 2477 "sql_yacc.yy"
    { Select->options|= SELECT_STRAIGHT_JOIN; }
    break;

  case 510:
#line 2479 "sql_yacc.yy"
    {
	    if (check_simple_select())
	      YYABORT;
	    Lex->lock_option= TL_READ_HIGH_PRIORITY;
	  }
    break;

  case 511:
#line 2485 "sql_yacc.yy"
    {
            if (Select->options & SELECT_ALL)
            {
              yyerror(ER(ER_SYNTAX_ERROR));
              YYABORT;
            }
            Select->options|= SELECT_DISTINCT; 
	  }
    break;

  case 512:
#line 2493 "sql_yacc.yy"
    { Select->options|= SELECT_SMALL_RESULT; }
    break;

  case 513:
#line 2494 "sql_yacc.yy"
    { Select->options|= SELECT_BIG_RESULT; }
    break;

  case 514:
#line 2496 "sql_yacc.yy"
    {
	    if (check_simple_select())
	      YYABORT;
	    Select->options|= OPTION_BUFFER_RESULT;
	  }
    break;

  case 515:
#line 2502 "sql_yacc.yy"
    {
	    if (check_simple_select())
	      YYABORT;
	    Select->options|= OPTION_FOUND_ROWS;
	  }
    break;

  case 516:
#line 2507 "sql_yacc.yy"
    { Lex->safe_to_cache_query=0; }
    break;

  case 517:
#line 2509 "sql_yacc.yy"
    {
	    Lex->select_lex.options|= OPTION_TO_QUERY_CACHE;
	  }
    break;

  case 518:
#line 2513 "sql_yacc.yy"
    {
            if (Select->options & SELECT_DISTINCT)
            {
              yyerror(ER(ER_SYNTAX_ERROR));
              YYABORT;
            }
            Select->options|= SELECT_ALL; 
	  }
    break;

  case 520:
#line 2526 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->current_select->set_lock_for_tables(TL_WRITE);
	    lex->safe_to_cache_query=0;
	  }
    break;

  case 521:
#line 2532 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->current_select->
	      set_lock_for_tables(TL_READ_WITH_SHARED_LOCKS);
	    lex->safe_to_cache_query=0;
	  }
    break;

  case 524:
#line 2544 "sql_yacc.yy"
    {
	    THD *thd= YYTHD;
	    if (add_item_to_list(thd, new Item_field(NULL, NULL, "*")))
	      YYABORT;
	    (thd->lex->current_select->with_wild)++;
	  }
    break;

  case 525:
#line 2554 "sql_yacc.yy"
    {
	    if (add_item_to_list(YYTHD, yyvsp[-2].item))
	      YYABORT;
	    if (yyvsp[0].lex_str.str)
	      yyvsp[-2].item->set_name(yyvsp[0].lex_str.str,yyvsp[0].lex_str.length,system_charset_info);
	    else if (!yyvsp[-2].item->name)
	      yyvsp[-2].item->set_name(yyvsp[-3].simple_string,(uint) (yyvsp[-1].simple_string - yyvsp[-3].simple_string), YYTHD->charset());
	  }
    break;

  case 526:
#line 2564 "sql_yacc.yy"
    { yyval.simple_string=(char*) Lex->tok_start; }
    break;

  case 527:
#line 2567 "sql_yacc.yy"
    { yyval.simple_string=(char*) Lex->tok_end; }
    break;

  case 528:
#line 2570 "sql_yacc.yy"
    { yyval.item=yyvsp[0].item; }
    break;

  case 529:
#line 2571 "sql_yacc.yy"
    { yyval.item=yyvsp[0].item; }
    break;

  case 530:
#line 2574 "sql_yacc.yy"
    { yyval.lex_str.str=0;}
    break;

  case 531:
#line 2575 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str; }
    break;

  case 532:
#line 2576 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str; }
    break;

  case 533:
#line 2577 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str; }
    break;

  case 534:
#line 2578 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str; }
    break;

  case 535:
#line 2582 "sql_yacc.yy"
    {}
    break;

  case 536:
#line 2583 "sql_yacc.yy"
    {}
    break;

  case 537:
#line 2587 "sql_yacc.yy"
    { yyval.item= yyvsp[0].item; }
    break;

  case 538:
#line 2588 "sql_yacc.yy"
    { yyval.item= yyvsp[0].item; }
    break;

  case 539:
#line 2591 "sql_yacc.yy"
    { yyval.boolfunc2creator = &comp_eq_creator; }
    break;

  case 540:
#line 2592 "sql_yacc.yy"
    { yyval.boolfunc2creator = &comp_ge_creator; }
    break;

  case 541:
#line 2593 "sql_yacc.yy"
    { yyval.boolfunc2creator = &comp_gt_creator; }
    break;

  case 542:
#line 2594 "sql_yacc.yy"
    { yyval.boolfunc2creator = &comp_le_creator; }
    break;

  case 543:
#line 2595 "sql_yacc.yy"
    { yyval.boolfunc2creator = &comp_lt_creator; }
    break;

  case 544:
#line 2596 "sql_yacc.yy"
    { yyval.boolfunc2creator = &comp_ne_creator; }
    break;

  case 545:
#line 2599 "sql_yacc.yy"
    { yyval.num = 1; }
    break;

  case 546:
#line 2600 "sql_yacc.yy"
    { yyval.num = 0; }
    break;

  case 547:
#line 2606 "sql_yacc.yy"
    { yyvsp[-1].item_list->push_front(yyvsp[-4].item); yyval.item= new Item_func_in(*yyvsp[-1].item_list); }
    break;

  case 548:
#line 2608 "sql_yacc.yy"
    { yyvsp[-1].item_list->push_front(yyvsp[-5].item); yyval.item= new Item_func_not(new Item_func_in(*yyvsp[-1].item_list)); }
    break;

  case 549:
#line 2610 "sql_yacc.yy"
    { yyval.item= new Item_in_subselect(yyvsp[-2].item, yyvsp[0].select_lex); }
    break;

  case 550:
#line 2612 "sql_yacc.yy"
    {
            yyval.item= new Item_func_not(new Item_in_subselect(yyvsp[-3].item, yyvsp[0].select_lex));
          }
    break;

  case 551:
#line 2616 "sql_yacc.yy"
    { yyval.item= new Item_func_between(yyvsp[-4].item,yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 552:
#line 2618 "sql_yacc.yy"
    { yyval.item= new Item_func_not(new Item_func_between(yyvsp[-5].item,yyvsp[-2].item,yyvsp[0].item)); }
    break;

  case 553:
#line 2619 "sql_yacc.yy"
    { yyval.item= or_or_concat(YYTHD, yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 554:
#line 2620 "sql_yacc.yy"
    { yyval.item= new Item_cond_or(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 555:
#line 2621 "sql_yacc.yy"
    { yyval.item= new Item_cond_xor(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 556:
#line 2622 "sql_yacc.yy"
    { yyval.item= new Item_cond_and(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 557:
#line 2624 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_eq(new Item_func_soundex(yyvsp[-3].item),
				 new Item_func_soundex(yyvsp[0].item));
	  }
    break;

  case 558:
#line 2629 "sql_yacc.yy"
    { yyval.item= new Item_func_like(yyvsp[-3].item,yyvsp[-1].item,yyvsp[0].item); }
    break;

  case 559:
#line 2631 "sql_yacc.yy"
    { yyval.item= new Item_func_not(new Item_func_like(yyvsp[-4].item,yyvsp[-1].item,yyvsp[0].item));}
    break;

  case 560:
#line 2632 "sql_yacc.yy"
    { yyval.item= new Item_func_regex(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 561:
#line 2634 "sql_yacc.yy"
    { yyval.item= new Item_func_not(new Item_func_regex(yyvsp[-3].item,yyvsp[0].item)); }
    break;

  case 562:
#line 2635 "sql_yacc.yy"
    { yyval.item= new Item_func_isnull(yyvsp[-2].item); }
    break;

  case 563:
#line 2636 "sql_yacc.yy"
    { yyval.item= new Item_func_isnotnull(yyvsp[-3].item); }
    break;

  case 564:
#line 2637 "sql_yacc.yy"
    { yyval.item= new Item_func_equal(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 565:
#line 2638 "sql_yacc.yy"
    { yyval.item= (*yyvsp[-1].boolfunc2creator)(0)->create(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 566:
#line 2640 "sql_yacc.yy"
    {
	  yyval.item= all_any_subquery_creator(yyvsp[-3].item, yyvsp[-2].boolfunc2creator, yyvsp[-1].num, yyvsp[0].select_lex);
	}
    break;

  case 567:
#line 2643 "sql_yacc.yy"
    { yyval.item= new Item_func_shift_left(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 568:
#line 2644 "sql_yacc.yy"
    { yyval.item= new Item_func_shift_right(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 569:
#line 2645 "sql_yacc.yy"
    { yyval.item= new Item_func_plus(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 570:
#line 2646 "sql_yacc.yy"
    { yyval.item= new Item_func_minus(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 571:
#line 2647 "sql_yacc.yy"
    { yyval.item= new Item_func_mul(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 572:
#line 2648 "sql_yacc.yy"
    { yyval.item= new Item_func_div(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 573:
#line 2649 "sql_yacc.yy"
    { yyval.item= new Item_func_int_div(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 574:
#line 2650 "sql_yacc.yy"
    { yyval.item= new Item_func_mod(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 575:
#line 2651 "sql_yacc.yy"
    { yyval.item= new Item_func_bit_or(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 576:
#line 2652 "sql_yacc.yy"
    { yyval.item= new Item_func_bit_xor(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 577:
#line 2653 "sql_yacc.yy"
    { yyval.item= new Item_func_bit_and(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 578:
#line 2654 "sql_yacc.yy"
    { yyval.item= new Item_func_mod(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 579:
#line 2656 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-3].item,yyvsp[-1].item,yyvsp[0].interval,0); }
    break;

  case 580:
#line 2658 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-3].item,yyvsp[-1].item,yyvsp[0].interval,1); }
    break;

  case 581:
#line 2664 "sql_yacc.yy"
    { yyval.item= new Item_func_between(yyvsp[-4].item,yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 582:
#line 2666 "sql_yacc.yy"
    { yyval.item= new Item_func_not(new Item_func_between(yyvsp[-5].item,yyvsp[-2].item,yyvsp[0].item)); }
    break;

  case 583:
#line 2667 "sql_yacc.yy"
    { yyval.item= or_or_concat(YYTHD, yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 584:
#line 2668 "sql_yacc.yy"
    { yyval.item= new Item_cond_or(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 585:
#line 2669 "sql_yacc.yy"
    { yyval.item= new Item_cond_xor(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 586:
#line 2670 "sql_yacc.yy"
    { yyval.item= new Item_cond_and(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 587:
#line 2672 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_eq(new Item_func_soundex(yyvsp[-3].item),
				 new Item_func_soundex(yyvsp[0].item));
	  }
    break;

  case 588:
#line 2677 "sql_yacc.yy"
    { yyval.item= new Item_func_like(yyvsp[-3].item,yyvsp[-1].item,yyvsp[0].item); }
    break;

  case 589:
#line 2679 "sql_yacc.yy"
    { yyval.item= new Item_func_not(new Item_func_like(yyvsp[-4].item,yyvsp[-1].item,yyvsp[0].item)); }
    break;

  case 590:
#line 2680 "sql_yacc.yy"
    { yyval.item= new Item_func_regex(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 591:
#line 2682 "sql_yacc.yy"
    { yyval.item= new Item_func_not(new Item_func_regex(yyvsp[-3].item,yyvsp[0].item)); }
    break;

  case 592:
#line 2683 "sql_yacc.yy"
    { yyval.item= new Item_func_isnull(yyvsp[-2].item); }
    break;

  case 593:
#line 2684 "sql_yacc.yy"
    { yyval.item= new Item_func_isnotnull(yyvsp[-3].item); }
    break;

  case 594:
#line 2685 "sql_yacc.yy"
    { yyval.item= new Item_func_equal(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 595:
#line 2686 "sql_yacc.yy"
    { yyval.item= (*yyvsp[-1].boolfunc2creator)(0)->create(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 596:
#line 2688 "sql_yacc.yy"
    {
	  all_any_subquery_creator(yyvsp[-3].item, yyvsp[-2].boolfunc2creator, yyvsp[-1].num, yyvsp[0].select_lex);
	}
    break;

  case 597:
#line 2691 "sql_yacc.yy"
    { yyval.item= new Item_func_shift_left(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 598:
#line 2692 "sql_yacc.yy"
    { yyval.item= new Item_func_shift_right(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 599:
#line 2693 "sql_yacc.yy"
    { yyval.item= new Item_func_plus(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 600:
#line 2694 "sql_yacc.yy"
    { yyval.item= new Item_func_minus(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 601:
#line 2695 "sql_yacc.yy"
    { yyval.item= new Item_func_mul(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 602:
#line 2696 "sql_yacc.yy"
    { yyval.item= new Item_func_div(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 603:
#line 2697 "sql_yacc.yy"
    { yyval.item= new Item_func_int_div(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 604:
#line 2698 "sql_yacc.yy"
    { yyval.item= new Item_func_bit_or(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 605:
#line 2699 "sql_yacc.yy"
    { yyval.item= new Item_func_bit_xor(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 606:
#line 2700 "sql_yacc.yy"
    { yyval.item= new Item_func_bit_and(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 607:
#line 2701 "sql_yacc.yy"
    { yyval.item= new Item_func_mod(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 608:
#line 2702 "sql_yacc.yy"
    { yyval.item= new Item_func_mod(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 609:
#line 2704 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-3].item,yyvsp[-1].item,yyvsp[0].interval,0); }
    break;

  case 610:
#line 2706 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-3].item,yyvsp[-1].item,yyvsp[0].interval,1); }
    break;

  case 612:
#line 2712 "sql_yacc.yy"
    { yyvsp[-1].item_list->push_front(yyvsp[-4].item); yyval.item= new Item_func_in(*yyvsp[-1].item_list); }
    break;

  case 613:
#line 2714 "sql_yacc.yy"
    { yyvsp[-1].item_list->push_front(yyvsp[-5].item); yyval.item= new Item_func_not(new Item_func_in(*yyvsp[-1].item_list)); }
    break;

  case 614:
#line 2716 "sql_yacc.yy"
    { yyval.item= new Item_in_subselect(yyvsp[-2].item, yyvsp[0].select_lex); }
    break;

  case 615:
#line 2718 "sql_yacc.yy"
    {
            yyval.item= new Item_func_not(new Item_in_subselect(yyvsp[-3].item, yyvsp[0].select_lex));
          }
    break;

  case 616:
#line 2722 "sql_yacc.yy"
    { yyval.item= new Item_func_between(yyvsp[-4].item,yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 617:
#line 2724 "sql_yacc.yy"
    { yyval.item= new Item_func_not(new Item_func_between(yyvsp[-5].item,yyvsp[-2].item,yyvsp[0].item)); }
    break;

  case 618:
#line 2725 "sql_yacc.yy"
    { yyval.item= or_or_concat(YYTHD, yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 619:
#line 2726 "sql_yacc.yy"
    { yyval.item= new Item_cond_or(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 620:
#line 2727 "sql_yacc.yy"
    { yyval.item= new Item_cond_xor(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 621:
#line 2729 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_eq(new Item_func_soundex(yyvsp[-3].item),
				 new Item_func_soundex(yyvsp[0].item));
	  }
    break;

  case 622:
#line 2734 "sql_yacc.yy"
    { yyval.item= new Item_func_like(yyvsp[-3].item,yyvsp[-1].item,yyvsp[0].item); }
    break;

  case 623:
#line 2736 "sql_yacc.yy"
    { yyval.item= new Item_func_not(new Item_func_like(yyvsp[-4].item,yyvsp[-1].item,yyvsp[0].item)); }
    break;

  case 624:
#line 2737 "sql_yacc.yy"
    { yyval.item= new Item_func_regex(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 625:
#line 2739 "sql_yacc.yy"
    { yyval.item= new Item_func_not(new Item_func_regex(yyvsp[-3].item,yyvsp[0].item)); }
    break;

  case 626:
#line 2740 "sql_yacc.yy"
    { yyval.item= new Item_func_isnull(yyvsp[-2].item); }
    break;

  case 627:
#line 2741 "sql_yacc.yy"
    { yyval.item= new Item_func_isnotnull(yyvsp[-3].item); }
    break;

  case 628:
#line 2742 "sql_yacc.yy"
    { yyval.item= new Item_func_equal(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 629:
#line 2743 "sql_yacc.yy"
    { yyval.item= (*yyvsp[-1].boolfunc2creator)(0)->create(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 630:
#line 2745 "sql_yacc.yy"
    {
	  all_any_subquery_creator(yyvsp[-3].item, yyvsp[-2].boolfunc2creator, yyvsp[-1].num, yyvsp[0].select_lex);
	}
    break;

  case 631:
#line 2748 "sql_yacc.yy"
    { yyval.item= new Item_func_shift_left(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 632:
#line 2749 "sql_yacc.yy"
    { yyval.item= new Item_func_shift_right(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 633:
#line 2750 "sql_yacc.yy"
    { yyval.item= new Item_func_plus(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 634:
#line 2751 "sql_yacc.yy"
    { yyval.item= new Item_func_minus(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 635:
#line 2752 "sql_yacc.yy"
    { yyval.item= new Item_func_mul(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 636:
#line 2753 "sql_yacc.yy"
    { yyval.item= new Item_func_div(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 637:
#line 2754 "sql_yacc.yy"
    { yyval.item= new Item_func_int_div(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 638:
#line 2755 "sql_yacc.yy"
    { yyval.item= new Item_func_bit_or(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 639:
#line 2756 "sql_yacc.yy"
    { yyval.item= new Item_func_bit_xor(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 640:
#line 2757 "sql_yacc.yy"
    { yyval.item= new Item_func_bit_and(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 641:
#line 2758 "sql_yacc.yy"
    { yyval.item= new Item_func_mod(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 642:
#line 2759 "sql_yacc.yy"
    { yyval.item= new Item_func_mod(yyvsp[-2].item,yyvsp[0].item); }
    break;

  case 643:
#line 2761 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-3].item,yyvsp[-1].item,yyvsp[0].interval,0); }
    break;

  case 644:
#line 2763 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-3].item,yyvsp[-1].item,yyvsp[0].interval,1); }
    break;

  case 646:
#line 2767 "sql_yacc.yy"
    { yyval.item=yyvsp[0].item; }
    break;

  case 648:
#line 2773 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_set_collation(yyvsp[-2].item,
					    new Item_string(yyvsp[0].lex_str.str,
							    yyvsp[0].lex_str.length,
                                                            YYTHD->charset()));
	  }
    break;

  case 651:
#line 2782 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_set_user_var(yyvsp[-2].lex_str,yyvsp[0].item);
	    Lex->uncacheable(UNCACHEABLE_RAND);
	  }
    break;

  case 652:
#line 2787 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_get_user_var(yyvsp[0].lex_str);
	    Lex->uncacheable(UNCACHEABLE_RAND);
	  }
    break;

  case 653:
#line 2792 "sql_yacc.yy"
    {

            if (yyvsp[-1].lex_str.str && yyvsp[0].lex_str.str && check_reserved_words(&yyvsp[-1].lex_str))
            {
              yyerror(ER(ER_SYNTAX_ERROR));
              YYABORT;
            }
	    if (!(yyval.item= get_system_var(YYTHD, (enum_var_type) yyvsp[-2].num, yyvsp[-1].lex_str, yyvsp[0].lex_str)))
	      YYABORT;
	  }
    break;

  case 655:
#line 2803 "sql_yacc.yy"
    { yyval.item= yyvsp[0].item; }
    break;

  case 656:
#line 2804 "sql_yacc.yy"
    { yyval.item= new Item_func_neg(yyvsp[0].item); }
    break;

  case 657:
#line 2805 "sql_yacc.yy"
    { yyval.item= new Item_func_bit_neg(yyvsp[0].item); }
    break;

  case 658:
#line 2807 "sql_yacc.yy"
    {
            yyval.item= negate_expression(YYTHD, yyvsp[0].item);
          }
    break;

  case 659:
#line 2811 "sql_yacc.yy"
    {
            yyval.item= negate_expression(YYTHD, yyvsp[0].item);
          }
    break;

  case 660:
#line 2814 "sql_yacc.yy"
    { yyval.item= yyvsp[-1].item; }
    break;

  case 661:
#line 2816 "sql_yacc.yy"
    {
	    yyvsp[-1].item_list->push_front(yyvsp[-3].item);
	    yyval.item= new Item_row(*yyvsp[-1].item_list);
	  }
    break;

  case 662:
#line 2821 "sql_yacc.yy"
    {
	    yyvsp[-1].item_list->push_front(yyvsp[-3].item);
	    yyval.item= new Item_row(*yyvsp[-1].item_list);
	  }
    break;

  case 663:
#line 2825 "sql_yacc.yy"
    { yyval.item= yyvsp[0].item; }
    break;

  case 664:
#line 2826 "sql_yacc.yy"
    { yyval.item= yyvsp[0].item; }
    break;

  case 665:
#line 2827 "sql_yacc.yy"
    { yyval.item= yyvsp[-1].item; }
    break;

  case 666:
#line 2829 "sql_yacc.yy"
    { yyvsp[-5].item_list->push_front(yyvsp[-2].item);
            Select->add_ftfunc_to_list((Item_func_match*)
                                        (yyval.item=new Item_func_match(*yyvsp[-5].item_list,yyvsp[-1].num))); }
    break;

  case 667:
#line 2832 "sql_yacc.yy"
    { yyval.item= new Item_func_ascii(yyvsp[-1].item); }
    break;

  case 668:
#line 2834 "sql_yacc.yy"
    {
	    yyval.item= create_func_cast(yyvsp[0].item, ITEM_CAST_CHAR, -1, &my_charset_bin);
	  }
    break;

  case 669:
#line 2838 "sql_yacc.yy"
    {
	    yyval.item= create_func_cast(yyvsp[-3].item, yyvsp[-1].cast_type,
				 Lex->length ? atoi(Lex->length) : -1,
				 Lex->charset);
	  }
    break;

  case 670:
#line 2844 "sql_yacc.yy"
    { yyval.item= new Item_func_case(* yyvsp[-2].item_list, yyvsp[-4].item, yyvsp[-1].item ); }
    break;

  case 671:
#line 2846 "sql_yacc.yy"
    {
	    yyval.item= create_func_cast(yyvsp[-3].item, yyvsp[-1].cast_type,
				 Lex->length ? atoi(Lex->length) : -1,
				 Lex->charset);
	  }
    break;

  case 672:
#line 2852 "sql_yacc.yy"
    { yyval.item= new Item_func_conv_charset(yyvsp[-3].item,yyvsp[-1].charset); }
    break;

  case 673:
#line 2854 "sql_yacc.yy"
    { yyval.item= new Item_default_value(yyvsp[-1].item); }
    break;

  case 674:
#line 2856 "sql_yacc.yy"
    { yyval.item= new Item_insert_value(yyvsp[-1].item); }
    break;

  case 675:
#line 2858 "sql_yacc.yy"
    {
	    if (!yyvsp[-2].symbol.symbol->create_func)
	    {
	      net_printf(Lex->thd, ER_FEATURE_DISABLED,
			 yyvsp[-2].symbol.symbol->group->name,
	                 yyvsp[-2].symbol.symbol->group->needed_define);
	      YYABORT;
	    }
	    yyval.item= ((Item*(*)(void))(yyvsp[-2].symbol.symbol->create_func))();
	  }
    break;

  case 676:
#line 2869 "sql_yacc.yy"
    {
	    if (!yyvsp[-3].symbol.symbol->create_func)
	    {
	      net_printf(Lex->thd, ER_FEATURE_DISABLED,
			 yyvsp[-3].symbol.symbol->group->name,
	                 yyvsp[-3].symbol.symbol->group->needed_define);
	      YYABORT;
	    }
	    yyval.item= ((Item*(*)(Item*))(yyvsp[-3].symbol.symbol->create_func))(yyvsp[-1].item);
	  }
    break;

  case 677:
#line 2880 "sql_yacc.yy"
    {
	    if (!yyvsp[-5].symbol.symbol->create_func)
	    {
	      net_printf(Lex->thd, ER_FEATURE_DISABLED,
			 yyvsp[-5].symbol.symbol->group->name,
	                 yyvsp[-5].symbol.symbol->group->needed_define);
	      YYABORT;
	    }
	    yyval.item= ((Item*(*)(Item*,Item*))(yyvsp[-5].symbol.symbol->create_func))(yyvsp[-3].item,yyvsp[-1].item);
	  }
    break;

  case 678:
#line 2891 "sql_yacc.yy"
    {
	    if (!yyvsp[-7].symbol.symbol->create_func)
	    {
	      net_printf(Lex->thd, ER_FEATURE_DISABLED,
			 yyvsp[-7].symbol.symbol->group->name,
	                 yyvsp[-7].symbol.symbol->group->needed_define);
	      YYABORT;
	    }
	    yyval.item= ((Item*(*)(Item*,Item*,Item*))(yyvsp[-7].symbol.symbol->create_func))(yyvsp[-5].item,yyvsp[-3].item,yyvsp[-1].item);
	  }
    break;

  case 679:
#line 2902 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-3].item, yyvsp[-1].item, INTERVAL_DAY, 0);}
    break;

  case 680:
#line 2904 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-5].item, yyvsp[-2].item, yyvsp[-1].interval, 0); }
    break;

  case 681:
#line 2906 "sql_yacc.yy"
    { yyval.item= new Item_func_atan(yyvsp[-1].item); }
    break;

  case 682:
#line 2908 "sql_yacc.yy"
    { yyval.item= new Item_func_atan(yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 683:
#line 2910 "sql_yacc.yy"
    { yyval.item= new Item_func_char(*yyvsp[-1].item_list); }
    break;

  case 684:
#line 2912 "sql_yacc.yy"
    { yyval.item= new Item_func_charset(yyvsp[-1].item); }
    break;

  case 685:
#line 2914 "sql_yacc.yy"
    { yyval.item= new Item_func_coalesce(* yyvsp[-1].item_list); }
    break;

  case 686:
#line 2916 "sql_yacc.yy"
    { yyval.item= new Item_func_collation(yyvsp[-1].item); }
    break;

  case 687:
#line 2918 "sql_yacc.yy"
    { yyval.item= new Item_func_concat(* yyvsp[-1].item_list); }
    break;

  case 688:
#line 2920 "sql_yacc.yy"
    { yyvsp[-1].item_list->push_front(yyvsp[-3].item); yyval.item= new Item_func_concat_ws(*yyvsp[-1].item_list); }
    break;

  case 689:
#line 2922 "sql_yacc.yy"
    {
	    Lex->time_zone_tables_used= &fake_time_zone_tables_list;
	    yyval.item= new Item_func_convert_tz(yyvsp[-5].item, yyvsp[-3].item, yyvsp[-1].item);
	  }
    break;

  case 690:
#line 2927 "sql_yacc.yy"
    { yyval.item= new Item_func_curdate_local(); Lex->safe_to_cache_query=0; }
    break;

  case 691:
#line 2929 "sql_yacc.yy"
    { yyval.item= new Item_func_curtime_local(); Lex->safe_to_cache_query=0; }
    break;

  case 692:
#line 2931 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_curtime_local(yyvsp[-1].item);
	    Lex->safe_to_cache_query=0;
	  }
    break;

  case 693:
#line 2936 "sql_yacc.yy"
    { yyval.item= create_func_current_user(); }
    break;

  case 694:
#line 2938 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-4].item,yyvsp[-2].item,yyvsp[-1].interval,0); }
    break;

  case 695:
#line 2940 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-4].item,yyvsp[-2].item,yyvsp[-1].interval,1); }
    break;

  case 696:
#line 2942 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_database();
            Lex->safe_to_cache_query=0;
	  }
    break;

  case 697:
#line 2947 "sql_yacc.yy"
    { yyval.item= new Item_date_typecast(yyvsp[-1].item); }
    break;

  case 698:
#line 2949 "sql_yacc.yy"
    { yyval.item= new Item_func_dayofmonth(yyvsp[-1].item); }
    break;

  case 699:
#line 2951 "sql_yacc.yy"
    { yyvsp[-1].item_list->push_front(yyvsp[-3].item); yyval.item= new Item_func_elt(*yyvsp[-1].item_list); }
    break;

  case 700:
#line 2953 "sql_yacc.yy"
    { yyval.item= new Item_func_make_set(yyvsp[-3].item, *yyvsp[-1].item_list); }
    break;

  case 701:
#line 2955 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_encrypt(yyvsp[-1].item);
	    Lex->uncacheable(UNCACHEABLE_RAND);
	  }
    break;

  case 702:
#line 2959 "sql_yacc.yy"
    { yyval.item= new Item_func_encrypt(yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 703:
#line 2961 "sql_yacc.yy"
    { yyval.item= new Item_func_decode(yyvsp[-3].item,yyvsp[-1].lex_str.str); }
    break;

  case 704:
#line 2963 "sql_yacc.yy"
    { yyval.item= new Item_func_encode(yyvsp[-3].item,yyvsp[-1].lex_str.str); }
    break;

  case 705:
#line 2965 "sql_yacc.yy"
    { yyval.item= new Item_func_des_decrypt(yyvsp[-1].item); }
    break;

  case 706:
#line 2967 "sql_yacc.yy"
    { yyval.item= new Item_func_des_decrypt(yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 707:
#line 2969 "sql_yacc.yy"
    { yyval.item= new Item_func_des_encrypt(yyvsp[-1].item); }
    break;

  case 708:
#line 2971 "sql_yacc.yy"
    { yyval.item= new Item_func_des_encrypt(yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 709:
#line 2973 "sql_yacc.yy"
    { yyval.item= new Item_func_export_set(yyvsp[-5].item, yyvsp[-3].item, yyvsp[-1].item); }
    break;

  case 710:
#line 2975 "sql_yacc.yy"
    { yyval.item= new Item_func_export_set(yyvsp[-7].item, yyvsp[-5].item, yyvsp[-3].item, yyvsp[-1].item); }
    break;

  case 711:
#line 2977 "sql_yacc.yy"
    { yyval.item= new Item_func_export_set(yyvsp[-9].item, yyvsp[-7].item, yyvsp[-5].item, yyvsp[-3].item, yyvsp[-1].item); }
    break;

  case 712:
#line 2979 "sql_yacc.yy"
    { yyval.item= new Item_func_format(yyvsp[-3].item,atoi(yyvsp[-1].lex_str.str)); }
    break;

  case 713:
#line 2981 "sql_yacc.yy"
    { yyval.item= new Item_func_from_unixtime(yyvsp[-1].item); }
    break;

  case 714:
#line 2983 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_date_format (new Item_func_from_unixtime(yyvsp[-3].item),yyvsp[-1].item,0);
	  }
    break;

  case 715:
#line 2987 "sql_yacc.yy"
    { yyvsp[-1].item_list->push_front(yyvsp[-3].item); yyval.item= new Item_func_field(*yyvsp[-1].item_list); }
    break;

  case 716:
#line 2989 "sql_yacc.yy"
    {
#ifdef HAVE_SPATIAL
	    yyval.item= yyvsp[0].item;
#else
	    net_printf(Lex->thd, ER_FEATURE_DISABLED,
	               sym_group_geom.name, sym_group_geom.needed_define);
	    YYABORT;
#endif
	  }
    break;

  case 717:
#line 2999 "sql_yacc.yy"
    { yyval.item= new Item_func_get_format(yyvsp[-3].date_time_type, yyvsp[-1].item); }
    break;

  case 718:
#line 3001 "sql_yacc.yy"
    { yyval.item= new Item_func_hour(yyvsp[-1].item); }
    break;

  case 719:
#line 3003 "sql_yacc.yy"
    { yyval.item= new Item_func_if(yyvsp[-5].item,yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 720:
#line 3005 "sql_yacc.yy"
    { yyval.item= new Item_func_insert(yyvsp[-7].item,yyvsp[-5].item,yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 721:
#line 3008 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[0].item,yyvsp[-3].item,yyvsp[-2].interval,0); }
    break;

  case 722:
#line 3010 "sql_yacc.yy"
    {
            if (yyvsp[0].item->type() != Item::ROW_ITEM)
            {
              yyerror(ER(ER_SYNTAX_ERROR));
              YYABORT;
            }
            yyval.item= new Item_func_interval((Item_row *)yyvsp[0].item);
          }
    break;

  case 723:
#line 3019 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_last_insert_id();
	    Lex->safe_to_cache_query= 0;
	  }
    break;

  case 724:
#line 3024 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_last_insert_id(yyvsp[-1].item);
	    Lex->safe_to_cache_query= 0;
	  }
    break;

  case 725:
#line 3029 "sql_yacc.yy"
    { yyval.item= new Item_func_left(yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 726:
#line 3031 "sql_yacc.yy"
    { yyval.item= new Item_func_locate(yyvsp[-1].item,yyvsp[-3].item); }
    break;

  case 727:
#line 3033 "sql_yacc.yy"
    { yyval.item= new Item_func_locate(yyvsp[-3].item,yyvsp[-5].item,yyvsp[-1].item); }
    break;

  case 728:
#line 3035 "sql_yacc.yy"
    { yyvsp[-1].item_list->push_front(yyvsp[-3].item); yyval.item= new Item_func_max(*yyvsp[-1].item_list); }
    break;

  case 729:
#line 3037 "sql_yacc.yy"
    { yyvsp[-1].item_list->push_front(yyvsp[-3].item); yyval.item= new Item_func_min(*yyvsp[-1].item_list); }
    break;

  case 730:
#line 3039 "sql_yacc.yy"
    { yyval.item= new Item_func_log(yyvsp[-1].item); }
    break;

  case 731:
#line 3041 "sql_yacc.yy"
    { yyval.item= new Item_func_log(yyvsp[-3].item, yyvsp[-1].item); }
    break;

  case 732:
#line 3043 "sql_yacc.yy"
    {
	    yyval.item= new Item_master_pos_wait(yyvsp[-3].item, yyvsp[-1].item);
	    Lex->safe_to_cache_query=0;
		  }
    break;

  case 733:
#line 3048 "sql_yacc.yy"
    {
	    yyval.item= new Item_master_pos_wait(yyvsp[-5].item, yyvsp[-3].item, yyvsp[-1].item);
	    Lex->safe_to_cache_query=0;
	  }
    break;

  case 734:
#line 3053 "sql_yacc.yy"
    { yyval.item= new Item_func_microsecond(yyvsp[-1].item); }
    break;

  case 735:
#line 3055 "sql_yacc.yy"
    { yyval.item= new Item_func_minute(yyvsp[-1].item); }
    break;

  case 736:
#line 3057 "sql_yacc.yy"
    { yyval.item = new Item_func_mod( yyvsp[-3].item, yyvsp[-1].item); }
    break;

  case 737:
#line 3059 "sql_yacc.yy"
    { yyval.item= new Item_func_month(yyvsp[-1].item); }
    break;

  case 738:
#line 3061 "sql_yacc.yy"
    { yyval.item= new Item_func_now_local(); Lex->safe_to_cache_query=0;}
    break;

  case 739:
#line 3063 "sql_yacc.yy"
    { yyval.item= new Item_func_now_local(yyvsp[-1].item); Lex->safe_to_cache_query=0;}
    break;

  case 740:
#line 3065 "sql_yacc.yy"
    {
	    yyval.item= YYTHD->variables.old_passwords ?
              (Item *) new Item_func_old_password(yyvsp[-1].item) :
	      (Item *) new Item_func_password(yyvsp[-1].item);
	  }
    break;

  case 741:
#line 3071 "sql_yacc.yy"
    { yyval.item=  new Item_func_old_password(yyvsp[-1].item); }
    break;

  case 742:
#line 3073 "sql_yacc.yy"
    { yyval.item = new Item_func_locate(yyvsp[-1].item,yyvsp[-3].item); }
    break;

  case 743:
#line 3075 "sql_yacc.yy"
    { yyval.item= new Item_func_rand(yyvsp[-1].item); Lex->uncacheable(UNCACHEABLE_RAND);}
    break;

  case 744:
#line 3077 "sql_yacc.yy"
    { yyval.item= new Item_func_rand(); Lex->uncacheable(UNCACHEABLE_RAND);}
    break;

  case 745:
#line 3079 "sql_yacc.yy"
    { yyval.item= new Item_func_replace(yyvsp[-5].item,yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 746:
#line 3081 "sql_yacc.yy"
    { yyval.item= new Item_func_right(yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 747:
#line 3083 "sql_yacc.yy"
    { yyval.item= new Item_func_round(yyvsp[-1].item, new Item_int((char*)"0",0,1),0); }
    break;

  case 748:
#line 3084 "sql_yacc.yy"
    { yyval.item= new Item_func_round(yyvsp[-3].item,yyvsp[-1].item,0); }
    break;

  case 749:
#line 3086 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-3].item, yyvsp[-1].item, INTERVAL_DAY, 1);}
    break;

  case 750:
#line 3088 "sql_yacc.yy"
    { yyval.item= new Item_date_add_interval(yyvsp[-5].item, yyvsp[-2].item, yyvsp[-1].interval, 1); }
    break;

  case 751:
#line 3090 "sql_yacc.yy"
    { yyval.item= new Item_func_second(yyvsp[-1].item); }
    break;

  case 752:
#line 3092 "sql_yacc.yy"
    { yyval.item= new Item_func_substr(yyvsp[-5].item,yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 753:
#line 3094 "sql_yacc.yy"
    { yyval.item= new Item_func_substr(yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 754:
#line 3096 "sql_yacc.yy"
    { yyval.item= new Item_func_substr(yyvsp[-5].item,yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 755:
#line 3098 "sql_yacc.yy"
    { yyval.item= new Item_func_substr(yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 756:
#line 3100 "sql_yacc.yy"
    { yyval.item= new Item_func_substr_index(yyvsp[-5].item,yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 757:
#line 3102 "sql_yacc.yy"
    { yyval.item= new Item_time_typecast(yyvsp[-1].item); }
    break;

  case 758:
#line 3104 "sql_yacc.yy"
    { yyval.item= new Item_datetime_typecast(yyvsp[-1].item); }
    break;

  case 759:
#line 3106 "sql_yacc.yy"
    { yyval.item= new Item_func_add_time(yyvsp[-3].item, yyvsp[-1].item, 1, 0); }
    break;

  case 760:
#line 3108 "sql_yacc.yy"
    { yyval.item= new Item_func_trim(yyvsp[-1].item); }
    break;

  case 761:
#line 3110 "sql_yacc.yy"
    { yyval.item= new Item_func_ltrim(yyvsp[-1].item,yyvsp[-3].item); }
    break;

  case 762:
#line 3112 "sql_yacc.yy"
    { yyval.item= new Item_func_rtrim(yyvsp[-1].item,yyvsp[-3].item); }
    break;

  case 763:
#line 3114 "sql_yacc.yy"
    { yyval.item= new Item_func_trim(yyvsp[-1].item,yyvsp[-3].item); }
    break;

  case 764:
#line 3116 "sql_yacc.yy"
    { yyval.item= new Item_func_ltrim(yyvsp[-1].item); }
    break;

  case 765:
#line 3118 "sql_yacc.yy"
    { yyval.item= new Item_func_rtrim(yyvsp[-1].item); }
    break;

  case 766:
#line 3120 "sql_yacc.yy"
    { yyval.item= new Item_func_trim(yyvsp[-1].item); }
    break;

  case 767:
#line 3122 "sql_yacc.yy"
    { yyval.item= new Item_func_trim(yyvsp[-1].item,yyvsp[-3].item); }
    break;

  case 768:
#line 3124 "sql_yacc.yy"
    { yyval.item= new Item_func_round(yyvsp[-3].item,yyvsp[-1].item,1); }
    break;

  case 769:
#line 3126 "sql_yacc.yy"
    {
	    if (yyvsp[-1].item_list != NULL)
	      yyval.item = new Item_sum_udf_str(yyvsp[-3].udf, *yyvsp[-1].item_list);
	    else
	      yyval.item = new Item_sum_udf_str(yyvsp[-3].udf);
	  }
    break;

  case 770:
#line 3133 "sql_yacc.yy"
    {
	    if (yyvsp[-1].item_list != NULL)
	      yyval.item = new Item_sum_udf_float(yyvsp[-3].udf, *yyvsp[-1].item_list);
	    else
	      yyval.item = new Item_sum_udf_float(yyvsp[-3].udf);
	  }
    break;

  case 771:
#line 3140 "sql_yacc.yy"
    {
	    if (yyvsp[-1].item_list != NULL)
	      yyval.item = new Item_sum_udf_int(yyvsp[-3].udf, *yyvsp[-1].item_list);
	    else
	      yyval.item = new Item_sum_udf_int(yyvsp[-3].udf);
	  }
    break;

  case 772:
#line 3147 "sql_yacc.yy"
    {
	    if (yyvsp[-1].item_list != NULL)
	      yyval.item = new Item_func_udf_str(yyvsp[-3].udf, *yyvsp[-1].item_list);
	    else
	      yyval.item = new Item_func_udf_str(yyvsp[-3].udf);
	  }
    break;

  case 773:
#line 3154 "sql_yacc.yy"
    {
	    if (yyvsp[-1].item_list != NULL)
	      yyval.item = new Item_func_udf_float(yyvsp[-3].udf, *yyvsp[-1].item_list);
	    else
	      yyval.item = new Item_func_udf_float(yyvsp[-3].udf);
	  }
    break;

  case 774:
#line 3161 "sql_yacc.yy"
    {
	    if (yyvsp[-1].item_list != NULL)
	      yyval.item = new Item_func_udf_int(yyvsp[-3].udf, *yyvsp[-1].item_list);
	    else
	      yyval.item = new Item_func_udf_int(yyvsp[-3].udf);
	  }
    break;

  case 775:
#line 3168 "sql_yacc.yy"
    {
            yyval.item= new Item_func_unique_users(yyvsp[-7].item,atoi(yyvsp[-5].lex_str.str),atoi(yyvsp[-3].lex_str.str), * yyvsp[-1].item_list);
	  }
    break;

  case 776:
#line 3172 "sql_yacc.yy"
    {
	    yyval.item= new Item_func_unix_timestamp();
	    Lex->safe_to_cache_query=0;
	  }
    break;

  case 777:
#line 3177 "sql_yacc.yy"
    { yyval.item= new Item_func_unix_timestamp(yyvsp[-1].item); }
    break;

  case 778:
#line 3179 "sql_yacc.yy"
    { yyval.item= new Item_func_user(); Lex->safe_to_cache_query=0; }
    break;

  case 779:
#line 3181 "sql_yacc.yy"
    { yyval.item= new Item_func_curdate_utc(); Lex->safe_to_cache_query=0;}
    break;

  case 780:
#line 3183 "sql_yacc.yy"
    { yyval.item= new Item_func_curtime_utc(); Lex->safe_to_cache_query=0;}
    break;

  case 781:
#line 3185 "sql_yacc.yy"
    { yyval.item= new Item_func_now_utc(); Lex->safe_to_cache_query=0;}
    break;

  case 782:
#line 3187 "sql_yacc.yy"
    {
            yyval.item= new Item_func_week(yyvsp[-1].item,new Item_int((char*) "0",
				   YYTHD->variables.default_week_format,1));
          }
    break;

  case 783:
#line 3192 "sql_yacc.yy"
    { yyval.item= new Item_func_week(yyvsp[-3].item,yyvsp[-1].item); }
    break;

  case 784:
#line 3194 "sql_yacc.yy"
    { yyval.item= new Item_func_year(yyvsp[-1].item); }
    break;

  case 785:
#line 3196 "sql_yacc.yy"
    { yyval.item= new Item_func_yearweek(yyvsp[-1].item,new Item_int((char*) "0",0,1)); }
    break;

  case 786:
#line 3198 "sql_yacc.yy"
    { yyval.item= new Item_func_yearweek(yyvsp[-3].item, yyvsp[-1].item); }
    break;

  case 787:
#line 3200 "sql_yacc.yy"
    {
	    yyval.item=new Item_func_benchmark(yyvsp[-3].ulong_num,yyvsp[-1].item);
	    Lex->uncacheable(UNCACHEABLE_SIDEEFFECT);
	  }
    break;

  case 788:
#line 3205 "sql_yacc.yy"
    { yyval.item=new Item_extract( yyvsp[-3].interval, yyvsp[-1].item); }
    break;

  case 789:
#line 3209 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-1].item)); }
    break;

  case 790:
#line 3211 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-3].item, yyvsp[-1].item)); }
    break;

  case 791:
#line 3213 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_wkb(yyvsp[-1].item)); }
    break;

  case 792:
#line 3215 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_wkb(yyvsp[-3].item, yyvsp[-1].item)); }
    break;

  case 793:
#line 3217 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_spatial_collection(* yyvsp[-1].item_list,
                           Geometry::wkb_geometrycollection,
                           Geometry::wkb_point)); }
    break;

  case 794:
#line 3221 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_spatial_collection(* yyvsp[-1].item_list,
                  Geometry::wkb_linestring, Geometry::wkb_point)); }
    break;

  case 795:
#line 3224 "sql_yacc.yy"
    { yyval.item= GEOM_NEW( Item_func_spatial_collection(* yyvsp[-1].item_list,
                   Geometry::wkb_multilinestring, Geometry::wkb_linestring)); }
    break;

  case 796:
#line 3227 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-1].item)); }
    break;

  case 797:
#line 3229 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-3].item, yyvsp[-1].item)); }
    break;

  case 798:
#line 3231 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-1].item)); }
    break;

  case 799:
#line 3233 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-3].item, yyvsp[-1].item)); }
    break;

  case 800:
#line 3235 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-1].item)); }
    break;

  case 801:
#line 3237 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-3].item, yyvsp[-1].item)); }
    break;

  case 802:
#line 3239 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_spatial_collection(* yyvsp[-1].item_list,
                  Geometry::wkb_multipoint, Geometry::wkb_point)); }
    break;

  case 803:
#line 3242 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_spatial_collection(* yyvsp[-1].item_list,
                  Geometry::wkb_multipolygon, Geometry::wkb_polygon)); }
    break;

  case 804:
#line 3245 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_point(yyvsp[-3].item,yyvsp[-1].item)); }
    break;

  case 805:
#line 3247 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-1].item)); }
    break;

  case 806:
#line 3249 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-3].item, yyvsp[-1].item)); }
    break;

  case 807:
#line 3251 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-1].item)); }
    break;

  case 808:
#line 3253 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-3].item, yyvsp[-1].item)); }
    break;

  case 809:
#line 3255 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_spatial_collection(* yyvsp[-1].item_list,
	          Geometry::wkb_polygon, Geometry::wkb_linestring)); }
    break;

  case 810:
#line 3258 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-1].item)); }
    break;

  case 811:
#line 3260 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-3].item, yyvsp[-1].item)); }
    break;

  case 812:
#line 3262 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-1].item)); }
    break;

  case 813:
#line 3264 "sql_yacc.yy"
    { yyval.item= GEOM_NEW(Item_func_geometry_from_text(yyvsp[-3].item, yyvsp[-1].item)); }
    break;

  case 814:
#line 3268 "sql_yacc.yy"
    { yyval.num= FT_NL;  }
    break;

  case 815:
#line 3269 "sql_yacc.yy"
    { yyval.num= FT_NL | FT_EXPAND; }
    break;

  case 816:
#line 3270 "sql_yacc.yy"
    { yyval.num= FT_BOOL; }
    break;

  case 817:
#line 3274 "sql_yacc.yy"
    { yyval.item_list= NULL; }
    break;

  case 818:
#line 3275 "sql_yacc.yy"
    { yyval.item_list= yyvsp[0].item_list;}
    break;

  case 819:
#line 3279 "sql_yacc.yy"
    { yyval.item=new Item_sum_avg(yyvsp[-1].item); }
    break;

  case 820:
#line 3281 "sql_yacc.yy"
    { yyval.item=new Item_sum_and(yyvsp[-1].item); }
    break;

  case 821:
#line 3283 "sql_yacc.yy"
    { yyval.item=new Item_sum_or(yyvsp[-1].item); }
    break;

  case 822:
#line 3285 "sql_yacc.yy"
    { yyval.item=new Item_sum_xor(yyvsp[-1].item); }
    break;

  case 823:
#line 3287 "sql_yacc.yy"
    { yyval.item=new Item_sum_count(new Item_int((int32) 0L,1)); }
    break;

  case 824:
#line 3289 "sql_yacc.yy"
    { yyval.item=new Item_sum_count(yyvsp[-1].item); }
    break;

  case 825:
#line 3291 "sql_yacc.yy"
    { Select->in_sum_expr++; }
    break;

  case 826:
#line 3293 "sql_yacc.yy"
    { Select->in_sum_expr--; }
    break;

  case 827:
#line 3295 "sql_yacc.yy"
    { yyval.item=new Item_sum_count_distinct(* yyvsp[-2].item_list); }
    break;

  case 828:
#line 3297 "sql_yacc.yy"
    { yyval.item= new Item_sum_unique_users(yyvsp[-7].item,atoi(yyvsp[-5].lex_str.str),atoi(yyvsp[-3].lex_str.str),yyvsp[-1].item); }
    break;

  case 829:
#line 3299 "sql_yacc.yy"
    { yyval.item=new Item_sum_min(yyvsp[-1].item); }
    break;

  case 830:
#line 3301 "sql_yacc.yy"
    { yyval.item=new Item_sum_max(yyvsp[-1].item); }
    break;

  case 831:
#line 3303 "sql_yacc.yy"
    { yyval.item=new Item_sum_std(yyvsp[-1].item); }
    break;

  case 832:
#line 3305 "sql_yacc.yy"
    { yyval.item=new Item_sum_variance(yyvsp[-1].item); }
    break;

  case 833:
#line 3307 "sql_yacc.yy"
    { yyval.item=new Item_sum_sum(yyvsp[-1].item); }
    break;

  case 834:
#line 3309 "sql_yacc.yy"
    { Select->in_sum_expr++; }
    break;

  case 835:
#line 3313 "sql_yacc.yy"
    {
	    Select->in_sum_expr--;
	    yyval.item=new Item_func_group_concat(yyvsp[-5].num,yyvsp[-3].item_list,Select->gorder_list,yyvsp[-1].string);
	    yyvsp[-3].item_list->empty();
	  }
    break;

  case 836:
#line 3320 "sql_yacc.yy"
    { yyval.num = 0; }
    break;

  case 837:
#line 3321 "sql_yacc.yy"
    { yyval.num = 1; }
    break;

  case 838:
#line 3324 "sql_yacc.yy"
    { yyval.string = new (YYTHD->mem_root) String(",",1,default_charset_info); }
    break;

  case 839:
#line 3325 "sql_yacc.yy"
    { yyval.string = yyvsp[0].string; }
    break;

  case 840:
#line 3330 "sql_yacc.yy"
    {
            Select->gorder_list = NULL;
	  }
    break;

  case 841:
#line 3334 "sql_yacc.yy"
    {
            SELECT_LEX *select= Select;
            select->gorder_list=
	      (SQL_LIST*) sql_memdup((char*) &select->order_list,
				     sizeof(st_sql_list));
	    select->order_list.empty();
	  }
    break;

  case 842:
#line 3345 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  if (lex->current_select->inc_in_sum_expr())
	  {
	    yyerror(ER(ER_SYNTAX_ERROR));
	    YYABORT;
	  }
	}
    break;

  case 843:
#line 3354 "sql_yacc.yy"
    {
	  Select->in_sum_expr--;
	  yyval.item= yyvsp[0].item;
	}
    break;

  case 844:
#line 3360 "sql_yacc.yy"
    { yyval.cast_type=ITEM_CAST_CHAR; Lex->charset= &my_charset_bin; }
    break;

  case 845:
#line 3361 "sql_yacc.yy"
    { yyval.cast_type=ITEM_CAST_CHAR; }
    break;

  case 846:
#line 3362 "sql_yacc.yy"
    { yyval.cast_type=ITEM_CAST_CHAR; Lex->charset= national_charset_info; }
    break;

  case 847:
#line 3363 "sql_yacc.yy"
    { yyval.cast_type=ITEM_CAST_SIGNED_INT; Lex->charset= NULL; Lex->length= (char*)0; }
    break;

  case 848:
#line 3364 "sql_yacc.yy"
    { yyval.cast_type=ITEM_CAST_SIGNED_INT; Lex->charset= NULL; Lex->length= (char*)0; }
    break;

  case 849:
#line 3365 "sql_yacc.yy"
    { yyval.cast_type=ITEM_CAST_UNSIGNED_INT; Lex->charset= NULL; Lex->length= (char*)0; }
    break;

  case 850:
#line 3366 "sql_yacc.yy"
    { yyval.cast_type=ITEM_CAST_UNSIGNED_INT; Lex->charset= NULL; Lex->length= (char*)0; }
    break;

  case 851:
#line 3367 "sql_yacc.yy"
    { yyval.cast_type=ITEM_CAST_DATE; Lex->charset= NULL; Lex->length= (char*)0; }
    break;

  case 852:
#line 3368 "sql_yacc.yy"
    { yyval.cast_type=ITEM_CAST_TIME; Lex->charset= NULL; Lex->length= (char*)0; }
    break;

  case 853:
#line 3369 "sql_yacc.yy"
    { yyval.cast_type=ITEM_CAST_DATETIME; Lex->charset= NULL; Lex->length= (char*)0; }
    break;

  case 854:
#line 3373 "sql_yacc.yy"
    { Select->expr_list.push_front(new List<Item>); }
    break;

  case 855:
#line 3375 "sql_yacc.yy"
    { yyval.item_list= Select->expr_list.pop(); }
    break;

  case 856:
#line 3378 "sql_yacc.yy"
    { Select->expr_list.head()->push_back(yyvsp[0].item); }
    break;

  case 857:
#line 3379 "sql_yacc.yy"
    { Select->expr_list.head()->push_back(yyvsp[0].item); }
    break;

  case 858:
#line 3382 "sql_yacc.yy"
    { yyval.item_list= yyvsp[0].item_list; }
    break;

  case 859:
#line 3383 "sql_yacc.yy"
    { yyval.item_list= yyvsp[-1].item_list; }
    break;

  case 860:
#line 3386 "sql_yacc.yy"
    { Select->expr_list.push_front(new List<Item>); }
    break;

  case 861:
#line 3388 "sql_yacc.yy"
    { yyval.item_list= Select->expr_list.pop(); }
    break;

  case 862:
#line 3391 "sql_yacc.yy"
    { Select->expr_list.head()->push_back(yyvsp[0].item); }
    break;

  case 863:
#line 3392 "sql_yacc.yy"
    { Select->expr_list.head()->push_back(yyvsp[0].item); }
    break;

  case 864:
#line 3395 "sql_yacc.yy"
    { yyval.item= NULL; }
    break;

  case 865:
#line 3396 "sql_yacc.yy"
    { yyval.item= yyvsp[0].item; }
    break;

  case 866:
#line 3399 "sql_yacc.yy"
    { yyval.item= NULL; }
    break;

  case 867:
#line 3400 "sql_yacc.yy"
    { yyval.item= yyvsp[0].item; }
    break;

  case 868:
#line 3403 "sql_yacc.yy"
    { Select->when_list.push_front(new List<Item>); }
    break;

  case 869:
#line 3405 "sql_yacc.yy"
    { yyval.item_list= Select->when_list.pop(); }
    break;

  case 870:
#line 3409 "sql_yacc.yy"
    {
	    SELECT_LEX *sel=Select;
	    sel->when_list.head()->push_back(yyvsp[-2].item);
	    sel->when_list.head()->push_back(yyvsp[0].item);
	}
    break;

  case 871:
#line 3415 "sql_yacc.yy"
    {
	    SELECT_LEX *sel=Select;
	    sel->when_list.head()->push_back(yyvsp[-2].item);
	    sel->when_list.head()->push_back(yyvsp[0].item);
	  }
    break;

  case 872:
#line 3422 "sql_yacc.yy"
    { yyval.table_list=yyvsp[0].table_list; }
    break;

  case 873:
#line 3423 "sql_yacc.yy"
    { yyval.table_list=yyvsp[0].table_list; }
    break;

  case 874:
#line 3424 "sql_yacc.yy"
    { yyval.table_list=yyvsp[0].table_list; }
    break;

  case 875:
#line 3426 "sql_yacc.yy"
    { yyval.table_list=yyvsp[0].table_list ; yyvsp[-2].table_list->next->straight=1; }
    break;

  case 876:
#line 3428 "sql_yacc.yy"
    { add_join_on(yyvsp[-2].table_list,yyvsp[0].item); yyval.table_list=yyvsp[-2].table_list; }
    break;

  case 877:
#line 3431 "sql_yacc.yy"
    {
	    SELECT_LEX *sel= Select;
	    sel->db1=yyvsp[-3].table_list->db; sel->table1=yyvsp[-3].table_list->alias;
	    sel->db2=yyvsp[-1].table_list->db; sel->table2=yyvsp[-1].table_list->alias;
	  }
    break;

  case 878:
#line 3437 "sql_yacc.yy"
    { add_join_on(yyvsp[-5].table_list,yyvsp[-1].item); yyval.table_list=yyvsp[-5].table_list; }
    break;

  case 879:
#line 3440 "sql_yacc.yy"
    { add_join_on(yyvsp[-2].table_list,yyvsp[0].item); yyvsp[-2].table_list->outer_join|=JOIN_TYPE_LEFT; yyval.table_list=yyvsp[-2].table_list; }
    break;

  case 880:
#line 3442 "sql_yacc.yy"
    {
	    SELECT_LEX *sel= Select;
	    sel->db1=yyvsp[-4].table_list->db; sel->table1=yyvsp[-4].table_list->alias;
	    sel->db2=yyvsp[0].table_list->db; sel->table2=yyvsp[0].table_list->alias;
	  }
    break;

  case 881:
#line 3448 "sql_yacc.yy"
    { add_join_on(yyvsp[-5].table_list,yyvsp[-1].item); yyvsp[-5].table_list->outer_join|=JOIN_TYPE_LEFT; yyval.table_list=yyvsp[-5].table_list; }
    break;

  case 882:
#line 3450 "sql_yacc.yy"
    {
	    add_join_natural(yyvsp[-5].table_list,yyvsp[-5].table_list->next);
	    yyvsp[-5].table_list->next->outer_join|=JOIN_TYPE_LEFT;
	    yyval.table_list=yyvsp[0].table_list;
	  }
    break;

  case 883:
#line 3456 "sql_yacc.yy"
    { add_join_on(yyvsp[-6].table_list,yyvsp[0].item); yyvsp[-6].table_list->outer_join|=JOIN_TYPE_RIGHT; yyval.table_list=yyvsp[-2].table_list; }
    break;

  case 884:
#line 3458 "sql_yacc.yy"
    {
	    SELECT_LEX *sel= Select;
	    sel->db1=yyvsp[-4].table_list->db; sel->table1=yyvsp[-4].table_list->alias;
	    sel->db2=yyvsp[0].table_list->db; sel->table2=yyvsp[0].table_list->alias;
	  }
    break;

  case 885:
#line 3464 "sql_yacc.yy"
    { add_join_on(yyvsp[-9].table_list,yyvsp[-1].item); yyvsp[-9].table_list->outer_join|=JOIN_TYPE_RIGHT; yyval.table_list=yyvsp[-5].table_list; }
    break;

  case 886:
#line 3466 "sql_yacc.yy"
    {
	    add_join_natural(yyvsp[-5].table_list->next,yyvsp[-5].table_list);
	    yyvsp[-5].table_list->outer_join|=JOIN_TYPE_RIGHT;
	    yyval.table_list=yyvsp[0].table_list;
	  }
    break;

  case 887:
#line 3472 "sql_yacc.yy"
    { add_join_natural(yyvsp[-3].table_list,yyvsp[-3].table_list->next); yyval.table_list=yyvsp[0].table_list; }
    break;

  case 888:
#line 3475 "sql_yacc.yy"
    {}
    break;

  case 889:
#line 3476 "sql_yacc.yy"
    {}
    break;

  case 890:
#line 3477 "sql_yacc.yy"
    {}
    break;

  case 891:
#line 3481 "sql_yacc.yy"
    {
	  SELECT_LEX *sel= Select;
	  sel->use_index_ptr=sel->ignore_index_ptr=0;
	  sel->table_join_options= 0;
	}
    break;

  case 892:
#line 3487 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  SELECT_LEX *sel= lex->current_select;
	  if (!(yyval.table_list= sel->add_table_to_list(lex->thd, yyvsp[-2].table, yyvsp[-1].lex_str_ptr,
					   sel->get_table_join_options(),
					   lex->lock_option,
					   sel->get_use_index(),
					   sel->get_ignore_index())))
	    YYABORT;
	}
    break;

  case 893:
#line 3498 "sql_yacc.yy"
    { add_join_on(yyvsp[-3].table_list,yyvsp[-1].item); yyvsp[-3].table_list->outer_join|=JOIN_TYPE_LEFT; yyval.table_list=yyvsp[-3].table_list; }
    break;

  case 894:
#line 3500 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  SELECT_LEX_UNIT *unit= lex->current_select->master_unit();
	  lex->current_select= unit->outer_select();
	  if (!(yyval.table_list= lex->current_select->
                add_table_to_list(lex->thd, new Table_ident(unit), yyvsp[0].lex_str_ptr, 0,
				  TL_READ,(List<String> *)0,
	                          (List<String> *)0)))

	    YYABORT;
	}
    break;

  case 895:
#line 3511 "sql_yacc.yy"
    { yyval.table_list=yyvsp[-1].table_list; }
    break;

  case 897:
#line 3516 "sql_yacc.yy"
    {
	    LEX *lex= Lex;
            SELECT_LEX * sel= lex->current_select;
	    if (sel->set_braces(1))
	    {
	      yyerror(ER(ER_SYNTAX_ERROR));
	      YYABORT;
	    }
            /* select in braces, can't contain global parameters */
	    if (sel->master_unit()->fake_select_lex)
              sel->master_unit()->global_parameters=
                 sel->master_unit()->fake_select_lex;
	  }
    break;

  case 898:
#line 3531 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  lex->derived_tables= 1;
	  if (((int)lex->sql_command >= (int)SQLCOM_HA_OPEN &&
	       lex->sql_command <= (int)SQLCOM_HA_READ) ||
	       lex->sql_command == (int)SQLCOM_KILL)
	  {
	    yyerror(ER(ER_SYNTAX_ERROR));
	    YYABORT;
	  }
	  if (lex->current_select->linkage == GLOBAL_OPTIONS_TYPE ||
              mysql_new_select(lex, 1))
	    YYABORT;
	  mysql_init_select(lex);
	  lex->current_select->linkage= DERIVED_TABLE_TYPE;
	  lex->current_select->parsing_place= SELECT_LIST;
	}
    break;

  case 899:
#line 3549 "sql_yacc.yy"
    {
	  Select->parsing_place= NO_MATTER;
	}
    break;

  case 901:
#line 3556 "sql_yacc.yy"
    {}
    break;

  case 902:
#line 3557 "sql_yacc.yy"
    {}
    break;

  case 903:
#line 3560 "sql_yacc.yy"
    {}
    break;

  case 904:
#line 3562 "sql_yacc.yy"
    {
	    SELECT_LEX *sel= Select;
	    sel->use_index= *yyvsp[0].string_list;
	    sel->use_index_ptr= &sel->use_index;
	  }
    break;

  case 905:
#line 3568 "sql_yacc.yy"
    {
	    SELECT_LEX *sel= Select;
	    sel->use_index= *yyvsp[0].string_list;
	    sel->use_index_ptr= &sel->use_index;
	    sel->table_join_options|= TL_OPTION_FORCE_INDEX;
	  }
    break;

  case 906:
#line 3575 "sql_yacc.yy"
    {
	    SELECT_LEX *sel= Select;
	    sel->ignore_index= *yyvsp[0].string_list;
	    sel->ignore_index_ptr= &sel->ignore_index;
	  }
    break;

  case 907:
#line 3582 "sql_yacc.yy"
    { Select->interval_list.empty(); }
    break;

  case 908:
#line 3584 "sql_yacc.yy"
    { yyval.string_list= &Select->interval_list; }
    break;

  case 909:
#line 3588 "sql_yacc.yy"
    {}
    break;

  case 910:
#line 3589 "sql_yacc.yy"
    {}
    break;

  case 911:
#line 3594 "sql_yacc.yy"
    { Select->
	    interval_list.push_back(new (YYTHD->mem_root) String((const char*) yyvsp[0].lex_str.str, yyvsp[0].lex_str.length,
				    system_charset_info)); }
    break;

  case 912:
#line 3598 "sql_yacc.yy"
    { Select->
	    interval_list.push_back(new (YYTHD->mem_root) String((const char*) yyvsp[0].lex_str.str, yyvsp[0].lex_str.length,
				    system_charset_info)); }
    break;

  case 913:
#line 3602 "sql_yacc.yy"
    { Select->
	    interval_list.push_back(new (YYTHD->mem_root) String("PRIMARY", 7,
				    system_charset_info)); }
    break;

  case 914:
#line 3608 "sql_yacc.yy"
    {
	    SELECT_LEX *sel= Select;
	    if (!(yyval.item= new Item_func_eq(new Item_field(sel->db1, sel->table1,
						      yyvsp[0].lex_str.str),
				       new Item_field(sel->db2, sel->table2,
						      yyvsp[0].lex_str.str))))
	      YYABORT;
	  }
    break;

  case 915:
#line 3617 "sql_yacc.yy"
    {
	    SELECT_LEX *sel= Select;
	    if (!(yyval.item= new Item_cond_and(new Item_func_eq(new Item_field(sel->db1,sel->table1,yyvsp[0].lex_str.str), new Item_field(sel->db2,sel->table2,yyvsp[0].lex_str.str)), yyvsp[-2].item)))
	      YYABORT;
	  }
    break;

  case 916:
#line 3624 "sql_yacc.yy"
    { yyval.interval=INTERVAL_DAY_HOUR; }
    break;

  case 917:
#line 3625 "sql_yacc.yy"
    { yyval.interval=INTERVAL_DAY_MICROSECOND; }
    break;

  case 918:
#line 3626 "sql_yacc.yy"
    { yyval.interval=INTERVAL_DAY_MINUTE; }
    break;

  case 919:
#line 3627 "sql_yacc.yy"
    { yyval.interval=INTERVAL_DAY_SECOND; }
    break;

  case 920:
#line 3628 "sql_yacc.yy"
    { yyval.interval=INTERVAL_DAY; }
    break;

  case 921:
#line 3629 "sql_yacc.yy"
    { yyval.interval=INTERVAL_HOUR_MICROSECOND; }
    break;

  case 922:
#line 3630 "sql_yacc.yy"
    { yyval.interval=INTERVAL_HOUR_MINUTE; }
    break;

  case 923:
#line 3631 "sql_yacc.yy"
    { yyval.interval=INTERVAL_HOUR_SECOND; }
    break;

  case 924:
#line 3632 "sql_yacc.yy"
    { yyval.interval=INTERVAL_HOUR; }
    break;

  case 925:
#line 3633 "sql_yacc.yy"
    { yyval.interval=INTERVAL_MICROSECOND; }
    break;

  case 926:
#line 3634 "sql_yacc.yy"
    { yyval.interval=INTERVAL_MINUTE_MICROSECOND; }
    break;

  case 927:
#line 3635 "sql_yacc.yy"
    { yyval.interval=INTERVAL_MINUTE_SECOND; }
    break;

  case 928:
#line 3636 "sql_yacc.yy"
    { yyval.interval=INTERVAL_MINUTE; }
    break;

  case 929:
#line 3637 "sql_yacc.yy"
    { yyval.interval=INTERVAL_MONTH; }
    break;

  case 930:
#line 3638 "sql_yacc.yy"
    { yyval.interval=INTERVAL_SECOND_MICROSECOND; }
    break;

  case 931:
#line 3639 "sql_yacc.yy"
    { yyval.interval=INTERVAL_SECOND; }
    break;

  case 932:
#line 3640 "sql_yacc.yy"
    { yyval.interval=INTERVAL_YEAR_MONTH; }
    break;

  case 933:
#line 3641 "sql_yacc.yy"
    { yyval.interval=INTERVAL_YEAR; }
    break;

  case 934:
#line 3645 "sql_yacc.yy"
    {yyval.date_time_type=MYSQL_TIMESTAMP_DATE;}
    break;

  case 935:
#line 3646 "sql_yacc.yy"
    {yyval.date_time_type=MYSQL_TIMESTAMP_TIME;}
    break;

  case 936:
#line 3647 "sql_yacc.yy"
    {yyval.date_time_type=MYSQL_TIMESTAMP_DATETIME;}
    break;

  case 937:
#line 3648 "sql_yacc.yy"
    {yyval.date_time_type=MYSQL_TIMESTAMP_DATETIME;}
    break;

  case 941:
#line 3657 "sql_yacc.yy"
    { yyval.lex_str_ptr=0; }
    break;

  case 942:
#line 3659 "sql_yacc.yy"
    { yyval.lex_str_ptr= (LEX_STRING*) sql_memdup(&yyvsp[0].lex_str,sizeof(LEX_STRING)); }
    break;

  case 945:
#line 3667 "sql_yacc.yy"
    { Select->where= 0; }
    break;

  case 946:
#line 3669 "sql_yacc.yy"
    {
            Select->parsing_place= IN_WHERE;
          }
    break;

  case 947:
#line 3673 "sql_yacc.yy"
    {
            SELECT_LEX *select= Select;
	    select->where= yyvsp[0].item;
            select->parsing_place= NO_MATTER;
	    if (yyvsp[0].item)
	      yyvsp[0].item->top_level_item();
	  }
    break;

  case 949:
#line 3685 "sql_yacc.yy"
    {
	    Select->parsing_place= IN_HAVING;
          }
    break;

  case 950:
#line 3689 "sql_yacc.yy"
    {
	    SELECT_LEX *sel= Select;
	    sel->having= yyvsp[0].item;
	    sel->parsing_place= NO_MATTER;
	    if (yyvsp[0].item)
	      yyvsp[0].item->top_level_item();
	  }
    break;

  case 951:
#line 3699 "sql_yacc.yy"
    { yyval.item= yyvsp[0].item; }
    break;

  case 952:
#line 3701 "sql_yacc.yy"
    { 
            yyval.item= new Item_string("\\", 1, &my_charset_latin1);
          }
    break;

  case 955:
#line 3717 "sql_yacc.yy"
    { if (add_group_to_list(YYTHD, yyvsp[-1].item,(bool) yyvsp[0].num)) YYABORT; }
    break;

  case 956:
#line 3719 "sql_yacc.yy"
    { if (add_group_to_list(YYTHD, yyvsp[-1].item,(bool) yyvsp[0].num)) YYABORT; }
    break;

  case 957:
#line 3722 "sql_yacc.yy"
    {}
    break;

  case 958:
#line 3724 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    if (lex->current_select->linkage == GLOBAL_OPTIONS_TYPE)
	    {
	      net_printf(lex->thd, ER_WRONG_USAGE, "WITH CUBE",
		       "global union parameters");
	      YYABORT;
	    }
	    lex->current_select->olap= CUBE_TYPE;
	    net_printf(lex->thd, ER_NOT_SUPPORTED_YET, "CUBE");
	    YYABORT;	/* To be deleted in 5.1 */
	  }
    break;

  case 959:
#line 3737 "sql_yacc.yy"
    {
	    LEX *lex= Lex;
	    if (lex->current_select->linkage == GLOBAL_OPTIONS_TYPE)
	    {
	      net_printf(lex->thd, ER_WRONG_USAGE, "WITH ROLLUP",
		       "global union parameters");
	      YYABORT;
	    }
	    lex->current_select->olap= ROLLUP_TYPE;
	  }
    break;

  case 962:
#line 3759 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  if (lex->current_select->linkage != GLOBAL_OPTIONS_TYPE &&
	      lex->current_select->olap !=
	      UNSPECIFIED_OLAP_TYPE)
	  {
	    net_printf(lex->thd, ER_WRONG_USAGE,
		       "CUBE/ROLLUP",
		       "ORDER BY");
	    YYABORT;
	  }
	}
    break;

  case 964:
#line 3774 "sql_yacc.yy"
    { if (add_order_to_list(YYTHD, yyvsp[-1].item,(bool) yyvsp[0].num)) YYABORT; }
    break;

  case 965:
#line 3776 "sql_yacc.yy"
    { if (add_order_to_list(YYTHD, yyvsp[-1].item,(bool) yyvsp[0].num)) YYABORT; }
    break;

  case 966:
#line 3779 "sql_yacc.yy"
    { yyval.num =  1; }
    break;

  case 967:
#line 3780 "sql_yacc.yy"
    { yyval.num =1; }
    break;

  case 968:
#line 3781 "sql_yacc.yy"
    { yyval.num =0; }
    break;

  case 969:
#line 3786 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  SELECT_LEX *sel= lex->current_select;
          sel->offset_limit= 0L;
          sel->select_limit= HA_POS_ERROR;
	}
    break;

  case 970:
#line 3792 "sql_yacc.yy"
    {}
    break;

  case 971:
#line 3796 "sql_yacc.yy"
    {}
    break;

  case 972:
#line 3797 "sql_yacc.yy"
    {}
    break;

  case 973:
#line 3801 "sql_yacc.yy"
    {}
    break;

  case 974:
#line 3806 "sql_yacc.yy"
    {
            SELECT_LEX *sel= Select;
            sel->select_limit= yyvsp[0].ulong_num;
            sel->offset_limit= 0L;
	    sel->explicit_limit= 1;
	  }
    break;

  case 975:
#line 3813 "sql_yacc.yy"
    {
	    SELECT_LEX *sel= Select;
	    sel->select_limit= yyvsp[0].ulong_num;
	    sel->offset_limit= yyvsp[-2].ulong_num;
	    sel->explicit_limit= 1;
	  }
    break;

  case 976:
#line 3820 "sql_yacc.yy"
    {
	    SELECT_LEX *sel= Select;
	    sel->select_limit= yyvsp[-2].ulong_num;
	    sel->offset_limit= yyvsp[0].ulong_num;
	    sel->explicit_limit= 1;
	  }
    break;

  case 977:
#line 3831 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->current_select->select_limit= HA_POS_ERROR;
	}
    break;

  case 978:
#line 3836 "sql_yacc.yy"
    {
	  SELECT_LEX *sel= Select;
	  sel->select_limit= (ha_rows) yyvsp[0].ulonglong_number;
	  sel->explicit_limit= 1;
	}
    break;

  case 979:
#line 3843 "sql_yacc.yy"
    { int error; yyval.ulong_num= (ulong) my_strtoll10(yyvsp[0].lex_str.str, (char**) 0, &error); }
    break;

  case 980:
#line 3844 "sql_yacc.yy"
    { int error; yyval.ulong_num= (ulong) my_strtoll10(yyvsp[0].lex_str.str, (char**) 0, &error); }
    break;

  case 981:
#line 3845 "sql_yacc.yy"
    { int error; yyval.ulong_num= (ulong) my_strtoll10(yyvsp[0].lex_str.str, (char**) 0, &error); }
    break;

  case 982:
#line 3846 "sql_yacc.yy"
    { int error; yyval.ulong_num= (ulong) my_strtoll10(yyvsp[0].lex_str.str, (char**) 0, &error); }
    break;

  case 983:
#line 3847 "sql_yacc.yy"
    { int error; yyval.ulong_num= (ulong) my_strtoll10(yyvsp[0].lex_str.str, (char**) 0, &error); }
    break;

  case 984:
#line 3851 "sql_yacc.yy"
    { int error; yyval.ulonglong_number= (ulonglong) my_strtoll10(yyvsp[0].lex_str.str, (char**) 0, &error); }
    break;

  case 985:
#line 3852 "sql_yacc.yy"
    { int error; yyval.ulonglong_number= (ulonglong) my_strtoll10(yyvsp[0].lex_str.str, (char**) 0, &error); }
    break;

  case 986:
#line 3853 "sql_yacc.yy"
    { int error; yyval.ulonglong_number= (ulonglong) my_strtoll10(yyvsp[0].lex_str.str, (char**) 0, &error); }
    break;

  case 987:
#line 3854 "sql_yacc.yy"
    { int error; yyval.ulonglong_number= (ulonglong) my_strtoll10(yyvsp[0].lex_str.str, (char**) 0, &error); }
    break;

  case 988:
#line 3855 "sql_yacc.yy"
    { int error; yyval.ulonglong_number= (ulonglong) my_strtoll10(yyvsp[0].lex_str.str, (char**) 0, &error); }
    break;

  case 990:
#line 3861 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    if (&lex->select_lex != lex->current_select)
	    {
	      net_printf(lex->thd, ER_WRONG_USAGE,
			  "PROCEDURE",
			  "subquery");
	      YYABORT;
	    }
	    lex->proc_list.elements=0;
	    lex->proc_list.first=0;
	    lex->proc_list.next= (byte**) &lex->proc_list.first;
	    if (add_proc_to_list(lex->thd, new Item_field(NULL,NULL,yyvsp[0].lex_str.str)))
	      YYABORT;
	    Lex->uncacheable(UNCACHEABLE_SIDEEFFECT);
	  }
    break;

  case 992:
#line 3881 "sql_yacc.yy"
    {}
    break;

  case 993:
#line 3882 "sql_yacc.yy"
    {}
    break;

  case 996:
#line 3890 "sql_yacc.yy"
    {
	    LEX *lex= Lex;
	    if (add_proc_to_list(lex->thd, yyvsp[0].item))
	      YYABORT;
	    if (!yyvsp[0].item->name)
	      yyvsp[0].item->set_name(yyvsp[-1].simple_string,(uint) ((char*) lex->tok_end - yyvsp[-1].simple_string), YYTHD->charset());
	  }
    break;

  case 997:
#line 3901 "sql_yacc.yy"
    {
             LEX *lex=Lex;
	     if (!lex->describe && (!(lex->result= new select_dumpvar())))
	        YYABORT;
	   }
    break;

  case 998:
#line 3907 "sql_yacc.yy"
    {}
    break;

  case 1000:
#line 3912 "sql_yacc.yy"
    {}
    break;

  case 1001:
#line 3916 "sql_yacc.yy"
    {
             LEX *lex=Lex;
	     if (lex->result && ((select_dumpvar *)lex->result)->var_list.push_back((LEX_STRING*) sql_memdup(&yyvsp[0].lex_str,sizeof(LEX_STRING))))
	       YYABORT;
	   }
    break;

  case 1002:
#line 3925 "sql_yacc.yy"
    {
          LEX *lex= Lex;
          lex->uncacheable(UNCACHEABLE_SIDEEFFECT);
          if (!(lex->exchange= new sql_exchange(yyvsp[0].lex_str.str, 0)) ||
              !(lex->result= new select_export(lex->exchange)))
            YYABORT;
	}
    break;

  case 1004:
#line 3934 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  if (!lex->describe)
	  {
	    lex->uncacheable(UNCACHEABLE_SIDEEFFECT);
	    if (!(lex->exchange= new sql_exchange(yyvsp[0].lex_str.str,1)))
	      YYABORT;
	    if (!(lex->result= new select_dump(lex->exchange)))
	      YYABORT;
	  }
	}
    break;

  case 1005:
#line 3946 "sql_yacc.yy"
    {
	  Lex->uncacheable(UNCACHEABLE_SIDEEFFECT);
	}
    break;

  case 1006:
#line 3956 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->sql_command = SQLCOM_DO;
	  mysql_init_select(lex);
	}
    break;

  case 1007:
#line 3962 "sql_yacc.yy"
    {
	  Lex->insert_list= yyvsp[0].item_list;
	}
    break;

  case 1008:
#line 3973 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->sql_command = SQLCOM_DROP_TABLE;
	  lex->drop_temporary= yyvsp[-4].num;
	  lex->drop_if_exists= yyvsp[-2].num;
	}
    break;

  case 1009:
#line 3979 "sql_yacc.yy"
    {}
    break;

  case 1010:
#line 3980 "sql_yacc.yy"
    {
	     LEX *lex=Lex;
	     lex->sql_command= SQLCOM_DROP_INDEX;
	     lex->alter_info.drop_list.empty();
	     lex->alter_info.drop_list.push_back(new Alter_drop(Alter_drop::KEY,
                                                                yyvsp[-3].lex_str.str));
	     if (!lex->current_select->add_table_to_list(lex->thd, yyvsp[-1].table, NULL,
							TL_OPTION_UPDATING))
	      YYABORT;
	  }
    break;

  case 1011:
#line 3991 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command= SQLCOM_DROP_DB;
	    lex->drop_if_exists=yyvsp[-1].num;
	    lex->name=yyvsp[0].lex_str.str;
	 }
    break;

  case 1012:
#line 3998 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command = SQLCOM_DROP_FUNCTION;
	    lex->udf.name = yyvsp[0].lex_str;
	  }
    break;

  case 1013:
#line 4004 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command = SQLCOM_DROP_USER;
	    lex->users_list.empty();
	  }
    break;

  case 1014:
#line 4010 "sql_yacc.yy"
    {}
    break;

  case 1017:
#line 4020 "sql_yacc.yy"
    {
	  if (!Select->add_table_to_list(YYTHD, yyvsp[0].table, NULL, TL_OPTION_UPDATING))
	    YYABORT;
	}
    break;

  case 1018:
#line 4027 "sql_yacc.yy"
    { yyval.num= 0; }
    break;

  case 1019:
#line 4028 "sql_yacc.yy"
    { yyval.num= 1; }
    break;

  case 1020:
#line 4032 "sql_yacc.yy"
    { yyval.num= 0; }
    break;

  case 1021:
#line 4033 "sql_yacc.yy"
    { yyval.num= 1; }
    break;

  case 1022:
#line 4041 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  lex->sql_command= SQLCOM_INSERT;
	  lex->duplicates= DUP_ERROR;
          mysql_init_select(lex);
	  /* for subselects */
          lex->lock_option= (using_update_log) ? TL_READ_NO_INSERT : TL_READ;
	  lex->select_lex.resolve_mode= SELECT_LEX::INSERT_MODE;
	}
    break;

  case 1023:
#line 4051 "sql_yacc.yy"
    {
	  Select->set_lock_for_tables(yyvsp[-2].lock_type);
	  Lex->current_select= &Lex->select_lex;
	}
    break;

  case 1024:
#line 4056 "sql_yacc.yy"
    {}
    break;

  case 1025:
#line 4061 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->sql_command = SQLCOM_REPLACE;
	  lex->duplicates= DUP_REPLACE;
          mysql_init_select(lex);
	  lex->select_lex.resolve_mode= SELECT_LEX::INSERT_MODE;
	}
    break;

  case 1026:
#line 4069 "sql_yacc.yy"
    {
	  Select->set_lock_for_tables(yyvsp[-1].lock_type);
	  Lex->current_select= &Lex->select_lex;
	}
    break;

  case 1027:
#line 4074 "sql_yacc.yy"
    {}
    break;

  case 1028:
#line 4075 "sql_yacc.yy"
    {}
    break;

  case 1029:
#line 4079 "sql_yacc.yy"
    { yyval.lock_type= TL_WRITE_CONCURRENT_INSERT; }
    break;

  case 1030:
#line 4080 "sql_yacc.yy"
    { yyval.lock_type= TL_WRITE_LOW_PRIORITY; }
    break;

  case 1031:
#line 4081 "sql_yacc.yy"
    { yyval.lock_type= TL_WRITE_DELAYED; }
    break;

  case 1032:
#line 4082 "sql_yacc.yy"
    { yyval.lock_type= TL_WRITE; }
    break;

  case 1033:
#line 4086 "sql_yacc.yy"
    { yyval.lock_type= yyvsp[0].lock_type; }
    break;

  case 1034:
#line 4087 "sql_yacc.yy"
    { yyval.lock_type= TL_WRITE_DELAYED; }
    break;

  case 1035:
#line 4090 "sql_yacc.yy"
    {}
    break;

  case 1036:
#line 4091 "sql_yacc.yy"
    {}
    break;

  case 1037:
#line 4095 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->field_list.empty();
	  lex->many_values.empty();
	  lex->insert_list=0;
	}
    break;

  case 1038:
#line 4103 "sql_yacc.yy"
    {}
    break;

  case 1039:
#line 4104 "sql_yacc.yy"
    {}
    break;

  case 1040:
#line 4105 "sql_yacc.yy"
    {}
    break;

  case 1041:
#line 4107 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    if (!(lex->insert_list = new List_item) ||
		lex->many_values.push_back(lex->insert_list))
	      YYABORT;
	   }
    break;

  case 1043:
#line 4116 "sql_yacc.yy"
    { }
    break;

  case 1044:
#line 4117 "sql_yacc.yy"
    { }
    break;

  case 1045:
#line 4118 "sql_yacc.yy"
    { }
    break;

  case 1046:
#line 4121 "sql_yacc.yy"
    { Lex->field_list.push_back(yyvsp[0].item); }
    break;

  case 1047:
#line 4122 "sql_yacc.yy"
    { Lex->field_list.push_back(yyvsp[0].item); }
    break;

  case 1048:
#line 4125 "sql_yacc.yy"
    {}
    break;

  case 1049:
#line 4126 "sql_yacc.yy"
    {}
    break;

  case 1050:
#line 4127 "sql_yacc.yy"
    { Select->set_braces(0);}
    break;

  case 1051:
#line 4127 "sql_yacc.yy"
    {}
    break;

  case 1052:
#line 4128 "sql_yacc.yy"
    { Select->set_braces(1);}
    break;

  case 1053:
#line 4128 "sql_yacc.yy"
    {}
    break;

  case 1058:
#line 4142 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  if (lex->field_list.push_back(yyvsp[-2].item) ||
	      lex->insert_list->push_back(yyvsp[0].item))
	    YYABORT;
	 }
    break;

  case 1059:
#line 4149 "sql_yacc.yy"
    {}
    break;

  case 1060:
#line 4150 "sql_yacc.yy"
    {}
    break;

  case 1061:
#line 4154 "sql_yacc.yy"
    {}
    break;

  case 1062:
#line 4155 "sql_yacc.yy"
    {}
    break;

  case 1063:
#line 4160 "sql_yacc.yy"
    {
	    if (!(Lex->insert_list = new List_item))
	      YYABORT;
	 }
    break;

  case 1064:
#line 4165 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  if (lex->many_values.push_back(lex->insert_list))
	    YYABORT;
	 }
    break;

  case 1065:
#line 4172 "sql_yacc.yy"
    {}
    break;

  case 1067:
#line 4177 "sql_yacc.yy"
    {
	  if (Lex->insert_list->push_back(yyvsp[0].item))
	    YYABORT;
	}
    break;

  case 1068:
#line 4182 "sql_yacc.yy"
    {
	    if (Lex->insert_list->push_back(yyvsp[0].item))
	      YYABORT;
	  }
    break;

  case 1069:
#line 4189 "sql_yacc.yy"
    { yyval.item= yyvsp[0].item;}
    break;

  case 1070:
#line 4190 "sql_yacc.yy"
    {yyval.item= new Item_default_value(); }
    break;

  case 1072:
#line 4195 "sql_yacc.yy"
    { Lex->duplicates= DUP_UPDATE; }
    break;

  case 1074:
#line 4203 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  mysql_init_select(lex);
          lex->sql_command= SQLCOM_UPDATE;
	  lex->lock_option= TL_UNLOCK; 	/* Will be set later */
	  lex->duplicates= DUP_ERROR; 
        }
    break;

  case 1075:
#line 4212 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
          if (lex->select_lex.table_list.elements > 1)
	  {
            lex->sql_command= SQLCOM_UPDATE_MULTI;
	    lex->multi_lock_option= yyvsp[-4].lock_type;
	  }
	  else if (lex->select_lex.get_table_list()->derived)
	  {
	    /* it is single table update and it is update of derived table */
	    net_printf(lex->thd, ER_NON_UPDATABLE_TABLE,
		       lex->select_lex.get_table_list()->alias, "UPDATE");
	    YYABORT;
	  }
	  else
	    Select->set_lock_for_tables(yyvsp[-4].lock_type);
	}
    break;

  case 1076:
#line 4229 "sql_yacc.yy"
    {}
    break;

  case 1079:
#line 4238 "sql_yacc.yy"
    {
	  if (add_item_to_list(YYTHD, yyvsp[-2].item) || add_value_to_list(YYTHD, yyvsp[0].item))
	    YYABORT;
	}
    break;

  case 1082:
#line 4249 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  if (lex->update_list.push_back(yyvsp[-2].item) || 
	      lex->value_list.push_back(yyvsp[0].item))
	    YYABORT;
	}
    break;

  case 1083:
#line 4257 "sql_yacc.yy"
    { yyval.lock_type= YYTHD->update_lock_default; }
    break;

  case 1084:
#line 4258 "sql_yacc.yy"
    { yyval.lock_type= TL_WRITE_LOW_PRIORITY; }
    break;

  case 1085:
#line 4264 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  lex->sql_command= SQLCOM_DELETE;
          mysql_init_select(lex);
	  lex->lock_option= lex->thd->update_lock_default;
	  lex->ignore= 0;
	  lex->select_lex.init_order();
	}
    break;

  case 1086:
#line 4272 "sql_yacc.yy"
    {}
    break;

  case 1087:
#line 4277 "sql_yacc.yy"
    {
	  if (!Select->add_table_to_list(YYTHD, yyvsp[0].table, NULL, TL_OPTION_UPDATING,
					 Lex->lock_option))
	    YYABORT;
	}
    break;

  case 1088:
#line 4283 "sql_yacc.yy"
    {}
    break;

  case 1089:
#line 4285 "sql_yacc.yy"
    { mysql_init_multi_delete(Lex); }
    break;

  case 1091:
#line 4288 "sql_yacc.yy"
    { mysql_init_multi_delete(Lex); }
    break;

  case 1092:
#line 4290 "sql_yacc.yy"
    {}
    break;

  case 1093:
#line 4294 "sql_yacc.yy"
    {}
    break;

  case 1094:
#line 4295 "sql_yacc.yy"
    {}
    break;

  case 1095:
#line 4299 "sql_yacc.yy"
    {
	  if (!Select->add_table_to_list(YYTHD, new Table_ident(yyvsp[-2].lex_str), yyvsp[0].lex_str_ptr,
					 TL_OPTION_UPDATING, Lex->lock_option))
	    YYABORT;
        }
    break;

  case 1096:
#line 4305 "sql_yacc.yy"
    {
	    if (!Select->add_table_to_list(YYTHD,
					   new Table_ident(YYTHD, yyvsp[-4].lex_str, yyvsp[-2].lex_str, 0),
					   yyvsp[0].lex_str_ptr, TL_OPTION_UPDATING,
					   Lex->lock_option))
	      YYABORT;
	  }
    break;

  case 1097:
#line 4315 "sql_yacc.yy"
    {}
    break;

  case 1098:
#line 4316 "sql_yacc.yy"
    {}
    break;

  case 1099:
#line 4320 "sql_yacc.yy"
    {}
    break;

  case 1100:
#line 4321 "sql_yacc.yy"
    {}
    break;

  case 1101:
#line 4324 "sql_yacc.yy"
    { Select->options|= OPTION_QUICK; }
    break;

  case 1102:
#line 4325 "sql_yacc.yy"
    { Lex->lock_option= TL_WRITE_LOW_PRIORITY; }
    break;

  case 1103:
#line 4326 "sql_yacc.yy"
    { Lex->ignore= 1; }
    break;

  case 1104:
#line 4330 "sql_yacc.yy"
    {
	  LEX* lex= Lex;
	  lex->sql_command= SQLCOM_TRUNCATE;
	  lex->select_lex.options= 0;
	  lex->select_lex.init_order();
	}
    break;

  case 1107:
#line 4345 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->wild=0;
	  bzero((char*) &lex->create_info,sizeof(lex->create_info));
	}
    break;

  case 1108:
#line 4351 "sql_yacc.yy"
    {}
    break;

  case 1109:
#line 4356 "sql_yacc.yy"
    { Lex->sql_command= SQLCOM_SHOW_DATABASES; }
    break;

  case 1110:
#line 4358 "sql_yacc.yy"
    {
	    LEX *lex= Lex;
	    lex->sql_command= SQLCOM_SHOW_TABLES;
	    lex->select_lex.db= yyvsp[-1].simple_string;
	   }
    break;

  case 1111:
#line 4364 "sql_yacc.yy"
    {
	    LEX *lex= Lex;
	    lex->sql_command= SQLCOM_SHOW_TABLES;
	    lex->describe= DESCRIBE_EXTENDED;
	    lex->select_lex.db= yyvsp[-1].simple_string;
	  }
    break;

  case 1112:
#line 4371 "sql_yacc.yy"
    {
	    LEX *lex= Lex;
	    lex->sql_command= SQLCOM_SHOW_OPEN_TABLES;
	    lex->select_lex.db= yyvsp[-1].simple_string;
	  }
    break;

  case 1113:
#line 4377 "sql_yacc.yy"
    { Lex->create_info.db_type= yyvsp[0].db_type; }
    break;

  case 1115:
#line 4380 "sql_yacc.yy"
    {
	    Lex->sql_command= SQLCOM_SHOW_FIELDS;
	    if (yyvsp[-1].simple_string)
	      yyvsp[-2].table->change_db(yyvsp[-1].simple_string);
	    if (!Select->add_table_to_list(YYTHD, yyvsp[-2].table, NULL, 0))
	      YYABORT;
	  }
    break;

  case 1116:
#line 4391 "sql_yacc.yy"
    {
	    Lex->sql_command = SQLCOM_SHOW_NEW_MASTER;
	    Lex->mi.log_file_name = yyvsp[-8].lex_str.str;
	    Lex->mi.pos = yyvsp[-4].ulonglong_number;
	    Lex->mi.server_id = yyvsp[0].ulong_num;
          }
    break;

  case 1117:
#line 4398 "sql_yacc.yy"
    {
	    Lex->sql_command = SQLCOM_SHOW_BINLOGS;
          }
    break;

  case 1118:
#line 4402 "sql_yacc.yy"
    {
	    Lex->sql_command = SQLCOM_SHOW_SLAVE_HOSTS;
          }
    break;

  case 1119:
#line 4406 "sql_yacc.yy"
    {
	    LEX *lex= Lex;
	    lex->sql_command= SQLCOM_SHOW_BINLOG_EVENTS;
          }
    break;

  case 1121:
#line 4411 "sql_yacc.yy"
    {
	    Lex->sql_command= SQLCOM_SHOW_KEYS;
	    if (yyvsp[0].simple_string)
	      yyvsp[-1].table->change_db(yyvsp[0].simple_string);
	    if (!Select->add_table_to_list(YYTHD, yyvsp[-1].table, NULL, 0))
	      YYABORT;
	  }
    break;

  case 1122:
#line 4419 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command= SQLCOM_SHOW_COLUMN_TYPES;
	  }
    break;

  case 1123:
#line 4424 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command= SQLCOM_SHOW_STORAGE_ENGINES;
	    WARN_DEPRECATED("SHOW TABLE TYPES", "SHOW [STORAGE] ENGINES");
	  }
    break;

  case 1124:
#line 4430 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command= SQLCOM_SHOW_STORAGE_ENGINES;
	  }
    break;

  case 1125:
#line 4435 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command= SQLCOM_SHOW_PRIVILEGES;
	  }
    break;

  case 1126:
#line 4440 "sql_yacc.yy"
    { (void) create_select_for_variable("warning_count"); }
    break;

  case 1127:
#line 4442 "sql_yacc.yy"
    { (void) create_select_for_variable("error_count"); }
    break;

  case 1128:
#line 4444 "sql_yacc.yy"
    { Lex->sql_command = SQLCOM_SHOW_WARNS;}
    break;

  case 1129:
#line 4446 "sql_yacc.yy"
    { Lex->sql_command = SQLCOM_SHOW_ERRORS;}
    break;

  case 1130:
#line 4448 "sql_yacc.yy"
    { Lex->sql_command= SQLCOM_SHOW_STATUS; }
    break;

  case 1131:
#line 4450 "sql_yacc.yy"
    { Lex->sql_command = SQLCOM_SHOW_INNODB_STATUS; WARN_DEPRECATED("SHOW INNODB STATUS", "SHOW ENGINE INNODB STATUS"); }
    break;

  case 1132:
#line 4452 "sql_yacc.yy"
    { Lex->sql_command= SQLCOM_SHOW_PROCESSLIST;}
    break;

  case 1133:
#line 4454 "sql_yacc.yy"
    {
	    THD *thd= YYTHD;
	    thd->lex->sql_command= SQLCOM_SHOW_VARIABLES;
	    thd->lex->option_type= (enum_var_type) yyvsp[-2].num;
	  }
    break;

  case 1134:
#line 4460 "sql_yacc.yy"
    { Lex->sql_command= SQLCOM_SHOW_CHARSETS; }
    break;

  case 1135:
#line 4462 "sql_yacc.yy"
    { Lex->sql_command= SQLCOM_SHOW_COLLATIONS; }
    break;

  case 1136:
#line 4464 "sql_yacc.yy"
    { Lex->sql_command= SQLCOM_SHOW_LOGS; WARN_DEPRECATED("SHOW BDB LOGS", "SHOW ENGINE BDB LOGS"); }
    break;

  case 1137:
#line 4466 "sql_yacc.yy"
    { Lex->sql_command= SQLCOM_SHOW_LOGS; WARN_DEPRECATED("SHOW LOGS", "SHOW ENGINE BDB LOGS"); }
    break;

  case 1138:
#line 4468 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command= SQLCOM_SHOW_GRANTS;
	    THD *thd= lex->thd;
	    LEX_USER *curr_user;
            if (!(curr_user= (LEX_USER*) thd->alloc(sizeof(st_lex_user))))
              YYABORT;
            curr_user->user.str= thd->priv_user;
            curr_user->user.length= strlen(thd->priv_user);
            if (*thd->priv_host != 0)
            {
              curr_user->host.str= thd->priv_host;
              curr_user->host.length= strlen(thd->priv_host);
            }
            else
            {
              curr_user->host.str= (char *) "%";
              curr_user->host.length= 1;
            }
            curr_user->password.str=NullS;
	    lex->grant_user= curr_user;
	  }
    break;

  case 1139:
#line 4491 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->sql_command= SQLCOM_SHOW_GRANTS;
	    lex->grant_user=yyvsp[0].lex_user;
	    lex->grant_user->password.str=NullS;
	  }
    break;

  case 1140:
#line 4498 "sql_yacc.yy"
    {
	    Lex->sql_command=SQLCOM_SHOW_CREATE_DB;
	    Lex->create_info.options=yyvsp[-1].num;
	    Lex->name=yyvsp[0].lex_str.str;
	  }
    break;

  case 1141:
#line 4504 "sql_yacc.yy"
    {
	    Lex->sql_command = SQLCOM_SHOW_CREATE;
	    if (!Select->add_table_to_list(YYTHD, yyvsp[0].table, NULL,0))
	      YYABORT;
	  }
    break;

  case 1142:
#line 4510 "sql_yacc.yy"
    {
	    Lex->sql_command = SQLCOM_SHOW_MASTER_STAT;
          }
    break;

  case 1143:
#line 4514 "sql_yacc.yy"
    {
	    Lex->sql_command = SQLCOM_SHOW_SLAVE_STAT;
          }
    break;

  case 1144:
#line 4520 "sql_yacc.yy"
    {
	    switch (Lex->create_info.db_type) {
	    case DB_TYPE_INNODB:
	      Lex->sql_command = SQLCOM_SHOW_INNODB_STATUS;
	      break;
	    default:
	      net_printf(YYTHD, ER_NOT_SUPPORTED_YET, "STATUS");
	      YYABORT;
	    }
	  }
    break;

  case 1145:
#line 4531 "sql_yacc.yy"
    {
	    switch (Lex->create_info.db_type) {
	    case DB_TYPE_BERKELEY_DB:
	      Lex->sql_command = SQLCOM_SHOW_LOGS;
	      break;
	    default:
	      net_printf(YYTHD, ER_NOT_SUPPORTED_YET, "LOGS");
	      YYABORT;
	    }
	  }
    break;

  case 1150:
#line 4551 "sql_yacc.yy"
    { yyval.simple_string= 0; }
    break;

  case 1151:
#line 4552 "sql_yacc.yy"
    { yyval.simple_string= yyvsp[0].lex_str.str; }
    break;

  case 1153:
#line 4557 "sql_yacc.yy"
    { Lex->wild=  new (YYTHD->mem_root) String(yyvsp[0].lex_str.str, yyvsp[0].lex_str.length,
                                                      system_charset_info); }
    break;

  case 1154:
#line 4561 "sql_yacc.yy"
    { Lex->verbose=0; }
    break;

  case 1155:
#line 4562 "sql_yacc.yy"
    { Lex->verbose=1; }
    break;

  case 1158:
#line 4569 "sql_yacc.yy"
    { Lex->mi.log_file_name = 0; }
    break;

  case 1159:
#line 4570 "sql_yacc.yy"
    { Lex->mi.log_file_name = yyvsp[0].lex_str.str; }
    break;

  case 1160:
#line 4573 "sql_yacc.yy"
    { Lex->mi.pos = 4; /* skip magic number */ }
    break;

  case 1161:
#line 4574 "sql_yacc.yy"
    { Lex->mi.pos = yyvsp[0].ulonglong_number; }
    break;

  case 1162:
#line 4580 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->wild=0;
	  lex->verbose=0;
	  lex->sql_command=SQLCOM_SHOW_FIELDS;
	  if (!Select->add_table_to_list(lex->thd, yyvsp[0].table, NULL,0))
	    YYABORT;
	}
    break;

  case 1163:
#line 4588 "sql_yacc.yy"
    {}
    break;

  case 1164:
#line 4590 "sql_yacc.yy"
    { Lex->describe|= DESCRIBE_NORMAL; }
    break;

  case 1165:
#line 4592 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    lex->select_lex.options|= SELECT_DESCRIBE;
	  }
    break;

  case 1168:
#line 4603 "sql_yacc.yy"
    {}
    break;

  case 1169:
#line 4604 "sql_yacc.yy"
    { Lex->describe|= DESCRIBE_EXTENDED; }
    break;

  case 1170:
#line 4608 "sql_yacc.yy"
    {}
    break;

  case 1171:
#line 4609 "sql_yacc.yy"
    { Lex->wild= yyvsp[0].string; }
    break;

  case 1172:
#line 4611 "sql_yacc.yy"
    { Lex->wild= new (YYTHD->mem_root) String((const char*) yyvsp[0].lex_str.str,yyvsp[0].lex_str.length,system_charset_info); }
    break;

  case 1173:
#line 4618 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->sql_command= SQLCOM_FLUSH; lex->type=0;
          lex->no_write_to_binlog= yyvsp[0].num;
	}
    break;

  case 1174:
#line 4624 "sql_yacc.yy"
    {}
    break;

  case 1177:
#line 4632 "sql_yacc.yy"
    { Lex->type|= REFRESH_TABLES; }
    break;

  case 1178:
#line 4632 "sql_yacc.yy"
    {}
    break;

  case 1179:
#line 4633 "sql_yacc.yy"
    { Lex->type|= REFRESH_TABLES | REFRESH_READ_LOCK; }
    break;

  case 1180:
#line 4634 "sql_yacc.yy"
    { Lex->type|= REFRESH_QUERY_CACHE_FREE; }
    break;

  case 1181:
#line 4635 "sql_yacc.yy"
    { Lex->type|= REFRESH_HOSTS; }
    break;

  case 1182:
#line 4636 "sql_yacc.yy"
    { Lex->type|= REFRESH_GRANT; }
    break;

  case 1183:
#line 4637 "sql_yacc.yy"
    { Lex->type|= REFRESH_LOG; }
    break;

  case 1184:
#line 4638 "sql_yacc.yy"
    { Lex->type|= REFRESH_STATUS; }
    break;

  case 1185:
#line 4639 "sql_yacc.yy"
    { Lex->type|= REFRESH_SLAVE; }
    break;

  case 1186:
#line 4640 "sql_yacc.yy"
    { Lex->type|= REFRESH_MASTER; }
    break;

  case 1187:
#line 4641 "sql_yacc.yy"
    { Lex->type|= REFRESH_DES_KEY_FILE; }
    break;

  case 1188:
#line 4642 "sql_yacc.yy"
    { Lex->type|= REFRESH_USER_RESOURCES; }
    break;

  case 1189:
#line 4645 "sql_yacc.yy"
    {;}
    break;

  case 1190:
#line 4646 "sql_yacc.yy"
    {;}
    break;

  case 1191:
#line 4650 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->sql_command= SQLCOM_RESET; lex->type=0;
	}
    break;

  case 1192:
#line 4654 "sql_yacc.yy"
    {}
    break;

  case 1195:
#line 4662 "sql_yacc.yy"
    { Lex->type|= REFRESH_SLAVE; }
    break;

  case 1196:
#line 4663 "sql_yacc.yy"
    { Lex->type|= REFRESH_MASTER; }
    break;

  case 1197:
#line 4664 "sql_yacc.yy"
    { Lex->type|= REFRESH_QUERY_CACHE;}
    break;

  case 1198:
#line 4668 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->type=0;
	}
    break;

  case 1199:
#line 4672 "sql_yacc.yy"
    {}
    break;

  case 1201:
#line 4681 "sql_yacc.yy"
    {
	   Lex->sql_command = SQLCOM_PURGE;
	   Lex->to_log = yyvsp[0].lex_str.str;
        }
    break;

  case 1202:
#line 4686 "sql_yacc.yy"
    {
	  if (yyvsp[0].item->check_cols(1) || yyvsp[0].item->fix_fields(Lex->thd, 0, &yyvsp[0].item))
	  {
	    net_printf(Lex->thd, ER_WRONG_ARGUMENTS, "PURGE LOGS BEFORE");
	    YYABORT;
	  }
	  Item *tmp= new Item_func_unix_timestamp(yyvsp[0].item);
	  /*
	    it is OK only emulate fix_fieds, because we need only
            value of constant
	  */
	  tmp->quick_fix_field();
	  Lex->sql_command = SQLCOM_PURGE_BEFORE;
	  Lex->purge_time= (ulong) tmp->val_int();
	}
    break;

  case 1203:
#line 4707 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  if (yyvsp[0].item->fix_fields(lex->thd, 0, &yyvsp[0].item) || yyvsp[0].item->check_cols(1))
	  {
	    send_error(lex->thd, ER_SET_CONSTANTS_ONLY);
	    YYABORT;
	  }
          lex->sql_command=SQLCOM_KILL;
	  lex->thread_id= (ulong) yyvsp[0].item->val_int();
	}
    break;

  case 1204:
#line 4721 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->sql_command=SQLCOM_CHANGE_DB;
	  lex->select_lex.db= yyvsp[0].lex_str.str;
	}
    break;

  case 1205:
#line 4730 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->sql_command= SQLCOM_LOAD;
	  lex->lock_option= yyvsp[-3].lock_type;
	  lex->local_file=  yyvsp[-2].num;
	  lex->duplicates= DUP_ERROR;
	  lex->ignore= 0;
	  if (!(lex->exchange= new sql_exchange(yyvsp[0].lex_str.str,0)))
	    YYABORT;
	  lex->field_list.empty();
	}
    break;

  case 1206:
#line 4743 "sql_yacc.yy"
    {
	  if (!Select->add_table_to_list(YYTHD, yyvsp[-4].table, NULL, TL_OPTION_UPDATING))
	    YYABORT;
	}
    break;

  case 1207:
#line 4749 "sql_yacc.yy"
    {
	  Lex->sql_command = SQLCOM_LOAD_MASTER_TABLE;
	  if (!Select->add_table_to_list(YYTHD, yyvsp[-2].table, NULL, TL_OPTION_UPDATING))
	    YYABORT;

        }
    break;

  case 1208:
#line 4757 "sql_yacc.yy"
    {
	  Lex->sql_command = SQLCOM_LOAD_MASTER_DATA;
        }
    break;

  case 1209:
#line 4762 "sql_yacc.yy"
    { yyval.num=0;}
    break;

  case 1210:
#line 4763 "sql_yacc.yy"
    { yyval.num=1;}
    break;

  case 1211:
#line 4766 "sql_yacc.yy"
    { yyval.lock_type= YYTHD->update_lock_default; }
    break;

  case 1212:
#line 4767 "sql_yacc.yy"
    { yyval.lock_type= TL_WRITE_CONCURRENT_INSERT ; }
    break;

  case 1213:
#line 4768 "sql_yacc.yy"
    { yyval.lock_type= TL_WRITE_LOW_PRIORITY; }
    break;

  case 1214:
#line 4772 "sql_yacc.yy"
    { Lex->duplicates=DUP_ERROR; }
    break;

  case 1215:
#line 4773 "sql_yacc.yy"
    { Lex->duplicates=DUP_REPLACE; }
    break;

  case 1216:
#line 4774 "sql_yacc.yy"
    { Lex->ignore= 1; }
    break;

  case 1221:
#line 4786 "sql_yacc.yy"
    {
            DBUG_ASSERT(Lex->exchange);
            Lex->exchange->field_term= yyvsp[0].string;
          }
    break;

  case 1222:
#line 4791 "sql_yacc.yy"
    {
            LEX *lex= Lex;
            DBUG_ASSERT(lex->exchange);
            lex->exchange->enclosed= yyvsp[0].string;
            lex->exchange->opt_enclosed= 1;
	  }
    break;

  case 1223:
#line 4798 "sql_yacc.yy"
    {
            DBUG_ASSERT(Lex->exchange);
            Lex->exchange->enclosed= yyvsp[0].string;
          }
    break;

  case 1224:
#line 4803 "sql_yacc.yy"
    {
            DBUG_ASSERT(Lex->exchange);
            Lex->exchange->escaped= yyvsp[0].string;
          }
    break;

  case 1229:
#line 4818 "sql_yacc.yy"
    {
            DBUG_ASSERT(Lex->exchange);
            Lex->exchange->line_term= yyvsp[0].string;
          }
    break;

  case 1230:
#line 4823 "sql_yacc.yy"
    {
            DBUG_ASSERT(Lex->exchange);
            Lex->exchange->line_start= yyvsp[0].string;
          }
    break;

  case 1232:
#line 4831 "sql_yacc.yy"
    {
            DBUG_ASSERT(Lex->exchange);
            Lex->exchange->skip_lines= atol(yyvsp[-1].lex_str.str);
          }
    break;

  case 1233:
#line 4840 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  yyval.item = new Item_string(yyvsp[0].lex_str.str,yyvsp[0].lex_str.length,thd->variables.collation_connection);
	}
    break;

  case 1234:
#line 4845 "sql_yacc.yy"
    { yyval.item=  new Item_string(yyvsp[0].lex_str.str,yyvsp[0].lex_str.length,national_charset_info); }
    break;

  case 1235:
#line 4847 "sql_yacc.yy"
    { yyval.item = new Item_string(yyvsp[0].lex_str.str,yyvsp[0].lex_str.length,Lex->charset); }
    break;

  case 1236:
#line 4849 "sql_yacc.yy"
    { ((Item_string*) yyvsp[-1].item)->append(yyvsp[0].lex_str.str,yyvsp[0].lex_str.length); }
    break;

  case 1237:
#line 4854 "sql_yacc.yy"
    { yyval.string=  new (YYTHD->mem_root) String(yyvsp[0].lex_str.str,yyvsp[0].lex_str.length,YYTHD->variables.collation_connection); }
    break;

  case 1238:
#line 4856 "sql_yacc.yy"
    {
	    Item *tmp = new Item_varbinary(yyvsp[0].lex_str.str,yyvsp[0].lex_str.length);
	    /*
	      it is OK only emulate fix_fieds, because we need only
              value of constant
	    */
	    yyval.string= tmp ?
	      tmp->quick_fix_field(), tmp->val_str((String*) 0) :
	      (String*) 0;
	  }
    break;

  case 1239:
#line 4870 "sql_yacc.yy"
    {
          THD *thd=YYTHD;
	  LEX *lex= thd->lex;
          if (thd->command == COM_PREPARE)
          {
            Item_param *item= new Item_param((uint) (lex->tok_start -
                                                     (uchar *) thd->query));
            if (!(yyval.item= item) || lex->param_list.push_back(item))
            {
	      send_error(thd, ER_OUT_OF_RESOURCES);
	      YYABORT;
            }
          }
          else
          {
            yyerror(ER(ER_SYNTAX_ERROR));
            YYABORT;
          }
        }
    break;

  case 1240:
#line 4892 "sql_yacc.yy"
    { yyval.item = yyvsp[0].item; }
    break;

  case 1241:
#line 4893 "sql_yacc.yy"
    { yyval.item = yyvsp[0].item_num; }
    break;

  case 1242:
#line 4895 "sql_yacc.yy"
    {
	    yyvsp[0].item_num->max_length++;
	    yyval.item= yyvsp[0].item_num->neg();
	  }
    break;

  case 1243:
#line 4903 "sql_yacc.yy"
    { yyval.item =	yyvsp[0].item; }
    break;

  case 1244:
#line 4904 "sql_yacc.yy"
    { yyval.item = yyvsp[0].item_num; }
    break;

  case 1245:
#line 4905 "sql_yacc.yy"
    { yyval.item =	new Item_null();
			  Lex->next_state=MY_LEX_OPERATOR_OR_IDENT;}
    break;

  case 1246:
#line 4907 "sql_yacc.yy"
    { yyval.item= new Item_int((char*) "FALSE",0,1); }
    break;

  case 1247:
#line 4908 "sql_yacc.yy"
    { yyval.item= new Item_int((char*) "TRUE",1,1); }
    break;

  case 1248:
#line 4909 "sql_yacc.yy"
    { yyval.item =	new Item_varbinary(yyvsp[0].lex_str.str,yyvsp[0].lex_str.length);}
    break;

  case 1249:
#line 4911 "sql_yacc.yy"
    {
	    Item *tmp= new Item_varbinary(yyvsp[0].lex_str.str,yyvsp[0].lex_str.length);
	    /*
	      it is OK only emulate fix_fieds, because we need only
              value of constant
	    */
	    String *str= tmp ?
	      tmp->quick_fix_field(), tmp->val_str((String*) 0) :
	      (String*) 0;
	    yyval.item= new Item_string(str ? str->ptr() : "",
				str ? str->length() : 0,
				Lex->charset);
	  }
    break;

  case 1250:
#line 4924 "sql_yacc.yy"
    { yyval.item = yyvsp[0].item; }
    break;

  case 1251:
#line 4925 "sql_yacc.yy"
    { yyval.item = yyvsp[0].item; }
    break;

  case 1252:
#line 4926 "sql_yacc.yy"
    { yyval.item = yyvsp[0].item; }
    break;

  case 1253:
#line 4929 "sql_yacc.yy"
    { int error; yyval.item_num = new Item_int(yyvsp[0].lex_str.str, (longlong) my_strtoll10(yyvsp[0].lex_str.str, NULL, &error), yyvsp[0].lex_str.length); }
    break;

  case 1254:
#line 4930 "sql_yacc.yy"
    { int error; yyval.item_num = new Item_int(yyvsp[0].lex_str.str, (longlong) my_strtoll10(yyvsp[0].lex_str.str, NULL, &error), yyvsp[0].lex_str.length); }
    break;

  case 1255:
#line 4931 "sql_yacc.yy"
    { yyval.item_num =	new Item_uint(yyvsp[0].lex_str.str, yyvsp[0].lex_str.length); }
    break;

  case 1256:
#line 4932 "sql_yacc.yy"
    { yyval.item_num =	new Item_real(yyvsp[0].lex_str.str, yyvsp[0].lex_str.length); }
    break;

  case 1257:
#line 4933 "sql_yacc.yy"
    { yyval.item_num =	new Item_float(yyvsp[0].lex_str.str, yyvsp[0].lex_str.length); }
    break;

  case 1258:
#line 4941 "sql_yacc.yy"
    { yyval.item=yyvsp[0].item; }
    break;

  case 1259:
#line 4942 "sql_yacc.yy"
    { yyval.item=yyvsp[0].item; }
    break;

  case 1260:
#line 4946 "sql_yacc.yy"
    {
	  yyval.item = new Item_field(NullS,yyvsp[-2].lex_str.str,"*");
	  Lex->current_select->with_wild++;
	}
    break;

  case 1261:
#line 4951 "sql_yacc.yy"
    {
	  yyval.item = new Item_field((YYTHD->client_capabilities &
   			     CLIENT_NO_SCHEMA ? NullS : yyvsp[-4].lex_str.str),
			     yyvsp[-2].lex_str.str,"*");
	  Lex->current_select->with_wild++;
	}
    break;

  case 1262:
#line 4960 "sql_yacc.yy"
    { yyval.item=yyvsp[0].item; }
    break;

  case 1263:
#line 4964 "sql_yacc.yy"
    {
	  SELECT_LEX *sel=Select;
	  yyval.item= (sel->parsing_place != IN_HAVING ||
	       sel->get_in_sum_expr() > 0) ?
              (Item*) new Item_field(NullS,NullS,yyvsp[0].lex_str.str) :
	      (Item*) new Item_ref(NullS, NullS, yyvsp[0].lex_str.str);
	}
    break;

  case 1264:
#line 4972 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  LEX *lex= thd->lex;
	  SELECT_LEX *sel= lex->current_select;
	  if (sel->no_table_names_allowed)
	  {
	    my_printf_error(ER_TABLENAME_NOT_ALLOWED_HERE,
			    ER(ER_TABLENAME_NOT_ALLOWED_HERE),
			    MYF(0), yyvsp[-2].lex_str.str, thd->where);
	  }
	  yyval.item= (sel->parsing_place != IN_HAVING ||
	       sel->get_in_sum_expr() > 0) ?
	      (Item*) new Item_field(NullS,yyvsp[-2].lex_str.str,yyvsp[0].lex_str.str) :
	      (Item*) new Item_ref(NullS, yyvsp[-2].lex_str.str, yyvsp[0].lex_str.str);
	}
    break;

  case 1265:
#line 4988 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  LEX *lex= thd->lex;
	  SELECT_LEX *sel= lex->current_select;
	  if (sel->no_table_names_allowed)
	  {
	    my_printf_error(ER_TABLENAME_NOT_ALLOWED_HERE,
			    ER(ER_TABLENAME_NOT_ALLOWED_HERE),
			    MYF(0), yyvsp[-2].lex_str.str, thd->where);
	  }
	  yyval.item= (sel->parsing_place != IN_HAVING ||
	       sel->get_in_sum_expr() > 0) ?
	      (Item*) new Item_field(NullS,yyvsp[-2].lex_str.str,yyvsp[0].lex_str.str) :
              (Item*) new Item_ref(NullS, yyvsp[-2].lex_str.str, yyvsp[0].lex_str.str);
	}
    break;

  case 1266:
#line 5004 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  LEX *lex= thd->lex;
	  SELECT_LEX *sel= lex->current_select;
	  if (sel->no_table_names_allowed)
	  {
	    my_printf_error(ER_TABLENAME_NOT_ALLOWED_HERE,
			    ER(ER_TABLENAME_NOT_ALLOWED_HERE),
			    MYF(0), yyvsp[-2].lex_str.str, thd->where);
	  }
	  yyval.item= (sel->parsing_place != IN_HAVING ||
	       sel->get_in_sum_expr() > 0) ?
	      (Item*) new Item_field((YYTHD->client_capabilities &
				      CLIENT_NO_SCHEMA ? NullS : yyvsp[-4].lex_str.str),
				     yyvsp[-2].lex_str.str, yyvsp[0].lex_str.str) :
	      (Item*) new Item_ref((YYTHD->client_capabilities &
				    CLIENT_NO_SCHEMA ? NullS : yyvsp[-4].lex_str.str),
                                   yyvsp[-2].lex_str.str, yyvsp[0].lex_str.str);
	}
    break;

  case 1267:
#line 5026 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str;}
    break;

  case 1268:
#line 5027 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str;}
    break;

  case 1269:
#line 5028 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str;}
    break;

  case 1270:
#line 5031 "sql_yacc.yy"
    { yyval.table=new Table_ident(yyvsp[0].lex_str); }
    break;

  case 1271:
#line 5032 "sql_yacc.yy"
    { yyval.table=new Table_ident(YYTHD, yyvsp[-2].lex_str,yyvsp[0].lex_str,0);}
    break;

  case 1272:
#line 5033 "sql_yacc.yy"
    { yyval.table=new Table_ident(yyvsp[0].lex_str);}
    break;

  case 1273:
#line 5037 "sql_yacc.yy"
    { LEX_STRING db={(char*) any_db,3}; yyval.table=new Table_ident(YYTHD, db,yyvsp[0].lex_str,0); }
    break;

  case 1274:
#line 5041 "sql_yacc.yy"
    { yyval.lex_str= yyvsp[0].lex_str; }
    break;

  case 1275:
#line 5043 "sql_yacc.yy"
    {
	    THD *thd= YYTHD;
	    if (thd->charset_is_system_charset)
            {
              CHARSET_INFO *cs= system_charset_info;
              int dummy_error;
              uint wlen= cs->cset->well_formed_len(cs, yyvsp[0].lex_str.str,
                                                   yyvsp[0].lex_str.str+yyvsp[0].lex_str.length,
                                                   yyvsp[0].lex_str.length, &dummy_error);
              if (wlen < yyvsp[0].lex_str.length)
              {
                net_printf(YYTHD, ER_INVALID_CHARACTER_STRING, cs->csname,
                           yyvsp[0].lex_str.str + wlen);
                YYABORT;
              }
	      yyval.lex_str= yyvsp[0].lex_str;
            }
	    else
	      thd->convert_string(&yyval.lex_str, system_charset_info,
				  yyvsp[0].lex_str.str, yyvsp[0].lex_str.length, thd->charset());
	  }
    break;

  case 1276:
#line 5068 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  if (thd->charset_is_system_charset)
	    yyval.lex_str= yyvsp[0].lex_str;
	  else
	    thd->convert_string(&yyval.lex_str, system_charset_info,
				yyvsp[0].lex_str.str, yyvsp[0].lex_str.length, thd->charset());
	}
    break;

  case 1277:
#line 5080 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  if (thd->charset_is_collation_connection)
	    yyval.lex_str= yyvsp[0].lex_str;
	  else
	    thd->convert_string(&yyval.lex_str, thd->variables.collation_connection,
				yyvsp[0].lex_str.str, yyvsp[0].lex_str.length, thd->charset());
	}
    break;

  case 1278:
#line 5092 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str; }
    break;

  case 1279:
#line 5094 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  yyval.lex_str.str=    thd->strmake(yyvsp[0].symbol.str, yyvsp[0].symbol.length);
	  yyval.lex_str.length= yyvsp[0].symbol.length;
	}
    break;

  case 1280:
#line 5102 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str;}
    break;

  case 1281:
#line 5103 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str;}
    break;

  case 1282:
#line 5104 "sql_yacc.yy"
    { yyval.lex_str=yyvsp[0].lex_str;}
    break;

  case 1283:
#line 5108 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  if (!(yyval.lex_user=(LEX_USER*) thd->alloc(sizeof(st_lex_user))))
	    YYABORT;
	  yyval.lex_user->user = yyvsp[0].lex_str;
	  yyval.lex_user->host.str= (char *) "%";
	  yyval.lex_user->host.length= 1;
	}
    break;

  case 1284:
#line 5117 "sql_yacc.yy"
    {
	    THD *thd= YYTHD;
	    if (!(yyval.lex_user=(LEX_USER*) thd->alloc(sizeof(st_lex_user))))
	      YYABORT;
	    yyval.lex_user->user = yyvsp[-2].lex_str; yyval.lex_user->host=yyvsp[0].lex_str;
	  }
    break;

  case 1285:
#line 5124 "sql_yacc.yy"
    {
          THD *thd= YYTHD;
          if (!(yyval.lex_user=(LEX_USER*) thd->alloc(sizeof(st_lex_user))))
            YYABORT;
          yyval.lex_user->user.str= thd->priv_user;
          yyval.lex_user->user.length= strlen(thd->priv_user);
          if (*thd->priv_host != 0)
          {
            yyval.lex_user->host.str= thd->priv_host;
            yyval.lex_user->host.length= strlen(thd->priv_host);
          }
          else
          {
            yyval.lex_user->host.str= (char *) "%";
            yyval.lex_user->host.length= 1;
          }
	}
    break;

  case 1286:
#line 5145 "sql_yacc.yy"
    {}
    break;

  case 1287:
#line 5146 "sql_yacc.yy"
    {}
    break;

  case 1288:
#line 5147 "sql_yacc.yy"
    {}
    break;

  case 1289:
#line 5148 "sql_yacc.yy"
    {}
    break;

  case 1290:
#line 5149 "sql_yacc.yy"
    {}
    break;

  case 1291:
#line 5150 "sql_yacc.yy"
    {}
    break;

  case 1292:
#line 5151 "sql_yacc.yy"
    {}
    break;

  case 1293:
#line 5152 "sql_yacc.yy"
    {}
    break;

  case 1294:
#line 5153 "sql_yacc.yy"
    {}
    break;

  case 1295:
#line 5154 "sql_yacc.yy"
    {}
    break;

  case 1296:
#line 5155 "sql_yacc.yy"
    {}
    break;

  case 1297:
#line 5156 "sql_yacc.yy"
    {}
    break;

  case 1298:
#line 5157 "sql_yacc.yy"
    {}
    break;

  case 1299:
#line 5158 "sql_yacc.yy"
    {}
    break;

  case 1300:
#line 5159 "sql_yacc.yy"
    {}
    break;

  case 1301:
#line 5160 "sql_yacc.yy"
    {}
    break;

  case 1302:
#line 5161 "sql_yacc.yy"
    {}
    break;

  case 1303:
#line 5162 "sql_yacc.yy"
    {}
    break;

  case 1304:
#line 5163 "sql_yacc.yy"
    {}
    break;

  case 1305:
#line 5164 "sql_yacc.yy"
    {}
    break;

  case 1306:
#line 5165 "sql_yacc.yy"
    {}
    break;

  case 1307:
#line 5166 "sql_yacc.yy"
    {}
    break;

  case 1308:
#line 5167 "sql_yacc.yy"
    {}
    break;

  case 1309:
#line 5168 "sql_yacc.yy"
    {}
    break;

  case 1310:
#line 5169 "sql_yacc.yy"
    {}
    break;

  case 1311:
#line 5170 "sql_yacc.yy"
    {}
    break;

  case 1312:
#line 5171 "sql_yacc.yy"
    {}
    break;

  case 1313:
#line 5172 "sql_yacc.yy"
    {}
    break;

  case 1314:
#line 5173 "sql_yacc.yy"
    {}
    break;

  case 1315:
#line 5174 "sql_yacc.yy"
    {}
    break;

  case 1316:
#line 5175 "sql_yacc.yy"
    {}
    break;

  case 1317:
#line 5176 "sql_yacc.yy"
    {}
    break;

  case 1318:
#line 5177 "sql_yacc.yy"
    {}
    break;

  case 1319:
#line 5178 "sql_yacc.yy"
    {}
    break;

  case 1320:
#line 5179 "sql_yacc.yy"
    {}
    break;

  case 1321:
#line 5180 "sql_yacc.yy"
    {}
    break;

  case 1322:
#line 5181 "sql_yacc.yy"
    {}
    break;

  case 1323:
#line 5182 "sql_yacc.yy"
    {}
    break;

  case 1324:
#line 5183 "sql_yacc.yy"
    {}
    break;

  case 1325:
#line 5184 "sql_yacc.yy"
    {}
    break;

  case 1326:
#line 5185 "sql_yacc.yy"
    {}
    break;

  case 1327:
#line 5186 "sql_yacc.yy"
    {}
    break;

  case 1328:
#line 5187 "sql_yacc.yy"
    {}
    break;

  case 1329:
#line 5188 "sql_yacc.yy"
    {}
    break;

  case 1330:
#line 5189 "sql_yacc.yy"
    {}
    break;

  case 1331:
#line 5190 "sql_yacc.yy"
    {}
    break;

  case 1332:
#line 5191 "sql_yacc.yy"
    {}
    break;

  case 1333:
#line 5192 "sql_yacc.yy"
    {}
    break;

  case 1334:
#line 5193 "sql_yacc.yy"
    {}
    break;

  case 1335:
#line 5194 "sql_yacc.yy"
    {}
    break;

  case 1336:
#line 5195 "sql_yacc.yy"
    {}
    break;

  case 1337:
#line 5196 "sql_yacc.yy"
    {}
    break;

  case 1338:
#line 5197 "sql_yacc.yy"
    {}
    break;

  case 1339:
#line 5198 "sql_yacc.yy"
    {}
    break;

  case 1340:
#line 5199 "sql_yacc.yy"
    {}
    break;

  case 1341:
#line 5200 "sql_yacc.yy"
    {}
    break;

  case 1342:
#line 5201 "sql_yacc.yy"
    {}
    break;

  case 1343:
#line 5202 "sql_yacc.yy"
    {}
    break;

  case 1344:
#line 5203 "sql_yacc.yy"
    {}
    break;

  case 1345:
#line 5204 "sql_yacc.yy"
    {}
    break;

  case 1346:
#line 5205 "sql_yacc.yy"
    {}
    break;

  case 1347:
#line 5206 "sql_yacc.yy"
    {}
    break;

  case 1348:
#line 5207 "sql_yacc.yy"
    {}
    break;

  case 1349:
#line 5208 "sql_yacc.yy"
    {}
    break;

  case 1350:
#line 5209 "sql_yacc.yy"
    {}
    break;

  case 1351:
#line 5210 "sql_yacc.yy"
    {}
    break;

  case 1352:
#line 5211 "sql_yacc.yy"
    {}
    break;

  case 1353:
#line 5212 "sql_yacc.yy"
    {}
    break;

  case 1354:
#line 5213 "sql_yacc.yy"
    {}
    break;

  case 1355:
#line 5214 "sql_yacc.yy"
    {}
    break;

  case 1356:
#line 5215 "sql_yacc.yy"
    {}
    break;

  case 1357:
#line 5216 "sql_yacc.yy"
    {}
    break;

  case 1358:
#line 5217 "sql_yacc.yy"
    {}
    break;

  case 1359:
#line 5218 "sql_yacc.yy"
    {}
    break;

  case 1360:
#line 5219 "sql_yacc.yy"
    {}
    break;

  case 1361:
#line 5220 "sql_yacc.yy"
    {}
    break;

  case 1362:
#line 5221 "sql_yacc.yy"
    {}
    break;

  case 1363:
#line 5222 "sql_yacc.yy"
    {}
    break;

  case 1364:
#line 5223 "sql_yacc.yy"
    {}
    break;

  case 1365:
#line 5224 "sql_yacc.yy"
    {}
    break;

  case 1366:
#line 5225 "sql_yacc.yy"
    {}
    break;

  case 1367:
#line 5226 "sql_yacc.yy"
    {}
    break;

  case 1368:
#line 5227 "sql_yacc.yy"
    {}
    break;

  case 1369:
#line 5228 "sql_yacc.yy"
    {}
    break;

  case 1370:
#line 5229 "sql_yacc.yy"
    {}
    break;

  case 1371:
#line 5230 "sql_yacc.yy"
    {}
    break;

  case 1372:
#line 5231 "sql_yacc.yy"
    {}
    break;

  case 1373:
#line 5232 "sql_yacc.yy"
    {}
    break;

  case 1374:
#line 5233 "sql_yacc.yy"
    {}
    break;

  case 1375:
#line 5234 "sql_yacc.yy"
    {}
    break;

  case 1376:
#line 5235 "sql_yacc.yy"
    {}
    break;

  case 1377:
#line 5236 "sql_yacc.yy"
    {}
    break;

  case 1378:
#line 5237 "sql_yacc.yy"
    {}
    break;

  case 1379:
#line 5238 "sql_yacc.yy"
    {}
    break;

  case 1380:
#line 5239 "sql_yacc.yy"
    {}
    break;

  case 1381:
#line 5240 "sql_yacc.yy"
    {}
    break;

  case 1382:
#line 5241 "sql_yacc.yy"
    {}
    break;

  case 1383:
#line 5242 "sql_yacc.yy"
    {}
    break;

  case 1384:
#line 5243 "sql_yacc.yy"
    {}
    break;

  case 1385:
#line 5244 "sql_yacc.yy"
    {}
    break;

  case 1386:
#line 5245 "sql_yacc.yy"
    {}
    break;

  case 1387:
#line 5246 "sql_yacc.yy"
    {}
    break;

  case 1388:
#line 5247 "sql_yacc.yy"
    {}
    break;

  case 1389:
#line 5248 "sql_yacc.yy"
    {}
    break;

  case 1390:
#line 5249 "sql_yacc.yy"
    {}
    break;

  case 1391:
#line 5250 "sql_yacc.yy"
    {}
    break;

  case 1392:
#line 5251 "sql_yacc.yy"
    {}
    break;

  case 1393:
#line 5252 "sql_yacc.yy"
    {}
    break;

  case 1394:
#line 5253 "sql_yacc.yy"
    {}
    break;

  case 1395:
#line 5254 "sql_yacc.yy"
    {}
    break;

  case 1396:
#line 5255 "sql_yacc.yy"
    {}
    break;

  case 1397:
#line 5256 "sql_yacc.yy"
    {}
    break;

  case 1398:
#line 5257 "sql_yacc.yy"
    {}
    break;

  case 1399:
#line 5258 "sql_yacc.yy"
    {}
    break;

  case 1400:
#line 5259 "sql_yacc.yy"
    {}
    break;

  case 1401:
#line 5260 "sql_yacc.yy"
    {}
    break;

  case 1402:
#line 5261 "sql_yacc.yy"
    {}
    break;

  case 1403:
#line 5262 "sql_yacc.yy"
    {}
    break;

  case 1404:
#line 5263 "sql_yacc.yy"
    {}
    break;

  case 1405:
#line 5264 "sql_yacc.yy"
    {}
    break;

  case 1406:
#line 5265 "sql_yacc.yy"
    {}
    break;

  case 1407:
#line 5266 "sql_yacc.yy"
    {}
    break;

  case 1408:
#line 5267 "sql_yacc.yy"
    {}
    break;

  case 1409:
#line 5268 "sql_yacc.yy"
    {}
    break;

  case 1410:
#line 5269 "sql_yacc.yy"
    {}
    break;

  case 1411:
#line 5270 "sql_yacc.yy"
    {}
    break;

  case 1412:
#line 5271 "sql_yacc.yy"
    {}
    break;

  case 1413:
#line 5272 "sql_yacc.yy"
    {}
    break;

  case 1414:
#line 5273 "sql_yacc.yy"
    {}
    break;

  case 1415:
#line 5274 "sql_yacc.yy"
    {}
    break;

  case 1416:
#line 5275 "sql_yacc.yy"
    {}
    break;

  case 1417:
#line 5276 "sql_yacc.yy"
    {}
    break;

  case 1418:
#line 5277 "sql_yacc.yy"
    {}
    break;

  case 1419:
#line 5278 "sql_yacc.yy"
    {}
    break;

  case 1420:
#line 5279 "sql_yacc.yy"
    {}
    break;

  case 1421:
#line 5280 "sql_yacc.yy"
    {}
    break;

  case 1422:
#line 5281 "sql_yacc.yy"
    {}
    break;

  case 1423:
#line 5282 "sql_yacc.yy"
    {}
    break;

  case 1424:
#line 5283 "sql_yacc.yy"
    {}
    break;

  case 1425:
#line 5284 "sql_yacc.yy"
    {}
    break;

  case 1426:
#line 5285 "sql_yacc.yy"
    {}
    break;

  case 1427:
#line 5286 "sql_yacc.yy"
    {}
    break;

  case 1428:
#line 5287 "sql_yacc.yy"
    {}
    break;

  case 1429:
#line 5288 "sql_yacc.yy"
    {}
    break;

  case 1430:
#line 5289 "sql_yacc.yy"
    {}
    break;

  case 1431:
#line 5290 "sql_yacc.yy"
    {}
    break;

  case 1432:
#line 5291 "sql_yacc.yy"
    {}
    break;

  case 1433:
#line 5292 "sql_yacc.yy"
    {}
    break;

  case 1434:
#line 5293 "sql_yacc.yy"
    {}
    break;

  case 1435:
#line 5294 "sql_yacc.yy"
    {}
    break;

  case 1436:
#line 5295 "sql_yacc.yy"
    {}
    break;

  case 1437:
#line 5296 "sql_yacc.yy"
    {}
    break;

  case 1438:
#line 5297 "sql_yacc.yy"
    {}
    break;

  case 1439:
#line 5298 "sql_yacc.yy"
    {}
    break;

  case 1440:
#line 5299 "sql_yacc.yy"
    {}
    break;

  case 1441:
#line 5300 "sql_yacc.yy"
    {}
    break;

  case 1442:
#line 5301 "sql_yacc.yy"
    {}
    break;

  case 1443:
#line 5302 "sql_yacc.yy"
    {}
    break;

  case 1444:
#line 5303 "sql_yacc.yy"
    {}
    break;

  case 1445:
#line 5304 "sql_yacc.yy"
    {}
    break;

  case 1446:
#line 5305 "sql_yacc.yy"
    {}
    break;

  case 1447:
#line 5306 "sql_yacc.yy"
    {}
    break;

  case 1448:
#line 5307 "sql_yacc.yy"
    {}
    break;

  case 1449:
#line 5308 "sql_yacc.yy"
    {}
    break;

  case 1450:
#line 5309 "sql_yacc.yy"
    {}
    break;

  case 1451:
#line 5310 "sql_yacc.yy"
    {}
    break;

  case 1452:
#line 5311 "sql_yacc.yy"
    {}
    break;

  case 1453:
#line 5312 "sql_yacc.yy"
    {}
    break;

  case 1454:
#line 5313 "sql_yacc.yy"
    {}
    break;

  case 1455:
#line 5314 "sql_yacc.yy"
    {}
    break;

  case 1456:
#line 5315 "sql_yacc.yy"
    {}
    break;

  case 1457:
#line 5316 "sql_yacc.yy"
    {}
    break;

  case 1458:
#line 5317 "sql_yacc.yy"
    {}
    break;

  case 1459:
#line 5318 "sql_yacc.yy"
    {}
    break;

  case 1460:
#line 5319 "sql_yacc.yy"
    {}
    break;

  case 1461:
#line 5320 "sql_yacc.yy"
    {}
    break;

  case 1462:
#line 5321 "sql_yacc.yy"
    {}
    break;

  case 1463:
#line 5322 "sql_yacc.yy"
    {}
    break;

  case 1464:
#line 5323 "sql_yacc.yy"
    {}
    break;

  case 1465:
#line 5324 "sql_yacc.yy"
    {}
    break;

  case 1466:
#line 5325 "sql_yacc.yy"
    {}
    break;

  case 1467:
#line 5326 "sql_yacc.yy"
    {}
    break;

  case 1468:
#line 5327 "sql_yacc.yy"
    {}
    break;

  case 1469:
#line 5328 "sql_yacc.yy"
    {}
    break;

  case 1470:
#line 5329 "sql_yacc.yy"
    {}
    break;

  case 1471:
#line 5330 "sql_yacc.yy"
    {}
    break;

  case 1472:
#line 5331 "sql_yacc.yy"
    {}
    break;

  case 1473:
#line 5332 "sql_yacc.yy"
    {}
    break;

  case 1474:
#line 5333 "sql_yacc.yy"
    {}
    break;

  case 1475:
#line 5334 "sql_yacc.yy"
    {}
    break;

  case 1476:
#line 5335 "sql_yacc.yy"
    {}
    break;

  case 1477:
#line 5336 "sql_yacc.yy"
    {}
    break;

  case 1478:
#line 5337 "sql_yacc.yy"
    {}
    break;

  case 1479:
#line 5338 "sql_yacc.yy"
    {}
    break;

  case 1480:
#line 5339 "sql_yacc.yy"
    {}
    break;

  case 1481:
#line 5340 "sql_yacc.yy"
    {}
    break;

  case 1482:
#line 5341 "sql_yacc.yy"
    {}
    break;

  case 1483:
#line 5342 "sql_yacc.yy"
    {}
    break;

  case 1484:
#line 5343 "sql_yacc.yy"
    {}
    break;

  case 1485:
#line 5344 "sql_yacc.yy"
    {}
    break;

  case 1486:
#line 5345 "sql_yacc.yy"
    {}
    break;

  case 1487:
#line 5346 "sql_yacc.yy"
    {}
    break;

  case 1488:
#line 5347 "sql_yacc.yy"
    {}
    break;

  case 1489:
#line 5348 "sql_yacc.yy"
    {}
    break;

  case 1490:
#line 5349 "sql_yacc.yy"
    {}
    break;

  case 1491:
#line 5350 "sql_yacc.yy"
    {}
    break;

  case 1492:
#line 5351 "sql_yacc.yy"
    {}
    break;

  case 1493:
#line 5352 "sql_yacc.yy"
    {}
    break;

  case 1494:
#line 5353 "sql_yacc.yy"
    {}
    break;

  case 1495:
#line 5360 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->sql_command= SQLCOM_SET_OPTION;
          mysql_init_select(lex);
	  lex->option_type=OPT_SESSION;
	  lex->var_list.empty();
          lex->one_shot_set= 0;
	}
    break;

  case 1496:
#line 5369 "sql_yacc.yy"
    {}
    break;

  case 1497:
#line 5373 "sql_yacc.yy"
    {}
    break;

  case 1498:
#line 5374 "sql_yacc.yy"
    {}
    break;

  case 1501:
#line 5381 "sql_yacc.yy"
    {}
    break;

  case 1502:
#line 5382 "sql_yacc.yy"
    {}
    break;

  case 1503:
#line 5386 "sql_yacc.yy"
    {}
    break;

  case 1504:
#line 5387 "sql_yacc.yy"
    { Lex->option_type= OPT_GLOBAL; }
    break;

  case 1505:
#line 5388 "sql_yacc.yy"
    { Lex->option_type= OPT_SESSION; }
    break;

  case 1506:
#line 5389 "sql_yacc.yy"
    { Lex->option_type= OPT_SESSION; }
    break;

  case 1507:
#line 5393 "sql_yacc.yy"
    {}
    break;

  case 1508:
#line 5394 "sql_yacc.yy"
    { Lex->option_type= OPT_SESSION; Lex->one_shot_set= 1; }
    break;

  case 1509:
#line 5398 "sql_yacc.yy"
    { yyval.num=OPT_SESSION; }
    break;

  case 1510:
#line 5399 "sql_yacc.yy"
    { yyval.num=OPT_GLOBAL; }
    break;

  case 1511:
#line 5400 "sql_yacc.yy"
    { yyval.num=OPT_SESSION; }
    break;

  case 1512:
#line 5401 "sql_yacc.yy"
    { yyval.num=OPT_SESSION; }
    break;

  case 1513:
#line 5405 "sql_yacc.yy"
    { yyval.num=OPT_DEFAULT; }
    break;

  case 1514:
#line 5406 "sql_yacc.yy"
    { yyval.num=OPT_GLOBAL; }
    break;

  case 1515:
#line 5407 "sql_yacc.yy"
    { yyval.num=OPT_SESSION; }
    break;

  case 1516:
#line 5408 "sql_yacc.yy"
    { yyval.num=OPT_SESSION; }
    break;

  case 1517:
#line 5413 "sql_yacc.yy"
    {
          LEX *lex=Lex;
          lex->var_list.push_back(new set_var(lex->option_type, yyvsp[-2].variable.var,
                                  &yyvsp[-2].variable.base_name, yyvsp[0].item));
        }
    break;

  case 1518:
#line 5419 "sql_yacc.yy"
    {
          LEX *lex=Lex;
          LEX_STRING tmp;
          tmp.str=0;
          tmp.length=0;
          lex->var_list.push_back(new set_var(lex->option_type,
                                              find_sys_var("tx_isolation"),
                                              &tmp,
                                              new Item_int((int32) yyvsp[0].tx_isolation)));
        }
    break;

  case 1519:
#line 5433 "sql_yacc.yy"
    {
	  Lex->var_list.push_back(new set_var_user(new Item_func_set_user_var(yyvsp[-2].lex_str,yyvsp[0].item)));
	}
    break;

  case 1520:
#line 5437 "sql_yacc.yy"
    {
          LEX *lex=Lex;
          lex->var_list.push_back(new set_var((enum_var_type) yyvsp[-3].num, yyvsp[-2].variable.var,
                                  &yyvsp[-2].variable.base_name, yyvsp[0].item));
        }
    break;

  case 1521:
#line 5443 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  LEX *lex= Lex;
	  yyvsp[0].charset= yyvsp[0].charset ? yyvsp[0].charset: global_system_variables.character_set_client;
	  lex->var_list.push_back(new set_var_collation_client(yyvsp[0].charset,thd->variables.collation_database,yyvsp[0].charset));
	}
    break;

  case 1522:
#line 5450 "sql_yacc.yy"
    {
	  THD *thd= YYTHD;
	  LEX *lex= Lex;
	  yyvsp[-1].charset= yyvsp[-1].charset ? yyvsp[-1].charset : global_system_variables.character_set_client;
	  yyvsp[0].charset= yyvsp[0].charset ? yyvsp[0].charset : yyvsp[-1].charset;
	  if (!my_charset_same(yyvsp[-1].charset,yyvsp[0].charset))
	  {
	    net_printf(thd,ER_COLLATION_CHARSET_MISMATCH,yyvsp[0].charset->name,yyvsp[-1].charset->csname);
	    YYABORT;
	  }
	  lex->var_list.push_back(new set_var_collation_client(yyvsp[0].charset,yyvsp[0].charset,yyvsp[0].charset));
	}
    break;

  case 1523:
#line 5463 "sql_yacc.yy"
    {
	    THD *thd=YYTHD;
	    LEX_USER *user;
	    if (!(user=(LEX_USER*) thd->alloc(sizeof(LEX_USER))))
	      YYABORT;
	    user->host.str=0;
	    user->user.str=thd->priv_user;
	    thd->lex->var_list.push_back(new set_var_password(user, yyvsp[0].simple_string));
	  }
    break;

  case 1524:
#line 5473 "sql_yacc.yy"
    {
	    Lex->var_list.push_back(new set_var_password(yyvsp[-2].lex_user,yyvsp[0].simple_string));
	  }
    break;

  case 1525:
#line 5480 "sql_yacc.yy"
    {
	  sys_var *tmp=find_sys_var(yyvsp[0].lex_str.str, yyvsp[0].lex_str.length);
	  if (!tmp)
	    YYABORT;
	  yyval.variable.var= tmp;
	  yyval.variable.base_name.str=0;
	  yyval.variable.base_name.length=0;
          /*
            If this is time_zone variable we should open time zone
            describing tables 
          */
          if (tmp == &sys_time_zone)
	    Lex->time_zone_tables_used= &fake_time_zone_tables_list;
	}
    break;

  case 1526:
#line 5495 "sql_yacc.yy"
    {
            if (check_reserved_words(&yyvsp[-2].lex_str))
            {
	      yyerror(ER(ER_SYNTAX_ERROR));
              YYABORT;
            }
	    sys_var *tmp=find_sys_var(yyvsp[0].lex_str.str, yyvsp[0].lex_str.length);
	    if (!tmp)
	      YYABORT;
	    if (!tmp->is_struct())
	      net_printf(YYTHD, ER_VARIABLE_IS_NOT_STRUCT, yyvsp[0].lex_str.str);
	    yyval.variable.var= tmp;
	    yyval.variable.base_name= yyvsp[-2].lex_str;
	  }
    break;

  case 1527:
#line 5510 "sql_yacc.yy"
    {
	    sys_var *tmp=find_sys_var(yyvsp[0].lex_str.str, yyvsp[0].lex_str.length);
	    if (!tmp)
	      YYABORT;
	    if (!tmp->is_struct())
	      net_printf(YYTHD, ER_VARIABLE_IS_NOT_STRUCT, yyvsp[0].lex_str.str);
	    yyval.variable.var= tmp;
	    yyval.variable.base_name.str=    (char*) "default";
	    yyval.variable.base_name.length= 7;
	  }
    break;

  case 1528:
#line 5523 "sql_yacc.yy"
    { yyval.tx_isolation= ISO_READ_UNCOMMITTED; }
    break;

  case 1529:
#line 5524 "sql_yacc.yy"
    { yyval.tx_isolation= ISO_READ_COMMITTED; }
    break;

  case 1530:
#line 5525 "sql_yacc.yy"
    { yyval.tx_isolation= ISO_REPEATABLE_READ; }
    break;

  case 1531:
#line 5526 "sql_yacc.yy"
    { yyval.tx_isolation= ISO_SERIALIZABLE; }
    break;

  case 1532:
#line 5530 "sql_yacc.yy"
    { yyval.simple_string=yyvsp[0].lex_str.str;}
    break;

  case 1533:
#line 5532 "sql_yacc.yy"
    {
	    yyval.simple_string= yyvsp[-1].lex_str.length ? YYTHD->variables.old_passwords ?
	        Item_func_old_password::alloc(YYTHD, yyvsp[-1].lex_str.str) :
	        Item_func_password::alloc(YYTHD, yyvsp[-1].lex_str.str) :
	      yyvsp[-1].lex_str.str;
	  }
    break;

  case 1534:
#line 5539 "sql_yacc.yy"
    {
	    yyval.simple_string= yyvsp[-1].lex_str.length ? Item_func_old_password::alloc(YYTHD, yyvsp[-1].lex_str.str) :
	      yyvsp[-1].lex_str.str;
	  }
    break;

  case 1535:
#line 5547 "sql_yacc.yy"
    { yyval.item=yyvsp[0].item; }
    break;

  case 1536:
#line 5548 "sql_yacc.yy"
    { yyval.item=0; }
    break;

  case 1537:
#line 5549 "sql_yacc.yy"
    { yyval.item=new Item_string("ON",  2, system_charset_info); }
    break;

  case 1538:
#line 5550 "sql_yacc.yy"
    { yyval.item=new Item_string("ALL", 3, system_charset_info); }
    break;

  case 1539:
#line 5551 "sql_yacc.yy"
    { yyval.item=new Item_string("binary", 6, system_charset_info); }
    break;

  case 1540:
#line 5559 "sql_yacc.yy"
    {
	  Lex->sql_command=SQLCOM_LOCK_TABLES;
	}
    break;

  case 1541:
#line 5563 "sql_yacc.yy"
    {}
    break;

  case 1546:
#line 5576 "sql_yacc.yy"
    {
	  if (!Select->add_table_to_list(YYTHD, yyvsp[-2].table, yyvsp[-1].lex_str_ptr, 0, (thr_lock_type) yyvsp[0].num))
	   YYABORT;
	}
    break;

  case 1547:
#line 5583 "sql_yacc.yy"
    { yyval.num=TL_READ_NO_INSERT; }
    break;

  case 1548:
#line 5584 "sql_yacc.yy"
    { yyval.num=YYTHD->update_lock_default; }
    break;

  case 1549:
#line 5585 "sql_yacc.yy"
    { yyval.num=TL_WRITE_LOW_PRIORITY; }
    break;

  case 1550:
#line 5586 "sql_yacc.yy"
    { yyval.num= TL_READ; }
    break;

  case 1551:
#line 5590 "sql_yacc.yy"
    { Lex->sql_command=SQLCOM_UNLOCK_TABLES; }
    break;

  case 1552:
#line 5600 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  lex->sql_command = SQLCOM_HA_OPEN;
	  if (!lex->current_select->add_table_to_list(lex->thd, yyvsp[-2].table, yyvsp[0].lex_str_ptr, 0))
	    YYABORT;
	}
    break;

  case 1553:
#line 5607 "sql_yacc.yy"
    {
	  LEX *lex= Lex;
	  lex->sql_command = SQLCOM_HA_CLOSE;
	  if (!lex->current_select->add_table_to_list(lex->thd, yyvsp[-1].table, 0, 0))
	    YYABORT;
	}
    break;

  case 1554:
#line 5614 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->sql_command = SQLCOM_HA_READ;
	  lex->ha_rkey_mode= HA_READ_KEY_EXACT;	/* Avoid purify warnings */
	  lex->current_select->select_limit= 1;
	  lex->current_select->offset_limit= 0L;
	  if (!lex->current_select->add_table_to_list(lex->thd, yyvsp[-1].table, 0, 0))
	    YYABORT;
        }
    break;

  case 1555:
#line 5623 "sql_yacc.yy"
    {}
    break;

  case 1556:
#line 5627 "sql_yacc.yy"
    { Lex->backup_dir= 0; }
    break;

  case 1557:
#line 5628 "sql_yacc.yy"
    { Lex->backup_dir= yyvsp[-1].lex_str.str; }
    break;

  case 1558:
#line 5632 "sql_yacc.yy"
    { Lex->ha_read_mode = RFIRST; }
    break;

  case 1559:
#line 5633 "sql_yacc.yy"
    { Lex->ha_read_mode = RNEXT;  }
    break;

  case 1560:
#line 5637 "sql_yacc.yy"
    { Lex->ha_read_mode = RFIRST; }
    break;

  case 1561:
#line 5638 "sql_yacc.yy"
    { Lex->ha_read_mode = RNEXT;  }
    break;

  case 1562:
#line 5639 "sql_yacc.yy"
    { Lex->ha_read_mode = RPREV;  }
    break;

  case 1563:
#line 5640 "sql_yacc.yy"
    { Lex->ha_read_mode = RLAST;  }
    break;

  case 1564:
#line 5642 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->ha_read_mode = RKEY;
	  lex->ha_rkey_mode=yyvsp[0].ha_rkey_mode;
	  if (!(lex->insert_list = new List_item))
	    YYABORT;
	}
    break;

  case 1565:
#line 5648 "sql_yacc.yy"
    { }
    break;

  case 1566:
#line 5652 "sql_yacc.yy"
    { yyval.ha_rkey_mode=HA_READ_KEY_EXACT;   }
    break;

  case 1567:
#line 5653 "sql_yacc.yy"
    { yyval.ha_rkey_mode=HA_READ_KEY_OR_NEXT; }
    break;

  case 1568:
#line 5654 "sql_yacc.yy"
    { yyval.ha_rkey_mode=HA_READ_KEY_OR_PREV; }
    break;

  case 1569:
#line 5655 "sql_yacc.yy"
    { yyval.ha_rkey_mode=HA_READ_AFTER_KEY;   }
    break;

  case 1570:
#line 5656 "sql_yacc.yy"
    { yyval.ha_rkey_mode=HA_READ_BEFORE_KEY;  }
    break;

  case 1571:
#line 5663 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->sql_command = SQLCOM_REVOKE;
	  lex->users_list.empty();
	  lex->columns.empty();
	  lex->grant= lex->grant_tot_col=0;
	  lex->select_lex.db=0;
	  lex->ssl_type= SSL_TYPE_NOT_SPECIFIED;
	  lex->ssl_cipher= lex->x509_subject= lex->x509_issuer= 0;
	  bzero((char*) &lex->mqh, sizeof(lex->mqh));
	}
    break;

  case 1572:
#line 5675 "sql_yacc.yy"
    {}
    break;

  case 1573:
#line 5680 "sql_yacc.yy"
    {}
    break;

  case 1574:
#line 5683 "sql_yacc.yy"
    {
	  Lex->sql_command = SQLCOM_REVOKE_ALL;
	}
    break;

  case 1575:
#line 5690 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->users_list.empty();
	  lex->columns.empty();
	  lex->sql_command = SQLCOM_GRANT;
	  lex->grant= lex->grant_tot_col= 0;
	  lex->select_lex.db= 0;
	  lex->ssl_type= SSL_TYPE_NOT_SPECIFIED;
	  lex->ssl_cipher= lex->x509_subject= lex->x509_issuer= 0;
	  bzero((char *)&(lex->mqh),sizeof(lex->mqh));
	}
    break;

  case 1576:
#line 5703 "sql_yacc.yy"
    {}
    break;

  case 1577:
#line 5707 "sql_yacc.yy"
    {}
    break;

  case 1578:
#line 5708 "sql_yacc.yy"
    { Lex->grant = GLOBAL_ACLS;}
    break;

  case 1583:
#line 5721 "sql_yacc.yy"
    { Lex->which_columns = SELECT_ACL;}
    break;

  case 1584:
#line 5721 "sql_yacc.yy"
    {}
    break;

  case 1585:
#line 5722 "sql_yacc.yy"
    { Lex->which_columns = INSERT_ACL;}
    break;

  case 1586:
#line 5722 "sql_yacc.yy"
    {}
    break;

  case 1587:
#line 5723 "sql_yacc.yy"
    { Lex->which_columns = UPDATE_ACL; }
    break;

  case 1588:
#line 5723 "sql_yacc.yy"
    {}
    break;

  case 1589:
#line 5724 "sql_yacc.yy"
    { Lex->which_columns = REFERENCES_ACL;}
    break;

  case 1590:
#line 5724 "sql_yacc.yy"
    {}
    break;

  case 1591:
#line 5725 "sql_yacc.yy"
    { Lex->grant |= DELETE_ACL;}
    break;

  case 1592:
#line 5726 "sql_yacc.yy"
    {}
    break;

  case 1593:
#line 5727 "sql_yacc.yy"
    { Lex->grant |= INDEX_ACL;}
    break;

  case 1594:
#line 5728 "sql_yacc.yy"
    { Lex->grant |= ALTER_ACL;}
    break;

  case 1595:
#line 5729 "sql_yacc.yy"
    { Lex->grant |= CREATE_ACL;}
    break;

  case 1596:
#line 5730 "sql_yacc.yy"
    { Lex->grant |= DROP_ACL;}
    break;

  case 1597:
#line 5731 "sql_yacc.yy"
    { Lex->grant |= EXECUTE_ACL;}
    break;

  case 1598:
#line 5732 "sql_yacc.yy"
    { Lex->grant |= RELOAD_ACL;}
    break;

  case 1599:
#line 5733 "sql_yacc.yy"
    { Lex->grant |= SHUTDOWN_ACL;}
    break;

  case 1600:
#line 5734 "sql_yacc.yy"
    { Lex->grant |= PROCESS_ACL;}
    break;

  case 1601:
#line 5735 "sql_yacc.yy"
    { Lex->grant |= FILE_ACL;}
    break;

  case 1602:
#line 5736 "sql_yacc.yy"
    { Lex->grant |= GRANT_ACL;}
    break;

  case 1603:
#line 5737 "sql_yacc.yy"
    { Lex->grant |= SHOW_DB_ACL;}
    break;

  case 1604:
#line 5738 "sql_yacc.yy"
    { Lex->grant |= SUPER_ACL;}
    break;

  case 1605:
#line 5739 "sql_yacc.yy"
    { Lex->grant |= CREATE_TMP_ACL;}
    break;

  case 1606:
#line 5740 "sql_yacc.yy"
    { Lex->grant |= LOCK_TABLES_ACL; }
    break;

  case 1607:
#line 5741 "sql_yacc.yy"
    { Lex->grant |= REPL_SLAVE_ACL;}
    break;

  case 1608:
#line 5742 "sql_yacc.yy"
    { Lex->grant |= REPL_CLIENT_ACL;}
    break;

  case 1609:
#line 5747 "sql_yacc.yy"
    {}
    break;

  case 1610:
#line 5748 "sql_yacc.yy"
    {}
    break;

  case 1613:
#line 5758 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  if (lex->x509_subject)
	  {
	    net_printf(lex->thd,ER_DUP_ARGUMENT, "SUBJECT");
	    YYABORT;
	  }
	  lex->x509_subject=yyvsp[0].lex_str.str;
	}
    break;

  case 1614:
#line 5768 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  if (lex->x509_issuer)
	  {
	    net_printf(lex->thd,ER_DUP_ARGUMENT, "ISSUER");
	    YYABORT;
	  }
	  lex->x509_issuer=yyvsp[0].lex_str.str;
	}
    break;

  case 1615:
#line 5778 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  if (lex->ssl_cipher)
	  {
	    net_printf(lex->thd,ER_DUP_ARGUMENT, "CIPHER");
	    YYABORT;
	  }
	  lex->ssl_cipher=yyvsp[0].lex_str.str;
	}
    break;

  case 1616:
#line 5791 "sql_yacc.yy"
    {
	    LEX *lex= Lex;
	    lex->current_select->db= lex->thd->db;
	    if (lex->grant == GLOBAL_ACLS)
	      lex->grant = DB_ACLS & ~GRANT_ACL;
	    else if (lex->columns.elements)
	    {
	      send_error(lex->thd,ER_ILLEGAL_GRANT_FOR_TABLE);
	      YYABORT;
	    }
	  }
    break;

  case 1617:
#line 5803 "sql_yacc.yy"
    {
	    LEX *lex= Lex;
	    lex->current_select->db = yyvsp[-2].lex_str.str;
	    if (lex->grant == GLOBAL_ACLS)
	      lex->grant = DB_ACLS & ~GRANT_ACL;
	    else if (lex->columns.elements)
	    {
	      send_error(lex->thd,ER_ILLEGAL_GRANT_FOR_TABLE);
	      YYABORT;
	    }
	  }
    break;

  case 1618:
#line 5815 "sql_yacc.yy"
    {
	    LEX *lex= Lex;
	    lex->current_select->db = NULL;
	    if (lex->grant == GLOBAL_ACLS)
	      lex->grant= GLOBAL_ACLS & ~GRANT_ACL;
	    else if (lex->columns.elements)
	    {
	      send_error(lex->thd,ER_ILLEGAL_GRANT_FOR_TABLE);
	      YYABORT;
	    }
	  }
    break;

  case 1619:
#line 5827 "sql_yacc.yy"
    {
	    LEX *lex=Lex;
	    if (!lex->current_select->add_table_to_list(lex->thd, yyvsp[0].table,NULL,0))
	      YYABORT;
	    if (lex->grant == GLOBAL_ACLS)
	      lex->grant =  TABLE_ACLS & ~GRANT_ACL;
	  }
    break;

  case 1620:
#line 5838 "sql_yacc.yy"
    { if (Lex->users_list.push_back(yyvsp[0].lex_user)) YYABORT;}
    break;

  case 1621:
#line 5840 "sql_yacc.yy"
    {
	    if (Lex->users_list.push_back(yyvsp[0].lex_user))
	      YYABORT;
	  }
    break;

  case 1622:
#line 5849 "sql_yacc.yy"
    {
	   yyval.lex_user=yyvsp[-3].lex_user; yyvsp[-3].lex_user->password=yyvsp[0].lex_str;
	   if (yyvsp[0].lex_str.length)
	   {
             if (YYTHD->variables.old_passwords)
             {
               char *buff= 
                 (char *) YYTHD->alloc(SCRAMBLED_PASSWORD_CHAR_LENGTH_323+1);
               if (buff)
                 make_scrambled_password_323(buff, yyvsp[0].lex_str.str);
               yyvsp[-3].lex_user->password.str= buff;
               yyvsp[-3].lex_user->password.length= SCRAMBLED_PASSWORD_CHAR_LENGTH_323;
             }
             else
             {
               char *buff= 
                 (char *) YYTHD->alloc(SCRAMBLED_PASSWORD_CHAR_LENGTH+1);
               if (buff)
                 make_scrambled_password(buff, yyvsp[0].lex_str.str);
               yyvsp[-3].lex_user->password.str= buff;
               yyvsp[-3].lex_user->password.length= SCRAMBLED_PASSWORD_CHAR_LENGTH;
             }
	  }
	}
    break;

  case 1623:
#line 5874 "sql_yacc.yy"
    { yyval.lex_user=yyvsp[-4].lex_user; yyvsp[-4].lex_user->password=yyvsp[0].lex_str ; }
    break;

  case 1624:
#line 5876 "sql_yacc.yy"
    { yyval.lex_user=yyvsp[0].lex_user; yyvsp[0].lex_user->password.str=NullS; }
    break;

  case 1625:
#line 5882 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->grant |= lex->which_columns;
	}
    break;

  case 1629:
#line 5894 "sql_yacc.yy"
    {
	  String *new_str = new (YYTHD->mem_root) String((const char*) yyvsp[0].lex_str.str,yyvsp[0].lex_str.length,system_charset_info);
	  List_iterator <LEX_COLUMN> iter(Lex->columns);
	  class LEX_COLUMN *point;
	  LEX *lex=Lex;
	  while ((point=iter++))
	  {
	    if (!my_strcasecmp(system_charset_info,
                               point->column.ptr(), new_str->ptr()))
		break;
	  }
	  lex->grant_tot_col|= lex->which_columns;
	  if (point)
	    point->rights |= lex->which_columns;
	  else
	    lex->columns.push_back(new LEX_COLUMN (*new_str,lex->which_columns));
	}
    break;

  case 1631:
#line 5916 "sql_yacc.yy"
    {
            Lex->ssl_type=SSL_TYPE_SPECIFIED;
          }
    break;

  case 1632:
#line 5920 "sql_yacc.yy"
    {
            Lex->ssl_type=SSL_TYPE_ANY;
          }
    break;

  case 1633:
#line 5924 "sql_yacc.yy"
    {
            Lex->ssl_type=SSL_TYPE_X509;
          }
    break;

  case 1634:
#line 5928 "sql_yacc.yy"
    {
	    Lex->ssl_type=SSL_TYPE_NONE;
	  }
    break;

  case 1635:
#line 5934 "sql_yacc.yy"
    {}
    break;

  case 1637:
#line 5938 "sql_yacc.yy"
    {}
    break;

  case 1638:
#line 5939 "sql_yacc.yy"
    {}
    break;

  case 1639:
#line 5943 "sql_yacc.yy"
    { Lex->grant |= GRANT_ACL;}
    break;

  case 1640:
#line 5945 "sql_yacc.yy"
    {
	  Lex->mqh.questions=yyvsp[0].ulong_num;
	  Lex->mqh.bits |= 1;
	}
    break;

  case 1641:
#line 5950 "sql_yacc.yy"
    {
	  Lex->mqh.updates=yyvsp[0].ulong_num;
	  Lex->mqh.bits |= 2;
	}
    break;

  case 1642:
#line 5955 "sql_yacc.yy"
    {
	  Lex->mqh.connections=yyvsp[0].ulong_num;
	  Lex->mqh.bits |= 4;
	}
    break;

  case 1643:
#line 5962 "sql_yacc.yy"
    { Lex->sql_command = SQLCOM_BEGIN; Lex->start_transaction_opt= 0;}
    break;

  case 1644:
#line 5962 "sql_yacc.yy"
    {}
    break;

  case 1645:
#line 5966 "sql_yacc.yy"
    {}
    break;

  case 1646:
#line 5967 "sql_yacc.yy"
    {;}
    break;

  case 1647:
#line 5971 "sql_yacc.yy"
    { Lex->sql_command = SQLCOM_COMMIT;}
    break;

  case 1648:
#line 5975 "sql_yacc.yy"
    {
	  Lex->sql_command = SQLCOM_ROLLBACK;
	}
    break;

  case 1649:
#line 5979 "sql_yacc.yy"
    {
	  Lex->sql_command = SQLCOM_ROLLBACK_TO_SAVEPOINT;
	  Lex->savepoint_name = yyvsp[0].lex_str.str;
	}
    break;

  case 1650:
#line 5985 "sql_yacc.yy"
    {
	  Lex->sql_command = SQLCOM_SAVEPOINT;
	  Lex->savepoint_name = yyvsp[0].lex_str.str;
	}
    break;

  case 1651:
#line 5996 "sql_yacc.yy"
    {}
    break;

  case 1653:
#line 6002 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  if (lex->exchange)
	  {
	    /* Only the last SELECT can have  INTO...... */
	    net_printf(lex->thd, ER_WRONG_USAGE, "UNION", "INTO");
	    YYABORT;
	  }
	  if (lex->current_select->linkage == GLOBAL_OPTIONS_TYPE)
	  {
            yyerror(ER(ER_SYNTAX_ERROR));
	    YYABORT;
	  }
	  if (mysql_new_select(lex, 0))
	    YYABORT;
          mysql_init_select(lex);
	  lex->current_select->linkage=UNION_TYPE;
          if (yyvsp[0].num) /* UNION DISTINCT - remember position */
            lex->current_select->master_unit()->union_distinct=
                                                      lex->current_select;
	}
    break;

  case 1654:
#line 6023 "sql_yacc.yy"
    {}
    break;

  case 1655:
#line 6027 "sql_yacc.yy"
    {}
    break;

  case 1656:
#line 6028 "sql_yacc.yy"
    {}
    break;

  case 1657:
#line 6032 "sql_yacc.yy"
    {}
    break;

  case 1658:
#line 6034 "sql_yacc.yy"
    {
	    THD *thd= YYTHD;
	    LEX *lex= thd->lex;
	    DBUG_ASSERT(lex->current_select->linkage != GLOBAL_OPTIONS_TYPE);
	    SELECT_LEX *sel= lex->current_select;
	    SELECT_LEX_UNIT *unit= sel->master_unit();
	    SELECT_LEX *fake= unit->fake_select_lex;
	    if (fake)
	    {
	      unit->global_parameters= fake;
	      fake->no_table_names_allowed= 1;
	      lex->current_select= fake;
	    }
	    thd->where= "global ORDER clause";
	  }
    break;

  case 1659:
#line 6050 "sql_yacc.yy"
    {
	    THD *thd= YYTHD;
	    thd->lex->current_select->no_table_names_allowed= 0;
	    thd->where= "";
          }
    break;

  case 1662:
#line 6063 "sql_yacc.yy"
    { yyval.num=1; }
    break;

  case 1663:
#line 6064 "sql_yacc.yy"
    { yyval.num=1; }
    break;

  case 1664:
#line 6065 "sql_yacc.yy"
    { yyval.num=0; }
    break;

  case 1665:
#line 6071 "sql_yacc.yy"
    {
	  yyval.item= yyvsp[-1].item;
	}
    break;

  case 1666:
#line 6077 "sql_yacc.yy"
    {
	  yyval.item= new Item_singlerow_subselect(Lex->current_select->
					   master_unit()->first_select());
	}
    break;

  case 1667:
#line 6085 "sql_yacc.yy"
    {
	  yyval.item= yyvsp[-1].item;
	}
    break;

  case 1668:
#line 6091 "sql_yacc.yy"
    {
	  yyval.item= new Item_exists_subselect(Lex->current_select->master_unit()->
					first_select());
	}
    break;

  case 1669:
#line 6099 "sql_yacc.yy"
    {
    yyval.select_lex= yyvsp[-1].select_lex;
  }
    break;

  case 1670:
#line 6105 "sql_yacc.yy"
    {
    yyval.select_lex= Lex->current_select->master_unit()->first_select();
  }
    break;

  case 1671:
#line 6111 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  if (((int)lex->sql_command >= (int)SQLCOM_HA_OPEN &&
	       lex->sql_command <= (int)SQLCOM_HA_READ) ||
	       lex->sql_command == (int)SQLCOM_KILL)
	  {
            yyerror(ER(ER_SYNTAX_ERROR));
	    YYABORT;
	  }
	  if (mysql_new_select(Lex, 1))
	    YYABORT;
	}
    break;

  case 1672:
#line 6126 "sql_yacc.yy"
    {
	  LEX *lex=Lex;
	  lex->current_select = lex->current_select->return_after_parsing();
	}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 21633 "sql_yacc.cc"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
	  yychar = YYEMPTY;

	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}



