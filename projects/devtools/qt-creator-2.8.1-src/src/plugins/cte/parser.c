/*
 * Filename: dataImpl.c ridotto preso da ATCMcontrol_RunTimeSystem
 */


/* ----  Local Defines:   ----------------------------------------------------- */
#define TRUE  1
#define FALSE 0
#define LINESIZE 1024
#define ctCOLS 13
#define SEMICOL ";"
/* ----  Includes:	 ---------------------------------------------------------- */

#include <ctype.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

uint16_t lastAlarmEvent = 0;
struct Alarms ALCrossTable[1 + DimAlarmsCT]; // campi sono riempiti a partire dall'indice 1

const char *fieldbusName[] = {"PLC",
                              "RTU",
                              "TCP",
                              "TCPRTU",
                              "CANOPEN",
                              "MECT",
                              "RTU_SRV",
                              "TCP_SRV",
                              "TCPRTU_SRV" };

const char *varTypeName[] = {	"BIT",
                                "BYTE_BIT",
                                "WORD_BIT",
                                "DWORD_BIT",
                                "BYTE",
                                "UINT",
                                "UINTBA",
                                "INT",
                                "INTBA",
                                "REAL",
                                "REALDCBA",
                                "REALCDAB",
                                "REALBADC",
                                "UDINT",
                                "UDINTDCBA",
                                "UDINTCDAB",
                                "UDINTBADC",
                                "DINT",
                                "DINTDCBA",
                                "DINTCDAB",
                                "DINTBADC",
                                "UNKNOWN" 	};

const char *updateTypeName[] = {"H",
                                "P",
                                "S",
                                "F",
                                "V",
                                "X" };

const char *logic_operators[] = {">",
                                 ">=",
                                 "<",
                                 "<=",
                                 "==",
                                 "!=",
                                 "RISING EDGE",
                                 "FALLING EDGE" };



// PRODUCT_NAMES <-- PRODUCT_ID
const char *product_name[] = {
    /*00*/ "AnyTPAC",
    /*01*/ "TP1043_01_A",
    /*02*/ "TP1043_01_B",
    /*03*/ "TP1043_01_C",
    /*04*/ "TP1057_01_A",
    /*05*/ "TP1057_01_B",
    /*06*/ "TP1070_01_A",
    /*07*/ "TP1070_01_B",
    /*08*/ "TP1070_01_C",
    /*09*/ "TP1070_01_D",
    /*10*/ "TPAC1006",
    /*11*/ "TPAC1007_03",
    /*12*/ "TPAC1007_04_AA",
    /*13*/ "TPAC1007_04_AB",
    /*14*/ "TPAC1007_04_AC",
    /*15*/ "TPAC1007_LV",
    /*16*/ "TPAC1008_01",
    /*17*/ "TPAC1008_02_AA",
    /*18*/ "TPAC1008_02_AB",
    /*19*/ "TPAC1008_02_AC",
    /*20*/ "TPAC1008_02_AD",
    /*21*/ "TPAC1008_02_AE",
    /*22*/ "TPAC1008_02_AF"
};

/*      Mappatura tra Costanti di Tipo, valori Letti e scritti in file CSV
        Const		Scrittura  		Lettura
        BIT = 0,    "BIT", 	 		"BIT"
        BYTE_BIT,   "BYTE_BIT",		"BYTE_BIT"
        WORD_BIT,   "WORD_BIT",		"WORD_BIT"
        DWORD_BIT,  "DWORD_BIT",    "DWORD_BIT"
        UINT8,      "BYTE",         "BYTE"
        UINT16,     "UINT",			"UINT", "UINTAB"
        UINT16BA,   "UINTBA",		"UINTBA"
        INT16,      "INT",			"INT", "INTAB"
        INT16BA,    "INTBA",        "INTBA"
        REAL,       "REAL",         "REAL", "FABCD"
        REALDCBA,   "REALDCBA",     "REALDCBA", "FDCBA"
        REALCDAB,   "REALCDAB",     "REALCDAB", "FCDAB"
        REALBADC,   "REALBADC",     "REALBADC", "FBADC"
        UDINT,      "UDINT", 		"UDINT", "UDINTABCD",
        UDINTDCBA,  "UDINTDCBA",    "UDINTDCBA"
        UDINTCDAB,  "UDINTCDAB",    "UDINTCDAB"
        UDINTBADC,  "UDINTBADC",    "UDINTBADC"
        DINT,       "DINT",         "DINT", "DINTABCD"
        DINTDCBA,   "DINTDCBA",     "DINTDCBA"
        DINTCDAB,   "DINTCDAB",		"DINTCDAB"
        DINTBADC,   "DINTBADC",     "DINTBADC"
        UNKNOWN     "UNKNOWN";		---------
*/





char *strtok_csv(char *string, const char *separators, char **savedptr)
{
    char *p, *s;

    if (separators == NULL || savedptr == NULL) {
        return NULL;
    }
    if (string == NULL) {
        p = *savedptr;
        if (p == NULL) {
            return NULL;
        }
    } else {
        p = string;
    }

    s = strstr(p, separators);
    if (s == NULL) {
        *savedptr = NULL;
        return p;
    }
    *s = 0;
    *savedptr = s + 1;

    // remove spaces at head
    while (p < s && isspace(*p)) {
        ++p;
    }
    // remove spaces at tail
    --s;
    while (s > p && isspace(*s)) {
        *s = 0;
        --s;
    }
    return p;
}

uint32_t str2ipaddr(char *str)
{
    uint32_t ipaddr = 0;
    char buffer[17];
    char *s, *r;
    int i;

    strncpy(buffer, str, 17);
    buffer[16] = 0;

    s = strtok_csv(buffer, ".", &r);
    for (i = 3; i >= 0; --i) {
        if (s == NULL) {
            return 0x00000000;
        }
        ipaddr += (strtoul(s, NULL, 10) % 255) << (i * 8);
        s = strtok_csv(NULL, ".", &r);
    }
    return ipaddr;
}

char *ipaddr2str(uint32_t ipaddr, char *buffer)
{
    if (buffer != NULL) {
        register uint8_t a, b, c, d;
        a = (ipaddr & 0xFF000000) >> 24;
        b = (ipaddr & 0x00FF0000) >> 16;
        c = (ipaddr & 0x0000FF00) >> 8;
        d = (ipaddr & 0x000000FF);
        sprintf(buffer, "%u.%u.%u.%u", a, b, c, d);
    }
    return buffer;
}
/*
 * Public domain strtok_r() by Charlie Gordon
 *
 * From comp.lang.c  9/14/2007
 *
 * http://groups.google.com/group/comp.lang.c/msg/2ab1ecbb86646684
 *
 * Declaration that it's public domain:
 *     http://groups.google.com/group/comp.lang.c/msg/7c7b39328fefab9c
 */
#ifndef strtok_r
char *strtok_r(char *str, const char *delim, char **nextp)
{
    char *ret;

    if (str == NULL)
        str = *nextp;

    str += strspn(str, delim);

    if (*str == '\0')
        return NULL;

    ret = str;

    str += strcspn(str, delim);

    if (*str)
        *str++ = '\0';

    *nextp = str;

    return ret;
}
#endif

static int newAlarmEvent(int isAlarm, uint16_t addr, char *expr, size_t len)
{
    char *p, *r;

    if (lastAlarmEvent >= DimAlarmsCT) {
        return -1;
    }
    ++lastAlarmEvent;
    ALCrossTable[lastAlarmEvent].ALType = (isAlarm ? Alarm : Event);
    ALCrossTable[lastAlarmEvent].TagAddr = addr;

    p = strtok_r(expr, " ]", &r);
    if (p == NULL) {
        goto exit_error;
    }
    strncpy(ALCrossTable[lastAlarmEvent].ALSource, p, MAX_IDNAME_LEN);

    p = strtok_r(NULL, " ]", &r);
    if (p == NULL) {
        goto exit_error;
    }
    // Vengono testati prima gli operatori a 2 caratteri...
    if (strncmp(p, logic_operators[oper_greater_eq], 2) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = oper_greater_eq;
    } else if (strncmp(p, logic_operators[oper_greater], 1) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = oper_greater;
    } else if (strncmp(p, logic_operators[oper_smaller_eq], 2) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = oper_smaller_eq;
    } else if (strncmp(p, logic_operators[oper_smaller], 1) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = oper_smaller;
    } else if (strncmp(p, logic_operators[oper_equal], 2) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = oper_equal;
    } else if (strncmp(p, logic_operators[oper_not_equal], 2) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = oper_not_equal;
    } else if (strncmp(p, logic_operators[oper_rising], 6) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = oper_rising;
    } else if (strncmp(p, logic_operators[oper_falling], 7) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = oper_falling;
    } else {
        goto exit_error;
    }
    ALCrossTable[lastAlarmEvent].ALCompareVar[0] = 0;
    if (ALCrossTable[lastAlarmEvent].ALOperator != oper_falling && ALCrossTable[lastAlarmEvent].ALOperator != oper_rising) {
        char *s;
        float f;

        p = strtok_r(NULL, " ]", &r);
        if (p == NULL) {
            goto exit_error;
        }
        f = strtof(p, &s);
        if (s == p) {
            // identifier (check later on)
            strncpy(ALCrossTable[lastAlarmEvent].ALCompareVar, p, MAX_IDNAME_LEN);
            ALCrossTable[lastAlarmEvent].ALCompareVal = 0.0;
        } else {
            // number
            ALCrossTable[lastAlarmEvent].ALCompareVar[0] = 0;
            ALCrossTable[lastAlarmEvent].ALCompareVal = f;
            // memcpy(&ALCrossTable[lastAlarmEvent].ALCompareVal, &f, sizeof(uint32_t));
        }
    }
    return 0;

exit_error:
    --lastAlarmEvent;
    return -1;
}

static uint16_t tagAddr(char *tag, struct CrossTableRecord *CrossTable)
{
    uint16_t addr;

    for (addr = 1; addr <= DimCrossTable; ++addr) {
        if (strncmp(tag, CrossTable[addr].Tag, MAX_IDNAME_LEN) == 0) {
            return addr;
        }
    }
    return 0;
}


int LoadXTable(char *crossTableFile, struct CrossTableRecord *CrossTable)
{
    uint32_t addr, indx;
    int ERR = FALSE;
    FILE *xtable = NULL;
    char *cPosComment = 0;

    // init tables
    for (addr = 1; addr <= DimCrossTable; ++addr) {
        CrossTable[addr].Enable = 0;
        CrossTable[addr].UsedEntry = 0;
        CrossTable[addr].Plc = FALSE;
        CrossTable[addr].Tag[0] = 0;
        CrossTable[addr].VarType = UNKNOWN;
        CrossTable[addr].Decimal = 0;
        CrossTable[addr].Protocol = PLC;
        CrossTable[addr].IPAddress = 0x00000000;
        CrossTable[addr].Port = 0;
        CrossTable[addr].NodeId = 0;
        CrossTable[addr].Offset = 0;
        CrossTable[addr].Block = 0;
        CrossTable[addr].BlockSize = 0;
        CrossTable[addr].Behavior = -1;
        CrossTable[addr].OldVal = 0;
        CrossTable[addr].device = 0xffff;
        CrossTable[addr].node = 0xffff;
        // New Elements used for Alarms
        CrossTable[addr].usedInAlarmsEvents = 0;
        CrossTable[addr].ALType = -1;
        CrossTable[addr].ALSource[0] = 0;
        CrossTable[addr].ALOperator = -1;
        CrossTable[addr].ALCompareVar[0] = 0;
        CrossTable[addr].ALCompareVal = 0;
    }
    lastAlarmEvent = 0;
    for (addr = 0; addr <= DimAlarmsCT; ++addr) {
        ALCrossTable[addr].ALType = FALSE;
        ALCrossTable[addr].ALSource[0] = '\0';
        ALCrossTable[addr].ALCompareVar[0] = '\0';
        ALCrossTable[addr].TagAddr = 0;
        ALCrossTable[addr].SourceAddr = 0;
        ALCrossTable[addr].CompareAddr = 0;
        ALCrossTable[addr].ALCompareVal = 0;
        ALCrossTable[addr].ALOperator = 0;
        ALCrossTable[addr].ALFilterTime = 0;
        ALCrossTable[addr].ALFilterCount = 0;
        ALCrossTable[addr].comparison = 0;
    }

    // open file
    fprintf(stderr, "loading '%s' ...", crossTableFile);
    xtable = fopen(crossTableFile, "r");
    if (xtable == NULL)  {
        ERR = TRUE;
        goto exit_function;
    }

    // read loop
    for (addr = 1; addr <= DimCrossTable; ++ addr) {
        char row[LINESIZE], *p, *r;

        if (fgets(row, LINESIZE, xtable) == NULL) {
            CrossTable[addr].Error = 1;
            // no ERR = TRUE;
            continue;
        }

        // Enable {0,1,2,3}
        p = strtok_csv(row, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        CrossTable[addr].Enable = atoi(p);
        // skip empty or disabled variables
        if (CrossTable[addr].Enable == 0) {
            CrossTable[addr].Error = 1;
        }

        // Plc {H,P,S,F}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        // Empty Line
        if (strlen(p) == 0)
            continue;

        switch (p[0]) {
        case 'H':
            CrossTable[addr].Plc = Htype;
            break;
        case 'P':
            CrossTable[addr].Plc = Ptype;
            break;
        case 'S':
            CrossTable[addr].Plc = Stype;
            break;
        case 'F':
            CrossTable[addr].Plc = Ftype;
            break;
        case 'V':
            CrossTable[addr].Plc = Vtype;
            break;
        case 'X':
            CrossTable[addr].Plc = Xtype;
            break;
        default:
            ERR = TRUE;
        }
        if (ERR) {
            break;
        }

        // Tag {identifier}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        strncpy(CrossTable[addr].Tag, p, MAX_IDNAME_LEN);
        // Marked Entry as used
        if (strlen(CrossTable[addr].Tag) > 0)
            CrossTable[addr].UsedEntry = 1;

        // Types {UINT, UDINT, DINT, FDCBA, ...}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        if (strcmp(p, "BIT") == 0) {
            CrossTable[addr].VarType = BIT;
        } else if (strcmp(p, "BYTE") == 0) {
            CrossTable[addr].VarType = UINT8;
        } else if (strcmp(p, "BYTE_BIT") == 0) {
            CrossTable[addr].VarType = BYTE_BIT;
        } else if (strcmp(p, "WORD_BIT") == 0) {
            CrossTable[addr].VarType = WORD_BIT;
        } else if (strcmp(p, "DWORD_BIT") == 0) {
            CrossTable[addr].VarType = DWORD_BIT;
        } else if (strcmp(p, "UINT") == 0) {
            CrossTable[addr].VarType = UINT16;
        } else if (strcmp(p, "UINTBA") == 0) {
            CrossTable[addr].VarType = UINT16BA;
        } else if (strcmp(p, "INT") == 0) {
            CrossTable[addr].VarType = INT16;
        } else if (strcmp(p, "INTBA") == 0) {
            CrossTable[addr].VarType = INT16BA;
        } else if (strcmp(p, "UDINT") == 0) {
            CrossTable[addr].VarType = UDINT;
        } else if (strcmp(p, "UDINTDCBA") == 0) {
            CrossTable[addr].VarType = UDINTDCBA;
        } else if (strcmp(p, "UDINTCDAB") == 0) {
            CrossTable[addr].VarType = UDINTCDAB;
        } else if (strcmp(p, "UDINTBADC") == 0) {
            CrossTable[addr].VarType = UDINTBADC;
        } else if (strcmp(p, "DINT") == 0) {
            CrossTable[addr].VarType = DINT;
        } else if (strcmp(p, "DINTDCBA") == 0) {
            CrossTable[addr].VarType = DINTDCBA;
        } else if (strcmp(p, "DINTCDAB") == 0) {
            CrossTable[addr].VarType = DINTCDAB;
        } else if (strcmp(p, "DINTBADC") == 0) {
            CrossTable[addr].VarType = DINTBADC;
        } else if (strcmp(p, "REAL") == 0) {
            CrossTable[addr].VarType = REAL;
        } else if (strcmp(p, "REALDCBA") == 0) {
            CrossTable[addr].VarType = REALDCBA;
        } else if (strcmp(p, "REALCDAB") == 0) {
            CrossTable[addr].VarType = REALCDAB;
        } else if (strcmp(p, "REALBADC") == 0) {
            CrossTable[addr].VarType = REALBADC;

        } else if (strcmp(p, "UINTAB") == 0) {
            CrossTable[addr].VarType = UINT16; // bUINT16ackward compatibility
        } else if (strcmp(p, "INTAB") == 0) {
            CrossTable[addr].VarType = INT16; // backward compatibility
        } else if (strcmp(p, "UDINTABCD") == 0) {
            CrossTable[addr].VarType = UDINT; // backward compatibility
        } else if (strcmp(p, "DINTABCD") == 0) {
            CrossTable[addr].VarType = DINT; // backward compatibility
        } else if (strcmp(p, "FDCBA") == 0) {
            CrossTable[addr].VarType = REALDCBA; // backward compatibility
        } else if (strcmp(p, "FCDAB") == 0) {
            CrossTable[addr].VarType = REALCDAB; // backward compatibility
        } else if (strcmp(p, "FABCD") == 0) {
            CrossTable[addr].VarType = REAL; // backward compatibility
        } else if (strcmp(p, "FBADC") == 0) {
            CrossTable[addr].VarType = REALBADC; // backward compatibility

        } else {
            if (CrossTable[addr].Enable > 0) {
                CrossTable[addr].VarType = UNKNOWN;
                ERR = TRUE;
                break;
            }
        }

        // Decimal {0, 1, 2, 3, 4, ...}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        CrossTable[addr].Decimal = atoi(p);

        // Protocol {"", RTU, TCP, TCPRTU}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        if (strcmp(p, "PLC") == 0) {
            CrossTable[addr].Protocol = PLC;
        } else if (strcmp(p, "RTU") == 0) {
            CrossTable[addr].Protocol = RTU;
        } else if (strcmp(p, "TCP") == 0) {
            CrossTable[addr].Protocol = TCP;
        } else if (strcmp(p, "TCPRTU") == 0) {
            CrossTable[addr].Protocol = TCPRTU;
        } else if (strcmp(p, "CANOPEN") == 0) {
            CrossTable[addr].Protocol = CANOPEN;
        } else if (strcmp(p, "MECT") == 0) {
            CrossTable[addr].Protocol = MECT_PTC;
        } else if (strcmp(p, "RTU_SRV") == 0) {
            CrossTable[addr].Protocol = RTU_SRV;
        } else if (strcmp(p, "TCP_SRV") == 0) {
            CrossTable[addr].Protocol = TCP_SRV;
        } else if (strcmp(p, "TCPRTU_SRV") == 0) {
            CrossTable[addr].Protocol = TCPRTU_SRV;
        } else {
            CrossTable[addr].Protocol = PLC;
            ERR = TRUE;
            break;
        }

        // IPAddress {identifier}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        CrossTable[addr].IPAddress = str2ipaddr(p);

        // Port {number}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        CrossTable[addr].Port = atoi(p);

        // NodeId {number}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        CrossTable[addr].NodeId = atoi(p);

        // Address {number}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        CrossTable[addr].Offset = atoi(p);

        // Block {number}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        CrossTable[addr].Block = atoi(p);

        // NReg {number}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        CrossTable[addr].BlockSize = atoi(p);
        // Ultimo Token
        // Handle ([RO]||[RW]|[AL|EV SOURCE OP COND]){text}
        p = strtok_csv(NULL, ";", &r);
        if (p == NULL) {
            ERR = TRUE;
            break;
        }
        // Commento alla riga
        strcpy(CrossTable[addr].Comment, "");
        // Copia del dato letto in Comment
        if (strncmp(p, "\n",1) > 0)  {
            cPosComment = strchr(p, ']');
            if (cPosComment != NULL)  {
                if (strlen(cPosComment + sizeof(char)) > 0)  {
                    strncpy(CrossTable[addr].Comment, cPosComment + sizeof(char), MAX_COMMENT_NAME);
                    // Rimuove il Cr-Lf
                    cPosComment = strstr(CrossTable[addr].Comment, "\n");
                    if (cPosComment  != NULL)
                        cPosComment[0] = 0;
                }
            }
            if (strncmp(p, "[RW]", 4) == 0) {
                CrossTable[addr].Behavior = behavior_readwrite;
            } else if (strncmp(p, "[RO]", 4) == 0) {
                CrossTable[addr].Behavior = behavior_readonly;
            } else if (strncmp(p, "[AL ", 4) == 0) {
                CrossTable[addr].Behavior = behavior_alarm;
                CrossTable[addr].ALType = Alarm;
                if (strlen(p) < 10 || newAlarmEvent(1, addr, &(p[3]), strlen(p) - 3)) {
                    ERR = TRUE;
                    break;
                }
            } else if (strncmp(p, "[EV ", 4) == 0) {
                CrossTable[addr].Behavior = behavior_event;
                CrossTable[addr].ALType = Event;
                if (strlen(p) < 10 || newAlarmEvent(0, addr, &p[3], strlen(p) - 3)) {
                    ERR = TRUE;
                    break;
                }
            }
            // fprintf(stderr, "Voice:%d - %s\n", addr, CrossTable[addr].Output == TRUE ? "R/W" : "R/O" );

        }
    }
    if (ERR) {
        CrossTable[addr].Error = 1;
        goto exit_function;
    }

    // check alarms and events
    fprintf(stderr, "\nalarms/events:\n");
    for (indx = 1; indx <= lastAlarmEvent; ++indx) {
        float fvalue = 0;
        int compatible = TRUE;
        // retrieve the source variable address (Name ---> Pos)
        addr = tagAddr(ALCrossTable[indx].ALSource, CrossTable);
        if (addr == 0) {
            ERR = TRUE;
            break;
        }
        ALCrossTable[indx].SourceAddr = addr;
        CrossTable[addr].usedInAlarmsEvents = TRUE;
        fprintf(stderr, "\t%2d: %s", indx, CrossTable[ALCrossTable[indx].TagAddr].Tag);
        fprintf(stderr, " = %s", CrossTable[ALCrossTable[indx].SourceAddr].Tag);

        // which comparison?
        switch (CrossTable[addr].VarType) {
            case BIT:
            case BYTE_BIT:
            case WORD_BIT:
            case DWORD_BIT:
                ALCrossTable[indx].comparison = COMP_UNSIGNED;
                fprintf(stderr, " (u)");
                break;
            case INT16:
            case INT16BA:
            case DINT:
            case DINTDCBA:
            case DINTCDAB:
            case DINTBADC:
                ALCrossTable[indx].comparison = COMP_SIGNED;
                fprintf(stderr, " (s)");
                break;
            case UINT8:
            case UINT16:
            case UINT16BA:
            case UDINT:
            case UDINTDCBA:
            case UDINTCDAB:
            case UDINTBADC:
                ALCrossTable[indx].comparison = COMP_UNSIGNED;
                fprintf(stderr, " (u)");
                break;
            case REAL:
            case REALDCBA:
            case REALCDAB:
            case REALBADC:
                ALCrossTable[indx].comparison = COMP_FLOATING;
                fprintf(stderr, " (f)");
                break;
            default:
                ; // FIXME: assert
        }

        switch (ALCrossTable[indx].ALOperator)  {
            case oper_greater       : fprintf(stderr, " %s", logic_operators[oper_greater]); break;
            case oper_greater_eq    : fprintf(stderr, " %s", logic_operators[oper_greater_eq]); break;
            case oper_smaller       : fprintf(stderr, " %s", logic_operators[oper_smaller]); break;
            case oper_smaller_eq    : fprintf(stderr, " %s", logic_operators[oper_smaller_eq]); break;
            case oper_equal         : fprintf(stderr, " %s", logic_operators[oper_equal]); break;
            case oper_not_equal     : fprintf(stderr, " %s", logic_operators[oper_not_equal]); break;
            case oper_rising        : fprintf(stderr, " %s", logic_operators[oper_rising]); break;
            case oper_falling       : fprintf(stderr, " %s", logic_operators[oper_falling]); break;
            default             : ;
        }

        if (ALCrossTable[lastAlarmEvent].ALOperator != oper_falling
            && ALCrossTable[lastAlarmEvent].ALOperator != oper_rising) {
            // if the comparison is with a variable
            if (ALCrossTable[indx].ALCompareVar[0] != 0) {
                // then retrieve the compare variable address
                addr = tagAddr(ALCrossTable[indx].ALCompareVar, CrossTable);
                if (addr == 0) {
                    ERR = TRUE;
                    break;
                }
                ALCrossTable[indx].CompareAddr = addr;
                CrossTable[addr].usedInAlarmsEvents = TRUE;
                fprintf(stderr, " %s", CrossTable[addr].Tag);

                // check for incompatibles types
                switch (CrossTable[ALCrossTable[indx].SourceAddr].VarType) {

                    case BIT:
                    case BYTE_BIT:
                    case WORD_BIT:
                    case DWORD_BIT:
                        switch (CrossTable[ALCrossTable[indx].CompareAddr].VarType) {
                            case BIT:
                            case BYTE_BIT:
                            case WORD_BIT:
                            case DWORD_BIT:
                                compatible = TRUE;
                                break;
                            case INT16:
                            case INT16BA:
                            case DINT:
                            case DINTDCBA:
                            case DINTCDAB:
                            case DINTBADC:
                                compatible = FALSE; // only == 0 and != 0
                                break;
                            case UINT8:
                            case UINT16:
                            case UINT16BA:
                            case UDINT:
                            case UDINTDCBA:
                            case UDINTCDAB:
                            case UDINTBADC:
                                compatible = FALSE; // only == 0 and != 0
                                break;
                            case REAL:
                            case REALDCBA:
                            case REALCDAB:
                            case REALBADC:
                                compatible = FALSE; // only == 0 and != 0
                                break;
                            default:
                                ; // FIXME: assert
                            }
                        break;

                    case INT16:
                    case INT16BA:
                    case DINT:
                    case DINTDCBA:
                    case DINTCDAB:
                    case DINTBADC:
                        switch (CrossTable[ALCrossTable[indx].CompareAddr].VarType) {
                            case BIT:
                            case BYTE_BIT:
                            case WORD_BIT:
                            case DWORD_BIT:
                                compatible = FALSE;
                                break;
                            case INT16:
                            case INT16BA:
                            case DINT:
                            case DINTDCBA:
                            case DINTCDAB:
                            case DINTBADC:
                                compatible = (CrossTable[ALCrossTable[indx].SourceAddr].Decimal == CrossTable[ALCrossTable[indx].CompareAddr].Decimal);
                                break;
                            case UINT8:
                            case UINT16:
                            case UINT16BA:
                            case UDINT:
                            case UDINTDCBA:
                            case UDINTCDAB:
                            case UDINTBADC:
                                // compatible = (CrossTable[ALCrossTable[indx].SourceAddr].Decimal == CrossTable[ALCrossTable[indx].CompareAddr].Decimal);
                                compatible = FALSE;
                                break;
                            case REAL:
                            case REALDCBA:
                            case REALCDAB:
                            case REALBADC:
                                compatible = FALSE;
                                break;
                            default:
                                ; // FIXME: assert
                        }
                        break;

                    case UINT8:
                    case UINT16:
                    case UINT16BA:
                    case UDINT:
                    case UDINTDCBA:
                    case UDINTCDAB:
                    case UDINTBADC:
                        switch (CrossTable[ALCrossTable[indx].CompareAddr].VarType) {
                            case BIT:
                            case BYTE_BIT:
                            case WORD_BIT:
                            case DWORD_BIT:
                                compatible = FALSE;
                                break;
                            case INT16:
                            case INT16BA:
                            case DINT:
                            case DINTDCBA:
                            case DINTCDAB:
                            case DINTBADC:
                                // compatible = (CrossTable[ALCrossTable[indx].SourceAddr].Decimal == CrossTable[ALCrossTable[indx].CompareAddr].Decimal);
                                compatible = FALSE;
                                break;
                            case UINT8:
                            case UINT16:
                            case UINT16BA:
                            case UDINT:
                            case UDINTDCBA:
                            case UDINTCDAB:
                            case UDINTBADC:
                                compatible = (CrossTable[ALCrossTable[indx].SourceAddr].Decimal == CrossTable[ALCrossTable[indx].CompareAddr].Decimal);
                                break;
                            case REAL:
                            case REALDCBA:
                            case REALCDAB:
                            case REALBADC:
                                compatible = FALSE;
                                break;
                            default:
                                ; // FIXME: assert
                        }
                        break;

                    case REAL:
                    case REALDCBA:
                    case REALCDAB:
                    case REALBADC:
                        switch (CrossTable[ALCrossTable[indx].CompareAddr].VarType) {
                            case BIT:
                            case BYTE_BIT:
                            case WORD_BIT:
                            case DWORD_BIT:
                                compatible = FALSE;
                                break;
                            case INT16:
                            case INT16BA:
                            case DINT:
                            case DINTDCBA:
                            case DINTCDAB:
                            case DINTBADC:
                                compatible = FALSE;
                                break;
                            case UINT8:
                            case UINT16:
                            case UINT16BA:
                            case UDINT:
                            case UDINTDCBA:
                            case UDINTCDAB:
                            case UDINTBADC:
                                compatible = FALSE;
                                break;
                            case REAL:
                            case REALDCBA:
                            case REALCDAB:
                            case REALBADC:
                                compatible = TRUE; // no decimal test
                                break;
                            default:
                                ; // FIXME: assert
                        }
                        break;

                    default:
                        ; // FIXME: assert
                }
                if (! compatible) {
                    fprintf(stderr, " [WARNING: comparison between incompatible types]");
                }

            } else {
                // the comparison CrossTableis with a fixed value, now check for the vartype
                // since we saved the value as float before and we wish to check
                // directly afterwards using uint32_t values
                // float fvalue = *(float *)&ALCrossTable[indx].ALCompareVal;
                fvalue = ALCrossTable[indx].ALCompareVal;
                int n;

                switch (CrossTable[addr].VarType) {
                    case BIT:
                    case BYTE_BIT:
                    case WORD_BIT:
                    case DWORD_BIT:
                            if (fvalue <= 0.0) {
                            ALCrossTable[indx].ALCompareVal = 0;
                            } else if (fvalue <= 1.0) {
                            ALCrossTable[indx].ALCompareVal = 1;
                        } else {
                            ALCrossTable[indx].ALCompareVal = 2;
                        }
                        break;
                    case INT16:
                    case INT16BA:
                    case DINT:
                    case DINTDCBA:
                    case DINTCDAB:
                    case DINTBADC:
                        for (n = 0; n < CrossTable[addr].Decimal; ++n) {
                            fvalue *= 10;
                        }
                        // NB this may either overflow or underflow
                        ALCrossTable[indx].ALCompareVal = fvalue;
                        break;
                        case UINT8:
                    case UINT16:
                    case UINT16BA:
                    case UDINT:
                    case UDINTDCBA:
                    case UDINTCDAB:
                    case UDINTBADC:
                        if (fvalue <= 0) {
                            fvalue = 0; // why check unsigned with a negative value?
                        } else {
                            for (n = 0; n < CrossTable[addr].Decimal; ++n) {
                                fvalue *= 10;
                            }
                        }
                        // NB this may overflow
                        ALCrossTable[indx].ALCompareVal = fvalue;
                        break;
                    case REAL:
                    case REALDCBA:
                    case REALCDAB:
                    case REALBADC:
                        // the value is already stored as a float, comparisons will be ok
                        break;
                    default:
                        ; // FIXME: assert
                }
                fprintf(stderr, " %f", fvalue);
            }

        }
        fprintf(stderr, "\n");
        // Saving CrossTable Alarm Values
        CrossTable[ALCrossTable[indx].TagAddr].usedInAlarmsEvents = TRUE;
        CrossTable[ALCrossTable[indx].TagAddr].ALComparison = ALCrossTable[indx].comparison;
        strcpy(CrossTable[ALCrossTable[indx].TagAddr].ALSource, ALCrossTable[indx].ALSource);
        CrossTable[ALCrossTable[indx].TagAddr].ALOperator = ALCrossTable[indx].ALOperator;
        CrossTable[ALCrossTable[indx].TagAddr].ALCompareVal = fvalue;
        CrossTable[ALCrossTable[indx].TagAddr].ALCompatible = compatible;

    }

// close file
    // close file
exit_function:
    if (xtable) {
        fclose(xtable);
    }
    if (ERR)
        fprintf(stderr, "ERROR. Row: %d\n", addr);
    else
        fprintf(stderr, " OK\n");
    return ERR;
}

int SaveXTable(char *crossTableFile, struct CrossTableRecord *CrossTable)
{
    uint32_t addr, nCol;
    int ERR = FALSE;
    FILE *xtable = NULL;
    char row[LINESIZE], token[LINESIZE];

    // open file for writing
    fprintf(stderr, "writing '%s' ...", crossTableFile);
    xtable = fopen(crossTableFile, "w");
    if (xtable == NULL)  {
        ERR = TRUE;
        goto exit_function;
    }
    // Cicle on Cross Table Elements
    // read loop
    for (addr = 1; addr <= DimCrossTable; ++ addr) {
        // Clear Rowfilling string with chars
        memset(row, 0, LINESIZE);
        // Priority
        if (CrossTable[addr].Enable == 0 && strlen(CrossTable[addr].Tag) == 0)
        {
            // Empty CT Line
            for (nCol = 0;nCol < ctCOLS-1; nCol++)
                strcat(row, SEMICOL);
        }
        else
        {
            // Priority Column
            sprintf(token, "%1d;", CrossTable[addr].Enable);
            strcat(row, token);
            // Update
            sprintf(token, "%s;", updateTypeName[CrossTable[addr].Plc]);
            strcat(row, token);
            // Name
            sprintf(token, "%-16s;", CrossTable[addr].Tag);
            strcat(row, token);
            // Type
            sprintf(token, "%-9s;", varTypeName[CrossTable[addr].VarType]);
            strcat(row, token);
            // Decimals CrossTable[addr].Decimal
            sprintf(token, "%-4d;", CrossTable[addr].Decimal);
            strcat(row, token);
            // Protocol
            sprintf(token, "%-10s;", fieldbusName[CrossTable[addr].Protocol]);
            strcat(row, token);
            // IP Address
            if (CrossTable[addr].Protocol == TCP || CrossTable[addr].Protocol == TCPRTU || CrossTable[addr].Protocol == TCP_SRV || CrossTable[addr].Protocol ==TCPRTU_SRV)  {
                ipaddr2str(CrossTable[addr].IPAddress, token);
            }
            else
                strcpy(token, "");
            sprintf(token, "%-15s;", token);
            strcat(row, token);
            // Port - NodeId - Register tutti a 0
            if (CrossTable[addr].Port == 0 && CrossTable[addr].NodeId == 0 && CrossTable[addr].Offset == 0)  {
                sprintf(token, "%-4s;", "");
                strcat(row, token);
                strcat(row, token);
                strcat(row, token);
            }
            else  {
                // Port
                sprintf(token, "%-4d;", CrossTable[addr].Port);
                strcat(row, token);
                // Node Id
                sprintf(token, "%-4d;", CrossTable[addr].NodeId);
                strcat(row, token);
                // Register - Offset
                sprintf(token, "%-4d;", CrossTable[addr].Offset);
                strcat(row, token);
            }
            // Block
            sprintf(token, "%-4d;", CrossTable[addr].Block);
            strcat(row, token);
            // Reg.Num
            sprintf(token, "%-4d;", CrossTable[addr].BlockSize);
            strcat(row, token);
            // Behavior (da completare con Gestione Allarmi)
            if (CrossTable[addr].Behavior == behavior_readwrite)  {
                strcat(row, "[RW]");
            }
            else if (CrossTable[addr].Behavior == behavior_readonly) {
                strcat(row, "[RO]");
            }
            else if (CrossTable[addr].Behavior == behavior_alarm || CrossTable[addr].Behavior == behavior_event)  {
                if (CrossTable[addr].Behavior == behavior_alarm)  {
                    strcat(row, "[AL ");
                }
                else {
                    strcat(row, "[EV ");
                }
                // TODO: Complete writing alarm conditions
                // Closing condition
                strcat(row, "]");
            }
            // Comment
            strcat(row, CrossTable[addr].Comment);
        }
        // Finally Write Row
        // strcat(row,"\n");
        if (fprintf(xtable, "%s\n",row) < 0) {
            ERR = TRUE;
            break;
        }
    }
    // close file

exit_function:
    if (xtable) {
        fclose(xtable);
    }
    fprintf(stderr, " %s\n", (ERR) ? "ERROR" : "OK");
    return ERR;
}
