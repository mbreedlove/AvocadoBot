#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct WinVerInfo {
    int PlatformID;
    int MajorVersion;
    int MinorVersion;
};

OSVERSIONINFOEX* getOSVerInfo() {
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    GetVersionEx((OSVERSIONINFO*) &osvi);

    return &osvi;
}

char* getOSInfoString(OSVERSIONINFOEX* OSVerInfo) {
    char* str;

    switch(OSVerInfo->dwMajorVersion) {
        case 6:
            switch(OSVerInfo->dwMinorVersion) {
                case 0:
                    if(OSVerInfo->wProductType == VER_NT_WORKSTATION)
                        str = "Windows Vista";
                    if(OSVerInfo->wProductType != VER_NT_WORKSTATION)
                        str = "Windows Server 2008";
                    break;

                case 1:
                    if(OSVerInfo->wProductType == VER_NT_WORKSTATION)
                        str = "Windows 7";
                    if(OSVerInfo->wProductType != VER_NT_WORKSTATION)
                        str = "Windows Server 2008 R2";
                    break;
            }
            break;
        case 5:
            switch(OSVerInfo->dwMinorVersion) {
                case 0:
                    str = "Windows 2000";
                    break;
                case 1:
                    str = "Windows XP";
                case 2:
                    break;
            }
            break;
    }

    return str;
}

int main(int argc, char* argv[]) {
    OSVERSIONINFOEX* OSVerInfo = getOSVerInfo();
    
    printf("%s\n", getOSInfoString(OSVerInfo));

    return 0;
}
