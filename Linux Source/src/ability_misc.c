#include <rogue.h>

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

bool DashPOSHelper(int x, int y) {
    if (map[y][x].noCollision) {
        return true;
    }
    if (y == player->pos.y && x == player->pos.x){
        return true;
    }
    return false;
}

/* Only applies to abilities that are attacks with effects. */
/* Applies directly after player attack, but before monster movements/attacks. */
void PostCombatEffects() {
    DrawMap();
    if (player->equippedAbility.postCombatEffects) {
        PostCombatAbilities(player->equippedAbility.abilityID);
    }
    if (combatHistory->playerCombat == true) DrawPlayerStats();
    player->equippedAbility = NoAbility();
}

void PreCombatEffects() {
    DrawMap();
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
        clear();
        DrawEverything();
        DrawBorder();
        DrawPlayerStats();
        DrawPlayerEquipment();
        return;
    }
    else if ((player->playerStats.mana) < (player->equippedAbility.manaCost) && !(player->equippedAbility.isAttack)) {
        NotEnoughMana();
    }
}

/*
Same as above, but happens prior to player combat.
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

