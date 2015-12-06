/*
Generic implementation of the CloudBuilderMarmalade extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "CloudBuilderMarmalade_internal.h"
s3eResult CloudBuilderMarmaladeInit()
{
	//Add any generic initialisation code here
	return CloudBuilderMarmaladeInit_platform();
}

void CloudBuilderMarmaladeTerminate()
{
	//Add any generic termination code here
	CloudBuilderMarmaladeTerminate_platform();
}

void** CloudBuilder_Init(void** aCotCFunctions)
{
	return CloudBuilder_Init_platform(aCotCFunctions);
}

void CloudBuilder_SetGlobalCotCCallback(CloudBuilderMarmaladeCallback aIndex, s3eCallback aCallback, void* aUserData)
{
	CloudBuilder_SetGlobalCotCCallback_platform(aIndex, aCallback, aUserData);
}

void CloudBuilder_PopCallback()
{
	CloudBuilder_PopCallback_platform();
}

s3eResult Clan_Setup(const char* aConfigurationJson, s3eCallback aClan_didSetup, void* aUserData)
{
	return Clan_Setup_platform(aConfigurationJson, aClan_didSetup, aUserData);
}

s3eResult Clan_BatchBegin()
{
	return Clan_BatchBegin_platform();
}

s3eResult Clan_BatchEnd(s3eCallback aClan_didBatchEnd, void* aUserData)
{
	return Clan_BatchEnd_platform(aClan_didBatchEnd, aUserData);
}

bool Clan_isSetup()
{
	return Clan_isSetup_platform();
}

bool Clan_isUserLogged()
{
	return Clan_isUserLogged_platform();
}

s3eResult User_RegisterAndLogin(const char* aEmail, const char* aPassword, const char* aPseudo, s3eCallback aUser_didRegisterAndLogin, void* aUserData)
{
	return User_RegisterAndLogin_platform(aEmail, aPassword, aPseudo, aUser_didRegisterAndLogin, aUserData);
}

s3eResult User_Login(const char* aPseudo, const char* aPassword, s3eCallback aUser_didLogin, void* aUserData)
{
	return User_Login_platform(aPseudo, aPassword, aUser_didLogin, aUserData);
}

s3eResult User_LoginWithFacebook(const char* aOptionalPassword, s3eCallback aUser_didLoginWithFacebook, void* aUserData)
{
	return User_LoginWithFacebook_platform(aOptionalPassword, aUser_didLoginWithFacebook, aUserData);
}

s3eResult User_LoginWithGooglePlus(const char* aOptionalPassword, s3eCallback aUser_didLoginWithGooglePlus, void* aUserData)
{
	return User_LoginWithGooglePlus_platform(aOptionalPassword, aUser_didLoginWithGooglePlus, aUserData);
}

s3eResult User_LoginWithGameCenter(s3eCallback aUser_didLoginWithGameCenter, void* aUserData)
{
	return User_LoginWithGameCenter_platform(aUser_didLoginWithGameCenter, aUserData);
}

s3eResult User_Logout(s3eCallback aUser_didLogout, void* aUserData)
{
	return User_Logout_platform(aUser_didLogout, aUserData);
}

s3eResult User_LinkAccountWithFacebook(s3eCallback aUser_didLinkAccountWithFacebook, void* aUserData)
{
	return User_LinkAccountWithFacebook_platform(aUser_didLinkAccountWithFacebook, aUserData);
}

s3eResult User_LinkAccountWithGooglePlus(s3eCallback aUser_didLinkAccountWithGooglePlus, void* aUserData)
{
	return User_LinkAccountWithGooglePlus_platform(aUser_didLinkAccountWithGooglePlus, aUserData);
}

s3eResult User_LinkAccountWithGameCenter(s3eCallback aUser_didLinkAccountWithGameCenter, void* aUserData)
{
	return User_LinkAccountWithGameCenter_platform(aUser_didLinkAccountWithGameCenter, aUserData);
}

s3eResult User_ChangePassword(const char* aOldPassword, const char* aNewPassword, s3eCallback aUser_didChangePassword, void* aUserData)
{
	return User_ChangePassword_platform(aOldPassword, aNewPassword, aUser_didChangePassword, aUserData);
}

s3eResult User_MailPassword(const char* aEmail, const char* aSubject, const char* aBody, s3eCallback aUser_didMailPassword, void* aUserData)
{
	return User_MailPassword_platform(aEmail, aSubject, aBody, aUser_didMailPassword, aUserData);
}

s3eResult User_SetUserProfile(const char* aJson, s3eCallback aUser_didSetUserProfile, void* aUserData)
{
	return User_SetUserProfile_platform(aJson, aUser_didSetUserProfile, aUserData);
}

s3eResult User_GetUserProfile(s3eCallback aUser_didGetUserProfile, void* aUserData)
{
	return User_GetUserProfile_platform(aUser_didGetUserProfile, aUserData);
}

const char* User_GetPseudo()
{
	return User_GetPseudo_platform();
}

const char* User_GetMail()
{
	return User_GetMail_platform();
}

s3eResult User_PublishOnMyFacebookWall(const char* aMessage, s3eCallback aUser_didPublishOnMyFacebookWall, void* aUserData)
{
	return User_PublishOnMyFacebookWall_platform(aMessage, aUser_didPublishOnMyFacebookWall, aUserData);
}

s3eResult User_ReadBinary(const char* aKey, s3eCallback aUser_didReadBinary, void* aUserData)
{
	return User_ReadBinary_platform(aKey, aUser_didReadBinary, aUserData);
}

s3eResult User_WriteBinary(const char* aKey, void* aPointer, unsigned long aLength, s3eCallback aUser_didWriteBinary, void* aUserData)
{
	return User_WriteBinary_platform(aKey, aPointer, aLength, aUser_didWriteBinary, aUserData);
}

s3eResult User_Read(const char* aKey, s3eCallback aUser_didRead, void* aUserData)
{
	return User_Read_platform(aKey, aUser_didRead, aUserData);
}

s3eResult User_Write(const char* aKey, const char* aValue, s3eCallback aUser_didWrite, void* aUserData)
{
	return User_Write_platform(aKey, aValue, aUser_didWrite, aUserData);
}

s3eResult User_SetProperties(bool aCanBeFound, const char* aPropertiesJson, s3eCallback aUser_didSetProperties, void* aUserData)
{
	return User_SetProperties_platform(aCanBeFound, aPropertiesJson, aUser_didSetProperties, aUserData);
}

s3eResult User_GetProperties(s3eCallback aUser_didGetProperties, void* aUserData)
{
	return User_GetProperties_platform(aUser_didGetProperties, aUserData);
}

s3eResult User_CheckUser(const char* aIdent, s3eCallback aUser_didCheckUser, void* aUserData)
{
	return User_CheckUser_platform(aIdent, aUser_didCheckUser, aUserData);
}

s3eResult User_SetAvatarSource(cbmExternalNetwork aSource, s3eCallback aUser_didSetAvatarSource, void* aUserData)
{
	return User_SetAvatarSource_platform(aSource, aUser_didSetAvatarSource, aUserData);
}

s3eResult Game_Score(long long aHighScore, const char* aMode, cbmScoreType aScoreType, const char* aInfoScore, bool aMayVary, s3eCallback aGame_didScore, void* aUserData)
{
	return Game_Score_platform(aHighScore, aMode, aScoreType, aInfoScore, aMayVary, aGame_didScore, aUserData);
}

s3eResult Game_GetRank(long long aHighScore, const char* aMode, cbmScoreType aScoreType, s3eCallback aGame_didGetRank, void* aUserData)
{
	return Game_GetRank_platform(aHighScore, aMode, aScoreType, aGame_didGetRank, aUserData);
}

s3eResult Game_BestHighScore(int aCount, const char* aMode, cbmScoreType aScoreType, s3eCallback aGame_didBestHighScore, void* aUserData)
{
	return Game_BestHighScore_platform(aCount, aMode, aScoreType, aGame_didBestHighScore, aUserData);
}

s3eResult Game_CenteredScore(int aCount, const char* aMode, cbmScoreType aScoreType, s3eCallback aGame_didCenteredScore, void* aUserData)
{
	return Game_CenteredScore_platform(aCount, aMode, aScoreType, aGame_didCenteredScore, aUserData);
}

s3eResult Game_GetRankArray(const char* aScoreArrayJson, cbmScoreType aScoreType, s3eCallback aGame_didGetRankArray, void* aUserData)
{
	return Game_GetRankArray_platform(aScoreArrayJson, aScoreType, aGame_didGetRankArray, aUserData);
}

s3eResult Game_BestHighScoreArray(int aCount, const char* aArrayModesJson, cbmScoreType aScoreType, s3eCallback aGame_didBestHighScoreArray, void* aUserData)
{
	return Game_BestHighScoreArray_platform(aCount, aArrayModesJson, aScoreType, aGame_didBestHighScoreArray, aUserData);
}

s3eResult Game_ReadBinary(const char* aKey, s3eCallback aGame_didReadBinary, void* aUserData)
{
	return Game_ReadBinary_platform(aKey, aGame_didReadBinary, aUserData);
}

s3eResult Game_WriteBinary(const char* aKey, void* aPointer, unsigned long aLength, s3eCallback aGame_didWriteBinary, void* aUserData)
{
	return Game_WriteBinary_platform(aKey, aPointer, aLength, aGame_didWriteBinary, aUserData);
}

s3eResult Game_Read(const char* aKey, s3eCallback aGame_didRead, void* aUserData)
{
	return Game_Read_platform(aKey, aGame_didRead, aUserData);
}

s3eResult Game_Write(const char* aKey, const char* aValue, s3eCallback aGame_didWrite, void* aUserData)
{
	return Game_Write_platform(aKey, aValue, aGame_didWrite, aUserData);
}

s3eResult Tribe_ListUsers(const char* aContainsString, s3eCallback aTribe_didListUsers, void* aUserData)
{
	return Tribe_ListUsers_platform(aContainsString, aTribe_didListUsers, aUserData);
}

s3eResult Tribe_ListGlobalFriends(s3eCallback aTribe_didListGlobalFriends, void* aUserData)
{
	return Tribe_ListGlobalFriends_platform(aTribe_didListGlobalFriends, aUserData);
}

s3eResult Tribe_BlacklistGlobalFriends(s3eCallback aTribe_didBlacklistGlobalFriends, void* aUserData)
{
	return Tribe_BlacklistGlobalFriends_platform(aTribe_didBlacklistGlobalFriends, aUserData);
}

s3eResult Tribe_ChangeGlobalRelationshipStatus(const char* aFriendPseudo, cbmRelationChange aNewState, s3eCallback aTribe_didChangeGlobalRelationshipStatus, void* aUserData)
{
	return Tribe_ChangeGlobalRelationshipStatus_platform(aFriendPseudo, aNewState, aTribe_didChangeGlobalRelationshipStatus, aUserData);
}

s3eResult Tribe_ListFriends(s3eCallback aTribe_didListFriends, void* aUserData)
{
	return Tribe_ListFriends_platform(aTribe_didListFriends, aUserData);
}

s3eResult Tribe_BlacklistFriends(s3eCallback aTribe_didBlacklistFriends, void* aUserData)
{
	return Tribe_BlacklistFriends_platform(aTribe_didBlacklistFriends, aUserData);
}

s3eResult Tribe_ChangeRelationshipStatus(const char* aFriendPseudo, cbmRelationChange aNewState, s3eCallback aTribe_didChangeRelationshipStatus, void* aUserData)
{
	return Tribe_ChangeRelationshipStatus_platform(aFriendPseudo, aNewState, aTribe_didChangeRelationshipStatus, aUserData);
}

s3eResult Tribe_ListFacebookFriends(s3eCallback aTribe_didListFacebookFriends, void* aUserData)
{
	return Tribe_ListFacebookFriends_platform(aTribe_didListFacebookFriends, aUserData);
}

s3eResult Tribe_ListGooglePlusFriends(s3eCallback aTribe_didListGooglePlusFriends, void* aUserData)
{
	return Tribe_ListGooglePlusFriends_platform(aTribe_didListGooglePlusFriends, aUserData);
}

s3eResult Tribe_ListGameCenterFriends(s3eCallback aTribe_didListGameCenterFriends, void* aUserData)
{
	return Tribe_ListGameCenterFriends_platform(aTribe_didListGameCenterFriends, aUserData);
}

s3eResult Tribe_InviteFriendByMail(const char* aEmail, const char* aSubject, const char* aBody, s3eCallback aTribe_didInviteFriendByMail, void* aUserData)
{
	return Tribe_InviteFriendByMail_platform(aEmail, aSubject, aBody, aTribe_didInviteFriendByMail, aUserData);
}

s3eResult Tribe_InviteFriendByFBID(const char* aFBFriendID, const char* aParamsJson, s3eCallback aTribe_didInviteFriendByFBID, void* aUserData)
{
	return Tribe_InviteFriendByFBID_platform(aFBFriendID, aParamsJson, aTribe_didInviteFriendByFBID, aUserData);
}

s3eResult Tribe_InviteFriendByGooglePlusID(const char* aGooglePlusFriendID, const char* aParamsJson, s3eCallback aTribe_didInviteFriendByGooglePlusID, void* aUserData)
{
	return Tribe_InviteFriendByGooglePlusID_platform(aGooglePlusFriendID, aParamsJson, aTribe_didInviteFriendByGooglePlusID, aUserData);
}

s3eResult Tribe_FriendsBestHighScore(const char* aMode, cbmScoreType aScoreType, s3eCallback aTribe_didFriendsBestHighScore, void* aUserData)
{
	return Tribe_FriendsBestHighScore_platform(aMode, aScoreType, aTribe_didFriendsBestHighScore, aUserData);
}

s3eResult Tribe_FriendsBestHighScoreArray(const char* aArrayModesJson, cbmScoreType aScoreType, s3eCallback aTribe_didFriendsBestHighScoreArray, void* aUserData)
{
	return Tribe_FriendsBestHighScoreArray_platform(aArrayModesJson, aScoreType, aTribe_didFriendsBestHighScoreArray, aUserData);
}

s3eResult Tribe_FindOpponents(const char* aFilterJson, s3eCallback aTribe_didFindOpponents, void* aUserData)
{
	return Tribe_FindOpponents_platform(aFilterJson, aTribe_didFindOpponents, aUserData);
}

const char* Match_GetActiveMatchID()
{
	return Match_GetActiveMatchID_platform();
}

bool Match_HasActiveMatch()
{
	return Match_HasActiveMatch_platform();
}

s3eResult Match_GetMatchData(const char* aMatchID, s3eCallback aMatch_didGetMatchData, void* aUserData)
{
	return Match_GetMatchData_platform(aMatchID, aMatch_didGetMatchData, aUserData);
}

s3eResult Match_ListMatch(bool aIncludeAllData, s3eCallback aMatch_didListMatch, void* aUserData)
{
	return Match_ListMatch_platform(aIncludeAllData, aMatch_didListMatch, aUserData);
}

s3eResult Match_ListPendingMatch(s3eCallback aMatch_didListPendingMatch, void* aUserData)
{
	return Match_ListPendingMatch_platform(aMatch_didListPendingMatch, aUserData);
}

s3eResult Match_CreateMatch(const char* aName, bool aPrivateMatch, const char* aMatchDataJson, s3eCallback aMatch_didCreateMatch, void* aUserData)
{
	return Match_CreateMatch_platform(aName, aPrivateMatch, aMatchDataJson, aMatch_didCreateMatch, aUserData);
}

s3eResult Match_InviteFriends(const char* aMatchID, const char* aArrayFriendsJson, bool aAutoAccept, const char* aNotifMessageJson, s3eCallback aMatch_didInviteFriends, void* aUserData)
{
	return Match_InviteFriends_platform(aMatchID, aArrayFriendsJson, aAutoAccept, aNotifMessageJson, aMatch_didInviteFriends, aUserData);
}

s3eResult Match_JoinMatch(const char* aMatchID, bool aAccept, const char* aNotifMessageJson, s3eCallback aMatch_didJoinMatch, void* aUserData)
{
	return Match_JoinMatch_platform(aMatchID, aAccept, aNotifMessageJson, aMatch_didJoinMatch, aUserData);
}

s3eResult Match_MatchMove(cbmMatchPhase aMatchPhase, const char* aMatchID, const char* aMatchStateJson, const char* aNotifMessageJson, s3eCallback aMatch_didMatchMove, void* aUserData)
{
	return Match_MatchMove_platform(aMatchPhase, aMatchID, aMatchStateJson, aNotifMessageJson, aMatch_didMatchMove, aUserData);
}

s3eResult Match_ReadBinary(const char* aMatchID, const char* aKey, s3eCallback aMatch_didReadBinary, void* aUserData)
{
	return Match_ReadBinary_platform(aMatchID, aKey, aMatch_didReadBinary, aUserData);
}

s3eResult Match_WriteBinary(const char* aMatchID, const char* aKey, void* aPointer, unsigned long aLength, s3eCallback aMatch_didWriteBinary, void* aUserData)
{
	return Match_WriteBinary_platform(aMatchID, aKey, aPointer, aLength, aMatch_didWriteBinary, aUserData);
}

s3eResult Match_Read(const char* aMatchID, const char* aKey, s3eCallback aMatch_didRead, void* aUserData)
{
	return Match_Read_platform(aMatchID, aKey, aMatch_didRead, aUserData);
}

s3eResult Match_Write(const char* aMatchID, const char* aKey, const char* aValue, s3eCallback aMatch_didWrite, void* aUserData)
{
	return Match_Write_platform(aMatchID, aKey, aValue, aMatch_didWrite, aUserData);
}

s3eResult Notification_NotifyUser(const char* aUserPseudo, const char* aDataJson, void* aReference, const char* apnMessageJson, s3eCallback aNotification_didNotifyUser, void* aUserData)
{
	return Notification_NotifyUser_platform(aUserPseudo, aDataJson, aReference, apnMessageJson, aNotification_didNotifyUser, aUserData);
}

bool GooglePlay_IsConnected()
{
	return GooglePlay_IsConnected_platform();
}

s3eResult GooglePlay_LoadPeople(const char* aListPeopleJSON, s3eCallback aGooglePlay_didLoadPeople, void* aUserData)
{
	return GooglePlay_LoadPeople_platform(aListPeopleJSON, aGooglePlay_didLoadPeople, aUserData);
}

s3eResult GooglePlay_ShowAllLeaderboards()
{
	return GooglePlay_ShowAllLeaderboards_platform();
}

s3eResult GooglePlay_ShowLeaderboard(const char* aLeaderboardID)
{
	return GooglePlay_ShowLeaderboard_platform(aLeaderboardID);
}

s3eResult GooglePlay_SubmitScore(const char* aLeaderboardID, long aScore, const char* aTag, s3eCallback aGooglePlay_didSubmitScore, void* aUserData)
{
	return GooglePlay_SubmitScore_platform(aLeaderboardID, aScore, aTag, aGooglePlay_didSubmitScore, aUserData);
}

s3eResult GooglePlay_LoadLeaderboardMetadata(const char* aLeaderboardID, s3eCallback aGooglePlay_didLoadLeaderboardMetadata, void* aUserData)
{
	return GooglePlay_LoadLeaderboardMetadata_platform(aLeaderboardID, aGooglePlay_didLoadLeaderboardMetadata, aUserData);
}

s3eResult GooglePlay_LoadLeaderboardsMetadata(s3eCallback aGooglePlay_didLoadLeaderboardsMetadata, void* aUserData)
{
	return GooglePlay_LoadLeaderboardsMetadata_platform(aGooglePlay_didLoadLeaderboardsMetadata, aUserData);
}

s3eResult GooglePlay_LoadPlayerCenteredScores(const char* aLeaderboardID, cbmGooglePlayTimeSpan aSpan, cbmGooglePlayLeaderboardCollection aLeaderboardCollection, int aMaxResults, bool aForceReload, s3eCallback aGooglePlay_didLoadPlayerCenteredScores, void* aUserData)
{
	return GooglePlay_LoadPlayerCenteredScores_platform(aLeaderboardID, aSpan, aLeaderboardCollection, aMaxResults, aForceReload, aGooglePlay_didLoadPlayerCenteredScores, aUserData);
}

s3eResult GooglePlay_LoadTopScores(const char* aLeaderboardID, cbmGooglePlayTimeSpan aSpan, cbmGooglePlayLeaderboardCollection aLeaderboardCollection, int aMaxResults, bool aForceReload, s3eCallback aGooglePlay_didLoadTopScores, void* aUserData)
{
	return GooglePlay_LoadTopScores_platform(aLeaderboardID, aSpan, aLeaderboardCollection, aMaxResults, aForceReload, aGooglePlay_didLoadTopScores, aUserData);
}

s3eResult GooglePlay_ShowAchievements()
{
	return GooglePlay_ShowAchievements_platform();
}

s3eResult GooglePlay_IncrementAchievement(const char* aAchievementID, int aNumSteps, s3eCallback aGooglePlay_didIncrementAchievement, void* aUserData)
{
	return GooglePlay_IncrementAchievement_platform(aAchievementID, aNumSteps, aGooglePlay_didIncrementAchievement, aUserData);
}

s3eResult GooglePlay_LoadAchievements(bool aForceReload, s3eCallback aGooglePlay_didLoadAchievements, void* aUserData)
{
	return GooglePlay_LoadAchievements_platform(aForceReload, aGooglePlay_didLoadAchievements, aUserData);
}

s3eResult GooglePlay_RevealAchievement(const char* aAchievementID, s3eCallback aGooglePlay_didRevealAchievement, void* aUserData)
{
	return GooglePlay_RevealAchievement_platform(aAchievementID, aGooglePlay_didRevealAchievement, aUserData);
}

s3eResult GooglePlay_UnlockAchievement(const char* aAchievementID, s3eCallback aGooglePlay_didUnlockAchievement, void* aUserData)
{
	return GooglePlay_UnlockAchievement_platform(aAchievementID, aGooglePlay_didUnlockAchievement, aUserData);
}
