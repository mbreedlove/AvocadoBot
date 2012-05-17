#ifndef OSINFO_H_
#define OSINFO_H_

#include <sstream>
#include <windows.h>

class OSInfo {
public:
    std::string OSVersionName;
    std::string hostname;
    std::string cpuArch;
    int cpuCount;

	std::string sysInfoStr();
    
	OSInfo();
	virtual ~OSInfo();

protected:
	std::string getOSVersionName();
	std::string getHostname();
	std::string getCPUArch();
	int getCPUCount();

};

#endif /* OSINFO_H_*/
