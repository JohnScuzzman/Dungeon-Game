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
  mvprintw(8, 128, "Armor: %s", player->equippedArmor.armorName);
  mvprintw(10, 128, "Armor Class: %d", player->playerStats.AC);
  mvprintw(12, 128, "Equipped Melee: %s", player->equippedMelee.weaponName);
  mvprintw(14, 128, "Equipped Ranged: %s", player->equippedRanged.weaponName);
  mvprintw(16, 128, "HP: %d", player->playerStats.HP);
  
  mvprintw(2, 157, "LVL: %d", player->playerStats.LVL);
  mvprintw(4, 157, "CHA: %d", player->playerStats.CHA);
  mvprintw(6, 157, "CON: %d", player->playerStats.CON);
  mvprintw(8, 157, "DEX: %d", player->playerStats.DEX);
  mvprintw(10, 157, "INT: %d", player->playerStats.INT);
  mvprintw(12, 157, "STR: %d", player->playerStats.STR);
  mvprintw(14, 157, "WIS: %d", player->playerStats.WIS);

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


void DrawDebug(Entity* mptr, int n_monsters) {
  for (int i = 0; i < n_monsters ; i++) {
	  // mvprintw(22, 128, "Player POS x:%d, y:%d", player->pos.x, player->pos.y);
    // mvprintw(23 + i, 128, "Mchar %c x:%d, y:%d ID:%d, Mapc:%c", mptr[i].ch, mptr[i].pos.x, mptr[i].pos.y, mptr[i].entityID, map[mptr[i].pos.y][mptr[i].pos.x].ch);
    mvprintw(23 + i, 128, "isAggro: %d Range: %d Range: %d", mptr[i].aggroFlag, mptr[i].aggroRange, GetDistance(player->pos, (mptr + i)->pos));
	// mvprintw(30, 128, "CH: %c x:%d, y:%d ID:%d", combatHistory->defender.ch, combatHistory->defender.pos.x, combatHistory->defender.pos.y, combatHistory->defender.entityID);


  }
  
}

/*Draw Everything*/ 
void DrawEverything(Entity* mptr, int n_monsters, bool playerCombat, bool monsterCombat, CombatHistory* combatHistory) {
	clear();
	DrawMap();
	DrawPlayer(player);
	DrawStats(player);
	DrawBorder();
	// DrawDebug(mptr, n_monsters);
	if (monsterCombat){
		DrawEntityAttack(combatHistory->defender, combatHistory->entityResult);
	}
	if (playerCombat){
		DrawPlayerAttack(combatHistory->defender, combatHistory->playerResult);
	}
}

void DrawEntityAttack(Entity attacker, bool combatResult) {
	if (combatResult) {
		mvprintw(28, 128, "The %s rolls a %d", attacker.entityName, combatHistory->attackerAccRoll);
		mvprintw(29, 128, "And hits with a %s.", attacker.entityWeapon);
		mvprintw(30, 128, "dealing %d damage.", combatHistory->attackerDMG);
	}
	if (!combatResult){
		mvprintw(28, 128, "The: %s attacks.", attacker.entityName);
		mvprintw(29, 128, "The: %s misses with %d.", attacker.entityName, combatHistory->attackerAccRoll);
	}
}

void DrawPlayerAttack(Entity defender, bool combatResult) {
	if (combatResult) {
    mvprintw(24, 128, "You attack the %s", defender.entityName);
		mvprintw(23, 128, "You hit with a %d", combatHistory->playerAccRoll);
		mvprintw(25, 128, "dealing %d damage.", combatHistory->playerDMG);	
	}
	if (!combatResult) {
		mvprintw(23, 128, "You attack the %s.", defender.entityName);
		mvprintw(24, 128, "You miss with a %d.", combatHistory->playerAccRoll);
	}
	if (defender.entityID == 0) {
		mvprintw(26, 128, "You kill the %s", defender.entityName);
	}

}
