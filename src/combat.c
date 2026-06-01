#include <rogue.h>

CombatHistory* CreateCombatHistory(Entity monster) {
    CombatHistory* combatHistory;
    combatHistory = calloc(1, sizeof(CombatHistory));
    combatHistory->defender = monster;
    return combatHistory;
}

/* Passed entity tries to attack player */
/* Returning false means they killed the player and the game will end.*/
bool AttackPlayer(Entity* attacker, CombatHistory* combatHistory, Player* player) {
    int playerAC = CalculatePlayerAC();
    int attackerAccRoll = CalculateEntityAccuracy(attacker);
    int attackerDMG = CalculateEntityDMG(attacker);
    int playerHP = player->playerStats.HP;

    if (attackerAccRoll >= playerAC) {
        player->playerStats.HP = (playerHP - attackerDMG);
        if (player->playerStats.HP <= 0) {
            //Player dead, Game is over.
            return false;
        }
        RecordMonsterHit(attacker, combatHistory, attackerAccRoll, attackerDMG);
        return true;
    }
    RecordMonsterMiss(attacker, combatHistory, attackerAccRoll, playerAC);
    return true;
}

/* Player tries to attack entity */
/* Returns true if combat happens at all. */
bool AttackEntity(Entity* defender, CombatHistory* combatHistory, Player* player) {
    int defenderAC = CalculateEntityAC(defender);
    int playerAccRoll = CalculatePlayerAccuracy();
    int playerDMG = CalculatePlayerDamage();
    int defenderHP = defender->entityStats.HP;

    if (playerAccRoll >= defenderAC) {
        defender->entityStats.HP = (defenderHP - playerDMG);
        if (defender->entityStats.HP <= 0) {
            RecordPlayerKill(defender, combatHistory, playerAccRoll, playerDMG);
            AssignCorpse(defender);
            return true;
        }
        RecordPlayerHit(defender, combatHistory, playerAccRoll, playerDMG);
        return true;
    }
    RecordPlayerMiss(defender, combatHistory, playerAccRoll, defenderAC);
    return true;
}

/* Returns true if the selected combat ability detects a monster in its range and LOS of player. */
/* Melee abilties still use this function, but with a range of 1. */
bool ShootTargetWithAbility(int x, int y) {
    // Will check if the ranged is not "none".
    if ((player->playerStats.mana) >= (player->equippedAbility.manaCost)) {
        // Player selected a monster.
        if ((map[y][x].isMonster) && LineOfSight(player->pos, map[y][x].pos) && 
        (GetDistance(player->pos, map[y][x].pos) <= player->equippedAbility.range)) {
            combatHistory->playerCombat = true;
            combatHistory->playerUsedAbility = true;
            combatHistory->defender = map[y][x];
            return true;
        }
        else if (map[y][x].isMonster && !(LineOfSight(player->pos, map[y][x].pos)) && 
        GetDistance(player->pos, map[y][x].pos) <= player->equippedRanged.range) {
            combatHistory->playerUsedAbility = false;
            combatHistory->playerCombat = false;
            strcpy(combatHistory->event, "Target not in line of sight.");
            QueueEvent(q, combatHistory->event);
            return false;
        }
        else if (map[y][x].isMonster && LineOfSight(player->pos, map[y][x].pos) && 
        GetDistance(player->pos, map[y][x].pos) > player->equippedAbility.range){
            combatHistory->playerUsedAbility = false;
            combatHistory->playerCombat = false;
            strcpy(combatHistory->event, "Target not in range.");
            QueueEvent(q, combatHistory->event);
            return false;
        }
    }
    else {
        combatHistory->playerUsedAbility = false;
        combatHistory->playerCombat = false;
        NotEnoughMana();
        return false;
    }
    
}

/* Returns true if there is a monster in LOS and range of equipped weapon.*/
bool ShootTarget(int x, int y) {
    // Will check if the ranged is not "none".
    if (player->equippedRanged.isRanged) {
            // Player selected a monster.
        if ((map[y][x].isMonster) && LineOfSight(player->pos, map[y][x].pos) && 
        (GetDistance(player->pos, map[y][x].pos) <= player->equippedRanged.range)) {
            combatHistory->playerCombat = true;
            combatHistory->playerUsedRanged = true;
            combatHistory->defender = map[y][x];
            return true;
        }
        else if (map[y][x].isMonster && !(LineOfSight(player->pos, map[y][x].pos)) && 
        GetDistance(player->pos, map[y][x].pos) <= player->equippedRanged.range) {
            combatHistory->playerUsedRanged = false;
            combatHistory->playerCombat = false;
            strcpy(combatHistory->event, "Target not in line of sight.");
            QueueEvent(q, combatHistory->event);
            return false;
        }
        else if (map[y][x].isMonster && LineOfSight(player->pos, map[y][x].pos) && 
        GetDistance(player->pos, map[y][x].pos) > player->equippedRanged.range){
            combatHistory->playerUsedRanged = false;
            combatHistory->playerCombat = false;
            strcpy(combatHistory->event, "Target not in range.");
            QueueEvent(q, combatHistory->event);
            return false;
        }
    }
    else {
        combatHistory->playerUsedRanged = false;
        combatHistory->playerCombat = false;
        strcpy(combatHistory->event, "No ranged weapons equipped.");
        QueueEvent(q, combatHistory->event);
        return false;
    }
    
}


int CalculateEntityAccuracy(Entity* attacker) {
    int attackerATKMod = attacker->entityStats.ATK;
    int attackerAccRoll = (rand() % 20) + 1;
    attackerAccRoll = attackerAccRoll + attackerATKMod;
    return attackerAccRoll;
}

int CalculateEntityDMG(Entity* attacker) {
    int maxDMG = attacker->entityStats.maxDMG;
    int minDMG = attacker->entityStats.minDMG;
    int attackerDMG = (rand() % maxDMG) + minDMG;
    return attackerDMG;
}

int CalculateEntityAC(Entity* defender) {
    int defenderDodgeMod = defender->entityStats.DEX;
    int defenderAC = defender->entityStats.AC;
    defenderDodgeMod = ((defenderDodgeMod - 10) / 2);
    defenderAC = (defenderAC + defenderDodgeMod + 10);
    return defenderAC;
}

int CalculatePlayerAccuracy() {
    int playerATKMod;
    if (combatHistory->playerUsedAbility == true && player->equippedAbility.isAttack == true){
        playerATKMod = player->equippedAbility.abilitySave;
    }
    else{
        playerATKMod = player->playerStats.ATK;
    }
    int playerAccRoll = (rand() % 20) + 1;
    playerAccRoll = playerAccRoll + playerATKMod;
    return playerAccRoll;
}

int CalculatePlayerDamage() {
    int maxDMG = player->playerStats.maxDMG;
    int minDMG = player->playerStats.minDMG;
    int playerDMG = (rand() % maxDMG) + minDMG;
    return playerDMG;
}

int CalculatePlayerAC() {
    int playerDodgeMod = player->playerStats.DEX;
    int playerAC = player->playerStats.AC;
    playerDodgeMod = ((playerDodgeMod - 10) / 2);
    playerAC = (playerAC + playerDodgeMod + 10);
    return playerAC;
}