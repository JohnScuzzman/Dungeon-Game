#include <rogue.h>

Ability ThornBolt() {
    Ability thornBolt;
    thornBolt.isAttack = true;
    thornBolt.isMagic = true;
    thornBolt.hasEffects = false;
    thornBolt.abilityID = THORN_BOLT;
    thornBolt.duration = 0;
    thornBolt.minDMG = 1;
    thornBolt.maxDMG = 5;
    thornBolt.manaCost = 1;
    thornBolt.range = 10;
    thornBolt.abilitySave = (player->playerStats.ATK) + 1;
    thornBolt.miscStat = 0;
    strcpy(thornBolt.abilityName, "Thorn Bolt");
    strcpy(thornBolt.abilityDesc, "none");
    return thornBolt;
}

// set hasEffects = true, then set to wander, then call in AbilityEffects() in  abilities.c
// void CastthornBolt() {

// }