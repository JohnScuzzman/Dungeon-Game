#include <rogue.h>

DungeonInfo* MakeDungeonInfo(){
    DungeonInfo* info;
    info = calloc(1, sizeof(DungeonInfo));
    info->currentFloor = 1;
    return info;
}

/* 
Fills map with randomly sized rooms full of dots. 
Place a monster in the center of the room as well.
Since rooms can currently overlap, this appears as random monster placement.
*/ 
Position SetupMap(Entity* mptr, int n_rooms) {
    int y, x, height, width, n_monsters, addChest;
    int spawnCeiling = MonsterSpawnCeiling(dungeonInfo->currentFloor);
    int spawnFloor = MonsterSpawnFloor(dungeonInfo->currentFloor);
    Room* rooms = calloc(n_rooms, sizeof(Room));
    Position start_pos;

    for (int i = 0; i < n_rooms; i++) {
        // left corner of room.
        y = (rand() % (MAP_HEIGHT - 15)) + 1; // 1-35
        x = (rand() % (MAP_WIDTH - 25)) + 1; // 1-100
        height = (rand() % 7) + 3; // 3-7
        width = (rand() % 15) + 5;// 5-15
        addChest = (rand() % 5) + 1; // 1-5

        rooms[i] = CreateRoom(y, x, height, width);
        
        /* Add the created room to the map */
        AddRoomToMap(rooms[i]);

        /* If not the first room, run this to create hallways. */ 
        if (i > 0) {
            int monsterID = i + 1;
            int monsterType = (rand() % spawnCeiling) + spawnFloor; // currently 1 to 5 if below level 3
            start_pos.y = rooms[i - 1].center.y;
            start_pos.x = rooms[i - 1].center.x;
            ConnectRooms(rooms[i - 1].center, rooms[i].center);
           
            /* Add 10-20 monsters to the map. with monster.c's AddMonster. */
            /* Create and save monsters to use later. */
            mptr[i - 1] = AssignMonster(rooms[i].center, monsterType, monsterID); 

            /* Use the list of monsters we just made and move them to our 2D matrix of entities.*/
            UpdateMonsterMap(mptr, monsterType);
            if (addChest == 5) AddChestToRoom(rooms[i].center, width, height);
        }
    }
    // Place the door to the next dungeon floor in the last made room.
    AssignStairsDown(rooms[n_rooms - 1].center.x + 1, rooms[n_rooms - 1].center.y + 1);

    //Prepare to return players starting POS to main.c
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

void MakeNewLevel(int* old_n_monsters) {
    for (int y = 0; y < MAP_HEIGHT; y++) { 
        for (int x = 0; x < MAP_WIDTH; x++) { 
            if (map[y][x].entityType == CORPSE) {
                AssignFloor(x, y);
            }
        }
    }
    

    for(int i = 0; i < *old_n_monsters; i++) {
        AssignFloor((mptr + i)->pos.x, (mptr + i)->pos.y);
        mptr[i] = map[(mptr + i)->pos.y][(mptr + i)->pos.x];
    }

    Position start_pos;
    int n_rooms =  (rand() % 11) + 10;
    *old_n_monsters = n_rooms - 1;
    /* Create our map using function in map.c*/
    map = CreateEntities();

    free(mptr);

    /* Make # of rooms -1 number of monsters. */
    /* Point mptr at monsterlist[0]. */
    mptr = MonsterList(*old_n_monsters);

    /* Create a starting position for player and setup the floor in map.c*/
    /* Pass the monsterList to populate it.*/
    start_pos = SetupMap(mptr, n_rooms);

    /* Place player */
    player->pos.y = start_pos.y;
    player->pos.x = start_pos.x;
    AssignFloor(start_pos.x, start_pos.y);
}

// returns max - min + 1 to get ceiling
int MonsterSpawnCeiling(int dungeonFloor) {
    for (int i = dungeonFloor; i < MAX_DUNGEON_FLOORS; i++) {
        if (i <= 1) return (GOBLIN_RANGER - RAT) + 1;
        if (i <= 6) return (SKELETON_WARRIOR - RAT) + 1;
        else {
            return (SKELETON_WARRIOR - RAT) + 1;
        }
    }
}

int MonsterSpawnFloor(int dungeonFloor) {
    for (int i = dungeonFloor; i < MAX_DUNGEON_FLOORS; i++) {
        if (i <= 2) return RAT;
        if (i <= 6) return GOBLIN_WARRIOR;
        else {
            return GOBLIN_WARRIOR;
        }
    }
}

// /* return farthest unexplored region in players FOV. */
// /* return monsters pos if monster found. */
// /* return players pos if no valid unexplored tile.*/
// Position FindClosestUnexplored() {
//     int y, x, distance;
// 	Position target;

//     for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++) { 
//             for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++) { 
//                 target.y = y;
//                 target.x = x;
//                 distance = GetDistance(player->pos, target);
//                 if (distance < RADIUS && IsInMap(y, x) && !(map[y][x].seen) && (map[y][x].ch == '.' && LineOfSight(player->pos, target))) { 
//                     if (map[y][x].entityID > 1) {
//                         target.x = x;
//                         target.y = y;
//                         return target;
//                     }
//                     target.x = x;
//                     target.y = y;
//                     return target;
//                 }
// 			} 
// 		} 
//     if (IsInMap(target.y, target.x)){
//         return(target);
//     }
//     return(FindClosestDoor());
// }


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

// Position FindClosestDoor() {
//     int y, x, distance;
// 	Position target;

//     for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++) { 
//             for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++) { 
//                 target.y = y;
//                 target.x = x;
//                 distance = GetDistance(player->pos, target);
//                 if(distance < RADIUS && IsInMap(y, x) && (map[y][x].entityID == 0)){
//                     if ((map[y + 1][x].entityID == 1 && map[y - 1][x].entityID == 1)) {
//                         target.x = x;
//                         target.y = y;	
//                         if (IsInMap(target.y, target.x)){
//                             return(target);
//                         }
//                     }
//                     if ((map[y][x + 1].entityID == 1 && map[y][x - 1].entityID == 1)) {
//                         target.x = x;
//                         target.y = y;	
//                         if (IsInMap(target.y, target.x)){
//                             return(target);
//                         }
//                     }
//                 }  
//             }
// 		} 
//     return(FindClosestUnexplored());
// }