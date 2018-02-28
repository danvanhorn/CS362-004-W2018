#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// testing the great hall card effect
int main()
{
    int success;
    gameState game;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    srand(time(NULL));
    initializeGame(2, k, rand(), &game);

    game.whoseTurn = 0;
    memset(game.hand[0], 5, sizeof(game.hand[0]));
    game.numActions = 1;

    printf("\n ======= TESTING THE 'great_hall branch' IN CARD EFFECT ======= \n");

    success = cardEffect(great_hall, 1, 2, 3, &game, 1, k);
    if (game.numActions == 2)
    {

        printf("PASSED: Expected 2 actions, actual: %d\n", game.numActions);
    }
    else
    {
        printf("FAILED: Expected 2 actions, actual: %d\n", game.numActions);
    }

    if (game.hand[0][game.handCount[0] - 1] != 5)
    {
        printf("PASSED: Expected card in hand !=5, actual: %d\n", game.hand[0][game.handCount[0] - 1]);
    }
    else
    {
        printf("FAILED: Expected card in hand !=5, actual: %d\n", game.hand[0][game.handCount[0] - 1]);
    }

    if (success == 0)
    {
        printf("PASSED: Expected card effect to return 0, actual: %d\n", success);
    }
    else
    {
        printf("FAILED: Expected card effect to return 0, actual: %d\n", success);
    }

    return 0;
}