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

void checkGameState(int numActions, int handCount, int *passed, int *failed, gameState *state)
{
    int failure = 0;
    // check if the pre deck count is less than state deck count
    if (numActions + 2 != state->numActions)
    {
        failure = 1;
        printf("FAILED: state->numActions: '%d' must 2 more than the original numActions '%d' \n",
               state->numActions,
               numActions);
    }
    // Check if the # of drawn cards is greater than the pre # drawn cards
    if (handCount != state->handCount[state->whoseTurn])
    {
        failure = 1;
        printf("FAILED: player %d's hand count ,value: '%d', must equal the original hand count ,value: '%d' \n",
               state->whoseTurn,
               state->handCount[state->whoseTurn],
               handCount);
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
    int i, j, passed, failed, randomSeed, players, player, numActions, handCount;
    int cards[10] = {minion, mine, cutpurse, sea_hag, tribute, smithy, adventurer, gardens, embargo, village};

    passed = 0;
    failed = 0;

    srand(time(NULL));
    gameState state;

    printf("\n ======= RANDOM TESTING: village() ======= \n");

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
            state.numActions = rand() % HANDSIZE;
            state.whoseTurn = player;
            handCount = state.handCount[player];
            numActions = state.numActions;
            state.hand[player][0] = village;
            cardEffect(village, 0, 0, 0, &state, 0, (int *)cards);
            checkGameState(numActions, handCount, &passed, &failed, &state);
        }
    }

    printf("\n ======== TESTNG COMPLETE ========= \n");
    printf("Tests passed: %d ", passed);
    printf("Tests failed: %d \n", failed);
    return 0;
}