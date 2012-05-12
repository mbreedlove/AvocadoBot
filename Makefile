CC=i686-w64-mingw32-gcc
AR=i686-w64-mingw32-ar
CFLAGS=

all:
	$(CC) $(CFLAGS) -o botnet.exe libbotnet.c
