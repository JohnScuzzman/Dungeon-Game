#include <rogue.h>


// Parent Class Item goes at the top of Armor, Weapon, etc structs to make it a child struct.
// Weapon newItem = ShortSword();
// reference the items variables with Item* itemPtr = (Item *)&newItem
// Even though newItem is a weapon, we can still look at its item info using pointer upcasting.


/* Refer to the enum Items in items.h */
/* WIP */
Item* CreateItemTable() {
    Item* items = calloc(64, sizeof(Item));
    for (int i = 0; i < ROBES; i++){
        items[i].equippable = true;
        items[i].itemID = i;
        items[i].type = WEAPON;
    }
    for  (int i = ROBES; i <= METALLIC_SKIN; i++){
        items[i].equippable = true;
        items[i].itemID = i;
        items[i].type = ARMOR;
    }
    return items;
}