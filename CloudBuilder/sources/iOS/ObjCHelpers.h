#pragma once

// TODO Florian -- create an equivalent .mm file and declare prototypes here for better reusability
namespace CloudBuilder {
	static CInternalResultHandler *BlockResultHandler(void (^block)(const CCloudResult *result)) {
		struct Handler: CInternalResultHandler {
			void (^block)(const CCloudResult *result);
			Handler(void (^block)(const CCloudResult *result)) : block(block), CInternalResultHandler(this, &Handler::Done) {}
			void Done(const CCloudResult *result) {
				block(result);
			}
		};
		return new Handler(block);
	}

	static void InvokeHandlerOnMainThread(CInternalResultHandler *handler, const CCloudResult *result) {
		CCloudResult *copy = result->Duplicate();
		dispatch_async(dispatch_get_main_queue(), ^{
			InvokeHandler(handler, copy);
			delete copy;
		});
	}
	
	static void InvokeHandlerOnMainThread(CInternalResultHandler *handler, eErrorCode code, const char *description = NULL) {
		char *copy = description? strdup(description) : NULL;
		dispatch_async(dispatch_get_main_queue(), ^{
			InvokeHandler(handler, code, copy);
			if (copy) { free(copy); }
		});
	}
}
