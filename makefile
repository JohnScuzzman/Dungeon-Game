CC = gcc
CFLAGS = -lncurses -lm -I./include/ -g
SOURCES = ./src/*.c

all: rogue run clean

rogue:
	$(CC) $(SOURCES) $(CFLAGS) -o rogue

run:
	./rogue

clean:
	rm rogue
