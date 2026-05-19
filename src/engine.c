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
        init_pair(HIGHLIGHT_COLOR, COLOR_BLACK, COLOR_WHITE);
        return true;
    }
    else {
        mvprintw(20, 50, "Console does not have color support. Please use another console.");
        getch();
        return false;
    }
}

void Cursor(int x, int y, int length){
    //A_BLINK 
    mvchgat(x, y, length, A_BOLD | A_STANDOUT | A_DIM, VISIBLE_COLOR, NULL);
}

void RemoveCursor(int x, int y, int length) {
    mvchgat(x, y, length, A_NORMAL, 0, NULL);
}

void GameLoop(Entity* mptr, int n_rooms) { 
    bool leaveFlag = false;
    int ch, next_ch;
    MakeFOV(player);
    DrawEverything(mptr, n_rooms);
    DrawPlayerBlink(player);
    bool PMove = false;
    keypad(stdscr, FALSE);
    while(!leaveFlag)
    { 
        ch = getch();
        if (ch == 27) { 
            // check for esape.
            nodelay(stdscr, TRUE);
            next_ch = getch();
            nodelay(stdscr, FALSE);
        }
        if (next_ch == ERR) {
            leaveFlag = true;
        }
        // Pmove = false spam here used to help force monsters to move once.
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
