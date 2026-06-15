#include <rogue.h>

/* Create a dynamic list of monsters.*/
Entity* MonsterList(int n_monsters) {
    /* Create an Array to hold our Monster Structs. */
    /* Can be accessed anywhere with mptr declared below. */
    Entity* mptr;
    mptr = (Entity *)calloc(n_monsters, sizeof(Entity));
    return mptr; // return pointer to the array.
}

void AggroMove(Entity* mptr) {

    /* If they are in both LOS and range, move towards them. */
    if (CheckAggro(mptr, player)) {
        mptr->playerLastPos.x = player->pos.x;
        mptr->playerLastPos.y = player->pos.y;
        mptr->hasMoved = MoveTowards(mptr, player->pos);
        mptr->aggroFlag = true;
    }

    /* If they are not in LOS/Range but are still aggro, move towards last seen position.*/
    /* lastPos > 0 means a players was last seen at that x/y location. */
    else if (mptr->aggroFlag && (mptr->playerLastPos.x != mptr->pos.x || mptr->playerLastPos.y != mptr->pos.y)){
        if(CheckAggro(mptr, player)) {
            mptr->playerLastPos.x = player->pos.x;
            mptr->playerLastPos.y = player->pos.y;
            mptr->hasMoved = MoveTowards(mptr, (mptr->playerLastPos));
            mptr->aggroFlag = true;
        }
        else {
            mptr->hasMoved = MoveTowards(mptr, (mptr->playerLastPos));
            mptr->aggroFlag = true;
        }
    }

    else {
        mptr->playerLastPos.x = 0;
        mptr->playerLastPos.y = 0; 
        mptr->aggroFlag = false;
    }
}

/* Check if a monster has LOS of player and is in their aggro range, or if player was seen previously.*/
bool CheckAggro(Entity* mptr, Player* player) {
    if (GetDistance(mptr->pos, player->pos) < mptr->aggroRange && LineOfSight(mptr->pos, player->pos)) {
        return true;
    }
    return false;
}

/* returns i value of closest monster */
/* use this to find an int to add to mptr to get the monster */
int FindClosestMonster(Entity* mptr, int n_monsters) {
    int closestMonster = 0;
    int closest = GetDistance(player->pos, (mptr)->pos);
    int temp = 0;
    for (int i = 0; i < n_monsters; i++) {
        if(((mptr + i)->visible) && GetDistance(player->pos, (mptr + i)->pos) <= 15 && ((mptr + i)->isMonster == true)) {
            temp = GetDistance(player->pos, (mptr + i)->pos);
            if(temp <= closest) {
                closest = temp;
                closestMonster = i;
            }
        }
    }
    /* no monsters in LOS*/
    /* returns a floor entity */
    if (closest == GetDistance(player->pos, (mptr)->pos) && !LineOfSight(player->pos, (mptr)->pos)){
        return -2;
    }
    if ((mptr + closestMonster)->isMonster){
        return (closestMonster);
    }

    return -2;
    
}

Entity* FindMonsterInList(int monsterID, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        // Monster found
        if(monsterID == mptr[i].entityID) {
            return (mptr + i);
        }
    }

    return NULL;
}


/* returns true if entity moved towards given coords.*/
bool MoveTowards(Entity* entity, Position pos) {
    int x = entity->pos.x;
    int y = entity->pos.y;
    if (!CheckPlayerAdjacent(entity->pos)) {
        // up and left
        // up & left
        if (y > pos.y && x > pos.x) {
            if ((map[entity->pos.y - 1][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved)){
                MoveUpLeft(entity);
                KeepMonsterIntegrity(entity);
                map[entity->pos.y + 1][entity->pos.x + 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateMonsterVisible(entity, player);
                return true;
            }
        }
        // down & left
        else if (y < pos.y && x > pos.x) {
            if ((map[entity->pos.y + 1][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved)){
                MoveDownLeft(entity);
                KeepMonsterIntegrity(entity);
                map[entity->pos.y - 1][entity->pos.x + 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateMonsterVisible(entity, player);
                return true;
            }
        }
        // down & right
        else if (y < pos.y && x < pos.x) {
            if ((map[entity->pos.y + 1][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved)){
                MoveDownRight(entity);
                KeepMonsterIntegrity(entity);
                map[entity->pos.y - 1][entity->pos.x - 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateMonsterVisible(entity, player);
                return true;
            }
        }
        // move up & right
        else if (y > pos.y && x < pos.x) {
            if ((map[entity->pos.y - 1][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved)){
                MoveUpRight(entity);
                KeepMonsterIntegrity(entity);
                map[entity->pos.y + 1][entity->pos.x - 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateMonsterVisible(entity, player);
                return true;
            }
        }
        //move up, y--
        if (y > pos.y) {
            if ((map[entity->pos.y - 1][(entity->pos.x)].noCollision) && (!entity->hasMoved)){
                MoveUp(entity);
                KeepMonsterIntegrity(entity);
                map[entity->pos.y + 1][entity->pos.x] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateMonsterVisible(entity, player);
                return true;
            }
        }
        //move left, x--
        else if (x > pos.x) {
            if ((map[entity->pos.y][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved)){
                MoveLeft(entity);
                KeepMonsterIntegrity(entity);
                map[entity->pos.y][entity->pos.x + 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateMonsterVisible(entity, player);
                return true;
            }
        }
        //move down, y++
        else if (y < pos.y) {
            if ((map[entity->pos.y + 1][(entity->pos.x)].noCollision) && (!entity->hasMoved)){
                MoveDown(entity);
                KeepMonsterIntegrity(entity);
                map[entity->pos.y - 1][entity->pos.x] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateMonsterVisible(entity, player);
                return true;
            }
        }
        //move right, x++
        else if (x < pos.x) {
            if ((map[entity->pos.y][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved)){
                MoveRight(entity);
                KeepMonsterIntegrity(entity);
                map[entity->pos.y][entity->pos.x - 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateMonsterVisible(entity, player);
                return true;
            }
        }
    }
    UpdateMonsterVisible(entity, player);
    return false;
}

/* update monster positions on map from mptr. */
void UpdateMonsterMap(Entity* monster, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        int y, x;
        y = (monster + i)->pos.y;
        x = (monster + i)->pos.x;
        // If monster, stay as monster
        if((monster + i)->isMonster) {
            map[y][x] = monster[i];
        }
        // If corpse, stay as a corpse.
        if(!((monster + i)->isMonster) && !(map[y][x].isMonster)) {
            map[y][x] = monster[i];
        }
    }
}

// /* update monster list based on map*/
// void UpdateMonsterCorpses(Entity* monster, int n_monsters) {
//     for (int i = 0; i < n_monsters; i++) {
//         int y, x;
//         y = monster[i].pos.y;
//         x = monster[i].pos.x;
//         if((map[y][x]).isMonster && !(monster[i].isMonster)) {
//             monster[i] = map[y][x];
//         }
//     }
// }

/* Credit to Harpy for helping me prototype this function. */
/* This would have taken signifiantly longer without her, I owe her a case of monster for this.*/
/* Monster attempts to move to a new tile chosen at random. */
/* If legal spot, monster moves, then updates the previous square they moved from. */
/* KeepMonsterIntegrity ensures the previous tile keeps all prior visible and seen values. */
void Wander(Entity* mptr){
    int randDirection = (rand() % 4); //0-3
    switch(randDirection) {
        //move up
        case 0:
        //newPOS.y--;
            if ((map[mptr->pos.y - 1][(mptr->pos.x)].noCollision) && (!mptr->hasMoved)){
                MoveUp(mptr);
                KeepMonsterIntegrity(mptr);
                // set new location to old location (have mptr still)
                map[mptr->pos.y + 1][mptr->pos.x] = map[mptr->pos.y][mptr->pos.x];
                //finally set new location to mptr
                }
        break;
        //move down
        case 1:
            //newPOS.y++;
            if ((map[mptr->pos.y + 1][(mptr->pos.x)].noCollision) && (!mptr->hasMoved)){
                MoveDown(mptr);
                KeepMonsterIntegrity(mptr);
                map[mptr->pos.y - 1][mptr->pos.x] = map[mptr->pos.y][mptr->pos.x];
            }
        break;
        //move left
        case 2:
            //newPOS.x--;
            if ((map[mptr->pos.y][(mptr->pos.x - 1)].noCollision) && (!mptr->hasMoved)){
                MoveLeft(mptr);
                KeepMonsterIntegrity(mptr);
                map[mptr->pos.y][mptr->pos.x + 1] = map[mptr->pos.y][mptr->pos.x];
            }
        break;
        //move right
        case 3:
        //newPOS.x++;
            if ((map[mptr->pos.y][(mptr->pos.x + 1)].noCollision) && (!mptr->hasMoved)){
                MoveRight(mptr);
                KeepMonsterIntegrity(mptr);
                map[mptr->pos.y][mptr->pos.x - 1] = map[mptr->pos.y][mptr->pos.x];
            }
        break;
        default:
        break;
    }
    map[mptr->pos.y][mptr->pos.x] = *mptr;
    UpdateMonsterVisible(mptr, player);

    /* If they move in range of the player, set aggro flag.*/
    if ((!(mptr)->aggroFlag)){
        (mptr)->aggroFlag = CheckAggro((mptr), player);
    }
}

void KeepMonsterIntegrity(Entity* mptr) {
    // if new has been seen before fix mptr/old location
    if (mptr->mapInfo.newSeen == true){
        mptr->seen = true;
        KeepMonsterMapIntegrity(mptr);
    }
    if (mptr->mapInfo.newSeen == false) {
        mptr->seen = false;
        KeepMonsterMapIntegrity(mptr);
    }
    if (mptr->mapInfo.newVisible == true) {
        mptr->seen = true;
        KeepMonsterMapIntegrity(mptr);
    }                
}

void KeepMonsterMapIntegrity(Entity* mptr) {
    if (mptr->mapInfo.oldSeen == false){
        map[mptr->pos.y][mptr->pos.x].seen = false;
    }
    if (mptr->mapInfo.oldSeen == true){
        map[mptr->pos.y][mptr->pos.x].seen = true;
    }
    if (mptr->mapInfo.oldVisible == false) {
        map[mptr->pos.y][mptr->pos.x].visible = false;
    }
    if (mptr->mapInfo.oldVisible == true) {
        map[mptr->pos.y][mptr->pos.x].visible = false;
    }
}

void UpdateMonsterVisible(Entity* monster, Player* player){
    if(LineOfSight(monster->pos, player->pos) && 
    GetDistance(monster->pos, player->pos) < 15) {
        monster->visible = true;
        monster->seen = true;
        map[monster->pos.y][monster->pos.x].visible = true;
        monster->ch = monster->staticCh;
        map[monster->pos.y][monster->pos.x].ch = monster->ch;
        RecordMonsterSeen(monster);
        if (GetDistance(monster->pos, player->pos) < 6) {
            monster->transparent = true;
        }
        else {
            monster->transparent = false;
        } 
    }
    else {
        monster->visible = false;
        monster->transparent = false;
        map[monster->pos.y][monster->pos.x].visible = false;

    }
 }

void ResetMoveFlags(Entity* mptr, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        mptr[i].hasMoved = false;
    }
}

void RecordMonsterSeen(Entity* monster) {
    if(!monster->seenByPlayer){
        strcpy(combatHistory->event, "You see a ");
        strcat(combatHistory->event, monster->entityName);
        strcat(combatHistory->event, " to the ");
        QueueEvent(q, combatHistory->event);
        strcpy(combatHistory->event, DIRECTIONS[MonsterDirection(monster)]);
        strcat(combatHistory->event, ".");
        QueueEvent(q, combatHistory->event);
        monster->seenByPlayer = true;
    }
}

/* Returns an int representing the monsters direction relative to the player. */
int MonsterDirection(Entity* monster) {
    if((player->pos.x) < (monster->pos.x) && (player->pos.y) < (monster->pos.y)) {
        return SOUTH_EAST;
    }
    else if ((player->pos.x) < (monster->pos.x) && (player->pos.y) > (monster->pos.y)) {
        return NORTH_EAST;
    }
    else if ((player->pos.x) > (monster->pos.x) && (player->pos.y) > (monster->pos.y)) {
        return NORTH_WEST;
    }
    else if ((player->pos.x) > (monster->pos.x) && (player->pos.y) < (monster->pos.y)) {
        return SOUTH_WEST;
    }
    else if ((player->pos.x) < (monster->pos.x) && (player->pos.y) == (monster->pos.y)) {
        return EAST;
    }
    else if ((player->pos.x) > (monster->pos.x) && (player->pos.y) == (monster->pos.y)) {
        return WEST;
    }
    else if ((player->pos.x) == (monster->pos.x) && (player->pos.y) < (monster->pos.y)) {
        return SOUTH;
    }
    else if ((player->pos.x) == (monster->pos.x) && (player->pos.y) > (monster->pos.y)) {
        return NORTH;
    } else {
        // Should never occur
        return NORTH;
    }
}