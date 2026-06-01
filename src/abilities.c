#include <rogue.h>


/* These initialize the abilities and are equipped to the player.*/
/* If no special effects, treat like a normal ranged attack.*/
/* Melee attack abilities have a range of 1.*/

Ability NoAbility() {
    Ability noAbility;
    noAbility.isAttack = false;
    noAbility.isMagic = false;
    noAbility.hasEffects = false;
    noAbility.postCombat = false;
    noAbility.abilityID = NO_ABILITY;
    noAbility.duration = 0;
    noAbility.minDMG = 0;
    noAbility.maxDMG = 0;
    noAbility.manaCost = 0;
    noAbility.range = 0;
    noAbility.abilitySave = 0;
    noAbility.miscStat = 0;
    strcpy(noAbility.abilityName, " ");
    strcpy(noAbility.abilityDesc, " ");
    return noAbility;
}

Ability AimedShot() {
    Ability aimedShot;
    aimedShot.isAttack = true;
    aimedShot.isMagic = false;
    aimedShot.hasEffects = false;
    aimedShot.postCombat = false;
    aimedShot.abilityID = AIMED_SHOT;
    aimedShot.duration = 0;
    aimedShot.minDMG = (player->equippedRanged.minDMG) + 1;
    aimedShot.maxDMG = (player->equippedRanged.maxDMG) + 4;
    aimedShot.manaCost = 3;
    aimedShot.range = (player->equippedRanged.range);
    aimedShot.abilitySave = (player->playerStats.ATK) + 10;
    aimedShot.miscStat = 0; // skeletons HP
    strcpy(aimedShot.abilityName, "Aimed Shot");
    strcpy(aimedShot.abilityDesc, "none");
    return aimedShot;
}

Ability Charge() {
    Ability charge;
    charge.isAttack = true;
    charge.isMagic = false;
    charge.hasEffects = true;
    charge.postCombat = false;
    charge.abilityID = CHARGE;
    charge.duration = 0;
    charge.minDMG = (player->equippedMelee.minDMG) + 4;
    charge.maxDMG = (player->equippedMelee.maxDMG) + 6;
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
    drainLife.postCombat = true;
    drainLife.abilityID = DRAIN_LIFE;
    drainLife.duration = 0;
    drainLife.minDMG = 4;
    drainLife.maxDMG = 10;
    drainLife.manaCost = 4;
    drainLife.range = 3;
    drainLife.abilitySave = (player->playerStats.ATK) + 4;
    drainLife.miscStat = 0; // HP gained
    strcpy(drainLife.abilityName, "Drain Life");
    strcpy(drainLife.abilityDesc, "none");
    return drainLife;
}

Ability Electrify() {
    Ability electrify;
    electrify.isAttack = true;
    electrify.isMagic = false;
    electrify.hasEffects = false;
    electrify.postCombat = false;
    electrify.abilityID = ELECTRIFY;
    electrify.duration = 0;
    electrify.minDMG = 1;
    electrify.maxDMG = 10;
    electrify.manaCost = 4;
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
    fireVolley.postCombat = false;
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
    iceArmor.postCombat = false;
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
    magicMissile.postCombat = false;
    magicMissile.abilityID = MAGIC_MISSILE;
    magicMissile.duration = 0;
    magicMissile.minDMG = (player->playerStats.LVL) + 2; //3d4 then 4d4 etc
    magicMissile.maxDMG = (magicMissile.minDMG) * 4;
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
    secondWind.postCombat = false;
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
    selfRepair.postCombat = false;
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
    summonSkeleton.postCombat = false;
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


/* If an ability does extra things, specify those things with Cast(AbilityName) */


void CastCharge(){
    ChargePlacement();
    // strcpy(combatHistory->event, "You charge at the ");
    // strcat(combatHistory->event, combatHistory->defender.entityName);
    // strcat(combatHistory->event, ".");
    // QueueEvent(q, combatHistory->event);
    // combatHistory->defender.hasMoved = true; // "stun" the enemy.
}

void CastDrainLife(){
    if ((combatHistory->playerResult)) {
        char eventDMGBuffer[EVENT_SIZE];
        strcpy(combatHistory->event, "You drain your enemy of life force,");
        QueueEvent(q, combatHistory->event);
        int healVal = (combatHistory->playerDMG);
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
        combatHistory->playerUsedAbility = true;
        combatHistory->playerCombat = false;
        strcpy(combatHistory->event, "You mend your wounds.");
        QueueEvent(q, combatHistory->event);
        
        if(((player->playerStats.HP) + healVal) >= (player->playerStats.maxHP)) {
            strcpy(combatHistory->event, "You heal yourself for ");
            snprintf(eventDMGBuffer, sizeof(eventDMGBuffer), "%d.", healValFull);
            strcat(combatHistory->event, eventDMGBuffer);
            QueueEvent(q, combatHistory->event);
            player->playerStats.HP = player->playerStats.maxHP;
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
        combatHistory->playerUsedAbility = true;
        combatHistory->playerCombat = false;
        strcpy(combatHistory->event, "You repair your metal frame.");
        QueueEvent(q, combatHistory->event);
        int repairVal = (rand() % (player->equippedAbility.maxDMG)) + (player->equippedAbility.minDMG);
        if(((player->playerStats.HP) + repairVal) >= (player->playerStats.maxHP)) {
            player->playerStats.HP = (player->playerStats.maxHP);
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
    int shieldVal = player->equippedAbility.miscStat;
    player->playerStats.AC -= shieldVal;
    player->passiveAbility = NoAbility();
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
        default:
        break;
        }
        player->playerStats.mana -= player->equippedAbility.manaCost;
        return;
    }
    else if ((player->playerStats.mana) < (player->equippedAbility.manaCost) && !(player->equippedAbility.isAttack)) {
        NotEnoughMana();
    }
}

/* If the player has an active passive ability, deincrement the timer.*/
/* If the timer reaches 0, undo the effects cooresponding to the ability.*/
void CheckPassiveAbilities() {
    if(!DeincrementAbilityTimer()) {
        ResetPassiveAbility(player->passiveAbility.abilityID);
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