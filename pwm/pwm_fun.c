/*
 * pwm_fun.c
 *
 *  Created on: Oct 4, 2013
 *      Author: bing
 */

#include "pwm_fun.h"

void pwm_start(void){
	unsigned tmp;
	tmp=ioread32(S3C64XX_GPFCON);

	tmp &= ~(0x3 << 28);
	tmp |=(0x2 << 28);

	iowrite32(tmp, S3C64XX_GPFCON);
}

void pwm_stop(void){
	unsigned tmp;
	tmp=ioread32(S3C64XX_GPFCON);

	tmp &= ~(0x3 << 28);

	iowrite32(tmp, S3C64XX_GPFCON);
}
