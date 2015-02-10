#include "AvocadoBot.h"

using namespace std;

int main(int argc, char *argv[]) {
	IRCManager* ircm = new IRCManager();
	ircm->start();

	while(true) {
		if(!ircm->isConnected()) {
			clog << "Disconnected" << endl;
			ircm->start();
		}
	}
	return 0;
}