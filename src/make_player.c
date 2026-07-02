#include <rogue.h>


Player* CreatePlayer(Position start_pos) {
    Player* player = calloc(1, sizeof(Player));
    player->noCollision = false;
    player->isResting = false;
    player->ch = '@';
    player->color = COLOR_PAIR(VISIBLE_COLOR);
    player->abilityTimer = 0;
    player->invHead = 0;
    player->invTail = 0;
    player->pos.y = start_pos.y;
    player->pos.x = start_pos.x;
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
    
    keypad(stdscr, TRUE);

    ChooseName(name);
    free(name);
    free(nameBuffer);
    
    noecho();           // Hide input again.
    keypad(stdscr, FALSE);
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
    while((ch = getch()) != ' ' && ch != '\n') { 
        escPressed = CheckEscape(ch);
        if(escPressed){ // if escape press, re run Choose Race
            ClearRaces();
            RemoveCursor(cursorBoundY, cursorBoundX, 11);
            nameChoice = false;
            while(!nameChoice) {
                nameChoice = AskPlayerInfo(player);
            }   
        }
        PrintRaces();
        Cursor(cursorBoundY, cursorBoundX, 11);
        switch(ch) {
            case 'A':
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
            case 'B':
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
            case 'D':
                if (cursorBoundX == 40) {
                    RemoveCursor(cursorBoundY, cursorBoundX, 11);
                    cursorBoundX = 60;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 11);
                    cursorBoundX = cursorBoundX - 20;
                }
                break;
            case 'C':
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
            Cursor(cursorBoundY, cursorBoundX, 11);
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
    while((ch = getch()) != ' ' && ch != '\n') {
        escPressed = CheckEscape(ch);
        if(escPressed){ // if escape press, re run Choose Race
            ClearClasses();
            RemoveCursor(cursorBoundY, cursorBoundX, 11);
            raceChoice = false;
            while(!raceChoice) {
                raceChoice = ChooseRace();
            }   
            PrintClasses();
            Cursor(cursorBoundY, cursorBoundX, 13);
        }
        Cursor(cursorBoundY, cursorBoundX, 13);
        switch(ch) {
            //move up
            case 'A':
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
            case 'B':
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
            case 'D':
                if (cursorBoundX == 40) {
                    RemoveCursor(cursorBoundY, cursorBoundX, 13);
                    cursorBoundX = 60;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 13);
                    cursorBoundX = cursorBoundX - 20;
                }
                break;
            case 'C':
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
        Cursor(cursorBoundY, cursorBoundX, 13);
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
