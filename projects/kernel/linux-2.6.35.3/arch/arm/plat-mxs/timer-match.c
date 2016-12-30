/*
 * System timer for Freescale i.MXS
 *
 * Copyright 2008 Embedded Alley Solutions, Inc All Rights Reserved.
 * Copyright (C) 2009-2010 Freescale Semiconductor, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/clocksource.h>
#include <linux/clockchips.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/irq.h>
#include <linux/interrupt.h>

#include <asm/mach/time.h>

#include <mach/device.h>
#include <mach/regs-timrot.h>

static struct mxs_sys_timer *online_timer;

static irqreturn_t mxs_timer_handler(int irq, void *dev_id);

#ifdef CONFIG_IPIPE

// arch/arm/mach-mx28/regs-digctl.h
// #include <mach/regs-digctl.h>
#define HW_DIGCTL_MICROSECONDS  (0x000000c0)

static inline void gpt_irq_acknowledge(void)
{
	__raw_writel(BM_TIMROT_TIMCTRLn_IRQ, online_timer->base + HW_TIMROT_TIMCTRLn_CLR(online_timer->id));
}

static inline void gpt_irq_enable(void)
{
	__raw_writel(BM_TIMROT_TIMCTRLn_IRQ_EN, online_timer->base + HW_TIMROT_TIMCTRLn_SET(online_timer->id));
}

static inline void gpt_irq_disable(void)
{
	__raw_writel(BM_TIMROT_TIMCTRLn_IRQ_EN, online_timer->base + HW_TIMROT_TIMCTRLn_CLR(online_timer->id));
}

static unsigned mxs_min_delay;

#ifdef CONFIG_NO_IDLE_HZ
#error "dynamic tick timer not yet supported with IPIPE"
#endif /* CONFIG_NO_IDLE_HZ */

int __ipipe_mach_timerint;
EXPORT_SYMBOL(__ipipe_mach_timerint);

int __ipipe_mach_timerstolen = 0;
EXPORT_SYMBOL(__ipipe_mach_timerstolen);

unsigned int __ipipe_mach_ticks_per_jiffy = LATCH;
EXPORT_SYMBOL(__ipipe_mach_ticks_per_jiffy);

#ifdef CONFIG_IPIPE_ARM_KUSER_TSC
static struct __ipipe_tscinfo mxs_tsc_info;
#endif

void __ipipe_mach_acktimer(void)
{
	gpt_irq_acknowledge();
}

void __ipipe_mach_set_dec(unsigned long delay)
{
	if (delay > mxs_min_delay) {
		register long counter;
		register long match;

		counter = __raw_readl(online_timer->base + HW_TIMROT_RUNNING_COUNTn(online_timer->id));
		match = counter - delay;
		__raw_writel(match, online_timer->base + HW_TIMROT_MATCH_COUNTn(online_timer->id));
		gpt_irq_enable();
	} else  {
		ipipe_trigger_irq(__ipipe_mach_timerint);
	}
}
EXPORT_SYMBOL(__ipipe_mach_set_dec);

unsigned long __ipipe_mach_get_dec(void)
{
	register long counter;
	register long match;
	counter = __raw_readl(online_timer->base + HW_TIMROT_RUNNING_COUNTn(online_timer->id));
	match = __raw_readl(online_timer->base + HW_TIMROT_MATCH_COUNTn(online_timer->id));
	return (unsigned long)(counter - match);
}
EXPORT_SYMBOL(__ipipe_mach_get_dec);
#endif /* CONFIG_IPIPE */

static cycle_t mxs_get_cycles(struct clocksource *cs)
{
	return ~__raw_readl(online_timer->base +
			    HW_TIMROT_RUNNING_COUNTn(online_timer->id));
}

static int mxs_set_next_event(unsigned long delta,
			      struct clock_event_device *dev)
{
#ifndef CONFIG_IPIPE
	unsigned int match;
	match = __raw_readl(online_timer->base +
			    HW_TIMROT_RUNNING_COUNTn(online_timer->id)) - delta;
	__raw_writel(match, online_timer->base +
		     HW_TIMROT_MATCH_COUNTn(online_timer->id));
	return (int)(match -
		     __raw_readl(online_timer->base +
				 HW_TIMROT_RUNNING_COUNTn(online_timer->id)))
	    > 0 ? -ETIME : 0;
#else
	register long counter, match;
	if (delta <= mxs_min_delay) {
		return 0;
	}
	counter = __raw_readl(online_timer->base + HW_TIMROT_RUNNING_COUNTn(online_timer->id));
	match = counter - delta;
	__raw_writel(match, online_timer->base + HW_TIMROT_MATCH_COUNTn(online_timer->id));
	gpt_irq_enable();
	return 0;
#endif
}

static void mxs_set_mode(enum clock_event_mode mode,
			 struct clock_event_device *evt)
{
	switch (mode) {
	case CLOCK_EVT_MODE_SHUTDOWN:
	__raw_writel(BM_TIMROT_TIMCTRLn_IRQ_EN | BM_TIMROT_TIMCTRLn_IRQ,
			online_timer->base  + HW_TIMROT_TIMCTRLn_CLR(0));
	break;
	case CLOCK_EVT_MODE_RESUME:
	case CLOCK_EVT_MODE_ONESHOT:
#ifndef CONFIG_IPIPE
	__raw_writel(BM_TIMROT_ROTCTRL_SFTRST | BM_TIMROT_ROTCTRL_CLKGATE,
			online_timer->base  + HW_TIMROT_ROTCTRL_CLR);
	__raw_writel(BF_TIMROT_TIMCTRLn_SELECT(online_timer->clk_sel) |
		     BM_TIMROT_TIMCTRLn_IRQ_EN |
		     BM_TIMROT_TIMCTRLn_MATCH_MODE,
		     online_timer->base + HW_TIMROT_TIMCTRLn(online_timer->id));
#else
	gpt_irq_acknowledge();
#endif
	break;
	default:
	break;
	}
}

static struct clock_event_device mxs_clockevent = {
	.name = "mxs tick timer ",
	.features = CLOCK_EVT_FEAT_ONESHOT,
	.shift = 32,
	.set_next_event = mxs_set_next_event,
	.set_mode = mxs_set_mode,
	.rating = 200,
};

static struct clocksource mxs_clocksource = {
	.name = "mxs clock source",
	.rating = 250,
	.read = mxs_get_cycles,
	.mask = CLOCKSOURCE_MASK(32),
	.shift = 10,
	.flags = CLOCK_SOURCE_IS_CONTINUOUS
};

static struct irqaction mxs_timer_irq = {
	.name = "i.MX/mxs Timer Tick",
	.flags = IRQF_DISABLED | IRQF_TIMER,
	.handler = mxs_timer_handler,
	.dev_id = &mxs_clockevent,
};

#ifdef CONFIG_IPIPE
int __ipipe_check_tickdev(const char *devname)
{
	return !strcmp(devname, mxs_clockevent.name);
}

void __ipipe_mach_release_timer(void)
{
	mxs_set_mode(mxs_clockevent.mode, &mxs_clockevent);
	if (mxs_clockevent.mode == CLOCK_EVT_MODE_ONESHOT)
	{
		mxs_clockevent.set_next_event(LATCH, &mxs_clockevent);
	}
}
EXPORT_SYMBOL(__ipipe_mach_release_timer);
#endif  /* CONFIG_IPIPE */

static int __init mxs_clocksource_init(struct clk *timer_clk)
{
	unsigned int c = clk_get_rate(timer_clk);

	mxs_clocksource.mult = clocksource_hz2mult(c, mxs_clocksource.shift);
	clocksource_register(&mxs_clocksource);
	return 0;
}

static int __init mxs_clockevent_init(struct clk *timer_clk)
{
	unsigned int c = clk_get_rate(timer_clk);

	mxs_clockevent.mult = div_sc(c, NSEC_PER_SEC, mxs_clockevent.shift);
	mxs_clockevent.min_delta_ns = clockevent_delta2ns(0xF, &mxs_clockevent);
	mxs_clockevent.max_delta_ns = clockevent_delta2ns(0xFFFFFFF0,
							  &mxs_clockevent);
	mxs_clockevent.cpumask = cpumask_of(0);

	clockevents_register_device(&mxs_clockevent);
	return 0;
}

static irqreturn_t mxs_timer_handler(int irq, void *dev_id)
{
	struct clock_event_device *c = dev_id;
#ifndef CONFIG_IPIPE
	if (__raw_readl(online_timer->base +
			HW_TIMROT_TIMCTRLn(online_timer->id)) &
	    BM_TIMROT_TIMCTRLn_IRQ) {
		__raw_writel(BM_TIMROT_TIMCTRLn_IRQ,
			     online_timer->base +
			     HW_TIMROT_TIMCTRLn_CLR(online_timer->id));
#else
	{
#ifdef CONFIG_IPIPE_ARM_KUSER_TSC
		__ipipe_tsc_update();
#endif
#endif
		c->event_handler(c);
	}
	return IRQ_HANDLED;
}

void mxs_timer_init(struct mxs_sys_timer *timer)
{
	unsigned long reg;

	if (!timer->base || !timer->clk || IS_ERR(timer->clk))
		return;
	if (online_timer)
		return;
	online_timer = timer;
	clk_enable(online_timer->clk);
#ifndef CONFIG_IPIPE
	__raw_writel(BF_TIMROT_TIMCTRLn_SELECT(online_timer->clk_sel) |
		     BM_TIMROT_TIMCTRLn_IRQ_EN |
		     BM_TIMROT_TIMCTRLn_MATCH_MODE,
		     online_timer->base + HW_TIMROT_TIMCTRLn(online_timer->id));
#else	// 39.5.10 Correct Way to Soft Reset a Block
	// vedi mx28_timer_init()
	do {
		reg = __raw_readl(online_timer->base + HW_TIMROT_ROTCTRL);
	} while (reg & BM_TIMROT_ROTCTRL_CLKGATE);
	__raw_writel(BF_TIMROT_TIMCTRLn_SELECT(online_timer->clk_sel), online_timer->base + HW_TIMROT_TIMCTRLn(online_timer->id));
	__raw_writel(BM_TIMROT_TIMCTRLn_MATCH_MODE                   , online_timer->base + HW_TIMROT_TIMCTRLn_SET(online_timer->id));
#endif
#ifdef CONFIG_IPIPE
	__ipipe_mach_timerint = online_timer->irq;
	__ipipe_mach_ticks_per_jiffy = (clk_get_rate(online_timer->clk) + HZ/2) / HZ;
	mxs_min_delay = ((__ipipe_cpu_freq + 500000) / 1000000) ?: 1;
#ifdef CONFIG_IPIPE_ARM_KUSER_TSC
#if 0
	mxs_tsc_info.freq = clk_get_rate(online_timer->clk); // 32kHz also __ipipe_mach_hrclock_freq in arch/arm/include/asm/ipipe.h
	mxs_tsc_info.type = IPIPE_TSC_TYPE_FREERUNNING_COUNTDOWN;
	mxs_tsc_info.u.counter_paddr = TIMROT_PHYS_ADDR + HW_TIMROT_RUNNING_COUNTn(online_timer->id);
	mxs_tsc_info.u.mask = 0xFFFFffff;
	printk("mxs_timer_init: TIMER%d (%lu), also clock (%u)\n", online_timer->id, clk_get_rate(online_timer->clk), mxs_tsc_info.freq);
#else
	mxs_tsc_info.freq = 1000000L; // 1MHz also __ipipe_mach_hrclock_freq in arch/arm/include/asm/ipipe.h 
	mxs_tsc_info.type = IPIPE_TSC_TYPE_FREERUNNING;
	mxs_tsc_info.u.counter_paddr = DIGCTL_PHYS_ADDR + HW_DIGCTL_MICROSECONDS;
	mxs_tsc_info.u.mask = 0xFFFFffff;
	printk("mxs_timer_init: TIMER%d (%lu), DIGCTL us (%u)\n", online_timer->id, clk_get_rate(online_timer->clk), mxs_tsc_info.freq);
#endif
#endif
	mxs_tsc_info.counter_vaddr = (unsigned long)(IO_ADDRESS(mxs_tsc_info.u.counter_paddr));
	__ipipe_tsc_register(&mxs_tsc_info);
#endif /* CONFIG_IPIPE */
	mxs_clocksource_init(online_timer->clk);
	mxs_clockevent_init(online_timer->clk);
	setup_irq(online_timer->irq, &mxs_timer_irq);
}


