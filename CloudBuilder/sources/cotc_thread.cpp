//
//  cotc_thread.cpp
//  CloudBuilder
//
//  Created by Roland Van Leeuwen on 23/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "cotc_thread.h"
#include "CloudBuilder_private.h"
#include <pthread.h>
#include <time.h>

using namespace CotCHelpers;

// On Windows some defines are missing
#ifdef WIN32
#include <sys/timeb.h>
struct timeval {
	long tv_sec, tv_usec;		// seconds/microseconds
};

int gettimeofday (struct timeval *tp, void *tz) {
	struct _timeb timebuffer;
	_ftime(&timebuffer);
	tp->tv_sec = (long) timebuffer.time;
	tp->tv_usec = timebuffer.millitm * 1000;
	return 0;
}
#else
#include <sys/time.h>
#endif

//////////////////////////// OS-specific vars for the classes //////////////////////////////////////////////
struct CotCHelpers::CMutexVars {
	pthread_mutex_t mutex;
};
struct CotCHelpers::CConditionVariableVars {
	pthread_cond_t cond;
};
struct CotCHelpers::CThreadVars {
	pthread_t runningThread;
};

//////////////////////////// Mutex //////////////////////////////////////////////
CMutex::CMutex() {
	mVars = new CMutexVars;
	pthread_mutex_init(&mVars->mutex, NULL);
}

CMutex::~CMutex() {
	pthread_mutex_destroy(&mVars->mutex);
	delete mVars;
}

void CMutex::Lock() {
	pthread_mutex_lock(&mVars->mutex);
}

void CMutex::Unlock() {
	pthread_mutex_unlock(&mVars->mutex);
}

//////////////////////////// Thread //////////////////////////////////////////////
CThread::CThread() : mState(READY) {
	mVars = new CThreadVars;
}

CThread::~CThread() {
	if (mState != READY) {
		pthread_detach(mVars->runningThread);
	}
	delete mVars;
}

bool CThread::Start() {
	// Do not allow to start it twice
	if (mState != READY) {
		return false;
	}

	// Start the thread
	int rc = pthread_create(&mVars->runningThread, NULL, startupRoutine, (void*) this);
	if (rc == 0) {
		mState = RUNNING;
		this->Retain();
	}
	return rc == 0;
}

bool CThread::Join() {
	if (mState != RUNNING) {
		return false;
	}

	void *unusedThExitCode;
	int rc = pthread_join(mVars->runningThread, &unusedThExitCode);
	return rc == 0;
}

void CThread::RunForInternalUse() {
	Run();
	mState = COMPLETED;
	this->Release();
}

void *CThread::startupRoutine(void *class_cotcThread) {
	CThread *ptr = (CThread*) class_cotcThread;
	ptr->RunForInternalUse();
	return NULL;
}

//////////////////////////// Condition variable //////////////////////////////////////////////
CConditionVariable::CConditionVariable() {
	mVars = new CConditionVariableVars;
	pthread_cond_init(&mVars->cond, NULL);
}

CConditionVariable::~CConditionVariable() {
	pthread_cond_destroy(&mVars->cond);
	delete mVars;
}

void CConditionVariable::LockVar() {
	mMutex.Lock();
}

void CConditionVariable::UnlockVar() {
	mMutex.Unlock();
}

void CConditionVariable::SignalAll() {
	pthread_cond_broadcast(&mVars->cond);
}

void CConditionVariable::SignalOne() {
	pthread_cond_signal(&mVars->cond);
}

bool CConditionVariable::Wait(int timeoutMilliseconds) {
	if (timeoutMilliseconds == 0) {
		return pthread_cond_wait(&mVars->cond, &mMutex.mVars->mutex) == 0;
	} else {
		timeval tv;
		timespec ts;
		gettimeofday(&tv, NULL);
		ts.tv_sec = time(NULL) + timeoutMilliseconds / 1000;
		ts.tv_nsec = tv.tv_usec * 1000 + 1000 * 1000 * (timeoutMilliseconds % 1000);
		ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
		ts.tv_nsec %= (1000 * 1000 * 1000);
		return pthread_cond_timedwait(&mVars->cond, &mMutex.mVars->mutex, &ts) == 0;
	}
}

//////////////////////////// Emulation for old CotCThread model //////////////////////////////////////////////
class CotThunkThread : public CThread {
	struct cotc_actual_call {
		void* (*func)(void *);
		void *arg;
	};

	cotc_actual_call mCall;
	void *mResult;

public:
	CotThunkThread(void *(*func) (void*), void *arg) {
		mCall.func = func;
		mCall.arg = arg;
		mResult = NULL;
	}

	virtual void Run() {
		void *(*func)(void *) = mCall.func;
		void *real_arg = mCall.arg;
		mResult = (*func)(real_arg);
	}

	void *getResult() { return mResult; }
};

CloudBuilder::CotCThread::CotCThread(void *(*func) (void*), void *arg)
{
	thread = new CotThunkThread(func, arg);
}

void CloudBuilder::CotCThread::Start(void)
{
	thread->Start();
}

void CloudBuilder::CotCThread::Lock(void)
{
	mMutex.Lock();
}

void CloudBuilder::CotCThread::Unlock(void)
{
	mMutex.Unlock();
}

void* CloudBuilder::CotCThread::Join(void)
{
	thread->Join();
	return thread->getResult();
}

CloudBuilder::CotCThread::~CotCThread(void) {
	thread->Release();
}
