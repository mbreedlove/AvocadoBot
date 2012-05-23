#ifndef SYSINFO_H_
#define SYSINFO_H_

#include <sstream>
#include <windows.h>

namespace SysInfo {
	std::string getOSVersionName();
	std::string getShortOSVersionName();
	std::string getHostname();
	std::string getCPUArch();
	int getCPUCount();

	std::string sysInfoStr();
}

#endif /* SYSINFO_H_*/
