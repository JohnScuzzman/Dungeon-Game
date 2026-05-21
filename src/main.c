#include <rogue.h>
/*  If you change MAP_HEIGHT or MAP_WIDTH, 
You need to also modify the parameters we are using to create our rooms,
so that they are within the dimensions of the map.
Otherwise, the game will crash when it tries to allocate a room outside of the map. */
const int MAP_HEIGHT = 50;
const int MAP_WIDTH = 125;
const int MAX_MONSTER_NAME = 33;

/* These are like global pointers.*/ 
/* We can use these in any function without declaring them over and over.*/
Player* player;
Entity** map;
Entity* mptr;
CombatHistory* combatHistory;

int main(void)
{
  /* Check if user is playing in a compatible terminal. */
  bool compatibleTerminal;
  compatibleTerminal = NcursesSetup();
  
  if (compatibleTerminal)
  {
    mousemask(BUTTON1_CLICKED, NULL);
    Position start_pos;
    /* Generate seeds */
    srand(time(NULL));

    /* Create random number between 10 and 20.*/ 
    /* These will be both the num of rooms & monsters created.*/
    int n_rooms =  (rand() % 11) + 10;
    int n_monsters = n_rooms - 1;

    /* Create our map using function in map.c*/
    map = CreateEntities();

    /* Make # of rooms -1 number of monsters. */
    /* Point mptr at monsterlist[0]. */
    mptr = MonsterList(n_monsters);

    /* Create a starting position for player and setup the floor in map.c*/
    /* Pass the monsterList to populate it.*/
    start_pos = SetupMap(mptr, n_rooms);

    /* Place player using method in player.c*/
    player = CreatePlayer(start_pos);

    /* Create Combat History */
    combatHistory = CreateCombatHistory(mptr[0]);
    
    /* Call Title Screen from asciiart.c*/
    TitleScreen();

    /* Ask info about the player's character from functions in player.c */
    AskPlayerInfo(player);

    keypad(stdscr, TRUE);

    /* Start main game loop located in engine.c */
    /* Pass the pointer to monsterList[0]. */
    /* Pass the number of monsters and rooms made. */
    GameLoop(mptr, combatHistory, n_monsters);
    CloseGame();
  }
  else
  {
    endwin();
  }

  return 0;
}