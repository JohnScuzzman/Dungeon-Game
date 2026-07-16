#include <rogue.h>
/*  If you change MAP_HEIGHT or MAP_WIDTH, 
You need to also modify the parameters we are using to create our rooms,
so that they are within the dimensions of the map.
Otherwise, the game will crash when it tries to allocate a room outside of the map. */
const char *DIRECTIONS[HEADINGS] = {
    "North",
    "West",
    "South",
    "East",
    "North West",
    "South West",
    "South East",
    "North East"
};
const int LVL_EXP_VALUES[MAX_LEVEL] = {
  LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5, 
  LEVEL_6, LEVEL_7, LEVEL_8, LEVEL_9, LEVEL_10
};

int ENTITY_ID = 256; // accounting for a theorhetical 256 monsters
int LOG_HEIGHT = 22;
int LOG_SIZE  = 27;
int LOG_WIDTH = 128;
int MAX_MONSTER_NAME = 33;
int MAX_NPCS = 512;
int MAX_ONSCREEN_NPCS = 64;
int MAP_HEIGHT = 50;
int MAP_WIDTH = 125;
int MAX_DUNGEON_FLOORS = 1024;
int RADIUS = 15;

/* These are like global pointers.*/ 
/* We can use these in any function without declaring them over and over.*/
Player* player; //player->equippedWeapon.DMG
Entity** map;
Entity* mptr; 
Entity* nptr;
Entity* npcs;
CombatHistory* combatHistory;
LogQueue* q;
Item* items;
DungeonInfo* dungeonInfo;

int main(void)
{
	#ifdef _WIN32
	#ifndef SIGBUS
	#define SIGBUS SIGSEGV
	#endif
	#endif
	// Register crash handlers before doing anything else
	signal(SIGBUS, handle_crash);
	signal(SIGSEGV, handle_crash);
	// Optional: Catch Ctrl+C if you want to clean up on manual exits
	// signal(SIGINT, handle_crash);

	/* Check if user is playing in a compatible terminal. */
	bool compatibleTerminal;
	compatibleTerminal = NcursesSetup(); 
	if (compatibleTerminal) {
	int maxX, maxY;
    // For windows version
    resize_term(2000, 2000); // something larger than 1920 

    getmaxyx(stdscr, maxY, maxX);

    resize_term(maxY - 1, maxX - 1); 

    /* Generate seeds */
    srand(time(NULL));

    /* Create random number between 10 and 20.*/ 
    /* These will be both the num of rooms & monsters created.*/
    int n_rooms =  (rand() % 11) + 10;
    int n_monsters = n_rooms - 1;

	Position start_pos;

    /*Dungeon Information*/
    dungeonInfo = MakeDungeonInfo();

    /* Item table */
    items = CreateItemTable();

    /* Create our map using function in map.c*/
    map = CreateEntities();

    /* Make # of rooms -1 number of monsters. */
    /* Point mptr at monsterlist[0]. */
    mptr = MonsterList(n_monsters);

    /* Generate empty npc list of (current) size 64 for localized floor use*/
    nptr = NPCList(MAX_ONSCREEN_NPCS);

    /* Generate global list of unique npcs somewhat similar to items*/
    // npcs = NPCList(MAX_NPCS);

    /* Create a starting position for player and setup the floor in map.c*/
    /* Pass the monsterList to populate it.*/
    start_pos = SetupMap(mptr, n_rooms);

    /* Place player using method in makeplayer.c*/
    player = CreatePlayer(start_pos);

    /* Player's Inv*/
    CreatePlayerInv();

    /* Create Combat History && Log*/
    combatHistory = CreateCombatHistory(mptr[0]);
    q = MakeCombatLogQueue();

    /* Call Title Screen from asciiart.c*/
    TitleScreen();

    /* Ask info about the player's character from functions in make_player.c */
    AskPlayerInfo(player);
    
    ChooseClass(); // Choose Class && Race.

    keypad(stdscr, TRUE);

    /* Start main game loop located in engine.c */
    /* Pass the pointer to monsterList[0]. */
    /* Pass the number of monsters and rooms made. */
    GameLoop(combatHistory, n_monsters, q, items);
    
    CloseGame();
  }
  else
  {
    endwin();
  }

  return 0;
}
