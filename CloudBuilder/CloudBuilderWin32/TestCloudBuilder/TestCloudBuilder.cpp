// TestCloudBuilder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Windows.h>

#include "CloudBuilder/Headers/CloudBuilder.h"
#include "CloudBuilder/Headers/CCallback.h"
#include "CloudBuilder/Headers/CClannishDB.h"

using namespace CloudBuilder;
using namespace CotCHelpers;

bool quit;

static void LOG(const CCloudResult *res, const char *funcname)
{
	if(res)
   	{ 
		eErrorCode ec = res->GetErrorCode();
		const CHJSON *json = res->GetJSON();
		if (json && json->size()!=0)
		{
			const char *str = json->print();
		}
	}
}

static void scoreCallback(void *data, const CCloudResult *result )
{
	LOG(result, "scoreCallback");
	quit = true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CClannishDB *conn = CClannishDB::Instance();
	
	CCloudResult *res = conn->Setup("AKIAJ6X7GL2Z6EFC7QCA", "yGOV1WM5Y3kQJabk3DDddpmTGYgg+aNvu8/o/pzP",
					  "AKIAJL3Q3FYPYXFB4LNA", "GYZQE5dL2biYUkNy7JjgDGTNGosCIoI0pIf2hhiG", NULL);
	LOG(res, "Setup");
								   		
	res =  conn->Login("r02", "pass");
	LOG(res, "Login");

	CCallback *cb = CCallback::callback(NULL, scoreCallback);
	res =  conn->Score(100, "standard", cb);
	delete cb;
	LOG(res, "Score");
	
	quit = false;
	while (!quit)
	{
		CCallback::popNextCallback();
		Sleep(10);
	} 
   
	res =  conn->Logout();
	LOG(res, "Logout");
	
	delete conn;	  

	return 0;
}

