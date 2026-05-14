#include <rogue.h>

void AssignGoblinWarrior(Monster *monster) {
    monster->ch = 'G';
    strcpy(monster->monsterName, "Goblin Warrior");
    strcpy(monster->monsterRace, "Goblin");
    strcpy(monster->monsterClass, "Warrior");
    strcpy(monster->monsterArmor, "Leather Armor");
    strcpy(monster->monsterWeapon, "Short Sword");
    monster->monsterHP = 4;
    monster->monsterAC = 1;
    monster->monsterMaxDMG = 1;
    monster->monsterMinDMG = 4;
    monster->monsterLVL = 1;
}

void AssignKoboldWarrior(Monster *monster) {
    monster->ch = 'K'; 
    strcpy(monster->monsterName, "Kobold Warrior");
    strcpy(monster->monsterRace, "Kobold");
    strcpy(monster->monsterClass, "Warrior");
    strcpy(monster->monsterArmor, "Leather Armor");
    strcpy(monster->monsterWeapon, "Dagger");
    monster->monsterHP = 4;
    monster->monsterAC = 1;
    monster->monsterMaxDMG = 1;
    monster->monsterMinDMG = 4;
    monster->monsterLVL = 1;
}

void AssignGoblinRanger(Monster *monster) {
    monster->ch = 'G'; 
    strcpy(monster->monsterName, "Goblin Ranger");
    strcpy(monster->monsterRace, "Goblin");
    strcpy(monster->monsterClass, "Ranger");
    strcpy(monster->monsterArmor, "Leather Armor");
    strcpy(monster->monsterWeapon, "Shortbow");
    monster->monsterHP = 4;
    monster->monsterAC = 0;
    monster->monsterMaxDMG = 1;
    monster->monsterMinDMG = 3;
    monster->monsterLVL = 1;
}

void AssignHobgoblinWarrior(Monster *monster) {
    strcpy(monster->monsterName, "Hoboblin Warrior");
    strcpy(monster->monsterRace, "Hobgoblin");
    strcpy(monster->monsterClass, "Warrior");
    strcpy(monster->monsterArmor, "Leather Armor");
    strcpy(monster->monsterWeapon, "Long Sword");
    monster->monsterHP = 6;
    monster->monsterAC = 1;
    monster->monsterMaxDMG = 1;
    monster->monsterMinDMG = 6;
    monster->monsterLVL = 1;
}