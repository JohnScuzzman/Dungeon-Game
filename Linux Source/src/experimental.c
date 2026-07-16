#include <rogue.h>

Ability ThornBolt() {
    Ability thornBolt;
    thornBolt.isAttack = true;
    thornBolt.isMagic = true;
    thornBolt.postCombatEffects = false;
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

// set postCombatEffects = true, then set to wander, then call in PostCombatAbilities() in  abilities.c
// void CastthornBolt() {

// }