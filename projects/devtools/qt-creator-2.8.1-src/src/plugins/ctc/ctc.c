/****************************************************************************
**
** Copyright (C) 2016 MECT srl.
** Contact: http://www.mect.it/
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General
** Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 3.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "csv.h"

#define dbg_printf(...)
//#define dbg_printf printf


#define GVL_NAME                "crosstable.gvl"
#define CPP_NAME                "crosstable.cpp"
#define CPP_H_NAME              "crosstable.h"

#define REGISTER_SIZE           4

#define MAX_ROWS                5472
#define FIELD_MAX_LENGTH        4096
#define ROW_FIELDS              13
#define CROSSTABLE_DEF          10000
#define ID_MAXLEN               16
#define ADDR_MAXLEN             15

/* All crosstable types */
enum type_e {
    TYPE_NONE = 0,

    TYPE_BIT,
    TYPE_BYTE_BIT,
    TYPE_WORD_BIT,
    TYPE_DWORD_BIT,

    TYPE_INT,
    TYPE_INTBA,
    TYPE_DINT,
    TYPE_DINTBADC,
    TYPE_DINTCDAB,
    TYPE_DINTDCBA,

    TYPE_BYTE,
    TYPE_UINT,
    TYPE_UINTBA,
    TYPE_UDINT,
    TYPE_UDINTBADC,
    TYPE_UDINTCDAB,
    TYPE_UDINTDCBA,

    TYPE_REAL,
    TYPE_REALBADC,
    TYPE_REALCDAB,
    TYPE_REALDCBA
};

/* All crosstable communication protocols */
enum protocol_e {
    PROTO_NONE = 0,
    PROTO_PLC,
    PROTO_RTU,
    PROTO_TCP,
    PROTO_TCPRTU,
    PROTO_CANOPEN,
    PROTO_RTU_SRV,
    PROTO_TCP_SRV,
    PROTO_TCPRTU_SRV,
    PROTO_MECT
};

/* All crosstable behaviors */
enum behav_e {
    BEHAV_NONE = 0,
    BEHAV_INPUT,
    BEHAV_OUTPUT,
    BEHAV_ALARM,
    BEHAV_EVENT
};

enum trigger_ops_e {
    TO_NONE,
    TO_EQ,
    TO_NE,
    TO_GT,
    TO_GE,
    TO_LT,
    TO_LE,
    TO_RISE,
    TO_FALL
};

/* Full crosstable row */
struct row_s {
    int priority;
    char update;
    char name[ID_MAXLEN + 1];
    enum type_e type;
    int decimal;
    enum protocol_e protocol;
    char address[ADDR_MAXLEN + 1];
    int port;
    int node_id;
    int reg;
    int block;
    char *comment;
    enum behav_e behavior;
    struct alarm_event_s {
        char *expr;
        char *op1_id;
        char *op2_id;
        float op2_f;
        int operator;
    } alarm_event;

    int number;

    int filled_fields;          /* Data in any field? */
};

/*
 * Variables
 */

static struct row_s row;

static struct crosstable_s {
    struct row_s *rows;         /* Cross table */
    unsigned int size;          /* Current cross table size */
    int index_last;             /* Index of last data filled in */

    int row_crt;                /* Current CSV row number */
    int field_crt;              /* Index of the current field */

    char *filename;             /* Name of the cross table file */
} crosstable = {
    .rows = NULL,
    .size = 0,
    .index_last = -1,

    .row_crt = 0,
    .field_crt = 0,

    .filename = NULL
};

/* Status data for GVL output */
static struct gvl_stat_s {
    char *filename;
} gvl = {
    .filename = NULL
};

/* Status data for C++ output */
static struct cpp_stat_s {
    char *source;
    char *include;
} cpp = {
    .source = NULL,
    .include = NULL
};

/* Symbol table */
static struct st_id_s {
    unsigned int index;
    struct st_s {
        char *id;               /* Symbol name */
        int rown;               /* Cross table row */
        int xref;               /* Reference to cross table entry */
    } st[MAX_ROWS];
} st_id;



/* Local function prototypes */
static void error_log(int line, char *msg);
static void error_log_exit(int line, char *msg);
static void perror_log_exit(int line, char *msg);
static void cperror_log_exit(struct csv_parser *p, int line, char *msg);
static void row_init(struct row_s *row);
static int crosstable_row_add(struct row_s *row);
static enum type_e type_get(char *type);
static char *cpp_type_get(struct row_s *row);
static int cpp_leading_comments_write(FILE *file);
static enum protocol_e protocol_get(char *protocol);
static enum behav_e behav_get(char *behavior);
static char *alarm_or_event_get(char *behavior, struct row_s *row);
static char *comment_get(char *behavior);
static void cb_field(void *s, size_t len, void *data);
static void cb_row(int c, void *data);
static int is_space(unsigned char c);
static int is_term(unsigned char c);
static int st_id_append(char *id, int rown, int xref);
static int duplicate_ids(void);
static int key_st_id_comp(const void *key, const void *st);
static int alarms_and_events_check(void);
static void xtable_cc(void);
static int gvl_gen(void);
static int cpp_gen(void);
static int cpp_h_gen(void);
static void usage(char *pn);



/**
 * Create a gcc-style error using the given line number and
 * message.
 *
 * @param line          line number
 * @param msg           error message
 */
static void
error_log(int line, char *msg)
{
    if (msg == NULL)
        msg = "[no message]";

    char *fn = crosstable.filename;
    if (fn == NULL)
        fn = "[no file]";

    if (line < 0)
        line = 0;

    fprintf(stderr, "%s:%d:%d: error: %s\n", fn, line, 1, msg);

    exit(EXIT_FAILURE);
}

/**
 * Create a gcc-style error using the given line number and
 * message, and abort execution.
 *
 * @param line          line number
 * @param msg           error message
 */
static void
error_log_exit(int line, char *msg)
{
    error_log(line, msg);

    exit(EXIT_FAILURE);
}

/**
 * Create a gcc-style error using the given line number and
 * message, add perror()  and abort execution.
 *
 * @param line          line number
 * @param msg           error message
 */
static void
perror_log_exit(int line, char *msg)
{
    char *perr = strdup(strerror(errno));
    /* Output the important error anyway. */
    if (perr == NULL)
        error_log_exit(line, msg);

    char *fullmsg = (char *)malloc(strlen(msg) + strlen(perr) + 2 + 1);
    /* Output the important error anyway. */
    if (fullmsg == NULL)
        error_log_exit(line, msg);

    strncpy(fullmsg, msg, strlen(msg) + 1);
    strncat(fullmsg, ": ", 3);
    strncat(fullmsg, perr, strlen(perr) + 1);
    error_log_exit(line, fullmsg);

    /* NOTE: free heap if not aborting. */
}

/**
 * Create a gcc-style error using the given line number and
 * message, add parser error and abort execution.
 *
 * @param p             CSV parser handle
 * @param line          line number
 * @param msg           error message
 */
static void
cperror_log_exit(struct csv_parser *p, int line, char *msg)
{
    char *fullmsg = (char *)malloc(strlen(msg) + strlen(csv_strerror(csv_error(p))) + 2 + 1);
    /* Output the important error anyway. */
    if (fullmsg == NULL)
        error_log_exit(line, msg);

    strncpy(fullmsg, msg, strlen(msg) + 1);
    strncat(fullmsg, ": ", 3);
    strncat(fullmsg, csv_strerror(csv_error(p)), strlen(csv_strerror(csv_error(p))) + 1);
    error_log_exit(line, fullmsg);

    /* NOTE: free heap if not aborting. */
}



static void
row_init(struct row_s *row)
{
    bzero(row, sizeof(struct row_s));

    row->priority = -1;
    row->type = TYPE_NONE;
    row->decimal = -1;
    row->protocol = PROTO_NONE;
    row->port = -1;
    row->node_id = -1;
    row->reg = -1;
    row->block = -1;
    row->behavior = BEHAV_NONE;
    bzero(&(row->alarm_event), sizeof(row->alarm_event));
}

/**
 * Add the given row to the default cross table.
 * Resize the table, if needed.
 *
 * @param row           row to add to cross table
 *
 * @return              1 for success, 0 for failure
 */
static int
crosstable_row_add(struct row_s *row)
{
    if ((unsigned)(crosstable.index_last + 1) >= crosstable.size) {
        crosstable.rows = (struct row_s *)realloc(crosstable.rows, sizeof(struct row_s) * (crosstable.size + CROSSTABLE_DEF));
        assert(crosstable.rows != NULL);

        crosstable.size += CROSSTABLE_DEF;
    }

    crosstable.rows[++crosstable.index_last] = *row;

    return 1;
}

/**
 * Return the code correspomding to the given data type.
 *
 * @param type          data type
 *
 * @return              code associated to type.
 */
static enum type_e
type_get(char *type)
{
    if (type == NULL)
        return TYPE_NONE;

    if (strcmp(type, "BIT") == 0)
        return TYPE_BIT;
    else if (strcmp(type, "BYTE_BIT") == 0)
        return TYPE_BYTE_BIT;
    else if (strcmp(type, "WORD_BIT") == 0)
        return TYPE_WORD_BIT;
    else if (strcmp(type, "DWORD_BIT") == 0)
        return TYPE_DWORD_BIT;
    else if (strcmp(type, "BYTE") == 0)
        return TYPE_BYTE;
    else if (strcmp(type, "UINT") == 0)
        return TYPE_UINT;
    else if (strcmp(type, "UINTBA") == 0)
        return TYPE_UINTBA;
    else if (strcmp(type, "INT") == 0)
        return TYPE_INT;
    else if (strcmp(type, "INTBA") == 0)
        return TYPE_INTBA;
    else if (strcmp(type, "UDINT") == 0)
        return TYPE_UDINT;
    else if (strcmp(type, "UDINTBADC") == 0)
        return TYPE_UDINTBADC;
    else if (strcmp(type, "UDINTCDAB") == 0)
        return TYPE_UDINTCDAB;
    else if (strcmp(type, "UDINTDCBA") == 0)
        return TYPE_UDINTDCBA;
    else if (strcmp(type, "DINT") == 0)
        return TYPE_DINT;
    else if (strcmp(type, "DINTBADC") == 0)
        return TYPE_DINTBADC;
    else if (strcmp(type, "DINTCDAB") == 0)
        return TYPE_DINTCDAB;
    else if (strcmp(type, "DINTDCBA") == 0)
        return TYPE_DINTDCBA;
    else if (strcmp(type, "REAL") == 0)
        return TYPE_REAL;
    else if (strcmp(type, "REALBADC") == 0)
        return TYPE_REALBADC;
    else if (strcmp(type, "REALCDAB") == 0)
        return TYPE_REALCDAB;
    else if (strcmp(type, "REALDCBA") == 0)
        return TYPE_REALDCBA;
    else
        return TYPE_NONE;
}

static char *
cpp_type_get(struct row_s *row)
{
    char *type = NULL;

    switch (row->type) {
        case TYPE_BIT:
        case TYPE_BYTE_BIT:
        case TYPE_WORD_BIT:
        case TYPE_DWORD_BIT:
            type = "int";

            break;

        case TYPE_BYTE:
            type = "u_int8_t";

            break;

        case TYPE_UINT:
        case TYPE_UINTBA:
            type = "u_int16_t";

            break;

        case TYPE_INT:
        case TYPE_INTBA:
            type = "int16_t";

            break;

        case TYPE_UDINT:
        case TYPE_UDINTBADC:
        case TYPE_UDINTCDAB:
        case TYPE_UDINTDCBA:
            type = "u_int32_t";

            break;

        case TYPE_DINT:
        case TYPE_DINTBADC:
        case TYPE_DINTCDAB:
        case TYPE_DINTDCBA:
            type = "int32_t";

            break;

        case TYPE_REAL:
        case TYPE_REALBADC:
        case TYPE_REALCDAB:
        case TYPE_REALDCBA:
            type = "float";

            break;

        default:
            type = "NONE FIXME";

            break;
    }

    return type;
}

/**
 * Write the leading comments for the C++ files.
 *
 * @param file          file to write into
 *
 * @return              0 for success, else failure code.
 */
static int
cpp_leading_comments_write(FILE *file)
{
    assert(file != NULL);

    fprintf(file, "/* File automatically generated by the cross table compiler */\n");
    fprintf(file, "/* from the cross table file %s. */\n", crosstable.filename);

    fprintf(file, "\n");

    fprintf(file, "/* BIT        ->  int       */\n");
    fprintf(file, "/* BYTE_BIT   ->  int       */\n");
    fprintf(file, "/* WORD_BIT   ->  int       */\n");
    fprintf(file, "/* DWORD_BIT  ->  int       */\n");
    fprintf(file, "/* BYTE       ->  u_int8_t  */\n");
    fprintf(file, "/* UINT       ->  u_int16_t */\n");
    fprintf(file, "/* UINTBA     ->  UINTBA    */\n");
    fprintf(file, "/* INT        ->  int16_t   */\n");
    fprintf(file, "/* INTBA      ->  INTBA     */\n");
    fprintf(file, "/* UDINT      ->  u_int32_t */\n");
    fprintf(file, "/* UDINTBADC  ->  UDINTBADC */\n");
    fprintf(file, "/* UDINTCDAB  ->  UDINTCDAB */\n");
    fprintf(file, "/* UDINTDCBA  ->  UDINTDCBA */\n");
    fprintf(file, "/* DINT       ->  int32_t   */\n");
    fprintf(file, "/* DINTBADC   ->  DINTBADC  */\n");
    fprintf(file, "/* DINTCDAB   ->  DINTCDAB  */\n");
    fprintf(file, "/* DINTDCBA   ->  DINTDCBA  */\n");
    fprintf(file, "/* REAL       ->  float     */\n");
    fprintf(file, "/* REALBADC   ->  REALBADC  */\n");
    fprintf(file, "/* REALCDAB   ->  REALCDAB  */\n");
    fprintf(file, "/* REALDCBA   ->  REALDCBA  */\n");

    return 0;
}

/**
 * Return the code correspomding to the given protocol.
 *
 * @param protocol      protocol type.
 *
 * @return              code associated to type.
 */
static enum protocol_e
protocol_get(char *protocol)
{
    if (protocol == NULL)
        return PROTO_NONE;

    if (strcmp(protocol, "PLC") == 0)
        return PROTO_PLC;

    if (strcmp(protocol, "RTU") == 0)
        return PROTO_RTU;

    if (strcmp(protocol, "TCP") == 0)
        return PROTO_TCP;

    if (strcmp(protocol, "TCPRTU") == 0)
        return PROTO_TCPRTU;

    if (strcmp(protocol, "CANOPEN") == 0)
        return PROTO_CANOPEN;

    if (strcmp(protocol, "RTU_SRV") == 0)
        return PROTO_RTU_SRV;

    if (strcmp(protocol, "TCP_SRV") == 0)
        return PROTO_TCP_SRV;

    if (strcmp(protocol, "TCPRTU_SRV") == 0)
        return PROTO_TCPRTU_SRV;

    if (strcmp(protocol, "MECT") == 0)
        return PROTO_MECT;

    return PROTO_NONE;
}

/**
 * Return the code of the given behavior.
 *
 * @param behavior      behavior expression
 *
 * @return              code associated to type.
 */
static enum behav_e
behav_get(char *behavior)
{
    if (behavior == NULL)
        return BEHAV_NONE;

    if (strncmp(behavior, "[RO]", 4) == 0)
        return BEHAV_INPUT;

    if (strncmp(behavior, "[RW]", 4) == 0)
        return BEHAV_OUTPUT;

    if (strncmp(behavior, "[AL ", 3) == 0)
        return BEHAV_ALARM;

    if (strncmp(behavior, "[EV ", 3) == 0)
        return BEHAV_EVENT;

    return BEHAV_NONE;
}

/**
 * Return the alarm or event expression for the given behavior.
 * Assume rigid format: [AL <expression] or [EV <expression]
 *
 * @param behavior      behavior expression
 * @param row           current row data
 *
 * @return              alarm/event expression or empty string.
 */
static char *
alarm_or_event_get(char *behavior, struct row_s *row)
{
    if (behavior == NULL)
        return "";

    if ((row->behavior != BEHAV_ALARM) && (row->behavior != BEHAV_EVENT))
        return "";

    char *start = strchr(behavior, '[');
    if (start == NULL)
        return "";
    start = strchr(start, ' ');
    if (start == NULL)
        return "";
    ++start;

    char *end = strchr(start, ']');
    if (end == NULL)
        return "";
    --end;

    if (start >= end)
        return "";

    char *alarm_or_event = (char *)malloc(end - start + 2);
    if (alarm_or_event == NULL)
        return "";

    bzero(alarm_or_event, end - start + 2);

    return strncpy(alarm_or_event, start, end - start + 1);
}

/**
 * Return the comment for the given behavior.
 *
 * @param behavior      behavior expression
 *
 * @return              comment or empty string.
 */
static char *
comment_get(char *behavior)
{
    char *comment = "";

    if (behavior != NULL) {
        char *c = NULL;

        c = strrchr(behavior, ']');
        /* Skip behavior terminator. */
        if (c != NULL)
            comment = c + 1;
    }

    return comment;
}



/**
 * New field callback.
 *
 * @param s             ???
 * @param len           non-whitespae characters
 * @param data          pointer to user-defined data tructure.
 */
static void
cb_field(void *s, size_t len, void *data)
{
    /* Field not empty? */
    if (len > 0) {
        char buf[FIELD_MAX_LENGTH];

        (((struct row_s *)data)->filled_fields)++;

        if (len >= FIELD_MAX_LENGTH)
            len = FIELD_MAX_LENGTH;

        strncpy(buf, s, len);
        buf[len] = '\0';

        switch (crosstable.field_crt) {
            case 0:
                ((struct row_s *)data)->priority = strtol(buf, NULL, 10);
                dbg_printf("Priority %d\n", ((struct row_s *)data)->priority);

            break;

            case 1:
                ((struct row_s *)data)->update = buf[0];
                dbg_printf("Update %c\n", ((struct row_s *)data)->update);

            break;

            case 2:
                strncpy(((struct row_s *)data)->name, buf, 17);
                dbg_printf("Name %s\n", ((struct row_s *)data)->name);

            break;

            case 3:
                ((struct row_s *)data)->type = type_get(buf);
                dbg_printf("Type %d\n", ((struct row_s *)data)->type);

            break;

            case 4:
                ((struct row_s *)data)->decimal = strtol(buf, NULL, 10);
                dbg_printf("Decimal %d\n", ((struct row_s *)data)->decimal);

            break;

            case 5:
                ((struct row_s *)data)->protocol = protocol_get(buf);
                dbg_printf("Protocol %d\n", ((struct row_s *)data)->protocol);

            break;

            case 6:
                strncpy(((struct row_s *)data)->address, buf, 16);
                dbg_printf("Address %s\n", ((struct row_s *)data)->address);

            break;

            case 7:
                ((struct row_s *)data)->port = strtol(buf, NULL, 10);
                dbg_printf("Port %d\n", ((struct row_s *)data)->port);

            break;

            case 8:
                ((struct row_s *)data)->node_id = strtol(buf, NULL, 10);
                dbg_printf("Node ID %d\n", ((struct row_s *)data)->node_id);

            break;

            case 9:
                ((struct row_s *)data)->reg = strtol(buf, NULL, 10);
                dbg_printf("Register %d\n", ((struct row_s *)data)->reg);

            break;

            case 10:
                ((struct row_s *)data)->block = strtol(buf, NULL, 10);
                dbg_printf("Block %d\n", ((struct row_s *)data)->block);

            break;

            case 11:

            break;

            case 12:
                ((struct row_s *)data)->behavior = behav_get(buf);
                dbg_printf("Behavior %d\n", ((struct row_s *)data)->behavior);

                /* NOTE: call AFTER behav_get(). */
                ((struct row_s *)data)->alarm_event.expr = alarm_or_event_get(buf, (struct row_s *)data);
                dbg_printf("Alarm/event %s\n", ((struct row_s *)data)->alarm_event.expr);

                ((struct row_s *)data)->comment = strdup(comment_get(buf));
                dbg_printf("Comment %s\n", ((struct row_s *)data)->comment);

            break;

            default:
                error_log_exit(crosstable.row_crt, "too many fields in the row.");

            break;
        }
    }

    crosstable.field_crt++;
}

/**
 * New row callbak.
 *
 * @param c             fields in the row;
 * @param data          pointer to user-defined data tructure.
 */
static void
cb_row(int c, void *data)
{
    crosstable.row_crt++;       /* Count rows from 1. */

    if ((c > ROW_FIELDS) || (crosstable.field_crt > ROW_FIELDS))
        error_log_exit(crosstable.row_crt, "too many fields in the row");
    else if ((c < ROW_FIELDS) || (crosstable.field_crt < ROW_FIELDS))
        error_log_exit(crosstable.row_crt, "too few fields in the row");

    /* Non-empty row */
    if (((struct row_s *)data)->filled_fields > 0) {
        struct row_s *row = data;

        /* Skip disabled variables. */
        if (row->priority != 0) {
            dbg_printf("Row\n");

            row->number = crosstable.row_crt;

            assert(crosstable_row_add(row));
        }

        row_init(row);
    }

    crosstable.field_crt = 0;
}

/**
 * Check if the given character is a space.
 *
 * @param c             character to check
 *
 * @return              1 is space, 0 is not space.
 */
static int
is_space(unsigned char c)
{
    if ((c == CSV_SPACE) || (c == CSV_TAB))
        return 1;

    return 0;
}

/**
 * Check if the given character is a line terminator.
 *
 * @param c             character to check
 *
 * @return              1 is terminator, 0 is not terminator.
 */
static int
is_term(unsigned char c)
{
    if ((c == CSV_CR) || (c == CSV_LF))
        return 1;

    return 0;
}



/**
 * Check the validity of the given ID.
 *
 * @param id            ID to check
 *
 * @return              0 for valid ID
 */
static int
xtable_ids_check(char *id)
{
    /* No ID */
    if (id == NULL)
        return 1;

    /* Empty ID */
    if (strlen(id) == 0)
        return 1;

    /* Start by '_' or letter. */
    if (!isalpha(id[0]) && (id[0] != '_'))
        return 1;

    /* Include only letters and '_'. */
    if (strspn(id, "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz0123456789") != strlen(id))
        return 1;

    return 0;
}

/**
 * Initialize the ID symbol table.
 */
static void
st_id_init(void)
{
    bzero((void *)&st_id, sizeof(st_id));
}

/**
 * Append the given ID and its row number in the cross table
 * to the ID store (do not check for duplicates).
 *
 * @param id            ID to add
 * @param rown          cross table row number
 * @param xrefy         cross table entry
 *
 * @return              0 for errors
 */
static int
st_id_append(char *id, int rown, int xref)
{
    /* Overflow? */
    if (st_id.index >= MAX_ROWS)
        return 0;

    st_id.st[st_id.index].id = id;
    st_id.st[st_id.index].rown = rown;
    st_id.st[st_id.index].xref = xref;

    ++st_id.index;

    return 1;
}

/**
 * Compare the two given ID symbol table entries.
 *
 * @param a             first entry
 * @param b             second entry
 *
 * @return              -1, 0, +1 for less than, equal, greater than
 */
static int
st_id_comp(const void *a, const void *b)
{
    if (((struct st_s *)a)->id == NULL)
        return -1;
    else if (((struct st_s *)b)->id == NULL)
        return 1;
    else if (((struct st_s *)a)->id == ((struct st_s *)b)->id)
        return 0;

    return strcmp(((struct st_s *)a)->id, ((struct st_s *)b)->id);
}

/**
 * Check for duplicate IDs in the symbol table.
 *
 * @return              0 if no duplicates
 */
static int
duplicate_ids(void)
{
    /* Sort the symbol table. */
    qsort(st_id.st, st_id.index, sizeof(st_id.st[0]), st_id_comp);

    /* Check for duplicate IDs, now always in adjacent entries. */
    int i = 0;
    for (i = 0; i < (int)st_id.index - 1; i++)
        if (!strcmp(st_id.st[i].id, st_id.st[i + 1].id)) {
            error_log_exit(st_id.st[i].rown, "duplicate name.");

            return 1;           /* Never reached */
        }

    return 0;
}

/**
 * Compare the the given key with the given ID symbol table entry.
 *
 * @param key           key string
 * @param st            symbol table entry
 *
 * @return              -1, 0, +1 for less than, equal, greater than
 */
static int
key_st_id_comp(const void *key, const void *st)
{
    if (key == NULL)
        return -1;

    if (((struct st_s *)st)->id == NULL)
        return 1;

    if (key == ((struct st_s *)st)->id)
        return 0;

    return strcmp(key, ((struct st_s *)st)->id);
}

/**
 * Check for consistency all alarm and event expressions.
 *
 * @return              0 if all check fine
 */
static int
alarms_and_events_check(void)
{
    int i = 0;
    for (i = 0; i <= crosstable.index_last; i++) {
        /* Skip empty rows. */
        if (crosstable.rows[i].filled_fields == 0)
            continue;

        char *ae = crosstable.rows[i].alarm_event.expr;

        /* No expression */
        if ((ae == NULL) || (ae[0] == '\0'))
            continue;

        ae = strdup(ae);
        if (ae == NULL)
            error_log_exit(crosstable.rows[i].number, "error acquiring the trigger expression.");

        char *token = NULL;

        /*
         * First trigger expression operand
         */
        token = strtok(ae, " ");
        if (token == NULL)
            error_log_exit(crosstable.rows[i].number, "no operand in the trigger expression.");

        /* Operand 1 name too long */
        if (strlen(token) > ID_MAXLEN)
            error_log_exit(crosstable.rows[i].number, "the name of the trigger expression first operand is too long.");

        if (xtable_ids_check(token) != 0)
            error_log_exit(crosstable.rows[i].number, "invalid first operand name trigger expression.");

        char **op1 = &(crosstable.rows[i].alarm_event.op1_id);

        /* Store first trigger expression operand. */
        *op1 = strndup(token, ID_MAXLEN);
        if (*op1 == NULL)
            error_log_exit(crosstable.rows[i].number, "error storing the trigger expression first operand.");

        /* Is the operand defined? */
        struct st_s *st_op1 = (struct st_s *)bsearch(*op1, st_id.st, st_id.index, sizeof(st_id.st[0]), key_st_id_comp);
        if (st_op1 == NULL)
            error_log_exit(crosstable.rows[i].number, "first trigger expression operand is not defined.");

        /*
         * Trigger expression operator
         */
        token = strtok(NULL, " ");
        if (token == NULL)
            error_log_exit(crosstable.rows[i].number, "incomplete trigger expression.");

        /* Store trigger expression operator. */
	int oplen = strlen(token);
	if ((oplen == 2) && (strncmp(token, "==", 2) == 0))
	    crosstable.rows[i].alarm_event.operator = TO_EQ;
	else if ((oplen == 2) && (strncmp(token, "!=", 2) == 0))
	    crosstable.rows[i].alarm_event.operator = TO_NE;
	else if ((oplen == 1) && (strncmp(token, ">", 1) == 0))
	    crosstable.rows[i].alarm_event.operator = TO_GT;
	else if ((oplen == 2) && (strncmp(token, ">=", 2) == 0))
	    crosstable.rows[i].alarm_event.operator = TO_GE;
	else if ((oplen == 1) && (strncmp(token, "<", 1) == 0))
	    crosstable.rows[i].alarm_event.operator = TO_LT;
	else if ((oplen == 2) && (strncmp(token, "<=", 2) == 0))
	    crosstable.rows[i].alarm_event.operator = TO_LE;
	else if ((oplen == 6) && (strncmp(token, "RISING", 6) == 0))
	    crosstable.rows[i].alarm_event.operator = TO_RISE;
	else if ((oplen == 7) && (strncmp(token, "FALLING", 7) == 0))
	    crosstable.rows[i].alarm_event.operator = TO_FALL;
	else
            error_log_exit(crosstable.rows[i].number, "unknown operator in trigger expression.");

        /*
         * Two operand expression
         */
        if ((crosstable.rows[i].alarm_event.operator != TO_RISE) && (crosstable.rows[i].alarm_event.operator != TO_FALL)) {
            token = strtok(NULL, " ");
            if (token == NULL)
                error_log_exit(crosstable.rows[i].number, "missing second trigger expression operand.");

            char *endptr = NULL;
            crosstable.rows[i].alarm_event.op2_f = strtof(token, &endptr);

            /* Two operand expression */
            if (endptr == token) {
                /* Operand 2 name too long */
                if (strlen(token) > ID_MAXLEN)
                    error_log_exit(crosstable.rows[i].number, "the name of the trigger expression second operand is too long.");

                if (xtable_ids_check(token) != 0)
                    error_log_exit(crosstable.rows[i].number, "invalid second operand name trigger expression.");

                char **op2 = &(crosstable.rows[i].alarm_event.op2_id);

                /* Store second trigger expression operand. */
                *op2 = strndup(token, ID_MAXLEN);
                if (*op2 == NULL)
                    error_log_exit(crosstable.rows[i].number, "error storing the trigger expression second operand.");

                /* Is the second operand defined? */
                struct st_s *st_op2 = (struct st_s *)bsearch(*op2, st_id.st, st_id.index, sizeof(st_id.st[0]), key_st_id_comp);
                if (st_op2 == NULL)
                    error_log_exit(crosstable.rows[i].number, "second trigger expression operand is not defined.");


                /* Check for operand type compatibility. */
                int opsc = 0;
                enum type_e op1_t = crosstable.rows[st_op1->xref].type;
                enum type_e op2_t = crosstable.rows[st_op2->xref].type;
                int opd_ok = (crosstable.rows[st_op1->xref].decimal == crosstable.rows[st_op2->xref].decimal);

                if ((op1_t == TYPE_BIT) || (op1_t == TYPE_BYTE_BIT) || (op1_t == TYPE_WORD_BIT) || (op1_t == TYPE_DWORD_BIT))
                    opsc = ((op2_t == TYPE_BIT) || (op2_t == TYPE_BYTE_BIT) || (op2_t == TYPE_WORD_BIT) || (op2_t == TYPE_DWORD_BIT));
                else if ((op1_t == TYPE_INT) || (op1_t == TYPE_INTBA) || (op1_t == TYPE_DINT) || (op1_t == TYPE_DINTBADC) || (op1_t == TYPE_DINTCDAB) || (op1_t == TYPE_DINTDCBA))
                    opsc = (
                        opd_ok
                        && ((op2_t == TYPE_INT) || (op2_t == TYPE_INTBA) || (op2_t == TYPE_DINT) || (op2_t == TYPE_DINTBADC) || (op2_t == TYPE_DINTCDAB) || (op2_t == TYPE_DINTDCBA))
                    );
                else if ((op1_t == TYPE_BYTE) || (op1_t == TYPE_UINT) || (op1_t == TYPE_UINTBA) || (op1_t == TYPE_UDINT) || (op1_t == TYPE_UDINTBADC) || (op1_t == TYPE_UDINTCDAB) || (op1_t == TYPE_UDINTDCBA))
                    opsc = (
                        opd_ok
                        && ((op2_t == TYPE_BYTE) || (op2_t == TYPE_UINT) || (op2_t == TYPE_UINTBA) || (op2_t == TYPE_UDINT) || (op2_t == TYPE_UDINTBADC) || (op2_t == TYPE_UDINTCDAB) || (op2_t == TYPE_UDINTDCBA))
                    );
                else if ((op1_t == TYPE_REAL) || (op1_t == TYPE_REALBADC) || (op1_t == TYPE_REALCDAB) || (op1_t == TYPE_REALDCBA))
                    opsc = ((op2_t == TYPE_REAL) || (op2_t == TYPE_REALBADC) || (op2_t == TYPE_REALCDAB) || (op2_t == TYPE_REALDCBA));
                else
                    error_log_exit(crosstable.rows[i].number, "unknown first operand type in trigger expression.");

                /* Incompatible operand types. */
                if (opsc == 0)
                    error_log_exit(crosstable.rows[i].number, "incompatible operand types in trigger expression.");
            }
        }

        /*
         * Clean up.
         */
        if (ae != NULL)
            free(ae);
    }

    return 0;
}

/**
 * Check cross table data for errors and consistency.
 */
static void
xtable_cc(void)
{
    int i = 0;
    for (i = 0; i <= crosstable.index_last; i++) {
        /* Skip empty rows. */
        if (crosstable.rows[i].filled_fields == 0)
            continue;

        char *id = crosstable.rows[i].name;

        /* ID length */
        if (strlen(id) > ID_MAXLEN)
            error_log_exit(crosstable.rows[i].number, "identifier too long.");

        /* ID format */
        if (xtable_ids_check(id) != 0)
            error_log_exit(crosstable.rows[i].number, "invalid identifier.");

        /* Store a valid ID (even duplicates). */
        if (!st_id_append(id, crosstable.rows[i].number, i))
            error_log_exit(crosstable.rows[i].number, "too many symbols.");

        /* Address length */
        if (strlen(crosstable.rows[i].address) > ADDR_MAXLEN)
            error_log_exit(crosstable.rows[i].number, "address too long.");
    }

    /* Check for duplicate IDs. */
    if (duplicate_ids() != 0)
        error_log_exit(0, "duplicate names.");          /* Not reached */

    /* Check alarm and event expressions. */
    if (alarms_and_events_check() != 0)
        error_log_exit(0, "illegal expression.");        /* Not reached */
}



/**
 * Generate the GVL declaration file.
 *
 * @return              0 for success, else failure code.
 */
static int
gvl_gen(void)
{
    if (gvl.filename == NULL)
        gvl.filename = GVL_NAME;

    FILE *gvl_file = fopen(gvl.filename, "wt");
    if (gvl_file == NULL) {
        perror("While opening the GVL file");

        return 1;
    }

    /* Generate the header. */
    fprintf(gvl_file, "VAR_GLOBAL\n");

    int i = 0;
    for (i = 0; i <= crosstable.index_last; i++) {
        fprintf(gvl_file, "\t%s", crosstable.rows[i].name);

        fprintf(gvl_file, " AT %%");

        switch (crosstable.rows[i].behavior) {
            case BEHAV_INPUT:
            case BEHAV_ALARM:
            case BEHAV_EVENT:
                fprintf(gvl_file, "I");

                break;

            case BEHAV_OUTPUT:
                fprintf(gvl_file, "Q");

                break;

            default:
                fprintf(gvl_file, "NONE FIXME");

                break;
        }

        char *plc_type = NULL;
        char *st_type = NULL;
        int decimal = 0;
        switch (crosstable.rows[i].type) {
            case TYPE_BIT:
                plc_type = "X";
                st_type = "BOOL";
                decimal = 1;

                break;

            case TYPE_BYTE_BIT:
                plc_type = "X";
                st_type = "BOOL";
                decimal = 1;

                break;

            case TYPE_WORD_BIT:
                plc_type = "X";
                st_type = "BOOL";
                decimal = 1;

                break;

            case TYPE_DWORD_BIT:
                plc_type = "X";
                st_type = "BOOL";
                decimal = 1;

                break;

            case TYPE_BYTE:
                plc_type = "B";
                st_type = "BYTE";

                break;

            case TYPE_UINT:
            case TYPE_UINTBA:
                plc_type = "W";
                st_type = "UINT";

                break;

            case TYPE_INT:
            case TYPE_INTBA:
                plc_type = "W";
                st_type = "INT";

                break;

            case TYPE_UDINT:
            case TYPE_UDINTBADC:
            case TYPE_UDINTCDAB:
            case TYPE_UDINTDCBA:
                plc_type = "D";
                st_type = "UDINT";

                break;

            case TYPE_DINT:
            case TYPE_DINTBADC:
            case TYPE_DINTCDAB:
            case TYPE_DINTDCBA:
                plc_type = "D";
                st_type = "DINT";

                break;

            case TYPE_REAL:
            case TYPE_REALBADC:
            case TYPE_REALCDAB:
            case TYPE_REALDCBA:
                plc_type = "D";
                st_type = "REAL";

                break;

            default:
                plc_type = "NONE FIXME";
                st_type = "NONE FIXME";

                break;
        }

        fprintf(gvl_file, "%s0.%u", plc_type, crosstable.rows[i].number * REGISTER_SIZE);

        if (decimal != 0)
            fprintf(gvl_file, ".0");

        fprintf(gvl_file, ":%s", st_type);

        fprintf(gvl_file, ";");

        /* Add the comment, if any. */
        if ((crosstable.rows[i].comment != NULL) && (*(crosstable.rows[i].comment) != '\0'))
            fprintf(gvl_file, "\t(* %s *)", crosstable.rows[i].comment);

        fprintf(gvl_file, "\n");
    }

    /* Generate the footer. */
    fprintf(gvl_file, "END_VAR\n");

    fclose(gvl_file);

    return 0;
}

/**
 * Generate the C++ file.
 *
 * @return              0 for success, else failure code.
 */
static int
cpp_gen(void)
{
    if (cpp.source == NULL)
        cpp.source = CPP_NAME;

    /* Open the C++ output file. */
    FILE *cpp_file = fopen(cpp.source, "wt");
    if (cpp_file == NULL) {
        perror("While opening the C++ file");

        return 1;
    }

    /* Generate the header. */
    if (cpp_leading_comments_write(cpp_file))
        return 1;

    fprintf(cpp_file, "\n");

    fprintf(cpp_file, "#include \"crosstable.h\"\n");
    fprintf(cpp_file, "#include \"cross_table_utility.h\"\n");
    fprintf(cpp_file, "#include \"global_var.h\"\n");

    /* Generate variable declarations and methods. */
    int i = 0;
    for (i = 0; i <= crosstable.index_last; i++) {
        char *type = cpp_type_get(&(crosstable.rows[i]));

        /* Start handling new variable. */
        fprintf(cpp_file, "\n/*\n * Variable %s", crosstable.rows[i].name);
        if ((crosstable.rows[i].comment != NULL) && (*(crosstable.rows[i].comment) != '\0'))
            fprintf(cpp_file, "\t[ %s ]", crosstable.rows[i].comment);
        fprintf(cpp_file, "\n */\n");

        /* Generate variable declaration. */
        fprintf(cpp_file, "\n%s %s = 0;\n\n", type, crosstable.rows[i].name);

        /* Generate doWrite() method. */
        fprintf(cpp_file, "int\ndoWrite_%s(%s value)\n{\n\treturn doWrite(ID_%s, &value);\n}\n\n", crosstable.rows[i].name, type, crosstable.rows[i].name);

        /* Generate addWrite() method. */
        fprintf(cpp_file, "int\naddWrite_%s(%s value)\n{\n\treturn addWrite(ID_%s, &value);\n}\n\n", crosstable.rows[i].name, type, crosstable.rows[i].name);

        /* Generate getStatus() method. */
        fprintf(cpp_file, "int\ngetStatus_%s(void)\n{\n\treturn getStatus(ID_%s);\n}\n\n", crosstable.rows[i].name, crosstable.rows[i].name);
    }

    /* Generate update_all() method. */
    fprintf(cpp_file, "\nint\nupdate_all(void)\n{\n\tint retval = 0;\n\n");
    for (i = 0; i <= crosstable.index_last; i++)
        fprintf(cpp_file, "\tretval += readFromDb(ID_%s, &%s);\n", crosstable.rows[i].name, crosstable.rows[i].name);
    fprintf(cpp_file, "\n\treturn retval;\n}\n");

    fclose(cpp_file);

    return 0;
}

/**
 * Generate the C++ header file.
 *
 * @return              0 for success, else failure code.
 */
static int
cpp_h_gen(void)
{
    if (cpp.include == NULL)
        cpp.include = CPP_H_NAME;

    /* Open the C++ header output file. */
    FILE *cpp_h_file = fopen(cpp.include, "wt");
    if (cpp_h_file == NULL) {
        perror("While opening the C++ file");

        return 1;
    }

    /* Generate the header. */
    if (cpp_leading_comments_write(cpp_h_file))
        return 1;

    fprintf(cpp_h_file, "\n");

    fprintf(cpp_h_file, "#ifndef CROSSTABLE_H__\n");
    fprintf(cpp_h_file, "#define CROSSTABLE_H__\n");

    fprintf(cpp_h_file, "\n");

    fprintf(cpp_h_file, "#ifdef __cplusplus\n");
    fprintf(cpp_h_file, "extern \"C\" {\n");
    fprintf(cpp_h_file, "#endif\n");

    fprintf(cpp_h_file, "\n");

    fprintf(cpp_h_file, "#include <sys/types.h>\n");

    fprintf(cpp_h_file, "\n");

    /* Generate method prototypes. */
    int i = 0;
    for (i = 0; i <= crosstable.index_last; i++) {
        char *type = cpp_type_get(&(crosstable.rows[i]));

        fprintf(cpp_h_file, "\n#define ID_%s %d\n", crosstable.rows[i].name, crosstable.rows[i].number);

        fprintf(cpp_h_file, "extern %s %s;", type, crosstable.rows[i].name);
        if ((crosstable.rows[i].comment != NULL) && (*(crosstable.rows[i].comment) != '\0'))
            fprintf(cpp_h_file, "\t/* %s */", crosstable.rows[i].comment);
        fprintf(cpp_h_file, "\n");

        fprintf(cpp_h_file, "int doWrite_%s(%s value);\n", crosstable.rows[i].name, type);

        fprintf(cpp_h_file, "int addWrite_%s(%s value);\n", crosstable.rows[i].name, type);

        fprintf(cpp_h_file, "int getStatus_%s(void);\n", crosstable.rows[i].name);
    }

    fprintf(cpp_h_file, "\n");

    fprintf(cpp_h_file, "#ifdef __cplusplus\n");
    fprintf(cpp_h_file, "}\n");
    fprintf(cpp_h_file, "#endif\n");
    fprintf(cpp_h_file, "#endif\n");

    fclose(cpp_h_file);

    return 0;
}



static void
usage(char *pn)
{
    fprintf(stderr, "Usage: %s <options>\n", pn);
    fprintf(stderr, "\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -c <file name>   - input cross table file name (CSV format)\n");
    fprintf(stderr, "  -g <file name>   - output declaration file name (ST format)\n");
    fprintf(stderr, "  -i <file name>   - output header file name (C++ format)\n");
    fprintf(stderr, "  -s <file name>   - output source file name (C++ format)\n");
    fprintf(stderr, "  -h               - print usage\n");
}

int
main(int argc, char *argv[])
{
    struct csv_parser p;

    /* Initialize the parser. */
    if (csv_init(&p, 0) != 0)
        error_log_exit(0, "cannot initialize the CSV parser.");

    csv_set_delim(&p, ';');
    csv_set_space_func(&p, is_space);
    csv_set_term_func(&p, is_term);

    /* Parse command line arguments. */
    int o = 0;
    unsigned char options = 0;
    while ((o = getopt(argc, argv, "c:g:hi:s:S")) != -1)
        switch (o) {
            case 'c':           /* CSV input file name */
                crosstable.filename = optarg;

                break;

            case 'g':           /* GVL output file name */
                gvl.filename = optarg;

                break;

            case 'i':           /* C++ output include file name */
                cpp.include = optarg;

                break;

            case 's':           /* C++ output source file name */
                cpp.source = optarg;

                break;

            case 'h':
            default:
                usage(argv[0]);

                exit(EXIT_FAILURE);

                break;
        }

    /* Sanity checks */
    if (crosstable.filename == NULL)
        error_log_exit(0, "no cross table file name.");

    FILE *fp = fopen(crosstable.filename, "rb");
    if (fp == NULL)
        perror_log_exit(0, "cannot open cross table file.");

    /* Set parser options. */
    options |= CSV_STRICT | CSV_STRICT_FINI | CSV_APPEND_NULL;
    csv_set_opts(&p, options);

    row_init(&row);

    /* Parse the file. */
    char buf[FIELD_MAX_LENGTH];
    size_t bytes_read;
    while ((bytes_read = fread(buf, 1, FIELD_MAX_LENGTH, fp)) > 0)
        if (csv_parse(&p, buf, bytes_read, cb_field, cb_row, &row) != bytes_read)
            cperror_log_exit(&p, crosstable.row_crt + 1, "while parsing the cross table");

    csv_fini(&p, cb_field, cb_row, &row);

    if (ferror(fp))
        perror_log_exit(crosstable.row_crt, "while reading cross table file");

    fclose(fp);

    /* Check cross table for errors and consistency. */
    st_id_init();
    xtable_cc();

    /* Generate structured text IEC 61131-3 declarations. */
    if (gvl_gen() != 0)
        exit(EXIT_FAILURE);

    /* Generate C++ header file with declarations. */
    if (cpp_h_gen() != 0)
        exit(EXIT_FAILURE);

    /* Generate C++ code and variable declarations. */
    if (cpp_gen() != 0)
        exit(EXIT_FAILURE);

    /* Cleanup. */
    csv_free(&p);

    exit(EXIT_SUCCESS);
}
