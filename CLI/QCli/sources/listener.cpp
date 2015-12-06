#include	<iostream>
#ifdef WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif
#include	"listener.h"


Listener::Listener()
{
}

void	Listener::process()
{
	while (42)
	{
#ifdef WIN32
		Sleep(100);
#else
		usleep(100000);
#endif
		emit	idleSig();
	}
}
