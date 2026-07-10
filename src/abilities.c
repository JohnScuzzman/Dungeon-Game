#include <rogue.h>
#define DMG_BUFFER 8
#define MAX_ENTITY 


void CastCharge(){
    ChargePlacement();
    player->playerStats.mana -= (player->equippedAbility.manaCost);
    // combatHistory->defender.hasMoved = true; // "stun" the enemy.
}

void ChargePlacement(){
    if((player->pos.x) < (combatHistory->defender.pos.x) && (player->pos.y) < (combatHistory->defender.pos.y)) {
        player->pos.x = ((combatHistory->defender.pos.x) - 1);
        player->pos.y = ((combatHistory->defender.pos.y) - 1);
        return;
    }
    else if ((player->pos.x) < (combatHistory->defender.pos.x) && (player->pos.y) > (combatHistory->defender.pos.y)){
        player->pos.x = ((combatHistory->defender.pos.x) - 1);
        player->pos.y = ((combatHistory->defender.pos.y) + 1);
        return;
    }
    else if ((player->pos.x) > (combatHistory->defender.pos.x) && (player->pos.y) < (combatHistory->defender.pos.y)){
        player->pos.x = ((combatHistory->defender.pos.x) + 1);
        player->pos.y = ((combatHistory->defender.pos.y) - 1);
        return;
    }
    else if ((player->pos.x) > (combatHistory->defender.pos.x) && (player->pos.y) > (combatHistory->defender.pos.y)){
        player->pos.x = ((combatHistory->defender.pos.x) + 1);
        player->pos.y = ((combatHistory->defender.pos.y) + 1);
        return;
    }
    else if ((player->pos.x) > (combatHistory->defender.pos.x) && (player->pos.y) == (combatHistory->defender.pos.y)){
        player->pos.x = ((combatHistory->defender.pos.x) + 1);
        return;
    }
    else if ((player->pos.x) < (combatHistory->defender.pos.x) && (player->pos.y) == (combatHistory->defender.pos.y)){
        player->pos.x = ((combatHistory->defender.pos.x) - 1);
        return;
    }
    else if ((player->pos.x) == (combatHistory->defender.pos.x) && (player->pos.y) > (combatHistory->defender.pos.y)){
        player->pos.y = ((combatHistory->defender.pos.y) + 1);
        return;
    }
    else if ((player->pos.x) == (combatHistory->defender.pos.x) && (player->pos.y) < (combatHistory->defender.pos.y)){
        player->pos.y = ((combatHistory->defender.pos.y) - 1);
        return;
    }
}

void CastDash() {
    int ch;
    int x = player->pos.x;
    int y = player->pos.y;
    Cursor(y, x, 1);
    strcpy(combatHistory->event, "Choose a direction to Dash.");
    QueueEvent(q, combatHistory->event);
    // char event[] = "Choose a direction to Dash.";
    // DrawCombatEvent(event);
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


bool DashPOSHelper(int x, int y) {
    if (map[y][x].noCollision) {
        return true;
    }
    if (y == player->pos.y && x == player->pos.x){
        return true;
    }
    return false;
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
    DrawCombatLog();

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
    if (map[y][x].noCollision && map[y][x].visible){
        player->playerStats.mana -= (player->equippedAbility.manaCost);
        // int NPCInList = AddToNPCList(nptr, skeletonPOS, NPC_SKELETON_WARRIOR);
        player->follower = AddToNPCList(nptr, skeletonPOS, NPC_SKELETON_WARRIOR);
        ClearFOV(player);
        MakeFOV(player);
    }
    else{
        strcpy(combatHistory->event, "Could not Place skeleton.");
        QueueEvent(q, combatHistory->event);
    }
}

/* 
Undoes the bonus provided by fire volley in precombat effects.
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

void RemoveSummonSkeleton() {
    Entity emptyNPC = {0};

    // Try and remove the NPC from the map here.
    player->passiveAbility = NoAbility();
    AssignFloor(player->follower.pos.x, player->follower.pos.y);
    nptr[player->follower.entityID] = emptyNPC;
    player->follower = emptyNPC;

    strcpy(combatHistory->event, "Your skeleton crumbles to dust.");
    QueueEvent(q, combatHistory->event);
}

/* When Ice Armors duration is up, remove the armor.*/
void RemoveIceArmor(){
    strcpy(combatHistory->event, "You're icy armor melts.");
    QueueEvent(q, combatHistory->event);
    int shieldVal = player->passiveAbility.miscStat;
    player->playerStats.AC -= shieldVal;
    player->passiveAbility = NoAbility();
}

void RemoveVengeance(){
    strcpy(combatHistory->event, "You're thirst for revenge fades.");
    QueueEvent(q, combatHistory->event);
    player->passiveAbility = NoAbility();
}

/* Only applies to abilities that are attacks with effects.*/
void PostCombatEffects() {
    if (player->equippedAbility.postCombatEffects) {
        PostCombatAbilities(player->equippedAbility.abilityID);
    }
    player->equippedAbility = NoAbility();
}

void PreCombatEffects() {
    if (player->equippedAbility.preCombatEffects) {
        PreCombatAbilities(player->equippedAbility.abilityID);
    }
}


/* Called if the players input is processed in UsePlayerAbility from player.c, including attacking a monster.*/
/* Handles both attacks and non attacking abilities.*/
/* This runs before the monster attacks back, so healing the player will save them from an otherwise killing blow.*/
/* If an ability is just an attack with no effects, no CastAbility function is needed.*/
void PostCombatAbilities(int abilityID){
    if ((player->playerStats.mana) >= (player->equippedAbility.manaCost)) {
        switch (abilityID) {
        case CHARGE: CastCharge();
            break;
        case DASH: CastDash();
            break;
        case DRAIN_LIFE: CastDrainLife();
            break;
        case FIRE_VOLLEY: CastFireVolley();
            break;
        case ICE_ARMOR: CastIceArmor();
            break;
        case SECOND_WIND: CastSecondWind();
            break;
        case SELF_REPAIR: CastSelfRepair();
            break;
        case SUMMON_SKELETON: CastSummonSkeleton();
            break;
        case VENGEANCE:
            ResetCombatHistory();
            CastVengeance();
            break;
        default:
            break;
        }

        return;
    }
    else if ((player->playerStats.mana) < (player->equippedAbility.manaCost) && !(player->equippedAbility.isAttack)) {
        NotEnoughMana();
    }
}

/*
Same as above, but happens prior to combat.
*/
void PreCombatAbilities(int abilityID) {
    if ((player->playerStats.mana) >= (player->equippedAbility.manaCost)) {
        switch (abilityID) {
            case FIRE_VOLLEY:
                if(CheckPlayerAdjacent(combatHistory->defender.pos)) {
                    player->equippedAbility.abilitySave += 10;
                }
                else if (GetDistance(player->pos, combatHistory->defender.pos) <= 3) {
                    player->equippedAbility.abilitySave += 4;
                } 
                break;
            default:
                break;
        }
    }
}

/* If the player has an active passive ability, deincrement the timer.*/
/* If the timer reaches 0, undo the effects cooresponding to the ability.*/
void CheckPassiveAbilities(int n_monsters) {
    if(!DeincrementAbilityTimer()) {
        ResetPassiveAbility(player->passiveAbility.abilityID);
    }
    switch(player->passiveAbility.abilityID) {
        case VENGEANCE:
            if((combatHistory->attackerDMG > 0) && (combatHistory->defender.entityType == MONSTER)) {
                strcpy(combatHistory->event, "You take vengeance on your enemy.");
                QueueEvent(q, combatHistory->event);
                Entity* target = FindMonsterInList(combatHistory->defender.entityID, n_monsters);
                if (target->entityType == MONSTER) {
                    combatHistory->playerCombat = AttackEntity(target, combatHistory, player, n_monsters);
                    ResetCombatHistory();
                }
            }
            break;
        case SUMMON_SKELETON:
            for (int i = 0; i < n_monsters; i++) {
                if (CheckMonsterAdjacent(player->follower.pos, (mptr + i)) && (mptr + i)->entityType != CORPSE) {
                    // make them attack monster if there is one adjacent
                    if(NPCAttackEntity(&player->follower, (mptr + i), combatHistory, n_monsters)) return;
                }
            }
            if (!player->follower.hasMoved) {
                FollowPlayer(&player->follower);
                player->follower.hasMoved = false;
            }
            else player->follower.hasMoved = false;
            break;
        default:
            break;
    }
}


/* Returns true if the abilityTimer was deincremented.*/
bool DeincrementAbilityTimer() {
    if ((player->abilityTimer) > 0) {
        player->abilityTimer--;
        return true;
    }
    return false;
}

void ResetPassiveAbility(int abilityID) {
        switch (abilityID) {
        case ICE_ARMOR:
            RemoveIceArmor();
        break;
        case SUMMON_SKELETON:
            RemoveSummonSkeleton();
        break;
        case VENGEANCE:
            RemoveVengeance();
        break;
        default:
            player->passiveAbility = NoAbility();
        break;
    }

}


/* Called from PlayerRangedAttack in player.c*/
/* We use PlayerRangedAttack since melee abilities technically have a range of 1.*/
/* A normal melee attack is made when a player simply moves into a monster, range of 0.*/
/* Thus to differentiate a melee ability, we borrow the RangedAttack function. */
/* PlayerRanged is in combat.c and PostCombatAbilities is in abilities.c*/
/* If False, dont charge the player for mana yet, look for it later in PostCombatEffects in engine.c*/
bool UsePlayerAbility(int n_monsters, int chosenAbility) {
    combatHistory->playerUsedAbility = true;
    player->equippedAbility = player->playerClass.abilities[chosenAbility];
    if(player->equippedAbility.isAttack) {
        if(PlayerRangedAttack(n_monsters) && !(player->equippedAbility.postCombatEffects)) {
            player->playerStats.mana -= player->equippedAbility.manaCost;
            return true;
        }
        else{
            return false;
        }
    }
    else {
            PostCombatAbilities(player->equippedAbility.abilityID);
            return true;
        }
    return false;
}
