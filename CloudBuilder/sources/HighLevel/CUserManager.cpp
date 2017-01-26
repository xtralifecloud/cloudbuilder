//
//  CUserManager.cpp
//  CloudBuilder
//
//  Created by Roland Van Leeuwen on 26/04/12.
//  Copyright (c) 2012 Clan of the Cloud. All rights reserved.
//

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "CClan.h"
#include "CUserManager.h"
#include "CloudBuilder_private.h"
#include "curltool.h"
#include "RegisterDevice.h"
#include "CFilesystem.h"
#include "CClannishRESTProxy.h"
#include "GameCenterHandler.h"
#include "CStoreGlue.h"

#define LOGIN_PARAMS_PATH "cotcsystem/LoginParams.json"

using namespace CotCHelpers;

namespace CloudBuilder {
	static singleton_holder<CUserManager> managerSingleton;

	CUserManager::CUserManager() :
	loginDoneHandler(*(new CGloballyKeptHandler<CResultHandler>)),
	linkDoneHandler(*(new CGloballyKeptHandler<CResultHandler>)),
	convertDoneHandler(*(new CGloballyKeptHandler<CResultHandler>)),
	binaryDoneHandler(*(new CGloballyKeptHandler<CResultHandler>)) {
	}
	
	CUserManager::~CUserManager() {
		delete &linkDoneHandler;
		delete &loginDoneHandler;
		delete &convertDoneHandler;
		delete &binaryDoneHandler;
	}

	CUserManager *CUserManager::Instance() {
		return managerSingleton.Instance();
	}

	void CUserManager::Terminate() {
		managerSingleton.Release();
	}

	const char *CUserManager::GetDisplayName()
	{
		return CClannishRESTProxy::Instance()->GetDisplayName();
	}
	
	const char *CUserManager::GetGamerID()
	{
		return CClannishRESTProxy::Instance()->GetGamerID();
	}

	const char *CUserManager::GetMail()
	{
		return CClannishRESTProxy::Instance()->GetMail();
	}


	void CUserManager::Logout(CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		
		if (mDeviceOS && mDeviceToken) {
			CClannishRESTProxy::Instance()->UnregisterDevice(mDeviceOS, mDeviceToken, NULL);
			mDeviceToken = NULL;
			mDeviceOS = NULL;
		}
		if (CClannishRESTProxy::Instance()->isLinkedWith("gamecenter")) {
			GameCenter::logout(NULL);
		}
		
		CClannishRESTProxy::Instance()->Logout(NULL, MakeBridgeDelegate(this, &CUserManager::LogoutDone, aHandler));
	}
	
	void CUserManager::LogoutDone(CCloudResult *res) {
		// Unregister event listeners
		CClannishRESTProxy::Instance()->StopEventListening();
		UnregisterDevice();
		// Clear login parameters
		persistedLoginParams.mGamerId = NULL;
		persistedLoginParams.mGamerSecret = NULL;
		mAccountNetwork = NULL;
		CommitLoginParams();
		//CloudBuilder::CClannishRESTProxy::Instance()->Suspend(); mainthread ?
	}

	void CUserManager::didLogin(const CCloudResult *result) {
		if (result->GetErrorCode() == enNoErr) {
			persistedLoginParams.mGamerId = result->GetJSON()->GetString("gamer_id");
			persistedLoginParams.mGamerSecret = result->GetJSON()->GetString("gamer_secret");
			mAccountNetwork = result->GetJSON()->GetString("network");
			CommitLoginParams();
			// If we're effectively logged in, launch a listener for the private event domain
			if (CClannishRESTProxy::Instance()->autoRegisterForNotification())
				this->RegisterForNotification();
			CClannishRESTProxy::Instance()->StartEventListening();
			// We do that to start AppStore processes once logged in, and to restore potential purchases
			CStoreGlue::Instance();
		}
        loginDoneHandler.Invoke(result);
	}
	
	bool CUserManager::IsAnonymousAccount() {
		return IsEqual(mAccountNetwork, "anonymous");
	}

	void CUserManager::RegisterForNotification() {
		::RegisterDevice();
	}
	
	void CUserManager::CommitLoginParams() {
		if (CClan::Instance()->useAutoResume()) {
			CHJSON result;
			result.Put("gamerId", persistedLoginParams.mGamerId);
			result.Put("gamerSecret", persistedLoginParams.mGamerSecret);
			CFilesystemManager::Instance()->WriteJson(LOGIN_PARAMS_PATH, &result);
		}
	}

	void CUserManager::ReadLoginParams(PersistedLoginParams *dest) {
		if (CClan::Instance()->useAutoResume()) {
			CHJSON *result = CFilesystemManager::Instance()->ReadJson(LOGIN_PARAMS_PATH);
			if (result) {
				dest->mGamerId = result->GetString("gamerId");
				dest->mGamerSecret = result->GetString("gamerSecret");
			}
		}
	}

	void CUserManager::LoginAnonymous(const CotCHelpers::CHJSON* aConfiguration, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enAlreadyLogged); return; }
		if (loginDoneHandler.IsSet()) { InvokeHandler(aHandler, enOperationAlreadyInProgress); return; }
		
		loginDoneHandler.Set(aHandler);
		CHJSON j;
		j.Put("device", collectDeviceInformation());
        if (aConfiguration && aConfiguration->Has("options"))
            j.Put("options", aConfiguration->Get("options")->Duplicate());
		CClannishRESTProxy::Instance()->LoginAnonymous(&j, MakeBridgeDelegate(this, &CUserManager::LoginAnonymousDone));
	}
	
	void CUserManager::LoginAnonymousDone(CCloudResult *res) {
		didLogin(res);
	}
	
	void CUserManager::ResumeSession(const CotCHelpers::CHJSON* aConfiguration, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enAlreadyLogged); return; }
		if (loginDoneHandler.IsSet()) { InvokeHandler(aHandler, enOperationAlreadyInProgress); return; }
		
		const char *identifier = aConfiguration->GetString("id");
		const char *secret = aConfiguration->GetString("secret");
		// Empty parameters?
		if (!identifier || !secret) {
			InvokeHandler(aHandler, enBadParameters, "Missing parameter id or secret in configuration");
			return;
		}
		loginDoneHandler.Set(aHandler);		// we won't call it from here

		CHJSON json;
		json.Put("network", "anonymous");
		json.Put("id", identifier);
		json.Put("secret", secret);
		json.Put("device", collectDeviceInformation());
		if (aConfiguration->Has("options")) json.Put("options", aConfiguration->Get("options")->Duplicate());
		CClannishRESTProxy::Instance()->Login(&json, MakeBridgeDelegate(this, &CUserManager::LoginDone));
	}
	
    void CUserManager::LoginWithShortCode(const CotCHelpers::CHJSON* aConfiguration, CResultHandler *aHandler) {
        if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
        if (CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enAlreadyLogged); return; }
        if (loginDoneHandler.IsSet()) { InvokeHandler(aHandler, enOperationAlreadyInProgress); return; }
        
        const char *shortcode = aConfiguration->GetString("shortcode");
        // Empty parameters?
        if (!shortcode) {
            InvokeHandler(aHandler, enBadParameters, "Missing parameter shortcode in configuration");
            return;
        }
        loginDoneHandler.Set(aHandler);		// we won't call it from here
        
        CHJSON json;
        json.Put("network", "restore");
        json.Put("id", "");
        json.Put("secret", shortcode);
        json.Put("device", collectDeviceInformation());
        if (aConfiguration->Has("options")) json.Put("options", aConfiguration->Get("options")->Duplicate());
        CClannishRESTProxy::Instance()->Login(&json, MakeBridgeDelegate(this, &CUserManager::LoginDone));
    }
    
	void CUserManager::LoginDone(CCloudResult *result) {
		if (!result->GetErrorCode()) {
			LinkWithOther("");
		}
		didLogin(result);
	}
	
	void CUserManager::LoginNetwork(const CotCHelpers::CHJSON* aConfiguration, CResultHandler *aHandler) {
		if (loginDoneHandler.IsSet()) { InvokeHandler(aHandler, enOperationAlreadyInProgress); return; }

		const char *identifier = aConfiguration->GetString("id");
		const char *secret = aConfiguration->GetString("secret");
		const char *network = aConfiguration->GetString("network");

		if (strcmp(network, "googleplus")==0) {
			InvokeHandler(aHandler, enBadParameters, "googleplus network obsolete");
		} else if (strcmp(network, "facebook")==0) {
			InvokeHandler(aHandler, enBadParameters, "facebook network obsolete");
            
        } else if(strncmp(network, "external:", 9)==0) {
            loginDoneHandler.Set(aHandler);
            CHJSON *j = aConfiguration->Duplicate();
            j->Put("device", collectDeviceInformation());
            CClannishRESTProxy::Instance()->LogWithExternalNetwork(j, MakeBridgeDelegate(this, &CUserManager::LoginDone));
            delete j;
        } else if (strcmp(network, "facebookId")==0 && identifier && secret) {
			loginDoneHandler.Set(aHandler);
			CHJSON *j = aConfiguration->Duplicate();
			j->Put("device", collectDeviceInformation());
			j->Put("network", "facebook");
			CClannishRESTProxy::Instance()->LogWithExternalNetwork(j, MakeBridgeDelegate(this, &CUserManager::LoginDone));
			delete j;
		} else if (strcmp(network, "googleplusId")==0 && identifier && secret) {
			loginDoneHandler.Set(aHandler);
			CHJSON *j = aConfiguration->Duplicate();
			j->Put("device", collectDeviceInformation());
			j->Put("network", "googleplus");
			CClannishRESTProxy::Instance()->LogWithExternalNetwork(j, MakeBridgeDelegate(this, &CUserManager::LoginDone));
			delete j;
		} else if (strcmp(network, "email")==0 && identifier && secret) {
			loginDoneHandler.Set(aHandler);
			CHJSON *j = aConfiguration->Duplicate();
			j->Put("device", collectDeviceInformation());
			CClannishRESTProxy::Instance()->Login(j, MakeBridgeDelegate(this, &CUserManager::LoginDone));
			delete j;
		} else if (strcmp(network, "restore")==0 && identifier && secret) {
			loginDoneHandler.Set(aHandler);
			CHJSON *j = aConfiguration->Duplicate();
			j->Put("device", collectDeviceInformation());
			CClannishRESTProxy::Instance()->Login(j, MakeBridgeDelegate(this, &CUserManager::LoginDone));
			delete j;
		} else if (strcmp(network, "gamecenter")==0) {

			struct LoggedInWithGC: CInternalResultHandler {
				_BLOCK2(LoggedInWithGC, CInternalResultHandler,
						CUserManager*, self,
						CHJSON*, options);
				void Done(const CCloudResult *result) {
					self->LogWithGC(result, options);
					delete options;
				}
			};
			
			loginDoneHandler.Set(aHandler);
			CHJSON *options = aConfiguration->Has("options") ? aConfiguration->Get("options")->Duplicate() : new CHJSON();
			GameCenter::login(new LoggedInWithGC(this, options));

		} else {
			InvokeHandler(aHandler, enBadParameters, "Unrecognized network");
		}
	}

	void CUserManager::MailPassword(const CotCHelpers::CHJSON *aJson, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		CClannishRESTProxy::Instance()->MailPassword(aJson, MakeBridgeDelegate(aHandler));
	}

	void CUserManager::ChangePassword(const char *aNewPassword, CResultHandler *aHandler) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		CClannishRESTProxy::Instance()->ChangePassword(aNewPassword, MakeBridgeDelegate(aHandler));
	}

	void CUserManager::ChangeEmail(const char *aNewEmail, CResultHandler *aHandler) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		CClannishRESTProxy::Instance()->ChangeEmail(aNewEmail, MakeBridgeDelegate(aHandler));
	}


	void CUserManager::Publish(const char *network, const CotCHelpers::CHJSON* aMessage, CResultHandler *aHandler)
	{
		InvokeHandler(aHandler, enExternalCommunityNotSetup, "Unrecognized network");
	}

	/***
	eErrorCode CUserManager::LinkWithFB(eErrorCode error, const CotCHelpers::CHJSON* details) {
		if (error == enNoErr) {
			CFacebookGlue* fb = CClan::Instance()->getFBGlue();
			CONSOLE_VERBOSE("enter LinkWithFB\n");
			if (fb && fb->IsConnected()) {
				CONSOLE_VERBOSE("is linked to Facebook\n");
				CHJSON json;
				json.Put("network", "facebook");
				json.Put("id", details->GetString("fbid"));
				json.Put("secret", details->GetString("accesstoken"));
				CClannishRESTProxy::Instance()->LinkWith(&json, MakeDelegate(this, &CUserManager::linkDone));
				return enNoErr;
			}
		}
		
		linkDoneHandler.Invoke(enExternalCommunityError);
		return error;
	}

	//////////////////////////// Google ////////////////////////////
		
	void CUserManager::LinkWithGP(eErrorCode ec)
	{
		if (ec == enNoErr) {
			CGooglePlusGlue *gp = CClan::Instance()->getGPGlue();
			CONSOLE_VERBOSE("enter LogWithGP\n");
			if (gp && gp->isConnected()) {
				CONSOLE_VERBOSE("is linked to Google\n");
				const char *token = gp->GetToken();
				const char *gpid = gp->GetGPID();
				CHJSON json;
				json.Put("network", "googleplus");
				json.Put("id", gpid);
				json.Put("secret", token);
				CClannishRESTProxy::Instance()->LinkWith(&json, MakeDelegate(this, &CUserManager::linkDone));
				return;
			}
		}
		
		linkDoneHandler.Invoke(enExternalCommunityError);
	}
	*/
	
	//////////////////////////// Game Center ////////////////////////////	
	void CUserManager::LogWithGC(const CCloudResult *result, const CotCHelpers::CHJSON *aOptions) {
		eErrorCode error = result->GetErrorCode();
		if (error) {
			return didLogin(result);
		}
		
		CHJSON json;
		json.Put("network", "gamecenter");
		json.Put("id", result->GetJSON()->GetString("playerid"));
		json.Put("secret", "n/a");
		json.Put("device", collectDeviceInformation());
		// Add GC-specific properties
		
		CHJSON *opt = aOptions->Duplicate();
		CHJSON gc;
		gc.Put("gcalias", result->GetJSON()->GetString("alias"));
		gc.Put("gcdisplayname", result->GetJSON()->GetString("nickname"));
		gc.Put("gcunderage", result->GetJSON()->GetBool("underage"));
		opt->Put("gamecenter", gc);
		json.Put("options", opt);

		
		CONSOLE_VERBOSE("async login with GC\n");
		CClannishRESTProxy::Instance()->LogWithExternalNetwork(&json, MakeDelegate(this, &CUserManager::LogWithGCDone));
	}

	eErrorCode CUserManager::LinkWithGC(eErrorCode error, const char *gcid, const char *displayname)
	{
		return enExternalCommunityNotSetup;
	}
	
	void CUserManager::LogWithGCDone(const CCloudResult *res) {
		if (res->GetErrorCode() == enNoErr) {
			CONSOLE_VERBOSE("loginGC done \n");
			LinkWithOther("gamecenter");
		}
		didLogin(res);
	}
	
	//////////////////////////// Link ////////////////////////////
	void CUserManager::Link(const char *aNetwork, CResultHandler *aHandler) {
		InvokeHandler(aHandler, enNotImplemented , "obsolete method");
	}

    void CUserManager::Link(const CotCHelpers::CHJSON* aConfiguration, CResultHandler *aHandler) {
        if (!CClan::Instance()->isUserLogged()) { return InvokeHandler(aHandler, enNotLogged); }
        
        CHJSON args;
        const char *network = aConfiguration->GetString("network");
        
        if (IsEqual(network, "facebookId")) {
            args.Put("network", "facebook");
        }
        else if (IsEqual(network, "googleplusId")) {
            args.Put("network", "googleplus");
        }
        else if (IsEqual(network, "gamecenterId")) {
            struct LoggedInWithGC: CInternalResultHandler {
                _BLOCK3(LoggedInWithGC, CInternalResultHandler,
                        CUserManager*, self,
                        CHJSON*, options,
                        CInternalResultHandler*, resultHandler);
                void Done(const CCloudResult *result) {
                    CHJSON args;
                    args.Put("network", "gamecenter");
                    args.Put("id", result->GetJSON()->GetString("playerid"));
                    args.Put("secret", "n/a");
                    CClannishRESTProxy::Instance()->LinkWith(&args, resultHandler);
                    delete options;
                }
            };
            CHJSON *options = aConfiguration->Has("options") ? aConfiguration->Get("options")->Duplicate() : new CHJSON();
            GameCenter::login(new LoggedInWithGC(this, options, MakeBridgeDelegate(aHandler)));
            // Continue in the callback, unlike other methods
            return;
        }
        else {
            return InvokeHandler(aHandler, enBadParameters, "Unrecognized network (facebookId, googleplusId, gamecenterId supported)");
        }
        
        args.Put("id", aConfiguration->GetString("id"));
        args.Put("secret", aConfiguration->GetString("secret"));
        CClannishRESTProxy::Instance()->LinkWith(&args, MakeBridgeDelegate(aHandler));
    }

    void CUserManager::Link(CResultHandler *aHandler, const CotCHelpers::CHJSON* aConfiguration) {
        this->Link(aConfiguration, aHandler);
    }
    
	void CUserManager::Unlink(const char *aNetwork, CResultHandler *aHandler) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		CHJSON json;
		json.Put("network", aNetwork);

		if (strcmp(aNetwork, "facebook") ==0) {
		}
		
		if (strcmp(aNetwork, "googleplus") ==0) {
		}
		
		if (strcmp(aNetwork, "gamecenter") ==0) {
			GameCenter::logout(NULL);
		}
		
		CClannishRESTProxy::Instance()->Unlink(&json, MakeBridgeDelegate(aHandler));
	}
	
	void CUserManager::linkDone(const CCloudResult *res) {
		linkDoneHandler.Invoke(res);
	}
	
	void CUserManager::LinkWithOther(const char *networkToExclude) {
		if (strcmp(networkToExclude, "facebook")!=0 && CClannishRESTProxy::Instance()->isLinkedWith("facebook")) {
		}
		if (strcmp(networkToExclude, "googleplus")!=0 && CClannishRESTProxy::Instance()->isLinkedWith("googleplus")) {
		}
		if (strcmp(networkToExclude, "gamecenter")!=0 && CClannishRESTProxy::Instance()->isLinkedWith("gamecenter")) {
			GameCenter::login(NULL);
		}
	}

	void CUserManager::Convert(const CotCHelpers::CHJSON *aConfiguration, CResultHandler *aHandler) {
		if (!CClan::Instance()->isUserLogged()) { return InvokeHandler(aHandler, enNotLogged); }
		if (!IsAnonymousAccount()) { return InvokeHandler(aHandler, enLogicError, "Conversion only applies to anonymous accounts"); }
		const char *network = aConfiguration->GetString("network");
		if (!network || !network[0]) { return InvokeHandler(aHandler, enBadParameters, "Missing network key"); }
		if (!aConfiguration->Has("id") || !aConfiguration->Has("secret")) {
			return InvokeHandler(aHandler, enBadParameters, "account conversion requires id, secret keys");
		}

		if (convertDoneHandler.IsSet()) { InvokeHandler(aHandler, enOperationAlreadyInProgress); return; }

		if (IsEqual(network, "googleplus")) {
			InvokeHandler(aHandler, enExternalCommunityNotSetup, "Google+ obsolete");
			return;
		} else if (IsEqual(network, "facebook")) {
			InvokeHandler(aHandler, enExternalCommunityNotSetup, "Facebook obsolete");
			return;
		} else if (IsEqual(network, "facebookId")) {
			CHJSON json;
			json.Put("network", "facebook");
			json.Put("id", aConfiguration->GetString("id"));
			json.Put("secret", aConfiguration->GetString("secret"));
			CClannishRESTProxy::Instance()->Convert(&json, MakeDelegate(this, &CUserManager::convertDone));
		} else if (IsEqual(network, "googleplusId")) {
			CHJSON json;
			json.Put("network", "googleplus");
			json.Put("id", aConfiguration->GetString("id"));
			json.Put("secret", aConfiguration->GetString("secret"));
			CClannishRESTProxy::Instance()->Convert(&json, MakeDelegate(this, &CUserManager::convertDone));
		} else if (IsEqual(network, "gamecenter")) {
			convertDoneHandler.Set(aHandler);
			GameCenter::login(MakeBridgeDelegate(this, &CUserManager::ConvertToGC));
		} else if (IsEqual(network, "email")) {
			CClannishRESTProxy::Instance()->Convert(aConfiguration, MakeBridgeDelegate(aHandler));
		}
		else
			InvokeHandler(aHandler, enBadParameters, "Unrecognized network");
	}

    void CUserManager::Convert(CResultHandler *aHandler, const CotCHelpers::CHJSON *aConfiguration) {
        this->Convert(aConfiguration, aHandler);
    }
    
	void CUserManager::ConvertToGC(CloudBuilder::CCloudResult *result) {
		if (result->GetErrorCode()) { return convertDone(result); }

		CHJSON json, opt, gc;
		CONSOLE_VERBOSE("Trying to convert to Game Center\n");
		json.Put("network", "gamecenter");
		json.Put("id", result->GetJSON()->GetString("playerid"));
		// Add GC-specific properties
		gc.Put("gcalias", result->GetJSON()->GetString("alias"));
		gc.Put("gcdisplayname", result->GetJSON()->GetString("nickname"));
		gc.Put("gcunderage", result->GetJSON()->GetBool("underage"));
		opt.Put("gamecenter", gc);
		json.Put("options", opt);
		CClannishRESTProxy::Instance()->Convert(&json, MakeDelegate(this, &CUserManager::convertDone));
	}
	
	void CUserManager::convertDone(const CloudBuilder::CCloudResult *res) {
		convertDoneHandler.Invoke(res);
	}
	
	//////////////////////////// User actions ////////////////////////////
	void CUserManager::UserExist(const char *aIdent, const char *aNetwork, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		
		CHJSON json;
		json.Put("id",aIdent);
		json.Put("network", aNetwork);
		CClannishRESTProxy::Instance()->UserExist(&json, MakeBridgeDelegate(aHandler));
	}

	void CUserManager::Outline(CResultHandler *aHandler) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		CClannishRESTProxy::Instance()->Outline(MakeBridgeDelegate(aHandler));
	}

	void CUserManager::GetGodfatherCode(const char *aDomain, CResultHandler *aHandler) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		CClannishRESTProxy::Instance()->GetGodfatherCode(aDomain, MakeBridgeDelegate(aHandler));
	}
	
    void CUserManager::GetGodfatherCode(CResultHandler *aHandler, const char *aDomain) {
        this->GetGodfatherCode(aDomain, aHandler);
    }
    
    void CUserManager::GetGodfather(const char *aDomain, CResultHandler *aHandler) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		CClannishRESTProxy::Instance()->GetGodfather(aDomain, MakeBridgeDelegate(aHandler));
	}

    void CUserManager::GetGodfather(CResultHandler *aHandler, const char *aDomain) {
        this->GetGodfather(aDomain, aHandler);
    }
    
    void CUserManager::SetGodfather(const char *aCode, const CHJSON *aOptions, CResultHandler *aHandler) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		CHJSON *j;
		if (aOptions)
			j = aOptions->Duplicate();
		else
			j = new CHJSON();
		j->Put("godfather", aCode);
		CClannishRESTProxy::Instance()->SetGodfather(j, MakeBridgeDelegate(aHandler));
		delete j;
	}
	
	void CUserManager::GetGodchildren(const char *aDomain, CResultHandler *aHandler) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		CClannishRESTProxy::Instance()->GetGodchildren(aDomain, MakeBridgeDelegate(aHandler));
	}
    void CUserManager::GetGodchildren(CResultHandler *aHandler, const char *aDomain) {
        this->GetGodchildren(aDomain, aHandler);
    }
    
	void CUserManager::SetProfile(const CotCHelpers::CHJSON *aJson, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		
		CClannishRESTProxy::Instance()->SetUserProfile(aJson, MakeBridgeDelegate(aHandler));
	}
		
	void CUserManager::GetProfile(CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }

		CHJSON emptyJson;
		CClannishRESTProxy::Instance()->GetUserProfile(&emptyJson, MakeBridgeDelegate(aHandler));
	}
	

	void CUserManager::SetProperties(const CotCHelpers::CHJSON* aPropertiesList, const char *aDomain, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		
		if (aPropertiesList->type() != CHJSON::jsonObject) {
			InvokeHandler(aHandler, enBadParameters, "Malformed properties JSON (must be an object)");
			return;
		}
			
		int nb = aPropertiesList->size();
		for (int i=0; i<nb; i++) {
			const CHJSON * j = aPropertiesList->GetSafe(i);
			CHJSON::jsonType t = j->type();
			if (t != CHJSON::jsonTrue && t != CHJSON::jsonFalse && t != CHJSON::jsonString && t != CHJSON::jsonNumber) {
				InvokeHandler(aHandler, enBadParameters, "Malformed properties JSON (unrecognized property type)");
				return;
			}
		}
			  
		CClannishRESTProxy::Instance()->UserSetProperties(aDomain, aPropertiesList, MakeBridgeDelegate(aHandler));
	}
	
    void CUserManager::SetProperties(CResultHandler *aHandler, const CotCHelpers::CHJSON* aPropertiesList, const char *aDomain) {
        this->SetProperties(aPropertiesList, aDomain, aHandler);
    }
    
    void CUserManager::GetProperties(const char *aDomain, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }

		CClannishRESTProxy::Instance()->UserGetProperties(aDomain, MakeBridgeDelegate(aHandler));
   }

    void CUserManager::GetProperties(CResultHandler *aHandler, const char *aDomain) {
        return GetProperties(aDomain, aHandler);
    }
    
	void CUserManager::SetProperty(const CotCHelpers::CHJSON* aProperty, const char *aDomain, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		
		if (aProperty->type() != CHJSON::jsonObject) {
			InvokeHandler(aHandler, enBadParameters, "Malformed properties JSON (must be an object)");
			return;
		}
		
		if (!aProperty->Has("key")) return InvokeHandler(aHandler, enBadParameters, "Malformed properties JSON (key not found)");
		
		if (!aProperty->Has("value")) return InvokeHandler(aHandler, enBadParameters, "Malformed properties JSON (value not found)");

		const CHJSON * j = aProperty->GetSafe("value");
		CHJSON::jsonType t = j->type();
		if (t != CHJSON::jsonTrue && t != CHJSON::jsonFalse && t != CHJSON::jsonString && t != CHJSON::jsonNumber) {
			InvokeHandler(aHandler, enBadParameters, "Malformed properties JSON (unrecognized property type)");
			return;
		}
		
		CClannishRESTProxy::Instance()->UserSetProperty(aDomain, aProperty, MakeBridgeDelegate(aHandler));
	}

    void CUserManager::SetProperty(CResultHandler *aHandler, const CotCHelpers::CHJSON* aProperty, const char *aDomain) {
        this->SetProperty(aProperty, aDomain, aHandler);
    }
    
    void CUserManager::GetProperty(const char *aField, const char *aDomain, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		CClannishRESTProxy::Instance()->UserGetProperty(aDomain, aField, MakeBridgeDelegate(aHandler));
		
	}

    void CUserManager::GetProperty(CResultHandler *aHandler, const char *aField, const char *aDomain) {
        this->GetProperty(aField, aDomain, aHandler);
    }
    
    void CUserManager::DeleteProperty(const char *aField, const char *aDomain, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		CClannishRESTProxy::Instance()->UserDelProperty(aDomain, aField, MakeBridgeDelegate(aHandler));
		
	}

    void CUserManager::DeleteProperty(CResultHandler *aHandler, const char *aField, const char *aDomain) {
        this->DeleteProperty(aField, aDomain, aHandler);
    }
    
	void CUserManager::Balance(const char *aDomain, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }

		CClannishRESTProxy::Instance()->Balance(aDomain, NULL, MakeBridgeDelegate(aHandler));
	}

	void CUserManager::TxHistory(const char *aDomain, const CotCHelpers::CHJSON *aJSONCurrency, CResultHandler *aHandler) {
		if (!CClan::Instance()->isSetup()) { InvokeHandler(aHandler, enSetupNotCalled); return; }
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }

		CClannishRESTProxy::Instance()->TxHistory(aDomain, aJSONCurrency, MakeBridgeDelegate(aHandler));
	}


    void CUserManager::KeyValueRead(const CHJSON *aConfiguration, CResultHandler *aHandler) {
        if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
        const char *domain = aConfiguration->GetString("domain");
        const char *key = aConfiguration->GetString("key");
        
        CClannishRESTProxy::Instance()->vfsRead(domain, key, MakeBridgeDelegate(aHandler));
    }
    
    void CUserManager::KeyValueWrite(const CHJSON *aConfiguration, CResultHandler *aHandler) {
        if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
        const char *domain = aConfiguration->GetString("domain");
        const char *key = aConfiguration->GetString("key");
        const CHJSON *value = aConfiguration->Get("data");
        if (!value) { InvokeHandler(aHandler, enBadParameters, "Missing data"); return; }
        
        CClannishRESTProxy::Instance()->vfsWrite(domain, key, value, false, MakeBridgeDelegate(aHandler));
    }
    
    void CUserManager::GetValue(const CHJSON *aConfiguration, CResultHandler *aHandler) {
        if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
        const char *domain = aConfiguration->GetString("domain");
        const char *key = aConfiguration->GetString("key");
        
        CClannishRESTProxy::Instance()->vfsReadv3(domain, key, MakeBridgeDelegate(aHandler));
    }
    
    void CUserManager::SetValue(const CHJSON *aConfiguration, CResultHandler *aHandler) {
        if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
        const char *domain = aConfiguration->GetString("domain");
        const char *key = aConfiguration->GetString("key");
        const CHJSON *value = aConfiguration->Get("data");
        if (!value) { InvokeHandler(aHandler, enBadParameters, "Missing data"); return; }
        
        CClannishRESTProxy::Instance()->vfsWritev3(domain, key, value, false, MakeBridgeDelegate(aHandler));
    }
    
    void CUserManager::DeleteValue(const CHJSON *aConfiguration, CResultHandler *aHandler) {
        if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
        const char *domain = aConfiguration->GetString("domain");
        const char *key = aConfiguration->GetString("key");
        CClannishRESTProxy::Instance()->vfsDelete(domain, key, false, MakeBridgeDelegate(aHandler));
    }
    
	void CUserManager::KeyValueDelete(const CHJSON *aConfiguration, CResultHandler *aHandler) {
        this->DeleteValue(aConfiguration, aHandler);
	}

	void CUserManager::BinaryRead(const CHJSON *aConfiguration, CResultHandler *aHandler) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		const char *domain = aConfiguration->GetString("domain");
		const char *key = aConfiguration->GetString("key");
		CClannishRESTProxy::Instance()->vfsRead(domain, key, MakeInternalResultHandler(this, &CUserManager::binaryReadDone, aHandler));
	}
	
	void CUserManager::binaryReadDone(const CCloudResult *result, CResultHandler *aHandler) {
		if (result->GetErrorCode() != enNoErr) { InvokeHandler(aHandler, result); return; }
		//CONSOLE_VERBOSE("readbin :%s", result->Print());
		const char *url = result->GetJSON()->GetString("value");
		if (url == NULL || *url ==0 ) return InvokeHandler(aHandler, enServerError);
		CClannishRESTProxy::Instance()->DownloadData(url, MakeBridgeDelegate(aHandler));
	}
	
	void CUserManager::BinaryWrite(const CHJSON *aConfiguration, const void* aPointer, size_t aSize, CResultHandler *aHandler)
	{
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		const char *domain = aConfiguration->GetString("domain");
		const char *key = aConfiguration->GetString("key");
		CClannishRESTProxy::Instance()->vfsWrite(domain, key, NULL, true, MakeInternalResultHandler(this, &CUserManager::binaryWriteDone, aPointer, aSize, aHandler));
	}

	/*
	void CUserManager::binaryWriteDone(const CloudBuilder::CCloudResult *result, const void* aPointer, size_t aSize, CResultHandler *aHandler) {
		if (result->GetErrorCode() == enNoErr) {
			const char *url = result->GetJSON()->GetString("putURL");
			if (url == NULL || *url ==0 ) return InvokeHandler(aHandler, enServerError);
			CClannishRESTProxy::Instance()->UploadData(url, aPointer, aSize, MakeBridgeDelegate(aHandler));
		} else
			InvokeHandler(aHandler,result);
	}
	*/
	
	void CUserManager::binaryWriteDone(const CloudBuilder::CCloudResult *result, const void* aPointer, size_t aSize, CResultHandler *aHandler) {
		if (result->GetErrorCode() == enNoErr) {
			const char *url = result->GetJSON()->GetString("putURL");
			char *geturl = strdup(result->GetJSON()->GetString("getURL"));
			CONSOLE_ERROR("get url = %s", geturl);
			if (url == NULL || *url ==0 ) return InvokeHandler(aHandler, enServerError);
			CClannishRESTProxy::Instance()->UploadData(url, aPointer, aSize, MakeInternalResultHandler(this, &CUserManager::binaryUploadDone, geturl,  aHandler));
		} else
			InvokeHandler(aHandler,result);
	}
	
	void CUserManager::binaryUploadDone(const CloudBuilder::CCloudResult *result, char* geturl, CResultHandler *aHandler)
	{
		CONSOLE_ERROR("upload get url = %s", geturl);
		CHJSON *json = 	 (CHJSON *) result->GetJSON();
		json->Put("getURL", geturl);
		free(geturl);
		InvokeHandler(aHandler,result);
	}

    void CUserManager::SetBinary(const CHJSON *aConfiguration, const void* aPointer, size_t aSize, CResultHandler *aHandler)
    {
        if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
        const char *domain = aConfiguration->GetString("domain");
        const char *key = aConfiguration->GetString("key");
        CClannishRESTProxy::Instance()->vfsWritev3(domain, key, NULL, true, MakeInternalResultHandler(this, &CUserManager::binaryWriteDone, aPointer, aSize, aHandler));
    }
    
    void CUserManager::GetBinary(const CHJSON *aConfiguration, CResultHandler *aHandler) {
        if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
        const char *domain = aConfiguration->GetString("domain");
        const char *key = aConfiguration->GetString("key");
        CClannishRESTProxy::Instance()->vfsReadv3(domain, key, MakeInternalResultHandler(this, &CUserManager::getBinaryDone, aHandler));
    }
    
    void CUserManager::getBinaryDone(const CCloudResult *result, CResultHandler *aHandler) {
        if (result->GetErrorCode() != enNoErr) { InvokeHandler(aHandler, result); return; }
        printf("readbin :%s", result->GetJSON()->printFormatted().c_str());
        const CHJSON* jsonBlob = result->GetJSON()->Get("result");
        CONSOLE_VERBOSE("Blob JSON :%s", jsonBlob->printFormatted().c_str());
        const CHJSON* jsonUrl = jsonBlob->Get(0);
        const char *url = jsonUrl->valueString();
        if (url == NULL || *url ==0 ) return InvokeHandler(aHandler, enServerError);
        CClannishRESTProxy::Instance()->DownloadData(url, MakeBridgeDelegate(aHandler));
    }
    
    void CUserManager::BinaryDelete(const CHJSON *aConfiguration, CResultHandler *aHandler) {
        this->DeleteBinary(aConfiguration, aHandler);
    }
    
    void CUserManager::DeleteBinary(const CHJSON *aConfiguration, CResultHandler *aHandler) {
        if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
        const char *domain = aConfiguration->GetString("domain");
        const char *key = aConfiguration->GetString("key");
        CClannishRESTProxy::Instance()->vfsDelete(domain, key, true, MakeBridgeDelegate(aHandler));
    }
    
	void CUserManager::ListAchievements(const CHJSON *configuration, CResultHandler *handler) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(handler, enNotLogged); return; }

		CClannishRESTProxy::Instance()->ListAchievements(configuration, MakeBridgeDelegate(handler));
	}

	void CUserManager::SetAchievementData(const CHJSON *configuration, CResultHandler *handler) {
		// Requires login
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(handler, enNotLogged); return; }

		// Check parameters
		const char *domain = configuration->GetString("domain");
		const char *name = configuration->GetString("name");
		const CHJSON *data = configuration->Get("data");
		if (!name || !data) { InvokeHandler(handler, enBadParameters, "Missing required parameter name or data"); return; }

		// Default domain
		domain = (domain && *domain) ? domain : "private";
		CClannishRESTProxy::Instance()->SetAchievementGamerData(domain, name, data, MakeBridgeDelegate(handler));
	}

	void CUserManager::EarnAchievement(const char *unit, int increment, const CHJSON *gamerData, CResultHandler *handler) {
		struct TransactionDone: CInternalResultHandler {
			_BLOCK1(TransactionDone, CInternalResultHandler,
					CResultHandler*, resultHandler);

			void Done(const CCloudResult *result) {
				InvokeHandler(resultHandler, result);
			}
		};

		struct DoTransaction: CInternalResultHandler {
			_BLOCK2(DoTransaction, CInternalResultHandler,
					CHJSON*, txConfig,
					CResultHandler*, resultHandler);

			void Done(const CCloudResult *result) {
				if (result->GetErrorCode() != enNoErr) {
					InvokeHandler(resultHandler, result);
					return;
				}

				CClannishRESTProxy::Instance()->Transaction(txConfig, true, new TransactionDone(resultHandler));
				delete txConfig;
			}
		};

		char desc[1024];
		CHJSON *txConfig = new CHJSON, *tx = new CHJSON;
		CInternalResultHandler *next = new DoTransaction(txConfig, handler);
		safe::sprintf(desc, "Earned achievement %s by %d", unit, increment);
		tx->Put(unit, increment);
		txConfig->Put("transaction", tx);
		txConfig->Put("description", desc);

		if (!gamerData) {
			InvokeHandler(next, enNoErr);
			return;
		}
		CClannishRESTProxy::Instance()->SetAchievementGamerData("private", unit, gamerData, next);
	}

	// Not exposed as intended, as it is only for us (dev environments)
	void FACTORY_FCT CUserManager_ResetAchievements(const char *domain, CResultHandler *handler) {
		domain = (domain && *domain) ? domain : "private";
		CClannishRESTProxy::Instance()->ResetAchievements(domain, MakeBridgeDelegate(handler));
	}

	void CUserManager::TransactionExtended(const CotCHelpers::CHJSON *configuration, CResultHandler *handler) {
		CClannishRESTProxy::Instance()->Transaction(configuration, true, MakeBridgeDelegate(handler));
	}

	void CUserManager::RegisterDevice(const char *aOS, const char *aToken) {
		mDeviceOS = aOS;
		mDeviceToken = aToken;
		CClannishRESTProxy::Instance()->RegisterDevice(aOS, aToken, NULL);
	}
	
	void CUserManager::RegisterEventListener(const char *domain, CEventListener *listener) {
		const char *realdomain = (domain && *domain) ? domain : "private";
		CClannishRESTProxy::Instance()->RegisterEventListener(realdomain, listener);
	}

	void CUserManager::UnregisterEventListener(const char *domain, CEventListener *listener) {
		CClannishRESTProxy::Instance()->UnregisterEventListener(domain, listener);
	}
	
	void CUserManager::PushEvent(const char *aDomain, const char* aGamerid, const CotCHelpers::CHJSON *aEvent, const CotCHelpers::CHJSON *aNotification, CResultHandler *aHandler) {
		CHJSON *message = new CHJSON();
		message->Put("type", "user");
		message->Put("event", aEvent);
		message->Put("from", this->GetGamerID());
		message->Put("name", this->GetDisplayName());
		message->Put("to" , aGamerid);
		if (aNotification)
			message->Put("osn", aNotification);
		CClannishRESTProxy::Instance()->PushEvent(aDomain, aGamerid, message, MakeBridgeDelegate(aHandler));
	}

	void CUserManager::DoSetupProcesses(CResultHandler *aHandler) {
		PersistedLoginParams paramsToRestore;
		ReadLoginParams(&paramsToRestore);

		if (paramsToRestore.mGamerId) {
			struct LoginBridge: CResultHandler {
				CResultHandler *aHandler;
				LoginBridge(CResultHandler *aHandler) : aHandler(aHandler), CResultHandler(this, &LoginBridge::Done) {}
				void Done(eErrorCode code, const CCloudResult *result) {
					// Whether login succeeds or fails, the setup is considered OK
					InvokeHandler(aHandler, result);
				}
			};
			CHJSON json;
			json.Put("network", "anonymous");
			json.Put("id", paramsToRestore.mGamerId);
			json.Put("secret", paramsToRestore.mGamerSecret);
			ResumeSession(&json, new LoginBridge(aHandler));
			return;
		}

		InvokeHandler(aHandler, enNoErr);
	}

	void CUserManager::Batch(const CotCHelpers::CHJSON *aConfiguration, const CotCHelpers::CHJSON *aParameters, CResultHandler *aHandler) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(aHandler, enNotLogged); return; }
		CClannishRESTProxy::Instance()->BatchUser(aConfiguration, aParameters, MakeBridgeDelegate(aHandler));
	}

    void CUserManager::Batch(CResultHandler *aHandler, const CotCHelpers::CHJSON *aConfiguration, const CotCHelpers::CHJSON *aParameters) {
        this->Batch(aConfiguration, aParameters, aHandler);
    }
}
