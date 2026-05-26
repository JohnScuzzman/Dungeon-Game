#include <rogue.h>

const int LOG_WIDTH = 128;
const int LOG_HEIGHT = 47;
const int LOG_SIZE = 100;

void CreateLog() {

    /* Create a pad for the log to use.*/
    WINDOW *pad = newpad(LOG_SIZE, 50);
    scrollok(pad, TRUE); // Allow the pad to scroll internally
    
    for (int i = 0; i < LOG_SIZE; i++) {
        wprintw(pad, "Combat Event #%d\n", i);
    }

    int current_line = 0;
    while (1) {
        // prefresh(pad, pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol)
        // pad = window to use, current_line, 0 are the coordinates of where the pad starts internally.
        // smins are the 2 top left coords where the pad begins on the physical screen.
        // max are the 2 bottom right coords where the pad ends on the physical screen.
        prefresh(pad, current_line, 0, 22, LOG_WIDTH, LOG_HEIGHT, (LOG_WIDTH) + 32);
        int next_ch;
        int ch = getch();
        if (ch == 27) { 
            // check for escape.
            nodelay(stdscr, TRUE);
            next_ch = getch();
            nodelay(stdscr, FALSE);
        }
        if (next_ch == ERR) {
            break;
        } 
        if (ch == KEY_UP && current_line > 0) current_line--;
        if (ch == KEY_DOWN && current_line < LOG_SIZE - LOG_HEIGHT) current_line++;
    }

    endwin();
}
