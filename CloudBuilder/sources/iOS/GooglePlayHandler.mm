#include "GooglePlayHandler.h"

#ifdef __MARMALADE_BUILD__
#import "GPGLeaderboardsController.h"
#import "GPGLeaderboardController.h"
#import "GPGScore.h"
#import "GPGApplicationModel.h"
#import "GPGLeaderboard.h"
#import "GPGLeaderboardModel.h"
#import "GPGLeaderboardMetadata.h"
#import "GPGManager.h"
#import "GPGAchievementController.h"
#import "GPGAchievement.h"
#import "GPGAchievementMetadata.h"
#import "GPGScoreReport.h"
#else
#import "GooglePlayGames/GPGLeaderboardsController.h"
#import "GooglePlayGames/GPGLeaderboardController.h"
#import "GooglePlayGames/GPGScore.h"
#import "GooglePlayGames/GPGApplicationModel.h"
#import "GooglePlayGames/GPGLeaderboard.h"
#import "GooglePlayGames/GPGLeaderboardModel.h"
#import "GooglePlayGames/GPGLeaderboardMetadata.h"
#import "GooglePlayGames/GPGManager.h"
#import "GooglePlayGames/GPGAchievementController.h"
#import "GooglePlayGames/GPGAchievement.h"
#import "GooglePlayGames/GPGAchievementMetadata.h"
#import "GooglePlayGames/GPGScoreReport.h"
#endif

#import <Foundation/NSString.h>

#include "GooglePlusHandler.h"
#include "CGooglePlay.h"
#include "CloudBuilder.h"
#include "CHJSON.h"
#include "CCallback.h"

using namespace CloudBuilder;
using namespace CotCHelpers;

extern GooglePlusHandler *gGPHandler;
extern CGooglePlay* gGooglePlayInstance;

CHJSON* MakeLeaderboardJSON(GPGLeaderboardMetadata* aLeaderboard);
void GPlayLoadScores(GPGLeaderboard* aLeaderboard);

@interface GooglePlayDelegate : NSObject <GPGLeaderboardsControllerDelegate, GPGLeaderboardControllerDelegate, GPGAchievementControllerDelegate>
@end

@implementation GooglePlayDelegate

- (void)leaderboardsViewControllerDidFinish: (GPGLeaderboardsController *)viewController {
	NSLog(@"Dismissing leaderboards controller");
	[[[UIApplication sharedApplication] keyWindow].rootViewController dismissViewControllerAnimated:YES completion:nil];
}

- (void)leaderboardViewControllerDidFinish: (GPGLeaderboardsController *)viewController {
	NSLog(@"Dismissing leaderboard controller");
	[[[UIApplication sharedApplication] keyWindow].rootViewController dismissViewControllerAnimated:YES completion:nil];
}

- (void)achievementViewControllerDidFinish:(GPGAchievementController *)viewController {
	NSLog(@"Dismissing achievements controller");
	[[[UIApplication sharedApplication] keyWindow].rootViewController dismissViewControllerAnimated:YES completion:nil];
}

@end

static GooglePlayDelegate* gGPlayDelegate = nil;

void GPlayInit(void)
{
	gGPlayDelegate = [[GooglePlayDelegate alloc] init];
}

bool GPlayIsConnected(void)
{
	return [[GPGManager sharedInstance] hasAuthorizer];
}

eErrorCode GPlayShowAllLeaderboards(void)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		GPGLeaderboardsController *leadsController = [[GPGLeaderboardsController alloc] init];
		leadsController.leaderboardsDelegate = gGPlayDelegate;
		[[[UIApplication sharedApplication] keyWindow].rootViewController presentViewController:leadsController animated:YES completion:nil];
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

eErrorCode GPlayShowLeaderboard(const char* aLeaderboardID)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		GPGLeaderboardController *leadController = [[GPGLeaderboardController alloc] initWithLeaderboardId:[NSString stringWithUTF8String:aLeaderboardID]];
		leadController.leaderboardDelegate = gGPlayDelegate;
		[[[UIApplication sharedApplication] keyWindow].rootViewController presentViewController:leadController animated:YES completion:nil];
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

eErrorCode GPlaySubmitScore(const char* aLeaderboardID, long long aScore, const char* aTag)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		GPGScore*   scoreSubmit;
		
		scoreSubmit = [GPGScore scoreWithLeaderboardId:[NSString stringWithUTF8String:aLeaderboardID]];
		scoreSubmit.value = aScore;
		scoreSubmit.scoreTag = [NSString stringWithUTF8String:aTag];
		[scoreSubmit submitScoreWithCompletionHandler:^(GPGScoreReport *report, NSError *error) {
			eErrorCode  cotcError;
			
			if(error.code == 0)
				cotcError = enNoErr;
			else
				cotcError = enErrorGooglePlayServices;

			gGooglePlayInstance->didSubmitScore(cotcError, error.code, [report.leaderboardId UTF8String]);
		}];
		
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

DECLARE_TASK(CGooglePlay, _LoadLeaderboardMetadata);

CCloudResult *_LoadLeaderboardMetadata::execute()
{
	GPGLeaderboardModel* leaderboardModel;
	GPGLeaderboardMetadata* metadata;
	CHJSON* json;
	CCloudResult* result;
	
	leaderboardModel = [GPGManager sharedInstance].applicationModel.leaderboard;
	metadata = [leaderboardModel metadataForLeaderboardId:[NSString stringWithUTF8String:mJSON->GetStringSafe("leaderboardID")]];
	json = MakeLeaderboardJSON(metadata);
	
	result = new CCloudResult(enNoErr);
	result->Add("leaderboard", json);
	
	return result;
}

void _LoadLeaderboardMetadata::done(const CCloudResult *res)
{
	eErrorCode err = res->GetErrorCode();
	self->didLoadLeaderboardMetadata(err, 0, res->Get("leaderboard"));
}		

eErrorCode GPlayLoadLeaderboardMetadata(const char* aLeaderboardID)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		TASKM(_LoadLeaderboardMetadata, gGooglePlayInstance);
		task->mJSON->AddStringSafe("leaderboardID", aLeaderboardID);
		task->run();
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

DECLARE_TASK(CGooglePlay, _LoadLeaderboardsMetadata);

CCloudResult *_LoadLeaderboardsMetadata::execute()
{
	GPGLeaderboardModel* leaderboardModel;
	GPGLeaderboardMetadata* metadata;
	NSArray* metadataArray;
	CHJSON* jsonArray;
	CCloudResult* result;
	
	jsonArray	= CHJSON::Array();
	leaderboardModel = [GPGManager sharedInstance].applicationModel.leaderboard;
	metadataArray = [leaderboardModel allMetadata];
	for(metadata in metadataArray)
		jsonArray->Add(MakeLeaderboardJSON(metadata));
	
	result = new CCloudResult(enNoErr);
	result->Add("leaderboards", jsonArray);
	
	return result;
}

void _LoadLeaderboardsMetadata::done(const CCloudResult *res)
{
	eErrorCode err = res->GetErrorCode();
	self->didLoadLeaderboardsMetadata(err, 0, res->Get("leaderboards"));
}

eErrorCode GPlayLoadLeaderboardsMetadata(void)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		TASKM(_LoadLeaderboardsMetadata, gGooglePlayInstance);
		task->run();
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

eErrorCode GPlayLoadPlayerCenteredScores(const char* aLeaderboardID, int aSpan, int aLeaderboardCollection, int aMaxResults, bool aForceReload)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		GPGLeaderboard* leaderboard;
		
		leaderboard = [GPGLeaderboard leaderboardWithId:[NSString stringWithUTF8String:aLeaderboardID]];
		leaderboard.personalWindow = TRUE;
		if(aSpan == tsDaily)
			leaderboard.timeScope = GPGLeaderboardTimeScopeToday;
		else if(aSpan == tsWeekly)
			leaderboard.timeScope = GPGLeaderboardTimeScopeThisWeek;
		else
			leaderboard.timeScope = GPGLeaderboardTimeScopeAllTime;
		if(aLeaderboardCollection == lcPublic)
			leaderboard.social = TRUE;
		else
			leaderboard.social = FALSE;
		
		GPlayLoadScores(leaderboard);
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

eErrorCode GPlayLoadTopScores(const char* aLeaderboardID, int aSpan, int aLeaderboardCollection, int aMaxResults, bool aForceReload)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		GPGLeaderboard* leaderboard;
		
		leaderboard = [GPGLeaderboard leaderboardWithId:[NSString stringWithUTF8String:aLeaderboardID]];
		leaderboard.personalWindow = FALSE;
		if(aSpan == tsDaily)
			leaderboard.timeScope = GPGLeaderboardTimeScopeToday;
		else if(aSpan == tsWeekly)
			leaderboard.timeScope = GPGLeaderboardTimeScopeThisWeek;
		else
			leaderboard.timeScope = GPGLeaderboardTimeScopeAllTime;
		if(aLeaderboardCollection == lcPublic)
			leaderboard.social = TRUE;
		else
			leaderboard.social = FALSE;
		
		GPlayLoadScores(leaderboard);
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

eErrorCode GPlayShowAchievements(void)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		GPGAchievementController *achievementController = [[GPGAchievementController alloc] init];
		achievementController.achievementDelegate = gGPlayDelegate;
		[[[UIApplication sharedApplication] keyWindow].rootViewController presentViewController:achievementController animated:YES completion:nil];
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

DECLARE_TASK(CGooglePlay, _LoadAchievements);

CCloudResult *_LoadAchievements::execute()
{
	GPGAchievementModel* achievementModel;
	GPGAchievementMetadata* metadata;
	NSArray* metadataArray;
	CHJSON* jsonArray;
	CCloudResult* result;
	
	jsonArray	= CHJSON::Array();
	achievementModel = [GPGManager sharedInstance].applicationModel.achievement;
	metadataArray = [achievementModel allMetadata];

	for(metadata in metadataArray)
	{
		CHJSON* json;
		int type, state;
		
		json = new CHJSON;
		
		type = metadata.type;
		state = metadata.state;
		
		json->AddStringSafe("id", [metadata.achievementId UTF8String]);
		json->Add("type", type);
		json->AddStringSafe("description", [metadata.achievementDescription UTF8String]);
		json->AddStringSafe("name", [metadata.name UTF8String]);
		if(state == GPGAchievementStateHidden)
			json->Add("state", (int) asAchievementHidden);
		else if(state == GPGAchievementStateRevealed)
			json->Add("state", (int) asAchievementRevealed);
		else if(state == GPGAchievementStateUnlocked)
			json->Add("state", (int) asAchievementUnlocked);
		if(type == GPGAchievementTypeIncremental)
		{
			json->Add("totalSteps", (int) metadata.numberOfSteps);
			json->Add("currentSteps", (int) metadata.completedSteps);
		}
		
		jsonArray->Add(json);
	}
	
	result  = new CCloudResult(enNoErr);
	result->Add("achievements", jsonArray);
	
	return result;
}

void _LoadAchievements::done(const CCloudResult *res)
{
	eErrorCode err = res->GetErrorCode();
	self->didLoadAchievements(err, 0, res->Get("achievements"));
}

eErrorCode GPlayLoadAchievements(void)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		TASKM(_LoadAchievements, gGooglePlayInstance);
		task->run();
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

eErrorCode GPlayIncrementAchievement(const char* aAchievementID, int aNumSteps)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		GPGAchievement* achievement;
		
		achievement = [GPGAchievement achievementWithId:[NSString stringWithUTF8String:aAchievementID]];
		[achievement incrementAchievementNumSteps:aNumSteps completionHandler:
		 ^(BOOL newlyUnlocked, int currentSteps, NSError *error) {
			 eErrorCode cotcError;
			 
			 if(error.code == 0)
				 cotcError = enNoErr;
			 else
				 cotcError = enErrorGooglePlayServices;
			 
			 gGooglePlayInstance->didIncrementAchievement(cotcError, error.code, aAchievementID, newlyUnlocked);
		 }];
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

eErrorCode GPlayRevealAchievement(const char* aAchievementID)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		GPGAchievement* achievement;
		
		achievement = [GPGAchievement achievementWithId:[NSString stringWithUTF8String:aAchievementID]];
		[achievement revealAchievementWithCompletionHandler:^(GPGAchievementState state, NSError *error) {
			eErrorCode cotcError;
			
			if(error.code == 0)
				cotcError = enNoErr;
			else
				cotcError = enErrorGooglePlayServices;
			
			gGooglePlayInstance->didRevealAchievement(cotcError, error.code, aAchievementID);
		}];
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

eErrorCode GPlayUnlockAchievement(const char* aAchievementID)
{
	if(gGPHandler->mGooglePlayAvailable)
	{
		GPGAchievement* achievement;
		
		achievement = [GPGAchievement achievementWithId:[NSString stringWithUTF8String:aAchievementID]];
		[achievement unlockAchievementWithCompletionHandler:^(BOOL newlyUnlocked, NSError *error) {
			eErrorCode cotcError;
			
			if(error.code == 0)
				cotcError = enNoErr;
			else
				cotcError = enErrorGooglePlayServices;
			
			gGooglePlayInstance->didUnlockAchievement(cotcError, error.code, aAchievementID);
		}];
		
		return enNoErr;
	}
	else
		return enUserNotLoggedInGooglePlayServices;
}

CHJSON* MakeLeaderboardJSON(GPGLeaderboardMetadata* aLeaderboard)
{
	CHJSON* json;
	
	json	= new CHJSON;
	
	if(aLeaderboard != nil)
	{
		json->AddStringSafe("DisplayName", [aLeaderboard.title UTF8String]);
		json->AddStringSafe("ID", [aLeaderboard.leaderboardId UTF8String]);
		if(aLeaderboard.order == GPGLeaderboardOrderLargerIsBetter)
			json->Add("ScoreOrder", (int) loLargerIsBetter);
		else
			json->Add("ScoreOrder", (int) loSmallerIsBetter);
		json->AddStringSafe("IconUri", [[aLeaderboard.iconUrl absoluteString] UTF8String]);
	}
	
	return json;
}

void GPlayLoadScores(GPGLeaderboard* aLeaderboard)
{
	[aLeaderboard loadScoresWithCompletionHandler:^(NSArray *scores, NSError *error) {
		GPGScore* score;
		CHJSON* jsonArray;
		GPGLeaderboardModel* leaderboardModel;
		GPGLeaderboardMetadata* metadata;
		CHJSON* json;
		eErrorCode cotcError;
		
		leaderboardModel = [GPGManager sharedInstance].applicationModel.leaderboard;
		metadata = [leaderboardModel metadataForLeaderboardId:aLeaderboard.leaderboardId];
		json = MakeLeaderboardJSON(metadata);
		jsonArray = CHJSON::Array();
		
		if(error.code == 0)
		{
			cotcError = enNoErr;
			
			for(score in scores)
			{
				CHJSON* json;
				
				json = new CHJSON;
				json->AddStringSafe("DisplayRank", [score.formattedRank UTF8String]);
				json->AddStringSafe("DisplayScore", [score.formattedScore UTF8String]);
				json->AddStringSafe("ScoreHolder", [score.displayName UTF8String]);
				json->Add("Timestamp", (int) score.writeTimestamp);
			}
		}
		else
			cotcError = enErrorGooglePlayServices;
		
		if(aLeaderboard.personalWindow == TRUE)
			gGooglePlayInstance->didLoadPlayerCenteredScores(cotcError, error.code, json, jsonArray);
		else
			gGooglePlayInstance->didLoadTopScores(cotcError, error.code, json, jsonArray);
		
		delete json;
		delete jsonArray;
	}];
}
