#include <rogue.h>
#define WINDOW_WIDTH 72
#define WINDOW_HEIGHT 34
#define OFFSET 11

void RenderInventoryMenu(WINDOW *invMenu, int cursor, int n_options, char** options) {
    int y = 3;
    int bottom = (WINDOW_WIDTH - OFFSET) / 2 + OFFSET;
    int center = ((WINDOW_WIDTH - OFFSET) / 2) + 3;
    int numLines = WINDOW_WIDTH - 2 - bottom;
    int top = 1;

    box(invMenu, 0, 0);

    // mvwhline(WINDOW *win, int y, int x, chtype ch, int n)
    // win - pointer to the window where the line is drawn.
    // y, x - The coordinates relative to the window's starting POS (0,0).
    // ch - The character and attributes to use for the line.
    // passing 0 uses the default horizontal character ACS_HLINE.
    mvwprintw(invMenu, top, center, " INVENTORY ");
    mvwhline(invMenu, top, top, ACS_HLINE, numLines);
    mvwhline(invMenu, top, bottom, ACS_HLINE, numLines);

    for (int i = 0; i < n_options; i++) {
        if (cursor == i) {
            wattron(invMenu, A_REVERSE);
            mvwprintw(invMenu, y, center, "%s", options[i]);
            wattroff(invMenu, A_REVERSE);
        }
        else {
            mvwprintw(invMenu, y, center, "%s", options[i]);
        }
        y++;
    }
    wrefresh(invMenu);
}

/* Creates a pause window and returns true if player quits */
/* Processes a new window and does a task if false. */
bool MakeInventoryMenu() {
    char *item_options[INVENTORY_SIZE];
    for(int i = 0; i < INVENTORY_SIZE; i++) {
        item_options[i] = playerInv[i].itemName;
    }

    int n_options = INVENTORY_SIZE / sizeof(char*);
    int pauseX = (COLS - WINDOW_WIDTH) / 2;
    int pauseY = (LINES - WINDOW_HEIGHT) / 2;
    bool escFlag = false;
    bool quitGame = false;
    int cursor = 0;
    int choice = -1;
    int ch;

    WINDOW *invMenu = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, pauseY, pauseX);
    keypad(invMenu, TRUE);
   
    /* First Render of Menu*/
    RenderInventoryMenu(invMenu, cursor, n_options, item_options);

    while(!escFlag) {
        ch = wgetch(invMenu);
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
        RenderInventoryMenu(invMenu, cursor, n_options, item_options);
        }
        quitGame = ProcessItemSelect(choice, invMenu);
        return quitGame;
    }

/* Returns true if we want to quit the game */
bool ProcessItemSelect(int choice, WINDOW* invMenu){
    switch(choice){
        case 0: // Resume
        refresh();
        delwin(invMenu);
        return true;
        break;
        case 1: // Options
        // Do the options window here
        refresh();
        delwin(invMenu);
        return true;
        break;
        case 2: // Save
        // Do the save window here
        refresh();
        delwin(invMenu);
        return true;
        break;
        case 3: // Load
        // Do the load window here
        refresh();
        delwin(invMenu);
        return true;
        break;
        case 4: // Quit
        refresh();
        delwin(invMenu);
        return true;
        break;
    }
}
