#include <rogue.h>
#define WINDOW_WIDTH 61
#define WINDOW_HEIGHT 47
#define OFFSET 11
#define INVENTORY_SIZE 64


/* Creates a pause window and returns true if player quits */
/* Processes a new window and does a task if false. */
bool MakeInventoryMenu(Item* items) {
    
    Item* playerInv[INVENTORY_SIZE];
    for(int i = 0; i < INVENTORY_SIZE; i++) {
        playerInv[i] = &player->inventory[i];
    }
    int n_options = player->invTail;
    int invX1 = 2; // begins at X
    int invX2 = 64; 
    int invY1 = 1; // begins at Y
    int invY2 = 25;
    bool escFlag = false;
    bool quitMenu = false;
    int cursor = 0;
    int choice = -1;
    int ch;
    
    WINDOW *menu = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, invY1, invX1);
    WINDOW *desc = newwin((WINDOW_HEIGHT / 2), WINDOW_WIDTH, invY1, invX2);
    WINDOW *loot = newwin((WINDOW_HEIGHT / 2), WINDOW_WIDTH, invY2, invX2);
    keypad(menu, TRUE);
    keypad(desc, FALSE);
    keypad(loot, FALSE); // Changed to TRUE when we swap to it with transfer
   
    /* First Render of Menu*/
    RenderInventoryMenu(menu, desc, loot, cursor, n_options, playerInv);

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
                escFlag = MakeItemOptionsWindow(playerInv, choice, menu, loot);
                break;
            case 10: // ENTER
                choice = cursor;
                escFlag = MakeItemOptionsWindow(playerInv, choice, menu, loot);
                break;
            default:
                break;
            }
        wclear(desc);
        RenderInventoryMenu(menu, desc, loot, cursor, n_options, playerInv);
        }
        quitMenu = InventorySelect(choice, menu);
        return quitMenu;
    }

void RenderInventoryMenu(WINDOW *menu, WINDOW *desc, WINDOW *loot, int cursor, int n_options, Item** playerInv) {
    int y = 3;
    int titleRight = (WINDOW_WIDTH - OFFSET) / 2 + OFFSET;
    int center = ((WINDOW_WIDTH - OFFSET) / 2) + 3;
    int numLines = WINDOW_WIDTH - 2 - titleRight;
    int top = 1;
    /* Update players info in real time. */
    wclear(menu);
    wclear(loot);

    box(menu, 0, 0);
    mvwprintw(menu, top, center - 3, " INVENTORY ");
    mvwhline(menu, top, top, ACS_HLINE, numLines );
    mvwhline(menu, top, titleRight, ACS_HLINE, numLines + 1);

    box(desc, 0, 0);
    mvwprintw(desc, top, center - 3, " DESCRIPTION ");
    mvwhline(desc, top, top, ACS_HLINE, numLines);
    mvwhline(desc, top, titleRight + 2, ACS_HLINE, numLines - 1);

    box(loot, 0, 0);
    mvwprintw(loot, top, center - 3, "%s", map[player->pos.y][player->pos.x].entityName.c_str());
    mvwhline(loot, top + 1, top, ACS_HLINE, (WINDOW_WIDTH) - 2);
    
    for (int i = 0; i < player->invTail; i++) {

        if(playerInv[i]->itemID == player->equippedMelee.item.itemID || playerInv[i]->itemID == player->equippedRanged.item.itemID || playerInv[i]->itemID == player->equippedArmor.item.itemID) {
            wattron(menu, A_DIM);
            mvwprintw(menu, y, (playerInv[i]->itemName.length() + 2), " (Equipped)");
            wattroff(menu, A_DIM);
        }
        mvwprintw(loot, y, 2, "%s", map[player->pos.y][player->pos.x].inventory[i].itemName.c_str());
        if (cursor == i) {
            wattron(menu, A_REVERSE);
            mvwprintw(menu, y, 2, "%s", playerInv[i]->itemName.c_str());
            mvwprintw(desc, 2, 2, "%s", playerInv[cursor]->itemDesc.c_str());
            mvwprintw(loot, y, 2, "%s", map[player->pos.y][player->pos.x].inventory[i].itemName.c_str());
            switch (playerInv[cursor]->type) {
                case WEAPON:
                {
                    Weapon weapon;
                    weapon = GetWeaponFromItem(playerInv[cursor]->itemID);
                    mvwprintw(desc, 3, 2, "DMG: %d - %d", weapon.minDMG, weapon.maxDMG);
                    mvwprintw(desc, 4, 2, "Range: %d", weapon.range);
                    mvwprintw(desc, 5, 2, "Value: %d", weapon.item.value);
                    break;
                }
                case ARMOR:
                {
                    Armor armor;
                    armor = GetArmorFromItem(playerInv[cursor]->itemID);
                    mvwprintw(desc, 3, 2, "AC: %d", armor.AC);
                    const char* armorType = GetArmorType(armor.type);
                    mvwprintw(desc, 4, 2, "Type: %s", armorType);
                    mvwprintw(desc, 5, 2, "Value: %d", armor.item.value);
                    break;
                }
                default:
                    break;
            }
            wattroff(menu, A_REVERSE);
        }
        else {
            mvwprintw(menu, y, 2, "%s", playerInv[i]->itemName.c_str());
            // mvwprintw(desc, y, 2, "%s\n", playerInv[cursor]->itemDesc.c_str());
        }
    y++;
    wrefresh(loot);
    wrefresh(desc);
    wrefresh(menu);
    }
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
            refresh();
            delwin(menu);
            return false;
            break;

        case 2: // Item 3
            refresh();
            delwin(menu);
            return false;
            break;

        case 3: // Item 4
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

bool MakeItemOptionsWindow(Item** playerInv, int choice, WINDOW *menu, WINDOW *loot) {
    bool unEquipMenu = false;
    if (playerInv[choice]->itemID == player->equippedMelee.item.itemID || playerInv[choice]->itemID == player->equippedRanged.item.itemID || playerInv[choice]->itemID == player->equippedArmor.item.itemID) {
        unEquipMenu = true;
    }
    const char *options1[] = {
    "Equip",
    "Transfer",
    "Drop",
    "Examine",
    "Exit",
    };
    const char *options2[] = {
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
    return InvOptionSelect(playerInv, choice, newChoice, menu, invOp, loot, unEquipMenu);
}

/* Tiny window for selecting Equip, Drop, transfer, etc. */
void RenderInvOptionMenu(WINDOW *invOp, int cursor, int n_options, const char** options) {
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
bool InvOptionSelect(Item** playerInv, int prevChoice, int newChoice, WINDOW* menu, WINDOW* invOp, WINDOW* loot, bool unEquipMenu) {
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
            wrefresh(loot);
            delwin(invOp);
            return false;
            break;

        case 1: // Transfer
            keypad(menu, FALSE);
            keypad(loot, TRUE);
            // LootMenu(loot, 0, -1, playerInv);
            refresh();
            delwin(invOp);
            return false;
            break;

        case 2: // Drop
            Unequip(*playerInv[prevChoice]);
            RemoveFromPlayerInventory(*playerInv[prevChoice]);
            DrawEverything();
            refresh();
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

// void RenderLootMenu(WINDOW *loot, int cursor, int n_options, Item** playerInv) {
//     int y = 3;
//     int titleRight = (WINDOW_WIDTH - OFFSET) / 2 + OFFSET;
//     int center = ((WINDOW_WIDTH - OFFSET) / 2) + 3;
//     int numLines = WINDOW_WIDTH - 2 - titleRight;
//     int top = 1;
//     /* Update players info in real time. */

//     box(loot, 0, 0);
//     mvwprintw(loot, top, center - 3, map[player->pos.y][player->pos.x].entityName);
//     mvwhline(loot, top + 1, top, ACS_HLINE, (WINDOW_WIDTH) - 2);
    
//     for (int i = 0; i < map[player->pos.y][player->pos.x].invTail; i++) {
//         if (cursor == i) {
//             wattron(loot, A_REVERSE);
//             mvwprintw(loot, y, 2, "%s", map[player->pos.y][player->pos.x].inventory[i].itemName);
//             switch (map[player->pos.y][player->pos.x].inventory[i].type) {
//                 case WEAPON:
//                     Weapon weapon;
//                     weapon = GetWeaponFromItem(map[player->pos.y][player->pos.x].inventory[i].itemID);
//                     mvwprintw(loot, 3, 2, "DMG: %d - %d", weapon.minDMG, weapon.maxDMG);
//                     mvwprintw(loot, 4, 2, "Range: %d", weapon.range);
//                     mvwprintw(loot, 5, 2, "Value: %d", weapon.item.value);
//                     break;
//                 case ARMOR:
//                     Armor armor;
//                     armor = GetArmorFromItem(map[player->pos.y][player->pos.x].inventory[i].itemID);
//                     mvwprintw(loot, 3, 2, "AC: %d", armor.AC);
//                     char* armorType = GetArmorType(armor.type);
//                     mvwprintw(loot, 4, 2, "Type: %s", armorType);
//                     mvwprintw(loot, 5, 2, "Value: %d", armor.item.value);
//                     break;
//                 default:
//                     break;
//             }
//             wattroff(loot, A_REVERSE);
//         }
//         else {
//             mvwprintw(loot, y, 2, "%s", map[player->pos.y][player->pos.x].inventory[i].itemName);
//         }
//     y++;
//     wrefresh(loot);
//     }
// }

// bool LootMenu(WINDOW *loot, int cursor, int n_options, Item** entityInv) {
//     bool escFlag = false;
//     int lootChoice = -1;
//     int ch;
//     RenderLootMenu(loot, cursor, n_options, entityInv);
//     while(!escFlag) {
//         ch = wgetch(loot);
//         escFlag = CheckEscape(ch);
//         switch(ch) {
//             case KEY_UP:
//                 if (cursor == 0) {
//                     cursor = n_options - 1;
//                 }
//                 else {
//                     cursor--;
//                 }
//                 break;
//             case KEY_DOWN: 
//                 if (cursor == n_options - 1) {
//                     cursor = 0;
//                 }
//                 else {
//                     cursor++;
//                 }
//                 break;
//             case 32: // SPB
//                 lootChoice = cursor;
//                 escFlag = true;
//                 break;
//             case 10: // ENTER
//                 lootChoice = cursor;
//                 escFlag = true;
//                 break;
//             default:
//                 break;
//         }
//     RenderLootMenu(loot, cursor, n_options, entityInv);
//     }
//     return (LootChoice(loot, lootChoice));
// }

// bool LootChoice(WINDOW* loot, int lootChoice) {
//     switch(lootChoice){ 
//         case 0: // Equip / Unequip
//         refresh();
//         delwin(loot);
//         return false;
//         break;

//     case 1: // Transfer
//         refresh();
//         delwin(loot);
//         return false;
//         break;

//     case 2: // Drop
//         refresh();
//         delwin(loot);
//         return false;
//         break;

//     case 3: // Examine
//         refresh();
//         delwin(loot);
//         return false;
//         break;
//     case 4:
//         refresh();
//         delwin(loot);
//         return false;
//         break;

//     default:
//         refresh();
//         delwin(loot);
//         return false;
//         break;
//     }
//     return true;
// }
