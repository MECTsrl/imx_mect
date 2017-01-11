#ifndef PWR_SIGNAL_H_INCLUDED
#define PWR_SIGNAL_H_INCLUDED

#ifdef __KERNEL__
#include <asm/siginfo.h>    //siginfo
#include <linux/rcupdate.h> //rcu_read_lock
#include <linux/sched.h>    //find_task_by_pid_type
#include <linux/rcupdate.h> //rcu_read_lock
#include <linux/debugfs.h>
#include <linux/uaccess.h>
#endif

#define PWRFAIL_SIGNAL
#define DBGFS_ROOT    "/sys/kernel/debug/"
#define PID_FILE    "signalconfpid"
#define PID_PATH	"/sys/kernel/debug/signalconfpid"
#define SIGPWRFAIL  44

#ifdef PWRFAIL_SIGNAL
#undef PWRFAIL_DEBUG
#if 1
#ifdef __KERNEL__
#include <asm/ioctl.h>
#else
#include <sys/ioctl.h>
#endif
#define RETENTIVE_MAGIC 'r'
#define RETENTIVE_POWEROFF _IO(RETENTIVE_MAGIC, 0)
#ifdef PWRFAIL_DEBUG
#define RETENTIVE_GPIOCTRL _IO(RETENTIVE_MAGIC, 1)
#endif
#endif

#endif //PWRFAIL_SIGNAL

#endif
