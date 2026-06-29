#include <rogue.h>


const int ALL_ITEMS = 256;
const int INVENTORY_SIZE = 65;

/*
Adds npc1's inventory to npc2's
*/
void CombineEntityInventories(Entity* npc1, Entity* npc2) {
    if(npc1->inventory[0].itemID == NULL_ITEM_ID) {
        return;
    }
    int tail = npc1->invTail;
    int i = 0;
    while(i < tail){
        AddToNPCInventory(npc2, npc1->inventory[i], npc1->inventory[i].quantity);
        i++;
    }
    ClearEntityInventory(npc1);
}

/* 
Clears the passed in entity's inventory.
*/
void ClearEntityInventory(Entity* npc) {
    if(npc->inventory[0].itemID == NULL_ITEM_ID) {
        return;
    }
    int i = 0;
    int tail = npc->invTail;
    while(i < tail){
        RemoveFromNPCInventory(npc, npc->inventory[i], npc->inventory[i].quantity);
        i++;
    }
    if(npc->inventory[0].itemID != 0) {
        npc->invTail = npc->invHead;
        npc->inventory[0] = items[NULL_ITEM_ID]; // replace with a null item, clearing the last one out.
    }
}

/*
Parent Class Item goes at the top of Armor, Weapon, etc structs to make it a child struct.
Weapon newItem = ShortSword();
Reference the items variables with Item* itemPtr = (Item *)&newItem
Even though newItem is a weapon, we can still look at its item info using pointer upcasting.
Refer to the enum Items in items.h.
*/
void CreatePlayerInv() {
    for (int i = 0; i < INVENTORY_SIZE; i++){
        player->inventory[i].equippable = false;
        player->inventory[i].lootable = false;
        player->inventory[i].unequippable = true;
        player->inventory[i].isEquipped = true;
        player->inventory[i].itemID = NULL_ITEM_ID;
        player->inventory[i].quantity = 0;
        player->inventory[i].type = NULL_ITEM_TYPE;
        player->inventory[i].value = 0;
        strcpy(player->inventory[i].itemName, " ");
        strcpy(player->inventory[i].itemDesc, " ");
    }
}

void CreateMonsterInv(Entity* monster) {
    for (int i = 0; i < INVENTORY_SIZE; i++){
        monster->inventory[i].equippable = false;
        monster->inventory[i].lootable = false;
        monster->inventory[i].unequippable = true;
        monster->inventory[i].isEquipped = false;
        monster->inventory[i].itemID = NULL_ITEM_ID;
        monster->inventory[i].quantity = 0;
        monster->inventory[i].type = NULL_ITEM_TYPE;
        monster->inventory[i].value = 0;
        strcpy(monster->inventory[i].itemName, " ");
        strcpy(monster->inventory[i].itemDesc, " ");
    }
}

void AddToNPCInventory(Entity* npc, Item newItem, int itemQuantity) {
    if(npc->invTail == (INVENTORY_SIZE - 1)) {
        return;
    }
    for (int i = 0; i < npc->invTail; i++) {
        if(npc->inventory[i].itemID == newItem.itemID && npc->inventory[i].quantity > 0) {
            npc->inventory[i].quantity += itemQuantity;
            map[npc->pos.y][npc->pos.x].wasLooted = true;
            return;
        }
    }
    npc->inventory[npc->invTail] = newItem;
    npc->inventory[npc->invTail].quantity = itemQuantity;
    npc->invTail++;
    map[npc->pos.y][npc->pos.x].wasLooted = true;
    return;
}

/* 
Finds the item if its exists in the npc's inventory.
Make the found item the tail item, copying it over, 
Now that the tail has been copied, make tail
Unlike players remove item, Does not add it to the map.
This is becuase removing a map's item would copy it again and effectively duplciate it accidentally.
*/
void RemoveFromNPCInventory(Entity* npc, Item target, int itemQuantity) {
    if(npc->invTail == 0) {
        return;
    }
    for(int i = npc->invHead; i < npc->invTail; i++) { 
        if(npc->inventory[i].itemID == target.itemID){
            if(npc->inventory[i].quantity == 0) return;
            if(npc->inventory[i].quantity == 1) {
                    npc->inventory[i].quantity--;
                    npc->invTail--;
                    npc->inventory[i] = npc->inventory[npc->invTail];
                    npc->inventory[npc->invTail] = items[NULL_ITEM_ID];
                    map[npc->pos.y][npc->pos.x].wasLooted = true;
                    return;
            } 
            else{
                npc->inventory[i].quantity -= itemQuantity;
                // Bounds checking
                if(npc->inventory[i].quantity <= 0) {
                    npc->inventory[i].quantity = 0;
                    npc->invTail--;
                    npc->inventory[i] = npc->inventory[npc->invTail];
                    npc->inventory[npc->invTail] = items[NULL_ITEM_ID];
                    map[npc->pos.y][npc->pos.x].wasLooted = true;
                    return;
                }
            }
        }
    }
}

/* 
Adds the item to the player inventory if possible, and the quantity of it passed in as itemQuantity.
*/
void AddToPlayerInventory(Item newItem, int itemQuantity) {
    if(player->invTail == (INVENTORY_SIZE - 1)) {
        return;
    }
    if(player->invTail == player->invHead) {
        player->inventory[player->invTail] = newItem;
        player->inventory[player->invTail].quantity = itemQuantity;
        player->invTail++;
        return;
    }
    for (int i = 0; i < player->invTail; i++) {
        if(player->inventory[i].itemID == newItem.itemID && player->inventory[i].quantity > 0) {
            player->inventory[i].quantity += itemQuantity;
            if(newItem.itemID == player->equippedAmmo.item.itemID) player->equippedAmmo.item.quantity += itemQuantity;
            return;
        }
    }
    player->inventory[player->invTail] = newItem;
    player->inventory[player->invTail].quantity = itemQuantity;
    player->invTail++;
    return;
}


/* 
Search player inventory for item, if found, set the item to the last item in the players inventory.
Set the last item in players inventory to NULL, then move tail backward once.
If equipped, unequip the item.
*/
void RemoveFromPlayerInventory(Item target, int itemQuantity) {
   if(player->invTail == 0) {
        return;
    }
    for (int i = 0; i < player->invTail; i++) {
        if(player->inventory[i].itemID == target.itemID) {
            if(player->inventory[i].quantity == 0) return;
            if(player->inventory[i].quantity == 1) {
                AddToNPCInventory(&map[player->pos.y][player->pos.x], player->inventory[i], 1);
                player->invTail--;
                player->inventory[i] = player->inventory[player->invTail];
                player->inventory[player->invTail] = items[NULL_ITEM_ID];
                return;
            }
            else{
                player->inventory[i].quantity -= itemQuantity;
                AddToNPCInventory(&map[player->pos.y][player->pos.x], player->inventory[i], itemQuantity);
                if(player->inventory[i].quantity <= 0) {
                    player->inventory[i].quantity = 0;
                    player->invTail--;
                    player->inventory[i] = player->inventory[player->invTail];
                    player->inventory[player->invTail] = items[NULL_ITEM_ID];
                }
                return;
            }
        }
    }
}

/* 
Used for removing projectiles from player inventory when shot.
*/
void ShootFromPlayerInventory(Item target, int itemQuantity) {
   if(player->invTail == 0) {
        return;
    }
    for (int i = 0; i < player->invTail; i++) {
        if(player->inventory[i].itemID == target.itemID) {
            if(player->inventory[i].quantity == 0) return;
            if(player->inventory[i].quantity == 1) {
                Unequip(player->inventory[i]);
                player->invTail--;
                player->inventory[i] = player->inventory[player->invTail];
                player->inventory[player->invTail] = items[NULL_ITEM_ID];
                return;
            }
            else{
                player->inventory[i].quantity -= itemQuantity;
                if(player->inventory[i].quantity <= 0) {
                    player->inventory[i].quantity = 0;
                    player->invTail--;
                    player->inventory[i] = player->inventory[player->invTail];
                    player->inventory[player->invTail] = items[NULL_ITEM_ID];
                }
                return;
            }
        }
    }
}