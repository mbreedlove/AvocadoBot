#ifndef OSINFO_H_
#define OSINFO_H_

#include <sstream>
#include <windows.h>

namespace OSInfo {
	std::string getOSVersionName();
	std::string getShortOSVersionName();
	std::string getHostname();
	std::string getCPUArch();
	int getCPUCount();

	std::string sysInfoStr();
}

#endif /* OSINFO_H_*/
