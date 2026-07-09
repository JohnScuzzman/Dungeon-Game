#include <rogue.h>

/* Create an empty list of npcs.*/
Entity* NPCList(int totalNpcs) {
    Entity* npc_ptr;
    npc_ptr = (Entity *)calloc(totalNpcs, sizeof(Entity));
    return npc_ptr; // return pointer to the array.
}

/* Returns the position in localized list where the NPC was just added. */
/* Used for adding an NPC to the map to later track its actions, movement, etc.*/
/* Return MAX_ONSCREEN_NPCS if failed to find or make*/
int AddToNPCList(Entity* npcs, Position pos, int npcType) {
    if (npcs[MAX_ONSCREEN_NPCS - 1].entityType == NPC) {
        return MAX_ONSCREEN_NPCS;
    }
    for (int i = 0; i < MAX_ONSCREEN_NPCS; i++) {
        if (npcs[i].entityType != NPC) {
            npcs[i] = AssignNPC(pos, npcType, i);
            return i;
        }
    }
    return MAX_ONSCREEN_NPCS;
}

Entity AssignNPC(Position pos, int npcType, int npcID) {
    if (map[pos.y][pos.x].noCollision) {
        Entity npc = {0};
        AssignNPCDefaults(&npc, pos, npcID);
        switch(npcType) {
            case NPC_SKELETON_WARRIOR: 
                AssignSkeletonWarrior(&npc);
                break;
            default:
                break;
        }
        npc.entityStats.mana = npc.entityStats.maxMana;
        npc.entityStats.HP = npc.entityStats.maxHP;
        npc.entityStats.EXP = 0;
        PlaceNPC(&npc, pos);
        return npc;
    }
    else {
        AssignFloor(pos.x, pos.y);
        Entity emptyNpc = {0};
        return emptyNpc;
    }

}

Entity AssignUniqueNPC(Position pos, int npcName, int npcID) {
    if (map[pos.y][pos.x].noCollision) {
        Entity npc = {0};
        AssignNPCDefaults(&npc, pos, npcID);
        switch(npcName) {
            default:
            break;
        }
        npc.entityStats.mana = npc.entityStats.maxMana;
        npc.entityStats.HP = npc.entityStats.maxHP;
        PlaceNPC(&npc, pos);
        return npc;
    }
    else {
        AssignFloor(pos.x, pos.y);
        Entity emptyNpc= {0};
        return emptyNpc;
    }
}

void AssignNPCDefaults(Entity* npc, Position n_pos, int npcID) {
    CreateEntityInv(npc);
    npc->entityStats.ATK = 0;
    npc->invTail = 0;
    npc->invHead = 0;
    npc->aggroFlag = false;
    npc->hasMoved = false;
    npc->noCollision = false;
    npc->seen = false;
    npc->transparent = true;
    npc->visible = false;
    npc->seenByPlayer = false;
    npc->wasLooted = false;
    npc->wasReplaced = false;
    npc->entityID = ENTITY_ID + npcID; // LIES BETWEEN 256 AND 320, 64 TOTAL
    npc->entityType = NPC;
    npc->color = COLOR_PAIR(VISIBLE_COLOR);
    npc->pos.y = n_pos.y;
    npc->pos.x = n_pos.x;
    npc->lastPos.x = n_pos.x;
    npc->lastPos.y = n_pos.y;
    npc->playerLastPos.x = 0;
    npc->playerLastPos.y = 0;
}

void PlaceNPC(Entity* npc, Position pos) {
    AssignFloor(pos.x, pos.y);
    map[pos.y][pos.x] = *npc;
}

