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
    Weapon weapon = GetWeaponFromItem(target.itemID);
    bool weaponReq = EquipWeaponRequirements(weapon);
    if (player->equippedMelee.item.itemID == FISTS || player->equippedMelee.item.itemID == CLAWS) {
        if (weaponReq){
            player->equippedMelee = weapon;
            player->equippedMelee.item.isEquipped = true;
        }
        else {
            strcpy(combatHistory->event, "You do not have enough ");
            strcat(combatHistory->event, GetRequiredStat(weapon.statUsed));
            strcat(combatHistory->event, ".");
            QueueEvent(q, combatHistory->event);
        }
    }
    else {
        if (weaponReq){
            Unequip(player->equippedMelee.item);
            player->equippedMelee = weapon;
            player->equippedMelee.item.isEquipped = true;
        }
        else {
            strcpy(combatHistory->event, "You do not have enough ");
            strcat(combatHistory->event, GetRequiredStat(weapon.statUsed));
            strcat(combatHistory->event, ".");
            QueueEvent(q, combatHistory->event);
        }
    }
}

void EquipRanged(Item target) {
    Weapon weapon = GetWeaponFromItem(target.itemID);
    bool weaponReq = EquipWeaponRequirements(weapon);
    if (player->equippedRanged.item.itemID == FISTS || player->equippedRanged.item.itemID == CLAWS) {
        if (weaponReq){
            player->equippedRanged = weapon;
            player->equippedRanged.item.isEquipped = true;
        }
        else {
            strcpy(combatHistory->event, "You do not have enough ");
            strcat(combatHistory->event, GetRequiredStat(weapon.statUsed));
            strcat(combatHistory->event, ".");
            QueueEvent(q, combatHistory->event);
        }
    }
    else {
        if (weaponReq){
            Unequip(player->equippedRanged.item);
            player->equippedRanged = weapon;
            player->equippedRanged.item.isEquipped = true;
        }
        else {
            strcpy(combatHistory->event, "You do not have enough ");
            strcat(combatHistory->event, GetRequiredStat(weapon.statUsed));
            strcat(combatHistory->event, ".");
            QueueEvent(q, combatHistory->event);
        }
    }
}

void EquipArmor(Item target) {
    Armor armor = GetArmorFromItem(target.itemID);
    bool armorReq = EquipArmorRequirements(armor);
    if (player->equippedArmor.item.itemID == NULL_ITEM_ID) {
        if (armorReq) {
            player->equippedArmor = armor;
            player->playerStats.AC = player->equippedArmor.AC;
            player->equippedArmor.item.isEquipped = true;
        }
        else {
            strcpy(combatHistory->event, "You do not have enough ");
            strcat(combatHistory->event, GetRequiredStat(armor.statUsed));
            strcat(combatHistory->event, ".");
            QueueEvent(q, combatHistory->event);
        }
    }
    else {
        if (armorReq) {
            Unequip(player->equippedArmor.item);
            player->equippedArmor = armor;
            player->playerStats.AC = player->equippedArmor.AC;
            player->equippedArmor.item.isEquipped = true;
        }
        else {
            strcpy(combatHistory->event, "You do not have enough ");
            strcat(combatHistory->event, GetRequiredStat(armor.statUsed));
            strcat(combatHistory->event, ".");
            QueueEvent(q, combatHistory->event);
        }
    }

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

bool EquipWeaponRequirements(Weapon target) {
    switch(target.statUsed) {
        case NULL_STAT_TYPE: return true;
        case STR: 
            if (target.statReq <= player->playerStats.STR) return true;
            return false;
        case DEX: 
            if (target.statReq <= player->playerStats.DEX) return true;
            return false;
        case CON: 
            if (target.statReq <= player->playerStats.CON) return true;
            return false;
        case INT: 
            if (target.statReq <= player->playerStats.INT) return true;
            return false;
        case CHA: 
            if (target.statReq <= player->playerStats.CHA) return true;
            return false;
        case WIS: 
            if (target.statReq <= player->playerStats.WIS) return true;
            return false;
        default: 
            return false;
    }
    return false;
}

bool EquipArmorRequirements(Armor target) {
    switch(target.statUsed) {
        case NULL_STAT_TYPE: return true;
        case STR: 
            if (target.statReq <= player->playerStats.STR) return true;
            return false;
        case DEX: 
            if (target.statReq <= player->playerStats.DEX) return true;
            return false;
        case CON: 
            if (target.statReq <= player->playerStats.CON) return true;
            return false;
        case INT: 
            if (target.statReq <= player->playerStats.INT) return true;
            return false;
        case CHA: 
            if (target.statReq <= player->playerStats.CHA) return true;
            return false;
        case WIS: 
            if (target.statReq <= player->playerStats.WIS) return true;
            return false;
        default: 
            return false;
    }
    return false;
}

char* GetRequiredStat(int reqType) {
    switch(reqType) {
        case NULL_STAT_TYPE: return "None";
        case STR: return "STR";
        case DEX: return "DEX";
        case CON: return "CON";
        case INT: return "INT";
        case CHA: return "CHA";
        case WIS: return "WIS";
    }
    return "None";
}
