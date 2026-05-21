#include <rogue.h>
void CreateArmors() {

}

// void CreateMeleeWeapons() {

// }

// void CreateRangedWeapons() {

// }

Armor Robes() {
    Armor robes;
    robes.armorID = 0;
    robes.value = 10;
    robes.AC = 1;
    robes.type = 1; // 1 = light, 2 = med, 3 = heavy
    strcpy(robes.armorName, "Robes");
    return robes;
}

Armor LeatherArmor() {
    Armor leatherArmor;
    leatherArmor.armorID = 1;
    leatherArmor.value = 30;
    leatherArmor.AC = 2;
    leatherArmor.type = 2;
    strcpy(leatherArmor.armorName, "Leather Armor");
    return leatherArmor;
}

Armor Chainmail() {
    Armor chainmail;
    chainmail.armorID = 2;
    chainmail.value = 50;
    chainmail.AC = 3;
    chainmail.type = 3;
    strcpy(chainmail.armorName, "Chainmail");
    return chainmail;
}

Armor RangersCloak() {
    Armor rangersCloak;
    rangersCloak.armorID = 3;
    rangersCloak.value = 75;
    rangersCloak.AC = 2;
    rangersCloak.type = 1;
    strcpy(rangersCloak.armorName, "Ranger's Cloak");
    return rangersCloak;
}
Armor MetallicSkin() {
    Armor metallicSkin;
    metallicSkin.armorID = 4;
    metallicSkin.value = 200;
    metallicSkin.AC = 4;
    metallicSkin.type = 3;
    strcpy(metallicSkin.armorName, "Metallic Skin");
    return metallicSkin;
}