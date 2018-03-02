#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct gameState gameState;

// testing the adventurerAction() function
int main()
{
    int success, discardCountPre, discardCountPost, deckCountPre, deckCountPost;
    gameState game;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    srand(time(NULL));
    initializeGame(2, k, rand(), &game);

    game.whoseTurn = 0;
    game.handCount[0] = 1;
    game.hand[0][0] = adventurer;
    game.coins = 0;
    deckCountPre = game.deckCount[0];
    discardCountPre = game.discardCount[0];

    printf("\n ======= TESTING THE 'adventurerAction()' FUNCTION ======= \n");

    success = cardEffect(adventurer,1,2,3,&game, 0, k);
    discardCountPost = game.discardCount[0];
    deckCountPost = game.deckCount[0];

    // check if cards have been discarded
    if (discardCountPost > 0 && (discardCountPost > discardCountPre))
    {
        printf("PASSED: Expected discard pile to be > 0, got %d \n", deckCountPost);
    }
    else if ((deckCountPre - deckCountPost) == 3)
    {
        printf("PASSED: Treasure cards were the top three cards\n");
    }
    else
    {
        printf("FAILED: Expected discard pile to be > 0, got %d \n", deckCountPost);
    }

    // check the return value
    if(success == 0){
        printf("PASSED: Expected adventurerAction() to return 0, got %d \n", success);
    }else{
        printf("FAILED: Expected adventurerAction() to return 0, got %d \n", success);
    }


    return 0;
}