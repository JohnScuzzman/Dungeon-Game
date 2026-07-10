#include <rogue.h>

Entity* FindNPCInList(int entityID, int maxNPCS) {
    for (int i = 0; i < maxNPCS; i++) {
        if(entityID == nptr[i].entityID) {
            return (nptr + i);
        }
    }
    return NULL;
}

/* Basic logic for how a friendly npc follower interacts and moves.*/
void FollowerLogic(Entity* follower, int n_monsters) {
    for (int i = 0; i < n_monsters; i++) {
        /* If an enemy monster is in aggro range and not adjacent, move towards them.*/
        if (((GetDistance(player->follower.pos, (mptr + i)->pos)) <= (player->follower.aggroRange)) && 
            (!CheckMonsterAdjacent(player->follower.pos, (mptr + i))) &&
            LineOfSight(player->follower.pos, (mptr + i)->pos) &&
            (!player->follower.hasMoved) &&
            (mptr + i)->visible) {
                int closestMonster = FindClosestMonster(mptr, n_monsters);
                MoveTowards(&player->follower, (mptr + closestMonster)->pos);
                player->follower.hasMoved = false;
                return;
        }
        /* If a monster is adjacent, don't move, and attack them.*/
        if (CheckMonsterAdjacent(player->follower.pos, (mptr + i))) {
            // make them attack monster if there is one adjacent
            ResetCombatHistory();
            if(NPCAttackEntity(&player->follower, (mptr + i), combatHistory, n_monsters)) {
                player->follower.hasMoved = false;
                return;
            }
        }
    }
    /* otherwise, move towards the player.*/
    if (!player->follower.hasMoved) {
        FollowPlayer(&player->follower); //TODO: Do something with this bool later.
        player->follower.hasMoved = false;
        return;
    }
    else player->follower.hasMoved = false;
    return;
}

void FollowPlayer(Entity* npc) {
    npc->hasMoved = false;
    if(MoveTowards(npc, player->pos)){
        npc->hasMoved = true;
    }
    else{
        npc->hasMoved = false;
    }
}

/* update monster positions on map from mptr. */
/* update corpses, then npcs to place them on top. */
void UpdateNPCMap(Entity* npc, int maxNPCS) {
    for (int i = 0; i < maxNPCS; i++) {
        int y, x;
        y = (npc + i)->pos.y;
        x = (npc + i)->pos.x;
        /* Draw npcs that died ontop of other npcs */
        if((npc + i)->entityType == CORPSE && !(npc + i)->wasReplaced && map[y][x].wasLooted) {
            map[y][x].wasLooted = false;
            npc[i] = map[y][x];
            map[y][x] = npc[i];
        }
        else if((npc + i)->entityType == CORPSE && !(npc + i)->wasReplaced && !map[y][x].wasLooted) {
            map[y][x] = npc[i];
        }
    }
    for (int i = 0; i < maxNPCS; i++) {
        int y, x;
        y = (npc + i)->pos.y;
        x = (npc + i)->pos.x;
        if((npc + i)->entityType == NPC && (npc + i)->entityID != player->follower.entityID) map[y][x] = npc[i];
    }
}

void KeepNPCIntegrity(Entity* npc) {
    // if new has been seen before fix mptr/old location
    if (npc->mapInfo.newSeen == true){
        npc->seen = true;
        KeepNPCMapIntegrity(npc);
    }
    if (npc->mapInfo.newSeen == false) {
        npc->seen = false;
        KeepNPCMapIntegrity(npc);
    }
    if (npc->mapInfo.newVisible == true) {
        npc->seen = true;
        KeepNPCMapIntegrity(npc);
    }                
}

void KeepNPCMapIntegrity(Entity* npc) {
    if (npc->mapInfo.oldSeen == false){
        map[npc->pos.y][npc->pos.x].seen = false;
    }
    if (npc->mapInfo.oldSeen == true){
        map[npc->pos.y][npc->pos.x].seen = true;
    }
    if (npc->mapInfo.oldVisible == false) {
        map[npc->pos.y][npc->pos.x].visible = false;
    }
    if (npc->mapInfo.oldVisible == true) {
        map[npc->pos.y][npc->pos.x].visible = false;
    }
}

void UpdateNPCVisible(Entity* npc, Player* player){
    if(LineOfSight(npc->pos, player->pos) && 
    GetDistance(npc->pos, player->pos) < 15 && npc->entityType != CORPSE) {
        npc->visible = true;
        npc->seen = true;
        map[npc->pos.y][npc->pos.x].visible = true;
        npc->ch = npc->staticCh;
        map[npc->pos.y][npc->pos.x].ch = npc->ch;
        RecordEntitySeen(npc);
        if (GetDistance(npc->pos, player->pos) < 6) {
            npc->transparent = true;
        }
        else {
            npc->transparent = false;
        } 
    }
    else if (LineOfSight(npc->pos, player->pos) && 
    GetDistance(npc->pos, player->pos) < 15) {
        npc->visible = true;
        npc->seen = true;
        map[npc->pos.y][npc->pos.x].visible = true;
        npc->ch = npc->staticCh;
        map[npc->pos.y][npc->pos.x].ch = npc->ch;
        RecordEntitySeen(npc);
        if (GetDistance(npc->pos, player->pos) < 6) {
            npc->transparent = true;
        }
        else {
            npc->transparent = false;
        } 
    }
    else {
        npc->seenByPlayer = false;
        npc->visible = false;
        npc->transparent = false;
        map[npc->pos.y][npc->pos.x].visible = false;
    }
 }