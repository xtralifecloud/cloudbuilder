#ifndef __REGISTERDEVICE__
#define __REGISTERDEVICE__

namespace CotCHelpers
{
	class CHJSON;
}

void RegisterDevice(void);
void UnregisterDevice(void);
CotCHelpers::CHJSON *collectDeviceInformation();

#endif	// __REGISTERDEVICE__