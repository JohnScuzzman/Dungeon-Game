#include <rogue.h>
#define WINDOW_WIDTH 32
#define WINDOW_HEIGHT 10
#define OFFSET 11

void RenderPauseMenu(WINDOW *menu, int cursor, int n_options, char** options) {
    int y = 3;
    int bottom = (WINDOW_WIDTH - OFFSET) / 2 + OFFSET;
    int center = ((WINDOW_WIDTH - OFFSET) / 2) + 3;
    int numLines = WINDOW_WIDTH - bottom;
    int top = 1;

    box(menu, 0, 0);

    // mvwhline(WINDOW *win, int y, int x, chtype ch, int n)
    // win - pointer to the window where the line is drawn.
    // y, x - The coordinates relative to the window's starting POS (0,0).
    // ch - The character and attributes to use for the line.
    // passing 0 uses the default horizontal character ACS_HLINE.
    mvwprintw(menu, top, center, " MENU ");
    mvwhline(menu, top, top, ACS_HLINE, numLines);
    mvwhline(menu, top, bottom - 1, ACS_HLINE, numLines );

    for (int i = 0; i < n_options; i++) {
        if (cursor == i) {
            wattron(menu, A_REVERSE);
            mvwprintw(menu, y, center, "%s", options[i]);
            wattroff(menu, A_REVERSE);
        }
        else {
            mvwprintw(menu, y, center, "%s", options[i]);
        }
        y++;
    }
    wrefresh(menu);
}

/* Creates a pause window and returns true if player quits */
/* Processes a new window and does a task if false. */
bool MakePauseMenu() {
    char *options[] = {
    "Resume",
    "Options",
    "Save Game",
    "Load Game",
    "Quit"
    };

    // TODO make this into a window struct and make one anytime we need one.
    int n_options = sizeof(options) / sizeof(char*);
    int pauseX = (COLS - WINDOW_WIDTH) / 2;
    int pauseY = (LINES - WINDOW_HEIGHT) / 2;
    bool escFlag = false;
    bool quitGame = false;
    int cursor = 0;
    int choice = -1;
    int ch;

    WINDOW *menu = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, pauseY, pauseX);
    keypad(menu, TRUE);
   
    /* First Render of Menu*/
    RenderPauseMenu(menu, cursor, n_options, options);

    while(!escFlag) {
        ch = wgetch(menu);
        escFlag = CheckEscape(ch);
        switch(ch) {
            case KEY_UP:
                if (cursor == 0) {
                    cursor = n_options - 1;
                }
                else {
                    cursor--;
                }
                break;
            case KEY_DOWN: 
                if (cursor == n_options - 1) {
                    cursor = 0;
                }
                else {
                    cursor++;
                }
                break;
            case 32: // SPB
                choice = cursor;
                escFlag = true;
                break;
            case 10: // ENTER
                choice = cursor;
                escFlag = true;
                break;
            default:
                break;
            }
        RenderPauseMenu(menu, cursor, n_options, options);
        }
        quitGame = ProcessPauseSelect(choice, menu);
        return quitGame;
    }

/* Returns true if we want to quit the game */
bool ProcessPauseSelect(int choice, WINDOW* menu){
    switch(choice){
        case 0: // Resume
            refresh();
            delwin(menu);
            return false;
            break;

        case 1: // Options
            // Do the options window here
            refresh();
            delwin(menu);
            return false;
            break;

        case 2: // Save
            // Do the save window here
            char saveName[32] = "Save 1";
            if(SavePlayerToJSON(saveName, player)){
                mvprintw(52, 2, "Saved Successfully!");
            }
            else{
                mvprintw(52, 2, "Saved Failed!");
            }
            refresh();
            delwin(menu);
            return false;
            break;

        case 3: // Load
            // Do the load window here
            refresh();
            delwin(menu);
            return false;
            break;

        case 4: // Quit
            refresh();
            delwin(menu);
            return true;
            break;

        default:
            refresh();
            delwin(menu);
            return false;
            break;
    }
}
