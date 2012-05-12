#ifndef IRCCLIENT_H
#define IRCCLIENT_H

#include <iostream>
#include <windows.h>
#include <string>
#include "IRCSocket.h"

class IRCClient {
protected:
    IRCSocket* ircSoc;
    std::string server;
    int port;
    std::string username;
    
public:
	IRCClient(std::string, int, std::string);
	~IRCClient();
    
    bool connect();
    
    void send(std::string);
    std::string recv();
    void close();
};

#endif
