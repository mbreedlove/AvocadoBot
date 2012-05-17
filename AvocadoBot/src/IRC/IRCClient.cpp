/*
 * IRCClient.cpp
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#include "IRCClient.h"

IRCClient::IRCClient(std::string server, int port) {
	this->server = server;
	this->port = port;

	soc = new Socket();
}

IRCClient::~IRCClient() {
	delete soc;
}

void IRCClient::sendRaw(std::string data) {
	soc->sendData(data + "\r\n");
}

std::string IRCClient::readRaw() {
	std::string data = soc->recvData();

	if(data.empty())
		return NULL;

	unsigned int stop = data.find_first_of(" ");
	if(stop != std::string::npos) {
		// Handle PING command
		if(data.substr(0, stop).compare("PING") == 0) {
			pong();
			return readRaw();
		}
		// Handle more Server messages here
	}
	return data;
}

bool IRCClient::connect() {
	std::cout << "Connecting to: " << this->server << ":" << this->port << std::endl;
	bool connected = soc->open(this->server, this->port);
	if(!connected) {
		std::cout << "IRCClient: Could not connect." << std::endl;
		return false;
	}
	sendRaw("USER " + CONFIG_IRC_USER + " localhost localhost :" + CONFIG_IRC_USER);
	sendRaw("NICK " + CONFIG_IRC_NICK);
	return true;
}

void IRCClient::disconnect() {
	sendRaw("QUIT");
	soc->close();
}

void IRCClient::joinChannel(std::string channel) {
	sendRaw("JOIN " + channel);
}

void IRCClient::partChannel(std::string channel) {
	sendRaw("PART " + channel);
}

void IRCClient::sendMessage(std::string target, std::string message) {
	sendRaw("PRIVMSG " + target + " :" + message);
}

void IRCClient::pong() {
	sendRaw("PONG " + this->server_name);
}

void IRCClient::setServer(std::string server) {
	this->server = server;
}

void IRCClient::setServerName(std::string server_name) {
	this->server_name = server_name;
}

void IRCClient::setPort(int port) {
	this->port = port;
}

void IRCClient::setName(std::string name) {
	this->name = name;
}
