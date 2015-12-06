#ifndef __CNOTIFICATIONMANAGERRUNTIME__
#define __CNOTIFICATIONMANAGERRUNTIME__

#include "CCloudBuilderRuntime.h"

namespace CloudBuilderWP8_RT
{
	public delegate bool receivedMaintenanceNotificationDelegate(Platform::String^ aKind, Platform::String^ aJSONData);

	public delegate void didNotificationNotifyUserDelegate(eErrorCode aErrorCode, Platform::String^ aReference);

	public ref class CNotification sealed
    {
    public:
		static void SetReceivedMaintenanceNotificationCallback(receivedMaintenanceNotificationDelegate^ aCallback);

		static void popNextCallback(void);
		static eErrorCode NotifyUser(Platform::String^ aUserPseudo, Platform::String^ aJSONData, Platform::String^ aReference, Platform::String^ aJSONapnMessage, didNotificationNotifyUserDelegate^ aCallback);
    };
}
#endif	// __CNOTIFICATIONMANAGERRUNTIME__