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
 * based on linux-2.6.35.3_ipipe/drivers/net/can/flexcan/mbm.c
 * Copyright 2008-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#include <linux/module.h>

#include <rtdm/rtdm_driver.h>
#include <rtdm/rtcan.h>
#include "rtcan_dev.h"
#include "rtcan_raw.h"
#include "rtcan_internal.h"
#include "rtcan_flexcan.h"
#include "rtcan_flexcan_regs.h"

#include <mach/hardware.h> // <mach/mx28.h>

#if 0
#define flexcan_swab32(x)	\
	(((x) << 24) | ((x) >> 24) |\
		(((x) & (__u32)0x0000ff00UL) << 8) |\
		(((x) & (__u32)0x00ff0000UL) >> 8))

static inline void flexcan_memcpy(void *dst, void *src, int len)
{
	int i;
	unsigned int *d = (unsigned int *)dst, *s = (unsigned int *)src;
	len = (len + 3) >> 2;
	for (i = 0; i < len; i++, s++, d++)
		*d = flexcan_swab32(*s);
}
#else
/* necessary for avoiding alignment traps, which cause illegal calls
   between Linux and Xenomai domains (don't know why there are no alignment
   issues in the original Linux driver, checked with
   "echo 5 > /proc/cpu/alignment"))
 */
static inline void flexcan_memcpy(void *dst, void *src, int len)
{
	register unsigned char *d = dst;
	register unsigned char *s = src;
	d[0] = s[3];
	d[1] = s[2];
	d[2] = s[1];
	d[3] = s[0];
	d[4] = s[7];
	d[5] = s[6];
	d[6] = s[5];
	d[7] = s[4];
}
#endif

static int flexcan_mb_bottom(struct rtcan_device *dev,
			struct rtcan_flexcan *flexcan,
			struct rtcan_skb *skb,
			int index,
			int *rcv_lock_free_ptr)
{
	int retval = 0;
	struct can_hw_mb *hwmb;
	struct rtcan_rb_frame *frame;
	unsigned int tmp;

	hwmb = flexcan->hwmb + index;
	if (flexcan->fifo || (index >= (flexcan->maxmb - flexcan->xmit_maxmb))) {
		if ((hwmb->mb_cs & MB_CS_CODE_MASK) >> MB_CS_CODE_OFFSET ==
							CAN_MB_TX_ABORT) {
			hwmb->mb_cs &= ~MB_CS_CODE_MASK;
			hwmb->mb_cs |= CAN_MB_TX_INACTIVE << MB_CS_CODE_OFFSET;
		}

		if (hwmb->mb_cs & (CAN_MB_TX_INACTIVE << MB_CS_CODE_OFFSET)) {
			++retval;
			goto exit_function;
		}
	}
	if (skb) {
		frame = &skb->rb_frame;
		memset(frame, 0, sizeof(*frame));
		skb->rb_frame_size = EMPTY_RB_FRAME_SIZE;

		if (hwmb->mb_cs & MB_CS_IDE_MASK)
			frame->can_id =
			    (hwmb->mb_id & CAN_EFF_MASK) | CAN_EFF_FLAG;
		else
			frame->can_id = (hwmb->mb_id >> 18) & CAN_SFF_MASK;

		frame->can_dlc =
		(hwmb->mb_cs & MB_CS_LENGTH_MASK) >> MB_CS_LENGTH_OFFSET;
		if (frame->can_dlc > 8)
			frame->can_dlc = 8;

		if (frame->can_dlc && frame->can_dlc)
			flexcan_memcpy(frame->data, hwmb->mb_data,
				       frame->can_dlc);

		if (flexcan->fifo
		    || (index >= (flexcan->maxmb - flexcan->xmit_maxmb))) {
			hwmb->mb_cs &= ~MB_CS_CODE_MASK;
			hwmb->mb_cs |= CAN_MB_TX_INACTIVE << MB_CS_CODE_OFFSET;
			++retval;
		}

		if (hwmb->mb_cs & MB_CS_RTR_MASK) {
			frame->can_id |= CAN_RTR_FLAG;
		} else {
			skb->rb_frame_size += frame->can_dlc;
		}
		
		/* the following timer read also unlocks the buffer */
		tmp = __raw_readl(flexcan->io_base + CAN_HW_REG_TIMER);

	    /* Take more locks. Ensure that they are taken and
	     * released only once in the IRQ handler. */
	    if (*rcv_lock_free_ptr) {
		*rcv_lock_free_ptr = 0;
		rtdm_lock_get(&rtcan_recv_list_lock);
		rtdm_lock_get(&rtcan_socket_lock);
	    }

	    /* Pass received frame out to the sockets */
	    rtcan_rcv(dev, skb);
	} else {
		tmp = hwmb->mb_cs;
		tmp = hwmb->mb_id;
		tmp = hwmb->mb_data[0];
		if (flexcan->fifo
		    || (index >= (flexcan->maxmb - flexcan->xmit_maxmb))) {
			hwmb->mb_cs &= ~MB_CS_CODE_MASK;
			hwmb->mb_cs |= CAN_MB_TX_INACTIVE << MB_CS_CODE_OFFSET;
			++retval;
		}
		/* the following timer read also unlocks the buffer */
		tmp = __raw_readl(flexcan->io_base + CAN_HW_REG_TIMER);
	}
exit_function:
	return retval;
}

static void flexcan_fifo_isr(struct rtcan_device *dev, struct rtcan_flexcan *flexcan,
			struct rtcan_skb *skb, unsigned int iflag1)
{
	struct can_hw_mb *hwmb = flexcan->hwmb;
	struct rtcan_rb_frame *frame;
	unsigned int tmp;

	if (iflag1 & __FIFO_RDY_INT) {
		if (skb) {
			frame = &skb->rb_frame;
			memset(frame, 0, sizeof(*frame));
			if (hwmb->mb_cs & MB_CS_IDE_MASK)
				frame->can_id =
				    (hwmb->mb_id & CAN_EFF_MASK) | CAN_EFF_FLAG;
			else
				frame->can_id =
				    (hwmb->mb_id >> 18) & CAN_SFF_MASK;

			if (hwmb->mb_cs & MB_CS_RTR_MASK)
				frame->can_id |= CAN_RTR_FLAG;

			frame->can_dlc =
				(hwmb->mb_cs & MB_CS_LENGTH_MASK) >>
						MB_CS_LENGTH_OFFSET;

			if (frame->can_dlc && (frame->can_dlc <= 8))
				flexcan_memcpy(frame->data, hwmb->mb_data,
					       frame->can_dlc);
			tmp = __raw_readl(flexcan->io_base + CAN_HW_REG_TIMER);
		} else {
			tmp = hwmb->mb_cs;
			tmp = hwmb->mb_id;
			tmp = hwmb->mb_data[0];
			tmp = __raw_readl(flexcan->io_base + CAN_HW_REG_TIMER);
		}
	}

	if (iflag1 & (__FIFO_OV_INT | __FIFO_WARN_INT)) {
		if (skb) {
			frame = &skb->rb_frame;
			memset(frame, 0, sizeof(*frame));
			frame->can_id = CAN_ERR_FLAG | CAN_ERR_CRTL;
			frame->can_dlc = CAN_ERR_DLC;
			if (iflag1 & __FIFO_WARN_INT)
				frame->data[1] |=
				    CAN_ERR_CRTL_TX_WARNING |
				    CAN_ERR_CRTL_RX_WARNING;
			if (iflag1 & __FIFO_OV_INT)
				frame->data[1] |= CAN_ERR_CRTL_RX_OVERFLOW;
		}
	}
}

int rtcan_flexcan_mbm_isr(struct rtcan_device *dev,
			struct rtcan_flexcan *flexcan,
			struct rtcan_skb *skb,
			int *rcv_lock_free_ptr)
{
	int i, iflag1, iflag2, maxmb, retval;

	retval = 0;
	if (flexcan->maxmb > 31) {
		maxmb = flexcan->maxmb + 1 - 32;
		iflag1 = __raw_readl(flexcan->io_base + CAN_HW_REG_IFLAG1) &
		    __raw_readl(flexcan->io_base + CAN_HW_REG_IMASK1);
		iflag2 = __raw_readl(flexcan->io_base + CAN_HW_REG_IFLAG2) &
		    __raw_readl(flexcan->io_base + CAN_HW_REG_IMASK2);
		iflag2 &= (1 << maxmb) - 1;
		maxmb = 32;
	} else {
		maxmb = flexcan->maxmb + 1;
		iflag1 = __raw_readl(flexcan->io_base + CAN_HW_REG_IFLAG1) &
		    __raw_readl(flexcan->io_base + CAN_HW_REG_IMASK1);
		iflag1 &= (1 << maxmb) - 1;
		iflag2 = 0;
	}

	__raw_writel(iflag1, flexcan->io_base + CAN_HW_REG_IFLAG1);
	__raw_writel(iflag2, flexcan->io_base + CAN_HW_REG_IFLAG2);

	if (flexcan->fifo) { /*TODO: test this*/
		flexcan_fifo_isr(dev, flexcan, skb, iflag1);
		iflag1 &= 0xFFFFFF00;
	}
	for (i = 0; iflag1 && (i < maxmb); i++) {
		if (iflag1 & (1 << i)) {
			iflag1 &= ~(1 << i);
			retval += flexcan_mb_bottom(dev, flexcan, skb, i, rcv_lock_free_ptr);
		}
	}

	for (i = maxmb; iflag2 && (i <= flexcan->maxmb); i++) {
		if (iflag2 & (1 << (i - 32))) {
			iflag2 &= ~(1 << (i - 32));
			retval += flexcan_mb_bottom(dev, flexcan, skb, i, rcv_lock_free_ptr);
		}
	}
	return retval;
}

int rtcan_flexcan_mbm_xmit(struct rtcan_flexcan *flexcan, struct can_frame *cframe) /* NB no rtcan_rb_frame */
{
	int i = flexcan->xmit_mb;
	struct can_hw_mb *hwmb = flexcan->hwmb;

	do {
		if ((hwmb[i].mb_cs & MB_CS_CODE_MASK) >> MB_CS_CODE_OFFSET ==
							    CAN_MB_TX_INACTIVE)
			break;
		if ((++i) > flexcan->maxmb) {
			if (flexcan->fifo)
				i = FLEXCAN_MAX_FIFO_MB;
			else
				i = flexcan->xmit_maxmb + 1;
		}
		if (i == flexcan->xmit_mb)
			return -1;
	} while (1);

	flexcan->xmit_mb = i + 1;
	if (flexcan->xmit_mb > flexcan->maxmb) {
		if (flexcan->fifo)
			flexcan->xmit_mb = FLEXCAN_MAX_FIFO_MB;
		else
			flexcan->xmit_mb = flexcan->xmit_maxmb + 1;
	}

	if (cframe->can_id & CAN_RTR_FLAG)
		hwmb[i].mb_cs |= 1 << MB_CS_RTR_OFFSET;
	else
		hwmb[i].mb_cs &= ~MB_CS_RTR_MASK;

	if (cframe->can_id & CAN_EFF_FLAG) {
		hwmb[i].mb_cs |= 1 << MB_CS_IDE_OFFSET;
		hwmb[i].mb_cs |= 1 << MB_CS_SRR_OFFSET;
		hwmb[i].mb_id = cframe->can_id & CAN_EFF_MASK;
	} else {
		hwmb[i].mb_cs &= ~MB_CS_IDE_MASK;
		hwmb[i].mb_id = (cframe->can_id & CAN_SFF_MASK) << 18;
	}

	hwmb[i].mb_cs &= ~MB_CS_LENGTH_MASK;
	hwmb[i].mb_cs |= cframe->can_dlc << MB_CS_LENGTH_OFFSET;
	flexcan_memcpy(hwmb[i].mb_data, cframe->data, cframe->can_dlc);
	hwmb[i].mb_cs &= ~MB_CS_CODE_MASK;
	hwmb[i].mb_cs |= CAN_MB_TX_ONCE << MB_CS_CODE_OFFSET;
	return 0;
}

void rtcan_flexcan_mbm_init(struct rtcan_flexcan *flexcan)
{
	struct can_hw_mb *hwmb;
	int rx_mb, i;

	/* Set global mask to receive all messages */
	__raw_writel(0, flexcan->io_base + CAN_HW_REG_RXGMASK);
	__raw_writel(0, flexcan->io_base + CAN_HW_REG_RX14MASK);
	__raw_writel(0, flexcan->io_base + CAN_HW_REG_RX15MASK);

	memset(flexcan->hwmb, 0, sizeof(*hwmb) * FLEXCAN_MAX_MB);
	/* Set individual mask to receive all messages */
	memset(flexcan->rx_mask, 0, sizeof(unsigned int) * FLEXCAN_MAX_MB);

	if (flexcan->fifo)
		rx_mb = FLEXCAN_MAX_FIFO_MB;
	else
		rx_mb = flexcan->maxmb - flexcan->xmit_maxmb;

	hwmb = flexcan->hwmb;
	if (flexcan->fifo) {
		volatile unsigned long *id_table = flexcan->io_base + CAN_FIFO_BASE;
		for (i = 0; i < rx_mb; i++)
			id_table[i] = 0;
	} else {
		for (i = 0; i < rx_mb; i++) {
			hwmb[i].mb_cs &= ~MB_CS_CODE_MASK;
			hwmb[i].mb_cs |= CAN_MB_RX_EMPTY << MB_CS_CODE_OFFSET;
			/*
			 * IDE bit can not control by mask registers
			 * So set message buffer to receive extend
			 * or standard message.
			 */
			if (flexcan->ext_msg && flexcan->std_msg) {
				hwmb[i].mb_cs &= ~MB_CS_IDE_MASK;
				hwmb[i].mb_cs |= (i & 1) << MB_CS_IDE_OFFSET;
			} else {
				if (flexcan->ext_msg)
					hwmb[i].mb_cs |= 1 << MB_CS_IDE_OFFSET;
			}
		}
	}

	for (; i <= flexcan->maxmb; i++) {
		hwmb[i].mb_cs &= ~MB_CS_CODE_MASK;
		hwmb[i].mb_cs |= CAN_MB_TX_INACTIVE << MB_CS_CODE_OFFSET;
	}

	flexcan->xmit_mb = rx_mb;
}
