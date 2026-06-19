#include <rogue.h>

/* 
These initialize the armors that will equipped to the player and npcs.
*/

Armor NoArmor() {
    Armor none;
    none.item.equippable = true;
    none.item.unequippable = false;
    none.item.isEquipped = false;
    none.item.type = NULL_ITEM_TYPE;
    none.item.itemID = NULL_ITEM_ID;
    none.item.quantity = 0;
    none.item.value = 0;
    strcpy(none.item.itemName, "None");
    strcpy(none.item.itemDesc, " ");
    none.AC = 0;
    none.type = LIGHT; // 1 = light, 2 = med, 3 = heavy
    return none;
}

Armor Rags() {
    Armor rags;
    rags.item.equippable = true;
    rags.item.unequippable = false;
    rags.item.isEquipped = false;
    rags.item.type = ARMOR;
    rags.item.itemID = RAGS; 
    rags.item.quantity = 0;
    rags.item.value = 2;
    rags.AC = 0;
    rags.type = LIGHT; 
    return rags;
}

Armor Robes() {
    Armor robes;
    robes.item.equippable = true;
    robes.item.unequippable = false;
    robes.item.isEquipped = false;
    robes.item.type = ARMOR;
    robes.item.itemID = ROBES;
    robes.item.quantity = 0;
    robes.item.value = 10;
    robes.AC = 1;
    robes.type = LIGHT; 
    return robes;
}

Armor LeatherArmor() {
    Armor leatherArmor;
    leatherArmor.item.equippable = true;
    leatherArmor.item.unequippable = false;
    leatherArmor.item.isEquipped = false;
    leatherArmor.item.type = ARMOR;
    leatherArmor.item.itemID = LEATHER_ARMOR;
    leatherArmor.item.quantity = 0;
    leatherArmor.item.value = 30;
    leatherArmor.AC = 2;
    leatherArmor.type = MEDIUM; // 1 = light, 2 = med, 3 = heavy
    return leatherArmor;
}

Armor Chainmail() {
    Armor chainmail;
    chainmail.item.equippable = true;
    chainmail.item.unequippable = false;
    chainmail.item.isEquipped = false;
    chainmail.item.type = ARMOR;
    chainmail.item.itemID = CHAINMAIL;
    chainmail.item.quantity = 0;
    chainmail.item.value = 50;
    chainmail.AC = 3;
    chainmail.type = HEAVY; // 1 = light, 2 = med, 3 = heavy
    return chainmail;
}

Armor RangersCloak() {
    Armor rangersCloak;
    rangersCloak.item.equippable = true;
    rangersCloak.item.unequippable = false;
    rangersCloak.item.isEquipped = false;
    rangersCloak.item.type = ARMOR;
    rangersCloak.item.itemID = RANGERS_CLOAK;
    rangersCloak.item.quantity = 0;
    rangersCloak.item.value = 75;
    rangersCloak.AC = 2;
    rangersCloak.type = LIGHT;
    return rangersCloak;
}

Armor MetallicSkin() {
    Armor metallicSkin;
    metallicSkin.item.equippable = true;
    metallicSkin.item.unequippable = true;
    metallicSkin.item.isEquipped = false;
    metallicSkin.item.type = ARMOR;
    metallicSkin.item.itemID = METALLIC_SKIN;
    metallicSkin.item.quantity = 0;
    metallicSkin.item.value = 200;
    metallicSkin.AC = 4;
    metallicSkin.type = HEAVY;
    return metallicSkin;
}