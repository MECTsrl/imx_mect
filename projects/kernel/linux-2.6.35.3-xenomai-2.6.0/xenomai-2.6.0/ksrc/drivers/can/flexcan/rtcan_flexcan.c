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
 * based on xenomai-2.6.0/ksrc/drivers/net/can/sja1000/rtcan_sja1000.c
 * Copyright (C) 2005, 2006 Sebastian Smolorz
 *                          <Sebastian.Smolorz@stud.uni-hannover.de>
 * Copyright (C) 2006 Wolfgang Grandegger <wg@grandegger.com>
 *
 * based on linux-2.6.35/drivers/net/can/flexcan/{dev,drv,mbm}.c
 * Copyright 2008-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#include <linux/module.h>

#include <rtdm/rtdm_driver.h>
#include <rtdm/rtcan.h>

#include <rtcan_socket.h>
#include <rtcan_dev.h>
#include <rtcan_raw.h>
#include <rtcan_list.h>

#include "rtcan_flexcan_regs.h"
#include "rtcan_flexcan.h"

static char *flexcan_ctrl_name = RTCAN_DRV_NAME;

MODULE_AUTHOR("Francesco Mandracci <francesco.mandracci@gmail.com>");
MODULE_DESCRIPTION("RTCAN driver for FlexCAN ");
MODULE_SUPPORTED_DEVICE(RTCAN_DRV_NAME);
MODULE_LICENSE("GPL");

/* NB see linux-2.6.35/drivers/net/can/flexcan/{dev,drv,mbm}.c with
 * "struct flexcan_device *flexcan" =---> "struct rtcan_flexcan *flexcan"
 */

#define STATE_OPERATING(state) \
    ((state) != CAN_STATE_STOPPED && (state) != CAN_STATE_BUS_OFF)

#define STATE_RESET(state) \
    ((state) == CAN_STATE_STOPPED || (state) == CAN_STATE_BUS_OFF)

static void flexcan_hw_start(struct rtcan_flexcan *flexcan)
{
	unsigned int reg;
	if ((flexcan->maxmb + 1) > 32) {
		__raw_writel(0xFFFFFFFF, flexcan->io_base + CAN_HW_REG_IMASK1);
		reg = (1 << (flexcan->maxmb - 31)) - 1;
		__raw_writel(reg, flexcan->io_base + CAN_HW_REG_IMASK2);
	} else {
		reg = (1 << (flexcan->maxmb + 1)) - 1;
		__raw_writel(reg, flexcan->io_base + CAN_HW_REG_IMASK1);
		__raw_writel(0, flexcan->io_base + CAN_HW_REG_IMASK2);
	}

	reg = __raw_readl(flexcan->io_base + CAN_HW_REG_MCR) & (~__MCR_HALT);
	__raw_writel(reg, flexcan->io_base + CAN_HW_REG_MCR);
}

static void flexcan_hw_stop(struct rtcan_flexcan *flexcan)
{
	unsigned int reg;
	reg = __raw_readl(flexcan->io_base + CAN_HW_REG_MCR);
	__raw_writel(reg | __MCR_HALT, flexcan->io_base + CAN_HW_REG_MCR);
}

static inline void rtcan_flexcan_enable(struct rtcan_device *dev)
{
	struct rtcan_flexcan *chip = (struct rtcan_flexcan *)dev->priv;

	chip->enable(dev, 1);
}

static inline void rtcan_flexcan_disable(struct rtcan_device *dev)
{
	struct rtcan_flexcan *chip = (struct rtcan_flexcan *)dev->priv;
	
	chip->enable(dev, 0);
}

static inline void rtcan_flexcan_err_interrupt(struct rtcan_device *dev,
					     struct rtcan_flexcan *flexcan,
					     struct rtcan_skb *skb,
					     unsigned int r_status)
{
	struct rtcan_rb_frame *frame = &skb->rb_frame;
	can_state_t state = dev->state;	
	unsigned int esr, ecr;

	// reading the ESR register seems necessary even if the manual states otherwise
	 esr = r_status;
	//esr = __raw_readl(flexcan->io_base + CAN_HW_REG_ESR);
	__raw_writel(esr & __ESR_INTERRUPTS, flexcan->io_base + CAN_HW_REG_ESR);

	skb->rb_frame_size = EMPTY_RB_FRAME_SIZE + CAN_ERR_DLC;
	frame->can_id = CAN_ERR_FLAG | CAN_ERR_CRTL;
	frame->can_dlc = CAN_ERR_DLC;
	memset(&frame->data[0], 0, frame->can_dlc);

	/* Data overrun interrupt? */
	/* Arbitratio lost interrupt? */
	/* TODO: check these */

	if (esr & __ESR_BOFF_INT) {
		state = CAN_STATE_BUS_OFF;
		frame->can_id |= CAN_ERR_BUSOFF;
		/* Wake up waiting senders */
		rtdm_sem_destroy(&dev->tx_sem);
        } else if (esr & __ESR_WAK_INT) {
                state = dev->state_before_sleep;
	} else if (esr & __ESR_TWRN_INT || esr & __ESR_RWRN_INT) {
		state = CAN_STATE_BUS_WARNING;
		if (esr & __ESR_TWRN_INT) {
			frame->data[1] |= CAN_ERR_CRTL_TX_WARNING;
		}
		if (esr & __ESR_RWRN_INT) {
			frame->data[1] |= CAN_ERR_CRTL_RX_WARNING;
		}
	} else if (esr & __ESR_ERR_INT) {
		/* Bus error interrupt? */
		state = CAN_STATE_BUS_WARNING;
		frame->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

		if (esr & __ESR_BIT1_ERR)
			frame->data[2] |= CAN_ERR_PROT_BIT1;

		if (esr & __ESR_BIT0_ERR)
			frame->data[2] |= CAN_ERR_PROT_BIT0;

		if (esr & __ESR_ACK_ERR)
			frame->can_id |= CAN_ERR_ACK;

		/*TODO:// if (esr & __ESR_CRC_ERR) */

		if (esr & __ESR_FRM_ERR)
			frame->data[2] |= CAN_ERR_PROT_FORM;

		if (esr & __ESR_STF_ERR)
			frame->data[2] |= CAN_ERR_PROT_STUFF;

		ecr = __raw_readl(flexcan->io_base + CAN_HW_REG_ECR);
		switch ((esr & __ESR_FLT_CONF_MASK) >> __ESR_FLT_CONF_OFF) {
		case 0:
			if (__ECR_TX_ERR_COUNTER(ecr) >= __ECR_ACTIVE_THRESHOLD)
				frame->data[1] |= CAN_ERR_CRTL_TX_WARNING;
			if (__ECR_RX_ERR_COUNTER(ecr) >= __ECR_ACTIVE_THRESHOLD)
				frame->data[1] |= CAN_ERR_CRTL_RX_WARNING;
			break;
		case 1:
			if (__ECR_TX_ERR_COUNTER(ecr) >=
			    __ECR_PASSIVE_THRESHOLD)
				frame->data[1] |= CAN_ERR_CRTL_TX_PASSIVE;

			if (__ECR_RX_ERR_COUNTER(ecr) >=
			    __ECR_PASSIVE_THRESHOLD)
				frame->data[1] |= CAN_ERR_CRTL_RX_PASSIVE;
			break;
		default:
			frame->can_id |= CAN_ERR_BUSOFF;
		}
	/* Re-entrance into error active state from bus-warn? */
	} else if (state == CAN_STATE_BUS_WARNING) {
	    state = CAN_STATE_ACTIVE;

	} else {
	    /* Bus-off recovery complete, enable all interrupts again */
	    /*TODO: check bus off condition*/
	}

    dev->state = state;
    frame->can_ifindex = dev->ifindex;
}

static int rtcan_flexcan_interrupt(rtdm_irq_t *irq_handle)
{
    struct rtcan_device *dev;
    struct rtcan_flexcan *flexcan;
    struct rtcan_skb skb;
    int recv_lock_free = 1;
    int ret = RTDM_IRQ_NONE;
    unsigned int reg;
    int tx, i;

    memset(&skb, 0, sizeof(skb));
    /* Get the ID of the device which registered this IRQ. */
    dev = (struct rtcan_device *)rtdm_irq_get_arg(irq_handle, void);
    flexcan = (struct rtcan_flexcan *)dev->priv;

    /* Take spinlock protecting HW register access and device structures. */
    rtdm_lock_get(&dev->device_lock);

    reg = __raw_readl(flexcan->io_base + CAN_HW_REG_ESR);

    /* Error Interrupt? */
    if (reg & __ESR_INTERRUPTS) {
        ret = RTDM_IRQ_HANDLED;
    	rtcan_flexcan_err_interrupt(dev, flexcan, &skb, reg);
        if (!(reg & __ESR_BOFF_INT)) {
	    if (recv_lock_free) {
	        recv_lock_free = 0;
	        rtdm_lock_get(&rtcan_recv_list_lock);
	        rtdm_lock_get(&rtcan_socket_lock);
	    }
	    /* Pass error frame out to the sockets */
	    rtcan_rcv(dev, &skb);
	}
    }

    /* Transmit or Receive Interrupt? */
    ret = RTDM_IRQ_HANDLED;
    /* rtcan_flexcan_mbm_isr() -> flexcan_mb_bottom() -> rtcan_rcv()+rtdm_lock_get() */
    tx = rtcan_flexcan_mbm_isr(dev, flexcan, &skb, &recv_lock_free);
    
    /* Transmit Interrupt? */
    for (i = 0; i < tx; ++i) {
        /* Wake up a sender */
        rtdm_sem_up(&dev->tx_sem);
    
        if (rtcan_loopback_pending(dev)) {
		if (recv_lock_free) {
		    recv_lock_free = 0;
		    rtdm_lock_get(&rtcan_recv_list_lock);
		    rtdm_lock_get(&rtcan_socket_lock);
		}
		rtcan_loopback(dev);
        }
    }
    if (flexcan->irq_ack)
	flexcan->irq_ack(dev);

    /* Release spinlocks */
    if (!recv_lock_free) {
	rtdm_lock_put(&rtcan_socket_lock);
	rtdm_lock_put(&rtcan_recv_list_lock);
    }
    rtdm_lock_put(&dev->device_lock);
    return ret;
}

static inline void flexcan_ctrl_setup(struct rtcan_flexcan *flexcan)
{
	unsigned int reg;

	reg = __raw_readl(flexcan->io_base + CAN_HW_REG_CTRL);
	reg &= ~(__CTRL_PRESDIV_MASK | __CTRL_RJW_MASK | __CTRL_PSEG1_MASK |
		 __CTRL_PSEG2_MASK | __CTRL_PROPSEG_MASK);

	if (flexcan->loopback)
		reg |= __CTRL_LPB;
	else
		reg &= ~__CTRL_LPB;

	if (flexcan->smp)
		reg |= __CTRL_SMP;
	else
		reg &= ~__CTRL_SMP;

	if (flexcan->boff_rec)
		reg |= __CTRL_BOFF_REC;
	else
		reg &= ~__CTRL_BOFF_REC;

	if (flexcan->tsyn)
		reg |= __CTRL_TSYN;
	else
		reg &= ~__CTRL_TSYN;

	if (flexcan->listen)
		reg |= __CTRL_LOM;
	else
		reg &= ~__CTRL_LOM;

	reg |= (flexcan->br_presdiv << __CTRL_PRESDIV_OFFSET) |
	    (flexcan->br_rjw << __CTRL_RJW_OFFSET) |
	    (flexcan->br_pseg1 << __CTRL_PSEG1_OFFSET) |
	    (flexcan->br_pseg2 << __CTRL_PSEG2_OFFSET) |
	    (flexcan->br_propseg << __CTRL_PROPSEG_OFFSET);

	reg &= ~__CTRL_LBUF;

	//reg |= __CTRL_TWRN_MSK | __CTRL_RWRN_MSK | __CTRL_BOFF_MSK |
	//    __CTRL_ERR_MSK;
	reg &= ~(__CTRL_TWRN_MSK | __CTRL_RWRN_MSK | __CTRL_BOFF_MSK |
	    __CTRL_ERR_MSK);

	__raw_writel(reg, flexcan->io_base + CAN_HW_REG_CTRL);
}

static int rtcan_flexcan_mode_stop(struct rtcan_device *dev,
				 rtdm_lockctx_t *lock_ctx)
{
	struct rtcan_flexcan *flexcan = (struct rtcan_flexcan *)dev->priv;
	can_state_t state;

	state = dev->state;
	if (STATE_RESET(state))
		goto out;
	flexcan_hw_stop(flexcan);
	dev->state = CAN_STATE_STOPPED;
	rtdm_sem_destroy(&dev->tx_sem);
out:
	return 0;
}

static int rtcan_flexcan_mode_start(struct rtcan_device *dev,
				  rtdm_lockctx_t *lock_ctx)
{
    int ret = 0;
    struct rtcan_flexcan *chip = (struct rtcan_flexcan *)dev->priv;

    if (dev->ctrl_mode & CAN_CTRLMODE_LISTENONLY)
        ; /* FIXME return error */
    if (dev->ctrl_mode & CAN_CTRLMODE_LOOPBACK)
        ; /* FIXME return error */

    switch (dev->state) {

    case CAN_STATE_ACTIVE:
    case CAN_STATE_BUS_WARNING:
    case CAN_STATE_BUS_PASSIVE:
        break;

    case CAN_STATE_STOPPED:
    case CAN_STATE_BUS_OFF:
	flexcan_hw_start(chip);
        dev->state = CAN_STATE_ACTIVE;
        rtdm_sem_init(&dev->tx_sem, 1);
        break;

    case CAN_STATE_SLEEPING:
	/* TODO */
        break;

    default:
        ;
    }
    return ret;
}

static int rtcan_flexcan_set_bit_time(struct rtcan_device *dev,
				    struct can_bittime *bit_time,
				    rtdm_lockctx_t *lock_ctx)
{
    struct rtcan_flexcan *flexcan = (struct rtcan_flexcan *)dev->priv;

    switch (bit_time->type) {
    case CAN_BITTIME_BTR:
	return -EINVAL;

    case CAN_BITTIME_STD:
	flexcan->br_presdiv = bit_time->std.brp;
	flexcan->br_rjw = bit_time->std.sjw;
	flexcan->br_pseg1 = bit_time->std.phase_seg1;
	flexcan->br_pseg2 = bit_time->std.phase_seg2;
	flexcan->br_propseg = bit_time->std.prop_seg;
	/* ignore triple sampling bit_time->std.sam; */
	break;

    default:
	return -EINVAL;
    }

    flexcan_ctrl_setup(flexcan);
    return 0;
}

static int rtcan_flexcan_start_xmit(struct rtcan_device *dev, can_frame_t *cframe)
{
	struct rtcan_flexcan *flexcan = (struct rtcan_flexcan *)dev->priv;
	
	if (cframe->can_dlc > 8) {
		return -EINVAL;
	}
	if (rtcan_flexcan_mbm_xmit(flexcan, cframe) < 0) {
		return -EIO;
	}
	return 0;
}

static int flexcan_hw_reset(struct rtcan_flexcan *flexcan)
{
	unsigned int reg;
	int timeout = 100000;

	reg = __raw_readl(flexcan->io_base + CAN_HW_REG_MCR);
	__raw_writel(reg | __MCR_MDIS, flexcan->io_base + CAN_HW_REG_MCR);

	reg = __raw_readl(flexcan->io_base + CAN_HW_REG_CTRL);
	if (flexcan->br_clksrc)
		reg |= __CTRL_CLK_SRC;
	else
		reg &= ~__CTRL_CLK_SRC;
	__raw_writel(reg, flexcan->io_base + CAN_HW_REG_CTRL);

	reg = __raw_readl(flexcan->io_base + CAN_HW_REG_MCR) & (~__MCR_MDIS);
	__raw_writel(reg, flexcan->io_base + CAN_HW_REG_MCR);
	reg |= __MCR_SOFT_RST;
	__raw_writel(reg, flexcan->io_base + CAN_HW_REG_MCR);

	reg = __raw_readl(flexcan->io_base + CAN_HW_REG_MCR);
	while (reg & __MCR_SOFT_RST) {
		if (--timeout <= 0) {
			printk(KERN_ERR "Flexcan software Reset Timeouted\n");
			return -1;
		}
		udelay(10);
		reg = __raw_readl(flexcan->io_base + CAN_HW_REG_MCR);
	}
	return 0;
}

static inline void flexcan_mcr_setup(struct rtcan_flexcan *flexcan)
{
	unsigned int reg;

	reg = __raw_readl(flexcan->io_base + CAN_HW_REG_MCR);
	reg &= ~(__MCR_MAX_MB_MASK | __MCR_WAK_MSK | __MCR_MAX_IDAM_MASK);

	if (flexcan->fifo)
		reg |= __MCR_FEN;
	else
		reg &= ~__MCR_FEN;

	if (flexcan->wakeup)
		reg |= __MCR_SLF_WAK | __MCR_WAK_MSK;
	else
		reg &= ~(__MCR_SLF_WAK | __MCR_WAK_MSK);

	if (flexcan->wak_src)
		reg |= __MCR_WAK_SRC;
	else
		reg &= ~__MCR_WAK_SRC;

	if (flexcan->srx_dis)
		reg |= __MCR_SRX_DIS;
	else
		reg &= ~__MCR_SRX_DIS;

	if (flexcan->bcc)
		reg |= __MCR_BCC;
	else
		reg &= ~__MCR_BCC;

	if (flexcan->lprio)
		reg |= __MCR_LPRIO_EN;
	else
		reg &= ~__MCR_LPRIO_EN;

	if (flexcan->abort)
		reg |= __MCR_AEN;
	else
		reg &= ~__MCR_AEN;

	reg |= (flexcan->maxmb << __MCR_MAX_MB_OFFSET);
	reg |= __MCR_DOZE | __MCR_MAX_IDAM_C;
	__raw_writel(reg, flexcan->io_base + CAN_HW_REG_MCR);
}

static int flexcan_hw_open(struct rtcan_flexcan *flexcan)
{
	if (flexcan_hw_reset(flexcan))
		return -EFAULT;

	flexcan_mcr_setup(flexcan);
	flexcan_ctrl_setup(flexcan);

	__raw_writel(0, flexcan->io_base + CAN_HW_REG_IMASK2);
	__raw_writel(0, flexcan->io_base + CAN_HW_REG_IMASK1);

	__raw_writel(0xFFFFFFFF, flexcan->io_base + CAN_HW_REG_IFLAG2);
	__raw_writel(0xFFFFFFFF, flexcan->io_base + CAN_HW_REG_IFLAG1);

	__raw_writel(0, flexcan->io_base + CAN_HW_REG_ECR);
	return 0;
}

static int flexcan_chip_config(struct rtcan_device *dev)
{
	struct rtcan_flexcan *flexcan = (struct rtcan_flexcan *)dev->priv;

	
	if (flexcan_hw_open(flexcan))
		return -1;
	rtcan_flexcan_mbm_init(flexcan);
	flexcan_hw_start(flexcan);
	return 0;
}

static inline int rtcan_flexcan_is_operating(struct rtcan_device *dev,
					 can_state_t *state)
{
    int is_operating = STATE_OPERATING(*state);
#if 0
    struct rtcan_flexcan *flexcan = (struct rtcan_flexcan *)dev->priv;

    /* this won't work in real-time because there's not enough time for the
       FlexCAN hw module to initialize, so "unlikely" becomes "always" :(
    */
    if (unlikely(is_operating &&
	__raw_readl(flexcan->io_base + CAN_HW_REG_MCR) & (~__MCR_NOTRDY))) {
	*state = CAN_STATE_STOPPED;
	is_operating = 0;
	/* Disable the controller's interrupts */
	__raw_writel(0, flexcan->io_base + CAN_HW_REG_IMASK2);
	__raw_writel(0, flexcan->io_base + CAN_HW_REG_IMASK1);
	/* Wake up waiting senders */
	rtdm_sem_destroy(&dev->tx_sem);
    }
#endif
    return is_operating;
}

static can_state_t rtcan_flexcan_get_state(struct rtcan_device *dev)
{
    can_state_t state = dev->state;
    rtcan_flexcan_is_operating(dev, &state);
    return state;
}

static int rtcan_flexcan_set_mode(struct rtcan_device *dev,
		       can_mode_t mode,
		       rtdm_lockctx_t *lock_ctx)
{
    int ret = 0;
    can_state_t state;
    struct rtcan_flexcan *flexcan = (struct rtcan_flexcan*)dev->priv;

    switch (mode) {

    case CAN_MODE_STOP:
	ret = rtcan_flexcan_mode_stop(dev, lock_ctx);
	break;

    case CAN_MODE_START:
	ret = rtcan_flexcan_mode_start(dev, lock_ctx);
	break;

    case CAN_MODE_SLEEP:

	state = dev->state;

	/* Controller must operate, otherwise go out */
	if (!rtcan_flexcan_is_operating(dev, &state)) {
	    ret = -ENETDOWN;
	    goto mode_sleep_out;
	}

	/* Is controller sleeping yet? If yes, go out */
	if (state == CAN_STATE_SLEEPING)
	    goto mode_sleep_out;

	/* Remember into which state to return when we
	 * wake up */
	dev->state_before_sleep = state;

	/* Let's take a nap. (Now I REALLY understand
	 * the meaning of interrupts ...) */
	state = CAN_STATE_SLEEPING;
	flexcan_hw_stop(flexcan);

    mode_sleep_out:
	dev->state = state;
	break;

    default:
	ret = -EOPNOTSUPP;
	break;
    }

    return ret;
}

int rtcan_flexcan_register(struct rtcan_device *dev)
{
	int ret;
	struct rtcan_flexcan *chip;

	if (dev == NULL)
		return -EINVAL;
	chip = (struct rtcan_flexcan *)dev->priv;
	if (chip == NULL)
		return -EINVAL;

	/* Enable FlexCAN module */
	rtcan_flexcan_enable(dev);

	/* Enter reset mode */
	dev->state = CAN_STATE_ACTIVE;
	rtcan_flexcan_mode_stop(dev, NULL);

	dev->ctrl_name = flexcan_ctrl_name;
	dev->hard_start_xmit = rtcan_flexcan_start_xmit;
	dev->do_set_mode = rtcan_flexcan_set_mode;
	dev->do_get_state = rtcan_flexcan_get_state;
	dev->do_set_bit_time = rtcan_flexcan_set_bit_time;

	ret = rtdm_irq_request(&dev->irq_handle, chip->irq_num,
				rtcan_flexcan_interrupt, chip->irq_flags,
				dev->ctrl_name, (void *)dev);
	if (ret) {
		printk(KERN_ERR "ERROR %d: rtdm_irq_request(%d) failed\n",
			ret, chip->irq_num);
		goto out_can_disable;
	}
	/* Configure FlexCAN module */
	if (flexcan_chip_config(dev)) {
		printk(KERN_ERR
		       "ERROR while trying to configure FlexCAN device!\n");
		goto out_irq_free;
	}

	/* Register RTDM device */
	ret = rtcan_dev_register(dev);
	if (ret) {
		printk(KERN_ERR
		       "ERROR while trying to register RTCAN device!\n");
		goto out_irq_free;
	}
	rtcan_flexcan_create_proc(dev);
	return 0;

out_irq_free:
	rtdm_irq_free(&dev->irq_handle);
out_can_disable:
	/* Disable FLEXCAN module. */
	rtcan_flexcan_disable(dev);
	return ret;
}

void rtcan_flexcan_unregister(struct rtcan_device *dev)
{
	struct rtcan_flexcan *chip;

	if (dev == NULL)
		return;
	chip = (struct rtcan_flexcan *)dev->priv;
	if (chip == NULL)
		return;

	printk("Unregistering %s device %s\n", RTCAN_DRV_NAME, dev->name);
	rtdm_irq_disable(&dev->irq_handle);
	rtcan_flexcan_mode_stop(dev, NULL);
	rtdm_irq_free(&dev->irq_handle);
	rtcan_flexcan_remove_proc(dev);
	rtcan_flexcan_disable(dev);
	rtcan_dev_unregister(dev);
}

int __init rtcan_flexcan_init(void)
{
    printk("RTCAN %s driver initialized\n", RTCAN_DRV_NAME);
    return 0;
}

void __exit rtcan_flexcan_exit(void)
{
    printk("RTCAN %s driver removed\n", RTCAN_DRV_NAME);
}

module_init(rtcan_flexcan_init);
module_exit(rtcan_flexcan_exit);

EXPORT_SYMBOL_GPL(rtcan_flexcan_register);
EXPORT_SYMBOL_GPL(rtcan_flexcan_unregister);
