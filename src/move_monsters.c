#include <rogue.h>

void MoveUp(Entity* mptr){
    mptr->pos.y = mptr->pos.y - 1;
    mptr->hasMoved = true;
    mptr->mapInfo.oldSeen = map[mptr->pos.y + 1][mptr->pos.x].seen;
    mptr->mapInfo.newSeen = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldVisible = map[mptr->pos.y + 1][mptr->pos.x].seen;
    mptr->mapInfo.newVisible = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldChar = map[mptr->pos.y + 1][mptr->pos.x].ch;
    mptr->mapInfo.newChar = map[mptr->pos.y][mptr->pos.x].ch;
    if(map[mptr->pos.y][mptr->pos.x].ch == 'X') {
        map[mptr->pos.y][mptr->pos.x].ch = '.';
    }
    if(map[mptr->pos.y + 1][mptr->pos.x].ch == 'X') {
        AssignFloor(mptr->pos.x, mptr->pos.y + 1);
        map[mptr->pos.y + 1][mptr->pos.x].ch = '.';
    }
    if(mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->staticCh;
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
    if(map[mptr->pos.y][mptr->pos.x].ch == 'X') {
        map[mptr->pos.y][mptr->pos.x].ch = '.';
    }
    if(map[mptr->pos.y - 1][mptr->pos.x].ch == 'X') {
        AssignFloor(mptr->pos.x, mptr->pos.y - 1);
        map[mptr->pos.y - 1][mptr->pos.x].ch = '.';
    }
    if(mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->staticCh;
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
    if(map[mptr->pos.y][mptr->pos.x].ch == 'X') {
        map[mptr->pos.y][mptr->pos.x].ch = '.';
    }
    if(map[mptr->pos.y][mptr->pos.x].ch == 'X') {
        AssignFloor(mptr->pos.x + 1, mptr->pos.y);
        map[mptr->pos.y][mptr->pos.x + 1].ch = '.';
    }
    if(mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->staticCh;
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
    if(map[mptr->pos.y][mptr->pos.x].ch == 'X') {
        map[mptr->pos.y][mptr->pos.x].ch = '.';
    }
    if(map[mptr->pos.y][mptr->pos.x - 1].ch == 'X') {
        AssignFloor(mptr->pos.x - 1, mptr->pos.y);
        map[mptr->pos.y][mptr->pos.x - 1].ch = '.';
    }
    if(mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->staticCh;
    }
}

void MoveDownRight(Entity* mptr){
    mptr->pos.x = mptr->pos.x + 1;
    mptr->pos.y = mptr->pos.y + 1;
    mptr->hasMoved = true;
    mptr->mapInfo.oldSeen = map[mptr->pos.y - 1][mptr->pos.x - 1].seen;
    mptr->mapInfo.newSeen = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldVisible = map[mptr->pos.y - 1][mptr->pos.x - 1].seen;
    mptr->mapInfo.newVisible = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldChar = map[mptr->pos.y - 1][mptr->pos.x - 1].ch;
    mptr->mapInfo.newChar = map[mptr->pos.y][mptr->pos.x].ch;
    if(map[mptr->pos.y][mptr->pos.x].ch == 'X') {
        map[mptr->pos.y][mptr->pos.x].ch = '.';
    }
    if(map[mptr->pos.y - 1][mptr->pos.x - 1].ch == 'X') {
        AssignFloor(mptr->pos.x - 1, mptr->pos.y + 1);
        map[mptr->pos.y - 1][mptr->pos.x - 1].ch = '.';
    }
    if(mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->staticCh;
    }
}

void MoveDownLeft(Entity* mptr){
    mptr->pos.x = mptr->pos.x - 1;
    mptr->pos.y = mptr->pos.y + 1;
    mptr->hasMoved = true;
    mptr->mapInfo.oldSeen = map[mptr->pos.y - 1][mptr->pos.x + 1].seen;
    mptr->mapInfo.newSeen = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldVisible = map[mptr->pos.y - 1][mptr->pos.x + 1].seen;
    mptr->mapInfo.newVisible = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldChar = map[mptr->pos.y - 1][mptr->pos.x + 1].ch;
    mptr->mapInfo.newChar = map[mptr->pos.y][mptr->pos.x].ch;
    if(map[mptr->pos.y][mptr->pos.x].ch == 'X') {
        map[mptr->pos.y][mptr->pos.x].ch = '.';
    }
    if(map[mptr->pos.y - 1][mptr->pos.x + 1].ch == 'X') {
        AssignFloor(mptr->pos.x + 1, mptr->pos.y - 1);
        map[mptr->pos.y - 1][mptr->pos.x + 1].ch = '.';
    }
    if(mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->staticCh;
    }
}

void MoveUpRight(Entity* mptr){
    mptr->pos.x = mptr->pos.x + 1;
    mptr->pos.y = mptr->pos.y - 1;
    mptr->hasMoved = true;
    mptr->mapInfo.oldSeen = map[mptr->pos.y + 1][mptr->pos.x - 1].seen;
    mptr->mapInfo.newSeen = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldVisible = map[mptr->pos.y + 1][mptr->pos.x - 1].seen;
    mptr->mapInfo.newVisible = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldChar = map[mptr->pos.y + 1][mptr->pos.x - 1].ch;
    mptr->mapInfo.newChar = map[mptr->pos.y][mptr->pos.x].ch;
    if(map[mptr->pos.y][mptr->pos.x].ch == 'X') {
        map[mptr->pos.y][mptr->pos.x].ch = '.';
    }
    if(map[mptr->pos.y + 1][mptr->pos.x - 1].ch == 'X') {
        AssignFloor(mptr->pos.x - 1, mptr->pos.y + 1);
        map[mptr->pos.y + 1][mptr->pos.x - 1].ch = '.';
    }
    if(mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->staticCh;
    }
}

void MoveUpLeft(Entity* mptr){
    mptr->pos.x = mptr->pos.x - 1;
    mptr->pos.y = mptr->pos.y - 1;
    mptr->hasMoved = true;
    mptr->mapInfo.oldSeen = map[mptr->pos.y + 1][mptr->pos.x + 1].seen;
    mptr->mapInfo.newSeen = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldVisible = map[mptr->pos.y + 1][mptr->pos.x + 1].seen;
    mptr->mapInfo.newVisible = map[mptr->pos.y][mptr->pos.x].seen;
    mptr->mapInfo.oldChar = map[mptr->pos.y + 1][mptr->pos.x + 1].ch;
    mptr->mapInfo.newChar = map[mptr->pos.y][mptr->pos.x].ch;
    if(map[mptr->pos.y][mptr->pos.x].ch == 'X') {
        map[mptr->pos.y][mptr->pos.x].ch = '.';
    }
    if(map[mptr->pos.y + 1][mptr->pos.x + 1].ch == 'X') {
        AssignFloor(mptr->pos.x + 1, mptr->pos.y + 1);
        map[mptr->pos.y + 1][mptr->pos.x + 1].ch = '.';
    }
    if(mptr->mapInfo.newChar == 'X') {
        mptr->mapInfo.newChar = mptr->staticCh;
    }
}