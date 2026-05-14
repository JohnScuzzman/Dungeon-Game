#include <rogue.h>

/* 
Reads the main menu's scroll ASCII art and prints it to the screen.
*/
void TitleScreen() {

    /* File reading variables. */
        FILE *fptr;
        char buffer[255];
            fptr = fopen("res/Banner.txt", "r");
        if (fptr != NULL) {
            while (fgets(buffer, 255, fptr)) {
            printw(" %s", buffer);
        }
        if (fptr == NULL){
            printw(" Error: Could not open banner file.\n");
        }
    }
    fclose(fptr);
}

