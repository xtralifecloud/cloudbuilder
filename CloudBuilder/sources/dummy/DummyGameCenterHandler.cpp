#include "CloudBuilder.h"
#include "CCallback.h"
#include "GameCenterHandler.h"

using namespace CloudBuilder;

void CloudBuilder::GameCenter::login(CInternalResultHandler *handler) { InvokeHandler(handler, enNotImplemented); }
void CloudBuilder::GameCenter::logout(CInternalResultHandler *handler) { InvokeHandler(handler, enNotImplemented); }
void CloudBuilder::GameCenter::listFriends(CInternalResultHandler *handler) { InvokeHandler(handler, enNotImplemented); }
