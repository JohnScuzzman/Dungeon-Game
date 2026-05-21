#include <rogue.h>

bool NcursesSetup(void) { 
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

void GameLoop(Entity* mptr, CombatHistory* combatHistory, int n_monsters) { 
    bool leaveFlag = false;
    bool playerCombat = false;
    bool monsterCombat = false;
    int ch, next_ch;
    MakeFOV(player);
    DrawEverything(mptr, n_monsters, playerCombat, monsterCombat, combatHistory);
    DrawPlayerBlink(player);
    bool PMove = false;
    keypad(stdscr, FALSE);
    while(!leaveFlag)
    { 
        UpdateMonsterMap(mptr, n_monsters);
        ch = getch();
        if (ch == 27) { 
            // check for esape.
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

            // Attempt to make game wait for player to take full turn.
            while(i == 0) {
                PMove = PlayerInput(ch, combatHistory);
                i = 1;
            }

            i = 0;

            // Check if player tried to attack something.
            if (combatHistory->playerCombat && combatHistory->defender.entityID > 1) {
                Entity* target = FindMonsterInList(combatHistory->defender.entityID, n_monsters);
                playerCombat = AttackEntity(target, combatHistory, player);
            }
            
            // If there is no adjacent player, move freely.
            while (!((mptr + i)->hasMoved) && i < n_monsters && PMove == true){
                if (!CheckPlayerAdjacent((mptr + i)->pos) && (mptr + i)->entityID > 1){
                    Wander(mptr + i);
                    i++;
                }
                else if (CheckPlayerAdjacent((mptr + i)->pos) && (mptr + i)->entityID > 1){
                    monsterCombat = AttackPlayer(mptr + i, combatHistory, player);
                    if(!monsterCombat) {
                        leaveFlag = true;
                    }
                    i++;
                }
                else {
                    i++;
                }
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
    }
    

void CloseGame(void) { 
    free(combatHistory);
    free(player);
    free(mptr);
    endwin();
    /* Free memory allocated by pointer. */
} 
