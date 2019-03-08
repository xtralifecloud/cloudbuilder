Create an Android application using Android Studio. {#getting_started_android_ref}
===========

This guide describes how to create a native application for Android, using the CloudBuilder library. We suppose that the C++ part that you will create here will serve for other platforms. Feel free to start with your existing C++ code base, but we recommend that you follow carefully how to write the Java code, manifest and build files.

In the file structure, directly on the `app` folder (module), paste the `libs` folder as supplied with the SDK archive.

In the `build.gradle` from the module `app`, ensure that you have at least the following code. This does not list the full gradle build file but a part of it. Just make sure that the relevant lines as given below are present.

~~~~
apply plugin: 'com.android.application'

android {
	[...]

	sourceSets.main {
		jniLibs.srcDir 'libs'
	}
}

repositories {
	flatDir {
		dirs 'libs'
	}
}

dependencies {
	compile fileTree(dir: 'libs', include: ['*.jar'])
	compile(name:'CloudBuilder-release', ext:'aar')
	[...]
	// If you are going to use GCM
	compile 'com.android.support:appcompat-v7:22.2.0'
	compile 'com.google.android.gms:play-services-gcm:7.5.0'
}
~~~~

Now in your main activity, you need to add the following in order to load CloudBuilder native libraries:

~~~~{.java}
// The timer will just call into C++ and ensure that incoming notifications are processed.
private class CloudBuilderUpdateTask extends TimerTask {
	@Override
	public void run() {
		cloudBuilderHandler.post(new Runnable() {
			public void run() { CloudBuilderUpdateJNIBridge(); }
		});
	}
}

static  {
	System.loadLibrary("CloudBuilder");
	System.loadLibrary("MyAppNative");
}

//	We need a timer and handler to call the CotC_Update() function regularly.
private Timer cloudBuilderTimer = null;
private Handler cloudBuilderHandler = null;

//	The 2 bridges to the 2 C++ functions we need to call.
public native void CloudBuilderSetupJNIBridge();
public native void CloudBuilderUpdateJNIBridge();
~~~~

Note: we will create the libMyAppNative a bit further in this guide.

Then in your onCreate method you need the following:

~~~~{.java}
// Init the library
CloudBuilder.Init(this);

// Disable the restriction for using Networking on main thread
// http://stackoverflow.com/questions/12529994/networking-issues-on-honeycomb-and-higher
if (android.os.Build.VERSION.SDK_INT > 9) {
	StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
	StrictMode.setThreadPolicy(policy);
}

// Setup the environment by calling into C++.
cloudBuilderHandler = new Handler();
CloudBuilderSetupJNIBridge();

// Then we immediately instantiate a timer (100ms) which will regularly
// poll to check if new notifications are pending.
cloudBuilderTimer = new Timer("CloudBuilderTimer");
cloudBuilderTimer.schedule(new CloudBuilderUpdateTask(), 0, 100);

// If you are going to use the store, you nee that as well
GooglePlayStoreHandler.InitGooglePlayStore(this);
~~~~

You also need to override a few methods in order to pass the appropriate messages to the native library. This approach may seem like a bit of work at first, but it allows to integrate seamlessly within your own activities.

~~~~{.java}
@Override
public synchronized void onPause() {
	super.onPause();
	CloudBuilder.Suspended();
}

@Override
public synchronized void onResume() {
	super.onResume();
	CloudBuilder.Resumed();
}
~~~~

Now you need to modify the manifest. Add the following permission at the very least:

~~~~{.xml}
<uses-permission android:name="android.permission.INTERNET"></uses-permission>
~~~~

Note: no, we are not kidding. While it may seem trivial, Android will prevent internet access to the CloudBuilder library in a undetectable way (basically silently failing DNS resolution) and this permission is not added automatically. Therefore, check that twice if you get errors such as CURL 6 (couldn't resolve host).

Ok so now in terms of Java and android specific setup, you are ready. Since CloudBuilder is a native library, you need to build a native wrapper in order to use it. We recommend creating a JNI project that references the CloudBuilder static libraries in the prebuilt subfolder. You should place that project under a jni folder at the same level as the app (that is, side by side to folders such as src, libs) and paste `prebuilt` and `Headers` from the CloudBuilder distribution.

Contents of Android.mk:

~~~~
LOCAL_PATH := $(call my-dir)

# Path to retrieve CloudBuilder files (headers, libraries).
CLOUDBUILDER_LIBS = ../prebuilt
CLOUDBUILDER_HEADERS = Headers

# Module to include libCloudBuilder.so
include $(CLEAR_VARS)

LOCAL_MODULE	:= CloudBuilder
LOCAL_SRC_FILES	:= $(CLOUDBUILDER_LIBS)/$(TARGET_ARCH_ABI)/libCloudBuilder.so

include $(PREBUILT_SHARED_LIBRARY)

# Module to compile the CloudBuilderSupport.cpp file, and the JNI bridge.
include $(CLEAR_VARS)

LOCAL_MODULE		:= MyAppNative
LOCAL_CFLAGS		:= -D__ANDROID__ -DDEBUG
LOCAL_CXXFLAGS		:= -std=c++11
LOCAL_SRC_FILES		:= MyAppNative.cpp
LOCAL_C_INCLUDES	:= $(CLOUDBUILDER_HEADERS)
 
LOCAL_LDLIBS			:= -llog
LOCAL_SHARED_LIBRARIES	:= CloudBuilder

include $(BUILD_SHARED_LIBRARY)
~~~~

Contents of Application.mk

~~~~
APP_ABI         := armeabi armeabi-v7a x86 x86_64 arm64-v8a
APP_PLATFORM	:= android-14
APP_STL			:= stlport_static
APP_CPPFLAGS	:= -std=c++11
~~~~

Sample contents of MyAppNative.cpp:

~~~~{.cpp}
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
		CUserManager::Instance()->LoginAnonymous(MakeResultHandler(this, &MyAppNative::loginDone));
	}

	void loginDone(eErrorCode code, const CCloudResult *result) {
		cstring text(result->GetJSONString(), true);
		OUTPUT("Result of login: %d, %s\n", code, text.c_str());
	}

public:
	MyAppNative() {}

	void setup() {
		CHJSON params;
		params.Put("key", "testgame-key");
		params.Put("secret", "testgame-secret");
		params.Put("env", "sandbox");
		CClan::Instance()->SetLogLevel(LOG_LEVEL_VERBOSE);
		CClan::Instance()->Setup(&params, MakeResultHandler(this, &MyAppNative::setupDone));
	}
};

static owned_ref<MyAppNative> g_myApp;

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	return JNI_VERSION_1_6;
}

extern "C" void Java_com_clanofthecloud_cli_MainActivity_CloudBuilderSetupJNIBridge(JNIEnv* env, jobject thiz) {
	OUTPUT("Native CloudBuilderSetupJNIBridge");

	// Your initialization code here
	g_myApp <<= new MyAppNative;
	g_myApp->setup();
}

extern "C" void Java_com_clanofthecloud_cli_MainActivity_CloudBuilderUpdateJNIBridge(JNIEnv* env, jobject thiz) {
	// Process this periodically
	if (g_myApp) {
		CClan::Instance()->ProcessIdleTasks();
	}
}
~~~~

Note: you could place the CloudBuilder header and prebuilt files anywhere you like. In our example we have put them under the JNI directory.

Then you can compile the project using ndk-build from the `app` directory. This will output the libs under `app/libs` (architecture/libMyAppNative.so), which can be used in your project. Do not reference the libs from the `prebuilt` folder: it is only used for compiling the shared library (libMyAppNative.so) and will be copied by the tool once build finishes.

Then you can use them from the Java code.
