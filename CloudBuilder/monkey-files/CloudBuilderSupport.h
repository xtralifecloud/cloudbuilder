//
//  CloudBuilderSupport.h
//  SampleCloudBuilder
//
//  Created by Michael EL BAKI on 1/29/13.
//  Copyright (c) 2013 Clan of the Cloud. All rights reserved.
//

#ifndef SampleCloudBuilder_CloudBuilderSupport_h
#define SampleCloudBuilder_CloudBuilderSupport_h

#include "CloudBuilder.h"
#include "CClan.h"
#include "CUserManager.h"
#include "CGameManager.h"
#include "CTribeManager.h"
#include "CNotificationManager.h"

class TMonkeyOptions {
public:
	TMonkeyOptions();
	bool run;
	bool newuser;
	char login[50];
	char password[40];
	int loop;
	int event;
	int score;
	bool infinite;
	bool nodelay;
	char host[40];
};

extern TMonkeyOptions gMonkeyOptions;

void popNextCallback();

void CotC_Setup(void);
void Monkey_Start(void);

using namespace CloudBuilder;


class MyNotificationManager : public CloudBuilder::CNotificationManager
{
public:
	MyNotificationManager(const char *server = NULL);
	virtual ~MyNotificationManager(void);

	void didNotifyUser(eErrorCode aError, void *aReference);
	
};



class MyUserManager : public CloudBuilder::CUserManager
{
public:
	MyUserManager(void);
	virtual ~MyUserManager(void);
    
	void didRegisterAndLogin(CloudBuilder::eErrorCode error);
	void didLogin(CloudBuilder::eErrorCode error);
	void didLogout(CloudBuilder::eErrorCode error);

	void didRead(CloudBuilder::eErrorCode aError, const char* aKey, const char* aValue);
	void didWrite(CloudBuilder::eErrorCode aError, const char* aKey);

    bool receivedNotifyUser(const char *aFromUserID, const CotCHelpers::CHJSON* aData);

};

class MyGameManager : public CloudBuilder::CGameManager
{
public:
	MyGameManager(void);
	virtual ~MyGameManager(void);
    
	void didScore(CloudBuilder::eErrorCode error);
	void didBestHighScore(eErrorCode aError, const char *mode, const CotCHelpers::CHJSON *aJson);
};

class MyTribeManager : public CTribeManager
{
public:
	MyTribeManager(void);
	virtual ~MyTribeManager(void);

	void didListFriends(eErrorCode aError, const CotCHelpers::CHJSON* aArrayFriends);
	void didFriendsBestHighScore(eErrorCode aError, const char *aMode, const CotCHelpers::CHJSON *aJson);
    
};

class MyClan : public CloudBuilder::CClan {
public:
	MyClan();
    
	void didFinishSetup(CloudBuilder::eErrorCode error);
    
	MyUserManager *myUser;
	MyGameManager *myGame;
	MyTribeManager *myTribe;
};

#endif
