#include <rogue.h>
#define TOTAL_WEAPONS 14 
#define TOTAL_ARMORS 5
#define TOTAL_AMMOS 2

void LowLevelChestLoot(Entity* chest){
    int randWeapon, randCurrency, randArmor, randAmmo, randQuantity;
    randAmmo = (rand() % TOTAL_AMMOS) + 1; // 50% chance to spawn with arrows or bullets
    randQuantity = (rand() % 4) + 1; 
    while (randQuantity) {
        randWeapon = (rand() % TOTAL_WEAPONS) + 1; 
        switch  (randWeapon){
            case 1:
            AddToNPCInventory(chest, items[DAGGER], 1);
            break;
            case 2:
            AddToNPCInventory(chest, items[SHORTSWORD], 1);
            break;
            case 3:
            AddToNPCInventory(chest, items[QUARTERSTAFF], 1);
            break;
            case 4:
            AddToNPCInventory(chest, items[LONGSWORD], 1);
            break;
            case 5:
            AddToNPCInventory(chest, items[CUTLASS], 1);
            break;
            case 6:
            AddToNPCInventory(chest, items[SCIMITAR], 1);
            break;
            case 7:
            AddToNPCInventory(chest, items[GREATSWORD], 1);
            break;
            case 8:
            AddToNPCInventory(chest, items[CHROME_FISTS], 1);
            break;
            case 9:
            AddToNPCInventory(chest, items[ACID_POTION], 1);
            break;
            case 10:
            AddToNPCInventory(chest, items[SHORTBOW], 1);
            break;
            case 11:
            AddToNPCInventory(chest, items[LONGBOW], 1);
            break;
            case 12:
            AddToNPCInventory(chest, items[FLINTLOCK_PISTOL], 1);
            break;
            case 13:
            AddToNPCInventory(chest, items[LIGHTNING_WAND], 1);
            break;
            case 14:
            AddToNPCInventory(chest, items[DUAL_FLINTLOCKS], 1);
            break;
            default:
            break;
        }
        randQuantity--;
    }
    randQuantity = (rand() % 2) + 1; 
    while (randQuantity) {
        randArmor = (rand() % TOTAL_ARMORS) + 1; 
        switch(randArmor){
            case 1:
            AddToNPCInventory(chest, items[RAGS], 1);
            break;
            case 2:
            AddToNPCInventory(chest, items[LEATHER_ARMOR], 1);
            break;
            case 3:
            AddToNPCInventory(chest, items[CHAINMAIL], 1);
            break;
            case 4:
            AddToNPCInventory(chest, items[ROBES], 1);
            break;
            case 5:
            AddToNPCInventory(chest, items[RANGERS_CLOAK], 1);
            break;
            default:
            break;
        }
        randQuantity--;
    }
    switch(randAmmo){
        case 1:
        randQuantity = (rand() % 14) + 6;
        AddToNPCInventory(chest, items[ARROWS], randQuantity);
        break;
        case 2:
        randQuantity = (rand() % 14) + 6;
        AddToNPCInventory(chest, items[BULLET_MUSKET], randQuantity);
        break;
        default:
        break;
    }
    // randCurrency = (rand() % 7) + 1; // 1-7 "gold"
}
