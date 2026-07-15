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

int ENTITY_ID  = 256; // accounting for a theorhetical 256 monsters
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
  // Register crash handlers before doing anything else
  signal(SIGBUS, handle_crash);
  signal(SIGSEGV, handle_crash);
  // Optional: Catch Ctrl+C if you want to clean up on manual exits
  // signal(SIGINT, handle_crash);
  
  /* Check if user is playing in a compatible terminal. */
  bool compatibleTerminal;
  compatibleTerminal = NcursesSetup();
  
  if (compatibleTerminal)
  {/* Dungeon Crawl Stone Soup Method for handling numpad inputs*/
    define_key("\033Op", 1000);
    define_key("\033Oq", 1001);
    define_key("\033Or", 1002);
    define_key("\033Os", 1003);
    define_key("\033Ot", 1004);
    define_key("\033Ou", 1005);
    define_key("\033Ov", 1006);
    define_key("\033Ow", 1007);
    define_key("\033Ox", 1008);
    define_key("\033Oy", 1009);

	/* Weird exceptions */
	define_key("\033[1~", 1031); // Home
	define_key("\033[4~", 1034); // End
	define_key("\033[E",  1040); // center arrow

	// Handle middle mouse clicks
    mousemask(BUTTON1_CLICKED, NULL);

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