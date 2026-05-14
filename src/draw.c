#include <rogue.h>

/* Draw the Map to the screen. */
void DrawMap(void)
{ 
  for (int y = 0; y < MAP_HEIGHT; y++)
  { 
    for (int x = 0; x < MAP_WIDTH; x++)
    { 
        if (map[y][x].visible)
        {
            mvaddch(y, x, map[y][x].ch | map[y][x].color);
        }
        else if (map[y][x].seen)
        {
            mvaddch(y, x, map[y][x].ch | COLOR_PAIR(SEEN_COLOR));
        }
        else
        {
            mvaddch(y, x, ' ');
        }
    } 
  } 
} 

/* Draw Entity based on position. */
void DrawEntity(Entity* entity) { 
  mvaddch(entity->pos.y, entity->pos.x, entity->ch | entity->color);
} 

/* Draw the players stats and equipment in the top right of screen. */
void DrawStats(Entity* entity) { 
  for (int x = 0; x < 41; x ++) {
    mvprintw(0, 126 + x, "=");
    mvprintw(20, 126 + x, "=");
    mvprintw(50, 126 + x, "=");
  }
  
  for (int y = 1; y < 50; y ++) {
    mvprintw(y, 166, "|");
  }

  mvprintw(2, 128, "Name: %s", entity->entityName);
  mvprintw(4, 128, "Race: %s", entity->entityRace);
  mvprintw(6, 128, "Class: %s", entity->entityClass);
  mvprintw(8, 128, "Armor: %s", entity->entityArmor);
  mvprintw(10, 128, "Armor Class: %d", entity->entityAC);
  mvprintw(12, 128, "Weapon: %s", entity->entityWeapon),
  mvprintw(14, 128, "Equipped Weapons Damage: %d-%d", entity->entityMinDMG, entity->entityMaxDMG);
  mvprintw(16, 128, "HP: %d", entity->entityHP);
  mvprintw(18, 128, "LVL: %d", entity->entityLVL);

  // mvprintw(5, 126, "HP: %d", entity->&entityHP);

} 

/* Draw a pretty border around the map and stats.*/
void DrawBorder(void) {

  for (int y = 0; y < MAP_HEIGHT; y++) {
    mvprintw(y, 0, "|");
    mvprintw(y, MAP_WIDTH, "|");
  }

  for (int x = 0; x <= MAP_WIDTH; x++) {
    mvprintw(0, x, "=");
    mvprintw(MAP_HEIGHT, x, "=");
  }

}

/*Draw Everything*/ 
void DrawEverything(void) {
  clear();
  DrawMap();
  DrawEntity(player);
  DrawStats(player);
  DrawBorder();
} 
