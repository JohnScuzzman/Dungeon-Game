#include <rogue.h>

Player* CreatePlayer(Position start_pos) {
    Player* player = calloc(1, sizeof(Player));
    player->noCollision = false;
    player->pos.y = start_pos.y;
    player->pos.x = start_pos.x;
    player->ch = '@';
    player->color = COLOR_PAIR(VISIBLE_COLOR);
    AssignFloor(start_pos.x, start_pos.y);
    return player;
}


/* checks if the player is adjacent to the passed coordinates. */
bool CheckPlayerAdjacent(Position origin) {
    if (origin.y == (player->pos.y))
    {
        if (origin.x == (player->pos.x - 1) || origin.x == (player->pos.x + 1)) {
            return true;
    }
    }
    if (origin.x == (player->pos.x)){
        if (origin.y == (player->pos.y - 1) || origin.y == (player->pos.y + 1)) {
        return true;
    }
    }
    return false;
}



// Decide what to do with input.
// Collision determined here as well.
bool PlayerInput(int input, CombatHistory* combatHistory) {
    // Get new coordinates.
    Position newPos = { player->pos.y, player->pos.x };

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
        case 102: // f key
            bool rangedAttack = PlayerRangedAttack();
            return rangedAttack;
        default:
            break;
            
    }
    return false;
}

// Test for floor tile, move if one is detected.
void MovePlayer(Position newPos, CombatHistory* combatHistory) { 
    Entity* monster;
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
    else if (map[newPos.y][newPos.x].entityID > 1 && !combatHistory->monsterKilled){
        combatHistory->playerCombat = true;
        combatHistory->defender = map[newPos.y][newPos.x];
        return;
    }
    else if (!combatHistory->monsterKilled){
        combatHistory->monsterKilled = false;
        return;
    }

}


