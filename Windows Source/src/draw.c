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
  for (int y = 0; y < MAP_HEIGHT y++)
  { 
    for (int x = 0; x < MAP_WIDTH; x++)
    { 
        if (map[y][x].visible) {
			if (map[y][x].color == BLOOD_COLOR && map[y][x].miscTimer > 0) {
				mvaddch(y, x, map[y][x].ch | COLOR_PAIR(BLOOD_COLOR) | A_DIM);
				map[y][x].miscTimer--;
			}
			else if (map[y][x].color == CHEST_COLOR) {
				mvaddch(y, x, map[y][x].ch | COLOR_PAIR(CHEST_COLOR) | A_DIM);
			}
			else mvaddch(y, x, map[y][x].ch | COLOR_PAIR(VISIBLE_COLOR));
        	if(map[y][x].entityType == FLOOR && map[y][x].color != BLOOD_COLOR){
        		if(map[y][x].inventory[0].itemID != NULL_ITEM_ID) mvaddch(y, x, map[y][x].ch | COLOR_PAIR(VISIBLE_COLOR) | A_DIM);
        	}
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
	mvaddch(player->pos.y, player->pos.x, (chtype)(player->ch | COLOR_PAIR(VISIBLE_COLOR) | A_BOLD));
  refresh();
	} 

/* Makes the players avatar blink when called.*/
void DrawPlayerBlink(Player* player) { 
	// attron(A_STANDOUT);
	mvaddch(player->pos.y, player->pos.x, (chtype)(player->ch | COLOR_PAIR(HIGHLIGHT_COLOR) | A_BLINK));
  refresh();
	// attroff(A_STANDOUT); 
	}  

/* Draws equipped items.*/
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

/* Draw the players stats like INT, HP, EXP, LVL, etc.*/
void DrawPlayerStats() {

  int EXPLen = GetNumberOfDigits(player->playerStats.EXP);
  int nextEXPLen = GetNumberOfDigits(player->playerStats.nextLVLEXP);
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
  mvprintw(18, STATS_COL2, "FLR: %d", dungeonInfo->currentFloor);
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

/* Splatters the target across the map, yay! */
void BloodSplatter(Position origin, Position target) {
	int dir = (rand() % 3) + 1;
	map[target.y][target.x].color = BLOOD_COLOR;
	map[target.y][target.x].miscTimer = (rand() % 30) + 10;
    if ((target.x) < (origin.x) && (target.y) < (origin.y)) {
		BloodSE(origin, target, dir);
    }
    else if ((target.x) < (origin.x) && (target.y) > (origin.y)) {
		BloodNE(origin, target, dir);	
    }
    else if ((target.x) > (origin.x) && (target.y) > (origin.y)) {
		BloodNW(origin, target, dir);
    }
    else if ((target.x) > (origin.x) && (target.y) < (origin.y)) {
		BloodSW(origin, target, dir);
    }
    else if ((target.x) < (origin.x) && (target.y) == (origin.y)) {
		BloodE(origin, target, dir);
    }
    else if ((target.x) > (origin.x) && (target.y) == (origin.y)) {
		BloodW(origin, target, dir);
    }
    else if ((target.x) == (origin.x) && (target.y) < (origin.y)) {
		BloodS(origin, target, dir);
    }
    else if ((target.x) == (origin.x) && (target.y) > (origin.y)) {
		BloodN(origin, target, dir);
	}
}

/* Splatters the target across the map, yay! */
void CritBloodSplatter(Position origin, Position target) {
	map[target.y][target.x].color = BLOOD_COLOR;
	map[target.y][target.x].miscTimer = (rand() % 30) + 10;
    if((target.x) < (origin.x) && (target.y) < (origin.y)) {
		map[(target.y) - 1][(target.x) - 1].color = BLOOD_COLOR;
		map[target.y][(target.x) - 1].color = BLOOD_COLOR;
		map[target.y][(target.x) - 1].color = BLOOD_COLOR;
		map[(target.y) - 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
		map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
		map[(target.y - 1)][target.x].miscTimer = (rand() % 30) + 10;
    }
    else if ((target.x) < (origin.x) && (target.y) > (origin.y)) {
		map[(target.y) + 1][(target.x) - 1].color = BLOOD_COLOR;
		map[target.y][(target.x) - 1].color = BLOOD_COLOR;
		map[(target.y) + 1][target.x].color = BLOOD_COLOR;
		map[(target.y) + 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
		map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
		map[(target.y) + 1][target.x].miscTimer = (rand() % 30) + 10;
    }
    else if ((target.x) > (origin.x) && (target.y) > (origin.y)) {
		map[(target.y) + 1][(target.x) + 1].color = BLOOD_COLOR;
		map[target.y][(target.x) + 1].color = BLOOD_COLOR;
		map[(target.y) + 1][target.x].color = BLOOD_COLOR;
		map[(target.y) + 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
		map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
		map[(target.y) + 1][target.x].miscTimer = (rand() % 30) + 10;
    }
    else if ((target.x) > (origin.x) && (target.y) < (origin.y)) {
		map[(target.y) - 1][(target.x) + 1].color = BLOOD_COLOR;
		map[target.y][(target.x) + 1].color = BLOOD_COLOR;
		map[(target.y) - 1][target.x].color = BLOOD_COLOR;
		map[(target.y) - 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
		map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
		map[(target.y) - 1][target.x].miscTimer = (rand() % 30) + 10;
    }
    else if ((target.x) < (origin.x) && (target.y) == (origin.y)) {
		map[(target.y) - 1][(target.x) - 1].color = BLOOD_COLOR;
		map[target.y][(target.x) - 1].color = BLOOD_COLOR;
		map[(target.y) + 1][(target.x) - 1].color = BLOOD_COLOR;
		map[(target.y) - 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
		map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
		map[(target.y) + 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
    }
    else if ((target.x) > (origin.x) && (target.y) == (origin.y)) {
		map[(target.y) - 1][(target.x) + 1].color = BLOOD_COLOR;
		map[target.y][(target.x) + 1].color = BLOOD_COLOR;
		map[(target.y) + 1][(target.x) + 1].color = BLOOD_COLOR;
		map[(target.y) - 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
		map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
		map[(target.y) + 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
    }
    else if ((target.x) == (origin.x) && (target.y) < (origin.y)) {
		map[(target.y) - 1][(target.x) + 1].color = BLOOD_COLOR;
		map[(target.y) - 1][target.x].color = BLOOD_COLOR;
		map[(target.y) - 1][(target.x) - 1].color = BLOOD_COLOR;
		map[(target.y) - 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
		map[(target.y) - 1][target.x].miscTimer = (rand() % 30) + 10;
		map[(target.y) - 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
    }
    else if ((target.x) == (origin.x) && (target.y) > (origin.y)) {
		map[(target.y) + 1][(target.x) + 1].color = BLOOD_COLOR;
		map[(target.y) + 1][target.x].color = BLOOD_COLOR;
		map[(target.y) + 1][(target.x) - 1].color = BLOOD_COLOR;
		map[(target.y) + 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
		map[(target.y) + 1][target.x].miscTimer = (rand() % 30) + 10;
		map[(target.y) + 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
	}
}

void BloodSE(Position origin, Position target, int dir){
	switch (dir) {
		case 1:
			map[(target.y) - 1][(target.x) - 1].color = BLOOD_COLOR;
			map[target.y][(target.x) - 1].color = BLOOD_COLOR;
			map[(target.y) - 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			break;
		case 2:
			map[target.y][(target.x) - 1].color = BLOOD_COLOR;
			map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			break;
		case 3:
			map[target.y][(target.x) - 1].color = BLOOD_COLOR;
			map[(target.y) - 1][(target.x) - 1].color = BLOOD_COLOR;
			map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			map[(target.y) - 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			break;
		default:
			break;
	}
}
void BloodNE(Position origin, Position target, int dir){
	switch (dir) {
		case 1:
			map[(target.y) + 1][(target.x) - 1].color = BLOOD_COLOR;
			map[target.y][(target.x) - 1].color = BLOOD_COLOR;
			map[(target.y) + 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			break;
		case 2:
			map[target.y][(target.x) - 1].color = BLOOD_COLOR;
			map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			break;
		case 3:
			map[target.y][(target.x) - 1].color = BLOOD_COLOR;
			map[(target.y) + 1][target.x].color = BLOOD_COLOR;
			map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			map[(target.y) + 1][target.x].miscTimer = (rand() % 30) + 10;
			break;
		default:
			break;
	}
}
void BloodNW(Position origin, Position target, int dir){
	switch (dir) {
		case 1:
			map[(target.y) + 1][(target.x) + 1].color = BLOOD_COLOR;
			map[target.y][(target.x) + 1].color = BLOOD_COLOR;
			map[(target.y) + 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			break;
		case 2:
			map[target.y][(target.x) + 1].color = BLOOD_COLOR;
			map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			break;
		case 3:
			map[target.y][(target.x) + 1].color = BLOOD_COLOR;
			map[(target.y) + 1][target.x].color = BLOOD_COLOR;
			map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			map[(target.y) + 1][target.x].miscTimer = (rand() % 30) + 10;
			break;
		default:
			break;
	}
}
void BloodSW(Position origin, Position target, int dir){
	switch (dir) {
		case 1:
			map[(target.y) - 1][(target.x) + 1].color = BLOOD_COLOR;
			map[target.y][(target.x) + 1].color = BLOOD_COLOR;
			map[(target.y) - 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			break;
		case 2:
			map[target.y][(target.x) + 1].color = BLOOD_COLOR;
			map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			break;
		case 3:
			map[target.y][(target.x) + 1].color = BLOOD_COLOR;
			map[(target.y) - 1][target.x].color = BLOOD_COLOR;
			map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			map[(target.y) - 1][target.x].miscTimer = (rand() % 30) + 10;
			break;
		default:
			break;
	}
}
void BloodE(Position origin, Position target, int dir){
	switch (dir) {
		case 1:
			map[(target.y) - 1][(target.x) - 1].color = BLOOD_COLOR;
			map[target.y][(target.x) - 1].color = BLOOD_COLOR;
			map[(target.y) - 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			break;
		case 2:
			map[target.y][(target.x) - 1].color = BLOOD_COLOR;
			map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			break;
		case 3:
			map[target.y][(target.x) - 1].color = BLOOD_COLOR;
			map[(target.y) + 1][(target.x) - 1].color = BLOOD_COLOR;
			map[target.y][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			map[(target.y) + 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			break;
		default:
			break;
	}
}
void BloodW(Position origin, Position target, int dir){
	switch (dir) {
		case 1:
			map[(target.y) - 1][(target.x) + 1].color = BLOOD_COLOR;
			map[target.y][(target.x) + 1].color = BLOOD_COLOR;
			map[(target.y) - 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			break;
		case 2:
			map[target.y][(target.x) + 1].color = BLOOD_COLOR;
			map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			break;
		case 3:
			map[target.y][(target.x) + 1].color = BLOOD_COLOR;
			map[(target.y) + 1][(target.x) + 1].color = BLOOD_COLOR;
			map[target.y][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			map[(target.y) + 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			break;
		default:
			break;
	}
}
void BloodS(Position origin, Position target, int dir){
	switch (dir) {
		case 1:
			map[(target.y) - 1][(target.x) + 1].color = BLOOD_COLOR;
			map[(target.y) - 1][target.x].color = BLOOD_COLOR;
			map[(target.y) - 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			map[(target.y) - 1][target.x].miscTimer = (rand() % 30) + 10;
			break;
		case 2:
			map[(target.y) - 1][target.x].color = BLOOD_COLOR;
			map[(target.y) - 1][target.x].miscTimer = (rand() % 30) + 10;
			break;
		case 3:
			map[(target.y) - 1][target.x].color = BLOOD_COLOR;
			map[(target.y) - 1][(target.x) - 1].color = BLOOD_COLOR;
			map[(target.y) - 1][target.x].miscTimer = (rand() % 30) + 10;
			map[(target.y) - 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			break;
		default:
			break;
	}
}
void BloodN(Position origin, Position target, int dir){
	switch (dir) {
		case 1:
			map[(target.y) + 1][(target.x) + 1].color = BLOOD_COLOR;
			map[(target.y) + 1][target.x].color = BLOOD_COLOR;
			map[(target.y) + 1][(target.x) + 1].miscTimer = (rand() % 30) + 10;
			map[(target.y) + 1][target.x].miscTimer = (rand() % 30) + 10;
			break;
		case 2:
			map[(target.y) + 1][target.x].color = BLOOD_COLOR;
			map[(target.y) + 1][target.x].miscTimer = (rand() % 30) + 10;
			break;
		case 3:
			map[(target.y) + 1][target.x].color = BLOOD_COLOR;
			map[(target.y) + 1][(target.x) - 1].color = BLOOD_COLOR;
			map[(target.y) + 1][target.x].miscTimer = (rand() % 30) + 10;
			map[(target.y) + 1][(target.x) - 1].miscTimer = (rand() % 30) + 10;
			break;
		default:
			break;
	}
}

void DrawDebug(Entity* mptr, int n_monsters) {
  // Position closest = FindClosestUnexplored();
    // for (int i = 0; i < (MAX_ONSCREEN_NPCS) ; i++) {
    mvprintw(54, 2, "ATK %d, ACC:%d", player->playerStats.ATK, combatHistory->playerAccRoll);
    // mvprintw(i, 170, "NPC_ID: %d, nptr[i]: %d, followerID: %d POS_X:%d POS_Y:%d", nptr[i].entityID, i, player->follower.entityID, nptr[i].pos.x, nptr[i].pos.y);
	// mvprintw(52, 2, "Player POS x:%d, y:%d, Tail:%d, inv[0].ID:%d", player->pos.x, player->pos.y, player->invTail, player->inventory[0].itemID);
    // mvprintw(52, 2, "Armor Req:%d, Armor Stat:%d, Melee Req:%d, Ranged Req:%d", player->equippedArmor.statReq, player->equippedArmor.statUsed, player->equippedMelee.statReq, player->equippedRanged.statReq);
    // mvprintw(23 + i, 128, "Playerlast x:%d y:%d ", mptr[i].playerLastPos.x, mptr[i].playerLastPos.y);
    // mvprintw(53 + i, 2, "Mchar %c x:%d, y:%d ID:%d, Mapc:%c Tail:%d inv[0]ID:%d", mptr[i].ch, mptr[i].pos.x, mptr[i].pos.y, mptr[i].entityID, map[mptr[i].pos.y][mptr[i].pos.x].ch, mptr[i].invTail, mptr[i].inventory[0].itemID);
    // mvprintw(27 + i, 2, "ID %c x:%d, y:%d MapID:%d, Mapc:%c", ((mptr + i)->entityID), mptr[i].pos.x, mptr[i].pos.y, mptr[i].entityID, map[mptr[i].pos.y][mptr[i].pos.x].ch);
    // mvprintw(23 + i, 128, "isAggro: %d Range: %d Range: %d", mptr[i].aggroFlag, mptr[i].aggroRange, GetDistance(player->pos, (mptr + i)->pos));
	// mvprintw(30, 128, "CH: %c x:%d, y:%d ID:%d", combatHistory->defender.ch, combatHistory->defender.pos.x, combatHistory->defender.pos.y, combatHistory->defender.entityID);
    // mvprintw(47, 2, "CH:%c x:%d, y:%d ID:%d", combatHistory->defender.ch, combatHistory->defender.pos.x, combatHistory->defender.pos.y, combatHistory->defender.entityID);
    // mvprintw(27 + i, 2, "CH:%c x:%d, y:%d px:%d, py:%d AGR:%d ", mptr[i].ch, mptr[i].pos.x, mptr[i].pos.y, mptr[i].playerLastPos.x, mptr[i].playerLastPos.y, mptr[i].aggroFlag);
    // }
    // mvprintw(22, 128, "Closest Unexplored: %d, %d", closest.y, closest.x);
  
}

/* 
Draws the combatlog Queue to the rightmost display area under player's stats.
*/
void DrawCombatLog() {
 	if (IsEmpty(q)){
        return;
    }
    for (int i = 0; i <= q->rear; i++) {
    	mvprintw(LOG_HEIGHT + i, SIDEBAR_X, "%s", q->events[i]);
  	}
}

/*Draw Everything*/ 
//void DrawEverything(Entity* mptr, int n_monsters, CombatHistory* combatHistory) {
void DrawEverything() {
	erase();
	DrawMap();
	DrawPlayer(player);
	DrawPlayerEquipment();
	DrawPlayerStats();
	DrawAbilities();
	DrawCombatLog();
	DrawBorder();
}