#include <rogue.h>

// formula for random items is (max - min + 1) + min;
void LowLevelChestLoot(Entity* chest){
    int randWeapon, randCurrency, randArmor, randAmmo, randQuantity;
    randQuantity = (rand() % 3); 
    while (randQuantity) {
        randWeapon = (rand() % ((_RANGED_ - 1) - DAGGER) + 1) + DAGGER; 
        AddToNPCInventory(chest, items[randWeapon], 1);
        randQuantity--;
    }
    randQuantity = (rand() % 3); 
    while (randQuantity) {
        randWeapon = (rand() % ((_AMMO_ - 1) - SLINGSHOT) + 1) + SLINGSHOT; 
        AddToNPCInventory(chest, items[randWeapon], 1);
        randQuantity--;
    }
    randQuantity = (rand() % 2); 
    while (randQuantity) {
        randArmor = (rand() % ((_END_ - 2) - RAGS) + 1) + RAGS; 
        AddToNPCInventory(chest, items[randArmor], 1);
        randQuantity--;
    }
    randAmmo = (rand() % 8) + 1; // small chance to spawn with arrows or bullets
    switch(randAmmo){
        case 1:
        randQuantity = (rand() % 20) + 4;
        AddToNPCInventory(chest, items[ARROWS], randQuantity);
        break;
        case 2:
        randQuantity = (rand() % 14) + 6;
        AddToNPCInventory(chest, items[BULLET_FLINTLOCK], randQuantity);
        break;
        case 3:
        randQuantity = (rand() % 12) + 6;
        AddToNPCInventory(chest, items[BULLET_9MM], randQuantity);
        break;
        case 4:
        randQuantity = (rand() % 12) + 6;
        AddToNPCInventory(chest, items[BULLET_45], randQuantity);
        break;
        case 5:
        randQuantity = (rand() % 7) + 1;
        AddToNPCInventory(chest, items[BULLET_50CAL], randQuantity);
        break;
        default:
        break;
    }
    // randCurrency = (rand() % 7) + 1; // 1-7 "gold"
}
