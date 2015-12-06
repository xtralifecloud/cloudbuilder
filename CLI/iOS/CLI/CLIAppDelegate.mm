//
//  CLIAppDelegate.m
//  CLI
//
//  Created by roland on 10/05/13.
//  Copyright (c) 2013 Clan of the CLoud. All rights reserved.
//

#import "CLIAppDelegate.h"

#include "CloudBuilder.h"
#include "CClan.h"
#include "CUserManager.h"
#include "CLIMainViewController.h"

using namespace CloudBuilder;

@implementation CLIAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	return YES;
}
							

- (void)applicationDidEnterBackground:(UIApplication *)application
{
	// Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
	// If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
	// Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}


- (BOOL)application:(UIApplication *)application
			openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
		 annotation:(id)annotation {
	// attempt to extract a token from the url
	if (url)
	{
		[CLIMainViewController HandleURL:[url absoluteString] source:sourceApplication];
	}
	
	return false;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
	// Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
	// Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
		
	CClan::Instance()->Suspend();
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{	
	// Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.

	application.applicationIconBadgeNumber = 0;

	CClan::Instance()->Resume();
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	// Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
	CClan::Instance()->Terminate();
}

- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings
{
	NSLog(@"notificationSettings %@", notificationSettings);
}

// Retrieve the device token
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
	CloudBuilder::AchieveRegisterDevice(deviceToken.length, deviceToken.bytes);
}


// Provide a user explanation for when the registration fails
- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error 
{
	NSLog(@"didFailToRegisterForRemoteNotificationsWithError :%@", error);
}

// Handle an actual notification
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
	NSLog(@"remote event  = %@", userInfo);
	application.applicationIconBadgeNumber = 0;
}

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification
{
}

@end
