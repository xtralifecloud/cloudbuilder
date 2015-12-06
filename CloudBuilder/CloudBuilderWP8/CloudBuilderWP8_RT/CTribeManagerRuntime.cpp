#include "CTribeManagerRuntime.h"

#include <malloc.h>

#include "RuntimeComponentHelper.h"
#include "WP8RuntimeComponentManagers.h"

using namespace Platform;
using namespace CotCHelpers;

CloudBuilderWP8_RT::relationshipHasChangedDelegate^ gRelationshipHasChanged = nullptr;

CloudBuilderWP8_RT::didTribeListUsersDelegate^ gDidTribeListUsers;
CloudBuilderWP8_RT::didTribeListFriendsDelegate^ gDidTribeListFriends;
CloudBuilderWP8_RT::didTribeBlacklistFriendsDelegate^ gDidTribeBlacklistFriends;
CloudBuilderWP8_RT::didTribeChangeRelationshipStatusDelegate^ gDidTribeChangeRelationshipStatus;
CloudBuilderWP8_RT::didTribeFriendsBestHighScoreDelegate^ gDidTribeFriendsBestHighScore;
CloudBuilderWP8_RT::didTribeFriendsBestHighScoreArrayDelegate^ gDidTribeFriendsBestHighScoreArray;
CloudBuilderWP8_RT::didTribeFindOpponentsDelegate^ gDidTribeFindOpponents;

void CloudBuilderWP8_RT::CTribe::SetRelationshipHasChangedCallback(relationshipHasChangedDelegate^ aCallback)
{
	gRelationshipHasChanged = aCallback;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CTribe::ListUsers(Platform::String^ aContainsString, didTribeListUsersDelegate^ aCallback)
{
	int		result;
	char*	containsStr;

	containsStr			= CStringFromRuntime(aContainsString);
	gDidTribeListUsers	= aCallback;

	result = gRuntimeClan->runtimeTribe->ListUsers(containsStr);
	free(containsStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CTribe::ListFriends(didTribeListFriendsDelegate^ aCallback)
{
	int		result;

	gDidTribeListFriends	= aCallback;

	result = gRuntimeClan->runtimeTribe->ListFriends();

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CTribe::BlacklistFriends(didTribeBlacklistFriendsDelegate^ aCallback)
{
	int		result;

	gDidTribeBlacklistFriends	= aCallback;

	result = gRuntimeClan->runtimeTribe->BlacklistFriends();

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CTribe::ChangeRelationshipStatus(Platform::String^ aFriendPseudo, eRelationChange aNewState, didTribeChangeRelationshipStatusDelegate^ aCallback)
{
	int		result;
	char*	friendPseudoStr;

	friendPseudoStr						= CStringFromRuntime(aFriendPseudo);
	gDidTribeChangeRelationshipStatus	= aCallback;

	result = gRuntimeClan->runtimeTribe->ChangeRelationshipStatus(friendPseudoStr, (CloudBuilder::eRelationChange) aNewState);
	free(friendPseudoStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CTribe::FriendsBestHighScore(Platform::String^ aMode, int aScoreType, didTribeFriendsBestHighScoreDelegate^ aCallback)
{
	int		result;
	char*	modeStr;

	modeStr							= CStringFromRuntime(aMode);
	gDidTribeFriendsBestHighScore	= aCallback;

	result = gRuntimeClan->runtimeTribe->FriendsBestHighScore(modeStr, (CloudBuilder::eScoreType) aScoreType);
	free(modeStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CTribe::FriendsBestHighScoreArray(Platform::String^ aJSONArrayModes, int aScoreType, didTribeFriendsBestHighScoreArrayDelegate^ aCallback)
{
	int		result;
	char*	modesStr;
	CHJSON*	json;

	modesStr							= CStringFromRuntime(aJSONArrayModes);
	json								= CHJSON::parse(modesStr);
	gDidTribeFriendsBestHighScoreArray	= aCallback;

	result = gRuntimeClan->runtimeTribe->FriendsBestHighScoreArray(json, (CloudBuilder::eScoreType) aScoreType);
	free(modesStr);
	delete json;

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CTribe::FindOpponents(Platform::String^ aJSONFilter, didTribeFindOpponentsDelegate^ aCallback)
{
	int		result;
	char*	filterStr;
	CHJSON*	json;

	filterStr				= CStringFromRuntime(aJSONFilter);
	json					= CHJSON::parse(filterStr);
	gDidTribeFindOpponents	= aCallback;

	result = gRuntimeClan->runtimeTribe->FindOpponents(json);
	free(filterStr);
	delete json;

	return (CloudBuilderWP8_RT::eErrorCode) result;
}