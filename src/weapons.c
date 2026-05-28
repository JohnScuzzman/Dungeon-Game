// void CreateMeleeWeapons() {

// }

// void CreateRangedWeapons() {

// }


#include <rogue.h>
Weapon None() {
    Weapon none;
    none.weaponID = 0;
    none.value = 0;
    none.minDMG = 0;
    none.maxDMG = 0;
    none.range = 0;
    none.isRanged = false;
    strcpy(none.weaponName, "None");
    return none;
}

Weapon Fists() {
    Weapon fists;
    fists.weaponID = 1;
    fists.value = 0;
    fists.minDMG = 1;
    fists.maxDMG = 3;
    fists.range = 0;
    fists.isRanged = false;
    strcpy(fists.weaponName, "Fists");
    return fists;
}

Weapon Claws() {
    Weapon claws;
    claws.weaponID = 2;
    claws.value = 0;
    claws.minDMG = 1;
    claws.maxDMG = 4;
    claws.range = 0;
    claws.isRanged = false;
    strcpy(claws.weaponName, "Claws");
    return claws;
}

Weapon Dagger() {
    Weapon dagger;
    dagger.weaponID = 3;
    dagger.value = 5;
    dagger.minDMG = 1;
    dagger.maxDMG = 4;
    dagger.range = 0;
    dagger.isRanged = false;
    strcpy(dagger.weaponName, "Dagger");
    return dagger;
}

Weapon Shortsword() {
    Weapon shortSword;
    shortSword.weaponID = 4;
    shortSword.value = 10;
    shortSword.minDMG = 1;
    shortSword.maxDMG = 6;
    shortSword.range = 0;
    shortSword.isRanged = false;
    strcpy(shortSword.weaponName, "Shortsword");
    return shortSword;
}

Weapon Longsword() {
    Weapon longSword;
    longSword.weaponID = 5;
    longSword.value = 20;
    longSword.minDMG = 1;
    longSword.maxDMG = 8;
    longSword.range = 0;
    longSword.isRanged = false;
    strcpy(longSword.weaponName, "Longsword");
    return longSword;
}

Weapon Greatsword() {
    Weapon greatSword;
    greatSword.weaponID = 6;
    greatSword.value = 45;
    greatSword.minDMG = 1;
    greatSword.maxDMG = 10;
    greatSword.range = 0;
    greatSword.isRanged = false;
    strcpy(greatSword.weaponName, "Greatsword");
    return greatSword;
}

Weapon Cutlass() {
    Weapon cutlass;
    cutlass.weaponID = 7;
    cutlass.value = 25;
    cutlass.minDMG = 2;
    cutlass.maxDMG = 7;
    cutlass.range = 0;
    cutlass.isRanged = false;
    strcpy(cutlass.weaponName, "Cutlass");
    return cutlass;
}

Weapon Quarterstaff() {
    Weapon quarterstaff;
    quarterstaff.weaponID = 8;
    quarterstaff.value = 10;
    quarterstaff.minDMG = 1;
    quarterstaff.maxDMG = 4;
    quarterstaff.range = 0;
    quarterstaff.isRanged = false;
    strcpy(quarterstaff.weaponName, "Quarterstaff");
    return quarterstaff;
}

Weapon ChromeFists() {
    Weapon chromeFists;
    chromeFists.weaponID = 9;
    chromeFists.value = 100;
    chromeFists.minDMG = 1;
    chromeFists.maxDMG = 6;
    chromeFists.range = 0;
    chromeFists.isRanged = false;
    strcpy(chromeFists.weaponName, "Chrome Fists");
    return chromeFists;
}

Weapon AcidPotion() {
    Weapon acidPotion;
    acidPotion.weaponID = 10;
    acidPotion.value = 25;
    acidPotion.minDMG = 2;
    acidPotion.maxDMG = 8;
    acidPotion.range = 6;
    acidPotion.isRanged = true;
    strcpy(acidPotion.weaponName, "Acid Potion");
    return acidPotion;
}

Weapon Shortbow() {
    Weapon shortbow;
    shortbow.weaponID = 11;
    shortbow.value = 25;
    shortbow.minDMG = 1;
    shortbow.maxDMG = 6;
    shortbow.range = 8;
    shortbow.isRanged = true;
    strcpy(shortbow.weaponName, "Short Bow");
    return shortbow;
}

Weapon Longbow() {
    Weapon longbow;
    longbow.weaponID = 12;
    longbow.value = 50;
    longbow.minDMG = 1;
    longbow.maxDMG = 8;
    longbow.range = 10;
    longbow.isRanged = true;
    strcpy(longbow.weaponName, "Long Bow");
    return longbow;
}

Weapon FlintlockPistol() {
    Weapon flintlockPistol;
    flintlockPistol.weaponID = 13;
    flintlockPistol.value = 75;
    flintlockPistol.minDMG = 1;
    flintlockPistol.maxDMG = 8;
    flintlockPistol.range = 5;
    flintlockPistol.isRanged = true;
    strcpy(flintlockPistol.weaponName, "Flintlock Pistol");
    return flintlockPistol;
}

Weapon LightningWand() {
    Weapon lightningWand;
    lightningWand.weaponID = 14;
    lightningWand.value = 75;
    lightningWand.minDMG = 1;
    lightningWand.maxDMG = 8;
    lightningWand.range = 10;
    lightningWand.isRanged = true;
    strcpy(lightningWand.weaponName, "Lightning Wand");
    return lightningWand;
}
