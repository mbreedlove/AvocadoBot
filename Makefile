PREFIX=i686-w64-mingw32-
CC=g++
CFLAGS=-O2
LIBS=-lws2_32

RELEASE=Release

all: dir AvocadoBot.exe

AvocadoBot.exe: AvocadoBot.o SysInfo.o IRCClient.o IRCManager.o Socket.o
	$(PREFIX)$(CC) $(CFLAGS) -static -o bin/$(RELEASE)/AvocadoBot.exe obj/*.o $(LIBS)

AvocadoBot.o:
	$(PREFIX)$(CC) $(CFLAGS) -c -o obj/AvocadoBot.o src/AvocadoBot.cpp
	
SysInfo.o:
	$(PREFIX)$(CC) $(CFLAGS) -c -o obj/SysInfo.o src/SysInfo.cpp

IRCClient.o:
	$(PREFIX)$(CC) $(CFLAGS) -c -o obj/IRCClient.o src/IRC/IRCClient.cpp

IRCManager.o:
	$(PREFIX)$(CC) $(CFLAGS) -c -o obj/IRCManager.o src/IRC/IRCManager.cpp

Socket.o:
	$(PREFIX)$(CC) $(CFLAGS) -c -o obj/Socket.o src/IRC/Socket.cpp

clean:
	rm -rf obj/ bin/

dir: 
	mkdir -p obj/ bin/$(RELEASE)
