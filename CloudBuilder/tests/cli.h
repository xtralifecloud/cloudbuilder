//
//  cli.h
//  CloudBuilderMacOSX
//
//  Created by roland on 03/05/13.
//
//

#ifndef __CloudBuilderMacOSX__cli__
#define __CloudBuilderMacOSX__cli__

class CLI;
class MyClan;

#include "CClan.h"
#include "CHJSON.h"
#include "CloudBuilder.h"
#include "CIndexManager.h"
#include "CUserManager.h"
#include "CTribeManager.h"
#include "CGameManager.h"
#include "CMatchManager.h"
#include "CStoreManager.h"
#include <time.h>

using namespace CloudBuilder;
using namespace CotCHelpers;

template <class T> class Singleton {
	T& operator= (const T&);
protected:
	static T mInstance;
public:
	static T *Instance();
};

class CLI {
	public:
		CLI();
		virtual ~CLI();
		
		void HandleURL(const CHJSON *config);
	
		eErrorCode execute(const char *li);
		long millisecondsElapsedSinceLastExecute();
		enum typelog {
			kLOG= 0,
			kCMD,
			kERR,
			kSCRIPT
		};
		virtual void logger(const char *message, typelog=kLOG);
		virtual void stopActivity(CloudBuilder::eErrorCode ec) = 0;
		virtual void getBasePath(char *path) { *path=0; }
	
		const char ** getcommands(const char*);

		eErrorCode parse(int argc, const char **argv);
		eErrorCode context(int argc, const char **argv);
		eErrorCode setup(int argc, const char **argv);
		eErrorCode setup2(int argc, const char **argv);
		eErrorCode script(int argc, const char **argv);
		eErrorCode cd(int argc, const char **argv);
		int tokenize(char *line, int *argc, char **argv);
		void endCmd(eErrorCode ec, const CCloudResult *json=NULL);
		const char *replaceVar(const char *line, char **res);
		
		void suspend();
		void resume();
		void idle();

		bool compareKey(const CHJSON *j, const CHJSON *jr, const char *key, bool store, char *error);
		bool compareExpected(const CCloudResult *json, char *error);
		void checkExpected(const CCloudResult *json);
		void abortScript(const char *error);

		void getFavorites(const char** &favoriteList, int &count);

		bool mWorking;
		bool mModeScript;
		int mFlowScript;
		MyClan *myClan;

	private:
		void setContext(const char *game);
		eErrorCode cmd(int argc, const char **argv);
		eErrorCode set(int argc, const char **argv);
		char *mScript[1000];
		int mSize;
		int mLine;
		int mCurLine;
		CHJSON *mExpected;
		int mPassed;
		int mMissed;
		int mSkipped;
		CHJSON *mVar;
		CHJSON *mMissedLog;
		double mLastExecuteStartTime;
};

#endif /* defined(__CloudBuilderMacOSX__cli__) */
