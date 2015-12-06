//
//  MarmaladeWrapper.cpp
//  CloudBuilderMarmalade_iphone
//
//  Created by Michael EL BAKI on 7/28/13.
//
//

#include "MarmaladeWrapper.h"

#include "string.h"

#ifdef __ANDROID__
#include "MarmaladeCotC.h"
#else
#include "MarmaladeCallbacks.h"
#endif

using namespace CloudBuilder;
using namespace CotCHelpers;

MarmaladeClan* gMarmaladeClan = NULL;

#pragma mark - MarmaladeNotificationManager

MarmaladeNotificationManager::MarmaladeNotificationManager(bool aPopNextCallback, bool aHandleAdminEvent, bool aHasSpecificEvent)
: CNotificationManager(aPopNextCallback, aHandleAdminEvent, aHasSpecificEvent)
{
}

#pragma mark - MarmaladeClan

MarmaladeClan::MarmaladeClan() : CClan(new MarmaladeNotificationManager(true, true, true))
{
	gMarmaladeClan = this;
	
	mMarmaladeGame = new MarmaladeGameManager();
	CNotificationManager::Instance()->SetGameDelegate(mMarmaladeGame);
	
	mMarmaladeLogin = new MarmaladeLoginManager();
	CNotificationManager::Instance()->SetUserDelegate(mMarmaladeLogin);
	
	mMarmaladeTribe = new MarmaladeTribeManager();
	CNotificationManager::Instance()->SetTribeDelegate(mMarmaladeTribe);

	mMarmaladeMatch = new MarmaladeMatchManager();
	CNotificationManager::Instance()->SetMatchDelegate(mMarmaladeMatch);
	
	mMarmaladeGooglePlay = new MarmaladeGooglePlay();
}

void MarmaladeClan::didFinishSetup(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cclan_didfinishsetup)(int);
	
	cclan_didfinishsetup = (void (*)(int)) gCloudBuilderCallbacks[ceCClan_didSetup];
	cclan_didfinishsetup(aError);
#else
	CClan_didSetup_CotC(aError);
#endif
}

void MarmaladeClan::didBatchEnd(CloudBuilder::eErrorCode aError, const CotCHelpers::CHJSON *aResults)
{
#ifdef __ANDROID__
	void (*cclan_didbatchend)(int, const char*);
	
	cclan_didbatchend = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCClan_didBatchEnd];
	cclan_didbatchend(aError, aResults ? aResults->print() : NULL);
#else
	CClan_didBatchEnd_CotC(aError, aResults ? aResults->print() : NULL);
#endif
}

#pragma mark - MarmaladeLoginManager

void MarmaladeLoginManager::didRegisterAndLogin(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cuser_didregisterandlogin)(int);
	
	cuser_didregisterandlogin = (void (*)(int)) gCloudBuilderCallbacks[ceCUser_didRegisterAndLogin];
	cuser_didregisterandlogin(aError);
#else
	CUser_didRegisterAndLogin_CotC(aError);
#endif
}

void MarmaladeLoginManager::didLogin(eErrorCode aError, const CotCHelpers::CHJSON *aJsonProfile)
{
#ifdef __ANDROID__
	void (*cuser_didlogin)(int, const char*);
	
	cuser_didlogin = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCUser_didLogin];
	cuser_didlogin(aError, aJsonProfile ? aJsonProfile->print() : NULL);
#else
	CUser_didLogin_CotC(aError, aJsonProfile ? aJsonProfile->print() : NULL);
#endif
}

void MarmaladeLoginManager::didLoginWithFacebook(eErrorCode aError, const CotCHelpers::CHJSON *aJsonProfile, const char *aDesc)
{
#ifdef __ANDROID__
	void (*cuser_didloginwithfacebook)(int, const char*, const char*);
	
	cuser_didloginwithfacebook = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCUser_didLoginWithFacebook];
	cuser_didloginwithfacebook(aError, aJsonProfile ? aJsonProfile->print() : NULL, aDesc ? strdup(aDesc) : NULL);
#else
	CUser_didLoginWithFacebook_CotC(aError, aJsonProfile ? aJsonProfile->print() : NULL, aDesc ? strdup(aDesc) : NULL);
#endif
}

void MarmaladeLoginManager::didLoginWithGooglePlus(eErrorCode aError, const CotCHelpers::CHJSON *aJsonProfile, const char *aDesc)
{
#ifdef __ANDROID__
	void (*cuser_didloginwithgoogleplus)(int, const char*, const char*);
	
	cuser_didloginwithgoogleplus = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCUser_didLoginWithGooglePlus];
	cuser_didloginwithgoogleplus(aError, aJsonProfile ? aJsonProfile->print() : NULL, aDesc ? strdup(aDesc) : NULL);
#else
	CUser_didLoginWithGooglePlus_CotC(aError, aJsonProfile ? aJsonProfile->print() : NULL, aDesc ? strdup(aDesc) : NULL);
#endif
}

void MarmaladeLoginManager::didLoginWithGameCenter(eErrorCode aError, const CotCHelpers::CHJSON *aJsonProfile, const char *aDesc)
{
#ifdef __ANDROID__
	void (*cuser_didloginwithgamecenter)(int, const char*, const char*);
	
	cuser_didloginwithgamecenter = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCUser_didLoginWithGameCenter];
	cuser_didloginwithgamecenter(aError, aJsonProfile ? aJsonProfile->print() : NULL, aDesc ? strdup(aDesc) : NULL);
#else
	CUser_didLoginWithGameCenter_CotC(aError, aJsonProfile ? aJsonProfile->print() : NULL, aDesc ? strdup(aDesc) : NULL);
#endif
}

void MarmaladeLoginManager::didLogout(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cuser_didlogout)(int);
	
	cuser_didlogout = (void (*)(int)) gCloudBuilderCallbacks[ceCUser_didLogout];
	cuser_didlogout(aError);
#else
	CUser_didLogout_CotC(aError);
#endif
}

void MarmaladeLoginManager::didLinkAccountWithFacebook(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cuser_didlinkaccountwithfacebook)(int);
	
	cuser_didlinkaccountwithfacebook = (void (*)(int)) gCloudBuilderCallbacks[ceCUser_didLinkAccountWithFacebook];
	cuser_didlinkaccountwithfacebook(aError);
#else
	CUser_didLinkAccountWithFacebook_CotC(aError);
#endif
}

void MarmaladeLoginManager::didLinkAccountWithGooglePlus(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cuser_didlinkaccountwithgoogleplus)(int);
	
	cuser_didlinkaccountwithgoogleplus = (void (*)(int)) gCloudBuilderCallbacks[ceCUser_didLinkAccountWithGooglePlus];
	cuser_didlinkaccountwithgoogleplus(aError);
#else
	CUser_didLinkAccountWithGooglePlus_CotC(aError);
#endif
}

void MarmaladeLoginManager::didLinkAccountWithGameCenter(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cuser_didlinkaccountwithgamecenter)(int);
	
	cuser_didlinkaccountwithgamecenter = (void (*)(int)) gCloudBuilderCallbacks[ceCUser_didLinkAccountWithGameCenter];
	cuser_didlinkaccountwithgamecenter(aError);
#else
	CUser_didLinkAccountWithGameCenter_CotC(aError);
#endif
}

void MarmaladeLoginManager::didChangePassword(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cuser_didchangepassword)(int);
	
	cuser_didchangepassword = (void (*)(int)) gCloudBuilderCallbacks[ceCUser_didChangePassword];
	cuser_didchangepassword(aError);
#else
	CUser_didChangePassword_CotC(aError);
#endif
}

void MarmaladeLoginManager::didMailPassword(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cuser_didmailpassword)(int);
	
	cuser_didmailpassword = (void (*)(int)) gCloudBuilderCallbacks[ceCUser_didMailPassword];
	cuser_didmailpassword(aError);
#else
	CUser_didMailPassword_CotC(aError);
#endif
}

void MarmaladeLoginManager::didSetUserProfile(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cuser_didsetuserprofile)(int);
	
	cuser_didsetuserprofile = (void (*)(int)) gCloudBuilderCallbacks[ceCUser_didSetUserProfile];
	cuser_didsetuserprofile(aError);
#else
	CUser_didSetUserProfile_CotC(aError);
#endif
}

void MarmaladeLoginManager::didGetUserProfile(eErrorCode aError, const CHJSON *aData)
{
#ifdef __ANDROID__
	void (*cuser_didgetuserprofile)(int, const char*);
	
	cuser_didgetuserprofile = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCUser_didGetUserProfile];
	cuser_didgetuserprofile(aError, aData ? aData->print() : NULL);
#else
	CUser_didGetUserProfile_CotC(aError, aData ? aData->print() : NULL);
#endif
}

void MarmaladeLoginManager::didPublishOnMyFacebookWall(eErrorCode aError)
{
	{
#ifdef __ANDROID__
		void (*cuser_didpublishonmyfacebookwall)(int);
		
		cuser_didpublishonmyfacebookwall = (void (*)(int)) gCloudBuilderCallbacks[ceCUser_didPublishOnMyFacebookWall];
		cuser_didpublishonmyfacebookwall(aError);
#else
		CUser_didPublishOnMyFacebookWall_CotC(aError);
#endif
	}
	
}

void MarmaladeLoginManager::didReadBinary(eErrorCode aError, const char *aKey, void *aPointer, unsigned long aLength)
{
#ifdef __ANDROID__
	void (*cuser_didreadbinary)(int, const char*, void*, unsigned long);
	
	cuser_didreadbinary = (void (*)(int, const char*, void*, unsigned long)) gCloudBuilderCallbacks[ceCUser_didReadBinary];
	cuser_didreadbinary(aError, aKey ? strdup(aKey) : NULL, aPointer, aLength);
#else
	CUser_didReadBinary_CotC(aError, aKey ? strdup(aKey) : NULL, aPointer, aLength);
#endif
}

void MarmaladeLoginManager::didWriteBinary(eErrorCode aError, const char* aKey, void* aPointer)
{
#ifdef __ANDROID__
	void (*cuser_didwritebinary)(int, const char*, void*);
	
	cuser_didwritebinary = (void (*)(int, const char*, void*)) gCloudBuilderCallbacks[ceCUser_didWriteBinary];
	cuser_didwritebinary(aError, aKey ? strdup(aKey) : NULL, aPointer);
#else
	CUser_didWriteBinary_CotC(aError, aKey ? strdup(aKey) : NULL, aPointer);
#endif
}

void MarmaladeLoginManager::didRead(eErrorCode aError, const char *aKey, const char* aValue)
{
#ifdef __ANDROID__
	void (*cuser_didread)(int, const char*, const char*);
	
	cuser_didread = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCUser_didRead];
	cuser_didread(aError, aKey ? strdup(aKey) : NULL, aValue ? strdup(aValue) : NULL);
#else
	CUser_didRead_CotC(aError, aKey ? strdup(aKey) : NULL, aValue ? strdup(aValue) : NULL);
#endif
}

void MarmaladeLoginManager::didWrite(eErrorCode aError, const char* aKey)
{
#ifdef __ANDROID__
	void (*cuser_didwrite)(int, const char*);
	
	cuser_didwrite = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCUser_didWrite];
	cuser_didwrite(aError, aKey ? strdup(aKey) : NULL);
#else
	CUser_didWrite_CotC(aError, aKey ? strdup(aKey) : NULL);
#endif
}

void MarmaladeLoginManager::didSetProperties(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cuser_didsetproperties)(int);
	
	cuser_didsetproperties = (void (*)(int)) gCloudBuilderCallbacks[ceCUser_didSetProperties];
	cuser_didsetproperties(aError);
#else
	CUser_didSetProperties_CotC(aError);
#endif
}

void MarmaladeLoginManager::didGetProperties(eErrorCode aError, bool aCanBeFound, const CHJSON* aPropertiesList)
{
#ifdef __ANDROID__
	void (*cuser_didgetproperties)(int, bool, const char*);
	
	cuser_didgetproperties = (void (*)(int, bool, const char*)) gCloudBuilderCallbacks[ceCUser_didGetProperties];
	cuser_didgetproperties(aError, aCanBeFound, aPropertiesList ? aPropertiesList->print() : NULL);
#else
	CUser_didGetProperties_CotC(aError, aCanBeFound, aPropertiesList ? aPropertiesList->print() : NULL);
#endif
}

void MarmaladeLoginManager::didCheckUser(eErrorCode aError, bool aExists)
{
#ifdef __ANDROID__
	void (*cuser_didcheckuser)(int, bool);
	
	cuser_didcheckuser = (void (*)(int, bool)) gCloudBuilderCallbacks[ceCUser_didCheckUser];
	cuser_didcheckuser(aError, aExists);
#else
	CUser_didCheckUser_CotC(aError, aExists);
#endif
}

void MarmaladeLoginManager::didSetAvatarSource(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cuser_didsetavatarsource)(int);
	
	cuser_didsetavatarsource = (void (*)(int)) gCloudBuilderCallbacks[ceCUser_didSetAvatarSource];
	cuser_didsetavatarsource(aError);
#else
	CUser_didSetAvatarSource_CotC(aError);
#endif
}

bool MarmaladeLoginManager::receivedNotifyUser(const char *aFromUserID, const CHJSON* aData)
{
#ifdef __ANDROID__
	void (*cuser_receivednotifyuser)(const char*, const char*);
	
	cuser_receivednotifyuser = (void (*)(const char*, const char*)) gCloudBuilderCallbacks[ceGlobal_UserReceivedNotifyUser];
	cuser_receivednotifyuser(aFromUserID ? strdup(aFromUserID) : NULL, aData ? aData->print() : NULL);
#else
	CUser_receivedNotifyUser_CotC(aFromUserID ? strdup(aFromUserID) : NULL, aData ? aData->print() : NULL);
#endif

	return true;
}

#pragma mark - MarmaladeGameManager

void MarmaladeGameManager::didScore(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cgame_didScore)(int);
	
	cgame_didScore = (void (*)(int)) gCloudBuilderCallbacks[ceCGame_didScore];
	cgame_didScore(aError);
#else
	CGame_didScore_CotC(aError);
#endif
}

void MarmaladeGameManager::didGetRank(eErrorCode aError, const char *aMode, long aRank)
{
#ifdef __ANDROID__
	void (*cgame_didgetrank)(int, const char*, long);
	
	cgame_didgetrank = (void (*)(int, const char*, long)) gCloudBuilderCallbacks[ceCGame_didGetRank];
	cgame_didgetrank(aError, aMode ? strdup(aMode) : NULL, aRank);
#else
	CGame_didGetRank_CotC(aError, aMode ? strdup(aMode) : NULL, aRank);
#endif
}

void MarmaladeGameManager::didBestHighScore(eErrorCode aError, const char * aMode, const CHJSON *aJson)
{
#ifdef __ANDROID__
	void (*cgame_didbesthighscore)(int, const char*, const char*);
	
	cgame_didbesthighscore = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCGame_didBestHighScore];
	cgame_didbesthighscore(aError, aMode ? strdup(aMode) : NULL, aJson ? aJson->print() : NULL);
#else
	CGame_didBestHighScore_CotC(aError, aMode ? strdup(aMode) : NULL, aJson ? aJson->print() : NULL);
#endif
}

void MarmaladeGameManager::didCenteredScore(eErrorCode aError, const char * aMode, const CHJSON *aJson)
{
#ifdef __ANDROID__
	void (*cgame_didcenteredscore)(int, const char*, const char*);
	
	cgame_didcenteredscore = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCGame_didCenteredScore];
	cgame_didcenteredscore(aError, aMode ? strdup(aMode) : NULL, aJson ? aJson->print() : NULL);
#else
	CGame_didCenteredScore_CotC(aError, aMode ? strdup(aMode) : NULL, aJson ? aJson->print() : NULL);
#endif
}

void MarmaladeGameManager::didGetRankArray(eErrorCode aError, const CHJSON *aRankArray)
{
#ifdef __ANDROID__
	void (*cgame_didgetrankarray)(int, const char*);
	
	cgame_didgetrankarray = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCGame_didGetRankArray];
	cgame_didgetrankarray(aError, aRankArray ? aRankArray->print() : NULL);
#else
	CGame_didGetRankArray_CotC(aError, aRankArray ? aRankArray->print() : NULL);
#endif
}

void MarmaladeGameManager::didBestHighScoreArray(eErrorCode aError, const CHJSON *aArrayModes, const CHJSON *aScoreArray)
{
#ifdef __ANDROID__
	void (*cgame_didbesthighscorearray)(int, const char*, const char*);
	
	cgame_didbesthighscorearray = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCGame_didBestHighScoreArray];
	cgame_didbesthighscorearray(aError, aArrayModes ? aArrayModes->print() : NULL, aScoreArray ? aScoreArray->print() : NULL);
#else
	CGame_didBestHighScoreArray_CotC(aError, aArrayModes ? aArrayModes->print() : NULL, aScoreArray ? aScoreArray->print() : NULL);
#endif
}

void MarmaladeGameManager::didReadBinary(eErrorCode aError, const char *aKey, void *aPointer, unsigned long aLength)
{
#ifdef __ANDROID__
	void (*cgame_didreadbinary)(int, const char*, void*, unsigned long);
	
	cgame_didreadbinary = (void (*)(int, const char*, void*, unsigned long)) gCloudBuilderCallbacks[ceCGame_didReadBinary];
	cgame_didreadbinary(aError, aKey ? strdup(aKey) : NULL, aPointer, aLength);
#else
	CGame_didReadBinary_CotC(aError, aKey ? strdup(aKey) : NULL, aPointer, aLength);
#endif
}

void MarmaladeGameManager::didWriteBinary(eErrorCode aError, const char* aKey, void* aPointer)
{
#ifdef __ANDROID__
	void (*cgame_didwritebinary)(int, const char*, void*);
	
	cgame_didwritebinary = (void (*)(int, const char*, void*)) gCloudBuilderCallbacks[ceCGame_didWriteBinary];
	cgame_didwritebinary(aError, aKey ? strdup(aKey) : NULL, aPointer);
#else
	CGame_didWriteBinary_CotC(aError, aKey ? strdup(aKey) : NULL, aPointer);
#endif
}

void MarmaladeGameManager::didRead(eErrorCode aError, const char *aKey, const char* aValue)
{
#ifdef __ANDROID__
	void (*cgame_didread)(int, const char*, const char*);
	
	cgame_didread = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCGame_didRead];
	cgame_didread(aError, aKey ? strdup(aKey) : NULL, aValue ? strdup(aValue) : NULL);
#else
	CGame_didRead_CotC(aError, aKey ? strdup(aKey) : NULL, aValue ? strdup(aValue) : NULL);
#endif
}

void MarmaladeGameManager::didWrite(eErrorCode aError, const char* aKey)
{
#ifdef __ANDROID__
	void (*cgame_didwrite)(int, const char*);
	
	cgame_didwrite = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCGame_didWrite];
	cgame_didwrite(aError, aKey ? strdup(aKey) : NULL);
#else
	CGame_didWrite_CotC(aError, aKey ? strdup(aKey) : NULL);
#endif
}

#pragma mark - MarmaladeTribeManager

void MarmaladeTribeManager::didListUsers(eErrorCode aError, const CHJSON* aArrayUsers)
{
#ifdef __ANDROID__
	void (*ctribe_didlistusers)(int, const char*);
	
	ctribe_didlistusers = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCTribe_didListFriends];
	ctribe_didlistusers(aError, aArrayUsers ? aArrayUsers->print() : NULL);
#else
	CTribe_didListFriends_CotC(aError, aArrayUsers ? aArrayUsers->print() : NULL);
#endif
}

void MarmaladeTribeManager::didListGlobalFriends(eErrorCode aError, const CHJSON* aArrayFriends)
{
#ifdef __ANDROID__
	void (*ctribe_didlistglobalfriends)(int, const char*);
	
	ctribe_didlistglobalfriends = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCTribe_didListGlobalFriends];
	ctribe_didlistglobalfriends(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#else
	CTribe_didListGlobalFriends_CotC(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#endif
}

void MarmaladeTribeManager::MarmaladeTribeManager::didBlacklistGlobalFriends(eErrorCode aError, const CHJSON* aArrayFriends)
{
#ifdef __ANDROID__
	void (*ctribe_didblacklistglobalfriends)(int, const char*);
	
	ctribe_didblacklistglobalfriends = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCTribe_didBlacklistGlobalFriends];
	ctribe_didblacklistglobalfriends(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#else
	CTribe_didBlacklistGlobalFriends_CotC(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#endif
}

void MarmaladeTribeManager::didChangeGlobalRelationshipStatus(eErrorCode aError, const char *aFriendPseudo, eRelationChange aNewState)
{
#ifdef __ANDROID__
	void (*ctribe_didchangeglobalrelationshipstatus)(int, const char*, int);
	
	ctribe_didchangeglobalrelationshipstatus = (void (*)(int, const char*, int)) gCloudBuilderCallbacks[ceCTribe_didChangeGlobalRelationshipStatus];
	ctribe_didchangeglobalrelationshipstatus(aError, aFriendPseudo ? strdup(aFriendPseudo) : NULL, (int) aNewState);
#else
	CTribe_didChangeGlobalRelationshipStatus_CotC(aError, aFriendPseudo ? strdup(aFriendPseudo) : NULL, (int) aNewState);
#endif
}

void MarmaladeTribeManager::didListFriends(eErrorCode aError, const CHJSON* aArrayFriends)
{
#ifdef __ANDROID__
	void (*ctribe_didlistfriends)(int, const char*);
	
	ctribe_didlistfriends = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCTribe_didListFriends];
	ctribe_didlistfriends(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#else
	CTribe_didListFriends_CotC(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#endif
}

void MarmaladeTribeManager::didBlacklistFriends(eErrorCode aError, const CHJSON* aArrayFriends)
{
#ifdef __ANDROID__
	void (*ctribe_didblacklistfriends)(int, const char*);
	
	ctribe_didblacklistfriends = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCTribe_didBlacklistFriends];
	ctribe_didblacklistfriends(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#else
	CTribe_didBlacklistFriends_CotC(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#endif
}

void MarmaladeTribeManager::didChangeRelationshipStatus(eErrorCode aError, const char *aFriendPseudo, eRelationChange aNewState)
{
#ifdef __ANDROID__
	void (*ctribe_didchangerelationshipstatus)(int, const char*, int);
	
	ctribe_didchangerelationshipstatus = (void (*)(int, const char*, int)) gCloudBuilderCallbacks[ceCTribe_didChangeRelationshipStatus];
	ctribe_didchangerelationshipstatus(aError, aFriendPseudo ? strdup(aFriendPseudo) : NULL, (int) aNewState);
#else
	CTribe_didChangeRelationshipStatus_CotC(aError, aFriendPseudo ? strdup(aFriendPseudo) : NULL, (int) aNewState);
#endif
}

void MarmaladeTribeManager::didListFacebookFriends(eErrorCode aError, const CHJSON* aArrayFriends)
{
#ifdef __ANDROID__
	void (*ctribe_didlistfacebookfriends)(int, const char*);
	
	ctribe_didlistfacebookfriends = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCTribe_didListFacebookFriends];
	ctribe_didlistfacebookfriends(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#else
	CTribe_didListFacebookFriends_CotC(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#endif
}

void MarmaladeTribeManager::didListGooglePlusFriends(eErrorCode aError, const CHJSON* aArrayFriends)
{
#ifdef __ANDROID__
	void (*ctribe_didlistgoogleplusfriends)(int, const char*);
	
	ctribe_didlistgoogleplusfriends = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCTribe_didListGooglePlusFriends];
	ctribe_didlistgoogleplusfriends(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#else
	CTribe_didListGooglePlusFriends_CotC(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#endif
}

void MarmaladeTribeManager::didListGameCenterFriends(eErrorCode aError, const CHJSON* aArrayFriends)
{
#ifdef __ANDROID__
	void (*ctribe_didlistgamecenterfriends)(int, const char*);
	
	ctribe_didlistgamecenterfriends = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCTribe_didListGameCenterFriends];
	ctribe_didlistgamecenterfriends(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#else
	CTribe_didListGameCenterFriends_CotC(aError, aArrayFriends ? aArrayFriends->print() : NULL);
#endif
}

void MarmaladeTribeManager::didInviteFriendByMail(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*ctribe_didlinvitefriendbymail)(int);
	
	ctribe_didlinvitefriendbymail = (void (*)(int)) gCloudBuilderCallbacks[ceCTribe_didInviteFriendByMail];
	ctribe_didlinvitefriendbymail(aError);
#else
	CTribe_didInviteFriendByMail_CotC(aError);
#endif
}

void MarmaladeTribeManager::didInviteFriendByFBID(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*ctribe_didlinvitefriendbyfbid)(int);
	
	ctribe_didlinvitefriendbyfbid = (void (*)(int)) gCloudBuilderCallbacks[ceCTribe_didInviteFriendByFBID];
	ctribe_didlinvitefriendbyfbid(aError);
#else
	CTribe_didInviteFriendByFBID_CotC(aError);
#endif
}

void MarmaladeTribeManager::didInviteFriendByGooglePlusID(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*ctribe_didlinvitefriendbygoogleplusid)(int);
	
	ctribe_didlinvitefriendbygoogleplusid = (void (*)(int)) gCloudBuilderCallbacks[ceCTribe_didInviteFriendByGooglePlusID];
	ctribe_didlinvitefriendbygoogleplusid(aError);
#else
	CTribe_didInviteFriendByGooglePlusID_CotC(aError);
#endif
}

void MarmaladeTribeManager::didFriendsBestHighScore(eErrorCode aError, const char *aMode, const CotCHelpers::CHJSON *aJson)
{
#ifdef __ANDROID__
	void (*ctribe_didfriendsbesthighscore)(int, const char*, const char*);
	
	ctribe_didfriendsbesthighscore = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCTribe_didFriendsBestHighScore];
	ctribe_didfriendsbesthighscore(aError, aMode ? strdup(aMode) : NULL, aJson ? aJson->print() : NULL);
#else
	CTribe_didFriendsBestHighScore_CotC(aError, aMode ? strdup(aMode) : NULL, aJson ? aJson->print() : NULL);
#endif
}

void MarmaladeTribeManager::didFriendsBestHighScoreArray(eErrorCode aError, const CHJSON *aArrayModes, const CHJSON *aScoreArray)
{
#ifdef __ANDROID__
	void (*ctribe_didfriendsbesthighscorearray)(int, const char*, const char*);
	
	ctribe_didfriendsbesthighscorearray = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCTribe_didFriendsBestHighScoreArray];
	ctribe_didfriendsbesthighscorearray(aError, aArrayModes ? aArrayModes->print() : NULL, aScoreArray ? aScoreArray->print() : NULL);
#else
	CTribe_didFriendsBestHighScoreArray_CotC(aError, aArrayModes ? aArrayModes->print() : NULL, aScoreArray ? aScoreArray->print() : NULL);
#endif
}

void MarmaladeTribeManager::didFindOpponents(eErrorCode aError, const CHJSON* aArrayPseudo)
{
#ifdef __ANDROID__
	void (*ctribe_didfindopponents)(int, const char*);
	
	ctribe_didfindopponents = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCTribe_didFindOpponents];
	ctribe_didfindopponents(aError, aArrayPseudo ? aArrayPseudo->print() : NULL);
#else
	CTribe_didFindOpponents_CotC(aError, aArrayPseudo ? aArrayPseudo->print() : NULL);
#endif
}

bool MarmaladeTribeManager::relationshipHasChanged(const char *aFriendPseudo, eRelationChange aNewState)
{
#ifdef __ANDROID__
	void (*ctribe_relationshiphaschanged)(const char*, int);
	
	ctribe_relationshiphaschanged = (void (*)(const char*, int)) gCloudBuilderCallbacks[ceGlobal_TribeRelationshipHasChanged];
	ctribe_relationshiphaschanged(aFriendPseudo ? strdup(aFriendPseudo) : NULL, aNewState);
#else
	CTribe_relationshipHasChanged_CotC(aFriendPseudo ? strdup(aFriendPseudo) : NULL, aNewState);
#endif

	return true;
}

#pragma mark - MarmaladeMatchManager

void MarmaladeMatchManager::didGetMatchData(eErrorCode aError, const char* aMatchID, const CHJSON *aMatchData)
{
#ifdef __ANDROID__
	void (*cmatch_didgetmatchdata)(int, const char*, const char*);
	
	cmatch_didgetmatchdata = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCMatch_didGetMatchData];
	cmatch_didgetmatchdata(aError, aMatchID ? strdup(aMatchID) : NULL, aMatchData ? aMatchData->print() : NULL);
#else
	CMatch_didGetMatchData_CotC(aError, aMatchID ? strdup(aMatchID) : NULL, aMatchData ? aMatchData->print() : NULL);
#endif
}

void MarmaladeMatchManager::didListMatch(eErrorCode aError, const CHJSON *aArrayMatch)
{
#ifdef __ANDROID__
	void (*cmatch_didlistmatch)(int, const char*);
	
	cmatch_didlistmatch = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCMatch_didListMatch];
	cmatch_didlistmatch(aError, aArrayMatch ? aArrayMatch->print() : NULL);
#else
	CMatch_didListMatch_CotC(aError, aArrayMatch ? aArrayMatch->print() : NULL);
#endif
}

void MarmaladeMatchManager::didListPendingMatch(eErrorCode aError, const CHJSON *aArrayMatch)
{
#ifdef __ANDROID__
	void (*cmatch_didlistpendingmatch)(int, const char*);
	
	cmatch_didlistpendingmatch = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCMatch_didListPendingMatch];
	cmatch_didlistpendingmatch(aError, aArrayMatch ? aArrayMatch->print() : NULL);
#else
	CMatch_didListPendingMatch_CotC(aError, aArrayMatch ? aArrayMatch->print() : NULL);
#endif
}

void MarmaladeMatchManager::didCreateMatch(eErrorCode aError, const char* aMatchID)
{
#ifdef __ANDROID__
	void (*cmatch_didcreatematch)(int, const char*);
	
	cmatch_didcreatematch = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCMatch_didCreateMatch];
	cmatch_didcreatematch(aError, aMatchID ? strdup(aMatchID) : NULL);
#else
	CMatch_didCreateMatch_CotC(aError, aMatchID ? strdup(aMatchID) : NULL);
#endif
}

void MarmaladeMatchManager::didInviteFriends(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cmatch_didinvitefriends)(int);
	
	cmatch_didinvitefriends = (void (*)(int)) gCloudBuilderCallbacks[ceCMatch_didInviteFriends];
	cmatch_didinvitefriends(aError);
#else
	CMatch_didInviteFriends_CotC(aError);
#endif
}

void MarmaladeMatchManager::didJoinMatch(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cmatch_didjoinmatch)(int);
	
	cmatch_didjoinmatch = (void (*)(int)) gCloudBuilderCallbacks[ceCMatch_didJoinMatch];
	cmatch_didjoinmatch(aError);
#else
	CMatch_didJoinMatch_CotC(aError);
#endif
}

void MarmaladeMatchManager::didMatchMove(eErrorCode aError)
{
#ifdef __ANDROID__
	void (*cmatch_didmatchmove)(int);
	
	cmatch_didmatchmove = (void (*)(int)) gCloudBuilderCallbacks[ceCMatch_didMatchMove];
	cmatch_didmatchmove(aError);
#else
	CMatch_didMatchMove_CotC(aError);
#endif
}

void MarmaladeMatchManager::didReadBinary(eErrorCode aError, const char* aMatchID, const char *aKey, void *aPointer, unsigned long aLength)
{
#ifdef __ANDROID__
	void (*cmatch_didreadbinary)(int, const char*, const char*, void*, unsigned long);
	
	cmatch_didreadbinary = (void (*)(int, const char*, const char*, void*, unsigned long)) gCloudBuilderCallbacks[ceCMatch_didReadBinary];
	cmatch_didreadbinary(aError, aMatchID ? strdup(aMatchID) : NULL, aKey ? strdup(aKey) : NULL, aPointer, aLength);
#else
	CMatch_didReadBinary_CotC(aError, aMatchID ? strdup(aMatchID) : NULL, aKey ? strdup(aKey) : NULL, aPointer, aLength);
#endif
}

void MarmaladeMatchManager::didWriteBinary(eErrorCode aError, const char* aMatchID, const char* aKey, void* aPointer)
{
#ifdef __ANDROID__
	void (*cmatch_didwritebinary)(int, const char*, const char*, void*);
	
	cmatch_didwritebinary = (void (*)(int, const char*, const char*, void*)) gCloudBuilderCallbacks[ceCMatch_didWriteBinary];
	cmatch_didwritebinary(aError, aMatchID ? strdup(aMatchID) : NULL, aKey ? strdup(aKey) : NULL, aPointer);
#else
	CMatch_didWriteBinary_CotC(aError, aMatchID ? strdup(aMatchID) : NULL, aKey ? strdup(aKey) : NULL, aPointer);
#endif
}

void MarmaladeMatchManager::didRead(eErrorCode aError, const char* aMatchID, const char *aKey, const char* aValue)
{
#ifdef __ANDROID__
	void (*cmatch_didread)(int, const char*, const char*, const char*);
	
	cmatch_didread = (void (*)(int, const char*, const char*, const char*)) gCloudBuilderCallbacks[ceCMatch_didRead];
	cmatch_didread(aError, aMatchID ? strdup(aMatchID) : NULL, aKey ? strdup(aKey) : NULL, aValue ? strdup(aValue) : NULL);
#else
	CMatch_didRead_CotC(aError, aMatchID ? strdup(aMatchID) : NULL, aKey ? strdup(aKey) : NULL, aValue ? strdup(aValue) : NULL);
#endif
}

void MarmaladeMatchManager::didWrite(eErrorCode aError, const char* aMatchID, const char* aKey)
{
#ifdef __ANDROID__
	void (*cmatch_didwrite)(int, const char*, const char*);
	
	cmatch_didwrite = (void (*)(int, const char*, const char*)) gCloudBuilderCallbacks[ceCMatch_didWrite];
	cmatch_didwrite(aError, aMatchID ? strdup(aMatchID) : NULL, aKey ? strdup(aKey) : NULL);
#else
	CMatch_didWrite_CotC(aError, aMatchID ? strdup(aMatchID) : NULL, aKey ? strdup(aKey) : NULL);
#endif
}

bool MarmaladeMatchManager::playerDidChangeState(const char* aMatchID, const char* aPseudoID, eMatchStatus aStatus)
{
#ifdef __ANDROID__
	void (*cmatch_playerdidchangestate)(const char*, const char*, int);
	
	cmatch_playerdidchangestate = (void (*)(const char*, const char*, int)) gCloudBuilderCallbacks[ceGlobal_MatchPlayerDidChangeState];
	cmatch_playerdidchangestate(aMatchID ? strdup(aMatchID) : NULL, aPseudoID ? strdup(aPseudoID) : NULL, aStatus);
#else
	CMatch_playerDidChangeState_CotC(aMatchID ? strdup(aMatchID) : NULL, aPseudoID ? strdup(aPseudoID) : NULL, aStatus);
#endif
	
	return true;
}

bool MarmaladeMatchManager::matchReceiveData(const char* aMatchID, const char* aFromPseudoID, eMatchPhase aPhase, const CHJSON *aMatchState)
{
#ifdef __ANDROID__
	void (*cmatch_matchreceivedata)(const char*, const char*, int, const char*);
	
	cmatch_matchreceivedata = (void (*)(const char*, const char*, int, const char*)) gCloudBuilderCallbacks[ceGlobal_MatchMatchReceiveData];
	cmatch_matchreceivedata(aMatchID ? strdup(aMatchID) : NULL, aFromPseudoID ? strdup(aFromPseudoID) : NULL, aPhase, aMatchState ? aMatchState->print() : NULL);
#else
	CMatch_matchReceiveData_CotC(aMatchID ? strdup(aMatchID) : NULL, aFromPseudoID ? strdup(aFromPseudoID) : NULL, aPhase, aMatchState ? aMatchState->print() : NULL);
#endif
	
	return true;
}

#pragma mark - MarmaladeNotificationManager

void MarmaladeNotificationManager::didNotifyUser(eErrorCode aError, void* aReference)
{
/*	SResultNotifyUser  result;
	
	result.mErrorCode   = aError;
	if(aReference)
		result.mReference  = aReference;
	else
		result.mReference  = NULL;
	
	s3eResult r = s3eEdkCallbacksEnqueue(S3E_EXT_CLOUDBUILDERMARMALADE_HASH, CLOUDBUILDERMARMALADE_CALLBACK_NOTIFICATION_DID_NOTIFY_USER, &result, sizeof(SResultNotifyUser), NULL, S3E_TRUE, NULL, NULL);
	if(r == S3E_RESULT_ERROR)
	{
		IwDebugTraceLinePrintf("Could not invoke CNotificationManager::didRead: %d", r);
	}*/
}

bool MarmaladeNotificationManager::receivedMaintenanceNotification(const char *aKind, const CotCHelpers::CHJSON* aData)
{
#ifdef __ANDROID__
	void (*cnotification_receivedmaintenancenotification)(const char*, const char*);
	
	cnotification_receivedmaintenancenotification = (void (*)(const char*, const char*)) gCloudBuilderCallbacks[ceGlobal_NotificationReceivedMaintenanceNotification];
	cnotification_receivedmaintenancenotification(aKind ? strdup(aKind) : NULL, aData ? aData->print() : NULL);
#else
	CNotification_receivedMaintenanceNotification_CotC(aKind ? strdup(aKind) : NULL, aData ? aData->print() : NULL);
#endif
	
	return true;
}

void MarmaladeNotificationManager::didBeginLookingForNotification()
{
#ifdef __ANDROID__
	void (*cnotification_didbeginlookingfornotification)(void);
	
	cnotification_didbeginlookingfornotification = (void (*)(void)) gCloudBuilderCallbacks[ceGlobal_NotificationDidBeginLookingForNotification];
	cnotification_didbeginlookingfornotification();
#else
	CNotification_didBeginLookingForNotification_CotC();
#endif
}

void MarmaladeNotificationManager::didEndLookingForNotification(int pendingEvents)
{
#ifdef __ANDROID__
	void (*cnotification_didendlookingfornotification)(int);
	
	cnotification_didendlookingfornotification = (void (*)(int)) gCloudBuilderCallbacks[ceGlobal_NotificationDidEndLookingForNotification];
	cnotification_didendlookingfornotification(pendingEvents);
#else
	CNotification_didEndLookingForNotification_CotC(pendingEvents);
#endif
}

void MarmaladeNotificationManager::didRegisterDevice(eErrorCode error)
{
#ifdef __ANDROID__
	void (*cnotification_didregisterdevice)(int);
	
	cnotification_didregisterdevice = (void (*)(int)) gCloudBuilderCallbacks[ceGlobal_NotificationDidRegisterDevice];
	cnotification_didregisterdevice(error);
#else
	CNotification_didRegisterDevice_CotC(error);
#endif
}

#pragma mark - MarmaladeGooglePlay

void MarmaladeGooglePlay::didLoadPeople(eErrorCode aError, const CotCHelpers::CHJSON* aListDetails)
{
#ifdef __ANDROID__
	void (*cgoogleplay_didloadpeople)(int, const char*);
	
	cgoogleplay_didloadpeople = (void (*)(int, const char*)) gCloudBuilderCallbacks[ceCGooglePlay_didLoadPeople];
	cgoogleplay_didloadpeople(aError, aListDetails ? aListDetails->print() : NULL);
#else
	CGGoglePlay_didLoadPeople_CotC(aError, aListDetails ? aListDetails->print() : NULL);
#endif
}

void MarmaladeGooglePlay::didSubmitScore(eErrorCode aError, int aGooglePlayServicesError, const char* aLeaderboardID)
{
#ifdef __ANDROID__
	void (*cgoogleplay_didsubmitscore)(int, int, const char*);
	
	cgoogleplay_didsubmitscore = (void (*)(int, int, const char*)) gCloudBuilderCallbacks[ceCGooglePlay_didSubmitScore];
	cgoogleplay_didsubmitscore(aError, aGooglePlayServicesError, aLeaderboardID ? strdup(aLeaderboardID) : NULL);
#else
	CGGoglePlay_didSubmitScore_CotC(aError, aGooglePlayServicesError, aLeaderboardID ? strdup(aLeaderboardID) : NULL);
#endif
}

void MarmaladeGooglePlay::didLoadLeaderboardMetadata(eErrorCode aError, int aGooglePlayServicesError, const CotCHelpers::CHJSON* aLeaderboardMetadata)
{
#ifdef __ANDROID__
	void (*cgoogleplay_didloadleaderboardmetadata)(int, int, const char*);
	
	cgoogleplay_didloadleaderboardmetadata = (void (*)(int, int, const char*)) gCloudBuilderCallbacks[ceCGooglePlay_didLoadLeaderboardMetadata];
	cgoogleplay_didloadleaderboardmetadata(aError, aGooglePlayServicesError, aLeaderboardMetadata ? aLeaderboardMetadata->print() : NULL);
#else
	CGGoglePlay_didLoadLeaderboardMetadata_CotC(aError, aGooglePlayServicesError, aLeaderboardMetadata ? aLeaderboardMetadata->print() : NULL);
#endif
}

void MarmaladeGooglePlay::didLoadLeaderboardsMetadata(eErrorCode aError, int aGooglePlayServicesError, const CotCHelpers::CHJSON* aLeaderboardMetadata)
{
#ifdef __ANDROID__
	void (*cgoogleplay_didloadleaderboardsmetadata)(int, int, const char*);
	
	cgoogleplay_didloadleaderboardsmetadata = (void (*)(int, int, const char*)) gCloudBuilderCallbacks[ceCGooglePlay_didLoadLeaderboardsMetadata];
	cgoogleplay_didloadleaderboardsmetadata(aError, aGooglePlayServicesError, aLeaderboardMetadata ? aLeaderboardMetadata->print() : NULL);
#else
	CGGoglePlay_didLoadLeaderboardsMetadata_CotC(aError, aGooglePlayServicesError, aLeaderboardMetadata ? aLeaderboardMetadata->print() : NULL);
#endif
}

void MarmaladeGooglePlay::didLoadPlayerCenteredScores(eErrorCode aError, int aGooglePlayServicesError, const CotCHelpers::CHJSON* aLeaderboard, const CotCHelpers::CHJSON* aScores)
{
#ifdef __ANDROID__
	void (*cgoogleplay_didloadplayercenteredscores)(int, int, const char*, const char*);
	
	cgoogleplay_didloadplayercenteredscores = (void (*)(int, int, const char*, const char*)) gCloudBuilderCallbacks[ceCGooglePlay_didLoadPlayerCenteredScores];
	cgoogleplay_didloadplayercenteredscores(aError, aGooglePlayServicesError, aLeaderboard ? aLeaderboard->print() : NULL, aScores ? aScores->print() : NULL);
#else
	CGGoglePlay_didLoadPlayerCenteredScores_CotC(aError, aGooglePlayServicesError, aLeaderboard ? aLeaderboard->print() : NULL, aScores ? aScores->print() : NULL);
#endif
}

void MarmaladeGooglePlay::didLoadTopScores(eErrorCode aError, int aGooglePlayServicesError, const CotCHelpers::CHJSON* aLeaderboard, const CotCHelpers::CHJSON* aScores)
{
#ifdef __ANDROID__
	void (*cgoogleplay_didloadtopscores)(int, int, const char*, const char*);
	
	cgoogleplay_didloadtopscores = (void (*)(int, int, const char*, const char*)) gCloudBuilderCallbacks[ceCGooglePlay_didLoadTopScores];
	cgoogleplay_didloadtopscores(aError, aGooglePlayServicesError, aLeaderboard ? aLeaderboard->print() : NULL, aScores ? aScores->print() : NULL);
#else
	CGGoglePlay_didLoadTopScores_CotC(aError, aGooglePlayServicesError, aLeaderboard ? aLeaderboard->print() : NULL, aScores ? aScores->print() : NULL);
#endif
}

void MarmaladeGooglePlay::didIncrementAchievement(eErrorCode aError, int aGooglePlayServicesError, const char* aAchievementID, bool aUnlocked)
{
#ifdef __ANDROID__
	void (*cgoogleplay_didincrementachievement)(int, int, const char*, bool);
	
	cgoogleplay_didincrementachievement = (void (*)(int, int, const char*, bool)) gCloudBuilderCallbacks[ceCGooglePlay_didIncrementAchievement];
	cgoogleplay_didincrementachievement(aError, aGooglePlayServicesError, aAchievementID ? strdup(aAchievementID) : NULL, aUnlocked);
#else
	CGGoglePlay_didIncrementAchievement_CotC(aError, aGooglePlayServicesError, aAchievementID ? strdup(aAchievementID) : NULL, aUnlocked);
#endif
}

void MarmaladeGooglePlay::didLoadAchievements(eErrorCode aError, int aGooglePlayServicesError, const CotCHelpers::CHJSON* aAchievements)
{
#ifdef __ANDROID__
	void (*cgoogleplay_didloadachievements)(int, int, const char*);
	
	cgoogleplay_didloadachievements = (void (*)(int, int, const char*)) gCloudBuilderCallbacks[ceCGooglePlay_didLoadAchievements];
	cgoogleplay_didloadachievements(aError, aGooglePlayServicesError, aAchievements ? aAchievements->print() : NULL);
#else
	CGGoglePlay_didLoadAchievements_CotC(aError, aGooglePlayServicesError, aAchievements ? aAchievements->print() : NULL);
#endif
}

void MarmaladeGooglePlay::didRevealAchievement(eErrorCode aError, int aGooglePlayServicesError, const char* aAchievementID)
{
#ifdef __ANDROID__
	void (*cgoogleplay_didrevealachievement)(int, int, const char*);
	
	cgoogleplay_didrevealachievement = (void (*)(int, int, const char*)) gCloudBuilderCallbacks[ceCGooglePlay_didRevealAchievement];
	cgoogleplay_didrevealachievement(aError, aGooglePlayServicesError, aAchievementID ? strdup(aAchievementID) : NULL);
#else
	CGGoglePlay_didRevealAchievement_CotC(aError, aGooglePlayServicesError, aAchievementID ? strdup(aAchievementID) : NULL);
#endif
}

void MarmaladeGooglePlay::didUnlockAchievement(eErrorCode aError, int aGooglePlayServicesError, const char* aAchievementID)
{
#ifdef __ANDROID__
	void (*cgoogleplay_didunlockachievement)(int, int, const char*);
	
	cgoogleplay_didunlockachievement = (void (*)(int, int, const char*)) gCloudBuilderCallbacks[ceCGooglePlay_didUnlockAchievement];
	cgoogleplay_didunlockachievement(aError, aGooglePlayServicesError, aAchievementID ? strdup(aAchievementID) : NULL);
#else
	CGGoglePlay_didUnlockAchievement_CotC(aError, aGooglePlayServicesError, aAchievementID ? strdup(aAchievementID) : NULL);
#endif
}
