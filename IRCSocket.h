#ifndef IRCSOCKET_H
#define IRCSOCKET_H

#include <iostream>
#include <windows.h>
#include <string>

class IRCSocket {
protected:
    WSADATA wsaData;
    SOCKET soc;
    sockaddr_in myAddr;
    
public:
	IRCSocket();
	~IRCSocket();
    
    bool connectToServer(std::string, int);
    
    void sendData(std::string);
    void recvData(char*, int);
    void close();
};

#endif
