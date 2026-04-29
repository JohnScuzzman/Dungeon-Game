#include "tables.h"

int main() {
    RNG();
    int LengthSum = 0;
    int WidthSum = 0;
    int RoomSeed = 0;
    int nextSeed = 0;
    int **floor1 = CreateFloor(100, 100);
    int **floor2 = CreateFloor(100, 100);
    int roomsNotPlaced = 0;

    while (roomsNotPlaced < 4)
    {
        
        // For loop for speed
        for (int i = 0; i < 5; i++) {
            RoomSeed = CreateRoom(floor1, floor2, WidthSum, LengthSum, nextSeed);
            LengthSum = LengthSum + RoomSeed + 1;
            nextSeed = nextSeed + 2;
        }
        // Try to place last 2 rooms if needed.
            if (LengthSum < 56)
            { 
                RoomSeed = CreateRoom(floor1, floor2, WidthSum, LengthSum, nextSeed);
                LengthSum = LengthSum + RoomSeed + 1;
                nextSeed = nextSeed + 2;
                if (LengthSum < 56)
                { 
                    RoomSeed = CreateRoom(floor1, floor2, WidthSum, LengthSum, nextSeed);
                    LengthSum = LengthSum + RoomSeed + 1;
                    nextSeed = nextSeed + 2;
                }
            }
        LengthSum = 0;
        WidthSum += 14;
        roomsNotPlaced++;
        
    }

    // Place monsters and print the floor & UI.
    PlaceMonsters(floor1, floor2, 69);

    // Begin Main Game loop.
    Move(floor1, floor2, 61, 67, 0);
    FreeUpRoom(floor2, 100);
    FreeUpRoom(floor1, 100);
    return 0;
}
