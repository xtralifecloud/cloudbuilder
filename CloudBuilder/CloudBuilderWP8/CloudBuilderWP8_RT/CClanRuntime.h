#pragma once

#include "CCloudBuilderRuntime.h"

namespace CloudBuilderWP8_RT
{
	public delegate void didClanSetupDelegate(eErrorCode aErrorCode);
	public delegate void didClanBatchDelegate(eErrorCode aErrorCode, Platform::String^ aJSONResults);

	public ref class CClan sealed
    {
    public:
		static eErrorCode Setup(Platform::String^ aJSONConfig, didClanSetupDelegate^ aCallback);
		static eErrorCode Batch(Platform::String^ aMapMethod, Platform::String^ aOptions, didClanBatchDelegate^ aCallback);

		static void Suspend(void);
		static void Resume(void);
		static void Terminate(void);

		static bool isSetup(void);
		static bool isUserLogged(void);
    };
}