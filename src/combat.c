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
            CheckForLevelUp();
            return true;
        }
        RecordPlayerHit(defender, combatHistory, playerAccRoll, playerDMG);
        return true;
    }
    RecordPlayerMiss(defender, combatHistory, playerAccRoll, defenderAC);
    return true;
}

/* Called from PlayerInput in player.c*/
/* Returns true if the selected combat ability detects a monster in its range and LOS of player. */
/* Melee abilties still use this function, but with a range of 1. */
bool ShootTargetWithAbility(int x, int y) {
    // Will check if the ranged is not "none".
    bool targetHit = false;
    if ((player->playerStats.mana) >= (player->equippedAbility.manaCost)) {
        // Player selected a monster.
        if ((map[y][x].isMonster) && LineOfSight(player->pos, map[y][x].pos) && 
        (GetDistance(player->pos, map[y][x].pos) <= player->equippedAbility.range)) {
            combatHistory->playerCombat = true;
            combatHistory->playerUsedAbility = true;
            combatHistory->defender = map[y][x];
            targetHit = true;
        }
        else if (map[y][x].isMonster && !(LineOfSight(player->pos, map[y][x].pos)) && 
        GetDistance(player->pos, map[y][x].pos) <= player->equippedRanged.range) {
            combatHistory->playerUsedAbility = false;
            combatHistory->playerCombat = false;
            strcpy(combatHistory->event, "Target not in line of sight.");
            QueueEvent(q, combatHistory->event);
        }
        else if (map[y][x].isMonster && LineOfSight(player->pos, map[y][x].pos) && 
        GetDistance(player->pos, map[y][x].pos) > player->equippedAbility.range){
            combatHistory->playerUsedAbility = false;
            combatHistory->playerCombat = false;
            strcpy(combatHistory->event, "Target not in range.");
            QueueEvent(q, combatHistory->event);
        }
    }
    else {
        combatHistory->playerUsedAbility = false;
        combatHistory->playerCombat = false;
        NotEnoughMana();
    }
    return targetHit;
}

/* Returns true if there is a monster in LOS and range of equipped weapon.*/
bool ShootTarget(int x, int y) {
    // Will check if the ranged is not "none".
    bool targetHit = false;
    if (player->equippedRanged.isRanged) {
            // Player selected a monster.
        if ((map[y][x].isMonster) && LineOfSight(player->pos, map[y][x].pos) && 
        (GetDistance(player->pos, map[y][x].pos) <= player->equippedRanged.range)) {
            combatHistory->playerCombat = true;
            combatHistory->playerUsedRanged = true;
            combatHistory->defender = map[y][x];
            targetHit = true;
        }
        else if (map[y][x].isMonster && !(LineOfSight(player->pos, map[y][x].pos)) && 
        GetDistance(player->pos, map[y][x].pos) <= player->equippedRanged.range) {
            combatHistory->playerUsedRanged = false;
            combatHistory->playerCombat = false;
            strcpy(combatHistory->event, "Target not in line of sight.");
            QueueEvent(q, combatHistory->event);
        }
        else if (map[y][x].isMonster && LineOfSight(player->pos, map[y][x].pos) && 
        GetDistance(player->pos, map[y][x].pos) > player->equippedRanged.range){
            combatHistory->playerUsedRanged = false;
            combatHistory->playerCombat = false;
            strcpy(combatHistory->event, "Target not in range.");
            QueueEvent(q, combatHistory->event);
        }
    }
    else {
        combatHistory->playerUsedRanged = false;
        combatHistory->playerCombat = false;
        strcpy(combatHistory->event, "No ranged weapons equipped.");
        QueueEvent(q, combatHistory->event);
    }
    return targetHit;
}

void PlayerMeleeOrRanged(Player* player){
    if (combatHistory->playerUsedAbility == true && player->equippedAbility.isAttack == true) {
        player->playerStats.maxDMG = player->equippedAbility.maxDMG;
        player->playerStats.minDMG = player->equippedAbility.minDMG;
        return;
        
    }
    if (combatHistory->playerUsedRanged == true) {
        player->playerStats.maxDMG = player->equippedRanged.maxDMG;
        player->playerStats.minDMG = player->equippedRanged.minDMG;
        return;
    }
    else {
        player->playerStats.maxDMG = player->equippedMelee.maxDMG;
        player->playerStats.minDMG = player->equippedMelee.minDMG;
        return;
    }
}

/* Check if player tried to attack something.*/ 
/* Then check if they used a ranged or melee weapon.*/ 
/* Set players current max and min DMG accoridingly and then attack the monster.*/ 
void PlayerPrepareCombat(int n_monsters) {
    PlayerMeleeOrRanged(player);
    Entity* target = FindMonsterInList(combatHistory->defender.entityID, n_monsters);
    if (target->isMonster) {
        combatHistory->playerCombat = AttackEntity(target, combatHistory, player);
    }
    // If a monster died, let other monsters still move.
    if(combatHistory->monsterKilled){
        ResetMoveFlags(mptr, n_monsters);
        combatHistory->monsterKilled = false;
    }
}

bool PlayerRangedAttack(int n_monsters){
    int ch;
    int closest = FindClosestMonster(mptr, n_monsters);
    int x = player->pos.x;
    int y = player->pos.y;

    /* make sure monster is in range */
    if (closest >= 0) {
        x = (mptr + closest)->pos.x;
        y = (mptr + closest)->pos.y;
    }
    if (closest == -2) {
        x = player->pos.x;
        y = player->pos.y;
    }

    Cursor(y, x, 1);
    while((ch = getch()) != 32 && ch != 102 && !(CheckEscape(ch))) {
        Cursor(y, x, 1);
        switch(ch) {
            //move up
            case KEY_UP:
                if (y == 0) {
                    break;
                }
                else {
                    RemoveCursor(y, x, 1);
                    y--;
                }
            break;
            //move down
            case KEY_DOWN:
                if (y == 50) {
                    break;
                }
                else {
                    RemoveCursor(y, x,13);
                    y++;
                }
                break;
            //move left
            case KEY_LEFT:
                if (x == 0) {
                    break;
                }
                else {
                    RemoveCursor(y, x, 1);
                    x--;
                }
                break;
            case KEY_RIGHT:
                if (x == 125) {
                    break;
                }
                else {
                    RemoveCursor(y, x, 1);
                    x++;
                }
                break;
            default:
                Cursor(y, x, 1);
                break;
            }
            Cursor(y, x, 1);
        }
    if (CheckEscape(ch)) {
        return false;
    }
    if(combatHistory->playerUsedAbility){
        return ShootTargetWithAbility(x, y);
    }
    else{
        return ShootTarget(x, y);
    }
}

void ResetCombatHistory(){
    combatHistory->monsterKilled = false;
    combatHistory->playerResult = false; // 0 = miss, 1 = hit
    combatHistory->entityResult = false;
    combatHistory->playerCombat = false; // true if player combat occurred
    combatHistory->playerUsedRanged = false;
    combatHistory->playerUsedAbility = false;
    combatHistory->attackerAccRoll = 0;
    combatHistory->attackerDMG = 0;
    combatHistory->defenderAC = 0;
    combatHistory->playerAccRoll = 0;
    combatHistory->playerDMG = 0;
    combatHistory->playerAC = 0;
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

/* playerATK Mod is already incorporated into the abilitySave if applicable in abilities.c*/
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