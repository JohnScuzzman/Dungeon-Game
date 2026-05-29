#include <rogue.h>

Ability NoAbility() {
    Ability noAbility;
    noAbility.isAttack = false;
    noAbility.isMagic = false;
    noAbility.isRanged = false;
    noAbility.isSummon = false;
    noAbility.duration = 0;
    noAbility.minDMG = 0;
    noAbility.maxDMG = 0;
    noAbility.manaCost = 0;
    noAbility.range = 0;
    noAbility.abilitySave = 0;
    noAbility.miscStat = 0;
    strcpy(noAbility.abilityName, "None");
    strcpy(noAbility.abilityDesc, " ");
    return noAbility;
}

Ability Charge() {
    Ability charge;
    charge.isAttack = true;
    charge.isMagic = false;
    charge.isRanged = false;
    charge.isSummon = false;
    charge.duration = 0;
    charge.minDMG = (player->equippedMelee.minDMG) * 2;
    charge.maxDMG = (player->equippedMelee.maxDMG) * 2;
    charge.manaCost = 5;
    charge.range = 5;
    charge.abilitySave = (player->playerStats.ATK) + 5;
    charge.miscStat = 0;
    strcpy(charge.abilityName, "Charge");
    strcpy(charge.abilityDesc, "none");
    return charge;
}

Ability FireVolley() {
    Ability fireVolley;
    fireVolley.isAttack = true;
    fireVolley.isMagic = false;
    fireVolley.isRanged = true;
    fireVolley.isSummon = false;
    // fireVolley.duration = 0;
    fireVolley.minDMG = (player->equippedRanged.minDMG);
    fireVolley.maxDMG = (player->equippedRanged.maxDMG);
    fireVolley.manaCost = 7;
    fireVolley.range = 5;
    fireVolley.abilitySave = (player->playerStats.ATK) + 3;
    fireVolley.miscStat = (player->playerStats.LVL); // number of shots fired.
    fireVolley.miscStat++;
    fireVolley.minDMG = (fireVolley.minDMG) * (fireVolley.miscStat);
    fireVolley.maxDMG = (fireVolley.minDMG) * (fireVolley.miscStat);
    strcpy(fireVolley.abilityName, "Fire Volley");
    strcpy(fireVolley.abilityDesc, "none");
    return fireVolley;
}

Ability MagicMissile() {
    Ability magicMissile;
    magicMissile.isAttack = true;
    magicMissile.isMagic = true;
    magicMissile.isRanged = true;
    magicMissile.isSummon = false;
    magicMissile.minDMG = (player->playerStats.LVL) + 2; //3d4 then 4d4 etc
    magicMissile.maxDMG = (magicMissile.minDMG) * 4;
    magicMissile.manaCost = 4;
    magicMissile.range = 15;
    magicMissile.abilitySave = 40; // hard to miss with MM
    magicMissile.miscStat = 3; // number of missiles shot
    strcpy(magicMissile.abilityName, "Magic Missile");
    strcpy(magicMissile.abilityDesc, "none");
    return magicMissile;
}

// Give player a shield based on its min/max DMG
Ability IceArmor() {
    Ability iceArmor;
    iceArmor.isAttack = false;
    iceArmor.isMagic = true;
    iceArmor.isRanged = false;
    iceArmor.isSummon = false;
    iceArmor.duration = 240;
    iceArmor.minDMG = 0;
    iceArmor.maxDMG = 0;
    iceArmor.manaCost = 10;
    iceArmor.range = 0;
    iceArmor.abilitySave = 0;
    iceArmor.miscStat = 5; // AC gained
    strcpy(iceArmor.abilityName, "Ice Armor");
    strcpy(iceArmor.abilityDesc, "none");
    return iceArmor;
}

// Give player a shield based on its min/max DMG
Ability DrainLife() {
    Ability drainLife;
    drainLife.isAttack = true;
    drainLife.isMagic = true;
    drainLife.isRanged = true;
    drainLife.isSummon = false;
    drainLife.duration = 0;
    drainLife.minDMG = 4;
    drainLife.maxDMG = 10;
    drainLife.manaCost = 4;
    drainLife.range = 3;
    drainLife.abilitySave = (player->playerStats.ATK) + 2;
    drainLife.miscStat = 0; // HP gained
    strcpy(drainLife.abilityName, "Drain Life");
    strcpy(drainLife.abilityDesc, "none");
    return drainLife;
}

Ability SummonSkeleton() {
    Ability summonSkeleton;
    summonSkeleton.isAttack = false;
    summonSkeleton.isMagic = true;
    summonSkeleton.isRanged = false;
    summonSkeleton.isSummon = true;
    summonSkeleton.duration = 1000;
    summonSkeleton.minDMG = 1; // skeletons dmg
    summonSkeleton.maxDMG = 6;
    summonSkeleton.manaCost = 16;
    summonSkeleton.range = 1;
    summonSkeleton.abilitySave = 0;
    summonSkeleton.miscStat = 8; // skeletons HP
    strcpy(summonSkeleton.abilityName, "Summon Skeleton");
    strcpy(summonSkeleton.abilityDesc, "none");
    return summonSkeleton;
}

Ability AimedShot() {
    Ability aimedShot;
    aimedShot.isAttack = true;
    aimedShot.isMagic = false;
    aimedShot.isRanged = true;
    aimedShot.isSummon = false;
    aimedShot.duration = 0;
    aimedShot.minDMG = (player->equippedRanged.minDMG) + 1;
    aimedShot.maxDMG = (player->equippedRanged.maxDMG) + 4;
    aimedShot.manaCost = 3;
    aimedShot.range = (player->equippedRanged.range);
    aimedShot.abilitySave = (player->playerStats.ATK) + 10;
    aimedShot.miscStat = 0; // skeletons HP
    strcpy(aimedShot.abilityName, "Aimed Shot");
    strcpy(aimedShot.abilityDesc, "none");
    return aimedShot;
}

// heals player from minDMG to maxDMG
Ability MakeHealthPotion() {
    Ability makeHealthPotion;
    makeHealthPotion.isAttack = false;
    makeHealthPotion.isMagic = false;
    makeHealthPotion.isRanged = false;
    makeHealthPotion.isSummon = false;
    makeHealthPotion.duration = 0;
    makeHealthPotion.minDMG = 2;
    makeHealthPotion.maxDMG = 8;
    makeHealthPotion.manaCost = 7;
    makeHealthPotion.range = 0;
    makeHealthPotion.abilitySave = 0;
    makeHealthPotion.miscStat = ((rand() % makeHealthPotion.maxDMG) + makeHealthPotion.minDMG);
    strcpy(makeHealthPotion.abilityName, "Make Health Potion");
    strcpy(makeHealthPotion.abilityDesc, "none");
    return makeHealthPotion;
}

Ability SelfRepair() {
    Ability selfRepair;
    selfRepair.isAttack = false;
    selfRepair.isMagic = false;
    selfRepair.isRanged = false;
    selfRepair.isSummon = false;
    selfRepair.duration = 0;
    selfRepair.minDMG = 1;
    selfRepair.maxDMG = 6;
    selfRepair.manaCost = 5;
    selfRepair.range = 0;
    selfRepair.abilitySave = 0;
    selfRepair.miscStat = ((rand() % selfRepair.maxDMG) + selfRepair.minDMG);
    strcpy(selfRepair.abilityName, "Self Repair");
    strcpy(selfRepair.abilityDesc, "none");
    return selfRepair;
}

Ability Electrify() {
    Ability electrify;
    electrify.isAttack = true;
    electrify.isMagic = false;
    electrify.isRanged = true;
    electrify.isSummon = false;
    electrify.duration = 0;
    electrify.minDMG = 1;
    electrify.maxDMG = 10;
    electrify.manaCost = 4;
    electrify.range = 3;
    electrify.abilitySave = (player->playerStats.ATK) + 3;
    electrify.miscStat = 0;
    strcpy(electrify.abilityName, "Electrify");
    strcpy(electrify.abilityDesc, "none");
    return electrify;
}

void CastSelfRepair(){
    player->playerStats.HP += (rand() % player->playerClass.abilities[0].maxDMG) + player->playerClass.abilities[0].minDMG;
    player->playerStats.mana -= player->playerClass.abilities[0].manaCost;
}