LOCAL_PATH := $(call my-dir)

#	Path to retrieve CloudBuilder files (headers, libraries).
CLOUDBUILDER_LIBS = ../prebuilt
CLOUDBUILDER_HEADERS = Headers

# Module to include libCloudBuilder.so
include $(CLEAR_VARS)

LOCAL_MODULE	:= CloudBuilder
LOCAL_SRC_FILES	:= $(CLOUDBUILDER_LIBS)/$(TARGET_ARCH_ABI)/libCloudBuilder.so

include $(PREBUILT_SHARED_LIBRARY)

#	Module to compile the CloudBuilderSupport.cpp file, and the JNI bridge.
include $(CLEAR_VARS)

LOCAL_MODULE		:= MyAppNative
LOCAL_CFLAGS		:= -D__ANDROID__ -DDEBUG
LOCAL_CXXFLAGS		:= -std=c++11
LOCAL_SRC_FILES		:= MyAppNative.cpp
LOCAL_C_INCLUDES	:= $(CLOUDBUILDER_HEADERS)
 
LOCAL_LDLIBS			:= -llog
LOCAL_SHARED_LIBRARIES	:= CloudBuilder

include $(BUILD_SHARED_LIBRARY)
