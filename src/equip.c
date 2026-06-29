#include <rogue.h>

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
        player->equippedAmmo.item.quantity = target.quantity;
    }
    else {
        if(player->equippedAmmo.item.itemID == target.itemID){
            player->equippedAmmo.item.quantity += target.quantity;
        }
        else{
            Unequip(player->equippedAmmo.item);
            player->equippedAmmo = GetAmmoFromItem(target.itemID);
            player->equippedAmmo.item.quantity = target.quantity;
        }
        for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
            if (player->inventory[i].itemID == target.itemID) {
                player->equippedAmmo.item.quantity += player->inventory[i].quantity;
            }
        }
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
