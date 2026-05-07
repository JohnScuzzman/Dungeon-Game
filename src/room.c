#include <rogue.h>

// Create a room passed from SetupMap in map.c
Room CreateRoom(int y, int x, int height, int width)
{
    Room newRoom;
    newRoom.pos.y = y;
    newRoom.pos.x = x;
    newRoom.height = height;
    newRoom.width = width;
    newRoom.center.y = y + (int)(height / 2);
    newRoom.center.x = x + (int)(width / 2);
    return newRoom;
}

// Hallway Generator.
// Recieves two room centers and tries to draw a hallway between them.
// Substracts 1 from temp.x, getting the difference between new x position and x position of the second room, centerTwo.x
// Then compares this number with the difference between the current temp.x and centerTwo.x.
// Then uses the abs() function on both sides to get a positive integer. 
// If the left side of the equation gives a smaller number than the right side,
// that means that by decreasing the x value of the first room's center, 
// we are getting closer to the center of the second room. 
// If that is the case, then the if statement condition is true and it runs.
void ConnectRooms(Position centerOne, Position centerTwo)
{ 
    // Temp is used at the end of each step to draw the next hallway tile.
    Position temp;
    temp.x = centerOne.x;
    temp.y = centerOne.y;

    while (true)
    { 
    // checks to see whether subtracting 1 
    // to the x of our temp variable creates a
    //  position which is closer to our second room center.
    if (abs((temp.x - 1) - centerTwo.x) < abs(temp.x - centerTwo.x))
        temp.x--;
    else if (abs((temp.x + 1) - centerTwo.x) < abs(temp.x - centerTwo.x))
        temp.x++;
    else if (abs((temp.y + 1) - centerTwo.y) < abs(temp.y - centerTwo.y))
        temp.y++;
    else if (abs((temp.y - 1) - centerTwo.y) < abs(temp.y - centerTwo.y))
        temp.y--;
    else
        break;

    map[temp.y][temp.x].ch = '.';
    map[temp.y][temp.x].noCollision = true;
    map[temp.y][temp.x].transparent = true;
    }
} 

// Fills the room with dots, effectively adding it to the map.
void AddRoomToMap(Room room)
{
  for (int y = room.pos.y; y < room.pos.y + room.height; y++)
  {
    for (int x = room.pos.x; x < room.pos.x + room.width; x++)
        {
            map[y][x].ch = '.';
            map[y][x].noCollision = true;
            map[y][x].transparent = true;
        }

    }
}

// Adds a monster to the map based on preset coordinates.
void AddMonster(Monster monster) {
    map[monster.pos.y][monster.pos.x].ch = monster.ch;
    map[monster.pos.y][monster.pos.x].noCollision = false;
    map[monster.pos.y][monster.pos.x].transparent = true;
}

