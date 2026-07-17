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
        /* If a monster is adjacent, don't move, and attack them.*/
        if (CheckMonsterAdjacent(player->follower.pos, (mptr + i)) == true) {
            // make them attack monster if there is one adjacent
            ResetCombatHistory();
            if(NPCAttackEntity(&player->follower, (mptr + i), combatHistory, n_monsters)) {
                player->follower.hasMoved = true;
                return;
            }
        }
    }
    int closestMonster = FindClosestMonster(mptr, n_monsters, follower->pos);
    /* If an enemy monster is in aggro range and not adjacent, move towards them.*/
    if ((((GetDistance(player->follower.pos, (mptr + closestMonster)->pos)) <= (player->follower.aggroRange)) && 
    ((mptr + closestMonster)->entityID) != CORPSE) &&
    (mptr + closestMonster)->visible) {
        if(MoveTowards(&player->follower, (mptr + closestMonster)->pos)) {
            player->follower.hasMoved = true;
            return;
        }
    }
    /* otherwise, move towards the player.*/
    if (!player->follower.hasMoved && !CheckPlayerAdjacent(player->follower.pos)) {
        FollowPlayer(&player->follower); //TODO: Do something with this bool later.
        player->follower.hasMoved = true;
        return;
    }
    if ((GetDistance(player->follower.pos, player->pos) == 0) || GetDistance(player->follower.pos, player->pos) >= RADIUS + 2) {
        PlaceAdjacentToPlayer(&player->follower);
        player->follower.hasMoved = true;
        return;
    }
    else player->follower.hasMoved = false;
    return;
}

void FollowPlayer(Entity* npc) {
    npc->hasMoved  = false;
    if(CheckPlayerAdjacent(npc->pos)) {
        npc->hasMoved = true;
        return;
    }
    if(MoveTowards(npc, player->pos)){
        npc->hasMoved = true;
    }
    else{
        npc->hasMoved = false;
    }
}
void RemovePlayerFollower(Entity* follower) {
    switch(player->passiveAbility.abilityID) {
        case SUMMON_SKELETON:
            RemoveSummonSkeleton();
            break;
        default:
            break;
    }
    player->passiveAbility = NoAbility();
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
        else if((npc + i)->entityType == NULL_ENTITY_TYPE) return;
    }
    for (int i = 0; i < maxNPCS; i++) {
        int y, x;
        y = (npc + i)->pos.y;
        x = (npc + i)->pos.x;
                if((npc + i)->entityType > NULL_NPC_TYPE && (npc + i)->entityType < NPC_END && (npc + i)->entityID != player->follower.entityID) map[y][x] = npc[i];
        else if((npc + i)->entityType == NULL_ENTITY_TYPE) return;
    }
}

void UpdateFollower(Entity* follower) {
    if (follower->entityType == NULL_ENTITY_TYPE) return;
    else if (follower->entityType > NULL_NPC_TYPE && follower->entityType > NULL_NPC_TYPE < NPC_END && map[follower->pos.y][follower->pos.x].entityType != CORPSE){
        map[follower->pos.y][follower->pos.x] = player->follower;
    }
    UpdateNPCVisible(follower, player);
}

void UpdateNPCVisible(Entity* npc, Player* player){
    if(LineOfSight(npc->pos, player->pos) && 
    GetDistance(npc->pos, player->pos) < 15) {
        npc->visible = true;
        npc->seen = true;
        map[npc->pos.y][npc->pos.x].visible = true;
        npc->ch = npc->staticCh;
        map[npc->pos.y][npc->pos.x].ch = npc->ch;
        if(npc->entityID != player->follower.entityID) RecordEntitySeen(npc);
        else npc->seenByPlayer = true;
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