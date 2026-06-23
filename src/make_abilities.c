#include <rogue.h>


/*
These initialize the abilities and are equipped to the player.
If no special effects, treat like a normal ranged attack.
Melee attack abilities have a range of 1.
*/


Ability NoAbility() {
    Ability noAbility;
    noAbility.isAttack = false;
    noAbility.isMagic = false;
    noAbility.hasEffects = false;
    noAbility.abilityID = NO_ABILITY;
    noAbility.duration = 0;
    noAbility.minDMG = 0;
    noAbility.maxDMG = 0;
    noAbility.manaCost = 0;
    noAbility.range = 0;
    noAbility.abilitySave = 0;
    noAbility.miscStat = 0;
    strcpy(noAbility.abilityName, "None");
    strcpy(noAbility.abilityDesc, "none");
    return noAbility;
}

Ability AimedShot() {
    Ability aimedShot;
    aimedShot.isAttack = true;
    aimedShot.isMagic = false;
    aimedShot.hasEffects = false;
    aimedShot.abilityID = AIMED_SHOT;
    aimedShot.duration = 0;
    aimedShot.minDMG = (player->equippedRanged.minDMG) + 1;
    aimedShot.maxDMG = (player->equippedRanged.maxDMG) + 1;
    aimedShot.manaCost = 3;
    aimedShot.range = (player->equippedRanged.range);
    aimedShot.abilitySave = (player->playerStats.ATK) + 10;
    aimedShot.miscStat = 0; 
    strcpy(aimedShot.abilityName, "Aimed Shot");
    strcpy(aimedShot.abilityDesc, "none");
    return aimedShot;
}

Ability Charge() {
    Ability charge;
    charge.isAttack = true;
    charge.isMagic = false;
    charge.hasEffects = true;
    charge.abilityID = CHARGE;
    charge.duration = 0;
    charge.minDMG = (player->equippedMelee.minDMG) + 1;
    charge.maxDMG = (player->equippedMelee.maxDMG) + 1;
    charge.manaCost = 4;
    charge.range = 5;
    charge.abilitySave = (player->playerStats.ATK) + 10;
    charge.miscStat = 0;
    strcpy(charge.abilityName, "Charge");
    strcpy(charge.abilityDesc, "none");
    return charge;
}

Ability DrainLife() {
    Ability drainLife;
    drainLife.isAttack = true;
    drainLife.isMagic = true;
    drainLife.hasEffects = true;
    drainLife.abilityID = DRAIN_LIFE;
    drainLife.duration = 0;
    drainLife.minDMG = 4;
    drainLife.maxDMG = 10;
    drainLife.manaCost = 4;
    drainLife.range = 1;
    drainLife.abilitySave = (player->playerStats.ATK) + 6;
    drainLife.miscStat = 0;
    strcpy(drainLife.abilityName, "Drain Life");
    strcpy(drainLife.abilityDesc, "none");
    return drainLife;
}

Ability Electrify() {
    Ability electrify;
    electrify.isAttack = true;
    electrify.isMagic = false;
    electrify.hasEffects = false;
    electrify.abilityID = ELECTRIFY;
    electrify.duration = 0;
    electrify.minDMG = 1;
    electrify.maxDMG = 6;
    electrify.manaCost = 2;
    electrify.range = 3;
    electrify.abilitySave = (player->playerStats.ATK) + 3;
    electrify.miscStat = 0;
    strcpy(electrify.abilityName, "Electrify");
    strcpy(electrify.abilityDesc, "none");
    return electrify;
}

Ability FireVolley() {
    Ability fireVolley;
    fireVolley.isAttack = true;
    fireVolley.isMagic = false;
    fireVolley.hasEffects = false;
    fireVolley.abilityID = FIRE_VOLLEY;
    fireVolley.duration = 0;
    fireVolley.minDMG = (player->equippedRanged.minDMG);
    fireVolley.maxDMG = (player->equippedRanged.maxDMG);
    fireVolley.manaCost = 5;
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

// Give player a shield based on its min/max DMG
Ability IceArmor() {
    Ability iceArmor;
    iceArmor.isAttack = false;
    iceArmor.isMagic = true;
    iceArmor.hasEffects = true;
    iceArmor.abilityID = ICE_ARMOR;
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

Ability MagicMissile() {
    Ability magicMissile;
    magicMissile.isAttack = true;
    magicMissile.isMagic = true;
    magicMissile.hasEffects = false;
    magicMissile.abilityID = MAGIC_MISSILE;
    magicMissile.duration = 0;
    magicMissile.minDMG = (player->playerStats.LVL) + 1; //3d4 then 4d4 etc
    magicMissile.maxDMG = ((player->playerStats.LVL) * 4) + 1;
    magicMissile.manaCost = 4;
    magicMissile.range = 15;
    magicMissile.abilitySave = 40; // hard to miss with MM
    magicMissile.miscStat = 3; // number of missiles shot
    strcpy(magicMissile.abilityName, "Magic Missile");
    strcpy(magicMissile.abilityDesc, "none");
    return magicMissile;
}

// heals player from minDMG to maxDMG
Ability SecondWind() {
    Ability secondWind;
    secondWind.isAttack = false;
    secondWind.isMagic = false;
    secondWind.hasEffects = true;
    secondWind.abilityID = SECOND_WIND;
    secondWind.duration = 0;
    secondWind.minDMG = 2;
    secondWind.maxDMG = 8;
    secondWind.manaCost = 7;
    secondWind.range = 0;
    secondWind.abilitySave = 0;
    secondWind.miscStat = ((rand() % secondWind.maxDMG) + secondWind.minDMG);
    strcpy(secondWind.abilityName, "Second Wind");
    strcpy(secondWind.abilityDesc, "none");
    return secondWind;
}

Ability SelfRepair() {
    Ability selfRepair;
    selfRepair.isAttack = false;
    selfRepair.isMagic = false;
    selfRepair.hasEffects = true;
    selfRepair.abilityID = SELF_REPAIR;
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

Ability SummonSkeleton() {
    Ability summonSkeleton;
    summonSkeleton.isAttack = false;
    summonSkeleton.isMagic = true;
    summonSkeleton.hasEffects = true;
    summonSkeleton.abilityID = SUMMON_SKELETON;
    summonSkeleton.duration = 0; // skeleton lives until it dies
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

Ability ShadowBolt() {
    Ability shadowBolt;
    shadowBolt.isAttack = true;
    shadowBolt.isMagic = true;
    shadowBolt.hasEffects = false;
    shadowBolt.abilityID = SHADOW_BOLT;
    shadowBolt.duration = 0;
    shadowBolt.minDMG = 4;
    shadowBolt.maxDMG = 12;
    shadowBolt.manaCost = 5;
    shadowBolt.range = 15;
    shadowBolt.abilitySave = (player->playerStats.ATK) + 6;
    shadowBolt.miscStat = 0;
    strcpy(shadowBolt.abilityName, "ShadowBolt");
    strcpy(shadowBolt.abilityDesc, "none");
    return shadowBolt;
}

Ability Vengeance() {
    Ability vengeance;
    vengeance.isAttack = false;
    vengeance.isMagic = false;
    vengeance.hasEffects = true;
    vengeance.abilityID = VENGEANCE;
    vengeance.duration = 240;
    vengeance.minDMG = (player->equippedMelee.minDMG) + 1;
    vengeance.maxDMG = (player->equippedMelee.maxDMG) + 1;
    vengeance.manaCost = 5;
    vengeance.range = 0;
    vengeance.abilitySave = (player->playerStats.ATK) + 6;
    vengeance.miscStat = 0;
    strcpy(vengeance.abilityName, "Vengeance");
    strcpy(vengeance.abilityDesc, "none");
    return vengeance;
}

Ability Dash() {
    Ability dash;
    dash.isAttack = false;
    dash.isMagic = false;
    dash.hasEffects = true;
    dash.abilityID = DASH;
    dash.duration = 0;
    dash.minDMG = 0;
    dash.maxDMG = 0;
    dash.manaCost = 3;
    dash.range = 5;
    dash.abilitySave = 0;
    dash.miscStat = 0;
    strcpy(dash.abilityName, "Dash");
    strcpy(dash.abilityDesc, "none");
    return dash;
}

Ability DevastatingInsult() {
    Ability devastatingInsult;
    devastatingInsult.isAttack = true;
    devastatingInsult.isMagic = true;
    devastatingInsult.hasEffects = false;
    devastatingInsult.abilityID = DEVASTATING_INSULT;
    devastatingInsult.duration = 0;
    devastatingInsult.minDMG = 1;
    devastatingInsult.maxDMG = 4;
    devastatingInsult.manaCost = 2;
    devastatingInsult.range = 4;
    devastatingInsult.abilitySave = (player->playerStats.ATK);
    devastatingInsult.miscStat = 0;
    strcpy(devastatingInsult.abilityName, "Devastating Insult");
    strcpy(devastatingInsult.abilityDesc, "Do you know who else missed their attack?");
    return devastatingInsult;
}
