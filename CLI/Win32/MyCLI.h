#pragma once

#include "cli.h"

// Interface for responding to CLI events
struct MyCLIResponder {
	virtual void didFinishCommand() = 0;
	virtual void shouldPrintText(const char *message, CLI::typelog kind) = 0;
};

class MyCLI : public CLI
{
	MyCLIResponder *mResponder;
	vector<string> history;
	unsigned currentHistoryIndex;

public:
	MyCLI(MyCLIResponder *responder);

	// Please use this instead of execute, allows for history functionality
	eErrorCode executeCommand(const char *command, bool pushInHistory = true);
	const char *recallPreviousCommand();
	const char *recallNextCommand();

	virtual void logger(const char *message, typelog kind);
	virtual void stopActivity(eErrorCode ec);
	virtual void getBasePath(char *path);
};
