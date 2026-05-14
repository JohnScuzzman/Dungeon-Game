#include <rogue.h>

/*  If you change MAP_HEIGHT or MAP_WIDTH, 
You need to also modify the parameters we are using to create our rooms,
so that they are within the dimensions of the map.
Otherwise, the game will crash when it tries to allocate a room outside of the map. */
const int MAP_HEIGHT = 50;
const int MAP_WIDTH = 125;

/* Entity points at player object,
Entities can be used in functions outside main.*/ 
Entity* player;
Tile** map;

int main(void)
{
  Position start_pos;

  /* Check if user is playing in a compatible terminal. */
  bool compatibleTerminal;

  compatibleTerminal = NcursesSetup();
  

  if (compatibleTerminal)
  {
    /* Generate seeds */
    srand(time(NULL));

    /* Create our map*/
    map = CreateTiles();

    /* Create a starting position for player and setup the map.*/
    start_pos = SetupMap();

    /* Place player */
    player = CreatePlayer(start_pos);

    /* Call Title Screen from asciiart.c*/
    TitleScreen();

    /* Ask info about the player's character.*/
    AskPlayerInfo(player);

    /* Start main game loop */
    GameLoop();

    CloseGame();
  }
  else
  {
    endwin();
  }

  return 0;
}