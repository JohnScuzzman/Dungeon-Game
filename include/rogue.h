


#ifndef ROGUE_H // These prevent compiling rogue_h multiple times.
#define ROGUE_H


#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h> // rng related stuff
#include "math.h" // complex math funtions
#include <stdio.h> // standard io
#include <unistd.h> // File reading
#include <string.h> // String copying
#include <ctype.h> // toupper functions
#include <stdbool.h>
#include <items.h>
#include <races.h>
#include <classes.h>

// color pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2
#define MONSTER_COLOR 2
#define HIGHLIGHT_COLOR 3
#define HEADINGS 8
#define MAX_LEVEL 10 // change later to 20
#define MAX_NAME_SIZE 33
#define MAX_EVENT_SIZE 64
#define MAX_INVENTORY_SIZE 64
#define MAX_LOG_SIZE 28

/* IMPORTANT*/
/* "typedef" is used instead of "struct cat_t" so that we dont have to */
/* type "struct" everytime we declare a struct variable.*/

typedef enum {
  NORTH,
  WEST,
  SOUTH,
  EAST,
  NORTH_WEST,
  SOUTH_WEST,
  SOUTH_EAST,
  NORTH_EAST
} Direction;

typedef enum {
    LEVEL_1 = 0,
    LEVEL_2 = 100,
    LEVEL_3 = 220,
    LEVEL_4 = 480,
    LEVEL_5 = 1000,
    LEVEL_6 = 2300,
    LEVEL_7 = 5150,
    LEVEL_8 = 11330,
    LEVEL_9 = 25000,
    LEVEL_10 = 55000
} Levels;

typedef struct {
  char events[MAX_LOG_SIZE][MAX_EVENT_SIZE];
  int front;
  int rear;
} LogQueue;

typedef struct {
    bool oldSeen;
    bool newSeen;
    bool oldVisible;
    bool newVisible;
    char oldChar;
    char newChar;
} MapInfo;

typedef struct {
    int y;
    int x;
} Position;

typedef struct {
  int ATK;
  int CHA;
  int CON;
  int DEX;
  int INT;
  int STR;
  int WIS;
  int AC;
  int HP;
  int mana;
  int maxHP;
  int maxMana;
  int LVL;
  int EXP;
  int nextLVLEXP;
  int maxDMG;
  int minDMG;
} Stats;

typedef struct {
  bool noCollision;
  char ch;
  int raceID;
  int color;
  int abilityTimer;
  int invTail;
  int invHead;
  Stats playerStats;
  Position pos;
  Armor equippedArmor;
  Weapon equippedMelee;
  Weapon equippedRanged;
  Ability equippedAbility;
  Ability passiveAbility;
  Class playerClass;
  Item inventory[MAX_INVENTORY_SIZE];
  char playerName[MAX_NAME_SIZE];
  char playerRace[MAX_NAME_SIZE];
} Player;
  
typedef struct {
  bool aggroFlag;
  bool hasMoved;
  bool noCollision;
  bool seen;
  bool transparent;
  bool visible;
  bool isCorpse;
  bool isMonster;
  bool seenByPlayer;
  char ch;
  char staticCh;
  int aggroRange;
  int color;
  int entityID;
  int invTail;
  int invHead;
  Stats entityStats;
  Position pos;
  Position playerLastPos;
  MapInfo mapInfo;
  Armor entityArmor;
  Weapon entityWeapon;
  Item inventory[MAX_INVENTORY_SIZE];
  char entityName[MAX_NAME_SIZE];
  char entityRace[MAX_NAME_SIZE];
  char entityClass[MAX_NAME_SIZE];
} Entity;

typedef struct {
    Entity defender;
    bool monsterKilled;
    bool playerResult; // 0 = miss, 1 = hit
    bool entityResult; // 0 = miss, 1 = hit
    bool playerCombat; // true if player combat occurred
    bool playerUsedRanged;
    bool playerUsedAbility;
    int attackerAccRoll;
    int attackerDMG;
    int defenderAC;
    int playerAccRoll;
    int playerDMG;
    int playerAC;
    char event[MAX_EVENT_SIZE];
} CombatHistory;

typedef struct
{
  int height; 
  int width;
  // pos used to connect rooms with hallways.
  Position pos;
  Position center;
} Room;

//experimental.c functions

// asciiart.c funcions
void TitleScreen();

// assign_npc.c functions
void AssignCorpse(Entity* entity);
void AssignFloor(int x, int y);
void AssignGoblinWarrior(Entity* monster);
void AssignGoblinRanger(Entity* monster);
void AssignHobgoblinWarrior(Entity* monster);
void AssignKoboldWarrior(Entity* monster);
Entity AssignMonster(Position pos, int RNG, int monsterID);
void AssignMonsterDefaults(Entity* monster, Position m_pos, int monsterID);


// assign_class.c functions
void AssignClass(int input);
void AssignStats(int input);
void AssignKnight();
void AssignSwashbuckler();
void AssignWizard();
void AssignNecromancer();
void AssignGunslinger();
void AssignDruid();
void AssignRanger();
void AssignDarkKnight();
void AssignWarlock();
void AssignConjurer();
void AssignCyborg();
void AssignBard();

//combat.c functions 
CombatHistory* CreateCombatHistory(Entity monster);
bool AttackPlayer(Entity* attacker, CombatHistory* combatHistory, Player* player);
bool AttackEntity(Entity* defender, CombatHistory* combatHistory, Player* player);
int CalculateEntityAccuracy(Entity* attacker) ;
int CalculateEntityDMG(Entity* attacker);
int CalculateEntityAC(Entity* defender);
int CalculatePlayerAccuracy();
int CalculatePlayerDamage();
int CalculatePlayerAC();
void ResetCombatHistory();
bool ShootTarget(int x, int y);
bool ShootTargetWithAbility(int x, int y);

// combatlog.c functions
void DequeueEvent (LogQueue *q);
bool IsEmpty(LogQueue *q);
bool IsFull(LogQueue *q);
LogQueue* MakeCombatLogQueue();
void NotEnoughMana();
char* PeekCombatQueue (LogQueue *q);
void PlayerMeleeOrRanged(Player* player);
void PlayerPrepareCombat(int n_monsters);
bool PlayerRangedAttack(int n_monsters);
void PrintCombatQueue (LogQueue*q, WINDOW *pad);
void QueueEvent(LogQueue *q, char* event);
void RecordPlayerKill(Entity* defender, CombatHistory* combatHistory, int playerAccRoll, int playerDMG);
void RecordPlayerMiss(Entity* attacker, CombatHistory* combatHistory, int playerAccRoll, int defenderAC);
void RecordPlayerHit(Entity* defender, CombatHistory* combatHistory, int playerAccRoll, int playerDMG);
void RecordMonsterHit(Entity* attacker, CombatHistory* combatHistory, int attackerAccRoll, int attackerDMG);
void RecordMonsterMiss(Entity* defender, CombatHistory* combatHistory, int attackerAccRoll, int playerAC);
void RecordAbilityUse();

// draw.c functions
void DrawAbilities();
void DrawBorder();
void DrawCombatLog();
void DrawDebug(Entity* mptr, int n_monsters);
void DrawEverything();
void DrawPlayerEquipment();
void DrawPlayerInventory();
void DrawPlayerStats();
void DrawMap();
void DrawMonsters(Entity* mptr, int n_monsters);
void DrawPlayer(Player* player);
void DrawPlayerBlink(Player* player);

// engine.c functions
bool CheckEscape(int ch);
void CloseGame(void);
void Cursor(int x, int y, int length);
void GameLoop(Entity* mptr, CombatHistory* combatHistory, int n_monsters, LogQueue *q, Item* items);
void Gameover();
void Greeting();
bool MoveMonsterLoop(Entity* mptr, int n_monsters, bool PMove);
bool NcursesSetup(void);
void RefreshGamestate(Entity* mptr, int n_monsters);
void RemoveCursor(int x, int y, int length);
int NumberOfDigits(int input);

// fov.c functions
void ClearFOV(Player* player);
int GetDistance(Position origin, Position target);
int GetSign(int a);
bool IsInMap(int y, int x);
bool LineOfSight(Position origin, Position target);
void MakeFOV(Player* playerint);

// handle_crash.c functions
void handle_crash(int sig);

//items.c functions
void CombineEntityInventories(Entity* npc1, Entity* npc2);
void CreatePlayerInv();
void CreateMonsterInv(Entity* monster);
Item* CreateItemTable();
void AddToNPCInventory(Entity* npc, Item newItem, int itemQuantity);
void AddToPlayerInventory(Item newItem, int itemQuantity);
void RemoveFromNPCInventory(Entity* npc, Item target, int itemQuantity);
void RemoveFromPlayerInventory(Item target, int itemQuantity);
Weapon GetWeaponFromItem(int itemID);
Armor GetArmorFromItem(int itemID);
char* GetArmorType(int ArmorType);
int CompareStrings(const void *a, const void *b);
void Equip(Item target);
void EquipMelee(Item target);
void EquipRanged(Item target);
void EquipArmor(Item target);
void Unequip(Item target);
bool IsMeleeWeaponItem(Item target);
bool IsRangedWeaponItem(Item target);
bool IsArmorItem(Item target);
void MakeWeaponItems(Item* items);
void MakeArmorItems(Item* items);
void NameWeaponItems(Item* items);
void NameArmorItems(Item* items);
void WeaponItemDescriptions(Item* items);
void ArmorItemDescriptions(Item* items);
// void NullItem(Item item);

// make_player.c functions
void AskPlayerInfo(Player* player);
void ChooseClass();
void ChooseName(char* name);
void ChooseRace();
Player* CreatePlayer(Position start_pos);
void PrintRaces();
void PrintClasses();

// map.c functions
Entity** CreateEntities(void);
void FreeMap(void);
Position SetupMap(Entity* mptr, int n_rooms);
// Position FindClosestUnexplored(void);
// Position FindClosestUnexplored();
// Position FindClosestDoor();

// map_rooms.c functions
void AddRoomToMap(Room room);
Room CreateRoom(int y, int x, int height, int width);
void ConnectRooms(Position centerOne, Position centerTwo);

//menu_inventory.c functions
bool MakeInventoryMenu();
bool MakeItemOptionsWindow(Item** playerInv, int choice, int n_options, WINDOW *menu, WINDOW *loot);
bool MoveInventoryCursor(WINDOW* menu, WINDOW* desc, WINDOW* loot);
void RenderInventoryMenu(WINDOW *menu, WINDOW *desc, WINDOW *loot, int cursor, int n_options, Item** playerInv);
bool InvOptionSelect(Item** playerInv, int prevChoice, int n_options, int newChoice, WINDOW* menu, WINDOW* invOp, WINDOW* loot, bool unEquipMenu);
void RenderInvOptionMenu(WINDOW *invOp, int cursor, int n_options, char** entityInv);
void RenderItemInfo(WINDOW* desc, Item* item);
void EquipOrUnequip(Item** playerInv, bool unEquipMenu, int prevChoice);
void PrintInventoryHeaders(WINDOW* menu, WINDOW* desc, WINDOW* loot);
void PrintAllItems (WINDOW* menu, WINDOW* desc, WINDOW* loot, int cursor, int* y, Item** playerInv);
// void RenderLootMenu(WINDOW *loot, int cursor, int n_options, Item** playerInv);
// bool LootMenu(WINDOW *loot, int cursor, int n_options, Item** playerInv);
// bool LootChoice(WINDOW* loot, int lootChoice);

//menu_loot.c functions
bool MoveLootCursor(WINDOW* menu, WINDOW* desc,WINDOW* loot, Item** playerInv);
void RenderLootMenu(WINDOW *menu, WINDOW *desc, WINDOW *loot, int cursor, int n_options, Item** entityInv, Item** playerInv);
void RenderLootOptionMenu(WINDOW *lootOp, int cursor, int n_options, char** options);
bool MakeLootOptionsWindow(Item** playerInv, Item** entityInv, int choice, int n_options, WINDOW *menu, WINDOW *loot);
bool LootOptionSelect(Item** playerInv, Item** entityInv, int prevChoice, int n_options, int newChoice, WINDOW* menu, WINDOW* lootOp, WINDOW* loot);

//menu_pause.c functions
bool MakePauseMenu();
bool ProcessPauseSelect(int choice, WINDOW* menu);
void RenderPauseMenu(WINDOW *menu_win, int cursor, int n_options, char** options);

// monster.c functions
void AggroMove(Entity* mptr);
bool CheckAggro(Entity* mptr, Player* player);
int FindClosestMonster(Entity* mptr, int n_monsters);
Entity* FindMonsterInList(int monsterID, int n_monsters);
void KeepMonsterIntegrity(Entity* mptr);
void KeepMonsterMapIntegrity(Entity* mptr);
int MonsterDirection(Entity* monster);
Entity* MonsterList(int n_monsters);
void MoveMonster(Entity* monster, Position newPOS);
void RecordMonsterSeen(Entity* monster);
void ResetMoveFlags(Entity* mptr, int n_monsters);
void UpdateMonsterMap(Entity* monster, int n_monsters);
void UpdateMonsterCorpses(Entity* monster, int n_monsters);
void UpdateMonster(Entity* monster, int monsterID, int n_monsters);
void UpdateMonsterVisible(Entity* monster, Player* player);
void Wander(Entity* mptr);

// movemonster.c functions
bool MoveTowards(Entity* entity, Position pos);
void MoveUp(Entity* mptr);
void MoveDown(Entity* mptr);
void MoveLeft(Entity* mptr);
void MoveRight(Entity* mptr);
void MoveDownRight(Entity* mptr);
void MoveDownLeft(Entity* mptr);
void MoveUpRight(Entity* mptr);
void MoveUpLeft(Entity* mptr);

// player.c functions
bool CheckPlayerAdjacent(Position origin);
void ManaRegen(int *manaRegen);
void MovePlayer(Position newPos, CombatHistory* combatHistory);
bool PlayerInput(int input, LogQueue *q, int n_monsters);
void PlayerRegen(int *playerRegen);
// bool AutoExplore(CombatHistory* combatHistory);

// Externals 
// Used in tandem with main to let any functions use these outside of main.
extern int MAP_HEIGHT;
extern int MAP_WIDTH;
extern int MAX_MONSTER_NAME;
extern const int EVENT_SIZE;
extern const int INVENTORY_SIZE;
extern int LOG_WIDTH;
extern int LOG_HEIGHT;
extern int LOG_SIZE;
extern const int LVL_EXP_VALUES[MAX_LEVEL];
extern const int ALL_ITEMS;
extern const char *DIRECTIONS[HEADINGS];


extern Player* player;
// Array of tiles
extern Entity** map;
// Pointer to the list of monsters
extern Entity* mptr;
// Combat History
extern CombatHistory* combatHistory;
// Combat Log
extern LogQueue* q;
// Item Table
extern Item* items;


#endif
