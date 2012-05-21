#ifndef OSINFO_H_
#define OSINFO_H_

#include <sstream>
#include <windows.h>

class OSInfo {
public:
	static std::string getOSVersionName();
	static std::string getShortOSVersionName();
	static std::string getHostname();
	static std::string getCPUArch();
	static int getCPUCount();

	static std::string sysInfoStr();

};

#endif /* OSINFO_H_*/
