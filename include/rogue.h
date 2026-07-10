


#ifndef ROGUE_H // These prevent compiling rogue_h multiple times.
#define ROGUE_H

#include <stdio.h> // standard io
#include <stdlib.h>
#include <string.h> // String copying
#include <ncurses.h>
#include <signal.h>
#include <time.h> // rng related stuff
#include "math.h" // complex math funtions
#include <unistd.h> // File reading
#include <ctype.h> // toupper functions
#include <stdbool.h>
#include <items.h>
#include <races.h>
#include <classes.h>
#include <npcs.h>
#include <cjson/cJSON.h>

// color pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2
#define MONSTER_COLOR 2
#define HIGHLIGHT_COLOR 3
#define HEADINGS 8
#define MAX_LEVEL 10 // change later to 20
#define MAX_NAME_SIZE 33
#define MAX_EVENT_SIZE 64
#define MAX_INVENTORY_SIZE 65
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
    LEVEL_2 = 200,
    LEVEL_3 = 440,
    LEVEL_4 = 1000,
    LEVEL_5 = 2300,
    LEVEL_6 = 5150,
    LEVEL_7 = 11330,
    LEVEL_8 = 25000,
    LEVEL_9 = 55000,
    LEVEL_10 = 100000
} Levels;

typedef enum {
  NULL_ENTITY_TYPE,
  FLOOR,
  WALL,
  DOOR,
  STAIRS,
  MONSTER,
  CORPSE,
  CHEST,
  NPC
} EntityTypes;

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
  bool aggroFlag;
  bool hasMoved;
  bool noCollision;
  bool seen;
  bool transparent;
  bool visible;
  bool seenByPlayer;
  bool wasLooted;
  bool wasReplaced;
  char ch;
  char staticCh;
  int aggroRange;
  int color;
  int entityID;
  int entityType;
  int invTail;
  int invHead;
  Stats entityStats;
  Position pos;
  Position lastPos;
  Position playerLastPos;
  MapInfo mapInfo;
  Armor entityArmor; // armor and weapons located in items.h
  Weapon entityWeapon;
  Item inventory[MAX_INVENTORY_SIZE];
  char entityName[MAX_NAME_SIZE];
  char entityRace[MAX_NAME_SIZE];
  char entityClass[MAX_NAME_SIZE];
} Entity;

typedef struct {
  bool noCollision;
  bool isResting;
  char ch;
  int raceID;
  int color;
  int abilityTimer;
  int invTail;
  int invHead;
  Stats playerStats;
  Position pos;
  Weapon equippedMelee;
  Weapon equippedRanged;
  Ammo equippedAmmo;
  Armor equippedArmor;
  Ability equippedAbility;
  Ability passiveAbility;
  Class playerClass;
  Item inventory[MAX_INVENTORY_SIZE];
  Entity follower;
  char playerName[MAX_NAME_SIZE];
  char playerRace[MAX_NAME_SIZE];
} Player;
  


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

typedef struct
{
  int currentFloor;
  // Entity** visitedFloors[MAX_DUNGEON_FLOORS];
} DungeonInfo;

//experimental.c functions

// asciiart.c funcions
void TitleScreen();

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
bool AttackEntity(Entity* defender, CombatHistory* combatHistory, Player* player, int n_monsters);
int CalculateEntityAccuracy(Entity* attacker);
int CalculateEntityDMG(Entity* attacker);
int CalculateEntityAC(Entity* defender);
int CalculatePlayerAccuracy();
int CalculatePlayerDamage();
int CalculatePlayerAC();
bool NPCAttackEntity(Entity* attacker, Entity* defender, CombatHistory* combatHistory, int n_monsters);
bool ProcessRangedAttack(bool abilityUsed, int x, int y);
void ResetCombatHistory();
bool ShootTarget(int x, int y);
bool ShootTargetWithAbility(int x, int y);
bool ShootWithAmmo(int ammoType, int x, int y);
bool ShootAbilityWithAmmo(int ammoType, int x, int y);

// combat_log.c functions
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
void RecordNPCHit(Entity* defender, Entity* attackingNPC, CombatHistory* combatHistory, int attackerAccRoll, int attackerDMG);
void RecordNPCKill(Entity* defender, Entity* attacker, CombatHistory* combatHistory, int attackerAccRoll, int attackerDMG);
void RecordNPCMiss(Entity* defender, Entity* attackingNPC, CombatHistory* combatHistory, int attackerAccRoll, int defenderAC);
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
void DrawPlayerStats();
void DrawMap();
void DrawMonsters(Entity* mptr, int n_monsters);
void DrawPlayer(Player* player);
void DrawPlayerBlink(Player* player);

// engine.c functions
void CloseGame(void);
bool EquipWeaponRequirements(Weapon target);
bool EquipArmorRequirements(Armor target);
void GameLoop(CombatHistory* combatHistory, int n_monsters, LogQueue *q, Item* items);
void Gameover();
void Greeting();
bool MoveMonsterLoop(Entity* mptr, int n_monsters, bool PMove);
bool NcursesSetup(void);
void RefreshGamestate(Entity* mptr, int n_monsters);

// equip.c functions
void Equip(Item target);
void EquipMelee(Item target);
void EquipRanged(Item target);
void EquipArmor(Item target);
void EquipAmmo(Item target);
void Unequip(Item target);
char* GetRequiredStat(int reqType);

// fov.c functions
void ClearFOV(Player* player);
int GetDistance(Position origin, Position target);
int GetSign(int a);
bool IsInMap(int y, int x);
bool LineOfSight(Position origin, Position target);
void MakeFOV(Player* playerint);

// handle_crash.c functions
void handle_crash(int sig);

//inventory.c functions
void AddToNPCInventory(Entity* npc, Item newItem, int itemQuantity);
void AddToPlayerInventory(Item newItem, int itemQuantity);
void CombineEntityInventories(Entity* npc1, Entity* npc2);
void ClearEntityInventory(Entity* npc);
void CreatePlayerInv();
void CreateEntityInv(Entity* npc);
void RemoveFromNPCInventory(Entity* npc, Item target, int itemQuantity);
void DropFromPlayerInventory(Item target, int itemQuantity);
void RemoveFromPlayerInventory(Item target, int itemQuantity);

//items.c functions
Item* CreateItemTable();
Weapon GetWeaponFromItem(int itemID);
Ammo GetAmmoFromItem(int itemID);
Armor GetArmorFromItem(int itemID);
char* GetAmmoType(int AmmoType);
char* GetArmorType(int ArmorType);
bool IsMeleeWeaponItem(Item target);
bool IsRangedWeaponItem(Item target);
bool IsAmmoItem(Item target);
bool IsArmorItem(Item target);
void MakeAmmoItems(Item* items);
void MakeArmorItems(Item* items);
void MakeHeaderItems(Item* items);
void MakeWeaponItems(Item* items);
void FillNullItems(Item* items);

//loot_tables_containers.c functions.
void LowLevelChestLoot(Entity* chest);

//loot_tables_monsters.c functions
void GoblinWarriorLoot(Entity* goblin);
void HobGoblinWarriorLoot(Entity* hobGoblin);
void KoboldWarriorLoot(Entity* kobold);
void SkeletonWarriorLoot(Entity* skeleton);

// make entities.c functions
Entity** CreateEntities(void);
void AssignChest(int x, int y);
void AssignCorpse(Entity* entity, int n_monsters);
void AssignStairsDown(int x, int y);
void AssignFloor(int x, int y);

// make_monster.c functions 
void AssignRat(Entity* monster);
void AssignGoblinWarrior(Entity* monster);
void AssignGoblinRanger(Entity* monster);
void AssignHobgoblinWarrior(Entity* monster);
void AssignKoboldWarrior(Entity* monster);
void AssignSkeletonWarrior(Entity* monster);
Entity AssignMonster(Position pos, int RNG, int monsterID);
void AssignMonsterDefaults(Entity* monster, Position m_pos, int monsterID);

// make_npcs.c functions
Entity* NPCList(int totalNpcs);
Entity AddToNPCList(Entity* npcs, Position pos, int npcType);
Entity AssignNPC(Position pos, int npcType, int npcID);
void AssignNPCDefaults(Entity* npc, Position n_pos, int npcID);
Entity AssignUniqueNPC(Position pos, int npcName, int npcID);
// void PlaceNPC(Entity* npc, Position pos);

// make_player.c functions
bool AskPlayerInfo(Player* player);
void ChooseClass();
void ChooseName(char* name);
bool ChooseRace();
void ClearClassStats();
void ClearRaceStats();
void ClearClasses();
void ClearRaces();
Player* CreatePlayer(Position start_pos);
void PrintRaces();
void PrintClasses();
void PrintClassStats(int input);
void PrintRaceStats(int input);

// map.c functions
DungeonInfo* MakeDungeonInfo();
void FreeMap(void);
Position SetupMap(Entity* mptr, int n_rooms);
void MakeNewLevel(int* old_n_monsters);
int MonsterSpawnCeiling(int dungeonFloor);
int MonsterSpawnFloor(int dungeonFloor);
// Position FindClosestUnexplored(void);
// Position FindClosestUnexplored();
// Position FindClosestDoor();

// map_rooms.c functions
void AddRoomToMap(Room room);
Room CreateRoom(int y, int x, int height, int width);
void ConnectRooms(Position centerOne, Position centerTwo);
void AddChestToRoom(Position center, int width, int height);

// menu_dialogue.c functions
bool MakeDescendWindow();
bool ProcessDescendSelect(int choice, WINDOW* descend);
void RenderDescendMenu(WINDOW *descend, int cursor, int n_options, char** options);

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
Entity* MonsterList(int n_monsters);
void ResetMoveFlags(Entity* mptr, int n_monsters);
void UpdateMonsterMap(Entity* monster, int n_monsters);
void Wander(Entity* mptr);

// move_npcs.c functions
bool MoveTowards(Entity* entity, Position pos);
void MoveUp(Entity* npc);
void MoveDown(Entity* npc);
void MoveLeft(Entity* npc);
void MoveRight(Entity* npc);
void MoveDownRight(Entity* npc);
void MoveDownLeft(Entity* npc);
void MoveUpRight(Entity* npc);
void MoveUpLeft(Entity* npc);

// npc.c functions
Entity* FindNPCInList(int entityID, int maxNPCS);
void FollowPlayer(Entity* npc);
void KeepNPCIntegrity(Entity* npc);
void KeepNPCMapIntegrity(Entity* npc);
void UpdateNPCMap(Entity* npc, int maxNPCS);
void UpdateNPCVisible(Entity* npc, Player* player);

// player.c functions
bool CheckPlayerAdjacent(Position origin);
void ManaRegen(int *manaRegen);
bool MovePlayer(Position newPos, CombatHistory* combatHistory, int* n_monsters);
bool PlayerInput(int input, LogQueue *q, int* n_monsters, int* playerRegen, int* manaRegen);
void PlayerRegen(int *playerRegen);
void RestUntilHealed(int n_monsters, int* playerRegen, int* manaRegen, bool PMove);
// bool AutoExplore(CombatHistory* combatHistory);

// save_player.c functions 
char* FileToString(const char* filename);
bool SavePlayerToJSON(const char *filename, const Player* player);
cJSON* SerializePlayerStats(const Stats* playerStats);
cJSON* SerializePlayerPOS(const Position* pos);
cJSON* SerializeItem(const Item* item);
cJSON* SerializePlayerWeapon(const Weapon* equippedMelee);
cJSON* SerializePlayerAmmo(const Ammo* equippedAmmo);
cJSON* SerializePlayerArmor(const Armor* equippedArmor);
cJSON* SerializePlayerAbility(const Ability* ability);
cJSON* SerializePlayerClass(const Class* class);
cJSON* SerializePlayerInventory(const Player* player);
cJSON* SerializeEntityInventory(const Entity* entity);
cJSON* SerializeEntity(const Entity* entity);
cJSON* SerializeMapInfo(const MapInfo* mapInfo);

// utility.c functions
bool CheckAdjacent(Position origin, Position target);
bool CheckMonsterAdjacent(Position origin, Entity* monster);
bool CheckEscape(int ch);
int CompareStrings(const void *a, const void *b);
void Cursor(int x, int y, int length);
int EntityDirection(Entity* monster);
int GetNumberOfDigits(int input);
int RandomNumber(int min, int max);
void RecordEntitySeen(Entity* monster);
void RemoveCursor(int x, int y, int length);

// Externals 
// Used in tandem with main to let any functions use these outside of main.
extern int MAP_HEIGHT;
extern int MAP_WIDTH;
extern int MAX_MONSTER_NAME;
extern int MAX_NPCS;
extern int MAX_ONSCREEN_NPCS;
extern int MAX_DUNGEON_FLOORS;
extern int ENTITY_ID;
extern int LOG_WIDTH;
extern int LOG_HEIGHT;
extern int LOG_SIZE;
extern const int EVENT_SIZE;
extern const int INVENTORY_SIZE;
extern const int LVL_EXP_VALUES[MAX_LEVEL];
extern const int ALL_ITEMS;
extern const char *DIRECTIONS[HEADINGS];


extern Player* player;
// Array of tiles
extern Entity** map;
// Pointer to the list of monsters
extern Entity* mptr;
// Pointer to list of npcs
extern Entity* nptr;
// Combat History
extern CombatHistory* combatHistory;
// Combat Log
extern LogQueue* q;
// Item Table
extern Item* items;
// Npc Table;
extern Entity* npcs;
// Dungeon Info
extern DungeonInfo* dungeonInfo;


#endif
