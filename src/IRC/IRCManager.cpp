/*
 * IRCManager.cpp
 *
 *  Created on: May 13, 2012
 *      Author: mbreedlove
 */

#include "IRCManager.h"

IRCManager::IRCManager() {
	IRCClient* ircc = new IRCClient(_CONFIG_IRC_SERVER, _CONFIG_IRC_PORT, "bot");

	ircc->connect();

//	DWORD threadID;
//    HANDLE hThread = CreateThread(
//        0,                   /* default security attributes.   */
//        0,                      /* use default stack size.        */
//        &IRCManager::myThread,				/* thread function name.          */
//        &ircc,                   /* argument to thread function.   */
//        0,                      /* use default creation flags.    */
//        &threadID);				  /* returns the thread identifier. */


	Sleep(5000);
	ircc->joinChannel(_CONFIG_IRC_CHANNEL);
	Sleep(3000);
	ircc->sendMessage("#tentrabot", "testmessage");
	Sleep(3000);
	ircc->disconnect();

}

IRCManager::~IRCManager() {
	// TODO Auto-generated destructor stub
}
