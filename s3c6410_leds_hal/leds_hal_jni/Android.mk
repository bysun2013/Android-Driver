LOCAL_PATH:= $(call my-dir)

# the library
# ============================================================
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS :=eng
LOCAL_MODULE:= leds_hal_jni

LOCAL_SRC_FILES := LedHalService.cpp

LOCAL_MODULE_PATH := \
/home/bing/android_project/s3c6410_leds_hal/leds_hal_jni
LOCAL_SHARED_LIBRARIES := \
    libandroid_runtime \
	libcutils \
	libhardware \
	libhardware_legacy \
	libnativehelper \
    libsystem_server \
	libutils \
	libui \
    libsurfaceflinger_client

LOCAL_C_INCLUDES += \
$(JNI_H_INCLUDE) \
hardware/leds_hal

LOCAL_PRELINK_MODULE :=false
include $(BUILD_SHARED_LIBRARY)

