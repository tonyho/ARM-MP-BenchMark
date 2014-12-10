LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := mpbuslib
LOCAL_SRC_FILES := busspdmp.c
# LOCAL_CFLAGS := -save-temps


include $(BUILD_SHARED_LIBRARY)
