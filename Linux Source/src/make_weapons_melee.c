#include <rogue.h>

Weapon NoWeapon() {
    Weapon none;
    none.item.equippable = true;
    none.item.unequippable = true;
    none.item.isEquipped = false;
    none.item.type = NULL_ITEM_TYPE;
    none.item.itemID = NULL_ITEM_ID;
    none.item.quantity = 0;
    none.item.value = 0;
    none.isMagic = false;
    none.isEnchanted = false;
    none.isRanged = false;
    none.capacity = 0;
    none.enchantLevel = 0;
    none.minDMG = 0;
    none.maxDMG = 0;
    none.range = 0;
    none.ammoType = NULL_AMMO_TYPE;
    none.statUsed = NULL_STAT_TYPE;
    none.statReq = 0;
    strcpy(none.item.itemName, "None");
    strcpy(none.item.itemDesc, " ");
    return none;
}

Weapon Fists() {
    Weapon fists;
    fists.item.equippable = true;
    fists.item.unequippable = true;
    fists.item.isEquipped = false;
    fists.item.type = WEAPON;
    fists.item.itemID = FISTS;
    fists.item.quantity = 0;
    fists.item.value = 0;
    fists.isMagic = false;
    fists.isEnchanted = false;
    fists.isRanged = false;
    fists.capacity = 0;
    fists.enchantLevel = 0;
    fists.minDMG = 1;
    fists.maxDMG = 3;
    fists.range = 0;
    fists.ammoType = NULL_AMMO_TYPE;
    fists.statUsed = STR;
    fists.statReq = 0;
    strcpy(fists.item.itemName, "Fists");
    strcpy(fists.item.itemDesc, "Punch something if you must.");
    return fists;
}

Weapon Claws() {
    Weapon claws;
    claws.item.equippable = true;
    claws.item.unequippable = true;
    claws.item.isEquipped = false;
    claws.item.type = WEAPON;
    claws.item.itemID = CLAWS;
    claws.item.quantity = 0;
    claws.item.value = 0;
    claws.isMagic = false;
    claws.isEnchanted = false;
    claws.isRanged = false;
    claws.capacity = 0;
    claws.enchantLevel = 0;
    claws.minDMG = 1;
    claws.maxDMG = 4;
    claws.range = 0;
    claws.ammoType = NULL_AMMO_TYPE;
    claws.statUsed = STR;
    claws.statReq = 0;
    strcpy(claws.item.itemName, "Claws");
    strcpy(claws.item.itemDesc, "Sharp claws, ready to scratch.");
    return claws;
}

Weapon Dagger() {
    Weapon dagger;
    dagger.item.equippable = true;
    dagger.item.unequippable = true;
    dagger.item.isEquipped = false;
    dagger.item.type = WEAPON;
    dagger.item.itemID = DAGGER;
    dagger.item.quantity = 0;
    dagger.item.value = 5;
    dagger.isMagic = false;
    dagger.isEnchanted = false;
    dagger.isRanged = false;
    dagger.capacity = 0;
    dagger.enchantLevel = 0;
    dagger.minDMG = 1;
    dagger.maxDMG = 4;
    dagger.range = 0;
    dagger.ammoType = NULL_AMMO_TYPE;
    dagger.statUsed = STR;
    dagger.statReq = 6;
    strcpy(dagger.item.itemName, "Dagger");
    strcpy(dagger.item.itemDesc, "A small, sharpened dagger.");
    return dagger;
}

Weapon CombatKnife() {
    Weapon combatKnife;
    combatKnife.item.equippable = true;
    combatKnife.item.unequippable = true;
    combatKnife.item.isEquipped = false;
    combatKnife.item.type = WEAPON;
    combatKnife.item.itemID = COMBAT_KNIFE;
    combatKnife.item.quantity = 0;
    combatKnife.item.value = 10;
    combatKnife.isMagic = false;
    combatKnife.isEnchanted = false;
    combatKnife.isRanged = false;
    combatKnife.capacity = 0;
    combatKnife.enchantLevel = 0;
    combatKnife.minDMG = 1;
    combatKnife.maxDMG = 5;
    combatKnife.range = 0;
    combatKnife.ammoType = NULL_AMMO_TYPE;
    combatKnife.statUsed = STR;
    combatKnife.statReq = 6;
    strcpy(combatKnife.item.itemName, "Combat Knife");
    strcpy(combatKnife.item.itemDesc, "A compact, serrated military-grade blade.");
    return combatKnife;
}

Weapon BattleAxe() {
    Weapon battleAxe;
    battleAxe.item.equippable = true;
    battleAxe.item.unequippable = true;
    battleAxe.item.isEquipped = false;
    battleAxe.item.type = WEAPON;
    battleAxe.item.itemID = BATTLE_AXE;
    battleAxe.item.quantity = 0;
    battleAxe.item.value = 10;
    battleAxe.isMagic = false;
    battleAxe.isEnchanted = false;
    battleAxe.isRanged = false;
    battleAxe.capacity = 0;
    battleAxe.enchantLevel = 0;    battleAxe.minDMG = 2;
    battleAxe.maxDMG = 8;
    battleAxe.range = 0;
    battleAxe.ammoType = NULL_AMMO_TYPE;
    battleAxe.statUsed = STR;
    battleAxe.statReq = 6;
    strcpy(battleAxe.item.itemName, "Battle Axe");
    strcpy(battleAxe.item.itemDesc, "A double-bladed axe, forged for war.");
    return battleAxe;
}

Weapon Shortsword() {
    Weapon shortSword;
    shortSword.item.equippable = true;
    shortSword.item.unequippable = true;
    shortSword.item.isEquipped = false;
    shortSword.item.type = WEAPON;
    shortSword.item.itemID = SHORTSWORD;
    shortSword.item.quantity = 0;
    shortSword.item.value = 10;
    shortSword.isMagic = false;
    shortSword.isEnchanted = false;
    shortSword.isRanged = false;
    shortSword.capacity = 0;
    shortSword.enchantLevel = 0;    
    shortSword.minDMG = 1;
    shortSword.maxDMG = 6;
    shortSword.range = 0;
    shortSword.ammoType = NULL_AMMO_TYPE;
    shortSword.statUsed = STR;
    shortSword.statReq = 8;
    strcpy(shortSword.item.itemName, "Shortsword");
    strcpy(shortSword.item.itemDesc, "A shortsword, only about arm's length.");
    return shortSword;
}

Weapon Quarterstaff() {
    Weapon quarterstaff;
    quarterstaff.item.equippable = true;
    quarterstaff.item.unequippable = true;
    quarterstaff.item.isEquipped = false;
    quarterstaff.item.type = WEAPON;
    quarterstaff.item.itemID = QUARTERSTAFF;
    quarterstaff.item.quantity = 0;
    quarterstaff.item.value = 10;
    quarterstaff.isMagic = false;
    quarterstaff.isEnchanted = false;
    quarterstaff.isRanged = false;
    quarterstaff.capacity = 0;
    quarterstaff.enchantLevel = 0;   
    quarterstaff.minDMG = 1;
    quarterstaff.maxDMG = 4;
    quarterstaff.range = 0;
    quarterstaff.ammoType = NULL_AMMO_TYPE;
    quarterstaff.statUsed = STR;
    quarterstaff.statReq = 6;
    strcpy(quarterstaff.item.itemName, "Quarterstaff");
    strcpy(quarterstaff.item.itemDesc, "A large wooden staff, gnarled and tough.");
    return quarterstaff;
}

Weapon Longsword() {
    Weapon longSword;
    longSword.item.equippable = true;
    longSword.item.unequippable = true;
    longSword.item.isEquipped = false;
    longSword.item.type = WEAPON;
    longSword.item.itemID = LONGSWORD;
    longSword.item.quantity = 0;
    longSword.item.value = 20;
    longSword.isMagic = false;
    longSword.isEnchanted = false;
    longSword.isRanged = false;
    longSword.capacity = 0;
    longSword.enchantLevel = 0;   
    longSword.minDMG = 1;
    longSword.maxDMG = 8;
    longSword.range = 0;
    longSword.ammoType = NULL_AMMO_TYPE;
    longSword.statUsed = STR;
    longSword.statReq = 10;
    strcpy(longSword.item.itemName, "Longsword");
    strcpy(longSword.item.itemDesc, "A mighty blade.");
    return longSword;
}

Weapon Greatsword() {
    Weapon greatSword;
    greatSword.item.equippable = true;
    greatSword.item.unequippable = true;
    greatSword.item.isEquipped = false;
    greatSword.item.type = WEAPON;
    greatSword.item.itemID = GREATSWORD;
    greatSword.item.quantity = 0;
    greatSword.item.value = 45;
    greatSword.isMagic = false;
    greatSword.isEnchanted = false;
    greatSword.isRanged = false;
    greatSword.capacity = 0;
    greatSword.enchantLevel = 0;   
    greatSword.minDMG = 1;
    greatSword.maxDMG = 10;
    greatSword.range = 0;
    greatSword.ammoType = NULL_AMMO_TYPE;
    greatSword.statUsed = STR;
    greatSword.statReq = 12;
    strcpy(greatSword.item.itemName, "Greatsword");
    strcpy(greatSword.item.itemDesc, "A large sword, demanding two hands of it's wielder.");
    return greatSword;
}

Weapon Cutlass() {
    Weapon cutlass;
    cutlass.item.equippable = true;
    cutlass.item.unequippable = true;
    cutlass.item.isEquipped = false;
    cutlass.item.type = WEAPON;
    cutlass.item.itemID = CUTLASS;
    cutlass.item.quantity = 0;
    cutlass.item.value = 25;
    cutlass.isMagic = false;
    cutlass.isEnchanted = false;
    cutlass.isRanged = false;
    cutlass.capacity = 0;
    cutlass.enchantLevel = 0;   
    cutlass.minDMG = 2;
    cutlass.maxDMG = 7;
    cutlass.range = 0;
    cutlass.ammoType = NULL_AMMO_TYPE;
    cutlass.statUsed = STR;
    cutlass.statReq = 8;
    strcpy(cutlass.item.itemName, "Cutlass");
    strcpy(cutlass.item.itemDesc, "A favored weapon of every brigand.");
    return cutlass;
}

Weapon Scimitar() {
    Weapon scimitar;
    scimitar.item.equippable = true;
    scimitar.item.unequippable = true;
    scimitar.item.isEquipped = false;
    scimitar.item.type = WEAPON;
    scimitar.item.itemID = SCIMITAR;
    scimitar.item.quantity = 0;
    scimitar.item.value = 30;
    scimitar.isMagic = false;
    scimitar.isEnchanted = false;
    scimitar.isRanged = false;
    scimitar.capacity = 0;
    scimitar.enchantLevel = 0;   
    scimitar.minDMG = 2;
    scimitar.maxDMG = 8;
    scimitar.range = 0;
    scimitar.ammoType = NULL_AMMO_TYPE;
    scimitar.statUsed = STR;
    scimitar.statReq = 8;
    strcpy(scimitar.item.itemName, "Scimitar");
    strcpy(scimitar.item.itemDesc, "A curved sword, honed for slashing.");
    return scimitar;
}


Weapon ChromeFists() {
    Weapon chromeFists;
    chromeFists.item.equippable = true;
    chromeFists.item.unequippable = true;
    chromeFists.item.isEquipped = false;
    chromeFists.item.type = WEAPON;
    chromeFists.item.itemID = CHROME_FISTS;
    chromeFists.item.quantity = 0;
    chromeFists.item.value = 100;
    chromeFists.isMagic = false;
    chromeFists.isEnchanted = false;
    chromeFists.isRanged = false;
    chromeFists.capacity = 0;
    chromeFists.enchantLevel = 0;   
    chromeFists.minDMG = 1;
    chromeFists.maxDMG = 6;
    chromeFists.range = 0;
    chromeFists.ammoType = NULL_AMMO_TYPE;
    chromeFists.statUsed = CON;
    chromeFists.statReq = 10;
    strcpy(chromeFists.item.itemName, "Chrome Fists");
    strcpy(chromeFists.item.itemDesc, "Fists of chrome, glinting in the dark.");
    return chromeFists;
}