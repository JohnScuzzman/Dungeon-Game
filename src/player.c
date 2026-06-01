#include <rogue.h>

Player* CreatePlayer(Position start_pos) {
    Player* player = calloc(1, sizeof(Player));
    player->noCollision = false;
    player->abilityTimer = 0;
    player->pos.y = start_pos.y;
    player->pos.x = start_pos.x;
    player->ch = '@';
    player->color = COLOR_PAIR(VISIBLE_COLOR);
    AssignFloor(start_pos.x, start_pos.y);
    return player;
}

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
bool PlayerInput(int input, LogQueue *q, int n_monsters) {
    // Get new coordinates.
    Position newPos = { player->pos.y, player->pos.x };
    bool rangedAttack;

    switch(input) {
        case 32: // space bar
            return true;
            break;
        //move up
        case KEY_UP:
            newPos.y--;
            MovePlayer(newPos, combatHistory);
            return true;
            break;
        //move down
        case KEY_DOWN:
            newPos.y++;
            MovePlayer(newPos, combatHistory);
            return true;
            break;
        //move left
        case KEY_LEFT:
            newPos.x--;
            MovePlayer(newPos, combatHistory);
            return true;
            break;
        //move right
        case KEY_RIGHT:
            newPos.x++;
            MovePlayer(newPos, combatHistory);
            return true;
            break;
        //move up and left with insert
        case KEY_IC:
            newPos.y--;
            newPos.x--;
            MovePlayer(newPos, combatHistory);
            return true;
            break;
        //move down and left with End
        case KEY_DC:
            newPos.y++;
            newPos.x--;
            MovePlayer(newPos, combatHistory);
            return true;
            break;
        //move down and right with pagedown
        case KEY_NPAGE:
            newPos.y++;
            newPos.x++;
            MovePlayer(newPos, combatHistory);
            return true;
            break;
        //move up and right with pageup
        case KEY_PPAGE:
            newPos.y--;
            newPos.x++;
            MovePlayer(newPos, combatHistory);
            return true;
            break;
        case 102: // f key
            return PlayerRangedAttack(n_monsters);
        case 70: // F key
            return PlayerRangedAttack(n_monsters);
        case KEY_HOME:
            return true;
            break;
        case 49: // 1 key
            return UsePlayerAbility(n_monsters, Ability_1);
            break;
        case 50: // 2 key
            return UsePlayerAbility(n_monsters , Ability_2);
            break;
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
    // needed to make sure monsters still get to move if player kills something.
    if (target->isMonster) {
        combatHistory->playerCombat = AttackEntity(target, combatHistory, player);
    }
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
    if(combatHistory->playerUsedAbility){
        return ShootTargetWithAbility(x, y);
    }
    else{
        return ShootTarget(x, y);
    }
    
}

/* We use PlayerRangedAttack since melee abilities technically have a range of one.*/
/* A normal melee attack is made when a player simply moves into a monster.*/
/* Thus to differentiate a melee ability, we borrow the RangedAttack function. */
/* PlayerRanged is in combat.c and AbilityEffects is in abilities.c*/
bool UsePlayerAbility(int n_monsters, int chosenAbility) {
    combatHistory->playerUsedAbility = true;
    player->equippedAbility = player->playerClass.abilities[chosenAbility];
    if(player->equippedAbility.isAttack) {
        if(PlayerRangedAttack(n_monsters)) {
            if (player->equippedAbility.hasEffects) {
                AbilityEffects(player->equippedAbility.abilityID);
            }
            return true;
        }
        else{ 
            return false;
        }
    }
    else {
            AbilityEffects(player->equippedAbility.abilityID);
            return true;
        }
    return false;
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
    


