//
//  MarmaladeWrapper.h
//  CloudBuilderMarmalade_iphone
//
//  Created by Michael EL BAKI on 7/28/13.
//
//

#ifndef CloudBuilderMarmalade_iphone_MarmaladeWrapper_h
#define CloudBuilderMarmalade_iphone_MarmaladeWrapper_h

#include "CNotificationManager.h"
#include "CUserManager.h"
#include "CClan.h"
#include "CGooglePlay.h"

class MarmaladeNotificationManager : public CloudBuilder::CNotificationManager {
public:
	MarmaladeNotificationManager(bool aPopNextCallback = true, bool aHandleAdminEvent = false,
                                 bool aHasSpecificEvent = false);

    void didNotifyUser(CloudBuilder::eErrorCode aError, void *aReference);

	bool receivedMaintenanceNotification(const char *aKind, const CotCHelpers::CHJSON* aData);
	void didBeginLookingForNotification();
	void didEndLookingForNotification(int pendingEvents);
	void didRegisterDevice(CloudBuilder::eErrorCode error);
};

class MarmaladeLoginManager : public CloudBuilder::CUserManager {
public:
	void didRegisterAndLogin(CloudBuilder::eErrorCode aError);
	void didLogin(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aJsonProfile);
	void didLoginWithFacebook(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aJsonProfile, const char *aDesc);
	void didLoginWithGooglePlus(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aJsonProfile, const char *aDesc);
	void didLoginWithGameCenter(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aJsonProfile, const char *aDesc);
	void didLogout(CloudBuilder::eErrorCode aError);
	void didLinkAccountWithFacebook(CloudBuilder::eErrorCode aError);
	void didLinkAccountWithGooglePlus(CloudBuilder::eErrorCode aError);
	void didLinkAccountWithGameCenter(CloudBuilder::eErrorCode aError);
    void didChangePassword(CloudBuilder::eErrorCode aError);
    void didMailPassword(CloudBuilder::eErrorCode aError);
	void didSetUserProfile(CloudBuilder::eErrorCode aError);
	void didGetUserProfile(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aData);
	void didPublishOnMyFacebookWall(CloudBuilder::eErrorCode aError);
    void didReadBinary(CloudBuilder::eErrorCode aError, const char* aKey, void* aPointer, unsigned long aLength);
    void didWriteBinary(CloudBuilder::eErrorCode aError, const char* aKey, void* aPointer);
    void didRead(CloudBuilder::eErrorCode aError, const char* aKey, const char* aValue);
	void didWrite(CloudBuilder::eErrorCode aError, const char* aKey);
    void didSetProperties(CloudBuilder::eErrorCode aError);
    void didGetProperties(CloudBuilder::eErrorCode aError, bool aCanBeFound, const CotCHelpers::CHJSON* aPropertiesList);
    void didCheckUser(CloudBuilder::eErrorCode aError, bool aExists);
    void didSetAvatarSource(CloudBuilder::eErrorCode aError);

	bool receivedNotifyUser(const char *aFromUserID, const CotCHelpers::CHJSON* aData);
};

class MarmaladeGameManager : public CloudBuilder::CGameManager {
public:
	void didScore(CloudBuilder::eErrorCode aError);
	void didBestHighScore(CloudBuilder::eErrorCode aError, const char * aMode, const CotCHelpers::CHJSON *aJson);
	void didCenteredScore(CloudBuilder::eErrorCode aError, const char * aMode, const CotCHelpers::CHJSON *aJson);
	void didGetRank(CloudBuilder::eErrorCode aError, const char *aMode, long aRank);
	void didBestHighScoreArray(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayModes, const CotCHelpers::CHJSON *aScoreArray);
	void didGetRankArray(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aRankArray);
    void didReadBinary(CloudBuilder::eErrorCode aError, const char* aKey, void* aPointer, unsigned long aLength);
    void didWriteBinary(CloudBuilder::eErrorCode aError, const char* aKey, void* aPointer);
	void didRead(CloudBuilder::eErrorCode aError, const char* aKey, const char* value);
	void didWrite(CloudBuilder::eErrorCode aError, const char* aKey);
};

class MarmaladeTribeManager : public CloudBuilder::CTribeManager {
public:
	void didListUsers(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aArrayUsers);
	void didListGlobalFriends(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aArrayFriends);
    void didBlacklistGlobalFriends(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aArrayFriends);
    void didChangeGlobalRelationshipStatus(CloudBuilder::eErrorCode aError, const char *aFriendPseudo, CloudBuilder::eRelationChange aNewState);
    void didListFriends(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aArrayFriends);
	void didBlacklistFriends(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aArrayFriends);
	void didChangeRelationshipStatus(CloudBuilder::eErrorCode aError, const char *aFriendPseudo, CloudBuilder::eRelationChange aNewState);
    void didListFacebookFriends(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aArrayFriends);
	void didListGooglePlusFriends(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aArrayFriends);
	void didListGameCenterFriends(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aArrayFriends);
	void didInviteFriendByMail(CloudBuilder::eErrorCode aError);
	void didInviteFriendByFBID(CloudBuilder::eErrorCode aError);
	void didInviteFriendByGooglePlusID(CloudBuilder::eErrorCode aError);
	void didFriendsBestHighScore(CloudBuilder::eErrorCode aError, const char *aMode, const CotCHelpers::CHJSON *aJson);
	void didFriendsBestHighScoreArray(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *arrayModes, const CotCHelpers::CHJSON *aJson);
    void didFindOpponents(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aArrayPseudo);
    
	bool relationshipHasChanged(const char *aFriendPseudo, CloudBuilder::eRelationChange aNewState);
};

class MarmaladeMatchManager : public CloudBuilder::CMatchManager {
public:
    void didGetMatchData(CloudBuilder::eErrorCode aError, const char* aMatchID, const CotCHelpers::CHJSON* aMatchData);
    void didListMatch(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayMatch);
    void didListPendingMatch(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aArrayMatch);
    void didCreateMatch(CloudBuilder::eErrorCode aError, const char* aMatchID);
    void didInviteFriends(CloudBuilder::eErrorCode aError);
    void didJoinMatch(CloudBuilder::eErrorCode aError);
    void didMatchMove(CloudBuilder::eErrorCode aError);
    void didReadBinary(CloudBuilder::eErrorCode aError, const char* aMatchID, const char* aKey, void* aPointer, unsigned long aLength);
    void didWriteBinary(CloudBuilder::eErrorCode aError, const char* aMatchID, const char* aKey, void* aPointer);
    void didRead(CloudBuilder::eErrorCode aError, const char* aMatchID, const char* aKey, const char* aValue);
    void didWrite(CloudBuilder::eErrorCode aError, const char* aMatchID, const char* aKey);
    
    bool playerDidChangeState(const char* aMatchID, const char* aPseudoID, CloudBuilder::eMatchStatus aStatus);
    bool matchReceiveData(const char* aMatchID, const char* aFromPseudoID, CloudBuilder::eMatchPhase aPhase, const CotCHelpers::CHJSON *aMatchState);
};

class MarmaladeGooglePlay : public CloudBuilder::CGooglePlay {
public:
    void didLoadPeople(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON* aListDetails);
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

class MarmaladeClan : public CloudBuilder::CClan {
public:
	MarmaladeClan();
	
	void didFinishSetup(CloudBuilder::eErrorCode aError);
    void didBatchEnd(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aResults);
    
	MarmaladeLoginManager *mMarmaladeLogin;
	MarmaladeGameManager *mMarmaladeGame;
	MarmaladeTribeManager *mMarmaladeTribe;
    MarmaladeMatchManager *mMarmaladeMatch;
    MarmaladeGooglePlay *mMarmaladeGooglePlay;
};

extern MarmaladeClan* gMarmaladeClan;

#endif
