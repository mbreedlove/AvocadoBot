/*
 * IRCClient.h
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#ifndef IRCCLIENT_H_
#define IRCCLIENT_H_

#include <windows.h>
#include <string>
#include <sstream>

#include "Socket.h"

class IRCClient {
public:
	IRCClient();
	IRCClient(std::string, int, std::string);
	virtual ~IRCClient();

	void sendRaw(std::string);
	std::string readRaw();

	bool connect();
	void disconnect();

	void joinChannel(std::string);
	void partChannel(std::string);
	void sendMessage(std::string, std::string);

	void setServer(std::string);
	void setPort(int);
	void setName(std::string);

protected:
	std::string server;
	int port;
	std::string name;

	Socket* soc;

	void pong();
};

#endif /* IRCCLIENT_H_ */
