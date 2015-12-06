#include "precompiled.h"
#include "CliForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace CLIApp;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
#ifdef USE_CONSOLE_DEBUG
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	Application::Run(gcnew CliForm());

#ifdef USE_CONSOLE_DEBUG
	FreeConsole();
#endif
	return 0;
}
