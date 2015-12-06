//
//  main.cpp
//  monkey
//
//  Created by roland on 07/03/13.
//  Copyright (c) 2013 Clan of the CLoud. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>

#include "../../CloudBuilder/tests/cli.h"

bool gReady = true;

std::list<std::string> gCmd;

class MyCLI : public CLI {
public:
	virtual void logger(const char *message, typelog kind);
	virtual void stopActivity(eErrorCode ec);

};

void MyCLI::logger (const char *message, typelog kind)
{
	switch (kind)
	{
		case kLOG:
			std::cout << message << "\n";
		break;
		case kERR:
			std::cout << "\033[1;31m" << message << "\033[0m\n";
		break;
		case kCMD:
			std::cout << "\033[1;32m> " << message << "\033[0m\n";
		break;
		case kSCRIPT:
			std::cout << "\033[1;32m>> " << message << "\033[0m\n";
		break;
	}
	
}

void MyCLI::stopActivity (eErrorCode ec)
{
	gReady = true;
	if (ec)
		this->logger(errorString(ec), kERR);
	else
		this->logger("Done.", kLOG);
}

MyCLI *mainCLI;

static void mgetline(char *command)
{
	bool inEscape = false;

	system("stty raw"); 
	*command = 0;
	
	char *p = command;
	char *l = command;

	while(true)
	{
		mainCLI->idle();
		char key = getchar();
		if (inEscape)
		{
			//printf("esc");
			//printf("[%d]", key);
			char code = getchar();
			switch (code)
			{
				case 'A': 
				{
					for(int i=strlen(command); i>1; i--)
						printf("\033[D");
					printf("\033[D\033[K"); 
					p = l = command;
					*command=0;
					std::list<std::string>::iterator it;
					for(it = gCmd.begin(); it!= gCmd.end(); it++)
					{
						printf("\n%s" , it->c_str());
					}

				}					
				break;
				case 'B': 
				{
					for(int i=strlen(command); i>1; i--)
						printf("\033[D");
					printf("\033[D\033[K"); 
					p = l = command;
					*command=0;
				}					
				break;
				case 'C':
					if (p<l)
					{
						printf("\033[C");
						p++;
					}
					break;
				case 'D':
					if (p>command)
					{
						printf("\033[D");
						p--;
					}
					break;
			}
			inEscape = false;
		}
		else switch (key)
		{
			case 3: system("stty cooked");  exit(0); return;

			case 13 : *l = 0; system("stty cooked"); printf("\n"); return;

			case 127 : // delete
				if (false && p>command)
				{
					if (p<l)
					{
						char end[1000];
						strcpy(end, p);
						--p;
						*p=0;
						strcat(command, end);
						l--;
						printf("\033[D\033[K"); 
						printf("%s", p);
						for(int i=strlen(end); i>0; i--)
							printf("\033[D");						
					}
					else
					{
						printf("\033[D\033[K"); 
						l--;
						p--;
						*p=0;
					}
				}
				break;

			case 9:
				break;

			case 27 :
				inEscape = true;
				//printf("ESC");
				break;

			default:
				if (p<l)
				{
					char end[1000];
					strcpy(end, p);
					*p++=key;
					*p=0;
					strcat(command, end);
					printf("%s", p-1);
					l++;
					for(int i=strlen(end); i>0; i--)
						printf("\033[D");						
				}
				else
				{
					*p++ = key;
					*p=0;
					l=p;
					printf("%c", key);
				}
				break;
		}
	}
}

int main(int argc, const char * argv[])
{

std::stringstream buffererr;
std::streambuf * olderr = std::cerr.rdbuf(buffererr.rdbuf());

	std::cout << "\nWelcome to CloudBuilder CLI\n\nType help to get lists of commands\n\n";

	mainCLI = new MyCLI();

	bool running = true;
	char command[1000];

	while(running)
	{
		std::cout << "> ";
 		mgetline(command);

 		if (*command!=0 ) gCmd.push_back(std::string(command));

 		running = (strcmp(command, "quit") != 0) && (strcmp(command, "exit") != 0);
 		if (running)
 		{
 			gReady = false;
 			eErrorCode ec = mainCLI->execute(command);
 			if (ec != enNoErr)
 			{
				if (ec!= -1)
					mainCLI->logger(errorString(ec), CLI::kERR);
				gReady = true;
			}
			else
			{
				while (!gReady)
				{
					usleep(100000);
					mainCLI->idle();
				}

			}
 		}
	}

	return 0;
}

