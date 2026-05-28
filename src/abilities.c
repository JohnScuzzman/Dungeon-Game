#include <rogue.h>

Ability NoAbility() {
    Ability none;
    none.isMagic = false;
    none.isSummon = false;
    none.duration = 0;
    none.minDMG = 0;
    none.maxDMG = 0;
    none.manaCost = 0;
    none.range = 0;
    none.abilitySave = 0;
    strcpy(none.abilityName, "none");
    strcpy(none.abilityDesc, "none");
    return none;
}

Ability Charge() {
    Ability charge;
    charge.isMagic = false;
    charge.isSummon = false;
    charge.duration = 0;
    charge.minDMG = (player->equippedMelee.minDMG) * 2;
    charge.maxDMG = (player->equippedMelee.maxDMG) * 2;
    charge.manaCost = 5;
    charge.range = 5;
    charge.abilitySave = player->playerStats.ATK;
    strcpy(charge.abilityName, "Charge");
    strcpy(charge.abilityDesc, "none");
    return charge;
}

Ability FireVolley() {
    Ability fireVolley;
    fireVolley.isMagic = false;
    fireVolley.isSummon = false;
    fireVolley.duration = 0;
    fireVolley.minDMG = (player->equippedRanged.minDMG) + 2;
    fireVolley.maxDMG = (player->equippedRanged.maxDMG) * 2;
    fireVolley.manaCost = 7;
    fireVolley.range = 5;
    fireVolley.abilitySave = player->playerStats.ATK;
    strcpy(fireVolley.abilityName, "Fire Volley");
    strcpy(fireVolley.abilityDesc, "none");
    return fireVolley;
}

Ability MagicMissile() {
    Ability magicMissile;
    magicMissile.isMagic = true;
    magicMissile.isSummon = false;
    magicMissile.minDMG = 2;
    magicMissile.maxDMG = 8;
    magicMissile.manaCost = 4;
    magicMissile.range = 15;
    magicMissile.abilitySave = 100; // hard to miss with MM
    strcpy(magicMissile.abilityName, "Magic Missile");
    strcpy(magicMissile.abilityDesc, "none");
    return magicMissile;
}

// Give player a shield based on its min/max DMG
Ability IceArmor() {
    Ability iceArmor;
    iceArmor.isMagic = true;
    iceArmor.isSummon = false;
    iceArmor.minDMG = 10;
    iceArmor.maxDMG = 10;
    iceArmor.manaCost = 5;
    iceArmor.range = 0;
    iceArmor.abilitySave = 0;
    strcpy(iceArmor.abilityName, "Ice Armor");
    strcpy(iceArmor.abilityDesc, "none");
    return iceArmor;
}

// Give player a shield based on its min/max DMG
Ability DrainLife() {
    Ability drainLife;
    drainLife.isMagic = true;
    drainLife.isSummon = false;
    drainLife.minDMG = 4;
    drainLife.maxDMG = 10;
    drainLife.manaCost = 4;
    drainLife.range = 0;
    drainLife.abilitySave = player->playerStats.ATK;
    strcpy(drainLife.abilityName, "Drain Life");
    strcpy(drainLife.abilityDesc, "none");
    return drainLife;
}

Ability SummonSkeleton() {
    Ability summonSkeleton;
    summonSkeleton.isMagic = true;
    summonSkeleton.isSummon = true;
    summonSkeleton.minDMG = 0;
    summonSkeleton.maxDMG = 0;
    summonSkeleton.manaCost = 16;
    summonSkeleton.range = 1;
    summonSkeleton.abilitySave = 0;
    strcpy(summonSkeleton.abilityName, "Summon Skeleton");
    strcpy(summonSkeleton.abilityDesc, "none");
    return summonSkeleton;
}

Ability AimedShot() {
    Ability aimedShot;
    aimedShot.isMagic = false;
    aimedShot.isSummon = false;
    aimedShot.minDMG = (player->equippedRanged.minDMG) + 1;
    aimedShot.maxDMG = (player->equippedRanged.maxDMG) + 4;
    aimedShot.manaCost = 3;
    aimedShot.range = player->equippedRanged.range;
    aimedShot.abilitySave = (player->playerStats.ATK) + 10;
    strcpy(aimedShot.abilityName, "Aimed Shot");
    strcpy(aimedShot.abilityDesc, "none");
    return aimedShot;
}

// heals player from minDMG to maxDMG
Ability MakeHealthPotion() {
    Ability makeHealthPotion;
    makeHealthPotion.isMagic = false;
    makeHealthPotion.isSummon = false;
    makeHealthPotion.minDMG = 2;
    makeHealthPotion.maxDMG = 8;
    makeHealthPotion.manaCost = 10;
    makeHealthPotion.range = 0;
    makeHealthPotion.abilitySave = 0;
    strcpy(makeHealthPotion.abilityName, "Make Health Potion");
    strcpy(makeHealthPotion.abilityDesc, "none");
    return makeHealthPotion;
}

Ability SelfRepair() {
    Ability selfRepair;
    selfRepair.isMagic = false;
    selfRepair.isSummon = false;
    selfRepair.minDMG = 1;
    selfRepair.maxDMG = 6;
    selfRepair.manaCost = 5;
    selfRepair.range = 0;
    selfRepair.abilitySave = 0;
    strcpy(selfRepair.abilityName, "Self Repair");
    strcpy(selfRepair.abilityDesc, "none");
    return selfRepair;
}

Ability Electrify() {
    Ability electrify;
    electrify.isMagic = false;
    electrify.isSummon = false;
    electrify.minDMG = 1;
    electrify.maxDMG = 6;
    electrify.manaCost = 2;
    electrify.range = 3;
    electrify.abilitySave = player->playerStats.ATK;
    strcpy(electrify.abilityName, "Electrify");
    strcpy(electrify.abilityDesc, "none");
    return electrify;
}