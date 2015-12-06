#pragma once

#include "CCloudBuilderRuntime.h"

namespace CloudBuilderWP8_RT
{
	public enum class eRelationChange {
		rcNone = 0,
        rcFriend,
        rcForget,
        rcBlacklist
	};

	public delegate bool relationshipHasChangedDelegate(Platform::String^ aFriendPseudo, eRelationChange aNewState);

	public delegate void didTribeListUsersDelegate(eErrorCode aErrorCode, Platform::String^ aJSONUsers);
	public delegate void didTribeListFriendsDelegate(eErrorCode aErrorCode, Platform::String^ aJSONFriends);
	public delegate void didTribeBlacklistFriendsDelegate(eErrorCode aErrorCode, Platform::String^ aJSONFriends);
	public delegate void didTribeChangeRelationshipStatusDelegate(eErrorCode aErrorCode, Platform::String^ aFriendPseudo, eRelationChange aNewState);
	public delegate void didTribeFriendsBestHighScoreDelegate(eErrorCode aErrorCode, Platform::String^ aMode, Platform::String^ aJSONScores);
	public delegate void didTribeFriendsBestHighScoreArrayDelegate(eErrorCode aErrorCode, Platform::String^ aJSONArrayModes, Platform::String^ aJSONScores);
	public delegate void didTribeFindOpponentsDelegate(eErrorCode aErrorCode, Platform::String^ aJSONArrayPseudos);

	public ref class CTribe sealed
    {
    public:
		static void SetRelationshipHasChangedCallback(relationshipHasChangedDelegate^ aCallback);

		static eErrorCode ListUsers(Platform::String^ aContainsString, didTribeListUsersDelegate^ aCallback);
		static eErrorCode ListFriends(didTribeListFriendsDelegate^ aCallback);
		static eErrorCode BlacklistFriends(didTribeBlacklistFriendsDelegate^ aCallback);
		static eErrorCode ChangeRelationshipStatus(Platform::String^ aFriendPseudo, eRelationChange aNewState, didTribeChangeRelationshipStatusDelegate^ aCallback);
		static eErrorCode FriendsBestHighScore(Platform::String^ aMode, int aScoreType, didTribeFriendsBestHighScoreDelegate^ aCallback);
		static eErrorCode FriendsBestHighScoreArray(Platform::String^ aJSONArrayModes, int aScoreType, didTribeFriendsBestHighScoreArrayDelegate^ aCallback);
		static eErrorCode FindOpponents(Platform::String^ aJSONFilter, didTribeFindOpponentsDelegate^ aCallback);
    };
}