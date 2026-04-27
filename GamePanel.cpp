#include <stdio.h>
#include <stdlib.h> // Used for random num generation.
#include <time.h> // Used for seed generation.
#include <string.h>
#include "tables.h"
#include "UI.h"
#define FLOOR_SIZE_MAX 100
#define FLOOR '.'
#define wallW '='
#define wallL '|'

struct Info information;
struct Monster m1;

int seeds[256]; // Array to hold 36 random ints, length and width.
int floorSizeToPrint = FLOOR_SIZE_MAX - 31;

int *RNG() {
    time_t t;
    srand(time(&t)); // Make a seed based off the current time.
    
    for(int i = 0; i < 256; i++) {
        seeds[i]= rand() % 10 + 4; // Store the random number in seeds. 3-12
    }
    return seeds;
}
/**
Creates the matrix that we will store our room's chars.
 */
char **CreateFloor(int row, int col) {
    
    // Dynamically allocate memory for array before use.
    char **room = (char **)malloc(row * sizeof(char *));
    if (room == NULL) {
        exit(EXIT_FAILURE);; // Handle failure.
    }
     // Allocate memory for each row and col
    for (int i = 0; i < row; i++) {
        room[i] = (char *)malloc(col * sizeof(char));
        if (room[i] == NULL) {
            // Handle allocation error & free previously allocated memory
            for (int j = 0; j < i; j++) free(room[j]);
            free(room);
            exit(EXIT_FAILURE);
        }
    }
     //Set entire floor to dots and makes boundary walls
    for (int i = 0; i < FLOOR_SIZE_MAX; i++) {
        for (int j = 0; j < FLOOR_SIZE_MAX; j++){ 
            // change -6 based on length of room.
            if((i == 0 || i == floorSizeToPrint -6) && (j > 0 && j < floorSizeToPrint)) {
                room[i][j] = wallW; // =
            } 
            else {
                room[i][j] = FLOOR;
            }
            if((j == 0 || j == floorSizeToPrint) && (i > 0 && i < floorSizeToPrint)) {
                room[i][j] = wallL; // =
            } 
        }  
    }

    room[0][0] = '#';
    room[0][floorSizeToPrint] = '#';
    room[floorSizeToPrint - 6][0] = '#';
    room[floorSizeToPrint - 6][floorSizeToPrint] = '#';
    return room; // Return the pointer to the allocated memory
}

/**
Accepts an x by y matrix, the vertical offset, and horizontal offset.
int **room is the x by y matrix.
int spacesUsedCol is the vertical offset.
int spacesUsedRow is the horizonal offset.
int currentSeed tracks which value in array we are currently using.
 */
int CreateRoom(char **room, int spacesUsedCol, int spacesUsedRow, int currentSeed) {
    int Rows = spacesUsedRow + 1;
    int Cols = spacesUsedCol + 1;
    int r = seeds[currentSeed];
    int r1 = seeds[currentSeed + 1];
    int oneToFourRand = 0;

    // If overlapping room try to move it, if still overlapping, move again.
    // Stick out a little tendril the length of room we are about to place.
    // If path is clear, place, else, increment columns 1 and try again.
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < r1; j++) {
                if ( i == 0 && room[i + Cols + (r % 10)][j + Rows + 1] != FLOOR) {
                    Cols = Cols + 1;
                    j--;
                }
            }
        }
        Cols = Cols + 1;

    // Make a single room of a random size.
    // Place room randomly along a row of the room.
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r1; j++){
            if (i == 0 || i == r - 1){
                room[i + Cols + (r % 10)][j + Rows + 1] = wallW;
            }
            if ((j == 0 && i != 0 && i != r-1) || (j == r1-1 && i != r-1 && i != 0)){
                room[i + Cols + (r % 10)][j + Rows + 1] = wallL;
            }
            // Fills the floor of room with the chosen char.
            if (i > 0 && i < r-1 && j > 0 && j < r1-1) {
                room[i + Cols + (r % 10)][j + Rows + 1] = '-';
            }
        }   
        oneToFourRand = (((seeds[i + currentSeed]) % 4) + 1); //0011223344
    }
    // The Following Creates doors.
    // Creates a random int from 1-4 then places it on a random side.
    
    switch(oneToFourRand) {
        case 1:
        room[Cols + (r % 10) + r/2][Rows + 1] = ' ';
        break;void FreeUpRoom(char **room, int row);
        case 2:
        room[Cols + (r % 10) + r/2][Rows + r1] = ' ';
        break;
        case 3:
        room[Cols + (r % 10)][Rows + r1/2] = ' ';
        break;
        case 4:
        room[Cols + (r % 10) + r - 1][Rows + r1/2 + 1] = ' ';
        break;
        default:
        break;
    }
     //PLACE PLAYER
    room[floorSizeToPrint - 8][floorSizeToPrint - 2] = 'X';

    return (r1); // return length of room we just made.
}
    
void CreateUI(char **room, struct Player p) {

    int counter;

    for (int i = 0; i < floorSizeToPrint - 4; i++) {
        for (int j = floorSizeToPrint + 1; j < FLOOR_SIZE_MAX; j++) {
            if (i == 4 && j > floorSizeToPrint + 2 && j < FLOOR_SIZE_MAX){ // - 16 to keep final '#' at the end/
                room[0][j] = '=';
                room[floorSizeToPrint - 6][j] = '=';
                room[i][j] = information.info[0][counter];
                room[i + 1][j] = p.playerName[counter];
                room[i + 3][j] = information.info[1][counter];
                room[i + 4][j] = p.playerRace[counter];
                room[i + 6][j] = information.info[2][counter];
                room[i + 7][j] = p.playerClass[counter];
                room[i + 9][j] = information.info[3][counter];
                room[i + 10][j] = p.playerHP[counter];
                room[i + 12][j] = information.info[4][counter];
                room[i + 13][j] = p.playerWeapon[counter];

                counter++;
            }
        }  
        counter = 0;
    }

     //Create borders and whitespace first to dodge problems of trying to do it all in one for loop.
    for (int i = 0; i < floorSizeToPrint - 4; i++) {
        for (int j = floorSizeToPrint + 1; j < FLOOR_SIZE_MAX; j++) {
            if (room[i][j] == '.') {
                room[i][j] = ' ';
            }
        }  
    }
}
   
void PlaceMonsters(char **room, int monsterRoom[FLOOR_SIZE_MAX][FLOOR_SIZE_MAX], int floorSizeToPrint) {
    int monstersToPlace = 4;
    int row = 0;
    int col = 1;
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < monstersToPlace; j++) {          
            if (room[(seeds[row] % 100) + row][(seeds[col] % 100) + col] == '|') {
                room[(seeds[row] % 100) + row][(seeds[col] % 100) + col - 1] = 'G';
                monsterRoom[(seeds[col] % 100) + col][row - 1 - (seeds[row] % 100)] = 1;
                row += seeds[i] % 100;
                col += seeds[j] % 100;
                
            }
            if (room[(seeds[row] % 100) + row][(seeds[col] % 100) + col] == '=') {
                room[(seeds[row] % 100) + row - 1][(seeds[col] % 100) + col] = 'G';
                monsterRoom[(seeds[col] % 100) + col][row - 1 - (seeds[row] % 100)] = 1;
                row += seeds[i] % 100;
                col += seeds[j] % 100;
            }
            else{ 
                room[(seeds[row] % 100) + row][(seeds[col] % 100) + col] = 'G';
                monsterRoom[(seeds[col] % 100) + col][row - 1 - (seeds[row] % 100)] = 1;
                row += seeds[i] % 100;
                col += seeds[j] % 100;
            }
            if(row > 58) {
                row = 0;
            }
        }
        col = 0;
        monstersToPlace = 3;
    }
    row = floorSizeToPrint;
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < monstersToPlace; j++) {
            if (room[(seeds[col] % 100) + col][row - (seeds[row] % 100)] == '|') {
                room[(seeds[col] % 100) + col][row - 1 - (seeds[row] % 100)] = 'G';
                monsterRoom[(seeds[col] % 100) + col][row - 1 - (seeds[row] % 100)] = 1;
                row -= seeds[i] % 100;
                col += seeds[j] % 100;
            }
            if (room[(seeds[col] % 100) + col][row - (seeds[row] % 100)] == '=') {
                room[(seeds[col] % 100) + col - 1][row - (seeds[row] % 100)] = 'G';
                monsterRoom[(seeds[col] % 100) + col][row - 1 - (seeds[row] % 100)] = 1;
                row -= seeds[i] % 100;
                col += seeds[j] % 100;
            }
            else {
                room[(seeds[col] % 100) + col][row - (seeds[row] % 100)] = 'G';
                monsterRoom[(seeds[col] % 100) + col][row - 1 - (seeds[row] % 100)] = 1;
                row -= seeds[i] % 100;
                col += seeds[j] % 100;
            }
            if(row < 15) {
                row = floorSizeToPrint;
            }
        }
        col = 0;
        monstersToPlace = 3;
    }
}

void MoveMonsters (char **room1, int room2[100][100]) {
    int counter = 0;
    int oneToFourRand = ((seeds[counter]) % 4); //0011223344

    for (int i = 1; i < floorSizeToPrint - 1; i++) {
        for (int j = 1; j < floorSizeToPrint - 1; j++){ 
            if(room2[i][j] == 1) {
                switch(oneToFourRand) {
                case 1:
                room2[i][j] = 0;
                room2[i][j+1] = 1;
                room1[i][j+1] = 'G';
                room1[i][j] = '.';
                j += 2;
                counter++;
                oneToFourRand = ((seeds[i]) % 4);
                break;
                case 2:
                room2[i][j] = 0;
                room2[i][j-1] = 1;
                room1[i][j-1] = 'G';
                room1[i][j] = '.';
                counter++;
                oneToFourRand = ((seeds[j]) % 4);
                break;
                case 3:
                room2[i][j] = 0;
                room2[i+1][j] = 1;
                room1[i+1][j] = 'G';
                room1[i][j] = '.';
                oneToFourRand = ((seeds[i]) % 4);
                counter++;
                i += 2;
                break;
                case 4:
                room2[i][j] = 0;
                room2[i-1][j] = 1;
                room1[i-1][j] = 'G';
                room1[i][j] = '.';
                oneToFourRand = ((seeds[j]) % 4);
                counter++;
                break;
                default:
                counter++;
                break;
            }
            } 
            counter = 0;
        }  
    }
}


/** 
Prints the floor passed in.
*/
void PrintFloor(char **room) {
    //Print entire floor
    for (int i = 0; i < floorSizeToPrint - 5; i++) {
        for (int j = 0; j < FLOOR_SIZE_MAX - 1; j++) {
                if ((room[i][j] == wallW && room[i][j+1] == wallW) && j < FLOOR_SIZE_MAX - 1) {
                    printf("%c=", room[i][j]);
                }
                else {
                    printf("%c ", room[i][j]);
                }
            }
        printf("\n");
    }
}


void FreeUpRoom(char **room, int row) {
    for (int i = 0; i < row; i++) {
        free(room[i]); // Free each row
    }
    free(room); // Free the array of pointers
}



// char *b = "bbbbb" is another way to declare a string in C

// COPYING STRINGS
// char a[10];
// char b[10];
// scanf("%9s", b);
// strncpy(a,b,9); // copy 9 chars (a strings addr) from b to a.

// CONCAT STRINGS
// char *strncat(char *dest, const cahr *src, size_t n)
// char a[n] = "hi";
// char b[10] = "bye";
// strncat(a,b,n-strlen(a)); // appends all chars (a strings addr) from b to a.

// STRING SEARCH
// char *strstr(const char *haystack, const char *needle);
// finds entire string & the null terminator
// char *strrchr(const char *str, char c)
// searches for the first occurrence of the char c.

// STRING TOKENS 
// char str[80] = "This is - www.tutorialspoint.com - website";
// const char s[2] = "-";
// char *token;

// get first token with token = strtok(str,s);
// while (token != NULL)
// {
//  printf("%s\n", token);
//  token = strtok(NULL,s);
// }
