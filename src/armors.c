#include <rogue.h>
void CreateArmors() {

}

Armor NoArmor() {
    Armor none;
    none.item.equippable = true;
    none.item.type = NULL_ITEM_TYPE;
    none.item.itemID = NULL_ITEM_ID;
    none.item.unequippable = false;
    strcpy(none.item.itemName, "None");
    none.value = 10;
    none.AC = 0;
    none.type = 1; // 1 = light, 2 = med, 3 = heavy
    return none;
}

Armor Rags() {
    Armor rags;
    rags.item.equippable = true;
    rags.item.type = ARMOR;
    rags.item.itemID = RAGS;
    rags.item.unequippable = false;
    strcpy(rags.item.itemName, "Rags");
    rags.AC = 0;
    rags.type = 1; // 1 = light, 2 = med, 3 = heavy
    return rags;
}

Armor Robes() {
    Armor robes;
    robes.item.equippable = true;
    robes.item.type = ARMOR;
    robes.item.itemID = ROBES;
    robes.item.unequippable = false;
    strcpy(robes.item.itemName, "Robes");
    robes.value = 10;
    robes.AC = 1;
    robes.type = 1; // 1 = light, 2 = med, 3 = heavy
    return robes;
}

Armor LeatherArmor() {
    Armor leatherArmor;
    leatherArmor.item.equippable = true;
    leatherArmor.item.type = ARMOR;
    leatherArmor.item.itemID = LEATHER_ARMOR;
    leatherArmor.item.unequippable = false;
    strcpy(leatherArmor.item.itemName, "Leather Armor");
    leatherArmor.value = 30;
    leatherArmor.AC = 2;
    leatherArmor.type = 2;
    return leatherArmor;
}

Armor Chainmail() {
    Armor chainmail;
    chainmail.item.equippable = true;
    chainmail.item.type = ARMOR;
    chainmail.item.itemID = CHAINMAIL;
    chainmail.item.unequippable = false;
    strcpy(chainmail.item.itemName, "Chainmail");
    chainmail.value = 50;
    chainmail.AC = 3;
    chainmail.type = 3;
    return chainmail;
}

Armor RangersCloak() {
    Armor rangersCloak;
    rangersCloak.item.equippable = true;
    rangersCloak.item.type = ARMOR;
    rangersCloak.item.itemID = RANGERS_CLOAK;
    rangersCloak.item.unequippable = false;
    strcpy(rangersCloak.item.itemName, "Ranger's Cloak");
    rangersCloak.value = 75;
    rangersCloak.AC = 2;
    rangersCloak.type = 1;
    return rangersCloak;
}
Armor MetallicSkin() {
    Armor metallicSkin;
    metallicSkin.item.equippable = true;
    metallicSkin.item.type = ARMOR;
    metallicSkin.item.itemID = METALLIC_SKIN;
    metallicSkin.item.unequippable = true;
    strcpy(metallicSkin.item.itemName, "Metallic Skin");
    metallicSkin.value = 200;
    metallicSkin.AC = 4;
    metallicSkin.type = 3;
    return metallicSkin;
}