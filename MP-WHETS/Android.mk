LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := mpwhetslib
LOCAL_SRC_FILES := mpwhets.c
# LOCAL_CFLAGS := -save-temps 


include $(BUILD_SHARED_LIBRARY)
