#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct gameState gameState;
// testing the smithyAction() function
int main()
{
    int success;
    gameState game;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    srand(time(NULL));
    initializeGame(2, k, rand(), &game);

    game.whoseTurn = 0;
    game.handCount[0] = 1;
    game.hand[0][0] = smithy;
    game.discardCount[0] = 0;

    // test that the smithyAction() completes succesfully
    printf("\n ======= TESTING 'smithyAction()' FUNCTION ======= \n");
    success = smithyAction(game.whoseTurn, &game, 0);
    if (success == 0)
    {
        printf("PASSED: expected 0 return value, received %d \n", success);
    }
    else
    {
        printf("FAILED: expected 0 return value, received %d \n", success);
    }

    if (game.handCount[0] == 3)
    {
        printf("PASSED: expected 3 cards in hand, actual: %d cards in hand \n", success);
    }
    else
    {
        printf("FAILED: expected 3 cards in hand, actual: %d cards in hand \n", success);
    }

    if (game.playedCards[0] == smithy)
    {
        printf("PASSED: expected smithy in played card pile, actual: smithy \n");
    }
    else
    {
        printf("FAILED: expected smithy in played card pile, actual: %d  \n", game.discard[0][0]);
    }

    return 0;
}