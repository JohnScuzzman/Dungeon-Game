#include <rogue.h>

/* Passed entity tries to attack player */
bool AttackPlayer(Entity* attacker) {
    int attackerATKMod = (attacker->entityStats.ATK);
    int playerDodgeMod = ((player->playerStats.DEX - 10) / 2); 
    int attackerAccRoll = ((rand() % 20) + 1) + attackerATKMod; // 1-20
    int playerDodgeRoll = ((rand() % 20) + 1) + playerDodgeMod;

    if (attackerAccRoll > playerDodgeRoll) {
        player->playerStats.HP -= (rand() % attacker->entityStats.maxDMG) + attacker->entityStats.minDMG;
        if (player->playerStats.HP <= 0) {
            //Player dead, Game is over.
            // Gameover()
            CloseGame();
        }
    }
}