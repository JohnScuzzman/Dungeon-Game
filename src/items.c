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
        player->inventory[i].isEquipped = true;
        player->inventory[i].itemID = NULL_ITEM_ID;
        player->inventory[i].quantity = 0;
        player->inventory[i].type = NULL_ITEM_TYPE;
        strcpy(player->inventory[i].itemName, " ");
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
        strcpy(monster->inventory[i].itemName, " ");
    }
}

/* Weapons begin at 'FIST', Armor Begins at 'ROBES'*/
Item* CreateItemTable() {
    Item* items = calloc(ALL_ITEMS, sizeof(Item));
    items[NULL_ITEM_ID].equippable = false;
    items[NULL_ITEM_ID].lootable = false;
    items[NULL_ITEM_ID].unequippable = true;
    items[NULL_ITEM_ID].isEquipped = false;
    items[NULL_ITEM_ID].itemID = NULL_ITEM_ID;
    items[NULL_ITEM_ID].quantity = 0;
    items[NULL_ITEM_ID].type = NULL_ITEM_TYPE;
    strcpy(items[NULL_ITEM_ID].itemName, " ");
    strcpy(items[NULL_ITEM_ID].itemDesc, " ");
    MakeWeaponItems(items);
    MakeArmorItems(items);
    NameWeaponItems(items);
    NameArmorItems(items);
    WeaponItemDescriptions(items);
    ArmorItemDescriptions(items);
    return items;
}

void AddToNPCInventory(Entity* npc, Item newItem, int itemQuantity) {
    if(npc->invTail == (INVENTORY_SIZE - 1)) {
        return;
    }
    for (int i = 0; i < npc->invTail; i++) {
        if(npc->inventory[i].itemID == newItem.itemID && npc->inventory[i].quantity > 0) {
            npc->inventory[i].quantity += itemQuantity;
            return;
        }
    }
    npc->inventory[npc->invTail] = newItem;
    npc->inventory[npc->invTail].quantity = itemQuantity;
    npc->invTail++;
    return;
}

/* finds the item if its exists in the npc's inventory.
 Make the found item the tail item, copying it over, 
 Now that the tail has been copied, make tail
Unlike players remove item, Does not add it to the map.
This is becuase removing a map's item would copy it again and effectively duplciate it accidentally.*/
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
                    return;
                }
            }
        }
    }
}

/*
Adds npc1's inventory to npc2's
*/
void CombineEntityInventories(Entity* npc1, Entity* npc2) {
    npc1->invTail;
    int i = 0;
    while(i < npc1->invTail){
        AddToNPCInventory(npc2, npc1->inventory[i], npc1->inventory[i].quantity);
        i++;
    }
    i = 0;
    while(npc1->invTail != 0){
        RemoveFromNPCInventory(npc1, npc1->inventory[i], npc1->inventory[i].quantity);
        i++;
    }
}

void AddToPlayerInventory(Item newItem, int itemQuantity) {
    if(player->invTail == (INVENTORY_SIZE - 1)) {
        return;
    }
    for (int i = 0; i < player->invTail; i++) {
        if(player->inventory[i].itemID == newItem.itemID && player->inventory[i].quantity > 0) {
            player->inventory[i].quantity += itemQuantity;
            return;
        }
    }
    player->inventory[player->invTail] = newItem;
    player->inventory[player->invTail].quantity = itemQuantity;
    player->invTail++;
    return;
}


/* Search player inventory for item, if found, set the item to the last item in the players inventory.*/
/* Set the last item in players inventory to NULL, then move tail backward once.*/
/* If equipped, unequip the item.*/
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
Helper method for Sort Inventory.
Currently not implemented but will be used later in conjuction with Q-sort.
*/
int CompareStrings(const void *a, const void *b) {
    const char *strA = *(const char **)a;
    const char *strB = *(const char **)b;

    return strcmp(strA, strB);
    
}

/* Equips an item if it is valid to do so.*/
void Equip(Item target) {
    if (IsMeleeWeaponItem(target)) {
        EquipMelee(target);
    }
    if (IsRangedWeaponItem(target)) {
        EquipRanged(target);
    }
    if (IsArmorItem(target)) {
        EquipArmor(target);
    }
}

/* Helper methods for Equip */

void EquipMelee(Item target) {
    if (player->equippedMelee.item.itemID == FISTS || player->equippedMelee.item.itemID == CLAWS) {
        player->equippedMelee = GetWeaponFromItem(target.itemID);
    }
    else {
        Unequip(player->equippedMelee.item);
        player->equippedMelee = GetWeaponFromItem(target.itemID);
    }
    player->equippedMelee.item.isEquipped = true;
}

void EquipRanged(Item target) {
    if (player->equippedRanged.item.itemID == NULL_ITEM_ID) {
        player->equippedRanged = GetWeaponFromItem(target.itemID);
    }
    else {
        Unequip(player->equippedRanged.item);
        player->equippedRanged = GetWeaponFromItem(target.itemID);
    }
    player->equippedRanged.item.isEquipped = true;
}

void EquipArmor(Item target) {
    if (player->equippedArmor.item.itemID == NULL_ITEM_ID) {
        player->equippedArmor = GetArmorFromItem(target.itemID);
        player->playerStats.AC = player->equippedArmor.AC;
    }
    else {
        Unequip(player->equippedArmor.item);
        player->equippedArmor = GetArmorFromItem(target.itemID);
        player->playerStats.AC = player->equippedArmor.AC;
    }
    player->equippedArmor.item.isEquipped = true;
}

/* Unequips target item but does NOT add it back to player inventory. */
void Unequip(Item target) {
    // If player is a humanoid class they get fists, otherwise they get claws.
    if (target.itemID == player->equippedMelee.item.itemID && player->raceID < DRAGONBORN) {
        target.isEquipped = false;
        player->equippedMelee = Fists();
    }
    else if (target.itemID == player->equippedMelee.item.itemID) {
        target.isEquipped = false;
        player->equippedMelee = Claws();
    }
    if (target.itemID == player->equippedRanged.item.itemID) {
        target.isEquipped = false;
        player->equippedRanged = NoWeapon();
    }
    if (target.itemID == player->equippedArmor.item.itemID) {
        target.isEquipped = false;
        player->equippedArmor = NoArmor();
        player->playerStats.AC = player->equippedArmor.AC;
    }
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
    for (int i = DAGGER; i < RAGS; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = WEAPON;
    }
}

void MakeArmorItems(Item* items) {
        // Armor
    for  (int i = RAGS; i <= METALLIC_SKIN; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = ARMOR;
    }
    // Cybernetics
    for  (int i = METALLIC_SKIN + 1; i < ALL_ITEMS; i++){
        items[i].equippable = false;
        items[i].lootable = false;
        items[i].unequippable = true;
        items[i].itemID = NULL_ITEM_ID;
        items[i].type = NULL_ITEM_TYPE;
        // TODO items[i].subtype = CYBERNETICS;
    }
}

/* After the items are added to the list "items" */
/* These methods add more specific names and descriptions based on the enum value.*/
void WeaponItemDescriptions(Item* items){
    strcpy(items[FISTS].itemDesc, "Punch something if you must.");
    strcpy(items[CLAWS].itemDesc, "Sharp claws, ready to scratch.");
    strcpy(items[DAGGER].itemDesc, "A small, sharpened dagger.");
    strcpy(items[SHORTSWORD].itemDesc, "A shortsword, only about arm's length.");
    strcpy(items[LONGSWORD].itemDesc, "A mighty blade.");
    strcpy(items[GREATSWORD].itemDesc, "A large sword, demanding two hands of it's wielder.");
    strcpy(items[CUTLASS].itemDesc, "A favored sidearm of every brigand.");
    strcpy(items[SCIMITAR].itemDesc, "A curved sword, honed for slashing");
    strcpy(items[QUARTERSTAFF].itemDesc, "A large wooden staff, gnarled and tough.");
    strcpy(items[CHROME_FISTS].itemDesc, "Fists of chrome, glinting in the dark.");
    strcpy(items[ACID_POTION].itemDesc, "A potion of volatile acid.");
    strcpy(items[SHORTBOW].itemDesc, "A small bow.");
    strcpy(items[LONGBOW].itemDesc, "A large bow, capable of achieving great range.");
    strcpy(items[FLINTLOCK_PISTOL].itemDesc, "A black powder pistol, devastating at close range.");
    strcpy(items[LIGHTNING_WAND].itemDesc, "A small wand of sparks, weak but efficient.");
    strcpy(items[DUAL_FLINTLOCKS].itemDesc, "A pair of black powder hand cannons.");
}

void ArmorItemDescriptions(Item* items){
    strcpy(items[RAGS].itemDesc, "Filthy Rags, long overworn.");
    strcpy(items[ROBES].itemDesc, "Long silken robes.");
    strcpy(items[LEATHER_ARMOR].itemDesc, "Tough and rigid, made of animal hide.");
    strcpy(items[CHAINMAIL].itemDesc, "Heavy, but provides formidable defense.");
    strcpy(items[RANGERS_CLOAK].itemDesc, "Provides concealment in dark and dense forests.");
    strcpy(items[METALLIC_SKIN].itemDesc, "Servos and steel are your bastion.");
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

/* This is effectively how we can translate an item into weapon.*/
/* Returns a copy of a struct depending on the given itemID */
/* The local copy should be recycled and deleted by the called method.*/
/* This copy will get passed up to whatever method uses it, and then get recycled once the method is done.*/
Weapon GetWeaponFromItem(int itemID) {
    switch(itemID) {
        case FISTS: return Fists();
        case CLAWS: return Claws();
        case DAGGER: return Dagger();
        case SHORTSWORD: return Shortsword();
        case LONGSWORD: return Longsword();
        case GREATSWORD: return Greatsword();
        case CUTLASS: return Cutlass();
        case SCIMITAR: return Scimitar();
        case QUARTERSTAFF: return Quarterstaff();
        case CHROME_FISTS: return ChromeFists();
        case ACID_POTION: return AcidPotion();
        case SHORTBOW: return Shortbow();
        case LONGBOW: return Longbow();
        case FLINTLOCK_PISTOL: return FlintlockPistol();
        case LIGHTNING_WAND: return LightningWand();
        case DUAL_FLINTLOCKS: return DualFlintlocks();
    }
    return NoWeapon();
}

Armor GetArmorFromItem(int itemID) {
    switch(itemID) {
        case RAGS: return Rags();
        case ROBES: return Robes();
        case LEATHER_ARMOR: return LeatherArmor(); 
        case CHAINMAIL: return Chainmail();
        case RANGERS_CLOAK: return RangersCloak();
        case METALLIC_SKIN: return MetallicSkin();
    }
    return NoArmor();
}

char* GetArmorType(int ArmorType) {
    switch(ArmorType) {
        case LIGHT: return "Light";
        case MEDIUM: return "Medium";
        case HEAVY: return "Heavy";
        case EXOSUIT: return "Exosuit";
        case POWER_ARMOR: return "Power Armor";
        case MAGIC_ARMOR: return "Magic Armor";
    }
    return "None";
}

/* This suite of functions just checks if an item is a certain type and returns true if it is*/

bool IsMeleeWeaponItem(Item target) {
    if (target.itemID > CLAWS && target.itemID < ACID_POTION) return true;
    return false;
}

bool IsRangedWeaponItem(Item target) {
    if (target.itemID > CHROME_FISTS && target.itemID < RAGS) return true;
    return false;
}

bool IsArmorItem(Item target) {
    if (target.itemID > DUAL_FLINTLOCKS && target.itemID <= METALLIC_SKIN) return true;
    return false;
}
// void NullItem(Item* item) {
//     item->equippable = true;
//     item->lootable = false;
//     item->unequippable = true;
//     item->itemID = NULL_ITEM_ID;
//     item->type = NULL_ITEM;
//     strcpy(item->itemName, " ");
// }