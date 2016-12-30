#include <linux/init.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/unistd.h>
#include <mach/regs-pwm.h>
#include <mach/system.h>
#include <asm/uaccess.h>
#include <asm/io.h>	//include __raw_writel 
#include <asm/system.h>

#include <linux/mxs-buzzer.h>

static int buzzer_open(struct inode *inode, struct file *file);
static int buzzer_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg);
static int buzzer_close(struct inode *inode, struct file *file);


struct buzzer_dev {
	struct timer_list bz_timer; /*timer to stop the buzzer after duration */
	struct clk *bz_pwm; /* clock that control the pwm */
	struct cdev bz_cdev; /* char device structure for buzzer*/
	dev_t bz_dev;
	int bz_has_opened;
};

struct buzzer_dev *buzzer = NULL;

/*
Tpwm =  BF_PWM_PERIODn_PERIOD * 1/(24Mhz: CDIV)
*/
/*scale factors to map a volume range 0-100 to a duty cycle range 10-50 multiplied by ten to work with integer x = (y*10 -(-SCALE_Q))/SCALE_M */
//#define SCALE_Q		250  
//#define SCALE_M		25 
#define SCALE_Q		0  
#define SCALE_M		10

#if defined CONFIG_MECT_VAL01
#define BUZZER_CLOCK_CYCLE_IN_PERIOD 	749 //500Hz //374 1kHz //81 corresponds to a frequency for pwm = 3.5 Khz
#else
#define BUZZER_CLOCK_CYCLE_IN_PERIOD 	599
#endif

#if defined CONFIG_MECT_VAL01
struct buzzer_mesg settings;
#endif

static const struct file_operations buzzer_fops ={
	.read = NULL,
	.write = NULL,
	.open = buzzer_open,
	.ioctl = buzzer_ioctl,
	.release = buzzer_close,
};

/******************************************************************************************* 
Open function 
********************************************************************************************/  

static int buzzer_open(struct inode *inode, struct file *file)  
{  
	struct buzzer_dev *buzzer; 
	int ret = 0;
	buzzer = container_of(inode->i_cdev, struct buzzer_dev, bz_cdev);  

	if(buzzer->bz_has_opened) 
		return -EBUSY;  

	buzzer->bz_pwm = clk_get(NULL, "pwm");
	if (IS_ERR(buzzer->bz_pwm)) {
		ret = PTR_ERR(buzzer->bz_pwm );
		return ret;
	}
	clk_enable(buzzer->bz_pwm);

        file->private_data = buzzer;
        buzzer->bz_has_opened++;   //Ensure that only one process use the device only once  

   
 	return 0;  
}  
 
/******************************************************************************************* 
Release function 
********************************************************************************************/ 
static int buzzer_close(struct inode *inode,struct file *file)
{	
	int ret;
	struct buzzer_dev *buzzer = file->private_data;
	
	clk_disable(buzzer->bz_pwm);
	clk_put(buzzer->bz_pwm);

	ret = del_timer(&(buzzer->bz_timer));
  	if (ret) 
		printk(KERN_WARNING "The timer is still in use...\n");
	
	buzzer->bz_has_opened--;   

	return 0;
}

/******************************************************************************************* 
Ioctl function 
********************************************************************************************/ 
static void buzzer_stop(unsigned long data)
{
	__raw_writel(BF_PWM_ACTIVEn_INACTIVE(0) | /* having 0 set for both inactive and active shut up the pwm*/
		     BF_PWM_ACTIVEn_ACTIVE(0),
		     REGS_PWM_BASE + HW_PWM_ACTIVEn(3));
	__raw_writel(BF_PWM_PERIODn_CDIV(5) |	/* divide by ??? */
		     BF_PWM_PERIODn_INACTIVE_STATE(2) |	/* low */
		     BF_PWM_PERIODn_ACTIVE_STATE(3) |	/* high */
		     BF_PWM_PERIODn_PERIOD(BUZZER_CLOCK_CYCLE_IN_PERIOD),
		     REGS_PWM_BASE + HW_PWM_PERIODn(3));
	__raw_writel(BM_PWM_CTRL_PWM3_ENABLE, REGS_PWM_BASE + HW_PWM_CTRL_CLR);	
	
}

#if defined CONFIG_MECT_VAL01
static int buzzer_beep(struct buzzer_dev *buzzer, struct buzzer_mesg settings)
{
	int duty_cycle = 0;
	
	duty_cycle = (((settings.volume * 10 + SCALE_Q)/SCALE_M) * BUZZER_CLOCK_CYCLE_IN_PERIOD)/100;
#else
static int buzzer_beep(struct buzzer_dev *buzzer, unsigned int duration)
{
#endif
	int ret=0;
	setup_timer(&(buzzer->bz_timer), buzzer_stop, 0 );

#if defined CONFIG_MECT_VAL01
	ret = mod_timer( &(buzzer->bz_timer), jiffies + msecs_to_jiffies(settings.duration) );
#else
  	ret = mod_timer( &(buzzer->bz_timer), jiffies + msecs_to_jiffies(duration) );
#endif
  	if (ret) 
		printk(KERN_INFO "Error in mod_timer\n");	

#if defined CONFIG_MECT_VAL01
	__raw_writel(BF_PWM_ACTIVEn_INACTIVE(duty_cycle) |
#else	
	__raw_writel(BF_PWM_ACTIVEn_INACTIVE(50) |
#endif
		     BF_PWM_ACTIVEn_ACTIVE(0),
		     REGS_PWM_BASE + HW_PWM_ACTIVEn(3));


	__raw_writel(BF_PWM_PERIODn_CDIV(5) |	/* divide by ??? */
		     BF_PWM_PERIODn_INACTIVE_STATE(2) |	/* low */
		     BF_PWM_PERIODn_ACTIVE_STATE(3) |	/* high */
		     BF_PWM_PERIODn_PERIOD(BUZZER_CLOCK_CYCLE_IN_PERIOD),
		     REGS_PWM_BASE + HW_PWM_PERIODn(3));
	__raw_writel(BM_PWM_CTRL_PWM3_ENABLE, REGS_PWM_BASE + HW_PWM_CTRL_SET);

	return ret;
}

static int buzzer_ioctl( __attribute__ ((unused)) struct inode *inode,struct file *file,unsigned int cmd,unsigned long arg)
{
	int ret = -ENOTTY;
	struct buzzer_dev *buzzer = file->private_data;
	
    if (_IOC_TYPE(cmd) != BUZZER_MAGIC)
        return -ENOTTY;

    if ((_IOC_DIR(cmd) & _IOC_READ) && (!access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd))))
        return -EFAULT;

    if ((_IOC_DIR(cmd) & _IOC_WRITE) && (!access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd))))
        return -EFAULT;

    switch (cmd) {
        case BUZZER_BEEP:
#if defined CONFIG_MECT_VAL01
	    __copy_from_user(&settings, (void *)arg, sizeof(settings));
	    buzzer_beep(buzzer, settings);
#else
            buzzer_beep(buzzer, (unsigned int)arg);
#endif
            ret = 0;
            break;
	default:
	printk(KERN_WARNING "%s: unknown commmand %d\n", __func__, cmd);
   }
   return ret;	
	
}


/*********************************************************************************
The module_init and module_cleanup function
*********************************************************************************/
int buzzer_init(void)
{
	int ret;
	dev_t dev;
	

	/*requesting mejor and minor to the kernel*/
	dev = MKDEV(BUZZER_MAJOR, BUZZER_MINOR);
	ret = register_chrdev_region(dev, 0, "buzzer");

	if(ret < 0)
	{
		printk(KERN_WARNING "BUZZER: can't get major %d\n",BUZZER_MAJOR);
		return ret;
	}
	/*allocating memory for my device*/	
	buzzer = kzalloc(sizeof(struct buzzer_dev), GFP_KERNEL);
	/*init the cdev structure beside memory allocation*/
	cdev_init(&(buzzer->bz_cdev), &buzzer_fops);
	
	buzzer->bz_cdev.owner=THIS_MODULE;
	buzzer->bz_dev = dev;
	buzzer->bz_has_opened = 0;
	/*registering the char device with the kernel*/
        ret = cdev_add(&(buzzer->bz_cdev),buzzer->bz_dev,1);

       if( ret < 0 )
       {
		printk(KERN_WARNING "Error registering device driver for buzzer\n");
		unregister_chrdev_region(buzzer->bz_dev,1);
		kfree(buzzer);
		return ret;
       }

       printk(KERN_INFO "Buzzer successfully registered!\n");



	return 0;
}
void buzzer_exit(void)
{
	unregister_chrdev_region(buzzer->bz_dev,1);
	cdev_del(&(buzzer->bz_cdev));
	kfree(buzzer);
	printk(KERN_INFO "BUZZER EXIT!\n");
}

module_init(buzzer_init);
module_exit(buzzer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mect srl");



