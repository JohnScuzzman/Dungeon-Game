#include <rogue.h>

/* 
Populates a monster struct with a char and their position.
monsterID is a random int 0-3 passed from map.c
*/ 
Entity AssignMonster(Position pos, int RNG, int monsterID)
{   
    if (map[pos.y][pos.x].noCollision) {
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
    entity->entityStats.maxHP = 0;
    entity->entityStats.LVL = 0;
    entity->entityStats.EXP = 0;
    entity->entityStats.maxDMG = 0;
    entity->entityStats.minDMG = 0;
    // strcpy(entity->entityName, "Corpse");
    // map[entity->pos.y][entity->pos.x].ch = entity->ch;
    // map[entity->pos.y][entity->pos.x].transparent = true;
    // map[entity->pos.y][entity->pos.x].entityID = entity->entityID;
    // map[entity->pos.y][entity->pos.x].isMonster = false;
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
    map[y][x].entityStats.maxHP = 0;
    map[y][x].entityStats.LVL = 0;
    map[y][x].entityStats.EXP = 0;
    map[y][x].entityStats.maxDMG = 0;
    map[y][x].entityStats.minDMG = 0;
    strcpy(map[y][x].entityArmor, "None");
    strcpy(map[y][x].entityClass, "None");
    strcpy(map[y][x].entityName, "Floor");
    strcpy(map[y][x].entityRace, "None");
    strcpy(map[y][x].entityWeapon, "None");
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
    monster->aggroRange = 15;
    monster->entityStats.AC = 1;
    monster->entityStats.maxHP = 4;
    monster->entityStats.EXP = 10;
    monster->entityStats.LVL = 1;
    monster->entityStats.maxDMG = 4;
    monster->entityStats.minDMG = 1;
    strcpy(monster->entityArmor, "Leather Armor");
    strcpy(monster->entityClass, "Warrior");
    strcpy(monster->entityName, "Goblin Warrior");
    strcpy(monster->entityRace, "Goblin");
    strcpy(monster->entityWeapon, "Short Sword");
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
    monster->aggroRange = 20;
    monster->entityStats.AC = 1;
    monster->entityStats.EXP = 10;
    monster->entityStats.maxHP = 4;
    monster->entityStats.LVL = 1;
    monster->entityStats.maxDMG = 4;
    monster->entityStats.minDMG = 1;
    strcpy(monster->entityArmor, "Leather Armor");
    strcpy(monster->entityClass, "Warrior");
    strcpy(monster->entityName, "Kobold Warrior");
    strcpy(monster->entityRace, "Kobold");
    strcpy(monster->entityWeapon, "Dagger");
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
    monster->aggroRange = 15;
    monster->entityStats.AC = 0;
    monster->entityStats.maxHP = 4;
    monster->entityStats.LVL = 1;
    monster->entityStats.EXP = 10;
    monster->entityStats.maxDMG = 3;
    monster->entityStats.minDMG = 1;
    strcpy(monster->entityArmor, "Leather Armor");
    strcpy(monster->entityClass, "Ranger");
    strcpy(monster->entityName, "Goblin Ranger");
    strcpy(monster->entityRace, "Goblin");
    strcpy(monster->entityWeapon, "Shortbow");
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
    monster->aggroRange = 12;
    monster->entityStats.AC = 1;
    monster->entityStats.maxHP = 6;
    monster->entityStats.LVL = 1;
    monster->entityStats.EXP = 20;
    monster->entityStats.maxDMG = 6;
    monster->entityStats.minDMG = 1;
    strcpy(monster->entityName, "Hoboblin Warrior");
    strcpy(monster->entityRace, "Hobgoblin");
    strcpy(monster->entityClass, "Warrior");
    strcpy(monster->entityArmor, "Leather Armor");
    strcpy(monster->entityWeapon, "Scimitar");
}

void AssignMonsterDefaults(Entity* monster, Position m_pos, int monsterID) {
    monster->entityStats.ATK = 0;
    monster->aggroFlag = false;
    monster->hasMoved = false;
    monster->noCollision = false;
    monster->seen = false;
    monster->transparent = false;
    monster->visible = false;
    monster->isMonster = true;
    monster->entityID = monsterID;
    monster->entityStats.HP = monster->entityStats.maxHP;
    monster->color = COLOR_PAIR(VISIBLE_COLOR);
    monster->pos.y = m_pos.y;
    monster->pos.x = m_pos.x;
    monster->playerLastPos.x = 0;
    monster->playerLastPos.y = 0;
}


/*
Assigns the class chosen by the player to the Entity struct player.
Each method is listed in classes.c
*/
void AssignClass(int input) {
    switch(input){
        case 68:
            AssignKnight();
            break;
        case 69:
            AssignSwashbuckler();
            break;
        case 70:
            AssignWizard();
            break;
        case 71:
            AssignNecromancer();
            break;
        case 72:
            AssignGunslinger();
            break;
        case 88:
            AssignRanger();
            break;
        case 89:
            AssignDarkKnight();
            break;
        case 90:
            AssignAlchemist();
            break;
        case 91:
            AssignConjurer();
            break;
        case 92:
            AssignCyborg();
            break;
        default:
            AssignKnight();
            break;
    }
}

/*
Assigns stats based on the race chosen by the player.
TODO Currently only adjusts HP, but will later adjust CHA, WIS, STR, etc.
*/
void AssignStats(int input) {
    switch(input){
        case 62:
            strcpy(player->playerRace, "Human");
            player->playerStats.HP = 10;
            player->playerStats.CHA = 12;
            player->playerStats.CON = 12;
            player->playerStats.DEX = 12;
            player->playerStats.INT = 12;
            player->playerStats.STR = 12;
            player->playerStats.WIS = 12;
        break;
        case 63:
            strcpy(player->playerRace, "Elf");
            player->playerStats.HP = 8;
            player->playerStats.CHA = 12;
            player->playerStats.CON = 10;
            player->playerStats.DEX = 16;
            player->playerStats.INT = 14;
            player->playerStats.STR = 10;
            player->playerStats.WIS = 12;
        break;
        case 64:
            strcpy(player->playerRace, "Dwarf");
            player->playerStats.HP = 10;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 14;
            player->playerStats.DEX = 10;
            player->playerStats.INT = 10;
            player->playerStats.STR = 14;
            player->playerStats.WIS = 16;
        break;
        case 65:
            strcpy(player->playerRace, "Dragonborn");
            player->playerStats.HP = 12;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 16;
            player->playerStats.DEX = 8;
            player->playerStats.INT = 10;
            player->playerStats.STR = 16;
            player->playerStats.WIS = 10;
        break;
        case 66:
            strcpy(player->playerRace, "Gnoll");
            player->playerStats.HP = 12;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 16;
            player->playerStats.DEX = 10;
            player->playerStats.INT = 8;
            player->playerStats.STR = 16;
            player->playerStats.WIS = 10;
        break;
        case 82:
            strcpy(player->playerRace, "Skeleton");
            player->playerStats.HP = 8;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 14;
            player->playerStats.DEX = 12;
            player->playerStats.INT = 16;
            player->playerStats.STR = 8;
            player->playerStats.WIS = 14;
        break;
        case 83:
            strcpy(player->playerRace, "Mantis");
            player->playerStats.HP = 12;
            player->playerStats.CHA = 8;
            player->playerStats.CON = 14;
            player->playerStats.DEX = 12;
            player->playerStats.INT = 10;
            player->playerStats.STR = 16;
            player->playerStats.WIS = 10;
        break;
        case 84:
            strcpy(player->playerRace, "Robot");
            player->playerStats.HP = 10;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 16;
            player->playerStats.DEX = 10;
            player->playerStats.INT = 12;
            player->playerStats.STR = 14;
            player->playerStats.WIS = 10;
        break;
        case 85:
            strcpy(player->playerRace, "Werewolf");
            player->playerStats.HP = 12;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 16;
            player->playerStats.DEX = 14;
            player->playerStats.INT = 8;
            player->playerStats.STR = 16;
            player->playerStats.WIS = 8;
        break;
        case 86:
            strcpy(player->playerRace, "Vampire");
            player->playerStats.HP = 10;
            player->playerStats.CHA = 16;
            player->playerStats.CON = 10;
            player->playerStats.DEX = 12;
            player->playerStats.INT = 14;
            player->playerStats.STR = 10;
            player->playerStats.WIS = 10;
        break;
        default:
            strcpy(player->playerRace, "Human");
            player->playerStats.HP = 10;
            player->playerStats.CHA = 12;
            player->playerStats.CON = 12;
            player->playerStats.DEX = 12;
            player->playerStats.INT = 12;
            player->playerStats.STR = 12;
            player->playerStats.WIS = 12;
        break;
    }
}
