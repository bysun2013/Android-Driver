/*
 * s3c6410_leds_hal.h
 *
 *  Created on: Oct 18, 2013
 *      Author: bing
 */

#ifndef S3C6410_LEDS_HAL_H_
#define S3C6410_LEDS_HAL_H_

#include <linux/module.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <mach/map.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-k.h>

#define DEVICE_NAME "s3c6410_leds_hal"
#define S3C6410_LEDS_MAJOR 0
#define S3C6410_LEDS_MINOR 234
#define S3C6410_LEDS_COUNT 1



#endif /* S3C6410_LEDS_HAL_H_ */
