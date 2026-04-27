#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include "tables.h"

struct termios orig_termios;
struct Player p;
struct Monster m;
struct Blades b;
struct Ranged r;
struct Armors a;

/*
Fucking abysmal switch statement for movement.
Update: FIXED keypress requiring enter but only works on linux.
TODO: Add a windows version?
 */
int moveFlag = 0;
int globalEvent = 1;
int currentMonster = 0;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/*
All of the game loops happens here in the move function.
Start the player off with a Short Sword and Leather Armor, then run main game loop.
As we move, swap new char we will access and move to it by swapping the chars with players POS.
If we encounter a wall or enemy, disallow a move.
If we encounter an enemy, go into the combat loop held in EventLog at the bottom.
*/
void Move(char **room, int monsterRoom[100][100], int colPOS, int rowPOS, char prevPOS) {
    char input;
    char POS = prevPOS;
    
    //Get Player's Name
    printf("Please enter your character's first name: ");
    scanf("%30[0-9a-zA-Z ]", p.playerName);

    strcpy(p.playerWeapon, b.blades[1]);
    strcpy(p.playerArmor, a.armors[0]);
    p.playerWeaponDMG = b.shortSword;
    p.playerArmorAC = a.leatherArmor;

    // Place monsters and print the floor & UI.
    PlaceMonsters(room, monsterRoom, 69);
    CreateUI(room, p);
    PrintFloor(room);

    EventLog(2, currentMonster);
    enableRawMode();

    // Indicates a successful move action/
    while(read(STDIN_FILENO, &input, 1) == 1 && input != 'x'){
        //DEBUG
        // if (iscntrl(input)) {
        //     printf("%d\n", input);
        // } else {
        //     printf("%d ('%c')\n", input, input);
        // }
        // ONLY WORKS WITH LINUX
        std::system("clear");
            // If floor char, allow move, otherwise send info to the Event Log.
            switch(input) {
                
                case 'A':
                POS = MoveNorth(room, colPOS, rowPOS, POS);
                if(moveFlag){
                    colPOS--;
                }
                break;

                case 'D':
                POS = MoveWest(room, colPOS, rowPOS, POS);
                if(moveFlag) {
                    rowPOS--;
                }
                break;

                case 'B':
                POS = MoveSouth(room, colPOS, rowPOS, POS);
                if(moveFlag) {
                    colPOS++;
                }
                break;

                case 'C':
                POS = MoveEast(room, colPOS, rowPOS, POS);
                if(moveFlag) {
                    rowPOS++;
                }
                break;
            }
        MoveMonsters(room, monsterRoom);
        CreateUI(room, p);
        PrintFloor(room);
        EventLog(globalEvent, currentMonster);
        globalEvent = 1;
        
    }
    disableRawMode();
}

char MoveNorth(char **room, int colPOS, int rowPOS, char prevPOS) {
    
    char nextPOS_N;
    // Save Next char we will overwrite with X.
    nextPOS_N = room[colPOS-1][rowPOS];
    // Check if valid, continue overwriting if so.
    if(nextPOS_N == ' ' || nextPOS_N == '.' || nextPOS_N == '-') {
        room[colPOS][rowPOS] = prevPOS;
        room[colPOS-1][rowPOS] = 'X';
        moveFlag = 1;
        return nextPOS_N;
    }
    switch(nextPOS_N) {
    case '|':
        break;
    case '=':
        break;
    case 'G': // Goblin
        currentMonster = 0;
        moveFlag = 0;
        globalEvent = 3;
        break;
    case 'O':
        currentMonster = 1;
        globalEvent = 3;
        moveFlag = 0;
        break;
    }
    moveFlag = 0;
    return prevPOS;
}
char MoveWest(char **room, int colPOS, int rowPOS, char prevPOS) {
    char nextPOS_W;
    nextPOS_W = room[colPOS][rowPOS-1];
    if(nextPOS_W == ' ' || nextPOS_W == '.' || nextPOS_W == '-') {
        room[colPOS][rowPOS] = prevPOS;
        room[colPOS][rowPOS-1] = 'X';
        moveFlag = 1;
        return nextPOS_W;
    }
    switch(nextPOS_W) {
    case '|':
        break;
    case '=':
        break;
    case 'G': // Goblin
        currentMonster = 0;
        moveFlag = 0;
        globalEvent = 3;
        break;
    case 'O':
        currentMonster = 1;
        moveFlag = 0;
        globalEvent = 3;
        break;
    }
    moveFlag = 0;
    return prevPOS;
}
char MoveSouth(char **room, int colPOS, int rowPOS, char prevPOS) {
    char nextPOS_S;
    nextPOS_S = room[colPOS+1][rowPOS];
    if(nextPOS_S == ' ' || nextPOS_S == '.' || nextPOS_S == '-') {
        room[colPOS][rowPOS] = prevPOS;
        room[colPOS+1][rowPOS] = 'X';
        moveFlag = 1;
        return nextPOS_S;
    }

    switch(nextPOS_S) {
    case '|':
        break;
    case '=':
        break;
    case 'G': // Goblin
        currentMonster = 0;
        moveFlag = 0;
        globalEvent = 3;
        break;
    case 'O':
        currentMonster = 1;
        moveFlag = 0;
        globalEvent = 3;
        break;
    }
    moveFlag = 0;
    return prevPOS;
}
char MoveEast(char **room, int colPOS, int rowPOS, char prevPOS){
    char nextPOS_E;
    nextPOS_E = room[colPOS][rowPOS+1];
    if(nextPOS_E == ' ' || nextPOS_E == '.' || nextPOS_E == '-') {
        room[colPOS][rowPOS] = prevPOS;
        room[colPOS][rowPOS+1] = 'X';
        moveFlag = 1;
        return nextPOS_E;
    }
    switch(nextPOS_E) {
    case '|':
        break;
    case '=':
        break;
    case 'G': // Goblin
        currentMonster = 0;
        moveFlag = 0;
        globalEvent = 3;
        break;
    case 'O':
        currentMonster = 1;
        moveFlag = 0;
        globalEvent = 3;
        break;
    }
    moveFlag = 0;
    return prevPOS;
}


void EventLog(int currentEvent, int monsterName) {
    // struct Player *ptr = &p; 
    // struct Monster *mptr = &m; 

    switch(currentEvent) {
        case 1:
            printf("Use the arrow keys to move and attack, or press 'x' to exit.\n");
            globalEvent = currentEvent;
        break;
        case 2:
            printf("Welcome to the Dungeon, %s!\nUse the arrow keys to move and attack, or press 'x' to exit.\n", p.playerName);
            globalEvent = currentEvent;
        break;
        case 3:
            printf("You swung at the %s with a %s.\n", m.monsterName[monsterName],
            p.playerWeapon);
            globalEvent = currentEvent;
        break;
        case 4:
            printf("You swing at the %s with a %s, but you missed.", m.monsterName[monsterName], 
            p.playerWeapon);
            globalEvent = currentEvent;
        break;
    }
}