#ifndef ITEMS_H // These prevent compiling items_h multiple times.
#define ITEMS_H

#define MAX_NAME_SIZE 33
#define ITEM_DESC_SIZE 65


typedef enum {
    NULL_ITEM_ID,
    _MELEE_,
    FISTS,
    CLAWS,
    DAGGER,
    COMBAT_KNIFE,
    SHORTSWORD,
    QUARTERSTAFF,
    LONGSWORD,
    CUTLASS,
    SCIMITAR,
    BATTLE_AXE,
    GREATSWORD,
    CHROME_FISTS,
    _RANGED_,
    SLINGSHOT,
    SHORTBOW,
    LONGBOW,
    FLINTLOCK_PISTOL,
    FLINTLOCK_RIFLE,
    LIGHT_PISTOL,
    MEDIUM_PISTOL,
    HEAVY_PISTOL,
    LIGHTNING_WAND,
    _AMMO_,
	ARROWS,
    BOLTS,
	ACID_POTION_AMMO,
	BULLET_FLINTLOCK,
	BULLET_5MM,
	BULLET_9MM,
    BULLET_45,
	BULLET_556,
	BULLET_762,
	BULLET_308,
	BULLET_50CAL,
	SHELL_BUCKSHOT,
	SHELL_SLUG,
	SHELL_DRAGONS_BREATH,
	MISSILES,
    ENERGY_PACKS,
	HEAVY_ENERGY_PACKS,
    _ARMOR_,
    RAGS,
    LEATHER_ARMOR,
    CHAINMAIL,
    HALF_PLATE,
    ROBES,
    RANGERS_CLOAK,
    METALLIC_SKIN,
    _END_
} ItemIDs;

typedef enum {
	NULL_ARMOR_TYPE,
    LIGHT,
    MEDIUM,
    HEAVY,
    EXOSUIT,
    POWER_ARMOR,
    MAGIC_ARMOR,
    CYBERWARE
} ArmorTypes;

typedef enum {
	NULL_AMMO_TYPE,
	TYPE_MAGIC,
    TYPE_ARROWS,
    TYPE_BOLTS,
    TYPE_FLINTLOCK,
    TYPE_5MM,
	TYPE_9MM,
    TYPE_45,
	TYPE_556,
	TYPE_762,
	TYPE_308,
	TYPE_50CAL,
	TYPE_SHOTGUN,
	TYPE_EXPLOSIVE_MISSILE,
    TYPE_THROWABLE,
	TYPE_ENERGY,
} AmmoTypes;

typedef enum {
    NULL_ITEM_TYPE,
    WEAPON,
	AMMO,
    ARMOR,
    PANTS,
    HELMET,
    SHOES,
    GLOVES,
    BACK,
    RING,
    AMULET,
    FOOD,
    POTIONS,
    CURRENCY,
    CYBERNETICS
} ItemTypes;

typedef struct {
    bool equippable;
    bool lootable;
    bool unequippable;
    bool isEquipped;
    int itemID;
    int quantity;
    int type;
    int value;
    char itemName[MAX_NAME_SIZE];
    char itemDesc[ITEM_DESC_SIZE];
}Item;

typedef struct {
    Item item;
    bool isMagic;
    bool isEnchanted;
    bool isRanged;
    int capacity;
    int enchantLevel;
    int minDMG;
    int maxDMG;
    int range;
    int ammoType;
    int statReq;
    int statUsed;
} Weapon;

typedef struct {
    Item item;
    bool isEnchanted;
    int AC;
    int enchantLevel;
    int type; // 1 = light, 2 = medium, 3 = heavy.
    int statReq;
    int statUsed;
} Armor;

typedef struct {
    Item item;
    int bonusDamage;
    int type; // Bullet or Arrow, etc.
} Ammo;

// typedef struct {
//   Amulets amulets;
//   Armors armors;
//   Back back;
//   Foods foods;
//   MeleeWeapons meleeWeapons;
//   Potions potions;
//   RangedWeapons rangedWeapons;
//   Rings rings;
//   Cybernetics cybernetics;
// } Inventory;

// make_weapons.c functions
Weapon NoWeapon();
Weapon Fists();
Weapon Claws();
Weapon Dagger();
Weapon CombatKnife();
Weapon Shortsword();
Weapon Quarterstaff();
Weapon Longsword();
Weapon Cutlass();
Weapon Scimitar();
Weapon BattleAxe();
Weapon Greatsword();
Weapon ChromeFists();
Weapon Slingshot();
Weapon Shortbow();
Weapon Longbow();
Weapon FlintlockPistol();
Weapon FlintlockRifle();
Weapon LightPistol();
Weapon MediumPistol();
Weapon HeavyPistol();
Weapon LightningWand();

//make_armors.c functions
Armor NoArmor();
Armor Robes();
Armor Rags();
Armor LeatherArmor();
Armor Chainmail();
Armor HalfPlate();
Armor RangersCloak();
Armor MetallicSkin();

//make_ammos.c fucntions
Ammo NoAmmo();
Ammo Arrows();
Ammo Bolts();
Ammo AcidPotionAmmo();
Ammo BulletFlintlock();
Ammo Bullet5mm();
Ammo Bullet9mm();
Ammo Bullet45();
Ammo Bullet556();
Ammo Bullet762();
Ammo Bullet308();
Ammo Bullet50Cal();
Ammo BulletBuckshot();
Ammo BulletSlug();
Ammo BulletDragonsBreath();
Ammo Missiles();
Ammo EnergyPacks();
Ammo HeavyEnergyPacks();


// typedef struct {
//   int amuletID;
//   int value;
//   CopperAmulet copperAmulet;
//   SilverAmulet silverAmulet;
// } Amulet;

// typedef struct {
//   int cyberneticID;
//   int value;
//   MetallicSkin metallicSkin;
//   ChromeFists chromeFists;
// } Cybernetic;

// typedef struct {
//   int ringID;
//   int value;
// } Ring;

// typedef struct {
//   int backID;
//   int value;
// } Back;

// typedef struct {
//   int foodID;
//   int value;
// } Food;

// typedef struct {
//   int potionID;
//   int value;
//   AcidPotion acidPotion;
// } Potion;

#endif