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

typedef struct
{
    int y;
    int x;
} Position;

typedef struct
{
  char entityName[MAX_NAME_SIZE];
  char entityRace[MAX_NAME_SIZE];
  char entityClass[MAX_NAME_SIZE];
  char entityArmor[MAX_NAME_SIZE];
  char entityWeapon[MAX_NAME_SIZE];
  int entityHP;
  int entityAC;
  int entityMaxDMG;
  int entityMinDMG;
  int entityLVL;
  Position pos;
  char ch;
  int color;
} Entity;

typedef struct
{
  char ch;
  int color;
  bool noCollision;
  bool transparent;
  bool visible;
  bool seen;
} Tile;

typedef struct
{
  Position pos;
  char ch;
  int color;
  bool noCollision;
  bool transparent;
  bool visible;
  bool seen;
  char monsterName[MAX_NAME_SIZE];
  char monsterRace[MAX_NAME_SIZE];
  char monsterClass[MAX_NAME_SIZE];
  char monsterArmor[MAX_NAME_SIZE];
  char monsterWeapon[MAX_NAME_SIZE];
  int monsterHP;
  int monsterAC;
  int monsterMaxDMG;
  int monsterMinDMG;
  int monsterLVL;
} Monster;

typedef struct
{
  int height; 
  int width;
  // pos used to connect rooms with hallways.
  Position pos;
  Position center;
} Room;


//asciiart.c funcions
void TitleScreen();

// draw.c functions
void DrawMap(void);
void DrawEntity(Entity* entity);
void DrawEverything(void);
void DrawStats(Entity* entity);

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

// engine.c functions
bool NcursesSetup(void);
void DisableMouseWheel();
void GameLoop(void);
void CloseGame(void);

// map.c functions
Tile** CreateTiles(void);
void FreeMap(void);
Position SetupMap(void);

// player.c functions
Entity* CreatePlayer(Position start_pos);
void PlayerInput(int input);
void MovePlayer(Position newPos);
void AskPlayerInfo(Entity* player);
void AssignStats(char input);
void AssignClass(char input);
void ChooseRace();
void ChooseName(char* name);
void ChooseClass();

// room.c functions
Room CreateRoom(int y, int x, int height, int width);
void AddRoomToMap(Room room);
void ConnectRooms(Position centerOne, Position centerTwo);
void AddMonster(Monster monster);

// fov.c functions
void MakeFOV(Entity* player);
void ClearFOV(Entity* player);
int GetDistance(Position origin, Position target);
bool IsInMap(int y, int x);
bool LineOfSight(Position origin, Position target);
int GetSign(int a);

// monster.c functions
Monster CreateMonster(Position m_pos, int monsterID);
void MoveMonster(Position newPos);

// monsterinfo.c functions
void AssignGoblinWarrior(Monster monster);
void AssignKoboldWarrior(Monster monster);
void AssignGoblinRanger(Monster monster);
void AssignHobgoblinWarrior(Monster monster);

// Externals 
// Used in tandem with main to let any functions use these outside of main.
extern Entity* player;
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;

// Array of tiles
extern Tile** map;

#endif
