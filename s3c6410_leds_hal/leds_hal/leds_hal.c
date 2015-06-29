/*
 * leds_hal.c
 *
 *  Created on: Oct 19, 2013
 *      Author: bing
 */

#include "leds_hal.h"
#include "../leds_hal_define.h"

#define DEV_NAME "/dev/s3c6410_leds_hal"

int dev_file = 0;

int led_on_off(struct led_control_device_t *dev, int32_t led, int32_t on_off){
	unsigned char buf[5];

	if(led < 0 || led >3){
		LOGI("LED Stub: set led %d on error, no the led.\n", led);
		return 0;
	}

	if(on_off == 1)
		LOGI("LED Stub: set %d on", led);
	else
		LOGI("LED Stub: set %d off", led);

	buf[0]= S3C6410_LEDS_HAL_READ_GPMDAT;
	write(dev_file, buf, 5);
	read(dev_file, buf, 5);

	buf[0]= S3C6410_LEDS_HAL_WRITE_GPMDAT;

	switch(led){
	case 0:
		if(on_off == 0)
			buf[4] |= 0x10;
		else
			buf[4] &= 0xEF;
		break;

	case 1:
		if(on_off == 0)
			buf[4] |= 0x20;
		else
			buf[4] &= 0xDF;
		break;
	case 2:
		if(on_off == 0)
			buf[4] |= 0x40;
		else
			buf[4] &= 0xBF;
		break;
	case 3:
		if(on_off == 0)
			buf[4] |= 0x80;
		else
			buf[4] &= 0x7F;
		break;
	}
	write(dev_file, buf, 5);
	return 0;
}

int led_on(struct led_control_device_t *dev, int32_t led){
	return led_on_off(dev, led, 1);
}

int led_off(struct led_control_device_t *dev, int32_t led){
	return led_on_off(dev, led, 0);
}

int led_device_close(struct hw_device_t *dev){
	struct led_control_device_t *ctx =(struct led_control_device_t *)dev;
	if(ctx)
		free(ctx);
	close(dev_file);
	return 0;
}

void leds_init_gpm(){

	/*
	 * 初始化GPMCON寄存器
	 * */
	unsigned char buf[5];
	buf[0] = S3C6410_LEDS_HAL_READ_GPMCON;
	read(dev_file, buf, 5);

//	buf[1] &= ~(0xff);
	buf[1] |= 0x11;

//	buf[2] &= ~(0xff);
	buf[2] |= 0x11;

	buf[0] = S3C6410_LEDS_HAL_WRITE_GPMCON;
	write(dev_file, buf, 5);

	/*
	 * 初始化GPMDAT寄存器
	 * */

}
static int led_device_open(struct hw_module_t *module, const char *name,
		struct hw_device_t **device)
{
	struct led_control_device_t *dev;
	dev=(struct led_control_device_t *)malloc(sizeof(*dev));
	memset(dev, 0, sizeof(*dev));

	dev->hw_device.tag = HARDWARE_DEVICE_TAG;
	dev->hw_device.version = 0;
	dev->hw_device.module = (struct hw_module_t *)module;
	dev->hw_device.close = led_device_close;
	dev->set_on = led_on;
	dev->set_off = led_off;

	*device = (struct hw_device_t *)dev;

	dev_file= open(DEV_NAME, O_RDWR);
	if(dev_file <0)
		LOGI("LED Stub: open "DEV_NAME" failed.\n");
	else
		LOGI("LED Stub: open "DEV_NAME" success.\n");

	leds_init_gpm();
	return 0;
}
struct hw_module_methods_t led_module_methods =
{
	open: led_device_open
};
struct led_module_t HAL_MODULE_INFO_SYM = {
		hw_module:
		{
			tag: HARDWARE_MODULE_TAG,
			version_major: 1,
			version_minor: 0,
			id: LED_HARDWARE_MODULE_ID,
			name: "simple LED HAL Stub",
			author: "Bing",
			methods: &led_module_methods,
		}
};

