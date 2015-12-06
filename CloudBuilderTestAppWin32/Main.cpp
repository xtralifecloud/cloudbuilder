#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "MainForm.h"
#include "CloudBuilderUtils.h"
#include "CGameManager.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace CloudBuilderTestAppWin32;

[STAThreadAttribute]
int main(array<String ^> ^args) {
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CHJSON config;
	config.Put("key", "testgame-key");
	config.Put("secret", "testgame-secret");
	config.Put("env", "sandbox");
	config.Put("httpVerbose", true);
	CClan::Instance()->SetLogLevel(LOG_LEVEL_VERBOSE);
	CClan::Instance()->Setup(&config, MakeResultHandler([] (eErrorCode code, const CCloudResult *result) {
		
		CHJSON keyConfig;
		keyConfig.Put("key", "testkey");
		CGameManager::Instance()->KeyValueRead(&keyConfig, MakeResultHandler([] (eErrorCode code, const CCloudResult *result) {
			printf("Got testkey: %s\n", result->Print());

			CHJSON keyConfig;
			keyConfig.Put("key", "stringkey");
			CGameManager::Instance()->KeyValueRead(&keyConfig, MakeResultHandler([] (eErrorCode code, const CCloudResult *result) {
				printf("Got stringkey: %s\n", result->Print());
			}));
		}));
	}));

	Application::Run(gcnew MainForm());

	FreeConsole();
	return 0;
}
