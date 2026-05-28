#include <rogue.h>

// ATK is the players modifier used to determine accuracy for attacks.
// This makes it so stacking dex is not always the go to option.
// Original Fallout games had this problem, where stack AGIL was always #1.

void AssignKnight() {
    strcpy(player->playerClass, "Knight");
    player->equippedArmor = Chainmail();
    player->equippedMelee = Greatsword();
    player->equippedRanged = Shortbow();
    player->playerStats.HP += 6;
    player->playerStats.maxHP = player->playerStats.HP;
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
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Cutlass();
    player->equippedRanged = FlintlockPistol();
    player->playerStats.HP += 4;
    player->playerStats.maxHP = player->playerStats.HP;
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
    player->equippedArmor = Robes();
    player->equippedMelee = Quarterstaff();
    player->equippedRanged = MagicMissile();
    player->playerStats.HP += 2;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.AC = 1;
    player->playerStats.maxDMG = 4;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.INT += 4;
    player->playerStats.ATK = (player->playerStats.INT - 10) / 2;
}
void AssignNecromancer() {
    strcpy(player->playerClass, "Necromancer");
    player->equippedArmor = Robes();
    player->equippedMelee = Dagger();
    player->equippedRanged = AcidPotion();
    player->playerStats.HP += 2;
    player->playerStats.maxHP = player->playerStats.HP;
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
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Shortsword();
    player->equippedRanged = FlintlockPistol();
    player->playerStats.HP += 4;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.AC = 2;
    player->playerStats.maxDMG = 10;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += 4;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
}
void AssignRanger() {
    strcpy(player->playerClass, "Ranger");
    player->equippedArmor = RangersCloak();
    player->equippedMelee = Longsword();
    player->equippedRanged = Longbow();
    player->playerStats.HP += 4;
    player->playerStats.maxHP = player->playerStats.HP;
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
    player->equippedArmor = Chainmail();
    player->equippedMelee = Greatsword();
    player->equippedRanged = Shortbow();
    player->playerStats.HP += 6;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.AC = 3;
    player->playerStats.maxDMG = 10;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.STR += 4;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
}
void AssignAlchemist() {
    strcpy(player->playerClass, "Alchemist");
    player->equippedArmor = Robes();
    player->equippedMelee = Quarterstaff();
    player->equippedRanged = AcidPotion();
    player->playerStats.HP += 4;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.AC = 1;
    player->playerStats.maxDMG = 8;
    player->playerStats.minDMG = 2;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += 2;
    player->playerStats.INT += 2;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
}
void AssignConjurer() {
    strcpy(player->playerClass, "Conjurer");
    player->equippedArmor = Robes();
    player->equippedMelee = Quarterstaff();
    player->equippedRanged = MagicMissile();
    player->playerStats.HP += 2;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.AC = 2;
    player->playerStats.maxDMG = 4;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.INT += 2;
    player->playerStats.CHA += 2;
    player->playerStats.ATK = (player->playerStats.CHA - 10) / 2;
}
void AssignCyborg() {
    strcpy(player->playerClass, "Cyborg");
    player->equippedArmor = MetallicSkin();
    player->equippedMelee = ChromeFists();
    player->equippedRanged = Shortbow();
    player->playerStats.HP += 6;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.AC = 3;
    player->playerStats.maxDMG = 6;
    player->playerStats.minDMG = 1;
    player->playerStats.LVL = 1;
    player->playerStats.STR += 2;
    player->playerStats.DEX += 2;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
}


