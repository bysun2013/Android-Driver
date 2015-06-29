# Copyright 2010 The Android Open Source Project
#
# not currently building V8 for x86 targets

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_SRC_FILES:= leds_hal.c
LOCAL_MODULE_TAGS := eng
LOCAL_MODULE := leds_hal.default
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

include $(BUILD_SHARED_LIBRARY)

