#pragma once

#include "main.h"
#include "MyCLI.h"

struct DialogHandler : public MyCLIResponder {
	DialogHandler(HWND hDlg);
	void onIdle();
	INT_PTR windowProc(UINT message, WPARAM wParam, LPARAM lParam);

	virtual void didFinishCommand();
	virtual void shouldPrintText(const char *message, CLI::typelog kind);

private:
	HWND hDlg;
	HWND executeButtonHwnd, consoleHwnd, commandHwnd;
	unique_ptr<MyCLI> cli;
	bool isWindowActive;

	void appendToConsole(const char *text, UINT color = 0xffc0c0c0);
	void appendToConsole(string text, UINT color = 0xffc0c0c0);
	void find_and_replace(string& source, const string &find, const string &replace);
	void runCommand(const char *command);
	void enableControls(bool whetherTo);
	string getCommandText();
	void setCommandText(const char *newText);
	void recallPreviousCommand();
	void recallNextCommand();

	struct CommandHandler: public ControlHandler {
		DialogHandler *dlgHandler;
		CommandHandler(DialogHandler *dlgHandler) : dlgHandler(dlgHandler) {}
		virtual INT_PTR windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
	struct ConsoleHandler: public ControlHandler {
		DialogHandler *dlgHandler;
		ConsoleHandler(DialogHandler *dlgHandler) : dlgHandler(dlgHandler) {}
		virtual INT_PTR windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
};
