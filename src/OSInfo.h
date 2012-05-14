#ifndef OSINFO_H_
#define OSINFO_H_

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
	virtual ~OSInfo();
};

#endif /* OSINFO_H_*/
