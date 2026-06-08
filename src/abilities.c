#include <rogue.h>


/* These initialize the abilities and are equipped to the player.*/
/* If no special effects, treat like a normal ranged attack.*/
/* Melee attack abilities have a range of 1.*/

Ability NoAbility() {
    Ability noAbility;
    noAbility.isAttack = false;
    noAbility.isMagic = false;
    noAbility.hasEffects = false;
    noAbility.abilityID = NO_ABILITY;
    noAbility.duration = 0;
    noAbility.minDMG = 0;
    noAbility.maxDMG = 0;
    noAbility.manaCost = 0;
    noAbility.range = 0;
    noAbility.abilitySave = 0;
    noAbility.miscStat = 0;
    strcpy(noAbility.abilityName, "None");
    strcpy(noAbility.abilityDesc, "none");
    return noAbility;
}

Ability AimedShot() {
    Ability aimedShot;
    aimedShot.isAttack = true;
    aimedShot.isMagic = false;
    aimedShot.hasEffects = false;
    aimedShot.abilityID = AIMED_SHOT;
    aimedShot.duration = 0;
    aimedShot.minDMG = (player->equippedRanged.minDMG) + 1;
    aimedShot.maxDMG = (player->equippedRanged.maxDMG) + 1;
    aimedShot.manaCost = 3;
    aimedShot.range = (player->equippedRanged.range);
    aimedShot.abilitySave = (player->playerStats.ATK) + 10;
    aimedShot.miscStat = 0; 
    strcpy(aimedShot.abilityName, "Aimed Shot");
    strcpy(aimedShot.abilityDesc, "none");
    return aimedShot;
}

Ability Charge() {
    Ability charge;
    charge.isAttack = true;
    charge.isMagic = false;
    charge.hasEffects = true;
    charge.abilityID = CHARGE;
    charge.duration = 0;
    charge.minDMG = (player->equippedMelee.minDMG) + 3;
    charge.maxDMG = (player->equippedMelee.maxDMG) + 3;
    charge.manaCost = 4;
    charge.range = 5;
    charge.abilitySave = (player->playerStats.ATK) + 5;
    charge.miscStat = 0;
    strcpy(charge.abilityName, "Charge");
    strcpy(charge.abilityDesc, "none");
    return charge;
}

Ability DrainLife() {
    Ability drainLife;
    drainLife.isAttack = true;
    drainLife.isMagic = true;
    drainLife.hasEffects = true;
    drainLife.abilityID = DRAIN_LIFE;
    drainLife.duration = 0;
    drainLife.minDMG = 4;
    drainLife.maxDMG = 10;
    drainLife.manaCost = 4;
    drainLife.range = 1;
    drainLife.abilitySave = (player->playerStats.ATK) + 6;
    drainLife.miscStat = 0;
    strcpy(drainLife.abilityName, "Drain Life");
    strcpy(drainLife.abilityDesc, "none");
    return drainLife;
}

Ability Electrify() {
    Ability electrify;
    electrify.isAttack = true;
    electrify.isMagic = false;
    electrify.hasEffects = false;
    electrify.abilityID = ELECTRIFY;
    electrify.duration = 0;
    electrify.minDMG = 1;
    electrify.maxDMG = 6;
    electrify.manaCost = 2;
    electrify.range = 3;
    electrify.abilitySave = (player->playerStats.ATK) + 3;
    electrify.miscStat = 0;
    strcpy(electrify.abilityName, "Electrify");
    strcpy(electrify.abilityDesc, "none");
    return electrify;
}

Ability FireVolley() {
    Ability fireVolley;
    fireVolley.isAttack = true;
    fireVolley.isMagic = false;
    fireVolley.hasEffects = false;
    fireVolley.abilityID = FIRE_VOLLEY;
    fireVolley.duration = 0;
    fireVolley.minDMG = (player->equippedRanged.minDMG);
    fireVolley.maxDMG = (player->equippedRanged.maxDMG);
    fireVolley.manaCost = 5;
    fireVolley.range = 5;
    fireVolley.abilitySave = (player->playerStats.ATK) + 3;
    fireVolley.miscStat = (player->playerStats.LVL); // number of shots fired.
    fireVolley.miscStat++;
    fireVolley.minDMG = (fireVolley.minDMG) * (fireVolley.miscStat);
    fireVolley.maxDMG = (fireVolley.minDMG) * (fireVolley.miscStat);
    strcpy(fireVolley.abilityName, "Fire Volley");
    strcpy(fireVolley.abilityDesc, "none");
    return fireVolley;
}

// Give player a shield based on its min/max DMG
Ability IceArmor() {
    Ability iceArmor;
    iceArmor.isAttack = false;
    iceArmor.isMagic = true;
    iceArmor.hasEffects = true;
    iceArmor.abilityID = ICE_ARMOR;
    iceArmor.duration = 240;
    iceArmor.minDMG = 0;
    iceArmor.maxDMG = 0;
    iceArmor.manaCost = 10;
    iceArmor.range = 0;
    iceArmor.abilitySave = 0;
    iceArmor.miscStat = 5; // AC gained
    strcpy(iceArmor.abilityName, "Ice Armor");
    strcpy(iceArmor.abilityDesc, "none");
    return iceArmor;
}

Ability MagicMissile() {
    Ability magicMissile;
    magicMissile.isAttack = true;
    magicMissile.isMagic = true;
    magicMissile.hasEffects = false;
    magicMissile.abilityID = MAGIC_MISSILE;
    magicMissile.duration = 0;
    magicMissile.minDMG = (player->playerStats.LVL) + 1; //3d4 then 4d4 etc
    magicMissile.maxDMG = ((player->playerStats.LVL) * 4) + 1;
    magicMissile.manaCost = 4;
    magicMissile.range = 15;
    magicMissile.abilitySave = 40; // hard to miss with MM
    magicMissile.miscStat = 3; // number of missiles shot
    strcpy(magicMissile.abilityName, "Magic Missile");
    strcpy(magicMissile.abilityDesc, "none");
    return magicMissile;
}

// heals player from minDMG to maxDMG
Ability SecondWind() {
    Ability secondWind;
    secondWind.isAttack = false;
    secondWind.isMagic = false;
    secondWind.hasEffects = true;
    secondWind.abilityID = SECOND_WIND;
    secondWind.duration = 0;
    secondWind.minDMG = 2;
    secondWind.maxDMG = 8;
    secondWind.manaCost = 7;
    secondWind.range = 0;
    secondWind.abilitySave = 0;
    secondWind.miscStat = ((rand() % secondWind.maxDMG) + secondWind.minDMG);
    strcpy(secondWind.abilityName, "Second Wind");
    strcpy(secondWind.abilityDesc, "none");
    return secondWind;
}

Ability SelfRepair() {
    Ability selfRepair;
    selfRepair.isAttack = false;
    selfRepair.isMagic = false;
    selfRepair.hasEffects = true;
    selfRepair.abilityID = SELF_REPAIR;
    selfRepair.duration = 0;
    selfRepair.minDMG = 1;
    selfRepair.maxDMG = 6;
    selfRepair.manaCost = 5;
    selfRepair.range = 0;
    selfRepair.abilitySave = 0;
    selfRepair.miscStat = ((rand() % selfRepair.maxDMG) + selfRepair.minDMG);
    strcpy(selfRepair.abilityName, "Self Repair");
    strcpy(selfRepair.abilityDesc, "none");
    return selfRepair;
}

Ability SummonSkeleton() {
    Ability summonSkeleton;
    summonSkeleton.isAttack = false;
    summonSkeleton.isMagic = true;
    summonSkeleton.hasEffects = true;
    summonSkeleton.abilityID = SUMMON_SKELETON;
    summonSkeleton.duration = 0; // skeleton lives until it dies
    summonSkeleton.minDMG = 1; // skeletons dmg
    summonSkeleton.maxDMG = 6;
    summonSkeleton.manaCost = 16;
    summonSkeleton.range = 1;
    summonSkeleton.abilitySave = 0;
    summonSkeleton.miscStat = 8; // skeletons HP
    strcpy(summonSkeleton.abilityName, "Summon Skeleton");
    strcpy(summonSkeleton.abilityDesc, "none");
    return summonSkeleton;
}

Ability ShadowBolt() {
    Ability shadowBolt;
    shadowBolt.isAttack = true;
    shadowBolt.isMagic = true;
    shadowBolt.hasEffects = false;
    shadowBolt.abilityID = SHADOW_BOLT;
    shadowBolt.duration = 0;
    shadowBolt.minDMG = 4;
    shadowBolt.maxDMG = 12;
    shadowBolt.manaCost = 5;
    shadowBolt.range = 15;
    shadowBolt.abilitySave = (player->playerStats.ATK) + 6;
    shadowBolt.miscStat = 0;
    strcpy(shadowBolt.abilityName, "ShadowBolt");
    strcpy(shadowBolt.abilityDesc, "none");
    return shadowBolt;
}

Ability Vengeance() {
    Ability vengeance;
    vengeance.isAttack = false;
    vengeance.isMagic = false;
    vengeance.hasEffects = true;
    vengeance.abilityID = VENGEANCE;
    vengeance.duration = 240;
    vengeance.minDMG = (player->equippedMelee.minDMG) + 1;
    vengeance.maxDMG = (player->equippedMelee.maxDMG) + 1;
    vengeance.manaCost = 5;
    vengeance.range = 0;
    vengeance.abilitySave = (player->playerStats.ATK) + 6;
    vengeance.miscStat = 0;
    strcpy(vengeance.abilityName, "Vengeance");
    strcpy(vengeance.abilityDesc, "none");
    return vengeance;
}

Ability Dash() {
    Ability dash;
    dash.isAttack = false;
    dash.isMagic = false;
    dash.hasEffects = true;
    dash.abilityID = DASH;
    dash.duration = 0;
    dash.minDMG = 0;
    dash.maxDMG = 0;
    dash.manaCost = 3;
    dash.range = 5;
    dash.abilitySave = 0;
    dash.miscStat = 0;
    strcpy(dash.abilityName, "Dash");
    strcpy(dash.abilityDesc, "none");
    return dash;
}

Ability DevastatingInsult() {
    Ability devastatingInsult;
    devastatingInsult.isAttack = true;
    devastatingInsult.isMagic = true;
    devastatingInsult.hasEffects = false;
    devastatingInsult.abilityID = DEVASTATING_INSULT;
    devastatingInsult.duration = 0;
    devastatingInsult.minDMG = 1;
    devastatingInsult.maxDMG = 4;
    devastatingInsult.manaCost = 2;
    devastatingInsult.range = 4;
    devastatingInsult.abilitySave = (player->playerStats.ATK);
    devastatingInsult.miscStat = 0;
    strcpy(devastatingInsult.abilityName, "Devastating Insult");
    strcpy(devastatingInsult.abilityDesc, "Do you know who else missed their attack?");
    return devastatingInsult;
}


/* If an ability does extra things, specify those things with Cast(AbilityName) */


void CastCharge(){
    ChargePlacement();
    player->playerStats.mana -= (player->equippedAbility.manaCost);
    // combatHistory->defender.hasMoved = true; // "stun" the enemy.
}

void CastDash() {
    int ch, i;
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
                if (y == 0) {
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
                if (y == 50) {
                    break;
                }
                else {
                    RemoveCursor(y, x,13);
                    y = y + player->equippedAbility.range;
                    while(!DashPOSHelper(x, y)) {
                        y--;
                    }
                }
                break;
            //move left
            case KEY_LEFT:
                if (x == 0) {
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
                if (x == 125) {
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
    if (map[y][x].noCollision && (GetDistance(player->pos, dashPOS) <= (player->equippedAbility.range))){
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
            player->playerStats.mana -= (player->equippedAbility.manaCost);
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
    if (player->equippedAbility.hasEffects) {
        AbilityEffects(player->equippedAbility.abilityID);
    }
    player->equippedAbility = NoAbility();
}

/* Called if the players input is processed in UsePlayerAbility from player.c, including attacking a monster.*/
/* Handles both attacks and non attacking abilities.*/
/* This runs before the monster attacks back, so healing the player will save them from an otherwise killing blow.*/
/* If an ability is just an attack with no effects, no CastAbility function is needed.*/
void AbilityEffects(int abilityID){
    if ((player->playerStats.mana) >= (player->equippedAbility.manaCost)) {
        switch (abilityID) {
        case CHARGE:
            CastCharge();
        break;
         case DASH:
            CastDash();
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

/* If the player has an active passive ability, deincrement the timer.*/
/* If the timer reaches 0, undo the effects cooresponding to the ability.*/
void CheckPassiveAbilities(int n_monsters) {
    if(!DeincrementAbilityTimer()) {
        ResetPassiveAbility(player->passiveAbility.abilityID);
    }
    switch(player->passiveAbility.abilityID) {
        case VENGEANCE:
        if((combatHistory->attackerDMG > 0) && (combatHistory->defender.isMonster)) {
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
            AbilityEffects(player->equippedAbility.abilityID);
            return true;
        }
    return false;
}
