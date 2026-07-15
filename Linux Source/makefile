CC = gcc
CFLAGS = -lpdcurses -lcjson -lm -I./include/ -I/mingw64/include/ncurses -o -g -L/mingw64/bin -DNCURSES_STATIC
SOURCES = ./src/*.c 

all: rogue run clean

rogue:
	$(CC) $(SOURCES) $(CFLAGS) -o rogue.exe

run:
	./rogue.exe

# clean:
# 	rm rogue
