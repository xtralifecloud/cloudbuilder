#include "CMatchManagerRuntime.h"

#include <malloc.h>

#include "RuntimeComponentHelper.h"
#include "WP8RuntimeComponentManagers.h"

using namespace Platform;
using namespace CotCHelpers;

CloudBuilderWP8_RT::playerDidChangeStateDelegate^ gPlayerDidChangeState = nullptr;
CloudBuilderWP8_RT::matchReceiveDataDelegate^ gMatchReceiveData = nullptr;

CloudBuilderWP8_RT::didMatchGetMatchDataDelegate^ gDidMatchGetData;
CloudBuilderWP8_RT::didMatchListMatchDelegate^ gDidMatchListMatch;
CloudBuilderWP8_RT::didMatchListPendingMatchDelegate^ gDidMatchListPendingMatch;
CloudBuilderWP8_RT::didMatchCreateMatchDelegate^ gDidMatchCreateMatch;
CloudBuilderWP8_RT::didMatchFindMatchDelegate^ gDidMatchFindMatch;
CloudBuilderWP8_RT::didMatchInviteFriendsDelegate^ gDidMatchInviteFriends;
CloudBuilderWP8_RT::didMatchJoinMatchDelegate^ gDidMatchJoinMatch;
CloudBuilderWP8_RT::didMatchMoveDelegate^ gDidMatchMove;
CloudBuilderWP8_RT::didMatchReadDelegate^ gDidMatchRead;
CloudBuilderWP8_RT::didMatchWriteDelegate^ gDidMatchWrite;

void CloudBuilderWP8_RT::CMatch::SetPlayerDidChangeStateCallback(playerDidChangeStateDelegate^ aCallback)
{
	gPlayerDidChangeState = aCallback;
}

void CloudBuilderWP8_RT::CMatch::SetMatchReceiveDataCallback(matchReceiveDataDelegate^ aCallback)
{
	gMatchReceiveData = aCallback;
}

Platform::String^ CloudBuilderWP8_RT::CMatch::GetActiveMatchID(void)
{
	return RuntimeStringFromC(gRuntimeClan->runtimeMatch->GetActiveMatchID());
}

bool CloudBuilderWP8_RT::CMatch::HasActiveMatch(void)
{
	return gRuntimeClan->runtimeMatch->HasActiveMatch();
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CMatch::GetMatchData(Platform::String^ aMatchID, didMatchGetMatchDataDelegate^ aCallback)
{
	int		result;
	char*	matchIDStr;

	matchIDStr			= CStringFromRuntime(aMatchID);
	gDidMatchGetData	= aCallback;

	result = gRuntimeClan->runtimeMatch->GetMatchData(matchIDStr);
	free(matchIDStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CMatch::ListMatch(bool aIncludeData, didMatchListMatchDelegate^ aCallback)
{
	gDidMatchListMatch = aCallback;

	return (CloudBuilderWP8_RT::eErrorCode) gRuntimeClan->runtimeMatch->ListMatch(aIncludeData);
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CMatch::ListPendingMatch(didMatchListPendingMatchDelegate^ aCallback)
{
	gDidMatchListPendingMatch = aCallback;

	return (CloudBuilderWP8_RT::eErrorCode) gRuntimeClan->runtimeMatch->ListPendingMatch();
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CMatch::CreateMatch(Platform::String^ aName, bool aPrivateMatch, Platform::String^ aJSONMatchData, Platform::String^ aJSONOptions, didMatchCreateMatchDelegate^ aCallback)
{
	int		result;
	char*	nameStr;
	char*	matchDataStr;
	char*	optionsStr;
	CHJSON*	json1;
	CHJSON*	json2;

	nameStr					= CStringFromRuntime(aName);
	matchDataStr			= CStringFromRuntime(aJSONMatchData);
	optionsStr				= CStringFromRuntime(aJSONOptions);
	json1					= CHJSON::parse(matchDataStr);
	json2					= CHJSON::parse(optionsStr);
	gDidMatchCreateMatch	= aCallback;

	result = gRuntimeClan->runtimeMatch->CreateMatch(nameStr, aPrivateMatch, json1, json2);
	free(nameStr);
	free(matchDataStr);
	free(optionsStr);
	delete json1;
	delete json2;

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CMatch::FindMatch(Platform::String^ aJSONMatchProperties, didMatchFindMatchDelegate^ aCallback)
{
	int		result;
	char*	matchPropsStr;
	CHJSON*	json;

	matchPropsStr		= CStringFromRuntime(aJSONMatchProperties);
	json				= CHJSON::parse(matchPropsStr);
	gDidMatchFindMatch	= aCallback;

	result = gRuntimeClan->runtimeMatch->FindMatch(json);
	free(matchPropsStr);
	delete json;

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CMatch::InviteFriends(Platform::String^ aMatchID, Platform::String^ aJSONArrayFriends, bool aAutoAccept, Platform::String^ aJSONapnMessage, didMatchInviteFriendsDelegate^ aCallback)
{
	int		result;
	char*	matchIDStr;
	char*	arrayFriendsStr;
	char*	apnMessageStr;
	CHJSON*	json1;
	CHJSON*	json2;

	matchIDStr				= CStringFromRuntime(aMatchID);
	arrayFriendsStr			= CStringFromRuntime(aJSONArrayFriends);
	apnMessageStr			= CStringFromRuntime(aJSONapnMessage);
	json1					= CHJSON::parse(arrayFriendsStr);
	json2					= CHJSON::parse(apnMessageStr);
	gDidMatchInviteFriends	= aCallback;

	result = gRuntimeClan->runtimeMatch->InviteFriends(matchIDStr, json1, aAutoAccept, json2);
	free(matchIDStr);
	free(arrayFriendsStr);
	free(apnMessageStr);
	delete json1;
	delete json2;

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CMatch::JoinMatch(Platform::String^ aMatchID, bool aAccept, Platform::String^ aJSONapnMessage, didMatchJoinMatchDelegate^ aCallback)
{
	int		result;
	char*	matchIDStr;
	char*	apnMessageStr;
	CHJSON*	json;

	matchIDStr			= CStringFromRuntime(aMatchID);
	apnMessageStr		= CStringFromRuntime(aJSONapnMessage);
	json				= CHJSON::parse(apnMessageStr);
	gDidMatchJoinMatch	= aCallback;

	result = gRuntimeClan->runtimeMatch->JoinMatch(matchIDStr, aAccept, json);
	free(matchIDStr);
	free(apnMessageStr);
	delete json;

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CMatch::MatchMove(CloudBuilderWP8_RT::eMatchPhase aPhase, Platform::String^ aMatchID, Platform::String^ aJSONMatchState, Platform::String^ aJSONapnMessage, didMatchMoveDelegate^ aCallback)
{
	int		result;
	char*	matchIDStr;
	char*	matchStateStr;
	char*	apnMessageStr;
	CHJSON*	json1;
	CHJSON*	json2;

	matchIDStr		= CStringFromRuntime(aMatchID);
	matchStateStr	= CStringFromRuntime(aJSONMatchState);
	apnMessageStr	= CStringFromRuntime(aJSONapnMessage);
	json1			= CHJSON::parse(matchStateStr);
	json2			= CHJSON::parse(apnMessageStr);
	gDidMatchMove	= aCallback;

	result = gRuntimeClan->runtimeMatch->MatchMove((CloudBuilder::eMatchPhase) aPhase, matchIDStr, json1, json2);
	free(matchIDStr);
	free(matchStateStr);
	free(apnMessageStr);
	delete json1;
	delete json2;

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CMatch::Read(Platform::String^ aMatchID, Platform::String^ aKey, didMatchReadDelegate^ aCallback)
{
	int		result;
	char*	matchIDStr;
	char*	keyStr;

	matchIDStr		= CStringFromRuntime(aMatchID);
	keyStr			= CStringFromRuntime(aKey);
	gDidMatchRead	= aCallback;

	result = gRuntimeClan->runtimeMatch->Read(matchIDStr, keyStr);
	free(matchIDStr);
	free(keyStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CMatch::Write(Platform::String^ aMatchID, Platform::String^ aKey, Platform::String^ aValue, didMatchWriteDelegate^ aCallback)
{
	int		result;
	char*	matchIDStr;
	char*	keyStr;
	char*	valueStr;

	matchIDStr		= CStringFromRuntime(aMatchID);
	keyStr			= CStringFromRuntime(aKey);
	valueStr		= CStringFromRuntime(aValue);
	gDidMatchWrite	= aCallback;

	result = gRuntimeClan->runtimeMatch->Write(matchIDStr, keyStr, valueStr);
	free(matchIDStr);
	free(keyStr);
	free(valueStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}
