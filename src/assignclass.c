#include <rogue.h>

// ATK is the players modifier used to determine accuracy for attacks.
// This makes it so stacking dex is not always the go to option.
// Original Fallout games had this problem, where stack AGIL was always #1.

/* Initializes the 1st level version of a class and assigns that class to the player.*/

void AssignKnight() {
    player->playerClass = Knight();
    player->equippedArmor = Chainmail();
    player->equippedMelee = Greatsword();
    player->equippedRanged = Shortbow();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 10;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 10;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.CON += player->playerClass.mainStat;
    player->playerStats.STR += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
}
void AssignSwashbuckler() {
    player->playerClass = Swashbuckler();
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Cutlass();
    player->equippedRanged = FlintlockPistol();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 10;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 10;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += player->playerClass.mainStat;
    player->playerStats.CHA += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
}
void AssignWizard() {
    player->playerClass = Wizard();
    player->equippedArmor = Robes();
    player->equippedMelee = Quarterstaff();
    player->equippedRanged = LightningWand();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 20;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 20;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.INT += 4;
    player->playerStats.ATK = (player->playerStats.INT - 10) / 2;
}
void AssignNecromancer() {
    player->playerClass = Necromancer();
    player->equippedArmor = Robes();
    player->equippedMelee = Dagger();
    player->equippedRanged = AcidPotion();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 16;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.INT += player->playerClass.mainStat;
    player->playerStats.WIS += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.INT - 10) / 2;
}
void AssignGunslinger() {
    player->playerClass = Gunslinger();
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Fists();
    player->equippedRanged = FlintlockPistol();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 10;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 10;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += 4;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
}
void AssignRanger() {
    player->playerClass = Ranger();
    player->equippedArmor = RangersCloak();
    player->equippedMelee = Longsword();
    player->equippedRanged = Longbow();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 10;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 10;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += player->playerClass.mainStat;
    player->playerStats.WIS += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
}
void AssignDarkKnight() {
    player->playerClass = DarkKnight();
    player->equippedArmor = Chainmail();
    player->equippedMelee = Greatsword();
    player->equippedRanged = None();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 10;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 10;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.STR += 4;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
}
void AssignAlchemist() {
    player->playerClass = Alchemist();
    player->equippedArmor = Robes();
    player->equippedMelee = Fists();
    player->equippedRanged = AcidPotion();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 10;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 10;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += player->playerClass.mainStat;
    player->playerStats.INT += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
}
void AssignConjurer() {
    player->playerClass = Conjurer();
    player->equippedArmor = Robes();
    player->equippedMelee = Quarterstaff();
    player->equippedRanged = None();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 16;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.INT += player->playerClass.mainStat;
    player->playerStats.CHA += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.CHA - 10) / 2;
}

void AssignCyborg() {
    player->playerClass = Cyborg();
    player->equippedArmor = MetallicSkin();
    player->equippedMelee = ChromeFists();
    player->equippedRanged = None();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 10;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 10;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.STR += player->playerClass.mainStat;
    player->playerStats.DEX += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
}


