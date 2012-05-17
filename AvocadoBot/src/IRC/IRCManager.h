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
#include "../Configs.h"

static void monitor(void*);

class IRCManager {
public:
	IRCManager();
	virtual ~IRCManager();

	void start();
	void stop();
	IRCClient* ircc;

protected:
	HANDLE hThread;
	bool isConnected;

	HANDLE startThread();
};

#endif /* IRCMANAGER_H_ */
