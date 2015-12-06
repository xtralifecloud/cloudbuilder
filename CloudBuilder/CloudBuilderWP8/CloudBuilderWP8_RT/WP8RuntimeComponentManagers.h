#ifndef __WP8RUNTIMECOMPONENTMANAGERS__
#define __WP8RUNTIMECOMPONENTMANAGERS__

#include "CloudBuilder.h"
#include "CNotificationManager.h"
#include "CUserManager.h"
#include "CClan.h"
#include "CGooglePlay.h"
#include "CHJSON.h"

class RuntimeNotificationManager : public CloudBuilder::CNotificationManager {
public:
	RuntimeNotificationManager(bool a, bool b, bool c) : CloudBuilder::CNotificationManager(a,b,c) {}

	void didRegisterDevice(CloudBuilder::eErrorCode aError);
	void didNotifyUser(CloudBuilder::eErrorCode aError, void *aReference);
	void didBeginLookingForNotification();
	void didEndLookingForNotification(int aPendingEvents);
	bool receivedMaintenanceNotification(const char *aKind, const CotCHelpers::CHJSON* aData);
};

class RuntimeLoginManager : public CloudBuilder::CUserManager {
public:
	void didRegisterAndLogin(CloudBuilder::eErrorCode aError);
	void didLogin(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aInfos);
	/*void didLoginWithFacebook(CloudBuilder::eErrorCode ec, const CotCHelpers::CHJSON* infos, const char *desc);
	void didLoginWithGooglePlus(CloudBuilder::eErrorCode ec, const CotCHelpers::CHJSON* infos, const char *desc);
	void didLoginWithGameCenter(CloudBuilder::eErrorCode ec, const CotCHelpers::CHJSON* infos, const char *desc);*/
	void didLogout(CloudBuilder::eErrorCode aError);
	bool receivedNotifyUser(const char *fromUserID, const CotCHelpers::CHJSON* data);
	void didRead(CloudBuilder::eErrorCode aError, const char* aKey, const char* aValue);
	void didWrite(CloudBuilder::eErrorCode aError, const char* aKey);
	/*void didPublishOnMyFacebookWall(CloudBuilder::eErrorCode aError);*/
    void didChangePassword(CloudBuilder::eErrorCode aError);
    void didMailPassword(CloudBuilder::eErrorCode aError);
	void didSetUserProfile(CloudBuilder::eErrorCode aError);
	void didGetUserProfile(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aData);
	/*void didLinkAccountWithFacebook(CloudBuilder::eErrorCode aError);
	void didLinkAccountWithGooglePlus(CloudBuilder::eErrorCode aError);
	void didLinkAccountWithGameCenter(CloudBuilder::eErrorCode aError);*/
    void didSetProperties(CloudBuilder::eErrorCode aError);
    void didGetProperties(CloudBuilder::eErrorCode aError, bool aCanBeFound, const CotCHelpers::CHJSON* aPropertiesList);
    /*void didSetAvatarSource(CloudBuilder::eErrorCode aError);*/
	void didCheckUser(CloudBuilder::eErrorCode aError, bool aExists);
	/*void didUnlink(CloudBuilder::eErrorCode aError);*/
};

class RuntimeGameManager : public CloudBuilder::CGameManager {
public:
	void didRead(CloudBuilder::eErrorCode aError, const char* aKey, const char* aValue);
	void didWrite(CloudBuilder::eErrorCode aError, const char* aKey);
	void didScore(CloudBuilder::eErrorCode aError);
	void didGetRank(CloudBuilder::eErrorCode aError, const char *aMode, long aRank);
	void didBestHighScore(CloudBuilder::eErrorCode aError, const char * aMode, const CotCHelpers::CHJSON *aJson);
	void didGetRankArray(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aRankArray);
	void didBestHighScoreArray(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayModes, const CotCHelpers::CHJSON *aScoreArray);
};

class RuntimeTribeManager : public CloudBuilder::CTribeManager {
public:
	void didListFriends(CloudBuilder::eErrorCode ec, const CotCHelpers::CHJSON* aArrayFriends);
	void didBlacklistFriends(CloudBuilder::eErrorCode ec, const CotCHelpers::CHJSON* aArrayFriends);
	void didListUsers(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aArrayUsers);
	void didChangeRelationshipStatus(CloudBuilder::eErrorCode aError, const char *aFriendPseudo, CloudBuilder::eRelationChange newState);
/*    void didListFacebookFriends(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aArrayFriends);
	void didListGooglePlusFriends(CloudBuilder::eErrorCode ec, const CotCHelpers::CHJSON* aArrayFriends);
    void didListGameCenterFriends(CloudBuilder::eErrorCode ec, const CotCHelpers::CHJSON* aArrayFriends);
	void didInviteFriendByMail(CloudBuilder::eErrorCode aError);
	void didInviteFriendByFBID(CloudBuilder::eErrorCode aError);
	void didInviteFriendByGooglePlusID(CloudBuilder::eErrorCode aError);*/
	void didFriendsBestHighScore(CloudBuilder::eErrorCode aError, const char *aMode, const CotCHelpers::CHJSON *aJson);
	void didFriendsBestHighScoreArray(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayModes, const CotCHelpers::CHJSON *aJson);
	bool relationshipHasChanged(const char *aFriendPseudo, CloudBuilder::eRelationChange aNewState);
	void didFindOpponents(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayPseudos);
};

class RuntimeMatchManager : public CloudBuilder::CMatchManager {
public:
    void didGetMatchData(CloudBuilder::eErrorCode aError, const char* aMatchID, const CotCHelpers::CHJSON* aMatchData);
    void didListMatch(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayMatch);
    void didListPendingMatch(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayMatch);
    void didCreateMatch(CloudBuilder::eErrorCode aError, const char* aMatchID);
    void didFindMatch(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayMatch);
    void didInviteFriends(CloudBuilder::eErrorCode aError);
    void didJoinMatch(CloudBuilder::eErrorCode aError);
    void didMatchMove(CloudBuilder::eErrorCode aError);
    bool playerDidChangeState(const char* aMatchID, const char* aPseudoID, CloudBuilder::eMatchStatus aStatus);
    bool matchReceiveData(const char* aMatchID, const char* aFromPseudoID, CloudBuilder::eMatchPhase aPhase, const CotCHelpers::CHJSON *aMatchState);
    void didRead(CloudBuilder::eErrorCode aError, const char* aMatchID, const char* aKey, const char* aValue);
    void didWrite(CloudBuilder::eErrorCode aError, const char* aMatchID, const char* aKey);
};

/*class UnityGooglePlay : public CloudBuilder::CGooglePlay {
public:
    void didSubmitScore(CloudBuilder::eErrorCode aError, int aGooglePlayServicesError, const char* aLeaderboardID);
    void didLoadLeaderboardMetadata(CloudBuilder::eErrorCode aError, int aGooglePlayServicesError, const CotCHelpers::CHJSON* aLeaderboardMetadata);
    void didLoadLeaderboardsMetadata(CloudBuilder::eErrorCode aError, int aGooglePlayServicesError, const CotCHelpers::CHJSON* aLeaderboardMetadata);
    void didLoadPlayerCenteredScores(CloudBuilder::eErrorCode aError, int aGooglePlayServicesError, const CotCHelpers::CHJSON* aLeaderboard, const CotCHelpers::CHJSON* aScores);
    void didLoadTopScores(CloudBuilder::eErrorCode aError, int aGooglePlayServicesError, const CotCHelpers::CHJSON* aLeaderboard, const CotCHelpers::CHJSON* aScores);
    void didIncrementAchievement(CloudBuilder::eErrorCode aError, int aGooglePlayServicesError, const char* aAchievementID, bool aUnlocked);
    void didLoadAchievements(CloudBuilder::eErrorCode aError, int aGooglePlayServicesError, const CotCHelpers::CHJSON* aAchievements);
    void didRevealAchievement(CloudBuilder::eErrorCode aError, int aGooglePlayServicesError, const char* aAchievementID);
    void didUnlockAchievement(CloudBuilder::eErrorCode aError, int aGooglePlayServicesError, const char* aAchievementID);
};
*/
class RuntimeClan : public CloudBuilder::CClan {
public:
	RuntimeClan();
	
	void didFinishSetup(CloudBuilder::eErrorCode aError);
	void didBatch(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aResults);
		
	RuntimeLoginManager *runtimeLogin;
	RuntimeGameManager *runtimeGame;
	RuntimeTribeManager *runtimeTribe;
	RuntimeMatchManager *runtimeMatch;
/*    UnityGooglePlay *unityGooglePlay;*/
};

extern RuntimeClan *gRuntimeClan;

#endif	// __WP8RUNTIMECOMPONENTMANAGERS__