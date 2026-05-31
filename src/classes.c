#include<rogue.h>

Class Knight(){
    Class knight;
    knight.isCaster = false;
    knight.hpPerLVL = 6;
    knight.manaPerLVL = 5;
    knight.mainStat = 2;
    knight.secondaryStat = 2;
    knight.abilities[Ability_1] = Charge();
    knight.abilities[Ability_2] = MakeHealthPotion();
    strcpy(knight.className, "Knight");
    strcpy(knight.classDesc, "A brave knight, forever journeying into the periless.");
    return knight;
}

Class Swashbuckler(){
    Class swashbuckler;
    swashbuckler.isCaster = false;
    swashbuckler.hpPerLVL = 4;
    swashbuckler.manaPerLVL = 5;
    swashbuckler.mainStat = 2;
    swashbuckler.secondaryStat = 2;
    swashbuckler.abilities[Ability_1] = FireVolley();
    swashbuckler.abilities[Ability_2] = Charge();
    strcpy(swashbuckler.className, "Swashbuckler");
    strcpy(swashbuckler.classDesc, "A black-hearted pirate, as strong as his rum.");
    return swashbuckler;
}

Class Wizard(){
    Class wizard;
    wizard.isCaster = true;
    wizard.hpPerLVL = 2;
    wizard.manaPerLVL = 7;
    wizard.mainStat = 4;
    wizard.secondaryStat = 0;
    wizard.abilities[Ability_1] = MagicMissile();
    wizard.abilities[Ability_2] = IceArmor();
    strcpy(wizard.className, "Wizard");
    strcpy(wizard.classDesc, "A lifelong academic, and master of the arcane.");
    return wizard;
}

Class Necromancer(){
    Class necromancer;
    necromancer.isCaster = true;
    necromancer.hpPerLVL = 2;
    necromancer.manaPerLVL = 7;
    necromancer.mainStat = 2;
    necromancer.secondaryStat = 2;
    necromancer.abilities[Ability_1] = DrainLife();
    necromancer.abilities[Ability_2] = SummonSkeleton();
    strcpy(necromancer.className, "Necromancer");
    strcpy(necromancer.classDesc, "Raises foul ghouls to do their bidding.");
    return necromancer;
}

Class Gunslinger(){
    Class gunslinger;
    gunslinger.isCaster = false;
    gunslinger.hpPerLVL = 4;
    gunslinger.manaPerLVL = 5;
    gunslinger.mainStat = 4;
    gunslinger.secondaryStat = 0;
    gunslinger.abilities[Ability_1] = FireVolley();
    gunslinger.abilities[Ability_2] = AimedShot();
    strcpy(gunslinger.className, "Gunslinger");
    strcpy(gunslinger.classDesc, "A crack shot, master of flash of gunpowder.");
    return gunslinger;
}

Class Ranger(){
    Class ranger;
    ranger.isCaster = false;
    ranger.hpPerLVL = 4;
    ranger.manaPerLVL = 5;
    ranger.mainStat = 2;
    ranger.secondaryStat = 2;
    ranger.abilities[Ability_1] = AimedShot();
    ranger.abilities[Ability_2] = MakeHealthPotion();
    strcpy(ranger.className, "Ranger");
    strcpy(ranger.classDesc, "A cloaked wanderer, skilled with a bow.");
    return ranger;
}

Class DarkKnight(){
    Class darkKnight;
    darkKnight.isCaster = true;
    darkKnight.hpPerLVL = 6;
    darkKnight.manaPerLVL = 5;
    darkKnight.mainStat = 4;
    darkKnight.secondaryStat = 0;
    darkKnight.abilities[Ability_1] = DrainLife();
    darkKnight.abilities[Ability_2] = Charge();
    strcpy(darkKnight.className, "Dark Knight");
    strcpy(darkKnight.classDesc, "A fallen hero.");
    return darkKnight;
}

Class Warlock(){
    Class warlock;
    warlock.isCaster = true;
    warlock.hpPerLVL = 2;
    warlock.manaPerLVL = 5;
    warlock.mainStat = 4;
    warlock.secondaryStat = 0;
    warlock.abilities[Ability_1] = DrainLife();
    warlock.abilities[Ability_2] = MagicMissile();
    strcpy(warlock.className, "Warlock");
    strcpy(warlock.classDesc, "A master of the dark arts.");
    return warlock;
}

Class Conjurer(){
    Class conjurer;
    conjurer.isCaster = true;
    conjurer.hpPerLVL = 2;
    conjurer.manaPerLVL = 7;
    conjurer.mainStat = 2;
    conjurer.secondaryStat = 2;
    conjurer.abilities[Ability_1] = Electrify();
    conjurer.abilities[Ability_2] = SummonSkeleton();
    strcpy(conjurer.className, "Conjurer");
    strcpy(conjurer.classDesc, "A Conjurer who pulls servants from the aether.");
    return conjurer;
}

Class Cyborg(){
    Class cyborg;
    cyborg.isCaster = false;
    cyborg.hpPerLVL = 6;
    cyborg.manaPerLVL = 5;
    cyborg.mainStat = 2;
    cyborg.secondaryStat = 2;
    cyborg.abilities[Ability_1] = SelfRepair();
    cyborg.abilities[Ability_2] = Electrify();
    strcpy(cyborg.className, "Cyborg");
    strcpy(cyborg.classDesc, "A Cyborg, out of time.");
    return cyborg;
}