//
//  CNotificationProxy.h
//  CloudBuilder
//
//  Created by Roland Van Leeuwen on 17/04/12.
//  Copyright (c) 2012 Clan of the Cloud. All rights reserved.
//

#ifndef CloudBuilder_CNotificationProxy_h
#define CloudBuilder_CNotificationProxy_h

#include "CloudBuilder.h"
#include "CCallback.h"
#include "CHJSON.h"

#define ACTION_CLAIMASFRIEND		"ClaimAsFriend"
#define ACTION_CHANGERELATIONSHIP 	"ChangeRelationship"
#define ACTION_CHANGECHALLENGE		"ChangeChallenge"
#define ACTION_INVITEFRIEND			"InviteFriend"
#define ACTION_JOINMATCH			"JoinMatch"
#define ACTION_MACTHMOVE			"MatchMove"

#ifdef WIN32

#ifdef SendMessage
#undef SendMessage
#endif

#endif

void platformSuspend();
void DeviceUUID(char *dest);

namespace CloudBuilder
{
	class CClan;
	class CQueue;
	class CNotificationManager;
	class CCloudSocketNotify;
	class CThreadQueue;
	
	typedef enum  etNotify {
		etAdmin = 1,
		etApp,
		etAppUser,
		etAppMatch
	} etNotify ;
	
	
	class CHandleNotify {
		public:
		static CHandleNotify* instance(etNotify type);

		virtual bool  	HandleNotify(const CotCHelpers::CHJSON* json);
	};

	class CHandleNotifyAdmin : public CHandleNotify {
	public:
		virtual bool  	HandleNotify(const CotCHelpers::CHJSON* json);
	};
	
	class CHandleNotifyApp : public CHandleNotify {
	public:
		virtual bool  	HandleNotify(const CotCHelpers::CHJSON* json);
		
	};
	
	class CHandleNotifyMatch : public CHandleNotify {
	public:
		virtual bool  	HandleNotify(const CotCHelpers::CHJSON* json);
		
	};

	class CNotificationProxy {
	public:
		
		static CNotificationProxy *Instance();
		static CNotificationManager *Manager();
		
		// called by CClan::afterInit; should not be called before user is logged...
		eErrorCode InitAfterLogin(const char *pseudo);

		CNotificationProxy(CNotificationManager *manager);
		virtual  ~CNotificationProxy();
		
		void		Reconnect();
		void		Suspend();
		void		Resume();
		eErrorCode	HandleRemoteNotification(const char *notificationID);
		void		LookupNotification();
		
		eErrorCode	RegisterDevice(const char *aDeviceName, const char *aDeviceToken);
		eErrorCode 	UnregisterDevice();
		eErrorCode	NotifyUser(const char *aUserID, const CotCHelpers::CHJSON* data, etNotify type, bool queued = true);
		eErrorCode	NotifyUser_Sync(const char *aUserID, const CotCHelpers::CHJSON* data, etNotify type, bool queued = true);
		bool		HandleEvents(const CotCHelpers::CHJSON* events);
		
		virtual void didRegisterDevice(eErrorCode error);
		virtual void didNotifyUser(eErrorCode error);

		FACTORY_MTD eErrorCode 	GetSharedData(const char* matchID, long tag);
		FACTORY_MTD eErrorCode 	SetSharedData(const char* matchID, long tag, const CotCHelpers::CHJSON *aJson);
		
		virtual FACTORY_MTD bool sharedDataHasChanged(const char* matchID, long tag, const CotCHelpers::CHJSON *aJson);

		virtual FACTORY_MTD void didGetSharedData(eErrorCode error, const char* matchID, long tag);
		virtual FACTORY_MTD void didSetSharedData(eErrorCode error,const char* matchID, long tag);

	protected:
		friend class CNotificationManager;
		friend class _HandleRemoteNotification;
		friend class _NotifyUser;
		
		const char* GetAdminQueueURL(const char *toUser);
		const char* GetAppQueueURL(const char *toUser);
		const char* GetUserQueueURL(const char *toUser);
		const char* GetMatchQueueURL(const char *toUser, const char* matchID);
		CQueue*	NewAdminQueue(const char *toUser);
		CQueue*	NewAppQueue(const char *toUser);
		CQueue*	NewUserQueue(const char *toUser);
		CQueue* NewMatchQueue(const char* toUser, const char* matchID);
		CQueue* GetMatchQueue(const char* toUser, const char* matchID);
		
		class CNotificationManager *mManager;
		static CNotificationProxy *gInstance;
		static 	bool gHandleAdminNotification;
		static 	bool gHasSpecificEvent;
		
	private:
		CQueue* mClannishQueue;
		CQueue* mAppQueue;
		CQueue* mUserQueue;
		CQueue* mMatchQueue;
		bool HandlingEvent;
		int mPendingNotification;
		CCloudSocketNotify* mSocket;
		CThreadQueue *mMessagesQueue;
		friend class CThreadQueue;
		char *mDeviceToken;
		bool mNotice;
	};

}


#endif
