#include <stdio.h>
#include <string.h>

#define INFO_SIZE 32

typedef struct Info{
        char info[INFO_SIZE][INFO_SIZE] = {"Name: ", "Race: ", "Class: ", "Current HP: ", "Weapon Equipped: ", "Armor Equipped: "};
    } info_t;