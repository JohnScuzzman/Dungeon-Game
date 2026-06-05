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
    LONGSWORD,
    GREATSWORD,
    CUTLASS,
    SCIMITAR,
    QUARTERSTAFF,
    CHROME_FISTS,
    ACID_POTION,
    SHORTBOW,
    LONGBOW,
    FLINTLOCK_PISTOL,
    LIGHTNING_WAND,
    DUAL_FLINTLOCKS,
    RAGS,
    ROBES,
    LEATHER_ARMOR,
    CHAINMAIL,
    RANGERS_CLOAK,
    METALLIC_SKIN
} ItemIDs;

typedef enum {
    LIGHT,
    MEDIUM,
    HEAVY,
    EXOSUIT,
    POWER_ARMOR,
    MAGIC_ARMOR
} ArmorTypes;

typedef enum {
    NULL_ITEM_TYPE,
    WEAPON,
    ARMOR,
    CYBERNETICS,
    HELMET,
    SHOES,
    GLOVES,
    BACK,
    RING,
    AMULET,
    FOOD,
    POTIONS,
} ItemTypes;

typedef struct {
  bool equippable;
  bool lootable;
  bool unequippable;
  int itemID;
  int type;
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
  int value;
} Weapon;

typedef struct {
  Item item;
  int AC;
  int type; // 1 = light, 2 = medium, 3 = heavy.
  int value;
} Armor;

// weapon.c functions
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

//armor.c functions
Armor NoArmor();
Armor Robes();
Armor Rags();
Armor LeatherArmor();
Armor Chainmail();
Armor RangersCloak();
Armor MetallicSkin();



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