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

void IRCClient::setServer(std::string server) {
	this->server = server;
}

void IRCClient::setPort(int port) {
	this->port = port;
}

void IRCClient::setName(std::string name) {
	this->name = name;
}

void IRCClient::connect() {
	soc->open(this->server, this->port);
}

void IRCClient::joinChannel(std::string channel) {

}

void IRCClient::partChannel(std::string channel) {

}
