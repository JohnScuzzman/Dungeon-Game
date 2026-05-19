#include <rogue.h>

/* 
Populates a monster struct with a char and their position.
monsterID is a random int 0-3 passed from map.c
*/ 
Entity AssignMonster(Position pos, int RNG, int monsterID)
{   
    Entity monster;
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

    AssignMonsterDefaults(&monster, pos, monsterID);
    return monster;
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
    map[y][x].entityAC = 0;
    map[y][x].entityAggroRange = 0;
    map[y][x].entityHP = 0;
    map[y][x].entityID = 0;
    map[y][x].entityLVL = 0;
    map[y][x].entityMaxDMG = 0;
    map[y][x].entityMinDMG = 0;
    strcpy(map[y][x].entityArmor, "None");
    strcpy(map[y][x].entityClass, "None");
    strcpy(map[y][x].entityName, "Floor");
    strcpy(map[y][x].entityRace, "None");
    strcpy(map[y][x].entityWeapon, "None");
}


void AssignGoblinWarrior(Entity* monster) {
    monster->ch = 'G';
    monster->staticCh = 'G'; 
    monster->entityAC = 1;
    monster->entityAggroRange = 15;
    monster->entityHP = 4;
    monster->entityLVL = 1;
    monster->entityMaxDMG = 1;
    monster->entityMinDMG = 4;
    strcpy(monster->entityArmor, "Leather Armor");
    strcpy(monster->entityClass, "Warrior");
    strcpy(monster->entityName, "Goblin Warrior");
    strcpy(monster->entityRace, "Goblin");
    strcpy(monster->entityWeapon, "Short Sword");
}

void AssignKoboldWarrior(Entity* monster) {
    monster->ch = 'K';
    monster->staticCh = 'K'; 
    monster->entityAC = 1;
    monster->entityAggroRange = 20;
    monster->entityLVL = 1;
    monster->entityHP = 4;
    monster->entityMaxDMG = 1;
    monster->entityMinDMG = 4;
    strcpy(monster->entityArmor, "Leather Armor");
    strcpy(monster->entityClass, "Warrior");
    strcpy(monster->entityName, "Kobold Warrior");
    strcpy(monster->entityRace, "Kobold");
    strcpy(monster->entityWeapon, "Dagger");
}

void AssignGoblinRanger(Entity* monster) {
    monster->ch = 'G';
    monster->staticCh = 'G'; 
    monster->entityAC = 0;
    monster->entityAggroRange = 15;
    monster->entityLVL = 1;
    monster->entityHP = 4;
    monster->entityMaxDMG = 1;
    monster->entityMinDMG = 3;
    strcpy(monster->entityArmor, "Leather Armor");
    strcpy(monster->entityClass, "Ranger");
    strcpy(monster->entityName, "Goblin Ranger");
    strcpy(monster->entityRace, "Goblin");
    strcpy(monster->entityWeapon, "Shortbow");
}

void AssignHobgoblinWarrior(Entity* monster) {
    monster->ch = 'H'; 
    monster->staticCh = 'H'; 
    monster->entityAC = 1;
    monster->entityAggroRange = 12;
    monster->entityHP = 6;
    monster->entityLVL = 1;
    monster->entityMaxDMG = 1;
    monster->entityMinDMG = 6;
    strcpy(monster->entityName, "Hoboblin Warrior");
    strcpy(monster->entityRace, "Hobgoblin");
    strcpy(monster->entityClass, "Warrior");
    strcpy(monster->entityArmor, "Leather Armor");
    strcpy(monster->entityWeapon, "Long Sword");
}

void AssignMonsterDefaults(Entity* monster, Position m_pos, int monsterID) {
    monster->aggroFlag = false;
    monster->hasMoved = false;
    monster->noCollision = false;
    monster->seen = false;
    monster->transparent = false;
    monster->visible = false;
    monster->entityID = monsterID;
    monster->color = COLOR_PAIR(VISIBLE_COLOR);
    monster->pos.y = m_pos.y;
    monster->pos.x = m_pos.x;
}
