#include <rogue.h>
#define DMG_BUFFER 8

void CastCharge(){
    ChargePlacement();
    player->playerStats.mana -= (player->equippedAbility.manaCost);
    // combatHistory->defender.hasMoved = true; // "stun" the enemy.
}

void CastDash() {
    int ch;
    int x = player->pos.x;
    int y = player->pos.y;
    Cursor(y, x, 1);
    strcpy(combatHistory->event, "Choose a direction to Dash.");
    QueueEvent(q, combatHistory->event);
    while((ch = getch()) != 10 && ch != 32 && !(CheckEscape(ch))) {
        RemoveCursor(y, x, 1);
        x = player->pos.x;
        y = player->pos.y;
        Cursor(y, x, 1);
        switch(ch) {
            //move up
            case KEY_UP:
                if (y <= 0) {
                    break;
                }
                else {
                    RemoveCursor(y, x, 1);
                    y = y - player->equippedAbility.range;
                    while(!DashPOSHelper(x, y)) {
                        y++;
                    }
                }
            break;
            //move down
            case KEY_DOWN:
                if (y >= 50) {
                    break;
                }
                else {
                    RemoveCursor(y, x, 1);
                    y = y + player->equippedAbility.range;
                    while(!DashPOSHelper(x, y)) {
                        y--;
                    }
                }
                break;
            //move left
            case KEY_LEFT:
                if (x <= 0) {
                    break;
                }
                else {
                    RemoveCursor(y, x, 1);
                    x = x - player->equippedAbility.range;
                    while(!DashPOSHelper(x, y)) {
                        x++;
                    }
                }
                break;
            case KEY_RIGHT:
                if (x >= 125) {
                    break;
                }
                else {
                    RemoveCursor(y, x, 1);
                    x = x + player->equippedAbility.range;
                    while(!DashPOSHelper(x, y)) {
                        x--;
                    }
                }
                break;
            default:
                Cursor(y, x, 1);
                break;
            }
        Cursor(y, x, 1);
    }
    if ((CheckEscape(ch))) {
        return;
    }
    Position dashPOS;
    dashPOS.y = y;
    dashPOS.x = x;
    if (map[y][x].noCollision && (GetDistance(player->pos, dashPOS) <= (player->equippedAbility.range)) && map[y][x].visible){
        player->pos.y = y;
        player->pos.x = x;
        player->playerStats.mana -= (player->equippedAbility.manaCost);
        ClearFOV(player);
        MakeFOV(player);
    }
    else{
        strcpy(combatHistory->event, "Too far away to Dash.");
        QueueEvent(q, combatHistory->event);
    }
}

void CastDrainLife(){
    if ((combatHistory->playerResult)) {
        char eventDMGBuffer[DMG_BUFFER];
        strcpy(combatHistory->event, "You drain your enemy of life force,");
        QueueEvent(q, combatHistory->event);
        int healVal = (combatHistory->playerDMG) / 2; // Divide Damage by 2 for HP gained.
        if(((player->playerStats.HP) + healVal) >= (player->playerStats.maxHP)) {
            strcpy(combatHistory->event, "healing to full for ");
            snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d.", ((player->playerStats.maxHP) - (player->playerStats.HP)));
            strcat(combatHistory->event, eventDMGBuffer);
            QueueEvent(q, combatHistory->event);
            player->playerStats.HP = player->playerStats.maxHP;
        }
        else {
            (player->playerStats.HP) += healVal;
            strcpy(combatHistory->event, "healing yourself for ");
            snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d.", healVal);
            strcat(combatHistory->event, eventDMGBuffer);
            QueueEvent(q, combatHistory->event);
            
        }
        player->playerStats.mana -= (player->equippedAbility.manaCost);
    }
}

void CastIceArmor(){
    if (player->passiveAbility.abilityID == NO_ABILITY) {
        strcpy(combatHistory->event, "You're covered in an icy embrace.");
        QueueEvent(q, combatHistory->event);
        int shieldVal = player->equippedAbility.miscStat;
        player->playerStats.AC += shieldVal;
        player->abilityTimer = player->equippedAbility.duration;
        player->passiveAbility = player->equippedAbility;
        player->playerStats.mana -= (player->equippedAbility.manaCost);
    }
    else {
        strcpy(combatHistory->event, "That spell is still active.");
        QueueEvent(q, combatHistory->event);
    }
}

void CastVengeance() {
    if (player->passiveAbility.abilityID == NO_ABILITY) {
        strcpy(combatHistory->event, "You prepare to retaliate.");
        QueueEvent(q, combatHistory->event);
        player->abilityTimer = player->equippedAbility.duration;
        player->passiveAbility = player->equippedAbility;
        player->playerStats.mana -= (player->equippedAbility.manaCost);
    }
    else {
        strcpy(combatHistory->event, "That spell is still active.");
        QueueEvent(q, combatHistory->event);
    }
}

void CastSecondWind(){
    if(player->playerStats.HP != player->playerStats.maxHP) {
        char eventDMGBuffer[DMG_BUFFER];
        int healValFull = (player->playerStats.maxHP) - (player->playerStats.HP);
        int healVal = (rand() % (player->equippedAbility.maxDMG)) + (player->equippedAbility.minDMG);
        combatHistory->playerCombat = false;
        strcpy(combatHistory->event, "You mend your wounds.");
        QueueEvent(q, combatHistory->event);

        if(((player->playerStats.HP) + healVal) >= (player->playerStats.maxHP)) {
            strcpy(combatHistory->event, "You heal yourself for ");
            snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d.", healValFull);
            strcat(combatHistory->event, eventDMGBuffer);
            QueueEvent(q, combatHistory->event);
            player->playerStats.HP = player->playerStats.maxHP;
            player->playerStats.mana -= (player->equippedAbility.manaCost);
        }
        else {
            (player->playerStats.HP) += healVal;
            strcpy(combatHistory->event, "You heal yourself for ");
            snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d.", healVal);
            strcat(combatHistory->event, eventDMGBuffer);
            QueueEvent(q, combatHistory->event);
            player->playerStats.mana -= (player->equippedAbility.manaCost);
        }
    }
    else{
        strcpy(combatHistory->event, "You are already at full HP.");
        QueueEvent(q, combatHistory->event);
    }
}

void CastSummonSkeleton() {
    int ch;
    int x = player->pos.x;
    int y = player->pos.y;
    if (player->passiveAbility.abilityID == NO_ABILITY) {
        player->abilityTimer = player->equippedAbility.duration;
        player->passiveAbility = player->equippedAbility;
    }
    else {
        strcpy(combatHistory->event, "Your skeleton is still active.");
        QueueEvent(q, combatHistory->event);
        return;
    }

    Cursor(y, x, 1);
    strcpy(combatHistory->event, "Choose where to place a skeleton.");
    QueueEvent(q, combatHistory->event);
    while((ch = getch()) != 10 && ch != 32 && !(CheckEscape(ch))) {
        RemoveCursor(y, x, 1);
        x = player->pos.x;
        y = player->pos.y;
        Cursor(y, x, 1);
        switch(ch) {
            //move up
            case KEY_UP:
                if (y <= 0 || y == y - 1) break;
                else {
                    RemoveCursor(y, x, 1);
                    y--;
                }
                break;
            //move down
            case KEY_DOWN:
                if (y >= 50 || y == y + 1) break;
                else {
                    RemoveCursor(y, x, 1);
                    y++;
                }
                break;
            //move left
            case KEY_LEFT:
                if (x <= 0 || x == x - 1) break;
                else {
                    RemoveCursor(y, x, 1);
                    x--;
                }
                break;
            case KEY_RIGHT:
                if (x >= 125 || x == x + 1) break;
                else {
                    RemoveCursor(y, x, 1);
                    x++;
                }
                break;
            default:
                Cursor(y, x, 1);
                break;
            }
        Cursor(y, x, 1);
    }
    if ((CheckEscape(ch))) {
        return;
    }
    Position skeletonPOS;
    skeletonPOS.y = y;
    skeletonPOS.x = x;
    if (map[y][x].noCollision && map[y][x].visible && map[y][x].entityType != CHEST){
        AssignFloor(x,y);
        player->playerStats.mana -= (player->equippedAbility.manaCost);
        // int NPCInList = AddToNPCList(nptr, skeletonPOS, NPC_SKELETON_WARRIOR);
        player->follower = AddToNPCList(nptr, skeletonPOS, NPC_SKELETON_WARRIOR);
        player->follower.hasMoved = true;
        UpdateNPCMap(nptr, MAX_ONSCREEN_NPCS);
        UpdateFollower(&player->follower);
        UpdateNPCVisible(nptr, player);
        ClearFOV(player);
        MakeFOV(player);
    }
    else{
        player->abilityTimer = 0;
        player->equippedAbility.abilityID = NO_ABILITY;
        player->passiveAbility.abilityID = NO_ABILITY;
        strcpy(combatHistory->event, "Could not Place skeleton.");
        QueueEvent(q, combatHistory->event);
    }
}

/* 
Undoes the bonus provided by fire volley in precombat effects.
Since the bonus is given prior to combat, the casted version removes the bonus since casts occur after player's attack.
*/
void CastFireVolley(){
    player->playerStats.mana -= (player->equippedAbility.manaCost);
    if(CheckPlayerAdjacent(combatHistory->defender.pos)) {
        player->equippedAbility.abilitySave -= 10;
    }
    else if (GetDistance(player->pos, combatHistory->defender.pos) <= 3) {
        player->equippedAbility.abilitySave -= 4;
    } 
}

void CastSelfRepair(){
    if(player->playerStats.HP != player->playerStats.maxHP) {
        char eventDMGBuffer[DMG_BUFFER];
        combatHistory->playerCombat = false;
        strcpy(combatHistory->event, "You repair your metal frame.");
        QueueEvent(q, combatHistory->event);
        int repairVal = (rand() % (player->equippedAbility.maxDMG)) + (player->equippedAbility.minDMG);
        if(((player->playerStats.HP) + repairVal) >= (player->playerStats.maxHP)) {
            player->playerStats.HP = player->playerStats.maxHP;
        }
        else {
            (player->playerStats.HP) += repairVal;
        }
        player->playerStats.mana -= (player->equippedAbility.manaCost);
        strcpy(combatHistory->event, "You heal yourself for ");
        snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d.", repairVal);
        strcat(combatHistory->event, eventDMGBuffer);
        QueueEvent(q, combatHistory->event);
    }
    else {
        strcpy(combatHistory->event, "You are already at full HP.");
        QueueEvent(q, combatHistory->event);
    }
}
