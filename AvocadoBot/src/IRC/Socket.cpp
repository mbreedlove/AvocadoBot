#include "Socket.h"

Socket::Socket() {
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
        std::cerr << "Socket Initialization: Error with WSAStartup\n";
        WSACleanup();
    }
    
    soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
       
    if(soc == INVALID_SOCKET) {
        std::cerr << "Socket Initialization: Error creating socket\n";
        WSACleanup();
    }
    connected = false;
}

Socket::~Socket() {
    WSACleanup();
}

/*
 * Establishes connection using parameters
 * \param[in] server The IP address to connect to
 * \param[in] port   The port to connect to
 */
bool Socket::open(std::string server, int port) {
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = inet_addr(server.c_str());
    myAddr.sin_port = htons(port);
    
    if(connect(soc, (SOCKADDR*) &myAddr, sizeof(myAddr)) == SOCKET_ERROR ) {
        std::cerr << "Socket: Failed to connect\n";
        WSACleanup();
        return FALSE;
    }

    connected = true;
    return TRUE;
}

/*
 * Closes socket connection
 */
void Socket::close() {
    closesocket(soc);
}

/*
 * Sends string to server
 * \param[in] data String to send to server
 */
void Socket::sendData(std::string data) {
	std::cout << "-->" << data << std::endl;
    send(soc, data.c_str(), strlen(data.c_str()), 0);
}

/*
 * Receives data from server
 * \return String containing data received
 */
std::string Socket::recvData() {
	char buf[2048];
	ZeroMemory(buf, sizeof(buf));

	recv(soc, buf, sizeof(buf), 0);

	// Is connection broken?
	if(buf[0] == 0x5b) {
		connected = false;
		return std::string();
	}
    return std::string(buf);
}


bool Socket::isConnected() {
	return connected;
}
