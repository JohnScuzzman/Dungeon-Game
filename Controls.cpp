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


char roomUI[100][100];
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
As we move, swap new int we will access and move to it by swapping the ints with players POS.
If we encounter a wall or enemy, disallow a move.
If we encounter an enemy, go into the combat loop held in EventLog at the bottom.
*/
void Move(int **room1, int **room2, int colPOS, int rowPOS, int prevPOS) {
    char input;
    int POS = prevPOS;

    // Clear Console.
    std::system("clear");

    // Print Banner.
    EventLog(2, currentMonster);

    //Get Player's Name
    printf("\n                              Please enter your name: ");
    scanf("%30[0-9a-zA-Z ]", p.playerName);

    strcpy(p.playerWeapon, b.blades[1]);
    strcpy(p.playerArmor, a.armors[0]);
    p.playerWeaponDMG = b.shortSword;
    p.playerArmorAC = a.leatherArmor;


    // Clear Console.
    std::system("clear");

    // Place monsters and print the floor & UI.
    PlaceMonsters(room1, room2, 69);
    CreateUI(room2, roomUI, p);
    EventLog(1, currentMonster);
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
                POS = MoveNorth(room1, room2, colPOS, rowPOS, POS);
                if(moveFlag){
                    colPOS--;
                }
                break;

                case 'D':
                POS = MoveWest(room1, room2, colPOS, rowPOS, POS);
                if(moveFlag) {
                    rowPOS--;
                }
                break;

                case 'B':
                POS = MoveSouth(room1, room2, colPOS, rowPOS, POS);
                if(moveFlag) {
                    colPOS++;
                }
                break;

                case 'C':
                POS = MoveEast(room1, room2, colPOS, rowPOS, POS);
                if(moveFlag) {
                    rowPOS++;
                }
                break;
            }
        MoveMonsters(room1, room2);
        CreateUI(room2, roomUI, p);
        EventLog(globalEvent, currentMonster);
        globalEvent = 1;
        
    }
    disableRawMode();
}

int MoveNorth(int **room1, int **room2, int colPOS, int rowPOS, int prevPOS) {
    
    int nextPOS_N;
    // Save Next int we will overwrite with 99/X (Player).
    nextPOS_N = room1[colPOS-1][rowPOS];

    // Check if valid, move player if so.
    if(nextPOS_N == 0 || nextPOS_N == 4) {
        room1[colPOS][rowPOS] = prevPOS;
        room1[colPOS-1][rowPOS] = 99;
        room2[colPOS][rowPOS] = prevPOS;
        room2[colPOS-1][rowPOS] = 99;
        moveFlag = 1;
        return nextPOS_N;
    }

    // Run if collision occurs
    switch(nextPOS_N) {
    case 1: // Wall
        break;
    case 2:
        break;
    case 11: // Goblin
        currentMonster = 0;
        moveFlag = 0;
        globalEvent = 3;
        break;
    case 13: // Orc
        currentMonster = 1;
        globalEvent = 3;
        moveFlag = 0;
        break;
    }
    moveFlag = 0;
    return prevPOS;
}

int MoveWest(int **room1, int **room2, int colPOS, int rowPOS, int prevPOS) {
    int nextPOS_W;
    nextPOS_W = room1[colPOS][rowPOS-1];
    if(nextPOS_W == 0 || nextPOS_W == 4) {
        room1[colPOS][rowPOS] = prevPOS;
        room1[colPOS][rowPOS-1] = 99;
        room2[colPOS][rowPOS] = prevPOS;
        room2[colPOS][rowPOS-1] = 99;
        moveFlag = 1;
        return nextPOS_W;
    }
    switch(nextPOS_W) {
    case 1: // Wall
        break;
    case 2:
        break;
    case 11: // Goblin
        currentMonster = 0;
        moveFlag = 0;
        globalEvent = 3;
        break;
    case 13: // Orc
        currentMonster = 1;
        globalEvent = 3;
        moveFlag = 0;
        break;
    }
    moveFlag = 0;
    return prevPOS;
}

int MoveSouth(int **room1,int **room2, int colPOS, int rowPOS, int prevPOS) {
    int nextPOS_S;
    nextPOS_S = room1[colPOS+1][rowPOS];
    if(nextPOS_S == 0 || nextPOS_S == 4) {
        room1[colPOS][rowPOS] = prevPOS;
        room1[colPOS+1][rowPOS] = 99;
        room2[colPOS][rowPOS] = prevPOS;
        room2[colPOS+1][rowPOS] = 99;
        moveFlag = 1;
        return nextPOS_S;
    }

    switch(nextPOS_S) {
    case 1: // Wall
        break;
    case 2:
        break;
    case 11: // Goblin
        currentMonster = 0;
        moveFlag = 0;
        globalEvent = 3;
        break;
    case 13: // Orc
        currentMonster = 1;
        globalEvent = 3;
        moveFlag = 0;
        break;
    }
    moveFlag = 0;
    return prevPOS;
}

int MoveEast(int **room1,int **room2, int colPOS, int rowPOS, int prevPOS){
    int nextPOS_E;
    nextPOS_E = room1[colPOS][rowPOS+1];
    if(nextPOS_E == 0 || nextPOS_E == 4){
        room1[colPOS][rowPOS] = prevPOS;
        room1[colPOS][rowPOS+1] = 99;
        room2[colPOS][rowPOS] = prevPOS;
        room2[colPOS][rowPOS+1] = 99;
        moveFlag = 1;
        return nextPOS_E;
    }
    switch(nextPOS_E) {
    case 1: // Wall
        break;
    case 2:
        break;
    case 11: // Goblin
        currentMonster = 0;
        moveFlag = 0;
        globalEvent = 3;
        break;
    case 13: // Orc
        currentMonster = 1;
        globalEvent = 3;
        moveFlag = 0;
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
        //File reading variables.
        FILE *fptr;
        char buffer[255];
            fptr = fopen("Banner.txt", "r");
        if (fptr == NULL) {
            printf("Error: Could not open banner file.\n");
            break;
        }
        while (fgets(buffer, 255, fptr)) {
            printf("%s", buffer);
        }
        fclose(fptr);
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