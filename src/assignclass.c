#include <rogue.h>

// ATK is the players modifier used to determine accuracy for attacks.
// This makes it so stacking dex is not always the go to option.
// Original Fallout games had this problem, where stack AGIL was always #1.

/* Initializes the 1st level version of a class and assigns that class to the player.*/

void AssignKnight() {
    player->equippedArmor = Chainmail();
    player->equippedMelee = Greatsword();
    player->equippedRanged = Shortbow();
    player->playerStats.mana = 12;
    player->playerStats.maxMana = 12;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Knight();
    player->playerStats.CON += (player->playerClass.mainStat);
    player->playerStats.STR += (player->playerClass.secondaryStat);
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
}
void AssignSwashbuckler() {
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Cutlass();
    player->equippedRanged = FlintlockPistol();
    player->playerStats.mana = 12;
    player->playerStats.maxMana = 12;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Swashbuckler();
    player->playerStats.DEX += (player->playerClass.mainStat);
    player->playerStats.CHA += (player->playerClass.secondaryStat);
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
}

void AssignWizard() {
    player->equippedArmor = Robes();
    player->equippedMelee = Quarterstaff();
    player->equippedRanged = LightningWand();
    player->playerStats.mana = 20;
    player->playerStats.maxMana = 20;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Wizard();
    player->playerStats.INT += (player->playerClass.mainStat);
    player->playerStats.ATK = (player->playerStats.INT - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
}
void AssignNecromancer() {
    player->equippedArmor = Robes();
    player->equippedMelee = Dagger();
    player->equippedRanged = AcidPotion();
    player->playerStats.mana = 16;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Necromancer();
    player->playerStats.INT += (player->playerClass.mainStat);
    player->playerStats.WIS += (player->playerClass.secondaryStat);
    player->playerStats.ATK = (player->playerStats.INT - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
}
void AssignGunslinger() {
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Fists();
    player->equippedRanged = FlintlockPistol();
    player->playerStats.mana = 16;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Gunslinger();
    player->playerStats.DEX += (player->playerClass.mainStat);
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
}

void AssignRanger() {
    player->equippedArmor = RangersCloak();
    player->equippedMelee = Longsword();
    player->equippedRanged = Longbow();
    player->playerStats.mana = 16;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Ranger();
    player->playerStats.DEX += (player->playerClass.mainStat);
    player->playerStats.WIS += (player->playerClass.secondaryStat);
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
}
void AssignDarkKnight() {
    player->equippedArmor = Chainmail();
    player->equippedMelee = Greatsword();
    player->equippedRanged = None();
    player->playerStats.mana = 12;
    player->playerStats.maxMana = 12;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = DarkKnight();
    player->playerStats.STR += (player->playerClass.mainStat);
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
}
void AssignAlchemist() {
    player->equippedArmor = Robes();
    player->equippedMelee = Fists();
    player->equippedRanged = AcidPotion();
    player->playerStats.mana = 16;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Alchemist();
    player->playerStats.DEX += (player->playerClass.mainStat);
    player->playerStats.INT += (player->playerClass.secondaryStat);
    player->playerStats.ATK = (player->playerStats.DEX - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    
}
void AssignConjurer() {
    player->equippedArmor = Robes();
    player->equippedMelee = Quarterstaff();
    player->equippedRanged = None();
    player->playerStats.mana = 20;
    player->playerStats.maxMana = 20;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Conjurer();
    player->playerStats.INT += (player->playerClass.mainStat);
    player->playerStats.CHA += (player->playerClass.secondaryStat);
    player->playerStats.ATK = (player->playerStats.CHA - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    
}

void AssignCyborg() {
    player->equippedArmor = MetallicSkin();
    player->equippedMelee = ChromeFists();
    player->equippedRanged = None();
    player->playerStats.mana = 12;
    player->playerStats.maxMana = 12;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerStats.ATK = (player->playerStats.STR - 10) / 2;
    player->playerClass = Cyborg();
    player->playerStats.STR += (player->playerClass.mainStat);
    player->playerStats.DEX += (player->playerClass.secondaryStat);
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
}


