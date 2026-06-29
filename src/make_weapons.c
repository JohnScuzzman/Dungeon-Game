#include <rogue.h>

Weapon NoWeapon() {
    Weapon none;
    none.item.equippable = true;
    none.item.unequippable = false;
    none.item.isEquipped = false;
    none.item.type = NULL_ITEM_TYPE;
    none.item.itemID = NULL_ITEM_ID;
    none.item.quantity = 0;
    none.item.value = 0;
    none.isMagic = false;
    none.isRanged = false;
    none.minDMG = 0;
    none.maxDMG = 0;
    none.range = 0;
    none.ammoType = NULL_AMMO_TYPE;
    strcpy(none.item.itemName, "None");
    return none;
}

Weapon Fists() {
    Weapon fists;
    fists.item.equippable = true;
    fists.item.unequippable = false;
    fists.item.isEquipped = false;
    fists.item.type = WEAPON;
    fists.item.itemID = FISTS;
    fists.item.quantity = 0;
    fists.item.value = 0;
    fists.isMagic = false;
    fists.isRanged = false;
    fists.minDMG = 1;
    fists.maxDMG = 3;
    fists.range = 0;
    fists.ammoType = NULL_AMMO_TYPE;
    strcpy(fists.item.itemName, "Fists");
    return fists;
}

Weapon Claws() {
    Weapon claws;
    claws.item.equippable = true;
    claws.item.unequippable = false;
    claws.item.isEquipped = false;
    claws.item.type = WEAPON;
    claws.item.itemID = CLAWS;
    claws.item.quantity = 0;
    claws.item.value = 0;
    strcpy(claws.item.itemName, "Claws");
    claws.isMagic = false;
    claws.isRanged = false;
    claws.minDMG = 1;
    claws.maxDMG = 4;
    claws.range = 0;
    claws.ammoType = NULL_AMMO_TYPE;
    strcpy(claws.item.itemName, "Claws");
    return claws;
}

Weapon Dagger() {
    Weapon dagger;
    dagger.item.equippable = true;
    dagger.item.unequippable = false;
    dagger.item.isEquipped = false;
    dagger.item.type = WEAPON;
    dagger.item.itemID = DAGGER;
    dagger.item.quantity = 0;
    dagger.item.value = 5;
    strcpy(dagger.item.itemName, "Dagger");
    dagger.isMagic = false;
    dagger.isRanged = false;
    dagger.minDMG = 1;
    dagger.maxDMG = 4;
    dagger.range = 0;
    dagger.ammoType = NULL_AMMO_TYPE;
    return dagger;
}

Weapon Shortsword() {
    Weapon shortSword;
    shortSword.item.equippable = true;
    shortSword.item.unequippable = false;
    shortSword.item.isEquipped = false;
    shortSword.item.type = WEAPON;
    shortSword.item.itemID = SHORTSWORD;
    shortSword.item.quantity = 0;
    shortSword.item.value = 10;
    strcpy(shortSword.item.itemName, "Shortsword");
    shortSword.isMagic = false;
    shortSword.isRanged = false;
    shortSword.minDMG = 1;
    shortSword.maxDMG = 6;
    shortSword.range = 0;
    shortSword.ammoType = NULL_AMMO_TYPE;
    return shortSword;
}

Weapon Quarterstaff() {
    Weapon quarterstaff;
    quarterstaff.item.equippable = true;
    quarterstaff.item.unequippable = false;
    quarterstaff.item.isEquipped = false;
    quarterstaff.item.type = WEAPON;
    quarterstaff.item.itemID = QUARTERSTAFF;
    quarterstaff.item.quantity = 0;
    quarterstaff.item.value = 10;
    strcpy(quarterstaff.item.itemName, "Quarterstaff");
    quarterstaff.isMagic = false;
    quarterstaff.isRanged = false;
    quarterstaff.minDMG = 1;
    quarterstaff.maxDMG = 4;
    quarterstaff.range = 0;
    quarterstaff.ammoType = NULL_AMMO_TYPE;
    return quarterstaff;
}

Weapon Longsword() {
    Weapon longSword;
    longSword.item.equippable = true;
    longSword.item.unequippable = false;
    longSword.item.isEquipped = false;
    longSword.item.type = WEAPON;
    longSword.item.itemID = LONGSWORD;
    longSword.item.quantity = 0;
    longSword.item.value = 20;
    strcpy(longSword.item.itemName, "Longsword");
    longSword.isMagic = false;
    longSword.isRanged = false;
    longSword.minDMG = 1;
    longSword.maxDMG = 8;
    longSword.range = 0;
    longSword.ammoType = NULL_AMMO_TYPE;
    return longSword;
}

Weapon Greatsword() {
    Weapon greatSword;
    greatSword.item.equippable = true;
    greatSword.item.unequippable = false;
    greatSword.item.isEquipped = false;
    greatSword.item.type = WEAPON;
    greatSword.item.itemID = GREATSWORD;
    greatSword.item.quantity = 0;
    greatSword.item.value = 45;
    strcpy(greatSword.item.itemName, "Greatsword");
    greatSword.isMagic = false;
    greatSword.isRanged = false;
    greatSword.minDMG = 1;
    greatSword.maxDMG = 10;
    greatSword.range = 0;
    greatSword.ammoType = NULL_AMMO_TYPE;
    return greatSword;
}

Weapon Cutlass() {
    Weapon cutlass;
    cutlass.item.equippable = true;
    cutlass.item.unequippable = false;
    cutlass.item.isEquipped = false;
    cutlass.item.type = WEAPON;
    cutlass.item.itemID = CUTLASS;
    cutlass.item.quantity = 0;
    cutlass.item.value = 25;
    strcpy(cutlass.item.itemName, "Cutlass");
    cutlass.isMagic = false;
    cutlass.isRanged = false;
    cutlass.minDMG = 2;
    cutlass.maxDMG = 7;
    cutlass.range = 0;
    cutlass.ammoType = NULL_AMMO_TYPE;
    return cutlass;
}

Weapon Scimitar() {
    Weapon scimitar;
    scimitar.item.equippable = true;
    scimitar.item.unequippable = false;
    scimitar.item.isEquipped = false;
    scimitar.item.type = WEAPON;
    scimitar.item.itemID = SCIMITAR;
    scimitar.item.quantity = 0;
    scimitar.item.value = 30;
    strcpy(scimitar.item.itemName, "Scimitar");
    scimitar.isMagic = false;
    scimitar.isRanged = false;
    scimitar.minDMG = 2;
    scimitar.maxDMG = 8;
    scimitar.range = 0;
    scimitar.ammoType = NULL_AMMO_TYPE;
    return scimitar;
}


Weapon ChromeFists() {
    Weapon chromeFists;
    chromeFists.item.equippable = true;
    chromeFists.item.unequippable = false;
    chromeFists.item.isEquipped = false;
    chromeFists.item.type = WEAPON;
    chromeFists.item.itemID = CHROME_FISTS;
    chromeFists.item.quantity = 0;
    chromeFists.item.value = 100;
    strcpy(chromeFists.item.itemName, "Chrome Fists");
    chromeFists.isMagic = false;
    chromeFists.isRanged = false;
    chromeFists.minDMG = 1;
    chromeFists.maxDMG = 6;
    chromeFists.range = 0;
    chromeFists.ammoType = NULL_AMMO_TYPE;
    return chromeFists;
}

Weapon AcidPotion() {
    Weapon acidPotion;
    acidPotion.item.equippable = true;
    acidPotion.item.unequippable = false;
    acidPotion.item.isEquipped = false;
    acidPotion.item.type = WEAPON;
    acidPotion.item.itemID = ACID_POTION;
    acidPotion.item.quantity = 0;
    acidPotion.item.value = 25;
    strcpy(acidPotion.item.itemName, "Acid Potion");
    acidPotion.isMagic = false;
    acidPotion.isRanged = true;
    acidPotion.minDMG = 2;
    acidPotion.maxDMG = 8;
    acidPotion.range = 6;
    acidPotion.ammoType = ACID_POTION_AMMO;
    return acidPotion;
}

Weapon Shortbow() {
    Weapon shortbow;
    shortbow.item.equippable = true;
    shortbow.item.unequippable = false;
    shortbow.item.isEquipped = false;
    shortbow.item.type = WEAPON;
    shortbow.item.itemID = SHORTBOW;
    shortbow.item.quantity = 0;
    shortbow.item.value = 25;
    strcpy(shortbow.item.itemName, "Shortbow");
    shortbow.isMagic = false;
    shortbow.isRanged = true;
    shortbow.minDMG = 1;
    shortbow.maxDMG = 6;
    shortbow.range = 8;
    shortbow.ammoType = ARROWS;
    return shortbow;
}

Weapon Longbow() {
    Weapon longbow;
    longbow.item.equippable = true;
    longbow.item.unequippable = false;
    longbow.item.isEquipped = false;
    longbow.item.type = WEAPON;
    longbow.item.itemID = LONGBOW;
    longbow.item.quantity = 0;
    longbow.item.value = 50;
    strcpy(longbow.item.itemName, "Longbow");
    longbow.isMagic = false;
    longbow.isRanged = true;
    longbow.minDMG = 1;
    longbow.maxDMG = 8;
    longbow.range = 10;
    longbow.ammoType = ARROWS;
    return longbow;
}

Weapon FlintlockPistol() {
    Weapon flintlockPistol;
    flintlockPistol.item.equippable = true;
    flintlockPistol.item.unequippable = false;
    flintlockPistol.item.isEquipped = false;
    flintlockPistol.item.type = WEAPON;
    flintlockPistol.item.itemID = FLINTLOCK_PISTOL;
    flintlockPistol.item.quantity = 0;
    flintlockPistol.item.value = 75;
    strcpy(flintlockPistol.item.itemName, "Flintlock Pistol");
    flintlockPistol.isMagic = false;
    flintlockPistol.isRanged = true;
    flintlockPistol.minDMG = 1;
    flintlockPistol.maxDMG = 8;
    flintlockPistol.range = 5;
    flintlockPistol.ammoType = BULLET_MUSKET;
    return flintlockPistol;
}

Weapon LightningWand() {
    Weapon lightningWand;
    lightningWand.item.equippable = true;
    lightningWand.item.unequippable = false;
    lightningWand.item.isEquipped = false;
    lightningWand.item.type = WEAPON;
    lightningWand.item.itemID = LIGHTNING_WAND;
    lightningWand.item.quantity = 0;
    lightningWand.item.value = 75;
    strcpy(lightningWand.item.itemName, "Wand of Sparks");
    lightningWand.isMagic = true;
    lightningWand.isRanged = true;
    lightningWand.minDMG = 1;
    lightningWand.maxDMG = 3;
    lightningWand.range = 10;
    lightningWand.ammoType = NULL_AMMO_TYPE;
    lightningWand.isRanged = true;
    return lightningWand;
}

Weapon DualFlintlocks() {
    Weapon dualFlintlocks;
    dualFlintlocks.item.equippable = true;
    dualFlintlocks.item.unequippable = false;
    dualFlintlocks.item.isEquipped = false;
    dualFlintlocks.item.type = WEAPON;
    dualFlintlocks.item.itemID = DUAL_FLINTLOCKS;
    dualFlintlocks.item.quantity = 0;
    dualFlintlocks.item.value = 150;
    strcpy(dualFlintlocks.item.itemName, "Dual Flintlocks");
    dualFlintlocks.isMagic = false;
    dualFlintlocks.isRanged = true;
    dualFlintlocks.minDMG = 2;
    dualFlintlocks.maxDMG = 12;
    dualFlintlocks.range = 5;
    dualFlintlocks.ammoType = BULLET_MUSKET;
    return dualFlintlocks;
}

