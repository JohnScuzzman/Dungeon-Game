#include <rogue.h>


bool CheckForLevelUp() {
    if(player->playerStats.EXP >= player->playerStats.nextLVLEXP){
        LevelUp(player->playerClass.classID);
        return true;
    }
    return false;
}

void LevelUp(int classID){
    player->playerStats.LVL += 1;
    player->playerStats.maxHP += (player->playerClass.hpPerLVL);
    player->playerStats.HP = player->playerStats.maxHP;
    player->playerStats.maxMana += (player->playerClass.manaPerLVL);
    player->playerStats.mana = player->playerStats.maxMana;
    player->playerStats.nextLVLEXP = LVL_EXP_VALUES[player->playerStats.LVL];
    switch(classID) {
        case KNIGHT:
            LevelKnight();
        break;
        case SWASHBUCKLER:
            LevelSwashbuckler();
        break;
        case WIZARD:
            LevelWizard();
        break;
        case NECROMANCER:
            LevelNecromancer();
        break;
        case GUNSLINGER:
            LevelGunslinger();
        break;
        case RANGER:
            LevelRanger();
        break;
        case DARK_KNIGHT:
            LevelDarkKnight();
        break;
        case WARLOCK:
            LevelWarlock();
        break;
        case CONJURER:
            LevelConjurer();
        break;
        case CYBORG:
            LevelCyborg();
        break;
    }
}

void LevelKnight() {
    player->playerStats.CON += (player->playerClass.mainStat);
    player->playerStats.STR += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.STR) - 10) / 2;
    switch((player->playerStats.LVL)) {
        case 2:
        player->playerClass.abilities[ABILITY_3] = Vengeance();
        break;
        case 3:
        player->playerClass.abilities[ABILITY_4] = Dash();
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void LevelSwashbuckler() {
    player->playerStats.DEX += (player->playerClass.mainStat);
    player->playerStats.CHA += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.DEX) - 10) / 2;
    switch((player->playerStats.LVL)) {
        case 2:
        player->playerClass.abilities[ABILITY_3] = SecondWind();
        break;
        case 3:
        player->playerClass.abilities[ABILITY_4] = Charge();
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void LevelWizard() {
    player->playerStats.INT += (player->playerClass.mainStat);
    player->playerStats.ATK = ((player->playerStats.INT) - 10) / 2;
    switch((player->playerStats.LVL)) {
        case 2:
        player->playerClass.abilities[ABILITY_3] = ShadowBolt();
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void LevelNecromancer() {
    player->playerStats.INT += (player->playerClass.mainStat);
    player->playerStats.WIS += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.INT) - 10) / 2;
    switch((player->playerStats.LVL)) {
        case 2:
        player->playerClass.abilities[ABILITY_3] = ShadowBolt();
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void LevelGunslinger() {
    player->playerStats.DEX += (player->playerClass.mainStat);
    player->playerStats.ATK = ((player->playerStats.DEX) - 10) / 2;
    switch((player->playerStats.LVL)) {
        case 2:
        player->playerClass.abilities[ABILITY_3] = AimedShot();
        break;
        case 3:
        player->playerClass.abilities[ABILITY_4] = SecondWind();
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void LevelRanger() {
    player->playerStats.DEX += (player->playerClass.mainStat);
    player->playerStats.WIS += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.DEX) - 10) / 2;
    switch((player->playerStats.LVL)) {
        case 2:
        player->playerClass.abilities[ABILITY_3] = Dash();
        break;
        case 3:
        player->playerClass.abilities[ABILITY_4] = FireVolley();
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void LevelDarkKnight() {
    player->playerStats.STR += (player->playerClass.mainStat);
    player->playerStats.ATK = ((player->playerStats.STR) - 10) / 2;
    switch((player->playerStats.LVL)) {
        case 2:
        player->playerClass.abilities[ABILITY_3] = Vengeance();
        break;
        case 3:
        player->playerClass.abilities[ABILITY_4] = ShadowBolt();
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void LevelWarlock() {
    player->playerStats.CHA += (player->playerClass.mainStat);
    player->playerStats.ATK = ((player->playerStats.CHA) - 10) / 2;
    switch((player->playerStats.LVL)) {
        case 2:
        player->playerClass.abilities[ABILITY_3] = ShadowBolt();
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void LevelConjurer() {
    player->playerStats.INT += (player->playerClass.mainStat);
    player->playerStats.CHA += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.CHA) - 10) / 2;
    switch((player->playerStats.LVL)) {
        case 2:
        player->playerClass.abilities[ABILITY_3] = MagicMissile();
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void LevelCyborg() {
    player->playerStats.STR += (player->playerClass.mainStat);
    player->playerStats.DEX += (player->playerClass.secondaryStat);
    player->playerStats.ATK = ((player->playerStats.STR) - 10) / 2;
    switch((player->playerStats.LVL)) {
        case 2:
        player->playerClass.abilities[ABILITY_3] = Charge();
        break;
        case 3:
        player->playerClass.abilities[ABILITY_4] = Dash();
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}
