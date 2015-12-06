/*
 * Internal header for the CloudBuilderMarmalade extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef CLOUDBUILDERMARMALADE_INTERNAL_H
#define CLOUDBUILDERMARMALADE_INTERNAL_H

#include "s3eTypes.h"
#include "CloudBuilderMarmalade.h"
#include "CloudBuilderMarmalade_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult CloudBuilderMarmaladeInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult CloudBuilderMarmaladeInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void CloudBuilderMarmaladeTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void CloudBuilderMarmaladeTerminate_platform();
void** CloudBuilder_Init_platform(void** aCotCFunctions);

void CloudBuilder_SetGlobalCotCCallback_platform(CloudBuilderMarmaladeCallback aIndex, s3eCallback aCallback, void* aUserData);

void CloudBuilder_PopCallback_platform();

s3eResult Clan_Setup_platform(const char* aConfigurationJson, s3eCallback aClan_didSetup, void* aUserData);

s3eResult Clan_BatchBegin_platform();

s3eResult Clan_BatchEnd_platform(s3eCallback aClan_didBatchEnd, void* aUserData);

bool Clan_isSetup_platform();

bool Clan_isUserLogged_platform();

s3eResult User_RegisterAndLogin_platform(const char* aEmail, const char* aPassword, const char* aPseudo, s3eCallback aUser_didRegisterAndLogin, void* aUserData);

s3eResult User_Login_platform(const char* aPseudo, const char* aPassword, s3eCallback aUser_didLogin, void* aUserData);

s3eResult User_LoginWithFacebook_platform(const char* aOptionalPassword, s3eCallback aUser_didLoginWithFacebook, void* aUserData);

s3eResult User_LoginWithGooglePlus_platform(const char* aOptionalPassword, s3eCallback aUser_didLoginWithGooglePlus, void* aUserData);

s3eResult User_LoginWithGameCenter_platform(s3eCallback aUser_didLoginWithGameCenter, void* aUserData);

s3eResult User_Logout_platform(s3eCallback aUser_didLogout, void* aUserData);

s3eResult User_LinkAccountWithFacebook_platform(s3eCallback aUser_didLinkAccountWithFacebook, void* aUserData);

s3eResult User_LinkAccountWithGooglePlus_platform(s3eCallback aUser_didLinkAccountWithGooglePlus, void* aUserData);

s3eResult User_LinkAccountWithGameCenter_platform(s3eCallback aUser_didLinkAccountWithGameCenter, void* aUserData);

s3eResult User_ChangePassword_platform(const char* aOldPassword, const char* aNewPassword, s3eCallback aUser_didChangePassword, void* aUserData);

s3eResult User_MailPassword_platform(const char* aEmail, const char* aSubject, const char* aBody, s3eCallback aUser_didMailPassword, void* aUserData);

s3eResult User_SetUserProfile_platform(const char* aJson, s3eCallback aUser_didSetUserProfile, void* aUserData);

s3eResult User_GetUserProfile_platform(s3eCallback aUser_didGetUserProfile, void* aUserData);

const char* User_GetPseudo_platform();

const char* User_GetMail_platform();

s3eResult User_PublishOnMyFacebookWall_platform(const char* aMessage, s3eCallback aUser_didPublishOnMyFacebookWall, void* aUserData);

s3eResult User_ReadBinary_platform(const char* aKey, s3eCallback aUser_didReadBinary, void* aUserData);

s3eResult User_WriteBinary_platform(const char* aKey, void* aPointer, unsigned long aLength, s3eCallback aUser_didWriteBinary, void* aUserData);

s3eResult User_Read_platform(const char* aKey, s3eCallback aUser_didRead, void* aUserData);

s3eResult User_Write_platform(const char* aKey, const char* aValue, s3eCallback aUser_didWrite, void* aUserData);

s3eResult User_SetProperties_platform(bool aCanBeFound, const char* aPropertiesJson, s3eCallback aUser_didSetProperties, void* aUserData);

s3eResult User_GetProperties_platform(s3eCallback aUser_didGetProperties, void* aUserData);

s3eResult User_CheckUser_platform(const char* aIdent, s3eCallback aUser_didCheckUser, void* aUserData);

s3eResult User_SetAvatarSource_platform(cbmExternalNetwork aSource, s3eCallback aUser_didSetAvatarSource, void* aUserData);

s3eResult Game_Score_platform(long long aHighScore, const char* aMode, cbmScoreType aScoreType, const char* aInfoScore, bool aMayVary, s3eCallback aGame_didScore, void* aUserData);

s3eResult Game_GetRank_platform(long long aHighScore, const char* aMode, cbmScoreType aScoreType, s3eCallback aGame_didGetRank, void* aUserData);

s3eResult Game_BestHighScore_platform(int aCount, const char* aMode, cbmScoreType aScoreType, s3eCallback aGame_didBestHighScore, void* aUserData);

s3eResult Game_CenteredScore_platform(int aCount, const char* aMode, cbmScoreType aScoreType, s3eCallback aGame_didCenteredScore, void* aUserData);

s3eResult Game_GetRankArray_platform(const char* aScoreArrayJson, cbmScoreType aScoreType, s3eCallback aGame_didGetRankArray, void* aUserData);

s3eResult Game_BestHighScoreArray_platform(int aCount, const char* aArrayModesJson, cbmScoreType aScoreType, s3eCallback aGame_didBestHighScoreArray, void* aUserData);

s3eResult Game_ReadBinary_platform(const char* aKey, s3eCallback aGame_didReadBinary, void* aUserData);

s3eResult Game_WriteBinary_platform(const char* aKey, void* aPointer, unsigned long aLength, s3eCallback aGame_didWriteBinary, void* aUserData);

s3eResult Game_Read_platform(const char* aKey, s3eCallback aGame_didRead, void* aUserData);

s3eResult Game_Write_platform(const char* aKey, const char* aValue, s3eCallback aGame_didWrite, void* aUserData);

s3eResult Tribe_ListUsers_platform(const char* aContainsString, s3eCallback aTribe_didListUsers, void* aUserData);

s3eResult Tribe_ListGlobalFriends_platform(s3eCallback aTribe_didListGlobalFriends, void* aUserData);

s3eResult Tribe_BlacklistGlobalFriends_platform(s3eCallback aTribe_didBlacklistGlobalFriends, void* aUserData);

s3eResult Tribe_ChangeGlobalRelationshipStatus_platform(const char* aFriendPseudo, cbmRelationChange aNewState, s3eCallback aTribe_didChangeGlobalRelationshipStatus, void* aUserData);

s3eResult Tribe_ListFriends_platform(s3eCallback aTribe_didListFriends, void* aUserData);

s3eResult Tribe_BlacklistFriends_platform(s3eCallback aTribe_didBlacklistFriends, void* aUserData);

s3eResult Tribe_ChangeRelationshipStatus_platform(const char* aFriendPseudo, cbmRelationChange aNewState, s3eCallback aTribe_didChangeRelationshipStatus, void* aUserData);

s3eResult Tribe_ListFacebookFriends_platform(s3eCallback aTribe_didListFacebookFriends, void* aUserData);

s3eResult Tribe_ListGooglePlusFriends_platform(s3eCallback aTribe_didListGooglePlusFriends, void* aUserData);

s3eResult Tribe_ListGameCenterFriends_platform(s3eCallback aTribe_didListGameCenterFriends, void* aUserData);

s3eResult Tribe_InviteFriendByMail_platform(const char* aEmail, const char* aSubject, const char* aBody, s3eCallback aTribe_didInviteFriendByMail, void* aUserData);

s3eResult Tribe_InviteFriendByFBID_platform(const char* aFBFriendID, const char* aParamsJson, s3eCallback aTribe_didInviteFriendByFBID, void* aUserData);

s3eResult Tribe_InviteFriendByGooglePlusID_platform(const char* aGooglePlusFriendID, const char* aParamsJson, s3eCallback aTribe_didInviteFriendByGooglePlusID, void* aUserData);

s3eResult Tribe_FriendsBestHighScore_platform(const char* aMode, cbmScoreType aScoreType, s3eCallback aTribe_didFriendsBestHighScore, void* aUserData);

s3eResult Tribe_FriendsBestHighScoreArray_platform(const char* aArrayModesJson, cbmScoreType aScoreType, s3eCallback aTribe_didFriendsBestHighScoreArray, void* aUserData);

s3eResult Tribe_FindOpponents_platform(const char* aFilterJson, s3eCallback aTribe_didFindOpponents, void* aUserData);

const char* Match_GetActiveMatchID_platform();

bool Match_HasActiveMatch_platform();

s3eResult Match_GetMatchData_platform(const char* aMatchID, s3eCallback aMatch_didGetMatchData, void* aUserData);

s3eResult Match_ListMatch_platform(bool aIncludeAllData, s3eCallback aMatch_didListMatch, void* aUserData);

s3eResult Match_ListPendingMatch_platform(s3eCallback aMatch_didListPendingMatch, void* aUserData);

s3eResult Match_CreateMatch_platform(const char* aName, bool aPrivateMatch, const char* aMatchDataJson, s3eCallback aMatch_didCreateMatch, void* aUserData);

s3eResult Match_InviteFriends_platform(const char* aMatchID, const char* aArrayFriendsJson, bool aAutoAccept, const char* aNotifMessageJson, s3eCallback aMatch_didInviteFriends, void* aUserData);

s3eResult Match_JoinMatch_platform(const char* aMatchID, bool aAccept, const char* aNotifMessageJson, s3eCallback aMatch_didJoinMatch, void* aUserData);

s3eResult Match_MatchMove_platform(cbmMatchPhase aMatchPhase, const char* aMatchID, const char* aMatchStateJson, const char* aNotifMessageJson, s3eCallback aMatch_didMatchMove, void* aUserData);

s3eResult Match_ReadBinary_platform(const char* aMatchID, const char* aKey, s3eCallback aMatch_didReadBinary, void* aUserData);

s3eResult Match_WriteBinary_platform(const char* aMatchID, const char* aKey, void* aPointer, unsigned long aLength, s3eCallback aMatch_didWriteBinary, void* aUserData);

s3eResult Match_Read_platform(const char* aMatchID, const char* aKey, s3eCallback aMatch_didRead, void* aUserData);

s3eResult Match_Write_platform(const char* aMatchID, const char* aKey, const char* aValue, s3eCallback aMatch_didWrite, void* aUserData);

s3eResult Notification_NotifyUser_platform(const char* aUserPseudo, const char* aDataJson, void* aReference, const char* apnMessageJson, s3eCallback aNotification_didNotifyUser, void* aUserData);

bool GooglePlay_IsConnected_platform();

s3eResult GooglePlay_LoadPeople_platform(const char* aListPeopleJSON, s3eCallback aGooglePlay_didLoadPeople, void* aUserData);

s3eResult GooglePlay_ShowAllLeaderboards_platform();

s3eResult GooglePlay_ShowLeaderboard_platform(const char* aLeaderboardID);

s3eResult GooglePlay_SubmitScore_platform(const char* aLeaderboardID, long aScore, const char* aTag, s3eCallback aGooglePlay_didSubmitScore, void* aUserData);

s3eResult GooglePlay_LoadLeaderboardMetadata_platform(const char* aLeaderboardID, s3eCallback aGooglePlay_didLoadLeaderboardMetadata, void* aUserData);

s3eResult GooglePlay_LoadLeaderboardsMetadata_platform(s3eCallback aGooglePlay_didLoadLeaderboardsMetadata, void* aUserData);

s3eResult GooglePlay_LoadPlayerCenteredScores_platform(const char* aLeaderboardID, cbmGooglePlayTimeSpan aSpan, cbmGooglePlayLeaderboardCollection aLeaderboardCollection, int aMaxResults, bool aForceReload, s3eCallback aGooglePlay_didLoadPlayerCenteredScores, void* aUserData);

s3eResult GooglePlay_LoadTopScores_platform(const char* aLeaderboardID, cbmGooglePlayTimeSpan aSpan, cbmGooglePlayLeaderboardCollection aLeaderboardCollection, int aMaxResults, bool aForceReload, s3eCallback aGooglePlay_didLoadTopScores, void* aUserData);

s3eResult GooglePlay_ShowAchievements_platform();

s3eResult GooglePlay_IncrementAchievement_platform(const char* aAchievementID, int aNumSteps, s3eCallback aGooglePlay_didIncrementAchievement, void* aUserData);

s3eResult GooglePlay_LoadAchievements_platform(bool aForceReload, s3eCallback aGooglePlay_didLoadAchievements, void* aUserData);

s3eResult GooglePlay_RevealAchievement_platform(const char* aAchievementID, s3eCallback aGooglePlay_didRevealAchievement, void* aUserData);

s3eResult GooglePlay_UnlockAchievement_platform(const char* aAchievementID, s3eCallback aGooglePlay_didUnlockAchievement, void* aUserData);


#endif /* !CLOUDBUILDERMARMALADE_INTERNAL_H */