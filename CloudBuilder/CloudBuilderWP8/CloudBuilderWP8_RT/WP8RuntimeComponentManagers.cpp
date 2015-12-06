#include "WP8RuntimeComponentManagers.h"

#include <malloc.h>
#include <string.h>

#include "CNotificationManagerRuntime.h"
#include "CClanRuntime.h"
#include "CUserManagerRuntime.h"
#include "CTribeManagerRuntime.h"
#include "CMatchManagerRuntime.h"
#include "CGameManagerRuntime.h"
#include "RuntimeComponentHelper.h"

using namespace Platform;

using namespace CloudBuilder;
using namespace CotCHelpers;

extern CloudBuilderWP8_RT::receivedMaintenanceNotificationDelegate^ gReceivedMaintenanceNotification;

extern CloudBuilderWP8_RT::didNotificationNotifyUserDelegate^ gDidNotificationNotifyUser;

void RuntimeNotificationManager::didNotifyUser(CloudBuilder::eErrorCode aError, void *aReference)
{
	gDidNotificationNotifyUser((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC((const char *) aReference));
}

void RuntimeNotificationManager::didRegisterDevice(eErrorCode ec)
{
//	RETURNERROR("didRegisterDevice")
}

void RuntimeNotificationManager::didBeginLookingForNotification()
{
//	UnitySendMessage("CloudBuilder", "didBeginLookingForNotification", "");
}

void RuntimeNotificationManager::didEndLookingForNotification(int pendingEvents)
{
/*	char pending[10];
	sprintf(pending, "%d", pendingEvents);
	UnitySendMessage("CloudBuilder", "didEndLookingForNotification", pending);*/
}

bool RuntimeNotificationManager::receivedMaintenanceNotification(const char *aKind, const CHJSON* aData)
{
	if(gReceivedMaintenanceNotification != nullptr)
	{
		const char* dataStr;

		dataStr = aData ? aData->print() : _strdup("");
		gReceivedMaintenanceNotification(RuntimeStringFromC(aKind), RuntimeStringFromC(dataStr));
		free((void *) dataStr);
	}

	return true;
}

RuntimeClan *gRuntimeClan = NULL;

extern CloudBuilderWP8_RT::didClanSetupDelegate^ gDidClanSetup;
extern CloudBuilderWP8_RT::didClanBatchDelegate^ gDidClanBatch;

RuntimeClan::RuntimeClan() : CClan(new RuntimeNotificationManager(true, true, true))
{
	gRuntimeClan = this;
	
	runtimeLogin = new RuntimeLoginManager();
	CNotificationManager::Instance()->SetUserDelegate(runtimeLogin);

	runtimeGame = new RuntimeGameManager();
	CNotificationManager::Instance()->SetGameDelegate(runtimeGame);
	
	runtimeTribe = new RuntimeTribeManager();
	CNotificationManager::Instance()->SetTribeDelegate(runtimeTribe);
	
	runtimeMatch = new RuntimeMatchManager();
	CNotificationManager::Instance()->SetMatchDelegate(runtimeMatch);

/*	unityGooglePlay = new UnityGooglePlay();*/
}

void RuntimeClan::didFinishSetup(eErrorCode aError)
{
	gDidClanSetup((CloudBuilderWP8_RT::eErrorCode) aError);
}

void RuntimeClan::didBatch(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aResults)
{
	const char* resultsStr;

	resultsStr = aResults ? aResults->print() : _strdup("");
	gDidClanBatch((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(resultsStr));
	free((void *) resultsStr);
}

extern CloudBuilderWP8_RT::receivedNotifyUserDelegate^ gReceivedNotifyUser;

extern CloudBuilderWP8_RT::didUserRegisterAndLoginDelegate^ gDidUserRegisterAndLogin;
extern CloudBuilderWP8_RT::didUserLoginDelegate^ gDidUserLogin;
extern CloudBuilderWP8_RT::didUserLogoutDelegate^ gDidUserLogout;
extern CloudBuilderWP8_RT::didUserReadDelegate^ gDidUserRead;
extern CloudBuilderWP8_RT::didUserWriteDelegate^ gDidUserWrite;
extern CloudBuilderWP8_RT::didUserChangePasswordDelegate^ gDidUserChangePassword;
extern CloudBuilderWP8_RT::didUserMailPasswordDelegate^ gDidUserMailPassword;
extern CloudBuilderWP8_RT::didUserGetProfileDelegate^ gDidUserGetProfile;
extern CloudBuilderWP8_RT::didUserSetProfileDelegate^ gDidUserSetProfile;
extern CloudBuilderWP8_RT::didUserGetPropertiesDelegate^ gDidUserGetProperties;
extern CloudBuilderWP8_RT::didUserSetPropertiesDelegate^ gDidUserSetProperties;
extern CloudBuilderWP8_RT::didUserCheckUserDelegate^ gDidUserCheckUser;

bool RuntimeLoginManager::receivedNotifyUser(const char *aFromUserID, const CotCHelpers::CHJSON* aData)
{
	if(gReceivedNotifyUser != nullptr)
	{
		const char* dataStr;

		dataStr = aData ? aData->print() : _strdup("");
		gReceivedNotifyUser(RuntimeStringFromC(aFromUserID), RuntimeStringFromC(dataStr));
		free((void *) dataStr);
	}

	return true;
}

void RuntimeLoginManager::didRegisterAndLogin(eErrorCode aError)
{
	gDidUserRegisterAndLogin((CloudBuilderWP8_RT::eErrorCode) aError);
}

void RuntimeLoginManager::didLogin(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aInfos)
{
	const char* infosStr;

	infosStr = aInfos ? aInfos->print() : _strdup("");
	gDidUserLogin((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(infosStr));
	free((void *) infosStr);
}

void RuntimeLoginManager::didLogout(eErrorCode aError)
{
	gDidUserLogout((CloudBuilderWP8_RT::eErrorCode) aError);
}

void RuntimeLoginManager::didRead(eErrorCode aError, const char* aKey, const char* aValue)
{
	gDidUserRead((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aKey), RuntimeStringFromC(aValue));
}

void RuntimeLoginManager::didWrite(eErrorCode aError, const char* aKey)
{
	gDidUserWrite((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aKey));
}

void RuntimeLoginManager::didChangePassword(eErrorCode aError)
{
	gDidUserChangePassword((CloudBuilderWP8_RT::eErrorCode) aError);
}

void RuntimeLoginManager::didMailPassword(eErrorCode aError)
{
	gDidUserMailPassword((CloudBuilderWP8_RT::eErrorCode) aError);
}

void RuntimeLoginManager::didSetUserProfile(CloudBuilder::eErrorCode aError)
{
	gDidUserSetProfile((CloudBuilderWP8_RT::eErrorCode) aError);
}

void RuntimeLoginManager::didGetUserProfile(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aData)
{
	const char* profileStr;

	profileStr = aData ? aData->print() : _strdup("");
	gDidUserGetProfile((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(profileStr));
	free((void *) profileStr);
}

void RuntimeLoginManager::didSetProperties(CloudBuilder::eErrorCode aError)
{
	gDidUserSetProperties((CloudBuilderWP8_RT::eErrorCode) aError);
}

void RuntimeLoginManager::didGetProperties(CloudBuilder::eErrorCode aError, bool aCanBeFound, const CotCHelpers::CHJSON* aPropertiesList)
{
	const char* propertiesStr;

	propertiesStr = aPropertiesList ? aPropertiesList->print() : _strdup("");
	gDidUserGetProperties((CloudBuilderWP8_RT::eErrorCode) aError, aCanBeFound, RuntimeStringFromC(propertiesStr));
	free((void *) propertiesStr);
}

void RuntimeLoginManager::didCheckUser(CloudBuilder::eErrorCode aError, bool aExists)
{
	gDidUserCheckUser((CloudBuilderWP8_RT::eErrorCode) aError, aExists);
}

extern CloudBuilderWP8_RT::relationshipHasChangedDelegate^ gRelationshipHasChanged;

extern CloudBuilderWP8_RT::didTribeListUsersDelegate^ gDidTribeListUsers;
extern CloudBuilderWP8_RT::didTribeListFriendsDelegate^ gDidTribeListFriends;
extern CloudBuilderWP8_RT::didTribeBlacklistFriendsDelegate^ gDidTribeBlacklistFriends;
extern CloudBuilderWP8_RT::didTribeChangeRelationshipStatusDelegate^ gDidTribeChangeRelationshipStatus;
extern CloudBuilderWP8_RT::didTribeFriendsBestHighScoreDelegate^ gDidTribeFriendsBestHighScore;
extern CloudBuilderWP8_RT::didTribeFriendsBestHighScoreArrayDelegate^ gDidTribeFriendsBestHighScoreArray;
extern CloudBuilderWP8_RT::didTribeFindOpponentsDelegate^ gDidTribeFindOpponents;

bool RuntimeTribeManager::relationshipHasChanged(const char *aFriendPseudo, CloudBuilder::eRelationChange aNewState)
{
	if(gRelationshipHasChanged != nullptr)
		gRelationshipHasChanged(RuntimeStringFromC(aFriendPseudo), (CloudBuilderWP8_RT::eRelationChange) aNewState);

	return true;
}

void RuntimeTribeManager::didListUsers(eErrorCode aError, const CHJSON* aArrayUsers)
{
	const char* usersStr;

	usersStr = aArrayUsers ? aArrayUsers->print() : _strdup("");
	gDidTribeListUsers((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(usersStr));
	free((void *) usersStr);
}

void RuntimeTribeManager::didListFriends(eErrorCode aError, const CHJSON* aArrayFriends)
{
	const char* friendsStr;

	friendsStr = aArrayFriends ? aArrayFriends->print() : _strdup("");
	gDidTribeListFriends((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(friendsStr));
	free((void *) friendsStr);
}

void RuntimeTribeManager::didBlacklistFriends(eErrorCode aError, const CHJSON* aArrayFriends)
{
	const char* friendsStr;

	friendsStr = aArrayFriends ? aArrayFriends->print() : _strdup("");
	gDidTribeBlacklistFriends((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(friendsStr));
	free((void *) friendsStr);
}

void RuntimeTribeManager::didChangeRelationshipStatus(CloudBuilder::eErrorCode aError, const char *aFriendPseudo, CloudBuilder::eRelationChange newState)
{
	gDidTribeChangeRelationshipStatus((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aFriendPseudo), (CloudBuilderWP8_RT::eRelationChange) newState);
}

void RuntimeTribeManager::didFriendsBestHighScore(eErrorCode aError, const char *aMode, const CotCHelpers::CHJSON *aJson)
{
	const char* scoresStr;

	scoresStr = aJson ? aJson->print() : _strdup("");
	gDidTribeFriendsBestHighScore((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aMode), RuntimeStringFromC(scoresStr));
	free((void *) scoresStr);
}

void RuntimeTribeManager::didFriendsBestHighScoreArray(eErrorCode aError, const CotCHelpers::CHJSON *aArrayModes, const CotCHelpers::CHJSON *aJson)
{
	const char* scoresStr;
	const char* arrayModesStr;

	scoresStr		= aJson ? aJson->print() : _strdup("");
	arrayModesStr = aJson ? aJson->print() : _strdup("");
	gDidTribeFriendsBestHighScoreArray((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(arrayModesStr), RuntimeStringFromC(scoresStr));
	free((void *) scoresStr);
	free((void *) arrayModesStr);
}

void RuntimeTribeManager::didFindOpponents(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayPseudos)
{
	const char* arrayPseudosStr;

	arrayPseudosStr		= aArrayPseudos ? aArrayPseudos->print() : _strdup("");
	gDidTribeFindOpponents((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(arrayPseudosStr));
	free((void *) arrayPseudosStr);
}

extern CloudBuilderWP8_RT::playerDidChangeStateDelegate^ gPlayerDidChangeState;
extern CloudBuilderWP8_RT::matchReceiveDataDelegate^ gMatchReceiveData;

extern CloudBuilderWP8_RT::didMatchGetMatchDataDelegate^ gDidMatchGetData;
extern CloudBuilderWP8_RT::didMatchListMatchDelegate^ gDidMatchListMatch;
extern CloudBuilderWP8_RT::didMatchListPendingMatchDelegate^ gDidMatchListPendingMatch;
extern CloudBuilderWP8_RT::didMatchCreateMatchDelegate^ gDidMatchCreateMatch;
extern CloudBuilderWP8_RT::didMatchFindMatchDelegate^ gDidMatchFindMatch;
extern CloudBuilderWP8_RT::didMatchInviteFriendsDelegate^ gDidMatchInviteFriends;
extern CloudBuilderWP8_RT::didMatchJoinMatchDelegate^ gDidMatchJoinMatch;
extern CloudBuilderWP8_RT::didMatchMoveDelegate^ gDidMatchMove;
extern CloudBuilderWP8_RT::didMatchReadDelegate^ gDidMatchRead;
extern CloudBuilderWP8_RT::didMatchWriteDelegate^ gDidMatchWrite;

bool RuntimeMatchManager::playerDidChangeState(const char* aMatchID, const char* aPseudoID, CloudBuilder::eMatchStatus aStatus)
{
	if(gPlayerDidChangeState != nullptr)
		gPlayerDidChangeState(RuntimeStringFromC(aMatchID), RuntimeStringFromC(aPseudoID), (CloudBuilderWP8_RT::eMatchStatus) aStatus);

	return true;
}

bool RuntimeMatchManager::matchReceiveData(const char* aMatchID, const char* aFromPseudoID, CloudBuilder::eMatchPhase aPhase, const CotCHelpers::CHJSON *aMatchState)
{
	if(gMatchReceiveData != nullptr)
	{
		char* matchStateStr;

		matchStateStr = aMatchState ? aMatchState->print() : _strdup("");
		gMatchReceiveData(RuntimeStringFromC(aMatchID), RuntimeStringFromC(aFromPseudoID), (CloudBuilderWP8_RT::eMatchPhase) aPhase, RuntimeStringFromC(matchStateStr));
		free(matchStateStr);
	}
	return true;
}

void RuntimeMatchManager::didGetMatchData(CloudBuilder::eErrorCode aError, const char* aMatchID, const CotCHelpers::CHJSON* aMatchData)
{
	const char* matchDataStr;

	matchDataStr		= aMatchData ? aMatchData->print() : _strdup("");
	gDidMatchGetData((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aMatchID), RuntimeStringFromC(matchDataStr));
	free((void *) matchDataStr);
}

void RuntimeMatchManager::didListMatch(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayMatch)
{
	const char* arrayMatchStr;

	arrayMatchStr		= aArrayMatch ? aArrayMatch->print() : _strdup("");
	gDidMatchListMatch((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(arrayMatchStr));
	free((void *) arrayMatchStr);
}

void RuntimeMatchManager::didListPendingMatch(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayMatch)
{
	const char* arrayMatchStr;

	arrayMatchStr		= aArrayMatch ? aArrayMatch->print() : _strdup("");
	gDidMatchListPendingMatch((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(arrayMatchStr));
	free((void *) arrayMatchStr);
}

void RuntimeMatchManager::didCreateMatch(CloudBuilder::eErrorCode aError, const char* aMatchID)
{
	gDidMatchCreateMatch((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aMatchID));
}

void RuntimeMatchManager::didFindMatch(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayMatch)
{
	const char* arrayMatchStr;

	arrayMatchStr		= aArrayMatch ? aArrayMatch->print() : _strdup("");
	gDidMatchFindMatch((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(arrayMatchStr));
	free((void *) arrayMatchStr);
}

void RuntimeMatchManager::didInviteFriends(CloudBuilder::eErrorCode aError)
{
	gDidMatchInviteFriends((CloudBuilderWP8_RT::eErrorCode) aError);
}

void RuntimeMatchManager::didJoinMatch(CloudBuilder::eErrorCode aError)
{
	gDidMatchJoinMatch((CloudBuilderWP8_RT::eErrorCode) aError);
}

void RuntimeMatchManager::didMatchMove(CloudBuilder::eErrorCode aError)
{
	gDidMatchMove((CloudBuilderWP8_RT::eErrorCode) aError);
}

void RuntimeMatchManager::didRead(CloudBuilder::eErrorCode aError, const char* aMatchID, const char* aKey, const char* aValue)
{
	gDidMatchRead((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aMatchID), RuntimeStringFromC(aKey), RuntimeStringFromC(aValue));
}

void RuntimeMatchManager::didWrite(CloudBuilder::eErrorCode aError, const char* aMatchID, const char* aKey)
{
	gDidMatchWrite((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aMatchID), RuntimeStringFromC(aKey));
}

extern CloudBuilderWP8_RT::didGameScoreDelegate^ gDidGameScore;
extern CloudBuilderWP8_RT::didGameGetRankDelegate^ gDidGameGetRank;
extern CloudBuilderWP8_RT::didGameBestHighScoreDelegate^ gDidGameBestHighScore;
extern CloudBuilderWP8_RT::didGameGetRankArrayDelegate^ gDidGameGetRankArray;
extern CloudBuilderWP8_RT::didGameBestHighScoreArrayDelegate^ gDidGameBestHighScoreArray;
extern CloudBuilderWP8_RT::didGameReadDelegate^ gDidGameRead;
extern CloudBuilderWP8_RT::didGameWriteDelegate^ gDidGameWrite;

void RuntimeGameManager::didRead(CloudBuilder::eErrorCode aError, const char* aKey, const char* aValue)
{
	gDidGameRead((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aKey), RuntimeStringFromC(aValue));
}

void RuntimeGameManager::didWrite(CloudBuilder::eErrorCode aError, const char* aKey)
{
	gDidGameWrite((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aKey));
}

void RuntimeGameManager::didScore(CloudBuilder::eErrorCode aError)
{
	gDidGameScore((CloudBuilderWP8_RT::eErrorCode) aError);
}

void RuntimeGameManager::didGetRank(CloudBuilder::eErrorCode aError, const char *aMode, long aRank)
{
	gDidGameGetRank((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aMode), aRank);
}

void RuntimeGameManager::didBestHighScore(CloudBuilder::eErrorCode aError, const char * aMode, const CotCHelpers::CHJSON *aJson)
{
	const char* highScoreStr;

	highScoreStr	= aJson ? aJson->print() : _strdup("");
	gDidGameBestHighScore((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(aMode), RuntimeStringFromC(highScoreStr));
	free((void *) highScoreStr);
}

void RuntimeGameManager::didGetRankArray(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aRankArray)
{
	const char* rankArrayStr;

	rankArrayStr	= aRankArray ? aRankArray->print() : _strdup("");
	gDidGameGetRankArray((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(rankArrayStr));
	free((void *) rankArrayStr);
}

void RuntimeGameManager::didBestHighScoreArray(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayModes, const CotCHelpers::CHJSON *aScoreArray)
{
	const char* arrayModesStr;
	const char* arrayScoresStr;

	arrayModesStr	= aArrayModes ? aArrayModes->print() : _strdup("");
	arrayScoresStr	= aScoreArray ? aScoreArray->print() : _strdup("");
	gDidGameBestHighScoreArray((CloudBuilderWP8_RT::eErrorCode) aError, RuntimeStringFromC(arrayModesStr), RuntimeStringFromC(arrayScoresStr));
	free((void *) arrayModesStr);
	free((void *) arrayScoresStr);
}
