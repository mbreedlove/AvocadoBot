#include "SysInfo.h"

// Not entirely complete, matches most common found versions
 std::string SysInfo::getOSVersionName() {
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetVersionEx((OSVERSIONINFO*) &osvi);

    switch(osvi.dwMajorVersion) {
        case 6:
            switch(osvi.dwMinorVersion) {
                case 0:
                    if(osvi.wProductType == VER_NT_WORKSTATION)
                        return "Windows Vista";
                    if(osvi.wProductType != VER_NT_WORKSTATION)
                        return "Windows Server 2008";
                    break;

                case 1:
                    if(osvi.wProductType == VER_NT_WORKSTATION)
                        return "Windows 7";
                    if(osvi.wProductType != VER_NT_WORKSTATION)
                        return "Windows Server 2008 R2";
                    break;
            }
            break;
        
		case 5:
            switch(osvi.dwMinorVersion) {
                case 0:
                    return "Windows 2000";

				case 1:
                    return "Windows XP";

                case 2:
					if(GetSystemMetrics(SM_SERVERR2) == 0)
						return "Windows Server 2003";
					if(osvi.wSuiteMask & VER_SUITE_WH_SERVER)
						return "Windows Home Server";
                    break;
            }
            break;
    }
    return 0;
}

std::string SysInfo::getShortOSVersionName() {
	std::string shortName = getOSVersionName();
	int index = shortName.find_first_of("Windows");
	shortName.replace(index, index +7, "Win");

	index = shortName.find_first_of("200");
	shortName.replace(index, index +3, "'0");


	while(index != std::string::npos) {
		shortName.replace(index, 1, "" );
		index = shortName.find(" ", index +1 );
	}

	return shortName;
}

 std::string SysInfo::getHostname() {
    char buf[32];
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
    gethostname(buf, sizeof(buf));
    
    return std::string(buf);
}

 std::string SysInfo::getCPUArch() {
    SYSTEM_INFO siSysInfo;
    
    // Copy the hardware information to the SYSTEM_INFO structure. 
    GetSystemInfo(&siSysInfo); 
    
    if(siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
        return "x86";
    else if(siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        return "x86_64";
    else if(siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
        return "Intel Itanium";
    else
        return "Undefined";
    return 0;
}

 int SysInfo::getCPUCount() {
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);

    return siSysInfo.dwNumberOfProcessors;
}

 std::string SysInfo::sysInfoStr() {
	std::ostringstream ss;

	ss << "Hostname: " << getHostname() << " | ";
	ss << "OS Ver: " << getOSVersionName() << " | ";
	ss << "CPU Cores: " << getCPUCount() << " | ";
	ss << "CPU Arch: " << getCPUArch();

	return ss.str();
}