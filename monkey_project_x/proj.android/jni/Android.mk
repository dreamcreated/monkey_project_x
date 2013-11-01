LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

MY_FILES_PATH := $(LOCAL_PATH) \
				 $(LOCAL_PATH)/../../Classes

MY_FILES_SUFFIX := %.cpp %.c %.cc

My_All_Files := $(foreach src_path, $(MY_FILES_PATH), $(shell find $(src_path) -type f))
My_All_Files := $(My_All_Files:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)
MY_SRC_LIST := $(filter $(MY_FILES_SUFFIX),$(My_All_Files))
MY_SRC_LIST := $(MY_SRC_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES := $(MY_SRC_LIST)

MONKEY_INCLUDE := $(LOCAL_PATH)/../../../monkey
MONKEY_CLIENT_INCLUDE := $(LOCAL_PATH)/../../../monkey_client/monkey_client
PROTOBUF_INCLUDE := $(LOCAL_PATH)/../../../protobuf/include
COMMON_INCLUDE := $(LOCAL_PATH)/../../../common
BOOST_INCLUDE := /cygdrive/d/workspace/boost_1_53_0

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					 $(MONKEY_INCLUDE) \
					 $(MONKEY_CLIENT_INCLUDE) \
					 $(PROTOBUF_INCLUDE) \
					 $(COMMON_INCLUDE) \
					 $(BOOST_INCLUDE)



LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)
$(call import-add-path, $(LOCAL_PATH)/../../../../cocos2d-x-2.2)
$(call import-add-path, $(LOCAL_PATH)/../../../../cocos2d-x-2.2/cocos2dx/platform/third_party/android/prebuilt)
$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
