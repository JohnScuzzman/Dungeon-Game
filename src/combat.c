#include <rogue.h>

CombatHistory* CreateCombatHistory(Entity monster) {
    CombatHistory* combatHistory;
    combatHistory = calloc(1, sizeof(CombatHistory));
    combatHistory->monsterKilled = false;
    combatHistory->playerResult = false; // 0 = miss, 1 = hit
    combatHistory->entityResult = false;
    combatHistory->playerCombat = false; // true if player combat occurred
    combatHistory->attackerATKMod = 0;
    combatHistory->attackerAccRoll = 0;
    combatHistory->attackerDMG = 0;
    combatHistory->defenderDodgeMod = 0;
    combatHistory->defenderDodgeRoll = 0;
    combatHistory->playerATKMod = 0;
    combatHistory->playerAccRoll = 0;
    combatHistory->playerDMG = 0;
    combatHistory->playerDodgeMod = 0;
    combatHistory->playerDodgeRoll = 0;
    combatHistory->defender = monster;
    return combatHistory;
}

/* Passed entity tries to attack player */
bool AttackPlayer(Entity* attacker, CombatHistory* combatHistory, Player* player) {
    int entityID = attacker->entityID;
    int attackerATKMod = attacker->entityStats.ATK;
    int playerDodgeMod = player->playerStats.DEX;
    int playerAC = player->playerStats.AC;
    playerDodgeMod = ((playerDodgeMod - 10) / 2);
    int attackerAccRoll = (rand() % 20) + 1;
    attackerAccRoll = attackerAccRoll + attackerATKMod;
    int playerDodgeRoll = (rand() % 20) + 1;
    playerDodgeRoll = playerDodgeRoll + playerDodgeMod + playerAC;
    int maxDMG = attacker->entityStats.maxDMG;
    int minDMG = attacker->entityStats.maxDMG;
    int playerHP = player->playerStats.HP;
    int attackerDMG = (rand() % maxDMG) + minDMG;
    if (attackerAccRoll >= playerDodgeRoll) {
        player->playerStats.HP = (playerHP - attackerDMG);
        if (player->playerStats.HP <= 0) {
            //Player dead, Game is over.
            // Gameover()
            return false;
        }
    // Hit
        combatHistory->defender = *attacker;
        combatHistory->playerDodgeMod = playerDodgeMod;
        combatHistory->attackerAccRoll = attackerAccRoll;
        combatHistory->playerDodgeRoll = playerDodgeRoll;
        combatHistory->attackerDMG = attackerDMG;
        combatHistory->entityResult = true;
        combatHistory->monsterKilled = false;
        return true;
    }
    // Miss
        combatHistory->defender = *attacker;
        combatHistory->playerDodgeMod = playerDodgeMod;
        combatHistory->attackerAccRoll = attackerAccRoll;
        combatHistory->playerDodgeRoll = playerDodgeRoll;
        combatHistory->attackerDMG = attackerDMG;
        combatHistory->entityResult = false;
        combatHistory->monsterKilled = false;
        return true;
}

/* Player tries to attack entity */
bool AttackEntity(Entity* defender, CombatHistory* combatHistory, Player* player) {
    int entityID = defender->entityID;
    int playerATKMod = player->playerStats.ATK;
    int defenderDodgeMod = defender->entityStats.DEX;
    int defenderAC = defender->entityStats.AC;
    defenderDodgeMod = ((defenderDodgeMod - 10) / 2);
    int playerAccRoll = (rand() % 20) + 1;
    playerAccRoll = playerAccRoll + playerATKMod;
    int defenderDodgeRoll = (rand() % 20) + 1;
    defenderDodgeRoll = defenderDodgeRoll + defenderDodgeMod + defenderAC;
    int maxDMG = player->playerStats.maxDMG;
    int minDMG = player->playerStats.minDMG;
    int defenderHP = defender->entityStats.HP;
    int playerDMG = (rand() % maxDMG) + minDMG;
    if (playerAccRoll >= defenderDodgeRoll) {
        defender->entityStats.HP = (defenderHP - playerDMG);
        if (defender->entityStats.HP <= 0) {
            AssignCorpse(defender);
            combatHistory->defender = *defender;
            combatHistory->playerATKMod = playerATKMod;
            combatHistory->defenderDodgeMod = defenderDodgeMod;
            combatHistory->playerAccRoll = playerAccRoll;
            combatHistory->defenderDodgeRoll = defenderDodgeRoll;
            combatHistory->playerDMG = playerDMG;
            // combatHistory->monsterKilled = true;
            combatHistory->playerResult = true;
            return true;
        }
        combatHistory->defender = *defender;
        combatHistory->playerATKMod = playerATKMod;
        combatHistory->defenderDodgeMod = defenderDodgeMod;
        combatHistory->playerAccRoll = playerAccRoll;
        combatHistory->defenderDodgeRoll = defenderDodgeRoll;
        combatHistory->playerDMG = playerDMG;
        combatHistory->monsterKilled = false;
        combatHistory->playerResult = true;
        return true;
    }
    combatHistory->defender = *defender;
    combatHistory->playerATKMod = playerATKMod;
    combatHistory->defenderDodgeMod = defenderDodgeMod;
    combatHistory->playerAccRoll = playerAccRoll;
    combatHistory->defenderDodgeRoll = defenderDodgeRoll;
    combatHistory->playerDMG = playerDMG;
    combatHistory->playerResult = false;
    combatHistory->monsterKilled = false;
    return true;
}

void ResetCombatHistory(CombatHistory* combatHistory) {
    combatHistory->playerResult = false; // 0 = miss, 1 = hit
    combatHistory->entityResult = false;
    combatHistory->playerCombat = false; // true if player combat occurred
    combatHistory->attackerATKMod = 0;
    combatHistory->attackerAccRoll = 0;
    combatHistory->attackerDMG = 0;
    combatHistory->defenderDodgeMod = 0;
    combatHistory->defenderDodgeRoll = 0;
    combatHistory->playerATKMod = 0;
    combatHistory->playerAccRoll = 0;
    combatHistory->playerDMG = 0;
    combatHistory->playerDodgeMod = 0;
    combatHistory->playerDodgeRoll = 0;
}