#include <rogue.h>


Weapon Slingshot() {
    Weapon slingShot;
    slingShot.item.equippable = true;
    slingShot.item.unequippable = true;
    slingShot.item.isEquipped = false;
    slingShot.item.type = WEAPON;
    slingShot.item.itemID = SLINGSHOT;
    slingShot.item.quantity = 0;
    slingShot.item.value = 25;
    slingShot.isMagic = false;
    slingShot.isRanged = true;
    slingShot.minDMG = 1;
    slingShot.maxDMG = 4;
    slingShot.range = 6;
    slingShot.ammoType = TYPE_THROWABLE;
    slingShot.statUsed = DEX;
    slingShot.statReq = 8;
    strcpy(slingShot.item.itemName, "Slingshot");
    strcpy(slingShot.item.itemDesc, "A wrist-mounted slingshot.");
    return slingShot;
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
    shortbow.statUsed = DEX;
    shortbow.statReq = 8;
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
    longbow.statUsed = DEX;
    longbow.statReq = 10;
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
    flintlockPistol.range = 5;
    flintlockPistol.ammoType = TYPE_FLINTLOCK;
    flintlockPistol.statUsed = STR;
    flintlockPistol.statReq = 6;
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
    dualFlintlocks.range = 4;
    dualFlintlocks.ammoType = TYPE_FLINTLOCK;
    dualFlintlocks.statUsed = DEX;
    dualFlintlocks.statReq = 10;
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
    lightPistol.range = 6;
    lightPistol.ammoType = TYPE_9MM;
    lightPistol.statUsed = DEX;
    lightPistol.statReq = 6;
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
    mediumPistol.range = 7;
    mediumPistol.ammoType = TYPE_45;
    mediumPistol.statUsed = DEX;
    mediumPistol.statReq = 8;
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
    heavyPistol.range = 7;
    heavyPistol.ammoType = TYPE_50CAL;
    heavyPistol.statUsed = STR;
    heavyPistol.statReq = 12;
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
    lightningWand.statUsed = INT;
    lightningWand.statReq = 10;
    strcpy(lightningWand.item.itemName, "Wand of Sparks");
    strcpy(lightningWand.item.itemDesc, "A small wand of sparks, weak but efficient.");
    return lightningWand;
}

