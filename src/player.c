#include <rogue.h>

void AskPlayerInfo(Entity* player) {
    char* name;
    char* race;
    char* class;
    char* armor;
    char* weapon;
    char inputString[3];
     //  char + \n

    name = (char*)malloc(33);
    ChooseName(name);
    free(name);
    
    ChooseRace();
    mvgetnstr(24, 20, inputString, 2);
    char input = inputString[0];

    AssignStats(input);
    
    ChooseClass();
    mvgetnstr(30, 20, inputString, 2);
    input = toupper(inputString[0]);
    AssignGear(input);
    
    noecho();           // Hide input again.
    cbreak();           // Set back to raw.
}   
    
void AssignGear(char input) {
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

void AssignStats(char input) {
    switch(input){
        case '0':
            strcpy(player->entityRace, "Human");
            player->entityHP = 10;
        break;
        case '1':
            strcpy(player->entityRace, "Elf");
            player->entityHP = 8;
        break;
        case '2':
            strcpy(player->entityRace, "Dwarf");
            player->entityHP = 12;
        break;
        case '3':
            strcpy(player->entityRace, "Dragonborn");
            player->entityHP = 14;
        break;
        case '4':
            strcpy(player->entityRace, "Gnoll");
            player->entityHP = 14;
        break;
        case '5':
            strcpy(player->entityRace, "Skeleton");
            player->entityHP = 8;
        break;
        case '6':
            strcpy(player->entityRace, "Mantis");
            player->entityHP = 14;
        break;
        case '7':
            strcpy(player->entityRace, "Robot");
            player->entityHP = 12;
        break;
        case '8':
            strcpy(player->entityRace, "Werewolf");
            player->entityHP = 14;
        break;
        case '9':
            strcpy(player->entityRace, "Vampire");
            player->entityHP = 10;
        break;
        default:
            strcpy(player->entityRace, "Human");
            player->entityHP = 10;
        break;
    }
}

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


void ChooseName(char* name) {
    echo();             
    nocbreak();         
    mvprintw(18, 40, "Please Enter your name: ");
    mvgetnstr(20, 44, name, 32);
    strcpy(player->entityName, name);
}

Entity* CreatePlayer(Position start_pos) {
    Entity* player = calloc(1, sizeof(Entity));
    player->pos.y = start_pos.y;
    player->pos.x = start_pos.x;
    player->ch = 'X';
    player->color = COLOR_PAIR(VISIBLE_COLOR);

    return player;
}

// Decide what to do with input.
// Collision determined here as well.
void PlayerInput(int input) {
    // Get new coordinates.
    Position newPos = { player->pos.y, player->pos.x };

    switch(input) {
        //move up
        case 'A':
            newPos.y--;
            break;
        //move down
        case 'B':
            newPos.y++;
            break;
        //move left
        case 'D':
            newPos.x--;
            break;
        //move right
        case 'C':
            newPos.x++;
            break;
        default:
            break;
    }
    MovePlayer(newPos);
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
