//
//  Marmalade_Callbacks.h
//  
//
//  Created by Michael EL BAKI on 23/Sep/13.
//
//

#ifndef ____MARMALADE_CALLBACKS__
#define ____MARMALADE_CALLBACKS__

#include "CloudBuilderMarmalade.h"

extern void* gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_MAX];

void InitGlobalCotCCallbacks(void);

extern "C"
{
    void CNotification_receivedMaintenanceNotification_CotC(const char *aKind, const char* aJsonData);
    void CNotification_didBeginLookingForNotification_CotC(void);
    void CNotification_didEndLookingForNotification_CotC(int aPendingEvents);
    void CNotification_didRegisterDevice_CotC(int aErrorCode);
    
    void CClan_didSetup_CotC(int aErrorCode);
    void CClan_didBatchEnd_CotC(int aErrorCode, const char* aResults);
    
    void CUser_didRegisterAndLogin_CotC(int aErrorCode);
    void CUser_didLogin_CotC(int aErrorCode, const char* aJsonProfile);
    void CUser_didLoginWithFacebook_CotC(int aErrorCode, const char* aJsonProfile, const char* aDescription);
    void CUser_didLoginWithGooglePlus_CotC(int aErrorCode, const char* aJsonProfile, const char* aDescription);
    void CUser_didLoginWithGameCenter_CotC(int aErrorCode, const char* aJsonProfile, const char* aDescription);
    void CUser_didLogout_CotC(int aErrorCode);
    void CUser_didLinkAccountWithFacebook_CotC(int aErrorCode);
    void CUser_didLinkAccountWithGooglePlus_CotC(int aErrorCode);
    void CUser_didLinkAccountWithGameCenter_CotC(int aErrorCode);
    void CUser_didChangePassword_CotC(int aErrorCode);
    void CUser_didMailPassword_CotC(int aErrorCode);
    void CUser_didSetUserProfile_CotC(int aErrorCode);
    void CUser_didGetUserProfile_CotC(int aErrorCode, const char* aJsonProfile);
    void CUser_didPublishOnMyFacebookWall_CotC(int aErrorCode);
    void CUser_didReadBinary_CotC(int aErrorCode, const char *aKey, void *aPointer, unsigned long aLength);
    void CUser_didWriteBinary_CotC(int aErrorCode, const char* aKey, void* aPointer);
    void CUser_didRead_CotC(int aErrorCode, const char *aKey, const char* aValue);
    void CUser_didWrite_CotC(int aErrorCode, const char* aKey);
    void CUser_didSetProperties_CotC(int aErrorCode);
    void CUser_didGetProperties_CotC(int aErrorCode, bool aCanBeFound, const char* aJsonPropertiesList);
    void CUser_didCheckUser_CotC(int aErrorCode, bool aExists);
    void CUser_didSetAvatarSource_CotC(int aErrorCode);
    void CUser_receivedNotifyUser_CotC(const char* aFromuserID, const char* aJsonData);
    
    void CGame_didScore_CotC(int aErrorCode);
    void CGame_didGetRank_CotC(int aErrorCode, const char *aMode, long aRank);
    void CGame_didBestHighScore_CotC(int aErrorCode, const char *aMode, const char* aJson);
    void CGame_didCenteredScore_CotC(int aErrorCode, const char *aMode, const char* aJson);
    void CGame_didGetRankArray_CotC(int aErrorCode, const char* aJsonRankArray);
    void CGame_didBestHighScoreArray_CotC(int aErrorCode, const char* aJsonArrayModes, const char* aJsonScoreArray);
    void CGame_didReadBinary_CotC(int aErrorCode, const char *aKey, void *aPointer, unsigned long aLength);
    void CGame_didWriteBinary_CotC(int aErrorCode, const char* aKey, void* aPointer);
    void CGame_didRead_CotC(int aErrorCode, const char *aKey, const char* aValue);
    void CGame_didWrite_CotC(int aErrorCode, const char* aKey);
    
    void CTribe_didListUsers_CotC(int aErrorCode, const char* aJsonArrayUsers);
    void CTribe_didListGlobalFriends_CotC(int aErrorCode, const char* aJsonArrayFriends);
    void CTribe_didBlacklistGlobalFriends_CotC(int aErrorCode, const char* aJsonArrayFriends);
    void CTribe_didChangeGlobalRelationshipStatus_CotC(int aErrorCode, const char* aFriendPseudo, int aNewState);
    void CTribe_didListFriends_CotC(int aErrorCode, const char* aJsonArrayFriends);
    void CTribe_didBlacklistFriends_CotC(int aErrorCode, const char* aJsonArrayFriends);
    void CTribe_didChangeRelationshipStatus_CotC(int aErrorCode, const char* aFriendPseudo, int aNewState);
    void CTribe_didListFacebookFriends_CotC(int aErrorCode, const char* aJsonArrayFriends);
    void CTribe_didListGooglePlusFriends_CotC(int aErrorCode, const char* aJsonArrayFriends);
    void CTribe_didListGameCenterFriends_CotC(int aErrorCode, const char* aJsonArrayFriends);
    void CTribe_didInviteFriendByMail_CotC(int aErrorCode);
    void CTribe_didInviteFriendByFBID_CotC(int aErrorCode);
    void CTribe_didInviteFriendByGooglePlusID_CotC(int aErrorCode);
    void CTribe_didFriendsBestHighScore_CotC(int aErrorCode, const char *aMode, const char* aJson);
    void CTribe_didFriendsBestHighScoreArray_CotC(int aErrorCode, const char* aJsonArrayModes, const char* aJson);
    void CTribe_didFindOpponents_CotC(int aErrorCode, const char* aJsonArrayPseudo);
    void CTribe_relationshipHasChanged_CotC(const char* aFriendPseudo, int aNewState);
    
    void CMatch_didGetMatchData_CotC(int aErrorCode, const char* aMatchID, const char* aJsonMatchData);
    void CMatch_didListMatch_CotC(int aErrorCode, const char* aJsonArrayMatch);
    void CMatch_didListPendingMatch_CotC(int aErrorCode, const char* aJsonArrayMatch);
    void CMatch_didCreateMatch_CotC(int aErrorCode, const char* aMatchID);
    void CMatch_didInviteFriends_CotC(int aErrorCode);
    void CMatch_didJoinMatch_CotC(int aErrorCode);
    void CMatch_didMatchMove_CotC(int aErrorCode);
    void CMatch_didReadBinary_CotC(int aErrorCode, const char* aMatchID, const char* aKey, void* aPointer, unsigned long aLength);
    void CMatch_didWriteBinary_CotC(int aErrorCode, const char* aMatchID, const char* aKey, void* aPointer);
    void CMatch_didRead_CotC(int aErrorCode, const char* aMatchID, const char* aKey, const char* aValue);
    void CMatch_didWrite_CotC(int aErrorCode, const char* aMatchID, const char* aKey);
    void CMatch_playerDidChangeState_CotC(const char* aMatchID, const char* aPseudoID, int aStatus);
    void CMatch_matchReceiveData_CotC(const char* aMatchID, const char* aFromPseudoID, int aPhase, const char* aJsonMatchState);
    
    void CGGoglePlay_didLoadPeople_CotC(int aErrorCode, const char* aJsonListDetails);
    void CGGoglePlay_didSubmitScore_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aLeaderboardID);
    void CGGoglePlay_didLoadLeaderboardMetadata_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aJsonLeaderboardMetadata);
    void CGGoglePlay_didLoadLeaderboardsMetadata_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aJsonLeaderboardMetadata);
    void CGGoglePlay_didLoadPlayerCenteredScores_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aJsonLeaderboard, const char* aJsonScores);
    void CGGoglePlay_didLoadTopScores_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aJsonLeaderboard, const char* aJsonScores);
    void CGGoglePlay_didIncrementAchievement_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aAchievementID, bool aUnlocked);
    void CGGoglePlay_didLoadAchievements_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aJsonAchievements);
    void CGGoglePlay_didRevealAchievement_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aAchievementID);
    void CGGoglePlay_didUnlockAchievement_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aAchievementID);
}

#endif //   ____MARMALADE_CALLBACKS__
