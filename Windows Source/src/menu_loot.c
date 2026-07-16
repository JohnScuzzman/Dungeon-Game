#include <rogue.h>
#define INVENTORY_SIZE 65
#define WINDOW_WIDTH 61
#define WINDOW_HEIGHT 47
#define OFFSET 11


/*
Should only return true if the loot menu is empty.
*/
bool MoveLootCursor(WINDOW* menu, WINDOW* desc,WINDOW* loot, Item** playerInv) {
    Item* entityInv[INVENTORY_SIZE];
    for(int i = 0; i < INVENTORY_SIZE; i++) {
        entityInv[i] = &map[player->pos.y][player->pos.x].inventory[i];
    }
    int n_options = map[player->pos.y][player->pos.x].invTail;
    bool escFlag = false;
    bool moveTail = false;
    int cursor = 0;
    int choice = -1;
    int ch;

    RenderLootMenu(menu, desc, loot, cursor, n_options, entityInv, playerInv);
    while(!escFlag) {
        ch = wgetch(loot);
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
            case KEY_LEFT: 
                refresh();
                return false;
            case 32: // SPB
                choice = cursor;
                moveTail = MakeLootOptionsWindow(playerInv, entityInv, choice, n_options, menu, loot);
                n_options = map[player->pos.y][player->pos.x].invTail;
                if (cursor == n_options && cursor != 0){
                    cursor--;
                }
                escFlag = moveTail;
                break;
            case 10: // ENTER
                choice = cursor;
                moveTail = MakeLootOptionsWindow(playerInv, entityInv, choice, n_options, menu, loot);
                n_options = map[player->pos.y][player->pos.x].invTail;
                if (cursor == n_options && cursor != 0){
                    cursor--;
                }
                escFlag = moveTail;
                break;
            default:
                break;
            }
        RenderLootMenu(menu, desc, loot, cursor, n_options, entityInv, playerInv);
    }
    return true;
}

void RenderLootMenu(WINDOW *menu, WINDOW *desc, WINDOW *loot, int cursor, int n_options, Item** entityInv, Item** playerInv) {
    int y = 3; // Items starting pos within window.

    wclear(desc);
    wclear(menu);
    wclear(loot);

    PrintInventoryHeaders(menu, desc, loot);
    
    for (int i = 0; i < player->invTail; i++){
        if(playerInv[i]->itemID == player->equippedMelee.item.itemID ||
             playerInv[i]->itemID == player->equippedRanged.item.itemID ||
              playerInv[i]->itemID == player->equippedArmor.item.itemID ||
               playerInv[i]->itemID == player->equippedAmmo.item.itemID) {
            wattron(menu, A_DIM);
            mvwprintw(menu, y, (strlen(playerInv[i]->itemName) + GetNumberOfDigits(playerInv[i]->quantity) + 4), " (Equipped)");
            wattroff(menu, A_DIM);
            mvwprintw(menu, y, 2, "%s", playerInv[i]->itemName);
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
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (entityInv[i]->itemID != NULL_ITEM_ID) {
            if (cursor == i) {
                wattron(loot, COLOR_PAIR(HIGHLIGHT_COLOR));
                mvwprintw(desc, 2, 2, "%s", entityInv[cursor]->itemDesc);
                mvwprintw(loot, y, 2, "%s", entityInv[i]->itemName);
                RenderItemInfo(desc, entityInv[cursor]);
                wattroff(loot, COLOR_PAIR(HIGHLIGHT_COLOR));
                wattron(loot, COLOR_PAIR(HIGHLIGHT_OFF));
                mvwprintw(loot, y, (strlen(entityInv[i]->itemName) + 3), "x%d", entityInv[i]->quantity);
            }
            else {
                mvwprintw(loot, y, 2, "%s", entityInv[i]->itemName);
                mvwprintw(loot, y, (strlen(entityInv[i]->itemName) + 3), "x%d", entityInv[i]->quantity);
                // mvwprintw(desc, y, 2, "%s\n", playerInv[cursor]->itemDesc);
            }
        }
    y++;
    wrefresh(loot);
    wrefresh(desc);
    wrefresh(menu);
    }
}

bool MakeLootOptionsWindow(Item** playerInv, Item** entityInv, int choice, int n_options, WINDOW *menu, WINDOW *loot) {

    char *options[] = {
        "Take",
        "Take All",
        "Equip",
        "Examine",
        "Exit",
    };

    //Sorry about the magic numbers
    int m_options = sizeof(options) / sizeof(char*);
    int invX = (WINDOW_WIDTH + OFFSET * 2) + strlen(entityInv[choice]->itemName);
    int invY = choice + 5;
    bool escFlag = false;
    int cursor = 0;
    int newChoice = -1;
    int ch;
    
    // Make a tiny window with 5 options for player to choose from.
    WINDOW *lootOp = newwin(((WINDOW_HEIGHT / 4) - 4), (WINDOW_WIDTH / 4), invY, invX);
    keypad(lootOp, TRUE);

    // Borrows function fomr menu_inventory.c
    RenderLootOptionMenu(lootOp, cursor, m_options, options);

    while(!escFlag) {
        ch = wgetch(lootOp);
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
        RenderLootOptionMenu(lootOp, cursor, m_options, options);
    }
    return LootOptionSelect(playerInv, entityInv, choice, n_options, newChoice, menu, lootOp, loot);
}

/* Tiny window for selecting Equip, Drop, transfer, etc. */
void RenderLootOptionMenu(WINDOW *lootOp, int cursor, int n_options, char** options) {
    int y = 1;
    int titleRight = (WINDOW_WIDTH - OFFSET) / 2 + OFFSET;
    int center = (WINDOW_WIDTH / 2) - (OFFSET * 3) + 5;
    int numLines = WINDOW_WIDTH - 2 - titleRight;
    int top = 1;
    int centerY, centerX;
    getmaxyx(lootOp, centerY, centerX);
    box(lootOp, 0, 0);

    for (int i = 0; i < n_options; i++) {
        center = (centerX - strlen(options[i])) / 2;
        if (cursor == i) {
            wattron(lootOp, COLOR_PAIR(HIGHLIGHT_COLOR));
            mvwprintw(lootOp, y, center, "%s", options[i]);
            wattroff(lootOp, COLOR_PAIR(HIGHLIGHT_COLOR));
            wattron(lootOp, COLOR_PAIR(HIGHLIGHT_OFF));
        }
        else {
            mvwprintw(lootOp, y, center, "%s", options[i]);
        }
        y++;
    }
    wrefresh(lootOp);
}

/* Selects an option from the tiny one above and acts based on the chosen selection. */
bool LootOptionSelect(Item** playerInv, Item** entityInv, int prevChoice, int n_options, int newChoice, WINDOW* menu, WINDOW* lootOp, WINDOW* loot) {
    switch(newChoice){
        case 0: // Take
            AddToPlayerInventory(*entityInv[prevChoice], 1);
            RemoveFromNPCInventory(&map[player->pos.y][player->pos.x], *entityInv[prevChoice], 1);
            DrawPlayerEquipment();
            // DrawEverything();
            refresh();
            wrefresh(loot);
            delwin(lootOp);
            if (entityInv[0]->itemID == NULL_ITEM_ID) return true; // if empty floor/npc inv, return to players
            else return false;
        case 1: // Take All
            //while entity Quantity of item > 0
            AddToPlayerInventory(*entityInv[prevChoice], entityInv[prevChoice]->quantity);
            RemoveFromNPCInventory(&map[player->pos.y][player->pos.x], *entityInv[prevChoice], entityInv[prevChoice]->quantity);
            DrawPlayerEquipment();
            // DrawEverything();
            refresh();
            wrefresh(loot);
            delwin(lootOp);
            if (entityInv[0]->itemID == NULL_ITEM_ID) return true;
            else return false;
        case 2: // Equip
            AddToPlayerInventory(*entityInv[prevChoice], 1);
            Equip(*entityInv[prevChoice]);
            RemoveFromNPCInventory(&map[player->pos.y][player->pos.x], *entityInv[prevChoice], 1);
            DrawPlayerEquipment();
            // DrawEverything();
            refresh();
            wrefresh(loot);
            delwin(lootOp);
            if (entityInv[0]->itemID == NULL_ITEM_ID) return true;
            else return false;
        case 3: // Examine
            // Ascii art of the item or something here.
            refresh();
            delwin(lootOp);
            if (entityInv[0]->itemID == NULL_ITEM_ID) return true;
            else return false;
            break;
        case 4: // Exit
            // leave.
            refresh();
            delwin(lootOp);
            return false;
            break;

        default:
            break;
    }
}
