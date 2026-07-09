#include <rogue.h>

Entity** CreateEntities(void) {
    Entity** map = calloc(MAP_HEIGHT, sizeof(Entity *));

    /* Change amount of wall entities created based on map dimensions. */ 
    for (int y = 0; y < MAP_HEIGHT; y++) {
        map[y] = calloc(MAP_WIDTH, sizeof(Entity));
        for (int x = 0 ; x < MAP_WIDTH; x++) {
            map[y][x].ch = '#';
            map[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
            map[y][x].entityID = 1;
            map[y][x].entityType = WALL;
            map[y][x].entityStats.AC = 30;
            map[y][x].entityStats.HP = 1000;
            strcpy(map[y][x].entityClass, "None");
            strcpy(map[y][x].entityName, "Stone Wall");
            strcpy(map[y][x].entityRace, "None");
            map[y][x].entityArmor = NoArmor();
            map[y][x].entityWeapon = NoWeapon();
        }
    }
    /* Return a 2D arr thats a pointer that points at pointers that point to our wall entities. */ 
    return map;
}

void AssignChest(int x, int y) {
    map[y][x].aggroFlag = false;
    map[y][x].hasMoved = false;
    map[y][x].noCollision = true; // TODO give collision and rewrite MakeInventoryMenu to take position as param.
    map[y][x].seen = false;
    map[y][x].transparent = true;
    map[y][x].visible = false;
    map[y][x].seenByPlayer = false;
    map[y][x].wasLooted = false;
    map[y][x].wasReplaced = false;
    map[y][x].ch = '$';
    map[y][x].staticCh = '$';
    map[y][x].aggroRange = 0;
    map[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
    map[y][x].entityID = 0;
    map[y][x].entityType = CHEST;
    map[y][x].entityStats.ATK = 0;
    map[y][x].entityStats.CHA = 0;
    map[y][x].entityStats.CON = 0;
    map[y][x].entityStats.DEX = 0;
    map[y][x].entityStats.INT = 0;
    map[y][x].entityStats.STR = 0;
    map[y][x].entityStats.WIS = 0;
    map[y][x].entityStats.AC = 0;
    map[y][x].entityStats.HP = 0;
    map[y][x].entityStats.mana = 0;
    map[y][x].entityStats.maxHP = 0;
    map[y][x].entityStats.maxMana = 0;
    map[y][x].entityStats.LVL = 0;
    map[y][x].entityStats.EXP = 0;
    map[y][x].entityStats.maxDMG = 0;
    map[y][x].entityStats.minDMG = 0;
    map[y][x].pos.x = x;
    map[y][x].pos.y = y;
    map[y][x].mapInfo.oldSeen = false;
    map[y][x].mapInfo.newSeen = false;
    map[y][x].mapInfo.oldVisible = false;
    map[y][x].mapInfo.newSeen = false;
    map[y][x].mapInfo.oldChar = '$';
    map[y][x].mapInfo.newChar = '$';
    map[y][x].entityArmor = NoArmor();
    map[y][x].entityWeapon = NoWeapon();
    ClearEntityInventory(&map[y][x]);
    LowLevelChestLoot(&map[y][x]);
    strcpy(map[y][x].entityClass, "None");
    strcpy(map[y][x].entityName, "Chest");
    strcpy(map[y][x].entityRace, "None");
}

/* 
Attempts to turn the monster into a corpse, changing both map entity and monster list entity into a "corpse".
*/
void AssignCorpse(Entity* entity, int n_monsters) {
    int x = entity->pos.x;
    int y = entity->pos.y;
    entity->ch = 'X';
    entity->staticCh = 'X';
    entity->color = COLOR_PAIR(VISIBLE_COLOR);
    entity->aggroFlag = false;
    entity->hasMoved = true;
    entity->noCollision = true;
    entity->transparent = true;
    entity->seen = true;
    entity->visible = false;
    entity->seenByPlayer = true;
    entity->aggroRange = 0;
    entity->entityType = CORPSE;
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
    entity->entityStats.maxDMG = 0;
    entity->entityStats.minDMG = 0;
    for(int i = 0; i < n_monsters; i++){
        if(((mptr + i)->entityID != entity->entityID)) {
            if (((mptr + i)->pos.x == entity->pos.x) && ((mptr + i)->pos.y == entity->pos.y) && (!(mptr + i)->wasReplaced) &&
            ((mptr + i)->inventory[0].itemID != NULL_ITEM_ID)) {
                (mptr + i)->wasReplaced = true; // mark as looted so we dont loot again.
                CombineEntityInventories((mptr + i), entity);
                map[y][x] = *entity;
                return;
            }
        }
    }
    AssignFloor(x,y); // DO NOT REMOVE
    map[y][x] = *entity;
}

void AssignStairsDown(int x, int y) {
    map[y][x].aggroFlag = false;
    map[y][x].hasMoved = false;
    map[y][x].noCollision = false;
    map[y][x].seen = false;
    map[y][x].transparent = true;
    map[y][x].visible = false;
    map[y][x].seenByPlayer = false;
    map[y][x].wasLooted = false;
    map[y][x].wasReplaced = false;
    map[y][x].ch = '=';
    map[y][x].staticCh = '=';
    map[y][x].aggroRange = 0;
    map[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
    map[y][x].entityID = 0;
    map[y][x].entityType = STAIRS;
    map[y][x].entityStats.ATK = 0;
    map[y][x].entityStats.CHA = 0;
    map[y][x].entityStats.CON = 0;
    map[y][x].entityStats.DEX = 0;
    map[y][x].entityStats.INT = 0;
    map[y][x].entityStats.STR = 0;
    map[y][x].entityStats.WIS = 0;
    map[y][x].entityStats.AC = 0;
    map[y][x].entityStats.HP = 0;
    map[y][x].entityStats.mana = 0;
    map[y][x].entityStats.maxHP = 0;
    map[y][x].entityStats.maxMana = 0;
    map[y][x].entityStats.LVL = 0;
    map[y][x].entityStats.EXP = 0;
    map[y][x].entityStats.maxDMG = 0;
    map[y][x].entityStats.minDMG = 0;
    map[y][x].pos.x = x;
    map[y][x].pos.y = y;
    map[y][x].mapInfo.oldSeen = false;
    map[y][x].mapInfo.newSeen = false;
    map[y][x].mapInfo.oldVisible = false;
    map[y][x].mapInfo.newSeen = false;
    map[y][x].mapInfo.oldChar = '=';
    map[y][x].mapInfo.newChar = '=';
    map[y][x].entityArmor = NoArmor();
    map[y][x].entityWeapon = NoWeapon();
    ClearEntityInventory(&map[y][x]);
    strcpy(map[y][x].entityClass, "None");
    strcpy(map[y][x].entityName, "Stairs to Next Floor");
    strcpy(map[y][x].entityRace, "None");
}

/* 
Assigns the entity at the given coordinates to a floor, and zeroes out all the information.
*/
void AssignFloor(int x, int y) {
    map[y][x].aggroFlag = false;
    map[y][x].hasMoved = false;
    map[y][x].noCollision = true;
    map[y][x].seen = false;
    map[y][x].transparent = true;
    map[y][x].visible = false;
    map[y][x].seenByPlayer = false;
    map[y][x].wasLooted = false;
    map[y][x].wasReplaced = false;
    map[y][x].ch = '.';
    map[y][x].staticCh = '.';
    map[y][x].aggroRange = 0;
    map[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
    map[y][x].entityID = 0;
    map[y][x].entityType = FLOOR;
    map[y][x].entityStats.ATK = 0;
    map[y][x].entityStats.CHA = 0;
    map[y][x].entityStats.CON = 0;
    map[y][x].entityStats.DEX = 0;
    map[y][x].entityStats.INT = 0;
    map[y][x].entityStats.STR = 0;
    map[y][x].entityStats.WIS = 0;
    map[y][x].entityStats.AC = 0;
    map[y][x].entityStats.HP = 0;
    map[y][x].entityStats.mana = 0;
    map[y][x].entityStats.maxHP = 0;
    map[y][x].entityStats.maxMana = 0;
    map[y][x].entityStats.LVL = 0;
    map[y][x].entityStats.EXP = 0;
    map[y][x].entityStats.maxDMG = 0;
    map[y][x].entityStats.minDMG = 0;
    map[y][x].pos.x = x;
    map[y][x].pos.y = y;
    map[y][x].mapInfo.oldSeen = false;
    map[y][x].mapInfo.newSeen = false;
    map[y][x].mapInfo.oldVisible = false;
    map[y][x].mapInfo.newSeen = false;
    map[y][x].mapInfo.oldChar = '.';
    map[y][x].mapInfo.newChar = '.';
    map[y][x].entityArmor = NoArmor();
    map[y][x].entityWeapon = NoWeapon();
    ClearEntityInventory(&map[y][x]);
    strcpy(map[y][x].entityClass, "None");
    strcpy(map[y][x].entityName, "Floor");
    strcpy(map[y][x].entityRace, "None");
}