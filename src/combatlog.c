#include <rogue.h>

#define LOG_WIDTH 128
#define LOG_HEIGHT 47
#define LOG_SIZE 100

/* Make a window that displays the combat log and lets the user scroll through it.*/
void CreateLogWindow(LogQueue *q) {

    /* Create a pad for the log to use.*/
    WINDOW *pad = newpad(LOG_SIZE, 50);
    scrollok(pad, TRUE); // Allow the pad to scroll internally
    

    PrintCombatQueue(q, pad);

    int current_line = 0;
    while (1) {
        // prefresh(pad, pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol)
        // pad = window to use, current_line, 0 are the coordinates of where the pad starts internally.
        // smins are the 2 top left coords where the pad begins on the physical screen.
        // max are the 2 bottom right coords where the pad ends on the physical screen.
        prefresh(pad, current_line, 0, 22, LOG_WIDTH, LOG_HEIGHT, (LOG_WIDTH) + 32);
        int next_ch;
        int ch = getch();
        if (ch == 27) { 
            // check for escape.
            nodelay(stdscr, TRUE);
            next_ch = getch();
            nodelay(stdscr, FALSE);
        }
        if (next_ch == ERR) {
            break;
        } 
        if (ch == KEY_UP && current_line > 0) current_line--;
        if (ch == KEY_DOWN && current_line < LOG_SIZE - LOG_HEIGHT) current_line++;
    }

    endwin();
}

/* Create the queue for the combat log */
/* Run this first to initialize it.*/
void MakeCombatLogQueue (LogQueue *q) {
    for (int i = 0; i < LOG_SIZE; i++) {
        q->events[i][0] = *(" ");
    }
    q->front = -1;
    q->rear = 0;
}

bool IsEmpty(LogQueue *q) {
    return(q->front == q->rear - 1);
}

bool IsFull(LogQueue *q) {
    return(q->rear == LOG_SIZE);
}

/* Queues a combat event as a string, if full, dequeues the front by incrementing it by one.*/
void QueueEvent(LogQueue *q, char* event) {
    if (IsFull(q)) {
        DequeueEvent(q);
        return;
    }
    q->events[q->rear][0] = *event;
    q->rear++;
}

void DequeueEvent (LogQueue *q) {
    if (IsEmpty(q)){
        return;
    }
    q->front++;
}

char* PeekCombatQueue (LogQueue *q) {
    if (IsEmpty(q)){
        return "Log is Empty, Cannot peek.";
    }
    return q->events[q->front + 1];
}

/* Prints the contents of the queue to the small scrollable window called pad.*/
void PrintCombatQueue (LogQueue *q, WINDOW *pad) {
    if (IsEmpty(q)){
        return;
    }
    for (int i = q->front + 1; i < q->rear; i++) {
        wprintw(pad, "%s", q->events[i]);
    }
}




void RecordPlayerKill(Entity* defender, CombatHistory* combatHistory, int playerAccRoll, int playerDMG) {
    player->playerStats.EXP += (defender->entityStats.EXP);
    combatHistory->defender = *defender;
    combatHistory->playerAccRoll = playerAccRoll;
    combatHistory->playerDMG = playerDMG;
    // combatHistory->monsterKilled = true; Causes issues at the moment
    combatHistory->playerResult = true;
}

void RecordPlayerMiss(Entity* attacker, CombatHistory* combatHistory, int playerAccRoll, int defenderAC) {
    combatHistory->defender = *attacker;
    combatHistory->playerAccRoll = playerAccRoll;
    combatHistory->defenderAC = defenderAC;
    combatHistory->entityResult = false;
    combatHistory->monsterKilled = false;
}

void RecordPlayerHit(Entity* defender, CombatHistory* combatHistory, int playerAccRoll, int playerDMG) {
    combatHistory->defender = *defender;
    combatHistory->playerAccRoll = playerAccRoll;
    combatHistory->playerDMG = playerDMG;
    combatHistory->monsterKilled = false;
    combatHistory->playerResult = true;
}

void RecordMonsterHit(Entity* attacker, CombatHistory* combatHistory, int attackerAccRoll, int attackerDMG) {
    combatHistory->defender = *attacker;
    combatHistory->attackerAccRoll = attackerAccRoll;
    combatHistory->attackerDMG = attackerDMG;
    combatHistory->entityResult = true;
    combatHistory->monsterKilled = false;
}

void RecordMonsterMiss(Entity* defender, CombatHistory* combatHistory, int attackerAccRoll, int playerAC) {
    combatHistory->defender = *defender;
    combatHistory->attackerAccRoll = attackerAccRoll;
    combatHistory->playerAC = playerAC;
    combatHistory->playerResult = false;
    combatHistory->monsterKilled = false;
}