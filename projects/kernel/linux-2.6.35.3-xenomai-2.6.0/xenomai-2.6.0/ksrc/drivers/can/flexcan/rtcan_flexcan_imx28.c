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
 * based on xenomai-2.6.0/ksrc/drivers/can/sja1000/rtcan_mem.c
 * Copyright (C) 2006 Matthias Fuchs <matthias.fuchs@esd-electronics.com>,
 *                    Jan Kiszka <jan.kiszka@web.de>
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
#include <mach/pinctrl.h>
#include <mach/gpio.h>


//#include <arch/arm/mach-mx28/regs-clkctrl.h>
//#include <arch/arm/mach-mx28/mx28_pins.h>
#define HW_CLKCTRL_FLEXCAN           (0x00000160)
#define BM_CLKCTRL_FLEXCAN_STOP_CAN0 0x40000000
#define BM_CLKCTRL_FLEXCAN_STOP_CAN1 0x10000000
#define PINID_SSP1_CMD		MXS_PIN_ENCODE(2, 13)

#define RTCAN_IMX28_MAX_DEV 2

MODULE_AUTHOR("Francesco Mandracci <francesco.mandracci@gmail.com>");
MODULE_DESCRIPTION("RTCAN driver for FlexCAN on i.MX28");
MODULE_SUPPORTED_DEVICE(RTCAN_DRV_NAME);
MODULE_LICENSE("GPL");

struct rtcan_imx28
{
	u32 base_addr;
	u32 base_size;
};

static struct rtcan_device *rtcan_devs[RTCAN_IMX28_MAX_DEV];

static void rtcan_imx28_enable(struct rtcan_device *dev, int enable)
{
	struct rtcan_flexcan *chip = (struct rtcan_flexcan *)dev->priv;
	unsigned enable_reg, enable_bits, reg;

	enable_reg = IO_ADDRESS(CLKCTRL_PHYS_ADDR) + HW_CLKCTRL_FLEXCAN;
	if (chip->id == 0) {
		enable_bits = BM_CLKCTRL_FLEXCAN_STOP_CAN0;
	} else {
		enable_bits = BM_CLKCTRL_FLEXCAN_STOP_CAN1;
	}
	reg = __raw_readl(enable_reg);
	if (enable) {
		reg &= ~enable_bits;
#ifdef CONFIG_MECT_CUSTOMIZATION
		gpio_set_value(MXS_PIN_TO_GPIO(PINID_SSP1_CMD), 0);
#else
		gpio_set_value(MXS_PIN_TO_GPIO(PINID_SSP1_CMD), 1);
#endif
	} else {
		reg |= enable_bits;
#ifdef CONFIG_MECT_CUSTOMIZATION
		gpio_set_value(MXS_PIN_TO_GPIO(PINID_SSP1_CMD), 1);
#else
		gpio_set_value(MXS_PIN_TO_GPIO(PINID_SSP1_CMD), 0);
#endif
	}
	__raw_writel(reg, enable_reg);
}

int __init rtcan_imx28_init_one(int idx)
{
	struct rtcan_device *dev;
	struct rtcan_flexcan *chip;
	struct rtcan_imx28 *board;
	int ret;

	dev = rtcan_dev_alloc(sizeof(struct rtcan_flexcan),
                                   sizeof(struct rtcan_imx28));
	if (dev == NULL)
		return -ENOMEM;

	chip = (struct rtcan_flexcan *)dev->priv;
	board = (struct rtcan_imx28 *)dev->board_priv;

	dev->board_name = "iMX28";
	chip->irq_flags = RTDM_IRQTYPE_SHARED; /* FIXME */
	chip->enable = rtcan_imx28_enable;

	// arch/arm/mach-mx28/device.c
	chip->id = idx;
	chip->br_presdiv = 2;
	chip->br_rjw = 2;
	chip->br_propseg = 4;
	chip->br_pseg1 = 4;
	chip->br_pseg2 = 4;
	chip->srx_dis = 1;
	chip->bcc = 1;
	chip->br_clksrc = 1;
	chip->smp = 0;
	chip->boff_rec = 1;
	chip->ext_msg = 1;
	chip->std_msg = 1;

	// linux-2.6.35.3_ipipe/drivers/net/can/flexcan/dev.c
	chip->maxmb = FLEXCAN_MAX_MB - 1;
	chip->xmit_maxmb = (FLEXCAN_MAX_MB >> 1) - 1;
	chip->xmit_mb = chip->maxmb - chip->xmit_maxmb;
	// chip->wd1_resv = 0;
	chip->fifo = 0;
	// chip->wakeup = 0;
	// chip->wak_src = 0;
	// chip->lprio = 0;
	// chip->abort = 0;
	// chip->loopback = 0;
	// chip->tsyn = 0;
	// chip->listen = 0;

	switch (idx) {
	case 0:
		chip->irq_num = IRQ_CAN0;
		board->base_addr = CAN0_PHYS_ADDR;
		board->base_size = 0x2000;
		break;
	case 1:
		chip->irq_num = IRQ_CAN1;
		board->base_addr = CAN1_PHYS_ADDR;
		board->base_size = 0x2000;
		break;
	default:
		;
	}
	if (!request_mem_region(board->base_addr, board->base_size, RTCAN_DRV_NAME)) {
		ret = -EBUSY;
		goto out_dev_free;
	}
	/* ioremap io memory */
	if (!(chip->io_base = ioremap(board->base_addr, board->base_size))) {
		ret = -EBUSY;
		goto out_release_mem;
	}
	chip->hwmb = (struct can_hw_mb *)(chip->io_base + CAN_MB_BASE);
	chip->rx_mask = (unsigned int *)(chip->io_base + CAN_RXMASK_BASE);
	/* Clock frequency in Hz */
	dev->can_sys_clock = 24000000; /* XTALCLK 0 24MHz */
	/* Registration */
	strncpy(dev->name, RTCAN_DEV_NAME, IFNAMSIZ);
	ret = rtcan_flexcan_register(dev);
	if (ret) {
		printk(KERN_ERR "ERROR %d while trying to register FLEXCAN "
		       "device!\n", ret);
		goto out_iounmap;
	}
	rtcan_devs[idx] = dev;
	return 0;

 out_iounmap:
	iounmap((void *)chip->io_base);

 out_release_mem:
	release_mem_region(board->base_addr, board->base_size);

 out_dev_free:
	rtcan_dev_free(dev);

	return ret;
}

static void rtcan_flexcan_imx28_exit(void);

/** Init module */
static int __init rtcan_flexcan_imx28_init(void)
{
	int i, err;
	int devices = 0;

	for (i = 0; i < RTCAN_IMX28_MAX_DEV; i++) {
		err = rtcan_imx28_init_one(i);
		if (err) {
			rtcan_flexcan_imx28_exit();
			return err;
		}
		devices++;
	}
	if (devices)
		return 0;
	return -EINVAL;
}


/** Cleanup module */
static void rtcan_flexcan_imx28_exit(void)
{
	int i;
	struct rtcan_device *dev;

	for (i = 0; i < RTCAN_IMX28_MAX_DEV; i++) {
		struct rtcan_flexcan *chip;
		struct rtcan_imx28 *board;

		dev = rtcan_devs[i];
		if (!dev)
			continue;
		chip = (struct rtcan_flexcan *)dev->priv;
		board = (struct rtcan_imx28 *)dev->board_priv;
		rtcan_flexcan_unregister(dev);
		iounmap(chip->io_base);
		release_mem_region(board->base_addr, board->base_size);
		rtcan_dev_free(dev);
	}
}

module_init(rtcan_flexcan_imx28_init);
module_exit(rtcan_flexcan_imx28_exit);
