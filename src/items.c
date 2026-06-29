#include <rogue.h>

/* Weapons begin at 'FIST', Armor Begins at 'ROBES'*/
Item* CreateItemTable() {
    Item* items = calloc(ALL_ITEMS, sizeof(Item));
    items[NULL_ITEM_ID].equippable = false;
    items[NULL_ITEM_ID].lootable = false;
    items[NULL_ITEM_ID].unequippable = true;
    items[NULL_ITEM_ID].isEquipped = false;
    items[NULL_ITEM_ID].itemID = NULL_ITEM_ID;
    items[NULL_ITEM_ID].quantity = 0;
    items[NULL_ITEM_ID].type = NULL_ITEM_TYPE;
    items[NULL_ITEM_ID].value = 0;
    strcpy(items[NULL_ITEM_ID].itemName, " ");
    strcpy(items[NULL_ITEM_ID].itemDesc, " ");
    MakeWeaponItems(items);
    MakeAmmoItems(items);
    MakeArmorItems(items);
    FillNullItems(items);
    return items;
}

/* Adds these weapons to a singleton-like global list called "items" */
void MakeWeaponItems(Item* items) {
     // Innate biological weapons
    for (int i = FISTS; i <= DUAL_FLINTLOCKS; i++){
        Weapon weapon = GetWeaponFromItem(i);
        items[i] = weapon.item;
    }
}

void MakeAmmoItems(Item* items) {
    for (int i = ARROWS; i <= HEAVY_ENERGY_PACKS; i++){
        Ammo ammo = GetAmmoFromItem(i);
        items[i] = ammo.item;
    } 
}

void MakeArmorItems(Item* items) {
    for (int i = RAGS; i <= METALLIC_SKIN; i++){
        Armor armor = GetArmorFromItem(i);
        items[i] = armor.item;
    }
}

/*
Fills remaining item list with empty items.
*/
void FillNullItems(Item* items){
    for (int i = METALLIC_SKIN + 1; i < ALL_ITEMS; i++){
        items[i].equippable = false;
        items[i].lootable = false;
        items[i].unequippable = true;
        items[i].isEquipped = false;
        items[i].itemID = NULL_ITEM_ID;
        items[i].quantity = 0;
        items[i].type = NULL_ITEM_TYPE;
        items[i].value = 0;
        strcpy(items[i].itemName, " ");
        strcpy(items[i].itemDesc, " ");
    }
}

/* This is effectively how we can translate an item into weapon.*/
/* Returns a copy of a struct depending on the given itemID */
/* The local copy should be recycled and deleted by the called method.*/
/* This copy will get passed up to whatever method uses it, and then get recycled once the method is done.*/
Weapon GetWeaponFromItem(int itemID) {
    switch(itemID) {
        case FISTS: return Fists();
        case CLAWS: return Claws();
        case DAGGER: return Dagger();
        case SHORTSWORD: return Shortsword();
        case QUARTERSTAFF: return Quarterstaff();
        case LONGSWORD: return Longsword();
        case CUTLASS: return Cutlass();
        case SCIMITAR: return Scimitar();
        case GREATSWORD: return Greatsword();
        case CHROME_FISTS: return ChromeFists();
        case ACID_POTION: return AcidPotion();
        case SHORTBOW: return Shortbow();
        case LONGBOW: return Longbow();
        case FLINTLOCK_PISTOL: return FlintlockPistol();
        case LIGHTNING_WAND: return LightningWand();
        case DUAL_FLINTLOCKS: return DualFlintlocks();
        default: return NoWeapon();
    }
    return NoWeapon();
}

Ammo GetAmmoFromItem(int itemID) {
    switch(itemID) {
        case ARROWS: return Arrows();
        case DARTS: return Darts();
        case ACID_POTION_AMMO: return AcidPotionAmmo();
        case BULLET_FLINTLOCK: return BulletFlintlock();
        case BULLET_5MM: return Bullet5mm();
        case BULLET_9MM: return Bullet9mm();
        case BULLET_556: return Bullet556();
        case BULLET_762:return Bullet762();
        case BULLET_308: return Bullet308();
        case BULLET_50CAL: return Bullet50Cal();
        case SHELL_BUCKSHOT: return BulletBuckshot();
        case SHELL_SLUG: return BulletSlug();
        case SHELL_DRAGONS_BREATH: return BulletDragonsBreath();
        case MISSILES: return Missiles();
        case ENERGY_PACKS: return EnergyPacks(); 
        case HEAVY_ENERGY_PACKS: return HeavyEnergyPacks();
    }
    return NoAmmo();
}

Armor GetArmorFromItem(int itemID) {
    switch(itemID) {
        case RAGS: return Rags();
        case ROBES: return Robes();
        case LEATHER_ARMOR: return LeatherArmor(); 
        case CHAINMAIL: return Chainmail();
        case RANGERS_CLOAK: return RangersCloak();
        case METALLIC_SKIN: return MetallicSkin();
    }
    return NoArmor();
}

char* GetAmmoType(int AmmoType) {
    switch(AmmoType) {
        case PRIMITIVE: return "Primitive";
        case MAGIC: return "Magic";
        case FLINTLOCK: return "Flintlock";
        case TYPE_5MM: return "5mm";
        case TYPE_9MM: return "9mm";
        case TYPE_556: return "5.56mm";
        case TYPE_762: return "7.62mm";
        case TYPE_308: return ".308";
        case TYPE_50CAL: return ".50";
        case SHOTGUN: return "Shotgun Shell";
        case EXPLOSIVE_MISSILE: return "Missile";
        case ENERGY: return "Energy";
    }
    return "None";
}

char* GetArmorType(int ArmorType) {
    switch(ArmorType) {
        case LIGHT: return "Light";
        case MEDIUM: return "Medium";
        case HEAVY: return "Heavy";
        case EXOSUIT: return "Exosuit";
        case POWER_ARMOR: return "Power Armor";
        case MAGIC_ARMOR: return "Magic Armor";
    }
    return "None";
}


/* This suite of functions just checks if an item is a certain type and returns true if it is*/
/* consult the enum list "ItemIDs" in items.h to modify this.*/
bool IsMeleeWeaponItem(Item target) {
    if (target.itemID > CLAWS && target.itemID < ACID_POTION) return true;
    return false;
}

bool IsRangedWeaponItem(Item target) {
    if (target.itemID > CHROME_FISTS && target.itemID < ARROWS) return true;
    return false;
}

bool IsAmmoItem(Item target) {
    if (target.itemID > DUAL_FLINTLOCKS && target.itemID < RAGS) return true;
    return false;
}

bool IsArmorItem(Item target) {
    if (target.itemID > HEAVY_ENERGY_PACKS && target.itemID <= METALLIC_SKIN) return true;
    return false;
}
