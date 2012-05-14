/*
 * IRCManager.h
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#ifndef IRCMANAGER_H_
#define IRCMANAGER_H_

#include <iostream>
#include <process.h>
#include "IRCClient.h"
#include "../Configs.h"

class IRCManager {
public:
	IRCManager();
	virtual ~IRCManager();

	DWORD WINAPI myThread(LPVOID);
};

#endif /* IRCMANAGER_H_ */
