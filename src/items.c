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
    MakeAmmoItems(items);
    MakeArmorItems(items);
    FillNullItems(items);
    NameWeaponItems(items);
    NameAmmoItems(items);
    NameArmorItems(items);
    WeaponItemDescriptions(items);
    AmmoItemDescriptions(items);
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

/* Used for removing projectiles from player inventory when shot.*/
void ShootFromPlayerInventory(Item target, int itemQuantity) {
   if(player->invTail == 0) {
        return;
    }
    for (int i = 0; i < player->invTail; i++) {
        if(player->inventory[i].itemID == target.itemID) {
            if(player->inventory[i].quantity == 0) return;
            if(player->inventory[i].quantity == 1) {
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
    if (IsAmmoItem(target)) {
        EquipAmmo(target);
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

void EquipAmmo(Item target) {
    if (player->equippedAmmo.item.itemID == NULL_ITEM_ID) {
        player->equippedAmmo = GetAmmoFromItem(target.itemID);
        player->equippedAmmo.item.quantity = 0;
    }
    else {
        Unequip(player->equippedAmmo.item);
        player->equippedAmmo = GetAmmoFromItem(target.itemID);
        player->equippedAmmo.item.quantity = target.quantity;
    }
    player->equippedAmmo.item.isEquipped = true;
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
    else if (target.itemID == player->equippedRanged.item.itemID) {
        target.isEquipped = false;
        player->equippedRanged = NoWeapon();
    }
    else if (target.itemID == player->equippedArmor.item.itemID) {
        target.isEquipped = false;
        player->equippedArmor = NoArmor();
        player->playerStats.AC = player->equippedArmor.AC;
    }
    else if (target.itemID == player->equippedAmmo.item.itemID) {
        target.isEquipped = false;
        player->equippedAmmo = NoAmmo();
    }
}

/* Adds these weapons to a singleton-like global list called "items" */
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
    for (int i = DAGGER; i <= DUAL_FLINTLOCKS; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = WEAPON;
    }
}

void MakeAmmoItems(Item* items) {
    // Primitives
    for (int i = ARROWS; i <= DARTS; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = AMMO;
    } // Magic
    for (int i = ACID_POTION_AMMO; i <= ACID_POTION_AMMO; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = AMMO;
    } // Bullets
    for (int i = BULLET_MUSKET; i <= BULLET_DRAGONS_BREATH; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = AMMO;
    } // Explosives
    for (int i = EXPLOSIVE; i <= EXPLOSIVE; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = AMMO;
    } // Energy
    for (int i = ENERGY_PACKS; i <= HEAVY_ENERGY_PACKS; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = AMMO;
    }
}

void MakeArmorItems(Item* items) {
    // Armor
    for (int i = RAGS; i < METALLIC_SKIN; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = true;
        items[i].itemID = i;
        items[i].type = ARMOR;
    }
    // Cybernetics
     for (int i = METALLIC_SKIN; i <= METALLIC_SKIN; i++){
        items[i].equippable = true;
        items[i].lootable = true;
        items[i].unequippable = false;
        items[i].itemID = i;
        items[i].type = ARMOR;
    }
}

/*
Fills remaining item list with empty items.
*/
void FillNullItems(Item* items){
    for (int i = METALLIC_SKIN + 1; i < ALL_ITEMS; i++){
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

void AmmoItemDescriptions(Item* items){
    strcpy(items[ARROWS].itemDesc, "Arrows, able to be fired from a bow.");
    strcpy(items[DARTS].itemDesc, "");
    strcpy(items[ACID_POTION_AMMO].itemDesc, "A green swirly potion, it burns the eyebrows.");
	strcpy(items[BULLET_MUSKET].itemDesc, "A small metal ball, fired with black powder.");
	strcpy(items[BULLET_5MM].itemDesc, "");
	strcpy(items[BULLET_9MM].itemDesc, "");
	strcpy(items[BULLET_556].itemDesc, "");
	strcpy(items[BULLET_762].itemDesc, "");
	strcpy(items[BULLET_308].itemDesc, "");
	strcpy(items[BULLET_50CAL].itemDesc, "");
	strcpy(items[BULLET_BUCKSHOT].itemDesc, "");
	strcpy(items[BULLET_SLUG].itemDesc, "");
	strcpy(items[BULLET_DRAGONS_BREATH].itemDesc, "");
	strcpy(items[MISSILES].itemDesc, "");
    strcpy(items[ENERGY_PACKS].itemDesc, "");
	strcpy(items[HEAVY_ENERGY_PACKS].itemDesc, "");
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

void NameAmmoItems(Item* items){
    strcpy(items[ARROWS].itemName, "Arrows");
    strcpy(items[DARTS].itemName, "Darts");
    strcpy(items[ACID_POTION_AMMO].itemName, "Acid Potions");
	strcpy(items[BULLET_MUSKET].itemName, "Flintlock Ammo");
	strcpy(items[BULLET_5MM].itemName, "5mm Ammo");
	strcpy(items[BULLET_9MM].itemName, "9mm Ammo");
	strcpy(items[BULLET_556].itemName, "5.56 Ammo");
	strcpy(items[BULLET_762].itemName, "7.62 Ammo");
	strcpy(items[BULLET_308].itemName, ".308 Ammo");
	strcpy(items[BULLET_50CAL].itemName, ".50 Cal Ammo");
	strcpy(items[BULLET_BUCKSHOT].itemName, "Buckshot Ammo");
	strcpy(items[BULLET_SLUG].itemName, "Shotgun Slugs");
	strcpy(items[BULLET_DRAGONS_BREATH].itemName, "Dragon's Breath Rounds");
	strcpy(items[MISSILES].itemName, "Missiles");
    strcpy(items[ENERGY_PACKS].itemName, "Energy Packs");
	strcpy(items[HEAVY_ENERGY_PACKS].itemName, "Heavy Energy Packs");
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

Ammo GetAmmoFromItem(int itemID) {
    switch(itemID) {
        case ARROWS: return Arrows();
        case DARTS: return Darts();
        case ACID_POTION_AMMO: return AcidPotionAmmo();
        case BULLET_MUSKET: return BulletMusket();
        case BULLET_5MM: return Bullet5mm();
        case BULLET_9MM: return Bullet9mm();
        case BULLET_556: return Bullet556();
        case BULLET_762:return Bullet762();
        case BULLET_308: return Bullet308();
        case BULLET_50CAL: return Bullet50Cal();
        case BULLET_BUCKSHOT: return BulletBuckshot();
        case BULLET_SLUG: return BulletSlug();
        case BULLET_DRAGONS_BREATH: return BulletDragonsBreath();
        case MISSILES: return Missiles();
        case ENERGY_PACKS: return EnergyPacks(); 
        case HEAVY_ENERGY_PACKS: return HeavyEnergyPacks();
    }
    return NoAmmo();
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

// char* GetAmmoType(int ArmorType) {
//     switch(ArmorType) {
//         case LIGHT: return "Light";
//         case MEDIUM: return "Medium";
//         case HEAVY: return "Heavy";
//         case EXOSUIT: return "Exosuit";
//         case POWER_ARMOR: return "Power Armor";
//         case MAGIC_ARMOR: return "Magic Armor";
//     }
//     return "None";
// }

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
/* consult the enum list "ItemIDs" in items.h to modify this.*/
bool IsMeleeWeaponItem(Item target) {
    if (target.itemID > CLAWS && target.itemID < ACID_POTION) return true;
    return false;
}

bool IsRangedWeaponItem(Item target) {
    if (target.itemID > CHROME_FISTS && target.itemID < ARROWS) return true;
    return false;
}

bool IsAmmoItem(Item target) {
    if (target.itemID > DUAL_FLINTLOCKS && target.itemID < RAGS) return true;
    return false;
}

bool IsArmorItem(Item target) {
    if (target.itemID > HEAVY_ENERGY_PACKS && target.itemID <= METALLIC_SKIN) return true;
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