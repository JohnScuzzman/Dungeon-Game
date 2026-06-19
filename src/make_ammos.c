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
    arrows.type = PRIMITIVE;
    return arrows;
}

Ammo Darts() {
    Ammo darts;
    darts.item.equippable = true;
    darts.item.unequippable = true;
    darts.item.isEquipped = false;
    darts.item.type = AMMO;
    darts.item.itemID = DARTS;
    darts.item.quantity = 0;
    darts.item.value = 1;
    darts.bonusDamage = 1;
    darts.type = PRIMITIVE;
    return darts;
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
    acidPotion.bonusDamage = 0;
    acidPotion.type = MAGIC;
    return acidPotion;
}


Ammo BulletMusket() {
    Ammo bulletMusket;
    bulletMusket.item.equippable = true;
    bulletMusket.item.unequippable = true;
    bulletMusket.item.isEquipped = false;
    bulletMusket.item.type = AMMO;
    bulletMusket.item.itemID = BULLET_MUSKET;
    bulletMusket.item.quantity = 0;
    bulletMusket.item.value = 5;
    bulletMusket.bonusDamage = 1;
    bulletMusket.type = FLINTLOCK;
    return bulletMusket;
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
    bullet5mm.type = BULLET;
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
    bullet9mm.type = BULLET;
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
    bullet556.type = BULLET;
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
    bullet762.type = BULLET;
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
    bullet308.type = BULLET;
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
    bullet50Cal.type = BULLET;
    return bullet50Cal;
}

Ammo BulletBuckshot() {
    Ammo bulletBuckshot;
    bulletBuckshot.item.equippable = true;
    bulletBuckshot.item.unequippable = true;
    bulletBuckshot.item.isEquipped = false;
    bulletBuckshot.item.type = AMMO;
    bulletBuckshot.item.itemID = BULLET_BUCKSHOT;
    bulletBuckshot.item.quantity = 0;
    bulletBuckshot.item.value = 6;
    bulletBuckshot.bonusDamage = 1;
    bulletBuckshot.type = BULLET;
    return bulletBuckshot;
}

Ammo BulletSlug() {
    Ammo bulletSlug;
    bulletSlug.item.equippable = true;
    bulletSlug.item.unequippable = true;
    bulletSlug.item.isEquipped = false;
    bulletSlug.item.type = AMMO;
    bulletSlug.item.itemID = BULLET_SLUG;
    bulletSlug.item.quantity = 0;
    bulletSlug.item.value = 7;
    bulletSlug.bonusDamage = 1;
    bulletSlug.type = BULLET;
    return bulletSlug;
}

Ammo BulletDragonsBreath() {
    Ammo bulletDragonsBreath;
    bulletDragonsBreath.item.equippable = true;
    bulletDragonsBreath.item.unequippable = true;
    bulletDragonsBreath.item.isEquipped = false;
    bulletDragonsBreath.item.type = AMMO;
    bulletDragonsBreath.item.itemID = BULLET_DRAGONS_BREATH;
    bulletDragonsBreath.item.quantity = 0;
    bulletDragonsBreath.item.value = 12;
    bulletDragonsBreath.bonusDamage = 1;
    bulletDragonsBreath.type = BULLET;
    return bulletDragonsBreath;
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
    missiles.type = EXPLOSIVE;
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
    energyPacks.type = ENERGY;
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
    heavyEnergyPacks.type = ENERGY;
    return heavyEnergyPacks;
}
