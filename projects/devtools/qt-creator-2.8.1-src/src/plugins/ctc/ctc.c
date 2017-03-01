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

#define FIELD_MAX_LENGTH        4096
#define CROSSTABLE_DEF          10000

/* All crosstable types */
enum type_e {
    TYPE_NONE = 0,
    TYPE_BIT,
    TYPE_BYTE_BIT,
    TYPE_WORD_BIT,
    TYPE_DWORD_BIT,
    TYPE_BYTE,
    TYPE_UINT,
    TYPE_UINTBA,
    TYPE_INT,
    TYPE_INTBA,
    TYPE_UDINT,
    TYPE_UDINTBADC,
    TYPE_UDINTCDAB,
    TYPE_UDINTDCBA,
    TYPE_DINT,
    TYPE_DINTBADC,
    TYPE_DINTCDAB,
    TYPE_DINTDCBA,
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

/* Full crosstable row */
struct row_s {
    int priority;
    char update;
    char name[17];
    enum type_e type;
    int decimal;
    enum protocol_e protocol;
    char address[16];
    int port;
    int node_id;
    int reg;
    int block;
    char *comment;
    enum behav_e behavior;

    int number;

    int filled_fields;          /* Data in any field? */
};

/*
 * Variables
 */

static struct row_s row;

static struct crosstable_s {
    struct row_s *rows;         /* Cross table representation */
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



/* Local function prototypes */
static void row_init(struct row_s *row);
static int crosstable_row_add(struct row_s *row);
static enum type_e type_get(char *type);
static char *cpp_type_get(struct row_s *row);
static int cpp_leading_comments_write(FILE *file);
static enum protocol_e protocol_get(char *protocol);
static enum behav_e behav_get(char *behavior);
static void cb_field(void *s, size_t len, void *data);
static void cb_row(int c, void *data);
static int is_space(unsigned char c);
static int is_term(unsigned char c);
static int gvl_gen(void);
static int cpp_gen(void);
static int cpp_h_gen(void);
static void usage(char *pn);



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
    if ((crosstable.index_last + 1) >= crosstable.size) {
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
    else if (strcmp(protocol, "RTU") == 0)
        return PROTO_RTU;
    else if (strcmp(protocol, "TCP") == 0)
        return PROTO_TCP;
    else if (strcmp(protocol, "TCPRTU") == 0)
        return PROTO_TCPRTU;
    else if (strcmp(protocol, "CANOPEN") == 0)
        return PROTO_CANOPEN;
    else if (strcmp(protocol, "RTU_SRV") == 0)
        return PROTO_RTU_SRV;
    else if (strcmp(protocol, "TCP_SRV") == 0)
        return PROTO_TCP_SRV;
    else if (strcmp(protocol, "TCPRTU_SRV") == 0)
        return PROTO_TCPRTU_SRV;
    else if (strcmp(protocol, "MECT") == 0)
        return PROTO_MECT;
    else
        return PROTO_NONE;
}

/**
 * Return the code correspomding to the given behavior.
 *
 * @param behavior      behavior type.
 *
 * @return              code associated to type.
 */
static enum behav_e
behav_get(char *behavior)
{
    if (behavior == NULL)
        return BEHAV_NONE;

    if (strcmp(behavior, "[RO]") == 0)
        return BEHAV_INPUT;
    else if (strcmp(behavior, "[RW]") == 0)
        return BEHAV_OUTPUT;
    else if (strcmp(behavior, "[AL ") == 0)
        return BEHAV_ALARM;
    else if (strcmp(behavior, "[EV ") == 0)
        return BEHAV_EVENT;
    else
        return BEHAV_NONE;
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
                ((struct row_s *)data)->comment = strdup(buf);
                dbg_printf("Comment %s\n", ((struct row_s *)data)->comment);

            break;

            case 12:
                ((struct row_s *)data)->behavior = behav_get(buf);
                dbg_printf("Behavior %d\n", ((struct row_s *)data)->behavior);

            break;

            default:
                fprintf(stderr, "Unknown field index %d.\nAborting.\n", crosstable.field_crt);

                exit(1);

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

        fprintf(gvl_file, ";\n");
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
        fprintf(cpp_file, "\n/*\n * Variable %s\n */\n", crosstable.rows[i].name);

        /* Generate variable declaration. */
        fprintf(cpp_file, "\n%s %s = 0;\n\n", type, crosstable.rows[i].name);

        /* Generate doWrite() method. */
        fprintf(cpp_file, "int\ndoWrite_%s(%s value)\n{\n\treturn ioComm->sendUdpWriteCmd(ID_%s, &value);\n}\n\n", crosstable.rows[i].name, type, crosstable.rows[i].name);

        /* Generate addWrite() method. */
        fprintf(cpp_file, "int\naddWrite_%s(%s value)\n{\n\treturn ioComm->sendUdpWriteCmd(ID_%s, &value);\n}\n\n", crosstable.rows[i].name, type, crosstable.rows[i].name);

        /* Generate getStatus() method. */
        fprintf(cpp_file, "int\ngetStatus_%s(void)\n{\n\treturn ioComm->getStatusVar(ID_%s);\n}\n\n", crosstable.rows[i].name, crosstable.rows[i].name);
    }

    /* Generate update_all() method. */
    fprintf(cpp_file, "\nint\nupdate_all(void)\n{\n\tint retval = 0;\n\n");
    for (i = 0; i <= crosstable.index_last; i++)
        fprintf(cpp_file, "\tretval += ioComm->readUdpReply(ID_%s, &%s);\n", crosstable.rows[i].name, crosstable.rows[i].name);
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

        fprintf(cpp_h_file, "extern %s %s;\n", type, crosstable.rows[i].name);

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
    fprintf(stderr, "  -S               - strict CSV parse\n");
    fprintf(stderr, "  -h               - print usage\n");
}

int
main(int argc, char *argv[])
{
    struct csv_parser p;

    /* Initialize the parser. */
    if (csv_init(&p, 0) != 0) {
        fprintf(stderr, "Failed to initialize the CSV parser.\n");

        exit(EXIT_FAILURE);
    }

    csv_set_delim(&p, ';');
    csv_set_space_func(&p, is_space);
    csv_set_term_func(&p, is_term);

    /* Parse command line arguments. */
    int o = 0;
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

            case 'S':           /* Strict CSV parse */
                csv_set_opts(&p, CSV_STRICT);

                break;

            case 'h':
            default:
                usage(argv[0]);

                exit(EXIT_FAILURE);

                break;
        }

    /* Sanity checks */
    if (crosstable.filename == NULL) {
        fprintf(stderr, "%s: cross table input file not specified.\n", argv[0]);

        usage(argv[0]);

        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(crosstable.filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open %s: %s\n", crosstable.filename, strerror(errno));

        exit(EXIT_FAILURE);
    }

    row_init(&row);

    /* Parse the file. */
    char buf[FIELD_MAX_LENGTH];
    size_t bytes_read;
    while ((bytes_read = fread(buf, 1, FIELD_MAX_LENGTH, fp)) > 0)
        if (csv_parse(&p, buf, bytes_read, cb_field, cb_row, &row) != bytes_read)
            fprintf(stderr, "Error while parsing file: %s\n", csv_strerror(csv_error(&p)));

    csv_fini(&p, cb_field, cb_row, &row);

    if (ferror(fp))
        fprintf(stderr, "Error while reading file %s\n", crosstable.filename);

    fclose(fp);


    if (gvl_gen() != 0)
        exit(EXIT_FAILURE);

    if (cpp_h_gen() != 0)
        exit(EXIT_FAILURE);

    if (cpp_gen() != 0)
        exit(EXIT_FAILURE);

    /* Cleanup. */
    csv_free(&p);

    exit(EXIT_SUCCESS);
}
