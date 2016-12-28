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
#define OPER_GREATER    41
#define OPER_GREATER_EQ 42
#define OPER_SMALLER    43
#define OPER_SMALLER_EQ 44
#define OPER_EQUAL      45
#define OPER_NOT_EQUAL  46
#define OPER_RISING     47
#define OPER_FALLING    48

/******************************************************************************
 ****************************** TYPEDEFS SECTION ******************************
 ******************************************************************************/
enum FieldbusType {PLC = 0, RTU, TCP, TCPRTU, CANOPEN, MECT, RTU_SRV, TCP_SRV, TCPRTU_SRV};

enum EventAlarm { Event = 0, Alarm};

enum UpdateType { Htype = 0, Ptype, Stype, Ftype, Vtype, Xtype};
#undef WORD_BIT
enum varTypes {BIT = 0,
               BYTE_BIT,
               WORD_BIT,
               DWORD_BIT,
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

struct  CrossTableRecord {
    int16_t Enable;
    int  UsedEntry;
    enum UpdateType Plc;
    char Tag[MAX_IDNAME_LEN];
    enum varTypes Types;
    uint16_t Decimal;
    enum FieldbusType Protocol;
    uint32_t IPAddress;
    uint16_t Port;
    uint8_t NodeId;
    uint16_t Offset;
    uint16_t Block;
    uint16_t BlockBase;
    int16_t BlockSize;
    int Output;
    int16_t Counter;
    uint32_t OldVal;
    uint16_t Error;
    int usedInAlarmsEvents;
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
    uint32_t ALCompareVal;
    uint16_t ALOperator;
    uint16_t ALFilterTime;
    uint16_t ALFilterCount;
    uint16_t ALError;
};

/******************************************************************************
 ***************************** PROTOTYPES SECTION *****************************
 ******************************************************************************/
int     LoadXTable(char *crossTableFile);
int     SaveXTable(char *crossTableFile);
char    *ipaddr2str(uint32_t ipaddr, char *buffer);

/******************************************************************************
 ***************************** VARIABLES SECTION *****************************
 ******************************************************************************/
extern const char *fieldbusName[];

struct CrossTableRecord CrossTable[1 + DimCrossTable];	 // campi sono riempiti a partire dall'indice 1
struct Alarms ALCrossTable[1 + DimAlarmsCT]; // campi sono riempiti a partire dall'indice 1

#ifdef __cplusplus
}
#endif

#endif // PARSER_H
