//
//  CloudbuilderClient.cpp
//  CloudBuilder
//
//  Created by roland on 24/10/12.
//  Copyright (c) 2012 Clan of the Cloud. All rights reserved.
//

#include <iostream>
#include "CotCHelpers.h"
#include "CloudBuilder_private.h"
#include "CloudbuilderClient.h"
#include "CHJSON.h"
#include "curltool.h"
#include "idea.h"
#include "CClannishRESTProxy.h"
#include "CNotificationProxy.h"
#include "CNotificationManager.h"

namespace CloudBuilder {
	
	using namespace CotCHelpers;
	
	char console_buff[10240];
	#define DISPLAY(...) { sprintf(console_buff, __VA_ARGS__); console(console_buff); }

	
	#define RUN(name) 	{						\
		DISPLAY("\n--- %s ---", name); 			\
		CHJSON *json = new CHJSON(); 			

	#define NORUN(name) if (false) 				\
			RUN(name)
			
	#define FINAL 								\
		delete json;							\
		eErrorCode error = cr->GetErrorCode();	\
		DISPLAY("result (%d): %s", error, p=cr->print());	\
		free(p);								\
		delete cr;								\
		DISPLAY("---");

	#define END	\
		FINAL }

	#define STOPONERR				\
		FINAL						\
		if (error) return error;	\
		}
				
	CClannishRESTProxy * rest = NULL;

	int invoke_api(const char *aCommunityKey, const char *aCommunitySecret, const char *aEnv, void(*console)(const char *))
	{

		eErrorCode err;
		CCloudResult *cr;
		char *p;

		if (rest == NULL)
		{
			CotCHelpers::Init();
			rest = new CClannishRESTProxy();
			CNotificationManager *notif = new CNotificationManager(true, true, true);
			CNotificationProxy *proxy = new CNotificationProxy(notif);

		}
		
		char timestr[30];
		aws_timestamp(timestr);
		DISPLAY("Start at : %s", timestr);
		
		CHJSON *mJSON = new CHJSON();
		
		mJSON->AddStringSafe("key", aCommunityKey);
		mJSON->AddStringSafe("secret", aCommunitySecret);
		mJSON->AddStringSafe("env", aEnv);
		
		
		DISPLAY("\n--- Setup:");
		cr = rest->Setup(mJSON);
		err= cr->GetErrorCode();
		DISPLAY("result : %s", p=cr->print());
		free(p);
		delete cr;
		delete mJSON;
		DISPLAY("------------");
		
		if (err) return err;
		
		NORUN("RegisterAndLogin")
			char encrypted[50];
			TIdea idea;
			idea.EncodeIDEA(encrypted, "pass", IDEA_ENCRYPT, 24);

			json->AddStringSafe("pseudo", "rolandz1");
			json->AddStringSafe("email", "roland@zeonecompany.fr");
			json->AddStringSafe("password", encrypted);
			cr = rest->RegisterAndLogin(json);
		END
		
		NORUN("Login")
			char encrypted[50];
			TIdea idea;
			idea.EncodeIDEA(encrypted, "pass", IDEA_ENCRYPT, 24);

			json->AddOrReplaceStringSafe("ident", "rolandz1");
			json->AddOrReplaceStringSafe("password", encrypted);
			cr = rest->Login(json);
		STOPONERR
		
		NORUN("SetUserProfile")
			json->AddStringSafe("displayname", "roro");
			json->AddStringSafe("fisrtname", "roland");
			json->AddStringSafe("lastname", "zeOne");
			cr = rest->SetUserProfile(json);
		END
		
		NORUN("GetUserProfile")
			cr = rest->GetUserProfile(json);
		END

		NORUN("SaveState")
			json->AddStringSafe("state", "{ level:1, life:3, xp: 'beginner' }");
			cr = rest->SaveState(json);
		END
		
		NORUN("GetState")
			cr = rest->GetState(json);
		END

		NORUN("Logout")
			cr = rest->Logout(NULL);
		END


		RUN("Login")
			char encrypted[50];
			TIdea idea;
			idea.EncodeIDEA(encrypted, "darwin", IDEA_ENCRYPT, 24);

			json->AddOrReplaceStringSafe("ident", "rolandvl");
			json->AddOrReplaceStringSafe("password", encrypted);
			cr = rest->Login(json);
		STOPONERR


		RUN("Pop")
			char queuename_appuser[100];
			sprintf(queuename_appuser, "queue:%s:%s", rest->GetAppID(), rest->GetPseudo());
			json->AddStringSafe("queuename", queuename_appuser);
			cr = rest->PopEvent(json); // infinite loop !
		END

		NORUN("ListUsers")
			json->AddStringSafe("filter", "rolandvl@icloud.com");
			cr = rest->ListUsers(json);
		END
		

		NORUN("Suspend")
			cr = new CCloudResult(enNoErr);
			rest->Suspend();
		END
		
		NORUN("Resume")
			cr = new CCloudResult(enNoErr);
			rest->Resume();
		END

		NORUN("Resume")
			cr = new CCloudResult(enNoErr);
			rest->Resume();
		END
		
		NORUN("Suspend")
			cr = new CCloudResult(enNoErr);
			rest->Suspend();
		END

		NORUN("Suspend")
			cr = new CCloudResult(enNoErr);
			rest->Suspend();
		END

		RUN("Resume")
			cr = new CCloudResult(enNoErr);
			rest->Resume();
		END

		NORUN("ChangeRelationshipStatus")
			json->AddStringSafe("friendID", "rolandz1");
			json->AddStringSafe("status", "2");
			cr = rest->ChangeRelationshipStatus(json);
		END
		
		NORUN("ListFriends")
			cr = rest->ListFriends(json);
		END
		
		RUN("RegisterDevice")
			json->AddStringSafe("itemName", "testunitaire-1");
			json->AddStringSafe("user", rest->GetPseudo());
			json->AddStringSafe("dev-name", "device-simulateur");
			json->AddStringSafe("dev-token", "token-simulateur");
			json->AddStringSafe("OS", "iOS-simu");
			json->AddStringSafe("appID", rest->GetAppID());
			cr = rest->RegisterDevice(json);
		END
		
		RUN("PromoteDevice")
			json->AddStringSafe("token", "testunitaire-1");
			cr = rest->PromoteDevice(json);
		END
		
		RUN("Resume")
			cr = new CCloudResult(enNoErr);
			rest->Resume();
		END

		RUN("Push")
			etNotify type = etAppUser;
			char typestr[3]; sprintf(typestr, "%d", type);
			json->AddStringSafe("type", typestr);
			
			json->AddStringSafe("fromUser", rest->GetPseudo());
			json->AddStringSafe("toUser", "unknownuser");
			json->AddStringSafe("data", "{ \"test\" : \"1\" }" );
			json->AddStringSafe("appID", rest->GetAppID());
			if (type == etAppMatch)
				json->AddStringSafe("activematch", "match-id-001");
			cr = rest->PushEvent(json);
		END

		RUN("Push")
			etNotify type = etAppUser;
			char typestr[3]; sprintf(typestr, "%d", type);
			json->AddStringSafe("type", typestr);
			
			json->AddStringSafe("fromUser", rest->GetPseudo());
			json->AddStringSafe("toUser", rest->GetPseudo());
			json->AddStringSafe("data", "{ \"test\" : \"2\" }" );
			json->AddStringSafe("appID", rest->GetAppID());
			if (type == etAppMatch)
				json->AddStringSafe("activematch", "match-id-001");
			cr = rest->PushEvent(json);
		END


		NORUN("CreateMatch")
			json->AddStringSafe("matchID", "roland-00000000000");
			json->AddStringSafe("private", "1");
			json->AddStringSafe("status", "1");
			json->AddStringSafe("data", "{ 'level': '1' }");
			cr = rest->CreateMatch(json);
		END

		NORUN("UpdateMatch")
			json->AddStringSafe("matchID", "roland-00000000000");
			json->AddStringSafe("invited", "['roland', 'rolandvl', 'rolandz1']");
			cr = rest->UpdateMatch(json);
		END

		NORUN("Score")
			json->AddStringSafe("mode", "easy");
			json->AddStringSafe("score", "0000001000");
			cr = rest->Score(json);
		END

		NORUN("UnregisterDevice")
			json->AddStringSafe("token", "testunitaire-1");
			cr = rest->UnregisterDevice(json);
		END
		
		NORUN("Logout")
			cr = rest->Logout(NULL);
		END
				
		aws_timestamp(timestr);
		DISPLAY("Stop at : %s", timestr);

		return 0;
	}
}
