#include "CUserManagerRuntime.h"

#include <malloc.h>

#include "CHJSON.h"

#include "RuntimeComponentHelper.h"
#include "WP8RuntimeComponentManagers.h"

using namespace Platform;

using namespace CotCHelpers;

CloudBuilderWP8_RT::receivedNotifyUserDelegate^ gReceivedNotifyUser = nullptr;

CloudBuilderWP8_RT::didUserRegisterAndLoginDelegate^ gDidUserRegisterAndLogin;
CloudBuilderWP8_RT::didUserLoginDelegate^ gDidUserLogin;
CloudBuilderWP8_RT::didUserLogoutDelegate^ gDidUserLogout;
CloudBuilderWP8_RT::didUserReadDelegate^ gDidUserRead;
CloudBuilderWP8_RT::didUserWriteDelegate^ gDidUserWrite;
CloudBuilderWP8_RT::didUserChangePasswordDelegate^ gDidUserChangePassword;
CloudBuilderWP8_RT::didUserMailPasswordDelegate^ gDidUserMailPassword;
CloudBuilderWP8_RT::didUserGetProfileDelegate^ gDidUserGetProfile;
CloudBuilderWP8_RT::didUserSetProfileDelegate^ gDidUserSetProfile;
CloudBuilderWP8_RT::didUserGetPropertiesDelegate^ gDidUserGetProperties;
CloudBuilderWP8_RT::didUserSetPropertiesDelegate^ gDidUserSetProperties;
CloudBuilderWP8_RT::didUserCheckUserDelegate^ gDidUserCheckUser;

void CloudBuilderWP8_RT::CUser::SetReceivedNotifyUserCallback(receivedNotifyUserDelegate^ aCallback)
{
	gReceivedNotifyUser = aCallback;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::RegisterAndLogin(Platform::String^ aEmail, Platform::String^ aPassword, Platform::String^ aPseudo, didUserRegisterAndLoginDelegate^ aCallback)
{
	int		result;
	char*	emailStr;
	char*	passowrdStr;
	char*	pseudoStr;

	emailStr	= CStringFromRuntime(aEmail);
	passowrdStr	= CStringFromRuntime(aPassword);
	pseudoStr	= CStringFromRuntime(aPseudo);

	gDidUserRegisterAndLogin	= aCallback;

	result = gRuntimeClan->runtimeLogin->RegisterAndLogin(emailStr, passowrdStr, pseudoStr);
	free(emailStr);
	free(passowrdStr);
	free(pseudoStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::Login(Platform::String^ aPseudo, Platform::String^ aPassword, didUserLoginDelegate^ aCallback)
{
	int		result;
	char*	passowrdStr;
	char*	pseudoStr;

	passowrdStr	= CStringFromRuntime(aPassword);
	pseudoStr	= CStringFromRuntime(aPseudo);

	gDidUserLogin	= aCallback;

	result = gRuntimeClan->runtimeLogin->Login(pseudoStr, passowrdStr);
	free(passowrdStr);
	free(pseudoStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::Logout(didUserLogoutDelegate^ aCallback)
{
	gDidUserLogout = aCallback;

	return (CloudBuilderWP8_RT::eErrorCode) gRuntimeClan->runtimeLogin->Logout();
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::Read(Platform::String^ aKey, didUserReadDelegate^ aCallback)
{
	int		result;
	char*	keyStr;

	keyStr	= CStringFromRuntime(aKey);

	gDidUserRead	= aCallback;

	result = gRuntimeClan->runtimeLogin->Read(keyStr);
	free(keyStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::Write(Platform::String^ aKey, Platform::String^ aValue, didUserWriteDelegate^ aCallback)
{
	int		result;
	char*	keyStr;
	char*	valueStr;

	keyStr		= CStringFromRuntime(aKey);
	valueStr	= CStringFromRuntime(aValue);

	gDidUserWrite	= aCallback;

	result = gRuntimeClan->runtimeLogin->Write(keyStr, valueStr);
	free(keyStr);
	free(valueStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::ChangePassword(Platform::String^ aOldPassword, Platform::String^ aNewPassword, didUserChangePasswordDelegate^ aCallback)
{
	int		result;
	char*	oldPasswordStr;
	char*	newPasswordStr;

	oldPasswordStr	= CStringFromRuntime(aOldPassword);
	newPasswordStr	= CStringFromRuntime(aNewPassword);

	gDidUserChangePassword	= aCallback;

	result = gRuntimeClan->runtimeLogin->ChangePassword(oldPasswordStr, newPasswordStr);
	free(oldPasswordStr);
	free(newPasswordStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::MailPassword(Platform::String^ aEmail, Platform::String^ aSubject, Platform::String^ aBody, didUserMailPasswordDelegate^ aCallback)
{
	int		result;
	char*	emailStr;
	char*	subjectStr;
	char*	bodyStr;

	emailStr	= CStringFromRuntime(aEmail);
	subjectStr	= CStringFromRuntime(aSubject);
	bodyStr		= CStringFromRuntime(aBody);

	gDidUserMailPassword	= aCallback;

	result = gRuntimeClan->runtimeLogin->MailPassword(emailStr, subjectStr, bodyStr);
	free(emailStr);
	free(subjectStr);
	free(bodyStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::GetProfile(didUserGetProfileDelegate^ aCallback)
{
	gDidUserGetProfile = aCallback;

	return (CloudBuilderWP8_RT::eErrorCode) gRuntimeClan->runtimeLogin->GetUserProfile();
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::SetProfile(Platform::String^ aProfileJson, didUserSetProfileDelegate^ aCallback)
{
	int		result;
	char*	profileStr;
	CHJSON*	json;

	profileStr	= CStringFromRuntime(aProfileJson);
	json		= CHJSON::parse(profileStr);

	gDidUserSetProfile	= aCallback;

	result = gRuntimeClan->runtimeLogin->SetUserProfile(json);
	free(profileStr);
	delete json;

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::GetProperties(didUserGetPropertiesDelegate^ aCallback)
{
	gDidUserGetProperties = aCallback;

	return (CloudBuilderWP8_RT::eErrorCode) gRuntimeClan->runtimeLogin->GetProperties();
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::SetProperties(bool aCanBeFound, Platform::String^ aPropertiesJson, didUserSetPropertiesDelegate^ aCallback)
{
	int		result;
	char*	propertiesStr;
	CHJSON*	json;

	propertiesStr	= CStringFromRuntime(aPropertiesJson);
	json			= CHJSON::parse(propertiesStr);

	gDidUserSetProperties	= aCallback;

	result = gRuntimeClan->runtimeLogin->SetProperties(aCanBeFound, json);
	free(propertiesStr);
	delete json;

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CUser::CheckUser(Platform::String^ aIdent, didUserCheckUserDelegate^ aCallback)
{
	int		result;
	char*	identStr;

	identStr	= CStringFromRuntime(aIdent);

	gDidUserCheckUser	= aCallback;

	result = gRuntimeClan->runtimeLogin->CheckUser(identStr);
	free(identStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

Platform::String^ CloudBuilderWP8_RT::CUser::GetPseudo(void)
{
	return RuntimeStringFromC(gRuntimeClan->runtimeLogin->GetPseudo());
}

Platform::String^ CloudBuilderWP8_RT::CUser::GetMail(void)
{
	return RuntimeStringFromC(gRuntimeClan->runtimeLogin->GetMail());
}
