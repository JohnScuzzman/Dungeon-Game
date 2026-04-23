#include <stdlib.h> // Used for random num generation.
#include <termios.h>
#include <unistd.h>
#include "tables.h"

struct termios orig_termios;
void enableRawMode();
void disableRawMode();

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    RNG();
    int LengthSum = 0;
    int WidthSum = 0;
    int RoomSeed = 0;
    int nextSeed = 0;
    int **floor = CreateFloor(100, 100);
    int roomsNotPlaced = 0;

    while (roomsNotPlaced < 4)
    {
        
        // For loop for speed
        for (int i = 0; i < 5; i++) {
            RoomSeed = CreateRoom(floor, WidthSum, LengthSum, nextSeed);
            LengthSum = LengthSum + RoomSeed + 1;
            nextSeed = nextSeed + 2;
        }
        // Try to place last 2 rooms if needed.
            if (LengthSum < 56)
            { 
                RoomSeed = CreateRoom(floor, WidthSum, LengthSum, nextSeed);
                LengthSum = LengthSum + RoomSeed + 1;
                nextSeed = nextSeed + 2;
                if (LengthSum < 56)
                { 
                    RoomSeed = CreateRoom(floor, WidthSum, LengthSum, nextSeed);
                    LengthSum = LengthSum + RoomSeed + 1;
                    nextSeed = nextSeed + 2;
                }
            }
        LengthSum = 0;
        WidthSum += 14;
        roomsNotPlaced++;
        
    }
    PlaceMonsters(floor, 69);
    PrintFloor(floor);
    // Start the event logger in GamePanel
    enableRawMode();
    // Player starting position.
    Move(floor, 61, 67, '.');
    FreeUpRoom(floor, 100);
    disableRawMode();
    return 0;
}
