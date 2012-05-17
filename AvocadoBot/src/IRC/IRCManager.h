/*
 * IRCManager.h
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#ifndef IRCMANAGER_H_
#define IRCMANAGER_H_

#include <windows.h>
#include <process.h>
#include "IRCClient.h"
#include "../OSInfo.h"
#include "../Configs.h"

void monitor(void*);
void parseData(IRCClient*, std::string);

class IRCManager {
public:
	IRCManager();
	virtual ~IRCManager();

	void start();
	void stop();
	bool isConnected();
	IRCClient* ircc;

protected:
	HANDLE hThread;
	bool connected;

	HANDLE startThread();
};

#endif /* IRCMANAGER_H_ */
