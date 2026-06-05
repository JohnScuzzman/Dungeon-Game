#include <rogue.h>
#define WINDOW_WIDTH 61
#define WINDOW_HEIGHT 47
#define OFFSET 11
#define INVENTORY_SIZE 64

void RenderInventoryMenu(WINDOW *menu, WINDOW *desc, int cursor, int n_options, Item** playerInv) {
    int y = 3;
    int titleRight = (WINDOW_WIDTH - OFFSET) / 2 + OFFSET;
    int center = ((WINDOW_WIDTH - OFFSET) / 2) + 3;
    int numLines = WINDOW_WIDTH - 2 - titleRight;
    int top = 1;

    /* Diabolical Pointer Upcasting */
    // Item* itemptr = (Item*)&player->equippedWeapon;


    box(menu, 0, 0);
    // mvwhline(WINDOW *win, int y, int x, chtype ch, int n)
    // win - pointer to the window where the line is drawn.
    // y, x - The coordinates relative to the window's starting POS (0,0).
    // ch - The character and attributes to use for the line.
    // passing 0 uses the default horizontal character ACS_HLINE.
    mvwprintw(menu, top, center - 3, " INVENTORY ");
    mvwhline(menu, top, top, ACS_HLINE, numLines );
    mvwhline(menu, top, titleRight, ACS_HLINE, numLines + 1);

    box(desc, 0, 0);
    mvwprintw(desc, top, center - 3, " DESCRIPTION ");
    mvwhline(desc, top, top, ACS_HLINE, numLines);
    mvwhline(desc, top, titleRight + 2, ACS_HLINE, numLines - 1);

    for (int i = 0; i < player->invTail; i++) {
        if (cursor == i) {
            wattron(menu, A_REVERSE);
            mvwprintw(menu, y, 2, "%s", playerInv[i]->itemName);
            mvwprintw(desc, y, 2, "%s\n", playerInv[i]->itemDesc);
            wattroff(menu, A_REVERSE);

        }
        else {
            mvwprintw(menu, y, 2, "%s", playerInv[i]->itemName);
            mvwprintw(desc, y, 2, "%s\n", playerInv[i]->itemDesc);
        }
        y++;
    }
    box(desc, 0, 0);
    mvwprintw(desc, top, center - 3, " DESCRIPTION ");
    mvwhline(desc, top, top, ACS_HLINE, numLines);
    mvwhline(desc, top, titleRight + 2, ACS_HLINE, numLines - 1);
    wrefresh(desc);
    wrefresh(menu);
}

/* Creates a pause window and returns true if player quits */
/* Processes a new window and does a task if false. */
bool MakeInventoryMenu(Item* items) {
    
    Item* playerInv[INVENTORY_SIZE] = {
        &player->inventory[0],
        &player->inventory[1],
        &player->inventory[2],
        &player->inventory[3],
        &player->inventory[4],
        &player->inventory[5],
        &player->inventory[6],
        &player->inventory[7],
        &player->inventory[8],
        &player->inventory[9],
        &player->inventory[10],
        &player->inventory[11],
        &player->inventory[12],
        &player->inventory[13],
        &player->inventory[14],
        &player->inventory[15],
        &player->inventory[16],
        &player->inventory[17],
        &player->inventory[18],
        &player->inventory[19],
        &player->inventory[20],
        &player->inventory[21],
        &player->inventory[22],
        &player->inventory[23],
        &player->inventory[24],
        &player->inventory[25],
        &player->inventory[26],
        &player->inventory[27],
        &player->inventory[28],
        &player->inventory[29],
        &player->inventory[30],
        &player->inventory[31],
        &player->inventory[32],
        &player->inventory[33],
        &player->inventory[34],
        &player->inventory[35],
        &player->inventory[36],
        &player->inventory[37],
        &player->inventory[38],
        &player->inventory[39],
        &player->inventory[40],
        &player->inventory[41],
        &player->inventory[42],
        &player->inventory[43],
        &player->inventory[44],
        &player->inventory[45],
        &player->inventory[46],
        &player->inventory[47],
        &player->inventory[48],
        &player->inventory[49],
        &player->inventory[50],
        &player->inventory[51],
        &player->inventory[52],
        &player->inventory[53],
        &player->inventory[54],
        &player->inventory[55],
        &player->inventory[56],
        &player->inventory[57],
        &player->inventory[58],
        &player->inventory[59],
        &player->inventory[60],
        &player->inventory[61],
        &player->inventory[62],
        &player->inventory[63],
    };
    int n_options = sizeof(playerInv) / sizeof(Item*);
    int invX1 = 2;
    int invX2 = 64;
    int invY = 1;
    bool escFlag = false;
    bool quitGame = false;
    int cursor = 0;
    int choice = -1;
    int ch;

    WINDOW *menu = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, invY, invX1);
    WINDOW *desc = newwin((WINDOW_HEIGHT / 2), WINDOW_WIDTH, invY, invX2);
    keypad(menu, TRUE);
    keypad(desc, FALSE);
   
    /* First Render of Menu*/
    RenderInventoryMenu(menu, desc, cursor, n_options, playerInv);

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
        RenderInventoryMenu(menu, desc, cursor, n_options, playerInv);
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