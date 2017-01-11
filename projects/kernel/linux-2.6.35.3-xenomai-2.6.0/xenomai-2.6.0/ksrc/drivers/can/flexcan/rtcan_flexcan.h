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
 * based on xenomai-2.6.0/ksrc/drivers/net/can/mscan/rtcan_mscan.h
 * Copyright (C) 2009 Wolfgang Grandegger <wg@denx.de>
 * based on xenomai-2.6.0/ksrc/drivers/net/can/sja1000/rtcan_sja1000.h
 * Copyright (C) 2006 Wolfgang Grandegger <wg@denx.de>
 */

#ifndef __RTCAN_FLEXCAN_H_
#define __RTCAN_FLEXCAN_H_

#define RTCAN_DEV_NAME    "rtcan%d"
#define RTCAN_DRV_NAME    "rtcan_flexcan"

/* FLEXCAN type variants */
enum {
        FLEXCAN_TYPE_IMX28
};

struct rtcan_flexcan {
	void (*enable)(struct rtcan_device *dev, int enable);
	void (*irq_ack)(struct rtcan_device *dev);

	volatile void __iomem *io_base;
	unsigned short irq_num;
	unsigned short irq_flags;
	unsigned short id;

        struct can_hw_mb *hwmb;
        unsigned int *rx_mask;
        unsigned int xmit_mb;
        unsigned int bitrate;

	/* word 1 */
	unsigned int br_presdiv:8;
	unsigned int br_rjw:2;
	unsigned int br_propseg:3;
	unsigned int br_pseg1:3;
	unsigned int br_pseg2:3;
	unsigned int maxmb:6;
	unsigned int xmit_maxmb:6;
	unsigned int wd1_resv:1;

	/* word 2 */
	unsigned int fifo:1;
	unsigned int wakeup:1;
	unsigned int srx_dis:1;
	unsigned int wak_src:1;
	unsigned int bcc:1;
	unsigned int lprio:1;
	unsigned int abort:1;
	unsigned int br_clksrc:1;
	unsigned int loopback:1;
	unsigned int smp:1;
	unsigned int boff_rec:1;
	unsigned int tsyn:1;
	unsigned int listen:1;
	
	unsigned int ext_msg:1;
	unsigned int std_msg:1;
};

extern int rtcan_flexcan_register(struct rtcan_device *dev);
extern void rtcan_flexcan_unregister(struct rtcan_device *dev);

extern int rtcan_flexcan_create_proc(struct rtcan_device* dev);
extern void rtcan_flexcan_remove_proc(struct rtcan_device* dev);

extern void rtcan_flexcan_mbm_init(struct rtcan_flexcan *flexcan);
extern int rtcan_flexcan_mbm_isr(struct rtcan_device *dev,
			struct rtcan_flexcan *flexcan,
			struct rtcan_skb *skb,
			int *rcv_lock_free_ptr);
extern int rtcan_flexcan_mbm_xmit(struct rtcan_flexcan *flexcan, struct can_frame *cframe);

#endif
