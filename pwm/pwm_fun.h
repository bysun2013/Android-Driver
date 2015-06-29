/*
 * pwm_fun.h
 *
 *  Created on: Oct 4, 2013
 *      Author: bing
 */

#ifndef PWM_FUN_H_
#define PWM_FUN_H_

#include <linux/module.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/semaphore.h>
#include <linux/miscdevice.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <mach/map.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-f.h>

#define DEVICE_NAME "pwm_dev"

#define PWM_IOCTL_START 1
#define PWM_IOCTL_STOP 0

void pwm_start(void);
void pwm_stop(void);

#endif /* PWM_FUN_H_ */
