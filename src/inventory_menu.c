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
    bool equippedItem = false;
    /* Update players info in real time. */
    wclear(menu);

    box(menu, 0, 0);
    mvwprintw(menu, top, center - 3, " INVENTORY ");
    mvwhline(menu, top, top, ACS_HLINE, numLines );
    mvwhline(menu, top, titleRight, ACS_HLINE, numLines + 1);

    box(desc, 0, 0);
    mvwprintw(desc, top, center - 3, " DESCRIPTION ");
    mvwhline(desc, top, top, ACS_HLINE, numLines);
    mvwhline(desc, top, titleRight + 2, ACS_HLINE, numLines - 1);
    
    for (int i = 0; i < player->invTail; i++) {
        if(playerInv[i]->itemID == player->equippedMelee.item.itemID || playerInv[i]->itemID == player->equippedRanged.item.itemID || playerInv[i]->itemID == player->equippedArmor.item.itemID) {
            wattron(menu, A_DIM);
            mvwprintw(menu, y, (strlen(playerInv[i]->itemName) + 2), " (Equipped)");
            wattroff(menu, A_DIM);
        }
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
                    break;
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
    bool quitMenu = false;
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
                escFlag = MakeItemOptionsWindow(playerInv, choice);
                break;
            case 10: // ENTER
                choice = cursor;
                escFlag = MakeItemOptionsWindow(playerInv, choice);
                break;
            default:
                break;
            }
        RenderInventoryMenu(menu, desc, cursor, n_options, playerInv);
        }
        quitMenu = InventorySelect(choice, menu);
        return quitMenu;
    }

/* Returns true if we want to exit the inventory choice*/
bool InventorySelect(int choice, WINDOW* menu){
    switch(choice){
        case 0: // Item 1
            refresh();
            delwin(menu);
            return false;
            break;

        case 1: // Item 2
            // Do the options window here
            refresh();
            delwin(menu);
            return false;
            break;

        case 2: // Item 3
            // Do the save window here
            refresh();
            delwin(menu);
            return false;
            break;

        case 3: // Item 4
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

bool MakeItemOptionsWindow(Item** playerInv, int choice) {
    bool unEquipMenu = false;
    if (playerInv[choice]->itemID == player->equippedMelee.item.itemID || playerInv[choice]->itemID == player->equippedRanged.item.itemID || playerInv[choice]->itemID == player->equippedArmor.item.itemID) {
        unEquipMenu = true;
    }
    char *options1[] = {
    "Equip",
    "Transfer",
    "Drop",
    "Examine",
    "Exit",
    };
    char *options2[] = {
    "Unequip",
    "Transfer",
    "Drop",
    "Examine",
    "Exit",
    };

    //Sorry about the magic numbers
    int n_options = sizeof(options1) / sizeof(char*);
    int invX = WINDOW_WIDTH / 2;
    int invY = choice + 3;
    bool escFlag = false;
    int cursor = 0;
    int newChoice = -1;
    int ch;
    
    // Make a tiny window with 5 options for player to choose from.
    WINDOW *invOp = newwin(((WINDOW_HEIGHT / 4) - 4), (WINDOW_WIDTH / 4), invY, invX);
    keypad(invOp, TRUE);

    if (unEquipMenu) {
        RenderInvOptionMenu(invOp, cursor, n_options, options2);
    }
    else {
        RenderInvOptionMenu(invOp, cursor, n_options, options1);
    }

    while(!escFlag) {
        ch = wgetch(invOp);
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
                newChoice = cursor;
                escFlag = true;
                break;
            case 10: // ENTER
                newChoice = cursor;
                escFlag = true;
                break;
            default:
                break;
            }
        if (unEquipMenu) {
            RenderInvOptionMenu(invOp, cursor, n_options, options2);
        }
        else {
            RenderInvOptionMenu(invOp, cursor, n_options, options1);
        }
    }
    return InvOptionSelect(playerInv, choice, newChoice, invOp, unEquipMenu);
}

void RenderInvOptionMenu(WINDOW *invOp, int cursor, int n_options, char** options) {
    int y = 1;
    int titleRight = (WINDOW_WIDTH - OFFSET) / 2 + OFFSET;
    int center = (WINDOW_WIDTH / 2) - (OFFSET * 3) + 5;
    int numLines = WINDOW_WIDTH - 2 - titleRight;
    int top = 1;
    int centerY, centerX;
    getmaxyx(invOp, centerY, centerX);
    box(invOp, 0, 0);

    for (int i = 0; i < n_options; i++) {
        center = (centerX - strlen(options[i])) / 2;
        if (cursor == i) {
            wattron(invOp, A_REVERSE);
            mvwprintw(invOp, y, center, "%s", options[i]);
            wattroff(invOp, A_REVERSE);
        }
        else {
            mvwprintw(invOp, y, center, "%s", options[i]);
        }
        y++;
    }
    wrefresh(invOp);
}



bool InvOptionSelect(Item** playerInv, int prevChoice, int newChoice, WINDOW* menu, bool unEquipMenu) {
    switch(newChoice){
        case 0: // Equip / Unequip
            if(unEquipMenu){
                Unequip(*playerInv[prevChoice]);
            } 
            else {
                Equip(*playerInv[prevChoice]);
            }
            DrawEverything();
            refresh();
            delwin(menu);
            return false;
            break;

        case 1: // Transfer
            refresh();
            delwin(menu);
            return false;
            break;

        case 2: // Drop
            Unequip(*playerInv[prevChoice]);
            RemoveFromPlayerInventory(*playerInv[prevChoice]);
            DrawEverything();
            refresh();
            delwin(menu);
            return false;
            break;

        case 3: // Examine
            // Do the load window here
            refresh();
            delwin(menu);
            return false;
            break;
        case 4: // Exit
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