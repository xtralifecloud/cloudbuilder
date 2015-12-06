//
//  MarmaladeFreeCallbacks.cpp
//  CloudBuilderMarmalade_iphone
//
//  Created by Michael EL BAKI on 7/28/13.
//
//

#include "MarmaladeFreeCallbacks.h"

#include "CloudBuilderMarmalade.h"

#include "stdlib.h"

void CallbackCompleteGlobalNotifyUser(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SGlobalNotifyUser* result;
	
	result  = (SGlobalNotifyUser *) systemData;
	FREE_GLOBAL_NOTIFY_USER(result);
}

void CallbackCompleteGlobalMaintenanceNotification(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SGlobalMaintenanceNotification* result;
	
	result  = (SGlobalMaintenanceNotification *) systemData;
	FREE_GLOBAL_MAINTENANCE_NOTIFICATION(result);
}

void CallbackCompleteGlobalRelationshipHasChanged(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SGlobalRelationshipHasChanged* result;
	
	result  = (SGlobalRelationshipHasChanged *) systemData;
	FREE_GLOBAL_RELATIONSHIP_HAS_CHANGED(result);
}

void CallbackCompleteGlobalPlayerDidChangeState(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SGlobalPlayerDidChangeState* result;
	
	result  = (SGlobalPlayerDidChangeState *) systemData;
	FREE_GLOBAL_RELATIONSHIP_HAS_CHANGED(result);
}

void CallbackCompleteGlobalMatchReceivedData(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SGlobalMatchReceiveData* result;
	
	result  = (SGlobalMatchReceiveData *) systemData;
	FREE_GLOBAL_MATCH_RECEIVE_DATA(result);
}

void CallbackCompleteResultWithDescription(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultWithDescription* result;
	
	result  = (SResultWithDescription *) systemData;
	FREE_RESULT_WITH_DESCRIPTION(result);
}

void CallbackCompleteResultWithJson(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultWithJson* result;
	
	result  = (SResultWithJson *) systemData;
	FREE_RESULT_WITH_JSON(result);
}

void CallbackCompleteResultLoginWith(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultLoginWith* result;
	
	result  = (SResultLoginWith *) systemData;
	FREE_RESULT_LOGIN_WITH(result);
}

void CallbackCompleteResultReadBinary(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultReadBinary* result;
	
	result  = (SResultReadBinary *) systemData;
	FREE_RESULT_READ_BINARY(result);
}

void CallbackCompleteResultWriteBinary(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultWriteBinary* result;
	
	result  = (SResultWriteBinary *) systemData;
	FREE_RESULT_WRITE_BINARY(result);
}

void CallbackCompleteResultRead(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultRead* result;
	
	result  = (SResultRead *) systemData;
	FREE_RESULT_READ(result);
}

void CallbackCompleteResultWrite(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultWrite* result;
	
	result  = (SResultWrite *) systemData;
	FREE_RESULT_WRITE(result);
}

void CallbackCompleteResultGetProperties(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultGetProperties* result;
	
	result  = (SResultGetProperties *) systemData;
	FREE_RESULT_GET_PROPERTIES(result);
}

void CallbackCompleteResultBestHighScore(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultBestHighScore* result;
	
	result  = (SResultBestHighScore *) systemData;
	FREE_RESULT_BEST_HIGH_SCORE(result);
}

void CallbackCompleteResultBestHighScoreArray(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultBestHighScoreArray* result;
	
	result  = (SResultBestHighScoreArray *) systemData;
	FREE_RESULT_BEST_HIGH_SCORE_ARRAY(result);
}

void CallbackCompleteResultGetRank(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultGetRank* result;
	
	result  = (SResultGetRank *) systemData;
	FREE_RESULT_GET_RANK(result);
}

void CallbackCompleteResultChangeRelationshipStatus(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultChangeRelationshipStatus* result;
	
	result  = (SResultChangeRelationshipStatus *) systemData;
	FREE_RESULT_CHANGE_RELATIONSHIP_STATUS(result);
}

void CallbackCompleteResultGetMatchData(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultGetMatchData* result;
	
	result  = (SResultGetMatchData *) systemData;
	FREE_RESULT_GET_MATCH_DATA(result);
}

void CallbackCompleteResultMatchReadBinary(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultMatchReadBinary* result;
	
	result  = (SResultMatchReadBinary *) systemData;
	FREE_RESULT_MATCH_READ_BINARY(result);
}

void CallbackCompleteResultMatchWriteBinary(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultMatchWriteBinary* result;
	
	result  = (SResultMatchWriteBinary *) systemData;
	FREE_RESULT_MATCH_WRITE_BINARY(result);
}

void CallbackCompleteResultMatchRead(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultMatchRead* result;
	
	result  = (SResultMatchRead *) systemData;
	FREE_RESULT_MATCH_READ(result);
}

void CallbackCompleteResultMatchWrite(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultMatchWrite* result;
	
	result  = (SResultMatchWrite *) systemData;
	FREE_RESULT_MATCH_WRITE(result);
}

void CallbackCompleteResultGooglePlaySubmitScore(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultGooglePlaySubmitScore* result;
	
	result  = (SResultGooglePlaySubmitScore *) systemData;
	FREE_RESULT_GOOGLEPLAY_SUBMIT_SCORE(result);
}

void CallbackCompleteResultGooglePlayLoadLeaderboardMetadata(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultGooglePlayLoadLeaderboardMetadata* result;
	
	result  = (SResultGooglePlayLoadLeaderboardMetadata *) systemData;
	FREE_RESULT_GOOGLEPLAY_LOAD_LEADERBOARD_METADATA(result);
}

void CallbackCompleteResultGooglePlayLoadScores(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultGooglePlayLoadScores* result;
	
	result  = (SResultGooglePlayLoadScores *) systemData;
	FREE_RESULT_GOOGLEPLAY_LOAD_SCORES(result);
}

void CallbackCompleteResultGooglePlayIncrementAchievement(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultGooglePlayIncrementAchievement* result;
	
	result  = (SResultGooglePlayIncrementAchievement *) systemData;
	FREE_RESULT_GOOGLEPLAY_INCREMENT_ACHIEVEMENT(result);
}

void CallbackCompleteResultGooglePlayLoadAchievements(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultGooglePlayLoadAchievements* result;
	
	result  = (SResultGooglePlayLoadAchievements *) systemData;
	FREE_RESULT_GOOGLEPLAY_LOAD_ACHIEVEMENTS(result);
}

void CallbackCompleteResultGooglePlayAchievementResult(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData)
{
	SResultGooglePlayAchievementResult* result;
	
	result  = (SResultGooglePlayAchievementResult *) systemData;
	FREE_RESULT_GOOGLEPLAY_ACHIEVEMENT_RESULT(result);
}

