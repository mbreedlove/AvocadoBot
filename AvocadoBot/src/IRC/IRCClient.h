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
#include "../Configs.h"

#include "Socket.h"

class IRCClient {
public:
	IRCClient(std::string, int);
	virtual ~IRCClient();

	void sendRaw(std::string);
	std::string readRaw();

	bool connect();
	void disconnect();

	void joinChannel(std::string);
	void partChannel(std::string);
	void sendMessage(std::string, std::string);

	void setServer(std::string);
	void setServerName(std::string);
	void setPort(int);
	void setName(std::string);

protected:
	std::string server;
	std::string server_name;
	int port;
	std::string name;

	Socket* soc;

	void pong();
};

#endif /* IRCCLIENT_H_ */
