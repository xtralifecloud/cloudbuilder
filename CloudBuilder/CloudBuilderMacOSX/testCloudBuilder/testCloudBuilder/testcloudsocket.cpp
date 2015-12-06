//
//  testcloudsocket.cpp
//  testCloudBuilder
//
//  Created by Roland Van Leeuwen on 19/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "CotCHelpers.h"
#include "CClan.h"
#include "CNotificationManager.h"

#include "../../../sources/CCloudSocket.h"

#include <unistd.h>

using namespace CloudBuilder;
using namespace CotCHelpers;


class dummyClan : public CClan {
public:
	dummyClan();
};

dummyClan::dummyClan() : CClan(false, new CNotificationManager())
{
}

class MySocket : public CCloudSocket {
public:
	MySocket() { connected = false; opening =true; };
	~MySocket() {};
	
	virtual void on_error(const char* error);
	virtual void on_close(int reason);
	virtual void on_open();
	virtual void on_data(const CotCHelpers::CHJSON* json);

	bool connected;
	bool opening;

};

void MySocket::on_error(const char *error)
{
	connected = false;
	printf("-- error:%s \n", error);
}

void MySocket::on_close(int reason)
{
	connected = false;
	printf("on close \n");
}
void MySocket::on_open()
{
	connected = true;
	opening = false;
	printf("on open \n");
}

void MySocket::on_data(const CotCHelpers::CHJSON *json)
{
	char *str = json->print();
	printf("on data: %s \n", str);
	free(str);
}


int main_socket(int argc, const char * argv[])
{
	CotCHelpers::Init();
	dummyClan *m = new dummyClan();
	
	printf("--- CloudBuilder !\n");
	MySocket *sckt = new MySocket();
	
	sckt->connect("localhost", 3001);
	int count = 0;
	int total = 0;
	
	do {
		usleep(1000);
		CNotificationManager::Instance()->popNextCallback();
		if (sckt->connected )
		{
			if (count==100 && total<10)
			{
				total++;
				count = 0;
				CHJSON *json = CHJSON::parse("{\"event\": \"test\",  \"data\" : {\"type\":\"toto\", \"message\":\"un message\"} }");
				sckt->emit(json);
				delete json;
			}
			count++;
		}
	}
	while (sckt->connected || sckt->opening);
	
	delete m;
	
	return 0;
}
