#include "botnet.h"

using namespace std;

int main(int argc, char* argv[]) {
    OSInfo* osi = new OSInfo();
    IRCClient* ircc = new IRCClient("127.0.0.1", 8080, "mr. bot");
    
    ircc->connect();
    ircc->send("ehhlo");
    return 0;
}
