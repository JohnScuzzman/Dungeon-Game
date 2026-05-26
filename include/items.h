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
#ifndef ITEMS_H // These prevent compiling items_h multiple times.
#define ITEMS_H
#define MAX_NAME_SIZE 33

typedef struct {
  int weaponID;
  int value;
  int minDMG;
  int maxDMG;
  int range;
  bool isRanged;
  char weaponName[MAX_NAME_SIZE];
} Weapon;

typedef struct {
  int armorID;
  int value;
  int AC;
  int type; // 1 = light, 2 = medium, 3 = heavy.
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
Weapon MagicMissile();

//armor.c functions
Armor Robes();
Armor LeatherArmor();
Armor Chainmail();
Armor RangersCloak();
Armor MetallicSkin();

#endif