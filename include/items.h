#ifndef ITEMS_H // These prevent compiling items_h multiple times.
#define ITEMS_H

#define ALL_ITEMS 1000
#define MAX_NAME_SIZE 33


typedef enum {
    NO_WEAPON,
    FISTS,
    CLAWS,
    DAGGER,
    SHORTSWORD,
    LONGSWORD,
    GREATSWORD,
    CUTLASS,
    QUARTERSTAFF,
    CHROME_FISTS,
    ACID_POTION,
    SHORTBOW,
    LONGBOW,
    FLINTLOCK_PISTOL,
    LIGHTNING_WAND,
    DUAL_FLINTLOCKS,
    NO_ARMOR,
    ROBES,
    LEATHER_ARMOR,
    CHAINMAIL,
    RANGERS_CLOAK,
    METALLIC_SKIN
} ItemIDs;

typedef enum {
    NULL_ITEM,
    WEAPON,
    ARMOR,
    HELMET,
    SHOES,
    GLOVES,
    BACK,
    RING,
    AMULET,
    FOOD,
    POTIONS,
    CYBERNETICS
} ItemTypes;

typedef struct {
  bool equippable;
  int type;
  int itemID;
} Item;

typedef struct {
  Item item;
  bool isMagic;
  bool isRanged;
  int minDMG;
  int maxDMG;
  int range;
  int value;
  char weaponName[MAX_NAME_SIZE];
} Weapon;

typedef struct {
  Item item;
  int AC;
  int type; // 1 = light, 2 = medium, 3 = heavy.
  int value;
  char armorName[MAX_NAME_SIZE];
} Armor;



// weapon.c functions
Weapon None();
Weapon Fists();
Weapon Claws();
Weapon Dagger();
Weapon Shortsword();
Weapon Longsword();
Weapon Greatsword();
Weapon Cutlass();
Weapon Quarterstaff();
Weapon ChromeFists();
Weapon AcidPotion();
Weapon Shortbow();
Weapon Longbow();
Weapon FlintlockPistol();
Weapon LightningWand();
Weapon DualFlintlocks();

//armor.c functions
Armor Robes();
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