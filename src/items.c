#include <rogue.h>


// Parent Class Item goes at the top of Armor, Weapon, etc structs to make it a child struct.
// Weapon newItem = ShortSword();
// reference the items variables with Item* itemPtr = (Item *)&newItem
// Even though newItem is a weapon, we can still look at its item info using pointer upcasting.
#define INVENTORY_SIZE 64
#define ALL_ITEMS 256
/* Refer to the enum Items in items.h */
/* WIP */
Item* CreatePlayerInv() {
    Item* inv = calloc(INVENTORY_SIZE, sizeof(Item));
    for (int i = 0; i < INVENTORY_SIZE; i++){
        items[i].equippable = false;
        items[i].lootable = false;
        items[i].itemID = 0;
        items[i].type = NULL_ITEM;
    }
    return inv;
}

void CreateMonsterInv(Entity* monster) {
    for (int i = 0; i < INVENTORY_SIZE; i++){
        monster->inventory[i].equippable = false;
        monster->inventory[i].lootable = false;
        monster->inventory[i].itemID = 0;
        monster->inventory[i].type = NULL_ITEM;
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
    }
    // Weapons
    for (int i = DAGGER; i < ROBES; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = WEAPON;
    }
    // Armor
    for  (int i = ROBES; i < METALLIC_SKIN; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = ARMOR;
    }
    // Cybernetics
    for  (int i = METALLIC_SKIN; i <= METALLIC_SKIN; i++){
        items[i].equippable = false;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = ARMOR;
        // TODO items[i].subtype = CYBERNETICS;
    }
    return items;
}

void AddToNPCInventory(Entity* npc, Item newItem) {
    npc->inventory[npc->inventoryPOS] = newItem;
    npc->inventoryPOS++;
}