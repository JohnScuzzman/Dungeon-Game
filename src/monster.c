#include <rogue.h>

/* Create a dynamic list of monsters.*/
Entity* MonsterList(int n_monsters) {
    /* Create an Array to hold our Monster Structs. */
    /* Can be accessed anywhere with mptr declared below. */
    Entity* mptr;
    mptr = (Entity *)malloc(n_monsters * sizeof(Entity));
    return mptr; // return pointer to the array.
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

/* update a single monster the list on map from mptr. */
void UpdateMonster(Entity* monster, int monsterID, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        int y, x;
        y = monster[i].pos.y;
        x = monster[i].pos.x;
        if (monsterID == monster[i].entityID) {
            monster[i] = map[y][x];
        }
    }
}

Entity* FindMonsterInList(int monsterID, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        // Monster found
        if(monsterID == mptr[i].entityID) {
            return (mptr + i);
        }
    }
}

/* Credit to Harpy for helping me prototype this function. */
/* This would have taken signifiantly longer without her, I owe her a case of monster for this.*/
/* Monster attempts to move to a new tile chosen at random. */
/* If legal spot, monster moves, then updates the previous square they moved from. */
/* KeepMonsterIntegrity ensures the previous tile keeps all prior visible and seen values. */
void Wander(Entity* mptr){
    int randDirection = (rand() % 4); //0-3
    bool oldSeen;
    bool newSeen;
    bool oldVisible;
    bool newVisible;
    bool oldChar;
    bool newChar;
    switch(randDirection) {
        //move up
        case 0:
            //newPOS.y--;
            if ((map[mptr->pos.y - 1][(mptr->pos.x)].noCollision) && (!mptr->hasMoved)){
                mptr->pos.y = mptr->pos.y - 1;
                mptr->hasMoved = true;
                oldSeen = map[mptr->pos.y + 1][mptr->pos.x].seen;
                newSeen = map[mptr->pos.y][mptr->pos.x].seen;
                oldVisible = map[mptr->pos.y + 1][mptr->pos.x].seen;
                newVisible = map[mptr->pos.y][mptr->pos.x].seen;
                oldChar = map[mptr->pos.y + 1][mptr->pos.x].ch;
                newChar = map[mptr->pos.y][mptr->pos.x].ch;

                // if new has been seen before fix mptr/old location
                if (newSeen){
                    mptr->seen = true;
                    KeepMonsterIntegrity(mptr,oldSeen, oldVisible);
                }
                if (!newSeen) {
                    mptr->seen = false;
                    KeepMonsterIntegrity(mptr, oldSeen, oldVisible);
                }
                if (newVisible) {
                    mptr->seen = true;
                    KeepMonsterIntegrity(mptr, oldSeen, oldVisible);
                }
                // set new location to old location (have mptr still)
                map[mptr->pos.y + 1][mptr->pos.x] = map[mptr->pos.y][mptr->pos.x];
                //finally set new location to mptr
                map[mptr->pos.y][mptr->pos.x] = *mptr;
                UpdateMonsterVisible(mptr, player);
            }
        break;
        //move down
        case 1:
            //newPOS.y++;
            if ((map[mptr->pos.y + 1][(mptr->pos.x)].noCollision) && (!mptr->hasMoved)){
                mptr->pos.y = mptr->pos.y + 1;
                mptr->hasMoved = true;
                oldSeen = map[mptr->pos.y - 1][mptr->pos.x].seen;
                newSeen = map[mptr->pos.y][mptr->pos.x].seen;
                oldVisible = map[mptr->pos.y - 1][mptr->pos.x].seen;
                newVisible = map[mptr->pos.y][mptr->pos.x].seen;
                oldChar = map[mptr->pos.y - 1][mptr->pos.x].ch;
                newChar = map[mptr->pos.y][mptr->pos.x].ch;

                // if new has been seen before fix mptr/old location
                if (newSeen){
                    mptr->seen = true;
                    KeepMonsterIntegrity(mptr, oldSeen, oldVisible);
                }
                if (!newSeen) {
                    mptr->seen = false;
                    KeepMonsterIntegrity(mptr, oldSeen, oldVisible);
                }
                if (newVisible) {
                    mptr->seen = true;
                    KeepMonsterIntegrity(mptr, oldSeen, oldVisible);
                }
                // set new location to old location (have mptr still)
                map[mptr->pos.y - 1][mptr->pos.x] = map[mptr->pos.y][mptr->pos.x];
                //finally set new location to mptr
                map[mptr->pos.y][mptr->pos.x] = *mptr;
                UpdateMonsterVisible(mptr, player);
            }
        break;
        //move left
        case 2:
            //newPOS.x--;
            if ((map[mptr->pos.y][(mptr->pos.x - 1)].noCollision) && (!mptr->hasMoved)){
                mptr->pos.x = mptr->pos.x - 1;
                mptr->hasMoved = true;
                oldSeen = map[mptr->pos.y][mptr->pos.x + 1].seen;
                newSeen = map[mptr->pos.y][mptr->pos.x].seen;
                oldVisible = map[mptr->pos.y][mptr->pos.x + 1].seen;
                newVisible = map[mptr->pos.y][mptr->pos.x].seen;
                oldChar = map[mptr->pos.y][mptr->pos.x + 1].ch;
                newChar = map[mptr->pos.y][mptr->pos.x].ch;
                // if new has been seen before fix mptr/old location
                if (newSeen){
                    mptr->seen = true;
                    KeepMonsterIntegrity(mptr, oldSeen, oldVisible);
                }
                if (!newSeen) {
                    mptr->seen = false;
                    KeepMonsterIntegrity(mptr, oldSeen, oldVisible);
                }
                if (newVisible) {
                    mptr->seen = true;
                    KeepMonsterIntegrity(mptr, oldSeen, oldVisible);
                }                
                // set new location to old location (have mptr still)
                map[mptr->pos.y][mptr->pos.x + 1] = map[mptr->pos.y][mptr->pos.x];
                //finally set new location to mptr
                map[mptr->pos.y][mptr->pos.x] = *mptr;
                UpdateMonsterVisible(mptr, player);
            }
        break;
        //move right
        case 3:
            if ((map[mptr->pos.y][(mptr->pos.x + 1)].noCollision) && (!mptr->hasMoved)){
                mptr->pos.x = mptr->pos.x + 1;
                mptr->hasMoved = true;
                oldSeen = map[mptr->pos.y][mptr->pos.x - 1].seen;
                newSeen = map[mptr->pos.y][mptr->pos.x].seen;
                oldVisible = map[mptr->pos.y][mptr->pos.x - 1].seen;
                newVisible = map[mptr->pos.y][mptr->pos.x].seen;
                oldChar = map[mptr->pos.y][mptr->pos.x - 1].ch;
                newChar = map[mptr->pos.y][mptr->pos.x].ch;
                // if new has been seen before fix mptr/old location
                if (newSeen){
                    mptr->seen = true;
                    KeepMonsterIntegrity(mptr, oldSeen, oldVisible);
                }
                if (!newSeen) {
                    mptr->seen = false;
                    KeepMonsterIntegrity(mptr, oldSeen, oldVisible);
                }
                if (newVisible) {
                    mptr->seen = true;
                    KeepMonsterIntegrity(mptr, oldSeen, oldVisible);
                }                
                // set new location to old location (have mptr still)
                map[mptr->pos.y][mptr->pos.x - 1] = map[mptr->pos.y][mptr->pos.x];
                //finally set new location to mptr
                map[mptr->pos.y][mptr->pos.x] = *mptr;
                UpdateMonsterVisible(mptr, player);
            }
        break;
        default:
        break;
    }
}

void KeepMonsterIntegrity(Entity* mptr, bool oldSeen, bool oldVisible) {
    if (!oldSeen){
        map[mptr->pos.y][mptr->pos.x].seen = false;
    }
    if (oldSeen){
        map[mptr->pos.y][mptr->pos.x].seen = true;
    }
    if (!oldVisible) {
        map[mptr->pos.y][mptr->pos.x].visible = false;
    }
    if (oldVisible) {
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



// // /*
// // Check if player is in range, if so return true.
// // Change 16 depending on given aggro range of monster.
// // */
// bool CheckAggroRange(Position monsterPos, Position playerLastPos, int aggroRange) {
//     // monster is origin, player is now target.
//     if (GetDistance(monsterPos, playerLastPos) < aggroRange) {
//         return true;
//     }
//     return false;
// }


// /*
// If monster is within Aggro Range, 
// */
// void MoveMonster(Monster monster) { 
//     if(CheckAggroRange(monster.pos, player->pos, monster.monsterAggroRange)) {
//         monster.aggroFlag = true;
//         MoveTowardsPlayer(monster);
//     }
//     else {
//         monster.aggroFlag = false;
//         Wander(monster);
//     }
// }

// /*
// Attempt to move the monster towards the player after they are within aggro range.
// Aggro range is checked in MoveMosnter
// */
// void MoveTowardsPlayer(Monster monster) {

//     int x = monster.pos.x - player->pos.x;
//     int y = monster.pos.y - player->pos.y;

//     /* Move monster x's accorinding to players x*/
//     if(x > 0) {
//         if (map[monster.pos.y][monster.pos.x - 1].noCollision) {
//             monster.pos.x--;
//         }
//     }
//     else {
//         if (map[monster.pos.y][monster.pos.x + 1].noCollision) {
//             monster.pos.x++;
//         }
//     }

//     /* Move monster y's accorinding to players y*/
//     if(y > 0) {
//         if (map[monster.pos.y - 1][monster.pos.x].noCollision) {
//             monster.pos.y--;
//         }
//     }
//     else {
//         if (map[monster.pos.y + 1][monster.pos.x].noCollision) {
//             monster.pos.y++;
//         }
//     }
// }

// /* 
// Makes a monster attempt to explore the dungeon til the find the player.
// */