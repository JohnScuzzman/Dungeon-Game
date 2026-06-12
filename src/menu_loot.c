#include <rogue.h>
#define INVENTORY_SIZE 64
#define WINDOW_WIDTH 61
#define WINDOW_HEIGHT 47
#define OFFSET 11

bool MoveLootCursor(WINDOW* menu, WINDOW* desc,WINDOW* loot, Item** playerInv) {
    Item* entityInv[INVENTORY_SIZE];
    for(int i = 0; i < INVENTORY_SIZE; i++) {
        entityInv[i] = &map[player->pos.y][player->pos.x].inventory[i];
    }
    int n_options = map[player->pos.y][player->pos.x].invTail;
    bool escFlag = false;
    bool quitMenu = false;
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
                escFlag = MakeLootOptionsWindow(playerInv, entityInv, choice, n_options, menu, loot);
                if(entityInv[0] == NULL_ITEM_ID) return false;
                break;
            case 10: // ENTER
                choice = cursor;
                escFlag = MakeLootOptionsWindow(playerInv, entityInv, choice, n_options, menu, loot);
                if(entityInv[0] == NULL_ITEM_ID) return false;
                break;
            default:
                break;
            }
        RenderLootMenu(menu, desc, loot, cursor, n_options, entityInv, playerInv);
    }
    return false;
}

void RenderLootMenu(WINDOW *menu, WINDOW *desc, WINDOW *loot, int cursor, int n_options, Item** entityInv, Item** playerInv) {
    int y = 3; // Items starting pos within window.

    wclear(desc);
    wclear(menu);
    wclear(loot);

    PrintInventoryHeaders(menu, desc, loot);
    
    for (int i = 0; i < player->invTail; i++){
        if(playerInv[i]->itemID == player->equippedMelee.item.itemID || playerInv[i]->itemID == player->equippedRanged.item.itemID || playerInv[i]->itemID == player->equippedArmor.item.itemID) {
            mvwprintw(menu, y, 2, "%s", playerInv[i]->itemName);
            wattron(menu, A_DIM);
            mvwprintw(menu, y, (strlen(playerInv[i]->itemName) + 2), " (Equipped)");
            wattroff(menu, A_DIM);
        }
        else mvwprintw(menu, y, 2, "%s", playerInv[i]->itemName);
        y++;
    }
    y = 3;

    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (entityInv[i]->itemID != NULL_ITEM_ID) {
            if (cursor == i) {
                wattron(loot, A_REVERSE);
                mvwprintw(desc, 2, 2, "%s", entityInv[cursor]->itemDesc);
                mvwprintw(loot, y, 2, "%s", entityInv[i]->itemName);
                RenderItemInfo(desc, entityInv[cursor]);
                wattroff(loot, A_REVERSE);
            }
            else {
                mvwprintw(loot, y, 2, "%s", entityInv[i]->itemName);
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
    int invY = (WINDOW_HEIGHT / 2) + choice + 5;
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
            wattron(lootOp, A_REVERSE);
            mvwprintw(lootOp, y, center, "%s", options[i]);
            wattroff(lootOp, A_REVERSE);
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
            AddToPlayerInventory(*entityInv[prevChoice]);
            RemoveFromNPCInventory(&map[player->pos.y][player->pos.x], *entityInv[prevChoice]);
            DrawEverything();
            refresh();
            wrefresh(loot);
            delwin(lootOp);
            if (entityInv[0]->itemID == NULL_ITEM_ID) return true; // if empty floor/npc inv, return to players
            else return false;
            return false;
        case 1: // Take All
            //while entity Quantity of item > 0
            AddToPlayerInventory(*entityInv[prevChoice]);
            RemoveFromNPCInventory(&map[player->pos.y][player->pos.x], *entityInv[prevChoice]);
            DrawEverything();
            refresh();
            wrefresh(loot);
            delwin(lootOp);
            if (entityInv[0]->itemID == NULL_ITEM_ID) return true;
            else return false;
        case 2: // Equip
            AddToPlayerInventory(*entityInv[prevChoice]);
            Equip(*entityInv[prevChoice]);
            RemoveFromNPCInventory(&map[player->pos.y][player->pos.x], *entityInv[prevChoice]);
            DrawEverything();
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
            return true;
            break;

        default:
            break;
    }
}
