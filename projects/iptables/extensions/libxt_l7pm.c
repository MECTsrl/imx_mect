/*
 * Shared library add-on to iptables to add layer 7 matching support with
 * pattern match engine.
 *
 * Copyright (C) 2008 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Based on libxt_layer7.c by Matthew Strait <quadong@users.sf.net>,
 * Oct 2003-Aug 2008.
 * http://l7-filter.sf.net
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>

#include <iptables.h>
#include <linux/netfilter_ipv4/ipt_l7pm.h>

#define MAX_FN_LEN 256
#define MAX_PROTO_INFO  4096
#define MAX_LINE_SIZE 1024
#define MODULENAME "l7pm"
static struct ipt_l7pm_info l7pm_info[MAX_PROTO_INFO];
static int l7pm_set = 0xb7;     // default set value for l7pm
static int l7pm_info_num = 0;

static char l7ini[MAX_FN_LEN] = "\0";

/* Function which prints out usage message. */
static void help(void)
{
	printf(
	"L7PM match v%s options:\n"
	"--l7ini <inifile>  : pattern ini file name\n"
	"                       (--l7ini must be specified before --l7proto if used!)\n"
	"--l7proto [!] <name> : Match the protocol defined in ini file\n",
	XTABLES_VERSION);
	fputc('\n', stdout);
}

static struct option opts[] = {
	{ .name = "l7proto", .has_arg = 1, .flag = 0, .val = '1' },
	{ .name = "l7ini",   .has_arg = 1, .flag = 0, .val = '2' },
	{ .name = 0 }
};

static int parse_protocol_ini(void)
{
    char * file = NULL;
    char _line[MAX_LINE_SIZE];
    FILE *f;
    enum {session_none, session_set, session_tags} session = session_none;

    if(l7pm_info_num) {
        // already parsed the ini file
        return 1;
    }
    if(strlen(l7ini) > 0) {
        file = l7ini;
    } else {
        file = "/etc/l7-protocols/layer7.ini";
    }
    f = fopen(file, "r");
    if(!f) {
        exit_error(OTHER_PROBLEM, "Couldn't find a pattern definition file for %s.\n", file);
        return 0;
    }
    // set "unknown" protocol
    strncpy(l7pm_info[l7pm_info_num].protocol, "unknown", MAX_PROTOCOL_LEN);
    l7pm_info[l7pm_info_num].tag = 0;
    l7pm_info[l7pm_info_num].set = l7pm_set;
    l7pm_info[l7pm_info_num].invert = 0;
    l7pm_info_num++;
    // parse ini file
    while(fgets(_line, MAX_LINE_SIZE, f) == _line) {
        char *comment = strchr(_line, '#');
        if(comment) {
            *comment = 0;
        }
        if(strstr(_line, "[SET]")) {
            session = session_set;
        } else if(strstr(_line, "[PATTERN_TAGS]")) {
            session = session_tags;
        } else {
            char *assign = strchr(_line, '=');
            char *name, *value;
            if(assign) {
                *assign = 0;
                name = _line;
                value = assign+1;
                if(session == session_set) {
                    if(strcmp("set", name) == 0) {
                        l7pm_set = strtoul(value, 0, 0);
                    } else {
                        exit_error(OTHER_PROBLEM, "%s: unknown value in [SET] session.\n", file);
                        return 0;
                    }
                } else if(session == session_tags) {
                    strncpy(l7pm_info[l7pm_info_num].protocol, name, MAX_PROTOCOL_LEN);
                    l7pm_info[l7pm_info_num].tag = strtoul(value, 0, 0);
                    l7pm_info[l7pm_info_num].set = l7pm_set;
                    l7pm_info[l7pm_info_num].invert = 0;
                    l7pm_info_num++;
                } else {
                    exit_error(OTHER_PROBLEM, "%s: parse error.\n", file);
                    return 0;
                }
            }
        }
    }
    return 1;
}

static void
parse_l7pm_protocol(const unsigned char *s, struct ipt_l7pm_info *info)
{
    int i;
    parse_protocol_ini();
    for(i = 0; i < l7pm_info_num; i++) {
        if(strncasecmp((const char *)s,l7pm_info[i].protocol, MAX_PROTOCOL_LEN) == 0) {
            strcpy(info->protocol, l7pm_info[i].protocol);
            info->tag = l7pm_info[i].tag;
            info->set = l7pm_info[i].set;
            info->invert = l7pm_info[i].invert;
            break;
        }
    }
    if(i == l7pm_info_num) {
        exit_error(OTHER_PROBLEM, "%s: can not find protocol.\n", s);
    }
}

/* Function which parses command options; returns true if it ate an option */
static int parse(int c, char **argv, int invert, unsigned int *flags,
      const void *entry, struct xt_entry_match **match)
{
	struct ipt_l7pm_info *l7pminfo =
		(struct ipt_l7pm_info *)(*match)->data;

	switch (c) {
	case '1':
		check_inverse(optarg, &invert, &optind, 0);
		parse_l7pm_protocol((const unsigned char*)argv[optind-1], l7pminfo);
		if (invert)
			l7pminfo->invert = 1;
		*flags = 1;
		break;

	case '2':
		/* not going to use this, but maybe we need to strip a ! anyway (?) */
		check_inverse(optarg, &invert, &optind, 0);

		if(strlen(argv[optind-1]) >= MAX_FN_LEN)
			exit_error(PARAMETER_PROBLEM, "file name too long\n");

		strncpy(l7ini, argv[optind-1], MAX_FN_LEN);

		*flags = 1;
		break;

	default:
		return 0;
	}

	return 1;
}

/* Final check; must have specified --l7proto */
static void final_check(unsigned int flags)
{
	if (!flags)
		exit_error(PARAMETER_PROBLEM,
			   "l7pm match: You must specify `--l7proto'");
}

static void print_protocol(char s[], int invert, int numeric)
{
	fputs("l7proto ", stdout);
	if (invert) fputc('!', stdout);
	printf("%s ", s);
}

/* Prints out the matchinfo. */
static void print(const struct ipt_ip *ip,
      const struct xt_entry_match *match,
      int numeric)
{
	printf("l7pm ");

	print_protocol(((struct ipt_l7pm_info *)match->data)->protocol,
		  ((struct ipt_l7pm_info *)match->data)->invert, numeric);
}
/* Saves the union ipt_matchinfo in parsable form to stdout. */
static void save(const void  *ip, const struct xt_entry_match *match)
{
        const struct ipt_l7pm_info *info =
            (const struct ipt_l7pm_info*) match->data;

        printf("--l7proto %s%s ", (info->invert)   ? "! ": "", info->protocol);
}

static struct xtables_match l7pm = {
    .name          = MODULENAME,
    .version       = XTABLES_VERSION,
    .size          = XT_ALIGN(sizeof(struct ipt_l7pm_info)),
    .userspacesize = XT_ALIGN(sizeof(struct ipt_l7pm_info)),
    .help          = &help,
    .parse         = &parse,
    .final_check   = &final_check,
    .print         = &print,
    .save          = &save,
    .extra_opts    = opts
};

void _init(void)
{
	xtables_register_match(&l7pm);
}
