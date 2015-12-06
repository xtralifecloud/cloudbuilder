#include "CNotificationManagerRuntime.h"

#include <malloc.h>

#include "CNotificationManager.h"
#include "RuntimeComponentHelper.h"

using namespace CotCHelpers;

CloudBuilderWP8_RT::receivedMaintenanceNotificationDelegate^ gReceivedMaintenanceNotification = nullptr;

CloudBuilderWP8_RT::didNotificationNotifyUserDelegate^ gDidNotificationNotifyUser;
	
void CloudBuilderWP8_RT::CNotification::SetReceivedMaintenanceNotificationCallback(receivedMaintenanceNotificationDelegate^ aCallback)
{
	gReceivedMaintenanceNotification = aCallback;
}

void CloudBuilderWP8_RT::CNotification::popNextCallback(void)
{
	CloudBuilder::CNotificationManager::popNextCallback();
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CNotification::NotifyUser(Platform::String^ aUserPseudo, Platform::String^ aJSONData, Platform::String^ aReference, Platform::String^ aJSONapnMessage, didNotificationNotifyUserDelegate^ aCallback)
{
	int		result;
	char*	userPseudoStr;
	char*	jsonDataStr;
	char*	referenceStr;
	char*	apnMessageStr;
	CHJSON*	json1;
	CHJSON*	json2;

	userPseudoStr				= CStringFromRuntime(aUserPseudo);
	jsonDataStr					= CStringFromRuntime(aJSONData);
	referenceStr				= CStringFromRuntime(aJSONData);
	apnMessageStr				= CStringFromRuntime(aJSONapnMessage);
	json1						= CHJSON::parse(jsonDataStr);
	json2						= CHJSON::parse(apnMessageStr);
	gDidNotificationNotifyUser	= aCallback;

	result = CloudBuilder::CNotificationManager::Instance()->NotifyUser(userPseudoStr, json1, referenceStr, json2);
	free(userPseudoStr);
	free(jsonDataStr);
	free(referenceStr);
	free(apnMessageStr);
	delete json1;
	delete json2;

	return (CloudBuilderWP8_RT::eErrorCode) result;
}
