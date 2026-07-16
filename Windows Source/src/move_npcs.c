#include <rogue.h>

/* 
Tries to move the entity to the passed position.
Returns true if entity moved towards given coords.
*/
bool MoveTowards(Entity* entity, Position pos) {
    int x = entity->pos.x;
    int y = entity->pos.y;
    if(CheckNPCDiagonals(entity, x, y, pos)) return true;
    if (y > pos.y) {
        if ((map[(entity->pos.y - 1)][(entity->pos.x)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y - 1)][(entity->pos.x)].entityType != CHEST){
            MoveUp(entity);
            ProcessMoveUp(entity);
            return true;
        }
        else if ((map[(entity->pos.y - 1)][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y - 1)][(entity->pos.x + 1)].entityType != CHEST){
            MoveUpRight(entity);
            ProcessMoveUpRight(entity);
            return true;
        }
        else if ((map[(entity->pos.y - 1)][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y - 1)][(entity->pos.x - 1)].entityType != CHEST){
            MoveUpLeft(entity);
            ProcessMoveUpLeft(entity);
            return true;
        }
    }
    else if (x > pos.x) {
        if ((map[entity->pos.y][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved) &&
            map[entity->pos.y][(entity->pos.x - 1)].entityType != CHEST){
            MoveLeft(entity);
            ProcessMoveLeft(entity);
            return true;
        }
        else if ((map[(entity->pos.y + 1)][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y + 1)][(entity->pos.x - 1)].entityType != CHEST){
            MoveDownLeft(entity);
            ProcessMoveDownLeft(entity);
            return true;
        }
        else if ((map[(entity->pos.y - 1)][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y - 1)][(entity->pos.x - 1)].entityType != CHEST){
            MoveUpLeft(entity);
            ProcessMoveUpLeft(entity);
            return true;
        }
    }
    else if (y < pos.y) {
        if ((map[(entity->pos.y + 1)][(entity->pos.x)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y + 1)][(entity->pos.x)].entityType != CHEST){
            MoveDown(entity);
            ProcessMoveDown(entity);
            return true;
        }
        else if ((map[(entity->pos.y + 1)][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y + 1)][(entity->pos.x + 1)].entityType != CHEST){
            MoveDownRight(entity);
            ProcessMoveDownRight(entity);
            return true;
        }
        else if ((map[(entity->pos.y + 1)][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y + 1)][(entity->pos.x - 1)].entityType != CHEST){
            MoveDownLeft(entity);
            ProcessMoveDownLeft(entity);
            return true;
        }
    }
    else if (x < pos.x) {
        if ((map[entity->pos.y][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y - 1)][(entity->pos.x + 1)].entityType != CHEST){
            MoveRight(entity);
            ProcessMoveRight(entity);
            return true;
        }
        else if ((map[(entity->pos.y + 1)][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y + 1)][(entity->pos.x + 1)].entityType != CHEST){
            MoveDownRight(entity);
            ProcessMoveDownRight(entity);
            return true;
        }
        else if ((map[(entity->pos.y - 1)][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y - 1)][(entity->pos.x + 1)].entityType != CHEST){
            MoveUpRight(entity);
            ProcessMoveUpRight(entity);
            return true;
        }
    }
    UpdateNPCVisible(entity, player);
    return false;
}

bool CheckNPCDiagonals(Entity* entity, int x, int y, Position pos) {
    if (y > pos.y && x > pos.x) {
        if ((map[(entity->pos.y - 1)][(entity->pos.x - 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y - 1)][(entity->pos.x - 1)].entityType != CHEST){
            MoveUpLeft(entity);
            ProcessMoveUpLeft(entity);
            return true;
        }
    }
    else if (y < pos.y && x > pos.x) {
        if ((map[(entity->pos.y + 1)][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y + 1)][(entity->pos.x + 1)].entityType != CHEST){
            MoveDownLeft(entity);
            ProcessMoveDownLeft(entity);
            return true;
        }
    }
    else if (y < pos.y && x < pos.x) {
        if ((map[(entity->pos.y + 1)][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y + 1)][(entity->pos.x + 1)].entityType != CHEST){
            MoveDownRight(entity);
            ProcessMoveDownRight(entity);
            return true;
        }
    }
    else if (y > pos.y && x < pos.x) {
        if ((map[(entity->pos.y - 1)][(entity->pos.x + 1)].noCollision) && (!entity->hasMoved) &&
            map[(entity->pos.y - 1)][(entity->pos.x + 1)].entityType != CHEST){
            MoveUpRight(entity);
            ProcessMoveUpRight(entity);
            return true;
        }
    }
    else return false;
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

void ProcessMoveUp(Entity* npc){
    KeepNPCIntegrity(npc);
    AssignFloor(npc->pos.x, npc->pos.y);
    map[npc->pos.y][npc->pos.x].seen = npc->mapInfo.newSeen;
    map[npc->pos.y + 1][npc->pos.x] = map[npc->pos.y][npc->pos.x];
    map[npc->pos.y][npc->pos.x] = *npc;
    UpdateNPCVisible(npc, player);
}

void ProcessMoveDown(Entity* npc){
    KeepNPCIntegrity(npc);
    AssignFloor(npc->pos.x, npc->pos.y);
    map[npc->pos.y][npc->pos.x].seen = npc->mapInfo.newSeen;
    map[npc->pos.y - 1][npc->pos.x] = map[npc->pos.y][npc->pos.x];
    map[npc->pos.y][npc->pos.x] = *npc;
    UpdateNPCVisible(npc, player);
}

void ProcessMoveLeft(Entity* npc){
    KeepNPCIntegrity(npc);
    AssignFloor(npc->pos.x, npc->pos.y);
    map[npc->pos.y][npc->pos.x].seen = npc->mapInfo.newSeen;
    map[npc->pos.y][npc->pos.x + 1] = map[npc->pos.y][npc->pos.x];
    map[npc->pos.y][npc->pos.x] = *npc;
    UpdateNPCVisible(npc, player);
}

void ProcessMoveRight(Entity* npc){
    KeepNPCIntegrity(npc);
    AssignFloor(npc->pos.x, npc->pos.y);
    map[npc->pos.y][npc->pos.x].seen = npc->mapInfo.newSeen;
    map[npc->pos.y][npc->pos.x - 1] = map[npc->pos.y][npc->pos.x];
    map[npc->pos.y][npc->pos.x] = *npc;
    UpdateNPCVisible(npc, player);
}

void ProcessMoveDownRight(Entity* npc){
    KeepNPCIntegrity(npc);
    AssignFloor(npc->pos.x, npc->pos.y);
    map[npc->pos.y][npc->pos.x].seen = npc->mapInfo.newSeen;
    map[npc->pos.y - 1][npc->pos.x - 1] = map[npc->pos.y][npc->pos.x];
    map[npc->pos.y][npc->pos.x] = *npc;
    UpdateNPCVisible(npc, player);
}

void ProcessMoveDownLeft(Entity* npc){
    KeepNPCIntegrity(npc);
    AssignFloor(npc->pos.x, npc->pos.y);
    map[npc->pos.y][npc->pos.x].seen = npc->mapInfo.newSeen;
    map[npc->pos.y - 1][npc->pos.x + 1] = map[npc->pos.y][npc->pos.x];
    map[npc->pos.y][npc->pos.x] = *npc;
    UpdateNPCVisible(npc, player);
}

void ProcessMoveUpRight(Entity* npc){
    KeepNPCIntegrity(npc);
    AssignFloor(npc->pos.x, npc->pos.y);
    map[npc->pos.y][npc->pos.x].seen = npc->mapInfo.newSeen;
    map[npc->pos.y + 1][npc->pos.x - 1] = map[npc->pos.y][npc->pos.x];
    map[npc->pos.y][npc->pos.x] = *npc;
    UpdateNPCVisible(npc, player);
}

void ProcessMoveUpLeft(Entity* npc){
    KeepNPCIntegrity(npc);
    AssignFloor(npc->pos.x, npc->pos.y);
    map[npc->pos.y][npc->pos.x].seen = npc->mapInfo.newSeen;
    map[npc->pos.y + 1][npc->pos.x + 1] = map[npc->pos.y][npc->pos.x];
    map[npc->pos.y][npc->pos.x] = *npc;
    UpdateNPCVisible(npc, player);
}