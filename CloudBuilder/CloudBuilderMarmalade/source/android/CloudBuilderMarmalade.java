/*
java implementation of the CloudBuilderMarmalade extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;

class CloudBuilderMarmalade
{
    public FIXME CloudBuilder_Init(FIXME aCotCFunctions)
    {
        
    }
    public void CloudBuilder_SetGlobalCotCCallback(FIXME aIndex, FIXME aCallback, FIXME aUserData)
    {
        
    }
    public void CloudBuilder_PopCallback()
    {
        
    }
    public int Clan_Setup(String aConfigurationJson, FIXME aClan_didSetup, FIXME aUserData)
    {
        return 0;
    }
    public int Clan_BatchBegin()
    {
        return 0;
    }
    public int Clan_BatchEnd(FIXME aClan_didBatchEnd, FIXME aUserData)
    {
        return 0;
    }
    public boolean Clan_isSetup()
    {
        return false;
    }
    public boolean Clan_isUserLogged()
    {
        return false;
    }
    public int User_RegisterAndLogin(String aEmail, String aPassword, String aPseudo, FIXME aUser_didRegisterAndLogin, FIXME aUserData)
    {
        return 0;
    }
    public int User_Login(String aPseudo, String aPassword, FIXME aUser_didLogin, FIXME aUserData)
    {
        return 0;
    }
    public int User_LoginWithFacebook(String aOptionalPassword, FIXME aUser_didLoginWithFacebook, FIXME aUserData)
    {
        return 0;
    }
    public int User_LoginWithGooglePlus(String aOptionalPassword, FIXME aUser_didLoginWithGooglePlus, FIXME aUserData)
    {
        return 0;
    }
    public int User_LoginWithGameCenter(FIXME aUser_didLoginWithGameCenter, FIXME aUserData)
    {
        return 0;
    }
    public int User_Logout(FIXME aUser_didLogout, FIXME aUserData)
    {
        return 0;
    }
    public int User_LinkAccountWithFacebook(FIXME aUser_didLinkAccountWithFacebook, FIXME aUserData)
    {
        return 0;
    }
    public int User_LinkAccountWithGooglePlus(FIXME aUser_didLinkAccountWithGooglePlus, FIXME aUserData)
    {
        return 0;
    }
    public int User_LinkAccountWithGameCenter(FIXME aUser_didLinkAccountWithGameCenter, FIXME aUserData)
    {
        return 0;
    }
    public int User_ChangePassword(String aOldPassword, String aNewPassword, FIXME aUser_didChangePassword, FIXME aUserData)
    {
        return 0;
    }
    public int User_MailPassword(String aEmail, String aSubject, String aBody, FIXME aUser_didMailPassword, FIXME aUserData)
    {
        return 0;
    }
    public int User_SetUserProfile(String aJson, FIXME aUser_didSetUserProfile, FIXME aUserData)
    {
        return 0;
    }
    public int User_GetUserProfile(FIXME aUser_didGetUserProfile, FIXME aUserData)
    {
        return 0;
    }
    public FIXME User_GetPseudo()
    {
        
    }
    public FIXME User_GetMail()
    {
        
    }
    public int User_PublishOnMyFacebookWall(String aMessage, FIXME aUser_didPublishOnMyFacebookWall, FIXME aUserData)
    {
        return 0;
    }
    public int User_ReadBinary(String aKey, FIXME aUser_didReadBinary, FIXME aUserData)
    {
        return 0;
    }
    public int User_WriteBinary(String aKey, FIXME aPointer, FIXME aLength, FIXME aUser_didWriteBinary, FIXME aUserData)
    {
        return 0;
    }
    public int User_Read(String aKey, FIXME aUser_didRead, FIXME aUserData)
    {
        return 0;
    }
    public int User_Write(String aKey, String aValue, FIXME aUser_didWrite, FIXME aUserData)
    {
        return 0;
    }
    public int User_SetProperties(boolean aCanBeFound, String aPropertiesJson, FIXME aUser_didSetProperties, FIXME aUserData)
    {
        return 0;
    }
    public int User_GetProperties(FIXME aUser_didGetProperties, FIXME aUserData)
    {
        return 0;
    }
    public int User_CheckUser(String aIdent, FIXME aUser_didCheckUser, FIXME aUserData)
    {
        return 0;
    }
    public int User_SetAvatarSource(FIXME aSource, FIXME aUser_didSetAvatarSource, FIXME aUserData)
    {
        return 0;
    }
    public int Game_Score(FIXME aHighScore, String aMode, FIXME aScoreType, String aInfoScore, boolean aMayVary, FIXME aGame_didScore, FIXME aUserData)
    {
        return 0;
    }
    public int Game_GetRank(FIXME aHighScore, String aMode, FIXME aScoreType, FIXME aGame_didGetRank, FIXME aUserData)
    {
        return 0;
    }
    public int Game_BestHighScore(int aCount, String aMode, FIXME aScoreType, FIXME aGame_didBestHighScore, FIXME aUserData)
    {
        return 0;
    }
    public int Game_CenteredScore(int aCount, String aMode, FIXME aScoreType, FIXME aGame_didCenteredScore, FIXME aUserData)
    {
        return 0;
    }
    public int Game_GetRankArray(String aScoreArrayJson, FIXME aScoreType, FIXME aGame_didGetRankArray, FIXME aUserData)
    {
        return 0;
    }
    public int Game_BestHighScoreArray(int aCount, String aArrayModesJson, FIXME aScoreType, FIXME aGame_didBestHighScoreArray, FIXME aUserData)
    {
        return 0;
    }
    public int Game_ReadBinary(String aKey, FIXME aGame_didReadBinary, FIXME aUserData)
    {
        return 0;
    }
    public int Game_WriteBinary(String aKey, FIXME aPointer, FIXME aLength, FIXME aGame_didWriteBinary, FIXME aUserData)
    {
        return 0;
    }
    public int Game_Read(String aKey, FIXME aGame_didRead, FIXME aUserData)
    {
        return 0;
    }
    public int Game_Write(String aKey, String aValue, FIXME aGame_didWrite, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_ListUsers(String aContainsString, FIXME aTribe_didListUsers, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_ListGlobalFriends(FIXME aTribe_didListGlobalFriends, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_BlacklistGlobalFriends(FIXME aTribe_didBlacklistGlobalFriends, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_ChangeGlobalRelationshipStatus(String aFriendPseudo, FIXME aNewState, FIXME aTribe_didChangeGlobalRelationshipStatus, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_ListFriends(FIXME aTribe_didListFriends, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_BlacklistFriends(FIXME aTribe_didBlacklistFriends, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_ChangeRelationshipStatus(String aFriendPseudo, FIXME aNewState, FIXME aTribe_didChangeRelationshipStatus, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_ListFacebookFriends(FIXME aTribe_didListFacebookFriends, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_ListGooglePlusFriends(FIXME aTribe_didListGooglePlusFriends, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_ListGameCenterFriends(FIXME aTribe_didListGameCenterFriends, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_InviteFriendByMail(String aEmail, String aSubject, String aBody, FIXME aTribe_didInviteFriendByMail, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_InviteFriendByFBID(String aFBFriendID, String aParamsJson, FIXME aTribe_didInviteFriendByFBID, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_InviteFriendByGooglePlusID(String aGooglePlusFriendID, String aParamsJson, FIXME aTribe_didInviteFriendByGooglePlusID, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_FriendsBestHighScore(String aMode, FIXME aScoreType, FIXME aTribe_didFriendsBestHighScore, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_FriendsBestHighScoreArray(String aArrayModesJson, FIXME aScoreType, FIXME aTribe_didFriendsBestHighScoreArray, FIXME aUserData)
    {
        return 0;
    }
    public int Tribe_FindOpponents(String aFilterJson, FIXME aTribe_didFindOpponents, FIXME aUserData)
    {
        return 0;
    }
    public FIXME Match_GetActiveMatchID()
    {
        
    }
    public boolean Match_HasActiveMatch()
    {
        return false;
    }
    public int Match_GetMatchData(String aMatchID, FIXME aMatch_didGetMatchData, FIXME aUserData)
    {
        return 0;
    }
    public int Match_ListMatch(boolean aIncludeAllData, FIXME aMatch_didListMatch, FIXME aUserData)
    {
        return 0;
    }
    public int Match_ListPendingMatch(FIXME aMatch_didListPendingMatch, FIXME aUserData)
    {
        return 0;
    }
    public int Match_CreateMatch(String aName, boolean aPrivateMatch, String aMatchDataJson, FIXME aMatch_didCreateMatch, FIXME aUserData)
    {
        return 0;
    }
    public int Match_InviteFriends(String aMatchID, String aArrayFriendsJson, boolean aAutoAccept, String aNotifMessageJson, FIXME aMatch_didInviteFriends, FIXME aUserData)
    {
        return 0;
    }
    public int Match_JoinMatch(String aMatchID, boolean aAccept, String aNotifMessageJson, FIXME aMatch_didJoinMatch, FIXME aUserData)
    {
        return 0;
    }
    public int Match_MatchMove(FIXME aMatchPhase, String aMatchID, String aMatchStateJson, String aNotifMessageJson, FIXME aMatch_didMatchMove, FIXME aUserData)
    {
        return 0;
    }
    public int Match_ReadBinary(String aMatchID, String aKey, FIXME aMatch_didReadBinary, FIXME aUserData)
    {
        return 0;
    }
    public int Match_WriteBinary(String aMatchID, String aKey, FIXME aPointer, FIXME aLength, FIXME aMatch_didWriteBinary, FIXME aUserData)
    {
        return 0;
    }
    public int Match_Read(String aMatchID, String aKey, FIXME aMatch_didRead, FIXME aUserData)
    {
        return 0;
    }
    public int Match_Write(String aMatchID, String aKey, String aValue, FIXME aMatch_didWrite, FIXME aUserData)
    {
        return 0;
    }
    public int Notification_NotifyUser(String aUserPseudo, String aDataJson, FIXME aReference, String apnMessageJson, FIXME aNotification_didNotifyUser, FIXME aUserData)
    {
        return 0;
    }
    public boolean GooglePlay_IsConnected()
    {
        return false;
    }
    public int GooglePlay_LoadPeople(String aListPeopleJSON, FIXME aGooglePlay_didLoadPeople, FIXME aUserData)
    {
        return 0;
    }
    public int GooglePlay_ShowAllLeaderboards()
    {
        return 0;
    }
    public int GooglePlay_ShowLeaderboard(String aLeaderboardID)
    {
        return 0;
    }
    public int GooglePlay_SubmitScore(String aLeaderboardID, FIXME aScore, String aTag, FIXME aGooglePlay_didSubmitScore, FIXME aUserData)
    {
        return 0;
    }
    public int GooglePlay_LoadLeaderboardMetadata(String aLeaderboardID, FIXME aGooglePlay_didLoadLeaderboardMetadata, FIXME aUserData)
    {
        return 0;
    }
    public int GooglePlay_LoadLeaderboardsMetadata(FIXME aGooglePlay_didLoadLeaderboardsMetadata, FIXME aUserData)
    {
        return 0;
    }
    public int GooglePlay_LoadPlayerCenteredScores(String aLeaderboardID, FIXME aSpan, FIXME aLeaderboardCollection, int aMaxResults, boolean aForceReload, FIXME aGooglePlay_didLoadPlayerCenteredScores, FIXME aUserData)
    {
        return 0;
    }
    public int GooglePlay_LoadTopScores(String aLeaderboardID, FIXME aSpan, FIXME aLeaderboardCollection, int aMaxResults, boolean aForceReload, FIXME aGooglePlay_didLoadTopScores, FIXME aUserData)
    {
        return 0;
    }
    public int GooglePlay_ShowAchievements()
    {
        return 0;
    }
    public int GooglePlay_IncrementAchievement(String aAchievementID, int aNumSteps, FIXME aGooglePlay_didIncrementAchievement, FIXME aUserData)
    {
        return 0;
    }
    public int GooglePlay_LoadAchievements(boolean aForceReload, FIXME aGooglePlay_didLoadAchievements, FIXME aUserData)
    {
        return 0;
    }
    public int GooglePlay_RevealAchievement(String aAchievementID, FIXME aGooglePlay_didRevealAchievement, FIXME aUserData)
    {
        return 0;
    }
    public int GooglePlay_UnlockAchievement(String aAchievementID, FIXME aGooglePlay_didUnlockAchievement, FIXME aUserData)
    {
        return 0;
    }
}
