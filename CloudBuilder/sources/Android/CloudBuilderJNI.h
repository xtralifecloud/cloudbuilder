#ifndef __CLOUDBUILDERJNI__
#define __CLOUDBUILDERJNI__

#include <jni.h>
#include <android/log.h>

extern JNIEnv *JNIGetEnv();

void RegisterDevice(void);
bool JNIIsConnected(void);

#endif	// __CLOUDBUILDERJNI__