#include <rogue.h>

void AggroMove(Entity* mptr) {
    /* If they are in both LOS and range, move towards them. */
    bool isAggro = CheckAggro(mptr, player);
    if (isAggro) {
        mptr->hasMoved = MoveTowards(mptr, player->pos);
    }

    /* If they are not in LOS/Range but are still aggro, move towards last seen position.*/
    /* lastPos > 0 means a players was last seen at that x/y location. */
    else if (!isAggro && mptr->playerLastPos.x > 0 && mptr->playerLastPos.y > 0) {
        mptr->hasMoved = MoveTowards(mptr, mptr->playerLastPos);
    }

    /* if we get here, mptr has navigated to players last POS*/
    else if (!isAggro && mptr->playerLastPos.x == mptr->pos.x && mptr->playerLastPos.y == mptr->pos.y){
        /* Check if player is in sight again */ 
        isAggro = CheckAggro(mptr, player);
        if(isAggro) {
            mptr->aggroFlag = true; 
        }
        else {
            mptr->aggroFlag = false; 
        }
    }
}


/* Check if a monster has LOS of player and is in their aggro range.*/
bool CheckAggro(Entity* mptr, Player* player) {
    if (mptr->aggroFlag) {
        return true;
    }
    if (GetDistance(mptr->pos, player->pos) < mptr->aggroRange  && LineOfSight(mptr->pos, player->pos)) {
        mptr->aggroFlag = true;
        mptr->playerLastPos.x = player->pos.x;
        mptr->playerLastPos.y = player->pos.y;
        return true;
    }
    return false;
}


Entity* FindMonsterInList(int monsterID, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        // Monster found
        if(monsterID == mptr[i].entityID) {
            return (mptr + i);
        }
    }
}

/* Create a dynamic list of monsters.*/
Entity* MonsterList(int n_monsters) {
    /* Create an Array to hold our Monster Structs. */
    /* Can be accessed anywhere with mptr declared below. */
    Entity* mptr;
    mptr = (Entity *)malloc(n_monsters * sizeof(Entity));
    return mptr; // return pointer to the array.
}

/* returns true if entity moved towards given coords.*/
bool MoveTowards(Entity* entity, Position pos) {
    int x = entity->pos.x;
    int y = entity->pos.y;
    if (!CheckPlayerAdjacent(entity->pos)){
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
        if (x > pos.x) {
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
        if (y < pos.y) {
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
        if (x < pos.x) {
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
    return false;
}

/* update monster positions on map from mptr. */
void UpdateMonsterMap(Entity* monster, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        int y, x;
        y = monster[i].pos.y;
        x = monster[i].pos.x;
        map[y][x] = monster[i];
    }
}

/* update monster list based on map*/
void UpdateMonsters(Entity* monster, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        int y, x;
        y = monster[i].pos.y;
        x = monster[i].pos.x;
        monster[i] = map[y][x];
    }
}

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
                KeepMonsterMapIntegrity(mptr);
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
                KeepMonsterMapIntegrity(mptr);
                map[mptr->pos.y - 1][mptr->pos.x] = map[mptr->pos.y][mptr->pos.x];
            }
        break;
        //move left
        case 2:
            //newPOS.x--;
            if ((map[mptr->pos.y][(mptr->pos.x - 1)].noCollision) && (!mptr->hasMoved)){
                MoveLeft(mptr);
                KeepMonsterMapIntegrity(mptr);
                map[mptr->pos.y][mptr->pos.x + 1] = map[mptr->pos.y][mptr->pos.x];
            }
        break;
        //move right
        case 3:
        //newPOS.x++;
            if ((map[mptr->pos.y][(mptr->pos.x + 1)].noCollision) && (!mptr->hasMoved)){
                MoveRight(mptr);
                KeepMonsterMapIntegrity(mptr);
                map[mptr->pos.y][mptr->pos.x - 1] = map[mptr->pos.y][mptr->pos.x];
            }
        break;
        default:
        break;
    }
    map[mptr->pos.y][mptr->pos.x] = *mptr;
    UpdateMonsterVisible(mptr, player);
}

void KeepMonsterMapIntegrity(Entity* mptr) {
    // if new has been seen before fix mptr/old location
    if (mptr->mapInfo.newSeen == true){
        mptr->seen = true;
        KeepMonsterIntegrity(mptr);
    }
    if (mptr->mapInfo.newSeen == false) {
        mptr->seen = false;
        KeepMonsterIntegrity(mptr);
    }
    if (mptr->mapInfo.newVisible == true) {
        mptr->seen = true;
        KeepMonsterIntegrity(mptr);
    }                
}

void KeepMonsterIntegrity(Entity* mptr) {
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

void ResetMoveFlags(Entity* monster, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        monster[i].hasMoved = false;
    }
}

void MoveUp(Entity* mptr){
    mptr->pos.y = mptr->pos.y - 1;
    mptr->hasMoved = true;
    mptr->mapInfo.oldSeen = map[mptr->pos.y + 1][mptr->pos.x].seen;
    mptr->mapInfo.newSeen = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldVisible = map[mptr->pos.y + 1][mptr->pos.x].seen;
    mptr->mapInfo.newVisible = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldChar = map[mptr->pos.y + 1][mptr->pos.x].ch;
    mptr->mapInfo.newChar = map[mptr->pos.y][mptr->pos.x].ch;
    if (mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->mapInfo.oldChar;
    }
}


void MoveDown(Entity* mptr){
    mptr->pos.y = mptr->pos.y + 1;
    mptr->hasMoved = true;
    mptr->mapInfo.oldSeen = map[mptr->pos.y - 1][mptr->pos.x].seen;
    mptr->mapInfo.newSeen = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldVisible = map[mptr->pos.y - 1][mptr->pos.x].seen;
    mptr->mapInfo.newVisible = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldChar = map[mptr->pos.y - 1][mptr->pos.x].ch;
    mptr->mapInfo.newChar = map[mptr->pos.y][mptr->pos.x].ch;
    if (mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->mapInfo.oldChar;
    }
}


void MoveLeft(Entity* mptr){
    mptr->pos.x = mptr->pos.x - 1;
    mptr->hasMoved = true;
    mptr->mapInfo.oldSeen = map[mptr->pos.y][mptr->pos.x + 1].seen;
    mptr->mapInfo.newSeen = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldVisible = map[mptr->pos.y][mptr->pos.x + 1].seen;
    mptr->mapInfo.newVisible = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldChar = map[mptr->pos.y][mptr->pos.x + 1].ch;
    mptr->mapInfo.newChar = map[mptr->pos.y][mptr->pos.x].ch;
    if (mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->mapInfo.oldChar;
    }
}


void MoveRight(Entity* mptr){
    mptr->pos.x = mptr->pos.x + 1;
    mptr->hasMoved = true;
    mptr->mapInfo.oldSeen = map[mptr->pos.y][mptr->pos.x - 1].seen;
    mptr->mapInfo.newSeen = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldVisible = map[mptr->pos.y][mptr->pos.x - 1].seen;
    mptr->mapInfo.newVisible = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldChar = map[mptr->pos.y][mptr->pos.x - 1].ch;
    mptr->mapInfo.newChar = map[mptr->pos.y][mptr->pos.x].ch;
    if (mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->mapInfo.oldChar;
    }
}


        /* TO ADD DIAGONAL MOVEMENT IN THE FUTURE USE THESE AND ADD enty->pos.x == x to the above. */

        // // Diag down right, x++, y++
        // if (x < pos.x && y < pos.y) {
        //     if ((map[entity->pos.y + 1][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved)){
        //         MoveDiagRight(entity);
        //         KeepMonsterIntegrity(entity);
        //         map[entity->pos.y - 1][entity->pos.x - 1] = map[entity->pos.y][entity->pos.x];
        //         map[entity->pos.y][entity->pos.x] = *entity;
        //         UpdateMonsterVisible(entity, player);
        //         return true;
        //     }
        // }
        // // Diag down left, x--, y++
        // if (x > pos.x && y < pos.y) {
        //     if ((map[entity->pos.y + 1][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved)){
        //         MoveUp(entity);
        //         KeepMonsterIntegrity(entity);
        //         map[entity->pos.y - 1][entity->pos.x + 1] = map[entity->pos.y][entity->pos.x];
        //         map[entity->pos.y][entity->pos.x] = *entity;
        //         UpdateMonsterVisible(entity, player);
        //         return true;
        //     }
        // }
        // // Diag up right, x++, y--
        // if (x < pos.x && y < pos.y) {
        //     if ((map[entity->pos.y - 1][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved)){
        //         MoveUp(entity);
        //         KeepMonsterIntegrity(entity);
        //         map[entity->pos.y + 1][entity->pos.x - 1] = map[entity->pos.y][entity->pos.x];
        //         map[entity->pos.y][entity->pos.x] = *entity;
        //         UpdateMonsterVisible(entity, player);
        //         return true;
        //     }
        // }
        // // Diag up left, x--, y--
        // if (x > pos.x && y > pos.y) {
        //     if ((map[entity->pos.y - 1][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved)){
        //         MoveUp(entity);
        //         KeepMonsterIntegrity(entity);
        //         map[entity->pos.y + 1][entity->pos.x + 1] = map[entity->pos.y][entity->pos.x];
        //         map[entity->pos.y][entity->pos.x] = *entity;
        //         UpdateMonsterVisible(entity, player);
        //         return true;
        //     }
        // }