#include <rogue.h>

void GoblinWarriorLoot(Entity* goblin){
    int randWeapon, randCurrency;
    randWeapon = (rand() % QUARTERSTAFF) + DAGGER;
    switch(randWeapon){
        case DAGGER:
        goblin->entityWeapon = Dagger();
        AddToNPCInventory(goblin, items[DAGGER], 1);
        break;
        case SHORTSWORD:
        goblin->entityWeapon = Shortsword();
        AddToNPCInventory(goblin, items[SHORTSWORD], 1);
        break;
        case QUARTERSTAFF:
        goblin->entityWeapon = Quarterstaff();
        AddToNPCInventory(goblin, items[QUARTERSTAFF], 1);
        break;
        default:
        goblin->entityWeapon = Shortsword();
        AddToNPCInventory(goblin, items[SHORTSWORD], 1);
        break;
    }
    // randCurrency = (rand() % 5) + 1; // 1-5 "gold"
}

void KoboldWarriorLoot(Entity* kobold){
    int randWeapon, randCurrency;
    randWeapon = (rand() % QUARTERSTAFF) + DAGGER;
    switch(randWeapon){
        case DAGGER:
        kobold->entityWeapon = Dagger();
        AddToNPCInventory(kobold, items[DAGGER], 1);
        break;
        case SHORTSWORD:
        kobold->entityWeapon = Shortsword();
        AddToNPCInventory(kobold, items[SHORTSWORD], 1);
        break;
        case QUARTERSTAFF:
        kobold->entityWeapon = Quarterstaff();
        AddToNPCInventory(kobold, items[QUARTERSTAFF], 1);
        break;
        default:
        kobold->entityWeapon = Shortsword();
        AddToNPCInventory(kobold, items[SHORTSWORD], 1);
        break;
    }
    // randCurrency = (rand() % 5) + 1; // 1-5 "gold"
}


void HobGoblinWarriorLoot(Entity* hobGoblin){
    int randWeapon, randCurrency;
    randWeapon = (rand() % SCIMITAR) + LONGSWORD;
    switch(randWeapon){
        case LONGSWORD:
        hobGoblin->entityWeapon = Longsword();
        AddToNPCInventory(hobGoblin, items[LONGSWORD], 1);
        break;
        case CUTLASS:
        hobGoblin->entityWeapon = Cutlass();
        AddToNPCInventory(hobGoblin, items[CUTLASS], 1);
        break;
        case SCIMITAR:
        hobGoblin->entityWeapon = Scimitar();
        AddToNPCInventory(hobGoblin, items[SCIMITAR], 1);
        break;
        default:
        hobGoblin->entityWeapon = Scimitar();
        AddToNPCInventory(hobGoblin, items[SCIMITAR], 1);
        break;
    }
    // randCurrency = (rand() % 7) + 1; // 1-7 "gold"
}
