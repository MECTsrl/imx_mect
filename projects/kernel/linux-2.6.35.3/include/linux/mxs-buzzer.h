#ifndef MXS_BUZZER_H_INCLUDED
#define MXS_BUZZER_H_INCLUDED

#ifdef __KERNEL__
#include <asm/ioctl.h>
#else
#include <sys/ioctl.h>
#endif

#define BUZZER_VER "1.0"
#define BUZZER_DATE "2011-09"
#define BUZZER_MAJOR 35
#define BUZZER_MINOR 0
#define BUZZER_DEVICE_NAME "buzzer"

#define BUZZER_MAGIC 'b'
#define BUZZER_BEEP _IO(BUZZER_MAGIC, 0)

#if defined CONFIG_MECT_VAL01 
struct buzzer_mesg {
      unsigned int duration; //expressed in ms
      unsigned int volume;   // volume level 0-->100
 };
#endif

#endif
