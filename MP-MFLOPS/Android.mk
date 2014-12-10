LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := mpmflopslib
LOCAL_SRC_FILES := mpmflops.c
# LOCAL_CFLAGS := -save-temps


include $(BUILD_SHARED_LIBRARY)
