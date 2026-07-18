#include <rogue.h>

bool CheckAdjacent(Position origin, Position target) {
    if (origin.y == target.y || origin.y == (target.y - 1) || origin.y == (target.y + 1)) {
        if (origin.x == (target.x - 1) || origin.x == (target.x + 1)) {
            return true;
    }
    }
    if (origin.x == target.x || origin.x == (target.x - 1) || origin.x == (target.x + 1)){
        if (origin.y == (target.y - 1) || origin.y == (target.y + 1)) {
            return true;
        }
    }
    return false;
}

bool CheckMonsterAdjacent(Position origin, Entity* monster) {
    if(monster->entityType == CORPSE) return false;
    if (origin.y == monster->pos.y || origin.y == (monster->pos.y - 1) || origin.y == (monster->pos.y + 1)) {
        if (origin.x == (monster->pos.x - 1) || origin.x == (monster->pos.x + 1)) {
            return true;
    }
    }
    if (origin.x == monster->pos.x || origin.x == (monster->pos.x - 1) || origin.x == (monster->pos.x + 1)){
        if (origin.y == (monster->pos.y - 1) || origin.y == (monster->pos.y + 1)) {
            return true;
        }
    }
    return false;
}

/*
Helper method for Sort Inventory.
Currently not implemented but will be used later in conjuction with Q-sort.
*/
int CompareStrings(const void *a, const void *b) {
    const char *strA = *(const char **)a;
    const char *strB = *(const char **)b;

    return strcmp(strA, strB);
}

/* Used to count number of digits in a number.*/
int GetNumberOfDigits(int input) {
  int count;
  int temp = abs(input);
  // condition ? expression_if_true : expression_if_false, this one handles a zero input.
  count = (temp == 0) ? 0 : (int)log10(temp) + 1;
  return count;
}

/* Returns true if escape was passed in.*/
/* Usually the passed in int 'ch' will be from getch().*/
bool CheckEscape(int ch) {
    int next_ch;
    if (ch == 27) { 
            // check for escape.
            nodelay(stdscr, TRUE);
            next_ch = getch();
            nodelay(stdscr, FALSE);
        }
        if (next_ch == ERR) {
            return true;
        }
    return false;
}

/*
Highlights the coordinates at given, and the length you would like to highlight.
for example passing "41, 30, 20" would highlight the square at 41, 30, and then the 20 squares to the right of it.
*/
void Cursor(int x, int y, int length){
    //A_BLINK 
    mvchgat(x, y, length, (attr_t)A_REVERSE, (short)VISIBLE_COLOR, NULL);
}

void RemoveCursor(int x, int y, int length) {
    mvchgat(x, y, length, (attr_t)A_NORMAL, (short)0, NULL);
}

/*
Returns an integer between the given min and max number.
*/
int RandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void RecordEntitySeen(Entity* entity) {
    if(!entity->seenByPlayer && entity->entityID != player->follower.entityID){
        strcpy(combatHistory->event, "You see a ");
        strcat(combatHistory->event, entity->entityName);
        QueueEvent(q, combatHistory->event);
        strcpy(combatHistory->event, "to the ");
        strcat(combatHistory->event, DIRECTIONS[EntityDirection(entity)]);
        strcat(combatHistory->event, ".");
        QueueEvent(q, combatHistory->event);
        entity->seenByPlayer = true;
        player->isResting = false;
    }
}

/* Returns an int representing the entitys direction relative to the player. */
int EntityDirection(Entity* entity) {
    if((player->pos.x) < (entity->pos.x) && (player->pos.y) < (entity->pos.y)) {
        return SOUTH_EAST;
    }
    else if ((player->pos.x) < (entity->pos.x) && (player->pos.y) > (entity->pos.y)) {
        return NORTH_EAST;
    }
    else if ((player->pos.x) > (entity->pos.x) && (player->pos.y) > (entity->pos.y)) {
        return NORTH_WEST;
    }
    else if ((player->pos.x) > (entity->pos.x) && (player->pos.y) < (entity->pos.y)) {
        return SOUTH_WEST;
    }
    else if ((player->pos.x) < (entity->pos.x) && (player->pos.y) == (entity->pos.y)) {
        return EAST;
    }
    else if ((player->pos.x) > (entity->pos.x) && (player->pos.y) == (entity->pos.y)) {
        return WEST;
    }
    else if ((player->pos.x) == (entity->pos.x) && (player->pos.y) < (entity->pos.y)) {
        return SOUTH;
    }
    else if ((player->pos.x) == (entity->pos.x) && (player->pos.y) > (entity->pos.y)) {
        return NORTH;
    } else {
        // Should never occur
        return NORTH;
    }
}

/*
Tries to place the passed entity next to the player.
returns false if there is not a valid tile to place it.
*/
bool PlaceAdjacentToPlayer(Entity* entity) {
    Position closestTile = CheckAdjacentCollisions(player->pos);
    if (closestTile.x == entity->pos.x && closestTile.y == entity->pos.y) return false;
    entity->pos = closestTile;
    AssignFloor(entity->pos.x, entity->pos.y);
    return true;
}

/*
Attempts to find the closest adjacent tile without collision.
If fails, returns the original pos.
*/
Position CheckAdjacentCollisions(Position pos) { 
    int y = pos.y;
    int x = pos.x;  
    Position temp = pos;
    if (map[(y - 1)][(x - 1)].noCollision) {
        temp.x--;
        temp.y--;
        return temp;
    }
    else if (map[(y + 1)][(x - 1)].noCollision) {
        temp.x--;
        temp.y++;
        return temp;
    }
    else if (map[(y + 1)][(x + 1)].noCollision) {
        temp.x--;
        temp.y++;
        return temp;
    }
    else if (map[(y - 1)][(x + 1)].noCollision) {
        temp.x++;
        temp.y--;
        return temp;
    }
    if (map[(y - 1)][x].noCollision) {
        temp.y--;
        return temp;
    }
    else if (map[y][(x - 1)].noCollision) {
        temp.x--;
        return temp;
    }
    else if (map[(y + 1)][x].noCollision) {
        temp.y++;
        return temp;
    }
    else if (map[y][(x + 1)].noCollision) {
        temp.x++;
        return temp;
    }
    return temp;
}