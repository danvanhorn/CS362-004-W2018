#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct gameState gameState;

// testing the playCard() function
int main()
{
    int i;
    gameState game, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int j[7] = {curse, estate, duchy, province, copper, silver, gold};

    srand(time(NULL));
    initializeGame(1, k, rand(), &game);

    // put every non-action card in their hand
    for (i = 0; i < 7; i++)
    {
        game.hand[0][i] = j[i];
    }
    game.phase = 50;
    // duplicate the game state
    memmove(&testGame, &game, sizeof(gameState));

    // check if it fails when the game phase != 0
    printf("\n======= TESTING 'playCard()' ON NON ZERO GAME PHASE =======\n");
    if (playCard(6, 5, 4, 3, &game) == -1)
    {
        printf("PASSED: cannot play on other phases than 0\n");
    }
    else
    {
        printf("FAILED: played card on phase that is not zero\n");
    }

    // check failure when the player has insufficient actions
    printf("\n======= TESTING 'playCard()' WITH 0 AVAILABLE ACTIONS =======\n");
    game.phase = 0;
    game.numActions = 0;
    if (playCard(6, 5, 4, 3, &game) == -1)
    {
        printf("PASSED: did not play card, no available actions.\n");
    }
    else
    {
        printf("FAILED: played a card with 0 available actions.\n");
    }

    // check failure for not playing a non action card
    printf("\n======= TESTING 'playCard()' WITH NON-ACTION CARDS =======\n");
    for (i = 0; i < 7; i++)
    {
        if (playCard(6, 5, 4, 3, &game) == -1)
        {
            printf("PASSED: did not play card, not an action card.\n");
        }
        else
        {
            printf("FAILED: played a non-action card on action phase\n");
        }
    }

    // now fill the player's hand with the valid action cards
    for (i = 0; i < 10; i++)
    {
        game.hand[0][i] = k[i];
        game.hand[0][i+10] = k[i+10];
        game.hand[0][i+20] = k[i+20];
        game.hand[0][i+30] = k[i+30];
    }
    game.numActions = 27;
    memmove(&testGame, &game, sizeof(gameState));

    printf("\n ======= TESTING 'buyCard()' ON VALID ACTION CARDS ======= \n");
    for(i = 0; i < 10; i++){
        if(playCard(i, i+10, i+20, i+30, &testGame) == 0){
            printf("PASSED: succesfully played card at hand pos %d \n", i);
        } else{
            printf("FAILED: could not play at hand pos %d \n", i);
        }
    }

    return 0;
}
