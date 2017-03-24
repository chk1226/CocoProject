LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

FILE_LIST_CLASS := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
FILE_LIST_GAME := $(wildcard $(LOCAL_PATH)/../../Classes/Game/*.cpp)
FILE_LIST_FRAMEWORK := $(wildcard $(LOCAL_PATH)/../../Classes/Framework/*.cpp)
FILE_LIST_TMXLOADER := $(wildcard $(LOCAL_PATH)/../../Classes/Framework/TMXLoader/*.cpp)

LOCAL_SRC_FILES := hellocpp/main.cpp 
LOCAL_SRC_FILES += $(FILE_LIST_CLASS:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST_GAME:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST_FRAMEWORK:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST_TMXLOADER:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
