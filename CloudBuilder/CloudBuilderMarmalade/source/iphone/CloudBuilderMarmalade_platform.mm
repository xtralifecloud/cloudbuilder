/*
 * iphone-specific implementation of the CloudBuilderMarmalade extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "CloudBuilderMarmalade_internal.h"

#include "MarmaladeWrapper.h"

#define S3E_CURRENT_EXT CLOUDBUILDERMARMALADE
#include "s3eEdkError.h"
#include "s3eEdk.h"
#include "IwDebug.h"

using namespace CotCHelpers;
using namespace CloudBuilder;

s3eResult CloudBuilderMarmaladeInit_platform()
{
	IwDebugTraceLinePrintf("CloudBuilderMarmaladeInit_platform()");
	
	gMarmaladeClan  = new MarmaladeClan;
	
	// Add any platform-specific initialisation code here
	return S3E_RESULT_SUCCESS;
}

void CloudBuilderMarmaladeTerminate_platform()
{
	IwDebugTraceLinePrintf("CloudBuilderMarmaladeTerminate_platform()");
	
	gMarmaladeClan->Terminate();
	
	// Add any platform-specific termination code here
}

void** CloudBuilder_Init_platform(void** aCotCFunctions)
{
	return NULL;
}

void CloudBuilder_SetGlobalCotCCallback_platform(CloudBuilderMarmaladeCallback aIndex, s3eCallback aCallback, void* aUserData)
{
}

void CloudBuilder_PopCallback_platform()
{
	CNotificationManager::popNextCallback();
}

s3eResult Clan_Setup_platform(const char* aConfigurationJson, s3eCallback aClan_didSetup, void* aUserData)
{
	eErrorCode  err;
	CHJSON*		json;

	json = CHJSON::parse(aConfigurationJson);
	err = gMarmaladeClan->Setup(json);
	delete json;

	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->BatchBegin();
	if(err == enNoErr)
		return S3E_RESULT_SUCCESS;
	
	IwDebugTraceLinePrintf("CClan::BatchBegin: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Clan_BatchEnd_platform(s3eCallback aClan_didBatchEnd, void* aUserData)
{
	eErrorCode  err;
	
	err = gMarmaladeClan->BatchEnd();
	if(err == enNoErr)
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
	return gMarmaladeClan->isSetup();
}

bool Clan_isUserLogged_platform()
{
	return gMarmaladeClan->isUserLogged();
}

s3eResult User_RegisterAndLogin_platform(const char* aEmail, const char* aPassword, const char* aPseudo, s3eCallback aUser_didRegisterAndLogin, void* aUserData)
{
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->RegisterAndLogin(aEmail, aPassword, aPseudo);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->Login(aPseudo, aPassword);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->LoginWithFacebook(aOptionalPassword);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->LoginWithGooglePlus(aOptionalPassword);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->LoginWithGameCenter();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->Logout();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->LinkAccountWithFacebook();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->LinkAccountWithGooglePlus();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->LinkAccountWithGameCenter();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->ChangePassword(aOldPassword, aNewPassword);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->MailPassword(aEmail, aSubject, aBody);
	if(err == enNoErr)
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
	eErrorCode  err;
	CHJSON*	 json;
	
	json	= CHJSON::parse(aJson);
	err	 = gMarmaladeClan->mMarmaladeLogin->SetUserProfile(json);
	delete json;
	
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->GetUserProfile();
	if(err == enNoErr)
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
	return gMarmaladeClan->mMarmaladeLogin->GetPseudo();
}

const char* User_GetMail_platform()
{
	return gMarmaladeClan->mMarmaladeLogin->GetMail();
}

s3eResult User_PublishOnMyFacebookWall_platform(const char* aMessage, s3eCallback aUser_didPublishOnMyFacebookWall, void* aUserData)
{
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->PublishOnMyFacebookWall(aMessage);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->ReadBinary(aKey);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->WriteBinary(aKey, aPointer, aLength);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->Read(aKey);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->Write(aKey, aValue);
	if(err == enNoErr)
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
	eErrorCode  err;
	CHJSON*	 json;
	
	json = CHJSON::parse(aPropertiesJson);
	err = gMarmaladeClan->mMarmaladeLogin->SetProperties(aCanBeFound, json);
	delete json;
	
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->GetProperties();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->CheckUser(aIdent);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeLogin->SetAvatarSource((eExternalNetwork) aSource);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGame->Score(aHighScore, aMode, (eScoreType) aScoreType, aInfoScore, aMayVary);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGame->GetRank(aHighScore, aMode, (eScoreType) aScoreType);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGame->BestHighScore(aCount, aMode, (eScoreType) aScoreType);
	if(err == enNoErr)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_BEST_HIGH_SCORE, aGame_didBestHighScore, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGameManager::BestHighScore failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Game_GetRankArray_platform(const char* aScoreArrayJson, cbmScoreType aScoreType, s3eCallback aGame_didGetRankArray, void* aUserData)
{
	eErrorCode  err;
	CHJSON*	 json;
	
	json	= CHJSON::parse(aScoreArrayJson);
	err	 = gMarmaladeClan->mMarmaladeGame->GetRankArray(json, (eScoreType) aScoreType);
	delete json;
	
	if(err == enNoErr)
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
	eErrorCode  err;
	CHJSON*	 json;
	
	json	= CHJSON::parse(aArrayModesJson);
	err	 = gMarmaladeClan->mMarmaladeGame->BestHighScoreArray(aCount, json, (eScoreType) aScoreType);
	delete json;
	
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGame->ReadBinary(aKey);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGame->WriteBinary(aKey, aPointer, aLength);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGame->Read(aKey);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGame->Write(aKey, aValue);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->ListUsers(aContainsString);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->ListGlobalFriends();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->BlacklistGlobalFriends();
	if(err == enNoErr)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_BLACKLIST_GLOBAL_FRIENDS, aTribe_didBlacklistGlobalFriends, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CTribeManager::BlacklistGlobalFriends failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}

s3eResult Tribe_ChangeGlobalRelationshipStatus_platform(const char* aFriendPseudo, cbmRelationChange aNewState, s3eCallback aTribe_didChangeGlobalRelationshipStatus, void* aUserData)
{
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->ChangeGlobalRelationshipStatus(aFriendPseudo, (eRelationChange) aNewState);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->ListFriends();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->BlacklistFriends();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->ChangeRelationshipStatus(aFriendPseudo, (eRelationChange) aNewState);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->ListFacebookFriends();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->ListGooglePlusFriends();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->ListGameCenterFriends();
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->InviteFriendByMail(aEmail, aSubject, aBody);
	if(err == enNoErr)
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
	eErrorCode  err;
	CHJSON*	 json;
	
	json	= CHJSON::parse(aParamsJson);
	err = gMarmaladeClan->mMarmaladeTribe->InviteFriendByFBID(aFBFriendID, json);
	delete json;
	if(err == enNoErr)
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
	eErrorCode  err;
	CHJSON*	 json;
	
	json	= CHJSON::parse(aParamsJson);
	err = gMarmaladeClan->mMarmaladeTribe->InviteFriendByGooglePlusID(aGooglePlusFriendID, json);
	delete json;
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeTribe->FriendsBestHighScore(aMode, (eScoreType) aScoreType);
	if(err == enNoErr)
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
	eErrorCode  err;
	CHJSON*	 json;
	
	json	= CHJSON::parse(aArrayModesJson);
	err = gMarmaladeClan->mMarmaladeTribe->FriendsBestHighScoreArray(json, (eScoreType) aScoreType);
	delete json;
	if(err == enNoErr)
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
	eErrorCode  err;
	CHJSON*	 json;
	
	json	= CHJSON::parse(aFilterJson);
	err = gMarmaladeClan->mMarmaladeTribe->FindOpponents(json);
	delete json;
	
	if(err == enNoErr)
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
	return gMarmaladeClan->mMarmaladeMatch->GetActiveMatchID();
}

bool Match_HasActiveMatch_platform()
{
	return gMarmaladeClan->mMarmaladeMatch->HasActiveMatch();
}

s3eResult Match_GetMatchData_platform(const char* aMatchID, s3eCallback aMatch_didGetMatchData, void* aUserData)
{
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeMatch->GetMatchData(aMatchID);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeMatch->ListMatch(aIncludeAllData);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeMatch->ListPendingMatch();
	if(err == enNoErr)
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
	eErrorCode  err;
	CHJSON*	 json;
	
	json	= CHJSON::parse(aMatchDataJson);
	err = gMarmaladeClan->mMarmaladeMatch->CreateMatch(aName, aPrivateMatch, json);
	delete json;
	
	if(err == enNoErr)
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
	eErrorCode  err;
	CHJSON*	 jsonFriends;
	CHJSON*	 jsonPushNotif;
	
	jsonFriends	= CHJSON::parse(aArrayFriendsJson);
	jsonPushNotif   = CHJSON::parse(aNotifMessageJson);
	err = gMarmaladeClan->mMarmaladeMatch->InviteFriends(aMatchID, jsonFriends, aAutoAccept, jsonPushNotif);
	delete jsonFriends;
	delete jsonPushNotif;
	
	if(err == enNoErr)
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
	eErrorCode  err;
	CHJSON*	 json;
  
	json	= CHJSON::parse(aNotifMessageJson);
	err = gMarmaladeClan->mMarmaladeMatch->JoinMatch(aMatchID, aAccept, json);
	delete json;
	if(err == enNoErr)
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
	eErrorCode  err;
	CHJSON*	 jsonState;
	CHJSON*	 jsonNotif;
	
	jsonState	= CHJSON::parse(aMatchStateJson);
	jsonNotif	= CHJSON::parse(aNotifMessageJson);
	err = gMarmaladeClan->mMarmaladeMatch->MatchMove((eMatchPhase) aMatchPhase, aMatchID, jsonState, jsonNotif);
	delete jsonState;
	delete jsonNotif;
	
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeMatch->ReadBinary(aMatchID, aKey);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeMatch->WriteBinary(aMatchID, aKey, aPointer, aLength);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeMatch->Read(aMatchID, aKey);
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeMatch->Write(aMatchID, aKey, aValue);
	if(err == enNoErr)
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
	eErrorCode  err;
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
	
	return S3E_RESULT_ERROR;
}

bool GooglePlay_IsConnected_platform()
{
	return CGooglePlay::IsConnected();
}

s3eResult GooglePlay_LoadPeople_platform(const char* aListPeopleJSON, s3eCallback aGooglePlay_didLoadPeople, void* aUserData)
{
	eErrorCode  err;
	CHJSON*	 json;
	
	json = CHJSON::parse(aListPeopleJSON);
	err = gMarmaladeClan->mMarmaladeGooglePlay->LoadPeople(json);
	delete json;
	
	if(err == enNoErr)
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
	eErrorCode err;
	
	err = CGooglePlay::ShowAllLeaderboards();
	if(err == enNoErr)
		return S3E_RESULT_SUCCESS;
	
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_ShowLeaderboard_platform(const char* aLeaderboardID)
{
	eErrorCode err;
	
	err = CGooglePlay::ShowLeaderboard(aLeaderboardID);
	if(err == enNoErr)
		return S3E_RESULT_SUCCESS;
	
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_SubmitScore_platform(const char* aLeaderboardID, long long aScore, const char* aTag, s3eCallback aGooglePlay_didSubmitScore, void* aUserData)
{
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGooglePlay->SubmitScore(aLeaderboardID, aScore, aTag);
	
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGooglePlay->LoadLeaderboardMetadata(aLeaderboardID);
	
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGooglePlay->LoadLeaderboardsMetadata();
	
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGooglePlay->LoadPlayerCenteredScores(aLeaderboardID, (eTimeSpan) aSpan, (eLeaderboardCollection) aLeaderboardCollection, aMaxResults, aForceReload);
	
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGooglePlay->LoadTopScores(aLeaderboardID, (eTimeSpan) aSpan, (eLeaderboardCollection) aLeaderboardCollection, aMaxResults, aForceReload);
	
	if(err == enNoErr)
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
	eErrorCode err;
	
	err = CGooglePlay::ShowAchievements();
	if(err == enNoErr)
		return S3E_RESULT_SUCCESS;
	
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	return S3E_RESULT_ERROR;
}

s3eResult GooglePlay_IncrementAchievement_platform(const char* aAchievementID, int aNumSteps, s3eCallback aGooglePlay_didIncrementAchievement, void* aUserData)
{
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGooglePlay->IncrementAchievement(aAchievementID, aNumSteps);
	
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGooglePlay->LoadAchievements(aForceReload);
	
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGooglePlay->RevealAchievement(aAchievementID);
	
	if(err == enNoErr)
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
	eErrorCode  err;
	
	err = gMarmaladeClan->mMarmaladeGooglePlay->UnlockAchievement(aAchievementID);
	
	if(err == enNoErr)
	{
		s3eResult r = CloudBuilderMarmaladeRegister(CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_UNLOCK_ACHIEVEMENT, aGooglePlay_didUnlockAchievement, aUserData);
		
		return S3E_RESULT_SUCCESS;
	}
	
	IwDebugTraceLinePrintf("CGooglePlay::UnlockAchievement failed: %d", err);
	s3eEdkErrorSet(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, err, S3E_EXT_ERROR_PRI_NORMAL);
	
	return S3E_RESULT_ERROR;
}
