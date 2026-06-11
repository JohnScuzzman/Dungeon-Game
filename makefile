CXX = g++
CXXFLAGS = -std=c++17 -lncurses -lm -I./include/ -g
SOURCES = ./src/*.cpp

all: rogue run clean

rogue:
	$(CXX) $(SOURCES) $(CXXFLAGS) -o rogue

run:
	./rogue

clean:
	rm rogue
