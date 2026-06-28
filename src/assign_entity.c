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

/* 
Populates a monster struct with a char and their position.
monsterID is a random int 0-3 passed from map.c
*/ 
Entity AssignMonster(Position pos, int RNG, int monsterID)
{   
    if (map[pos.y][pos.x].noCollision) {
        Entity monster = {0};
        AssignMonsterDefaults(&monster, pos, monsterID);
        switch (RNG) {
            /* Call functions from assign.c */
            case 0:
            AssignRat(&monster);
            break;
            case 1:
            AssignGoblinWarrior(&monster);
            break;
            case 2:
            AssignKoboldWarrior(&monster);
            break;
            case 3:
            AssignHobgoblinWarrior(&monster);
            break;
            case 4:
            AssignGoblinRanger(&monster);
            break;
            default:
            AssignGoblinWarrior(&monster);
            break; 
        }
        monster.entityStats.mana = monster.entityStats.maxMana;
        monster.entityStats.HP = monster.entityStats.maxHP;
        return monster;
    }
    else { 
        AssignFloor(pos.x, pos.y);
        Entity emptyMonster = {0};
        return emptyMonster;
    }
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

void AssignRat(Entity* monster) {
    monster->ch = 'R'; 
    monster->staticCh = 'R'; 
    monster->entityStats.CHA = 4;
    monster->entityStats.CON = 4;
    monster->entityStats.DEX = 4;
    monster->entityStats.INT = 4;
    monster->entityStats.STR = 4;
    monster->entityStats.WIS = 4;
    monster->entityArmor = NoArmor();
    monster->entityWeapon = Claws();
    monster->aggroRange = 12;
    monster->entityStats.AC = ((monster->entityStats.STR - 10) / 2) + (monster->entityArmor.AC);
    monster->entityStats.maxDMG = 2; // hit hard but shouldn't 1-shot
    monster->entityStats.minDMG = 1;
    monster->entityStats.maxHP = 2;
    monster->entityStats.maxMana = 0;
    monster->entityStats.LVL = 1;
    monster->entityStats.EXP = 10;
    strcpy(monster->entityName, "Rat");
    strcpy(monster->entityRace, "Rat");
    strcpy(monster->entityClass, "None");
}

/* The following functions are used to create monster entities based on a passed Entity pointer.*/

void AssignGoblinWarrior(Entity* monster) {
    monster->ch = 'G';
    monster->staticCh = 'G'; 
    monster->entityStats.CHA = 8;
    monster->entityStats.CON = 8;
    monster->entityStats.DEX = 10;
    monster->entityStats.INT = 8;
    monster->entityStats.STR = 12;
    monster->entityStats.WIS = 8;
    monster->entityArmor = Rags();
    AddToNPCInventory(monster, items[RAGS], 1);
    GoblinWarriorLoot(monster);
    monster->aggroRange = 15;
    monster->entityStats.AC = ((monster->entityStats.DEX - 10) / 2) + (monster->entityArmor.AC);
    monster->entityStats.maxDMG = (monster->entityWeapon.maxDMG) - 2; // Their swords suck.
    monster->entityStats.minDMG = monster->entityWeapon.minDMG;
    monster->entityStats.maxHP = 4;
    monster->entityStats.maxMana = 0;
    monster->entityStats.LVL = 1;
    monster->entityStats.EXP = 10;
    monster->entityStats.maxDMG = 4;
    monster->entityStats.minDMG = 1;
    strcpy(monster->entityClass, "Warrior");
    strcpy(monster->entityName, "Goblin Warrior");
    strcpy(monster->entityRace, "Goblin");
}

void AssignKoboldWarrior(Entity* monster) {
    monster->ch = 'K';
    monster->staticCh = 'K'; 
    monster->entityStats.CHA = 8;
    monster->entityStats.CON = 8;
    monster->entityStats.DEX = 12;
    monster->entityStats.INT = 8;
    monster->entityStats.STR = 10;
    monster->entityStats.WIS = 8;
    monster->entityArmor = Rags();
    monster->entityWeapon = Dagger();
    AddToNPCInventory(monster, items[RAGS], 1);
    KoboldWarriorLoot(monster);
    monster->aggroRange = 20;
    monster->entityStats.AC = ((monster->entityStats.DEX - 10) / 2) + (monster->entityArmor.AC);
    monster->entityStats.maxDMG = monster->entityWeapon.maxDMG;
    monster->entityStats.minDMG = monster->entityWeapon.minDMG;
    monster->entityStats.maxHP = 4;
    monster->entityStats.maxMana = 0;
    monster->entityStats.LVL = 1;
    monster->entityStats.EXP = 10;
    strcpy(monster->entityClass, "Warrior");
    strcpy(monster->entityName, "Kobold Warrior");
    strcpy(monster->entityRace, "Kobold");
}

void AssignGoblinRanger(Entity* monster) {
    int randArrows = 12;
    monster->ch = 'G';
    monster->staticCh = 'G'; 
    monster->entityStats.CHA = 8;
    monster->entityStats.CON = 10;
    monster->entityStats.DEX = 14;
    monster->entityStats.INT = 8;
    monster->entityStats.STR = 8;
    monster->entityStats.WIS = 8;
    monster->entityArmor = Rags();
    monster->entityWeapon = Shortbow();
    AddToNPCInventory(monster, items[RAGS], 1);
    AddToNPCInventory(monster, items[SHORTBOW], 1);
    AddToNPCInventory(monster, items[ARROWS], (rand() % randArrows) + 5); // 5 - 12 arrows
    monster->aggroRange = 15;
    monster->entityStats.AC = ((monster->entityStats.DEX - 10) / 2) + (monster->entityArmor.AC);
    monster->entityStats.maxDMG = (monster->entityWeapon.maxDMG) - 4; // Their shortbows should suck more than normal.
    monster->entityStats.minDMG = monster->entityWeapon.minDMG;
    monster->entityWeapon.range -= 4; 
    monster->entityStats.maxHP = 4;
    monster->entityStats.maxMana = 0;
    monster->entityStats.LVL = 1;
    monster->entityStats.EXP = 10;
    strcpy(monster->entityClass, "Ranger");
    strcpy(monster->entityName, "Goblin Ranger");
    strcpy(monster->entityRace, "Goblin");
}

void AssignHobgoblinWarrior(Entity* monster) {
    monster->ch = 'H'; 
    monster->staticCh = 'H'; 
    monster->entityStats.CHA = 8;
    monster->entityStats.CON = 12;
    monster->entityStats.DEX = 12;
    monster->entityStats.INT = 8;
    monster->entityStats.STR = 12;
    monster->entityStats.WIS = 8;
    monster->entityArmor = LeatherArmor();
    AddToNPCInventory(monster, items[LEATHER_ARMOR], 1);
    HobGoblinWarriorLoot(monster);
    monster->aggroRange = 12;
    monster->entityStats.AC = ((monster->entityStats.STR - 10) / 2) + (monster->entityArmor.AC);
    monster->entityStats.maxDMG = (monster->entityWeapon.maxDMG) - 3; // hit hard but shouldn't 1-shot
    monster->entityStats.minDMG = monster->entityWeapon.minDMG;
    monster->entityStats.maxHP = 6;
    monster->entityStats.maxMana = 0;
    monster->entityStats.LVL = 1;
    monster->entityStats.EXP = 20;
    strcpy(monster->entityName, "Hoboblin Warrior");
    strcpy(monster->entityRace, "Hobgoblin");
    strcpy(monster->entityClass, "Warrior");
}
    
void AssignMonsterDefaults(Entity* monster, Position m_pos, int monsterID) {
    CreateMonsterInv(monster);
    monster->entityStats.ATK = 0;
    monster->invTail = 0;
    monster->invHead = 0;
    monster->aggroFlag = false;
    monster->hasMoved = false;
    monster->noCollision = false;
    monster->seen = false;
    monster->transparent = false;
    monster->visible = false;
    monster->seenByPlayer = false;
    monster->wasLooted = false;
    monster->wasReplaced = false;
    monster->entityID = monsterID;
    monster->entityType = MONSTER;
    monster->color = COLOR_PAIR(VISIBLE_COLOR);
    monster->pos.y = m_pos.y;
    monster->pos.x = m_pos.x;
    monster->pos.y = m_pos.y;
    monster->lastPos.x = m_pos.x;
    monster->lastPos.y = m_pos.y;
    monster->playerLastPos.x = 0;
    monster->playerLastPos.y = 0;
}


