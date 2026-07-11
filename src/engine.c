#include <rogue.h>

bool NcursesSetup(void) { 
    /* Makes escape key press register instantly.*/
    setenv("ESCDELAY", "25", 1);
    /* Starts Ncurses. */
    initscr();
    /* Disable Ncurses from immediately drawing to the screen. */ 
    noecho();
    /* Make cursor invisible. */ 
    curs_set(0);
    /* Add color to the console! */
    if (has_colors()) {
        start_color();
        init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
        init_pair(HIGHLIGHT_COLOR, COLOR_BLACK, COLOR_WHITE);
        return true;
    }
    else {
        mvprintw(20, 50, "Console does not have color support. Please use another console.");
        getch();
        return false;
    }
}

/* Moves monsters, returns false unless player dies.*/
bool MoveMonsterLoop(Entity* mptr, int n_monsters, bool PMove){
    int i = 0;
    bool monsterCombat;
    /* Wander checks if LOS to player and flips aggro is they are in range.*/
    while (!((mptr + i)->hasMoved) && i < n_monsters && PMove == true){
        /* Check if player is in aggro range. */
        if(!((mptr + i)->aggroFlag)){
            (mptr + i)->aggroFlag = CheckAggro((mptr + i), player);
        }

        /* If no adjacent Player, Wander.*/
        if (!CheckPlayerAdjacent((mptr + i)->pos) && !((mptr + i)->aggroFlag) && (mptr + i)->entityType == MONSTER){
            Wander(mptr + i);
            i++;
        }
        /* If adjacent to player, attack them in melee.*/
        else if (CheckPlayerAdjacent((mptr + i)->pos) == true && (mptr + i)->entityType == MONSTER){
            monsterCombat = AttackPlayer((mptr + i), combatHistory, player);
            /* If monsterCombat = false, player died, end the game.*/
            if (monsterCombat == false) {
                return true;
            }
            i++;
        }
        /* If in range of player and have a ranged weapon equipped, attack them at range.*/
        else if (((mptr + i)->entityWeapon.isRanged) &&
        (GetDistance((mptr + i)->pos, player->pos) <= (mptr + i)->entityWeapon.range) &&
        (LineOfSight((mptr + i)->pos, player->pos)) &&
        ((mptr + i)->entityType == MONSTER)){
            monsterCombat = AttackPlayer((mptr + i), combatHistory, player);
            /* If monsterCombat = false, player died, end the game.*/
            if (monsterCombat == false) {
                return true;
            }
            i++;
        }
        /* If player was seen, move towards player.*/
        else if (((mptr + i)->aggroFlag) && ((mptr + i)->entityType == MONSTER)){
            /* Move towards players last known locations.*/
            AggroMove(mptr + i);
            i++;
        }
        else {
            i++;
        }
    }
    return false;
}

/* 
Updates the monsters info, playersFOV, draws the updated info of both.
It then resets the monsters moveflags and games combatHistory.
*/
void RefreshGamestate(Entity* mptr, int n_monsters) {
    UpdateMonsterMap(mptr, n_monsters);
    MakeFOV(player);
    DrawEverything();
    UpdateNPCMap(nptr, MAX_ONSCREEN_NPCS);
    // UpdateNPCVisible(nptr, player);
    // DrawDebug(mptr, n_monsters); // Toggle if you would like to see the debugger!
    ResetMoveFlags(mptr, n_monsters);
    ResetCombatHistory();
    player->follower.hasMoved = false;
}

void GameLoop(CombatHistory* combatHistory, int n_monsters, LogQueue *q, Item* items) { 
    bool leaveFlag = false;
    bool PMove = false;
    bool escPressed = false;
    int ch, next_ch;
    int playerRegen = 0;
    int manaRegen = 0;

    Greeting();
    RefreshGamestate(mptr, n_monsters);
    DrawPlayerBlink(player);
    
    while(!leaveFlag){ 
        ch = getch();
        escPressed = CheckEscape(ch);
        if(escPressed){
            leaveFlag = MakePauseMenu();
        }
        PMove = false;
        if (ch == 105 || ch == 73) {
            MakeInventoryMenu();
            if(map[player->pos.y][player->pos.x].wasLooted){
                Entity* entityToUpdate = FindMonsterInList(map[player->pos.y][player->pos.x].entityID, n_monsters);
                entityToUpdate = &map[player->pos.y][player->pos.x];
            }
        }
        if(ch != ERR) {
            if (ch == 96) {
                RestUntilHealed(n_monsters, &playerRegen, &manaRegen, PMove);
                player->isResting = false;
            }
            else {
                PlayerRegen(&playerRegen);
                ManaRegen(&manaRegen);
                PMove = PlayerInput(ch, q, &n_monsters, &playerRegen, &manaRegen);
                if (combatHistory->playerCombat) {
                    PlayerPrepareCombat(n_monsters);
                    PostCombatEffects();
                    PMove = true;
                }
                if(MoveMonsterLoop(mptr, n_monsters, PMove)){
                    leaveFlag = true;
                }
            }
        }
        CheckPassiveAbilities(n_monsters);
        RefreshGamestate(mptr, n_monsters);
        PMove = false;  
    }
    Gameover();
}

void Gameover() {
    clear();
    keypad(stdscr, TRUE);
    mvprintw(20, 40, "Game Over.");
    getch();
}

/* Free memory allocated by pointer. */
void CloseGame(void) { 
    free(dungeonInfo);
    free(items);
    free(q);
    free(combatHistory);
    free(player);
    free(mptr);
    free(nptr);
    free(npcs);
    endwin();

} 

void Greeting(){
    strcpy(combatHistory->event, "Welcome to the dungeon,");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, player->playerName);
    strcat(combatHistory->event, "!");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, "Use arrow keys to move & fight.");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, "Press 'F' + 'Space' to use ranged.");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, "Use keys 1-5 + 'Space' to use abilities.");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, "Press '~' to rest and regain HP/Mana.");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, "Press 'I' to open your inventory.");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, "Press 'Space' to loot tiles with items.");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, "Press ESC to open the pause menu.");
    QueueEvent(q, combatHistory->event);
}
