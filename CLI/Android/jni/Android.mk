LOCAL_PATH := $(call my-dir)

#	Path to retrieve CloudBuilder files (headers, libraries).
CLOUDBUILDER_PATH	= ../../../delivery/CloudBuilder

#	Module to include libCloudBuilder.so from the delivery folder.
include $(CLEAR_VARS)

LOCAL_MODULE	:= CloudBuilder
LOCAL_SRC_FILES	:= $(CLOUDBUILDER_PATH)/Android/prebuilt/$(TARGET_ARCH_ABI)/libCloudBuilder.so

include $(PREBUILT_SHARED_LIBRARY)

#	Module to compile the CloudBuilderSupport.cpp file, and the JNI bridge.
include $(CLEAR_VARS)

LOCAL_MODULE		:= AndroidCLI
LOCAL_CFLAGS		:= -D__ANDROID__ -DDEBUG
LOCAL_CXXFLAGS		:= -std=c++0x
LOCAL_SRC_FILES		:= AndroidCLI.cpp ../../../CloudBuilder/tests/cli.cpp
LOCAL_C_INCLUDES	:= .. ../../../delivery/CloudBuilder/Headers ../../../CloudBuilder/tests
 
LOCAL_LDLIBS			:= -llog
LOCAL_SHARED_LIBRARIES	:= CloudBuilder

include $(BUILD_SHARED_LIBRARY)

