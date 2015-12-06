//
//  CTribeManager.cpp
//  CloudBuilder
//
//  Created by Roland Van Leeuwen on 20/04/12.
//  Copyright (c) 2012 Clan of the Cloud. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "CloudBuilder_private.h"
#include "CClan.h"
#include "CCallback.h"
#include "CTribeManager.h"
#include "CClannishRESTProxy.h"
#include "GameCenterHandler.h"

using namespace CotCHelpers;

namespace CloudBuilder {

	static singleton_holder<CTribeManager> managerSingleton;
	
	CTribeManager::CTribeManager() : friendHandler(*(new CGloballyKeptHandler<CResultHandler>)) {
	}
	
	CTribeManager::~CTribeManager() {
		delete &friendHandler;
	}
	
	CTribeManager *CTribeManager::Instance() {
		return managerSingleton.Instance();
	}

	void CTribeManager::Terminate() {
		managerSingleton.Release();
	}

	void CTribeManager::ListUsers(const char *containsString, int limit, int skip, CResultHandler *handler)
	{
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(handler, enNotLogged); return; }
		CHJSON json;
		json.Put("q",containsString);
		json.Put("skip",skip);
		json.Put("limit",limit);
		return CClannishRESTProxy::Instance()->ListUsers(&json, MakeBridgeDelegate(handler));
	}
	
	void CTribeManager::ListFriends(CResultHandler *handler, const char *aDomain) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(handler, enNotLogged); return; }
		CHJSON json;
		json.Put("domain", aDomain);
		return CClannishRESTProxy::Instance()->ListFriends(&json, MakeBridgeDelegate(handler));
	}
			
	void CTribeManager::BlacklistFriends(CResultHandler *handler, const char *aDomain) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(handler, enNotLogged); return; }
		CHJSON json;
		json.Put("domain", aDomain);
		return CClannishRESTProxy::Instance()->BlacklistFriends(&json, MakeBridgeDelegate(handler));
	}
	
	void CTribeManager::ChangeRelationshipStatus(CResultHandler *handler, const CotCHelpers::CHJSON *aOptions) {
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(handler, enNotLogged); return; }
		if (aOptions == NULL) { InvokeHandler(handler, enBadParameters); return; }
		if (IsEqual(aOptions->GetString("id", ""), CClannishRESTProxy::Instance()->GetGamerID())) { InvokeHandler(handler, enFriendYourself); return; }
		return CClannishRESTProxy::Instance()->ChangeRelationshipStatus(aOptions, MakeBridgeDelegate(handler));
		
	}
	
	void CTribeManager::ListNetworkFriends(CResultHandler *handler, const CotCHelpers::CHJSON* aConfiguration)
	{
		const char *network = aConfiguration->GetString("network");
		
		CONSOLE_VERBOSE("List network friends\n");
		if (!CClan::Instance()->isUserLogged()) { InvokeHandler(handler, enNotLogged); return; }
		
		if (IsEqual(network, "googleplus")) {
			return InvokeHandler(handler, enExternalCommunityNotSetup, "Obsolete network");
		} else if (IsEqual(network, "facebook")) {
			return InvokeHandler(handler, enExternalCommunityNotSetup, "Obsolete network");
		} else if (IsEqual(network, "googleplusId")) {
			return CClannishRESTProxy::Instance()->GetNetworkFriends("googleplus", aConfiguration, MakeBridgeDelegate(handler));
		} else if (IsEqual(network, "facebookId")) {
			return CClannishRESTProxy::Instance()->GetNetworkFriends("facebook", aConfiguration, MakeBridgeDelegate(handler));
		} else if (IsEqual(network, "gamecenter")) {
			// List game center friends -- will continue to ListFriendsGCDone
			struct ListedFriendsGC: CInternalResultHandler {
				_BLOCK3(ListedFriendsGC, CInternalResultHandler,
						CTribeManager *, self,
						CHJSON *, mConfig,
						CResultHandler *, resultHandler);
				void Done(const CCloudResult *result) {
					owned_ref<CHJSON> config (mConfig); // To ensure release when exited

					self->ListFriendsGCDone(result, config, resultHandler);
				}
			};
			GameCenter::listFriends(new ListedFriendsGC(this, aConfiguration->Duplicate(), handler));
			
		} else {
			return InvokeHandler(handler, enExternalCommunityNotSetup, "Unrecognized network");
		}
		
	}
	
	void CTribeManager::ListNetworkFriends(CResultHandler *handler, const char *network, const CotCHelpers::CHJSON* aFriends ) {
		CHJSON config;
		config.Put("network" , network);
		config.Put("friends" , aFriends->Duplicate());
		ListNetworkFriends(handler, &config);
	}
	
	void CTribeManager::ListFriendsGCDone(const CCloudResult *result, CotCHelpers::CHJSON* aConfiguration, CResultHandler *callNext) {
		CHJSON friendsForCotC;
		const CHJSON *gcPlayers = result->GetJSON()->GetSafe("players");

		// Iterate over friend array items
		for (int i = 0, count = gcPlayers->size(); i < count; i++) {
			const CHJSON *player = gcPlayers->Get(i);
			const char *key = player->GetString("playerid");
			if (!key) {
				return InvokeHandler(callNext, enExternalCommunityError, "Malformed data returned from Game Center APIs");
			}
			friendsForCotC.Put(key, player->Duplicate());
		}
				
		// Push to the server
		CHJSON *j = aConfiguration->Duplicate();
		j->Put("network", "gamecenter");
		j->Put("friends", friendsForCotC);
		
		CClannishRESTProxy::Instance()->GetNetworkFriends("gamecenter", j, MakeBridgeDelegate(callNext));
		delete j;
	}

	void CTribeManager::FriendsBestHighScore(CResultHandler *handler, int aCount, int aPage, const char *aMode, const char *aDomain)
	{
		CHJSON json;
		json.Put("count", aCount);
		json.Put("mode", aMode);
		json.Put("page", aPage);
		json.Put("domain", aDomain);
		return CClannishRESTProxy::Instance()->FriendsBestHighScore(&json, MakeBridgeDelegate(handler));
	}

	void CTribeManager::FindOpponents(CResultHandler *handler, const CotCHelpers::CHJSON *aFilter, const char *aDomain) {
		return CClannishRESTProxy::Instance()->FindOpponents(aDomain, aFilter, MakeBridgeDelegate(handler));
	}
}

