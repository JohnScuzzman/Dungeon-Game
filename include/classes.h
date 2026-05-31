#ifndef CLASSES_H // These prevent compiling items_h multiple times.
#define CLASSES_H


#define MAX_NAME_SIZE 33
#define MAX_DESC_SIZE 65
#define MAX_ABILITIES 5 // change later to 10


typedef struct {
    bool isAttack;
    bool isMagic;
    bool hasEffects;
    bool postCombat;
    int abilityID;
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

typedef enum {
    Ability_1,
    Ability_2,
    Ability_3,
    Ability_4,
    Ability_5,
} AbilityKeypress;
    
typedef enum {
    NO_ABILITY,
    AIMED_SHOT,
    CHARGE,
    DRAIN_LIFE,
    ELECTRIFY,
    FIRE_VOLLEY,
    ICE_ARMOR,
    MAGIC_MISSILE,
    MAKE_HEALTH_POTION,
    SELF_REPAIR,
    SUMMON_SKELETON
} AbilitiyIDs;

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
void AbilityEffects(int abilityID);
void CastCharge();
void CastDrainLife();
void CastIceArmor();
void CastMakeHealthPotion();
void CastSelfRepair();
void ChargePlacement();
void CheckPassiveAbilities();
bool DeincrementAbilityTimer();
void PostChargeInfo();
void RemoveIceArmor();
void ResetPassiveAbility(int abilityID);

// classes.c functions
Class Knight();
Class Swashbuckler();
Class Wizard();
Class Necromancer();
Class Gunslinger();
Class Ranger();
Class DarkKnight();
Class Warlock();
Class Conjurer();
Class Cyborg();

#endif