#include "tables.h"

int main() {
    RNG();
    int LengthSum = 0;
    int WidthSum = 0;
    int RoomSeed = 0;
    int nextSeed = 0;
    char **floor = CreateFloor(100, 100);
    int monsterFloor[100][100];
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

    // Place monsters and print the floor & UI.
    PlaceMonsters(floor, monsterFloor, 69);
    // Begin Main Game loop.
    Move(floor, 61, 67, '.');
    FreeUpRoom(floor, 100);

    return 0;
}
