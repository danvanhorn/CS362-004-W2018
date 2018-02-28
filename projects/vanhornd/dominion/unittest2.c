#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct gameState gameState;

// testing the supplyCount() function
int main()
{
    int i;
    gameState game, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    srand(time(NULL)); 
    initializeGame(2, k, rand(), &game);

    for (i = 0; i < 27; i++)
    {
        game.supplyCount[i] = rand(); // randomize the supply count
    }

    // duplicate the game state
    memmove(&testGame, &game, sizeof(gameState));

    printf("======= TESTING 'supplyCount()' FUNCTION =======\n"); 
    for (i = 0; i < 27; i++)
    {
        if (supplyCount(i, &testGame) == game.supplyCount[i])
        {
            printf("PASSED: The supply count at pos %d is correct.\n", i);
        }
        else
        {
            printf("FAILED: The supply count at pos %d is incorrect.\n", i);
        }
    }

    return 0;
}
