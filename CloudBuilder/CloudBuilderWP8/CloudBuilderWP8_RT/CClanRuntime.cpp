// CloudBuilderWP8_RT.cpp
#include "CClanRuntime.h"

#include <malloc.h>
#include <thread>
#include <chrono>

#include "RuntimeComponentHelper.h"
#include "WP8RuntimeComponentManagers.h"

using namespace Platform;
using namespace CotCHelpers;

CloudBuilderWP8_RT::didClanSetupDelegate^ gDidClanSetup;
CloudBuilderWP8_RT::didClanBatchDelegate^ gDidClanBatch;

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CClan::Setup(Platform::String^ aJSONConfig, didClanSetupDelegate^ aCallback)
{
	CHJSON*	config;
	int		result;
	char*	jsonStr;

	gRuntimeClan = new RuntimeClan;

	jsonStr			= CStringFromRuntime(aJSONConfig);
	config			= CHJSON::parse(jsonStr);
	gDidClanSetup	= aCallback;

	result = gRuntimeClan->Setup(config);
	delete config;
	free(jsonStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

CloudBuilderWP8_RT::eErrorCode CloudBuilderWP8_RT::CClan::Batch(Platform::String^ aMapMethod, Platform::String^ aOptions, didClanBatchDelegate^ aCallback)
{
	CHJSON*	mapMethod;
	CHJSON*	options;
	int		result;
	char*	mapMethodStr;
	char*	optionsStr;

	mapMethodStr	= CStringFromRuntime(aMapMethod);
	optionsStr		= CStringFromRuntime(aOptions);
	mapMethod		= CHJSON::parse(mapMethodStr);
	options			= CHJSON::parse(optionsStr);
	gDidClanBatch	= aCallback;

	result = gRuntimeClan->Batch(mapMethod, options);
	delete mapMethod;
	delete options;
	free(mapMethodStr);
	free(optionsStr);

	return (CloudBuilderWP8_RT::eErrorCode) result;
}

void CloudBuilderWP8_RT::CClan::Suspend(void)
{
	gRuntimeClan->Suspend();
}

void CloudBuilderWP8_RT::CClan::Resume(void)
{
	gRuntimeClan->Resume();
}

void CloudBuilderWP8_RT::CClan::Terminate(void)
{
	gRuntimeClan->Terminate();
}

bool CloudBuilderWP8_RT::CClan::isSetup(void)
{
	return gRuntimeClan->isSetup();
}

bool CloudBuilderWP8_RT::CClan::isUserLogged(void)
{
	return gRuntimeClan->isUserLogged();
}

int usleep(long usec) {
	std::chrono::milliseconds dura((usec/1000) ? (usec/1000) : 1);
	std::this_thread::sleep_for(dura)
	return 0;
}
