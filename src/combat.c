#include <rogue.h>

CombatHistory* CreateCombatHistory(Entity monster) {
    CombatHistory* combatHistory;
    combatHistory = calloc(1, sizeof(CombatHistory));
    combatHistory->monsterKilled = false;
    combatHistory->playerResult = false; // 0 = miss, 1 = hit
    combatHistory->entityResult = false;
    combatHistory->playerCombat = false; // true if player combat occurred
    combatHistory->playerUsedRanged = false;
    combatHistory->attackerATKMod = 0;
    combatHistory->attackerAccRoll = 0;
    combatHistory->attackerDMG = 0;
    combatHistory->defenderDodgeMod = 0;
    combatHistory->defenderAC = 0;
    combatHistory->playerATKMod = 0;
    combatHistory->playerAccRoll = 0;
    combatHistory->playerDMG = 0;
    combatHistory->playerDodgeMod = 0;
    combatHistory->playerAC = 0;
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
    playerAC = (playerAC + playerDodgeMod + 10);

    int maxDMG = attacker->entityStats.maxDMG;
    int minDMG = attacker->entityStats.minDMG;
    int playerHP = player->playerStats.HP;
    int attackerDMG = (rand() % maxDMG) + minDMG;

    if (attackerAccRoll >= playerAC) {
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
        combatHistory->playerAC = playerAC;
        combatHistory->attackerDMG = attackerDMG;
        combatHistory->entityResult = true;
        combatHistory->monsterKilled = false;
        return true;
    }
    // Miss
        combatHistory->defender = *attacker;
        combatHistory->playerDodgeMod = playerDodgeMod;
        combatHistory->attackerAccRoll = attackerAccRoll;
        combatHistory->playerAC = playerAC;
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
    defenderAC = (defenderAC + defenderDodgeMod + 10);

    int maxDMG = player->playerStats.maxDMG;
    int minDMG = player->playerStats.minDMG;
    int defenderHP = defender->entityStats.HP;
    int playerDMG = (rand() % maxDMG) + minDMG;

    if (playerAccRoll >= defenderAC) {
        defender->entityStats.HP = (defenderHP - playerDMG);
        if (defender->entityStats.HP <= 0) {
            AssignCorpse(defender);
            combatHistory->defender = *defender;
            combatHistory->playerATKMod = playerATKMod;
            combatHistory->defenderDodgeMod = defenderDodgeMod;
            combatHistory->playerAccRoll = playerAccRoll;
            combatHistory->defenderAC = defenderAC;
            combatHistory->playerDMG = playerDMG;
            // combatHistory->monsterKilled = true;
            combatHistory->playerResult = true;
            return true;
        }
        combatHistory->defender = *defender;
        combatHistory->playerATKMod = playerATKMod;
        combatHistory->defenderDodgeMod = defenderDodgeMod;
        combatHistory->playerAccRoll = playerAccRoll;
        combatHistory->defenderAC = defenderAC;
        combatHistory->playerDMG = playerDMG;
        combatHistory->monsterKilled = false;
        combatHistory->playerResult = true;
        return true;
    }
    combatHistory->defender = *defender;
    combatHistory->playerATKMod = playerATKMod;
    combatHistory->defenderDodgeMod = defenderDodgeMod;
    combatHistory->playerAccRoll = playerAccRoll;
    combatHistory->defenderAC = defenderAC;
    combatHistory->playerDMG = playerDMG;
    combatHistory->playerResult = false;
    combatHistory->monsterKilled = false;
    return true;
}

void PlayerMeleeOrRanged(Player* player){
    if (combatHistory->playerUsedRanged == true) {
        player->playerStats.maxDMG = player->equippedRanged.maxDMG;
        player->playerStats.minDMG = player->equippedRanged.minDMG;
    }
    else {
        player->playerStats.maxDMG = player->equippedMelee.maxDMG;
        player->playerStats.minDMG = player->equippedMelee.minDMG;
    }
}


bool PlayerRangedAttack(){
    int ch;
    int x = player->pos.x;
    int y = player->pos.y;
    Cursor(y, x, 1);
    while((ch = getch()) != 32 && ch != 102) {
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
    return ShootTarget(x, y);
}

bool ShootTarget(int x, int y) {
    // Will check if the ranged is not "none".
    if (player->equippedRanged.isRanged) {
            // Player selected a monster.
        if (map[y][x].entityID > 1 && LineOfSight(player->pos, map[y][x].pos)) {
            combatHistory->playerCombat = true;
            combatHistory->playerUsedRanged = true;
            combatHistory->defender = map[y][x];
            return true;
        }
        if (map[y][x].entityID > 1 && !LineOfSight(player->pos, map[y][x].pos)) {
            combatHistory->playerUsedRanged = false;
            mvprintw(23, 128, "Target not in line of sight.");
            return false;
        }
        else {
            mvprintw(23, 128, "Not a valid target.");
            combatHistory->playerUsedRanged = false;
            return false;
        }
    }
    else {
        mvprintw(23, 128, "No ranged weapons equipped.");
        combatHistory->playerUsedRanged = false;
        return false;
    }
}



