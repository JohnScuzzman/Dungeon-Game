#include <rogue.h>

#define ABILITY_BAR_STARTX 2
#define ABILITIY_BAR_BUFFERX 12
#define STATS_WIDTH 40
#define ABILITY_BAR_Y (LINES - 1)
#define QUEUE_START_Y 22

/* * DYNAMIC LAYOUT ENGINE
 * Instead of hardcoding, we compute coordinates relative to the screen dimensions
 */
static int camera_x = 0;
static int camera_y = 0;
static int current_map_view_width = 0;
static int current_map_view_height = 0;
static int dynamic_sidebar_x = 0;

void UpdateCameraAndLayout(void) {
    // 1. Determine how much room we have for the sidebar
    // Stats width is 40. Let's give the sidebar absolute priority on screen space.
    dynamic_sidebar_x = COLS - 42; 
    if (dynamic_sidebar_x > MAP_WIDTH + 2) {
        dynamic_sidebar_x = MAP_WIDTH + 2; // Cap it at its max beautiful layout size
    }

    // 2. The map gets whatever space is left over on the left side
    current_map_view_width = dynamic_sidebar_x - 2;
    if (current_map_view_width > MAP_WIDTH) current_map_view_width = MAP_WIDTH;

    // 3. Vertical layout allocation (Reserve 2 rows at bottom for abilities if needed)
    current_map_view_height = LINES - 4; 
    if (current_map_view_height > MAP_HEIGHT) current_map_view_height = MAP_HEIGHT;

    // 4. Center the camera viewport around the player's physical location
    camera_x = player->pos.x - (current_map_view_width / 2);
    camera_y = player->pos.y - (current_map_view_height / 2);

    // 5. Clamp the camera viewport bounds so we don't look into empty code void
    if (camera_x < 0) camera_x = 0;
    if (camera_y < 0) camera_y = 0;
    if (camera_x > MAP_WIDTH - current_map_view_width)   camera_x = MAP_WIDTH - current_map_view_width;
    if (camera_y > MAP_HEIGHT - current_map_view_height) camera_y = MAP_HEIGHT - current_map_view_height;
}

/* Draw the Map to the screen using our sliding camera viewport. */
void DrawMap()
{ 
  // We only iterate through what can physically fit on screen right now!
  for (int y = 0; y < current_map_view_height; y++)
  { 
    for (int x = 0; x < current_map_view_width; x++)
    { 
        // Translate screen coordinate to our internal large virtual map index
        int map_y = camera_y + y;
        int map_x = camera_x + x;
        
        if (map[map_y][map_x].visible) {
			    mvaddch(y + 1, x + 1, map[map_y][map_x].ch | COLOR_PAIR(VISIBLE_COLOR));

        	if(map[map_y][map_x].entityType == FLOOR){
        		if(map[map_y][map_x].inventory[0].itemID != NULL_ITEM_ID) mvaddch(y + 1, x + 1, map[map_y][map_x].ch | COLOR_PAIR(VISIBLE_COLOR) | A_DIM);
        	}
		    }
        else if (map[map_y][map_x].seen && map[map_y][map_x].entityID < 2){
          mvaddch(y + 1, x + 1, map[map_y][map_x].ch | COLOR_PAIR(SEEN_COLOR));
        }
        else if (map[map_y][map_x].seen && map[map_y][map_x].entityID > 1){
          mvaddch(y + 1, x + 1, '.' | COLOR_PAIR(SEEN_COLOR));
        }
        else if (!map[map_y][map_x].seen && map[map_y][map_x].entityID > 1){
          mvaddch(y + 1, x + 1, ' ' | COLOR_PAIR(SEEN_COLOR));
        }
        else {
          mvaddch(y + 1, x + 1, ' ');
        }
    } 
  } 
}

/* Draw Player adjusting for camera position offset */
void DrawPlayer(Player* player) { 
  int screen_x = (player->pos.x - camera_x) + 1;
  int screen_y = (player->pos.y - camera_y) + 1;

  // Only draw player if they are physically within our screen bounds
  if (screen_x > 0 && screen_x <= current_map_view_width && screen_y > 0 && screen_y <= current_map_view_height) {
      mvaddch(screen_y, screen_x, player->ch | player->color | A_BOLD | A_DIM);
  }
  refresh();
} 

void DrawPlayerBlink(Player* player) { 
  int screen_x = (player->pos.x - camera_x) + 1;
  int screen_y = (player->pos.y - camera_y) + 1;

  if (screen_x > 0 && screen_x <= current_map_view_width && screen_y > 0 && screen_y <= current_map_view_height) {
      mvaddch(screen_y, screen_x, player->ch | player->color | A_BOLD | A_DIM | A_BLINK);
  }
}

/* Draws equipped items based on dynamic layout anchor */
void DrawPlayerEquipment(){
  mvprintw(2, dynamic_sidebar_x, "Name: %s", player->playerName);
  mvprintw(4, dynamic_sidebar_x, "Race: %s", player->playerRace);
  mvprintw(6, dynamic_sidebar_x, "Class: %s", player->playerClass.className);
  mvprintw(8, dynamic_sidebar_x, "Armor: %s", player->equippedArmor.item.itemName);
  mvprintw(12, dynamic_sidebar_x, "Melee: %s", player->equippedMelee.item.itemName);
  mvprintw(14, dynamic_sidebar_x, "Ranged: %s", player->equippedRanged.item.itemName);
}

/* Draw the players stats adjusting columns dynamically */
void DrawPlayerStats() {
  int stats_col2 = dynamic_sidebar_x + 24; // shifted closer to look clean on tight layouts
  int EXPLen = GetNumberOfDigits(player->playerStats.EXP);
  int nextEXPLen = GetNumberOfDigits(player->playerStats.nextLVLEXP);
  int EXPbuffer = (EXPLen + nextEXPLen);

  mvprintw(10, dynamic_sidebar_x, "Armor Class: %d", (player->playerStats.AC) + 10);
  mvprintw(16, dynamic_sidebar_x, "HP: %d", player->playerStats.HP);
  if(player->playerClass.isCaster) {
    mvprintw(18, dynamic_sidebar_x, "Mana: %d", player->playerStats.mana);
  }
  else {
    mvprintw(18, dynamic_sidebar_x, "Energy: %d", player->playerStats.mana);
  }
  mvprintw(2, stats_col2, "LVL: %d", player->playerStats.LVL);
  mvprintw(4, stats_col2, "CHA: %d", player->playerStats.CHA);
  mvprintw(6, stats_col2, "CON: %d", player->playerStats.CON);
  mvprintw(8, stats_col2, "DEX: %d", player->playerStats.DEX);
  mvprintw(10, stats_col2, "INT: %d", player->playerStats.INT);
  mvprintw(12, stats_col2, "STR: %d", player->playerStats.STR);
  mvprintw(14, stats_col2, "WIS: %d", player->playerStats.WIS);
  mvprintw(16, stats_col2 + 1 - EXPbuffer, "EXP: %d/%d", player->playerStats.EXP, player->playerStats.nextLVLEXP);
  mvprintw(18, stats_col2, "FLR: %d", dungeonInfo->currentFloor);
}

void DrawCombatLog() {
  if (IsEmpty(q)){
        return;
  }
  // Let log draw starting below stats box bounding box
  for (int i = 0; i <= q->rear; i++) {
    mvprintw(LOG_HEIGHT + i, dynamic_sidebar_x, "%s", q->events[i]);
  }
}

void DrawAbilities() { 
  int ability_y = current_map_view_height + 2;
  int buffer;
  mvprintw(ability_y, 0, "|");
  mvprintw(ability_y, ABILITY_BAR_STARTX, "1: %s - %d |", 
  player->playerClass.abilities[ABILITY_1].abilityName, 
  player->playerClass.abilities[ABILITY_1].manaCost);

  buffer = strlen(player->playerClass.abilities[ABILITY_1].abilityName) + ABILITIY_BAR_BUFFERX;
  mvprintw(ability_y, buffer, "2: %s - %d |", player->playerClass.abilities[ABILITY_2].abilityName,
  player->playerClass.abilities[ABILITY_2].manaCost);
  buffer -= ABILITY_BAR_STARTX;
  if (player->playerClass.abilities[ABILITY_3].abilityID > NO_ABILITY) {
    buffer += (strlen(player->playerClass.abilities[ABILITY_2].abilityName) + ABILITIY_BAR_BUFFERX);
    mvprintw(ability_y, buffer, 
    "3: %s - %d |", player->playerClass.abilities[ABILITY_3].abilityName,
    player->playerClass.abilities[ABILITY_3].manaCost);
  }
  if (player->playerClass.abilities[ABILITY_4].abilityID > NO_ABILITY){
    buffer += (strlen(player->playerClass.abilities[ABILITY_3].abilityName) + ABILITIY_BAR_BUFFERX);
    mvprintw(ability_y, buffer,
    "4: %s - %d |", player->playerClass.abilities[ABILITY_4].abilityName,
    player->playerClass.abilities[ABILITY_4].manaCost);
  } 
  if (player->playerClass.abilities[ABILITY_5].abilityID > NO_ABILITY) {
    buffer += (strlen(player->playerClass.abilities[ABILITY_4].abilityName) + ABILITIY_BAR_BUFFERX);
    mvprintw(ability_y, buffer,
    "5: %s - %d |", player->playerClass.abilities[ABILITY_5].abilityName,
    player->playerClass.abilities[ABILITY_5].manaCost);
  }

  mvprintw(ability_y, current_map_view_width + 1, "|");
}

void DrawBorder(void) {
  int bottom_border = current_map_view_height + 3;
  // Draw box around dynamic map viewport
  for (int y = 0; y <= current_map_view_height + 1; y++) {
    mvprintw(y, 0, "|");
    mvprintw(y, current_map_view_width + 1, "|");
  }

  for (int x = 0; x <= current_map_view_width + 1; x++) {
    mvprintw(0, x, "=");
    mvprintw(bottom_border, x, "=");
  }

  int right_border_edge = dynamic_sidebar_x + STATS_WIDTH;

  // Draw box around dynamic sidebar panel
  for (int x = 0; x <= STATS_WIDTH; x++) {
    mvprintw(0, dynamic_sidebar_x + x, "=");
    mvprintw(20, dynamic_sidebar_x + x, "=");
    mvprintw(bottom_border, dynamic_sidebar_x + x, "=");
  }

  // Right border
  for (int y = 1; y <= current_map_view_height + 2; y++) {
    mvprintw(y, right_border_edge, "|");
  }

  // Bottom map border
  for (int x = 0; x < current_map_view_width + 1; x++) {
    mvprintw(current_map_view_height + 1, x, "=");
  }
}


void DrawPlayerInventory() {
    for(int i = player->invHead; i < player->invTail; i++) {
        mvprintw(26 + i, 2, "ItemID:%d, Item:%s", player->inventory[i].itemID, player->inventory[i].itemName);
    }
}

void DrawDebug(Entity* mptr, int n_monsters) {
  // Position closest = FindClosestUnexplored();
    for (int i = 0; i < (MAX_ONSCREEN_NPCS) ; i++) {
    // mvprintw(52, 2, "ATK %d, ACC:%d", player->playerStats.ATK, combatHistory->playerAccRoll);
    mvprintw(i, 170, "NPC_ID: %d, nptr[i]: %d, followerID: %d", nptr[i].entityID, i, player->follower.entityID);
	  // mvprintw(52, 2, "Player POS x:%d, y:%d, Tail:%d, inv[0].ID:%d", player->pos.x, player->pos.y, player->invTail, player->inventory[0].itemID);
    // mvprintw(52, 2, "Armor Req:%d, Armor Stat:%d, Melee Req:%d, Ranged Req:%d", player->equippedArmor.statReq, player->equippedArmor.statUsed, player->equippedMelee.statReq, player->equippedRanged.statReq);
    // mvprintw(23 + i, 128, "Playerlast x:%d y:%d ", mptr[i].playerLastPos.x, mptr[i].playerLastPos.y);
    // mvprintw(53 + i, 2, "Mchar %c x:%d, y:%d ID:%d, Mapc:%c Tail:%d inv[0]ID:%d", mptr[i].ch, mptr[i].pos.x, mptr[i].pos.y, mptr[i].entityID, map[mptr[i].pos.y][mptr[i].pos.x].ch, mptr[i].invTail, mptr[i].inventory[0].itemID);
    // mvprintw(27 + i, 2, "ID %c x:%d, y:%d MapID:%d, Mapc:%c", ((mptr + i)->entityID), mptr[i].pos.x, mptr[i].pos.y, mptr[i].entityID, map[mptr[i].pos.y][mptr[i].pos.x].ch);
    // mvprintw(23 + i, 128, "isAggro: %d Range: %d Range: %d", mptr[i].aggroFlag, mptr[i].aggroRange, GetDistance(player->pos, (mptr + i)->pos));
	  // mvprintw(30, 128, "CH: %c x:%d, y:%d ID:%d", combatHistory->defender.ch, combatHistory->defender.pos.x, combatHistory->defender.pos.y, combatHistory->defender.entityID);
    // mvprintw(47, 2, "CH:%c x:%d, y:%d ID:%d", combatHistory->defender.ch, combatHistory->defender.pos.x, combatHistory->defender.pos.y, combatHistory->defender.entityID);
    // mvprintw(27 + i, 2, "CH:%c x:%d, y:%d px:%d, py:%d AGR:%d ", mptr[i].ch, mptr[i].pos.x, mptr[i].pos.y, mptr[i].playerLastPos.x, mptr[i].playerLastPos.y, mptr[i].aggroFlag);
    }
    // mvprintw(22, 128, "Closest Unexplored: %d, %d", closest.y, closest.x);
  
}

void DrawEverything() {
  clear();
  
  // Force recalculating limits dynamically based on current window boundaries
  UpdateCameraAndLayout();
  
  DrawMap();
  DrawPlayer(player);
  DrawBorder();
  DrawPlayerEquipment();
  DrawPlayerStats();
  DrawAbilities();
	DrawCombatLog();
}

