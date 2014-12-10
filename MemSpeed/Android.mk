LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := memspeedlib
LOCAL_SRC_FILES := memspeed.c
# LOCAL_CFLAGS := -save-temps
# LOCAL_CFLAGS := -DFPM_ARM -O3 -mcpu=cortex-a8  -mfpu=neon -ftree-vectorize -save-temps

include $(BUILD_SHARED_LIBRARY)
