#ifndef ITEMS_H // These prevent compiling items_h multiple times.
#define ITEMS_H

#define MAX_NAME_SIZE 33
#define ITEM_DESC_SIZE 65


typedef enum {
    NULL_ITEM_ID,
    FISTS,
    CLAWS,
    DAGGER,
    SHORTSWORD,
    QUARTERSTAFF,
    LONGSWORD,
    CUTLASS,
    SCIMITAR,
    GREATSWORD,
    CHROME_FISTS,
    ACID_POTION,
    SHORTBOW,
    LONGBOW,
    FLINTLOCK_PISTOL,
    LIGHTNING_WAND,
    DUAL_FLINTLOCKS,
	ARROWS,
    DARTS,
	ACID_POTION_AMMO,
	BULLET_MUSKET,
	BULLET_5MM,
	BULLET_9MM,
	BULLET_556,
	BULLET_762,
	BULLET_308,
	BULLET_50CAL,
	BULLET_BUCKSHOT,
	BULLET_SLUG,
	BULLET_DRAGONS_BREATH,
	MISSILES,
    ENERGY_PACKS,
	HEAVY_ENERGY_PACKS,
    RAGS,
    LEATHER_ARMOR,
    CHAINMAIL,
    ROBES,
    RANGERS_CLOAK,
    METALLIC_SKIN
} ItemIDs;

typedef enum {
	NULL_ARMOR_TYPE,
    LIGHT,
    MEDIUM,
    HEAVY,
    EXOSUIT,
    POWER_ARMOR,
    MAGIC_ARMOR
} ArmorTypes;

typedef enum {
	NULL_AMMO_TYPE,
    PRIMITIVE,
	MAGIC,
	FLINTLOCK,
	BULLET,
	EXPLOSIVE,
	ENERGY
} AmmoTypes;

typedef enum {
    NULL_ITEM_TYPE,
    WEAPON,
	AMMO,
    ARMOR,
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
  bool isRanged;
  int minDMG;
  int maxDMG;
  int range;
  //int ammoType
} Weapon;

typedef struct {
  Item item;
  int AC;
  int type; // 1 = light, 2 = medium, 3 = heavy.
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
Weapon Shortsword();
Weapon Longsword();
Weapon Greatsword();
Weapon Cutlass();
Weapon Scimitar();
Weapon Quarterstaff();
Weapon ChromeFists();
Weapon AcidPotion();
Weapon Shortbow();
Weapon Longbow();
Weapon FlintlockPistol();
Weapon LightningWand();
Weapon DualFlintlocks();

//make_armors.c functions
Armor NoArmor();
Armor Robes();
Armor Rags();
Armor LeatherArmor();
Armor Chainmail();
Armor RangersCloak();
Armor MetallicSkin();

//make_ammos.c fucntions
Ammo NoAmmo();
Ammo Arrows();
Ammo Darts();
Ammo AcidPotionAmmo();
Ammo BulletMusket();
Ammo Bullet5mm();
Ammo Bullet9mm();
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