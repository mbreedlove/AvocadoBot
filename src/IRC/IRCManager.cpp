/*
 * IRCManager.cpp
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#include "IRCManager.h"

IRCManager::IRCManager() {
	ircc = new IRCClient(_CONFIG_IRC_SERVER, _CONFIG_IRC_PORT, "bot");
}

IRCManager::~IRCManager() {
	delete ircc;
}

void IRCManager::start() {
	isConnected = ircc->connect();
	if(!isConnected) {
		return;
	}
	hThread = this->startThread();
	
	// Simulate connection
	Sleep(3000);

	ircc->joinChannel(_CONFIG_IRC_CHANNEL);
	
	// Test connection
	ircc->sendMessage("#tentrabot", "testmessage");
}

void IRCManager::stop() {
	CloseHandle(hThread);
	ircc->disconnect();
}

HANDLE IRCManager::startThread() {
	HANDLE hThread;
	hThread = (HANDLE)_beginthread(monitor, 0, NULL);
	return hThread;
}

static void monitor(void* i) {
	IRCClient* ircc = (IRCClient*)i;
	Sleep(2000);
	while(true) {
		std::string data = ircc->readRaw();
		std::cout << data << std::endl;
		Sleep(100);
	}
}
