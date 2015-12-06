//
//  performOnMain.mm
//  CloudBuilder
//
//  Created by Roland Van Leeuwen on 27/09/11.
//  Copyright 2011 Clan of the Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#include "CloudBuilder.h"
#include "CCallback.h"
#include "CHJSON.h"
#include "cotc_thread.h"
#include "CClan.h"
#include "CClannishRESTProxy.h"
#include "RegisterDevice.h"

#include "CloudBuilder_private.h"
//#include "AndroidGooglePlusHandler.h"

#include <sys/socket.h> // Per msqr
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>

using namespace CotCHelpers;
using namespace CloudBuilder;

UIBackgroundTaskIdentifier bgTask = UIBackgroundTaskInvalid;

namespace CloudBuilder {

static char *macaddress(char *uuid)
{
	int				 mib[6];
	size_t			  len;
	char				*buf;
	unsigned char	   *ptr;
	struct if_msghdr	*ifm;
	struct sockaddr_dl  *sdl;
	
	mib[0] = CTL_NET;
	mib[1] = AF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_LINK;
	mib[4] = NET_RT_IFLIST;
	
	if ((mib[5] = if_nametoindex("en0")) == 0) {
		printf("Error: if_nametoindex error\n");
		return NULL;
	}
	
	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
		printf("Error: sysctl, take 1\n");
		return NULL;
	}
	
	if ((buf = (char*)malloc(len)) == NULL) {
		printf("Could not allocate memory. error!\n");
		return NULL;
	}
	
	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
		printf("Error: sysctl, take 2");
		free(buf);
		return NULL;
	}
	
	ifm = (struct if_msghdr *)buf;
	sdl = (struct sockaddr_dl *)(ifm + 1);
	ptr = (unsigned char *)LLADDR(sdl);
	sprintf(uuid, "%02X:%02X:%02X:%02X:%02X:%02X", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5));
	free(buf);
	
	return uuid;
}

void AchieveRegisterDevice(unsigned long len, const void *bytes)
{
	NSData *deviceToken = [NSData dataWithBytes:bytes length:len];
	NSString *tokenString = [NSString stringWithFormat:@"%@", deviceToken];
	tokenString = [tokenString stringByReplacingOccurrencesOfString:@"<" withString:@""];
	tokenString = [tokenString stringByReplacingOccurrencesOfString:@">" withString:@""];
	tokenString = [tokenString stringByReplacingOccurrencesOfString:@" " withString:@""];

	CUserManager::Instance()->RegisterDevice("ios", [tokenString UTF8String]);
}

}

void RegisterDevice(void)
 {
	 if ([[UIApplication sharedApplication] respondsToSelector:@selector(registerUserNotificationSettings:)]){
		 [[UIApplication sharedApplication] registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:(UIUserNotificationTypeSound | UIUserNotificationTypeAlert | UIUserNotificationTypeBadge) categories:nil]];
		 [[UIApplication sharedApplication] registerForRemoteNotifications];
	 }
	 else{
		 [[UIApplication sharedApplication] registerForRemoteNotificationTypes:
		  (UIUserNotificationTypeBadge | UIUserNotificationTypeSound | UIUserNotificationTypeAlert)];
	 }
 }

void UnregisterDevice(void)
{
	[[UIApplication sharedApplication] unregisterForRemoteNotifications];
}


CotCHelpers::CHJSON *collectDeviceInformation() {

	CotCHelpers::CHJSON *j = new CotCHelpers::CHJSON();
	
	UIDevice *d = [UIDevice currentDevice];
	size_t size;

	sysctlbyname("hw.machine", NULL, &size, NULL, 0);
	char *machine = new char[size];
	sysctlbyname("hw.machine", machine, &size, NULL, 0);

	j->Put("id", [[d.identifierForVendor UUIDString] UTF8String]);
	j->Put("osname", [d.systemName UTF8String]);
	j->Put("osversion", [d.systemVersion UTF8String]);
	j->Put("name", [d.name UTF8String]);
	j->Put("model", machine);
	j->Put("version", "1");
	
	delete [] machine;

	return j;
}
