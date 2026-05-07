#include <rogue.h>

bool NcursesSetup(void)
{ 
  // Starts Ncurses.
  initscr();
  // Disable Ncurses from immediately drawing to the screen.
  noecho();
  // Make cursor invisible.
  curs_set(0);

  // Add color to the console!
  if (has_colors())
    {
        start_color();

        init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
        return true;
    }
  else
    {
        mvprintw(20, 50, "Console does not have color support. Please use another console.");
        getch();
        return false;
    }
}

void GameLoop(void)
{ 
    int ch;

    MakeFOV(player);
    DrawEverything();

    while(ch = getch())
    { 
        if (ch == 'x')
        { 
        break;
        } 
        PlayerInput(ch);
        DrawEverything();
    } 
} 

void CloseGame(void)
{ 
    
    endwin();
    // Free memory allocated by pointer.
    free(player);


} 
