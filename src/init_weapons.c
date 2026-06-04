#include <rogue.h>

Weapon NoWeapon() {
    Weapon none;
    none.item.equippable = true;
    none.item.type = NULL_ITEM;
    none.item.itemID = NULL_ITEM_ID;
    none.isMagic = false;
    none.isRanged = false;
    none.value = 0;
    none.minDMG = 0;
    none.maxDMG = 0;
    none.range = 0;
    strcpy(none.item.itemName, "None");
    return none;
}

Weapon Fists() {
    Weapon fists;
    fists.item.equippable = true;
    fists.item.type = WEAPON;
    fists.item.itemID = FISTS;
    fists.isMagic = false;
    fists.isRanged = false;
    fists.value = 0;
    fists.minDMG = 1;
    fists.maxDMG = 3;
    fists.range = 0;
    strcpy(fists.item.itemName, "Fists");
    return fists;
}

Weapon Claws() {
    Weapon claws;
    claws.item.equippable = true;
    claws.item.type = WEAPON;
    claws.item.itemID = CLAWS;
    claws.isMagic = false;
    claws.isRanged = false;
    claws.value = 0;
    claws.minDMG = 1;
    claws.maxDMG = 4;
    claws.range = 0;
    strcpy(claws.item.itemName, "Claws");
    return claws;
}

Weapon Dagger() {
    Weapon dagger;
    dagger.item.equippable = true;
    dagger.item.type = WEAPON;
    dagger.item.itemID = DAGGER;
    dagger.isMagic = false;
    dagger.isRanged = false;
    dagger.value = 5;
    dagger.minDMG = 1;
    dagger.maxDMG = 4;
    dagger.range = 0;
    strcpy(dagger.item.itemName, "Dagger");
    return dagger;
}

Weapon Shortsword() {
    Weapon shortSword;
    shortSword.item.equippable = true;
    shortSword.item.type = WEAPON;
    shortSword.item.itemID = SHORTSWORD;
    shortSword.isMagic = false;
    shortSword.isRanged = false;
    shortSword.value = 10;
    shortSword.minDMG = 1;
    shortSword.maxDMG = 6;
    shortSword.range = 0;
    strcpy(shortSword.item.itemName, "Shortsword");
    return shortSword;
}

Weapon Longsword() {
    Weapon longSword;
    longSword.item.equippable = true;
    longSword.item.type = WEAPON;
    longSword.item.itemID = LONGSWORD;
    longSword.isMagic = false;
    longSword.isRanged = false;
    longSword.value = 20;
    longSword.minDMG = 1;
    longSword.maxDMG = 8;
    longSword.range = 0;
    strcpy(longSword.item.itemName, "Longsword");
    return longSword;
}

Weapon Greatsword() {
    Weapon greatSword;
    greatSword.item.equippable = true;
    greatSword.item.type = WEAPON;
    greatSword.item.itemID = GREATSWORD;
    greatSword.isMagic = false;
    greatSword.isRanged = false;
    greatSword.value = 45;
    greatSword.minDMG = 1;
    greatSword.maxDMG = 10;
    greatSword.range = 0;
    strcpy(greatSword.item.itemName, "Greatsword");
    return greatSword;
}

Weapon Cutlass() {
    Weapon cutlass;
    cutlass.item.equippable = true;
    cutlass.item.type = WEAPON;
    cutlass.item.itemID = CUTLASS;
    cutlass.isMagic = false;
    cutlass.isRanged = false;
    cutlass.value = 25;
    cutlass.minDMG = 2;
    cutlass.maxDMG = 7;
    cutlass.range = 0;
    strcpy(cutlass.item.itemName, "Cutlass");
    return cutlass;
}

Weapon Scimitar() {
    Weapon scimitar;
    scimitar.item.equippable = true;
    scimitar.item.type = WEAPON;
    scimitar.item.itemID = SCIMITAR;
    scimitar.isMagic = false;
    scimitar.isRanged = false;
    scimitar.value = 30;
    scimitar.minDMG = 2;
    scimitar.maxDMG = 8;
    scimitar.range = 0;
    strcpy(scimitar.item.itemName, "Scimitar");
    return scimitar;
}

Weapon Quarterstaff() {
    Weapon quarterstaff;
    quarterstaff.item.equippable = true;
    quarterstaff.item.type = WEAPON;
    quarterstaff.item.itemID = QUARTERSTAFF;
    quarterstaff.isMagic = false;
    quarterstaff.isRanged = false;
    quarterstaff.value = 10;
    quarterstaff.minDMG = 1;
    quarterstaff.maxDMG = 4;
    quarterstaff.range = 0;
    strcpy(quarterstaff.item.itemName, "Quarterstaff");
    return quarterstaff;
}

Weapon ChromeFists() {
    Weapon chromeFists;
    chromeFists.item.equippable = true;
    chromeFists.item.type = WEAPON;
    chromeFists.item.itemID = CHROME_FISTS;
    chromeFists.isMagic = false;
    chromeFists.isRanged = false;
    chromeFists.value = 100;
    chromeFists.minDMG = 1;
    chromeFists.maxDMG = 6;
    chromeFists.range = 0;
    strcpy(chromeFists.item.itemName, "Chrome Fists");
    return chromeFists;
}

Weapon AcidPotion() {
    Weapon acidPotion;
    acidPotion.item.equippable = true;
    acidPotion.item.type = WEAPON;
    acidPotion.item.itemID = ACID_POTION;
    acidPotion.isMagic = false;
    acidPotion.isRanged = true;
    acidPotion.value = 25;
    acidPotion.minDMG = 2;
    acidPotion.maxDMG = 8;
    acidPotion.range = 6;
    strcpy(acidPotion.item.itemName, "Acid Potion");
    return acidPotion;
}

Weapon Shortbow() {
    Weapon shortbow;
    shortbow.item.equippable = true;
    shortbow.item.type = WEAPON;
    shortbow.item.itemID = SHORTBOW;
    shortbow.isMagic = false;
    shortbow.isRanged = true;
    shortbow.value = 25;
    shortbow.minDMG = 1;
    shortbow.maxDMG = 6;
    shortbow.range = 8;
    strcpy(shortbow.item.itemName, "Short Bow");
    return shortbow;
}

Weapon Longbow() {
    Weapon longbow;
    longbow.item.equippable = true;
    longbow.item.type = WEAPON;
    longbow.item.itemID = LONGBOW;
    longbow.isMagic = false;
    longbow.isRanged = true;
    longbow.value = 50;
    longbow.minDMG = 1;
    longbow.maxDMG = 8;
    longbow.range = 10;
    strcpy(longbow.item.itemName, "Long Bow");
    return longbow;
}

Weapon FlintlockPistol() {
    Weapon flintlockPistol;
    flintlockPistol.item.equippable = true;
    flintlockPistol.item.type = WEAPON;
    flintlockPistol.item.itemID = FLINTLOCK_PISTOL;
    flintlockPistol.isMagic = false;
    flintlockPistol.isRanged = true;
    flintlockPistol.value = 75;
    flintlockPistol.minDMG = 1;
    flintlockPistol.maxDMG = 8;
    flintlockPistol.range = 5;
    strcpy(flintlockPistol.item.itemName, "Flintlock Pistol");
    return flintlockPistol;
}

Weapon LightningWand() {
    Weapon lightningWand;
    lightningWand.item.equippable = true;
    lightningWand.item.type = WEAPON;
    lightningWand.item.itemID = LIGHTNING_WAND;
    lightningWand.isMagic = true;
    lightningWand.isRanged = true;
    lightningWand.value = 75;
    lightningWand.minDMG = 1;
    lightningWand.maxDMG = 3;
    lightningWand.range = 10;
    lightningWand.isRanged = true;
    strcpy(lightningWand.item.itemName, "Wand of Sparks");
    return lightningWand;
}

Weapon DualFlintlocks() {
    Weapon dualFlintlocks;
    dualFlintlocks.item.equippable = true;
    dualFlintlocks.item.type = WEAPON;
    dualFlintlocks.item.itemID = DUAL_FLINTLOCKS;
    dualFlintlocks.isMagic = false;
    dualFlintlocks.isRanged = true;
    dualFlintlocks.value = 150;
    dualFlintlocks.minDMG = 2;
    dualFlintlocks.maxDMG = 12;
    dualFlintlocks.range = 5;
    strcpy(dualFlintlocks.item.itemName, "Dual Flintlocks");
    return dualFlintlocks;
}

