CC = gcc
CFLAGS = -I./include/ -I/ucrt64/include/cjson/ -I/ucrt64/include/pdcurses/ 
LDFLAGS = -lpdcurses -lcjson 

all: 
	$(CC) ./src/*.c $(CFLAGS) $(LDFLAGS) -o rogue.exe
