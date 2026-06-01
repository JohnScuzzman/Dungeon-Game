#include <rogue.h>

#define ABILITY_BAR_STARTX 2
#define ABILITIY_BAR_BUFFERX 12
#define ABILITY_BAR_Y 49
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

/* Draw Player based on position. */
void DrawPlayer(Player* player) { 
	mvaddch(player->pos.y, player->pos.x, player->ch | player->color | A_BOLD | A_DIM);
  	refresh();
	} 

void DrawPlayerBlink(Player* player) { 
	// attron(A_STANDOUT);
	mvaddch(player->pos.y, player->pos.x, player->ch | player->color | A_BOLD | A_DIM | A_BLINK);
	// attroff(A_STANDOUT); 
	}  

void DrawPlayerEquipment(){
  mvprintw(2, 128, "Name: %s", player->playerName);
  mvprintw(4, 128, "Race: %s", player->playerRace);
  mvprintw(6, 128, "Class: %s", player->playerClass.className);
  mvprintw(8, 128, "Armor: %s", player->equippedArmor.armorName);
  mvprintw(12, 128, "Melee: %s", player->equippedMelee.weaponName);
  mvprintw(14, 128, "Ranged: %s", player->equippedRanged.weaponName);
}

void DrawPlayerStats() {
  mvprintw(10, 128, "Armor Class: %d", (player->playerStats.AC) + 10);
  mvprintw(16, 128, "HP: %d", player->playerStats.HP);
  if(player->playerClass.isCaster) {
    mvprintw(18, 128, "Mana: %d", player->playerStats.mana);
  }
  else {
    mvprintw(18, 128, "Energy: %d", player->playerStats.mana);
  }
  mvprintw(2, 157, "LVL: %d", player->playerStats.LVL);
  mvprintw(4, 157, "CHA: %d", player->playerStats.CHA);
  mvprintw(6, 157, "CON: %d", player->playerStats.CON);
  mvprintw(8, 157, "DEX: %d", player->playerStats.DEX);
  mvprintw(10, 157, "INT: %d", player->playerStats.INT);
  mvprintw(12, 157, "STR: %d", player->playerStats.STR);
  mvprintw(14, 157, "WIS: %d", player->playerStats.WIS);
  mvprintw(16, 157, "EXP: %d", player->playerStats.EXP);
}

/* Draw the players Abilities in the bottom left of screen. */
void DrawAbilities() { 
  mvprintw(ABILITY_BAR_Y, ABILITY_BAR_STARTX, "1: %s - %d |", 
  player->playerClass.abilities[Ability_1].abilityName, 
  player->playerClass.abilities[Ability_1].manaCost);

  mvprintw(ABILITY_BAR_Y, ABILITIY_BAR_BUFFERX +
  strlen(player->playerClass.abilities[Ability_1].abilityName), 
  "2: %s - %d |", player->playerClass.abilities[Ability_2].abilityName,
  player->playerClass.abilities[Ability_2].manaCost);
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

  /* Internal borders for stats & abilites */
  for (int x = 0; x < 41; x++) {
    mvprintw(0, 126 + x, "=");
    mvprintw(20, 126 + x, "=");
    mvprintw(50, 126 + x, "=");
  }
  
  for (int y = 1; y < 50; y ++) {
    mvprintw(y, 166, "|");
  }

  for (int x = 0; x < (MAP_WIDTH); x++) {
    mvprintw(48, x, "=");
  }

}

void DrawDebug(Entity* mptr, int n_monsters) {
  // Position closest = FindClosestUnexplored();
    for (int i = 0; i < n_monsters ; i++) {
	  mvprintw(26, 2, "Player POS x:%d, y:%d", player->pos.x, player->pos.y);
    // mvprintw(23 + i, 128, "Playerlast x:%d y:%d ", mptr[i].playerLastPos.x, mptr[i].playerLastPos.y);
    // mvprintw(23 + i, 128, "Mchar %c x:%d, y:%d ID:%d, Mapc:%c", mptr[i].ch, mptr[i].pos.x, mptr[i].pos.y, mptr[i].entityID, map[mptr[i].pos.y][mptr[i].pos.x].ch);
    // mvprintw(27 + i, 2, "ID %c x:%d, y:%d MapID:%d, Mapc:%c", ((mptr + i)->entityID), mptr[i].pos.x, mptr[i].pos.y, mptr[i].entityID, map[mptr[i].pos.y][mptr[i].pos.x].ch);
    // mvprintw(23 + i, 128, "isAggro: %d Range: %d Range: %d", mptr[i].aggroFlag, mptr[i].aggroRange, GetDistance(player->pos, (mptr + i)->pos));
	  // mvprintw(30, 128, "CH: %c x:%d, y:%d ID:%d", combatHistory->defender.ch, combatHistory->defender.pos.x, combatHistory->defender.pos.y, combatHistory->defender.entityID);
    // mvprintw(47, 2, "CH:%c x:%d, y:%d ID:%d", combatHistory->defender.ch, combatHistory->defender.pos.x, combatHistory->defender.pos.y, combatHistory->defender.entityID);
    mvprintw(27 + i, 2, "CH:%c x:%d, y:%d px:%d, py:%d AGR:%d ", mptr[i].ch, mptr[i].pos.x, mptr[i].pos.y, mptr[i].playerLastPos.x, mptr[i].playerLastPos.y, mptr[i].aggroFlag);
    }
    // mvprintw(22, 128, "Closest Unexplored: %d, %d", closest.y, closest.x);
  
}

void DrawCombatLog() {
 	if (IsEmpty(q)){
        return;
    }
	for (int i = 0; i <= q->rear; i++) {
   		mvprintw(LOG_HEIGHT + i, LOG_WIDTH, "%s", q->events[i]);
  	}
}

/*Draw Everything*/ 
void DrawEverything(Entity* mptr, int n_monsters, CombatHistory* combatHistory) {
	clear();
	DrawMap();
	DrawPlayer(player);
	DrawBorder();
  DrawPlayerEquipment();
  DrawPlayerStats();
  DrawAbilities();
  // DrawDebug(mptr, n_monsters);
	DrawCombatLog();
}

