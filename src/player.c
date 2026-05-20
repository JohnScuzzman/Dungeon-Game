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
bool PlayerInput(int input) {
    // Get new coordinates.
    Position newPos = { player->pos.y, player->pos.x };

    switch(input) {
        //move up
        case 'A':
            newPos.y--;
            MovePlayer(newPos);
            return true;
            break;
        //move down
        case 'B':
            newPos.y++;
            MovePlayer(newPos);
            return true;
            break;
        //move left
        case 'D':
            newPos.x--;
            MovePlayer(newPos);
            return true;
            break;
        //move right
        case 'C':
            newPos.x++;
            MovePlayer(newPos);
            return true;
            break;
        default:
            break;
    }
    return false;
    
}

// Test for floor tile, move if one is detected.
void MovePlayer(Position newPos) { 
  if (map[newPos.y][newPos.x].noCollision) {
    // Update FOV
    ClearFOV(player);
    player->pos.y = newPos.y;
    player->pos.x = newPos.x;
    MakeFOV(player);
  }
}


