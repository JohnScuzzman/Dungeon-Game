#ifndef CLASSES_H // These prevent compiling items_h multiple times.
#define CLASSES_H


#define MAX_NAME_SIZE 33
#define MAX_DESC_SIZE 65
#define MAX_ABILITIES 3 // change later to 10


typedef struct {
    bool isAttack;
    bool isMagic;
    bool isRanged;
    bool isSummon;
    int duration;
    int minDMG;
    int maxDMG;
    int manaCost;
    int range;
    int abilitySave;
    int miscStat;
    char abilityName[MAX_NAME_SIZE];
    char abilityDesc[MAX_DESC_SIZE];
} Ability;


typedef struct {
    bool isCaster;
    int hpPerLVL;
    int manaPerLVL;
    int mainStat;
    int secondaryStat;
    Ability abilities[MAX_ABILITIES];
    char className[MAX_NAME_SIZE];
    char classDesc[MAX_DESC_SIZE];
} Class;

// abilities.c functions
Ability NoAbility();
Ability Charge();
Ability FireVolley();
Ability MagicMissile();
Ability IceArmor();
Ability DrainLife();
Ability SummonSkeleton();
Ability AimedShot();
Ability MakeHealthPotion();
Ability SelfRepair();
Ability Electrify();
void CastSelfRepair();

// classes.c functions
Class Knight();
Class Swashbuckler();
Class Wizard();
Class Necromancer();
Class Gunslinger();
Class Ranger();
Class DarkKnight();
Class Alchemist();
Class Conjurer();
Class Cyborg();

#endif