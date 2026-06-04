#include <rogue.h>

const int ALL_ITEMS = 256;
const int INVENTORY_SIZE = 64;

// Parent Class Item goes at the top of Armor, Weapon, etc structs to make it a child struct.
// Weapon newItem = ShortSword();
// reference the items variables with Item* itemPtr = (Item *)&newItem
// Even though newItem is a weapon, we can still look at its item info using pointer upcasting.
/* Refer to the enum Items in items.h */
/* WIP */
Item* CreatePlayerInv() {
    Item* playerInv = calloc(INVENTORY_SIZE, sizeof(Item));
    for (int i = 0; i < INVENTORY_SIZE; i++){
        playerInv[i].equippable = false;
        playerInv[i].lootable = false;
        playerInv[i].unequippable = true;
        playerInv[i].itemID = 0;
        playerInv[i].type = NULL_ITEM;
        strcpy(playerInv[i].itemName, " ");
    }
    return playerInv;
}

void CreateMonsterInv(Entity* monster) {
    for (int i = 0; i < INVENTORY_SIZE; i++){
        monster->inventory[i].equippable = false;
        monster->inventory[i].lootable = false;
        monster->inventory[i].unequippable = true;
        monster->inventory[i].itemID = NULL_ITEM_ID;
        monster->inventory[i].type = NULL_ITEM;
        strcpy(monster->inventory[i].itemName, " ");

    }
}

/* Weapons begin at 'FIST', Armor Begins at 'ROBES'*/
Item* CreateItemTable() {
    Item* items = calloc(ALL_ITEMS, sizeof(Item));
    // Innate biological weapons
    for (int i = FISTS; i < DAGGER; i++){
        items[i].equippable = true;
        items[i].lootable = false;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = WEAPON;
        strcpy(items[i].itemName, " ");
    }
    // Weapons
    for (int i = DAGGER; i < ROBES; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = WEAPON;
        strcpy(items[i].itemName, " ");
    }
    // Armor
    for  (int i = ROBES; i < METALLIC_SKIN; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = ARMOR;
        strcpy(items[i].itemName, " ");
    }
    // Cybernetics
    for  (int i = METALLIC_SKIN; i <= METALLIC_SKIN; i++){
        items[i].equippable = false;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = ARMOR;
        strcpy(items[i].itemName, " ");
        // TODO items[i].subtype = CYBERNETICS;
    }
    return items;
}

void AddToNPCInventory(Entity* npc, Item newItem) {
    if(npc->invTail == (INVENTORY_SIZE - 1)) {
        return;
    }
    npc->inventory[npc->invTail] = newItem;
    npc->invTail++;
}

void RemoveFromNPCInventory(Entity* npc) {
    if(npc->invTail == 0) {
        return;
    }
    npc->inventory[npc->invTail] = items[NULL_ITEM_ID];
    npc->invTail--;
}

void AddToPlayerInventory(Item* newItem) {
    if(player->invTail == (INVENTORY_SIZE - 1)) {
        return;
    }
    playerInv[player->invTail] = *newItem;
    player->invTail++;
}

void RemoveFromPlayerInventory() {
    if(player->invTail == 0) {
        return;
    }
    playerInv[player->invTail] = items[NULL_ITEM_ID];
    player->invTail--;
}

void NullItem(Item* item) {
    item->equippable = true;
    item->lootable = false;
    item->unequippable = true;
    item->itemID = NULL_ITEM_ID;
    item->type = NULL_ITEM;
    strcpy(item->itemName, " ");
}