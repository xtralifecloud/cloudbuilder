#include "stdafx.h"
#include "MyCLI.h"

MyCLI::MyCLI(MyCLIResponder *responder) : CLI(), mResponder(responder), currentHistoryIndex(0) {
	const char **favorites;
	int count;
	CLI::getFavorites(favorites, count);
	// Add favorites first
	for (int i = 0; i < count; i++) {
		history.push_back(favorites[i]);
	}
}

eErrorCode MyCLI::executeCommand(const char *command, bool pushInHistory) {
	// Remove discarded next commands
//	history.erase(history.begin() + currentHistoryIndex, history.end());
	// Store the command
	if (pushInHistory) {
		history.push_back(command);
	}
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
		return "";
	}
	return history[currentHistoryIndex].c_str();
}

const char *MyCLI::recallNextCommand() {
	// Would go past the end?
	if (currentHistoryIndex + 1 >= history.size()) {
		currentHistoryIndex = history.size();
		return "";
	} else {
		return history[++currentHistoryIndex].c_str();
	}
}

void MyCLI::getBasePath(char *path) {
	strcpy(path, "../scripts/");
}
