#include<rogue.h>

Class Knight(){
    Class knight;
    knight.isCaster = false;
    knight.classID = 0;
    knight.hpPerLVL = 6;
    knight.manaPerLVL = 5;
    knight.mainStat = 2;
    knight.secondaryStat = 2;
    knight.abilities[ABILITY_1] = Charge();
    knight.abilities[ABILITY_2] = SecondWind();
    knight.abilities[ABILITY_3] = NoAbility();
    knight.abilities[ABILITY_4] = NoAbility();
    knight.abilities[ABILITY_5] = NoAbility();
    strcpy(knight.className, "Knight");
    strcpy(knight.classDesc, "A brave knight, forever journeying into the periless.");
    return knight;
}

Class Swashbuckler(){
    Class swashbuckler;
    swashbuckler.isCaster = false;
    swashbuckler.classID = 1;
    swashbuckler.hpPerLVL = 4;
    swashbuckler.manaPerLVL = 5;
    swashbuckler.mainStat = 2;
    swashbuckler.secondaryStat = 2;
    swashbuckler.abilities[ABILITY_1] = FireVolley();
    swashbuckler.abilities[ABILITY_2] = Dash();
    swashbuckler.abilities[ABILITY_3] = NoAbility();
    swashbuckler.abilities[ABILITY_4] = NoAbility();
    swashbuckler.abilities[ABILITY_5] = NoAbility();
    strcpy(swashbuckler.className, "Swashbuckler");
    strcpy(swashbuckler.classDesc, "A black-hearted pirate, as strong as his rum.");
    return swashbuckler;
}

Class Wizard(){
    Class wizard;
    wizard.isCaster = true;
    wizard.classID = 2;
    wizard.hpPerLVL = 2;
    wizard.manaPerLVL = 7;
    wizard.mainStat = 4;
    wizard.secondaryStat = 0;
    wizard.abilities[ABILITY_1] = MagicMissile();
    wizard.abilities[ABILITY_2] = IceArmor();
    wizard.abilities[ABILITY_3] = NoAbility();
    wizard.abilities[ABILITY_4] = NoAbility();
    wizard.abilities[ABILITY_5] = NoAbility();
    strcpy(wizard.className, "Wizard");
    strcpy(wizard.classDesc, "A lifelong academic, and master of the arcane.");
    return wizard;
}

Class Necromancer(){
    Class necromancer;
    necromancer.isCaster = true;
    necromancer.classID = 3;
    necromancer.hpPerLVL = 2;
    necromancer.manaPerLVL = 7;
    necromancer.mainStat = 2;
    necromancer.secondaryStat = 2;
    necromancer.abilities[ABILITY_1] = DrainLife();
    necromancer.abilities[ABILITY_2] = SummonSkeleton();
    necromancer.abilities[ABILITY_3] = NoAbility();
    necromancer.abilities[ABILITY_4] = NoAbility();
    necromancer.abilities[ABILITY_5] = NoAbility();
    strcpy(necromancer.className, "Necromancer");
    strcpy(necromancer.classDesc, "Raises foul ghouls to do their bidding.");
    return necromancer;
}

Class Gunslinger(){
    Class gunslinger;
    gunslinger.isCaster = false;
    gunslinger.classID = 4;
    gunslinger.hpPerLVL = 4;
    gunslinger.manaPerLVL = 5;
    gunslinger.mainStat = 4;
    gunslinger.secondaryStat = 0;
    gunslinger.abilities[ABILITY_1] = FireVolley();
    gunslinger.abilities[ABILITY_2] = Dash();
    gunslinger.abilities[ABILITY_3] = NoAbility();
    gunslinger.abilities[ABILITY_4] = NoAbility();
    gunslinger.abilities[ABILITY_5] = NoAbility();
    strcpy(gunslinger.className, "Gunslinger");
    strcpy(gunslinger.classDesc, "A crack shot, master of flash of gunpowder.");
    return gunslinger;
}

Class Ranger(){
    Class ranger;
    ranger.isCaster = false;
    ranger.classID = 5;
    ranger.hpPerLVL = 5;
    ranger.manaPerLVL = 5;
    ranger.mainStat = 2;
    ranger.secondaryStat = 2;
    ranger.abilities[ABILITY_1] = AimedShot();
    ranger.abilities[ABILITY_2] = SecondWind();
    ranger.abilities[ABILITY_3] = NoAbility();
    ranger.abilities[ABILITY_4] = NoAbility();
    ranger.abilities[ABILITY_5] = NoAbility();
    strcpy(ranger.className, "Ranger");
    strcpy(ranger.classDesc, "A cloaked wanderer, skilled with a bow.");
    return ranger;
}

Class DarkKnight(){
    Class darkKnight;
    darkKnight.isCaster = true;
    darkKnight.classID = 6;
    darkKnight.hpPerLVL = 6;
    darkKnight.manaPerLVL = 5;
    darkKnight.mainStat = 4;
    darkKnight.secondaryStat = 0;
    darkKnight.abilities[ABILITY_1] = Charge();
    darkKnight.abilities[ABILITY_2] = DrainLife();
    darkKnight.abilities[ABILITY_3] = NoAbility();
    darkKnight.abilities[ABILITY_4] = NoAbility();
    darkKnight.abilities[ABILITY_5] = NoAbility();
    strcpy(darkKnight.className, "Dark Knight");
    strcpy(darkKnight.classDesc, "A fallen hero.");
    return darkKnight;
}

Class Warlock(){
    Class warlock;
    warlock.isCaster = true;
    warlock.classID = 7;
    warlock.hpPerLVL = 2;
    warlock.manaPerLVL = 5;
    warlock.mainStat = 4;
    warlock.secondaryStat = 0;
    warlock.abilities[ABILITY_1] = DrainLife();
    warlock.abilities[ABILITY_2] = MagicMissile();
    warlock.abilities[ABILITY_3] = NoAbility();
    warlock.abilities[ABILITY_4] = NoAbility();
    warlock.abilities[ABILITY_5] = NoAbility();
    strcpy(warlock.className, "Warlock");
    strcpy(warlock.classDesc, "A master of the dark arts.");
    return warlock;
}

Class Conjurer(){
    Class conjurer;
    conjurer.isCaster = true;
    conjurer.classID = 8;
    conjurer.hpPerLVL = 2;
    conjurer.manaPerLVL = 7;
    conjurer.mainStat = 2;
    conjurer.secondaryStat = 2;
    conjurer.abilities[ABILITY_1] = IceArmor();
    conjurer.abilities[ABILITY_2] = SummonSkeleton();
    conjurer.abilities[ABILITY_3] = NoAbility();
    conjurer.abilities[ABILITY_4] = NoAbility();
    conjurer.abilities[ABILITY_5] = NoAbility();
    strcpy(conjurer.className, "Conjurer");
    strcpy(conjurer.classDesc, "A Conjurer who pulls servants from the aether.");
    return conjurer;
}

Class Cyborg(){
    Class cyborg;
    cyborg.isCaster = false;
    cyborg.classID = 9;
    cyborg.hpPerLVL = 6;
    cyborg.manaPerLVL = 5;
    cyborg.mainStat = 2;
    cyborg.secondaryStat = 2;
    cyborg.abilities[ABILITY_1] = Electrify();
    cyborg.abilities[ABILITY_2] = SelfRepair();
    cyborg.abilities[ABILITY_3] = NoAbility();
    cyborg.abilities[ABILITY_4] = NoAbility();
    cyborg.abilities[ABILITY_5] = NoAbility();
    strcpy(cyborg.className, "Cyborg");
    strcpy(cyborg.classDesc, "A Cyborg, out of time.");
    return cyborg;
}