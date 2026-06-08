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
int MAX_MONSTER_NAME = 33;
int MAP_HEIGHT = 50;
int MAP_WIDTH = 125;
int LOG_HEIGHT = 22;
int LOG_SIZE  = 27;
int LOG_WIDTH = 128;



/* These are like global pointers.*/ 
/* We can use these in any function without declaring them over and over.*/
Player* player; //player->equippedWeapon.DMG
Entity** map;
Entity* mptr; 
CombatHistory* combatHistory;
LogQueue* q;
Item* items;

int main(void)
{
  /* Check if user is playing in a compatible terminal. */
  bool compatibleTerminal;
  compatibleTerminal = NcursesSetup();
  
  if (compatibleTerminal)
  {
    mousemask(BUTTON1_CLICKED, NULL);
    /* Adjust layout to terminal size so the view scales */
    int term_rows, term_cols;
    getmaxyx(stdscr, term_rows, term_cols);
    int sidebar_width = 40;
    if (term_cols < 100) sidebar_width = term_cols / 3;
    if (sidebar_width < 20) sidebar_width = 20;
    MAP_WIDTH = term_cols - sidebar_width - 3;
    if (MAP_WIDTH < 20) MAP_WIDTH = 20;
    MAP_HEIGHT = term_rows - 3;
    if (MAP_HEIGHT < 10) MAP_HEIGHT = 10;
    LOG_WIDTH = MAP_WIDTH + 2;
    LOG_HEIGHT = 22;
    Position start_pos;
    /* Generate seeds */
    srand(time(NULL));

    /* Create random number between 10 and 20.*/ 
    /* These will be both the num of rooms & monsters created.*/
    int n_rooms =  (rand() % 11) + 10;
    int n_monsters = n_rooms - 1;


    /* Item table */
    items = CreateItemTable();

    /* Create our map using function in map.c*/
    map = CreateEntities();

    /* Make # of rooms -1 number of monsters. */
    /* Point mptr at monsterlist[0]. */
    mptr = MonsterList(n_monsters);

    /* Create a starting position for player and setup the floor in map.c*/
    /* Pass the monsterList to populate it.*/
    start_pos = SetupMap(mptr, n_rooms);

    /* Place player using method in makeplayer.c*/
    player = CreatePlayer(start_pos);

    /* Create Combat History && Log*/
    combatHistory = CreateCombatHistory(mptr[0]);
    q = MakeCombatLogQueue();

    /* Player's Inv*/
    CreatePlayerInv();

    /* Call Title Screen from asciiart.c*/
    TitleScreen();

    /* Ask info about the player's character from functions in player.c */
    AskPlayerInfo(player);

    keypad(stdscr, TRUE);

    /* Start main game loop located in engine.c */
    /* Pass the pointer to monsterList[0]. */
    /* Pass the number of monsters and rooms made. */
    GameLoop(mptr, combatHistory, n_monsters, q, items);
    CloseGame();
  }
  else
  {
    endwin();
  }

  return 0;
}