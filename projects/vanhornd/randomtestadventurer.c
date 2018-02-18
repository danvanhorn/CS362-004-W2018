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

void checkGameState(int handCount, int deckSizePre, int discardCountPre, int treasureCountPre, int *passed, int *failed, gameState *state)
{
    int stateComputedDeckSize = 0, stateComputedTreasureAmt = 0;
    int currentPlayer = state->whoseTurn;
    int failure = 0;
    if (state->deckCount > 0)
    {
        // check if the prior handcount is increased by 2, drawing two cards
        if (handCount + 2 != state->handCount[currentPlayer])
        {
            failure = 1;
            printf("FAILED: handCount: %d gameState handCount: %d\n",
                   handCount,
                   state->handCount[currentPlayer]);
        }
        // check if the deck size and discard pile of state  equal the initial deck size
        stateComputedDeckSize = state->deckCount[currentPlayer] + state->discardCount[currentPlayer];
        if (deckSizePre > stateComputedDeckSize)
        {
            failure = 1;
            printf("FAILED: deckSizePre: %d  stateComputedDeckSize: %d\n",
                   handCount,
                   stateComputedDeckSize);
        }
        // do some math check if the discard count is correct
        stateComputedTreasureAmt = countHandCoins(state->whoseTurn, state);
        if (treasureCountPre >= stateComputedTreasureAmt)
        {
            failure = 1;
            printf("FAILED: treasureCountPre: %d is greater than  stateComputedTreasureAmt: %d\n",
                   treasureCountPre,
                   stateComputedTreasureAmt);
        }

        if (failure)
        {
            *failed += 1;
            printf("Test %d failed\n", *passed + *failed);
        }
        else
        {
            *passed += 1;
            printf("Test %d passed\n", *passed + *failed);
        }
    }

}

int main()
{
    int passed, failed;
    int cards[10] = {minion, mine, cutpurse, sea_hag, tribute, smithy, adventurer, gardens, embargo, village};
    int i, j, player, players, discardCountPre, deckCountPre, handCount, randomSeed, treasureCount;

    srand(time(NULL));

    gameState state;

    passed = 0;
    failed = 0;

    printf("\n ======= RANDOM TESTING: Adventurer ======= \n");

    for (i = 0; i < NUM_TESTS; i++)
    {
        randomSeed = rand() % 50 + 1;
        players = rand() % 4 + 1;
        for (player = 0; player < players; player++)
        {
            initializeGame(players, cards, randomSeed, &state); // init the game
            for (j = 0; j < players; j++)
            {
                // loop through each player and give them random values
                state.handCount[j] = rand() % MAX_HAND;
                state.deckCount[j] = rand() % MAX_DECK;
                state.discardCount[j] = rand() % MAX_DECK;
            }
            state.whoseTurn = player; // set current player
            deckCountPre = state.deckCount[player];
            discardCountPre = state.discardCount[player]; // preserve discarded card value
            treasureCount = countHandCoins(player, &state);
            // get the original hand count
            handCount = numHandCards(&state);
            // play the adventurer
            adventurerAction(player, &state);
            // check the game state and assert
            checkGameState(handCount, deckCountPre, discardCountPre, treasureCount, &passed, &failed, &state);
        }
    }

    printf("\n ======== TESTNG COMPLETE ========= \n");
    printf("Tests passed: %d ", passed);
    printf("Tests failed: %d \n", failed);
    return 0;
}