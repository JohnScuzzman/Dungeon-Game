#include <rogue.h>

// ATK is the players modifier used to determine accuracy for attacks.
// This makes it so stacking dex is not always the go to option.
// Original Fallout games had this problem, where stack AGIL was always #1.

/* Initializes the 1st level version of a class and assigns that class to the player.*/

void AssignKnight() {
    player->equippedArmor = Chainmail();
    player->equippedMelee = Greatsword();
    player->equippedRanged = Shortbow();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 12;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 12;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.CON += player->playerClass.mainStat;
    player->playerStats.STR += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
    player->playerClass = Knight();
}
void AssignSwashbuckler() {
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Cutlass();
    player->equippedRanged = FlintlockPistol();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 12;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 12;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += player->playerClass.mainStat;
    player->playerStats.CHA += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
    player->playerClass = Swashbuckler();
}

void AssignWizard() {
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
    player->playerClass = Wizard();
}
void AssignNecromancer() {
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
    player->playerClass = Necromancer();
}
void AssignGunslinger() {
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Fists();
    player->equippedRanged = FlintlockPistol();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 16;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += 4;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
    player->playerClass = Gunslinger();
}
void AssignRanger() {
    player->equippedArmor = RangersCloak();
    player->equippedMelee = Longsword();
    player->equippedRanged = Longbow();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 16;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += player->playerClass.mainStat;
    player->playerStats.WIS += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
    player->playerClass = Ranger();
}
void AssignDarkKnight() {
    player->equippedArmor = Chainmail();
    player->equippedMelee = Greatsword();
    player->equippedRanged = None();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 12;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 12;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.STR += 4;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
    player->playerClass = DarkKnight();
}
void AssignAlchemist() {
    player->equippedArmor = Robes();
    player->equippedMelee = Fists();
    player->equippedRanged = AcidPotion();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 16;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.DEX += player->playerClass.mainStat;
    player->playerStats.INT += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
    player->playerClass = Alchemist();
}
void AssignConjurer() {
    player->equippedArmor = Robes();
    player->equippedMelee = Quarterstaff();
    player->equippedRanged = None();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 20;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 20;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.INT += player->playerClass.mainStat;
    player->playerStats.CHA += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.CHA - 10) / 2;
    player->playerClass = Conjurer();
}

void AssignCyborg() {
    player->equippedArmor = MetallicSkin();
    player->equippedMelee = ChromeFists();
    player->equippedRanged = None();
    player->playerStats.HP += player->playerClass.hpPerLVL;
    player->playerStats.mana = 12;
    player->playerStats.maxHP = player->playerStats.HP;
    player->playerStats.maxMana = 12;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.STR += player->playerClass.mainStat;
    player->playerStats.DEX += player->playerClass.secondaryStat;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
    player->playerClass = Cyborg();
}


