#include <rogue.h>
void CreateArmors() {

}

Armor NoArmor() {
    Armor none;
    none.item.equippable = true;
    none.item.type = NULL_ITEM;
    none.item.itemID = NO_ARMOR;
    none.value = 10;
    none.AC = 0;
    none.type = 1; // 1 = light, 2 = med, 3 = heavy
    strcpy(none.armorName, "None");
    return none;
}

Armor Robes() {
    Armor robes;
    robes.item.equippable = true;
    robes.item.type = ARMOR;
    robes.item.itemID = ROBES;
    robes.value = 10;
    robes.AC = 1;
    robes.type = 1; // 1 = light, 2 = med, 3 = heavy
    strcpy(robes.armorName, "Robes");
    return robes;
}

Armor LeatherArmor() {
    Armor leatherArmor;
    leatherArmor.item.equippable = true;
    leatherArmor.item.type = ARMOR;
    leatherArmor.item.itemID = ROBES;
    leatherArmor.value = 30;
    leatherArmor.AC = 2;
    leatherArmor.type = 2;
    strcpy(leatherArmor.armorName, "Leather Armor");
    return leatherArmor;
}

Armor Chainmail() {
    Armor chainmail;
    chainmail.item.equippable = true;
    chainmail.item.type = ARMOR;
    chainmail.item.itemID = ROBES;
    chainmail.value = 50;
    chainmail.AC = 3;
    chainmail.type = 3;
    strcpy(chainmail.armorName, "Chainmail");
    return chainmail;
}

Armor RangersCloak() {
    Armor rangersCloak;
    rangersCloak.item.equippable = true;
    rangersCloak.item.type = ARMOR;
    rangersCloak.item.itemID = ROBES;
    rangersCloak.value = 75;
    rangersCloak.AC = 2;
    rangersCloak.type = 1;
    strcpy(rangersCloak.armorName, "Ranger's Cloak");
    return rangersCloak;
}
Armor MetallicSkin() {
    Armor metallicSkin;
    metallicSkin.item.equippable = true;
    metallicSkin.item.type = ARMOR;
    metallicSkin.item.itemID = ROBES;
    metallicSkin.value = 200;
    metallicSkin.AC = 4;
    metallicSkin.type = 3;
    strcpy(metallicSkin.armorName, "Metallic Skin");
    return metallicSkin;
}