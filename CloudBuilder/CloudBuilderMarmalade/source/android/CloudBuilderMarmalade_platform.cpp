/*
 * android-specific implementation of the CloudBuilderMarmalade extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "CloudBuilderMarmalade_internal.h"

#include "MarmaladeCallbacksEnums.h"
#include "MarmaladeCallbacks.h"

#define S3E_CURRENT_EXT CLOUDBUILDERMARMALADE

#include "s3eEdkError.h"
#include "s3eEdk.h"
#include "IwDebug.h"

void**  gCotCFunctions;
void*   gCotCCallbacks[ceNumCallbacks];

s3eResult CloudBuilderMarmaladeInit_platform()
{
	IwDebugTraceLinePrintf("CloudBuilderMarmaladeInit_platform()");
	IwDebugTraceLinePrintf("Launching Marmalade Wrapper v1.1.14.0");
	
	//gMarmaladeClan  = new MarmaladeClan;
	
	// Add any platform-specific initialisation code here
	return S3E_RESULT_SUCCESS;
}

void CloudBuilderMarmaladeTerminate_platform()
{
	IwDebugTraceLinePrintf("CloudBuilderMarmaladeTerminate_platform()");
	
	//gMarmaladeClan->Terminate();
	
	// Add any platform-specific termination code here
}

void** CloudBuilder_Init_platform(void** aCotCFunctions)
{
	gCotCFunctions = aCotCFunctions;
	
	gCotCCallbacks[ceGlobal_UserReceivedNotifyUser] = (void *) CUser_receivedNotifyUser_CotC;
	gCotCCallbacks[ceGlobal_NotificationReceivedMaintenanceNotification] = (void *) CNotification_receivedMaintenanceNotification_CotC;
	gCotCCallbacks[ceGlobal_NotificationDidBeginLookingForNotification] = (void *) CNotification_didBeginLookingForNotification_CotC;
	gCotCCallbacks[ceGlobal_NotificationDidEndLookingForNotification] = (void *) CNotification_didEndLookingForNotification_CotC;
	gCotCCallbacks[ceGlobal_NotificationDidRegisterDevice] = (void *) CNotification_didRegisterDevice_CotC;
	gCotCCallbacks[ceGlobal_TribeRelationshipHasChanged] = (void *) CTribe_relationshipHasChanged_CotC;
	gCotCCallbacks[ceGlobal_MatchPlayerDidChangeState] = (void *) CMatch_playerDidChangeState_CotC;
	gCotCCallbacks[ceGlobal_MatchMatchReceiveData] = (void *) CMatch_matchReceiveData_CotC;
	
	gCotCCallbacks[ceCClan_didSetup] = (void *) CClan_didSetup_CotC;
	gCotCCallbacks[ceCClan_didBatchEnd] = (void *) CClan_didBatchEnd_CotC;
	
	gCotCCallbacks[ceCUser_didRegisterAndLogin] = (void *) CUser_didRegisterAndLogin_CotC;
	gCotCCallbacks[ceCUser_didLogin] = (void *) CUser_didLogin_CotC;
	gCotCCallbacks[ceCUser_didLoginWithFacebook] = (void *) CUser_didLoginWithFacebook_CotC;
	gCotCCallbacks[ceCUser_didLoginWithGooglePlus] = (void *) CUser_didLoginWithGooglePlus_CotC;
	gCotCCallbacks[ceCUser_didLoginWithGameCenter] = (void *) CUser_didLoginWithGameCenter_CotC;
	gCotCCallbacks[ceCUser_didLinkAccountWithFacebook] = (void *) CUser_didLinkAccountWithFacebook_CotC;
	gCotCCallbacks[ceCUser_didLinkAccountWithGooglePlus] = (void *) CUser_didLinkAccountWithGooglePlus_CotC;
	gCotCCallbacks[ceCUser_didLinkAccountWithGameCenter] = (void *) CUser_didLinkAccountWithGameCenter_CotC;
	gCotCCallbacks[ceCUser_didLogout] = (void *) CUser_didLogout_CotC;
	gCotCCallbacks[ceCUser_didChangePassword] = (void *) CUser_didChangePassword_CotC;
	gCotCCallbacks[ceCUser_didMailPassword] = (void *) CUser_didMailPassword_CotC;
	gCotCCallbacks[ceCUser_didSetUserProfile] = (void *) CUser_didSetUserProfile_CotC;
	gCotCCallbacks[ceCUser_didGetUserProfile] = (void *) CUser_didGetUserProfile_CotC;
	gCotCCallbacks[ceCUser_didPublishOnMyFacebookWall] = (void *) CUser_didPublishOnMyFacebookWall_CotC;
	gCotCCallbacks[ceCUser_didReadBinary] = (void *) CUser_didReadBinary_CotC;
	gCotCCallbacks[ceCUser_didWriteBinary] = (void *) CUser_didWriteBinary_CotC;
	gCotCCallbacks[ceCUser_didRead] = (void *) CUser_didRead_CotC;
	gCotCCallbacks[ceCUser_didWrite] = (void *) CUser_didWrite_CotC;
	gCotCCallbacks[ceCUser_didSetProperties] = (void *) CUser_didSetProperties_CotC;
	gCotCCallbacks[ceCUser_didGetProperties] = (void *) CUser_didGetProperties_CotC;
	gCotCCallbacks[ceCUser_didCheckUser] = (void *) CUser_didCheckUser_CotC;
	gCotCCallbacks[ceCUser_didSetAvatarSource] = (void *) CUser_didSetAvatarSource_CotC;
	
	gCotCCallbacks[ceCGame_didScore] = (void *) CGame_didScore_CotC;
	gCotCCallbacks[ceCGame_didGetRank] = (void *) CGame_didGetRank_CotC;
	gCotCCallbacks[ceCGame_didBestHighScore] = (void *) CGame_didBestHighScore_CotC;
	gCotCCallbacks[ceCGame_didCenteredScore] = (void *) CGame_didCenteredScore_CotC;
	gCotCCallbacks[ceCGame_didGetRankArray] = (void *) CGame_didGetRankArray_CotC;
	gCotCCallbacks[ceCGame_didBestHighScoreArray] = (void *) CGame_didBestHighScoreArray_CotC;
	gCotCCallbacks[ceCGame_didReadBinary] = (void *) CGame_didReadBinary_CotC;
	gCotCCallbacks[ceCGame_didWriteBinary] = (void *) CGame_didWriteBinary_CotC;
	gCotCCallbacks[ceCGame_didRead] = (void *) CGame_didRead_CotC;
	gCotCCallbacks[ceCGame_didWrite] = (void *) CGame_didWrite_CotC;
	
	gCotCCallbacks[ceCTribe_didListUsers] = (void *) CTribe_didListUsers_CotC;
	gCotCCallbacks[ceCTribe_didListGlobalFriends] = (void *) CTribe_didListGlobalFriends_CotC;
	gCotCCallbacks[ceCTribe_didBlacklistGlobalFriends] = (void *) CTribe_didBlacklistGlobalFriends_CotC;
	gCotCCallbacks[ceCTribe_didChangeGlobalRelationshipStatus] = (void *) CTribe_didChangeGlobalRelationshipStatus_CotC;
	gCotCCallbacks[ceCTribe_didListFriends] = (void *) CTribe_didListFriends_CotC;
	gCotCCallbacks[ceCTribe_didBlacklistFriends] = (void *) CTribe_didBlacklistFriends_CotC;
	gCotCCallbacks[ceCTribe_didChangeRelationshipStatus] = (void *) CTribe_didChangeRelationshipStatus_CotC;
	gCotCCallbacks[ceCTribe_didListFacebookFriends] = (void *) CTribe_didListFacebookFriends_CotC;
	gCotCCallbacks[ceCTribe_didListGooglePlusFriends] = (void *) CTribe_didListGooglePlusFriends_CotC;
	gCotCCallbacks[ceCTribe_didListGameCenterFriends] = (void *) CTribe_didListGameCenterFriends_CotC;
	gCotCCallbacks[ceCTribe_didInviteFriendByMail] = (void *) CTribe_didInviteFriendByMail_CotC;
	gCotCCallbacks[ceCTribe_didInviteFriendByFBID] = (void *) CTribe_didInviteFriendByFBID_CotC;
	gCotCCallbacks[ceCTribe_didInviteFriendByGooglePlusID] = (void *) CTribe_didInviteFriendByGooglePlusID_CotC;
	gCotCCallbacks[ceCTribe_didFriendsBestHighScore] = (void *) CTribe_didFriendsBestHighScore_CotC;
	gCotCCallbacks[ceCTribe_didFriendsBestHighScoreArray] = (void *) CTribe_didFriendsBestHighScoreArray_CotC;
	gCotCCallbacks[ceCTribe_didFindOpponents] = (void *) CTribe_didFindOpponents_CotC;
	
	gCotCCallbacks[ceCMatch_didGetMatchData] = (void *) CMatch_didGetMatchData_CotC;
	gCotCCallbacks[ceCMatch_didListMatch] = (void *) CMatch_didListMatch_CotC;
	gCotCCallbacks[ceCMatch_didListPendingMatch] = (void *) CMatch_didListPendingMatch_CotC;
	gCotCCallbacks[ceCMatch_didCreateMatch] = (void *) CMatch_didCreateMatch_CotC;
	gCotCCallbacks[ceCMatch_didInviteFriends] = (void *) CMatch_didInviteFriends_CotC;
	gCotCCallbacks[ceCMatch_didJoinMatch] = (void *) CMatch_didJoinMatch_CotC;
	gCotCCallbacks[ceCMatch_didMatchMove] = (void *) CMatch_didMatchMove_CotC;
	gCotCCallbacks[ceCMatch_didReadBinary] = (void *) CMatch_didReadBinary_CotC;
	gCotCCallbacks[ceCMatch_didWriteBinary] = (void *) CMatch_didWriteBinary_CotC;
	gCotCCallbacks[ceCMatch_didRead] = (void *) CMatch_didRead_CotC;
	gCotCCallbacks[ceCMatch_didWrite] = (void *) CMatch_didWrite_CotC;
	
	gCotCCallbacks[ceCGooglePlay_didLoadPeople] = (void *) CGGoglePlay_didLoadPeople_CotC;
	gCotCCallbacks[ceCGooglePlay_didSubmitScore] = (void *) CGGoglePlay_didSubmitScore_CotC;
	gCotCCallbacks[ceCGooglePlay_didLoadLeaderboardMetadata] = (void *) CGGoglePlay_didLoadLeaderboardMetadata_CotC;
	gCotCCallbacks[ceCGooglePlay_didLoadLeaderboardsMetadata] = (void *) CGGoglePlay_didLoadLeaderboardsMetadata_CotC;
	gCotCCallbacks[ceCGooglePlay_didLoadPlayerCenteredScores] = (void *) CGGoglePlay_didLoadPlayerCenteredScores_CotC;
	gCotCCallbacks[ceCGooglePlay_didLoadTopScores] = (void *) CGGoglePlay_didLoadTopScores_CotC;
	gCotCCallbacks[ceCGooglePlay_didIncrementAchievement] = (void *) CGGoglePlay_didIncrementAchievement_CotC;
	gCotCCallbacks[ceCGooglePlay_didLoadAchievements] = (void *) CGGoglePlay_didLoadAchievements_CotC;
	gCotCCallbacks[ceCGooglePlay_didRevealAchievement] = (void *) CGGoglePlay_didRevealAchievement_CotC;
	gCotCCallbacks[ceCGooglePlay_didUnlockAchievement] = (void *) CGGoglePlay_didUnlockAchievement_CotC;
	
	return gCotCCallbacks;
}

void CloudBuilder_SetGlobalCotCCallback_platform(CloudBuilderMarmaladeCallback aIndex, s3eCallback aCallback, void* aUserData)
{
	if((aIndex < CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_MAX) && (aCallback != NULL) && (aCallback != gGlobalCotCCallbacks[aIndex]))
	{
		CloudBuilderMarmaladeUnRegister(aIndex, (s3eCallback) gGlobalCotCCallbacks[aIndex]);
		gGlobalCotCCallbacks[aIndex] = (void *) aCallback;
		CloudBuilderMarmaladeRegister(aIndex, aCallback, aUserData);
	}
}

void CloudBuilder_PopCallback_platform()
{
	void (*cloudbuilder_popcallback)(void);
	
	cloudbuilder_popcallback = (void (*)(void)) gCotCFunctions[eCloudBuilder_PopCallback];
	cloudbuilder_popcallback();
}

s3eResult Clan_Setup_platform(const char* aConfigurationJson, s3eCallback aClan_didSetup, void* aUserData)
{
	int  err;
	int (*clan_setup)(const char*);

	clan_setup = (int (*)(const char*)) gCotCFunctions[eClan_Setup];
	err = clan_setup(aConfigurationJson);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_CLAN_DID_SETUP, aClan_didSetup, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CClan::Setup failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Clan_BatchBegin_platform()
{
	int  err;
	int (*clan_batchbegin)(void);
	
	clan_batchbegin = (int (*)(void)) gCotCFunctions[eClan_BatchBegin];
	err = clan_batchbegin();

	if(err == 0)
		return S3E_RESULT_SUCCESS;
	
	IwDebugTraceLinePrintf("CClan::BatchBegin: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Clan_BatchEnd_platform(s3eCallback aClan_didBatchEnd, void* aUserData)
{
	int  err;
	int (*clan_batchend)(void);
	
	clan_batchend = (int (*)(void)) gCotCFunctions[eClan_BatchEnd];
	err = clan_batchend();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_CLAN_DID_BATCH_END, aClan_didBatchEnd, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CClan::BatchEnd failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

bool Clan_isSetup_platform()
{
	bool (*clan_issetup)(void);
	
	clan_issetup = (bool (*)(void)) gCotCFunctions[eClan_isSetup];
	return clan_issetup();
}

bool Clan_isUserLogged_platform()
{
	bool (*clan_isuserlogged)(void);
	
	clan_isuserlogged = (bool (*)(void)) gCotCFunctions[eClan_isUserLogged];
	return clan_isuserlogged();
}

s3eResult User_RegisterAndLogin_platform(const char* aEmail, const char* aPassword, const char* aPseudo, s3eCallback aUser_didRegisterAndLogin, void* aUserData)
{
	int  err;
	int (*cuser_registerandlogin)(const char*, const char*, const char*);
	
	cuser_registerandlogin = (int (*)(const char*, const char*, const char*)) gCotCFunctions[eUser_RegisterAndLogin];
	err = cuser_registerandlogin(aEmail, aPassword, aPseudo);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_REGISTER_AND_LOGIN, aUser_didRegisterAndLogin, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::RegisterAndLogin failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_Login_platform(const char* aPseudo, const char* aPassword, s3eCallback aUser_didLogin, void* aUserData)
{
	int  err;
	int (*cuser_login)(const char*, const char*);
	
	cuser_login = (int (*)(const char*, const char*)) gCotCFunctions[eUser_Login];
	err = cuser_login(aPseudo, aPassword);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LOGIN, aUser_didLogin, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::Login failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_LoginWithFacebook_platform(const char* aOptionalPassword, s3eCallback aUser_didLoginWithFacebook, void* aUserData)
{
	int  err;
	int (*cuser_loginwithfacebook)(const char*);
	
	cuser_loginwithfacebook = (int (*)(const char*)) gCotCFunctions[eUser_LoginWithFacebook];
	err = cuser_loginwithfacebook(aOptionalPassword);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LOGIN_WITH_FACEBOOK, aUser_didLoginWithFacebook, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::LoginWithFacebook failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_LoginWithGooglePlus_platform(const char* aOptionalPassword, s3eCallback aUser_didLoginWithGooglePlus, void* aUserData)
{
	int  err;
	int (*cuser_loginwithgoogleplus)(const char*);
	
	cuser_loginwithgoogleplus = (int (*)(const char*)) gCotCFunctions[eUser_LoginWithGooglePlus];
	err = cuser_loginwithgoogleplus(aOptionalPassword);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LOGIN_WITH_GOOGLEPLUS, aUser_didLoginWithGooglePlus, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::LoginWithGooglePlus failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_LoginWithGameCenter_platform(s3eCallback aUser_didLoginWithGameCenter, void* aUserData)
{
	int  err;
	int (*cuser_loginwithgamecenter)(void);
	
	cuser_loginwithgamecenter = (int (*)(void)) gCotCFunctions[eUser_LoginWithGameCenter];
	err = cuser_loginwithgamecenter();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LOGIN_WITH_GAMECENTER, aUser_didLoginWithGameCenter, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::LoginWithGameCenter failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_Logout_platform(s3eCallback aUser_didLogout, void* aUserData)
{
	int  err;
	int (*cuser_logout)(void);
	
	cuser_logout = (int (*)(void)) gCotCFunctions[eUser_Logout];
	err = cuser_logout();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LOGOUT, aUser_didLogout, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::Logout failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_LinkAccountWithFacebook_platform(s3eCallback aUser_didLinkAccountWithFacebook, void* aUserData)
{
	int  err;
	int (*cuser_linkaccountwithfacebook)(void);
	
	cuser_linkaccountwithfacebook = (int (*)(void)) gCotCFunctions[eUser_LinkAccountWithFacebook];
	err = cuser_linkaccountwithfacebook();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LINK_ACCOUNT_WITH_FACEBOOK, aUser_didLinkAccountWithFacebook, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::LinkAccountWithFacebook failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_LinkAccountWithGooglePlus_platform(s3eCallback aUser_didLinkAccountWithGooglePlus, void* aUserData)
{
	int  err;
	int (*cuser_linkaccountwithgoogleplus)(void);
	
	cuser_linkaccountwithgoogleplus = (int (*)(void)) gCotCFunctions[eUser_LinkAccountWithGooglePlus];
	err = cuser_linkaccountwithgoogleplus();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LINK_ACCOUNT_WITH_GOOGLEPLUS, aUser_didLinkAccountWithGooglePlus, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::LinkAccountWithGooglePlus failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_LinkAccountWithGameCenter_platform(s3eCallback aUser_didLinkAccountWithGameCenter, void* aUserData)
{
	int  err;
	int (*cuser_linkaccountwithgamecenter)(void);
	
	cuser_linkaccountwithgamecenter = (int (*)(void)) gCotCFunctions[eUser_LinkAccountWithGameCenter];
	err = cuser_linkaccountwithgamecenter();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LINK_ACCOUNT_WITH_GAMECENTER, aUser_didLinkAccountWithGameCenter, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::LinkAccountWithGameCenter failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_ChangePassword_platform(const char* aOldPassword, const char* aNewPassword, s3eCallback aUser_didChangePassword, void* aUserData)
{
	int  err;
	int (*cuser_changepassword)(const char*, const char*);
	
	cuser_changepassword = (int (*)(const char*, const char*)) gCotCFunctions[eUser_ChangePassword];
	err = cuser_changepassword(aOldPassword, aNewPassword);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_CHANGE_PASSWORD, aUser_didChangePassword, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::ChangePassword failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_MailPassword_platform(const char* aEmail, const char* aSubject, const char* aBody, s3eCallback aUser_didMailPassword, void* aUserData)
{
	int  err;
	int (*cuser_mailpassword)(const char*, const char*, const char*);
	
	cuser_mailpassword = (int (*)(const char*, const char*, const char*)) gCotCFunctions[eUser_MailPassword];
	err = cuser_mailpassword(aEmail, aSubject, aBody);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_MAIL_PASSWORD, aUser_didMailPassword, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::MailPassword failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_SetUserProfile_platform(const char* aJson, s3eCallback aUser_didSetUserProfile, void* aUserData)
{
	int  err;
	int (*cuser_setuserprofile)(const char*);
	
	cuser_setuserprofile = (int (*)(const char*)) gCotCFunctions[eUser_SetUserProfile];
	err = cuser_setuserprofile(aJson);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_SET_USER_PROFILE, aUser_didSetUserProfile, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::SetUserProfile failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_GetUserProfile_platform(s3eCallback aUser_didGetUserProfile, void* aUserData)
{
	int  err;
	int (*cuser_getuserprofile)(void);
	
	cuser_getuserprofile = (int (*)(void)) gCotCFunctions[eUser_GetUserProfile];
	err = cuser_getuserprofile();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_GET_USER_PROFILE, aUser_didGetUserProfile, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::GetUserProfile failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

const char* User_GetPseudo_platform()
{
	const char* (*user_getpseudo)(void);
	
	user_getpseudo = (const char* (*)(void)) gCotCFunctions[eUser_GetPseudo];
	return user_getpseudo();
}

const char* User_GetMail_platform()
{
	const char* (*user_getmail)(void);
	
	user_getmail = (const char* (*)(void)) gCotCFunctions[eUser_GetMail];
	return user_getmail();
}

s3eResult User_PublishOnMyFacebookWall_platform(const char* aMessage, s3eCallback aUser_didPublishOnMyFacebookWall, void* aUserData)
{
	int  err;
	int (*cuser_publishonmyfacebookwall)(const char*);
	
	cuser_publishonmyfacebookwall = (int (*)(const char*)) gCotCFunctions[eUser_PublishOnMyFacebookWall];
	err = cuser_publishonmyfacebookwall(aMessage);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_PUBLISH_ON_MY_FACEBOOK_WALL, aUser_didPublishOnMyFacebookWall, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::PublishOnMyFacebookWall failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_ReadBinary_platform(const char* aKey, s3eCallback aUser_didReadBinary, void* aUserData)
{
	int  err;
	int (*cuser_readbinary)(const char*);
	
	cuser_readbinary = (int (*)(const char*)) gCotCFunctions[eUser_ReadBinary];
	err = cuser_readbinary(aKey);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_READ_BINARY, aUser_didReadBinary, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::ReadBinary failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_WriteBinary_platform(const char* aKey, void* aPointer, unsigned long aLength, s3eCallback aUser_didWriteBinary, void* aUserData)
{
	int  err;
	int (*cuser_writebinary)(const char*, void*, unsigned long);
	
	cuser_writebinary = (int (*)(const char*, void*, unsigned long)) gCotCFunctions[eUser_WriteBinary];
	err = cuser_writebinary(aKey, aPointer, aLength);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_WRITE_BINARY, aUser_didWriteBinary, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::WriteBinary failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_Read_platform(const char* aKey, s3eCallback aUser_didRead, void* aUserData)
{
	int  err;
	int (*cuser_read)(const char*);
	
	cuser_read = (int (*)(const char*)) gCotCFunctions[eUser_Read];
	err = cuser_read(aKey);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_READ, aUser_didRead, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::Read failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_Write_platform(const char* aKey, const char* aValue, s3eCallback aUser_didWrite, void* aUserData)
{
	int  err;
	int (*cuser_write)(const char*, const char*);
	
	cuser_write = (int (*)(const char*, const char*)) gCotCFunctions[eUser_Write];
	err = cuser_write(aKey, aValue);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_WRITE, aUser_didWrite, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::Write failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_SetProperties_platform(bool aCanBeFound, const char* aPropertiesJson, s3eCallback aUser_didSetProperties, void* aUserData)
{
	int  err;
	int (*cuser_setproperties)(bool, const char*);
	
	cuser_setproperties = (int (*)(bool, const char*)) gCotCFunctions[eUser_SetProperties];
	err = cuser_setproperties(aCanBeFound, aPropertiesJson);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_SET_PROPERTIES, aUser_didSetProperties, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::SetProperties failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_GetProperties_platform(s3eCallback aUser_didGetProperties, void* aUserData)
{
	int  err;
	int (*cuser_getproperties)(void);
	
	cuser_getproperties = (int (*)(void)) gCotCFunctions[eUser_GetProperties];
	err = cuser_getproperties();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_GET_PROPERTIES, aUser_didGetProperties, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::GetProperties failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_CheckUser_platform(const char* aIdent, s3eCallback aUser_didCheckUser, void* aUserData)
{
	int  err;
	int (*cuser_checkuser)(const char*);
	
	cuser_checkuser = (int (*)(const char*)) gCotCFunctions[eUser_CheckUser];
	err = cuser_checkuser(aIdent);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_CHECK_USER, aUser_didCheckUser, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::CheckUser failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult User_SetAvatarSource_platform(cbmExternalNetwork aSource, s3eCallback aUser_didSetAvatarSource, void* aUserData)
{
	int  err;
	int (*cuser_setavatarsource)(int);
	
	cuser_setavatarsource = (int (*)(int)) gCotCFunctions[eUser_SetAvatarSource];
	err = cuser_setavatarsource((int) aSource);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_SET_AVATAR_SOURCE, aUser_didSetAvatarSource, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CUserManager::SetAvatarSource failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Game_Score_platform(long long aHighScore, const char* aMode, cbmScoreType aScoreType, const char* aInfoScore, bool aMayVary, s3eCallback aGame_didScore, void* aUserData)
{
	int  err;
	int (*cgame_score)(long long, const char*, int, const char*, bool);
	
	cgame_score = (int (*)(long long, const char*, int, const char*, bool)) gCotCFunctions[eGame_Score];
	err = cgame_score(aHighScore, aMode, (int) aScoreType, aInfoScore, aMayVary);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_SCORE, aGame_didScore, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGameManager::Score failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Game_GetRank_platform(long long aHighScore, const char* aMode, cbmScoreType aScoreType, s3eCallback aGame_didGetRank, void* aUserData)
{
	int  err;
	int (*cgame_getrank)(long long, const char*, int);
	
	cgame_getrank = (int (*)(long long, const char*, int)) gCotCFunctions[eGame_GetRank];
	err = cgame_getrank(aHighScore, aMode, (int) aScoreType);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_GET_RANK, aGame_didGetRank, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGameManager::GetRank failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Game_BestHighScore_platform(int aCount, const char* aMode, cbmScoreType aScoreType, s3eCallback aGame_didBestHighScore, void* aUserData)
{
	int  err;
	int (*cgame_besthighscore)(int, const char*, int);
	
	cgame_besthighscore = (int (*)(int, const char*, int)) gCotCFunctions[eGame_BestHighScore];
	err = cgame_besthighscore(aCount, aMode, (int) aScoreType);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_BEST_HIGH_SCORE, aGame_didBestHighScore, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGameManager::BestHighScore failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Game_CenteredScore_platform(int aCount, const char* aMode, cbmScoreType aScoreType, s3eCallback aGame_didCenteredScore, void* aUserData)
{
	int  err;
	int (*cgame_centeredscore)(int, const char*, int);
	
	cgame_centeredscore = (int (*)(int, const char*, int)) gCotCFunctions[eGame_CenteredScore];
	err = cgame_centeredscore(aCount, aMode, (int) aScoreType);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_CENTERED_SCORE, aGame_didCenteredScore, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGameManager::CenteredScore failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;}

s3eResult Game_GetRankArray_platform(const char* aScoreArrayJson, cbmScoreType aScoreType, s3eCallback aGame_didGetRankArray, void* aUserData)
{
	int  err;
	int (*cgame_getrankarray)(const char*, int);
	
	cgame_getrankarray = (int (*)(const char*, int)) gCotCFunctions[eGame_GetRankArray];
	err = cgame_getrankarray(aScoreArrayJson, (int) aScoreType);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_GET_RANK_ARRAY, aGame_didGetRankArray, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGameManager::GetRankArray failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Game_BestHighScoreArray_platform(int aCount, const char* aArrayModesJson, cbmScoreType aScoreType, s3eCallback aGame_didBestHighScoreArray, void* aUserData)
{
	int  err;
	int (*cgame_besthighscorearray)(int, const char*, int);
	
	cgame_besthighscorearray = (int (*)(int, const char*, int)) gCotCFunctions[eGame_BestHighScoreArray];
	err = cgame_besthighscorearray(aCount, aArrayModesJson, (int) aScoreType);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_BEST_HIGH_SCORE_ARRAY, aGame_didBestHighScoreArray, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGameManager::BestHighScoreArray failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Game_ReadBinary_platform(const char* aKey, s3eCallback aGame_didReadBinary, void* aUserData)
{
	int  err;
	int (*cgame_readbinary)(const char*);
	
	cgame_readbinary = (int (*)(const char*)) gCotCFunctions[eGame_ReadBinary];
	err = cgame_readbinary(aKey);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_READ_BINARY, aGame_didReadBinary, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGameManager::ReadBinary failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Game_WriteBinary_platform(const char* aKey, void* aPointer, unsigned long aLength, s3eCallback aGame_didWriteBinary, void* aUserData)
{
	int  err;
	int (*cgame_writebinary)(const char*, void*, unsigned long);
	
	cgame_writebinary = (int (*)(const char*, void*, unsigned long)) gCotCFunctions[eGame_WriteBinary];
	err = cgame_writebinary(aKey, aPointer, aLength);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_WRITE_BINARY, aGame_didWriteBinary, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGameManager::WriteBinary failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Game_Read_platform(const char* aKey, s3eCallback aGame_didRead, void* aUserData)
{
	int  err;
	int (*cgame_read)(const char*);
	
	cgame_read = (int (*)(const char*)) gCotCFunctions[eGame_Read];
	err = cgame_read(aKey);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_READ, aGame_didRead, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGameManager::Read failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Game_Write_platform(const char* aKey, const char* aValue, s3eCallback aGame_didWrite, void* aUserData)
{
	int  err;
	int (*cgame_write)(const char*, const char*);
	
	cgame_write = (int (*)(const char*, const char*)) gCotCFunctions[eGame_Write];
	err = cgame_write(aKey, aValue);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_WRITE, aGame_didWrite, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGameManager::Write failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_ListUsers_platform(const char* aContainsString, s3eCallback aTribe_didListUsers, void* aUserData)
{
	int  err;
	int (*ctribe_listusers)(const char*);
	
	ctribe_listusers = (int (*)(const char*)) gCotCFunctions[eTribe_ListUsers];
	err = ctribe_listusers(aContainsString);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_USERS, aTribe_didListUsers, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::ListUsers failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_ListGlobalFriends_platform(s3eCallback aTribe_didListGlobalFriends, void* aUserData)
{
	int  err;
	int (*ctribe_listglobalfriends)(void);
	
	ctribe_listglobalfriends = (int (*)(void)) gCotCFunctions[eTribe_ListGlobalFriends];
	err = ctribe_listglobalfriends();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_GLOBAL_FRIENDS, aTribe_didListGlobalFriends, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::ListGlobalFriends failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_BlacklistGlobalFriends_platform(s3eCallback aTribe_didBlacklistGlobalFriends, void* aUserData)
{
	int  err;
	int (*ctribe_blacklistglobalfriends)(void);
	
	ctribe_blacklistglobalfriends = (int (*)(void)) gCotCFunctions[eTribe_BlacklistGlobalFriends];
	err = ctribe_blacklistglobalfriends();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_BLACKLIST_GLOBAL_FRIENDS, aTribe_didBlacklistGlobalFriends, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::BlackistGlobalFriends failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_ChangeGlobalRelationshipStatus_platform(const char* aFriendPseudo, cbmRelationChange aNewState, s3eCallback aTribe_didChangeGlobalRelationshipStatus, void* aUserData)
{
	int  err;
	int (*ctribe_changeglobalrelationshipstatus)(const char*, int);
	
	ctribe_changeglobalrelationshipstatus = (int (*)(const char*, int)) gCotCFunctions[eTribe_ChangeGlobalRelationshipStatus];
	err = ctribe_changeglobalrelationshipstatus(aFriendPseudo,(int) aNewState);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_CHANGE_GLOBAL_RELATIONSHIP_STATUS, aTribe_didChangeGlobalRelationshipStatus, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::ChangeGlobalRelationshipStatus failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_ListFriends_platform(s3eCallback aTribe_didListFriends, void* aUserData)
{
	int  err;
	int (*ctribe_listfriends)(void);
	
	ctribe_listfriends = (int (*)(void)) gCotCFunctions[eTribe_ListFriends];
	err = ctribe_listfriends();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_FRIENDS, aTribe_didListFriends, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::ListFriends failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_BlacklistFriends_platform(s3eCallback aTribe_didBlacklistFriends, void* aUserData)
{
	int  err;
	int (*ctribe_blacklistfriends)(void);
	
	ctribe_blacklistfriends = (int (*)(void)) gCotCFunctions[eTribe_BlacklistFriends];
	err = ctribe_blacklistfriends();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_BLACKLIST_FRIENDS, aTribe_didBlacklistFriends, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::BlacklistFriends failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_ChangeRelationshipStatus_platform(const char* aFriendPseudo, cbmRelationChange aNewState, s3eCallback aTribe_didChangeRelationshipStatus, void* aUserData)
{
	int  err;
	int (*ctribe_changerelationshipstatus)(const char*, int);
	
	ctribe_changerelationshipstatus = (int (*)(const char*, int)) gCotCFunctions[eTribe_ChangeRelationshipStatus];
	err = ctribe_changerelationshipstatus(aFriendPseudo,(int) aNewState);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_CHANGE_RELATIONSHIP_STATUS, aTribe_didChangeRelationshipStatus, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::ChangeRelationshipStatus failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_ListFacebookFriends_platform(s3eCallback aTribe_didListFacebookFriends, void* aUserData)
{
	int  err;
	int (*ctribe_listfacebookfriends)(void);
	
	ctribe_listfacebookfriends = (int (*)(void)) gCotCFunctions[eTribe_ListFacebookFriends];
	err = ctribe_listfacebookfriends();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_FACEBOOK_FRIENDS, aTribe_didListFacebookFriends, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::ListFacebookFriends failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_ListGooglePlusFriends_platform(s3eCallback aTribe_didListGooglePlusFriends, void* aUserData)
{
	int  err;
	int (*ctribe_listgoogleplusfriends)(void);
	
	ctribe_listgoogleplusfriends = (int (*)(void)) gCotCFunctions[eTribe_ListGooglePlusFriends];
	err = ctribe_listgoogleplusfriends();
   
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_GOOGLEPLUS_FRIENDS, aTribe_didListGooglePlusFriends, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::ListGooglePlusFriends failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_ListGameCenterFriends_platform(s3eCallback aTribe_didListGameCenterFriends, void* aUserData)
{
	int  err;
	int (*ctribe_listgamecenterfriends)(void);
	
	ctribe_listgamecenterfriends = (int (*)(void)) gCotCFunctions[eTribe_ListGameCenterFriends];
	err = ctribe_listgamecenterfriends();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_GAMECENTER_FRIENDS, aTribe_didListGameCenterFriends, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::ListGameCenterFriends failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_InviteFriendByMail_platform(const char* aEmail, const char* aSubject, const char* aBody, s3eCallback aTribe_didInviteFriendByMail, void* aUserData)
{
	int  err;
	int (*ctribe_invitefriendbymail)(const char*, const char*, const char*);
	
	ctribe_invitefriendbymail = (int (*)(const char*, const char*, const char*)) gCotCFunctions[eTribe_InviteFriendByMail];
	err = ctribe_invitefriendbymail(aEmail, aSubject, aBody);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_INVITE_FRIEND_BY_MAIL, aTribe_didInviteFriendByMail, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::InviteFriendByMail failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_InviteFriendByFBID_platform(const char* aFBFriendID, const char* aParamsJson, s3eCallback aTribe_didInviteFriendByFBID, void* aUserData)
{
	int  err;
	int (*ctribe_invitefriendbyfbid)(const char*, const char*);
	
	ctribe_invitefriendbyfbid = (int (*)(const char*, const char*)) gCotCFunctions[eTribe_InviteFriendByFBID];
	err = ctribe_invitefriendbyfbid(aFBFriendID, aParamsJson);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_INVITE_FRIEND_BY_FBID, aTribe_didInviteFriendByFBID, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::InviteFriendByFBID failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_InviteFriendByGooglePlusID_platform(const char* aGooglePlusFriendID, const char* aParamsJson, s3eCallback aTribe_didInviteFriendByGooglePlusID, void* aUserData)
{
	int  err;
	int (*ctribe_invitefriendbygoogleplusid)(const char*, const char*);
	
	ctribe_invitefriendbygoogleplusid = (int (*)(const char*, const char*)) gCotCFunctions[eTribe_InviteFriendByGooglePlusID];
	err = ctribe_invitefriendbygoogleplusid(aGooglePlusFriendID, aParamsJson);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_INVITE_FRIEND_BY_GOOGLEPLUSID, aTribe_didInviteFriendByGooglePlusID, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::InviteFriendByGooglePlusID failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_FriendsBestHighScore_platform(const char* aMode, cbmScoreType aScoreType, s3eCallback aTribe_didFriendsBestHighScore, void* aUserData)
{
	int  err;
	int (*ctribe_friendsbesthighscore)(const char*, int);
	
	ctribe_friendsbesthighscore = (int (*)(const char*, int)) gCotCFunctions[eTribe_FriendsBestHighScore];
	err = ctribe_friendsbesthighscore(aMode, (int) aScoreType);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_FRIENDS_BEST_HIGH_SCORE, aTribe_didFriendsBestHighScore, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::FriendsBestHighScore failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_FriendsBestHighScoreArray_platform(const char* aArrayModesJson, cbmScoreType aScoreType, s3eCallback aTribe_didFriendsBestHighScoreArray, void* aUserData)
{
	int  err;
	int (*ctribe_friendsbesthighscorearray)(const char*, int);
	
	ctribe_friendsbesthighscorearray = (int (*)(const char*, int)) gCotCFunctions[eTribe_FriendsBestHighScoreArray];
	err = ctribe_friendsbesthighscorearray(aArrayModesJson, (int) aScoreType);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_FRIENDS_BEST_HIGH_SCORE_ARRAY, aTribe_didFriendsBestHighScoreArray, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::FriendsBestHighScoreArray failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_FindOpponents_platform(const char* aFilterJson, s3eCallback aTribe_didFindOpponents, void* aUserData)
{
	int  err;
	int (*ctribe_findopponents)(const char*);
	
	ctribe_findopponents = (int (*)(const char*)) gCotCFunctions[eTribe_FindOpponents];
	err = ctribe_findopponents(aFilterJson);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_FIND_OPPONENTS, aTribe_didFindOpponents, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::FindOpponents failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

const char* Match_GetActiveMatchID_platform()
{
	const char* (*cmatch_getactivematchid)(void);
	
	cmatch_getactivematchid = (const char* (*)(void)) gCotCFunctions[eMatch_GetActiveMatchID];
	return cmatch_getactivematchid();
}

bool Match_HasActiveMatch_platform()
{
	bool (*cmatch_hasactivematch)(void);
	
	cmatch_hasactivematch = (bool (*)(void)) gCotCFunctions[eMatch_HasActiveMatch];
	return cmatch_hasactivematch();
}

s3eResult Match_GetMatchData_platform(const char* aMatchID, s3eCallback aMatch_didGetMatchData, void* aUserData)
{
	int  err;
	int (*cmatch_getmatchdata)(const char*);
	
	cmatch_getmatchdata = (int (*)(const char*)) gCotCFunctions[eMatch_GetMatchData];
	err = cmatch_getmatchdata(aMatchID);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_GET_MATCH_DATA, aMatch_didGetMatchData, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CMatchManager::GetMatchData failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Match_ListMatch_platform(bool aIncludeAllData, s3eCallback aMatch_didListMatch, void* aUserData)
{
	int  err;
	int (*cmatch_listmatch)(bool);
	
	cmatch_listmatch = (int (*)(bool)) gCotCFunctions[eMatch_ListMatch];
	err = cmatch_listmatch(aIncludeAllData);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_LIST_MATCH, aMatch_didListMatch, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CMatchManager::ListMatch failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Match_ListPendingMatch_platform(s3eCallback aMatch_didListPendingMatch, void* aUserData)
{
	int  err;
	int (*cmatch_listpendingmatch)(void);
	
	cmatch_listpendingmatch = (int (*)(void)) gCotCFunctions[eMatch_ListPendingMatch];
	err = cmatch_listpendingmatch();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_LIST_PENDING_MATCH, aMatch_didListPendingMatch, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CMatchManager::ListPendingMatch failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Match_CreateMatch_platform(const char* aName, bool aPrivateMatch, const char* aMatchDataJson, s3eCallback aMatch_didCreateMatch, void* aUserData)
{
	int  err;
	int (*cmatch_creatematch)(const char*, bool, const char*);
	
	cmatch_creatematch = (int (*)(const char*, bool, const char*)) gCotCFunctions[eMatch_CreateMatch];
	err = cmatch_creatematch(aName, aPrivateMatch, aMatchDataJson);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_CREATE_MATCH, aMatch_didCreateMatch, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CMatchManager::CreateMatch failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Match_InviteFriends_platform(const char* aMatchID, const char* aArrayFriendsJson, bool aAutoAccept, const char* aNotifMessageJson, s3eCallback aMatch_didInviteFriends, void* aUserData)
{
	int  err;
	int (*cmatch_invitefriends)(const char*, const char*, bool, const char*);
	
	cmatch_invitefriends = (int (*)(const char*, const char*, bool, const char*)) gCotCFunctions[eMatch_InviteFriends];
	err = cmatch_invitefriends(aMatchID, aArrayFriendsJson, aAutoAccept, aNotifMessageJson);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_INVITE_FRIENDS, aMatch_didInviteFriends, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CMatchManager::InviteFriends failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Match_JoinMatch_platform(const char* aMatchID, bool aAccept, const char* aNotifMessageJson, s3eCallback aMatch_didJoinMatch, void* aUserData)
{
	int  err;
	int (*cmatch_joinmatch)(const char*, bool, const char*);
	
	cmatch_joinmatch = (int (*)(const char*, bool, const char*)) gCotCFunctions[eMatch_JoinMatch];
	err = cmatch_joinmatch(aMatchID, aAccept, aNotifMessageJson);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_JOIN_MATCH, aMatch_didJoinMatch, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CMatchManager::JoinMatch failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Match_MatchMove_platform(cbmMatchPhase aMatchPhase, const char* aMatchID, const char* aMatchStateJson, const char* aNotifMessageJson, s3eCallback aMatch_didMatchMove, void* aUserData)
{
	int  err;
	int (*cmatch_matchmove)(int, const char*, const char*, const char*);
	
	cmatch_matchmove = (int (*)(int, const char*, const char*, const char*)) gCotCFunctions[eMatch_MatchMove];
	err = cmatch_matchmove((int) aMatchPhase, aMatchID, aMatchStateJson, aNotifMessageJson);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_MATCH_MOVE, aMatch_didMatchMove, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CMatchManager::MatchMove failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Match_ReadBinary_platform(const char* aMatchID, const char* aKey, s3eCallback aMatch_didReadBinary, void* aUserData)
{
	int  err;
	int (*cmatch_readbinary)(const char*, const char*);
	
	cmatch_readbinary = (int (*)(const char*, const char*)) gCotCFunctions[eMatch_ReadBinary];
	err = cmatch_readbinary(aMatchID, aKey);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_READ_BINARY, aMatch_didReadBinary, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CMatchManager::ReadBinary failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Match_WriteBinary_platform(const char* aMatchID, const char* aKey, void* aPointer, unsigned long aLength, s3eCallback aMatch_didWriteBinary, void* aUserData)
{
	int  err;
	int (*cmatch_writebinary)(const char*, const char*, void*, unsigned long);
	
	cmatch_writebinary = (int (*)(const char*, const char*, void*, unsigned long)) gCotCFunctions[eMatch_WriteBinary];
	err = cmatch_writebinary(aMatchID, aKey, aPointer, aLength);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_WRITE_BINARY, aMatch_didWriteBinary, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CMatchManager::WriteBinary failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Match_Read_platform(const char* aMatchID, const char* aKey, s3eCallback aMatch_didRead, void* aUserData)
{
	int  err;
	int (*cmatch_read)(const char*, const char*);
	
	cmatch_read = (int (*)(const char*, const char*)) gCotCFunctions[eMatch_Read];
	err = cmatch_read(aMatchID, aKey);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_READ, aMatch_didRead, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CMatchManager::Read failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Match_Write_platform(const char* aMatchID, const char* aKey, const char* aValue, s3eCallback aMatch_didWrite, void* aUserData)
{
	int  err;
	int (*cmatch_write)(const char*, const char*, const char*);
	
	cmatch_write = (int (*)(const char*, const char*, const char*)) gCotCFunctions[eMatch_Write];
	err = cmatch_write(aMatchID, aKey, aValue);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_WRITE, aMatch_didWrite, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CMatchManager::Write failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Notification_NotifyUser_platform(const char* aUserPseudo, const char* aDataJson, void* aReference, const char* apnMessageJson, s3eCallback aNotification_didNotifyUser, void* aUserData)
{
/*	eErrorCode  err;
	CHJSON*	 json;
	
	json	= CHJSON::parse(aDataJson);
	err = CNotificationManager::Instance()->NotifyUser(aUserPseudo, json, aReference);
	delete json;
	
	if(err == enNoErr)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_NOTIFICATION_DID_NOTIFY_USER, aNotification_didNotifyUser, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CNotificationManager::NotifyUser failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
*/	return S3E_RESULT_ERROR;
}

bool GooglePlay_IsConnected_platform()
{
	bool (*cgoogleplay_isconnected)(void);
	
	cgoogleplay_isconnected = (bool (*)(void)) gCotCFunctions[eGooglePlay_IsConnected];
	return cgoogleplay_isconnected();
}

s3eResult GooglePlay_LoadPeople_platform(const char* aListPeopleJSON, s3eCallback aGooglePlay_didLoadPeople, void* aUserData)
{
	int  err;
	int (*cgoogleplay_loadpeople)(const char*);
	
	cgoogleplay_loadpeople = (int (*)(const char*)) gCotCFunctions[eGooglePlay_LoadPeople];
	err = cgoogleplay_loadpeople(aListPeopleJSON);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_PEOPLE, aGooglePlay_didLoadPeople, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGooglePlay::LoadPeople failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_ShowAllLeaderboards_platform()
{
	int err;
	
	int (*cgoogleplay_showallleaderboards)(void);
	
	cgoogleplay_showallleaderboards = (int (*)(void)) gCotCFunctions[eGooglePlay_ShowAllLeaderboards];
	err = cgoogleplay_showallleaderboards();
	if(err == 0)
		return S3E_RESULT_SUCCESS;

	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_ShowLeaderboard_platform(const char* aLeaderboardID)
{
	int err;
	
	int (*cgoogleplay_showleaderboard)(const char*);
	
	cgoogleplay_showleaderboard = (int (*)(const char*)) gCotCFunctions[eGooglePlay_ShowLeaderboard];
	err = cgoogleplay_showleaderboard(aLeaderboardID);
	if(err == 0)
		return S3E_RESULT_SUCCESS;
	
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_SubmitScore_platform(const char* aLeaderboardID, long aScore, const char* aTag, s3eCallback aGooglePlay_didSubmitScore, void* aUserData)
{
	int  err;
	int (*cgoogleplay_submitscore)(const char*, long, const char*);
	
	cgoogleplay_submitscore = (int (*)(const char*, long, const char*)) gCotCFunctions[eGooglePlay_SubmitScore];
	err = cgoogleplay_submitscore(aLeaderboardID, aScore, aTag);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_SUBMIT_SCORE, aGooglePlay_didSubmitScore, aUserData);

		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGooglePlay::SubmitScore failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_LoadLeaderboardMetadata_platform(const char* aLeaderboardID, s3eCallback aGooglePlay_didLoadLeaderboardMetadata, void* aUserData)
{
	int  err;
	int (*cgoogleplay_loadleaderboardmetadata)(const char*);
	
	cgoogleplay_loadleaderboardmetadata = (int (*)(const char*)) gCotCFunctions[eGooglePlay_LoadLeaderboardMetadata];
	err = cgoogleplay_loadleaderboardmetadata(aLeaderboardID);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_LEADERBOARD_METADATA, aGooglePlay_didLoadLeaderboardMetadata, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGooglePlay::LoadLeaderboardMetadata failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_LoadLeaderboardsMetadata_platform(s3eCallback aGooglePlay_didLoadLeaderboardsMetadata, void* aUserData)
{
	int  err;
	int (*cgoogleplay_loadleaderboardsmetadata)(void);
	
	cgoogleplay_loadleaderboardsmetadata = (int (*)(void)) gCotCFunctions[eGooglePlay_LoadLeaderboardsMetadata];
	err = cgoogleplay_loadleaderboardsmetadata();
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_LEADERBOARDS_METADATA, aGooglePlay_didLoadLeaderboardsMetadata, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGooglePlay::LoadLeaderboardsMetadata failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_LoadPlayerCenteredScores_platform(const char* aLeaderboardID, cbmGooglePlayTimeSpan aSpan, cbmGooglePlayLeaderboardCollection aLeaderboardCollection, int aMaxResults, bool aForceReload, s3eCallback aGooglePlay_didLoadPlayerCenteredScores, void* aUserData)
{
	int  err;
	int (*cgoogleplay_loadplayercenteredscores)(const char*, int, int, int, bool);
	
	cgoogleplay_loadplayercenteredscores = (int (*)(const char*, int, int, int, bool)) gCotCFunctions[eGooglePlay_LoadPlayerCenteredScores];
	err = cgoogleplay_loadplayercenteredscores(aLeaderboardID, (int) aSpan, (int) aLeaderboardCollection, aMaxResults, aForceReload);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_PLAYER_CENTERED_SCORES, aGooglePlay_didLoadPlayerCenteredScores, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGooglePlay::LoadPlayerCenteredScores failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_LoadTopScores_platform(const char* aLeaderboardID, cbmGooglePlayTimeSpan aSpan, cbmGooglePlayLeaderboardCollection aLeaderboardCollection, int aMaxResults, bool aForceReload, s3eCallback aGooglePlay_didLoadTopScores, void* aUserData)
{
	int  err;
	int (*cgoogleplay_loadtopscores)(const char*, int, int, int, bool);
	
	cgoogleplay_loadtopscores = (int (*)(const char*, int, int, int, bool)) gCotCFunctions[eGooglePlay_LoadTopScores];
	err = cgoogleplay_loadtopscores(aLeaderboardID, (int) aSpan, (int) aLeaderboardCollection, aMaxResults, aForceReload);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_TOP_SCORES, aGooglePlay_didLoadTopScores, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGooglePlay::LoadTopScores failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_ShowAchievements_platform()
{
	int err;
	
	int (*cgoogleplay_showachievements)(void);
	
	cgoogleplay_showachievements = (int (*)(void)) gCotCFunctions[eGooglePlay_ShowAchievements];
	err = cgoogleplay_showachievements();
	if(err == 0)
		return S3E_RESULT_SUCCESS;
	
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_IncrementAchievement_platform(const char* aAchievementID, int aNumSteps, s3eCallback aGooglePlay_didIncrementAchievement, void* aUserData)
{
	int  err;
	int (*cgoogleplay_incrementachievement)(const char*, int);
	
	cgoogleplay_incrementachievement = (int (*)(const char*, int)) gCotCFunctions[eGooglePlay_IncrementAchievement];
	err = cgoogleplay_incrementachievement(aAchievementID, aNumSteps);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_INCREMENT_ACHIEVEMENT, aGooglePlay_didIncrementAchievement, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGooglePlay::IncrementAchievement failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_LoadAchievements_platform(bool aForceReload, s3eCallback aGooglePlay_didLoadAchievements, void* aUserData)
{
	int  err;
	int (*cgoogleplay_loadachievements)(bool);
	
	cgoogleplay_loadachievements = (int (*)(bool)) gCotCFunctions[eGooglePlay_LoadAchievements];
	err = cgoogleplay_loadachievements(aForceReload);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_ACHIEVEMENTS, aGooglePlay_didLoadAchievements, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGooglePlay::LoadAchievements failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_RevealAchievement_platform(const char* aAchievementID, s3eCallback aGooglePlay_didRevealAchievement, void* aUserData)
{
	int  err;
	int (*cgoogleplay_revealachievement)(const char*);
	
	cgoogleplay_revealachievement = (int (*)(const char*)) gCotCFunctions[eGooglePlay_RevealAchievement];
	err = cgoogleplay_revealachievement(aAchievementID);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_REVEAL_ACHIEVEMENT, aGooglePlay_didRevealAchievement, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGooglePlay::RevealAchievement failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_UnlockAchievement_platform(const char* aAchievementID, s3eCallback aGooglePlay_didUnlockAchievement, void* aUserData)
{
	int  err;
	int (*cgoogleplay_unlockachievement)(const char*);
	
	cgoogleplay_unlockachievement = (int (*)(const char*)) gCotCFunctions[eGooglePlay_UnlockAchievement];
	err = cgoogleplay_unlockachievement(aAchievementID);
	
	if(err == 0)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_UNLOCK_ACHIEVEMENT, aGooglePlay_didUnlockAchievement, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGooglePlay::UnlockAchievement failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}
