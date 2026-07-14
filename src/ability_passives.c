#include <rogue.h>

/* Try and remove the NPC from the map and the player's follower value. */
void RemoveSummonSkeleton() {
    player->passiveAbility = NoAbility();
    ClearEntityInventory(FindNPCInList(player->follower.entityID, MAX_ONSCREEN_NPCS));
    Entity* temp = FindNPCInList(player->follower.entityID, MAX_ONSCREEN_NPCS);
    AssignFloor(temp->pos.x, temp->pos.y);
    ZeroEntity(FindNPCInList(player->follower.entityID, MAX_ONSCREEN_NPCS));
    ClearEntityInventory(&player->follower);
    AssignFloor(player->follower.pos.x, player->follower.pos.y);
    ZeroEntity(&player->follower);
    ClearFOV(player);
    UpdateNPCMap(nptr, MAX_ONSCREEN_NPCS);
    UpdateNPCVisible(&player->follower, player);
    MakeFOV(player);
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

/* If the player has an active passive ability, deincrement the timer.*/
/* If the timer reaches 0, undo the effects cooresponding to the ability.*/
void CheckPassiveAbilities(int n_monsters, bool playerMoved) {
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
            if(playerMoved) FollowerLogic(&player->follower, n_monsters);
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
            if(player->follower.entityType != NPC){
                player->passiveAbility = NoAbility();
            }
            break;
        case VENGEANCE:
            RemoveVengeance();
            break;
        default:
            player->passiveAbility = NoAbility();
            break;
    }

}