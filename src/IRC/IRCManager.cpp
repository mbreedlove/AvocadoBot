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

//	unsigned threadID;
//    _beginthreadex(
//    		NULL,
//    		0,
//    		IRCManager::threadEntryPoint,
//    		NULL,
//    		0,
//    		&threadID
//    	);


	Sleep(5000);
	ircc->joinChannel(_CONFIG_IRC_CHANNEL);
	Sleep(3000);
	ircc->sendMessage("#tentrabot", "testmessage");
	Sleep(3000);
	ircc->disconnect();
	CloseHandle(hThread);
}

IRCManager::~IRCManager() {
	// TODO Auto-generated destructor stub
}


DWORD WINAPI IRCManager::myThread(LPVOID lpParam) {
	std::cout << "Thread!" << std::endl;

	return 0;
}
