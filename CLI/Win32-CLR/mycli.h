#ifndef MYCLI_H
#define MYCLI_H

#include "cli.h"
#include <gcroot.h>

// Interface for responding to CLI events
public interface class MyCLIResponder {
	void didFinishCommand();
	void shouldPrintText(const char *message, CLI::typelog kind);
};

class MyCLI : public CLI
{
	gcroot<MyCLIResponder^> mResponder;
	vector<string> history;
	unsigned currentHistoryIndex;

public:
	MyCLI(MyCLIResponder ^responder);

	// Please use this instead of execute, allows for history functionality
	eErrorCode executeCommand(const char *command);
	const char *recallPreviousCommand();
	const char *recallNextCommand();

	virtual void logger(const char *message, typelog kind);
	virtual void stopActivity(eErrorCode ec);
};

#endif // MYCLI_H
