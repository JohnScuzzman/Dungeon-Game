#include <rogue.h>

// ATK is the players modifier used to determine accuracy for attacks.
// This makes it so stacking dex is not always the go to option.
// Original Fallout games had this problem, where stack AGIL was always #1.

/* Initializes the 1st level version of a class and assigns that class to the player.*/

void AssignKnight() {
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Longsword();
    player->equippedRanged = Shortbow();
    player->equippedAmmo = Arrows();
    AddToPlayerInventory(items[LEATHER_ARMOR], 1);
    AddToPlayerInventory(items[LONGSWORD], 1);
    AddToPlayerInventory(items[SHORTBOW], 1);
    AddToPlayerInventory(items[ARROWS], 20);
    player->equippedAmmo.item.quantity = 20;
    player->playerStats.mana = 16;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Knight();
    player->playerStats.CON += (player->playerClass.mainStat);
    player->playerStats.STR += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.STR) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
}

void AssignSwashbuckler() {
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Cutlass();
    player->equippedRanged = FlintlockPistol();
    player->equippedAmmo = BulletFlintlock();
    AddToPlayerInventory(items[LEATHER_ARMOR], 1);
    AddToPlayerInventory(items[CUTLASS], 1);
    AddToPlayerInventory(items[FLINTLOCK_PISTOL], 1);
    AddToPlayerInventory(items[BULLET_FLINTLOCK], 20);
    player->equippedAmmo.item.quantity = 20;
    player->playerStats.mana = 16;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Swashbuckler();
    player->playerStats.DEX += (player->playerClass.mainStat);
    player->playerStats.CHA += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.DEX) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
}

void AssignWizard() {
    player->equippedArmor = Robes();
    player->equippedMelee = Quarterstaff();
    player->equippedRanged = LightningWand();
    AddToPlayerInventory(items[ROBES], 1);
    AddToPlayerInventory(items[QUARTERSTAFF], 1);
    AddToPlayerInventory(items[LIGHTNING_WAND], 1);
    player->playerStats.mana = 20;
    player->playerStats.maxMana = 20;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Wizard();
    player->playerStats.INT += (player->playerClass.mainStat);
    player->playerStats.ATK = ((player->playerStats.INT) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
}

void AssignNecromancer() {
    player->equippedArmor = Robes();
    player->equippedMelee = Dagger();
    player->equippedRanged = Slingshot();
    player->equippedAmmo = AcidPotionAmmo();
    AddToPlayerInventory(items[ROBES], 1);
    AddToPlayerInventory(items[DAGGER], 1);
    AddToPlayerInventory(items[SLINGSHOT], 1);
    AddToPlayerInventory(items[ACID_POTION_AMMO], 10);
    player->equippedAmmo.item.quantity = 10;
    player->playerStats.mana = 16;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Necromancer();
    player->playerStats.INT += (player->playerClass.mainStat);
    player->playerStats.WIS += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.INT) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
}

void AssignGunslinger() {
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Fists();
    player->equippedRanged = FlintlockRifle();
    player->equippedAmmo = BulletFlintlock();
    AddToPlayerInventory(items[LEATHER_ARMOR], 1);
    AddToPlayerInventory(items[FLINTLOCK_RIFLE], 1);
    AddToPlayerInventory(items[BULLET_FLINTLOCK], 20);
    player->equippedAmmo.item.quantity = 20;
    player->playerStats.mana = 16;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Gunslinger();
    player->playerStats.DEX += (player->playerClass.mainStat);
    player->playerStats.ATK = ((player->playerStats.DEX) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
}
void AssignDruid() {
    player->equippedArmor = Robes();
    player->equippedMelee = Claws();
    player->equippedRanged = LightningWand();
    player->equippedAmmo = NoAmmo();
    AddToPlayerInventory(items[ROBES], 1);
    AddToPlayerInventory(items[LIGHTNING_WAND], 1);
    player->playerStats.mana = 20;
    player->playerStats.maxMana = 20;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Druid();
    player->playerStats.WIS += (player->playerClass.mainStat);
    player->playerStats.ATK = ((player->playerStats.WIS) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
}

void AssignRanger() {
    player->equippedArmor = RangersCloak();
    player->equippedMelee = Longsword();
    player->equippedRanged = Longbow();
    player->equippedAmmo = Arrows();
    AddToPlayerInventory(items[RANGERS_CLOAK], 1);
    AddToPlayerInventory(items[LONGSWORD], 1);
    AddToPlayerInventory(items[LONGBOW], 1);
    AddToPlayerInventory(items[ARROWS], 20);
    player->equippedAmmo.item.quantity = 20;
    player->playerStats.mana = 16;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Ranger();
    player->playerStats.DEX += (player->playerClass.mainStat);
    player->playerStats.WIS += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.DEX) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
}

void AssignDarkKnight() {
    player->equippedArmor = LeatherArmor();
    player->equippedMelee = Longsword();
    player->equippedRanged = NoWeapon();
    player->equippedAmmo = NoAmmo();
    AddToPlayerInventory(items[LEATHER_ARMOR], 1);
    AddToPlayerInventory(items[LONGSWORD], 1);
    player->playerStats.mana = 16;
    player->playerStats.maxMana = 16;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = DarkKnight();
    player->playerStats.STR += (player->playerClass.mainStat);
    player->playerStats.ATK = ((player->playerStats.STR) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
}

void AssignWarlock() {
    player->equippedArmor = Robes();
    player->equippedMelee = Dagger();
    player->equippedRanged = LightningWand();
    player->equippedAmmo = NoAmmo();
    AddToPlayerInventory(items[ROBES], 1);
    AddToPlayerInventory(items[DAGGER], 1);
    AddToPlayerInventory(items[LIGHTNING_WAND], 1);
    player->playerStats.mana = 20;
    player->playerStats.maxMana = 20;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Warlock();
    player->playerStats.CHA += (player->playerClass.mainStat);
    player->playerStats.ATK = ((player->playerStats.CHA) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
    
}

void AssignConjurer() {
    player->equippedArmor = Robes();
    player->equippedMelee = Quarterstaff();
    player->equippedRanged = Slingshot();
    player->equippedAmmo = AcidPotionAmmo();
    AddToPlayerInventory(items[ROBES], 1);
    AddToPlayerInventory(items[QUARTERSTAFF], 1);
    AddToPlayerInventory(items[SLINGSHOT], 1);
    AddToPlayerInventory(items[ACID_POTION_AMMO], 10);
    player->equippedAmmo.item.quantity = 10;
    player->playerStats.mana = 20;
    player->playerStats.maxMana = 20;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Conjurer();
    player->playerStats.INT += (player->playerClass.mainStat);
    player->playerStats.CHA += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.CHA) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
    
}

void AssignCyborg() {
    player->equippedArmor = MetallicSkin();
    player->equippedMelee = ChromeFists();
    player->equippedRanged = NoWeapon();
    player->equippedAmmo = NoAmmo();
    AddToPlayerInventory(items[METALLIC_SKIN], 1);
    AddToPlayerInventory(items[CHROME_FISTS], 1);
    player->playerStats.mana = 20;
    player->playerStats.maxMana = 20;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Cyborg();
    player->playerStats.STR += (player->playerClass.mainStat);
    player->playerStats.DEX += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.STR) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
}

void AssignBard() {
    player->equippedArmor = RangersCloak();
    player->equippedMelee = Dagger();
    player->equippedRanged = Shortbow();
    player->equippedAmmo = Arrows();
    AddToPlayerInventory(items[RANGERS_CLOAK], 1);
    AddToPlayerInventory(items[DAGGER], 1);
    AddToPlayerInventory(items[SHORTBOW], 1);
    AddToPlayerInventory(items[ARROWS], 20);
    player->equippedAmmo.item.quantity = 20;
    player->playerStats.mana = 20;
    player->playerStats.maxMana = 20;
    player->playerStats.AC = player->equippedArmor.AC;
    player->playerStats.LVL = 1;
    player->playerClass = Bard();
    player->playerStats.CHA += (player->playerClass.mainStat);
    player->playerStats.DEX += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.CHA) - 10) / 2;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->passiveAbility = NoAbility();
}

/*
Assigns the class chosen by the player to the Entity struct player.
Each method is listed in classes.c.
The numbers are the combination of x + y coordinates in MakePlayer
*/
void AssignClass(int input) {
    switch(input){
        case KNIGHT:
            AssignKnight();
            break;
        case SWASHBUCKLER:
            AssignSwashbuckler();
            break;
        case WIZARD:
            AssignWizard();
            break;
        case NECROMANCER:
            AssignNecromancer();
            break;
        case GUNSLINGER:
            AssignGunslinger();
            break;
        case DRUID:
            AssignDruid();
            break;
        case RANGER:
            AssignRanger();
            break;
        case DARK_KNIGHT:
            AssignDarkKnight();
            break;
        case WARLOCK:
            AssignWarlock();
            break;
        case CONJURER:
            AssignConjurer();
            break;
        case CYBORG:
            AssignCyborg();
            break;
        case BARD:
            AssignBard();
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
    player->playerStats.nextLVLEXP = LEVEL_2;
    switch(input){
        case HUMAN:
            player->raceID = HUMAN;
            strcpy(player->playerRace, "Human");
            player->playerStats.maxHP = 10;
            player->playerStats.CHA = 12;
            player->playerStats.CON = 12;
            player->playerStats.DEX = 12;
            player->playerStats.INT = 12;
            player->playerStats.STR = 12;
            player->playerStats.WIS = 12;
        break;
        case ELF:
            player->raceID = ELF;
            strcpy(player->playerRace, "Elf");
            player->playerStats.maxHP = 8;
            player->playerStats.CHA = 12;
            player->playerStats.CON = 10;
            player->playerStats.DEX = 16;
            player->playerStats.INT = 14;
            player->playerStats.STR = 10;
            player->playerStats.WIS = 12;
        break;
        case DWARF:
            player->raceID = DWARF;
            strcpy(player->playerRace, "Dwarf");
            player->playerStats.maxHP = 10;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 14;
            player->playerStats.DEX = 10;
            player->playerStats.INT = 10;
            player->playerStats.STR = 14;
            player->playerStats.WIS = 16;
        break;
        case DRAGONBORN:
            player->raceID = DRAGONBORN;
            strcpy(player->playerRace, "Dragonborn");
            player->playerStats.maxHP = 12;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 16;
            player->playerStats.DEX = 8;
            player->playerStats.INT = 10;
            player->playerStats.STR = 16;
            player->playerStats.WIS = 10;
        break;
        case GNOLL:
            player->raceID = GNOLL;
            strcpy(player->playerRace, "Gnoll");
            player->playerStats.maxHP = 12;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 16;
            player->playerStats.DEX = 10;
            player->playerStats.INT = 8;
            player->playerStats.STR = 16;
            player->playerStats.WIS = 10;
        break;
        case CANIDAE:
            player->raceID = CANIDAE;
            strcpy(player->playerRace, "Canidae");
            player->playerStats.maxHP = 12;
            player->playerStats.CHA = 12;
            player->playerStats.CON = 16;
            player->playerStats.DEX = 10;
            player->playerStats.INT = 8;
            player->playerStats.STR = 14;
            player->playerStats.WIS = 10;
        break;
        case SKELETON:
            player->raceID = SKELETON;
            strcpy(player->playerRace, "Skeleton");
            player->playerStats.maxHP = 8;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 14;
            player->playerStats.DEX = 12;
            player->playerStats.INT = 16;
            player->playerStats.STR = 8;
            player->playerStats.WIS = 14;
        break;
        case MANTIS:
            player->raceID = MANTIS;
            strcpy(player->playerRace, "Mantis");
            player->playerStats.maxHP = 12;
            player->playerStats.CHA = 8;
            player->playerStats.CON = 14;
            player->playerStats.DEX = 12;
            player->playerStats.INT = 10;
            player->playerStats.STR = 16;
            player->playerStats.WIS = 10;
        break;
        case AUTOMATON:
            player->raceID = AUTOMATON;
            strcpy(player->playerRace, "Automaton");
            player->playerStats.maxHP = 10;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 16;
            player->playerStats.DEX = 10;
            player->playerStats.INT = 12;
            player->playerStats.STR = 14;
            player->playerStats.WIS = 10;
        break;
        case WEREWOLF:
            player->raceID = WEREWOLF;
            strcpy(player->playerRace, "Werewolf");
            player->playerStats.maxHP = 12;
            player->playerStats.CHA = 10;
            player->playerStats.CON = 16;
            player->playerStats.DEX = 14;
            player->playerStats.INT = 8;
            player->playerStats.STR = 16;
            player->playerStats.WIS = 8;
        break;
        case VAMPIRE:
            player->raceID = VAMPIRE;
            strcpy(player->playerRace, "Vampire");
            player->playerStats.maxHP = 10;
            player->playerStats.CHA = 16;
            player->playerStats.CON = 10;
            player->playerStats.DEX = 12;
            player->playerStats.INT = 14;
            player->playerStats.STR = 10;
            player->playerStats.WIS = 10;
        break;
        case SUCCUBUS:
            player->raceID = SUCCUBUS;
            strcpy(player->playerRace, "Succubus");
            player->playerStats.maxHP = 8;
            player->playerStats.CHA = 16;
            player->playerStats.CON = 10;
            player->playerStats.DEX = 12;
            player->playerStats.INT = 14;
            player->playerStats.STR = 8;
            player->playerStats.WIS = 12;
        break;
        default:
            player->raceID = HUMAN;
            strcpy(player->playerRace, "Human");
            player->playerStats.maxHP = 10;
            player->playerStats.CHA = 12;
            player->playerStats.CON = 12;
            player->playerStats.DEX = 12;
            player->playerStats.INT = 12;
            player->playerStats.STR = 12;
            player->playerStats.WIS = 12;
        break;
    }
}

