#include <rogue.h>
#define WINDOW_WIDTH 61
#define WINDOW_HEIGHT 47
#define OFFSET 11
#define INVENTORY_SIZE 65

/*
Creates the inventory window for the player, item description, and floor's inventory.
*/
bool MakeInventoryMenu() {
    int invX1 = 2; // begins at X
    int invX2 = 65; 
    int invY1 = 1; // begins at Y
    int invY2 = 25;

    
    WINDOW *menu = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, invY1, invX1);
    WINDOW *desc = newwin((WINDOW_HEIGHT / 2), WINDOW_WIDTH, invY1, invX2);
    WINDOW *loot = newwin((WINDOW_HEIGHT / 2), WINDOW_WIDTH, invY2, invX2);
    keypad(menu, TRUE);
    keypad(desc, FALSE);
    keypad(loot, FALSE); // Changed to TRUE when we swap to it with transfer

    return(MoveInventoryCursor(menu, desc, loot));
}

/*
Renders the 3 passed windows, then lets player 
move between the items in their inventory.
Once an item has been pressed for selection, opens a subwindow to select what to do.
TODO: add ability to scroll in this window.
*/
bool MoveInventoryCursor (WINDOW *menu, WINDOW *desc, WINDOW *loot){
    // Create an array of pointers for us to look at the players inventory.
    Item* playerInv[INVENTORY_SIZE];
    for(int i = 0; i < INVENTORY_SIZE; i++) {
        playerInv[i] = &player->inventory[i];
    }
    int n_options = player->invTail;
    bool escFlag = false;
    bool moveTail = false;
    int cursor = 0;
    int choice = -1;
    int ch;
    /* First Render of Menu*/
    RenderInventoryMenu(menu, desc, loot, cursor, n_options, playerInv);
    while(!escFlag) {
        n_options = player->invTail;
        ch = wgetch(menu);
        escFlag = CheckEscape(ch);
        switch(ch) {
            case KEY_UP:
                if (cursor == 0) cursor = n_options - 1;
                else cursor--; 
                break;
            case KEY_DOWN: 
                if (cursor == n_options - 1) cursor = 0;
                else cursor++;
                break;
            case KEY_RIGHT: 
                if (is_keypad(menu) == TRUE && map[player->pos.y][player->pos.x].inventory[0].itemID != NULL_ITEM_ID){
                    keypad(menu, FALSE);
                    keypad(loot, TRUE);
                    moveTail = MoveLootCursor(menu, desc, loot, playerInv);
                    n_options = player->invTail;
                    if(moveTail) {
                        cursor = n_options - 1;
                    }
                    keypad(menu, TRUE);
                    keypad(loot, FALSE);
                }
                break;
            case 32: // SPB
                choice = cursor;
                moveTail = MakeItemOptionsWindow(playerInv, choice, n_options, menu, loot);
                n_options = player->invTail;
                if(moveTail) {
                    if (cursor == n_options && cursor != 0){
                        cursor--;
                    }
                    moveTail = false;
                }
                escFlag = moveTail;
                break;
            case 10: // ENTER
                choice = cursor;
                moveTail = MakeItemOptionsWindow(playerInv, choice, n_options, menu, loot);
                n_options = player->invTail;
                if(moveTail) {
                    if (cursor == n_options && cursor != 0){
                        cursor--;
                    }
                    moveTail = false;
                }
                escFlag = moveTail;
                break;
            default:
                break;
        }
        RenderInventoryMenu(menu, desc, loot, cursor, n_options, playerInv);
    }
    return false;
}


void RenderInventoryMenu(WINDOW *menu, WINDOW *desc, WINDOW *loot, int cursor, int n_options, Item** playerInv) {
    int y = 3; // Items starting pos within window.

    wclear(desc);
    wclear(menu);
    wclear(loot);

    PrintInventoryHeaders(menu, desc, loot);
    
    for (int i = 0; i < player->invTail; i++) {

        if(playerInv[i]->itemID == player->equippedMelee.item.itemID || playerInv[i]->itemID == player->equippedRanged.item.itemID || playerInv[i]->itemID == player->equippedArmor.item.itemID || playerInv[i]->itemID == player->equippedAmmo.item.itemID) {
            wattron(menu, A_DIM);
            mvwprintw(menu, y, (strlen(playerInv[i]->itemName) + 5), " (Equipped)");
            wattroff(menu, A_DIM);
            mvwprintw(menu, y, (strlen(playerInv[i]->itemName) + 3), "x%d", playerInv[i]->quantity);
        }
        if (cursor == i) {
            wattron(menu, A_REVERSE);
            mvwprintw(menu, y, 2, "%s", playerInv[i]->itemName);
            mvwprintw(desc, 2, 2, "%s", playerInv[cursor]->itemDesc);
            mvwprintw(loot, y, 2, "%s", map[player->pos.y][player->pos.x].inventory[i].itemName);
            RenderItemInfo(desc, playerInv[cursor]);
            wattroff(menu, A_REVERSE);
            mvwprintw(menu, y, (strlen(playerInv[i]->itemName) + 3), "x%d", playerInv[i]->quantity); 
        }
        else {
            mvwprintw(menu, y, 2, "%s", playerInv[i]->itemName);
            mvwprintw(menu, y, (strlen(playerInv[i]->itemName) + 3), "x%d", playerInv[i]->quantity);
            // mvwprintw(desc, y, 2, "%s\n", playerInv[cursor]->itemDesc);
        }
    y++;
    }

    y = 3;
    for (int i = 0; i < map[player->pos.y][player->pos.x].invTail; i++) {
            mvwprintw(loot, y, 2, "%s", map[player->pos.y][player->pos.x].inventory[i].itemName);
            mvwprintw(loot, y, (strlen(map[player->pos.y][player->pos.x].inventory[i].itemName) + 3), "x%d", map[player->pos.y][player->pos.x].inventory[i].quantity);
            y++;
        }
    wrefresh(loot);
    wrefresh(desc);
    wrefresh(menu);
}


bool MakeItemOptionsWindow(Item** playerInv, int choice, int n_options, WINDOW *menu, WINDOW *loot) {
    bool unEquipMenu = false;
    if (playerInv[choice]->itemID == player->equippedMelee.item.itemID || playerInv[choice]->itemID == player->equippedRanged.item.itemID || playerInv[choice]->itemID == player->equippedArmor.item.itemID || playerInv[choice]->itemID == player->equippedAmmo.item.itemID) {
        unEquipMenu = true;
    }
    char *options1[] = {
    "Drop",
    "Drop All",
    "Equip",
    "Examine",
    "Exit",
    };
    char *options2[] = {
    "Drop",
    "Drop All",
    "Unequip",
    "Examine",
    "Exit",
    };

    //Sorry about the magic numbers
    int m_options = sizeof(options1) / sizeof(char*);
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
        RenderInvOptionMenu(invOp, cursor, m_options, options2);
    }
    else {
        RenderInvOptionMenu(invOp, cursor, m_options, options1);
    }

    while(!escFlag) {
        ch = wgetch(invOp);
        escFlag = CheckEscape(ch);
        switch(ch) {
            case KEY_UP:
                if (cursor == 0) {
                    cursor = m_options - 1;
                }
                else {
                    cursor--;
                }
                break;
            case KEY_DOWN: 
                if (cursor == m_options - 1) {
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
            RenderInvOptionMenu(invOp, cursor, m_options, options2);
        }
        else {
            RenderInvOptionMenu(invOp, cursor, m_options, options1);
        }
    }
    return InvOptionSelect(playerInv, choice, n_options, newChoice, menu, invOp, loot, unEquipMenu);
}

/* Tiny window for selecting Equip, Drop, transfer, etc. */
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

/* Selects an option from the tiny one above and acts based on the chosen selection. */
/* Returns true if the player drops their last item.*/
bool InvOptionSelect(Item** playerInv, int prevChoice, int n_options, int newChoice, WINDOW* menu, WINDOW* invOp, WINDOW* loot, bool unEquipMenu) {
    switch(newChoice){
        case 0: // Drop
            if(playerInv[prevChoice]->quantity == 1 && playerInv[prevChoice]->unequippable) {
                Unequip(*playerInv[prevChoice]);
                RemoveFromPlayerInventory(*playerInv[prevChoice], 1);
            }
            DrawEverything();
            refresh();
            delwin(invOp);
            return true;
            break;
        case 1: // Drop All
            if(playerInv[prevChoice]->unequippable) {
                Unequip(*playerInv[prevChoice]);
                RemoveFromPlayerInventory(*playerInv[prevChoice], playerInv[prevChoice]->quantity);
            }
            DrawEverything();
            refresh();
            delwin(invOp);
            return true;
            break;
        case 2: // Equip
            EquipOrUnequip(playerInv, unEquipMenu, prevChoice);
            DrawEverything();
            refresh();
            wrefresh(loot);
            delwin(invOp);
            return false;
            break;
        case 3: // Examine
            // Do the load window here
            refresh();
            delwin(invOp);
            return false;
            break;
        case 4: // Exit
            // Do the load window here
            refresh();
            delwin(invOp);
            return false;
            break;

        default:
            refresh();
            delwin(invOp);
            return false;
            break;
    }
}

/* 
Renders the item info passed in from item into the window desc.
*/
void RenderItemInfo(WINDOW* desc, Item* item) {
    switch (item->type) {
        case WEAPON:
            Weapon weapon;
            weapon = GetWeaponFromItem(item->itemID);
            mvwprintw(desc, 3, 2, "DMG: %d - %d", weapon.minDMG, weapon.maxDMG);
            mvwprintw(desc, 4, 2, "Range: %d", weapon.range);
            mvwprintw(desc, 5, 2, "Value: %d", weapon.item.value);
            break;
        case AMMO:
            Ammo ammo;
            ammo = GetAmmoFromItem(item->itemID);
            // char* ammoType = GetArmorType(ammo.type);
            // mvwprintw(desc, 4, 2, "Type: %s", ammoType);
            mvwprintw(desc, 3, 2, "Value: %d", ammo.item.value);
            break;
        case ARMOR:
            Armor armor;
            armor = GetArmorFromItem(item->itemID);
            mvwprintw(desc, 3, 2, "AC: %d", armor.AC);
            char* armorType = GetArmorType(armor.type);
            mvwprintw(desc, 4, 2, "Type: %s", armorType);
            mvwprintw(desc, 5, 2, "Value: %d", armor.item.value);
            break;
        default:
            break;
    }
}

void EquipOrUnequip (Item** playerInv, bool unEquipMenu, int prevChoice) {
    if(unEquipMenu){
        if(playerInv[prevChoice]->unequippable)Unequip(*playerInv[prevChoice]);
        else{
            strcpy(combatHistory->event, "You cannot unequip that.");
            QueueEvent(q, combatHistory->event);
            DrawCombatLog();
        }
    } 
    else {
        if(playerInv[prevChoice]->equippable)Equip(*playerInv[prevChoice]);
        else{
            strcpy(combatHistory->event, "You cannot equip that.");
            QueueEvent(q, combatHistory->event);
            DrawCombatLog();
        }
    }
}

/* Makes and prints the inventory menus headers*/
void PrintInventoryHeaders(WINDOW* menu, WINDOW* desc, WINDOW* loot) {
    int titleRight = (WINDOW_WIDTH - OFFSET) / 2 + OFFSET;
    int center = ((WINDOW_WIDTH - OFFSET) / 2) + 3;
    int numLines = WINDOW_WIDTH - 2 - titleRight;
    int top = 1;
    /* Update players info in real time. */
    box(menu, 0, 0);
    mvwprintw(menu, top, center - 3, " INVENTORY ");
    mvwhline(menu, top, top, ACS_HLINE, numLines );
    mvwhline(menu, top, titleRight, ACS_HLINE, numLines + 1);

    box(desc, 0, 0);
    mvwprintw(desc, top, center - 3, " DESCRIPTION ");
    mvwhline(desc, top, top, ACS_HLINE, numLines);
    mvwhline(desc, top, titleRight + 2, ACS_HLINE, numLines - 1);

    box(loot, 0, 0);
    mvwprintw(loot, top, center - 3, map[player->pos.y][player->pos.x].entityName);
    mvwhline(loot, top + 1, top, ACS_HLINE, (WINDOW_WIDTH) - 2);
}
