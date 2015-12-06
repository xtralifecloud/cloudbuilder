#pragma once

#include "CCloudBuilderRuntime.h"

namespace CloudBuilderWP8_RT
{
	public delegate bool receivedNotifyUserDelegate(Platform::String^ aFromUserID, Platform::String^ aJSONData);

	public delegate void didUserRegisterAndLoginDelegate(eErrorCode aErrorCode);
	public delegate void didUserLoginDelegate(eErrorCode aErrorCode, Platform::String^ aJsonProfile);
	public delegate void didUserLogoutDelegate(eErrorCode aErrorCode);
	public delegate void didUserReadDelegate(eErrorCode aErrorCode, Platform::String^ aKey, Platform::String^ aValue);
	public delegate void didUserWriteDelegate(eErrorCode aErrorCode, Platform::String^ aKey);
	public delegate void didUserChangePasswordDelegate(eErrorCode aErrorCode);
	public delegate void didUserMailPasswordDelegate(eErrorCode aErrorCode);
	public delegate void didUserGetProfileDelegate(eErrorCode aErrorCode, Platform::String^ aJsonProfile);
	public delegate void didUserSetProfileDelegate(eErrorCode aErrorCode);
	public delegate void didUserGetPropertiesDelegate(eErrorCode aErrorCode, bool aCanBeFound, Platform::String^ aJsonProperties);
	public delegate void didUserSetPropertiesDelegate(eErrorCode aErrorCode);
	public delegate void didUserCheckUserDelegate(eErrorCode aErrorCode, bool aExists);

	public ref class CUser sealed
    {
    public:
		static void SetReceivedNotifyUserCallback(receivedNotifyUserDelegate^ aCallback);

		static eErrorCode RegisterAndLogin(Platform::String^ aEmail, Platform::String^ aPassword, Platform::String^ aPseudo, didUserRegisterAndLoginDelegate^ aCallback);
		static eErrorCode Login(Platform::String^ aPseudo, Platform::String^ aPassword, didUserLoginDelegate^ aCallback);
		static eErrorCode Logout(didUserLogoutDelegate^ aCallback);
		static eErrorCode Read(Platform::String^ aKey, didUserReadDelegate^ aCallback);
		static eErrorCode Write(Platform::String^ aKey, Platform::String^ aValue, didUserWriteDelegate^ aCallback);
		static eErrorCode ChangePassword(Platform::String^ aOldPassword, Platform::String^ aNewPassword, didUserChangePasswordDelegate^ aCallback);
		static eErrorCode MailPassword(Platform::String^ aEmail, Platform::String^ aSubject, Platform::String^ aBody, didUserMailPasswordDelegate^ aCallback);
		static eErrorCode GetProfile(didUserGetProfileDelegate^ aCallback);
		static eErrorCode SetProfile(Platform::String^ aProfileJson, didUserSetProfileDelegate^ aCallback);
		static eErrorCode GetProperties(didUserGetPropertiesDelegate^ aCallback);
		static eErrorCode SetProperties(bool aCanBeFound, Platform::String^ aPropertiesJson, didUserSetPropertiesDelegate^ aCallback);
		static eErrorCode CheckUser(Platform::String^ aIdent, didUserCheckUserDelegate^ aCallback);
		static Platform::String^ GetPseudo(void);
		static Platform::String^ GetMail(void);
    };
}