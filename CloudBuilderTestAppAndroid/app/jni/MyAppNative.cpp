#include <jni.h>
#include <android/log.h>

#include "CClan.h"
#include "CUserManager.h"

using namespace CloudBuilder;
using namespace CotCHelpers;

#define OUTPUT(...) __android_log_print(ANDROID_LOG_VERBOSE, "MyAppNative", __VA_ARGS__)

class MyAppNative {

	void setupDone(eErrorCode code, const CCloudResult *result) {
		cstring text(result->GetJSONString(), true);
		OUTPUT("Result of setup: %d, %s\n", code, text.c_str());

		// Now we can log in anonymously
		CClan::Instance()->SetLogLevel(LOG_LEVEL_VERBOSE);
	}

	void loginDone(eErrorCode code, const CCloudResult *result) {
		cstring text(result->GetJSONString(), true);
		OUTPUT("Result of login: %d, %s\n", code, text.c_str());
	}

	void logoutDone(eErrorCode code, const CCloudResult *result) {
		cstring text(result->GetJSONString(), true);
		OUTPUT("Result of logout: %d, %s\n", code, text.c_str());
	}

public:
	MyAppNative() {}

	void setup() {
		CHJSON params;
		params.Put("key", "cloudbuilder-key");
		params.Put("secret", "azerty");
		params.Put("env", "sandbox");
		params.Put("httpVerbose", true);
		CClan::Instance()->Setup(&params, MakeResultHandler(this, &MyAppNative::setupDone));
	}

	void login() {
		CHJSON params;
		params.Put("network", "email");
		params.Put("id", "testuser@localhost.localdomain");
		params.Put("secret", "pass1234");
		CUserManager::Instance()->LoginNetwork(&params, MakeResultHandler(this, &MyAppNative::loginDone));
	}

	void logout() {
		CUserManager::Instance()->Logout(MakeResultHandler(this, &MyAppNative::logoutDone));
	}
};

static owned_ref<MyAppNative> g_myApp;

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	return JNI_VERSION_1_6;
}

extern "C" void Java_com_clanofthecloud_cloudbuildertestapp2_MainActivity_CloudBuilderSetupJNIBridge(JNIEnv* env, jobject thiz) {
	OUTPUT("Native CloudBuilderSetupJNIBridge");

	// Your initialization code here
	g_myApp <<= new MyAppNative;
	g_myApp->setup();
}

extern "C" void Java_com_clanofthecloud_cloudbuildertestapp2_MainActivity_DoLoginNatively(JNIEnv* env, jobject thiz) {
	g_myApp->login();
}

extern "C" void Java_com_clanofthecloud_cloudbuildertestapp2_MainActivity_DoLogoutNatively(JNIEnv* env, jobject thiz) {
	g_myApp->logout();
}

extern "C" void Java_com_clanofthecloud_cloudbuildertestapp2_MainActivity_CloudBuilderUpdateJNIBridge(JNIEnv* env, jobject thiz) {
	// Process this periodically
	if (g_myApp) {
		CClan::Instance()->ProcessIdleTasks();
	}
}
