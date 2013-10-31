LOCAL_PATH := $(call my-dir)
LOCAL_PATH := $(LOCAL_PATH)/../
NDK_PROJECT_PATH := LOCAL_PATH

include $(CLEAR_VARS)

LOCAL_MODULE := monkey

LOCAL_MODULE_FILENAME := libmonkey

MY_FILES_PATH := $(LOCAL_PATH)

MY_FILES_SUFFIX := %.cpp %.c %.cc

My_All_Files := $(foreach src_path, $(MY_FILES_PATH), $(shell find $(src_path) -type f))
My_All_Files := $(My_All_Files:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)
MY_SRC_LIST := $(filter $(MY_FILES_SUFFIX),$(My_All_Files))
MY_SRC_LIST := $(MY_SRC_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES := $(MY_SRC_LIST)


LOCAL_C_INCLUDES := /cygdrive/d/workspace/boost_1_53_0 \
					$(LOCAL_PATH)/../../protobuf/include

include $(BUILD_STATIC_LIBRARY)
