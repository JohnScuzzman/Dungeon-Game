#include<rogue.h>

Class Knight(){
    Class knight;
    knight.hpPerLVL = 6;
    knight.manaPerLVL = 5;
    knight.mainStat = 2;
    knight.secondaryStat = 2;
    knight.abilities[0] = Charge();
    knight.abilities[1] = NoAbility();
    strcpy(knight.className, "Knight");
    strcpy(knight.classDesc, "A brave knight, forever journeying into the periless.");
    return knight;
}

Class Swashbuckler(){
    Class swashbuckler;
    swashbuckler.hpPerLVL = 4;
    swashbuckler.manaPerLVL = 5;
    swashbuckler.mainStat = 2;
    swashbuckler.secondaryStat = 2;
    swashbuckler.abilities[0] = FireVolley();
    swashbuckler.abilities[1] = NoAbility();
    strcpy(swashbuckler.className, "Swashbuckler");
    strcpy(swashbuckler.classDesc, "A black-hearted pirate, as strong as his rum.");
    return swashbuckler;
}

Class Wizard(){
    Class wizard;
    wizard.hpPerLVL = 2;
    wizard.manaPerLVL = 7;
    wizard.mainStat = 4;
    wizard.secondaryStat = 0;
    wizard.abilities[0] = MagicMissile();
    wizard.abilities[1] = IceArmor();
    strcpy(wizard.className, "Wizard");
    strcpy(wizard.classDesc, "A lifelong academic, and master of the arcane.");
    return wizard;
}

Class Necromancer(){
    Class necromancer;
    necromancer.hpPerLVL = 2;
    necromancer.manaPerLVL = 7;
    necromancer.mainStat = 2;
    necromancer.secondaryStat = 2;
    necromancer.abilities[0] = DrainLife();
    necromancer.abilities[1] = SummonSkeleton();
    strcpy(necromancer.className, "Necromancer");
    strcpy(necromancer.classDesc, "Raises foul ghouls to do their bidding.");
    return necromancer;
}

Class Gunslinger(){
    Class gunslinger;
    gunslinger.hpPerLVL = 4;
    gunslinger.manaPerLVL = 5;
    gunslinger.mainStat = 4;
    gunslinger.secondaryStat = 0;
    gunslinger.abilities[0] = FireVolley();
    gunslinger.abilities[1] = AimedShot();
    strcpy(gunslinger.className, "Gunslinger");
    strcpy(gunslinger.classDesc, "A crack shot, master of flash of gunpowder.");
    return gunslinger;
}

Class Ranger(){
    Class ranger;
    ranger.hpPerLVL = 4;
    ranger.manaPerLVL = 5;
    ranger.mainStat = 2;
    ranger.secondaryStat = 2;
    ranger.abilities[0] = AimedShot();
    ranger.abilities[1] = NoAbility();
    strcpy(ranger.className, "Ranger");
    strcpy(ranger.classDesc, "A cloaked wanderer, skilled with a bow.");
    return ranger;
}

Class DarkKnight(){
    Class darkKnight;
    darkKnight.hpPerLVL = 6;
    darkKnight.manaPerLVL = 5;
    darkKnight.mainStat = 4;
    darkKnight.secondaryStat = 0;
    darkKnight.abilities[0] = DrainLife();
    darkKnight.abilities[1] = NoAbility();
    strcpy(darkKnight.className, "Dark Knight");
    strcpy(darkKnight.classDesc, "A fallen hero.");
    return darkKnight;
}

Class Alchemist(){
    Class alchemist;
    alchemist.hpPerLVL = 4;
    alchemist.manaPerLVL = 5;
    alchemist.mainStat = 2;
    alchemist.secondaryStat = 2;
    alchemist.abilities[0] = MakeHealthPotion();
    alchemist.abilities[1] = NoAbility();
    strcpy(alchemist.className, "Alchemist");
    strcpy(alchemist.classDesc, "A Skilled potion-maker.");
    return alchemist;
}

Class Conjurer(){
    Class conjurer;
    conjurer.hpPerLVL = 2;
    conjurer.manaPerLVL = 7;
    conjurer.mainStat = 2;
    conjurer.secondaryStat = 2;
    conjurer.abilities[0] = MagicMissile();
    conjurer.abilities[1] = SummonSkeleton();
    strcpy(conjurer.className, "Conjurer");
    strcpy(conjurer.classDesc, "A Conjurer who pulls servants from the aether.");
    return conjurer;
}

Class Cyborg(){
    Class cyborg;
    cyborg.hpPerLVL = 6;
    cyborg.manaPerLVL = 5;
    cyborg.mainStat = 2;
    cyborg.secondaryStat = 2;
    cyborg.abilities[0] = Charge();
    cyborg.abilities[1] = Electrify();
    strcpy(cyborg.className, "Cyborg");
    strcpy(cyborg.classDesc, "A Cyborg, out of time.");
    return cyborg;
}