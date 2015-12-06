#include "optional/CStdioBasedFileImpl.h"
#include "helpers.h"
#include "CloudBuilder_private.h"
#include <jni.h>
#include "JNIUtilities.h"

using namespace CloudBuilder;

extern char *CFilesystem_appFolder;
extern JavaVM *sJavaVM;

JNIEnv *getEnv() {
	JNIEnv *env;
	if (sJavaVM->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
		CONSOLE_ERROR("Couldn't retrieve JNIEnv.");
		return NULL;
	}
	return env;
}

static void buildFullPath(char *destPath, size_t bufSize, const char *relativePath) {
	// Fetch default directory
	char directoryOnly[1024];
	JNIEnv *env = getEnv();
	if (!env) { return; }

	jclass cloudBuilderClass = env->FindClass("com/clanofthecloud/cloudbuilder/CloudBuilder");
	jmethodID method = env->GetStaticMethodID(cloudBuilderClass, "GetDataDirectory", "()Ljava/lang/String;");
	jstring rv = (jstring) env->CallStaticObjectMethod(cloudBuilderClass, method, 0);
	JavaString appDataPath (env, rv);

	safe::sprintf(destPath, bufSize, "%s/%s/%s", appDataPath.c_str(), CFilesystem_appFolder, relativePath);

	// Extract the path
	safe::strcpy(directoryOnly, destPath);
	for (char *ptr = directoryOnly + strlen(directoryOnly) - 1; ptr >= directoryOnly; ptr--) {
		if (*ptr == '/') {
			*ptr = '\0';
			break;
		}
	}

	// For further reference, string memory is to be managed by us (directoryOnly in that case)
	jstring path = env->NewStringUTF(directoryOnly);
	method = env->GetStaticMethodID(cloudBuilderClass, "CreateDirectory", "(Ljava/lang/String;)Z");
	env->CallStaticBooleanMethod(cloudBuilderClass, method, path);
}

bool CFilesystemHandler::Delete(const char *relativePath) {
	char fullPath[1024];
	JNIEnv *env = getEnv();
	if (!env) { return false; }

	buildFullPath(fullPath, sizeof(fullPath), relativePath);

	// Use JNI to delete the actual folder
	jclass cloudBuilderClass = env->FindClass("com/clanofthecloud/cloudbuilder/CloudBuilder");
	jstring path = env->NewStringUTF(fullPath);
	jmethodID method = env->GetStaticMethodID(cloudBuilderClass, "DeleteFile", "(Ljava/lang/String;)Z");
	if (env->CallStaticBooleanMethod(cloudBuilderClass, method, path) == 0) {
		CONSOLE_ERROR("Could not delete file %s\n", fullPath);
		return false;
	}
	return true;
}

CInputFile *CFilesystemHandler::OpenForReading(const char *relativePath) {
	char fullPath[1024];
	buildFullPath(fullPath, sizeof(fullPath), relativePath);
	return new CInputFileStdio(fullPath);
}

COutputFile *CFilesystemHandler::OpenForWriting(const char *relativePath) {
	char fullPath[1024];
	buildFullPath(fullPath, sizeof(fullPath), relativePath);
	CONSOLE_VERBOSE("Writing to %s\n", fullPath);
	return new COutputFileStdio(fullPath);
}
