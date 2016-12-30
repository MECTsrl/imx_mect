/*
 * Copyright 2012 Francesco Mandracci. All Rights Reserved.
 *
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 *
 * based on xenomai-2.6.0/ksrc/drivers/can/sja1000/rtcan_sja1000_proc.c
 * Copyright (C) 2006 Wolfgang Grandegger <wg@grandegger.com>
 */

#include <linux/module.h>
#include <linux/ioport.h>
#include <linux/delay.h>

#include <rtdm/rtdm_driver.h>

#include <rtcan_dev.h>
#include <rtcan_internal.h>
#include <rtcan_flexcan.h>

#ifdef CONFIG_XENO_DRIVERS_CAN_DEBUG

struct {
	int offset;
	char name[18];
} flexcan_regs[] = {
                //123456789012345678
	{ 0x000, "HW_CAN_MCR       " },
	{ 0x004, "HW_CAN_CRTL      " },
	{ 0x008, "HW_CAN_TIMER     " },
	{ 0x010, "HW_CAN_RXGMASK   " },
	{ 0x014, "HW_CAN_RX14MASK  " },
	{ 0x018, "HW_CAN_RX15MASK  " },
	{ 0x01c, "HW_CAN_ECR       " },
	{ 0x020, "HW_CAN_ESR       " },
	{ 0x024, "HW_CAN_IMASK2    " },
	{ 0x028, "HW_CAN_IMASK1    " },
	{ 0x02c, "HW_CAN_IFLAG2    " },
	{ 0x030, "HW_CAN_IFLAG1    " },
	{ 0x034, "HW_CAN_GFWR      " },
	{ 0x080, "HW_CAN_MBn[00]   " },
	{ 0x084, "HW_CAN_MBn[01]   " },
	{ 0x17c, "HW_CAN_MBn[63]   " },
	{ 0x880, "HW_CAN_RXIMRn[00]" },
	{ 0x884, "HW_CAN_RXIMRn[01]" },
	{ 0x97c, "HW_CAN_RXIMRn[63]" },
};

static int rtcan_flexcan_proc_regs(char *buf, char **start, off_t offset,
				 int count, int *eof, void *data)
{
    struct rtcan_device *dev = (struct rtcan_device *)data;
    struct rtcan_flexcan *chip = (struct rtcan_flexcan *)dev->priv;
    int i;
    RTCAN_PROC_PRINT_VARS(80);

    if (!RTCAN_PROC_PRINT("FlexCAN registers\n")) {
	goto done;
    }
    for (i = 0; i < sizeof(flexcan_regs)/sizeof(flexcan_regs[0]); ++i) {
        if (!RTCAN_PROC_PRINT("%s: 0x%08x\n", flexcan_regs[i].name,
		__raw_readl(chip->io_base + flexcan_regs[i].offset))) {
		goto done;
	}
    }
 done:
    RTCAN_PROC_PRINT_DONE;
}

int rtcan_flexcan_create_proc(struct rtcan_device* dev)
{
    struct proc_dir_entry *proc_entry;

    if (!dev->proc_root)
	return -EINVAL;

    proc_entry = create_proc_entry("registers", S_IFREG | S_IRUGO | S_IWUSR,
				   dev->proc_root);
    if (!proc_entry)
	goto error;
    proc_entry->read_proc = rtcan_flexcan_proc_regs;
    proc_entry->data = dev;

    return 0;

  error:
    printk("%s: unable to create /proc entries for FlexCAN\n", dev->name);
    return -1;
}

void rtcan_flexcan_remove_proc(struct rtcan_device* dev)
{
    if (!dev->proc_root)
	return;

    remove_proc_entry("registers", dev->proc_root);
}

#else /* !CONFIG_XENO_DRIVERS_CAN_DEBUG */

void rtcan_flexcan_remove_proc(struct rtcan_device* dev)
{
}

int rtcan_flexcan_create_proc(struct rtcan_device* dev)
{
    return 0;
}
#endif	/* CONFIG_XENO_DRIVERS_CAN_DEBUG */

