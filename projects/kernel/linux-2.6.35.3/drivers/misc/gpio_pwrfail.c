/*
 * Driver for powerfail detection based on GPIO interrrupt.
 *
 * Based on work done by Phil Blundell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>

#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/gpio_pwrfail.h>
#include <linux/gpio.h>

#include <mach/lcdif.h>
#include <mach/regs-lcdif.h>
#include <mach/regs-pwm.h>
#include <mach/regs-power.h>
#include <mach/pinctrl.h>



//defines for pheriperal shutdown
#define REGS_ENET_BASE IO_ADDRESS(ENET_PHYS_ADDR)	
#define HW_ENET_MAC_ECR	(0x00000024)
#define BM_ENET_MAC_ECR_SLEEP	(0x00000008)

#define REGS_USBPHY0_BASE	IO_ADDRESS(USBPHY0_PHYS_ADDR)
#define REGS_USBPHY1_BASE	IO_ADDRESS(USBPHY1_PHYS_ADDR)
#define HW_USBPHY_CTRL_SET	(0x00000034)
#define HW_USBPHY_CTRL_CLR	(0x00000038)
#define BM_USBPHY_CTRL_CLKGATE	0x40000000

#define REGS_CAN0_BASE	IO_ADDRESS(CAN0_PHYS_ADDR)
#define REGS_CAN1_BASE	IO_ADDRESS(CAN1_PHYS_ADDR)
#define CAN_HW_REG_MCR		0x00
#define __MCR_MDIS		(1 << 31)

#define REGS_SSP0_BASE	IO_ADDRESS(SSP0_PHYS_ADDR)
#define REGS_SSP1_BASE	IO_ADDRESS(SSP1_PHYS_ADDR)
#define REGS_SSP2_BASE	IO_ADDRESS(SSP2_PHYS_ADDR)
#define REGS_SSP3_BASE	IO_ADDRESS(SSP3_PHYS_ADDR)
#define REGS_PERFMON_BASE IO_ADDRESS(PERFMON_PHYS_ADDR)
#define HW_PERFMON_CTRL_SET (0x00000004)
#define BM_PERFMON_CTRL_CLKGATE 0x40000000
#define BM_PERFMON_CTRL_SFTRST 0x80000000

#define RTC_BASE_ADDR IO_ADDRESS(RTC_PHYS_ADDR)	

#define AUART0_BASE_ADDR IO_ADDRESS(AUART0_PHYS_ADDR)
#define AUART1_BASE_ADDR IO_ADDRESS(AUART1_PHYS_ADDR)
#define AUART2_BASE_ADDR IO_ADDRESS(AUART2_PHYS_ADDR)
#define AUART3_BASE_ADDR IO_ADDRESS(AUART3_PHYS_ADDR)
#define AUART4_BASE_ADDR IO_ADDRESS(AUART4_PHYS_ADDR)
#define HW_UARTAPP_CTRL0_SET	(0x00000004)
#define BM_UARTAPP_CTRL0_CLKGATE	0x40000000
#define BM_UARTAPP_CTRL0_SFTRST	0x80000000

#define PXP_BASE_ADDR 	IO_ADDRESS(PXP_PHYS_ADDR)
#define HW_PXP_CTRL_SET	(0x00000004)
#define BM_PXP_CTRL_CLKGATE	0x40000000
#define BM_PXP_CTRL_SFTRST	0x80000000

#define SAIF0_BASE_ADDR IO_ADDRESS(SAIF0_PHYS_ADDR)
#define SAIF1_BASE_ADDR IO_ADDRESS(SAIF0_PHYS_ADDR)
#define HW_SAIF_CTRL_SET	(0x00000004)
#define BM_SAIF_CTRL_CLKGATE	0x40000000
#define BM_SAIF_CTRL_SFTRST	0x80000000

#define SPDIF_BASE_ADDR IO_ADDRESS(SPDIF_PHYS_ADDR)
#define HW_SPDIF_CTRL_SET	(0x00000004)
#define BM_SPDIF_CTRL_CLKGATE	0x40000000
#define BM_SPDIF_CTRL_SFTRST	0x80000000

#define HSADC_BASE_ADDR IO_ADDRESS(HSADC_PHYS_ADDR)
#define HW_HSADC_CTRL0_SET	(0x00000004)
#define BM_HSADC_CTRL0_CLKGATE	0x40000000
#define BM_HSADC_CTRL0_SFTRST	0x80000000
#define HW_HSADC_CTRL2_SET	(0x00000024)
#define BM_HSADC_CTRL2_POWERDOWN 0x00002000

#define PINID_SSP2_MOSI		MXS_PIN_ENCODE(2, 17)
#define PINID_AUART2_TX		MXS_PIN_ENCODE(3, 9)
#define PINID_SSP1_DATA3	MXS_PIN_ENCODE(2, 15)
#define PINID_SSP1_DATA0	MXS_PIN_ENCODE(2, 14)



struct gpio_pwrfail_data {
	struct gpio_pwrfail *pwrfail;
	struct work_struct work;
	bool disabled;
};

struct gpio_pwrfail_drvdata {
	unsigned int n_pwrfails;
	struct gpio_pwrfail_data data[0];
};



#ifdef PWRFAIL_SIGNAL


struct dentry *file;
int pid;

struct siginfo pwr_sig_info;
struct task_struct *t;

static int retentive_shutdown( __attribute__ ((unused)) struct inode *inode,struct file *file,unsigned int cmd,__attribute__ ((unused)) unsigned long arg)
{
	int ret = -ENOTTY;
	
    if (_IOC_TYPE(cmd) != RETENTIVE_MAGIC)
        return -ENOTTY;

    if ((_IOC_DIR(cmd) & _IOC_READ) && (!access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd))))
        return -EFAULT;

    if ((_IOC_DIR(cmd) & _IOC_WRITE) && (!access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd))))
        return -EFAULT;

    switch (cmd) {
        case RETENTIVE_POWEROFF:
	    __raw_writel(0x3e770000, REGS_POWER_BASE + HW_POWER_RESET);
		/*power down*/
	    __raw_writel(0x3e770001, REGS_POWER_BASE + HW_POWER_RESET);
            
            ret = 0;
            break;
#ifdef PWRFAIL_DEBUG
	case RETENTIVE_GPIOCTRL:
		//printk(KERN_INFO "%s: setting to 1 PINID_SSP1_DATA0\n", __func__);
		gpio_set_value(MXS_PIN_TO_GPIO(PINID_SSP1_DATA0), 1);
		break;
#endif
	default:
	printk(KERN_WARNING "%s: unknown commmand %d\n", __func__, cmd);
   }
   return ret;	
	
}

static ssize_t write_pid(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	char mybuf[10];

	/* read the value from user space */
	if(count > 10)
		return -EINVAL;
	copy_from_user(mybuf, buf, count);
	sscanf(mybuf, "%d", &pid);
	printk(KERN_INFO "pid = %d\n", pid);

	memset(&pwr_sig_info, 0, sizeof(struct siginfo));
	pwr_sig_info.si_signo = SIGPWRFAIL;
	pwr_sig_info.si_code = SI_QUEUE;	// this is bit of a trickery: SI_QUEUE is normally used by sigqueue from user space,
	// and kernel space should use SI_KERNEL. But if SI_KERNEL is used the real_time data 
	// is not delivered to the user space signal handler function. 
	pwr_sig_info.si_int = 1234;  		//real time signals may have 32 bits of data.

	rcu_read_lock();
	t = find_task_by_vpid(pid);  //find the task_struct associated with this pid
	if(t == NULL){
		printk("no such pid\n");
		rcu_read_unlock();
		return -ENODEV;
	}
	rcu_read_unlock();

	return count;
}

static const struct file_operations my_fops = {
	.write = write_pid,
	.ioctl = retentive_shutdown
};

#endif


static void gpio_pwrfail_work_func(struct work_struct *work)
{
	struct gpio_pwrfail_data *plat_data = container_of(work, struct gpio_pwrfail_data, work);
	struct gpio_pwrfail *pwrfail = plat_data->pwrfail;
	int val;
	int level = (gpio_get_value(pwrfail->gpio) ? 1 : 0);

#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: ENTER level %d\n", __func__, level);
#endif

	if (level) //pwrfail event
	{
#ifdef PWRFAIL_SIGNAL
		
		if (pid > 0)
		{
			//be prepared for a possible 24V hole detection
			set_irq_type(gpio_to_irq(pwrfail->gpio), IRQ_TYPE_EDGE_FALLING);
		
		//usb disable
			gpio_direction_output(MXS_PIN_TO_GPIO(PINID_AUART2_TX), 0);
			gpio_set_value(MXS_PIN_TO_GPIO(PINID_AUART2_TX), 0);

		//lan disable 
#if defined CONFIG_MECT_CUSTOMIZATION
#if defined CONFIG_MECT_VAL01
		        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 1);
#else
		        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 1);
#endif
#else
		        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 1);
#endif

		//stop ethernet
			//put the controller in sleep mode when asserted 
			val = __raw_readl(REGS_ENET_BASE + HW_ENET_MAC_ECR);
			val |= (BM_ENET_MAC_ECR_SLEEP);
			__raw_writel(val, REGS_ENET_BASE + HW_ENET_MAC_ECR);


		//stop LCDIF
			//__raw_writel(BM_LCDIF_CTRL_CLKGATE, REGS_LCDIF_BASE + HW_LCDIF_CTRL_SET);


		//stop bcklight
			__raw_writel(BF_PWM_ACTIVEn_INACTIVE(0) |
				     BF_PWM_ACTIVEn_ACTIVE(0),
				     REGS_PWM_BASE + HW_PWM_ACTIVEn(2));
			__raw_writel(BF_PWM_PERIODn_CDIV(6) |	/* divide by 64 */
				     BF_PWM_PERIODn_INACTIVE_STATE(2) |	/* low */
				     BF_PWM_PERIODn_ACTIVE_STATE(3) |	/* high */
				     BF_PWM_PERIODn_PERIOD(599),
				     REGS_PWM_BASE + HW_PWM_PERIODn(2));
			__raw_writel(BM_PWM_CTRL_PWM2_ENABLE, REGS_PWM_BASE + HW_PWM_CTRL_CLR);

		//usb

			//__raw_writel(BM_USBPHY_CTRL_CLKGATE, REGS_USBPHY0_BASE + HW_USBPHY_CTRL_SET);
			//__raw_writel(BM_USBPHY_CTRL_CLKGATE, REGS_USBPHY1_BASE + HW_USBPHY_CTRL_SET);

		//can
		/*	val = __raw_readl(REGS_CAN0_BASE + CAN_HW_REG_MCR);
			__raw_writel(val | __MCR_MDIS, REGS_CAN0_BASE + CAN_HW_REG_MCR);
			val = __raw_readl(REGS_CAN1_BASE + CAN_HW_REG_MCR);
			__raw_writel(val | __MCR_MDIS, REGS_CAN1_BASE + CAN_HW_REG_MCR);
		*/

#ifdef PWRFAIL_DEBUG_PRINT
			printk(" 2pid");
#endif
				/* send the signal */
				if (send_sig_info(SIGPWRFAIL, &pwr_sig_info, t) < 0) {
					printk(KERN_INFO "error sending signal to pid %d\n", pid);
				}
				else
				{
#ifdef PWRFAIL_DEBUG_PRINT
					printk(" sent");
#endif		
				}
		}
		else
		{
#ifdef PWRFAIL_DEBUG_PRINT
		printk(" no_pid");
#endif			
		}
#endif

	}
	else //we have 24V woking again
	{
		set_irq_type(gpio_to_irq(pwrfail->gpio), IRQ_TYPE_EDGE_RISING);
		
		//enable USB
		gpio_direction_output(MXS_PIN_TO_GPIO(PINID_AUART2_TX), 1);
		gpio_set_value(MXS_PIN_TO_GPIO(PINID_AUART2_TX), 1);

		//__raw_writel(BM_USBPHY_CTRL_CLKGATE, REGS_USBPHY0_BASE + HW_USBPHY_CTRL_CLR);
		//__raw_writel(BM_USBPHY_CTRL_CLKGATE, REGS_USBPHY1_BASE + HW_USBPHY_CTRL_CLR);

		//enable LAN
		val = __raw_readl(REGS_ENET_BASE + HW_ENET_MAC_ECR);
		val &= ~(BM_ENET_MAC_ECR_SLEEP);
		__raw_writel(val, REGS_ENET_BASE + HW_ENET_MAC_ECR);

#if defined CONFIG_MECT_CUSTOMIZATION
#if defined CONFIG_MECT_VAL01
	        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 0);
#else
	        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 0);
#endif
#else
	        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 0);
#endif

		//enable LCD
		//__raw_writel(BM_LCDIF_CTRL_CLKGATE, REGS_LCDIF_BASE + HW_LCDIF_CTRL_CLR);

		
		__raw_writel(BF_PWM_ACTIVEn_INACTIVE(0) |
			     BF_PWM_ACTIVEn_ACTIVE(0),
			     REGS_PWM_BASE + HW_PWM_ACTIVEn(2));

		__raw_writel(BF_PWM_PERIODn_CDIV(6) |	/* divide by 64 */
			     BF_PWM_PERIODn_INACTIVE_STATE(2) |	/* low */
			     BF_PWM_PERIODn_ACTIVE_STATE(3) |	/* high */
			     BF_PWM_PERIODn_PERIOD(599),
			     REGS_PWM_BASE + HW_PWM_PERIODn(2));
		__raw_writel(BM_PWM_CTRL_PWM2_ENABLE, REGS_PWM_BASE + HW_PWM_CTRL_SET);

	}

}


static irqreturn_t gpio_pwrfails_isr(int irq, void *dev_id)
{
	struct gpio_pwrfail_data *plat_data = dev_id;
	struct gpio_pwrfail *pwrfail = plat_data->pwrfail;
	
	int val;
	int level;

#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT PWRFAIL event INTERRUPT %s\n", __func__);
#endif

#ifdef PWRFAIL_DEBUG
	//spengo il led di segnalazione T4
	gpio_set_value(MXS_PIN_TO_GPIO(PINID_SSP1_DATA0), 0);
#endif
	BUG_ON(irq != gpio_to_irq(pwrfail->gpio));
	level = (gpio_get_value(pwrfail->gpio) ? 1 : 0);

#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: ENTER level %d\n", __func__, level);
#endif

#if defined CONFIG_MECT_RAISING_PWRFAIL
	if (!level) //pwrfail event for tpac1006 is reversed wrt the ATN01
#else
	if (level) //pwrfail event default as ATN01
#endif
	{
#ifdef PWRFAIL_SIGNAL
		
		if (pid > 0)
		{
			#if defined CONFIG_MECT_RAISING_PWRFAIL
			//hole detection is reversed as well
			set_irq_type(gpio_to_irq(pwrfail->gpio), IRQ_TYPE_EDGE_RISING);	
			#else
			set_irq_type(gpio_to_irq(pwrfail->gpio), IRQ_TYPE_EDGE_FALLING);
			#endif

		
		//usb disable
			gpio_direction_output(MXS_PIN_TO_GPIO(PINID_AUART2_TX), 0);
			gpio_set_value(MXS_PIN_TO_GPIO(PINID_AUART2_TX), 0);

		//lan disable 
#if defined CONFIG_MECT_CUSTOMIZATION
#if defined CONFIG_MECT_VAL01
		        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 1);
#else
		        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 1);
#endif
#else
		        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 1);
#endif

		//stop ethernet
			//put the controller in sleep mode when asserted 
			val = __raw_readl(REGS_ENET_BASE + HW_ENET_MAC_ECR);
			val |= (BM_ENET_MAC_ECR_SLEEP);
			__raw_writel(val, REGS_ENET_BASE + HW_ENET_MAC_ECR);


		//stop LCDIF
			//__raw_writel(BM_LCDIF_CTRL_CLKGATE, REGS_LCDIF_BASE + HW_LCDIF_CTRL_SET);


		//stop bcklight
			__raw_writel(BF_PWM_ACTIVEn_INACTIVE(0) |
				     BF_PWM_ACTIVEn_ACTIVE(0),
				     REGS_PWM_BASE + HW_PWM_ACTIVEn(2));
			__raw_writel(BF_PWM_PERIODn_CDIV(6) |	/* divide by 64 */
				     BF_PWM_PERIODn_INACTIVE_STATE(2) |	/* low */
				     BF_PWM_PERIODn_ACTIVE_STATE(3) |	/* high */
				     BF_PWM_PERIODn_PERIOD(599),
				     REGS_PWM_BASE + HW_PWM_PERIODn(2));
			__raw_writel(BM_PWM_CTRL_PWM2_ENABLE, REGS_PWM_BASE + HW_PWM_CTRL_CLR);

		//usb

			//__raw_writel(BM_USBPHY_CTRL_CLKGATE, REGS_USBPHY0_BASE + HW_USBPHY_CTRL_SET);
			//__raw_writel(BM_USBPHY_CTRL_CLKGATE, REGS_USBPHY1_BASE + HW_USBPHY_CTRL_SET);

		//can
		/*	val = __raw_readl(REGS_CAN0_BASE + CAN_HW_REG_MCR);
			__raw_writel(val | __MCR_MDIS, REGS_CAN0_BASE + CAN_HW_REG_MCR);
			val = __raw_readl(REGS_CAN1_BASE + CAN_HW_REG_MCR);
			__raw_writel(val | __MCR_MDIS, REGS_CAN1_BASE + CAN_HW_REG_MCR);
		*/

#ifdef PWRFAIL_DEBUG_PRINT
			printk(" 2pid");
#endif
				/* send the signal */
				if (send_sig_info(SIGPWRFAIL, &pwr_sig_info, t) < 0) {
					printk(KERN_INFO "error sending signal to pid %d\n", pid);
				}
				else
				{
#ifdef PWRFAIL_DEBUG_PRINT
					printk(" sent");
#endif		
				}
		}
		else
		{
#ifdef PWRFAIL_DEBUG_PRINT
		printk(" no_pid");
#endif			
		}
#endif

	}
	else //we have 24V woking again
	{
		#if defined CONFIG_MECT_RAISING_PWRFAIL
		set_irq_type(gpio_to_irq(pwrfail->gpio), IRQ_TYPE_EDGE_FALLING);
		#else
		set_irq_type(gpio_to_irq(pwrfail->gpio), IRQ_TYPE_EDGE_RISING);
		#endif
		
		//enable USB
		gpio_direction_output(MXS_PIN_TO_GPIO(PINID_AUART2_TX), 1);
		gpio_set_value(MXS_PIN_TO_GPIO(PINID_AUART2_TX), 1);

		//__raw_writel(BM_USBPHY_CTRL_CLKGATE, REGS_USBPHY0_BASE + HW_USBPHY_CTRL_CLR);
		//__raw_writel(BM_USBPHY_CTRL_CLKGATE, REGS_USBPHY1_BASE + HW_USBPHY_CTRL_CLR);

		//enable LAN
		val = __raw_readl(REGS_ENET_BASE + HW_ENET_MAC_ECR);
		val &= ~(BM_ENET_MAC_ECR_SLEEP);
		__raw_writel(val, REGS_ENET_BASE + HW_ENET_MAC_ECR);

#if defined CONFIG_MECT_CUSTOMIZATION
#if defined CONFIG_MECT_VAL01
	        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 0);
#else
	        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 0);
#endif
#else
	        gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA3), 0);
#endif

		//enable LCD
		//__raw_writel(BM_LCDIF_CTRL_CLKGATE, REGS_LCDIF_BASE + HW_LCDIF_CTRL_CLR);

		
		__raw_writel(BF_PWM_ACTIVEn_INACTIVE(0) |
			     BF_PWM_ACTIVEn_ACTIVE(0),
			     REGS_PWM_BASE + HW_PWM_ACTIVEn(2));

		__raw_writel(BF_PWM_PERIODn_CDIV(6) |	/* divide by 64 */
			     BF_PWM_PERIODn_INACTIVE_STATE(2) |	/* low */
			     BF_PWM_PERIODn_ACTIVE_STATE(3) |	/* high */
			     BF_PWM_PERIODn_PERIOD(599),
			     REGS_PWM_BASE + HW_PWM_PERIODn(2));
		__raw_writel(BM_PWM_CTRL_PWM2_ENABLE, REGS_PWM_BASE + HW_PWM_CTRL_SET);

	}


	//schedule_work(&plat_data->work);

	return IRQ_HANDLED;
}


static int __devinit gpio_pwrfail_setup(struct platform_device *pdev,
					 struct gpio_pwrfail_data *plat_data,
					 struct gpio_pwrfail *pwrfail)
{

	char *desc = pwrfail->desc ? pwrfail->desc : "gpio_pwrfails";
	struct device *dev = &pdev->dev;
	unsigned long irqflags;
	int irq, error;

#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: ENTER\n", __func__);
#endif
#ifdef PWRFAIL_DEBUG
	//led di segnalazione per debug
	error = gpio_request(MXS_PIN_TO_GPIO(PINID_SSP1_DATA0), "debug_pwrfail_gpio");
	if (error < 0) {
		printk(KERN_INFO "failed to request GPIO %d, error %d\n",
			MXS_PIN_TO_GPIO(PINID_SSP1_DATA0), error);
		goto fail2;
	}
	else
	{
		printk(KERN_INFO "requested debug GPIO %d, error %d\n",
			MXS_PIN_TO_GPIO(PINID_SSP1_DATA0), error);
		gpio_direction_output(MXS_PIN_TO_GPIO(PINID_SSP1_DATA0), 0);
		printk(KERN_INFO "set direction output for debug GPIO %d, error %d\n",
			MXS_PIN_TO_GPIO(PINID_SSP1_DATA0), error);
	}
#endif

	//INIT_WORK(&plat_data->work, gpio_pwrfail_work_func);
	error = gpio_request(pwrfail->gpio, desc);
	if (error < 0) {
		dev_err(dev, "failed to request GPIO %d, error %d\n",
			pwrfail->gpio, error);
		goto fail2;
	}
#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: gpio_request completed\n", __func__);
#endif
	error = gpio_direction_input(pwrfail->gpio);
	if (error < 0) {
		dev_err(dev, "failed to configure"
			" direction for GPIO %d, error %d\n",
			pwrfail->gpio, error);
		goto fail3;
	}
#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: gpio_direction_input completed\n", __func__);
#endif
	irq = gpio_to_irq(pwrfail->gpio);
	if (irq < 0) {
		error = irq;
		dev_err(dev, "Unable to get irq number for GPIO %d, error %d\n",
			pwrfail->gpio, error);
		goto fail3;
	}
#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: gpio_to_irq %d\n", __func__, irq);
#endif
         //irqflags =  IRQF_TRIGGER_RISING; /* | IRQF_TRIGGER_FALLING; */
	irqflags =  IRQF_TRIGGER_RISING;
	
	/*
	 * If platform has specified that the button can be disabled,
	 * we don't want it to share the interrupt line.
	 */
	if (!pwrfail->can_disable)
		irqflags |= IRQF_SHARED;

	error = request_irq(irq, gpio_pwrfails_isr, irqflags, desc, plat_data);
	if (error) {
		dev_err(dev, "Unable to claim irq %d; error %d\n",
			irq, error);
		goto fail3;
	}
#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: SETUP REGULAR END\n", __func__);
#endif
	return 0;

fail3:
#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: EXIT FAIL3\n", __func__);
#endif
	gpio_free(pwrfail->gpio);
fail2:
#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: EXIT FAIL2\n", __func__);
#endif
	return error;
}


static int __devinit gpio_pwrfails_probe(struct platform_device *pdev)
{

	struct gpio_pwrfail_platform_data *pdata = pdev->dev.platform_data;
	struct gpio_pwrfail_drvdata *ddata;
	struct device *dev = &pdev->dev;
	int i, error;
	
#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: ENTER\n", __func__);
#endif	

	ddata = kzalloc(sizeof(struct gpio_pwrfail_drvdata) +
			pdata->npwrfails * sizeof(struct gpio_pwrfail_data),
			GFP_KERNEL);

	if (!ddata ) {
		dev_err(dev, "failed to allocate state\n");
		error = -ENOMEM;
		goto fail1;
	}

	ddata->n_pwrfails = pdata->npwrfails;
	platform_set_drvdata(pdev, ddata);

	for (i = 0; i < pdata->npwrfails; i++) {
		struct gpio_pwrfail *pwrfail = &pdata->pwrfails[i];
		struct gpio_pwrfail_data *plat_data = &ddata->data[i];

		plat_data->pwrfail = pwrfail;

		error = gpio_pwrfail_setup(pdev, plat_data, pwrfail);
		if (error)
			goto fail2;

	}
	//add code to setup  and manage signalconfpid
#ifdef PWRFAIL_DEBUG_PRINT

	printk("PWRFAIL_DEBUG_PRINT %s: PROBE REGULAR END\n", __func__);
#endif
	return 0;

 fail2:
#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: EXIT FAIL2\n", __func__);
#endif
	while (--i >= 0) {
		free_irq(gpio_to_irq(pdata->pwrfails[i].gpio), &ddata->data[i]);
		cancel_work_sync(&ddata->data[i].work);
		gpio_free(pdata->pwrfails[i].gpio);
	}
	platform_set_drvdata(pdev, NULL);
 fail1:
#ifdef PWRFAIL_DEBUG_PRINT
	printk("PWRFAIL_DEBUG_PRINT %s: EXIT FAIL1\n", __func__);
#endif
	kfree(ddata);

	return error;
}



static int __devexit gpio_pwrfails_remove(struct platform_device *pdev)
{
	struct gpio_pwrfail_platform_data *pdata = pdev->dev.platform_data;
	struct gpio_pwrfail_drvdata *ddata = platform_get_drvdata(pdev);
	
	int i;

	for (i = 0; i < pdata->npwrfails; i++) {
		int irq = gpio_to_irq(pdata->pwrfails[i].gpio);
		free_irq(irq, &ddata->data[i]);
		cancel_work_sync(&ddata->data[i].work);
		gpio_free(pdata->pwrfails[i].gpio);
	}

	return 0;
}


static struct platform_driver gpio_pwrfails_device_driver = {
	.probe		= gpio_pwrfails_probe,
	.remove		= __devexit_p(gpio_pwrfails_remove),
	.driver		= {
		.name	= "gpio-pwrfails",
		.owner	= THIS_MODULE,
	}
};

static int __init gpio_pwrfails_init(void)
{
	int ret;	
	ret =  platform_driver_register(&gpio_pwrfails_device_driver);
#ifdef PWRFAIL_SIGNAL
	/* only root can write to this file (no read) */
	file = debugfs_create_file("signalconfpid", 0200, NULL, NULL, &my_fops);
	pid = 0;
#endif
	return ret;
}

static void __exit gpio_pwrfails_exit(void)
{
	platform_driver_unregister(&gpio_pwrfails_device_driver);
#ifdef PWRFAIL_SIGNAL
	if (file)
		debugfs_remove(file);
#endif
}

module_init(gpio_pwrfails_init);
module_exit(gpio_pwrfails_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Monica Donno <mdonno@mect.it>");
MODULE_DESCRIPTION("GPIO based power fail management driver");
MODULE_ALIAS("platform:gpio-pwrfails");


