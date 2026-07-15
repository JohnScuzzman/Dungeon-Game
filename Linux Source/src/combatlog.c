#include <rogue.h>
#define DMG_BUFFER 8

/* 
Initialize the combat history, used to track the combat events of the turn before being reset.
*/
CombatHistory* CreateCombatHistory(Entity monster) {
    CombatHistory* combatHistory;
    combatHistory = calloc(1, sizeof(CombatHistory));
    combatHistory->defender = monster;
    return combatHistory;
}

/* Create the queue for the combat log */
/* Run this first to initialize it.*/
LogQueue* MakeCombatLogQueue() {
    LogQueue* q;
    q = calloc(1, sizeof(LogQueue));
    q->front = 0;
    q->rear = 0;
    return q;
}

bool IsEmpty(LogQueue *q) {
    return(q->front == q->rear);
}

bool IsFull(LogQueue *q) {
    return(q->rear == LOG_SIZE);
}

/* Queues a combat event as a string, if full, dequeues the front by incrementing it by one.*/
void QueueEvent(LogQueue *q, char* event) {
    if (IsFull(q)) {
        strcpy(q->events[q->rear], event);
        DequeueEvent(q);
        strcpy(q->events[q->rear], " ");
        
        return;
    }
    else{
        strcpy(q->events[q->rear], event);
        q->rear++;
    }
}

/* 
Currently not used, but may be used in the future.
*/
void DequeueEvent (LogQueue *q) {
    if (IsEmpty(q)){
        return;
    }
    for (int i = 1; i  <= LOG_SIZE; i++){
        strcpy(q->events[i - 1], q->events[i]);
    }
        // q->front++;
}

/* 
Currently not used, but may be used in the future.
*/
char* PeekCombatQueue (LogQueue *q) {
    if (IsEmpty(q)){
        return "Log is Empty, Cannot peek.";
    }
    return q->events[q->front];
}

void NotEnoughMana() {
    if(player->playerClass.isCaster){
            strcpy(combatHistory->event, "Not enough mana.");
            QueueEvent(q, combatHistory->event);
        }
    else {
        strcpy(combatHistory->event, "Not enough energy.");
        QueueEvent(q, combatHistory->event);
    }
}

/* Prints the contents of the queue to the small scrollable window called pad.*/
// void PrintCombatQueue (LogQueue *q, WINDOW *pad) {
//     if (IsEmpty(q)){
//         return;
//     }
//     for (int i = 0; i <= q->rear; i++) {
//         mvwprintw(pad, i, 0, "%s", q->events[i]);
//     }
// }

void RecordPlayerKill(Entity* defender, CombatHistory* combatHistory, int playerAccRoll, int playerDMG) {
    char eventDMGBuffer[DMG_BUFFER];
    combatHistory->defender = *defender;
    player->playerStats.EXP += (defender->entityStats.EXP);
    combatHistory->playerAccRoll = playerAccRoll;
    combatHistory->playerDMG = playerDMG;
    combatHistory->playerResult = true;
    combatHistory->monsterKilled = true;
    RecordAbilityUse(); // Checks if player used ability & records it.
    strcpy(combatHistory->event, "You kill the ");
    strcat(combatHistory->event, combatHistory->defender.entityName);
    strcat(combatHistory->event, ".");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, "Dealing ");
    snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d", playerDMG);
    strcat(combatHistory->event, eventDMGBuffer);
    strcat(combatHistory->event, " total damage.");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, "You Gained ");
    snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d", defender->entityStats.EXP);
    strcat(combatHistory->event, eventDMGBuffer);
    strcat(combatHistory->event, " EXP!");
    QueueEvent(q, combatHistory->event);
}

void RecordNPCKill(Entity* defender, Entity* attacker, CombatHistory* combatHistory, int attackerAccRoll, int attackerDMG) {
    char eventDMGBuffer[DMG_BUFFER];
    combatHistory->defender = *defender;
    combatHistory->playerAccRoll = attackerAccRoll;
    combatHistory->playerDMG = attackerDMG;
    combatHistory->playerResult = false;
    combatHistory->monsterKilled = true;
    if(attacker->entityID == player->follower.entityID) player->playerStats.EXP += (defender->entityStats.EXP);
    strcpy(combatHistory->event, "The ");
    strcat(combatHistory->event, attacker->entityName);
    strcat(combatHistory->event, " Kills the ");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, combatHistory->defender.entityName);
    strcat(combatHistory->event, ".");
    QueueEvent(q, combatHistory->event);
}

void RecordPlayerMiss(Entity* attacker, CombatHistory* combatHistory, int playerAccRoll, int defenderAC) {
    combatHistory->defender = *attacker;
    combatHistory->playerAccRoll = playerAccRoll;
    combatHistory->defenderAC = defenderAC;
    combatHistory->playerResult = false;
    combatHistory->monsterKilled = false;
    RecordAbilityUse();
    strcpy(combatHistory->event, "You miss the ");
    strcat(combatHistory->event, combatHistory->defender.entityName);
    strcat(combatHistory->event, ".");
    QueueEvent(q, combatHistory->event);
}

void RecordNPCMiss(Entity* defender, Entity* attackingNPC, CombatHistory* combatHistory, int attackerAccRoll, int defenderAC) {
    combatHistory->defender = *defender;
    combatHistory->playerAccRoll = attackerAccRoll;
    combatHistory->defenderAC = defenderAC;
    combatHistory->playerResult = false;
    combatHistory->monsterKilled = false;
    strcpy(combatHistory->event, "The ");
    strcat(combatHistory->event, attackingNPC->entityName);
    strcat(combatHistory->event, " missed the ");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, defender->entityName);
    strcat(combatHistory->event, ".");
    QueueEvent(q, combatHistory->event);
}

void RecordPlayerHit(Entity* defender, CombatHistory* combatHistory, int playerAccRoll, int playerDMG) {
    char eventDMGBuffer[DMG_BUFFER];
    combatHistory->defender = *defender;
    combatHistory->playerAccRoll = playerAccRoll;
    combatHistory->playerDMG = playerDMG;
    combatHistory->monsterKilled = false;
    combatHistory->playerResult = true;
    RecordAbilityUse();
    strcpy(combatHistory->event, "You hit the ");
    strcat(combatHistory->event, combatHistory->defender.entityName);
    strcat(combatHistory->event, " for ");
    snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d.", playerDMG);
    strcat(combatHistory->event, eventDMGBuffer);
    // strcat(combatHistory->event, " .\n");
    QueueEvent(q, combatHistory->event);
}

void RecordNPCHit(Entity* defender, Entity* attackingNPC, CombatHistory* combatHistory, int attackerAccRoll, int attackerDMG) {
    char eventDMGBuffer[DMG_BUFFER];
    combatHistory->defender = *defender;
    combatHistory->playerAccRoll = attackerAccRoll;
    combatHistory->playerDMG = attackerDMG;
    combatHistory->monsterKilled = false;
    combatHistory->playerResult = false;
    strcpy(combatHistory->event, "The ");
    strcat(combatHistory->event, attackingNPC->entityName);
    strcat(combatHistory->event, " hits the ");
    QueueEvent(q, combatHistory->event);
    strcpy(combatHistory->event, combatHistory->defender.entityName);
    strcat(combatHistory->event, " for ");
    snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d.", attackerDMG);
    strcat(combatHistory->event, eventDMGBuffer);
    QueueEvent(q, combatHistory->event);
}

void RecordMonsterHit(Entity* attacker, CombatHistory* combatHistory, int attackerAccRoll, int attackerDMG) {
    char eventDMGBuffer[DMG_BUFFER];
    combatHistory->defender = *attacker;
    combatHistory->attackerAccRoll = attackerAccRoll;
    combatHistory->attackerDMG = attackerDMG;
    combatHistory->entityResult = true;
    combatHistory->monsterKilled = false;
    strcpy(combatHistory->event, "The ");
    strcat(combatHistory->event, combatHistory->defender.entityName);
    strcat(combatHistory->event, " hits you for ");
    snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d.", attackerDMG);
    strcat(combatHistory->event, eventDMGBuffer);
    // strcat(combatHistory->event, " .\n");
    QueueEvent(q, combatHistory->event);
}

void RecordMonsterMiss(Entity* defender, CombatHistory* combatHistory, int attackerAccRoll, int playerAC) {
    combatHistory->defender = *defender;
    combatHistory->attackerAccRoll = attackerAccRoll;
    combatHistory->playerAC = playerAC;
    combatHistory->entityResult = false;
    combatHistory->monsterKilled = false;
    strcpy(combatHistory->event, "The ");
    strcat(combatHistory->event, combatHistory->defender.entityName);
    strcat(combatHistory->event, " misses.");
    QueueEvent(q, combatHistory->event);
}

void RecordAbilityUse(){
    if (combatHistory->playerUsedAbility && player->equippedAbility.isMagic) {
        strcpy(combatHistory->event, "You cast ");
        strcat(combatHistory->event, player->equippedAbility.abilityName);
        strcat(combatHistory->event, ".");
        QueueEvent(q, combatHistory->event);
    }
    else if (combatHistory->playerUsedAbility) {
        strcpy(combatHistory->event, "You use ");
        strcat(combatHistory->event, player->equippedAbility.abilityName);
        strcat(combatHistory->event, ".");
        QueueEvent(q, combatHistory->event);
    }
}

// TODO Make two versions of this below for an inventory system?
// /* Make a window that displays the combat log and lets the user scroll through it.*/
// void CreateLogWindow(LogQueue *q) {

//     /* Create a pad for the log to use.*/
//     WINDOW *pad = newpad(LOG_SIZE, DMG_BUFFER);
//     scrollok(pad, TRUE); // Allow the pad to scroll internally
    

//     PrintCombatQueue(q, pad);

//     int current_line = 0;
//     while (1) {
//         // prefresh(pad, pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol)
//         // pad = window to use, current_line, 0 are the coordinates of where the pad starts internally.
//         // smins are the 2 top left coords where the pad begins on the physical screen.
//         // max are the 2 bottom right coords where the pad ends on the physical screen.
//         prefresh(pad, current_line, 0, 22, LOG_WIDTH, LOG_HEIGHT, (LOG_WIDTH) + 32);
//         int next_ch;
//         int ch = getch();
//         if (ch == 27) { 
//             // check for escape.
//             nodelay(stdscr, TRUE);
//             next_ch = getch();
//             nodelay(stdscr, FALSE);
//         }
//         if (next_ch == ERR) {
//             break;
//         } 
//         if (ch == KEY_UP && current_line > 0) current_line--;
//         if (ch == KEY_DOWN && current_line < LOG_SIZE - LOG_HEIGHT) current_line++;
//     }

//     endwin();
// }
