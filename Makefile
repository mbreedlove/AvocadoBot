CC=i686-w64-mingw32-g++
CFLAGS=-Wall -static
LIBS=-lws2_32
FILES=osinfo.cpp IRCSocket.cpp botnet.cpp

all: botnet

botnet:
	$(CC) $(CFLAGS) $(FILES) -o botnet.exe $(LIBS)

osinfo.o:
	$(CC) $(CFLAGS) -c osinfo.cpp -o osinfo.o $(LIBS)
	
IRCSocket.o:
	$(CC) $(CFLAGS) -c IRCSocket.cpp -o IRCSocket.o $(LIBS)

clean:
	rm -f *.a *.o botnet.exe
