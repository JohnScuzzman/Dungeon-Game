#ifndef ROGUE_H // These prevent compiling rogue_h multiple times.
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h> // rng related stuff
#include "math.h" // complex math funtions
#include <stdio.h> // standard io
#include <unistd.h> // File reading
#include <string.h> // String copying
#include <ctype.h> // toupper functions
#include "items.h"

// color pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2
#define MONSTER_COLOR 2
#define HIGHLIGHT_COLOR 3
#define MAX_NAME_SIZE 33
#define INVENTORY_SIZE 64

/* IMPORTANT*/
/* "typedef" is used instead of "struct cat_t" so that we dont have to */
/* type "struct" everytime we declare a struct variable.*/

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
  int LVL;
  int maxDMG;
  int minDMG;
} Stats;

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

typedef struct {
  bool noCollision;
  char ch;
  int color;
  Stats playerStats;
  Position pos;
  char playerName[MAX_NAME_SIZE];
  char playerRace[MAX_NAME_SIZE];
  char playerClass[MAX_NAME_SIZE];
  char playerArmor[MAX_NAME_SIZE];
  char playerWeapon[MAX_NAME_SIZE];
} Player;
  
typedef struct {
  bool aggroFlag;
  bool hasMoved;
  bool noCollision;
  bool seen;
  bool transparent;
  bool visible;
  char ch;
  char staticCh;
  int color;
  int entityAggroRange;
  int entityID;
  Stats entityStats;
  Position pos;
  char entityName[MAX_NAME_SIZE];
  char entityRace[MAX_NAME_SIZE];
  char entityClass[MAX_NAME_SIZE];
  char entityArmor[MAX_NAME_SIZE];
  char entityWeapon[MAX_NAME_SIZE];
} Entity;

typedef struct {
    Entity defender;
    bool monsterKilled;
    bool playerResult; // 0 = miss, 1 = hit
    bool entityResult;
    bool playerCombat; // true if player combat occurred
    int attackerATKMod;
    int attackerAccRoll;
    int attackerDMG;
    int defenderDodgeMod;
    int defenderAC;
    int playerATKMod;
    int playerAccRoll;
    int playerDMG;
    int playerDodgeMod;
    int playerAC;
} CombatHistory;

typedef struct
{
  int height; 
  int width;
  // pos used to connect rooms with hallways.
  Position pos;
  Position center;
} Room;


// asciiart.c funcions
void TitleScreen();


// assign.c functions
void AssignClass(int input);
void AssignCorpse(Entity* entity);
void AssignFloor(int x, int y);
void AssignGoblinWarrior(Entity* monster);
void AssignGoblinRanger(Entity* monster);
void AssignHobgoblinWarrior(Entity* monster);
void AssignKoboldWarrior(Entity* monster);
Entity AssignMonster(Position pos, int RNG, int monsterID);
void AssignMonsterDefaults(Entity* monster, Position m_pos, int monsterID);
void AssignStats(int input);

//combat.c functions 
CombatHistory* CreateCombatHistory(Entity monster);
bool AttackPlayer(Entity* attacker, CombatHistory* combatHistory, Player* player);
bool AttackEntity(Entity* defender, CombatHistory* combatHistory, Player* player);
void ResetCombatHistory(CombatHistory* combatHistory);

// classes.c functions
void AssignKnight();
void AssignSwashbuckler();
void AssignWizard();
void AssignNecromancer();
void AssignGunslinger();
void AssignRanger();
void AssignDarkKnight();
void AssignAlchemist();
void AssignConjurer();
void AssignCyborg();


// draw.c functions
void DrawBorder(void);
void DrawEntityAttack(Entity attacker, bool combatResult);
void DrawPlayerAttack(Entity defender, bool combatResult);
void DrawDebug(Entity* mptr, int n_monsters);
void DrawEverything(Entity* mptr, int n_monsters, bool playeCombat, bool monsterCombat, CombatHistory* combatHistory);
void DrawMap();
void DrawMonsters(Entity* mptr, int n_monsters);
void DrawPlayer(Player* player);
void DrawPlayerBlink(Player* player);
void DrawStats(Player* player);


// engine.c functions
bool NcursesSetup(void);
void GameLoop(Entity* mptr, CombatHistory* combatHistory, int n_monsters);
void CloseGame(void);
void Cursor(int x, int y, int length);
void RemoveCursor(int x, int y, int length);
void Gameover();


// fov.c functions
void MakeFOV(Player* playerint);
void ClearFOV(Player* player);
int GetDistance(Position origin, Position target);
bool IsInMap(int y, int x);
bool LineOfSight(Position origin, Position target);
int GetSign(int a);

// makeplayer.c functions
Player* CreatePlayer(Position start_pos);
void AskPlayerInfo(Player* player);
void ChooseRace();
void ChooseName(char* name);
void ChooseClass();
void PrintRaces();
void PrintClasses();

// map.c functions
Entity** CreateEntities(void);
Position SetupMap(Entity* mptr, int n_rooms);
void FreeMap(void);

// monster.c functions
Entity* MonsterList(int n_monsters);
void UpdateMonsterMap(Entity* monster, int n_monsters);
void UpdateMonsters(Entity* monster, int n_monsters);
void UpdateMonster(Entity* monster, int monsterID, int n_monsters);
void MoveMonster(Entity* monster, Position newPOS);
void UpdateMonsterVisible(Entity* monster, Player* player);
// void MoveMonster(Monster monster);
// bool CheckAggroRange(Position monsterPos, Position playerLastPos, int aggroRange);
// void MoveTowardsPlayer(Monster monster);
// void MoveAllMonsters();
// void SetMonsterListLen(int n_rooms);
void KeepMonsterIntegrity(Entity* mptr, bool oldSeen, bool oldVisible);
void ResetMoveFlags(Entity* monster, int n_monsters);
void Wander(Entity* mptr);
Entity* FindMonsterInList(int monsterID, int n_monsters);



// player.c functions
bool PlayerInput(int input, CombatHistory* combatHistory);
void MovePlayer(Position newPos, CombatHistory* combatHistory);
bool CheckPlayerAdjacent(Position origin);

// room.c functions
Room CreateRoom(int y, int x, int height, int width);
void AddRoomToMap(Room room);
void ConnectRooms(Position centerOne, Position centerTwo);



// Externals 
// Used in tandem with main to let any functions use these outside of main.
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern const int MAX_MONSTER_NAME;

extern Player* player;
// Array of tiles
extern Entity** map;
// Pointer to the list of monsters
extern Entity* mptr;
// Combat History
extern CombatHistory* combatHistory;



#endif
