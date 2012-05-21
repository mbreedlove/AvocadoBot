/*
 * IRCClient.cpp
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#include "IRCClient.h"

IRCClient::IRCClient(std::string server, int port) {
	this->IRC_ServAddr = server;
	this->IRC_ServPort = port;

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
	bool connected = soc->open(this->IRC_ServAddr, this->IRC_ServPort);
	if(!connected) {
		std::cout << "IRCClient: Could not connect." << std::endl;
		return false;
	}
	sendRaw("USER " + IRC_Username + " localhost localhost :" + IRC_Username);
	sendRaw("NICK " + IRC_Nickname);

	joinChannel(IRC_Channels[0]);
	return true;
}

void IRCClient::disconnect() {
	sendRaw("QUIT");
	soc->close();
}

void IRCClient::joinChannel(std::string channel) {
	// Add channel to list
	IRC_Channels.push_back(channel);
	sendRaw("JOIN :" + channel);
}

void IRCClient::partChannel(std::string channel) {
	// Remove channel from list
	auto ind = std::find(IRC_Channels.begin(), IRC_Channels.end(), channel);
	IRC_Channels.erase(IRC_Channels.begin() +2);
	sendRaw("PART :" + channel);
}

void IRCClient::sendMessage(std::string target, std::string message) {
	sendRaw("PRIVMSG " + target + " :" + message);
}

void IRCClient::pong() {
	sendRaw("PONG " + this->IRC_ServAddr);
}

// Setters

void IRCClient::setNickname(std::string nickname) {
	this->IRC_Nickname = nickname;
}

void IRCClient::setServerName(std::string ServerName) {
	this->IRC_ServName = ServerName;
}

// Getters

std::vector<std::string> IRCClient::getIRCChannels() {
	return this->IRC_Channels;
}