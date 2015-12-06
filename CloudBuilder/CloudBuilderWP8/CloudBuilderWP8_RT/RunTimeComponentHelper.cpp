#include "RuntimeComponentHelper.h"

#include <string>
#include <vector>

#include "utf8.h"

char* CStringFromRuntime(Platform::String^ aString)
{
	char*	cstring;
	long	cstringSize;

	std::wstring stdStr = aString->Data();
	std::vector<unsigned char> utf8result;
	utf8::utf16to8(stdStr.c_str(), stdStr.c_str() + stdStr.length(), back_inserter(utf8result));

	cstringSize = utf8result.size();
	cstring = (char *) malloc(cstringSize + 1);
	memcpy(cstring, &utf8result[0], cstringSize);
	cstring[cstringSize] = 0;

	return cstring;
}

Platform::String^ RuntimeStringFromC(const char* aString)
{
	Platform::String^ runtimeString;
	
	std::vector<wchar_t> utf16result;
	utf8::utf8to16(aString, aString + strlen(aString), back_inserter(utf16result));
	utf16result.push_back(0);

	return ref new Platform::String(&utf16result[0]);
}