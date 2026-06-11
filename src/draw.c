#include <rogue.h>

#define ABILITY_BAR_STARTX 2
#define ABILITIY_BAR_BUFFERX 12
#define ABILITY_BAR_Y (MAP_HEIGHT - 1)

/* Sidebar/layout helpers */
#define SIDEBAR_X (MAP_WIDTH + 2)
#define STATS_COL2 (SIDEBAR_X + 29)
#define STATS_WIDTH 40
#define RIGHT_BORDER (SIDEBAR_X + STATS_WIDTH)
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
  mvprintw(2, SIDEBAR_X, "Name: %s", player->playerName);
  mvprintw(4, SIDEBAR_X, "Race: %s", player->playerRace);
  mvprintw(6, SIDEBAR_X, "Class: %s", player->playerClass.className);
  mvprintw(8, SIDEBAR_X, "Armor: %s", player->equippedArmor.item.itemName);
  mvprintw(12, SIDEBAR_X, "Melee: %s", player->equippedMelee.item.itemName);
  mvprintw(14, SIDEBAR_X, "Ranged: %s", player->equippedRanged.item.itemName);
  // mvprintw(8, 128, "Armor: %s", player->equippedArmor.armorName);
  // mvprintw(12, 128, "Melee: %s", player->equippedMelee.weaponName);
  // mvprintw(14, 128, "Ranged: %s", player->equippedRanged.weaponName);
}

void DrawPlayerStats() {

  int EXPLen = NumberOfDigits(player->playerStats.EXP);
  int nextEXPLen = NumberOfDigits(player->playerStats.nextLVLEXP);
  int EXPbuffer = (EXPLen + nextEXPLen);
  mvprintw(10, SIDEBAR_X, "Armor Class: %d", (player->playerStats.AC) + 10);
  mvprintw(16, SIDEBAR_X, "HP: %d", player->playerStats.HP);
  if(player->playerClass.isCaster) {
    mvprintw(18, SIDEBAR_X, "Mana: %d", player->playerStats.mana);
  }
  else {
    mvprintw(18, SIDEBAR_X, "Energy: %d", player->playerStats.mana);
  }
  mvprintw(2, STATS_COL2, "LVL: %d", player->playerStats.LVL);
  mvprintw(4, STATS_COL2, "CHA: %d", player->playerStats.CHA);
  mvprintw(6, STATS_COL2, "CON: %d", player->playerStats.CON);
  mvprintw(8, STATS_COL2, "DEX: %d", player->playerStats.DEX);
  mvprintw(10, STATS_COL2, "INT: %d", player->playerStats.INT);
  mvprintw(12, STATS_COL2, "STR: %d", player->playerStats.STR);
  mvprintw(14, STATS_COL2, "WIS: %d", player->playerStats.WIS);
  mvprintw(16, STATS_COL2 + 1 - EXPbuffer, "EXP: %d/%d", player->playerStats.EXP, player->playerStats.nextLVLEXP);
}

/* Draw the players Abilities in the bottom left of screen. */
/*1: %s - %d |, 2: %s - %d |, etc, are ABILITY_BAR_BUFFERX*/
void DrawAbilities() { 
  int buffer;
  mvprintw(ABILITY_BAR_Y, ABILITY_BAR_STARTX, "1: %s - %d |", 
  player->playerClass.abilities[ABILITY_1].abilityName, 
  player->playerClass.abilities[ABILITY_1].manaCost);

  buffer = strlen(player->playerClass.abilities[ABILITY_1].abilityName) + ABILITIY_BAR_BUFFERX;
  mvprintw(ABILITY_BAR_Y, buffer, "2: %s - %d |", player->playerClass.abilities[ABILITY_2].abilityName,
  player->playerClass.abilities[ABILITY_2].manaCost);
  buffer -= ABILITY_BAR_STARTX;
  if (player->playerClass.abilities[ABILITY_3].abilityID > NO_ABILITY) {
    buffer += (strlen(player->playerClass.abilities[ABILITY_2].abilityName) + ABILITIY_BAR_BUFFERX);
    mvprintw(ABILITY_BAR_Y, buffer, 
    "3: %s - %d |", player->playerClass.abilities[ABILITY_3].abilityName,
    player->playerClass.abilities[ABILITY_3].manaCost);
  }
  if (player->playerClass.abilities[ABILITY_4].abilityID > NO_ABILITY){
    buffer += (strlen(player->playerClass.abilities[ABILITY_3].abilityName) + ABILITIY_BAR_BUFFERX);
    mvprintw(ABILITY_BAR_Y, buffer,
    "4: %s - %d |", player->playerClass.abilities[ABILITY_4].abilityName,
    player->playerClass.abilities[ABILITY_4].manaCost);
  } 
  if (player->playerClass.abilities[ABILITY_5].abilityID > NO_ABILITY) {
    buffer += (strlen(player->playerClass.abilities[ABILITY_4].abilityName) + ABILITIY_BAR_BUFFERX);
    mvprintw(ABILITY_BAR_Y, buffer,
    "5: %s - %d |", player->playerClass.abilities[ABILITY_5].abilityName,
    player->playerClass.abilities[ABILITY_5].manaCost);
  }
}


/* Draw a pretty border around the map and stats.*/
void DrawBorder(void) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    mvprintw(y, 0, "|");
    mvprintw(y, MAP_WIDTH, "|");
  }

  for (int x = 0; x <= MAP_WIDTH + 1; x++) {
    mvprintw(0, x, "=");
    mvprintw(MAP_HEIGHT, x, "=");
  }

  /* Internal borders for stats & abilites */
  for (int x = 0; x < STATS_WIDTH + 1; x++) {
    mvprintw(0, SIDEBAR_X + x, "=");
    mvprintw(20, SIDEBAR_X + x, "=");
    mvprintw(MAP_HEIGHT, SIDEBAR_X + x, "=");
  }

  for (int y = 1; y < MAP_HEIGHT; y ++) {
    mvprintw(y, RIGHT_BORDER, "|");
  }

  for (int x = 0; x < MAP_WIDTH; x++) {
    mvprintw(ABILITY_BAR_Y - 1, x, "=");
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
    	mvprintw(LOG_HEIGHT + i, SIDEBAR_X, "%s", q->events[i]);
  	}
}


void DrawPlayerInventory() {
    for(int i = player->invHead; i < player->invTail; i++) {
        mvprintw(26 + i, 2, "ItemID:%d, Item:%s", player->inventory[i].itemID, player->inventory[i].itemName);
    }
}

/*Draw Everything*/ 
//void DrawEverything(Entity* mptr, int n_monsters, CombatHistory* combatHistory) {
void DrawEverything() {
	clear();
	DrawMap();
	DrawPlayer(player);
	DrawBorder();
  DrawPlayerEquipment();
  DrawPlayerStats();
  DrawAbilities();
  // DrawPlayerInventory();
  // DrawDebug(mptr, n_monsters);
	DrawCombatLog();
}

