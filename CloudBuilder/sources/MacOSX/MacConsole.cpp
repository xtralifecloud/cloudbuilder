//
//  MacConsole.cpp
//  CloudBuilderMacOSX
//
//  Created by roland on 11/09/2014.
//
//

#include <stdio.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#include "CSocialFB.h"
#include "GameCenterHandler.h"

#include "optional/CStdioBasedFileImpl.h"
#include "helpers.h"
#include "CloudBuilder_private.h"

using namespace CloudBuilder;

extern char *CFilesystem_appFolder;

bool CFilesystemHandler::Delete(const char *relativePath) {
	return false;
}

CInputFile *CFilesystemHandler::OpenForReading(const char *relativePath) {
	return new CInputFileStdio(relativePath);
}

COutputFile *CFilesystemHandler::OpenForWriting(const char *relativePath) {
	return new COutputFileStdio(relativePath);
}

void RegisterDevice(void)
{
}

void UnregisterDevice(void)
{
}


CotCHelpers::CHJSON *collectDeviceInformation() {
	
	/*** WARNING : when you change the content of this json, don't forget to update the SDKVERSION ***/
	CotCHelpers::CHJSON *j = new CotCHelpers::CHJSON();
	
	size_t size;
	
	sysctlbyname("hw.model", NULL, &size, NULL, 0);
	char *machine = new char[size];
	sysctlbyname("hw.model", machine, &size, NULL, 0);


	
	sysctlbyname("kern.hostmane", NULL, &size, NULL, 0);
	char *hostname = new char[size];
	sysctlbyname("kern.hostmane", hostname, &size, NULL, 0);
  
	j->Put("id", hostname);
	j->Put("model", machine);
	j->Put("version", "1");
	
	delete [] machine;
	delete [] hostname;
	
	return j;
}

// GameCenterHandler.mm
void CloudBuilder::GameCenter::login(CInternalResultHandler *handler) { InvokeHandler(handler, enNotImplemented); }
void CloudBuilder::GameCenter::logout(CInternalResultHandler *handler) { InvokeHandler(handler, enNotImplemented); }
void CloudBuilder::GameCenter::listFriends(CInternalResultHandler *handler) { InvokeHandler(handler, enNotImplemented); }
