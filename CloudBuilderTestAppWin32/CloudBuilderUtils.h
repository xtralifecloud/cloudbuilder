#pragma once

#include <functional>
#include "CClan.h"

using namespace CloudBuilder;

typedef std::function<void(eErrorCode, const CCloudResult*)> resultHandler_t;

static CResultHandler *MakeResultHandler(resultHandler_t func) {
	struct FunctionalResultHandler: CResultHandler {
		resultHandler_t func;
		FunctionalResultHandler(resultHandler_t func) : func(func), CResultHandler(this, &FunctionalResultHandler::Done) {}
		void Done(eErrorCode code, const CCloudResult *result) {
			func(code, result);
		}
	};
	return new FunctionalResultHandler(func);
}
