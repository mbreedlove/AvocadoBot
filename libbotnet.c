#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
    char OSVersion[32];
    char hostname[32];
    int  memory;
    long int  hddSize;
} OSInfo;

int getOSVersionName(char* buffer) {
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetVersionEx((OSVERSIONINFO*) &osvi);

    switch(osvi.dwMajorVersion) {
        case 6:
            switch(osvi.dwMinorVersion) {
                case 0:
                    if(osvi.wProductType == VER_NT_WORKSTATION)
                        strcpy(buffer, "Windows Vista");
                    if(osvi.wProductType != VER_NT_WORKSTATION)
                        strcpy(buffer, "Windows Server 2008");
                    break;

                case 1:
                    if(osvi.wProductType == VER_NT_WORKSTATION)
                        strcpy(buffer, "Windows 7");
                    if(osvi.wProductType != VER_NT_WORKSTATION)
                        strcpy(buffer, "Windows Server 2008 R2");
                    break;
            }
            break;
        case 5:
            switch(osvi.dwMinorVersion) {
                case 0:
                    strcpy(buffer, "Windows 2000");
                    break;
                case 1:
                    strcpy(buffer, "Windows XP");
                    break;
                case 2:
                    break;
            }
            break;
    }
    return 0;
}

int getRAMSize() {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof( statex );
    GlobalMemoryStatusEx(&statex);

    return statex.ullTotalPhys;
}

int getHostname(char* buffer) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    gethostname(buffer, 32);
    WSACleanup();
    return 0;
}

int getOSInfo(OSInfo* osi) {
    getOSVersionName(osi->OSVersion);
    getHostname(osi->hostname);
    osi->memory = getRAMSize();
    return 0;
}

int main(int argc, char* argv[]) {
    OSInfo osi;
    getOSInfo(&osi);
   
    printf("OS: %s\nHostname: %s\nMemory: %d MB\n", osi.OSVersion, osi.hostname, (int)(osi.memory / 1024 / 1024));
    return 0;
}
