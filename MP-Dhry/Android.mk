LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := mpdhrylib
LOCAL_SRC_FILES := mpdhry.c dhry22.c 
# LOCAL_CFLAGS := -save-temps 


include $(BUILD_SHARED_LIBRARY)
