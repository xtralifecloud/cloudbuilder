//
//  JNIUtilities.h
//  CloudBuilder
//
//  Created by Florian Br�nnimann on 08/09/14.
//  Copyright (c) 2014 Clan of the Cloud. All rights reserved.
//
//  Put here various utilities for JNI.

#pragma once

class JavaString {
	JNIEnv *env;
	jstring jString;
	const char *cString;
public:
	JavaString(JNIEnv *env, jstring jString) : env(env), jString(jString) {
		if (jString) {
			jboolean unusedIsCopy;
			cString = env->GetStringUTFChars(jString, &unusedIsCopy);
		} else {
			cString = NULL;
		}
	}
	~JavaString() {
		if (cString) {
			env->ReleaseStringUTFChars(jString, cString);
		}
	}
	operator const char *() { return cString; }
	const char *c_str() { return cString; }
};

extern CotCHelpers::CHJSON *BuildJsonFromHashMap(JNIEnv *env, jobject jHashMap);
extern void JNIInvokeJavaHandler(int handlerId, CloudBuilder::eErrorCode errorCode, const CotCHelpers::CHJSON *json);

