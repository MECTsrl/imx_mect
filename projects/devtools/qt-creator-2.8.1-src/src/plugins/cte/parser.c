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

const char *fieldbusName[] = {"PLC", "RTU", "TCP", "TCPRTU", "CANOPEN", "MECT", "RTU_SRV", "TCP_SRV", "TCPRTU_SRV" };
const char *varTypeName[] = {"BIT", "BYTE_BIT", "WORD_BIT", "DWORD_BIT", "BYTE", "UINT16", "UINT16BA", "INT16", "INT16BA", "REAL", "REALDCBA", "REALCDAB", "REALBADC", "UDINT", "UDINTDCBA", "UDINTCDAB", "UDINTBADC", "DINT", "DINTDCBA", "DINTCDAB", "DINTBADC", "UNKNOWN" };
const char *updateTypeName[] = {"H", "P", "S", "F", "V", "X" };

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
    if (strncmp(p, ">", 1) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = OPER_GREATER;
    } else if (strncmp(p, ">=", 2) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = OPER_GREATER_EQ;
    } else if (strncmp(p, "<", 1) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = OPER_SMALLER;
    } else if (strncmp(p, "<=", 2) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = OPER_SMALLER_EQ;
    } else if (strncmp(p, "==", 2) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = OPER_EQUAL;
    } else if (strncmp(p, "!=", 2) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = OPER_NOT_EQUAL;
    } else if (strncmp(p, "RISING", 6) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = OPER_RISING;
    } else if (strncmp(p, "FALLING", 7) == 0) {
        ALCrossTable[lastAlarmEvent].ALOperator = OPER_FALLING;
    } else {
        goto exit_error;
    }

    if (ALCrossTable[lastAlarmEvent].ALOperator != OPER_FALLING && ALCrossTable[lastAlarmEvent].ALOperator != OPER_RISING) {
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
        } else {
            // number
            ALCrossTable[lastAlarmEvent].ALCompareVar[0] = 0;
            memcpy(&ALCrossTable[lastAlarmEvent].ALCompareVal, &f, sizeof(uint32_t));
        }
    }
    return 0;

exit_error:
    --lastAlarmEvent;
    return -1;
}

static uint16_t tagAddr(char *tag)
{
    uint16_t addr;

    for (addr = 1; addr <= DimCrossTable; ++addr) {
        if (strncmp(tag, CrossTable[addr].Tag, MAX_IDNAME_LEN) == 0) {
            return addr;
        }
    }
    return 0;
}


int LoadXTable(char *crossTableFile)
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
        CrossTable[addr].Types = UNKNOWN;
        CrossTable[addr].Decimal = 0;
        CrossTable[addr].Protocol = PLC;
        CrossTable[addr].IPAddress = 0x00000000;
        CrossTable[addr].Port = 0;
        CrossTable[addr].NodeId = 0;
        CrossTable[addr].Offset = 0;
        CrossTable[addr].Block = 0;
        CrossTable[addr].BlockSize = 0;
        CrossTable[addr].Output = FALSE;
        CrossTable[addr].OldVal = 0;
        CrossTable[addr].Error = 0;
        CrossTable[addr].device = 0xffff;
        CrossTable[addr].node = 0xffff;
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
        if (strncmp(p, "BIT", strlen(p)) == 0) {
            CrossTable[addr].Types = BIT;
        } else if (strncmp(p, "BYTE_BIT", strlen(p)) == 0) {
            CrossTable[addr].Types = BYTE_BIT;
        } else if (strncmp(p, "WORD_BIT", strlen(p)) == 0) {
            CrossTable[addr].Types = WORD_BIT;
        } else if (strncmp(p, "DWORD_BIT", strlen(p)) == 0) {
            CrossTable[addr].Types = DWORD_BIT;
        } else if (strncmp(p, "UINT", strlen(p)) == 0) {
            CrossTable[addr].Types = UINT16;
        } else if (strncmp(p, "UINTBA", strlen(p)) == 0) {
            CrossTable[addr].Types = UINT16BA;
        } else if (strncmp(p, "INT", strlen(p)) == 0) {
            CrossTable[addr].Types = INT16;
        } else if (strncmp(p, "INTBA", strlen(p)) == 0) {
            CrossTable[addr].Types = INT16BA;
        } else if (strncmp(p, "UDINT", strlen(p)) == 0) {
            CrossTable[addr].Types = UDINT;
        } else if (strncmp(p, "UDINTDCBA", strlen(p)) == 0) {
            CrossTable[addr].Types = UDINTDCBA;
        } else if (strncmp(p, "UDINTCDAB", strlen(p)) == 0) {
            CrossTable[addr].Types = UDINTCDAB;
        } else if (strncmp(p, "UDINTBADC", strlen(p)) == 0) {
            CrossTable[addr].Types = UDINTBADC;
        } else if (strncmp(p, "DINT", strlen(p)) == 0) {
            CrossTable[addr].Types = DINT;
        } else if (strncmp(p, "DINTDCBA", strlen(p)) == 0) {
            CrossTable[addr].Types = DINTDCBA;
        } else if (strncmp(p, "DINTCDAB", strlen(p)) == 0) {
            CrossTable[addr].Types = DINTCDAB;
        } else if (strncmp(p, "DINTBADC", strlen(p)) == 0) {
            CrossTable[addr].Types = DINTBADC;
        } else if (strncmp(p, "REAL", strlen(p)) == 0) {
            CrossTable[addr].Types = REAL;
        } else if (strncmp(p, "REALDCBA", strlen(p)) == 0) {
            CrossTable[addr].Types = REALDCBA;
        } else if (strncmp(p, "REALCDAB", strlen(p)) == 0) {
            CrossTable[addr].Types = REALCDAB;
        } else if (strncmp(p, "REALBADC", strlen(p)) == 0) {
            CrossTable[addr].Types = REALBADC;

        } else if (strncmp(p, "UINTAB", strlen(p)) == 0) {
            CrossTable[addr].Types = UINT16; // backward compatibility
        } else if (strncmp(p, "INTAB", strlen(p)) == 0) {
            CrossTable[addr].Types = INT16; // backward compatibility
        } else if (strncmp(p, "UDINTABCD", strlen(p)) == 0) {
            CrossTable[addr].Types = UDINT; // backward compatibility
        } else if (strncmp(p, "DINTABCD", strlen(p)) == 0) {
            CrossTable[addr].Types = DINT; // backward compatibility
        } else if (strncmp(p, "FDCBA", strlen(p)) == 0) {
            CrossTable[addr].Types = REALDCBA; // backward compatibility
        } else if (strncmp(p, "FCDAB", strlen(p)) == 0) {
            CrossTable[addr].Types = REALCDAB; // backward compatibility
        } else if (strncmp(p, "FABCD", strlen(p)) == 0) {
            CrossTable[addr].Types = REAL; // backward compatibility
        } else if (strncmp(p, "FBADC", strlen(p)) == 0) {
            CrossTable[addr].Types = REALBADC; // backward compatibility

        } else {
            if (CrossTable[addr].Enable > 0) {
                CrossTable[addr].Types = UNKNOWN;
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
        if (strncmp(p, "PLC", strlen(p)) == 0) {
            CrossTable[addr].Protocol = PLC;
        } else if (strncmp(p, "RTU", strlen(p)) == 0) {
            CrossTable[addr].Protocol = RTU;
        } else if (strncmp(p, "TCP", strlen(p)) == 0) {
            CrossTable[addr].Protocol = TCP;
        } else if (strncmp(p, "TCPRTU", strlen(p)) == 0) {
            CrossTable[addr].Protocol = TCPRTU;
        } else if (strncmp(p, "CANOPEN", strlen(p)) == 0) {
            CrossTable[addr].Protocol = CANOPEN;
        } else if (strncmp(p, "MECT", strlen(p)) == 0) {
            CrossTable[addr].Protocol = MECT;
        } else if (strncmp(p, "RTU_SRV", strlen(p)) == 0) {
            CrossTable[addr].Protocol = RTU_SRV;
        } else if (strncmp(p, "TCP_SRV", strlen(p)) == 0) {
            CrossTable[addr].Protocol = TCP_SRV;
        } else if (strncmp(p, "TCPRTU_SRV", strlen(p)) == 0) {
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
                CrossTable[addr].Output = TRUE;
            } else if (strncmp(p, "[RO]", 4) == 0) {
                CrossTable[addr].Output = FALSE;
            } else if (strncmp(p, "[AL ", 4) == 0) {
                CrossTable[addr].Output = FALSE;
                if (strlen(p) < 10 || newAlarmEvent(1, addr, &(p[3]), strlen(p) - 3)) {
                    ERR = TRUE;
                    break;
                }
            } else if (strncmp(p, "[EV ", 4) == 0) {
                CrossTable[addr].Output = FALSE;
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
    for (indx = 1; indx <= lastAlarmEvent; ++indx) {
        // retrieve the source variable address
        addr = tagAddr(ALCrossTable[indx].ALSource);
        if (addr == 0) {
            ERR = TRUE;
            break;
        }
        ALCrossTable[indx].SourceAddr = addr;
        CrossTable[addr].usedInAlarmsEvents = TRUE;
        // if the comparison is with a variable
        if (ALCrossTable[indx].ALCompareVar[0] != 0) {
            // then retrieve the compare variable address
            addr = tagAddr(ALCrossTable[indx].ALCompareVar);
            if (addr == 0) {
                ERR = TRUE;
                break;
            }
            ALCrossTable[indx].CompareAddr = addr;
            CrossTable[addr].usedInAlarmsEvents = TRUE;
        } else {
            // the comparison is with a fixed value, now check for the vartype
            // since we saved the value as float before and we wish to check
            // directly afterwards using uint32_t values
            float fvalue = *(float *)&ALCrossTable[indx].ALCompareVal;
            int n;

            switch (CrossTable[addr].Types) {
            case BIT:
            case BYTE_BIT:
            case WORD_BIT:
            case DWORD_BIT:
                if (fvalue <= 0) {
                    ALCrossTable[indx].ALCompareVal = 0;
                } else if (fvalue <= 1) {
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

int SaveXTable(char *crossTableFile)
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
            sprintf(token, "%-9s;", varTypeName[CrossTable[addr].Types]);
            strcat(row, token);
            // Decimals CrossTable[addr].Decimal
            sprintf(token, "%-4d;", CrossTable[addr].Decimal);
            strcat(row, token);
            // Protocol
            sprintf(token, "%-9s;", fieldbusName[CrossTable[addr].Protocol]);
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
            if (CrossTable[addr].Output)  {
                strcat(row, "[RW]");
            }
            else  {
                strcat(row, "[RO]");
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
