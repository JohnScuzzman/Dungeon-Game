#include <rogue.h>

/* 
Populates a monster struct with a char and their position.
monsterID is a random int 0-3 passed from map.c
*/ 

Entity AssignMonster(Position pos, int RNG, int monsterID)
{   
    if (map[pos.y][pos.x].noCollision) {
        Entity monster;
        AssignMonsterDefaults(&monster, pos, monsterID);
        switch (RNG) {
            /* Call functions from assign.c */
            case 0:
            AssignGoblinWarrior(&monster);
            break;
            case 1:
            AssignKoboldWarrior(&monster);
            break;
            case 2:
            AssignHobgoblinWarrior(&monster);
            break;
            case 3:
            AssignGoblinRanger(&monster);
            break;
            default:
            AssignGoblinWarrior(&monster);
            break; 
        }
        return monster;
    }
    else{ 
        AssignFloor(pos.x, pos.y);
    }
   
}

void AssignCorpse(Entity* entity) {
    int x = entity->pos.x;
    int y = entity->pos.y;
    AssignFloor(x,y);
    entity->ch = 'X';
    entity->color = COLOR_PAIR(VISIBLE_COLOR);
    entity->aggroFlag = false;
    entity->hasMoved = true;
    entity->noCollision = true;
    entity->transparent = true;
    entity->seen = true;
    entity->visible = false;
    entity->isMonster = false;
    entity->seenByPlayer = true;
    entity->aggroRange = 0;
    entity->entityID = 0;
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
    map[entity->pos.y][entity->pos.x] = *entity;
}

void AssignFloor(int x, int y) {
    map[y][x].ch = '.';
    map[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
    map[y][x].aggroFlag = false;
    map[y][x].hasMoved = false;
    map[y][x].noCollision = true;
    map[y][x].transparent = true;
    map[y][x].seen = false;
    map[y][x].visible = false;
    map[y][x].isMonster = false;
    map[y][x].seenByPlayer = false;
    map[y][x].aggroRange = 0;
    map[y][x].entityID = 0;
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
    map[y][x].entityWeapon = NoWeapon();
    map[y][x].entityArmor = NoArmor();
    strcpy(map[y][x].entityClass, "None");
    strcpy(map[y][x].entityName, "Floor");
    strcpy(map[y][x].entityRace, "None");

}

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
    monster->entityWeapon = Shortsword();
    AddToNPCInventory(monster, items[RAGS]);
    AddToNPCInventory(monster, items[SHORTSWORD]);
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
    monster->entityArmor = LeatherArmor();
    monster->entityWeapon = Dagger();
    AddToNPCInventory(monster, items[LEATHER_ARMOR]);
    AddToNPCInventory(monster, items[DAGGER]);
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
    AddToNPCInventory(monster, items[RAGS]);
    AddToNPCInventory(monster, items[SHORTBOW]);
    monster->aggroRange = 15;
    monster->entityStats.AC = ((monster->entityStats.DEX - 10) / 2) + (monster->entityArmor.AC);
    monster->entityStats.maxDMG = (monster->entityWeapon.maxDMG) - 3; // Their shortbows should suck more than normal.
    monster->entityStats.minDMG = monster->entityWeapon.minDMG;
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
    monster->entityWeapon = Scimitar();
    AddToNPCInventory(monster, items[LEATHER_ARMOR]);
    AddToNPCInventory(monster, items[SCIMITAR]);
    monster->aggroRange = 12;
    monster->entityStats.AC = ((monster->entityStats.STR - 10) / 2) + (monster->entityArmor.AC);
    monster->entityStats.maxDMG = monster->entityWeapon.maxDMG;
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
    monster->inventoryPOS = 0;
    monster->aggroFlag = false;
    monster->hasMoved = false;
    monster->noCollision = false;
    monster->seen = false;
    monster->transparent = false;
    monster->visible = false;
    monster->isMonster = true;
    monster->seenByPlayer = false;
    monster->entityID = monsterID;
    monster->entityStats.mana = monster->entityStats.maxMana;
    monster->entityStats.HP = monster->entityStats.maxHP;
    monster->color = COLOR_PAIR(VISIBLE_COLOR);
    monster->pos.y = m_pos.y;
    monster->pos.x = m_pos.x;
    monster->playerLastPos.x = 0;
    monster->playerLastPos.y = 0;
}


