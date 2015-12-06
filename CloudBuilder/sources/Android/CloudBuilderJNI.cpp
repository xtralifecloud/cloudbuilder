#include "CloudBuilderJNI.h"
#include "CClan.h"
#include "CloudBuilder_private.h"
#include "CUserManager.h"
#include "CHJSON.h"
#include "JNIUtilities.h"
#include "CCallback.h"
#include "GameCenterHandler.h"

#ifdef __MARMALADE_BUILD__
#include "s3eEdk.h"
#include "s3eEdk_android.h"
#endif

using namespace CloudBuilder;
using namespace CotCHelpers;

#pragma mark - Java native function prototypes

extern "C" JNIEXPORT jint JNICALL Java_com_clanofthecloud_cloudbuilder_CloudBuilder_RegisterDevice(JNIEnv * aEnv, jclass aClass, jstring aToken);
extern "C" JNIEXPORT jint JNICALL Java_com_clanofthecloud_cloudbuilder_CloudBuilder_UnregisterDevice(JNIEnv * aEnv, jclass aClass, jstring aToken);

extern "C" JNIEXPORT jint JNICALL Java_com_clanofthecloud_cloudbuilder_CloudBuilder_HandleRemoteNotification(JNIEnv * aEnv, jclass aClass, jobject aMessage);

extern "C" JNIEXPORT jint JNICALL Java_com_clanofthecloud_cloudbuilder_CloudBuilder_Suspended(JNIEnv* aEnv, jclass aClass);
extern "C" JNIEXPORT jint JNICALL Java_com_clanofthecloud_cloudbuilder_CloudBuilder_Resumed(JNIEnv* aEnv, jclass aClass);


JavaVM *sJavaVM = NULL;

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	sJavaVM	= vm;
	__android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "Launching CloudBuilder C++ v%s", SDKVERSION);
	
	return JNI_VERSION_1_6;
}

JNIEnv *JNIGetEnv() {
	JNIEnv *env = NULL;
#ifdef __MARMALADE_BUILD__
	env = s3eEdkJNIGetEnv();
	__android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "JNIEnv is: %p", env);
#else
	if (sJavaVM->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
		__android_log_print(ANDROID_LOG_ERROR, "CloudBuilder C++", "Couldn't even retrieve JNIEnv");
	}
#endif
	return env;
}

/*void JNIFetchMethod(JNIEnv* &env, jclass &clazz, jmethod &method,
					const char *className, const char *methodName, const char *methodSignature,
					CInternalResultHandler *calledOnError) {
	if (!env) { env = JNIGetEnv(); }
	if (!env) { return InvokeHandler(calledOnError, enInternalError, "JNI: No environment set up"); }

	clazz = currentJNIEnv->FindClass(className);
	if (!clazz) { return InvokeHandler(calledOnError, enInternalError, csprintf("JNI: %s class not found", className)); }

	method	= currentJNIEnv->GetStaticMethodID(cloudBuilderClass, methodName, methodSignature);
	if (!method) { return InvokeHandler(calledOnError, enInternalError, csprintf("JNI: %s.%s not found", className, methodName)); }
}*/

#pragma mark - Java native functions implementation

extern "C" JNIEXPORT jint JNICALL Java_com_clanofthecloud_cloudbuilder_CloudBuilder_InvokeHandler(JNIEnv* aEnv, jclass aClass, jlong handlerId, jstring jsonStr) {
	CInternalResultHandler *handler = (CInternalResultHandler*) handlerId;
	// Make a CCloudResult out of the JSON string
	JavaString jsonCstr(aEnv, jsonStr);
	CCloudResult result (CHJSON::parse(jsonCstr));
	InvokeHandler(handler, &result);
	return 0;
}


namespace CloudBuilder
{
void AchieveRegisterDevice(unsigned long len, const void *bytes)
{
	CUserManager::Instance()->RegisterDevice("android", (const char*) bytes);
}
}

void RegisterDevice(void)
{
    JNIEnv*		currentJNIEnv;
    jclass		cloudBuilderClass;
    jmethodID	queryRegisterDevice;
    jthrowable	exc;
    
    __android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "Calling Java QueryRegisterDevice");
    
#ifdef __MARMALADE_BUILD__
    currentJNIEnv = s3eEdkJNIGetEnv();
    __android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "JNIEnv is: %p", currentJNIEnv);
#else
    __android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "Using JavaVM: %p", sJavaVM);
    
    if (sJavaVM->GetEnv(reinterpret_cast<void**>(&currentJNIEnv), JNI_VERSION_1_6) != JNI_OK)
    {
        __android_log_print(ANDROID_LOG_ERROR, "CloudBuilder C++", "Couldn't even retrieve JNIEnv");
        return;
    }
#endif
    
    cloudBuilderClass	= currentJNIEnv->FindClass("com/clanofthecloud/cloudbuilder/CloudBuilder");
    exc = currentJNIEnv->ExceptionOccurred();
    if(exc)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "No notification module available");
        currentJNIEnv->ExceptionClear();
        
        return;
    }
    
    __android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "CloudBuilderClass is:%p", cloudBuilderClass);
    if(cloudBuilderClass)
    {
        queryRegisterDevice	= currentJNIEnv->GetStaticMethodID(cloudBuilderClass, "QueryRegisterDevice", "()V");
        __android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "QueryRegisterDevice is:%p", queryRegisterDevice);
        
        currentJNIEnv->CallStaticVoidMethod(cloudBuilderClass, queryRegisterDevice);
    }
}

void UnregisterDevice(void)
{
    JNIEnv*		currentJNIEnv;
    jclass		cloudBuilderClass;
    jmethodID	unregisterDevice;
    jthrowable	exc;
    
    __android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "Calling Java UnregisterDevice");
    
#ifdef __MARMALADE_BUILD__
    currentJNIEnv = s3eEdkJNIGetEnv();
    __android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "JNIEnv is: %p", currentJNIEnv);
#else
    if (sJavaVM->GetEnv(reinterpret_cast<void**>(&currentJNIEnv), JNI_VERSION_1_6) != JNI_OK)
    {
        __android_log_print(ANDROID_LOG_ERROR, "CloudBuilder C++", "Couldn't even retrieve JNIEnv");
        return;
    }
#endif
    
    cloudBuilderClass	= currentJNIEnv->FindClass("com/clanofthecloud/cloudbuilder/CloudBuilder");
    exc = currentJNIEnv->ExceptionOccurred();
    if(exc)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "No notification module available");
        currentJNIEnv->ExceptionClear();
        
        return;
    }
    
    __android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "CloudBuilderClass is:%p", cloudBuilderClass);
    if(cloudBuilderClass)
    {
        unregisterDevice	= currentJNIEnv->GetStaticMethodID(cloudBuilderClass, "UnregisterDevice", "()V");
        __android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "UnregisterDevice is:%p", unregisterDevice);
        
        currentJNIEnv->CallStaticVoidMethod(cloudBuilderClass, unregisterDevice);
    }
}

CotCHelpers::CHJSON *collectDeviceInformation() {

	JNIEnv*		currentJNIEnv;
	jclass		cloudBuilderClass;
	jmethodID	collect;
	
	__android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "Calling Java CollectDeviceInformation");
	
#ifdef __MARMALADE_BUILD__
	currentJNIEnv = s3eEdkJNIGetEnv();
	__android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "JNIEnv is: %p", currentJNIEnv);
#else
	if (sJavaVM->GetEnv(reinterpret_cast<void**>(&currentJNIEnv), JNI_VERSION_1_6) != JNI_OK)
	{
		__android_log_print(ANDROID_LOG_ERROR, "CloudBuilder C++", "Couldn't even retrieve JNIEnv");
	}
#endif
	
	cloudBuilderClass	= currentJNIEnv->FindClass("com/clanofthecloud/cloudbuilder/CloudBuilder");
	__android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "CloudBuilder is:%p", cloudBuilderClass);
	collect = currentJNIEnv->GetStaticMethodID(cloudBuilderClass, "CollectDeviceInformation", "()Ljava/lang/String;");
	__android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "CollectDeviceInformation is:%p", collect);
	jstring info = (jstring) currentJNIEnv->CallStaticObjectMethod(cloudBuilderClass, collect);

	CotCHelpers::CHJSON *j = CHJSON::parse(JavaString(currentJNIEnv, info));
	__android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "CollectDeviceInformation: %s", j->printFormatted().c_str());

	return j;
}


JNIEXPORT jint JNICALL Java_com_clanofthecloud_cloudbuilder_CloudBuilder_RegisterDevice(JNIEnv* aEnv, jclass aClass, jstring aToken)
{
	JavaString	token(aEnv, aToken);

	AchieveRegisterDevice(strlen(token), token.c_str());
	__android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "Registered device:android with token:%s", token.c_str());

	return enNoErr;
}

JNIEXPORT jint JNICALL Java_com_clanofthecloud_cloudbuilder_CloudBuilder_HandleRemoteNotification(JNIEnv* aEnv, jclass aClass, jobject aMessage) {
	return enNotImplemented;
}

JNIEXPORT jint JNICALL Java_com_clanofthecloud_cloudbuilder_CloudBuilder_Suspended(JNIEnv* aEnv, jclass aClass)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "Suspended");

	if (CClan::Instance())
		CClan::Instance()->Suspend();

	return 0;
}

JNIEXPORT jint JNICALL Java_com_clanofthecloud_cloudbuilder_CloudBuilder_Resumed(JNIEnv* aEnv, jclass aClass)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "CloudBuilder C++", "Resumed");
	
	if (CClan::Instance())
		CClan::Instance()->Resume();

	return 0;
}

// GameCenterHandler.mm - dummy implementations
void CloudBuilder::GameCenter::login(CInternalResultHandler *handler) { InvokeHandler(handler, enNotImplemented); }
void CloudBuilder::GameCenter::logout(CInternalResultHandler *handler) { InvokeHandler(handler, enNotImplemented); }
void CloudBuilder::GameCenter::listFriends(CInternalResultHandler *handler) { InvokeHandler(handler, enNotImplemented); }
