//
//  CNotificationProxy.cpp
//  CloudBuilder
//
//  Created by Roland Van Leeuwen on 17/04/12.
//  Copyright (c) 2012 Clan of the Cloud. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CloudBuilder_private.h"
#include "CClan.h"
#include "CNotificationProxy.h"
#include "CNotificationManager.h"
#include "CCallback.h"
#include "CSharedQueueProxy.h"
#include "CloudBuilder_private.h"
#include "CTribeManager.h"
#include "CClannishDBProxy.h"
#include "curltool.h"
#include "CCloudSocket.h"
#include <list>
#include "cotc_thread.h"

#ifdef WIN32

#define usleep(x)	Sleep((x/1000) ? (x/1000) : 1);
#define strdup		_strdup

#else
#include <unistd.h>
#endif

using namespace CotCHelpers;

namespace CloudBuilder {

	class CCloudSocketNotify : public CCloudSocket {
	public:
		CCloudSocketNotify();
		~CCloudSocketNotify();
		virtual void on_error(const char* error);
		virtual void on_close(int reason);
		virtual void on_open();
		virtual void on_data(const CotCHelpers::CHJSON* json);		
	};
	
	CCloudSocketNotify::CCloudSocketNotify() {}
	CCloudSocketNotify::~CCloudSocketNotify(){}
	
	void CCloudSocketNotify::on_error(const char* error) {
		// try to reconnect 
	}
	
	void CCloudSocketNotify::on_close(int reason) {
		if (reason == 1)
		{
			// alert closing because another session went alive !
			CClan::Instance()->Alert(ALERT_RECONNECT, "Connection closed due to another session went alive");
		}
	}
	
	void CCloudSocketNotify::on_open() {
		const char *args[] = {
			"pseudo",	CClannishDBProxy::Instance()->GetPseudo(), 	
			"appID",	CClannishDBProxy::Instance()->GetAppID(),
			NULL,			NULL
		};
		CHJSON *json = CHJSON::initWith(args);

		CHJSON *event = new CHJSON();
		event->AddStringSafe("event", "welcome");
		event->Add("data", json);
		emit(event);
		delete event;
	}
	
	void CCloudSocketNotify::on_data(const CotCHelpers::CHJSON* json) {
		const char *event = json->GetStringSafe("event");
		if (strcmp(event, "notify-queued")==0)
		{
			CNotificationManager::Instance()->HandleRemoteNotification("");
			const char *ackID = json->GetStringSafe("ackID");
			this->emit_ack(ackID);
		}
		else if (strcmp(event, "notify")==0)
		{
			CONSOLE_VERBOSE("%s", json->printFormatted());
			const CHJSON* data = json->Get("data");
			
			int type = atoi(data->GetStringSafe("type"));
			
			CHandleNotify* notif = CHandleNotify::instance((etNotify)type);

			bool handled = notif->HandleNotify(data);
			if (handled)
			{
				const char *ackID = json->GetStringSafe("ackID");
				this->emit_ack(ackID);
			}
			delete notif;

		}
		else 
		{
			char *message = json->print();
			CClan::Instance()->Alert(INFO, message);		
			free(message);
		}
	}
	
	class CThreadQueue : public CThread {
	public:
		CThreadQueue();
		~CThreadQueue();
		
		virtual void task();
		
		void push(CHJSON *data);
		int pop();
		
		CCloudResult* send(CHJSON *data);
		void done(const CCloudResult *res);
		
		std::list<CHJSON *> datastack;
	};
	
	CThreadQueue::CThreadQueue() {
		
	}
	
	CThreadQueue::~CThreadQueue() {
	}
	
	void CThreadQueue::task ()
	{
		while (true)
		{
			this->pop();
			usleep(1 * 100);
		}
	}
	
	void CThreadQueue::push(CHJSON *data)
	{
		this->lock();
		datastack.push_back(data);
		this->unlock();
	}
	
	int CThreadQueue::pop()
	{
		this->lock();
		if (datastack.empty())
		{
			this->unlock();
			return 0;
		}
		
		CHJSON *data = datastack.front();
		datastack.pop_front();
		this->unlock();
		
		CCallback *callback = CCallback::classCallback( this,  (TclassCallback)&CThreadQueue::done);
		Invoke(callback, this->send(data));

		return 1;
	}
	
	CCloudResult* CThreadQueue::send(CHJSON *mJSON)
	{
		CCloudResult *res = NULL;
		etNotify type = (etNotify) atoi(mJSON->GetStringSafe("type"));
		
		// WARNING !
		// GetQueueURL is done event if not queued, to be sure that the queue will be create
		// in case of timeout at the server side !!!
		const char *queueUrl;
		switch (type)
		{
			case etAppUser:
				queueUrl = CNotificationProxy::Instance()->GetUserQueueURL(mJSON->GetStringSafe("toUser"));
				break;
			case etApp:
				queueUrl = CNotificationProxy::Instance()->GetAppQueueURL(mJSON->GetStringSafe("toUser"));
				break;
			case etAdmin:
				queueUrl = CNotificationProxy::Instance()->GetAdminQueueURL(mJSON->GetStringSafe("toUser"));
				break;
			case etAppMatch:
				queueUrl = CNotificationProxy::Instance()->GetMatchQueueURL(mJSON->GetStringSafe("toUser"), mJSON->GetStringSafe("activematch"));
				break;
		}
		
		bool mBool = strcmp(mJSON->GetStringSafe("queued"), "1")==0;
		if (mBool)
		{
			char *message = mJSON->print();
			
			if (queueUrl && *queueUrl!=0)
				res = CClannishDBProxy::GetQueueManager(type==etAdmin)->SendMessage(queueUrl, message);
			else
				res = new CCloudResult(enQueueDoesNotExist);
			
			free(message);
			
			if (res->GetErrorCode() == enNoErr)
			{
				eErrorCode err = cloudserver_invoke("notifyuserqueued", mJSON);
				delete res;
				return new CCloudResult(err);
			}
			else
				return res;
		}
		else
		{
			char *message = mJSON->print();
			CHJSON *json = new CHJSON();
			json->AddStringSafe("event", "notify");
			json->AddStringSafe("data", message);
			eErrorCode err = (eErrorCode) CNotificationProxy::Instance()->mSocket->emit(json);
			free(message);
			delete json;
			return new CCloudResult(err);
		}
	}
	
	void CThreadQueue::done(const CCloudResult *res)
	{
		eErrorCode err = res->GetErrorCode();
		CNotificationProxy::Instance()->didNotifyUser(err);
	}		
	
	
#pragma mark - CNotificationProxy
	
	CNotificationProxy *CNotificationProxy::gInstance = NULL;
	
	bool CNotificationProxy::gHandleAdminNotification = false;
	bool CNotificationProxy::gHasSpecificEvent = false;

	CNotificationProxy::CNotificationProxy(CNotificationManager *manager)
	{
		mClannishQueue = NULL;
		mAppQueue = NULL;
		mUserQueue = NULL;
		mMatchQueue = NULL;
		HandlingEvent = false;
		gInstance = this;
		mManager = manager;
		mSocket = NULL;
		mPendingNotification = 0;
		mMessagesQueue = NULL;
		mDeviceToken = NULL;
		mNotice = false;
	}
	
	CNotificationProxy::~CNotificationProxy()
	{
		delete mManager;
		delete mClannishQueue;
		delete mAppQueue;
		delete mUserQueue;
		delete mMatchQueue;
		if (mSocket)
			delete mSocket;
		if (mMessagesQueue);
			delete mMessagesQueue;
		if (mDeviceToken)
			free(mDeviceToken);
	}
	
	CNotificationProxy *CNotificationProxy::Instance() { return CNotificationProxy::gInstance; }
	CNotificationManager *CNotificationProxy::Manager() { return CNotificationProxy::gInstance->mManager; }
	
	void CNotificationProxy::Reconnect()
	{
		mSocket->reconnect();
	}
	
	void CNotificationProxy::Suspend()
	{
		if (CClan::Instance()->isUserLogged())
		{
			if (mSocket) mSocket->emit_suspend();
		}
	}
	
	DECLARE_TASK(CNotificationProxy, _Resume);

	void CNotificationProxy::Resume()
	{
		if (CClan::Instance()->isUserLogged())
		{
			if (mSocket) mSocket->emit_resume();
			
			HandleRemoteNotification("");
			
			if (mDeviceToken)
			{
				TASK(_Resume);
				task->mJSON->AddStringSafe("token", mDeviceToken);
				task->run();
			}
		}
	}

	CCloudResult *_Resume::execute()
	{
		(void) cloudserver_invoke("promote", mJSON);
		CCloudResult *res = CClannishDBProxy::Instance()->PromoteDevice(mJSON);
		return res;
	}
	
	void _Resume::done(const CCloudResult *res)
	{
	}

	eErrorCode CNotificationProxy::InitAfterLogin(const char *pseudo)
	{
		mAppQueue = NewAppQueue(pseudo);

		if (gHandleAdminNotification)
			mClannishQueue = NewAdminQueue(pseudo);
		
		
		if (gHasSpecificEvent)
			mUserQueue = NewUserQueue(pseudo);
		
		mSocket = new CCloudSocketNotify();
		
//		const char *server = "clanofthecloud.mobi";
//		const char *server = "23.23.233.232";
//		const char *server = "10.0.1.7";
//		const char *server = "54.243.179.125";

		int port = 3001;
		const char *server = "54.243.179.125";
		
		if (APN_SERVER && *APN_SERVER != 0)
		{
			char serv[100];
			strcpy(serv, APN_SERVER);
			char *p = strchr(APN_SERVER, ':'); 
			if (p)
			{
				strcpy(serv, p+3); // "://"
				p = strchr(serv, ':'); // second :
				if (p)
				{
					*p=0;
					server = serv;
					port = atoi(++p);
					port += 1;
				}
			}
		}

		CONSOLE_ERROR("\n\nConnecting to notifyserver at %s:%d\n", server, port);
		mSocket->connect(server, port);
		
		mMessagesQueue = new CThreadQueue();
		mMessagesQueue->run();
		
		return enNoErr;
	}
		
	CQueue* CNotificationProxy::NewAdminQueue(const char *toUser)
	{
		
		char queuename[100];
		sprintf(queuename, "q-%s-admin-cotc-", toUser);
		CQueue *queue = new CQueue(CClannishDBProxy::GetQueueManager(true), etAdmin);
		CCloudResult *result = queue->GetOrCreate(queuename, 60, 86400, 10240);
		if (result->GetErrorCode()!=enNoErr)
		{
			delete queue;
			queue = NULL;
		}
		delete result;
		
		return queue;
	}
	
	const char* CNotificationProxy::GetAdminQueueURL(const char *toUser)
	{
		static CHJSON *queueAdminList = new CHJSON();
		
		const char *queueURL = queueAdminList->GetStringSafe(toUser);
		if (*queueURL != 0)
			return 	queueURL;

		CQueue *queue = NewAdminQueue(toUser);
		if (queue)
		{
			queueAdminList->AddStringSafe(toUser,queue->GetQueueURL());
			delete queue;
		}
		
		return queueAdminList->GetStringSafe(toUser);
	}
	
	CQueue* CNotificationProxy::NewAppQueue(const char *toUser)
	{
		
		char queuename[100];
		sprintf(queuename, "q-%s-%s-cotc-", toUser, CClannishDBProxy::Instance()->GetAppID());
		CQueue *queue = new CQueue(CClannishDBProxy::GetQueueManager(false), etApp);
		CCloudResult *result = queue->GetOrCreate(queuename, 60, 86400, 10240);
		if (result->GetErrorCode()!=enNoErr)
		{
			delete queue;
			queue = NULL;
		}
		delete result;
		
		return queue;
	}

	const char* CNotificationProxy::GetAppQueueURL(const char *toUser)
	{
		static CHJSON *queueAppList = new CHJSON();
		
		const char *queueURL = queueAppList->GetStringSafe(toUser);
		if (*queueURL != 0)
			return 	queueURL;
		
		CQueue *queue = NewAppQueue(toUser);
		if (queue)
		{
			queueAppList->AddStringSafe(toUser,queue->GetQueueURL());
			delete queue;
		}
		
		return queueAppList->GetStringSafe(toUser);
	}

	CQueue* CNotificationProxy::NewUserQueue(const char *toUser)
	{
		
		char queuename[100];
		sprintf(queuename, "q-%s-external-%s-cotc-", toUser, CClannishDBProxy::Instance()->GetAppID());
		CQueue *queue = new CQueue(CClannishDBProxy::GetQueueManager(false), etAppUser);
		CCloudResult *result = queue->GetOrCreate(queuename, 60, 86400, 10240);
		if (result->GetErrorCode()!=enNoErr)
		{
			delete queue;
			queue = NULL;
		}
		delete result;
		
		return queue;
	}

	const char* CNotificationProxy::GetUserQueueURL(const char *toUser)
	{
		static CHJSON *queueUserList = new CHJSON();
		
		const char *queueURL = queueUserList->GetStringSafe(toUser);
		if (*queueURL != 0)
			return 	queueURL;
		
		CQueue *queue = NewUserQueue(toUser);
		if (queue)
		{
			queueUserList->AddStringSafe(toUser,queue->GetQueueURL());
			delete queue;
		}
		
		return queueUserList->GetStringSafe(toUser);
	}

	CQueue* CNotificationProxy::NewMatchQueue(const char* toUser, const char* matchID)
	{
		
		char queuename[100];
		sprintf(queuename, "q-%s-%s-match-cotc-", toUser, matchID);
		CQueue *queue = new CQueue(CClannishDBProxy::GetQueueManager(false), etAppMatch);
		CCloudResult *result = queue->GetOrCreate(queuename, 60, 86400, 10240);
		if (result->GetErrorCode()!=enNoErr)
		{
			delete queue;
			queue = NULL;
		}
		delete result;
		
		return queue;
	}
	
	CQueue* CNotificationProxy::GetMatchQueue(const char* toUser, const char* matchID)
	{
		static char lastMatchID[200] = "";
		static CQueue* lastQueue = NULL;
		
		if (strcmp(lastMatchID, matchID)==0)
			return lastQueue;
		else 
		{
			if (lastQueue)
				delete lastQueue;
			strcpy(lastMatchID, matchID);
			lastQueue = NewMatchQueue(toUser, matchID);
		}
		return lastQueue;
	}
	
	const char* CNotificationProxy::GetMatchQueueURL(const char *toUser, const char* matchID)
	{
		static CHJSON *queueMatchList = new CHJSON();
		
		char key[200];
		sprintf(key, "%s-%s", toUser, matchID);
		
		const char *queueURL = queueMatchList->GetStringSafe(key);
		if (*queueURL != 0)
			return 	queueURL;
		
		CQueue *queue = NewMatchQueue(toUser, matchID);
		if (queue)
		{
			queueMatchList->AddStringSafe(key,queue->GetQueueURL());
			delete queue;
		}
		
		return queueMatchList->GetStringSafe(key);
	}

	DECLARE_TASK(CNotificationProxy, _HandleRemoteNotification);
	
	CCloudResult *_HandleRemoteNotification::execute()
	{
		CCloudResult* res;
		
		if (self->gHandleAdminNotification && self->mClannishQueue)
		{
			 res = self->mClannishQueue->HandleRemoteNotification();
			delete res;
		}
			
		if (self->mAppQueue)
		{
			res = self->mAppQueue->HandleRemoteNotification();
			delete res;
		}
		
		if (self->mUserQueue)
		{
			res = self->mUserQueue->HandleRemoteNotification();
			delete res;
		}
		
		CMatchManager *matchManager = self->mManager->MatchDelegate;
		if (matchManager && matchManager->HasActiveMatch())
		{
			CQueue* matchQueue  = self->GetMatchQueue(CClannishDBProxy::Instance()->GetPseudo(), matchManager->GetActiveMatchID());
			if (matchQueue)
			{
				res =  matchQueue->HandleRemoteNotification();
				delete res;
			}
		}
			
		return new CCloudResult(enNoErr);
	}
	
	void _HandleRemoteNotification::done(const CCloudResult *res)
	{
		self->HandlingEvent = false;
	}		

	void CNotificationProxy::LookupNotification()
	{
		if (!HandlingEvent)
		{
			if (mPendingNotification)
			{
				CONSOLE_VERBOSE("lookup queue\n");
				mPendingNotification--;
				CNotificationProxy::Instance()->HandleRemoteNotification("");
			}
			else if (mNotice)
			{
				mNotice = false;
				CNotificationManager::Instance()->didEndLookingForNotification();
			}
		}
	}
	
	eErrorCode	CNotificationProxy::HandleRemoteNotification(const char *notificationID)
	{
		if (!HandlingEvent)
		{
			CNotificationManager::Instance()->didBeginLookingForNotification();
			mNotice = true;
			HandlingEvent = true;
			TASK(_HandleRemoteNotification);
			task->run();
			return enNoErr;
		}
		else
		{
			CONSOLE_VERBOSE("pending queue\n");
			mPendingNotification++;
		}
		return recursiveQueueEvent;
	}
		

	bool CNotificationProxy::HandleEvents(const CotCHelpers::CHJSON* events)
	{
		return true;
	}
	
	// called by _Logout::execute (which is not the main thread)
	eErrorCode CNotificationProxy::UnregisterDevice()
	{
		eErrorCode err = enNoErr;
		if (mDeviceToken)
		{
			CHJSON *json = new CHJSON();
			json->AddStringSafe("token", mDeviceToken);
			err = cloudserver_invoke("unregister", json);
			CCloudResult *res = CClannishDBProxy::Instance()->UnregisterDevice(json);
			err = res->GetErrorCode();
			delete res;
		}
		return err;
	}

	DECLARE_TASK(CNotificationProxy, _RegisterDevice);
	
	eErrorCode CNotificationProxy::RegisterDevice(const char *aDeviceName, const char *aDeviceToken)
	{
		if (!CClan::Instance()->isUserLogged())
				return enNotLogged;
			
		TASK(_RegisterDevice);
		
		char aDeviceUUID[100];
		
		#ifdef __IOS__
			DeviceUUID(aDeviceUUID);
		#else
			strcpy(aDeviceUUID, aDeviceName);
		#endif
		
		char itemName[200];
		sprintf(itemName, "%s-%s-%s-%s", LIBCOTC_OS, CClannishDBProxy::Instance()->GetAppID(), CClannishDBProxy::Instance()->GetPseudo(), aDeviceUUID);

		mDeviceToken = strdup(itemName);
		
		task->mJSON->AddStringSafe("itemName", itemName);
		task->mJSON->AddStringSafe("user", CClannishDBProxy::Instance()->GetPseudo());
		task->mJSON->AddStringSafe("dev-name", aDeviceName);
		task->mJSON->AddStringSafe("dev-token", aDeviceToken);
		task->mJSON->AddStringSafe("OS", LIBCOTC_OS);
		task->mJSON->AddStringSafe("appID", CClannishDBProxy::Instance()->GetAppID());
		task->run();
		return enNoErr;
	}
	
	CCloudResult *_RegisterDevice::execute()
	{
		// TODO : add (user,device,token) to AWS DB
		CCloudResult *res = CClannishDBProxy::Instance()->RegisterDevice(mJSON);
		if (res->GetErrorCode() == enNoErr)
		{
			delete res;
			return new CCloudResult(cloudserver_invoke("register", mJSON));
		}
		return res;
	}
	
	void _RegisterDevice::done(const CCloudResult *res)
	{
		eErrorCode err = res->GetErrorCode();
		self->didRegisterDevice(err); 
	}		
	
	
	eErrorCode CNotificationProxy::NotifyUser_Sync(const char *aUserID, const CHJSON* data, etNotify type, bool queued)
	{
		if (!CClan::Instance()->isUserLogged())
			return enNotLogged;
		
		char *dataString = data->print();
		
		CHJSON *mJSON = new CHJSON();
		char typestr[3]; sprintf(typestr, "%d", type);
		mJSON->AddStringSafe("type", typestr);
		mJSON->AddStringSafe("fromUser", CClannishDBProxy::Instance()->GetPseudo());
		mJSON->AddStringSafe("toUser", aUserID);
		mJSON->AddStringSafe("data", dataString);
		mJSON->AddStringSafe("appID", CClannishDBProxy::Instance()->GetAppID());		
		if (type == etAppMatch)
		{
			CMatchManager *matchManager = this->mManager->MatchDelegate;
			if (matchManager && matchManager->HasActiveMatch())
				mJSON->AddStringSafe("activematch", matchManager->GetActiveMatchID());
			else
				return enBadParameters;
		}

		
		eErrorCode err = enNoErr;

		// WARNING !
		// GetQueueURL is done event if not queued, to be sure that the queue will be create
		// in case of timeout at the server side !!!
		const char *queueUrl;
		switch (type)
		{
			case etAppUser:
				queueUrl = this->GetUserQueueURL(mJSON->GetStringSafe("toUser"));
				break;
			case etApp:
				queueUrl = this->GetAppQueueURL(mJSON->GetStringSafe("toUser"));
				break;
			case etAdmin:
				queueUrl = this->GetAdminQueueURL(mJSON->GetStringSafe("toUser"));
				break;
			case etAppMatch:
				queueUrl = this->GetMatchQueueURL(mJSON->GetStringSafe("toUser"), mJSON->GetStringSafe("activematch"));
				break;
		}

		if (queued)
		{
			CCloudResult *res;
			char *message = mJSON->print();
			
			if (queueUrl && *queueUrl!=0)
			{
				res = CClannishDBProxy::GetQueueManager(type==etAdmin)->SendMessage(queueUrl, message);
				err = res->GetErrorCode();
				delete res;
				if (err == enNoErr)
				{
					err = cloudserver_invoke("notifyuserqueued", mJSON);
				}
			}
			else 
				err = enQueueDoesNotExist;
			
			free(message);
		}
		else
		{
			char *message = mJSON->print();
			CHJSON *json = new CHJSON();
			json->AddStringSafe("event", "notify");
			json->AddStringSafe("data", message);
			err = (eErrorCode) mSocket->emit(json);
			free(message);
			delete json;
		}
		
		free(dataString);
		delete mJSON;

		return err;
	}

	eErrorCode CNotificationProxy::NotifyUser(const char *aUserID, const CHJSON* data, etNotify type, bool queued)
	{
		if (!CClan::Instance()->isUserLogged())
			return enNotLogged;
		
		char *dataString = data->print();
		char typestr[3]; sprintf(typestr, "%d", type);
		
		CHJSON *json = new CHJSON();
		json->AddStringSafe("queued", queued ? "1": "0");
		json->AddStringSafe("type", typestr);
		json->AddStringSafe("fromUser", CClannishDBProxy::Instance()->GetPseudo());
		json->AddStringSafe("toUser", aUserID);
		json->AddStringSafe("data", dataString);
		json->AddStringSafe("appID", CClannishDBProxy::Instance()->GetAppID());
		if (type == etAppMatch)
		{
			CMatchManager *matchManager = this->mManager->MatchDelegate;
			if (matchManager && matchManager->HasActiveMatch())
				json->AddStringSafe("activematch", matchManager->GetActiveMatchID());
		}
		
		mMessagesQueue->push(json);
		
		free(dataString);
		return enNoErr;
	}
		
	void CNotificationProxy::didRegisterDevice(eErrorCode error)
	{
		mManager->didRegisterDevice(error);
	}
	void CNotificationProxy::didNotifyUser(eErrorCode error)
	{
		mManager->didNotifyUser(error);
	}

	
	eErrorCode 	CNotificationProxy::GetSharedData(const char* matchID, long tag)
	{
		return enNoErr;		
	}
	
	eErrorCode 	CNotificationProxy::SetSharedData(const char* matchID, long tag, const CotCHelpers::CHJSON *aJson)
	{
		return enNoErr;		
	}
	
	bool CNotificationProxy::sharedDataHasChanged(const char* matchID, long tag, const CotCHelpers::CHJSON *aJson)
	{
		if (matchID != NULL && mManager->MatchDelegate)
			return mManager->MatchDelegate->sharedDataHasChanged(matchID, tag, aJson);
		else if (matchID == NULL && mManager->GameDelegate)
			return mManager->GameDelegate->sharedDataHasChanged(tag, aJson);
		else
			return true;
	}
	
	
	void CNotificationProxy::didGetSharedData(eErrorCode error, const char* matchID, long tag)
	{
		if (matchID != NULL && mManager->MatchDelegate)
			mManager->MatchDelegate->didGetSharedData(error, matchID, tag);
		else if (matchID == NULL && mManager->GameDelegate)
			mManager->GameDelegate->didGetSharedData(error, tag);
		return;
	}
	
	void CNotificationProxy::didSetSharedData(eErrorCode error,const char* matchID, long tag)
	{
		if (matchID != NULL && mManager->MatchDelegate)
			mManager->MatchDelegate->didSetSharedData(error, matchID, tag);
		else if (matchID == NULL && mManager->GameDelegate)
			mManager->GameDelegate->didGetSharedData(error, tag);
			return;
	}

#pragma mark -
#pragma mark - CHandleNotify


	CHandleNotify* CHandleNotify::instance(etNotify type)
	{
		switch (type) {
			case etAdmin:
				return new CHandleNotifyAdmin();
				break;
			case etApp:
				return new CHandleNotifyApp();
				break;
			case etAppMatch:
				return new CHandleNotifyMatch();
				break;
				
			default:
				return new CHandleNotify();
				break;
		}
	}

	bool CHandleNotify::HandleNotify(const CHJSON *json)
	{
		CHJSON *data = CHJSON::parse(json->GetStringSafe("data"));
	 	
		bool ret = CNotificationProxy::Manager()->receivedNotifyUser(json->GetStringSafe("fromUser"), data);
		
		delete data;
		return ret;
	}
	
	
#pragma mark - CHandleNotifyAdmin
	
	bool  CHandleNotifyAdmin::HandleNotify(const CHJSON *json)
	{
		CHJSON *data = CHJSON::parse(json->GetStringSafe("data"));
		const char *action = data->GetStringSafe("Action");
		
		bool ret = false;
		
		if (strcmp(action, ACTION_CHANGERELATIONSHIP)==0)
		{
			eRelationState newStatus = (eRelationState)atoi(data->GetStringSafe("status"));
			eRelationChange newState = ecUnknow;
			switch(newStatus)
			{
				case eRequested: newState=ecClaimed; break;
				case eFriend: newState=ecAccepted; break;
				case eReject: newState=ecRefused; break;
				default: break;
					
			}
			ret = CNotificationProxy::Manager()->relationshipHasChanged(json->GetStringSafe("fromUser"), newState);
		}
		else if (strcmp(action, ACTION_CLAIMASFRIEND)==0)
		{
			ret = CNotificationProxy::Manager()->relationshipHasChanged(json->GetStringSafe("fromUser"), ecClaimed);
		}
		else if (strcmp(action, ACTION_CHANGECHALLENGE)==0)
		{
			ret = CNotificationProxy::Manager()->challengeHasChanged(data->GetStringSafe("challengeID"),
					json->GetStringSafe("fromUser"), (eChallengeStatus)atoi(data->GetStringSafe("status")));
		}
		
		delete data;
		return ret;
	}
	
	
#pragma mark - CHandleNotifyApp
	
	bool CHandleNotifyApp::HandleNotify(const CHJSON *json)
	{
		CHJSON *data = CHJSON::parse(json->GetStringSafe("data"));
		const char *action = data->GetStringSafe("Action");
		
		bool ret = false;
		eMatchStatus status;
		if (strcmp(action, ACTION_INVITEFRIEND)==0)
		{
			status = eMatchClaimed;
		}
		else if (strcmp(action, ACTION_JOINMATCH)==0)
		{
			status = (eMatchStatus)atoi(data->GetStringSafe("status"));
		}
		
		return CNotificationProxy::Manager()->playerDidChangeState(data->GetStringSafe("matchID"),
																   json->GetStringSafe("fromUser"), status);
		
		delete data;
		return ret;
	}
	
#pragma mark - CHandleNotifyMatch
		
	bool CHandleNotifyMatch::HandleNotify(const CHJSON *json)
	{
		CHJSON *data = CHJSON::parse(json->GetStringSafe("data"));
		const char *action = data->GetStringSafe("Action");
		
		bool ret = false;
		if (strcmp(action, ACTION_MACTHMOVE)==0)
		{
			eMatchPhase phase = (eMatchPhase)atoi(data->GetStringSafe("phase"));
			CHJSON *controlJson = CHJSON::parse(data->GetStringSafe("control"));
			
			ret = CNotificationProxy::Manager()->MatchReceiveData(data->GetStringSafe("matchID"), json->GetStringSafe("fromUser"), phase, controlJson);
			
			delete controlJson;
		}
		
		delete data;
		return ret;
	}

}

