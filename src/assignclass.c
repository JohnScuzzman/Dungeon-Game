#include <rogue.h>

// ATK is the players modifier used to determine accuracy for attacks.
// This makes it so stacking dex is not always the go to option.
// Original Fallout games had this problem, where stack AGIL was always #1.

void AssignKnight() {
    strcpy(player->playerClass, "Knight");
    strcpy(player->playerArmor, "Chainmail");
    strcpy(player->playerWeapon, "Long Sword");
    player->playerStats.HP += 6;
    player->playerStats.AC = 3;
    player->playerStats.maxDMG = 10;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.CON += 2;
    player->playerStats.STR += 2;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
}

void AssignSwashbuckler() {
    strcpy(player->playerClass, "Swashbuckler");
    strcpy(player->playerArmor, "Leather");
    strcpy(player->playerWeapon, "Cutlass");
    player->playerStats.HP += 4;
    player->playerStats.AC = 2;
    player->playerStats.maxDMG = 7;
    player->playerStats.minDMG = 2;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += 2;
    player->playerStats.CHA += 2;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
}
void AssignWizard() {
    strcpy(player->playerClass, "Wizard");
    strcpy(player->playerArmor, "Robes");
    strcpy(player->playerWeapon, "Quarterstaff");
    player->playerStats.HP += 2;
    player->playerStats.AC = 1;
    player->playerStats.maxDMG = 4;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.INT += 4;
    player->playerStats.ATK = (player->playerStats.INT - 10) / 2;
}
void AssignNecromancer() {
    strcpy(player->playerClass, "Necromancer");
    strcpy(player->playerArmor, "Robes");
    strcpy(player->playerWeapon, "Dagger");
    player->playerStats.HP += 2;
    player->playerStats.AC = 1;
    player->playerStats.maxDMG = 4;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.INT += 2;
    player->playerStats.WIS += 2;
    player->playerStats.ATK = (player->playerStats.INT - 10) / 2;
}
void AssignGunslinger() {
    strcpy(player->playerClass, "Gunslinger");
    strcpy(player->playerArmor, "Leather");
    strcpy(player->playerWeapon, "Flintlock Pistol");
    player->playerStats.HP += 4;
    player->playerStats.AC = 2;
    player->playerStats.maxDMG = 10;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += 4;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
}
void AssignRanger() {
    strcpy(player->playerClass, "Ranger");
    strcpy(player->playerArmor, "Ranger's Cloak");
    strcpy(player->playerWeapon, "Longbow");
    player->playerStats.HP += 4;
    player->playerStats.AC = 2;
    player->playerStats.maxDMG = 8;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += 2;
    player->playerStats.WIS += 2;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
}
void AssignDarkKnight() {
    strcpy(player->playerClass, "Dark Knight");
    strcpy(player->playerArmor, "Chainmail");
    strcpy(player->playerWeapon, "Long Sword");
    player->playerStats.HP += 6;
    player->playerStats.AC = 3;
    player->playerStats.maxDMG = 10;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.STR += 4;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
}
void AssignAlchemist() {
    strcpy(player->playerClass, "Alchemist");
    strcpy(player->playerArmor, "Robes");
    strcpy(player->playerWeapon, "Acid Potion");
    player->playerStats.HP += 4;
    player->playerStats.AC = 1;
    player->playerStats.maxDMG = 8;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += 2;
    player->playerStats.INT += 2;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
}
void AssignConjurer() {
    strcpy(player->playerClass, "Conjurer");
    strcpy(player->playerArmor, "Robes");
    strcpy(player->playerWeapon, "Quarterstaff");
    player->playerStats.HP += 2;
    player->playerStats.AC = 1;
    player->playerStats.maxDMG = 4;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.INT += 2;
    player->playerStats.CHA += 2;
    player->playerStats.ATK = (player->playerStats.CHA - 10) / 2;
}
void AssignCyborg() {
    strcpy(player->playerClass, "Cyborg");
    strcpy(player->playerArmor, "Metallic Skin");
    strcpy(player->playerWeapon, "Chrome Fists");
    player->playerStats.HP += 6;
    player->playerStats.AC = 3;
    player->playerStats.maxDMG = 6;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.STR += 2;
    player->playerStats.DEX += 2;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
}


