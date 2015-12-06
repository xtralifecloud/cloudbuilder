#pragma once

#include "CCloudBuilderRuntime.h"

namespace CloudBuilderWP8_RT
{
    public enum class eMatchStatus {
		eMatchClaimed = 0,
		eMatchJoin,
		eMatchRefuse,
		eMatchSuspend,
		eMatchResume
	};

	public enum class eMatchPhase {
		ePhaseStart = 0,
		ePhaseMove,
		ePhaseEnd
	};

	public delegate bool playerDidChangeStateDelegate(Platform::String^ aMatchID, Platform::String^ aPseudoID, eMatchStatus aStatus);
	public delegate bool matchReceiveDataDelegate(Platform::String^ aMatchID, Platform::String^ aFromPseudoID, eMatchPhase aPhase, Platform::String^ aJSONMatchState);

	public delegate void didMatchGetMatchDataDelegate(eErrorCode aErrorCode, Platform::String^ aMatchID, Platform::String^ aJSONMatchData);
	public delegate void didMatchListMatchDelegate(eErrorCode aErrorCode, Platform::String^ aJSONArrayMatch);
	public delegate void didMatchListPendingMatchDelegate(eErrorCode aErrorCode, Platform::String^ aJSONArrayMatch);
	public delegate void didMatchCreateMatchDelegate(eErrorCode aErrorCode, Platform::String^ aMatchID);
	public delegate void didMatchFindMatchDelegate(eErrorCode aErrorCode, Platform::String^ aJSONMatchList);
	public delegate void didMatchInviteFriendsDelegate(eErrorCode aErrorCode);
	public delegate void didMatchJoinMatchDelegate(eErrorCode aErrorCode);
	public delegate void didMatchMoveDelegate(eErrorCode aErrorCode);
	public delegate void didMatchReadDelegate(eErrorCode aErrorCode, Platform::String^ aMatchID, Platform::String^ aKey, Platform::String^ aValue);
	public delegate void didMatchWriteDelegate(eErrorCode aErrorCode, Platform::String^ aMatchID, Platform::String^ aKey);

	public ref class CMatch sealed
    {
    public:
		static void SetPlayerDidChangeStateCallback(playerDidChangeStateDelegate^ aCallback);
		static void SetMatchReceiveDataCallback(matchReceiveDataDelegate^ aCallback);

		static Platform::String^ GetActiveMatchID(void);
		static bool HasActiveMatch(void);
		static eErrorCode GetMatchData(Platform::String^ aMatchID, didMatchGetMatchDataDelegate^ aCallback);
		static eErrorCode ListMatch(bool aIncludeData, didMatchListMatchDelegate^ aCallback);
		static eErrorCode ListPendingMatch(didMatchListPendingMatchDelegate^ aCallback);
		static eErrorCode CreateMatch(Platform::String^ aName, bool aPrivateMatch, Platform::String^ aJSONMatchData, Platform::String^ aJSONOptions, didMatchCreateMatchDelegate^ aCallback);
		static eErrorCode FindMatch(Platform::String^ aJSONMatchProperties, didMatchFindMatchDelegate^ aCallback);
		static eErrorCode InviteFriends(Platform::String^ aMatchID, Platform::String^ aJSONArrayFriends, bool aAutoAccept, Platform::String^ aJSONapnMessage, didMatchInviteFriendsDelegate^ aCallback);
		static eErrorCode JoinMatch(Platform::String^ aMatchID, bool aAccept, Platform::String^ aJSONapnMessage, didMatchJoinMatchDelegate^ aCallback);
		static eErrorCode MatchMove(eMatchPhase aPhase, Platform::String^ aMatchID, Platform::String^ aJSONMatchState, Platform::String^ aJSONapnMessage, didMatchMoveDelegate^ aCallback);
		static eErrorCode Read(Platform::String^ aMatchID, Platform::String^ aKey, didMatchReadDelegate^ aCallback);
		static eErrorCode Write(Platform::String^ aMatchID, Platform::String^ aKey, Platform::String^ aValue, didMatchWriteDelegate^ aCallback);
	};
}