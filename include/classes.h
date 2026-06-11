#ifndef CLASSES_H // These prevent compiling items_h multiple times.
#define CLASSES_H

#include <string>

#define MAX_ABILITIES 5 // change later to 10
#define MAX_NAME_SIZE 33
#define MAX_DESC_SIZE 65

typedef enum {
    ABILITY_1,
    ABILITY_2,
    ABILITY_3,
    ABILITY_4,
    ABILITY_5,
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
    SECOND_WIND,
    SELF_REPAIR,
    SUMMON_SKELETON,
    SHADOW_BOLT,
    THORN_BOLT,
    VENGEANCE,
    DASH,
    DEVASTATING_INSULT
} AbilitiyIDs;

typedef enum {
    KNIGHT,
    SWASHBUCKLER,
    WIZARD,
    NECROMANCER,
    GUNSLINGER,
    DRUID,
    RANGER,
    DARK_KNIGHT,
    WARLOCK,
    CONJURER,
    CYBORG,
    BARD
} ClassIDs;

typedef struct {
    bool isAttack;
    bool isMagic;
    bool hasEffects;
    int abilityID;
    int duration;
    int minDMG;
    int maxDMG;
    int manaCost;
    int range;
    int abilitySave;
    int miscStat;
    std::string abilityName;
    std::string abilityDesc;
} Ability;

typedef struct {
    bool isCaster;
    int classID;
    int hpPerLVL;
    int manaPerLVL;
    int mainStat;
    int secondaryStat;
    Ability abilities[MAX_ABILITIES];
    std::string className;
    std::string classDesc;
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
Ability SecondWind();
Ability SelfRepair();
Ability Electrify();
Ability ShadowBolt();
Ability Vengeance();
Ability Dash();
Ability DevastatingInsult();
Ability ThornBolt();
void AbilityEffects(int abilityID);
void CastCharge();
void CastDash();
bool DashPOSHelper(int x, int y);
void CastDrainLife();
void CastIceArmor();
void CastSecondWind();
void CastSelfRepair();
void CastVengeance();
void ChargePlacement();
void CheckPassiveAbilities(int n_monsters);
bool DeincrementAbilityTimer();
void PostCombatEffects();
void PostChargeInfo();
void RemoveIceArmor();
void RemoveVengeance();
void ResetPassiveAbility(int abilityID);
bool UsePlayerAbility(int n_monsters, int chosenAbility);

// classes.c functions
Class Knight();
Class Swashbuckler();
Class Wizard();
Class Necromancer();
Class Gunslinger();
Class Druid();
Class Ranger();
Class DarkKnight();
Class Warlock();
Class Conjurer();
Class Cyborg();
Class Bard();
// Class Technomancer
// Class Sniper

//levelup.c functions
bool CheckForLevelUp();
void LevelUp(int classID);
void LevelKnight();
void LevelSwashbuckler();
void LevelWizard();
void LevelNecromancer();
void LevelGunslinger(); 
void LevelDruid();
void LevelRanger();
void LevelDarkKnight();
void LevelWarlock();
void LevelConjurer();
void LevelCyborg();
void LevelBard();


#endif