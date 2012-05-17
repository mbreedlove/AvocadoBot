#include "AvocadoBot.h"

using namespace std;

int main(int argc, char *argv[], char *envp[]) {
	IRCManager* ircm = new IRCManager();
	ircm->start();

	return 0;
}
