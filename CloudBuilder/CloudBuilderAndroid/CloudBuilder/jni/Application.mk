# The ARMv7 is significanly faster due to the use of the hardware FPU
APP_PLATFORM := android-25
APP_ABI         := armeabi armeabi-v7a x86 x86_64 arm64-v8a

APP_STL := gnustl_static
APP_CPPFLAGS += -frtti

#APP_OPTIM		:= debug
APP_OPTIM		:= release