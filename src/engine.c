#include <rogue.h>

bool NcursesSetup(void) { 
  /* Starts Ncurses. */
  initscr();
  /* Disable Ncurses from immediately drawing to the screen. */ 
  noecho();
  /* Make cursor invisible. */ 
  curs_set(0);

  /* Add color to the console! */
  if (has_colors()) {
        start_color();

        init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
        return true;
    }
  else {
        mvprintw(20, 50, "Console does not have color support. Please use another console.");
        getch();
        return false;
    }
}

void DisableMouseWheel() {
    mouseinterval(0);
}

void GameLoop(Entity* mptr, int n_rooms) { 
    int ch;
    MakeFOV(player);
    DrawEverything(mptr, n_rooms);
    bool PMove = false;
    while((ch = getch()) != 'x')
    { 
        PMove = false;
        if(ch != ERR) {
            int i = 0;
        PMove = PlayerInput(ch);
        while (!((mptr + i)->hasMoved) && i < n_rooms && PMove == true){
            Wander(mptr + i);
            i++;
        }
        ResetMoveFlags(mptr, n_rooms);
        MakeFOV(player);
        DrawEverything(mptr, n_rooms);
        PMove = false;
        }

    } 
        
} 

void CloseGame(void) { 
    free(mptr);
    endwin();
    /* Free memory allocated by pointer. */
    free(player);
} 
