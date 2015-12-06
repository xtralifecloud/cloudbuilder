LOCAL_PATH := $(call my-dir)
DELIVERY_PATH := ../../../../delivery

common_CFLAGS := -D__ANDROID__ -DDEBUG -DCOTC_DISABLE_EXCEPTIONS

include $(CLEAR_VARS)

LOCAL_MODULE	:= curl
LOCAL_SRC_FILES	:= $(DELIVERY_PATH)/curl/Android/$(TARGET_ARCH_ABI)/libcurl.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE	:= libcrypto
LOCAL_SRC_FILES	:= $(DELIVERY_PATH)/openssl/Android/lib/$(TARGET_ARCH_ABI)/libcrypto.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE	:= libssl
LOCAL_SRC_FILES	:= $(DELIVERY_PATH)/openssl/Android/lib/$(TARGET_ARCH_ABI)/libssl.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE		:= CloudBuilder
LOCAL_CFLAGS 		:= $(common_CFLAGS)
LOCAL_CXXFLAGS		:= -std=c++11

CLOUDBUILDER_DIR	:= ../../..

LOCAL_C_INCLUDES	:= $(LOCAL_PATH)
LOCAL_C_INCLUDES 	+=  $(LOCAL_PATH)/../../../../delivery/curl/Headers       \
						$(LOCAL_PATH)/../../../../delivery/openssl/Android/include
LOCAL_C_INCLUDES 	+=  $(LOCAL_PATH)/$(CLOUDBUILDER_DIR)/Headers			\
						$(LOCAL_PATH)/$(CLOUDBUILDER_DIR)/sources			\
						$(LOCAL_PATH)/$(CLOUDBUILDER_DIR)/sources/Android	\
						$(LOCAL_PATH)/$(CLOUDBUILDER_DIR)/sources/cJSON		\
						$(LOCAL_PATH)/$(CLOUDBUILDER_DIR)/sources/hmac		\
						$(LOCAL_PATH)/$(CLOUDBUILDER_DIR)/sources/idea		\
						$(LOCAL_PATH)/$(CLOUDBUILDER_DIR)/sources/sdb		\
						$(LOCAL_PATH)/$(CLOUDBUILDER_DIR)/sources/tinyxml	\
						$(LOCAL_PATH)/$(CLOUDBUILDER_DIR)/sources/sqs		\
						$(LOCAL_PATH)/$(CLOUDBUILDER_DIR)/sources/tools		\
#						$(LOCAL_PATH)/$(CLOUDBUILDER_DIR)/sources/Marmalade
						
LOCAL_SRC_FILES		:= 	$(CLOUDBUILDER_DIR)/sources/CCallback.cpp				\
						$(CLOUDBUILDER_DIR)/sources/CClannishRESTproxy.cpp		\
						$(CLOUDBUILDER_DIR)/sources/CHjSON.cpp					\
						$(CLOUDBUILDER_DIR)/sources/cotc_thread.cpp				\
						$(CLOUDBUILDER_DIR)/sources/CotCHelpers.cpp				\
						$(CLOUDBUILDER_DIR)/sources/ErrorStrings.cpp			\
						$(CLOUDBUILDER_DIR)/sources/Android/CloudBuilderJNI.cpp	\
						$(CLOUDBUILDER_DIR)/sources/Android/JNIUtilities.cpp	\
						$(CLOUDBUILDER_DIR)/sources/Android/CAndroidFilesystemHandlerImpl.cpp	\
						$(CLOUDBUILDER_DIR)/sources/Android/GooglePlayStoreHandler.cpp	\
						$(CLOUDBUILDER_DIR)/sources/cJSON/cJSON.c				\
						$(CLOUDBUILDER_DIR)/sources/HighLevel/CClan.cpp				\
						$(CLOUDBUILDER_DIR)/sources/HighLevel/CFilesystem.cpp				\
						$(CLOUDBUILDER_DIR)/sources/HighLevel/CGameManager.cpp				\
						$(CLOUDBUILDER_DIR)/sources/HighLevel/CTribeManager.cpp				\
						$(CLOUDBUILDER_DIR)/sources/HighLevel/CUserManager.cpp				\
						$(CLOUDBUILDER_DIR)/sources/HighLevel/CMatchManager.cpp				\
						$(CLOUDBUILDER_DIR)/sources/HighLevel/CStoreManager.cpp				\
						$(CLOUDBUILDER_DIR)/sources/HighLevel/CIndexManager.cpp				\
						$(CLOUDBUILDER_DIR)/sources/optional/CStdioBasedFileImpl.cpp		\
						$(CLOUDBUILDER_DIR)/sources/sdb/base64.cpp				\
						$(CLOUDBUILDER_DIR)/sources/sdb/util.cpp				\
						$(CLOUDBUILDER_DIR)/sources/tools/helpers.cpp			\
						$(CLOUDBUILDER_DIR)/sources/tools/curltool.cpp			\
						$(CLOUDBUILDER_DIR)/sources/tools/ssl_bio.cpp

LOCAL_LDLIBS			:= -lm -llog
LOCAL_STATIC_LIBRARIES	:= curl ssl crypto 

include $(BUILD_SHARED_LIBRARY)

