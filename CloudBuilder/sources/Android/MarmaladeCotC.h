//
//  Marmalade_CotC.h
//  
//
//  Created by Michael EL BAKI on 23/Sep/13.
//
//

#ifndef ____MARMALADE_COTC__
#define ____MARMALADE_COTC__

#include "MarmaladeCallbacksEnums.h"

extern void** gCloudBuilderCallbacks;

extern "C"
{
    void InitCloudBuilderCallbacks(void** aCloudBuilderCallbacks);
    
    void CloudBuilder_PopCallback_CotC(void);
    
    int CClan_Setup_CotC(const char* aConfigurationJson);
    int CClan_BatchBegin_CotC(void);
    int CClan_BatchEnd_CotC(void);
    bool CClan_isSetup_CotC(void);
    bool CClan_isUserLogged_CotC(void);
    
    int CUser_RegisterAndLogin_CotC(const char *aEmail, const char *aPassword, const char *aPseudo);
    int CUser_Login_CotC(const char *aPseudo, const char *aPassword);
    int CUser_LoginWithFacebook_CotC(const char* aOptionalPassword);
    int CUser_LoginWithGooglePlus_CotC(const char* aOptionalPassword);
    int CUser_LoginWithGameCenter_CotC(void);
    int CUser_Logout_CotC(void);
    int CUser_LinkAccountWithFacebook_CotC(void);
    int CUser_LinkAccountWithGooglePlus_CotC(void);
    int CUser_LinkAccountWithGameCenter_CotC(void);
    int CUser_ChangePassword_CotC(const char* aOldPassword, const char* aNewPassword);
    int CUser_MailPassword_CotC(const char *aEmail, const char* aSubject, const char* aBody);
    int CUser_SetUserProfile_CotC(const char* aJsonProdile);
    int CUser_GetUserProfile_CotC(void);
    const char* CUser_GetPseudo_CotC(void);
    const char* CUser_GetMail_CotC(void);
    int CUser_PublishOnMyFacebookWall_CotC(const char* aMessage);
    int CUser_ReadBinary_CotC(const char* aKey);
    int CUser_WriteBinary_CotC(const char* aKey, void* aPointer, unsigned long aLength);
    int CUser_Read_CotC(const char* aKey);
    int CUser_Write_CotC(const char* aKey, const char* aValue);
    int CUser_SetProperties_CotC(bool aCanBeFound, const char* aJsonPropertiesList);
    int CUser_GetProperties_CotC(void);
    int CUser_CheckUser_CotC(const char* aIdent);
    int CUser_SetAvatarSource_CotC(int aSource);
    
    int CGame_Score_CotC(long long aHighScore, const char *aMode, int aScoreType, const char *aInfoScore);
    int CGame_GetRank_CotC(long long aHighScore, const char *aMode, int aScoreType);
    int CGame_BestHighScore_CotC(int aCount, const char *aMode, int aScoreType);
    int CGame_CenteredScore_CotC(int aCount, const char *aMode, int aScoreType);
    int CGame_GetRankArray_CotC(const char* aJsonScoreArray, int aScoreType);
    int CGame_BestHighScoreArray_CotC(int aCount, const char* aJsonArrayModes, int aScoreType);
    int CGame_ReadBinary_CotC(const char* aKey);
    int CGame_WriteBinary_CotC(const char* aKey, void* aPointer, unsigned long aLength);
    int CGame_Read_CotC(const char* aKey);
    int CGame_Write_CotC(const char* aKey, const char* aValue);
    
    int CTribe_ListUsers_CotC(const char* aContainsString);
    int CTribe_ListGlobalFriends_CotC(void);
    int CTribe_BlacklistGlobalFriends_CotC(void);
    int CTribe_ChangeGlobalRelationshipStatus_CotC(const char* aFriendPseudo, int aNewState);
    int CTribe_ListFriends_CotC(void);
    int CTribe_BlacklistFriends_CotC(void);
    int CTribe_ChangeRelationshipStatus_CotC(const char* aFriendPseudo, int aNewState);
    int CTribe_ListFacebookFriends_CotC(void);
    int CTribe_ListGooglePlusFriends_CotC(void);
    int CTribe_ListGameCenterFriends_CotC(void);
    int CTribe_InviteFriendByMail_CotC(const char *aEmail, const char *aSubject, const char *aBody);
    int CTribe_InviteFriendByFBID_CotC(const char *aFBFriendID, const char* aJsonParams);
    int CTribe_InviteFriendByGooglePlusID_CotC(const char *aGooglePlusFriendID, const char* aJsonParams);
    int CTribe_FriendsBestHighScore_CotC(const char *aMode, int aScoreType);
    int CTribe_FriendsBestHighScoreArray_CotC(const char *aJsonArrayModes, int aScoreType);
    int CTribe_FindOpponents_CotC(const char *aJsonFilter);

    const char* CMatch_GetActiveMatchID_CotC(void);
    bool CMatch_HasActiveMatch_CotC(void);
    int CMatch_GetMatchData_CotC(const char* aMatchID);
    int CMatch_ListMatch_CotC(bool aIncludeAllData);
    int CMatch_ListPendingMatch_CotC(void);
    int CMatch_CreateMatch_CotC(const char* aName, bool aPrivateMatch, const char* aJsonMatchData);
    int CMatch_InviteFriends_CotC(const char* aMatchID, const char* aJsonArrayFriends, bool aAutoAccept, const char* aPNMessage);
    int CMatch_JoinMatch_CotC(const char* aMatchID, bool aAccept, const char* aPNMessage);
    int CMatch_MatchMove_CotC(int aPhase, const char* aMatchID, const char* aJsonMatchState, const char* aPNMessage);
    int CMatch_ReadBinary_CotC(const char* aMatchID, const char* aKey);
    int CMatch_WriteBinary_CotC(const char* aMatchID, const char* aKey, void* aPointer, unsigned long aLength);
    int CMatch_Read_CotC(const char* aMatchID, const char* aKey);
    int CMatch_Write_CotC(const char* aMatchID, const char* aKey, const char* aValue);
    
    bool CGGoglePlay_IsConnected_CotC(void);
    int CGGoglePlay_LoadPeople_CotC(const char* aJsonListPeople);
    int CGGoglePlay_ShowAllLeaderboards_CotC(void);
    int CGGoglePlay_ShowLeaderboard_CotC(const char* aLeaderboardID);
    int CGGoglePlay_SubmitScore_CotC(const char* aLeaderboardID, long aScore, const char* aTag);
    int CGGoglePlay_LoadLeaderboardMetadata_CotC(const char* aLeaderboardID);
    int CGGoglePlay_LoadLeaderboardsMetadata_CotC(void);
    int CGGoglePlay_LoadPlayerCenteredScores_CotC(const char* aLeaderboardID, int aSpan, int aLeaderboardCollection, int aMaxResults, bool aForceReload);
    int CGGoglePlay_LoadTopScores_CotC(const char* aLeaderboardID, int aSpan, int aLeaderboardCollection, int aMaxResults, bool aForceReload);
    int CGGoglePlay_ShowAchievements_CotC(void);
    int CGGoglePlay_IncrementAchievement_CotC(const char* aAchievementID, int aNumSteps);
    int CGGoglePlay_LoadAchievements_CotC(bool aForceReload);
    int CGGoglePlay_RevealAchievement_CotC(const char* aAchievementID);
    int CGGoglePlay_UnlockAchievement_CotC(const char* aAchievementID);
}

#endif //   ____MARMALADE_COTC__
