#include <rogue.h>

/* Create an empty list of npcs.*/
Entity* NPCList(int totalNpcs) {
    Entity* npc_ptr;
    npc_ptr = (Entity *)calloc(totalNpcs, sizeof(Entity));
    return npc_ptr; // return pointer to the array.
}

/* Returns the NPC that was just added. */
/* Used for adding an NPC to the map to later track its actions, movement, etc.*/
/* Return MAX_ONSCREEN_NPCS if failed to find or make*/
Entity AddToNPCList(Entity* npcs, Position pos, int npcType) {
    Entity emptyNPC = {0};
    if (npcs[MAX_ONSCREEN_NPCS - 1].entityType != NULL_NPC_TYPE) {
        return emptyNPC;
    }
    for (int i = 0; i < MAX_ONSCREEN_NPCS; i++) {
        if (npcs[i].entityType == NULL_ENTITY_TYPE) {
            npcs[i] = AssignNPC(pos, npcType, i + 64);
            return npcs[i];
        }
    }
    return emptyNPC;
}

// /* Fills the onscreen npc table with empty npcs.*/
// void FillNullNPCs(Entity* npcs) {
//     for (int i = 0; i < MAX_ONSCREEN_NPCS; i++) {
//         AssignEmptyNPC((npcs + i));
//     }
// }

void ZeroEntity(Entity* entity) {
    entity->aggroFlag = false;
    entity->hasMoved = false;
    entity->noCollision = true;
    entity->seen = false;
    entity->transparent = false;
    entity->visible = false;
    entity->seenByPlayer = false;
    entity->wasLooted = false;
    entity->wasReplaced = false;
    entity->ch = ' ';
    entity->staticCh = ' ';
    entity->aggroRange = 0;
    entity->color = COLOR_PAIR(VISIBLE_COLOR);
    entity->entityID = 0;
    entity->entityType = FLOOR;
    ClearEntityInventory(entity);
    ZeroEntityStats(entity);
    ZeroEntityMapInfo(entity);
    entity->entityArmor = NoArmor(); // armor and weapons located in items.h
    entity->entityWeapon = NoWeapon();
    strcpy(entity->entityName, " ");
    strcpy(entity->entityRace, " ");
    strcpy(entity->entityClass, " ");
}

void ZeroEntityStats(Entity* entity) {
    entity->entityStats.ATK = 0;
    entity->entityStats.CHA = 0;
    entity->entityStats.CON = 0;
    entity->entityStats.DEX = 0;
    entity->entityStats.INT = 0;
    entity->entityStats.STR = 0;
    entity->entityStats.WIS = 0;
    entity->entityStats.AC = 0;
    entity->entityStats.HP = 0;
    entity->entityStats.mana = 0;
    entity->entityStats.maxHP = 0;
    entity->entityStats.maxMana = 0;
    entity->entityStats.LVL = 0;
    entity->entityStats.EXP = 0;
    entity->entityStats.nextLVLEXP = 0;
    entity->entityStats.maxDMG = 0;
    entity->entityStats.minDMG = 0;
}

void ZeroEntityMapInfo(Entity* entity) {
    entity->pos.x = 0;
    entity->pos.y = 0;
    entity->lastPos.x = 0;
    entity->lastPos.y = 0;
    entity->playerLastPos.x = 0;
    entity->playerLastPos.y = 0;
    entity->mapInfo.oldSeen = false;
    entity->mapInfo.newSeen = false;
    entity->mapInfo.oldVisible = false;
    entity->mapInfo.newVisible = false;
    entity->mapInfo.newColor = COLOR_PAIR(VISIBLE_COLOR);
    entity->mapInfo.oldColor = COLOR_PAIR(VISIBLE_COLOR);
    entity->mapInfo.oldChar = '.';
    entity->mapInfo.newChar = '.';
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
        // PlaceNPC(&npc, pos);
        return npc;
    }
    else {
        Entity emptyNpc = {0};
        ZeroEntity(&emptyNpc);
        AssignFloor(emptyNpc.pos.x, emptyNpc.pos.y);
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
        // PlaceNPC(&npc, pos);
        return npc;
    }
    else {
        Entity emptyNpc = {0};
        ZeroEntity(&emptyNpc);
        AssignFloor(emptyNpc.pos.x, emptyNpc.pos.y);
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
    npc->entityID = npcID; // LIES BETWEEN 256 AND 320, 64 TOTAL
    npc->entityType = NPC;
    npc->color = COLOR_PAIR(VISIBLE_COLOR);
    npc->pos.y = n_pos.y;
    npc->pos.x = n_pos.x;
    npc->lastPos.x = n_pos.x;
    npc->lastPos.y = n_pos.y;
    npc->playerLastPos.x = 0;
    npc->playerLastPos.y = 0;
}

// void PlaceNPC(Entity* npc, Position pos) {
//     AssignFloor(pos.x, pos.y);
//     map[pos.y][pos.x] = *npc;
// }

