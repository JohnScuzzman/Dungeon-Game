#include <rogue.h>

/* 
Tries to move the entity to the passed position.
Returns true if entity moved towards given coords.
*/
bool MoveTowards(Entity* entity, Position pos) {
    int x = entity->pos.x;
    int y = entity->pos.y;
    if (!CheckPlayerAdjacent(entity->pos)) {
        // up and left
        // up & left
        if (y > pos.y && x > pos.x) {
            if ((map[entity->pos.y - 1][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved)){
                MoveUpLeft(entity);
                KeepNPCIntegrity(entity);
                AssignFloor(entity->pos.x, entity->pos.y);
                map[entity->pos.y][entity->pos.x].seen = entity->mapInfo.newSeen;
                map[entity->pos.y + 1][entity->pos.x + 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateNPCVisible(entity, player);
                return true;
            }
        }
        // down & left
        else if (y < pos.y && x > pos.x) {
            if ((map[entity->pos.y + 1][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved)){
                MoveDownLeft(entity);
                KeepNPCIntegrity(entity);
                AssignFloor(entity->pos.x, entity->pos.y);
                map[entity->pos.y][entity->pos.x].seen = entity->mapInfo.newSeen;
                map[entity->pos.y - 1][entity->pos.x + 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateNPCVisible(entity, player);
                return true;
            }
        }
        // down & right
        else if (y < pos.y && x < pos.x) {
            if ((map[entity->pos.y + 1][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved)){
                MoveDownRight(entity);
                KeepNPCIntegrity(entity);
                AssignFloor(entity->pos.x, entity->pos.y);
                map[entity->pos.y][entity->pos.x].seen = entity->mapInfo.newSeen;
                map[entity->pos.y - 1][entity->pos.x - 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateNPCVisible(entity, player);
                return true;
            }
        }
        // move up & right
        else if (y > pos.y && x < pos.x) {
            if ((map[entity->pos.y - 1][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved)){
                MoveUpRight(entity);
                KeepNPCIntegrity(entity);
                AssignFloor(entity->pos.x, entity->pos.y);
                map[entity->pos.y][entity->pos.x].seen = entity->mapInfo.newSeen;
                map[entity->pos.y + 1][entity->pos.x - 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateNPCVisible(entity, player);
                return true;
            }
        }
        //move up, y--
        if (y > pos.y) {
            if ((map[entity->pos.y - 1][(entity->pos.x)].noCollision) && (!entity->hasMoved)){
                MoveUp(entity);
                KeepNPCIntegrity(entity);
                AssignFloor(entity->pos.x, entity->pos.y);
                map[entity->pos.y][entity->pos.x].seen = entity->mapInfo.newSeen;
                map[entity->pos.y + 1][entity->pos.x] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateNPCVisible(entity, player);
                return true;
            }
        }
        //move left, x--
        else if (x > pos.x) {
            if ((map[entity->pos.y][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved)){
                MoveLeft(entity);
                KeepNPCIntegrity(entity);
                AssignFloor(entity->pos.x, entity->pos.y);
                map[entity->pos.y][entity->pos.x].seen = entity->mapInfo.newSeen;
                map[entity->pos.y][entity->pos.x + 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateNPCVisible(entity, player);
                return true;
            }
        }
        //move down, y++
        else if (y < pos.y) {
            if ((map[entity->pos.y + 1][(entity->pos.x)].noCollision) && (!entity->hasMoved)){
                MoveDown(entity);
                KeepNPCIntegrity(entity);
                AssignFloor(entity->pos.x, entity->pos.y);
                map[entity->pos.y][entity->pos.x].seen = entity->mapInfo.newSeen;
                map[entity->pos.y - 1][entity->pos.x] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateNPCVisible(entity, player);
                return true;
            }
        }
        //move right, x++
        else if (x < pos.x) {
            if ((map[entity->pos.y][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved)){
                MoveRight(entity);
                KeepNPCIntegrity(entity);
                AssignFloor(entity->pos.x, entity->pos.y);
                map[entity->pos.y][entity->pos.x].seen = entity->mapInfo.newSeen;
                map[entity->pos.y][entity->pos.x - 1] = map[entity->pos.y][entity->pos.x];
                map[entity->pos.y][entity->pos.x] = *entity;
                UpdateNPCVisible(entity, player);
                return true;
            }
        }
    }
    UpdateNPCVisible(entity, player);
    return false;
}

void MoveUp(Entity* npc){
    npc->pos.y = (npc->pos.y - 1);
    npc->lastPos.y = (npc->pos.y + 1);
    npc->hasMoved = true;
    npc->mapInfo.oldSeen = map[(npc->pos.y + 1)][npc->pos.x].seen;
    npc->mapInfo.newSeen = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldVisible = map[(npc->pos.y + 1)][npc->pos.x].seen;
    npc->mapInfo.newVisible = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldChar = map[(npc->pos.y + 1)][npc->pos.x].ch;
    npc->mapInfo.newChar = map[npc->pos.y][npc->pos.x].ch;
    if(map[npc->pos.y][npc->pos.x].ch == 'X') {
        map[npc->pos.y][npc->pos.x].ch = '.';
    }
    if(map[(npc->pos.y + 1)][npc->pos.x].ch == 'X') {
        map[(npc->pos.y + 1)][npc->pos.x].ch = '.';
    }
    if(npc->mapInfo.newChar == 'X') {
        npc->mapInfo.newChar = npc->staticCh;
    }
}

void MoveDown(Entity* npc){
    npc->pos.y = (npc->pos.y + 1);
    npc->lastPos.y = (npc->pos.y - 1);
    npc->hasMoved = true;
    npc->mapInfo.oldSeen = map[(npc->pos.y - 1)][npc->pos.x].seen;
    npc->mapInfo.newSeen = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldVisible = map[(npc->pos.y - 1)][npc->pos.x].seen;
    npc->mapInfo.newVisible = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldChar = map[(npc->pos.y - 1)][npc->pos.x].ch;
    npc->mapInfo.newChar = map[npc->pos.y][npc->pos.x].ch;
    if(map[npc->pos.y][npc->pos.x].ch == 'X') {
        map[npc->pos.y][npc->pos.x].ch = '.';
    }
    if(map[(npc->pos.y - 1)][npc->pos.x].ch == 'X') {
        map[(npc->pos.y - 1)][npc->pos.x].ch = '.';
    }
    if(npc->mapInfo.newChar == 'X') {
        npc->mapInfo.newChar = npc->staticCh;
    }
}

void MoveLeft(Entity* npc){
    npc->pos.x = (npc->pos.x - 1);
    npc->lastPos.x = (npc->pos.x + 1);
    npc->hasMoved = true;
    npc->mapInfo.oldSeen = map[npc->pos.y][(npc->pos.x + 1)].seen;
    npc->mapInfo.newSeen = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldVisible = map[npc->pos.y][(npc->pos.x + 1)].seen;
    npc->mapInfo.newVisible = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldChar = map[npc->pos.y][(npc->pos.x + 1)].ch;
    npc->mapInfo.newChar = map[npc->pos.y][npc->pos.x].ch;
    if(map[npc->pos.y][npc->pos.x].ch == 'X') {
        map[npc->pos.y][npc->pos.x].ch = '.';
    }
    if(map[npc->pos.y][npc->pos.x].ch == 'X') {
        map[npc->pos.y][(npc->pos.x + 1)].ch = '.';
    }
    if(npc->mapInfo.newChar == 'X') {
        npc->mapInfo.newChar = npc->staticCh;
    }
}

void MoveRight(Entity* npc){
    npc->pos.x = (npc->pos.x + 1);
    npc->lastPos.x = (npc->pos.x - 1);
    npc->hasMoved = true;
    npc->mapInfo.oldSeen = map[npc->pos.y][(npc->pos.x - 1)].seen;
    npc->mapInfo.newSeen = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldVisible = map[npc->pos.y][(npc->pos.x - 1)].seen;
    npc->mapInfo.newVisible = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldChar = map[npc->pos.y][(npc->pos.x - 1)].ch;
    npc->mapInfo.newChar = map[npc->pos.y][npc->pos.x].ch;
    if(map[npc->pos.y][npc->pos.x].ch == 'X') {
        map[npc->pos.y][npc->pos.x].ch = '.';
    }
    if(map[npc->pos.y][(npc->pos.x - 1)].ch == 'X') {
        map[npc->pos.y][(npc->pos.x - 1)].ch = '.';
    }
    if(npc->mapInfo.newChar == 'X') {
        npc->mapInfo.newChar = npc->staticCh;
    }
}

void MoveDownRight(Entity* npc){
    npc->pos.x = (npc->pos.x + 1);
    npc->pos.y = (npc->pos.y + 1);
    npc->lastPos.x = (npc->pos.x - 1);
    npc->lastPos.y = (npc->pos.y - 1);
    npc->hasMoved = true;
    npc->mapInfo.oldSeen = map[(npc->pos.y - 1)][(npc->pos.x - 1)].seen;
    npc->mapInfo.newSeen = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldVisible = map[(npc->pos.y - 1)][(npc->pos.x - 1)].seen;
    npc->mapInfo.newVisible = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldChar = map[(npc->pos.y - 1)][(npc->pos.x - 1)].ch;
    npc->mapInfo.newChar = map[npc->pos.y][npc->pos.x].ch;
    if(map[npc->pos.y][npc->pos.x].ch == 'X') {
        map[npc->pos.y][npc->pos.x].ch = '.';
    }
    if(map[(npc->pos.y - 1)][(npc->pos.x - 1)].ch == 'X') {
        map[(npc->pos.y - 1)][(npc->pos.x - 1)].ch = '.';
    }
    if(npc->mapInfo.newChar == 'X') {
        npc->mapInfo.newChar = npc->staticCh;
    }
}

void MoveDownLeft(Entity* npc){
    npc->pos.x = (npc->pos.x - 1);
    npc->pos.y = (npc->pos.y + 1);
    npc->lastPos.x = (npc->pos.x + 1);
    npc->lastPos.y = (npc->pos.y - 1);
    npc->hasMoved = true;
    npc->mapInfo.oldSeen = map[(npc->pos.y - 1)][(npc->pos.x + 1)].seen;
    npc->mapInfo.newSeen = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldVisible = map[(npc->pos.y - 1)][(npc->pos.x + 1)].seen;
    npc->mapInfo.newVisible = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldChar = map[(npc->pos.y - 1)][(npc->pos.x + 1)].ch;
    npc->mapInfo.newChar = map[npc->pos.y][npc->pos.x].ch;
    if(map[npc->pos.y][npc->pos.x].ch == 'X') {
        map[npc->pos.y][npc->pos.x].ch = '.';
    }
    if(map[(npc->pos.y - 1)][(npc->pos.x + 1)].ch == 'X') {
        map[(npc->pos.y - 1)][(npc->pos.x + 1)].ch = '.';
    }
    if(npc->mapInfo.newChar == 'X') {
        npc->mapInfo.newChar = npc->staticCh;
    }
}

void MoveUpRight(Entity* npc){
    npc->pos.x = (npc->pos.x + 1);
    npc->pos.y = (npc->pos.y - 1);
    npc->lastPos.x = (npc->pos.x - 1);
    npc->lastPos.y = (npc->pos.y + 1);
    npc->hasMoved = true;
    npc->mapInfo.oldSeen = map[(npc->pos.y + 1)][(npc->pos.x - 1)].seen;
    npc->mapInfo.newSeen = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldVisible = map[(npc->pos.y + 1)][(npc->pos.x - 1)].seen;
    npc->mapInfo.newVisible = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldChar = map[(npc->pos.y + 1)][(npc->pos.x - 1)].ch;
    npc->mapInfo.newChar = map[npc->pos.y][npc->pos.x].ch;
    if(map[npc->pos.y][npc->pos.x].ch == 'X') {
        map[npc->pos.y][npc->pos.x].ch = '.';
    }
    if(map[(npc->pos.y + 1)][(npc->pos.x - 1)].ch == 'X') {
        map[(npc->pos.y + 1)][(npc->pos.x - 1)].ch = '.';
    }
    if(npc->mapInfo.newChar == 'X') {
        npc->mapInfo.newChar = npc->staticCh;
    }
}

void MoveUpLeft(Entity* npc){
    npc->pos.x = (npc->pos.x - 1);
    npc->pos.y = (npc->pos.y - 1);
    npc->lastPos.x = (npc->pos.x + 1);
    npc->lastPos.y = (npc->pos.y + 1);
    npc->hasMoved = true;
    npc->mapInfo.oldSeen = map[(npc->pos.y + 1)][(npc->pos.x + 1)].seen;
    npc->mapInfo.newSeen = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldVisible = map[(npc->pos.y + 1)][(npc->pos.x + 1)].seen;
    npc->mapInfo.newVisible = map[npc->pos.y][npc->pos.x].seen;
    npc->mapInfo.oldChar = map[(npc->pos.y + 1)][(npc->pos.x + 1)].ch;
    npc->mapInfo.newChar = map[npc->pos.y][npc->pos.x].ch;
    if(map[npc->pos.y][npc->pos.x].ch == 'X') {
        map[npc->pos.y][npc->pos.x].ch = '.';
    }
    if(map[(npc->pos.y + 1)][(npc->pos.x + 1)].ch == 'X') {
        map[(npc->pos.y + 1)][(npc->pos.x + 1)].ch = '.';
    }
    if(npc->mapInfo.newChar == 'X') {
        npc->mapInfo.newChar = npc->staticCh;
    }
}