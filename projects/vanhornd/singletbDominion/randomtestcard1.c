#include "dominion.h"
#include "interface.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_TESTS 1000

typedef struct gameState gameState;

void checkGameState(int deckCountPre, int drawnCardsPre, int *passed, int *failed, gameState *state)
{
    int failure = 0;
    // check if the pre deck count is less than state deck count
    if (deckCountPre <= state->deckCount[state->whoseTurn])
    {
        failure = 1;
        printf("FAILED: deckCountPre %d is greater than or equal to state->deckCount: %d \n",
               deckCountPre,
               drawnCardsPre);
    }
    // Check if the # of drawn cards is greater than the pre # dran cards
    if (drawnCardsPre + 2 != state->handCount[state->whoseTurn])
    {
        failure = 1;
        printf("FAILED: original hand count %d must be two less than %d \n",
               drawnCardsPre,
               state->handCount[state->whoseTurn]);
    }
    *passed += failure == 1 ? 0 : 1;
    *failed += failure == 1 ? 1 : 0;
    if (failure == 1)
    {
        printf("Test %d failed\n", *passed + *failed);
    }
    else
    {
        printf("Test %d passed\n", *passed + *failed);
    }
}

int main()
{
    int i, j, passed, failed, randomSeed, players, player, smithyPos, deckCountPre, drawnCardsPre;
    int cards[10] = {minion, mine, cutpurse, sea_hag, tribute, smithy, adventurer, gardens, embargo, village};

    passed = 0;
    failed = 0;

    srand(time(NULL));
    gameState state;

    printf("\n ======= RANDOM TESTING: smithy() ======= \n");

    for (i = 0; i < NUM_TESTS; i++)
    {
        randomSeed = rand() % 50 + 1;
        players = rand() % 4 + 1;
        for (player = 0; player < players; player++)
        {
            initializeGame(players, cards, randomSeed, &state);
            for (j = 0; j < players; j++)
            {
                // loop through each player and give them random values
                state.handCount[j] = rand() % MAX_HAND;
                state.deckCount[j] = rand() % MAX_DECK;
                state.discardCount[j] = rand() % MAX_DECK;
            }

            smithyPos = state.handCount[player];
            deckCountPre = state.deckCount[player];
            drawnCardsPre = state.handCount[player];

            smithyCard(player, smithyPos, &state);
            checkGameState(deckCountPre, drawnCardsPre, &passed, &failed, &state);
        }
    }

    printf("\n ======== TESTNG COMPLETE ========= \n");
    printf("Tests passed: %d ", passed);
    printf("Tests failed: %d \n", failed);
    return 0;
}