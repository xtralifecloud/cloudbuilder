#include "precompiled.h"
#include "mycli.h"

MyCLI::MyCLI(MyCLIResponder ^responder)
	: CLI(), mResponder(responder), currentHistoryIndex(0)
{
}

eErrorCode MyCLI::executeCommand(const char *command) {
	// Remove discarded next commands
//	history.erase(history.begin() + currentHistoryIndex, history.end());
	// Store the command
	history.push_back(command);
	currentHistoryIndex = history.size();
	// And execute it
	return execute(command);
}

void MyCLI::logger(const char *message, typelog kind) {
	mResponder->shouldPrintText(message, kind);
}

void MyCLI::stopActivity(eErrorCode ec) {
	if (ec)
		this->logger(errorString(ec), kERR);
	else
		mResponder->didFinishCommand();
}

const char *MyCLI::recallPreviousCommand() {
	if (currentHistoryIndex > 0) {
		currentHistoryIndex--;
	}
	if (history.empty()) {
		return NULL;
	}
	return history[currentHistoryIndex].c_str();
}

const char *MyCLI::recallNextCommand() {
	// Would go past the end?
	if (currentHistoryIndex + 1 >= history.size()) {
		currentHistoryIndex = history.size();
		return NULL;
	} else {
		return history[++currentHistoryIndex].c_str();
	}
}
