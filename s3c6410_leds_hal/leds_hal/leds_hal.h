/*
 * leds_hal.h
 *
 *  Created on: Oct 19, 2013
 *      Author: bing
 */

#ifndef LEDS_HAL_H_
#define LEDS_HAL_H_

#include <hardware/hardware.h>
#include <fcntl.h>
#include <cutils/log.h>

struct led_module_t{
	struct hw_module_t hw_module;
};

struct led_control_device_t{
	struct hw_device_t hw_device;
	int (*set_on)(struct led_control_device_t *dev, int32_t led);
	int (*set_off)(struct led_control_device_t *dev, int32_t led);
};

#define LED_HARDWARE_MODULE_ID "led_hal"

#endif /* LEDS_HAL_H_ */
