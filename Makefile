PREFIX=x86_64-w64-mingw32-
CC=g++
CFLAGS=-g3 -O0 -Wall
FILES=
LIBS=-lws2_32

all: AvocadoBot.exe

AvocadoBot.exe: AvocadoBot.o OSInfo.o IRCClient.o IRCManager.o Socket.o
	$(PREFIX)$(CC) $(CFLAGS) -static -o bin/AvocadoBot.exe obj/*.o $(LIBS)

AvocadoBot.o:
	$(PREFIX)$(CC) $(CFLAGS) -c -o obj/AvocadoBot.o AvocadoBot/src/AvocadoBot.cpp
	
OSInfo.o:
	$(PREFIX)$(CC) $(CFLAGS) -c -o obj/OSInfo.o AvocadoBot/src/OSInfo.cpp

IRCClient.o:
	$(PREFIX)$(CC) $(CFLAGS) -c -o obj/IRCClient.o AvocadoBot/src/IRC/IRCClient.cpp

IRCManager.o:
	$(PREFIX)$(CC) $(CFLAGS) -c -o obj/IRCManager.o AvocadoBot/src/IRC/IRCManager.cpp

Socket.o:
	$(PREFIX)$(CC) $(CFLAGS) -c -o obj/Socket.o AvocadoBot/src/IRC/Socket.cpp
