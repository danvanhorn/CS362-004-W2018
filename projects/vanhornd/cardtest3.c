#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// testing the sea_hag card effect
int main()
{
    int success, p1DiscardCountPre, top1Pre, p1DiscardCountPost, top1Post;
    gameState game;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    srand(time(NULL));
    initializeGame(2, k, rand(), &game);

    game.whoseTurn = 0;

    top1Pre = game.deck[1][game.deckCount[1] - 1];
    p1DiscardCountPre = game.discardCount[1];

    success = cardEffect(sea_hag, 1, 2, 3, &game, 1, k);

    top1Post = game.deck[1][game.deckCount[1] - 1];
    p1DiscardCountPost = game.discardCount[1];

    printf("\n ======= TESTING THE 'sea_hag branch' IN CARD EFFECT ======= \n");
    if (top1Pre != curse && top1Post == curse)
    {
        printf("PASSED: Expected top card of player 2 to be 0(curse), actual: %d\n", top1Post);
    }
    else
    {
        printf("FAILED: Expected top card of player 2 to be 0(curse), actual: %d\n", top1Post);
    }

    if (p1DiscardCountPre == 0 && p1DiscardCountPost == 1)
    {
        printf("PASSED: Expected discard size for player 2 to be 1 card, actual: %d\n", p1DiscardCountPost);
    }
    else
    {
        printf("FAILED: Expected discard size for player 2 to be 1 card, actual: %d\n", p1DiscardCountPost);
    }

    if(success == 0)
        {
        printf("PASSED: Expected card effect to return 0, actual: %d\n", success);
    }
    else
    {
        printf("FAILED: Expected card effect to return 0, actual: %d\n", success);
    }

    return 0;
}