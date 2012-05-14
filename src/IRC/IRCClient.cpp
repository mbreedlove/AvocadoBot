/*
 * IRCClient.cpp
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#include "IRCClient.h"

IRCClient::IRCClient(std::string server, int port, std::string name) {
	this->server = server;
	this->port = port;
	this->name = name;

	soc = new Socket();
}

IRCClient::~IRCClient() {
	// TODO Auto-generated destructor stub
}

void IRCClient::connect() {
	soc->open(this->server, this->port);
}

void IRCClient::joinChannel(std::string channel) {
	soc->sendData("JOIN " + channel);
}

void IRCClient::partChannel(std::string channel) {
	soc->sendData("PART " + channel);
}

void IRCClient::sendMessage(std::string target, std::string message) {
	soc->sendData("PRIVMSG " + target + " " + message);
}

void IRCClient::pong() {
	soc->sendData("PONG " + this->server);
}

void IRCClient::setServer(std::string server) {
	this->server = server;
}

void IRCClient::setPort(int port) {
	this->port = port;
}

void IRCClient::setName(std::string name) {
	this->name = name;
}
