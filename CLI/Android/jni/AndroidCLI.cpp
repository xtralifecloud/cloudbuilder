#include <jni.h>

#ifdef __ANDROID__
#include <android/log.h>
#define OUTPUT(...) __android_log_print(ANDROID_LOG_VERBOSE, "AndroidCLI", __VA_ARGS__)
#else
#include <stdio.h>
#define OUTPUT(...) printf (__VA_ARGS__)
#endif

#include "../../../CloudBuilder/tests/cli.h"

static JavaVM*		sJavaVM = NULL;

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	sJavaVM	= vm;
	return JNI_VERSION_1_6;
}

void sendMessage(const char *message)
{
	JNIEnv*		currentJNIEnv;
	jclass		cliClass;
	jmethodID	messageMethod;

//	OUTPUT ("try send %s", message);

	sJavaVM->GetEnv(reinterpret_cast<void**>(&currentJNIEnv), JNI_VERSION_1_6);

	if (!currentJNIEnv) {
		OUTPUT("Logging in an invalid Java Environment! %s", message);
		return;
	}
	jstring jstr = currentJNIEnv->NewStringUTF(message);

	cliClass	= currentJNIEnv->FindClass("com/clanofthecloud/cli/MicroConsole");
//	OUTPUT("class  = %ld", cliClass);
	messageMethod	= currentJNIEnv->GetStaticMethodID(cliClass, "WriteMessage", "(Ljava/lang/String;)V");
//	OUTPUT("method  = %ld", messageMethod);
	currentJNIEnv->CallStaticVoidMethod(cliClass, messageMethod, jstr);

}

void stopWait(const char *message)
{
	JNIEnv*		currentJNIEnv;
	jclass		cliClass;
	jmethodID	messageMethod;

//	OUTPUT ("try send %s", message);

	sJavaVM->GetEnv(reinterpret_cast<void**>(&currentJNIEnv), JNI_VERSION_1_6);

	jstring jstr = currentJNIEnv->NewStringUTF(message);

	cliClass	= currentJNIEnv->FindClass("com/clanofthecloud/cli/MicroConsole");
//	OUTPUT("class  = %ld", cliClass);
	messageMethod	= currentJNIEnv->GetStaticMethodID(cliClass, "StopWait", "(Ljava/lang/String;)V");
//	OUTPUT("method  = %ld", messageMethod);
	currentJNIEnv->CallStaticVoidMethod(cliClass, messageMethod, jstr);

}


class androidCLI : public CLI {
public:
	androidCLI() : CLI() {}
	~androidCLI() {}
	virtual void stopActivity(eErrorCode ec);
	virtual void logger(const char *message, typelog=kLOG);
};

void androidCLI::stopActivity(eErrorCode ec)
{
	OUTPUT("stopActivity get %d", ec);
	if (ec == 0)
		sendMessage("Done.");
	else
	{
		sendMessage(errorString(ec));
	}
	stopWait("");
}

void androidCLI::logger(const char *message, typelog)
{
//	OUTPUT("-- %s", message);
	sendMessage(message);
}



androidCLI *myCLI = NULL;

extern "C" void Java_com_clanofthecloud_cli_MicroConsole_CloudBuilderSetupJNIBridge(JNIEnv* env, jobject thiz)
{
	OUTPUT("Setup CloudBuilder");
	myCLI = new androidCLI();
	if (myCLI==NULL)
		OUTPUT("ERROR at androidCLI create");
	else
		OUTPUT("androidCLI created");

}

extern "C" jint Java_com_clanofthecloud_cli_MicroConsole_CLIExecute(JNIEnv* env, jobject thiz, jobject command)
{
	jstring		commandString;
	jboolean	isCopy;
	const char* cmd;

	commandString = (jstring) command;
	cmd	= env->GetStringUTFChars(commandString, &isCopy);

	OUTPUT("exec cmd : %s", cmd);

	eErrorCode ec =  myCLI->execute(cmd);

	OUTPUT("cmd return : %d", ec);


	env->ReleaseStringUTFChars(commandString, cmd);

	return (int) ec;

}

extern "C" void Java_com_clanofthecloud_cli_MicroConsole_CloudBuilderUpdateJNIBridge(JNIEnv* env, jobject thiz)
{
	if (myCLI)
	{
//		OUTPUT("popNextCallback");
		CClan::Instance()->ProcessIdleTasks();
	}
}
