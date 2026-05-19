#include <rogue.h>

/* Draw the Map to the screen. */
void DrawMap()
{ 
  for (int y = 0; y < MAP_HEIGHT; y++)
  { 
    for (int x = 0; x < MAP_WIDTH; x++)
    { 
        if (map[y][x].visible) {
          mvaddch(y, x, map[y][x].ch | COLOR_PAIR(VISIBLE_COLOR));
        }
        else if (map[y][x].seen && map[y][x].entityID < 2){
          mvaddch(y, x, map[y][x].ch | COLOR_PAIR(SEEN_COLOR));
        }
        else if (map[y][x].seen && map[y][x].entityID > 1){
          mvaddch(y, x, '.' | COLOR_PAIR(SEEN_COLOR));
        }
        else if (!map[y][x].seen && map[y][x].entityID > 1){
          mvaddch(y, x, ' ' | COLOR_PAIR(SEEN_COLOR));
        }
        else {
          mvaddch(y, x, ' ');
        }
    } 
  } 
}
// void DrawMonsters(Entity* mptr, int n_rooms) {
//   for (int i = 0; i < n_rooms; i++)
//     { 
//       mvaddch(mptr->pos.y, mptr->pos.x, mptr->ch  | map[mptr->pos.y][mptr->pos.x].color);
//     } 
//   } 


/* Draw Player based on position. */
void DrawPlayer(Player* player) { 
  mvaddch(player->pos.y, player->pos.x, player->ch | player->color);
} 

/* Draw the players stats and equipment in the top right of screen. */
void DrawStats(Player* player) { 
  for (int x = 0; x < 41; x ++) {
    mvprintw(0, 126 + x, "=");
    mvprintw(20, 126 + x, "=");
    mvprintw(50, 126 + x, "=");
  }
  
  for (int y = 1; y < 50; y ++) {
    mvprintw(y, 166, "|");
  }

  mvprintw(2, 128, "Name: %s", player->playerName);
  mvprintw(4, 128, "Race: %s", player->playerRace);
  mvprintw(6, 128, "Class: %s", player->playerClass);
  mvprintw(8, 128, "Armor: %s", player->playerArmor);
  mvprintw(10, 128, "Armor Class: %d", player->playerAC);
  mvprintw(12, 128, "Weapon: %s", player->playerWeapon),
  mvprintw(14, 128, "Equipped Weapons Damage: %d-%d", player->playerMinDMG, player->playerMaxDMG);
  mvprintw(16, 128, "HP: %d", player->playerHP);
  mvprintw(18, 128, "LVL: %d", player->playerLVL);

  // mvprintw(5, 126, "HP: %d", player->&playerHP);

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


void DrawDebug(Entity* mptr, int n_rooms) {
  for (int i = 0; i < n_rooms ; i++) {
	  mvprintw(22, 128, "Player POS x:%d, y:%d", player->pos.x, player->pos.y);
    mvprintw(23 + i, 128, "Mchar %c x:%d, y:%d ID:%d, Mapc:%c", mptr[i].ch, mptr[i].pos.x, mptr[i].pos.y, mptr[i].entityID, map[mptr[i].pos.y][mptr[i].pos.x].ch);
  }
  
}

/*Draw Everything*/ 
void DrawEverything(Entity* mptr, int n_rooms) {
  clear();
  DrawMap();
  DrawPlayer(player);
  DrawStats(player);
  DrawBorder();
  DrawDebug(mptr, n_rooms);
} 
