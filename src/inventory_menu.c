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
            mvwprintw(desc, 2, 2, "%s\n", playerInv[cursor]->itemDesc);
            switch (playerInv[cursor]->type) {
                case WEAPON:
                    Weapon weapon;
                    weapon = GetWeaponFromItem(playerInv[cursor]->itemID);
                    mvwprintw(desc, 3, 2, "DMG: %d - %d\n", weapon.minDMG, weapon.maxDMG);
                    mvwprintw(desc, 4, 2, "Range: %d\n", weapon.range);
                    mvwprintw(desc, 5, 2, "Value: %d\n", weapon.item.value);
                break;
                case ARMOR:
                    Armor armor;
                    armor = GetArmorFromItem(playerInv[cursor]->itemID);
                    mvwprintw(desc, 3, 2, "AC: %d\n", armor.AC);
                    char* armorType = GetArmorType(armor.type);
                    mvwprintw(desc, 4, 2, "Type: %s\n", armorType);
                    mvwprintw(desc, 5, 2, "Value: %d\n", armor.item.value);
                default:
                break;
            }
            wattroff(menu, A_REVERSE);
        }
        else {
            mvwprintw(menu, y, 2, "%s", playerInv[i]->itemName);
            // mvwprintw(desc, y, 2, "%s\n", playerInv[cursor]->itemDesc);
        }
        y++;
    box(desc, 0, 0);
    mvwprintw(desc, top, center - 3, " DESCRIPTION ");
    mvwhline(desc, top, top, ACS_HLINE, numLines);
    mvwhline(desc, top, titleRight + 2, ACS_HLINE, numLines - 1);
    wrefresh(desc);
    wrefresh(menu);
    }
}
/* Creates a pause window and returns true if player quits */
/* Processes a new window and does a task if false. */
bool MakeInventoryMenu(Item* items) {
    
    Item* playerInv[INVENTORY_SIZE];
    for(int i = 0; i < INVENTORY_SIZE; i++) {
        playerInv[i] = &player->inventory[i];
    }
    int n_options = player->invTail;
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

        default:
            refresh();
            delwin(menu);
            return false;
            break;

    }
}