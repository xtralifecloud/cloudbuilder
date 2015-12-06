//
//  Marmalade_CotC.cpp
//  
//
//  Created by Michael EL BAKI on 23/Sep/13.
//
//

#include "MarmaladeCallbacks.h"

#include "CloudBuilderMarmalade_internal.h"
#include "MarmaladeFreeCallbacks.h"

#include "s3eEdk.h"
#include "s3eMemory.h"
#include "IwDebug.h"

#include <string.h>

void* gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_MAX];

void InitGlobalCotCCallbacks(void)
{
	gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_USER_RECEIVED_NOTIFY_USER] = NULL;
	gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_RECEIVED_MAINTENANCE_NOTIFICATION] = NULL;
	gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_DID_BEGIN_LOOKING_FOR_NOTIFICATION] = NULL;
	gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_DID_END_LOOKING_FOR_NOTIFICATION] = NULL;
	gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_DID_REGISTER_DEVICE] = NULL;
	gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_TRIBE_RELATIONSHIP_HAS_CHANGED] = NULL;
	gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_MATCH_PLAYER_DID_CHANGE_STATE] = NULL;
	gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_MATCH_MATCH_RECEIVE_DATA] = NULL;
}

void CNotification_receivedMaintenanceNotification_CotC(const char *aKind, const char* aJsonData)
{
	if(gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_RECEIVED_MAINTENANCE_NOTIFICATION] != NULL)
	{
		SGlobalMaintenanceNotification* result;
		
		result = new SGlobalMaintenanceNotification;
		result->mKind = aKind;
		result->mData = aJsonData;
		
		s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_RECEIVED_MAINTENANCE_NOTIFICATION, result, 0, NULL, S3E_FALSE, CallbackCompleteGlobalMaintenanceNotification, NULL);
		if(r == S3E_RESULT_ERROR)
		{
			FREE_GLOBAL_MAINTENANCE_NOTIFICATION(result);
			IwDebugTraceLinePrintf("Could not invoke CNotification::receivedMaintenanceNotification: %d", r);
		}
	}
}

void CNotification_didBeginLookingForNotification_CotC(void)
{
	if(gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_DID_BEGIN_LOOKING_FOR_NOTIFICATION] != NULL)
	{
		s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_DID_BEGIN_LOOKING_FOR_NOTIFICATION, NULL, 0, NULL, S3E_FALSE, NULL, NULL);
		if(r == S3E_RESULT_ERROR)
			IwDebugTraceLinePrintf("Could not invoke CNotification::didBeginLookingForNotification: %d", r);
	}
}

void CNotification_didEndLookingForNotification_CotC(int aPendingEvents)
{
	if(gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_DID_END_LOOKING_FOR_NOTIFICATION] != NULL)
	{
		int pendingEvents;
		
		pendingEvents = aPendingEvents;
		
		s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_DID_END_LOOKING_FOR_NOTIFICATION, &pendingEvents, sizeof(int), NULL, S3E_FALSE, NULL, NULL);
		if(r == S3E_RESULT_ERROR)
			IwDebugTraceLinePrintf("Could not invoke CNotification::didEndLookingForNotification: %d", r);
	}
}

void CNotification_didRegisterDevice_CotC(int aErrorCode)
{
	if(gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_DID_REGISTER_DEVICE] != NULL)
	{
		CloudBuilder_ErrorCode  errorCode;
		
		errorCode   = aErrorCode;
		
		s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_NOTIFICATION_DID_REGISTER_DEVICE, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_FALSE, NULL, NULL);
		if(r == S3E_RESULT_ERROR)
			IwDebugTraceLinePrintf("Could not invoke CNotification::didRegisterDevice: %d", r);
	}
}

void CClan_didSetup_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_CLAN_DID_SETUP, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CClan::didFinishSetup: %d", r);
}

void CClan_didBatchEnd_CotC(int aErrorCode, const char* aResults)
{
	SResultWithJson* result;
	
	result  = new SResultWithJson;
	result->mErrorCode   = aErrorCode;
	result->mJson	= aResults;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_CLAN_DID_BATCH_END, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CClan::didBatchEnd: %d", r);
	}
}

void CUser_didRegisterAndLogin_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_REGISTER_AND_LOGIN, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didRegisterAndLogin: %d", r);
}

void CUser_didLogin_CotC(int aErrorCode, const char* aJsonProfile)
{
	SResultWithJson* result;
	
	result  = new SResultWithJson;
	result->mErrorCode   = aErrorCode;
	result->mJson	= aJsonProfile;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LOGIN, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didLogin: %d", r);
	}
}

void CUser_didLoginWithFacebook_CotC(int aErrorCode, const char* aJsonProfile, const char* aDescription)
{
	SResultLoginWith*  result;
	
	result  = new SResultLoginWith;
	result->mErrorCode   = aErrorCode;
	result->mProfileJson	= aJsonProfile;
	result->mDescription	= aDescription;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LOGIN_WITH_FACEBOOK, result, 0, NULL, S3E_TRUE, CallbackCompleteResultLoginWith, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_LOGIN_WITH(result);
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didLoginWithFacebook: %d", r);
	}
}

void CUser_didLoginWithGooglePlus_CotC(int aErrorCode, const char* aJsonProfile, const char* aDescription)
{
	SResultLoginWith*  result;
	
	result  = new SResultLoginWith;
	result->mErrorCode   = aErrorCode;
	result->mProfileJson	= aJsonProfile;
	result->mDescription	= aDescription;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LOGIN_WITH_GOOGLEPLUS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultLoginWith, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_LOGIN_WITH(result);
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didLoginWithGooglePlus: %d", r);
	}
}

void CUser_didLoginWithGameCenter_CotC(int aErrorCode, const char* aJsonProfile, const char* aDescription)
{
	SResultLoginWith*  result;
	
	result  = new SResultLoginWith;
	result->mErrorCode   = aErrorCode;
	result->mProfileJson	= aJsonProfile;
	result->mDescription	= aDescription;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LOGIN_WITH_GAMECENTER, result, 0, NULL, S3E_TRUE, CallbackCompleteResultLoginWith, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_LOGIN_WITH(result);
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didLoginWithGameCenter: %d", r);
	}
}

void CUser_didLogout_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LOGOUT, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didLogout: %d", r);
}

void CUser_didLinkAccountWithFacebook_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LINK_ACCOUNT_WITH_FACEBOOK, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didLinkAccountWithFacebook: %d", r);
}

void CUser_didLinkAccountWithGooglePlus_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LINK_ACCOUNT_WITH_GOOGLEPLUS, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didLinkAccountWithGooglePlus: %d", r);
}

void CUser_didLinkAccountWithGameCenter_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_LINK_ACCOUNT_WITH_GAMECENTER, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didLinkAccountWithGameCenter: %d", r);
}

void CUser_didChangePassword_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_CHANGE_PASSWORD, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didChangePassword: %d", r);
}

void CUser_didMailPassword_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_MAIL_PASSWORD, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didMailPassword: %d", r);
}

void CUser_didSetUserProfile_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_SET_USER_PROFILE, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didSetUserProfile: %d", r);
}

void CUser_didGetUserProfile_CotC(int aErrorCode, const char* aJsonProfile)
{
	SResultWithJson* result;
	
	result  = new SResultWithJson;
	result->mErrorCode   = aErrorCode;
	result->mJson	= aJsonProfile;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_GET_USER_PROFILE, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didGetUserProfile: %d", r);
	}
}

void CUser_didPublishOnMyFacebookWall_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_PUBLISH_ON_MY_FACEBOOK_WALL, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didPublishOnMyFacebookWall: %d", r);
}

void CUser_didReadBinary_CotC(int aErrorCode, const char *aKey, void *aPointer, unsigned long aLength)
{
	SResultReadBinary*  result;

	result  = new SResultReadBinary;
	result->mErrorCode = aErrorCode;
	result->mKey = aKey;
	result->mPointer = aPointer;
	result->mLength = aLength;

	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_READ_BINARY, result, 0, NULL, S3E_TRUE, CallbackCompleteResultReadBinary, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_READ_BINARY(result);
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didReadBinary: %d", r);
	}
}

void CUser_didWriteBinary_CotC(int aErrorCode, const char* aKey, void* aPointer)
{
	SResultWriteBinary*  result;
	
	result  = new SResultWriteBinary;
	result->mErrorCode = aErrorCode;
	result->mKey = aKey;
	result->mPointer = aPointer;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_WRITE_BINARY, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWriteBinary, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WRITE_BINARY(result);
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didWriteBinary: %d", r);
	}
}

void CUser_didRead_CotC(int aErrorCode, const char *aKey, const char* aValue)
{
	SResultRead*  result;
	
	result  = new SResultRead;
	result->mErrorCode = aErrorCode;
	result->mKey = aKey;
	result->mValue = aValue;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_READ, result, 0, NULL, S3E_TRUE, CallbackCompleteResultRead, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_READ(result);
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didRead: %d", r);
	}
}

void CUser_didWrite_CotC(int aErrorCode, const char* aKey)
{
	SResultWrite*  result;
	
	result  = new SResultWrite;
	result->mErrorCode = aErrorCode;
	result->mKey = aKey;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_WRITE, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWrite, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WRITE(result);
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didWrite: %d", r);
	}
}

void CUser_didSetProperties_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_SET_PROPERTIES, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didSetProperties: %d", r);
}

void CUser_didGetProperties_CotC(int aErrorCode, bool aCanBeFound, const char* aJsonPropertiesList)
{
	SResultGetProperties*  result;
	
	result  = new SResultGetProperties;
	result->mErrorCode = aErrorCode;
	result->mCanBeFound = aCanBeFound;
	result->mPropertiesListJson = aJsonPropertiesList;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_GET_PROPERTIES, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGetProperties, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GET_PROPERTIES(result);
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didGetProperties: %d", r);
	}
}

void CUser_didCheckUser_CotC(int aErrorCode, bool aExists)
{
	SResultCheckUser  result;
	
	result.mErrorCode = aErrorCode;
	result.mExists = aExists;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_CHECK_USER, &result, sizeof(SResultCheckUser), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didCheckUser: %d", r);
}

void CUser_didSetAvatarSource_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_USER_DID_SET_AVATAR_SOURCE, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CUserManager::didSetAvatarSource: %d", r);
}

void CUser_receivedNotifyUser_CotC(const char* aFromuserID, const char* aJsonData)
{
	if(gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_USER_RECEIVED_NOTIFY_USER] != NULL)
	{
		SGlobalNotifyUser* result;
		
		result = new SGlobalNotifyUser;
		result->mFromUserID = aFromuserID;
		result->mData = aJsonData;
		
		s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_USER_RECEIVED_NOTIFY_USER, result, 0, NULL, S3E_FALSE, CallbackCompleteGlobalNotifyUser, NULL);
		if(r == S3E_RESULT_ERROR)
		{
			FREE_GLOBAL_NOTIFY_USER(result);
			IwDebugTraceLinePrintf("Could not invoke CUser::receivedNotifyUser: %d", r);
		}
	}
}

void CGame_didScore_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode   = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_SCORE, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CGameManager::didScore: %d", r);
}

void CGame_didGetRank_CotC(int aErrorCode, const char *aMode, long aRank)
{
	SResultGetRank*  result;
	
	result  = new SResultGetRank;
	result->mErrorCode = aErrorCode;
	result->mMode = aMode;
	result->mRank = aRank;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_GET_RANK, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGetRank, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GET_RANK(result);
		IwDebugTraceLinePrintf("Could not invoke CGameManager::didGetRank: %d", r);
	}
}

void CGame_didBestHighScore_CotC(int aErrorCode, const char *aMode, const char* aJson)
{
	SResultBestHighScore*  result;
	
	result  = new SResultBestHighScore;
	result->mErrorCode = aErrorCode;
	result->mMode = aMode;
	result->mScoresJson = aJson;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_BEST_HIGH_SCORE, result, 0, NULL, S3E_TRUE, CallbackCompleteResultBestHighScore, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_BEST_HIGH_SCORE(result);
		IwDebugTraceLinePrintf("Could not invoke CGameManager::didBestHighScore: %d", r);
	}
}

void CGame_didCenteredScore_CotC(int aErrorCode, const char *aMode, const char* aJson)
{
	SResultBestHighScore*  result;
	
	result  = new SResultBestHighScore;
	result->mErrorCode = aErrorCode;
	result->mMode = aMode;
	result->mScoresJson = aJson;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_CENTERED_SCORE, result, 0, NULL, S3E_TRUE, CallbackCompleteResultBestHighScore, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_BEST_HIGH_SCORE(result);
		IwDebugTraceLinePrintf("Could not invoke CGameManager::didCenteredScore: %d", r);
	}
}

void CGame_didGetRankArray_CotC(int aErrorCode, const char* aJsonRankArray)
{
	SResultWithJson*  result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonRankArray;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_GET_RANK_ARRAY, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CGameManager::didGetRankArray: %d", r);
	}
}

void CGame_didBestHighScoreArray_CotC(int aErrorCode, const char* aJsonArrayModes, const char* aJsonScoreArray)
{
	SResultBestHighScoreArray*  result;
	
	result  = new SResultBestHighScoreArray;
	result->mModesJson = aJsonArrayModes;
	result->mScoresJson = aJsonScoreArray;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_BEST_HIGH_SCORE_ARRAY, result, 0, NULL, S3E_TRUE, CallbackCompleteResultBestHighScoreArray, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_BEST_HIGH_SCORE_ARRAY(result);
		IwDebugTraceLinePrintf("Could not invoke CGameManager::didBestHighScoreArray: %d", r);
	}
}

void CGame_didReadBinary_CotC(int aErrorCode, const char *aKey, void *aPointer, unsigned long aLength)
{
	SResultReadBinary*  result;
	
	result  = new SResultReadBinary;
	result->mErrorCode = aErrorCode;
	result->mKey = aKey;
	result->mPointer = aPointer;
	result->mLength = aLength;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_READ_BINARY, result, 0, NULL, S3E_TRUE, CallbackCompleteResultReadBinary, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_READ_BINARY(result);
		IwDebugTraceLinePrintf("Could not invoke CGameManager::didReadBinary: %d", r);
	}
}

void CGame_didWriteBinary_CotC(int aErrorCode, const char* aKey, void* aPointer)
{
	SResultWriteBinary*  result;
	
	result  = new SResultWriteBinary;
	result->mErrorCode = aErrorCode;
	result->mKey = aKey;
	result->mPointer = aPointer;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_WRITE_BINARY, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWriteBinary, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WRITE_BINARY(result);
		IwDebugTraceLinePrintf("Could not invoke CGameManager::didWriteBinary: %d", r);
	}
}

void CGame_didRead_CotC(int aErrorCode, const char *aKey, const char* aValue)
{
	SResultRead*  result;
	
	result  = new SResultRead;
	result->mErrorCode = aErrorCode;
	result->mKey = aKey;
	result->mValue = aValue;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_READ, result, 0, NULL, S3E_TRUE, CallbackCompleteResultRead, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_READ(result);
		IwDebugTraceLinePrintf("Could not invoke CGameManager::didRead: %d", r);
	}
}

void CGame_didWrite_CotC(int aErrorCode, const char* aKey)
{
	SResultWrite*  result;
	
	result  = new SResultWrite;
	result->mErrorCode = aErrorCode;
	result->mKey = aKey;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GAME_DID_WRITE, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWrite, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WRITE(result);
		IwDebugTraceLinePrintf("Could not invoke CGameManager::didWrite: %d", r);
	}
}

void CTribe_didListUsers_CotC(int aErrorCode, const char* aJsonArrayUsers)
{
	SResultWithJson*  result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonArrayUsers;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_USERS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didListUsers: %d", r);
	}
}

void CTribe_didListGlobalFriends_CotC(int aErrorCode, const char* aJsonArrayFriends)
{
	SResultWithJson*  result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonArrayFriends;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_GLOBAL_FRIENDS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didListGlobalFriends: %d", r);
	}
}

void CTribe_didBlacklistGlobalFriends_CotC(int aErrorCode, const char* aJsonArrayFriends)
{
	SResultWithJson*  result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonArrayFriends;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_BLACKLIST_GLOBAL_FRIENDS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didBlacklistGlobalFriends: %d", r);
	}
}

void CTribe_didChangeGlobalRelationshipStatus_CotC(int aErrorCode, const char* aFriendPseudo, int aNewState)
{
	SResultChangeRelationshipStatus*  result;
	
	result  = new SResultChangeRelationshipStatus;
	result->mErrorCode = aErrorCode;
	result->mFriendPseudo = aFriendPseudo;
	result->mNewState = (cbmRelationChange) aNewState;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_CHANGE_GLOBAL_RELATIONSHIP_STATUS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultChangeRelationshipStatus, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_CHANGE_RELATIONSHIP_STATUS(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didChangeGlobalRelationshipStatus: %d", r);
	}
}

void CTribe_didListFriends_CotC(int aErrorCode, const char* aJsonArrayFriends)
{
	SResultWithJson*  result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonArrayFriends;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_FRIENDS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didListFriends: %d", r);
	}
}

void CTribe_didBlacklistFriends_CotC(int aErrorCode, const char* aJsonArrayFriends)
{
	SResultWithJson*  result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonArrayFriends;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_BLACKLIST_FRIENDS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didBlacklistFriends: %d", r);
	}
}

void CTribe_didChangeRelationshipStatus_CotC(int aErrorCode, const char* aFriendPseudo, int aNewState)
{
	SResultChangeRelationshipStatus*  result;
	
	result  = new SResultChangeRelationshipStatus;
	result->mErrorCode = aErrorCode;
	result->mFriendPseudo = aFriendPseudo;
	result->mNewState = (cbmRelationChange) aNewState;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_CHANGE_RELATIONSHIP_STATUS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultChangeRelationshipStatus, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_CHANGE_RELATIONSHIP_STATUS(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didChangeRelationshipStatus: %d", r);
	}
}

void CTribe_didListFacebookFriends_CotC(int aErrorCode, const char* aJsonArrayFriends)
{
	SResultWithJson*  result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonArrayFriends;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_FACEBOOK_FRIENDS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didListFacebookFriends: %d", r);
	}
}

void CTribe_didListGooglePlusFriends_CotC(int aErrorCode, const char* aJsonArrayFriends)
{
	SResultWithJson*  result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonArrayFriends;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_GOOGLEPLUS_FRIENDS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didListGooglePlusFriends: %d", r);
	}
}

void CTribe_didListGameCenterFriends_CotC(int aErrorCode, const char* aJsonArrayFriends)
{
	SResultWithJson*  result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonArrayFriends;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_LIST_GAMECENTER_FRIENDS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didListGameCenterFriends: %d", r);
	}
}

void CTribe_didInviteFriendByMail_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_INVITE_FRIEND_BY_MAIL, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didInviteFriendByMail: %d", r);
}

void CTribe_didInviteFriendByFBID_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_INVITE_FRIEND_BY_FBID, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didInviteFriendByFBID: %d", r);
}

void CTribe_didInviteFriendByGooglePlusID_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_INVITE_FRIEND_BY_GOOGLEPLUSID, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didInviteFriendByGooglePlusID: %d", r);
}

void CTribe_didFriendsBestHighScore_CotC(int aErrorCode, const char *aMode, const char* aJson)
{
	SResultBestHighScore*  result;
	
	result  = new SResultBestHighScore;
	result->mErrorCode = aErrorCode;
	result->mMode = aMode;
	result->mScoresJson = aJson;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_FRIENDS_BEST_HIGH_SCORE, result, 0, NULL, S3E_TRUE, CallbackCompleteResultBestHighScore, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_BEST_HIGH_SCORE(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didFriendsBestHighScore: %d", r);
	}
}

void CTribe_didFriendsBestHighScoreArray_CotC(int aErrorCode, const char *aJsonArrayModes, const char* aJson)
{
	SResultBestHighScoreArray*  result;
	
	result  = new SResultBestHighScoreArray;
	result->mErrorCode = aErrorCode;
	result->mModesJson = aJsonArrayModes;
	result->mScoresJson = aJson;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_FRIENDS_BEST_HIGH_SCORE_ARRAY, result, 0, NULL, S3E_TRUE, CallbackCompleteResultBestHighScoreArray, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_BEST_HIGH_SCORE_ARRAY(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didFriendsBestHighScoreArray: %d", r);
	}
}

void CTribe_didFindOpponents_CotC(int aErrorCode, const char* aJsonArrayPseudo)
{
	SResultWithJson*  result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonArrayPseudo;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_TRIBE_DID_FIND_OPPONENTS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CTribeManager::didFindOpponents: %d", r);
	}
}

void CTribe_relationshipHasChanged_CotC(const char* aFriendPseudo, int aNewState)
{
	if(gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_TRIBE_RELATIONSHIP_HAS_CHANGED] != NULL)
	{
		SGlobalRelationshipHasChanged* result;
		
		result = new SGlobalRelationshipHasChanged;
		result->mUserID = aFriendPseudo;
		result->mNewState = (cbmRelationChange) aNewState;
		
		s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_TRIBE_RELATIONSHIP_HAS_CHANGED, result, 0, NULL, S3E_FALSE, CallbackCompleteGlobalRelationshipHasChanged, NULL);
		if(r == S3E_RESULT_ERROR)
		{
			FREE_GLOBAL_RELATIONSHIP_HAS_CHANGED(result);
			IwDebugTraceLinePrintf("Could not invoke CTribeManager::relationshipHasChanged: %d", r);
		}
	}
}

void CMatch_didGetMatchData_CotC(int aErrorCode, const char* aMatchID, const char* aJsonMatchData)
{
	SResultGetMatchData*   result;
	
	result  = new SResultGetMatchData;
	result->mErrorCode = aErrorCode;
	result->mMatchID  = aMatchID;
	result->mMatchDataJson = aJsonMatchData;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_GET_MATCH_DATA, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGetMatchData, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GET_MATCH_DATA(result);
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didGetMatchData: %d", r);
	}
}

void CMatch_didListMatch_CotC(int aErrorCode, const char* aJsonArrayMatch)
{
	SResultWithJson*   result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonArrayMatch;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_LIST_MATCH, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didListMatch: %d", r);
	}
}

void CMatch_didListPendingMatch_CotC(int aErrorCode, const char* aJsonArrayMatch)
{
	SResultWithJson*   result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonArrayMatch;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_LIST_PENDING_MATCH, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didListPendingMatch: %d", r);
	}
}

void CMatch_didCreateMatch_CotC(int aErrorCode, const char* aMatchID)
{
	SResultWithDescription*   result;
	
	result  = new SResultWithDescription;
	result->mErrorCode = aErrorCode;
	result->mDescription = aMatchID;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_CREATE_MATCH, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithDescription, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_DESCRIPTION(result);
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didCreateMatch: %d", r);
	}
}

void CMatch_didInviteFriends_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_INVITE_FRIENDS, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didInviteFriends: %d", r);
}

void CMatch_didJoinMatch_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_JOIN_MATCH, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didJoinMatch: %d", r);
}

void CMatch_didMatchMove_CotC(int aErrorCode)
{
	CloudBuilder_ErrorCode  errorCode;
	
	errorCode = aErrorCode;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_MATCH_MOVE, &errorCode, sizeof(CloudBuilder_ErrorCode), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didMatchMove: %d", r);
}

void CMatch_didReadBinary_CotC(int aErrorCode, const char* aMatchID, const char* aKey, void* aPointer, unsigned long aLength)
{
	SResultMatchReadBinary*  result;
	
	result  = new SResultMatchReadBinary;
	result->mErrorCode = aErrorCode;
	result->mMatchID = aMatchID;
	result->mKey = aKey;
	result->mPointer = aPointer;
	result->mLength = aLength;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_READ_BINARY, result, 0, NULL, S3E_TRUE, CallbackCompleteResultMatchReadBinary, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_MATCH_READ_BINARY(result);
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didReadBinary: %d", r);
	}
}

void CMatch_didWriteBinary_CotC(int aErrorCode, const char* aMatchID, const char* aKey, void* aPointer)
{
	SResultMatchWriteBinary*  result;
	
	result  = new SResultMatchWriteBinary;
	result->mErrorCode = aErrorCode;
	result->mMatchID = aMatchID;
	result->mKey = aKey;
	result->mPointer = aPointer;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_WRITE_BINARY, result, 0, NULL, S3E_TRUE, CallbackCompleteResultMatchWriteBinary, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_MATCH_WRITE_BINARY(result);
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didWriteBinary: %d", r);
	}
}

void CMatch_didRead_CotC(int aErrorCode, const char* aMatchID, const char* aKey, const char* aValue)
{
	SResultMatchRead*  result;
	
	result  = new SResultMatchRead;
	result->mErrorCode = aErrorCode;
	result->mMatchID = aMatchID;
	result->mKey = aKey;
	result->mValue = aValue;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_READ, result, 0, NULL, S3E_TRUE, CallbackCompleteResultMatchRead, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_MATCH_READ(result);
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didRead: %d", r);
	}
}

void CMatch_didWrite_CotC(int aErrorCode, const char* aMatchID, const char* aKey)
{
	SResultMatchWrite*  result;
	
	result  = new SResultMatchWrite;
	result->mErrorCode = aErrorCode;
	result->mMatchID = aMatchID;
	result->mKey = aKey;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_MATCH_DID_WRITE, result, 0, NULL, S3E_TRUE, CallbackCompleteResultMatchWrite, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_MATCH_WRITE(result);
		IwDebugTraceLinePrintf("Could not invoke CMatchManager::didWrite: %d", r);
	}
}

void CMatch_playerDidChangeState_CotC(const char* aMatchID, const char* aPseudoID, int aStatus)
{
	if(gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_MATCH_PLAYER_DID_CHANGE_STATE] != NULL)
	{
		SGlobalPlayerDidChangeState* result;
		
		result = new SGlobalPlayerDidChangeState;
		result->mMatchID = aMatchID;
		result->mUserID = aPseudoID;
		result->mStatus = (cbmMatchStatus) aStatus;
		
		s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_MATCH_PLAYER_DID_CHANGE_STATE, result, 0, NULL, S3E_FALSE, CallbackCompleteGlobalPlayerDidChangeState, NULL);
		if(r == S3E_RESULT_ERROR)
		{
			FREE_GLOBAL_PLAYER_DID_CHANGE_STATE(result);
			IwDebugTraceLinePrintf("Could not invoke CMatchManager::playerDidChangeState: %d", r);
		}
	}
}

void CMatch_matchReceiveData_CotC(const char* aMatchID, const char* aFromPseudoID, int aPhase, const char* aJsonMatchState)
{
	if(gGlobalCotCCallbacks[CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_MATCH_MATCH_RECEIVE_DATA] != NULL)
	{
		SGlobalMatchReceiveData* result;
		
		result = new SGlobalMatchReceiveData;
		result->mMatchID = aMatchID;
		result->mFromUserID = aFromPseudoID;
		result->mPhase = (cbmMatchPhase) aPhase;
		result->mMatchState = aJsonMatchState;
		
		s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GLOBAL_MATCH_MATCH_RECEIVE_DATA, result, 0, NULL, S3E_FALSE, CallbackCompleteGlobalMatchReceivedData, NULL);
		if(r == S3E_RESULT_ERROR)
		{
			FREE_GLOBAL_MATCH_RECEIVE_DATA(result);
			IwDebugTraceLinePrintf("Could not invoke CMatchManager::matchReceiveData: %d", r);
		}
	}
}

void CGGoglePlay_didLoadPeople_CotC(int aErrorCode, const char* aJsonListDetails)
{
	SResultWithJson*   result;
	
	result  = new SResultWithJson;
	result->mErrorCode = aErrorCode;
	result->mJson = aJsonListDetails;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_PEOPLE, result, 0, NULL, S3E_TRUE, CallbackCompleteResultWithJson, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_WITH_JSON(result);
		IwDebugTraceLinePrintf("Could not invoke CGooglePlay::didLoadPeople: %d", r);
	}
}

void CGGoglePlay_didSubmitScore_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aLeaderboardID)
{
	SResultGooglePlaySubmitScore*  result;
	
	result  = new SResultGooglePlaySubmitScore;
	result->mErrorCode = aErrorCode;
	result->mGooglePlayError = aGooglePlayServicesError;
	result->mLeaderboardID = aLeaderboardID;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_SUBMIT_SCORE, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGooglePlaySubmitScore, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GOOGLEPLAY_SUBMIT_SCORE(result);
		IwDebugTraceLinePrintf("Could not invoke CGooglePlay::didSubmitScore: %d", r);
	}
}

void CGGoglePlay_didLoadLeaderboardMetadata_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aJsonLeaderboardMetadata)
{
	SResultGooglePlayLoadLeaderboardMetadata*  result;
	
	result  = new SResultGooglePlayLoadLeaderboardMetadata;
	result->mErrorCode = aErrorCode;
	result->mGooglePlayError = aGooglePlayServicesError;
	result->mJsonLeaderboardMetadata = aJsonLeaderboardMetadata;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_LEADERBOARD_METADATA, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGooglePlayLoadLeaderboardMetadata, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GOOGLEPLAY_LOAD_LEADERBOARD_METADATA(result);
		IwDebugTraceLinePrintf("Could not invoke CGooglePlay::didLoadLeaderboardMetadata: %d", r);
	}
}

void CGGoglePlay_didLoadLeaderboardsMetadata_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aJsonLeaderboardMetadata)
{
	SResultGooglePlayLoadLeaderboardMetadata*  result;
	
	result  = new SResultGooglePlayLoadLeaderboardMetadata;
	result->mErrorCode = aErrorCode;
	result->mGooglePlayError = aGooglePlayServicesError;
	result->mJsonLeaderboardMetadata = aJsonLeaderboardMetadata;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_LEADERBOARDS_METADATA, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGooglePlayLoadLeaderboardMetadata, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GOOGLEPLAY_LOAD_LEADERBOARD_METADATA(result);
		IwDebugTraceLinePrintf("Could not invoke CGooglePlay::didLoadLeaderboardsMetadata: %d", r);
	}
}

void CGGoglePlay_didLoadPlayerCenteredScores_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aJsonLeaderboard, const char* aJsonScores)
{
	SResultGooglePlayLoadScores*  result;
	
	result  = new SResultGooglePlayLoadScores;
	result->mErrorCode = aErrorCode;
	result->mGooglePlayError = aGooglePlayServicesError;
	result->mJsonLeaderboard = aJsonLeaderboard;
	result->mJsonScores = aJsonScores;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_PLAYER_CENTERED_SCORES, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGooglePlayLoadScores, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GOOGLEPLAY_LOAD_SCORES(result);
		IwDebugTraceLinePrintf("Could not invoke CGooglePlay::didLoadPlayerCenteredScores: %d", r);
	}
}

void CGGoglePlay_didLoadTopScores_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aJsonLeaderboard, const char* aJsonScores)
{
	SResultGooglePlayLoadScores*  result;
	
	result  = new SResultGooglePlayLoadScores;
	result->mErrorCode = aErrorCode;
	result->mGooglePlayError = aGooglePlayServicesError;
	result->mJsonLeaderboard = aJsonLeaderboard;
	result->mJsonScores = aJsonScores;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_TOP_SCORES, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGooglePlayLoadScores, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GOOGLEPLAY_LOAD_SCORES(result);
		IwDebugTraceLinePrintf("Could not invoke CGooglePlay::didLoadTopScores: %d", r);
	}
}

void CGGoglePlay_didIncrementAchievement_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aAchievementID, bool aUnlocked)
{
	SResultGooglePlayIncrementAchievement*  result;
	
	result  = new SResultGooglePlayIncrementAchievement;
	result->mErrorCode = aErrorCode;
	result->mGooglePlayError = aGooglePlayServicesError;
	result->mAchievement = aAchievementID;
	result->mUnlocked = aUnlocked;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_INCREMENT_ACHIEVEMENT, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGooglePlayIncrementAchievement, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GOOGLEPLAY_INCREMENT_ACHIEVEMENT(result);
		IwDebugTraceLinePrintf("Could not invoke CGooglePlay::didIncrementAchievement: %d", r);
	}
}

void CGGoglePlay_didLoadAchievements_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aJsonAchievements)
{
	SResultGooglePlayLoadAchievements*  result;
	
	result  = new SResultGooglePlayLoadAchievements;
	result->mErrorCode = aErrorCode;
	result->mGooglePlayError = aGooglePlayServicesError;
	result->mJsonAchievements = aJsonAchievements;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_LOAD_ACHIEVEMENTS, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGooglePlayLoadAchievements, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GOOGLEPLAY_LOAD_ACHIEVEMENTS(result);
		IwDebugTraceLinePrintf("Could not invoke CGooglePlay::didLoadAchievements: %d", r);
	}
}

void CGGoglePlay_didRevealAchievement_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aAchievementID)
{
	SResultGooglePlayAchievementResult*  result;
	
	result  = new SResultGooglePlayAchievementResult;
	result->mErrorCode = aErrorCode;
	result->mGooglePlayError = aGooglePlayServicesError;
	result->mAchievement = aAchievementID;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_REVEAL_ACHIEVEMENT, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGooglePlayAchievementResult, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GOOGLEPLAY_ACHIEVEMENT_RESULT(result);
		IwDebugTraceLinePrintf("Could not invoke CGooglePlay::didRevealAchievement: %d", r);
	}
}

void CGGoglePlay_didUnlockAchievement_CotC(int aErrorCode, int aGooglePlayServicesError, const char* aAchievementID)
{
	SResultGooglePlayAchievementResult*  result;
	
	result  = new SResultGooglePlayAchievementResult;
	result->mErrorCode = aErrorCode;
	result->mGooglePlayError = aGooglePlayServicesError;
	result->mAchievement = aAchievementID;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_GOOGLEPLAY_DID_UNLOCK_ACHIEVEMENT, result, 0, NULL, S3E_TRUE, CallbackCompleteResultGooglePlayAchievementResult, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		FREE_RESULT_GOOGLEPLAY_ACHIEVEMENT_RESULT(result);
		IwDebugTraceLinePrintf("Could not invoke CGooglePlay::didUnlockAchievement: %d", r);
	}
}
