LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
# 这里填写要编译的源文件路径，这里只列举了一部分
LOCAL_SRC_FILES := linux_run_on_android.cc
# 默认包含的头文件路径
LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/..
# -g 后面的一系列附加项目添加了才能使用 arm_neon.h 头文件
# -mfloat-abi=softfp -mfpu=neon 使用 arm_neon.h 必须
LOCAL_CFLAGS := -D__cpusplus -g -mfloat-abi=softfp -mfpu=neon -march=armv7-a -mtune=cortex-a8
LOCAL_LDLIBS := -lz -llog
TARGET_ARCH_ABI :=armeabi-v7a
LOCAL_ARM_MODE := arm
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
# 采用NEON优化技术
LOCAL_ARM_NEON := true
endif
LOCAL_MODULE := linux_run_on_android
# 生成动态调用库
include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_EXECUTABLE)
