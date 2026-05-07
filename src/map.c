#include <rogue.h>
Tile** CreateTiles(void)
{
    Tile** tiles = calloc(MAP_HEIGHT, sizeof(Tile *));


    // Change amount of tiles created based on map dimensions.
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        tiles[y] = calloc(MAP_WIDTH, sizeof(Tile));
        for (int x = 0 ; x < MAP_WIDTH; x++)
        {
            tiles[y][x].ch = '#';
            tiles[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
            tiles[y][x].noCollision = false;
            tiles[y][x].transparent = false;
            tiles[y][x].visible = false;
            tiles[y][x].seen = false;
        }
    }

    // Return a 2D arr thats a pointer that points at pointers that point to tiles.
    return tiles;
}

// Fill map with dots and rooms.
Position SetupMap(void)
{
    int y, x, height, width, n_rooms;
    // random number between 10 and 20.
    n_rooms =  (rand() % 11) + 10;
    Room* rooms = calloc(n_rooms, sizeof(Room));
    Monster* monsters = calloc(n_rooms, sizeof(Monster));
    Position start_pos;
    

  for (int i = 0; i < n_rooms; i++)
  {
    // define upper left corner of room
    // 1-15
    y = (rand() % (MAP_HEIGHT - 15)) + 1;
    // 1-80
    x = (rand() % (MAP_WIDTH - 25)) + 1;


    // 3-9
    height = (rand() % 7) + 3;

    // 5-19
    width = (rand() % 15) + 5;

    rooms[i] = CreateRoom(y, x, height, width);
    monsters[i] = CreateMonster(rooms[i].center, 'G'); // Create just goblins for now.
    
    
    AddRoomToMap(rooms[i]);

    //Add 10-20 goblins to the map.

    // If not the first room, run this to create hallways.
    if (i > 0)
    {
        start_pos.y = rooms[i].center.y;
        start_pos.x = rooms[i].center.x;
        ConnectRooms(rooms[i-1].center, rooms[i].center);
        //Add 10-20 goblins to the map.
        AddMonster(monsters[i]);
    }
  }

    start_pos.y = rooms[0].center.y;
    start_pos.x = rooms[0].center.x;
    free(monsters);
    free(rooms);
    return start_pos;
}

// USE FOR PREVENTING ROOMS FROM OVERLAPPING.
// bool roomOverlaps(Room* rooms, int rooms_counter, int y, int x, int height, int width)
// {
//   for (int i = 0; i < rooms_counter; i++)
//   {
//     if (x >= rooms[i].pos.x + rooms[i].width || rooms[i].pos.x >= x + width)
//     {
//       continue;
//     }
//     if (y + height <= rooms[i].pos.y || rooms[i].pos.y + rooms[i].height <= y)
//     {
//       continue;
//     }

//     return true;
//   }

//   return false;
// }

void FreeMap(void)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        free(map[y]);
    }
    free(map);
}
