#include "IRCClient.h"

IRCClient::IRCClient(std::string server, int port, std::string username){
    ircSoc = new IRCSocket();
    this->server = server;
    this->port = port;
    this->username = username;
    
}

bool IRCClient::connect() {
    return ircSoc->connectToServer(this->server, this->port);
}

void IRCClient::send(std::string) {
    ircSoc->sendData(string);
}
std::string IRCClient::recv() {
    char buf[128];
    ircSoc->recvData(buf, sizeof(buf));
    
    return std::string(buf);
}

void IRCClient::close() {
    ircSoc->close();
}

