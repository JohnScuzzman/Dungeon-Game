#include <rogue.h>
/*
Ask the player for info about their character.
Uses the TitleScreen ASCII art, and prints to certain areas of it.
*/
void AskPlayerInfo(Player* player) {
    char* name;
    char* race;
    char* class;
    char* armor;
    char* weapon;
    int nameBufferSize = 3;
    char *nameBuffer = (char *)malloc(nameBufferSize * sizeof(char));

    if (nameBuffer == NULL) {
        printf("Memory allocation error when creating input buffer.\n");
        return;
    }

    name = (char*)malloc(33);

    if (name == NULL) {
        printf("Memory allocation error when creating name buffer.\n");
        return;
    }
    
    keypad(stdscr, TRUE);

    ChooseName(name);
    free(name);
    free(nameBuffer);
    
    noecho();           // Hide input again.
    keypad(stdscr, FALSE);
    cbreak();           // Set back to raw.
    ChooseRace();
    ChooseClass();
    
}   

void ChooseRace() {
    int ch;
    int cursorBoundY = 22;
    int cursorBoundX = 40;
    PrintRaces();
    Cursor(cursorBoundY, cursorBoundX, 11);
    while((ch = getch()) != ' ' && ch != '\n')
    { 
        Cursor(cursorBoundY, cursorBoundX, 11);
        switch(ch) {
            case 'A':
            if (cursorBoundY == 22) {
                break;
            }
            else {
                RemoveCursor(cursorBoundY, cursorBoundX, 11);
                cursorBoundY--;
                Cursor(cursorBoundY, cursorBoundX, 11);
            }
            break;
            //move down
            case 'B':
                if (cursorBoundY == 26) {
                    break;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 11);
                    cursorBoundY++;
                    Cursor(cursorBoundY, cursorBoundX, 11);
                }
                break;
            //move left
            case 'D':
                if (cursorBoundX == 40) {
                    break;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 11);
                    cursorBoundX = cursorBoundX - 20;
                    Cursor(cursorBoundY, cursorBoundX, 11);
                }
                break;
            case 'C':
                if (cursorBoundX == 60) {
                    break;
                }
                else {
                    RemoveCursor(cursorBoundY, cursorBoundX, 11);
                    cursorBoundX = cursorBoundX + 20;
                }
                break;
            default:
                Cursor(cursorBoundY, cursorBoundX, 11);
                refresh();
                break;
            }
            Cursor(cursorBoundY, cursorBoundX, 11);
            refresh();
        }
    AssignStats((cursorBoundY + cursorBoundX));
}

void ChooseClass() {
    int ch;
    int cursorBoundY = 28;
    int cursorBoundX = 40;
    PrintClasses();
    Cursor(cursorBoundY, cursorBoundX, 13);
    while((ch = getch()) != ' ' && ch != '\n') {
    Cursor(cursorBoundY, cursorBoundX, 13);
    switch(ch) {
        //move up
        case 'A':
            if (cursorBoundY == 28) {
                break;
            }
            else {
                RemoveCursor(cursorBoundY, cursorBoundX, 13);
                cursorBoundY--;
            }
        break;
        //move down
        case 'B':
            if (cursorBoundY == 32) {
                break;
            }
            else {
                RemoveCursor(cursorBoundY, cursorBoundX, 13);
                cursorBoundY++;
            }
            break;
        //move left
        case 'D':
            if (cursorBoundX == 40) {
                break;
            }
            else {
                RemoveCursor(cursorBoundY, cursorBoundX, 13);
                cursorBoundX = cursorBoundX - 20;
            }
            break;
        case 'C':
            if (cursorBoundX == 60) {
                break;
            }
            else {
                RemoveCursor(cursorBoundY, cursorBoundX, 13);
                cursorBoundX = cursorBoundX + 20;
            }
            break;
        default:
            Cursor(cursorBoundY, cursorBoundX, 13);
            refresh();
            break;
        }
        Cursor(cursorBoundY, cursorBoundX, 13);
        refresh();
    }
    AssignClass((cursorBoundY + cursorBoundX));   
}


/*
Lets the player enter their name.
*/
void ChooseName(char* name) {
    echo();             
    nocbreak();         
    mvprintw(18, 40, "Please Enter your name: ");
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
    mvprintw(22, 60, "Skeleton");
    mvprintw(23, 60, "Mantis");
    mvprintw(24, 60, "Robot");
    mvprintw(25, 60, "Werewolf");
    mvprintw(26, 60, "Vampire");
}

/*
Prints available classes.
*/
void PrintClasses() {
    mvprintw(28, 10, "Please Choose a Class: ");
    mvprintw(28, 40, "Knight");
    mvprintw(29, 40, "Swashbuckler");
    mvprintw(30, 40, "Wizard");
    mvprintw(31, 40, "Necromancer");
    mvprintw(32, 40, "Gunslinger");
    mvprintw(28, 60, "Ranger");
    mvprintw(29, 60, "Dark Knight");
    mvprintw(30, 60, "Alchemist");
    mvprintw(31, 60, "Conjurer");
    mvprintw(32, 60, "Cyborg");
}

