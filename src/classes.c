#include <rogue.h>

void AssignKnight() {
    strcpy(player->playerClass, "Knight");
    strcpy(player->playerArmor, "Chainmail");
    strcpy(player->playerWeapon, "Long Sword");
    player->playerHP += 6;
    player->playerAC = 3;
    player->playerMaxDMG = 10;
    player->playerMinDMG = 1;
    player->playerLVL = 1;
}

void AssignSwashbuckler() {
    strcpy(player->playerClass, "Swashbuckler");
    strcpy(player->playerArmor, "Leather");
    strcpy(player->playerWeapon, "Cutlass");
    player->playerHP += 4;
    player->playerAC = 2;
    player->playerMaxDMG = 7;
    player->playerMinDMG = 2;
    player->playerLVL = 1;
}
void AssignWizard() {
    strcpy(player->playerClass, "Wizard");
    strcpy(player->playerArmor, "Robes");
    strcpy(player->playerWeapon, "Quarterstaff");
    player->playerHP += 2;
    player->playerAC = 1;
    player->playerMaxDMG = 4;
    player->playerMinDMG = 1;
    player->playerLVL = 1;
}
void AssignNecromancer() {
    strcpy(player->playerClass, "Necormancer");
    strcpy(player->playerArmor, "Robes");
    strcpy(player->playerWeapon, "Dagger");
    player->playerHP += 2;
    player->playerAC = 1;
    player->playerMaxDMG = 4;
    player->playerMinDMG = 1;
    player->playerLVL = 1;
}
void AssignGunslinger() {
    strcpy(player->playerClass, "Gunslinger");
    strcpy(player->playerArmor, "Leather");
    strcpy(player->playerWeapon, "Flintlock Pistol");
    player->playerHP += 4;
    player->playerAC = 2;
    player->playerMaxDMG = 10;
    player->playerMinDMG = 1;
    player->playerLVL = 1;
}
void AssignRanger() {
    strcpy(player->playerClass, "Ranger");
    strcpy(player->playerArmor, "Ranger's Cloak");
    strcpy(player->playerWeapon, "Longbow");
    player->playerHP += 4;
    player->playerAC = 2;
    player->playerMaxDMG = 8;
    player->playerMinDMG = 1;
    player->playerLVL = 1;
}
void AssignDarkKnight() {
    strcpy(player->playerClass, "Dark Knight");
    strcpy(player->playerArmor, "Chainmail");
    strcpy(player->playerWeapon, "Long Sword");
    player->playerHP += 6;
    player->playerAC = 3;
    player->playerMaxDMG = 10;
    player->playerMinDMG = 1;
    player->playerLVL = 1;
}
void AssignAlchemist() {
    strcpy(player->playerClass, "Alchemist");
    strcpy(player->playerArmor, "Robes");
    strcpy(player->playerWeapon, "Acid Potion");
    player->playerHP += 4;
    player->playerAC = 1;
    player->playerMaxDMG = 8;
    player->playerMinDMG = 1;
    player->playerLVL = 1;
}
void AssignConjurer() {
    strcpy(player->playerClass, "Conjurer");
    strcpy(player->playerArmor, "Robes");
    strcpy(player->playerWeapon, "Quarterstaff");
    player->playerHP += 2;
    player->playerAC = 1;
    player->playerMaxDMG = 4;
    player->playerMinDMG = 1;
    player->playerLVL = 1;
}
void AssignCyborg() {
    strcpy(player->playerClass, "Cyborg");
    strcpy(player->playerArmor, "Metallic Skin");
    strcpy(player->playerWeapon, "Chrome Fists");
    player->playerHP += 6;
    player->playerAC = 3;
    player->playerMaxDMG = 6;
    player->playerMinDMG = 1;
    player->playerLVL = 1;
}


