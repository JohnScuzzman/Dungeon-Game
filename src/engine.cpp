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

/* Returns true if escape was passed in.*/
/* Usually the passed in int 'ch' will be from getch().*/
bool CheckEscape(int ch) {
    int next_ch;
    if (ch == 27) { 
            // check for escape.
            nodelay(stdscr, TRUE);
            next_ch = getch();
            nodelay(stdscr, FALSE);
        }
        if (next_ch == ERR) {
            return true;
        }
    return false;
}

void Cursor(int x, int y, int length){
    //A_BLINK 
    mvchgat(x, y, length, A_BOLD | A_STANDOUT | A_DIM, VISIBLE_COLOR, NULL);
}

void RemoveCursor(int x, int y, int length) {
    mvchgat(x, y, length, A_NORMAL, 0, NULL);
}

/* Moves monsters, returns false unless player dies.*/
bool MoveMonsterLoop(Entity* mptr, int n_monsters, bool PMove){
    int i = 0;
    bool monsterCombat;
    /* Wander checks if LOS to player and flips aggro is they are in range.*/
    while (!((mptr + i)->hasMoved) && i < n_monsters && PMove == true){
        /* Check if player is in aggro range. */
        if(!((mptr+i)->aggroFlag)){
            (mptr + i)->aggroFlag = CheckAggro((mptr + i), player);
        }

        /* If no adjacent Player, Wander.*/
        if (!CheckPlayerAdjacent((mptr + i)->pos) && !((mptr + i)->aggroFlag) && (mptr + i)->isMonster == true){
            Wander(mptr + i);
            i++;
        }
        /* If adjacent to player, attack them.*/
        else if (CheckPlayerAdjacent((mptr + i)->pos) == true && (mptr + i)->isMonster == true){
            monsterCombat = AttackPlayer((mptr + i), combatHistory, player);
            /* If monsterCombat = false, player died, end the game.*/
            if (monsterCombat == false) {
                return true;
            }
            i++;
        }
        /* If player was seen, move towards player.*/
        else if (((mptr + i)->aggroFlag) && ((mptr + i)->isMonster)){
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

void RefreshGamestate(Entity* mptr, int n_monsters) {
    UpdateMonsterMap(mptr, n_monsters);
    MakeFOV(player);
    DrawEverything();
    ResetMoveFlags(mptr, n_monsters);
    ResetCombatHistory();
}

void GameLoop(Entity* mptr, CombatHistory* combatHistory, int n_monsters, LogQueue *q, Item* items) { 
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
            leaveFlag = MakeInventoryMenu(items);
        }
        if(ch != ERR) {
            PlayerRegen(&playerRegen);
            ManaRegen(&manaRegen);
            PMove = PlayerInput(ch, q, n_monsters);
            if (combatHistory->playerCombat) {
                PlayerPrepareCombat(n_monsters);
                PostCombatEffects();
            }
            if(MoveMonsterLoop(mptr, n_monsters, PMove)){
                leaveFlag = true;
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
    free(items);
    free(q);
    free(combatHistory);
    free(player);
    free(mptr);
    endwin();

} 

void Greeting(){
    combatHistory->event = "Welcome to the dungeon,";
    QueueEvent(q, combatHistory->event);
    combatHistory->event = player->playerName;
    combatHistory->event += "!";
    QueueEvent(q, combatHistory->event);
    combatHistory->event = "Use arrow keys to move & fight.";
    QueueEvent(q, combatHistory->event);
    combatHistory->event = "Press 'F' to use ranged attacks.";
    QueueEvent(q, combatHistory->event);
    combatHistory->event = "Press ESC to exit at anytime.";
    QueueEvent(q, combatHistory->event);
    combatHistory->event = "Use keys 1-5 to use abilities.";
    QueueEvent(q, combatHistory->event);
}

/* Used to count number of digits in a number.*/
int NumberOfDigits(int input) {
  int count;
  int temp = abs(input);
  // condition ? expression_if_true : expression_if_false, this one handles a zero input.
  count = (temp == 0) ? 0 : (int)log10(temp) + 1;
  return count;
}