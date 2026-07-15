#include <rogue.h>
/* 
Helper function that reads a file into a string buffer.
*/
char* FileToString(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (buffer) {
        fread(buffer, 1, length, file);
        buffer[length] = '\0';
    }
    fclose(file);
    return buffer;
}

/* 
Converts a player struct to a JSON file, then saves it to the pass in filename.
*/
bool SavePlayerToJSON(const char *filename, const Player* player) {
    // Create root JSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) return false;

    // Add fields to the JSON object
    cJSON_AddBoolToObject(root, "noCollision", player->noCollision);
    cJSON_AddBoolToObject(root, "isResting", player->isResting);
    cJSON_AddStringToObject(root, "ch", &player->ch);
    cJSON_AddNumberToObject(root, "raceID", player->raceID);
    cJSON_AddNumberToObject(root, "color", player->color);
    cJSON_AddNumberToObject(root, "abilityTimer", player->abilityTimer);
    cJSON_AddNumberToObject(root, "invTail", player->invTail);
    cJSON_AddNumberToObject(root, "invHead", player->invHead);
    cJSON_AddItemToObject(root, "playerStats", SerializePlayerStats(&player->playerStats));
    cJSON_AddItemToObject(root, "playerPosition", SerializePlayerPOS(&player->pos));
    cJSON_AddItemToObject(root, "equippedMelee", SerializePlayerWeapon(&player->equippedMelee));
    cJSON_AddItemToObject(root, "equippedRanged", SerializePlayerWeapon(&player->equippedRanged));
    cJSON_AddItemToObject(root, "equippedAmmo", SerializePlayerAmmo(&player->equippedAmmo));
    cJSON_AddItemToObject(root, "equippedArmor", SerializePlayerArmor(&player->equippedArmor));
    cJSON_AddItemToObject(root, "equippedAbility", SerializePlayerAbility(&player->equippedAbility));
    cJSON_AddItemToObject(root, "passiveAbility", SerializePlayerAbility(&player->passiveAbility));
    cJSON_AddItemToObject(root, "playerClass", SerializePlayerClass(&player->playerClass));
    cJSON_AddItemToObject(root, "inventory", SerializePlayerInventory(player));
    cJSON_AddItemToObject(root, "follower", SerializeEntity(&player->follower));
    cJSON_AddStringToObject(root, "playerName", player->playerName);
    cJSON_AddStringToObject(root, "playerRace", player->playerRace);
    
    // Convert JSON object to a string
    char *json_string = cJSON_Print(root);
    if (!json_string) {
        cJSON_Delete(root);
        return false;
    }

    // Write the string to a file
    FILE *file = fopen(filename, "w");
    if (!file) {
        free(json_string);
        cJSON_Delete(root);
        return false;
    }
    fprintf(file, "%s", json_string);

    // Clean up memory and file pointers
    fclose(file);
    free(json_string);
    cJSON_Delete(root);
    return true;
}

/* Helper functions for the nested player structs*/
cJSON* SerializePlayerStats(const Stats* playerStats) {
    cJSON* playerStatsObj = cJSON_CreateObject();
    if (playerStatsObj == NULL) return NULL;

    cJSON_AddNumberToObject(playerStatsObj, "ATK", playerStats->ATK);
    cJSON_AddNumberToObject(playerStatsObj, "CHA", playerStats->CHA);
    cJSON_AddNumberToObject(playerStatsObj, "CON", playerStats->CON);
    cJSON_AddNumberToObject(playerStatsObj, "DEX", playerStats->DEX);
    cJSON_AddNumberToObject(playerStatsObj, "INT", playerStats->INT);
    cJSON_AddNumberToObject(playerStatsObj, "STR", playerStats->STR);
    cJSON_AddNumberToObject(playerStatsObj, "WIS", playerStats->WIS);
    cJSON_AddNumberToObject(playerStatsObj, "AC", playerStats->AC);
    cJSON_AddNumberToObject(playerStatsObj, "HP", playerStats->HP);
    cJSON_AddNumberToObject(playerStatsObj, "mana", playerStats->mana);
    cJSON_AddNumberToObject(playerStatsObj, "maxHP", playerStats->maxHP);
    cJSON_AddNumberToObject(playerStatsObj, "maxMana", playerStats->maxMana);
    cJSON_AddNumberToObject(playerStatsObj, "LVL", playerStats->LVL);
    cJSON_AddNumberToObject(playerStatsObj, "EXP", playerStats->EXP);
    cJSON_AddNumberToObject(playerStatsObj, "nextLVLEXP", playerStats->nextLVLEXP);
    cJSON_AddNumberToObject(playerStatsObj, "maxDMG", playerStats->maxDMG);
    cJSON_AddNumberToObject(playerStatsObj, "minDMG", playerStats->minDMG);

    return playerStatsObj;
}

cJSON* SerializePlayerPOS(const Position* pos) {
    cJSON* playerPOSObj = cJSON_CreateObject();
    if (playerPOSObj == NULL) return NULL;

    cJSON_AddNumberToObject(playerPOSObj, "y", pos->y);
    cJSON_AddNumberToObject(playerPOSObj, "x", pos->x);

    return playerPOSObj;
}

cJSON* SerializeItem(const Item* item) {
    cJSON* itemObj = cJSON_CreateObject();
    if (itemObj == NULL) return NULL;

    cJSON_AddBoolToObject(itemObj, "equippable", item->equippable);
    cJSON_AddBoolToObject(itemObj, "lootable", item->lootable);
    cJSON_AddBoolToObject(itemObj, "unequippable", item->unequippable);
    cJSON_AddBoolToObject(itemObj, "isEquipped", item->isEquipped);
    cJSON_AddNumberToObject(itemObj, "itemID", item->itemID);
    cJSON_AddNumberToObject(itemObj, "quantity", item->quantity);
    cJSON_AddNumberToObject(itemObj, "type", item->type);
    cJSON_AddNumberToObject(itemObj, "value", item->value);
    cJSON_AddStringToObject(itemObj, "itemName", item->itemName);
    cJSON_AddStringToObject(itemObj, "itemDesc", item->itemDesc);

    return itemObj;
}

cJSON* SerializePlayerWeapon(const Weapon* equippedMelee) {
    cJSON* playerWeaponObj = cJSON_CreateObject();
    if (playerWeaponObj == NULL) return NULL;

    // 1. Serialize the nested structure into its own cJSON object
    cJSON* weaponItemObj = SerializeItem(&equippedMelee->item);
    
    // 2. Attach the nested object to the root object
    if (weaponItemObj != NULL) {
        cJSON_AddItemToObject(playerWeaponObj, "weaponItemObj", weaponItemObj);
    }
    
    cJSON_AddBoolToObject(playerWeaponObj, "isMagic", equippedMelee->isMagic);
    cJSON_AddBoolToObject(playerWeaponObj, "isEnchanted", equippedMelee->isEnchanted);
    cJSON_AddBoolToObject(playerWeaponObj, "isRanged", equippedMelee->isRanged);
    cJSON_AddNumberToObject(playerWeaponObj, "capacity", equippedMelee->capacity);
    cJSON_AddNumberToObject(playerWeaponObj, "enchantLevel", equippedMelee->enchantLevel);
    cJSON_AddNumberToObject(playerWeaponObj, "minDMG", equippedMelee->minDMG);
    cJSON_AddNumberToObject(playerWeaponObj, "maxDMG", equippedMelee->maxDMG);
    cJSON_AddNumberToObject(playerWeaponObj, "range", equippedMelee->range);
    cJSON_AddNumberToObject(playerWeaponObj, "ammoType", equippedMelee->ammoType);
    cJSON_AddNumberToObject(playerWeaponObj, "ammoType", equippedMelee->ammoType);
    cJSON_AddNumberToObject(playerWeaponObj, "statUsed", equippedMelee->statUsed);
    cJSON_AddNumberToObject(playerWeaponObj, "statReq", equippedMelee->statReq);

    return playerWeaponObj;
}


cJSON* SerializePlayerAmmo(const Ammo* equippedAmmo) {
    cJSON* playerAmmoObj = cJSON_CreateObject();
    if (playerAmmoObj == NULL) return NULL;

    cJSON* AmmoItemObj = SerializeItem(&equippedAmmo->item);

    if (AmmoItemObj != NULL) {
        cJSON_AddItemToObject(playerAmmoObj, "AmmoItemObj", AmmoItemObj);
    }
    
    cJSON_AddNumberToObject(playerAmmoObj, "bonusDamage", equippedAmmo->bonusDamage);
    cJSON_AddNumberToObject(playerAmmoObj, "type", equippedAmmo->type);

    return playerAmmoObj;
}


cJSON* SerializePlayerArmor(const Armor* equippedArmor) {
    cJSON* playerArmorObj = cJSON_CreateObject();
    if (playerArmorObj == NULL) return NULL;

    cJSON* ArmorItemObj = SerializeItem(&equippedArmor->item);

    if (ArmorItemObj != NULL) {
        cJSON_AddItemToObject(playerArmorObj, "ArmorItemObj", ArmorItemObj);
    }
    
    cJSON_AddNumberToObject(playerArmorObj, "AC", equippedArmor->AC);
    cJSON_AddNumberToObject(playerArmorObj, "type", equippedArmor->type);
    cJSON_AddNumberToObject(playerArmorObj, "statUsed", equippedArmor->type);
    cJSON_AddNumberToObject(playerArmorObj, "statReq", equippedArmor->type);


    return playerArmorObj;
}


cJSON* SerializePlayerAbility(const Ability* ability) {
    cJSON* playerAbilityObj = cJSON_CreateObject();

    if (playerAbilityObj == NULL) return NULL;

    cJSON_AddBoolToObject(playerAbilityObj, "isAttack", ability->isAttack);
    cJSON_AddBoolToObject(playerAbilityObj, "isMagic", ability->isMagic);
    cJSON_AddBoolToObject(playerAbilityObj, "isRanged", ability->isRanged);
    cJSON_AddBoolToObject(playerAbilityObj, "preCombatEffects", ability->preCombatEffects);
    cJSON_AddBoolToObject(playerAbilityObj, "postCombatEffects", ability->postCombatEffects);
    cJSON_AddNumberToObject(playerAbilityObj, "abilityID", ability->abilityID);
    cJSON_AddNumberToObject(playerAbilityObj, "duration", ability->duration);
    cJSON_AddNumberToObject(playerAbilityObj, "minDMG", ability->minDMG);
    cJSON_AddNumberToObject(playerAbilityObj, "maxDMG", ability->maxDMG);
    cJSON_AddNumberToObject(playerAbilityObj, "manaCost", ability->manaCost);
    cJSON_AddNumberToObject(playerAbilityObj, "range", ability->range);
    cJSON_AddNumberToObject(playerAbilityObj, "abilitySave", ability->abilitySave);
    cJSON_AddNumberToObject(playerAbilityObj, "miscStat", ability->miscStat);
    cJSON_AddStringToObject(playerAbilityObj, "abilityName", ability->abilityName);
    cJSON_AddStringToObject(playerAbilityObj, "abilityDesc", ability->abilityDesc);

    return playerAbilityObj;
}

cJSON* SerializePlayerClass(const Class* class) {
    cJSON* playerClassObj = cJSON_CreateObject();

    if (playerClassObj == NULL) return NULL;

    cJSON_AddBoolToObject(playerClassObj, "isCaster", class->isCaster);
    cJSON_AddNumberToObject(playerClassObj, "classID", class->classID);
    cJSON_AddNumberToObject(playerClassObj, "hpPerLVL", class->hpPerLVL);
    cJSON_AddNumberToObject(playerClassObj, "manaPerLVL", class->manaPerLVL);
    cJSON_AddNumberToObject(playerClassObj, "mainStat", class->mainStat);
    cJSON_AddNumberToObject(playerClassObj, "secondaryStat", class->secondaryStat);

    cJSON* abilityArray = cJSON_CreateArray();
    if (abilityArray == NULL) return NULL;
     // /* MAY NOT WORK IF "abilityObj" CANNOT BE HAVE THE SAME NAME, MIGHT HAVE TO BE DONE MANUALLY */
    for(int i = 0; i < MAX_ABILITIES; i++){
        cJSON* abilityObj = SerializePlayerAbility(&class->abilities[i]);

        if (abilityObj != NULL) {
            cJSON_AddItemToArray(abilityArray, abilityObj);
        }

    }

    cJSON_AddStringToObject(playerClassObj, "className", class->className);
    cJSON_AddStringToObject(playerClassObj, "classDesc", class->classDesc);

    return playerClassObj;
}

cJSON* SerializePlayerInventory(const Player* player) {
    cJSON* playerInvArray = cJSON_CreateArray();
    if (playerInvArray == NULL) return NULL;
   
    for(int i = 0; i < MAX_INVENTORY_SIZE; i++){
        cJSON* playerItemObj = SerializeItem(&player->inventory[i]);

        if (playerItemObj != NULL) {
            cJSON_AddItemToArray(playerInvArray, playerItemObj);
        }
    }
    return playerInvArray;
}

cJSON* SerializeEntityInventory(const Entity* entity) {
    cJSON* entityInvArray = cJSON_CreateArray();
    if (entityInvArray == NULL) return NULL;
   
    for(int i = 0; i < MAX_INVENTORY_SIZE; i++){
        cJSON* entityItemObj = SerializeItem(&entity->inventory[i]);

        if (entityItemObj != NULL) {
            cJSON_AddItemToArray(entityInvArray, entityItemObj);
        }
    }
    return entityInvArray;
}

cJSON* SerializeEntity(const Entity* entity) {
    cJSON* entityObj = cJSON_CreateObject();
    if (entityObj == NULL) return NULL;
   
    cJSON_AddBoolToObject(entityObj, "aggroFlag", entity->aggroFlag);
    cJSON_AddBoolToObject(entityObj, "hasMoved", entity->hasMoved);
    cJSON_AddBoolToObject(entityObj, "noCollision", entity->noCollision);
    cJSON_AddBoolToObject(entityObj, "seen", entity->seen);
    cJSON_AddBoolToObject(entityObj, "transparent", entity->transparent);
    cJSON_AddBoolToObject(entityObj, "visible", entity->visible);
    cJSON_AddBoolToObject(entityObj, "seenByPlayer", entity->seenByPlayer);
    cJSON_AddBoolToObject(entityObj, "wasLooted", entity->wasLooted);
    cJSON_AddBoolToObject(entityObj, "wasReplaced", entity->wasReplaced);
    cJSON_AddStringToObject(entityObj, "ch", &entity->ch);
    cJSON_AddStringToObject(entityObj, "ch", &entity->staticCh);
    cJSON_AddNumberToObject(entityObj, "aggroRange", entity->aggroRange);
    cJSON_AddNumberToObject(entityObj, "color", entity->color);
    cJSON_AddNumberToObject(entityObj, "entityID", entity->entityID);
    cJSON_AddNumberToObject(entityObj, "entityType", entity->entityType);
    cJSON_AddNumberToObject(entityObj, "invTail", entity->invTail);
    cJSON_AddNumberToObject(entityObj, "invHead", entity->invHead);
    cJSON_AddItemToObject(entityObj, "entityStats", SerializePlayerStats(&entity->entityStats));
    cJSON_AddItemToObject(entityObj, "entityPosition", SerializePlayerPOS(&entity->pos));
    cJSON_AddItemToObject(entityObj, "entityLastPosition", SerializePlayerPOS(&entity->lastPos));
    cJSON_AddItemToObject(entityObj, "entityPlayerLastPosition", SerializePlayerPOS(&entity->playerLastPos));
    cJSON_AddItemToObject(entityObj, "entityMapInfo", SerializeMapInfo(&entity->mapInfo));
    cJSON_AddItemToObject(entityObj, "entityArmor", SerializePlayerArmor(&entity->entityArmor));
    cJSON_AddItemToObject(entityObj, "entityWeapon", SerializePlayerWeapon(&entity->entityWeapon));
    cJSON_AddItemToObject(entityObj, "entityInv", SerializeEntityInventory(entity));
    cJSON_AddStringToObject(entityObj, "entityName", entity->entityName);
    cJSON_AddStringToObject(entityObj, "entityRace", entity->entityRace);
    cJSON_AddStringToObject(entityObj, "entityClass", entity->entityClass);

    return entityObj;
}

cJSON* SerializeMapInfo(const MapInfo* mapInfo) {
    cJSON* mapInfoObj = cJSON_CreateObject();
    if (mapInfoObj == NULL) return NULL;

    cJSON_AddBoolToObject(mapInfoObj, "oldSeen", mapInfo->oldSeen);
    cJSON_AddBoolToObject(mapInfoObj, "newSeen", mapInfo->newSeen);
    cJSON_AddBoolToObject(mapInfoObj, "oldVisible", mapInfo->oldVisible);
    cJSON_AddBoolToObject(mapInfoObj, "newVisible", mapInfo->newVisible);
    cJSON_AddStringToObject(mapInfoObj, "oldChar", &mapInfo->oldChar);
    cJSON_AddStringToObject(mapInfoObj, "newChar", &mapInfo->newChar);
   
    return mapInfoObj;
}

/*
 
Useful cJSON  functions for later 

cJSON_AddNullToObject(object, name)Adds a null value.
cJSON_AddTrueToObject(object, name)Adds a true boolean value.cJSON_AddFalseToObject(object, name)Adds a false boolean value.
cJSON_AddBoolToObject(object, name, b)Adds a boolean value based on the integer/boolean passed in.
cJSON_AddNumberToObject(object, name, n)Adds a numeric value.
cJSON_AddStringToObject(object, name, s)Adds a string value.
cJSON_AddRawToObject(object, name, raw)Adds a raw string of JSON (without escaping).
cJSON_AddObjectToObject(object, name)Adds an empty nested JSON object.
cJSON_AddArrayToObject(object, name)Adds an empty JSON array.
*/