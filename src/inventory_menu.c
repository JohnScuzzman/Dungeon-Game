#include <rogue.h>
#define WINDOW_WIDTH 50
#define WINDOW_HEIGHT 25
#define OFFSET 11
#define INVENTORY_SIZE 64

void RenderInventoryMenu(WINDOW *menu, int cursor, int n_options, char** options) {
    int y = 3;
    int bottom = (WINDOW_WIDTH - OFFSET) / 2 + OFFSET;
    int center = ((WINDOW_WIDTH - OFFSET) / 2) + 3;
    int numLines = WINDOW_WIDTH - 2 - bottom;
    int top = 1;

    box(menu, 0, 0);

    // mvwhline(WINDOW *win, int y, int x, chtype ch, int n)
    // win - pointer to the window where the line is drawn.
    // y, x - The coordinates relative to the window's starting POS (0,0).
    // ch - The character and attributes to use for the line.
    // passing 0 uses the default horizontal character ACS_HLINE.
    mvwprintw(menu, top, center - 3, " INVENTORY ");
    mvwhline(menu, top, top, ACS_HLINE, numLines );
    mvwhline(menu, top, bottom, ACS_HLINE, numLines +1);

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
bool MakeInventoryMenu(Item* items) {
    
    char* options[INVENTORY_SIZE] = {
        player->inventory[0].itemName,
        player->inventory[1].itemName,
        player->inventory[2].itemName,
        player->inventory[3].itemName,
        player->inventory[4].itemName,
        player->inventory[5].itemName,
        player->inventory[6].itemName,
        player->inventory[7].itemName,
        player->inventory[8].itemName,
        player->inventory[9].itemName,
        player->inventory[10].itemName,
        player->inventory[11].itemName,
        player->inventory[12].itemName,
        player->inventory[13].itemName,
        player->inventory[14].itemName,
        player->inventory[15].itemName,
        player->inventory[16].itemName,
        player->inventory[17].itemName,
        player->inventory[18].itemName,
        player->inventory[19].itemName,
        player->inventory[20].itemName,
        player->inventory[21].itemName,
        player->inventory[22].itemName,
        player->inventory[23].itemName,
        player->inventory[24].itemName,
        player->inventory[25].itemName,
        player->inventory[26].itemName,
        player->inventory[27].itemName,
        player->inventory[28].itemName,
        player->inventory[29].itemName,
        player->inventory[30].itemName,
        player->inventory[31].itemName,
        player->inventory[32].itemName,
        player->inventory[33].itemName,
        player->inventory[34].itemName,
        player->inventory[35].itemName,
        player->inventory[36].itemName,
        player->inventory[37].itemName,
        player->inventory[38].itemName,
        player->inventory[39].itemName,
        player->inventory[40].itemName,
        player->inventory[41].itemName,
        player->inventory[42].itemName,
        player->inventory[43].itemName,
        player->inventory[44].itemName,
        player->inventory[45].itemName,
        player->inventory[46].itemName,
        player->inventory[47].itemName,
        player->inventory[48].itemName,
        player->inventory[49].itemName,
        player->inventory[50].itemName,
        player->inventory[51].itemName,
        player->inventory[52].itemName,
        player->inventory[53].itemName,
        player->inventory[54].itemName,
        player->inventory[55].itemName,
        player->inventory[56].itemName,
        player->inventory[57].itemName,
        player->inventory[58].itemName,
        player->inventory[59].itemName,
        player->inventory[60].itemName,
        player->inventory[61].itemName,
        player->inventory[62].itemName,
        player->inventory[63].itemName,
    };
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
    RenderInventoryMenu(menu, cursor, n_options, options);

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
        RenderInventoryMenu(menu, cursor, n_options, options);
        }
        quitGame = ProcessInventorySelect(choice, menu);
        return quitGame;
    }

/* Returns true if we want to quit the game */
bool ProcessInventorySelect(int choice, WINDOW* menu){
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
    }
}