#include <rogue.h>


Player* CreatePlayer(Position start_pos) {
    Player* player = calloc(1, sizeof(Player));
    Entity emptyNpc = {0};

    player->noCollision = false;
    player->isResting = false;
    player->ch = '@';
    player->color = COLOR_PAIR(VISIBLE_COLOR);
    player->abilityTimer = 0;
    player->invHead = 0;
    player->invTail = 0;
    player->pos.y = start_pos.y;
    player->pos.x = start_pos.x;
    player->follower = emptyNpc;
    for(int i = 0; i < MAX_ABILITIES; i++){
        player->playerClass.abilities[i] = NoAbility();
    }
    AssignFloor(start_pos.x, start_pos.y);
    return player;
}

/*
Ask the player for info about their character.
Uses the TitleScreen ASCII art, and prints to certain areas of it.
*/
bool AskPlayerInfo(Player* player) {
    char* name;
    int nameBufferSize = 3;
    char *nameBuffer = (char *)malloc(nameBufferSize * sizeof(char));

    if (nameBuffer == NULL) {
        printf("Memory allocation error when creating input buffer.\n");
        return false;
    }

    name = (char*)malloc(33);

    if (name == NULL) {
        printf("Memory allocation error when creating name buffer.\n");
        return false;
    }
    
    keypad(stdscr, FALSE);

    ChooseName(name);
    free(name);
    free(nameBuffer);
    
    noecho();           // Hide input again.
    keypad(stdscr, TRUE);
    cbreak();           // Set back to raw.  
    return true;
}   

/* 
Lets player choose a race based on X + Y coordinates, then sends those chosen coordinates to
AssignRace in assignplayer.c
returns true if ran successfull, if false is returned, re-run ChooseRace() inside ChooseClass().
*/
bool ChooseRace() {
    int ch;
    int cursorBoundY = 22;
    int cursorBoundX = 40;
    bool nameChoice = false;
    bool leaveFlag = false;
    bool escPressed = false;
    PrintRaces();
    Cursor(cursorBoundY, cursorBoundX, 11);
    PrintRaceStats(cursorBoundY + cursorBoundX);
    while((ch = getch()) != ' ' && ch != '\n') { 
        escPressed = CheckEscape(ch);
        if(escPressed){ // if escape press, re run Choose Race
            ClearRaces();
            ClearRaceStats();
            RemoveCursor(cursorBoundY, cursorBoundX, 11);
            nameChoice = false;
            while(!nameChoice) {
                nameChoice = AskPlayerInfo(player);
            }   
        }
        PrintRaces();
        Cursor(cursorBoundY, cursorBoundX, 11);
        switch(ch) {
            case KEY_UP:
            if (cursorBoundY == 22) {
                RemoveCursor(cursorBoundY, cursorBoundX, 11);
                cursorBoundY = 27;
            }
            else {
                RemoveCursor(cursorBoundY, cursorBoundX, 11);
                cursorBoundY--;
            }
            break;
            //move down
            case KEY_DOWN:
                if (cursorBoundY == 27) {
                    RemoveCursor(cursorBoundY, cursorBoundX, 11);
                    cursorBoundY = 22;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 11);
                    cursorBoundY++;
                }
                break;
            //move left
            case KEY_LEFT:
                if (cursorBoundX == 40) {
                    RemoveCursor(cursorBoundY, cursorBoundX, 11);
                    cursorBoundX = 60;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 11);
                    cursorBoundX = cursorBoundX - 20;
                }
                break;
            case KEY_RIGHT:
                if (cursorBoundX == 60) {
                    RemoveCursor(cursorBoundY, cursorBoundX, 11);
                    cursorBoundX = 40;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 11);
                    cursorBoundX = cursorBoundX + 20;
                }
                break;
            default:
                Cursor(cursorBoundY, cursorBoundX, 11);
                break;
            }
            ClearRaceStats();
            Cursor(cursorBoundY, cursorBoundX, 11);
            PrintRaceStats(cursorBoundY + cursorBoundX);
        }
    AssignStats((cursorBoundY + cursorBoundX));
    return true;
}

/* 
Lets player choose a class based on X + Y coordinates, then sends those chosen coordinates to
AssignClass in assignplayer.c.
Also contains the Choose Race function, to try and allow player to choose a new race if they change their mind.
*/
void ChooseClass() {
    bool raceChoice = false;
    while(!raceChoice) {
        raceChoice = ChooseRace();
    }
    int ch;
    int cursorBoundY = 29;
    int cursorBoundX = 40;
    bool escPressed = false;
    bool leaveFlag = false;
    PrintClasses();
    Cursor(cursorBoundY, cursorBoundX, 13);
    PrintClassStats(cursorBoundX + cursorBoundY);
    while((ch = getch()) != ' ' && ch != '\n') {
        escPressed = CheckEscape(ch);
        if(escPressed){ // if escape press, re run Choose Race
            ClearClasses();
            ClearClassStats();
            ClearRaceStats();
            RemoveCursor(cursorBoundY, cursorBoundX, 13);
            raceChoice = false;
            while(!raceChoice) {
                raceChoice = ChooseRace();
            }   
            PrintClasses();
        }
        Cursor(cursorBoundY, cursorBoundX, 13);
        switch(ch) {
            //move up
            case KEY_UP:
                if (cursorBoundY == 29) {
                    RemoveCursor(cursorBoundY, cursorBoundX, 13);
                    cursorBoundY = 34;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 13);
                    cursorBoundY--;
                }
            break;
            //move down
            case KEY_DOWN:
                if (cursorBoundY == 34) {
                    RemoveCursor(cursorBoundY, cursorBoundX, 13);
                    cursorBoundY = 29;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 13);
                    cursorBoundY++;
                }
                break;
            //move left
            case KEY_LEFT:
                if (cursorBoundX == 40) {
                    RemoveCursor(cursorBoundY, cursorBoundX, 13);
                    cursorBoundX = 60;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 13);
                    cursorBoundX = cursorBoundX - 20;
                }
                break;
            case KEY_RIGHT:
                if (cursorBoundX == 60) {
                    RemoveCursor(cursorBoundY, cursorBoundX, 13);
                    cursorBoundX = 40;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 13);
                    cursorBoundX = cursorBoundX + 20;
                }
                break;
            default:
                Cursor(cursorBoundY, cursorBoundX, 13);
                break;
            }
        ClearClassStats();
        Cursor(cursorBoundY, cursorBoundX, 13);
        PrintClassStats(cursorBoundX + cursorBoundY);
    }
    AssignClass((cursorBoundY + cursorBoundX));   
}

/*
Lets the player enter their name.
*/
void ChooseName(char* name) {
    echo();             
    nocbreak();   // character available immediately & no line buffering.
    keypad(stdscr, FALSE);      
    mvprintw(18, 40, "Please Enter your name: ");
    mvprintw(20, 44, "                                ");
    mvgetnstr(20, 44, name, 32);
    strcpy(player->playerName, name);
}

/*
Prints available races.
*/
void PrintRaces() {
    mvprintw(22, 10, "Please Choose a Race: ");
    mvprintw(22, 40, "Human");
    mvprintw(23, 40, "Elf");
    mvprintw(24, 40, "Dwarf");
    mvprintw(25, 40, "Dragonborn");
    mvprintw(26, 40, "Gnoll");
    mvprintw(27, 40, "Canidae");
    mvprintw(22, 60, "Skeleton");
    mvprintw(23, 60, "Mantis");
    mvprintw(24, 60, "Automaton");
    mvprintw(25, 60, "Werewolf");
    mvprintw(26, 60, "Vampire");
    mvprintw(27, 60, "Succubus");
}

/*
Prints available classes.
*/
void PrintClasses() {
    mvprintw(29, 10, "Please Choose a Class: ");
    mvprintw(29, 40, "Knight");
    mvprintw(30, 40, "Swashbuckler");
    mvprintw(31, 40, "Wizard");
    mvprintw(32, 40, "Necromancer");
    mvprintw(33, 40, "Gunslinger");
    mvprintw(34, 40, "Druid");
    mvprintw(29, 60, "Ranger");
    mvprintw(30, 60, "Dark Knight");
    mvprintw(31, 60, "Warlock");
    mvprintw(32, 60, "Conjurer");
    mvprintw(33, 60, "Cyborg");
    mvprintw(34, 60, "Bard");
}

void PrintClassStats(int input){
    switch(input){
        case KNIGHT:
            mvprintw(31, 10, "HP/LVL: %d", 6);
            mvprintw(32, 10, "MAIN STAT: %s", "STR");
            mvprintw(33, 10, "SECOND STAT: %s", "CON");
            break;
        case SWASHBUCKLER:
            mvprintw(31, 10, "HP/LVL: %d", 4);
            mvprintw(32, 10, "MAIN STAT: %s", "CHA");
            mvprintw(33, 10, "SECOND STAT: %s", "DEX");
            break;
        case WIZARD:
            mvprintw(31, 10, "HP/LVL: %d", 2);
            mvprintw(32, 10, "MAIN STAT: %s", "INT");
            mvprintw(33, 10, "SECOND STAT: %s", " ");
            break;
        case NECROMANCER:
            mvprintw(31, 10, "HP/LVL: %d", 2);
            mvprintw(32, 10, "MAIN STAT: %s", "INT");
            mvprintw(33, 10, "SECOND STAT: %s", "WIS");
            break;
        case GUNSLINGER:
            mvprintw(31, 10, "HP/LVL: %d", 4);
            mvprintw(32, 10, "MAIN STAT: %s", "DEX");
            mvprintw(33, 10, "SECOND STAT: %s", " ");
            break;
            break;
        case DRUID:
            mvprintw(31, 10, "HP/LVL: %d", 4);
            mvprintw(32, 10, "MAIN STAT: %s", "WIS");
            mvprintw(33, 10, "SECOND STAT: %s", " ");
            break;
        case RANGER:
            mvprintw(31, 10, "HP/LVL: %d", 5);
            mvprintw(32, 10, "MAIN STAT: %s", "DEX");
            mvprintw(33, 10, "SECOND STAT: %s", "WIS");
            break;
        case DARK_KNIGHT:
            mvprintw(31, 10, "HP/LVL: %d", 6);
            mvprintw(32, 10, "MAIN STAT: %s", "STR");
            mvprintw(33, 10, "SECOND STAT: %s", " ");
            break;
        case WARLOCK:
            mvprintw(31, 10, "HP/LVL: %d", 2);
            mvprintw(32, 10, "MAIN STAT: %s", "CHA");
            mvprintw(33, 10, "SECOND STAT: %s", " ");
            break;
        case CONJURER:
            mvprintw(31, 10, "HP/LVL: %d", 2);
            mvprintw(32, 10, "MAIN STAT: %s", "CHA");
            mvprintw(33, 10, "SECOND STAT: %s", "INT");
            break;
        case CYBORG:
            mvprintw(31, 10, "HP/LVL: %d", 6);
            mvprintw(32, 10, "MAIN STAT: %s", "STR");
            mvprintw(33, 10, "SECOND STAT: %s", "DEX");
            break;
        case BARD:
            mvprintw(31, 10, "HP/LVL: %d", 3);
            mvprintw(32, 10, "MAIN STAT: %s", "CHA");
            mvprintw(33, 10, "SECOND STAT: %s", "DEX");
            break;
            break;
    }
}

void PrintRaceStats(int input) {
    switch(input){
        case HUMAN:
            mvprintw(24, 10, "HP: %d", 10);
            mvprintw(25, 10, "CHA: %d", 12);
            mvprintw(26, 10, "CON: %d", 12);
            mvprintw(27, 10, "DEX: %d", 12);
            mvprintw(25, 18, "INT: %d", 12);
            mvprintw(26, 18, "STR: %d", 12);
            mvprintw(27, 18, "WIS: %d", 12);
            break;
        case ELF:
            mvprintw(24, 10, "HP: %d", 8);
            mvprintw(25, 10, "CHA: %d", 12);
            mvprintw(26, 10, "CON: %d", 10);
            mvprintw(27, 10, "DEX: %d", 16);
            mvprintw(25, 18, "INT: %d", 14);
            mvprintw(26, 18, "STR: %d", 10);
            mvprintw(27, 18, "WIS: %d", 12);
            break;
        case DWARF:
            mvprintw(24, 10, "HP: %d", 10);
            mvprintw(25, 10, "CHA: %d", 10);
            mvprintw(26, 10, "CON: %d", 14);
            mvprintw(27, 10, "DEX: %d", 10);
            mvprintw(25, 18, "INT: %d", 10);
            mvprintw(26, 18, "STR: %d", 14);
            mvprintw(27, 18, "WIS: %d", 16);
            break;
        case DRAGONBORN:
            mvprintw(24, 10, "HP: %d", 12);
            mvprintw(25, 10, "CHA: %d", 10);
            mvprintw(26, 10, "CON: %d", 16);
            mvprintw(27, 10, "DEX: %d", 8);
            mvprintw(25, 18, "INT: %d", 10);
            mvprintw(26, 18, "STR: %d", 16);
            mvprintw(27, 18, "WIS: %d", 10);
            break;
        case GNOLL:
            mvprintw(24, 10, "HP: %d", 12);
            mvprintw(25, 10, "CHA: %d", 10);
            mvprintw(26, 10, "CON: %d", 16);
            mvprintw(27, 10, "DEX: %d", 10);
            mvprintw(25, 18, "INT: %d", 8);
            mvprintw(26, 18, "STR: %d", 16);
            mvprintw(27, 18, "WIS: %d", 10);
            break;
        case CANIDAE:
            mvprintw(24, 10, "HP: %d", 12);
            mvprintw(25, 10, "CHA: %d", 12);
            mvprintw(26, 10, "CON: %d", 16);
            mvprintw(27, 10, "DEX: %d", 10);
            mvprintw(25, 18, "INT: %d", 8);
            mvprintw(26, 18, "STR: %d", 14);
            mvprintw(27, 18, "WIS: %d", 10);
            break;
        case SKELETON:
            mvprintw(24, 10, "HP: %d", 8);
            mvprintw(25, 10, "CHA: %d", 10);
            mvprintw(26, 10, "CON: %d", 14);
            mvprintw(27, 10, "DEX: %d", 12);
            mvprintw(25, 18, "INT: %d", 16);
            mvprintw(26, 18, "STR: %d", 8);
            mvprintw(27, 18, "WIS: %d", 14);
            break;
        case MANTIS:
            mvprintw(24, 10, "HP: %d", 12);
            mvprintw(25, 10, "CHA: %d", 8);
            mvprintw(26, 10, "CON: %d", 14);
            mvprintw(27, 10, "DEX: %d", 12);
            mvprintw(25, 18, "INT: %d", 10);
            mvprintw(26, 18, "STR: %d", 16);
            mvprintw(27, 18, "WIS: %d", 10);
            break;
        case AUTOMATON:
            mvprintw(24, 10, "HP: %d", 10);
            mvprintw(25, 10, "CHA: %d", 10);
            mvprintw(26, 10, "CON: %d", 16);
            mvprintw(27, 10, "DEX: %d", 10);
            mvprintw(25, 18, "INT: %d", 12);
            mvprintw(26, 18, "STR: %d", 14);
            mvprintw(27, 18, "WIS: %d", 10);
            break;
        case WEREWOLF:
            mvprintw(24, 10, "HP: %d", 12);
            mvprintw(25, 10, "CHA: %d", 10);
            mvprintw(26, 10, "CON: %d", 16);
            mvprintw(27, 10, "DEX: %d", 14);
            mvprintw(25, 18, "INT: %d", 8);
            mvprintw(26, 18, "STR: %d", 16);
            mvprintw(27, 18, "WIS: %d", 8);
            break;
        case VAMPIRE:
            mvprintw(24, 10, "HP: %d", 10);
            mvprintw(25, 10, "CHA: %d", 16);
            mvprintw(26, 10, "CON: %d", 10);
            mvprintw(27, 10, "DEX: %d", 12);
            mvprintw(25, 18, "INT: %d", 14);
            mvprintw(26, 18, "STR: %d", 10);
            mvprintw(27, 18, "WIS: %d", 10);
            break;
        case SUCCUBUS:
            mvprintw(24, 10, "HP: %d", 8);
            mvprintw(25, 10, "CHA: %d", 16);
            mvprintw(26, 10, "CON: %d", 10);
            mvprintw(27, 10, "DEX: %d", 12);
            mvprintw(25, 18, "INT: %d", 14);
            mvprintw(26, 18, "STR: %d", 8);
            mvprintw(27, 18, "WIS: %d", 12);
            break;
        default:
            mvprintw(24, 10, "HP: %d", 10);
            mvprintw(25, 10, "CHA: %d", 12);
            mvprintw(26, 10, "CON: %d", 12);
            mvprintw(27, 10, "DEX: %d", 12);
            mvprintw(25, 18, "INT: %d", 12);
            mvprintw(26, 18, "STR: %d", 12);
            mvprintw(27, 18, "WIS: %d", 12);
            break;
    }
}

void ClearClassStats() {
    mvprintw(31, 10, "                 ");
    mvprintw(32, 10, "                 ");
    mvprintw(33, 10, "                 ");
}

void ClearRaceStats() {
    mvprintw(24, 10, "       ");
    mvprintw(25, 10, "       ");
    mvprintw(26, 10, "       ");
    mvprintw(27, 10, "       ");
    mvprintw(25, 18, "       ");
    mvprintw(26, 18, "       ");
    mvprintw(27, 18, "       ");
}


void ClearClasses() {
    mvprintw(29, 10, "                         ");
    mvprintw(29, 40, "               ");
    mvprintw(30, 40, "               ");
    mvprintw(31, 40, "               ");
    mvprintw(32, 40, "               ");
    mvprintw(33, 40, "               ");
    mvprintw(34, 40, "               ");
    mvprintw(29, 60, "               ");
    mvprintw(30, 60, "               ");
    mvprintw(31, 60, "               ");
    mvprintw(32, 60, "               ");
    mvprintw(33, 60, "               ");
    mvprintw(34, 60, "               ");
    RemoveCursor(22, 40, 13); // clear previous cursor
    RemoveCursor(23, 40, 13);
    RemoveCursor(24, 40, 13);
    RemoveCursor(25, 40, 13);
    RemoveCursor(26, 40, 13);
    RemoveCursor(27, 40, 13);
    RemoveCursor(22, 60, 13);
    RemoveCursor(23, 60, 13);
    RemoveCursor(24, 60, 13);
    RemoveCursor(25, 60, 13);
    RemoveCursor(26, 60, 13);
    RemoveCursor(27, 60, 13);
}

void ClearRaces() {
    mvprintw(22, 10, "                         ");
    mvprintw(22, 40, "               ");
    mvprintw(23, 40, "               ");
    mvprintw(24, 40, "               ");
    mvprintw(25, 40, "               ");
    mvprintw(26, 40, "               ");
    mvprintw(27, 40, "               ");
    mvprintw(22, 60, "               ");
    mvprintw(23, 60, "               ");
    mvprintw(24, 60, "               ");
    mvprintw(25, 60, "               ");
    mvprintw(26, 60, "               ");
    mvprintw(27, 60, "               ");
}
