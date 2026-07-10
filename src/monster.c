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
    int closestDist = 16; //RADIUS + 1
    int tempDist = 0;
    for (int i = 0; i < n_monsters; i++) {
        if (CheckPlayerAdjacent((mptr + i)->pos) && (mptr + i)->entityType == MONSTER) return i;
        else if(((mptr + i)->visible) && ((mptr + i)->entityType == MONSTER)) {
            tempDist = GetDistance(player->pos, (mptr + i)->pos);
            if(tempDist <= closestDist) {
                closestDist = tempDist;
                closestMonster = i;
            }
        }
    }
    /* no monsters in LOS*/
    /* returns a floor entity */
    if (((mptr + closestMonster)->entityType == MONSTER) && ((mptr + closestMonster)->visible)){
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

/* update monster positions on map from mptr. */
/* update corpses, then monsters to place them on top. */
void UpdateMonsterMap(Entity* monster, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        int y, x;
        y = (monster + i)->pos.y;
        x = (monster + i)->pos.x;
        /* Draw monsters that died ontop of other monsters */
        if((monster + i)->entityType == CORPSE && !(monster + i)->wasReplaced && map[y][x].wasLooted) {
            map[y][x].wasLooted = false;
            monster[i] = map[y][x];
            map[y][x] = monster[i];
        }
        else if((monster + i)->entityType == CORPSE && !(monster + i)->wasReplaced && !map[y][x].wasLooted && map[y][x].entityType == FLOOR) {
            map[y][x] = monster[i];
        }
    }
    for (int i = 0; i < n_monsters; i++) {
        int y, x;
        y = (monster + i)->pos.y;
        x = (monster + i)->pos.x;
        if((monster + i)->entityType == MONSTER) map[y][x] = monster[i];
    }
}

// /* update monster list based on map*/
// void UpdateMonsters(Entity* monster, int n_monsters) {
//     for (int i = 0; i < n_monsters; i++) {
//         int y, x;
//         y = monster[i].pos.y;
//         x = monster[i].pos.x;
//         monster[i] = map[y][x];
//     }
// }


/* Credit to Harpy for helping me prototype this function. */
/* This would have taken signifiantly longer without her, I owe her a case of monster for this.*/
/* Monster attempts to move to a new tile chosen at random. */
/* If legal spot, monster moves, then updates the previous square they moved from. */
/* KeepNPCIntegrity ensures the previous tile keeps all prior visible and seen values. */
void Wander(Entity* mptr){
    int randDirection = (rand() % 4); //0-3
    switch(randDirection) {
        //move up
        case 0:
        //newPOS.y--;
            if ((map[mptr->pos.y - 1][(mptr->pos.x)].noCollision) && (!mptr->hasMoved)){
                MoveUp(mptr);
                KeepNPCIntegrity(mptr);
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
                KeepNPCIntegrity(mptr);
                map[mptr->pos.y - 1][mptr->pos.x] = map[mptr->pos.y][mptr->pos.x];
            }
        break;
        //move left
        case 2:
            //newPOS.x--;
            if ((map[mptr->pos.y][(mptr->pos.x - 1)].noCollision) && (!mptr->hasMoved)){
                MoveLeft(mptr);
                KeepNPCIntegrity(mptr);
                map[mptr->pos.y][mptr->pos.x + 1] = map[mptr->pos.y][mptr->pos.x];
            }
        break;
        //move right
        case 3:
        //newPOS.x++;
            if ((map[mptr->pos.y][(mptr->pos.x + 1)].noCollision) && (!mptr->hasMoved)){
                MoveRight(mptr);
                KeepNPCIntegrity(mptr);
                map[mptr->pos.y][mptr->pos.x - 1] = map[mptr->pos.y][mptr->pos.x];
            }
        break;
        default:
        break;
    }
    map[mptr->pos.y][mptr->pos.x] = *mptr;
    UpdateNPCVisible(mptr, player);

    /* If they move in range of the player, set aggro flag.*/
    if ((!(mptr)->aggroFlag)){
        (mptr)->aggroFlag = CheckAggro((mptr), player);
    }
}



void ResetMoveFlags(Entity* mptr, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        mptr[i].hasMoved = false;
    }
}
