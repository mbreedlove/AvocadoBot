/*
 * IRCManager.cpp
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#include "IRCManager.h"

IRCManager::IRCManager() {
	ircc = new IRCClient(CONFIG_IRC_SERVER, CONFIG_IRC_PORT);
	connected = false;
	hThread = 0;
}

IRCManager::~IRCManager() {
	delete ircc;
}

bool IRCManager::isConnected() {
	return connected;
}

void IRCManager::start() {
	connected = ircc->connect();
	if(!connected) {
		return;
	}
	hThread = this->startThread();
	
	ircc->joinChannel(CONFIG_IRC_CHANNEL);
	
	// Test connection
	ircc->sendMessage("#tentrabot", "testmessage");
}

void IRCManager::stop() {
	connected = false;
	CloseHandle(hThread);
	ircc->disconnect();
}

HANDLE IRCManager::startThread() {
	HANDLE hThread;
	hThread = (HANDLE)_beginthread(monitor, 0, this);
	return hThread;
}

void monitor(void* i) {
	IRCClient* ircc = (IRCClient*)((IRCManager*)i)->ircc;
	while(true) {
		std::string data;
		data = ircc->readRaw();
		if(data.empty()) {
			((IRCManager*)i)->stop();
			return;
		}
		std::cout << data;
		fflush(stdout);
	}
}
