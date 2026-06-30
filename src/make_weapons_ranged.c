#include <rogue.h>


Weapon AcidPotion() {
    Weapon acidPotion;
    acidPotion.item.equippable = true;
    acidPotion.item.unequippable = true;
    acidPotion.item.isEquipped = false;
    acidPotion.item.type = WEAPON;
    acidPotion.item.itemID = ACID_POTION;
    acidPotion.item.quantity = 0;
    acidPotion.item.value = 25;
    acidPotion.isMagic = false;
    acidPotion.isRanged = true;
    acidPotion.minDMG = 2;
    acidPotion.maxDMG = 8;
    acidPotion.range = 6;
    acidPotion.ammoType = TYPE_MAGIC;
    strcpy(acidPotion.item.itemName, "Acid Potion");
    strcpy(acidPotion.item.itemDesc, "A potion of volatile acid.");
    return acidPotion;
}

Weapon Shortbow() {
    Weapon shortbow;
    shortbow.item.equippable = true;
    shortbow.item.unequippable = true;
    shortbow.item.isEquipped = false;
    shortbow.item.type = WEAPON;
    shortbow.item.itemID = SHORTBOW;
    shortbow.item.quantity = 0;
    shortbow.item.value = 25;
    shortbow.isMagic = false;
    shortbow.isRanged = true;
    shortbow.minDMG = 1;
    shortbow.maxDMG = 6;
    shortbow.range = 8;
    shortbow.ammoType = TYPE_ARROWS;
    strcpy(shortbow.item.itemName, "Shortbow");
    strcpy(shortbow.item.itemDesc, "A small bow.");
    return shortbow;
}

Weapon Longbow() {
    Weapon longbow;
    longbow.item.equippable = true;
    longbow.item.unequippable = true;
    longbow.item.isEquipped = false;
    longbow.item.type = WEAPON;
    longbow.item.itemID = LONGBOW;
    longbow.item.quantity = 0;
    longbow.item.value = 50;
    longbow.isMagic = false;
    longbow.isRanged = true;
    longbow.minDMG = 1;
    longbow.maxDMG = 6;
    longbow.range = 8;
    longbow.ammoType = TYPE_ARROWS;
    strcpy(longbow.item.itemName, "Longbow");
    strcpy(longbow.item.itemDesc, "A large bow, capable of achieving great range.");
    return longbow;
}

Weapon FlintlockPistol() {
    Weapon flintlockPistol;
    flintlockPistol.item.equippable = true;
    flintlockPistol.item.unequippable = true;
    flintlockPistol.item.isEquipped = false;
    flintlockPistol.item.type = WEAPON;
    flintlockPistol.item.itemID = FLINTLOCK_PISTOL;
    flintlockPistol.item.quantity = 0;
    flintlockPistol.item.value = 75;
    flintlockPistol.isMagic = false;
    flintlockPistol.isRanged = true;
    flintlockPistol.minDMG = 1;
    flintlockPistol.maxDMG = 8;
    flintlockPistol.range = 4;
    flintlockPistol.ammoType = TYPE_FLINTLOCK;
    strcpy(flintlockPistol.item.itemName, "Flintlock Pistol");
    strcpy(flintlockPistol.item.itemDesc, "A black powder pistol, devastating at close range.");
    return flintlockPistol;
}

Weapon DualFlintlocks() {
    Weapon dualFlintlocks;
    dualFlintlocks.item.equippable = true;
    dualFlintlocks.item.unequippable = true;
    dualFlintlocks.item.isEquipped = false;
    dualFlintlocks.item.type = WEAPON;
    dualFlintlocks.item.itemID = DUAL_FLINTLOCKS;
    dualFlintlocks.item.quantity = 0;
    dualFlintlocks.item.value = 150;
    dualFlintlocks.isMagic = false;
    dualFlintlocks.isRanged = true;
    dualFlintlocks.minDMG = 2;
    dualFlintlocks.maxDMG = 12;
    dualFlintlocks.range = 3;
    dualFlintlocks.ammoType = TYPE_FLINTLOCK;
    strcpy(dualFlintlocks.item.itemName, "Dual Flintlocks");
    strcpy(dualFlintlocks.item.itemDesc, "A pair of black powder hand cannons.");
    return dualFlintlocks;
}

Weapon LightPistol() {
    Weapon lightPistol;
    lightPistol.item.equippable = true;
    lightPistol.item.unequippable = true;
    lightPistol.item.isEquipped = false;
    lightPistol.item.type = WEAPON;
    lightPistol.item.itemID = LIGHT_PISTOL;
    lightPistol.item.quantity = 0;
    lightPistol.item.value = 265;
    lightPistol.isMagic = false;
    lightPistol.isRanged = true;
    lightPistol.minDMG = 1;
    lightPistol.maxDMG = 10;
    lightPistol.range = 5;
    lightPistol.ammoType = TYPE_9MM;
    strcpy(lightPistol.item.itemName, "9mm Pistol");
    strcpy(lightPistol.item.itemDesc, "A small, 9mm pistol.");
    return lightPistol;
}

Weapon MediumPistol() {
    Weapon mediumPistol;
    mediumPistol.item.equippable = true;
    mediumPistol.item.unequippable = true;
    mediumPistol.item.isEquipped = false;
    mediumPistol.item.type = WEAPON;
    mediumPistol.item.itemID = MEDIUM_PISTOL;
    mediumPistol.item.quantity = 0;
    mediumPistol.item.value = 340;
    mediumPistol.isMagic = false;
    mediumPistol.isRanged = true;
    mediumPistol.minDMG = 2;
    mediumPistol.maxDMG = 12;
    mediumPistol.range = 6;
    mediumPistol.ammoType = TYPE_45;
    strcpy(mediumPistol.item.itemName, ".45 Pistol");
    strcpy(mediumPistol.item.itemDesc, "A small, .45 pistol.");
    return mediumPistol;
}

Weapon HeavyPistol() {
    Weapon heavyPistol;
    heavyPistol.item.equippable = true;
    heavyPistol.item.unequippable = true;
    heavyPistol.item.isEquipped = false;
    heavyPistol.item.type = WEAPON;
    heavyPistol.item.itemID = HEAVY_PISTOL;
    heavyPistol.item.quantity = 0;
    heavyPistol.item.value = 460;
    heavyPistol.isMagic = false;
    heavyPistol.isRanged = true;
    heavyPistol.minDMG = 5;
    heavyPistol.maxDMG = 12;
    heavyPistol.range = 6;
    heavyPistol.ammoType = TYPE_50CAL;
    strcpy(heavyPistol.item.itemName, "50 Cal Pistol");
    strcpy(heavyPistol.item.itemDesc, "A Large, 50 Cal pistol.");
    return heavyPistol;
}

Weapon LightningWand() {
    Weapon lightningWand;
    lightningWand.item.equippable = true;
    lightningWand.item.unequippable = true;
    lightningWand.item.isEquipped = false;
    lightningWand.item.type = WEAPON;
    lightningWand.item.itemID = LIGHTNING_WAND;
    lightningWand.item.quantity = 0;
    lightningWand.item.value = 75;
    lightningWand.isMagic = true;
    lightningWand.isRanged = true;
    lightningWand.minDMG = 1;
    lightningWand.maxDMG = 3;
    lightningWand.range = 10;
    lightningWand.ammoType = NULL_AMMO_TYPE;
    lightningWand.isRanged = true;
    strcpy(lightningWand.item.itemName, "Wand of Sparks");
    strcpy(lightningWand.item.itemDesc, "A small wand of sparks, weak but efficient.");
    return lightningWand;
}

