//
//  Marmalade_CotC.h
//  
//
//  Created by Michael EL BAKI on 23/Sep/13.
//
//

#ifndef ____MARMALADE_CALLBACKS_ENUMS__
#define ____MARMALADE_CALLBACKS_ENUMS__

enum eCallbacksEnums
{
    ceGlobal_UserReceivedNotifyUser = 0,
    ceGlobal_NotificationReceivedMaintenanceNotification,
    ceGlobal_NotificationDidBeginLookingForNotification,
    ceGlobal_NotificationDidEndLookingForNotification,
    ceGlobal_NotificationDidRegisterDevice,
    ceGlobal_TribeRelationshipHasChanged,
    ceGlobal_MatchPlayerDidChangeState,
    ceGlobal_MatchMatchReceiveData,
    
    ceCClan_didSetup,
    ceCClan_didBatchEnd,
    
    ceCUser_didRegisterAndLogin,
    ceCUser_didLogin,
    ceCUser_didLoginWithFacebook,
    ceCUser_didLoginWithGooglePlus,
    ceCUser_didLoginWithGameCenter,
    ceCUser_didLogout,
    ceCUser_didLinkAccountWithFacebook,
    ceCUser_didLinkAccountWithGooglePlus,
    ceCUser_didLinkAccountWithGameCenter,
    ceCUser_didChangePassword,
    ceCUser_didMailPassword,
    ceCUser_didSetUserProfile,
    ceCUser_didGetUserProfile,
    ceCUser_didPublishOnMyFacebookWall,
    ceCUser_didReadBinary,
    ceCUser_didWriteBinary,
    ceCUser_didRead,
    ceCUser_didWrite,
    ceCUser_didSetProperties,
    ceCUser_didGetProperties,
    ceCUser_didCheckUser,
    ceCUser_didSetAvatarSource,
    
    ceCGame_didScore,
    ceCGame_didGetRank,
    ceCGame_didBestHighScore,
    ceCGame_didCenteredScore,
    ceCGame_didGetRankArray,
    ceCGame_didBestHighScoreArray,
    ceCGame_didReadBinary,
    ceCGame_didWriteBinary,
    ceCGame_didRead,
    ceCGame_didWrite,
    
    ceCTribe_didListUsers,
    ceCTribe_didListGlobalFriends,
    ceCTribe_didBlacklistGlobalFriends,
    ceCTribe_didChangeGlobalRelationshipStatus,
    ceCTribe_didListFriends,
    ceCTribe_didBlacklistFriends,
    ceCTribe_didChangeRelationshipStatus,
    ceCTribe_didListFacebookFriends,
    ceCTribe_didListGooglePlusFriends,
    ceCTribe_didListGameCenterFriends,
    ceCTribe_didInviteFriendByMail,
    ceCTribe_didInviteFriendByFBID,
    ceCTribe_didInviteFriendByGooglePlusID,
    ceCTribe_didFriendsBestHighScore,
    ceCTribe_didFriendsBestHighScoreArray,
    ceCTribe_didFindOpponents,
    
    ceCMatch_didGetMatchData,
    ceCMatch_didListMatch,
    ceCMatch_didListPendingMatch,
    ceCMatch_didCreateMatch,
    ceCMatch_didInviteFriends,
    ceCMatch_didJoinMatch,
    ceCMatch_didMatchMove,
    ceCMatch_didReadBinary,
    ceCMatch_didWriteBinary,
    ceCMatch_didRead,
    ceCMatch_didWrite,
    
    ceCGooglePlay_didLoadPeople,
    ceCGooglePlay_didSubmitScore,
    ceCGooglePlay_didLoadLeaderboardMetadata,
    ceCGooglePlay_didLoadLeaderboardsMetadata,
    ceCGooglePlay_didLoadPlayerCenteredScores,
    ceCGooglePlay_didLoadTopScores,
    ceCGooglePlay_didIncrementAchievement,
    ceCGooglePlay_didLoadAchievements,
    ceCGooglePlay_didRevealAchievement,
    ceCGooglePlay_didUnlockAchievement,

    ceNumCallbacks
};

#endif //   ____MARMALADE_CALLBACKS_ENUMS__
