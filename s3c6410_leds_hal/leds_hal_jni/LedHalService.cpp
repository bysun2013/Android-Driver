/*
 * LedHalService.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: bing
 */

#include <stdio.h>
#include <string.h>
#include <jni.h>
#include <leds_hal.h>

struct led_control_device_t *led_hal_device =NULL;

static jboolean led_SetOn(JNIEnv* env, jobject thiz, jint led){
	LOGI("LED HAL JNI: led_setOn() is invoked.");
	if(led_hal_device == NULL){
		LOGI("LED HAL JNI: led_hal_device is not fetched correctly.\n");
		return -1;
	}else{
		return led_hal_device->set_on(led_hal_device, led);
	}
}

static jboolean led_SetOff(JNIEnv* env, jobject thiz, jint led){
	LOGI("LED HAL JNI: led_setOff() is invoked.");
	if(led_hal_device == NULL){
		LOGI("LED HAL JNI: led_hal_device is not fetched correctly.\n");
		return -1;
	}else{
		return led_hal_device->set_off(led_hal_device, led);
	}
}

static inline int led_control_open(const struct hw_module_t *module, struct led_control_device_t **device){
	return module->methods->open(module, LED_HARDWARE_MODULE_ID, (struct hw_device_t **)device);
}

static jboolean led_init(JNIEnv *env, jclass clazz){
	struct led_module_t *module;

	LOGE("************Start find hal**************");
	LOGE(LED_HARDWARE_MODULE_ID);

	if(hw_get_module(LED_HARDWARE_MODULE_ID, (const struct hw_module_t**)&module) == 0)
	{
		LOGI("LedService JNI: LED Stub found.");
		if(led_control_open(&module->hw_module, &led_hal_device) ==0){
			LOGI("LedService JNI: LED Stub operation found.");
			return 0;
		}
	}
	LOGI("LedService JNI: LED Stub operation failed.");
	return -1;
}

static const JNINativeMethod methods[]={
		{"_init", "()Z", (void *)led_init},
		{"_set_on", "(I)Z", (void *)led_SetOn},
		{"_set_off", "(I)Z", (void *)led_SetOff},
};

int register_led_hal_jni(JNIEnv* env){
	static const char* const KClassName = "mobile/android/leds/hal/service/LedHalDervice";

	jclass clazz;
	clazz = env->FindClass(KClassName);
	if(clazz == NULL){
		LOGE("Can't find class %s\n", KClassName);
		return -1;
	}

	if(env->RegisterNatives(clazz, methods, sizeof(methods)/sizeof(methods[0])) != JNI_OK){
		LOGE("Failed registering methods for %s", KClassName);
		return -1;
	}
	return 0;
}
jint JNI_OnLoad(JavaVM *vm, void *reserved){
	JNIEnv* env = NULL;
	jint result = -1;
	if(vm->GetEnv((void **)&env, JNI_VERSION_1_4) != JNI_OK){
		LOGE("GetEnv failed!");
		return result;
	}
	register_led_hal_jni(env);
	return JNI_VERSION_1_4;
}

