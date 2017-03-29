#ifndef PARSER_H
#define PARSER_H
#include <ctype.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
 ****************************** DEFINES  SECTION ******************************
 ******************************************************************************/
#define DimCrossTable   5472
#define CROSSTABLE_CSV "/local/etc/sysconfig/Crosstable.csv"
#define DimAlarmsCT     1152
#define MAX_IPADDR_LEN      17 // 123.567.901.345.
#define MAX_NUMBER_LEN      12 // -2147483648. -32768.
#define MAX_IDNAME_LEN      17 // abcdefghijklmno.
#define MAX_VARTYPE_LEN      9 // UDINTABCD.
#define MAX_PROTOCOL_LEN     9 // TCPRTUSRV.
#define MAX_DEVICE_LEN      13 // /dev/ttyUSB0.
#define MAX_COMMENT_NAME    30

#define COMP_UNSIGNED   77
#define COMP_SIGNED     78
#define COMP_FLOATING      79

/******************************************************************************
 ****************************** TYPEDEFS SECTION ******************************
 ******************************************************************************/
enum FieldbusType {PLC = 0,
                   RTU,
                   TCP,
                   TCPRTU,
                   CANOPEN,
                   MECT_PTC,
                   RTU_SRV,
                   TCP_SRV,
                   TCPRTU_SRV
                  };

enum EventAlarm { Event = 0, Alarm};

enum UpdateType { Htype = 0,
                  Ptype,
                  Stype,
                  Ftype,
                  Vtype,
                  Xtype
                };
#undef WORD_BIT
enum varTypes {BIT = 0,
               BYTE_BIT,
               WORD_BIT,
               DWORD_BIT,
               UINT8,
               UINT16,
               UINT16BA,
               INT16,
               INT16BA,
               REAL,
               REALDCBA,
               REALCDAB,
               REALBADC,
               UDINT,
               UDINTDCBA,
               UDINTCDAB,
               UDINTBADC,
               DINT,
               DINTDCBA,
               DINTCDAB,
               DINTBADC,
               UNKNOWN
              };

enum productId {
        /*00*/ AnyTPAC = 0,
        /*01*/ TP1043_01_A,
        /*02*/ TP1043_01_B,
        /*03*/ TP1043_01_C,
        /*04*/ TP1057_01_A,
        /*05*/ TP1057_01_B,
        /*06*/ TP1070_01_A,
        /*07*/ TP1070_01_B,
        /*08*/ TP1070_01_C,
        /*09*/ TP1070_01_D,
        /*10*/ TPAC1006,
        /*11*/ TPAC1007_03,
        /*12*/ TPAC1007_04_AA,
        /*13*/ TPAC1007_04_AB,
        /*14*/ TPAC1007_04_AC,
        /*15*/ TPAC1007_LV,
        /*16*/ TPAC1008_01,
        /*17*/ TPAC1008_02_AA,
        /*18*/ TPAC1008_02_AB,
        /*19*/ TPAC1008_02_AC,
        /*20*/ TPAC1008_02_AD,
        /*21*/ TPAC1008_02_AE,
        /*22*/ TPAC1008_02_AF
};

enum logicalOperators {
    oper_greater = 0,
    oper_greater_eq,
    oper_smaller,
    oper_smaller_eq,
    oper_equal,
    oper_not_equal,
    oper_rising,
    oper_falling,
    oper_totals
};

enum behaviors  {
    behavior_readonly = 0,
    behavior_readwrite,
    behavior_alarm,
    behavior_event,
    behavior_totals
};

struct  CrossTableRecord {
    int16_t Enable;
    int  UsedEntry;
    enum UpdateType Plc;
    char Tag[MAX_IDNAME_LEN];
    enum varTypes VarType;
    uint16_t Decimal;
    enum FieldbusType Protocol;
    uint32_t IPAddress;
    uint16_t Port;
    uint8_t NodeId;
    uint16_t Offset;
    uint16_t Block;
    uint16_t BlockBase;
    int16_t BlockSize;
    int     Behavior;
    int16_t Counter;
    uint32_t OldVal;
    uint16_t Error;
    // Fields for Events / Alarms
    int     usedInAlarmsEvents;
    int     ALType;
    char    ALSource[MAX_IDNAME_LEN];
    int     ALOperator;
    char    ALCompareVar[MAX_IDNAME_LEN];
    float   ALCompareVal;
    int     ALComparison;
    int     ALCompatible;
    //
    uint16_t device;
    uint16_t node;
    char Comment[MAX_COMMENT_NAME];
};

struct  Alarms {
    enum EventAlarm ALType;
    uint16_t TagAddr;
    char ALSource[MAX_IDNAME_LEN];
    char ALCompareVar[MAX_IDNAME_LEN];
    uint16_t SourceAddr;
    uint16_t CompareAddr;
    float ALCompareVal;
    uint16_t ALOperator;
    uint16_t ALFilterTime;
    uint16_t ALFilterCount;
    uint16_t ALError;
    int comparison;
};

/******************************************************************************
 ***************************** PROTOTYPES SECTION *****************************
 ******************************************************************************/
int     LoadXTable(char *crossTableFile, struct CrossTableRecord *CrossTable);
int     SaveXTable(char *crossTableFile, struct CrossTableRecord *CrossTable);
char    *ipaddr2str(uint32_t ipaddr, char *buffer);
uint32_t str2ipaddr(char *str);

/******************************************************************************
 ***************************** VARIABLES SECTION *****************************
 ******************************************************************************/
extern const char *fieldbusName[];
extern const char *varTypeName[];
extern const char *updateTypeName[];
extern const char *product_name[];
extern const char *logic_operators[];

//struct CrossTableRecord CrossTable[1 + DimCrossTable];	 // campi sono riempiti a partire dall'indice 1

#ifdef __cplusplus
}
#endif

#endif // PARSER_H
