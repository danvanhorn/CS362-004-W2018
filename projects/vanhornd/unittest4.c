#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct gameState gameState;

// testing the endTurn() function
int main()
{
    int i;
    gameState game, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
    srand(time(NULL));
    initializeGame(1, k, rand(), &game);

    return 0;
}