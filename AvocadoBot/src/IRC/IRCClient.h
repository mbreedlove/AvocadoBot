/*
 * IRCClient.h
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#ifndef IRCCLIENT_H_
#define IRCCLIENT_H_

#include <windows.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include "../Configs.h"
#include "../OSInfo.h"

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

	//Setters
	void setServerName(std::string);
	void setNickname(std::string);

	//Getters
	std::vector<std::string> getIRCChannels();

protected:
	std::string IRC_ServAddr;
	std::string IRC_ServName;
	int IRC_ServPort;
	std::vector<std::string> IRC_Channels;
	std::string IRC_Username;
	std::string IRC_Nickname;

	Socket* soc;

	void pong();
};

#endif /* IRCCLIENT_H_ */
