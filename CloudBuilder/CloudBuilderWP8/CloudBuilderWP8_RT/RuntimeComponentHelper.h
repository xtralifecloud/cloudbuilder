#ifndef __RUNTIMECOMPONENTHELPER__
#define __RUNTIMECOMPONENTHELPER__

char* CStringFromRuntime(Platform::String^ aString);
Platform::String^ RuntimeStringFromC(const char* aString);

#endif	// __RUNTIMECOMPONENTHELPER__