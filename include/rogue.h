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

// color pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2
#define MONSTER_COLOR 2
#define MAX_NAME_SIZE 33

/* IMPORTANT*/
/* "typedef" is used instead of "struct cat_t" so that we dont have to */
/* type "struct" everytime we declare a struct variable.*/

typedef struct {
    int y;
    int x;
} Position;

typedef struct {
  bool noCollision;
  char ch;
  int playerHP;
  int playerAC;
  int playerMaxDMG;
  int playerMinDMG;
  int playerLVL;
  int color;
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
  int entityAC;
  int entityAggroRange;
  int entityHP;
  int entityID;
  int entityLVL;
  int entityMaxDMG;
  int entityMinDMG;
  Position pos;
  char entityName[MAX_NAME_SIZE];
  char entityRace[MAX_NAME_SIZE];
  char entityClass[MAX_NAME_SIZE];
  char entityArmor[MAX_NAME_SIZE];
  char entityWeapon[MAX_NAME_SIZE];
} Entity;

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
Entity AssignMonster(Position pos, int RNG, int monsterID);
void AssignFloor(int x, int y);
void AssignGoblinWarrior(Entity* monster);
void AssignKoboldWarrior(Entity* monster);
void AssignGoblinRanger(Entity* monster);
void AssignHobgoblinWarrior(Entity* monster);
void AssignMonsterDefaults(Entity* monster, Position m_pos, int monsterID);

// class.c functions
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
void DrawDebug(Entity* mptr, int n_rooms);
void DrawEverything(Entity* mptr, int n_rooms);
void DrawMap();
void DrawMonsters(Entity* mptr, int n_rooms);
void DrawPlayer(Player* player);
void DrawStats(Player* player);


// engine.c functions
bool NcursesSetup(void);
void DisableMouseWheel();
void GameLoop(Entity* mptr, int n_rooms);
void CloseGame(void);

// fov.c functions
void MakeFOV(Player* playerint);
void ClearFOV(Player* player);
int GetDistance(Position origin, Position target);
bool IsInMap(int y, int x);
bool LineOfSight(Position origin, Position target);
int GetSign(int a);


// map.c functions
Entity** CreateEntities(void);
Position SetupMap(Entity* mptr, int n_rooms);
void FreeMap(void);

// monster.c functions
Entity* MonsterList(int n_rooms);
void UpdateMonsters(Entity* monster, int n_monsters);
void MoveMonster(Entity* monster, Position newPOS);
void UpdateMonsterVisible(Entity* monster, Player* player);
// void MoveMonster(Monster monster);
// bool CheckAggroRange(Position monsterPos, Position playerLastPos, int aggroRange);
// void MoveTowardsPlayer(Monster monster);
// void MoveAllMonsters();
// void SetMonsterListLen(int n_rooms);
void KeepMonsterIntegrity(Entity* mptr, bool oldSeen, bool oldVisible);
void ResetMoveFlags(Entity* monster, int n_rooms);
void Wander(Entity* mptr);



// player.c functions
Player* CreatePlayer(Position start_pos);
bool PlayerInput(int input);
void MovePlayer(Position newPos);
void AskPlayerInfo(Player* player);
void AssignStats(char input);
void AssignClass(char input);
void ChooseRace();
void ChooseName(char* name);
void ChooseClass();

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



#endif
