//
//  main.cpp
//  monkey
//
//  Created by roland on 07/03/13.
//  Copyright (c) 2013 Clan of the CLoud. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CloudBuilderSupport.h"


#define IS(a, b) if (strcmp(option, a)==0) { { b } return 0;  }

TMonkeyOptions gMonkeyOptions;

TMonkeyOptions::TMonkeyOptions() {
	run = true;
	newuser = true; // if true, then create a new user each time monkey"pid", else use the login/passord pref
	strcpy(login, "monkey");
	strcpy(password, "pass");
	loop = 1;
	event = 3;
	score = 1;
	infinite = true;
	nodelay = false;
	*host = 0;
}

static void usage()
{
	printf("monkey --user name --pass password --register Y/N \n");
}

static int handleoption(const char *option, const char *param)
{
	IS("user",
		strcpy(gMonkeyOptions.login, param);
	)

	IS("host",
		sprintf(gMonkeyOptions.host, "https://%s:3500", param);
	)
	
	IS("pass",
		strcpy(gMonkeyOptions.password, param);
	)

	IS("register",
		gMonkeyOptions.newuser = (strcmp(param, "Y")==0);
	)
		
	IS("loop",
		gMonkeyOptions.loop = atoi(param);
	)

	IS("event",
		gMonkeyOptions.event = atoi(param);
	)

	IS("score",
		gMonkeyOptions.score = atoi(param);
	)

	IS("nodelay",
		gMonkeyOptions.nodelay = (strcmp(param, "Y")==0);
	)
	IS("infinite",
		gMonkeyOptions.infinite = (strcmp(param, "Y")==0);
	)

	return -1;
}

int main(int argc, const char * argv[])
{
	char option[100];
	
	for (int n=1; n<argc; n++)
	{
		const char *p = argv[n];
		if (p[0] == '-')
		{
			int l = strlen(p);
			if (l>1)
			{
				strcpy(option, p+1);
				int r = (n+1< argc) ? handleoption(option, argv[n+1]) : -1;
				if (r==-1) // invalid syntax or parameter
				{
					usage();
					exit(1);
				}
				else
					n++;
			}
		}
	}
	
	CotC_Setup();
	while (gMonkeyOptions.run)
	{
		usleep(100000);
		popNextCallback();
	}
	
	for (int n=gMonkeyOptions.loop; n > 0; n--)
	{
		time_t now;
		time(&now);
		struct tm* ptm;
		ptm = gmtime(&now);

		gMonkeyOptions.run = true;
		
		char name[40];
		gethostname(name, 40);
		
		std::cout <<  name << "\n";
		
		std::cout << "-----\nMonkey "<< getpid() <<" started at " << asctime(ptm) << "\n";
		Monkey_Start();

		while (gMonkeyOptions.run)
		{
			usleep(100000);
			popNextCallback();
		}

		time_t end;
		time(&end);
		ptm = gmtime(&end);
		std::cout << "\nMonkey "<< getpid() << " stopped at " << asctime(ptm);
		std::cout << "Monkey "<< getpid() << " tooks " << end-now << "s\n";
		std::cout << "-----\n";
	}

	return 0;
}

