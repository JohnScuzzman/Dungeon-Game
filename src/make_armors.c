#include <rogue.h>

/* 
These initialize the armors that will equipped to the player and npcs.
*/

Armor NoArmor() {
    Armor none;
    none.item.equippable = true;
    none.item.unequippable = true;
    none.item.isEquipped = false;
    none.item.type = NULL_ITEM_TYPE;
    none.item.itemID = NULL_ITEM_ID;
    none.item.quantity = 0;
    none.item.value = 0;
    none.AC = 0;
    none.type = LIGHT; // 1 = light, 2 = med, 3 = heavy
    none.statUsed = NULL_STAT_TYPE;
    none.statReq = 0;
    strcpy(none.item.itemName, "None");
    strcpy(none.item.itemDesc, " ");
    return none;
}

Armor Rags() {
    Armor rags;
    rags.item.equippable = true;
    rags.item.unequippable = true;
    rags.item.isEquipped = false;
    rags.item.type = ARMOR;
    rags.item.itemID = RAGS; 
    rags.item.quantity = 0;
    rags.item.value = 2;
    rags.AC = 0;
    rags.type = LIGHT; 
    rags.statUsed = STR;
    rags.statReq = 0;
    strcpy(rags.item.itemName, "Rags");
    strcpy(rags.item.itemDesc, "Filthy Rags, long overworn.");
    return rags;
}

Armor Robes() {
    Armor robes;
    robes.item.equippable = true;
    robes.item.unequippable = true;
    robes.item.isEquipped = false;
    robes.item.type = ARMOR;
    robes.item.itemID = ROBES;
    robes.item.quantity = 0;
    robes.item.value = 10;
    robes.AC = 1;
    robes.type = LIGHT; 
    robes.statUsed = STR;
    robes.statReq = 0;
    strcpy(robes.item.itemName, "Robes");
    strcpy(robes.item.itemDesc, "Long silken robes.");
    return robes;
}

Armor LeatherArmor() {
    Armor leatherArmor;
    leatherArmor.item.equippable = true;
    leatherArmor.item.unequippable = true;
    leatherArmor.item.isEquipped = false;
    leatherArmor.item.type = ARMOR;
    leatherArmor.item.itemID = LEATHER_ARMOR;
    leatherArmor.item.quantity = 0;
    leatherArmor.item.value = 30;
    leatherArmor.AC = 2;
    leatherArmor.type = MEDIUM; // 1 = light, 2 = med, 3 = heavy
    leatherArmor.statUsed = STR;
    leatherArmor.statReq = 8;
    strcpy(leatherArmor.item.itemName, "Leather Armor");
    strcpy(leatherArmor.item.itemDesc, "Tough and rigid, made of animal hide.");
    return leatherArmor;
}

Armor Chainmail() {
    Armor chainmail;
    chainmail.item.equippable = true;
    chainmail.item.unequippable = true;
    chainmail.item.isEquipped = false;
    chainmail.item.type = ARMOR;
    chainmail.item.itemID = CHAINMAIL;
    chainmail.item.quantity = 0;
    chainmail.item.value = 50;
    chainmail.AC = 3;
    chainmail.type = HEAVY; // 1 = light, 2 = med, 3 = heavy
    chainmail.statUsed = STR;
    chainmail.statReq = 10;
    strcpy(chainmail.item.itemName, "Chainmail");
    strcpy(chainmail.item.itemDesc, "Heavy, but provides formidable defense.");
    return chainmail;
}

Armor HalfPlate() {
    Armor halfPlate;
    halfPlate.item.equippable = true;
    halfPlate.item.unequippable = true;
    halfPlate.item.isEquipped = false;
    halfPlate.item.type = ARMOR;
    halfPlate.item.itemID = HALF_PLATE;
    halfPlate.item.quantity = 0;
    halfPlate.item.value = 300;
    halfPlate.AC = 5;
    halfPlate.type = HEAVY;
    halfPlate.statUsed = STR;
    halfPlate.statReq = 14;
    strcpy(halfPlate.item.itemName, "Half-Plate");
    strcpy(halfPlate.item.itemDesc, "A true knight's set of armor.");
    return halfPlate;
}

Armor RangersCloak() {
    Armor rangersCloak;
    rangersCloak.item.equippable = true;
    rangersCloak.item.unequippable = true;
    rangersCloak.item.isEquipped = false;
    rangersCloak.item.type = ARMOR;
    rangersCloak.item.itemID = RANGERS_CLOAK;
    rangersCloak.item.quantity = 0;
    rangersCloak.item.value = 75;
    rangersCloak.AC = 2;
    rangersCloak.type = LIGHT;
    rangersCloak.statUsed = DEX;
    rangersCloak.statReq = 12;
    strcpy(rangersCloak.item.itemName, "Ranger's Cloak");
    strcpy(rangersCloak.item.itemDesc, "Provides concealment in dark and dense forests.");
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
    metallicSkin.statUsed = CON;
    metallicSkin.statReq = 10;
    strcpy(metallicSkin.item.itemName, "Metallic Skin");
    strcpy(metallicSkin.item.itemDesc, "Servos and steel are your bastion.");
    return metallicSkin;
}