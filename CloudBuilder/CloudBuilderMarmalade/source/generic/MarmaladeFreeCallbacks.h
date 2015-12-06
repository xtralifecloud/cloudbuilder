//
//  MarmaladeWrapper.h
//  CloudBuilderMarmalade_iphone
//
//  Created by Michael EL BAKI on 7/28/13.
//
//

#ifndef __MARMAMALADE_FREE_CALLBACKS
#define __MARMAMALADE_FREE_CALLBACKS

#include "s3eEdk.h"

#define FREE_CONST(pointer) free((void*) pointer)

#define FREE_GLOBAL_NOTIFY_USER(result) if(result->mFromUserID)FREE_CONST(result->mFromUserID);if(result->mData)FREE_CONST(result->mData);delete(result);
#define FREE_GLOBAL_MAINTENANCE_NOTIFICATION(result) if(result->mKind)FREE_CONST(result->mKind);if(result->mData)FREE_CONST(result->mData);delete(result);
#define FREE_GLOBAL_RELATIONSHIP_HAS_CHANGED(result) if(result->mUserID)FREE_CONST(result->mUserID);delete(result);
#define FREE_GLOBAL_PLAYER_DID_CHANGE_STATE(result) if(result->mMatchID)FREE_CONST(result->mMatchID);if(result->mUserID)FREE_CONST(result->mUserID);delete(result);
#define FREE_GLOBAL_MATCH_RECEIVE_DATA(result) if(result->mMatchID)FREE_CONST(result->mMatchID);if(result->mFromUserID)FREE_CONST(result->mFromUserID);if(result->mMatchState)FREE_CONST(result->mMatchState);delete(result);

#define FREE_RESULT_WITH_DESCRIPTION(result) if(result->mDescription)FREE_CONST(result->mDescription);delete(result);
#define FREE_RESULT_WITH_JSON(result) if(result->mJson)FREE_CONST(result->mJson);delete(result);
#define FREE_RESULT_LOGIN_WITH(result) if(result->mDescription)FREE_CONST(result->mDescription);if(result->mProfileJson)FREE_CONST(result->mProfileJson);delete(result);
#define FREE_RESULT_READ_BINARY(result) if(result->mKey)FREE_CONST(result->mKey);delete(result);
#define FREE_RESULT_WRITE_BINARY(result) if(result->mKey)FREE_CONST(result->mKey);delete(result);
#define FREE_RESULT_READ(result) if(result->mKey)FREE_CONST(result->mKey);if(result->mValue)FREE_CONST(result->mValue);delete(result);
#define FREE_RESULT_WRITE(result) if(result->mKey)FREE_CONST(result->mKey);delete(result);
#define FREE_RESULT_GET_PROPERTIES(result) if(result->mPropertiesListJson)FREE_CONST(result->mPropertiesListJson);delete(result);
#define FREE_RESULT_BEST_HIGH_SCORE(result) if(result->mMode)FREE_CONST(result->mMode);if(result->mScoresJson)FREE_CONST(result->mScoresJson);delete(result);
#define FREE_RESULT_BEST_HIGH_SCORE_ARRAY(result) if(result->mModesJson)FREE_CONST(result->mModesJson);if(result->mScoresJson)FREE_CONST(result->mScoresJson);delete(result);
#define FREE_RESULT_GET_RANK(result) if(result->mMode)FREE_CONST(result->mMode);delete(result);
#define FREE_RESULT_CHANGE_RELATIONSHIP_STATUS(result) if(result->mFriendPseudo)FREE_CONST(result->mFriendPseudo);delete(result);
#define FREE_RESULT_GET_MATCH_DATA(result) if(result->mMatchID)FREE_CONST(result->mMatchID);if(result->mMatchDataJson)FREE_CONST(result->mMatchDataJson);delete(result);
#define FREE_RESULT_MATCH_READ_BINARY(result) if(result->mMatchID)FREE_CONST(result->mMatchID);if(result->mKey)FREE_CONST(result->mKey);delete(result);
#define FREE_RESULT_MATCH_WRITE_BINARY(result) if(result->mMatchID)FREE_CONST(result->mMatchID);if(result->mKey)FREE_CONST(result->mKey);delete(result);
#define FREE_RESULT_MATCH_READ(result) if(result->mMatchID)FREE_CONST(result->mMatchID);if(result->mKey)FREE_CONST(result->mKey);if(result->mValue)FREE_CONST(result->mValue);delete(result);
#define FREE_RESULT_MATCH_WRITE(result) if(result->mMatchID)FREE_CONST(result->mMatchID);if(result->mKey)FREE_CONST(result->mKey);delete(result);
#define FREE_RESULT_GOOGLEPLAY_SUBMIT_SCORE(result) if(result->mLeaderboardID)FREE_CONST(result->mLeaderboardID);delete(result);
#define FREE_RESULT_GOOGLEPLAY_LOAD_LEADERBOARD_METADATA(result) if(result->mJsonLeaderboardMetadata)FREE_CONST(result->mJsonLeaderboardMetadata);delete(result);
#define FREE_RESULT_GOOGLEPLAY_LOAD_SCORES(result) if(result->mJsonLeaderboard)FREE_CONST(result->mJsonLeaderboard);if(result->mJsonScores)FREE_CONST(result->mJsonScores);delete(result);
#define FREE_RESULT_GOOGLEPLAY_INCREMENT_ACHIEVEMENT(result) if(result->mAchievement)FREE_CONST(result->mAchievement);delete(result);
#define FREE_RESULT_GOOGLEPLAY_LOAD_ACHIEVEMENTS(result) if(result->mJsonAchievements)FREE_CONST(result->mJsonAchievements);delete(result);
#define FREE_RESULT_GOOGLEPLAY_ACHIEVEMENT_RESULT(result) if(result->mAchievement)FREE_CONST(result->mAchievement);delete(result);

void CallbackCompleteGlobalNotifyUser(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteGlobalMaintenanceNotification(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteGlobalRelationshipHasChanged(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteGlobalPlayerDidChangeState(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteGlobalMatchReceivedData(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultWithDescription(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultWithJson(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultLoginWith(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultReadBinary(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultWriteBinary(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultRead(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultWrite(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultGetProperties(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultBestHighScore(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultBestHighScoreArray(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultGetRank(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultChangeRelationshipStatus(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultGetMatchData(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultMatchReadBinary(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultMatchWriteBinary(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultMatchRead(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultMatchWrite(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultGooglePlaySubmitScore(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultGooglePlayLoadLeaderboardMetadata(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultGooglePlayLoadScores(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultGooglePlayIncrementAchievement(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultGooglePlayLoadAchievements(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);
void CallbackCompleteResultGooglePlayAchievementResult(uint32 extID, int32 notification, void*systemData, void* instance, int32 returnCode, void* completeData);

#endif