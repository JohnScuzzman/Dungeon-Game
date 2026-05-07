#include <rogue.h>

//  if you change MAP_HEIGHT or MAP_WIDTH, 
//  you need to also modify the parameters we are using to create our rooms
//  so that they are within the dimensions of the map.
//  Otherwise, the game will crash when it tries to allocate a room outside of the map.
const int MAP_HEIGHT = 50;
const int MAP_WIDTH = 125;

// Entity points at player object,
// Entities can be used in functions outside main.
Entity* player;
Tile** map;

int main(void)
{
  Position start_pos;

  // Check if user is playing in a compatible terminal.
  bool compatibleTerminal;

  compatibleTerminal = NcursesSetup();
  

  if (compatibleTerminal)
  {
    TitleScreen();
    srand(time(NULL));
    map = CreateTiles();
    start_pos = SetupMap();
    player = CreatePlayer(start_pos);
    AskPlayerInfo(player);

    GameLoop();

    CloseGame();
  }
  else
  {
    endwin();
  }

  return 0;
}