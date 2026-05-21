#include <rogue.h>

Entity** CreateEntities(void) {
    Entity** map = calloc(MAP_HEIGHT, sizeof(Entity *));


    /* Change amount of wall entities created based on map dimensions. */ 
    for (int y = 0; y < MAP_HEIGHT; y++) {
        map[y] = calloc(MAP_WIDTH, sizeof(Entity));
        for (int x = 0 ; x < MAP_WIDTH; x++) {
            map[y][x].ch = '#';
            map[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
            map[y][x].aggroFlag = false;
            map[y][x].hasMoved = false;
            map[y][x].noCollision = false;
            map[y][x].transparent = false;
            map[y][x].seen = false;
            map[y][x].visible = false;
            map[y][x].entityAggroRange = 0;
            map[y][x].entityID = 1;
            map[y][x].entityStats.CHA = 0;
            map[y][x].entityStats.CON = 0;
            map[y][x].entityStats.DEX = 0;
            map[y][x].entityStats.INT = 0;
            map[y][x].entityStats.STR = 0;
            map[y][x].entityStats.WIS = 0;
            map[y][x].entityStats.AC = 30;
            map[y][x].entityStats.HP = 1000;
            map[y][x].entityStats.LVL = 0;
            map[y][x].entityStats.maxDMG = 0;
            map[y][x].entityStats.minDMG = 0;
            strcpy(map[y][x].entityArmor, "None");
            strcpy(map[y][x].entityClass, "None");
            strcpy(map[y][x].entityName, "Stone Wall");
            strcpy(map[y][x].entityRace, "None");
            strcpy(map[y][x].entityWeapon, "None");
        }
    }
    /* Return a 2D arr thats a pointer that points at pointers that point to our wall entities. */ 
    return map;
}

/* 
Fills map with randomly sized rooms full of dots. 
Place a monster in the center of the room as well.
Since rooms can currently overlap, this appears as random monster placement.
*/ 
Position SetupMap(Entity* mptr, int n_rooms) {
    int y, x, height, width, n_monsters;
    Room* rooms = calloc(n_rooms, sizeof(Room));
    Position start_pos;
    

    for (int i = 0; i < n_rooms; i++) {
        // left corner of room.
        y = (rand() % (MAP_HEIGHT - 15)) + 1; // 1-15
        x = (rand() % (MAP_WIDTH - 25)) + 1; // 1-80
        height = (rand() % 7) + 3; // 3-9
        width = (rand() % 15) + 5;// 5-19

        rooms[i] = CreateRoom(y, x, height, width);

        
        
        /* Add the created room to the map */
        AddRoomToMap(rooms[i]);


        /* If not the first room, run this to create hallways. */ 
        if (i > 0) {
            start_pos.y = rooms[i - 1].center.y;
            start_pos.x = rooms[i - 1].center.x;
            ConnectRooms(rooms[i-1].center, rooms[i].center);
            int monsterID = i + 1;
            /* Add 10-20 monsters to the map. with monster.c's AddMonster. */
            /* Create and save monsters to use later. */
            n_monsters = (rand() % 4);
            mptr[i - 1] = AssignMonster(rooms[i].center, n_monsters, monsterID); 

            /* Use the list of monsters we just made and move them to our 2D matrix of entities.*/
            UpdateMonsterMap(mptr, n_rooms - 1);
        }
    }

    start_pos.y = rooms[0].center.y;
    start_pos.x = rooms[0].center.x;
    free(rooms);
    return start_pos;
}

void FreeMap(void) {
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        free(map[y]);
    }
    free(map);
}

/* Prevent rooms from overlapping if desired. */
// bool roomOverlaps(Room* rooms, int rooms_counter, int y, int x, int height, int width) {
//   for (int i = 0; i < rooms_counter; i++) {
//     if (x >= rooms[i].pos.x + rooms[i].width || rooms[i].pos.x >= x + width) {
//       continue;
//     }
//     if (y + height <= rooms[i].pos.y || rooms[i].pos.y + rooms[i].height <= y) {
//       continue;
//     }

//     return true;
//   }

//   return false;
// }