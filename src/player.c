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
    
    ChooseName(name);
    free(name);
    
    ChooseRace();
    mvgetnstr(24, 20, nameBuffer, 2);
    char input = nameBuffer[0];

    AssignStats(input);
    
    ChooseClass();
    mvgetnstr(30, 20, nameBuffer, 2);
    input = toupper(nameBuffer[0]);
    AssignClass(input);

    free(nameBuffer);
    noecho();           // Hide input again.
    cbreak();           // Set back to raw.
}   

/*
Assigns the class chosen by the player to the Entity struct player.
Each method is listed in classes.c
*/
void AssignClass(char input) {
    switch(input){
        case 'A':
            AssignKnight();
            break;
        case 'B':
            AssignSwashbuckler();
            break;
        case 'C':
            AssignWizard();
            break;
        case 'D':
            AssignNecromancer();
            break;
        case 'E':
            AssignGunslinger();
            break;
        case 'F':
            AssignRanger();
            break;
        case 'G':
            AssignDarkKnight();
            break;
        case 'H':
            AssignAlchemist();
            break;
        case 'I':
            AssignConjurer();
            break;
        case 'J':
            AssignCyborg();
            break;
        default:
            AssignKnight();
            break;
    }
}

/*
Assigns stats based on the race chosen by the player.
TODO Currently only adjusts HP, but will later adjust CHA, WIS, STR, etc.
*/
void AssignStats(char input) {
    switch(input){
        case '0':
            strcpy(player->playerRace, "Human");
            player->playerHP = 10;
        break;
        case '1':
            strcpy(player->playerRace, "Elf");
            player->playerHP = 8;
        break;
        case '2':
            strcpy(player->playerRace, "Dwarf");
            player->playerHP = 12;
        break;
        case '3':
            strcpy(player->playerRace, "Dragonborn");
            player->playerHP = 14;
        break;
        case '4':
            strcpy(player->playerRace, "Gnoll");
            player->playerHP = 14;
        break;
        case '5':
            strcpy(player->playerRace, "Skeleton");
            player->playerHP = 8;
        break;
        case '6':
            strcpy(player->playerRace, "Mantis");
            player->playerHP = 14;
        break;
        case '7':
            strcpy(player->playerRace, "Robot");
            player->playerHP = 12;
        break;
        case '8':
            strcpy(player->playerRace, "Werewolf");
            player->playerHP = 14;
        break;
        case '9':
            strcpy(player->playerRace, "Vampire");
            player->playerHP = 10;
        break;
        default:
            strcpy(player->playerRace, "Human");
            player->playerHP = 10;
        break;
    }
}

/*
Prints available races.
*/
void ChooseRace() {
    mvprintw(22, 10, "Please Choose a Race: ");
    mvprintw(22, 40, "0 - Human");
    mvprintw(23, 40, "1 - Elf");
    mvprintw(24, 40, "2 - Dwarf");
    mvprintw(25, 40, "3 - Dragonborn");
    mvprintw(26, 40, "4 - Gnoll");
    mvprintw(22, 60, "5 - Skeleton");
    mvprintw(23, 60, "6 - Mantis");
    mvprintw(24, 60, "7 - Robot");
    mvprintw(25, 60, "8 - Werewolf");
    mvprintw(26, 60, "9 - Vampire");
}

/*
Prints available classes.
*/
void ChooseClass() {
    mvprintw(28, 10, "Please Choose a Class: ");
    mvprintw(28, 40, "A - Knight");
    mvprintw(29, 40, "B - Swashbuckler");
    mvprintw(30, 40, "C - Wizard");
    mvprintw(31, 40, "D - Necromancer");
    mvprintw(32, 40, "E - Gunslinger");
    mvprintw(28, 60, "F - Ranger");
    mvprintw(29, 60, "G - Dark Knight");
    mvprintw(30, 60, "H - Alchemist");
    mvprintw(31, 60, "I - Conjurer");
    mvprintw(32, 60, "J - Cyborg");
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

Player* CreatePlayer(Position start_pos) {
    Player* player = calloc(1, sizeof(Player));
    player->noCollision = false;
    player->pos.y = start_pos.y;
    player->pos.x = start_pos.x;
    player->ch = 'X';
    player->color = COLOR_PAIR(VISIBLE_COLOR);
    AssignFloor(start_pos.x, start_pos.y);
    return player;
}

// Decide what to do with input.
// Collision determined here as well.
bool PlayerInput(int input) {
    // Get new coordinates.
    Position newPos = { player->pos.y, player->pos.x };

    switch(input) {
        //move up
        case 'A':
            newPos.y--;
            MovePlayer(newPos);
            return true;
            break;
        //move down
        case 'B':
            newPos.y++;
            MovePlayer(newPos);
            return true;
            break;
        //move left
        case 'D':
            newPos.x--;
            MovePlayer(newPos);
            return true;
            break;
        //move right
        case 'C':
            newPos.x++;
            MovePlayer(newPos);
            return true;
            break;
        default:
            break;
    }
    return false;
    
}

// Test for floor tile, move if one is detected.
void MovePlayer(Position newPos) { 
  if (map[newPos.y][newPos.x].noCollision) {
    // Update FOV
    ClearFOV(player);
    player->pos.y = newPos.y;
    player->pos.x = newPos.x;
    MakeFOV(player);
  }
}
