// void CreateMeleeWeapons() {

// }

// void CreateRangedWeapons() {

// }

#include <rogue.h>
Weapon Dagger() {
    Weapon dagger;
    dagger.weaponID = 1;
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
    shortSword.weaponID = 2;
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
    longSword.weaponID = 3;
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
    greatSword.weaponID = 4;
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
    cutlass.weaponID = 5;
    cutlass.value = 25;
    cutlass.minDMG = 1;
    cutlass.maxDMG = 8;
    cutlass.range = 0;
    cutlass.isRanged = false;
    strcpy(cutlass.weaponName, "Cutlass");
    return cutlass;
}

Weapon Quarterstaff() {
    Weapon quarterstaff;
    quarterstaff.weaponID = 6;
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
    chromeFists.weaponID = 7;
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
    acidPotion.weaponID = 8;
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
    shortbow.weaponID = 9;
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
    longbow.weaponID = 10;
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
    flintlockPistol.weaponID = 11;
    flintlockPistol.value = 75;
    flintlockPistol.minDMG = 1;
    flintlockPistol.maxDMG = 10;
    flintlockPistol.range = 6;
    flintlockPistol.isRanged = true;
    strcpy(flintlockPistol.weaponName, "Flintlock Pistol");
    return flintlockPistol;
}

Weapon MagicMissile() {
    Weapon magicMissile;
    magicMissile.weaponID = 12;
    magicMissile.value = 75;
    magicMissile.minDMG = 2;
    magicMissile.maxDMG = 8;
    magicMissile.range = 12;
    magicMissile.isRanged = true;
    strcpy(magicMissile.weaponName, "Magic Missile");
    return magicMissile;
}
