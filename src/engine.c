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



void Cursor(int x, int y, int length){
    //A_BLINK 
    mvchgat(x, y, length, A_BOLD | A_STANDOUT | A_DIM, VISIBLE_COLOR, NULL);
}

void RemoveCursor(int x, int y, int length) {
    mvchgat(x, y, length, A_NORMAL, 0, NULL);
}

void GameLoop(Entity* mptr, CombatHistory* combatHistory, int n_monsters, LogQueue *q) { 
    bool leaveFlag = false;
    bool playerCombat = false;
    bool monsterCombat = false;
    bool PMove = false;
    bool isAggro = false;
    int ch, next_ch;
    int playerRegen = 0;
    MakeFOV(player);
    DrawEverything(mptr, n_monsters, playerCombat, monsterCombat, combatHistory);
    DrawPlayerBlink(player);

    // Force use of keyboard and disable mouse clicks.
    keypad(stdscr, TRUE);

    while(!leaveFlag)
    { 
        UpdateMonsterMap(mptr, n_monsters);
        ch = getch();
        if (ch == 27) { 
            // check for escape.
            nodelay(stdscr, TRUE);
            next_ch = getch();
            nodelay(stdscr, FALSE);
        }
        if (next_ch == ERR) {
            leaveFlag = true;
        }
        // Pmove = false spam here used to help force monsters to move once.
        PMove = false;
        playerCombat = false;
        monsterCombat = false;
        if(ch != ERR) {
            int i = 0;

            if (playerRegen >= 20) {
                player->playerStats.HP++;
                playerRegen = 0;
            }
            else{
                playerRegen++;
            }

            PMove = PlayerInput(ch, q, n_monsters);

            // Check if player tried to attack something.
            // Then check if they used a ranged or melee weapon
            // Set max and min DMG accoridingly and attack the monster.
            if (combatHistory->playerCombat) {
                PlayerMeleeOrRanged(player);
                Entity* target = FindMonsterInList(combatHistory->defender.entityID, n_monsters);
                if (target->isMonster) {
                    playerCombat = AttackEntity(target, combatHistory, player);
                }
                if(combatHistory->monsterKilled){
                    //Do something
                    UpdateMonsterMap(mptr, n_monsters);
                }
            }
            

            /* Wander fires first and moves monsters randomly*/
            /* Wander checks if LOS to player and flips aggro is they are in range.*/
            /* (mptr + i)->entityID > 1 ensures we iterate over corpses.*/ 
            while (!((mptr + i)->hasMoved) && i < n_monsters && PMove == true){

                /* Check if player is in aggro range. */
                (mptr + i)->aggroFlag = CheckAggro((mptr + i), player);

                /* If no adjacent Player, Wander.*/
                if (!CheckPlayerAdjacent((mptr + i)->pos) && (!(mptr + i)->aggroFlag) && (mptr + i)->isMonster == true){
                    Wander(mptr + i);
                    
                    /* If they move in range of the player, set aggro flag.*/
                    if (!isAggro){
                        (mptr + i)->aggroFlag = CheckAggro((mptr + i), player);
                    }
                    i++;
                }
                /* If adjacent to player, attack them.*/
                else if (CheckPlayerAdjacent((mptr + i)->pos) == true && (mptr + i)->isMonster == true){
                    // Change the 'false' to true later for a ranged attack.
                    monsterCombat = AttackPlayer((mptr + i), combatHistory, player);
                    if(!monsterCombat) {
                        leaveFlag = true;
                    }
                    i++;
                }
                /* If player was seen, move towards player.*/
                else if ((mptr +i)->playerLastPos.x != 0 && (mptr + i)->playerLastPos.y != 0 && (mptr + i)->isMonster == true){
                    /* Move towards players last known locations.*/
                    AggroMove(mptr + i);
                    i++;
                }
                else {
                    i++;
                }
                // UpdateMonsters(mptr, n_monsters);
            }
        }
        UpdateMonsterMap(mptr, n_monsters);
        ResetMoveFlags(mptr, n_monsters);
        MakeFOV(player);
        DrawEverything(mptr, n_monsters, playerCombat, monsterCombat, combatHistory);
        
        combatHistory->monsterKilled = false;
        // ResetCombatHistory(combatHistory);
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

void CloseGame(void) { 
    free(q);
    free(combatHistory);
    free(player);
    free(mptr);
    endwin();
    /* Free memory allocated by pointer. */
} 
