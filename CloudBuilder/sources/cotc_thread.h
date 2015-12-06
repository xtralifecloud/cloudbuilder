//
//  cotc_thread.h
//  CloudBuilder
//
//  Created by Roland Van Leeuwen on 23/09/11.
//  Copyright 2011 Clan of the Cloud. All rights reserved.
//

#ifndef CloudBuilder_cotc_thread_h
#define CloudBuilder_cotc_thread_h

#include "cloudbuilder.h"
#include "CotCHelpers.h"
#include "CCallback.h"

#if defined(__WINDOWS_32__) || defined(__WP8__)
	extern int usleep(long usec);
	/** WP8-way
		#include <thread>
		#include <chrono>

		#define usleep(x)	 {std::chrono::milliseconds dura((x/1000) ? (x/1000) : 1);std::this_thread::sleep_for(dura);}
	*/
#else
#	include <unistd.h>
#endif

class CotThunkThread;

namespace CloudBuilder {

	// Emulation for the old CotCThread model
	class CotCThread {
		CotCHelpers::CMutex mMutex;
		class CotThunkThread *thread;

	public:
		CotCThread(void *(*func) (void*), void *arg);
		virtual ~CotCThread(void);

		void Start(void);
		void Lock(void);
		void Unlock(void);

		void *Join(void);
	};
}

#endif
