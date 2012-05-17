#ifndef SOCKET_H_
#define SOCKET_H_

#include <iostream>
#include <string>
#include "Windows.h"

class Socket {
protected:
    WSADATA wsaData;
    SOCKET soc;
    sockaddr_in myAddr;
    bool connected;
    
public:
	Socket();
	virtual ~Socket();
    
    bool open(std::string, int);
    void close();
    
    void sendData(std::string);
    std::string recvData();

    bool isConnected();
};

#endif /* SOCKET_H_*/
