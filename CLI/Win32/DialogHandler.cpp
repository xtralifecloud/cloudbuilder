#include "stdafx.h"
#include "DialogHandler.h"

#define Lime RGB(128, 255, 0)
#define LightGray RGB(224, 224, 224)
#define ErrorRed RGB(255, 128, 128)
#define DoneText RGB(192, 192, 96)

DialogHandler::DialogHandler(HWND hDlg) : hDlg(hDlg), isWindowActive(true) {
	cli = make_unique(new MyCLI(this));
}

void DialogHandler::onIdle() {
	cli->idle();
}

INT_PTR DialogHandler::windowProc(UINT message, WPARAM wParam, LPARAM lParam) {
	int wmId, wmEvent, width, height;
	HFONT hFont;

	switch (message) {
	case WM_INITDIALOG:
		SETTEXTEX ste;
		ste.flags = ST_NEWCHARS;
		ste.codepage = 1200;

		consoleHwnd = GetDlgItem(hDlg, IDC_CONSOLE);
		commandHwnd = GetDlgItem(hDlg, IDC_COMMAND);
		executeButtonHwnd = GetDlgItem(hDlg, IDOK);
		setHandlerForControl(commandHwnd, make_shared(new CommandHandler(this)));
		setHandlerForControl(consoleHwnd, make_shared(new ConsoleHandler(this)));
		SendMessage(consoleHwnd, EM_SETTEXTEX, (WPARAM) &ste, (LPARAM) "{\\rtf1\\deff0{\\fonttbl{\\f0\\fcharset0 Consolas;}}"
			"{\\colortbl ;\\red224\\green224\\blue224;}\\fs18\\cf1\\f0 Welcome! Type help [RETURN] to list available commands.}");
		SendMessage(consoleHwnd, EM_SETBKGNDCOLOR, 0, RGB(0, 0, 0));
		appendToConsole("\n");
		// Set the font of the command window
		hFont = CreateFont(14, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Consolas"));
		SendMessage(commandHwnd, WM_SETFONT, (WPARAM) hFont, MAKELPARAM(FALSE, 0));

		// Issue a first command
		shouldPrintText("Type cmd <number> to execute one of these commands:", CLI::kLOG);
		cli->executeCommand("cmd", false);
		return (INT_PTR) TRUE;

	case WM_ACTIVATE: {
		bool active = wParam != 0;
		g_hDlgCurrent = wParam? hDlg : NULL;
		// Notify suspend/resume events
		if (active != isWindowActive) {
			active ? CClan::Instance()->Resume() : CClan::Instance()->Suspend();
			isWindowActive = active;
		}
		break;
	}

	case WM_SIZE:
		width = LOWORD(lParam), height = HIWORD(lParam);
		MoveWindow(commandHwnd, 5, height - 26, width - 95, 23, TRUE);
		MoveWindow(consoleHwnd, 0, 0, width, height - 29, TRUE);
		MoveWindow(executeButtonHwnd, width - 87, height - 27, 83, 25, TRUE);
		break;

	case WM_COMMAND:
		wmId	= LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId) {
		case IDOK:
			runCommand(getCommandText().c_str());
			return (INT_PTR) true;

		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			PostQuitMessage(0);
			return (INT_PTR) TRUE;
		}
		break;
	}
	return (INT_PTR) FALSE;
}

//////////////// MyCLIResponder ////////////////
void DialogHandler::didFinishCommand() {
	long time = cli->millisecondsElapsedSinceLastExecute();
	char timeStr[128];
	appendToConsole("Done!	", LightGray);
	// Display the time in the t.ttt format
	sprintf_s(timeStr, "(%d.%03d sec)\n", time / 1000, time % 1000);
	appendToConsole(timeStr, DoneText);
	enableControls(true);
}

void DialogHandler::shouldPrintText(const char *message, CLI::typelog kind) {
	string result(message);
	UINT col;
	find_and_replace(result, "\r", "\n");

	switch (kind) {
	case CLI::kLOG: col = LightGray; break;
	case CLI::kCMD: col = LightGray; break;
	case CLI::kERR: col = ErrorRed; break;
	case CLI::kSCRIPT: col = LightGray; break;
	default: col = RGB(255, 255, 0); break;
	}

	appendToConsole(result + "\n", col);
	enableControls(true);
}

//////////////// Private ////////////////
void DialogHandler::appendToConsole(const char *text, UINT color) {
	CHARRANGE cr;
	SETTEXTEX ste;
	char colortbl[128];
	sprintf_s(colortbl, "{\\colortbl ;\\red%d\\green%d\\blue%d;}", color & 0xff, color >> 8 & 0xff, color >> 16 & 0xff);
	string rtf = "{\\rtf1" + string(colortbl) + "\\fs18\\cf1\\f0" + string(text) + "}";
	find_and_replace(rtf, "\n", "\\par");

	cr.cpMin = -1;
	cr.cpMax = -1;
	ste.flags = ST_SELECTION;
	ste.codepage = 1200;

	// hwnd = rich edit hwnd
	SendMessage(consoleHwnd, EM_EXSETSEL, 0, (LPARAM)&cr);
	SendMessage(consoleHwnd, EM_SETTEXTEX, (WPARAM) &ste, (LPARAM) rtf.c_str());

	// Scroll to bottom
	SendMessage(consoleHwnd, EM_EXSETSEL, 0, (LPARAM)&cr);
	SendMessage(consoleHwnd, WM_VSCROLL, SB_BOTTOM, 0);
}

void DialogHandler::appendToConsole(string text, UINT color) {
	appendToConsole(text.c_str(), color);
}

void DialogHandler::find_and_replace(string& source, const string &find, const string &replace) {
	for (unsigned i = 0; (i = source.find(find, i)) != std::string::npos; ) {
		source.replace(i, find.length(), replace);
		i += replace.length() - find.length() + 1;
	}
}

void DialogHandler::runCommand(const char *command) {
	// Special commands
	if (!strcmp(command, "loginflo")) {
		command = "resumesession 54213d261cfd7f984741fa08 b8b22f0d7fae33b91b85928e40e614858096bbeb";
	}

	// Print the command
	appendToConsole("-> " + string(command) + "\n", Lime);
	setCommandText("");
	enableControls(false);
	// Execute it
	CloudBuilder::eErrorCode ec = cli->executeCommand(command);
	if (ec != enNoErr) {
		if (ec != -1)
			shouldPrintText(errorString(ec), CLI::kERR);
		enableControls(true);
	}
}


void DialogHandler::enableControls(bool whetherTo) {
	EnableWindow(commandHwnd, whetherTo);
	EnableWindow(executeButtonHwnd, whetherTo);
	// While grayed out, focus the console, else re-focus the command box
	SetFocus(whetherTo ? commandHwnd : consoleHwnd);
}

string DialogHandler::getCommandText() {
	char chars[1024];
	GetWindowTextA(commandHwnd, chars, numberof(chars));
	return string(chars);
}

void DialogHandler::setCommandText(const char *newText) {
	SetWindowTextA(commandHwnd, newText);
}

void DialogHandler::recallPreviousCommand() {
	const char *cmd = cli->recallPreviousCommand();
	int len = strlen(cmd);
	setCommandText(cmd);
	// Move caret to the end
	SendMessage(commandHwnd, EM_SETSEL, len, len);
}

void DialogHandler::recallNextCommand() {
	const char *cmd = cli->recallNextCommand();
	int len = strlen(cmd);
	setCommandText(cmd);
	// Move caret to the end
	SendMessage(commandHwnd, EM_SETSEL, len, len);
}

INT_PTR DialogHandler::CommandHandler::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if ((message == WM_CHAR) && (wParam == 'R')) {
		PostQuitMessage(0);
		return 0;
	} else if (message == WM_KEYDOWN) {
		if (wParam == VK_UP) {
			dlgHandler->recallPreviousCommand();
			return 1;
		} else if (wParam == VK_DOWN) {
			dlgHandler->recallNextCommand();
			return 1;
		}
	}
	return CallWindowProc(previousProc, hWnd, message, wParam, lParam);
}

INT_PTR DialogHandler::ConsoleHandler::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// Focus the command when something is written in the console
	if (message == WM_CHAR) {
		SetFocus(dlgHandler->commandHwnd);
	}
	return CallWindowProc(previousProc, hWnd, message, wParam, lParam);
}
