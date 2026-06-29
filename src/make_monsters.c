#include <rogue.h>

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


