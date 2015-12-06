/*
	 File: AppDelegate.m 
 Abstract: The application's delegate for managing its windows.
  
  Version: 1.0 
  
 Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple 
 Inc. ("Apple") in consideration of your agreement to the following 
 terms, and your use, installation, modification or redistribution of 
 this Apple software constitutes acceptance of these terms.  If you do 
 not agree with these terms, please do not use, install, modify or 
 redistribute this Apple software. 
  
 In consideration of your agreement to abide by the following terms, and 
 subject to these terms, Apple grants you a personal, non-exclusive 
 license, under Apple's copyrights in this original Apple software (the 
 "Apple Software"), to use, reproduce, modify and redistribute the Apple 
 Software, with or without modifications, in source and/or binary forms; 
 provided that if you redistribute the Apple Software in its entirety and 
 without modifications, you must retain this notice and the following 
 text and disclaimers in all such redistributions of the Apple Software. 
 Neither the name, trademarks, service marks or logos of Apple Inc. may 
 be used to endorse or promote products derived from the Apple Software 
 without specific prior written permission from Apple.  Except as 
 expressly stated in this notice, no other rights or licenses, express or 
 implied, are granted by Apple herein, including but not limited to any 
 patent rights that may be infringed by your derivative works or by other 
 works in which the Apple Software may be incorporated. 
  
 The Apple Software is provided by Apple on an "AS IS" basis.  APPLE 
 MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION 
 THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS 
 FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND 
 OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS. 
  
 IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL 
 OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, 
 MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED 
 AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), 
 STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE 
 POSSIBILITY OF SUCH DAMAGE. 
  
 Copyright (C) 2011 Apple Inc. All Rights Reserved. 
  
 */

#import "AppDelegate.h"
#import "MailWindowController.h"
#import "CollapseWindowController.h"
#import "MailWindowController.h"

#include "CClan.h"

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{

  
	[[NSAppleEventManager sharedAppleEventManager] setEventHandler:self andSelector:@selector(getUrl:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
	
	
	NSLog(@"initialized");

	[self doMailStyleSplit:self];
	
}

- (void) getUrl:(NSAppleEventDescriptor *)event withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
	NSString *url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
	NSLog(@"url :%@", url);
	
	NSRange r = [url rangeOfString:@"://cotc/"];

	if (r.location != NSNotFound && gMain && [gMain GetCLI]) {
		CHJSON j;
		j.Put("url", [url UTF8String]);
		[gMain GetCLI]->HandleURL(&j);
	}
	
}

- (void)application:(NSApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
	NSLog(@"%@ with token = %@", NSStringFromSelector(_cmd), deviceToken);
	
	// Send the device token to the provider so it knows the app is ready to receive notifications.
	CloudBuilder::AchieveRegisterDevice(deviceToken.length, deviceToken.bytes);
}


- (void)application:(NSApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
	NSLog(@"%@ with error = %@", NSStringFromSelector(_cmd), error);
}


- (void)application:(NSApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
	NSLog(@"%@ : \n %@", NSStringFromSelector(_cmd), userInfo);
	
	NSDictionary *apsDictionary = [userInfo valueForKey:@"aps"];
	
	if (apsDictionary != nil) {
	}
}

- (void)applicationWillResignActive:(NSApplication *)application
{
	// Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
	// Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
		
	if (gMain && [gMain GetCLI] && [gMain GetCLI]->GetClan())
		[gMain GetCLI]->GetClan()->Suspend();
}

- (void)applicationDidEnterBackground:(NSApplication *)application
{
	// Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
	// If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(NSApplication *)application
{
	// Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(NSApplication *)application
{	
	// Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.

	if (gMain && [gMain GetCLI] && [gMain GetCLI]->GetClan())
		[gMain GetCLI]->GetClan()->Resume();
}

- (void)applicationWillTerminate:(NSApplication *)application
{
	// Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
	if (gMain && [gMain GetCLI] && [gMain GetCLI]->GetClan())
		[gMain GetCLI]->GetClan()->Terminate();
}


// -------------------------------------------------------------------------------
//	dealloc
// -------------------------------------------------------------------------------
- (void)dealloc
{
	[super dealloc];
}

// -------------------------------------------------------------------------------
//	openReadMe:sender
// -------------------------------------------------------------------------------
- (IBAction)openReadMe:(id)sender
{
	NSString* fullPath = [[NSBundle mainBundle] pathForResource:@"ReadMe" ofType:@"md"];
	[[NSWorkspace sharedWorkspace] openFile:fullPath];
}

// -------------------------------------------------------------------------------
//	doMailStyleSplit:sender
// -------------------------------------------------------------------------------
- (IBAction)doMailStyleSplit:(id)sender
{
	MailWindowController *ctrl = [[MailWindowController alloc] initWithWindowNibName:@"MailSplit"];
	[ctrl showWindow:self];
}

@end
