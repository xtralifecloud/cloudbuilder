#include "CloudBuilder.h"
#include "CClan.h"
#include "GameCenterHandler.h"
#include "CCallback.h"
#include "CloudBuilder_private.h"
#import <GameKit/GameKit.h>

using namespace CloudBuilder;
using CotCHelpers::CHJSON;

// Converts player data to a caller-owned JSON object
static CHJSON *jsonFromPlayer(GKPlayer *p);
static bool alreadyCalled;

void CloudBuilder::GameCenter::login(CInternalResultHandler *handler) {
	GKLocalPlayer* localPlayer = [GKLocalPlayer localPlayer];

	// Old way
	alreadyCalled = false;
	[localPlayer authenticateWithCompletionHandler:^(NSError *error) {
		// Due to bad retro compatibility implementation in iOS 8, this block may be called multiple times (like upon application resume)
		if (alreadyCalled) {
			return;
		}
		alreadyCalled = true;
		
		if (error) {
			CHJSON *json = new CHJSON();
			json->Put("error", error.description);
			CCloudResult result(enExternalCommunityError, json);
			//CCloudResult result(enExternalCommunityError);
			//result.Put("error", error.description);
			
			NSLog(@"Game Center error: %@", error.description);
			InvokeHandler(handler, &result);
			
		} else {
			CHJSON *json = jsonFromPlayer(localPlayer);
			json->Put("underage", localPlayer.underage == YES);
			NSLog(@"Connected Game Center player %@", localPlayer.playerID);

			CCloudResult result (enNoErr, jsonFromPlayer(localPlayer));
			InvokeHandler(handler, &result);
		}
	}];
}

void CloudBuilder::GameCenter::logout(CInternalResultHandler *handler) {
	// Nothing to do really
	InvokeHandler(handler, enNoErr);
}

void CloudBuilder::GameCenter::listFriends(CInternalResultHandler *handler) {
	GKLocalPlayer* localPlayer = [GKLocalPlayer localPlayer];
	[localPlayer loadFriendsWithCompletionHandler:^(NSArray *friends, NSError *error) {
		[GKPlayer loadPlayersForIdentifiers:friends withCompletionHandler:^(NSArray *friendPlayers, NSError *error) {
			CHJSON *playersArray = CHJSON::Array();
			for (GKPlayer *f in friendPlayers) {
				playersArray->Add(jsonFromPlayer(f));
			}
			CHJSON *json = new CHJSON();
			json->Put("players", playersArray);
			CCloudResult result(enNoErr, json);
			InvokeHandler(handler, &result);
		}];
	}];
}

CHJSON *jsonFromPlayer(GKPlayer *p) {
	CHJSON *result = new CHJSON;
	result->Put("playerid", [p.playerID UTF8String]);
	result->Put("alias", [p.alias UTF8String]);
	result->Put("nickname", [p.displayName UTF8String]);
	result->Put("isfriend", p.isFriend == YES);
	return result;
}
