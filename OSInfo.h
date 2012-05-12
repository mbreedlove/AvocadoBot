#ifndef OSINFO_H
#define OSINFO_H

#include <windows.h>
#include <string>

class OSInfo {

protected:
	std::string getOSVersionName();
	std::string getHostname();
	std::string getCPUArch();
	int getCPUCount();
	
public:
    std::string OSVersionName;
    std::string hostname;
    std::string cpuArch;
    int cpuCount;
    
	OSInfo();
	~OSInfo();
};

#endif
