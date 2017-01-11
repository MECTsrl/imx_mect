/*
 * Copyright 2016 MECT s.r.l. <info@mect.it>
 *
 * Derived from Freescale STMP37XX/STMP378X Application UART driver.
 *
 * Author: Mihai Lazarescu <mlazarescu@mect.it>
 *
 * Copyright 2012 Wolfgang Grandegger <wg@denx.de>
 * Copyright 2008-2010 Freescale Semiconductor, Inc.
 * Copyright 2008 Embedded Alley Solutions, Inc All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/serial.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/clk.h>
#include <linux/cpufreq.h>
#include <linux/delay.h>
#include <linux/uaccess.h>

#include <asm/cacheflush.h>

#include <mach/hardware.h>
#include <mach/device.h>

#include <rtdm/rtserial.h>
#include <rtdm/rtdm_driver.h>
#include <native/alarm.h>
#include <native/task.h>

#include "regs-uartapp.h"


#define DRIVER_NAME		"xeno_imx_mxs_auart"

#define AUART_FIFO_SIZE		16
#define IN_BUFFER_SIZE		4096
#define OUT_BUFFER_SIZE		4096

#define IER_RX			0x01
#define IER_TX			0x02
#define IER_STAT		0x04
#define IER_MODEM		0x08

struct rt_imx_mxs_auart_port {
	struct uart_port port;

	unsigned int flags;
	unsigned int irq[3];
	unsigned int use_hwflow;

	struct clk *clk;
	struct device *dev;
	struct list_head rx_done;
	struct list_head free;
	struct tasklet_struct rx_task;
	struct rtdm_device rtdm_dev;		/* RTDM device structure */
};

struct rt_imx_mxs_auart_ctx {
	struct rtser_config config;		/* current device configuration */

	rtdm_irq_t irq_handle;			/* device IRQ handle */
	rtdm_lock_t lock;			/* lock to protect context struct */

	int in_head;				/* RX ring buffer, head pointer */
	int in_tail;				/* RX ring buffer, tail pointer */
	size_t in_npend;			/* pending bytes in RX ring */
	int in_nwait;				/* bytes the user waits for */
	rtdm_event_t in_event;			/* raised to unblock reader */
	char in_buf[IN_BUFFER_SIZE];		/* RX ring buffer */
	volatile unsigned long in_lock; 	/* single-reader lock */
	uint64_t *in_history;			/* RX timestamp buffer */

	int out_head;				/* TX ring buffer, head pointer */
	int out_tail;				/* TX ring buffer, tail pointer */
	size_t out_npend;			/* pending bytes in TX ring */
	rtdm_event_t out_event;			/* raised to unblock writer */
	char out_buf[OUT_BUFFER_SIZE];		/* TX ring buffer */
	rtdm_mutex_t out_lock;			/* single-writer mutex */

	uint64_t last_timestamp;		/* timestamp of last event */
	int ioc_events;				/* recorded events */
	rtdm_event_t ioc_event;			/* raised to unblock event waiter */
	volatile unsigned long ioc_event_lock;	/* single-waiter lock */

	int ier_status;				/* IER cache */
	int mcr_status;				/* MCR cache */
	int status;				/* cache for LSR + soft-states */
	int saved_errors;			/* error cache for RTIOC_GET_STATUS */

	/*
	 * The port structure holds all the information about the UART
	 * port like base address, and so on.
	 */
	struct rt_imx_mxs_auart_port *port;

	/* Flags for driver-side handling the RTS line in RS485 mode. */
#define RS485_RTS_RQ_MASK	0x0001		/* The driver operates in RS485 mode. */
#define RS485_RTS_AL_MASK	0x0002		/* The alarm for RTS timing exists. */
	uint32_t rs485;				/* Flags for RS485 mode */

	RTIME char_time_ns; 			/* one character time in ns on wire */
	RT_ALARM rts_deassert;			/* Xenomai alarm to time RTS deassert */
};

#define PARITY_MASK		0x03
#define DATA_BITS_MASK		0x03
#define STOP_BITS_MASK		0x01
#define FIFO_MASK		0xC0
#define EVENT_MASK		0x0F

static const struct rtser_config default_config = {
	.config_mask = 0xFFFF,
	.baud_rate = RTSER_DEF_BAUD,
	.parity = RTSER_DEF_PARITY,
	.data_bits = RTSER_DEF_BITS,
	.stop_bits = RTSER_DEF_STOPB,
	.handshake = RTSER_DEF_HAND,
	.fifo_depth = RTSER_DEF_FIFO_DEPTH,
	.rx_timeout = RTSER_DEF_TIMEOUT,
	.tx_timeout = RTSER_DEF_TIMEOUT,
	.event_timeout = RTSER_DEF_TIMEOUT,
	.timestamp_history = RTSER_DEF_TIMESTAMP_HISTORY,
	.event_mask = RTSER_DEF_EVENT_MASK,
	.mect_rts = RTSER_MECT_RTS_CLR
};

static int rt_imx_mxs_auart_set_config(struct rt_imx_mxs_auart_ctx *ctx, const struct rtser_config *config, uint64_t **in_history_ptr);


void rts_deassert_func(struct rt_alarm *rts_deassert, void *data)
{
	struct rt_imx_mxs_auart_ctx *ctx = (struct rt_imx_mxs_auart_ctx *)data;

	if (!(__raw_readl(ctx->port->port.membase + HW_UARTAPP_STAT) & BM_UARTAPP_STAT_BUSY)) {
		rt_alarm_stop(&ctx->rts_deassert);

		/* TX completed. Deassert RTS and enable RX. */
		__raw_writel((BM_UARTAPP_CTRL2_RTS), ctx->port->port.membase + HW_UARTAPP_CTRL2_SET);
		__raw_writel((BM_UARTAPP_CTRL2_RXE), ctx->port->port.membase + HW_UARTAPP_CTRL2_SET);

		rtdm_event_signal(&ctx->out_event);
	}
}

static inline struct rt_imx_mxs_auart_port *
to_auart_port(struct uart_port *u)
{
	return container_of(u, struct rt_imx_mxs_auart_port, port);
}

static inline void
rt_imx_mxs_auart_tx_chars(struct rt_imx_mxs_auart_ctx *ctx)
{
	struct rt_imx_mxs_auart_port *port = ctx->port;
	int count;
	int ch;

	if (!testbits(ctx->ier_status, IER_TX))
		return;		// spurious interrupt

	/* Transfer pending bytes to TX FIFO. */
	count = 0;
	while (!(__raw_readl(port->port.membase + HW_UARTAPP_STAT) & BM_UARTAPP_STAT_TXFF)) {
		if (ctx->out_npend == 0)
			break;

		ch = ctx->out_buf[ctx->out_head++];
		__raw_writel(ch, port->port.membase + HW_UARTAPP_DATA);

		ctx->out_head &= (OUT_BUFFER_SIZE - 1);
		++count;
		--ctx->out_npend;
	}

	if (ctx->out_npend > 0) {
		__raw_writel(BM_UARTAPP_INTR_TXIEN, port->port.membase + HW_UARTAPP_INTR_SET);
	} else {
		__raw_writel(BM_UARTAPP_INTR_TXIEN, port->port.membase + HW_UARTAPP_INTR_CLR);
		ctx->ier_status &= ~IER_TX;
		if (ctx->rs485 & RS485_RTS_RQ_MASK) {
			if (ctx->rs485 & RS485_RTS_AL_MASK) {
				/* Deassert RTS at most one frame after the TX FIFO and SR are flushed. */
				RTIME value = count * ctx->char_time_ns;
				// RTIME interval = TM_INFINITE; /* the alarm will not be reloaded after it has expired */
				RTIME interval = ctx->char_time_ns;
				if (value < 50000)
					value = 50000; // i.MX28 limit

				if (interval < 50000)
					interval = 50000; // i.MX28 limit

				rt_alarm_start(&ctx->rts_deassert, value, interval);
				//rtdm_printk("%s(%d): start in %llu at %llu\n", DRIVER_NAME, ctx->port->port.line, value, interval);
			} else {
				rtdm_printk("%s(%d): alarm for RTS line timing not defined.\n", DRIVER_NAME, ctx->port->port.line);
				rtdm_event_signal(&ctx->out_event);
			}
		} else {
			rtdm_event_signal(&ctx->out_event);
		}
	}
}

static int
rt_imx_mxs_auart_rx_chars(struct rt_imx_mxs_auart_ctx *ctx, uint64_t *timestamp)
{
	struct rt_imx_mxs_auart_port *port = ctx->port;
	u32 stat = 0;
	int rbytes = 0;
	int lsr = 0;

	/* we are here if RX data ready or RX timeout or RX errors
	 * i.e. (BM_UARTAPP_INTR_OEIS | BM_UARTAPP_INTR_BEIS | BM_UARTAPP_INTR_PEIS | BM_UARTAPP_INTR_FEIS
	 *     | BM_UARTAPP_INTR_RXISk | BM_UARTAPP_INTR_RTIS)
	 */
	do {
		register u32 data;
		register int n;
		register int invalid_chars;

		data = __raw_readl(port->port.membase + HW_UARTAPP_DATA);
		stat = __raw_readl(port->port.membase + HW_UARTAPP_STAT);

		/* flags management, relative to the previous read HW_UARTAPP_DATA */
		if (stat & BM_UARTAPP_STAT_BERR) {
			/* NOTE Here we ignore break requests. */
			stat &= ~BM_UARTAPP_STAT_BERR;
			ctx->port->port.icount.brk++;
			lsr |= RTSER_LSR_BREAK_IND;
		}

		if (stat & BM_UARTAPP_STAT_PERR) {
			stat &= ~BM_UARTAPP_STAT_PERR;
			port->port.icount.parity++;
			lsr |= RTSER_LSR_PARITY_ERR;
		}

		if (stat & BM_UARTAPP_STAT_FERR) {
			stat &= ~BM_UARTAPP_STAT_FERR;
			port->port.icount.frame++;
			lsr |= RTSER_LSR_FRAMING_ERR;
		}

		if (stat & BM_UARTAPP_STAT_OERR) {
			/* any write to the status register will clear this */
			port->port.icount.overrun++;
			lsr |= RTSER_LSR_OVERRUN_ERR;
		}

		__raw_writel(stat, port->port.membase + HW_UARTAPP_STAT);

		/* save the valid received characters */
		invalid_chars = (stat & BM_UARTAPP_STAT_RXBYTE_INVALID) >> BP_UARTAPP_STAT_RXBYTE_INVALID;
		for (n = 0; n < 1; ++n) { // NB: the other three characters can only be used when DMA is on
			if (!(invalid_chars & (1 << n))) {
				register u8 c = (data >> (n * 8)) & 0x000000FF;

				ctx->in_buf[ctx->in_tail] = c;

				if (ctx->in_history)
					ctx->in_history[ctx->in_tail] = *timestamp;

				ctx->in_tail = (ctx->in_tail + 1) & (IN_BUFFER_SIZE - 1);

				if (++ctx->in_npend > IN_BUFFER_SIZE) {
					ctx->in_npend--;

					lsr |= RTSER_SOFT_OVERRUN_ERR;
				}

				++rbytes;
			}
		}
	} while (!((stat & BM_UARTAPP_STAT_RXFE) || (rbytes > AUART_FIFO_SIZE)));

	/* Save new errors */
	ctx->status |= lsr;

	return rbytes;
}

static unsigned int
rt_imx_mxs_auart_get_msr(struct rt_imx_mxs_auart_ctx *ctx)
{
	/* Nothing to report. */
	return 0;
}

static void
rt_imx_mxs_auart_set_mcr(struct rt_imx_mxs_auart_ctx *ctx, unsigned int mcr)
{
	struct rt_imx_mxs_auart_port *port = ctx->port;
	int ctrl2 = __raw_readl(port->port.membase + HW_UARTAPP_CTRL2);

	/* Set hardware flow control. */
	if (mcr & RTSER_MCR_RTS) {
		/* Switch to hardware-driven hardware flow control */
		if (ctx->port->use_hwflow)
			ctrl2 |= BM_UARTAPP_CTRL2_CTSEN /* | BM_UARTAPP_CTRL2_RTSEN */;
		else
			ctrl2 &= ~BM_UARTAPP_CTRL2_CTSEN /* & ~BM_UARTAPP_CTRL2_RTSEN */;
	} else {
		ctrl2 &= ~BM_UARTAPP_CTRL2_CTSEN /* & ~BM_UARTAPP_CTRL2_RTSEN */;
	}

	/* Set loopback. */
	if (mcr & RTSER_MCR_LOOP)
		ctrl2 |= BM_UARTAPP_CTRL2_LBE;
	else
		ctrl2 &= ~BM_UARTAPP_CTRL2_LBE;

	__raw_writel(ctrl2, port->port.membase + HW_UARTAPP_CTRL2);
}

/* Flush TX and RX FIFOs and buffers. */
static void
rt_imx_mxs_auart_flush(struct rt_imx_mxs_auart_ctx *ctx)
{
	rtdm_lockctx_t lock_ctx;
	struct rt_imx_mxs_auart_port *port = ctx->port;

	rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);

	/* Empty the RX buffer. */
	ctx->in_head = 0;
	ctx->in_tail = 0;
	ctx->in_npend = 0;
	ctx->in_nwait = 0;

	/* Empty the RX FIFO. */
	while (!(__raw_readl(port->port.membase + HW_UARTAPP_STAT) & BM_UARTAPP_STAT_RXFE))
		__raw_readl(port->port.membase + HW_UARTAPP_DATA);

	/* Empty the TX buffer. */
	ctx->out_head = 0;
	ctx->out_tail = 0;
	ctx->out_npend = 0;

	rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

	/* Wait for the flush of the TX FIFO. */
	while (__raw_readl(port->port.membase + HW_UARTAPP_STAT) & BM_UARTAPP_STAT_BUSY)
		rt_task_yield();
}

static int
rt_imx_mxs_auart_ioctl(struct rtdm_dev_context *context, rtdm_user_info_t *user_info, unsigned int request, void *arg)
{
	rtdm_lockctx_t lock_ctx;
	struct rt_imx_mxs_auart_ctx *ctx;
	int err = 0;

	ctx = (struct rt_imx_mxs_auart_ctx *)context->dev_private;

	switch (request) {
	case RTSER_RTIOC_GET_CONFIG:
		if (user_info)
			err = rtdm_safe_copy_to_user(user_info, arg, &ctx->config, sizeof(struct rtser_config));
		else
			memcpy(arg, &ctx->config, sizeof(struct rtser_config));

		break;

	case RTSER_RTIOC_SET_CONFIG:
		{
			struct rtser_config *config;
			struct rtser_config config_buf;
			uint64_t *hist_buf = NULL;

			config = (struct rtser_config *)arg;

			if (user_info) {
				err = rtdm_safe_copy_from_user(user_info, &config_buf, arg, sizeof(struct rtser_config));
			if (err)
				return err;

			config = &config_buf;
		}

		/* Invalid baudrate? */
		if (testbits(config->config_mask, RTSER_SET_BAUD) && (config->baud_rate > clk_get_rate(ctx->port->clk) / 16 || config->baud_rate <= 0))
			return -EINVAL;

		if (testbits(config->config_mask, RTSER_SET_TIMESTAMP_HISTORY)) {
			/* Reject in RT context since we allocate/free the buffer. */
			if (rtdm_in_rt_context())
				return -ENOSYS;

			if (testbits(config->timestamp_history, RTSER_RX_TIMESTAMP_HISTORY))
				hist_buf = kmalloc(IN_BUFFER_SIZE * sizeof(nanosecs_abs_t), GFP_KERNEL);
		}

		rt_imx_mxs_auart_set_config(ctx, config, &hist_buf);

		if (hist_buf)
			kfree(hist_buf);

		break;
	}

	case RTSER_RTIOC_GET_STATUS:
		{
			int status;
			int msr;

			rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);

			status = ctx->saved_errors | ctx->status;
			ctx->status = 0;
			ctx->saved_errors = 0;
			ctx->ioc_events &= ~RTSER_EVENT_ERRPEND;

			msr = rt_imx_mxs_auart_get_msr(ctx);

			rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

			if (user_info) {
				struct rtser_status status_buf;

				status_buf.line_status = status;
				status_buf.modem_status = msr;
				err = rtdm_safe_copy_to_user(user_info, arg, &status_buf, sizeof(struct rtser_status));
			} else {
				((struct rtser_status *)arg)->line_status = 0;
				((struct rtser_status *)arg)->modem_status = msr;
			}

			break;
		}

	case RTSER_RTIOC_GET_CONTROL:
		if (user_info)
			err = rtdm_safe_copy_to_user(user_info, arg, &ctx->mcr_status, sizeof(int));
		else
			*(int *)arg = ctx->mcr_status;

		break;

	case RTSER_RTIOC_SET_CONTROL: {
		int new_mcr = (long)arg;

		rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);

		ctx->mcr_status = new_mcr;
		rt_imx_mxs_auart_set_mcr(ctx, new_mcr);

		rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

		break;
	}

	case RTSER_RTIOC_WAIT_EVENT:
		{
			struct rtser_event ev = {
				.rxpend_timestamp = 0
			};
			rtdm_toseq_t timeout_seq;

			if (!rtdm_in_rt_context())
				return -ENOSYS;

			/* Only one waiter allowed, stop any further attempts here. */
			if (test_and_set_bit(0, &ctx->ioc_event_lock))
				return -EBUSY;

			rtdm_toseq_init(&timeout_seq, ctx->config.event_timeout);

			rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);

			while (!ctx->ioc_events) {
				/* Enable error interrupt only when the user waits for it. */
				if (testbits(ctx->config.event_mask, RTSER_EVENT_ERRPEND))
					ctx->ier_status |= IER_STAT;

				rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

				err = rtdm_event_timedwait(&ctx->ioc_event, ctx->config.event_timeout, &timeout_seq);
				if (err) {
					/* Device has been closed? */
					if (err == -EIDRM)
						err = -EBADF;

					goto wait_unlock_out;
				}

				rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);
			}

			ev.events = ctx->ioc_events;
			ctx->ioc_events &= ~(RTSER_EVENT_MODEMHI | RTSER_EVENT_MODEMLO);

			ev.last_timestamp = ctx->last_timestamp;
			ev.rx_pending = ctx->in_npend;

			if (ctx->in_history)
				ev.rxpend_timestamp = ctx->in_history[ctx->in_head];

			rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

			if (user_info)
				err = rtdm_safe_copy_to_user(user_info, arg, &ev, sizeof(struct rtser_event));
			else
				memcpy(arg, &ev, sizeof(struct rtser_event));

wait_unlock_out:
			/* Release the simple event waiter lock */
			clear_bit(0, &ctx->ioc_event_lock);

			break;
		}

	case RTSER_RTIOC_BREAK_CTL:
		{
			rt_imx_mxs_auart_flush(ctx);

			break;
		}

	default:
		err = -ENOTTY;
	}

	return err;
}

static void
rt_imx_mxs_auart_start_tx(struct rt_imx_mxs_auart_ctx *ctx)
{
	ctx->ier_status |= IER_TX;

	/* The driver should handle the RTS line. */
	if (ctx->rs485 & RS485_RTS_RQ_MASK) {
		/* No alarm set for RTS line timing. */
		if (!(ctx->rs485 & RS485_RTS_AL_MASK)) {
			char name[42];

			sprintf(name, "rts_deassert_%d", ctx->port->port.line);
			rt_alarm_create(&ctx->rts_deassert, name, rts_deassert_func, (void *)ctx);

			ctx->rs485 |= RS485_RTS_AL_MASK;
		}

		/* Disable RX and assert RTS to start TX. */
		__raw_writel((BM_UARTAPP_CTRL2_RXE), ctx->port->port.membase + HW_UARTAPP_CTRL2_CLR);
		__raw_writel((BM_UARTAPP_CTRL2_RTS), ctx->port->port.membase + HW_UARTAPP_CTRL2_CLR);
	}

	/* Enable TX interrupts. */
	__raw_writel(BM_UARTAPP_INTR_TXIEN, ctx->port->port.membase + HW_UARTAPP_INTR_SET);

	rt_imx_mxs_auart_tx_chars(ctx); /* this call from the syscall */
}

static int
rt_imx_mxs_auart_irq_handle(rtdm_irq_t *irq_context)
{
	int retval = RTDM_IRQ_NONE;
	uint64_t timestamp = rtdm_clock_read();
	struct rt_imx_mxs_auart_ctx *ctx;
	int rbytes = 0;
	int events = 0;
	u32 istat;
	struct rt_imx_mxs_auart_port *port;

	ctx = rtdm_irq_get_arg(irq_context, struct rt_imx_mxs_auart_ctx);
	port = ctx->port;

	rtdm_lock_get(&ctx->lock);

	istat = __raw_readl(port->port.membase + HW_UARTAPP_INTR);

	/* RX data ready or RX timeout or other RX errors
	 * NB: RTIS helps in getting here as soon as the data ended and the FIFO was not yet full
	 */
	if (istat & (BM_UARTAPP_INTR_OEIS | BM_UARTAPP_INTR_BEIS | BM_UARTAPP_INTR_PEIS | BM_UARTAPP_INTR_FEIS | BM_UARTAPP_INTR_RXIS | BM_UARTAPP_INTR_RTIS)) {
		__raw_writel((BM_UARTAPP_INTR_OEIS | BM_UARTAPP_INTR_BEIS | BM_UARTAPP_INTR_PEIS | BM_UARTAPP_INTR_FEIS | BM_UARTAPP_INTR_RTIS | BM_UARTAPP_INTR_RXIS), port->port.membase + HW_UARTAPP_INTR_CLR);
		rbytes += rt_imx_mxs_auart_rx_chars(ctx, &timestamp);
		events |= RTSER_EVENT_RXPEND;
		retval = RTDM_IRQ_HANDLED;
	}

	/* TX ready */
	if (istat & BM_UARTAPP_INTR_TXIS) {
		__raw_writel(BM_UARTAPP_INTR_TXIS, port->port.membase + HW_UARTAPP_INTR_CLR);
		rt_imx_mxs_auart_tx_chars(ctx); /* this call from the irq handler */
		retval = RTDM_IRQ_HANDLED;
	}

	/* Modem CTS */
	if (istat & BM_UARTAPP_INTR_CTSMIS) {
		__raw_writel(BM_UARTAPP_INTR_CTSMIS, port->port.membase + HW_UARTAPP_INTR_CLR);
		retval = RTDM_IRQ_HANDLED;
	}

	if (ctx->in_nwait > 0) {
		if ((ctx->in_nwait <= rbytes) || ctx->status) {
			ctx->in_nwait = 0;

			rtdm_event_signal(&ctx->in_event);
		} else {
			ctx->in_nwait -= rbytes;
		}
	}

	if (ctx->status)
		events |= RTSER_EVENT_ERRPEND;

	if (testbits(events, ctx->config.event_mask)) {
		int old_events = ctx->ioc_events;

		ctx->last_timestamp = timestamp;
		ctx->ioc_events = events;

		if (!old_events)
			rtdm_event_signal(&ctx->ioc_event);
	}

	rtdm_lock_put(&ctx->lock);

	/* Modem status interrupt bits are undefined after reset and DSRMIS, DCDMIS and RIMIS are not supported.
	 * So, we ignore them.
	 */
	if (istat & (BM_UARTAPP_INTR_DSRMIS | BM_UARTAPP_INTR_DCDMIS | BM_UARTAPP_INTR_RIMIS))
		/* i.MX28 always sets these bits up the first time, so print nothing */
		__raw_writel((BM_UARTAPP_INTR_DSRMIS | BM_UARTAPP_INTR_DCDMIS | BM_UARTAPP_INTR_RIMIS), port->port.membase + HW_UARTAPP_INTR_CLR);

	if (istat & (BM_UARTAPP_INTR_ABDIS)) {
		__raw_writel(BM_UARTAPP_INTR_ABDIS, port->port.membase + HW_UARTAPP_INTR_CLR);
		rtdm_printk("%s(%d): unhandled status 0x%08x\n", DRIVER_NAME, ctx->port->port.line, istat);
	}

	/* Diagnostic output (out of rtdm_lock) */
	if (istat & (BM_UARTAPP_INTR_OEIS | BM_UARTAPP_INTR_BEIS | BM_UARTAPP_INTR_PEIS | BM_UARTAPP_INTR_FEIS))
		rtdm_printk("%s(%d): error(s):%s%s%s%s\n", DRIVER_NAME, ctx->port->port.line,
			   (istat & BM_UARTAPP_INTR_OEIS) ? " OEIS" : "",
			   (istat & BM_UARTAPP_INTR_BEIS) ? " BEIS" : "",
			   (istat & BM_UARTAPP_INTR_PEIS) ? " PEIS" : "",
			   (istat & BM_UARTAPP_INTR_FEIS) ? " FEIS" : "");

	return retval;
}

static inline void
rt_imx_mxs_auart_reset(struct uart_port *u)
{
	int i;

	/* Deassert soft reset request. */
	__raw_writel(BM_UARTAPP_CTRL0_SFTRST, u->membase + HW_UARTAPP_CTRL0_CLR);

	/* Wait at least one microsecond for SFTRST to deassert. */
	for (i = 0; (__raw_readl(u->membase + HW_UARTAPP_CTRL0) & BM_UARTAPP_CTRL0_SFTRST) && (i < 10000); i++)
		udelay(1);

	/* Soft reset still asserted. */
	if (__raw_readl(u->membase + HW_UARTAPP_CTRL0) & BM_UARTAPP_CTRL0_SFTRST)
		return;

	/* Clear clock gating so we can wait for its assertion below. */
	__raw_writel(BM_UARTAPP_CTRL0_CLKGATE, u->membase + HW_UARTAPP_CTRL0_CLR);

	/* Request a soft reset of the hardware. */
	__raw_writel(BM_UARTAPP_CTRL0_SFTRST, u->membase + HW_UARTAPP_CTRL0_SET);

	/* Wait for clock gating before clearing the soft reset and clock gate. */
	for (i = 0; !(__raw_readl(u->membase + HW_UARTAPP_CTRL0) & BM_UARTAPP_CTRL0_CLKGATE) && (i < 10000); i++)
		udelay(1);

	/* The clock was not gated. */
	if (!(__raw_readl(u->membase + HW_UARTAPP_CTRL0) & BM_UARTAPP_CTRL0_CLKGATE))
		return;

	/* Remove the soft reset request. */
	__raw_writel(BM_UARTAPP_CTRL0_SFTRST, u->membase + HW_UARTAPP_CTRL0_CLR);

	/* Wait at least one microsecond for soft reset request to deassert. */
	for (i = 0; (__raw_readl(u->membase + HW_UARTAPP_CTRL0) & BM_UARTAPP_CTRL0_SFTRST) && (i < 10000); i++)
		udelay(1);

	/* Soft reset request did not deassert. */
	if (__raw_readl(u->membase + HW_UARTAPP_CTRL0) & BM_UARTAPP_CTRL0_SFTRST)
		return;

	/* Clear clock gating. */
	__raw_writel(BM_UARTAPP_CTRL0_CLKGATE, u->membase + HW_UARTAPP_CTRL0_CLR);

	/* Wait for clock gating deassertion. */
	for (i = 0; (__raw_readl(u->membase + HW_UARTAPP_CTRL0) & BM_UARTAPP_CTRL0_CLKGATE) && (i < 10000); i++)
		udelay(1);

	/* The clock is still gated. */
	if (__raw_readl(u->membase + HW_UARTAPP_CTRL0) & BM_UARTAPP_CTRL0_CLKGATE)
		return;
}

static int
rt_imx_mxs_auart_set_config(struct rt_imx_mxs_auart_ctx *ctx, const struct rtser_config *config, uint64_t **in_history_ptr)
{
	rtdm_lockctx_t lock_ctx;
	int err = 0;

	rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);

	if (testbits(config->config_mask, RTSER_SET_BAUD))
		ctx->config.baud_rate = config->baud_rate;

	if (testbits(config->config_mask, RTSER_SET_DATA_BITS))
		ctx->config.data_bits = config->data_bits & DATA_BITS_MASK;

	if (testbits(config->config_mask, RTSER_SET_PARITY))
		ctx->config.parity = config->parity & PARITY_MASK;

	if (testbits(config->config_mask, RTSER_SET_STOP_BITS))
		ctx->config.stop_bits = config->stop_bits & STOP_BITS_MASK;

	/* Timeout manipulation is not atomic.	The user should
	   not use and change the timeouts at the same time. */
	if (testbits(config->config_mask, RTSER_SET_TIMEOUT_RX))
		ctx->config.rx_timeout = config->rx_timeout;

	if (testbits(config->config_mask, RTSER_SET_TIMEOUT_TX))
		ctx->config.tx_timeout = config->tx_timeout;

	if (testbits(config->config_mask, RTSER_SET_TIMEOUT_EVENT))
		ctx->config.event_timeout = config->event_timeout;

	if (testbits(config->config_mask, RTSER_SET_TIMESTAMP_HISTORY)) {
		if (testbits(config->timestamp_history, RTSER_RX_TIMESTAMP_HISTORY)) {
			if (!ctx->in_history) {
				ctx->in_history = *in_history_ptr;
				*in_history_ptr = NULL;

				if (!ctx->in_history)
					err = -ENOMEM;
			}
		} else {
			*in_history_ptr = ctx->in_history;
			ctx->in_history = NULL;
		}
	}

	if (testbits(config->config_mask, RTSER_SET_EVENT_MASK)) {
		ctx->config.event_mask = config->event_mask & EVENT_MASK;
		ctx->ioc_events = 0;

		if (testbits(config->event_mask, RTSER_EVENT_RXPEND) && (ctx->in_npend > 0))
			ctx->ioc_events |= RTSER_EVENT_RXPEND;

		if (testbits(config->event_mask, RTSER_EVENT_ERRPEND) && ctx->status)
			ctx->ioc_events |= RTSER_EVENT_ERRPEND;
	}

	if (testbits(config->config_mask, RTSER_SET_HANDSHAKE))
		ctx->config.handshake = config->handshake;

	if (testbits(config->config_mask, RTSER_SET_MECT_RTS_MASK)) {
		/* MECT RS485 half-duplex: RTS set / clear with automatic stop / start of the receiver channel */
		ctx->config.mect_rts = config->mect_rts;
		if (ctx->config.mect_rts == RTSER_MECT_RTS_SET) {
			// enable RTS and then the receive channel since we are going to receive
			__raw_writel((BM_UARTAPP_CTRL2_RTS), ctx->port->port.membase + HW_UARTAPP_CTRL2_SET);
			__raw_writel((BM_UARTAPP_CTRL2_RXE), ctx->port->port.membase + HW_UARTAPP_CTRL2_SET);
		} else if (ctx->config.mect_rts == RTSER_MECT_RTS_CLR) {
			// disable the receive channel and then RTS since we are going to transmit
			__raw_writel((BM_UARTAPP_CTRL2_RXE), ctx->port->port.membase + HW_UARTAPP_CTRL2_CLR);
			__raw_writel((BM_UARTAPP_CTRL2_RTS), ctx->port->port.membase + HW_UARTAPP_CTRL2_CLR);
		}
	}

	/*
	 * Configure the hardware.
	 */
	if (testbits(config->config_mask, (RTSER_SET_DATA_BITS
					   | RTSER_SET_HANDSHAKE 
					   | RTSER_SET_STOP_BITS
					   | RTSER_SET_PARITY
					   | RTSER_SET_BAUD
					   | RTSER_SET_EVENT_MASK))) {
		u32 ctrl;
		u32 ctrl2;
		u32 div;
		u32 ctrl0;
		u32 to_bits;

		/* Get HW configuration. */
		ctrl = __raw_readl(ctx->port->port.membase + HW_UARTAPP_LINECTRL);
		ctrl2 = __raw_readl(ctx->port->port.membase + HW_UARTAPP_CTRL2);
		ctrl0 = __raw_readl(ctx->port->port.membase + HW_UARTAPP_CTRL0);

		/* Enable FIFO. */
		ctrl |= BM_UARTAPP_LINECTRL_FEN;

		/* Data size: either 8 or 7 bit */
		ctrl &= ~BF_UARTAPP_LINECTRL_WLEN(0xffffffff);
		if (ctx->config.data_bits == RTSER_8_BITS)
			ctrl |= BF_UARTAPP_LINECTRL_WLEN(3);
		else
			ctrl |= BF_UARTAPP_LINECTRL_WLEN(2);

		/* Hardware flow control (RTS/CTS) */
		/* NOTE: RTS leaved out for RS485. */
		if (ctx->config.handshake == RTSER_RTSCTS_HAND)
			ctrl2 |= BM_UARTAPP_CTRL2_CTSEN /* | BM_UARTAPP_CTRL2_RTSEN */;
		else
			ctrl2 &= ~BM_UARTAPP_CTRL2_CTSEN /* & ~BM_UARTAPP_CTRL2_RTSEN */;

		/* Stop bits (1 or 2) */
		ctrl &= ~BM_UARTAPP_LINECTRL_STP2;
		if (ctx->config.stop_bits == RTSER_2_STOPB)
			ctrl |= BM_UARTAPP_LINECTRL_STP2;
		else if (ctx->config.stop_bits == RTSER_1_STOPB)
			ctrl &= ~BM_UARTAPP_LINECTRL_STP2;

		/* Parity check: either even or odd. */
		ctrl &= ~BM_UARTAPP_LINECTRL_PEN;
		if ((ctx->config.parity == RTSER_ODD_PARITY) || (ctx->config.parity == RTSER_EVEN_PARITY)) {
			ctrl |= BM_UARTAPP_LINECTRL_PEN;
			if (ctx->config.parity == RTSER_EVEN_PARITY)
				ctrl |= BM_UARTAPP_LINECTRL_EPS;
		}

		/* Baud rate */
		{
			u32 uc = 0;

			uc = ctx->port->port.uartclk << 5;

			div = uc / ctx->config.baud_rate;
			/* Round to nearest integer. */
			if (((div + 1) * ctx->config.baud_rate - uc) < (uc - div * ctx->config.baud_rate))
				div++;
		}

		/* TODO Replace this hackish detection with a proper IOCTL. */
		/* Do NOT handle the RTS line. */
		if ((ctx->config.baud_rate == 225000) && (ctx->port->port.line == 3)) {
			ctx->rs485 &= ~RS485_RTS_RQ_MASK;

			rtdm_printk("%s(%d): switch to full-duplex mode\n", DRIVER_NAME, ctx->port->port.line);
		} else {
			ctx->rs485 |= RS485_RTS_RQ_MASK;

			rtdm_printk("%s(%d): switch to half-duplex mode\n", DRIVER_NAME, ctx->port->port.line);
		}

		ctrl &= ~BF_UARTAPP_LINECTRL_BAUD_DIVFRAC(0xffffffff);
		ctrl |= BF_UARTAPP_LINECTRL_BAUD_DIVFRAC(div);

		ctrl &= ~BF_UARTAPP_LINECTRL_BAUD_DIVINT(0xffffffff);
		ctrl |= BF_UARTAPP_LINECTRL_BAUD_DIVINT(div >> 6);

		{
			/* computing variables at the given serial config */
			register u32 bit_time_ns = 1000000000 / ctx->config.baud_rate;
			register u32 char_bits = 1;

			if (ctx->config.data_bits == RTSER_8_BITS)
				char_bits += 8;
			else
				char_bits += 7;

			if ((ctx->config.parity == RTSER_ODD_PARITY) || (ctx->config.parity == RTSER_EVEN_PARITY))
				char_bits += 1;

			if (ctx->config.stop_bits == RTSER_2_STOPB)
				char_bits += 2;
			else
				char_bits += 1;

			ctx->char_time_ns = char_bits * bit_time_ns;
			//rtdm_printk("%s(%d): char_time_ns=%llu\n", DRIVER_NAME, ctx->port->port.line, ctx->char_time_ns);

			/* Modbus RTU reception requires an inter-character timeout:
			 * -- 1.5 chars = 1.5 * (1 + data_bits + parity + stop_bits) for baudrates <= 19200
			 * -- capped to 0.750 s for higher baudrates
			 */
			if (ctx->config.baud_rate <= 19200)
				to_bits = 15 * char_bits / 10;
			else
				to_bits = 750000 / bit_time_ns;		// 750000 ns = 0.750 ms
		}
		/* i.MX28 RX timeout is set in "8 bit-times" with a "7 bit" base ("1" --> 15 bit time) */
		if (to_bits >= 7)
			to_bits = to_bits - 7;
		else
			to_bits = 0;
		to_bits /= 8;

		ctrl0 &= ~BF_UARTAPP_CTRL0_RXTIMEOUT(0x7ff);
		ctrl0 |= BF_UARTAPP_CTRL0_RXTIMEOUT(to_bits);

		/* Set up the HW. */
		__raw_writel(ctrl, ctx->port->port.membase + HW_UARTAPP_LINECTRL);
		__raw_writel(ctrl2, ctx->port->port.membase + HW_UARTAPP_CTRL2);
		__raw_writel(ctrl0, ctx->port->port.membase + HW_UARTAPP_CTRL0);

		/* Always enable the receiver. */
		__raw_writel((BM_UARTAPP_CTRL2_RTS), ctx->port->port.membase + HW_UARTAPP_CTRL2_SET);
		__raw_writel((BM_UARTAPP_CTRL2_RXE), ctx->port->port.membase + HW_UARTAPP_CTRL2_SET);

		ctx->status = 0;
		ctx->ioc_events &= ~RTSER_EVENT_ERRPEND;
	}

	rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

	return err;
}

static ssize_t
rt_imx_mxs_auart_write(struct rtdm_dev_context *context, rtdm_user_info_t *user_info, const void *buf, size_t nbyte)
{
	struct rt_imx_mxs_auart_ctx *ctx;
	rtdm_lockctx_t lock_ctx;
	size_t written = 0;
	int free;
	int block;
	int subblock;
	int out_pos;
	char *in_pos = (char *)buf;
	rtdm_toseq_t timeout_seq;
	ssize_t ret;

	if (nbyte == 0)
		return 0;

	if (user_info && !rtdm_read_user_ok(user_info, buf, nbyte))
		return -EFAULT;

	ctx = (struct rt_imx_mxs_auart_ctx *)context->dev_private;

	rtdm_toseq_init(&timeout_seq, ctx->config.tx_timeout);

	/* Make write operation atomic. */
	ret = rtdm_mutex_timedlock(&ctx->out_lock, ctx->config.tx_timeout, &timeout_seq);
	if (ret)
		return ret;

	while (nbyte > 0) {
		rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);

		free = OUT_BUFFER_SIZE - ctx->out_npend;

		if (free > 0) {
			block = subblock = (nbyte <= free) ? nbyte : free;
			out_pos = ctx->out_tail;

			rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

			/* Wrap around buffer end? */
			if (out_pos + subblock > OUT_BUFFER_SIZE) {
				/* Treat the block between head and buffer end separately. */
				subblock = OUT_BUFFER_SIZE - out_pos;

				if (user_info) {
					if (rtdm_copy_from_user(user_info, &ctx->out_buf[out_pos], in_pos, subblock) != 0) {
						ret = -EFAULT;

						break;
					}
				} else {
					memcpy(&ctx->out_buf[out_pos], in_pos, subblock);
				}

				written += subblock;
				in_pos += subblock;

				subblock = block - subblock;
				out_pos = 0;
			}

			if (user_info) {
				if (rtdm_copy_from_user(user_info, &ctx->out_buf[out_pos], in_pos, subblock) != 0) {
					ret = -EFAULT;

					break;
				}
			} else {
				memcpy(&ctx->out_buf[out_pos], in_pos, block);
			}

			written += subblock;
			in_pos += subblock;
			nbyte -= block;

			rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);

			ctx->out_tail = (ctx->out_tail + block) & (OUT_BUFFER_SIZE - 1);
			ctx->out_npend += block;

			rt_imx_mxs_auart_start_tx(ctx);

			rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

			continue;
		}

		rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

		ret = rtdm_event_timedwait(&ctx->out_event, ctx->config.tx_timeout, &timeout_seq);
		if (ret < 0) {
			if (ret == -EIDRM)
				/* Device has been closed - return immediately. */
				return -EBADF;

			if (ret == -EWOULDBLOCK)
				/* Fix error code for non-blocking mode. */
				ret = -EAGAIN;

			break;
		}
	}

	rtdm_mutex_unlock(&ctx->out_lock);

	if ((written > 0) && ((ret == 0) || (ret == -EAGAIN) || (ret == -ETIMEDOUT) || (ret == -EINTR)))
		ret = written;

	return ret;
}

ssize_t
rt_imx_mxs_auart_read(struct rtdm_dev_context *context, rtdm_user_info_t *user_info, void *buf, size_t nbyte)
{
	struct rt_imx_mxs_auart_ctx *ctx;
	rtdm_lockctx_t lock_ctx;
	size_t read = 0;
	int pending;
	int block;
	int subblock;
	int in_pos;
	char *out_pos = (char *)buf;
	rtdm_toseq_t timeout_seq;
	ssize_t ret = -EAGAIN;	/* for non-blocking read */
	int nonblocking;

	if (nbyte == 0)
		return 0;

	if (user_info && !rtdm_rw_user_ok(user_info, buf, nbyte))
		return -EFAULT;

	ctx = (struct rt_imx_mxs_auart_ctx *)context->dev_private;

	rtdm_toseq_init(&timeout_seq, ctx->config.rx_timeout);

	/* non-blocking is handled separately here */
	nonblocking = (ctx->config.rx_timeout < 0);

	/* only one reader allowed, stop any further attempts here */
	if (test_and_set_bit(0, &ctx->in_lock))
		return -EBUSY;

	rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);

	while (1) {
		if (ctx->status) {
			if (testbits(ctx->status, RTSER_LSR_BREAK_IND))
				ret = -EPIPE;
			else
				ret = -EIO;

			ctx->saved_errors = ctx->status & (RTSER_LSR_OVERRUN_ERR | RTSER_LSR_PARITY_ERR | RTSER_LSR_FRAMING_ERR | RTSER_SOFT_OVERRUN_ERR);
			ctx->status = 0;

			break;
		}

		pending = ctx->in_npend;

		if (pending > 0) {
			block = subblock = (pending <= nbyte) ? pending : nbyte;
			in_pos = ctx->in_head;

			rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

			/* Wrap around buffer end? */
			if (in_pos + subblock > IN_BUFFER_SIZE) {
				/* Treat the block between head and buffer end separately. */
				subblock = IN_BUFFER_SIZE - in_pos;

				if (user_info) {
					if (rtdm_copy_to_user(user_info, out_pos, &ctx->in_buf[in_pos], subblock) != 0) {
						ret = -EFAULT;

						goto break_unlocked;
					}
				} else {
					memcpy(out_pos, &ctx->in_buf[in_pos], subblock);
				}

				read += subblock;
				out_pos += subblock;

				subblock = block - subblock;
				in_pos = 0;
			}

			if (user_info) {
				if (rtdm_copy_to_user(user_info, out_pos, &ctx->in_buf[in_pos], subblock) != 0) {
					ret = -EFAULT;

					goto break_unlocked;
				}
			} else {
				memcpy(out_pos, &ctx->in_buf[in_pos], subblock);
			}

			read += subblock;
			out_pos += subblock;
			nbyte -= block;

			rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);

			ctx->in_head = (ctx->in_head + block) & (IN_BUFFER_SIZE - 1);
			ctx->in_npend -= block;
			if (ctx->in_npend == 0)
				ctx->ioc_events &= ~RTSER_EVENT_RXPEND;

			if (nbyte == 0)
				break; /* All requested bytes were read. */

			continue;
		}

		/* ret was set to EAGAIN in case of a real non-blocking call
		   or contains the error returned by rtdm_event_wait[_until] */
		if (nonblocking)
			break;

		ctx->in_nwait = nbyte;

		rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

		ret = rtdm_event_timedwait(&ctx->in_event, ctx->config.rx_timeout, &timeout_seq);
		if (ret < 0) {
			if (ret == -EIDRM)
				/* Device has been closed - return immediately. */
				return -EBADF;

			rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);

			nonblocking = 1;
			if (ctx->in_npend > 0)
				/* Final turn: collect pending bytes before exit. */
				continue;

			ctx->in_nwait = 0;

			break;
		}

		rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);
	}

	rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

break_unlocked:
	/* Release the simple reader lock, */
	clear_bit(0, &ctx->in_lock);

	if ((read > 0) && ((ret == 0) || (ret == -EAGAIN) || (ret == -ETIMEDOUT) || (ret == -EINTR)))
		ret = read;

	return ret;
}

static int
rt_imx_mxs_auart_close(struct rtdm_dev_context *context, rtdm_user_info_t *user_info)
{
	struct rt_imx_mxs_auart_ctx *ctx;
	struct rt_imx_mxs_auart_port *port;
	uint64_t *in_history;
	rtdm_lockctx_t lock_ctx;
	RT_ALARM_INFO rts_deassert_info;
	int retval;

	ctx = (struct rt_imx_mxs_auart_ctx *)context->dev_private;
	port = ctx->port;

	/* Wait for the alarm to expire. */
	if (ctx->rs485 & RS485_RTS_AL_MASK) {
		retval = rt_alarm_inquire(&ctx->rts_deassert, &rts_deassert_info);
		/* Wait for the alarm to expire. */
		while ((retval >= 0) && (rts_deassert_info.expiration != TM_INFINITE)) {
			rt_task_yield();

			retval = rt_alarm_inquire(&ctx->rts_deassert, &rts_deassert_info);
		}
		/* Wait for the alarm to notify the expiration to the handler. */
		while (retval > 0) {
			rt_task_yield();

			retval = rt_alarm_inquire(&ctx->rts_deassert, &rts_deassert_info);
		}
	}

	rtdm_lock_get_irqsave(&ctx->lock, lock_ctx);

	/* Destroy the alarm. */
	if (ctx->rs485 & RS485_RTS_AL_MASK) {
		rt_alarm_delete(&ctx->rts_deassert);

		ctx->rs485 &= ~RS485_RTS_AL_MASK;
	}

	__raw_writel(BM_UARTAPP_CTRL0_SFTRST, port->port.membase + HW_UARTAPP_CTRL0_SET);

	__raw_writel(BM_UARTAPP_INTR_OEIEN | BM_UARTAPP_INTR_BEIEN | BM_UARTAPP_INTR_PEIEN | BM_UARTAPP_INTR_FEIEN | BM_UARTAPP_INTR_RXIEN | BM_UARTAPP_INTR_RTIEN | BM_UARTAPP_INTR_CTSMIEN, port->port.membase + HW_UARTAPP_INTR_CLR);

	in_history = ctx->in_history;
	ctx->in_history = NULL;

	rtdm_lock_put_irqrestore(&ctx->lock, lock_ctx);

	rtdm_irq_free(&ctx->irq_handle);

	rtdm_event_destroy(&ctx->in_event);
	rtdm_event_destroy(&ctx->out_event);
	rtdm_event_destroy(&ctx->ioc_event);
	rtdm_mutex_destroy(&ctx->out_lock);

	if (in_history)
		kfree(in_history);

	return 0;
}

static int
rt_imx_mxs_auart_open(struct rtdm_dev_context *context, rtdm_user_info_t *user_info, int oflags)
{
	struct rt_imx_mxs_auart_ctx *ctx;
	struct rt_imx_mxs_auart_port *port;
	int ret;
	uint64_t *dummy;

	ctx = (struct rt_imx_mxs_auart_ctx *)context->dev_private;
	ctx->port = (struct rt_imx_mxs_auart_port *)context->device->device_data;
	port = ctx->port;

	/* IPC initialisation - cannot fail with these parameters */
	rtdm_lock_init(&ctx->lock);
	rtdm_event_init(&ctx->in_event, 0);
	rtdm_event_init(&ctx->out_event, 0);
	rtdm_event_init(&ctx->ioc_event, 0);
	rtdm_mutex_init(&ctx->out_lock);

	ctx->in_head = 0;
	ctx->in_tail = 0;
	ctx->in_npend = 0;
	ctx->in_nwait = 0;
	ctx->in_lock = 0;
	ctx->in_history = NULL;

	ctx->out_head = 0;
	ctx->out_tail = 0;
	ctx->out_npend = 0;

	ctx->ioc_events = 0;
	ctx->ioc_event_lock = 0;
	ctx->status = 0;
	ctx->saved_errors = 0;

	ctx->rs485 &= (~RS485_RTS_RQ_MASK & ~RS485_RTS_AL_MASK);
	ctx->char_time_ns = 1000000; /* 1 ms preset */

	rt_imx_mxs_auart_reset(&port->port);

	__raw_writel(BM_UARTAPP_INTR_OEIEN | BM_UARTAPP_INTR_BEIEN | BM_UARTAPP_INTR_PEIEN | BM_UARTAPP_INTR_FEIEN | BM_UARTAPP_INTR_RXIEN | BM_UARTAPP_INTR_RTIEN, port->port.membase + HW_UARTAPP_INTR);

	__raw_writel(BM_UARTAPP_INTR_CTSMIEN, port->port.membase + HW_UARTAPP_INTR_SET);

	__raw_writel(BM_UARTAPP_LINECTRL_FEN, port->port.membase + HW_UARTAPP_LINECTRL_SET);

	rt_imx_mxs_auart_set_config(ctx, &default_config, &dummy);

	ret = rtdm_irq_request(&ctx->irq_handle, port->port.irq, rt_imx_mxs_auart_irq_handle, 0, context->device->proc_name, ctx);

	__raw_writel(BM_UARTAPP_CTRL2_UARTEN, port->port.membase + HW_UARTAPP_CTRL2_SET);

	//rtdm_printk("%s(%d): open %s\n", DRIVER_NAME, ctx->port->port.line, ret ? "failure" : "success");

	return ret;
}

static const struct rtdm_device __initdata device_tmpl = {
	.struct_version		= RTDM_DEVICE_STRUCT_VER,

	.device_flags		= RTDM_NAMED_DEVICE | RTDM_EXCLUSIVE,
	.context_size		= sizeof(struct rt_imx_mxs_auart_ctx),
	.device_name		= "",

	.open_nrt		= rt_imx_mxs_auart_open,
	.ops = {
		.close_nrt	= rt_imx_mxs_auart_close,
		.ioctl_rt	= rt_imx_mxs_auart_ioctl,
		.ioctl_nrt	= rt_imx_mxs_auart_ioctl,
		.read_rt	= rt_imx_mxs_auart_read,
		.write_rt	= rt_imx_mxs_auart_write,
	},

	.device_class		= RTDM_CLASS_SERIAL,
	.device_sub_class	= RTDM_SUBCLASS_16550A,
	.profile_version	= RTSER_PROFILE_VER,
	.driver_name		= DRIVER_NAME,
	.driver_version		= RTDM_DRIVER_VER(1, 0, 0),
	.peripheral_name	= "IMX MXS application UART",
	.provider_name		= "MECT s.r.l.",
};

static int __devinit
rt_imx_mxs_auart_probe(struct platform_device *pdev)
{
	struct rtdm_device *dev;
	u32 version;
	int i;
	int err = 0;
	struct mxs_auart_plat_data *pdata;	// plat
	struct rt_imx_mxs_auart_port *port;	// s
	struct resource *res;			// r

	port = kzalloc(sizeof(struct rt_imx_mxs_auart_port), GFP_KERNEL);
	if (!port)
		return -ENOMEM;

	pdata = pdev->dev.platform_data;
	if (pdata == NULL) {
		err = -ENOMEM;

		goto kfree_out;
	}

	if (pdata && pdata->clk)
		port->clk = clk_get(NULL, pdata->clk);
	else
		port->clk = clk_get(NULL, "uart");
	if (IS_ERR(port->clk)) {
		err = PTR_ERR(port->clk);

		goto kfree_out;
	}

	clk_enable(port->clk);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		err = -ENXIO;

		goto clk_disable_out;
	}

	port->port.mapbase = res->start;
	port->port.membase = (void __iomem *)IO_ADDRESS(res->start);
	port->port.ops = NULL;
	port->port.iotype = UPIO_MEM;
	port->port.line = pdev->id < 0 ? 0 : pdev->id;
	port->port.fifosize = pdata->fifo_size;
	port->port.timeout = pdata->timeout ? pdata->timeout : (HZ / 10);
	port->port.uartclk = clk_get_rate(port->clk);
	port->port.type = PORT_IMX;
	port->port.dev = port->dev = get_device(&pdev->dev);

	port->flags = 0;

	for (i = 0; i < ARRAY_SIZE(port->irq); i++) {
		port->irq[i] = platform_get_irq(pdev, i);
		if (port->irq[i] < 0) {
			err = port->irq[i];

			goto clk_disable_out;
		}
	}

	port->port.irq = port->irq[0];

	/* RTDM */
	dev = &port->rtdm_dev;

	memcpy(dev, &device_tmpl, sizeof(struct rtdm_device));

	snprintf(dev->device_name, RTDM_MAX_DEVNAME_LEN, "rtser%d", pdev->id);
	dev->proc_name = dev->device_name;
	dev->device_id = pdev->id;
	dev->device_data = port;

	pdata = pdev->dev.platform_data;

	err = rtdm_dev_register(dev);
	if (err)
		goto clk_disable_out;

	port->use_hwflow = 0;

	platform_set_drvdata(pdev, port);

	device_init_wakeup(&pdev->dev, 1);

	version = __raw_readl(port->port.membase + HW_UARTAPP_VERSION);
	printk(
		KERN_INFO
		"%s on Xenomai RTDM MXS APPUART%d (v%d.%d.%d): membase=0x%p mapbase=%#x irq=%d uartclk=%d\n",
		dev->device_name,
		pdev->id,
		(version >> 24) & 0xFF,
		(version >> 16) & 0xFF,
		version & 0xFFFF,
		port->port.membase,
		(u32)port->port.mapbase,
		port->port.irq,
		port->port.uartclk
	);

	return 0;

clk_disable_out:
	if (!IS_ERR(port->clk)) {
		clk_put(port->clk);
		clk_disable(port->clk);
	}

kfree_out:
	kfree(port);

	return err;
}

static int __devexit
rt_imx_mxs_auart_remove(struct platform_device *pdev)
{
	struct rt_imx_mxs_auart_port *port; // s
	struct rtdm_device *dev;

	port = platform_get_drvdata(pdev);
	platform_set_drvdata(pdev, NULL);

	dev = &port->rtdm_dev;
	rtdm_dev_unregister(dev, 1000);

	if (port) {
		put_device(port->dev);

		if (port->clk) {
			clk_disable(port->clk);
			clk_put(port->clk);
		}

		kfree(port);
	}

	return 0;
}

static const struct platform_device_id rt_imx_mxs_auart_id_table[] = {
	{"mxs-auart",},
	{},
};

static struct platform_driver rt_imx_mxs_auart_driver = {
	.probe = rt_imx_mxs_auart_probe,
	.remove = __devexit_p(rt_imx_mxs_auart_remove),
	.id_table = rt_imx_mxs_auart_id_table,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	},
};

static int __init
rt_imx_mxs_auart_init(void)
{
	return platform_driver_register(&rt_imx_mxs_auart_driver);
}

static void __exit
rt_imx_mxs_auart_exit(void)
{
	platform_driver_unregister(&rt_imx_mxs_auart_driver);
}

module_init(rt_imx_mxs_auart_init)
module_exit(rt_imx_mxs_auart_exit)

MODULE_AUTHOR("Mihai Lazarescu <mlazarescu@mect.it>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xenomai RTDM driver for Freescale MXS application UART");

/* vim: set tabstop=8 shiftwidth=8 : */
