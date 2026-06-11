#include <rogue.h>


Armor NoArmor() {
    Armor none;
    none.item.equippable = true;
    none.item.type = NULL_ITEM_TYPE;
    none.item.itemID = NULL_ITEM_ID;
    none.item.unequippable = false;
    none.item.value = 0;
    none.item.itemName = "None";
    none.AC = 0;
    none.type = LIGHT; // 1 = light, 2 = med, 3 = heavy
    return none;
}

Armor Rags() {
    Armor rags;
    rags.item.equippable = true;
    rags.item.type = ARMOR;
    rags.item.itemID = RAGS; 
    rags.item.unequippable = false;
    rags.item.value = 2;
    rags.item.itemName = "Rags";
    rags.AC = 0;
    rags.type = LIGHT; // 1 = light, 2 = med, 3 = heavy
    return rags;
}

Armor Robes() {
    Armor robes;
    robes.item.equippable = true;
    robes.item.type = ARMOR;
    robes.item.itemID = ROBES;
    robes.item.unequippable = false;
    robes.item.itemName = "Robes";
    robes.item.value = 10;
    robes.AC = 1;
    robes.type = LIGHT; // 1 = light, 2 = med, 3 = heavy
    return robes;
}

Armor LeatherArmor() {
    Armor leatherArmor;
    leatherArmor.item.equippable = true;
    leatherArmor.item.type = ARMOR;
    leatherArmor.item.itemID = LEATHER_ARMOR;
    leatherArmor.item.unequippable = false;
    leatherArmor.item.value = 30;
    leatherArmor.item.itemName = "Leather Armor";
    leatherArmor.AC = 2;
    leatherArmor.type = MEDIUM;
    return leatherArmor;
}

Armor Chainmail() {
    Armor chainmail;
    chainmail.item.equippable = true;
    chainmail.item.type = ARMOR;
    chainmail.item.itemID = CHAINMAIL;
    chainmail.item.unequippable = false;
    chainmail.item.value = 50;
    chainmail.item.itemName = "Chainmail";
    chainmail.AC = 3;
    chainmail.type = HEAVY;
    return chainmail;
}

Armor RangersCloak() {
    Armor rangersCloak;
    rangersCloak.item.equippable = true;
    rangersCloak.item.type = ARMOR;
    rangersCloak.item.itemID = RANGERS_CLOAK;
    rangersCloak.item.unequippable = false;
    rangersCloak.item.value = 75;
    rangersCloak.item.itemName = "Ranger's Cloak";
    rangersCloak.AC = 2;
    rangersCloak.type = LIGHT;
    return rangersCloak;
}

Armor MetallicSkin() {
    Armor metallicSkin;
    metallicSkin.item.equippable = true;
    metallicSkin.item.type = ARMOR;
    metallicSkin.item.itemID = METALLIC_SKIN;
    metallicSkin.item.unequippable = true;
    metallicSkin.item.value = 200;
    metallicSkin.item.itemName = "Metallic Skin";
    metallicSkin.AC = 4;
    metallicSkin.type = HEAVY;
    return metallicSkin;
}