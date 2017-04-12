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
               UNKNOWN,
               TYPE_TOTALS
              };

enum productId {
        /*00*/ AnyTPAC = 0,
        /*01*/ TP1043_01_A,
        /*02*/ TP1043_01_B,
        /*03*/ TP1057_01_A,
        /*04*/ TP1057_01_B,
        /*05*/ TP1070_01_A,
        /*06*/ TP1070_01_B,
        /*07*/ TP1070_01_C,
        /*08*/ TPAC1006,
        /*09*/ TPAC1007_03,
        /*10*/ TPAC1007_04_AA,
        /*11*/ TPAC1007_04_AB,
        /*12*/ TPAC1007_04_AC,
        /*13*/ TPAC1007_LV,
        /*14*/ TPAC1008_01,
        /*15*/ TPAC1008_02_AA,
        /*16*/ TPAC1008_02_AB,
        /*17*/ TPAC1008_02_AD,
        /*18*/ TPAC1008_02_AE,
        /*19*/ TPAC1008_02_AF,
        /*20*/ TPLC100,
        /*21*/ TPLC150,
               MODEL_TOTALS
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

// Indici dei Tab della finestra Settings
enum tabSettings_e
{
    tabSystem = 0,
    tabSerial0,
    tabSerial1,
    tabSerial2,
    tabSerial3,
    tabTCP,
    tabCan0,
    tabCan1,
    tabTotals
};


struct  CrossTableRecord {
    int16_t Enable;
    int  UsedEntry;
    enum UpdateType Update;
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
    int     usedInAlarmsEvents;                     // 1 if used in AL/EV
    int     ALType;                                 // from enum EventAlarm (0=Alarm 1=Event...)
    char    ALSource[MAX_IDNAME_LEN];               // Name of source variable in Alarms
    int     ALOperator;                             // Operator on variable, from enum logicalOperators
    char    ALCompareVar[MAX_IDNAME_LEN];           // Compare variable (right side of operation, if any)
    float   ALCompareVal;                           // Fixed comparision value (in alternative to Compare Variable)
    int     ALComparison;                           // Type of comparision (Signed, unsigned, float determined from left variable type)
    int     ALCompatible;                           // 1 if both side of comparision are between compatible types
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
