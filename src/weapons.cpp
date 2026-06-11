#include <rogue.h>

Weapon NoWeapon() {
    Weapon none;
    none.item.equippable = true;
    none.item.type = NULL_ITEM_TYPE;
    none.item.itemID = NULL_ITEM_ID;
    none.item.unequippable = false;
    none.item.value = 0;
    none.isMagic = false;
    none.isRanged = false;
    none.minDMG = 0;
    none.maxDMG = 0;
    none.range = 0;
    none.item.itemName = "None";
    return none;
}

Weapon Fists() {
    Weapon fists;
    fists.item.equippable = true;
    fists.item.type = WEAPON;
    fists.item.itemID = FISTS;
    fists.item.unequippable = false;
    fists.item.value = 0;
    fists.isMagic = false;
    fists.isRanged = false;
    fists.minDMG = 1;
    fists.maxDMG = 3;
    fists.range = 0;
    fists.item.itemName = "Fists";
    return fists;
}

Weapon Claws() {
    Weapon claws;
    claws.item.equippable = true;
    claws.item.type = WEAPON;
    claws.item.itemID = CLAWS;
    claws.item.unequippable = false;
    claws.item.value = 0;
    claws.item.itemName = "Claws";
    claws.isMagic = false;
    claws.isRanged = false;
    claws.minDMG = 1;
    claws.maxDMG = 4;
    claws.range = 0;
    claws.item.itemName = "Claws";
    return claws;
}

Weapon Dagger() {
    Weapon dagger;
    dagger.item.equippable = true;
    dagger.item.type = WEAPON;
    dagger.item.itemID = DAGGER;
    dagger.item.unequippable = false;
    dagger.item.value = 5;
    dagger.item.itemName = "Dagger";
    dagger.isMagic = false;
    dagger.isRanged = false;
    dagger.minDMG = 1;
    dagger.maxDMG = 4;
    dagger.range = 0;
    return dagger;
}

Weapon Shortsword() {
    Weapon shortSword;
    shortSword.item.equippable = true;
    shortSword.item.type = WEAPON;
    shortSword.item.itemID = SHORTSWORD;
    shortSword.item.unequippable = false;
    shortSword.item.value = 10;
    shortSword.item.itemName = "Shortsword";
    shortSword.isMagic = false;
    shortSword.isRanged = false;
    shortSword.minDMG = 1;
    shortSword.maxDMG = 6;
    shortSword.range = 0;
    return shortSword;
}

Weapon Longsword() {
    Weapon longSword;
    longSword.item.equippable = true;
    longSword.item.type = WEAPON;
    longSword.item.itemID = LONGSWORD;
    longSword.item.unequippable = false;
    longSword.item.value = 20;
    longSword.item.itemName = "Longsword";
    longSword.isMagic = false;
    longSword.isRanged = false;
    longSword.minDMG = 1;
    longSword.maxDMG = 8;
    longSword.range = 0;
    return longSword;
}

Weapon Greatsword() {
    Weapon greatSword;
    greatSword.item.equippable = true;
    greatSword.item.type = WEAPON;
    greatSword.item.itemID = GREATSWORD;
    greatSword.item.unequippable = false;
    greatSword.item.value = 45;
    greatSword.item.itemName = "Greatsword";
    greatSword.isMagic = false;
    greatSword.isRanged = false;
    greatSword.minDMG = 1;
    greatSword.maxDMG = 10;
    greatSword.range = 0;
    return greatSword;
}

Weapon Cutlass() {
    Weapon cutlass;
    cutlass.item.equippable = true;
    cutlass.item.type = WEAPON;
    cutlass.item.itemID = CUTLASS;
    cutlass.item.unequippable = false;
    cutlass.item.value = 25;
    cutlass.item.itemName = "Cutlass";
    cutlass.isMagic = false;
    cutlass.isRanged = false;
    cutlass.minDMG = 2;
    cutlass.maxDMG = 7;
    cutlass.range = 0;
    return cutlass;
}

Weapon Scimitar() {
    Weapon scimitar;
    scimitar.item.equippable = true;
    scimitar.item.type = WEAPON;
    scimitar.item.itemID = SCIMITAR;
    scimitar.item.unequippable = false;
    scimitar.item.value = 30;
    scimitar.item.itemName = "Scimitar";
    scimitar.isMagic = false;
    scimitar.isRanged = false;
    scimitar.minDMG = 2;
    scimitar.maxDMG = 8;
    scimitar.range = 0;
    return scimitar;
}

Weapon Quarterstaff() {
    Weapon quarterstaff;
    quarterstaff.item.equippable = true;
    quarterstaff.item.type = WEAPON;
    quarterstaff.item.itemID = QUARTERSTAFF;
    quarterstaff.item.unequippable = false;
    quarterstaff.item.value = 10;
    quarterstaff.item.itemName = "Quarterstaff";
    quarterstaff.isMagic = false;
    quarterstaff.isRanged = false;
    quarterstaff.minDMG = 1;
    quarterstaff.maxDMG = 4;
    quarterstaff.range = 0;
    return quarterstaff;
}

Weapon ChromeFists() {
    Weapon chromeFists;
    chromeFists.item.equippable = true;
    chromeFists.item.type = WEAPON;
    chromeFists.item.itemID = CHROME_FISTS;
    chromeFists.item.unequippable = false;
    chromeFists.item.value = 100;
    chromeFists.item.itemName = "Chrome Fists";
    chromeFists.isMagic = false;
    chromeFists.isRanged = false;
    chromeFists.minDMG = 1;
    chromeFists.maxDMG = 6;
    chromeFists.range = 0;
    return chromeFists;
}

Weapon AcidPotion() {
    Weapon acidPotion;
    acidPotion.item.equippable = true;
    acidPotion.item.type = WEAPON;
    acidPotion.item.itemID = ACID_POTION;
    acidPotion.item.unequippable = false;
    acidPotion.item.value = 25;
    acidPotion.item.itemName = "Acid Potion";
    acidPotion.isMagic = false;
    acidPotion.isRanged = true;
    acidPotion.minDMG = 2;
    acidPotion.maxDMG = 8;
    acidPotion.range = 6;
    return acidPotion;
}

Weapon Shortbow() {
    Weapon shortbow;
    shortbow.item.equippable = true;
    shortbow.item.type = WEAPON;
    shortbow.item.itemID = SHORTBOW;
    shortbow.item.unequippable = false;
    shortbow.item.value = 25;
    shortbow.item.itemName = "Shortbow";
    shortbow.isMagic = false;
    shortbow.isRanged = true;
    shortbow.minDMG = 1;
    shortbow.maxDMG = 6;
    shortbow.range = 8;
    return shortbow;
}

Weapon Longbow() {
    Weapon longbow;
    longbow.item.equippable = true;
    longbow.item.type = WEAPON;
    longbow.item.itemID = LONGBOW;
    longbow.item.unequippable = false;
    longbow.item.value = 50;
    longbow.item.itemName = "Longbow";
    longbow.isMagic = false;
    longbow.isRanged = true;
    longbow.minDMG = 1;
    longbow.maxDMG = 8;
    longbow.range = 10;
    return longbow;
}

Weapon FlintlockPistol() {
    Weapon flintlockPistol;
    flintlockPistol.item.equippable = true;
    flintlockPistol.item.type = WEAPON;
    flintlockPistol.item.itemID = FLINTLOCK_PISTOL;
    flintlockPistol.item.unequippable = false;
    flintlockPistol.item.value = 75;
    flintlockPistol.item.itemName = "Flintlock Pistol";
    flintlockPistol.isMagic = false;
    flintlockPistol.isRanged = true;
    flintlockPistol.minDMG = 1;
    flintlockPistol.maxDMG = 8;
    flintlockPistol.range = 5;
    return flintlockPistol;
}

Weapon LightningWand() {
    Weapon lightningWand;
    lightningWand.item.equippable = true;
    lightningWand.item.type = WEAPON;
    lightningWand.item.itemID = LIGHTNING_WAND;
    lightningWand.item.unequippable = false;
    lightningWand.item.value = 75;
    lightningWand.item.itemName = "Wand of Sparks";
    lightningWand.isMagic = true;
    lightningWand.isRanged = true;
    lightningWand.minDMG = 1;
    lightningWand.maxDMG = 3;
    lightningWand.range = 10;
    lightningWand.isRanged = true;
    return lightningWand;
}

Weapon DualFlintlocks() {
    Weapon dualFlintlocks;
    dualFlintlocks.item.equippable = true;
    dualFlintlocks.item.type = WEAPON;
    dualFlintlocks.item.itemID = DUAL_FLINTLOCKS;
    dualFlintlocks.item.unequippable = false;
    dualFlintlocks.item.value = 150;
    dualFlintlocks.item.itemName = "Dual Flintlocks";
    dualFlintlocks.isMagic = false;
    dualFlintlocks.isRanged = true;
    dualFlintlocks.minDMG = 2;
    dualFlintlocks.maxDMG = 12;
    dualFlintlocks.range = 5;
    return dualFlintlocks;
}

