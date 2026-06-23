#include <rogue.h>
#define TURN_BUFFER 8

/* checks if the player is adjacent to the passed coordinates. */
bool CheckPlayerAdjacent(Position origin) {
    if (origin.y == (player->pos.y) || origin.y == ((player->pos.y) - 1) || origin.y == ((player->pos.y) + 1)) {
        if (origin.x == (player->pos.x - 1) || origin.x == (player->pos.x + 1)) {
            return true;
    }
    }
    if (origin.x == (player->pos.x) || origin.x == ((player->pos.x) - 1) || origin.x == ((player->pos.x) + 1)){
        if (origin.y == (player->pos.y - 1) || origin.y == (player->pos.y + 1)) {
            return true;
        }
    }
    return false;
}

/* Combat history passed to record events that happen in combat. */
/* If player moves into monster, fight, count it as a move.*/
/* If player fires their ranged weapon, count it as a move. */
/* If legal move, move player. */
bool PlayerInput(int input, LogQueue *q, int n_monsters, int* playerRegen, int* manaRegen) {
    // Get new coordinates.
    Position newPos = { player->pos.y, player->pos.x };
    bool rangedAttack;

    switch(input) {
        case 32: // space bar
            return true;
        case KEY_UP:
            newPos.y--;
            MovePlayer(newPos, combatHistory);
            return true;
        //move down
        case KEY_DOWN:
            newPos.y++;
            MovePlayer(newPos, combatHistory);
            return true;
        //move left
        case KEY_LEFT:
            newPos.x--;
            MovePlayer(newPos, combatHistory);
            return true;
        //move right
        case KEY_RIGHT:
            newPos.x++;
            MovePlayer(newPos, combatHistory);
            return true;
        //move up and left with insert
        case KEY_HOME:
            newPos.y--;
            newPos.x--;
            MovePlayer(newPos, combatHistory);
            return true;
        //move down and left with End
        case KEY_END:
            newPos.y++;
            newPos.x--;
            MovePlayer(newPos, combatHistory);
            return true;
        //move down and right with pagedown
        case KEY_NPAGE:
            newPos.y++;
            newPos.x++;
            MovePlayer(newPos, combatHistory);
            return true;
        //move up and right with pageup
        case KEY_PPAGE:
            newPos.y--;
            newPos.x++;
            MovePlayer(newPos, combatHistory);
            return true;
        case 1005: // keypad center
            return true;
        case 1040: // keypad center
            return true;
        case 102: // f key
            return PlayerRangedAttack(n_monsters);
        case 70: // F key
            return PlayerRangedAttack(n_monsters);
        case 49: // 1 key
            return UsePlayerAbility(n_monsters, ABILITY_1);
        case 50: // 2 key
            return UsePlayerAbility(n_monsters , ABILITY_2);
        case 51: // 3 key
            if (player->playerClass.abilities[ABILITY_3].abilityID > NO_ABILITY){
                    return UsePlayerAbility(n_monsters , ABILITY_3);
            }
            break;
        case 52: // 4 key
            if (player->playerClass.abilities[ABILITY_4].abilityID > NO_ABILITY){
                    return UsePlayerAbility(n_monsters , ABILITY_4);
            }
            break;
        case 53: // 5 key
            if (player->playerClass.abilities[ABILITY_5].abilityID > NO_ABILITY){
                    return UsePlayerAbility(n_monsters , ABILITY_5);
            }
            break;
        // case 65: // c key
        //     //Player menu function here
        //     break;
        // case 105: // i key
        //     break;
        // case 126:
        //     // RestUntilHealed(n_monsters, playerRegen, manaRegen);
        //     break;
        // case KEY_HOME: // debug
        //     player->playerStats.EXP += 90;
        //     break;
        // case 92: // debug
        //     player->playerStats.EXP += 90;
        //     break;
        default:
            break;
    }
    return false;
}

// Test for floor tile, move if one is detected.
void MovePlayer(Position newPos, CombatHistory* combatHistory) { 
    if (map[newPos.y][newPos.x].noCollision && !combatHistory->monsterKilled) {
        // Update FOV
        ClearFOV(player);
        player->pos.y = newPos.y;
        player->pos.x = newPos.x;
        MakeFOV(player);
        combatHistory->playerCombat = false;
        return;
    }
    // Attempted to move into monster, flag and prepare for combat.
    else if (map[newPos.y][newPos.x].isMonster && !combatHistory->monsterKilled){
        combatHistory->playerCombat = true;
        combatHistory->defender = map[newPos.y][newPos.x];
        return;
    }
    else if (!combatHistory->monsterKilled){
        combatHistory->monsterKilled = false;
        return;
    }

}

void RestUntilHealed(int n_monsters, int* playerRegen, int* manaRegen, bool PMove) {
    /* Check if player already is at full */
    if (player->playerStats.HP == player->playerStats.maxHP && player->playerStats.mana == player->playerStats.maxMana){
        strcpy(combatHistory->event, "You are already fully rested.");
        QueueEvent(q, combatHistory->event);
        return;
    }
    /* Check if in range of a visible monster. */
    for (int i = 0; i < n_monsters; i++){
        if((mptr + i)->visible && (mptr + i)->isMonster) {
            strcpy(combatHistory->event, "You cannot rest now, a");
            strcat(combatHistory->event, (mptr + i)->entityName);
            QueueEvent(q, combatHistory->event);
            strcpy(combatHistory->event, " lies to the ");
            strcpy(combatHistory->event, DIRECTIONS[MonsterDirection((mptr + i))]);
            strcat(combatHistory->event, ".");
            QueueEvent(q, combatHistory->event);
            return;
        }
    }
    char eventBuffer[TURN_BUFFER];
    int turnCount = 0;
    player->isResting = true;
    bool moveMonsters = false;
    PMove = true;
    while(player->isResting) {
        PMove = true;  
        PlayerRegen(playerRegen);
        PlayerRegen(playerRegen);
        PlayerRegen(playerRegen);
        ManaRegen(manaRegen);
        ManaRegen(manaRegen);
        ManaRegen(manaRegen);
        moveMonsters = MoveMonsterLoop(mptr, n_monsters, PMove);
        CheckPassiveAbilities(n_monsters);
        UpdateMonsterMap(mptr, n_monsters);
        ResetMoveFlags(mptr, n_monsters); 
        turnCount++;
        if(player->playerStats.HP == player->playerStats.maxHP && player->playerStats.mana == player->playerStats.maxMana){
            player->isResting = false;
        }
    }
    strcpy(combatHistory->event, "You finish resting.");
    QueueEvent(q, combatHistory->event);
    snprintf(eventBuffer, sizeof(eventBuffer), "%d ", turnCount);
    strcpy(combatHistory->event, eventBuffer);
    strcat(combatHistory->event, "turns have passed.");
    QueueEvent(q, combatHistory->event);
    RefreshGamestate(mptr, n_monsters);
    PMove = false;  
}

void PlayerRegen(int *playerRegen){
        if (*playerRegen >= 20 && (player->playerStats.HP < player->playerStats.maxHP)) {
            player->playerStats.HP++;
            *playerRegen = 0;
        }
        else{
            ++*playerRegen;
        }

}

void ManaRegen(int *manaRegen){
        if (*manaRegen >= 15 && (player->playerStats.mana < player->playerStats.maxMana)) {
            player->playerStats.mana++;
            *manaRegen = 0;
        }
        else{
            ++*manaRegen;
        }

}


/* Run FindClosestUnexplored, break if it returns a monster. */
/* return true if monster was found immediately and broke */
/* return false if monster was found or no more to explore */
// bool AutoExplore(CombatHistory* combatHistory){
//     bool playerMoved = false;
//     Position newPos = { player->pos.y, player->pos.x };
//     // Position targetPos = FindClosestUnexplored();
//     // if(map[targetPos.y][targetPos.x].entityID > 1) {
//     //         playerMoved = true;
//     //     }
//     if (!playerMoved) {
//         targetPos = FindClosestDoor();
        
//         if (map[(player->pos.y) - 1][(player->pos.x) - 1].noCollision && targetPos.x < player->pos.x && targetPos.y < player->pos.y){
//             newPos.x--;
//             newPos.y--;
//             MovePlayer(newPos, combatHistory);
//             playerMoved = true;
//         }
//         else if (map[(player->pos.y) + 1][(player->pos.x) - 1].noCollision && targetPos.x < player->pos.x && targetPos.y > player->pos.y){
//             newPos.x--;
//             newPos.y++;
//             MovePlayer(newPos, combatHistory);
//             playerMoved = true;
//         }
//         else if (map[(player->pos.y) + 1][(player->pos.x) + 1].noCollision && targetPos.x > player->pos.x && targetPos.y > player->pos.y){
//             newPos.x++;
//             newPos.y++;
//             MovePlayer(newPos, combatHistory);
//             playerMoved = true;
//         }
//         else if (map[(player->pos.y) - 1][(player->pos.x) + 1].noCollision && targetPos.x > player->pos.x && targetPos.y < player->pos.y){
//             newPos.x++;
//             newPos.y--;
//             MovePlayer(newPos, combatHistory);
//             playerMoved = true;
//         }
//         else if (map[(player->pos.y) - 1][player->pos.x].noCollision && targetPos.y < player->pos.y){
//             newPos.y--;
//             MovePlayer(newPos, combatHistory);
//             playerMoved = true;
//         }
//         else if (map[(player->pos.y) + 1][player->pos.x].noCollision && targetPos.y > player->pos.y){
//             newPos.y++;
//             MovePlayer(newPos, combatHistory);
//             playerMoved = true;
//         }
//         else if (map[player->pos.y][(player->pos.x) - 1].noCollision && targetPos.x < player->pos.x){
//             newPos.x--;
//             MovePlayer(newPos, combatHistory);
//             playerMoved = true;
//         }
//         else if (map[player->pos.y][(player->pos.x) + 1].noCollision && targetPos.x > player->pos.x){
//             newPos.x++;
//             MovePlayer(newPos, combatHistory);
//             playerMoved = true;
//         }
//         playerMoved = true;
//     }


// }
    


