#ifndef _GPIO_PWRFAIL_H
#define _GPIO_PWRFAIL_H


#include <linux/pwrsignal.h>


struct gpio_pwrfail {
	int gpio;
	char *desc;
#ifdef __KERNEL__
	bool can_disable;
#endif
};

struct gpio_pwrfail_platform_data {
	struct gpio_pwrfail *pwrfails;
	int npwrfails;
};

#endif
