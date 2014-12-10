LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := mprandlib
LOCAL_SRC_FILES := mprandmem.c
# LOCAL_CFLAGS := -save-temps


include $(BUILD_SHARED_LIBRARY)
