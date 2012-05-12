#include "IRCSocket.h"

IRCSocket::IRCSocket() {
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
        std::cerr << "Socket Initialization: Error with WSAStartup\n";
        WSACleanup();
    }
    
    soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
       
    if(soc == INVALID_SOCKET) {
        std::cerr << "Socket Initialization: Error creating socket\n";
        WSACleanup();
    }
}

IRCSocket::~IRCSocket() {
    WSACleanup();
}

bool IRCSocket::connectToServer(std::string server, int port) {
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = inet_addr(server.c_str());
    myAddr.sin_port = htons(port);
    
    if(connect(soc, (SOCKADDR*) &myAddr, sizeof(myAddr)) == SOCKET_ERROR ) {
        std::cerr << "ClientSocket: Failed to connect\n";
        WSACleanup();
        return FALSE;
    }
    return TRUE;
}

void IRCSocket::sendData(std::string data) {
    send(soc, data.c_str(), strlen(data.c_str()), 0);
}

void IRCSocket::recvData(char* buff, int len) {
    recv(soc, buff, len, 0);
}

void IRCSocket::close() {
    closesocket(soc);
}
