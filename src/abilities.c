#include <rogue.h>

/* If an ability does extra things, specify those things with Cast(AbilityName) */


void CastCharge(){
    ChargePlacement();
    player->playerStats.mana -= (player->equippedAbility.manaCost);
    // combatHistory->defender.hasMoved = true; // "stun" the enemy.
}

bool CastDash(int n_monsters) {
    int ch, i;
    int x = player->pos.x;
    int y = player->pos.y;
    strcpy(combatHistory->event, "Choose a direction to Dash.");
    QueueEvent(q, combatHistory->event);
    DrawEverything(n_monsters);
    while((ch = getch()) != 10 && ch != 32 && !(CheckEscape(ch))) {
        RemoveCursor(y, x, 1);
        x = player->pos.x;
        y = player->pos.y;
        Cursor(y, x, 1);
        switch(ch) {
            //move up
            case KEY_UP:
                if (IsInMap(y - (player->equippedAbility.range), x)) {
                    RemoveCursor(y, x, 1);
                    y = y - (player->equippedAbility.range);
                    while(!DashPOSHelper(x, y)) {
                        y++;
                    }
                }
            break;
            //move down
            case KEY_DOWN:
                if (IsInMap(y + (player->equippedAbility.range), x)) {
                    RemoveCursor(y, x, 1);
                    y = y + (player->equippedAbility.range);
                    while(!DashPOSHelper(x, y)) {
                        y--;
                    }
                }
                break;
            //move left
            case KEY_LEFT:
                if (IsInMap(y, x - (player->equippedAbility.range))) {
                    RemoveCursor(y, x, 1);
                    x = x - (player->equippedAbility.range);
                    while(!DashPOSHelper(x, y)) {
                        x++;
                    }
                }
                break;
            case KEY_RIGHT:
                if (IsInMap(y, x + (player->equippedAbility.range))) {
                    RemoveCursor(y, x, 1);
                    x = x + (player->equippedAbility.range);
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
        return false;
    }
    Position dashPOS;
    dashPOS.y = y;
    dashPOS.x = x;
    if (map[y][x].noCollision && (GetDistance(player->pos, dashPOS) <= (player->equippedAbility.range)) && LineOfSight(player->pos, dashPOS)){
        player->pos.y = y;
        player->pos.x = x;
        player->playerStats.mana -= (player->equippedAbility.manaCost);
        ClearFOV(player);
        MakeFOV(player);
        return true;
    }
    else{
        strcpy(combatHistory->event, "Too far away to dash.");
        QueueEvent(q, combatHistory->event);
        return false;
    }
}


bool DashPOSHelper(int x, int y) {
    Position dashPOS;
    dashPOS.y = y;
    dashPOS.x = x;
    if (map[y][x].noCollision && (LineOfSight(player->pos, dashPOS)) && IsInMap(y,x)) {
        return true;
    }
    if (y == player->pos.y && x == player->pos.x){
        return true;
    }
    return false;
}

void CastDrainLife(){
    if ((combatHistory->playerResult)) {
        char eventDMGBuffer[EVENT_SIZE];
        strcpy(combatHistory->event, "You drain your enemy of life force,");
        QueueEvent(q, combatHistory->event);
        int healVal = (combatHistory->playerDMG) / 2; // Divide Damage by 2 for HP gained.
        if(((player->playerStats.HP) + healVal) >= (player->playerStats.maxHP)) {
            strcpy(combatHistory->event, "healing to full for ");
            snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d.", ((player->playerStats.maxHP) - (player->playerStats.HP)));
            strcat(combatHistory->event, eventDMGBuffer);
            QueueEvent(q, combatHistory->event);
            player->playerStats.HP = player->playerStats.maxHP;
            player->playerStats.mana -= (player->equippedAbility.manaCost);
        }
        else {
            (player->playerStats.HP) += healVal;
            strcpy(combatHistory->event, "healing yourself for ");
            snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d.", healVal);
            strcat(combatHistory->event, eventDMGBuffer);
            QueueEvent(q, combatHistory->event);
        }
    }
}

void CastIceArmor(){
    if (player->passiveAbility.abilityID == NO_ABILITY){
        strcpy(combatHistory->event, "You're covered in an icy embrace.");
        QueueEvent(q, combatHistory->event);
        int shieldVal = player->equippedAbility.miscStat;
        player->playerStats.AC += shieldVal;
        player->abilityTimer = player->equippedAbility.duration;
        player->passiveAbility = IceArmor();
        player->playerStats.mana -= (player->equippedAbility.manaCost);
    }
    else {
        strcpy(combatHistory->event, "That spell is still active.");
        QueueEvent(q, combatHistory->event);
    }
}

void CastVengeance() {
    if (player->passiveAbility.abilityID == NO_ABILITY){
        strcpy(combatHistory->event, "You prepare to retaliate.");
        QueueEvent(q, combatHistory->event);
        player->abilityTimer = player->equippedAbility.duration;
        player->passiveAbility = Vengeance();
        player->playerStats.mana -= (player->equippedAbility.manaCost);
    }
    else {
        strcpy(combatHistory->event, "That spell is still active.");
        QueueEvent(q, combatHistory->event);
    }
}

void CastSecondWind(){
    if(player->playerStats.HP != player->playerStats.maxHP){
        char eventDMGBuffer[EVENT_SIZE];
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
        }
    }
    else{
        strcpy(combatHistory->event, "You are already at full HP.");
        QueueEvent(q, combatHistory->event);
    }
}

void CastSelfRepair(){
    if(player->playerStats.HP != player->playerStats.maxHP) {
        char eventDMGBuffer[EVENT_SIZE];
        combatHistory->playerCombat = false;
        strcpy(combatHistory->event, "You repair your metal frame.");
        QueueEvent(q, combatHistory->event);
        int repairVal = (rand() % (player->equippedAbility.maxDMG)) + (player->equippedAbility.minDMG);
        if(((player->playerStats.HP) + repairVal) >= (player->playerStats.maxHP)) {
            player->playerStats.HP = player->playerStats.maxHP;
            player->playerStats.mana -= (player->equippedAbility.manaCost);
        }
        else {
            (player->playerStats.HP) += repairVal;
        }
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
void PostCombatEffects(int n_monsters) {
    if (player->equippedAbility.hasEffects) {
        AbilityEffects(player->equippedAbility.abilityID, n_monsters);
    }
    player->equippedAbility = NoAbility();
}

/* Called if the players input is processed in UsePlayerAbility from player.c, including attacking a monster.*/
/* Handles both attacks and non attacking abilities.*/
/* This runs before the monster attacks back, so healing the player will save them from an otherwise killing blow.*/
/* If an ability is just an attack with no effects, no CastAbility function is needed.*/
bool AbilityEffects(int abilityID, int n_monsters){
    if ((player->playerStats.mana) >= (player->equippedAbility.manaCost)) {
        switch (abilityID) {
            case CHARGE:
                CastCharge();
            break;
            case DASH:
                return CastDash(n_monsters);
            break;
            case DRAIN_LIFE:
                CastDrainLife();
            break;
            case ICE_ARMOR:
                CastIceArmor();
            break;
            case SECOND_WIND:
                CastSecondWind();
            break;
            case SELF_REPAIR:
                CastSelfRepair();
            break;
            case SUMMON_SKELETON:
            break;
            case VENGEANCE:
                CastVengeance();
            break;
            default:
            break;
            }
        return true;
    }
    else if ((player->playerStats.mana) < (player->equippedAbility.manaCost) && !(player->equippedAbility.isAttack)) {
        NotEnoughMana();
        return false;
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
        if(combatHistory->entityResult  && (combatHistory->defender.isMonster)) {
            strcpy(combatHistory->event, "You take vengeance on your enemy.");
            QueueEvent(q, combatHistory->event);
            Entity* target = FindMonsterInList(combatHistory->defender.entityID, n_monsters);
            if (target->isMonster) {
                combatHistory->playerCombat = AttackEntity(target, combatHistory, player);
                ResetCombatHistory();
            }
        }
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
        break;
        case VENGEANCE:
            RemoveVengeance();
        break;
        default:
            player->passiveAbility = NoAbility();
        break;
    }
    
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

/* Called from PlayerRangedAttack in player.c*/
/* We use PlayerRangedAttack since melee abilities technically have a range of 1.*/
/* A normal melee attack is made when a player simply moves into a monster, range of 0.*/
/* Thus to differentiate a melee ability, we borrow the RangedAttack function. */
/* PlayerRanged is in combat.c and AbilityEffects is in abilities.c*/
/* If False, dont charge the player for mana yet, look for it later in PostCombatEffects in engine.c*/
bool UsePlayerAbility(int n_monsters, int chosenAbility) {
    combatHistory->playerUsedAbility = true;
    player->equippedAbility = player->playerClass.abilities[chosenAbility];
    if(player->equippedAbility.isAttack) {
        if(PlayerRangedAttack(n_monsters) && !(player->equippedAbility.hasEffects)) {
            player->playerStats.mana -= player->equippedAbility.manaCost;
            return true;
        }
        else{ 
            return false;
        }
    }
    else {
            return AbilityEffects(player->equippedAbility.abilityID, n_monsters);
        }
    return false;
}
