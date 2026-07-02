#include <rogue.h>
#define TOTAL_AMMOS 2

// formula for random items is (max - min + 1) + min;
void LowLevelChestLoot(Entity* chest){
    int randWeapon, randCurrency, randArmor, randAmmo, randQuantity;
    randAmmo = (rand() % TOTAL_AMMOS) + 1; // 50% chance to spawn with arrows or bullets
    randQuantity = (rand() % 3) + 1; 
    while (randQuantity) {
        randWeapon = (rand() % ((_RANGED_ - 1) - DAGGER) + 1) + DAGGER; 
        AddToNPCInventory(chest, items[randWeapon], 1);
        randQuantity--;
    }
    randQuantity = (rand() % 3) + 1; 
    while (randQuantity) {
        randWeapon = (rand() % ((_AMMO_ - 1) - SLINGSHOT) + 1) + SLINGSHOT; 
        AddToNPCInventory(chest, items[randWeapon], 1);
        randQuantity--;
    }
    randQuantity = (rand() % 2) + 1; 
    while (randQuantity) {
        randArmor = (rand() % ((_END_ - 1) - RAGS) + 1) + RAGS; 
        AddToNPCInventory(chest, items[randArmor], 1);
        randQuantity--;
    }
    randQuantity = (rand() % 14) + 6;
    switch(randAmmo){
        case 1:
        randQuantity = (rand() % 14) + 6;
        AddToNPCInventory(chest, items[ARROWS], randQuantity);
        break;
        case 2:
        randQuantity = (rand() % 14) + 6;
        AddToNPCInventory(chest, items[BULLET_FLINTLOCK], randQuantity);
        break;
        default:
        break;
    }
    // randCurrency = (rand() % 7) + 1; // 1-7 "gold"
}
