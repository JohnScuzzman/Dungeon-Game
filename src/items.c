#include <rogue.h>

const int ALL_ITEMS = 256;
const int INVENTORY_SIZE = 64;

// Parent Class Item goes at the top of Armor, Weapon, etc structs to make it a child struct.
// Weapon newItem = ShortSword();
// reference the items variables with Item* itemPtr = (Item *)&newItem
// Even though newItem is a weapon, we can still look at its item info using pointer upcasting.
/* Refer to the enum Items in items.h */
/* WIP */
void CreatePlayerInv() {
    for (int i = 0; i < INVENTORY_SIZE; i++){
        player->inventory[i].equippable = false;
        player->inventory[i].lootable = false;
        player->inventory[i].unequippable = true;
        player->inventory[i].itemID = NULL_ITEM_ID;
        player->inventory[i].type = NULL_ITEM_TYPE;
        strcpy(player->inventory[i].itemName, " ");
    }
}

void CreateMonsterInv(Entity* monster) {
    for (int i = 0; i < INVENTORY_SIZE; i++){
        monster->inventory[i].equippable = false;
        monster->inventory[i].lootable = false;
        monster->inventory[i].unequippable = true;
        monster->inventory[i].itemID = NULL_ITEM_ID;
        monster->inventory[i].type = NULL_ITEM_TYPE;
        strcpy(monster->inventory[i].itemName, " ");
    }
}

/* Weapons begin at 'FIST', Armor Begins at 'ROBES'*/
Item* CreateItemTable() {
    Item* items = calloc(ALL_ITEMS, sizeof(Item));
        items[NULL_ITEM_ID].equippable = false;
        items[NULL_ITEM_ID].lootable = false;
        items[NULL_ITEM_ID].unequippable = true;
        items[NULL_ITEM_ID].itemID = NULL_ITEM_ID;
        items[NULL_ITEM_ID].type = NULL_ITEM_TYPE;
        strcpy(items[NULL_ITEM_ID].itemName, " ");
    MakeWeaponItems(items);
    MakeArmorItems(items);
    NameWeaponItems(items);
    NameArmorItems(items);
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

void AddToPlayerInventory(Item newItem) {
    if(player->invTail == (INVENTORY_SIZE - 1)) {
        return;
    }
    player->inventory[player->invTail] = newItem;
    player->invTail++;
}

void RemoveFromPlayerInventory() {
    if(player->invTail == 0) {
        return;
    }
    player->inventory[player->invTail] = items[NULL_ITEM_ID];
    player->invTail--;
}

void MakeWeaponItems(Item* items) {
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
}

void MakeArmorItems(Item* items) {
        // Armor
    for  (int i = ROBES; i <= METALLIC_SKIN; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = ARMOR;
    }
    // Cybernetics
    for  (int i = METALLIC_SKIN; i < ALL_ITEMS; i++){
        items[i].equippable = false;
        items[i].lootable = false;
        items[i].unequippable = true;
        items[i].itemID = NULL_ITEM_ID;
        items[i].type = NULL_ITEM_TYPE;
        // TODO items[i].subtype = CYBERNETICS;
    }
}

void NameWeaponItems(Item* items){
    strcpy(items[FISTS].itemName, "Fists");
    strcpy(items[CLAWS].itemName, "Claws");
    strcpy(items[DAGGER].itemName, "Dagger");
    strcpy(items[SHORTSWORD].itemName, "Shortsword");
    strcpy(items[LONGSWORD].itemName, "Longsword");
    strcpy(items[GREATSWORD].itemName, "Greatsword");
    strcpy(items[CUTLASS].itemName, "Cutlass");
    strcpy(items[SCIMITAR].itemName, "Scimitar");
    strcpy(items[QUARTERSTAFF].itemName, "Quarterstaff");
    strcpy(items[CHROME_FISTS].itemName, "Chrome Fists");
    strcpy(items[ACID_POTION].itemName, "Acid Potion");
    strcpy(items[SHORTBOW].itemName, "Shortbow");
    strcpy(items[LONGBOW].itemName, "Longbow");
    strcpy(items[FLINTLOCK_PISTOL].itemName, "Flintlock_Pistol");
    strcpy(items[LIGHTNING_WAND].itemName, "Wand of Sparks");
    strcpy(items[DUAL_FLINTLOCKS].itemName, "Dual Flintlocks");
}

void NameArmorItems(Item* items){
    strcpy(items[RAGS].itemName, "Rags");
    strcpy(items[ROBES].itemName, "Robes");
    strcpy(items[LEATHER_ARMOR].itemName, "Leather Armor");
    strcpy(items[CHAINMAIL].itemName, "Chainmail");
    strcpy(items[RANGERS_CLOAK].itemName, "Ranger's Cloak");
    strcpy(items[METALLIC_SKIN].itemName, "Metallic Skin");
}

// void NullItem(Item* item) {
//     item->equippable = true;
//     item->lootable = false;
//     item->unequippable = true;
//     item->itemID = NULL_ITEM_ID;
//     item->type = NULL_ITEM;
//     strcpy(item->itemName, " ");
// }