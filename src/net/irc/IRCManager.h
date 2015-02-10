/*
 * IRCManager.h
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#ifndef IRCMANAGER_H_
#define IRCMANAGER_H_

#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <process.h>
#include <windows.h>
#include "IRCClient.h"
#include "../../SysInfo.h"
#include "../../Configs.h"

void monitorIRC(void*);
void parseData(IRCClient*, std::string, char);
std::string executeCommand(std::string, std::string);

class IRCManager {
public:
	IRCManager();
	virtual ~IRCManager();

	char getIRCCommandPrefix();

	void start();
	void stop();
	bool isConnected();
	IRCClient* ircc;

protected:
	HANDLE hThread;
	bool connected;

	char IRC_CommandPrefix;

	HANDLE startThread();
};

#endif /* IRCMANAGER_H_ */
