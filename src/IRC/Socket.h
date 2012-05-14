#ifndef SOCKET_H_
#define SOCKET_H_

#include <iostream>
#include <windows.h>
#include <string>

class Socket {
protected:
    WSADATA wsaData;
    SOCKET soc;
    sockaddr_in myAddr;
    
public:
	Socket();
	virtual ~Socket();
    
    bool open(std::string, int);
    void close();
    
    void sendData(std::string);
    std::string recvData();
};

#endif /* SOCKET_H_*/
