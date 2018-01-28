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
    }
    memmove(&testGame, &game, sizeof(gameState));

    // check if the card effect function returns -1
    

    // check for success (return 0)

    return 0;
}
