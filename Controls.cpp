#include <cstdlib>
#include <unistd.h>
//#include <ctype.h>
#include <stdio.h>
#include "tables.h"
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
void PrintFloor(int **room);
char MoveNorth(int **room, int colPOS, int rowPOS, char prevPOS);
char MoveWest(int **room, int colPOS, int rowPOS, char prevPOS);
char MoveSouth(int **room, int colPOS, int rowPOS, char prevPOS);
char MoveEast(int **room, int colPOS, int rowPOS, char prevPOS);
void EventLog(int currentEvent, int monsterName);
void enableRawMode();
int moveFlag = 0;
int globalEvent = 1;
int currentMonster = 0;

/*
All of the game loops happens here in the move function.
Start the player off with a Short Sword and Leather Armor, then run main game loop.
As we move, swap new char we will access and move to it by swapping the chars with players POS.
If we encounter a wall or enemy, disallow a move.
If we encounter an enemy, go into the combat loop held in EventLog at the bottom.
*/
void Move(int **room, int colPOS, int rowPOS, char prevPOS) {

    char input;
    char POS = prevPOS;
    
    strcpy(p.playerWeapon, b.blades[1]);
    strcpy(p.playerArmor, a.armors[0]);
    p.playerWeaponDMG = b.shortSword;
    p.playerArmorAC = a.leatherArmor;
    EventLog(2, currentMonster);
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

        PrintFloor(room);
        EventLog(globalEvent, currentMonster);
        globalEvent = 1;
        
    }
}

char MoveNorth(int **room, int colPOS, int rowPOS, char prevPOS) {
    
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
        EventLog(3, currentMonster);
        break;
    case 'O':
        currentMonster = 1;
        moveFlag = 0;
        EventLog(3, currentMonster);
        break;
    }
    moveFlag = 0;
    return prevPOS;
}
char MoveWest(int **room, int colPOS, int rowPOS, char prevPOS) {
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
        EventLog(3, currentMonster);
        break;
    case 'O':
        currentMonster = 1;
        moveFlag = 0;
        EventLog(3, currentMonster);
        break;
    }
    moveFlag = 0;
    return prevPOS;
}
char MoveSouth(int **room, int colPOS, int rowPOS, char prevPOS) {
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
        EventLog(3, currentMonster);
        break;
    case 'O':
        currentMonster = 1;
        moveFlag = 0;
        EventLog(3, currentMonster);
        break;
    }
    moveFlag = 0;
    return prevPOS;
}
char MoveEast(int **room, int colPOS, int rowPOS, char prevPOS){
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
        EventLog(3, currentMonster);
        break;
    case 'O':
        currentMonster = 1;
        moveFlag = 0;
        EventLog(3, currentMonster);
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
            printf("Choose a direction W, A, S, D, or X to exit.\n");
            globalEvent = currentEvent;
        break;
        case 2:
            printf("Welcome to the Dungeon!\nChoose a direction W, A, S, D, or X to exit.\n");
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