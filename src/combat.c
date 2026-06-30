#include <rogue.h>

/* 
Passed entity tries to attack player 
Returning false means they killed the player and the game will end.
*/
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

/* 
Player tries to attack entity
Returns true if combat happens at all. 
*/
bool AttackEntity(Entity* defender, CombatHistory* combatHistory, Player* player, int n_monsters) {
    int defenderAC = CalculateEntityAC(defender);
    int playerAccRoll = CalculatePlayerAccuracy();
    int playerDMG = CalculatePlayerDamage();
    int defenderHP = defender->entityStats.HP;

    if (playerAccRoll >= defenderAC) {
        defender->entityStats.HP = (defenderHP - playerDMG);
        if (defender->entityStats.HP <= 0) {
            RecordPlayerKill(defender, combatHistory, playerAccRoll, playerDMG);
            AssignCorpse(defender, n_monsters);
            CheckForLevelUp();
            return true;
        }
        RecordPlayerHit(defender, combatHistory, playerAccRoll, playerDMG);
        return true;
    }
    RecordPlayerMiss(defender, combatHistory, playerAccRoll, defenderAC);
    return true;
}

/* Called from PlayerInput in player.c
Returns true if the selected combat ability detects a monster in its range and LOS of player.
Melee abilties still use this function, but with a range of 1.
*/
bool ShootTargetWithAbility(int x, int y) {
    // Will check if the ranged is not "none".
    bool targetHit = false;
    if ((player->playerStats.mana) >= (player->equippedAbility.manaCost)) {
        // Player selected a monster.
        if ((map[y][x].entityType == MONSTER) && LineOfSight(player->pos, map[y][x].pos) && 
        (GetDistance(player->pos, map[y][x].pos) <= player->equippedAbility.range)) {
            combatHistory->playerCombat = true;
            combatHistory->playerUsedAbility = true;
            combatHistory->defender = map[y][x];
            targetHit = true;
        }
        else if (map[y][x].entityType == MONSTER && !(LineOfSight(player->pos, map[y][x].pos)) && 
        GetDistance(player->pos, map[y][x].pos) <= player->equippedRanged.range) {
            combatHistory->playerUsedAbility = false;
            combatHistory->playerCombat = false;
            strcpy(combatHistory->event, "Target not in line of sight.");
            QueueEvent(q, combatHistory->event);
        }
        else if (map[y][x].entityType == MONSTER && LineOfSight(player->pos, map[y][x].pos) && 
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
        if ((map[y][x].entityType == MONSTER) && LineOfSight(player->pos, map[y][x].pos) && 
        (GetDistance(player->pos, map[y][x].pos) <= player->equippedRanged.range)) {
            combatHistory->playerCombat = true;
            combatHistory->playerUsedRanged = true;
            combatHistory->defender = map[y][x];
            targetHit = true;
        }
        else if (map[y][x].entityType == MONSTER && !(LineOfSight(player->pos, map[y][x].pos)) && 
        GetDistance(player->pos, map[y][x].pos) <= player->equippedRanged.range) {
            combatHistory->playerUsedRanged = false;
            combatHistory->playerCombat = false;
            strcpy(combatHistory->event, "Target not in line of sight.");
            QueueEvent(q, combatHistory->event);
        }
        else if (map[y][x].entityType == MONSTER && LineOfSight(player->pos, map[y][x].pos) && 
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


/* Determines if a player used a ranged attack/ability or melee attack/ability. */
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
    if (target->entityType == MONSTER) {
        combatHistory->playerCombat = AttackEntity(target, combatHistory, player, n_monsters);
    }
    // If a monster died, let other monsters still move.
    if(combatHistory->monsterKilled){
        ResetMoveFlags(mptr, n_monsters);
        combatHistory->monsterKilled = false;
    }
}

/*
Uses the players ranged weapon or ability for damage and ATK stat from
players stats or abilitySave from the used ability for accuracy.
Tries to lock on to the nearest monster.
FindClosestMonster is located in monster.c
*/
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
    if (CheckEscape(ch) || y == player->pos.y && x == player->pos.x) {
        return false;
    }
    /* If player uses a ranged, non magic ability, charge them ammo.*/
    if (combatHistory->playerUsedAbility){
        if (player->equippedAbility.isRanged && !player->equippedAbility.isMagic && player->equippedAmmo.item.quantity > 0){
            if (player->equippedRanged.ammoType == player->equippedAmmo.item.itemID){
                if (player->equippedAmmo.type == PRIMITIVE && map[y][x].entityType == FLOOR) { // Lets player pick up their arrows lol.
                    AddToNPCInventory(&map[y][x], items[player->equippedAmmo.item.itemID], 1);
                    strcpy(combatHistory->event, "You shoot the ");
                    strcat(combatHistory->event, map[y][x].entityName);
                    strcat(combatHistory->event, ".");
                    ShootFromPlayerInventory(player->equippedAmmo.item, 1);
                    QueueEvent(q, combatHistory->event);
                }
                RemoveFromPlayerInventory(player->equippedAmmo.item, 1);
                return ShootTargetWithAbility(x, y); // otherwise, dont add ammo to the monsters inv & shoot them.
            }
            else if (player->equippedRanged.ammoType != player->equippedAmmo.item.itemID){
                strcpy(combatHistory->event, "You have the wrong ammo equipped.");
                QueueEvent(q, combatHistory->event);
                return false;
            }
        }
        return ShootTargetWithAbility(x, y); // Not a ranged attack, Do not consume ammo.
    }
    else if (player->equippedAmmo.item.quantity > 0) {
        if (player->equippedRanged.ammoType == player->equippedAmmo.item.itemID){
            if (player->equippedAmmo.type == PRIMITIVE && map[y][x].entityType == FLOOR) { 
                    AddToNPCInventory(&map[y][x], items[player->equippedAmmo.item.itemID], 1);
                    strcpy(combatHistory->event, "You shoot the ");
                    strcat(combatHistory->event, map[y][x].entityName);
                    strcat(combatHistory->event, ".");
                    QueueEvent(q, combatHistory->event);
                    ShootFromPlayerInventory(player->equippedAmmo.item, 1);
                    return true;
            }
            else {
                ShootFromPlayerInventory(player->equippedAmmo.item, 1);
                return ShootTarget(x, y);
            }
        }
        else {
            strcpy(combatHistory->event, "You have the wrong ammo equipped.");
            QueueEvent(q, combatHistory->event);
            return false;
        }
    }
    else {
        strcpy(combatHistory->event, "You do not have enough ammo equipped.");
        QueueEvent(q, combatHistory->event);
        return false;
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
    /* Ranged weapon in melee suffers a minus 4 penalty.*/
    if(attacker->entityWeapon.isRanged && CheckPlayerAdjacent(attacker->pos)){
        attackerAccRoll -= 4;
    }
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
    if(combatHistory->playerUsedRanged && CheckPlayerAdjacent(combatHistory->defender.pos)){
        playerAccRoll -= 4;
    }
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