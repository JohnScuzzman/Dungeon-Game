#include <stdio.h>
#include <string.h>

#define INVENTORY_SIZE 10
#define NAME_SIZE 32
#define TOTAL_BLADES 7
#define TOTAL_RANGED 7
#define TOTAL_ARMORS 8
#define TOTAL_MONSTERS 10


// Links each weapon to its max damage value.
    typedef struct Blades{
        //To add a new weapon increase the total values.
        char blades[TOTAL_BLADES][NAME_SIZE] = {"Dagger", "Short Sword",
            "Long Sword", "BattleAxe", "Scimitar", 
            "Falcion", "Great Sword"};
        int dagger = 4;
        int shortSword = 6;
        int longSword = 8;
        int battleAxe = 10;
        int scimitar = 8;
        int falcion = 10;
        int greatSword = 12;
        int bladeTable[7] = {dagger, shortSword, longSword, 
            battleAxe, scimitar, falcion, greatSword};
    } blades_t;

    typedef struct Ranged{
        char ranged[TOTAL_RANGED][NAME_SIZE] = {"Short Bow", "Long Bow", "Crossbow", 
            "Heavy Crossbow", "Sling", "Elven Bow", "Dragon Bow"};
        int shortBow = 6;
        int longBow = 8;
        int crossbow = 10;
        int heavyCrossbow = 12;
        int sling = 4;
        int elvenBow = 10;
        int dragonBow = 12;
        int rangedTable[TOTAL_RANGED] = {shortBow, longBow, crossbow, heavyCrossbow,
        sling, elvenBow, dragonBow};
    } ranged_t;

    // Store AC's of armors
    typedef struct Armors{
        char armors[TOTAL_ARMORS][NAME_SIZE] = {"Leather Armor", "Padded Armor", 
        "Reinforced Armor","Scalemail", "Splintmail", "Chainmail", 
        "Half-Plate", "Full-Plate"};
        int leatherArmor = 1;
        int paddedArmor = 2;
        int reinforcedLeather = 3;
        int scaleMail = 4;
        int splintMail = 4;
        int chainMail = 5;
        int halfPlate = 6;
        int fullPlate = 7;
        int armorTable[TOTAL_ARMORS] = {leatherArmor, paddedArmor, reinforcedLeather, scaleMail,
        splintMail, chainMail, halfPlate, fullPlate};
    } armors_t;

    typedef struct Player{
        char playerName[NAME_SIZE];
        char playerWeapon[NAME_SIZE];
        char playerArmor[NAME_SIZE];
        int playerInventory[INVENTORY_SIZE][NAME_SIZE];
        int playerHP = 100;
        int playerWeaponDMG = 0;
        int playerArmorAC = 0;
        

    } player_t;

    // Contains names of monsters and their starting HP
    typedef struct Monster{
        char monsterName[TOTAL_MONSTERS][NAME_SIZE] = {"Goblin", "Orc", "Zombie",
        "Skeleton", "Skeleton Archer", "Troll", "Hobgoblin", "Gnoll", "Ooze",
        "Ghoul"};
        int goblin = 5;
        int orc = 12;
        int zombie = 8;
        int skeleton = 6;
        int skeletonArcher = 4;
        int troll = 15;
        int hobgoblin = 10;
        int gnoll = 10;
        int ooze = 3;
        int ghoul = 14;
        int monsterTable[TOTAL_MONSTERS] = {goblin, orc, zombie, skeleton,
        skeletonArcher, troll, hobgoblin, gnoll, ooze, ghoul};
        char monsterWeapons[TOTAL_MONSTERS][NAME_SIZE] = {"Dagger", "Long Sword", 
        "Dagger", "Claws", "Short Bow", "Claws", "Long Sword",
        "Scimitar", "Acid", "Claws"};
    } monster_t;

int **CreateFloor(int row, int col);
int CreateRoom(int **room, int spacesUsedCol, int spacesUsedRow, int currentSeed);
void FreeUpRoom(int **room, int row);
void PrintFloor(int **room);
int *RNG();
void EventLog(int currentEvent, int monsterName);
void Move(int **room, int colPOS, int rowPOS, char prevPOS);
void PlaceMonsters(int **room, int floorSizeToPrint);