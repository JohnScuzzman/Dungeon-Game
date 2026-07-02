#include <rogue.h>

Ammo NoAmmo() {
    Ammo none;
    none.item.equippable = true;
    none.item.unequippable = true;
    none.item.isEquipped = false;
    none.item.type = NULL_ITEM_TYPE;
    none.item.itemID = NULL_ITEM_ID;
    none.item.quantity = 0;
    none.item.value = 0;
    none.bonusDamage = 1;
    none.type = NULL_AMMO_TYPE;
    strcpy(none.item.itemName, "None");
    strcpy(none.item.itemDesc, " ");
    return none;
}

Ammo Arrows() {
    Ammo arrows;
    arrows.item.equippable = true;
    arrows.item.unequippable = true;
    arrows.item.isEquipped = false;
    arrows.item.type = AMMO;
    arrows.item.itemID = ARROWS;
    arrows.item.quantity = 0;
    arrows.item.value = 1;
    arrows.bonusDamage = 0;
    arrows.type = TYPE_ARROWS;
    strcpy(arrows.item.itemName, "Arrows");
    strcpy(arrows.item.itemDesc, "Arrows, able to be fired from a bow.");
    return arrows;
}

Ammo Bolts() {
    Ammo bolts;
    bolts.item.equippable = true;
    bolts.item.unequippable = true;
    bolts.item.isEquipped = false;
    bolts.item.type = AMMO;
    bolts.item.itemID = BOLTS;
    bolts.item.quantity = 0;
    bolts.item.value = 1;
    bolts.bonusDamage = 1;
    bolts.type = TYPE_BOLTS;
    strcpy(bolts.item.itemName, "Bolts");
    strcpy(bolts.item.itemDesc, "Small wooden bolts, fired by crossbows.");
    return bolts;
}

Ammo AcidPotionAmmo() {
    Ammo acidPotion;
    acidPotion.item.equippable = true;
    acidPotion.item.unequippable = true;
    acidPotion.item.isEquipped = false;
    acidPotion.item.type = AMMO;
    acidPotion.item.itemID = ACID_POTION_AMMO;
    acidPotion.item.quantity = 0;
    acidPotion.item.value = 25;
    acidPotion.bonusDamage = 3;
    acidPotion.type = TYPE_THROWABLE;
    strcpy(acidPotion.item.itemName, "Acid Potions");
    strcpy(acidPotion.item.itemDesc, "A green swirly potion, it burns the eyebrows.");
    return acidPotion;
}

Ammo BulletFlintlock() {
    Ammo bulletFlintlock;
    bulletFlintlock.item.equippable = true;
    bulletFlintlock.item.unequippable = true;
    bulletFlintlock.item.isEquipped = false;
    bulletFlintlock.item.type = AMMO;
    bulletFlintlock.item.itemID = BULLET_FLINTLOCK;
    bulletFlintlock.item.quantity = 0;
    bulletFlintlock.item.value = 5;
    bulletFlintlock.bonusDamage = 1;
    bulletFlintlock.type = TYPE_FLINTLOCK;
    strcpy(bulletFlintlock.item.itemName, "Flintlock Ammo");
	strcpy(bulletFlintlock.item.itemDesc, "A small metal ball, fired with black powder.");
    return bulletFlintlock;
}

Ammo Bullet5mm() {
    Ammo bullet5mm;
    bullet5mm.item.equippable = true;
    bullet5mm.item.unequippable = true;
    bullet5mm.item.isEquipped = false;
    bullet5mm.item.type = AMMO;
    bullet5mm.item.itemID = BULLET_5MM;
    bullet5mm.item.quantity = 0;
    bullet5mm.item.value = 10;
    bullet5mm.bonusDamage = 1;
    bullet5mm.type = TYPE_5MM;
    strcpy(bullet5mm.item.itemName, "5mm ammo");
	strcpy(bullet5mm.item.itemDesc, "");
    return bullet5mm;
}

Ammo Bullet9mm() {
    Ammo bullet9mm;
    bullet9mm.item.equippable = true;
    bullet9mm.item.unequippable = true;
    bullet9mm.item.isEquipped = false;
    bullet9mm.item.type = AMMO;
    bullet9mm.item.itemID = BULLET_9MM;
    bullet9mm.item.quantity = 0;
    bullet9mm.item.value = 12;
    bullet9mm.bonusDamage = 1;
    bullet9mm.type = TYPE_9MM;
    strcpy(bullet9mm.item.itemName, "9mm Ammo");
	strcpy(bullet9mm.item.itemDesc, "");
    return bullet9mm;
}

Ammo Bullet556() {
    Ammo bullet556;
    bullet556.item.equippable = true;
    bullet556.item.unequippable = true;
    bullet556.item.isEquipped = false;
    bullet556.item.type = AMMO;
    bullet556.item.itemID = BULLET_556;
    bullet556.item.quantity = 0;
    bullet556.item.value = 16;
    bullet556.bonusDamage = 1;
    bullet556.type = TYPE_556;
    strcpy(bullet556.item.itemName, "5.56 Ammo");
	strcpy(bullet556.item.itemDesc, "");
    return bullet556;
}

Ammo Bullet762() {
    Ammo bullet762;
    bullet762.item.equippable = true;
    bullet762.item.unequippable = true;
    bullet762.item.isEquipped = false;
    bullet762.item.type = AMMO;
    bullet762.item.itemID = BULLET_762;
    bullet762.item.quantity = 0;
    bullet762.item.value = 18;
    bullet762.bonusDamage = 1;
    bullet762.type = TYPE_762;
    strcpy(bullet762.item.itemName, "7.62 Ammo");
	strcpy(bullet762.item.itemDesc, "");
    return bullet762;
}

Ammo Bullet308() {
    Ammo bullet308;
    bullet308.item.equippable = true;
    bullet308.item.unequippable = true;
    bullet308.item.isEquipped = false;
    bullet308.item.type = AMMO;
    bullet308.item.itemID = BULLET_308;
    bullet308.item.quantity = 0;
    bullet308.item.value = 22;
    bullet308.bonusDamage = 1;
    bullet308.type = TYPE_308;
    strcpy(bullet308.item.itemName, ".308 Ammo");
	strcpy(bullet308.item.itemDesc, "");
    return bullet308;
}

Ammo Bullet50Cal() {
    Ammo bullet50Cal;
    bullet50Cal.item.equippable = true;
    bullet50Cal.item.unequippable = true;
    bullet50Cal.item.isEquipped = false;
    bullet50Cal.item.type = AMMO;
    bullet50Cal.item.itemID = BULLET_50CAL;
    bullet50Cal.item.quantity = 0;
    bullet50Cal.item.value = 28;
    bullet50Cal.bonusDamage = 1;
    bullet50Cal.type = TYPE_50CAL;
    strcpy(bullet50Cal.item.itemName, ".50 Cal Ammo");
	strcpy(bullet50Cal.item.itemDesc, "");
    return bullet50Cal;
}

Ammo BulletBuckshot() {
    Ammo shellBuckshot;
    shellBuckshot.item.equippable = true;
    shellBuckshot.item.unequippable = true;
    shellBuckshot.item.isEquipped = false;
    shellBuckshot.item.type = AMMO;
    shellBuckshot.item.itemID = SHELL_BUCKSHOT;
    shellBuckshot.item.quantity = 0;
    shellBuckshot.item.value = 6;
    shellBuckshot.bonusDamage = 1;
    shellBuckshot.type = TYPE_SHOTGUN;
    strcpy(shellBuckshot.item.itemName, "Buckshot Ammo");
	strcpy(shellBuckshot.item.itemDesc, "");
    return shellBuckshot;
}

Ammo BulletSlug() {
    Ammo shellSlug;
    shellSlug.item.equippable = true;
    shellSlug.item.unequippable = true;
    shellSlug.item.isEquipped = false;
    shellSlug.item.type = AMMO;
    shellSlug.item.itemID = SHELL_SLUG;
    shellSlug.item.quantity = 0;
    shellSlug.item.value = 7;
    shellSlug.bonusDamage = 1;
    shellSlug.type = TYPE_SHOTGUN;
    strcpy(shellSlug.item.itemName, "Shotgun Slugs");
	strcpy(shellSlug.item.itemDesc, "");
    return shellSlug;
}

Ammo BulletDragonsBreath() {
    Ammo shellDragonsBreath;
    shellDragonsBreath.item.equippable = true;
    shellDragonsBreath.item.unequippable = true;
    shellDragonsBreath.item.isEquipped = false;
    shellDragonsBreath.item.type = AMMO;
    shellDragonsBreath.item.itemID = SHELL_DRAGONS_BREATH;
    shellDragonsBreath.item.quantity = 0;
    shellDragonsBreath.item.value = 12;
    shellDragonsBreath.bonusDamage = 1;
    shellDragonsBreath.type = TYPE_SHOTGUN;
    strcpy(shellDragonsBreath.item.itemName, "Dragon's Breath Rounds");
	strcpy(shellDragonsBreath.item.itemDesc, "");
    return shellDragonsBreath;
}

Ammo Missiles() {
    Ammo missiles;
    missiles.item.equippable = true;
    missiles.item.unequippable = true;
    missiles.item.isEquipped = false;
    missiles.item.type = AMMO;
    missiles.item.itemID = MISSILES;
    missiles.item.quantity = 0;
    missiles.item.value = 210;
    missiles.bonusDamage = 1;
    missiles.type = TYPE_EXPLOSIVE_MISSILE;
    strcpy(missiles.item.itemName, "Missiles");
	strcpy(missiles.item.itemDesc, "");
    return missiles;
}

Ammo EnergyPacks() {
    Ammo energyPacks;
    energyPacks.item.equippable = true;
    energyPacks.item.unequippable = true;
    energyPacks.item.isEquipped = false;
    energyPacks.item.type = AMMO;
    energyPacks.item.itemID = ENERGY_PACKS;
    energyPacks.item.quantity = 0;
    energyPacks.item.value = 38;
    energyPacks.bonusDamage = 1;
    energyPacks.type = TYPE_ENERGY;
    strcpy(energyPacks.item.itemName, "Energy Packs");
    strcpy(energyPacks.item.itemDesc, "");
    return energyPacks;
}

Ammo HeavyEnergyPacks() {
    Ammo heavyEnergyPacks;
    heavyEnergyPacks.item.equippable = true;
    heavyEnergyPacks.item.unequippable = true;
    heavyEnergyPacks.item.isEquipped = false;
    heavyEnergyPacks.item.type = AMMO;
    heavyEnergyPacks.item.itemID = HEAVY_ENERGY_PACKS;
    heavyEnergyPacks.item.quantity = 0;
    heavyEnergyPacks.item.value = 124;
    heavyEnergyPacks.bonusDamage = 1;
    heavyEnergyPacks.type = TYPE_ENERGY;
    strcpy(heavyEnergyPacks.item.itemName, "Heavy Energy Packs");
	strcpy(heavyEnergyPacks.item.itemDesc, "");
    return heavyEnergyPacks;
}
