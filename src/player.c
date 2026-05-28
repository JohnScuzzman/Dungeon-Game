#include <rogue.h>

Player* CreatePlayer(Position start_pos) {
    Player* player = calloc(1, sizeof(Player));
    player->noCollision = false;
    player->moveTowardsDoor = true;
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
    if (origin.x == (player->pos.x) || origin.x == ((player->pos.x) - 1) || origin.x == ((player->pos.y) + 1)){
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
            rangedAttack = PlayerRangedAttack(n_monsters);
            return rangedAttack;
        case 70: // F key
            rangedAttack = PlayerRangedAttack(n_monsters);
            return rangedAttack;
        case KEY_HOME:
            return true;
            break;
        case 104: // h key
        //DEBUG
            // player->playerStats.HP += 600;
            break;
        case 72: // H key
        //DEBUG
            // player->playerStats.HP += 600;
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
    


