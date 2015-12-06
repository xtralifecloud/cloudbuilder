//
//  Marmalade_CotC.cpp
//  
//
//  Created by Michael EL BAKI on 23/Sep/13.
//
//

#include "MarmaladeCotC.h"

#include "MarmaladeWrapper.h"

using namespace CloudBuilder;
using namespace CotCHelpers;

void** gCloudBuilderCallbacks;

void InitCloudBuilderCallbacks(void** aCloudBuilderCallbacks)
{
	gCloudBuilderCallbacks = aCloudBuilderCallbacks;
}

void CloudBuilder_PopCallback_CotC(void)
{
	CNotificationManager::popNextCallback();
}

int CClan_Setup_CotC(const char* aConfigurationJson)
{
	CHJSON* json;
	int	 result;
	
	gMarmaladeClan  = new MarmaladeClan;

	json = CHJSON::parse(aConfigurationJson);
	result = gMarmaladeClan->Setup(json);
	delete json;
	
	return result;
}

int CClan_BatchBegin_CotC(void)
{
	return enNotImplemented;
}

int CClan_BatchEnd_CotC(void)
{
	return enNotImplemented;
}

bool CClan_isSetup_CotC(void)
{
	return gMarmaladeClan->isSetup();
}

bool CClan_isUserLogged_CotC(void)
{
	return gMarmaladeClan->isUserLogged();
}

int CUser_RegisterAndLogin_CotC(const char *aEmail, const char *aPassword, const char *aPseudo)
{
	return enNotImplemented;
}

int CUser_Login_CotC(const char *aPseudo, const char *aPassword)
{
	return enNotImplemented;
}

int CUser_LoginWithFacebook_CotC(const char* aOptionalPassword)
{
	return enNotImplemented;
}

int CUser_LoginWithGooglePlus_CotC(const char* aOptionalPassword)
{
	return enNotImplemented;
}

int CUser_LoginWithGameCenter_CotC(void)
{
	return gMarmaladeClan->mMarmaladeLogin->LoginWithGameCenter();
}

int CUser_Logout_CotC(void)
{
	return gMarmaladeClan->mMarmaladeLogin->Logout();
}

int CUser_LinkAccountWithFacebook_CotC(void)
{
	return gMarmaladeClan->mMarmaladeLogin->LinkAccountWithFacebook();
}

int CUser_LinkAccountWithGooglePlus_CotC(void)
{
	return gMarmaladeClan->mMarmaladeLogin->LinkAccountWithGooglePlus();
}

int CUser_LinkAccountWithGameCenter_CotC(void)
{
	return gMarmaladeClan->mMarmaladeLogin->LinkAccountWithGameCenter();
}

int CUser_ChangePassword_CotC(const char* aOldPassword, const char* aNewPassword)
{
	return enNotImplemented;
}

int CUser_MailPassword_CotC(const char *aEmail, const char* aSubject, const char* aBody)
{
	return enNotImplemented;
}

const char* CUser_GetPseudo_CotC(void)
{
	return gMarmaladeClan->mMarmaladeLogin->GetPseudo();
}

const char* CUser_GetMail_CotC(void)
{
	return gMarmaladeClan->mMarmaladeLogin->GetMail();
}

int CUser_SetUserProfile_CotC(const char* aJsonProdile)
{
	CHJSON* json;
	int	 result;
	
	json = CHJSON::parse(aJsonProdile);
	result = gMarmaladeClan->mMarmaladeLogin->SetUserProfile(json);
	delete json;
	
	return result;
}

int CUser_GetUserProfile_CotC(void)
{
	return gMarmaladeClan->mMarmaladeLogin->GetUserProfile();
}

int CUser_PublishOnMyFacebookWall_CotC(const char* aMessage)
{
	CHJSON* json;
	int	 result;
	
	json = CHJSON::parse(aMessage);
	return gMarmaladeClan->mMarmaladeLogin->PublishOnMyFacebookWall(json);
	delete json;
	
	return result;
}

int CUser_ReadBinary_CotC(const char* aKey)
{
	return enNotImplemented;
}

int CUser_WriteBinary_CotC(const char* aKey, void* aPointer, unsigned long aLength)
{
	return enNotImplemented;
}

int CUser_Read_CotC(const char* aKey)
{
	return enNotImplemented;
}

int CUser_Write_CotC(const char* aKey, const char* aValue)
{
	return enNotImplemented;
}

int CUser_SetProperties_CotC(bool aCanBeFound, const char* aJsonPropertiesList)
{
	int result;
	CHJSON* json;
	
	json = CHJSON::parse(aJsonPropertiesList);
	result = gMarmaladeClan->mMarmaladeLogin->SetProperties(aCanBeFound, json);
	delete json;
	
	return result;
}

int CUser_GetProperties_CotC(void)
{
	return gMarmaladeClan->mMarmaladeLogin->GetProperties();
}

int CUser_CheckUser_CotC(const char* aIdent)
{
	return gMarmaladeClan->mMarmaladeLogin->CheckUser(aIdent);
}

int CUser_SetAvatarSource_CotC(int aSource)
{
	return enNotImplemented;
}

int CGame_Score_CotC(long long aHighScore, const char *aMode, int aScoreType, const char *aInfoScore)
{
	return gMarmaladeClan->mMarmaladeGame->Score(aHighScore, aMode, (eScoreType) aScoreType);
}

int CGame_GetRank_CotC(long long aHighScore, const char *aMode, int aScoreType)
{
	return gMarmaladeClan->mMarmaladeGame->GetRank(aHighScore, aMode, (eScoreType) aScoreType);
}

int CGame_BestHighScore_CotC(int aCount, const char *aMode, int aScoreType)
{
	return gMarmaladeClan->mMarmaladeGame->BestHighScore(aCount, aMode, (eScoreType) aScoreType);
}

int CGame_CenteredScore_CotC(int aCount, const char *aMode, int aScoreType)
{
	return gMarmaladeClan->mMarmaladeGame->CenteredScore(aCount, aMode, (eScoreType) aScoreType);
}

int CGame_GetRankArray_CotC(const char* aJsonScoreArray, int aScoreType)
{
	int result;
	CHJSON* json;
	
	json = CHJSON::parse(aJsonScoreArray);
	result = gMarmaladeClan->mMarmaladeGame->GetRankArray(json, (eScoreType) aScoreType);
	delete json;
	
	return result;
}

int CGame_BestHighScoreArray_CotC(int aCount, const char* aJsonArrayModes, int aScoreType)
{
	int result;
	CHJSON* json;
	
	json = CHJSON::parse(aJsonArrayModes);
	result = gMarmaladeClan->mMarmaladeGame->BestHighScoreArray(aCount, json, (eScoreType) aScoreType);
	delete json;
	
	return result;
}

int CGame_ReadBinary_CotC(const char* aKey)
{
	return enNotImplemented;
}

int CGame_WriteBinary_CotC(const char* aKey, void* aPointer, unsigned long aLength)
{
	return enNotImplemented;
}

int CGame_Read_CotC(const char* aKey)
{
	return enNotImplemented;
}

int CGame_Write_CotC(const char* aKey, const char* aValue)
{
	return enNotImplemented;
}

int CTribe_ListUsers_CotC(const char* aContainsString)
{
	return gMarmaladeClan->mMarmaladeTribe->ListUsers(aContainsString);
}

int CTribe_ListGlobalFriends_CotC(void)
{
	return gMarmaladeClan->mMarmaladeTribe->ListGlobalFriends();
}

int CTribe_BlacklistGlobalFriends_CotC(void)
{
	return gMarmaladeClan->mMarmaladeTribe->BlacklistGlobalFriends();
}

int CTribe_ChangeGlobalRelationshipStatus_CotC(const char* aFriendPseudo, int aNewState)
{
	return gMarmaladeClan->mMarmaladeTribe->ChangeGlobalRelationshipStatus(aFriendPseudo, (eRelationChange) aNewState);
}

int CTribe_ListFriends_CotC(void)
{
	return gMarmaladeClan->mMarmaladeTribe->ListFriends();
}

int CTribe_BlacklistFriends_CotC(void)
{
	return gMarmaladeClan->mMarmaladeTribe->BlacklistFriends();
}

int CTribe_ChangeRelationshipStatus_CotC(const char* aFriendPseudo, int aNewState)
{
	return gMarmaladeClan->mMarmaladeTribe->ChangeRelationshipStatus(aFriendPseudo, (eRelationChange) aNewState);
}

int CTribe_ListFacebookFriends_CotC(void)
{
	return gMarmaladeClan->mMarmaladeTribe->ListFacebookFriends();
}

int CTribe_ListGooglePlusFriends_CotC(void)
{
	return gMarmaladeClan->mMarmaladeTribe->ListGooglePlusFriends();
}

int CTribe_ListGameCenterFriends_CotC(void)
{
	return gMarmaladeClan->mMarmaladeTribe->ListGameCenterFriends();
}

int CTribe_InviteFriendByMail_CotC(const char *aEmail, const char *aSubject, const char *aBody)
{
	return gMarmaladeClan->mMarmaladeTribe->InviteFriendByMail(aEmail, aSubject, aBody);
}

int CTribe_InviteFriendByFBID_CotC(const char *aFBFriendID, const char* aJsonParams)
{
	int result;
	CHJSON* json;
	
	json = CHJSON::parse(aJsonParams);
	result = gMarmaladeClan->mMarmaladeTribe->InviteFriendByFBID(aFBFriendID, json);
	delete json;
	
	return result;
}

int CTribe_InviteFriendByGooglePlusID_CotC(const char *aGooglePlusFriendID, const char* aJsonParams)
{
	int result;
	CHJSON* json;
	
	json = CHJSON::parse(aJsonParams);
	result = gMarmaladeClan->mMarmaladeTribe->InviteFriendByGooglePlusID(aGooglePlusFriendID, json);
	delete json;
	
	return result;
}

int CTribe_FriendsBestHighScore_CotC(const char *aMode, int aScoreType)
{
	return gMarmaladeClan->mMarmaladeTribe->FriendsBestHighScore(aMode, (eScoreType) aScoreType);
}

int CTribe_FriendsBestHighScoreArray_CotC(const char *aJsonArrayModes, int aScoreType)
{
	int result;
	CHJSON* json;
	
	json = CHJSON::parse(aJsonArrayModes);
	result = gMarmaladeClan->mMarmaladeTribe->FriendsBestHighScoreArray(json, (eScoreType) aScoreType);
	delete json;
	
	return result;
}

int CTribe_FindOpponents_CotC(const char *aJsonFilter)
{
	int result;
	CHJSON* json;
	
	json = CHJSON::parse(aJsonFilter);
	result = gMarmaladeClan->mMarmaladeTribe->FindOpponents(json);
	delete json;
	
	return result;
}

const char* CMatch_GetActiveMatchID_CotC(void)
{
	return gMarmaladeClan->mMarmaladeMatch->GetActiveMatchID();
}

bool CMatch_HasActiveMatch_CotC(void)
{
	return gMarmaladeClan->mMarmaladeMatch->HasActiveMatch();
}

int CMatch_GetMatchData_CotC(const char* aMatchID)
{
	return gMarmaladeClan->mMarmaladeMatch->GetMatchData(aMatchID);
}

int CMatch_ListMatch_CotC(bool aIncludeAllData)
{
	return gMarmaladeClan->mMarmaladeMatch->ListMatch(aIncludeAllData);
}

int CMatch_ListPendingMatch_CotC(void)
{
	return gMarmaladeClan->mMarmaladeMatch->ListPendingMatch();
}

int CMatch_CreateMatch_CotC(const char* aName, bool aPrivateMatch, const char* aJsonMatchData)
{
	CHJSON* json;
	int result;
	
	json = CHJSON::parse(aJsonMatchData);
	result = gMarmaladeClan->mMarmaladeMatch->CreateMatch(aName, aPrivateMatch, json);
	delete json;
	
	return result;
}

int CMatch_InviteFriends_CotC(const char* aMatchID, const char* aJsonArrayFriends, bool aAutoAccept, const char* aPNMessage)
{
	CHJSON* jsonFriends;
	CHJSON* jsonMessage;
	int result;
	
	jsonFriends = CHJSON::parse(aJsonArrayFriends);
	jsonMessage = CHJSON::parse(aPNMessage);
	result = gMarmaladeClan->mMarmaladeMatch->InviteFriends(aMatchID, jsonFriends, aAutoAccept, jsonMessage);
	delete jsonFriends;
	delete jsonMessage;
	
	return result;
}

int CMatch_JoinMatch_CotC(const char* aMatchID, bool aAccept, const char* aPNMessage)
{
	CHJSON* jsonMessage;
	int result;
	
	jsonMessage = CHJSON::parse(aPNMessage);
	result = gMarmaladeClan->mMarmaladeMatch->JoinMatch(aMatchID, aAccept, jsonMessage);
	delete jsonMessage;
	
	return result;
}

int CMatch_MatchMove_CotC(int aPhase, const char* aMatchID, const char* aJsonMatchState, const char* aPNMessage)
{
	CHJSON* jsonState;
	CHJSON* jsonMessage;
	int result;
	
	jsonState = CHJSON::parse(aJsonMatchState);
	jsonMessage = CHJSON::parse(aPNMessage);
	result = gMarmaladeClan->mMarmaladeMatch->MatchMove((eMatchPhase) aPhase, aMatchID, jsonState, jsonMessage);
	delete jsonState;
	delete jsonMessage;
	
	return result;
}

int CMatch_ReadBinary_CotC(const char* aMatchID, const char* aKey)
{
	return gMarmaladeClan->mMarmaladeMatch->ReadBinary(aMatchID, aKey);
}

int CMatch_WriteBinary_CotC(const char* aMatchID, const char* aKey, void* aPointer, unsigned long aLength)
{
	return gMarmaladeClan->mMarmaladeMatch->WriteBinary(aMatchID, aKey, aPointer, aLength);
}

int CMatch_Read_CotC(const char* aMatchID, const char* aKey)
{
	return gMarmaladeClan->mMarmaladeMatch->Read(aMatchID, aKey);
}

int CMatch_Write_CotC(const char* aMatchID, const char* aKey, const char* aValue)
{
	return gMarmaladeClan->mMarmaladeMatch->Write(aMatchID, aKey, aValue);
}

bool CGGoglePlay_IsConnected_CotC(void)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->IsConnected();
}

int CGGoglePlay_ShowAllLeaderboards_CotC(void)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->ShowAllLeaderboards();
}

int CGGoglePlay_ShowLeaderboard_CotC(const char* aLeaderboardID)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->ShowLeaderboard(aLeaderboardID);
}

int CGGoglePlay_LoadPeople_CotC(const char* aJsonListPeople)
{
	CHJSON* json;
	int result;
	
	json	= CHJSON::parse(aJsonListPeople);
	result  = gMarmaladeClan->mMarmaladeGooglePlay->LoadPeople(json);
	delete json;
	
	return result;
}

int CGGoglePlay_SubmitScore_CotC(const char* aLeaderboardID, long aScore, const char* aTag)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->SubmitScore(aLeaderboardID, aScore, aTag);
}

int CGGoglePlay_LoadLeaderboardMetadata_CotC(const char* aLeaderboardID)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->LoadLeaderboardMetadata(aLeaderboardID);
}

int CGGoglePlay_LoadLeaderboardsMetadata_CotC(void)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->LoadLeaderboardsMetadata();
}

int CGGoglePlay_LoadPlayerCenteredScores_CotC(const char* aLeaderboardID, int aSpan, int aLeaderboardCollection, int aMaxResults, bool aForceReload)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->LoadPlayerCenteredScores(aLeaderboardID, (eTimeSpan) aSpan, (eLeaderboardCollection) aLeaderboardCollection, aMaxResults, aForceReload);
}

int CGGoglePlay_LoadTopScores_CotC(const char* aLeaderboardID, int aSpan, int aLeaderboardCollection, int aMaxResults, bool aForceReload)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->LoadTopScores(aLeaderboardID, (eTimeSpan) aSpan, (eLeaderboardCollection) aLeaderboardCollection, aMaxResults, aForceReload);
}

int CGGoglePlay_ShowAchievements_CotC(void)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->ShowAchievements();
}

int CGGoglePlay_IncrementAchievement_CotC(const char* aAchievementID, int aNumSteps)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->IncrementAchievement(aAchievementID, aNumSteps);
}

int CGGoglePlay_LoadAchievements_CotC(bool aForceReload)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->LoadAchievements(aForceReload);
}

int CGGoglePlay_RevealAchievement_CotC(const char* aAchievementID)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->RevealAchievement(aAchievementID);
}

int CGGoglePlay_UnlockAchievement_CotC(const char* aAchievementID)
{
	return gMarmaladeClan->mMarmaladeGooglePlay->UnlockAchievement(aAchievementID);
}
