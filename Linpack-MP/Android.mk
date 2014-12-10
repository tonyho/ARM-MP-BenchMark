LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := linpackmplib
 ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_CFLAGS : += -DHAVE_NEON=1 
    LOCAL_SRC_FILES = linpackmp.c.neon
 endif

 LOCAL_STATIC_LIBRARIES := cpufeatures

 include $(BUILD_SHARED_LIBRARY)
 $(call import-module,cpufeatures)
 