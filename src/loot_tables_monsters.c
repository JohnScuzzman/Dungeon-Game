#include <rogue.h>

void GoblinWarriorLoot(Entity* goblin){
    int randWeapon, randCurrency;
    randWeapon = (rand() % (QUARTERSTAFF - DAGGER) + 1) + DAGGER;
    AddToNPCInventory(goblin, items[randWeapon], 1);
    goblin->entityWeapon = GetWeaponFromItem(randWeapon);
    // randCurrency = (rand() % 5) + 1; // 1-5 "gold"
}

void KoboldWarriorLoot(Entity* kobold){
    int randWeapon, randCurrency;
    randWeapon = (rand() % (QUARTERSTAFF - DAGGER) + 1) + DAGGER;
    AddToNPCInventory(kobold, items[randWeapon], 1);
    kobold->entityWeapon = GetWeaponFromItem(randWeapon);
    // randCurrency = (rand() % 5) + 1; // 1-5 "gold"
}

void SkeletonWarriorLoot(Entity* skeleton){
    int randWeapon, randCurrency;
    randWeapon = (rand() % (SCIMITAR - DAGGER) + 1) + DAGGER;
    AddToNPCInventory(skeleton, items[randWeapon], 1);
    skeleton->entityWeapon = GetWeaponFromItem(randWeapon);
    // randCurrency = (rand() % 5) + 1; // 1-5 "gold"
}

void HobGoblinWarriorLoot(Entity* hobGoblin){
    int randWeapon, randCurrency;
    randWeapon = (rand() % (SCIMITAR - LONGSWORD) + 1) + LONGSWORD;
    AddToNPCInventory(hobGoblin, items[randWeapon], 1);
    hobGoblin->entityWeapon = GetWeaponFromItem(randWeapon);
    // randCurrency = (rand() % 7) + 1; // 1-7 "gold"
}
