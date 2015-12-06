//
//  CloudBuilderSupport.cpp
//  SampleCloudBuilder
//
//  Created by Michael EL BAKI on 1/29/13.
//  Copyright (c) 2013 Clan of the Cloud. All rights reserved.
//

#include <iostream>

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "CloudBuilderSupport.h"
#include "CNotificationManager.h"

#define STATE(A, B, C) {if (strcmp(etat, A) == 0) { \
	if (ec==enNoErr) B  else { gMonkeyOptions.run = false; C } }}

#define PSTATE(A, min, max,  B) {if (strcmp(etat, A) == 0) {\
	 	wait(min, max); \
		time(&state_time_begin); \
	 	B  }}

static void putstate(const char *etat);
static void wait(int  min,  int max);

using namespace CloudBuilder;

MyClan*  theClan;

time_t state_time_begin;
const char *time_state;

int eventreceived = 0;
int eventsend = 0;
int eventreallysend = 0;
int countscore = 0;

#pragma mark state

void state( const char *etat, eErrorCode ec)
{
	time_t now;
	time(&now);
		
	if (ec == enCURLError)
	{
		std::cerr << " -----Process " << getpid() << " fail on CURLerror !!!!!\n";
		exit(1);
	}
	
	if (strcmp(time_state,"notified") !=0 && strcmp(time_state,"wait") !=0
		&& strcmp(time_state,"loopA") !=0 && strcmp(time_state,"loopB") !=0 )
		printf("%s tooks %lds\n", time_state, now-state_time_begin);

	STATE("setup", {
		gMonkeyOptions.run = false;
	}, {
	})

	STATE("wait", {
		if(gMonkeyOptions.event== 0 || eventsend >= gMonkeyOptions.event)
			putstate("quit");
	}, {
	})
	
	STATE("register", {
		putstate("write");
	}, {
		if (ec == enRegisterWithUsedEmailOrPseudo)
		{
			gMonkeyOptions.run = true;
			putstate("login");
		}
	})

	STATE("login", {
		putstate("write");
	}, {
	})


	STATE("write", {
		putstate("read");
	}, {
	})

	STATE("read", {
		putstate("score");
	}, {
	})

	STATE("logout", {
		gMonkeyOptions.run = false;
	}, {
	})
	
	STATE("score", {
		countscore++;
		if(countscore<=gMonkeyOptions.score)
			putstate("score");
		else
			putstate("bestscore");
	}, {
		if (ec == enNotHigherScore)
		{
			gMonkeyOptions.run = true;
			countscore++;
			if(countscore<=gMonkeyOptions.score)
				putstate("score");
			else
				putstate("bestscore");
		}
	})

	STATE("bestscore", {
		putstate("listfriends");
	}, {
	})
	
	STATE("listfriends", {
		putstate("bestscorefriends");
	}, {
	})

	STATE("bestscorefriends", {
		if (gMonkeyOptions.event)
			putstate("notify");
		else
			putstate("quit");
	}, {
	})

	STATE("notify", {
		if (eventsend < gMonkeyOptions.event)
			putstate("notify");
		else
			putstate("wait");
	}, {
	})

	STATE("notified", {
		if (eventsend < gMonkeyOptions.event)
			putstate("notify");
		else if (eventreceived < eventreallysend)
			putstate("wait");
		else
			putstate("quit");
	}, {
	})

	STATE("loopA", {
		putstate("loopA");
	}, {
	})

	STATE("loopB", {
		putstate("loopB");
	}, {
	})

	STATE("quit", {
		putstate("suspend");
		putstate("logout");
	}, {
	})

}


#pragma mark put state

static void wait(int  min,  int max)
{
	if (max>0 && gMonkeyOptions.nodelay==false)
	{
		int t = min + 1.0*(max-min)*rand()/RAND_MAX;
		if (t)
		{
			if (strcmp(time_state,"loopA") !=0 && strcmp(time_state,"loopB") !=0)
				printf("waiting %ds before %s ...\n", t, time_state);
				
			for (int i=0; i< t*10; i++)
			{
				popNextCallback();
				usleep(100000);
			}
		}
	}
	
}

static void putstate(const char *etat)
{
	eErrorCode  ec;

	time_state = etat;
	
	PSTATE("setup", 0,0, {
		ec = theClan->Setup("1", "AKIAJEDLW27VWGPHBBVA", "27bqPBwthKitSN0vE9udb340kuX2J1A6HTpMKE7t", "DEV");
		if (ec) printf("Setup returns %d : %s\n", ec, errorString(ec));
	})
	
	PSTATE("start", 0,0, {
		eventreceived = 0;
		eventsend = 0;
		eventreallysend = 0;
		countscore = 0;

		if (gMonkeyOptions.newuser)
			putstate("register");
		else
			putstate("login");
	})

	PSTATE("logout", 20,20, { // 20 secondes pour attendre tout les events qui trainent.....
		ec = theClan->myUser->Logout();
		if (ec) printf("Logout returns %d : %s\n", ec, errorString(ec));
	})
	

	PSTATE("register",0,0, {
		char mail[50];
		char pseudo[40];
			
		char name[40];
		gethostname(name, 40);
		
		char hname[40];
		char *s=hname;
		
		for (char *p = name; *p!=0; p++)
		{
			if (*p!='-' && *p!='.' ) *s++ = *p;
		}
		*s=0;
		
		
		sprintf(pseudo, "monkey%d%s", getpid(), hname);
		sprintf(mail, "%s@nomail.com", pseudo);
		
		//strcpy(pseudo, "monkey");
		
		strcpy(gMonkeyOptions.login, pseudo); // keep login in case on already used pid...
		strcpy(gMonkeyOptions.password, "pass");
		
		printf("Register with %s\n", pseudo);
		ec = theClan->myUser->RegisterAndLogin(mail, "pass", pseudo);
		if (ec) printf("RegisterAndLogin returns %d : %s\n", ec, errorString(ec));			
	})
	
	PSTATE("login", 0,0, {
		printf("Login with %s\n", gMonkeyOptions.login);
		ec = theClan->myUser->Login(gMonkeyOptions.login, gMonkeyOptions.password);
		if (ec) printf("Login returns %d : %s\n", ec, errorString(ec));
	})

	PSTATE("write", 0,2, {
		ec = theClan->myUser->Write("keymonkey", "valuemonkey");
		if (ec) printf("Write returns %d : %s\n", ec, errorString(ec));
	})

	PSTATE("read", 1,2, {
		ec = theClan->myUser->Read("keymonkey");
		if (ec) printf("Read returns %d : %s\n", ec, errorString(ec));
	})
	
	PSTATE("score", 0,2, {
		unsigned long score = 1000000.0*rand()/RAND_MAX;
		ec = theClan->myGame->Score(score, "monkey mode", stHighToLow);
		if (ec) printf("Score returns %d : %s\n", ec, errorString(ec));
	})

	PSTATE("bestscore", 0,2, {
		ec = theClan->myGame->BestHighScore(10, "monkey mode", stHighToLow);
		if (ec) printf("BestHighScore returns %d : %s\n", ec, errorString(ec));
	})

	PSTATE("listfriends", 0,2, {
		ec = theClan->myTribe->ListFriends();
		if (ec) printf("ListFriends returns %d : %s\n", ec, errorString(ec));
	})
	
	PSTATE("bestscorefriends", 0,2, {
		ec = theClan->myTribe->FriendsBestHighScore("monkey mode", stHighToLow);
		if (ec) printf("FriendsBestHighScore returns %d : %s\n", ec, errorString(ec));
	})

	PSTATE("notify", 1,5, {
		CotCHelpers::CHJSON *data = new CotCHelpers::CHJSON();
		data->Add("number", eventsend+1);
		int *reference = (int *)malloc(sizeof(int));
		*reference = eventsend+1;
		ec = CNotificationManager::Instance()->NotifyUser(gMonkeyOptions.login, data, reference);
		if (ec) printf("NotifyUser returns %d : %s\n", ec, errorString(ec));
		delete data;
	})

	PSTATE("suspend", 5,6, {
		theClan->Suspend();
	})

	PSTATE("wait", 0,1, {
	})

	PSTATE("loopA", 1,2, {
		static int loopcounter =0;
		char loopstr[20];
		sprintf(loopstr, "%d", ++loopcounter);
		ec = theClan->myUser->Write("keymonkeyloop", loopstr);
		if (ec) printf("Write Loop returns %d : %s\n", ec, errorString(ec));
	})

	PSTATE("loopB", 3,5, {
		ec = theClan->myUser->Read("keymonkeyloop");
		if (ec) printf("Read Loop returns %d : %s\n", ec, errorString(ec));
	})

	PSTATE("quit", 0,0, {
		if (gMonkeyOptions.infinite)
		{
			printf("\nStarting infinite loop...\n");
			state("loopA", enNoErr);
		}
		else
			state("quit", enNoErr);
	})

}

#pragma mark MyClan

void popNextCallback()
{
	CNotificationManager::popNextCallback();	
}

void CotC_Setup(void)
{
	srand(time(0));
	theClan = new MyClan();
	putstate("setup");
}

void Monkey_Start(void)
{
	putstate("start");
}

MyClan::MyClan() : CClan(false, new MyNotificationManager((*gMonkeyOptions.host ==0) ? NULL :  gMonkeyOptions.host ))
{
	myUser = new MyUserManager();
	myGame = new MyGameManager();
	myTribe = new MyTribeManager();
	
	CNotificationManager::Instance()->SetUserDelegate(myUser);
	CNotificationManager::Instance()->SetTribeDelegate(myTribe);
	CNotificationManager::Instance()->SetGameDelegate(myGame);

}

void MyClan::didFinishSetup(eErrorCode ec)
{
	if (ec) printf("didFinishSetup returns %d : %s\n", ec, errorString(ec));
	state("setup", ec);
}

#pragma mark MyNotificationManager
MyNotificationManager::MyNotificationManager(const char *server) : CNotificationManager(true, true, true, server)
{
}

MyNotificationManager::~MyNotificationManager()
{
}

void MyNotificationManager::didNotifyUser(eErrorCode ec, void *aReference)
{
	if (ec) printf("didNotifyUser returns %d : %s\n", ec, errorString(ec));
	if (aReference)
	{
		int id = *(int *)aReference;
		printf("Event %d sended\n", id);
		free(aReference);
		eventreallysend++;
	}
	eventsend++;
	state("notify", ec);
}


#pragma mark MyUserManager

MyUserManager::MyUserManager(void)
{
}

MyUserManager::~MyUserManager(void)
{
}

void MyUserManager::didRegisterAndLogin(eErrorCode ec)
{
	if (ec) printf("didRegister returns %d : %s\n", ec, errorString(ec));
	strcpy(gMonkeyOptions.login, this->GetPseudo());
	state("register", ec);
}

void MyUserManager::didLogin(eErrorCode ec)
{
	if (ec) printf("didLogin returns %d : %s\n", ec, errorString(ec));
	strcpy(gMonkeyOptions.login, this->GetPseudo());
	state("login", ec);
}

void MyUserManager::didLogout(eErrorCode ec)
{
	if (ec) printf("didLogout returns %d : %s\n", ec, errorString(ec));
	state("logout", ec);
}

void MyUserManager::didRead(CloudBuilder::eErrorCode ec, const char* aKey, const char* aValue)
{
	if (strcmp(aKey, "keymonkeyloop") == 0)
	{
		if (ec)
			printf("didRead Loop returns %d : %s\n", ec, errorString(ec));
		else
			printf("Loop %s\n", aValue);
		state("loopA", ec);
	}
	else
	{
		if (ec) printf("didRead returns %d : %s\n", ec, errorString(ec));
		state("read", ec);
	}
}

void MyUserManager::didWrite(CloudBuilder::eErrorCode ec, const char* aKey)
{
	if (strcmp(aKey, "keymonkeyloop") == 0)
	{
		if (ec) printf("didWrite Loop returns %d : %s\n", ec, errorString(ec));
		state("loopB", ec);
	}
	else
	{
		if (ec) printf("didWrite returns %d : %s\n", ec, errorString(ec));
		state("write", ec);
	}
}

bool MyUserManager::receivedNotifyUser(const char *aFromUserID, const CotCHelpers::CHJSON* aData)
{
	printf("Notification received from %s\n", aFromUserID);
	printf("%d Events received\n", ++eventreceived);
	state("notified", enNoErr);
	return true;
}

#pragma mark MyGameManager

MyGameManager::MyGameManager(void)
{
}

MyGameManager::~MyGameManager(void)
{
}

void MyGameManager::didScore(eErrorCode ec)
{
	if (ec) printf("didScore returns %d : %s\n", ec, errorString(ec));
	state("score", ec);
}

void MyGameManager::didBestHighScore(eErrorCode ec, const char *mode, const CotCHelpers::CHJSON *aJson)
{
	if (ec) printf("didBestHighScore returns %d : %s\n", ec, errorString(ec));
	state("bestscore", ec);
}

#pragma mark MyTribeManager

MyTribeManager::MyTribeManager(void)
{
}

MyTribeManager::~MyTribeManager(void)
{
}

void MyTribeManager::didListFriends(eErrorCode ec, const CotCHelpers::CHJSON* aArrayFriends)
{
	if (ec) printf("didListFriends returns %d : %s\n", ec, errorString(ec));
	state("listfriends", ec);
}

void MyTribeManager::didFriendsBestHighScore(eErrorCode ec, const char *aMode, const CotCHelpers::CHJSON *aJson)
{
	if (ec) printf("didFriendsBestHighScore returns %d : %s\n", ec, errorString(ec));
	state("bestscorefriends", ec);
}


