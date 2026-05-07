#include <rogue.h>

void AssignKnight() {
    strcpy(player->entityClass, "Knight");
    strcpy(player->entityArmor, "Chainmail");
    strcpy(player->entityWeapon, "Long Sword");
    player->entityHP += 6;
    player->entityAC = 3;
    player->entityMaxDMG = 10;
    player->entityMinDMG = 1;
    player->entityLVL = 1;
}

void AssignSwashbuckler() {
    strcpy(player->entityClass, "Swashbuckler");
    strcpy(player->entityArmor, "Leather");
    strcpy(player->entityWeapon, "Cutlass");
    player->entityHP += 4;
    player->entityAC = 2;
    player->entityMaxDMG = 7;
    player->entityMinDMG = 2;
    player->entityLVL = 1;
}
void AssignWizard() {
    strcpy(player->entityClass, "Wizard");
    strcpy(player->entityArmor, "Robes");
    strcpy(player->entityWeapon, "Quarterstaff");
    player->entityHP += 2;
    player->entityAC = 1;
    player->entityMaxDMG = 4;
    player->entityMinDMG = 1;
    player->entityLVL = 1;
}
void AssignNecromancer() {
    strcpy(player->entityClass, "Necormancer");
    strcpy(player->entityArmor, "Robes");
    strcpy(player->entityWeapon, "Dagger");
    player->entityHP += 2;
    player->entityAC = 1;
    player->entityMaxDMG = 4;
    player->entityMinDMG = 1;
    player->entityLVL = 1;
}
void AssignGunslinger() {
    strcpy(player->entityClass, "Gunslinger");
    strcpy(player->entityArmor, "Leather");
    strcpy(player->entityWeapon, "Flintlock Pistol");
    player->entityHP += 4;
    player->entityAC = 2;
    player->entityMaxDMG = 10;
    player->entityMinDMG = 1;
    player->entityLVL = 1;
}
void AssignRanger() {
    strcpy(player->entityClass, "Ranger");
    strcpy(player->entityArmor, "Ranger's Cloak");
    strcpy(player->entityWeapon, "Longbow");
    player->entityHP += 4;
    player->entityAC = 2;
    player->entityMaxDMG = 8;
    player->entityMinDMG = 1;
    player->entityLVL = 1;
}
void AssignDarkKnight() {
    strcpy(player->entityClass, "Dark Knight");
    strcpy(player->entityArmor, "Chainmail");
    strcpy(player->entityWeapon, "Long Sword");
    player->entityHP += 6;
    player->entityAC = 3;
    player->entityMaxDMG = 10;
    player->entityMinDMG = 1;
    player->entityLVL = 1;
}
void AssignAlchemist() {
    strcpy(player->entityClass, "Alchemist");
    strcpy(player->entityArmor, "Robes");
    strcpy(player->entityWeapon, "Acid Potion");
    player->entityHP += 4;
    player->entityAC = 1;
    player->entityMaxDMG = 8;
    player->entityMinDMG = 1;
    player->entityLVL = 1;
}
void AssignConjurer() {
    strcpy(player->entityClass, "Conjurer");
    strcpy(player->entityArmor, "Robes");
    strcpy(player->entityWeapon, "Quarterstaff");
    player->entityHP += 2;
    player->entityAC = 1;
    player->entityMaxDMG = 4;
    player->entityMinDMG = 1;
    player->entityLVL = 1;
}
void AssignCyborg() {
    strcpy(player->entityClass, "Cyborg");
    strcpy(player->entityArmor, "Metallic Skin");
    strcpy(player->entityWeapon, "Chrome Fists");
    player->entityHP += 6;
    player->entityAC = 3;
    player->entityMaxDMG = 6;
    player->entityMinDMG = 1;
    player->entityLVL = 1;
}


