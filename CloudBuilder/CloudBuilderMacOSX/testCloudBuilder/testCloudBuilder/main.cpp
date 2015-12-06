//
//  main.cpp
//  testCloudBuilder
//
//  Created by Roland Van Leeuwen on 09/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CClan.h"
#include "CHJSON.h"

using namespace CloudBuilder;

#import "CloudBuilder.h"
#import "CClan.h"
#import "CNotificationManager.h"
#import "CUserManager.h"

using namespace CloudBuilder;


// "http://10.0.1.25:3000"

//	const char *server = "http://192.168.10.250:3000"; // 
//	const char *server = "http://10.0.1.25:3000"; //


class MyLoginManager : public CUserManager {
public:
	void didLogin(CloudBuilder::eErrorCode err);
};



class MyClan : public CClan {
public:
	MyClan();
	static bool waiting;
	MyLoginManager *user;
	
	void didFinishSetup(eErrorCode error);
	
};

bool MyClan::waiting = true;


void MyLoginManager::didLogin(eErrorCode ec)
{
	std::cout << "--- didLogin return " << ec << " !\n";
	MyClan::waiting = false;
}


MyClan::MyClan() : CClan(false, new CNotificationManager())
{
	user = new MyLoginManager();
}

void MyClan::didFinishSetup(eErrorCode ec)
{
	std::cout << "--- didFinishSetup return " << ec << " !\n";
	if (ec)
		waiting = false;
	else {
		user->Login("rolandvl", "pass");
	}
}


int main_clan(int argc, const char * argv[])
{
	// insert code here...
	std::cout << "--- CloudBuilder !\n";
	MyClan *clan = new MyClan();

	eErrorCode ec = clan->Setup("1", "AKIAJY5SFRCOF2PLWUDQ", "BrH7huCRfH3tSqqmoDIOiZPE87fjetN+TK+56rO+", "DEV");

	if (ec)
		std::cout << "--- Setup return " << ec << " !\n";
	else {
		while (MyClan::waiting)
			CNotificationManager::popNextCallback();
	}
	
	std::cout << "--- test finished !\n";
		
	return 0;
}

int main_socket(int argc, const char * argv[]);
int main_curl(void);

int main(int argc, const char * argv[])
{
//	main_clan(argc, argv);
	main_socket(argc, argv);
//	main_curl();
}

