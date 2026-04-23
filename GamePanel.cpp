#include <stdio.h>
#include <stdlib.h> // Used for random num generation.
#include <time.h> // Used for seed generation.
#include "tables.h"
#define FLOOR_SIZE_MAX 100
#define FLOOR '.'
#define wallW '='
#define wallL '|'

struct Monster m1;
int **CreateFloor(int row, int col);
int CreateRoom(int **room, int spacesUsedCol, int spacesUsedRow, int currentSeed);
void FreeUpRoom(int **room, int row);
void PrintFloor(int **room);
void BannerW();
void BannerL();
int *RNG();
void PlaceMonsters(int **room, int floorSizeToPrint);
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
int **CreateFloor(int row, int col) {
    
    // Dynamically allocate memory for array before use.
    int **room = (int **)malloc(row * sizeof(int *));
    if (room == NULL) {
        exit(EXIT_FAILURE);; // Handle failure.
    }
     // Allocate memory for each row and col
    for (int i = 0; i < row; i++) {
        room[i] = (int *)malloc(col * sizeof(int));
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
int CreateRoom(int **room, int spacesUsedCol, int spacesUsedRow, int currentSeed) {
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
        break;
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

    room[floorSizeToPrint - 9][floorSizeToPrint - 3] = 'G';
     //PLACE PLAYER
    room[floorSizeToPrint - 8][floorSizeToPrint - 2] = 'X';
    return (r1); // return length of room we just made.
}
    
   
void PlaceMonsters(int **room, int floorSizeToPrint) {
    int monstersToPlace = 4;
    int row = 0;
    int col = 1;
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < monstersToPlace; j++) {
            printf("Attempting to place monster at: %d, %d\n", (seeds[row] % 100) + row, (seeds[col] % 100) + col);
            
            if (room[(seeds[row] % 100) + row][(seeds[col] % 100) + col] == '|') {
                room[(seeds[row] % 100) + row][(seeds[col] % 100) + col - 1] = 'G';
                row += seeds[i] % 100;
                col += seeds[j] % 100;
                
            }
            if (room[(seeds[row] % 100) + row][(seeds[col] % 100) + col] == '=') {
                room[(seeds[row] % 100) + row - 1][(seeds[col] % 100) + col] = 'G';
                row += seeds[i] % 100;
                col += seeds[j] % 100;
            }
            else{ 
                room[(seeds[row] % 100) + row][(seeds[col] % 100) + col] = 'G';
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
            printf("2: Attempting to place monster at: %d, %d\n", row - (seeds[row] % 100), (seeds[col] % 100) + col);
            if (room[(seeds[col] % 100) + col][row - (seeds[row] % 100)] == '|') {
                room[(seeds[col] % 100) + col][row - 1 - (seeds[row] % 100)] = 'G';
                row -= seeds[i] % 100;
                col += seeds[j] % 100;
            }
            if (room[(seeds[col] % 100) + col][row - (seeds[row] % 100)] == '=') {
                room[(seeds[col] % 100) + col - 1][row - (seeds[row] % 100)] = 'G';
                row -= seeds[i] % 100;
                col += seeds[j] % 100;
            }
            else {
                room[(seeds[col] % 100) + col][row - (seeds[row] % 100)] = 'G';
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


// void PlaceMonsters(int **room, int floorSizeToPrint) {
//     int monstersToPlace = 30;
//     for (int i = 0; i < floorSizeToPrint; i++) {
//         for (int j = 0; j < floorSizeToPrint; j++){
//             if (room[(seeds[i] % 10)][(seeds[j] % 10)] != wallL &&
//             room[(seeds[i] % 10)][(seeds[j] % 10)] != wallW && monstersToPlace){
//                 room[((seeds[i] % 10))][(seeds[j] % 10)] = 'G';
//                 monstersToPlace--;
//                 i = i + seeds[i] % 10;
//                 j = j + seeds[j] % 10;
//             }
//         }   
//     }
// }


void PrintFloor(int **room) {
    //Print entire floor
    for (int i = 0; i < floorSizeToPrint - 5; i++) {
        for (int j = 0; j < floorSizeToPrint + 1; j++){
            if ((i == 0 || i == floorSizeToPrint || (room[i][j] == wallW && room[i][j+1] == wallW)) && j < floorSizeToPrint)
            {
                printf("%c=", room[i][j]);
            }
            else {
                printf("%c ", room[i][j]);
            }
        }  
        printf("\n");
    }
}

void FreeUpRoom(int **room, int row) {
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
