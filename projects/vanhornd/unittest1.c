#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct gameState gameState;

// testing the buyCard() function
int main()
{
    int i, j, success, random;
    gameState game, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    srand(time(NULL)); // should only be called once
    random = rand();   // returns a pseudo-random integer between 0 and RAND_MAX
    initializeGame(2, k, random, &game);

    game.whoseTurn = 0; // doesn't really matter which player is buying
    game.numBuys = 27;  // a phase to buy each card in the supply
    game.coins = 0;     // at first, we want insuccifient funds
    // copy the game object for comparison during the test
    memmove(&testGame, &game, sizeof(gameState));

    // check trying to buy a card with insufficient gold
    printf("======= TESTING 'buyCard()' WITH 0 COINS ======= \n");
    for (i = 0; i < 27; i++)
    {
        success = buyCard(i, &game);
        // we've purchased a free curse or copper
        if ((i == 0 || i == 4) && (success == 0))
        {
            printf("PASSED: bought supply card at pos %d for free\n", i);
        } // we failed to purchase a card with insufficient funds
        else if (success == -1)
        {
            printf("PASSED: can't purchase card at supply pos %d with insufficient funds.\n", i);
        } // we were able to purchase a card with insufficient funds
        else
        {
            printf("FAILED: bought a card at supply pos %d with insuficient funds\n", i);
        }
    }

    // check trying to buy a card with no buys left
    game.numBuys = 0;
    memmove(&testGame, &game, sizeof(gameState));
    printf("\n======= TESTING 'buyCard()' WITH NO AVAILABLE BUYS =======\n");
    for (i = 0; i < 27; i++)
    {
        success = buyCard(i, &testGame);
        if (success == -1)
        {
            printf("PASSED: unable to buy card with no buys left \n");
        }
        else
        {
            printf("FAILED: bought a card with no buys left\n");
        }
    }

    game.coins = 10000;
    game.numBuys = 10000;
    
    for(i = 0; i< 27; i++){ // make sure we have an equal number of each card for the test
        game.supplyCount[i] = 10;
        testGame.supplyCount[i] = 10;
        printf("supply count at pos %d is %d\n", i , game.supplyCount[i]);
    }
    memmove(&testGame, &game, sizeof(gameState));

    // buy each card in the game object directly
    // buy each card in the testGame using drawCard()
    printf("\n======= TESTING 'buyCard()' TO CLEAR THE WHOLE SUPPLY =======\n");
    for (j = 0; j < 10; j++)
    {
        printf("\n\nITERATION %d: \n\n", j);
        for (i = 0; i < 27; i++)
        {
            game.phase = 1;
            gainCard(i, &game, 0, game.whoseTurn); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)
            game.coins = (game.coins) - (getCost(i));
            game.numBuys--;

            // use the buyCard() function to buy a card from the testGame object
            success = buyCard(i, &testGame);

            if (memcmp(&game, &testGame, sizeof(gameState)) == 0)
            {
                printf("PASSED: 'buyCard()' is successful for supply pos %d \n", i);
            }
            else
            {
                printf("FAILED: 'buyCard()' is unsuccessful at supply pos %d \n", i);
            }

        }
    }

    // attempt to buy a card when there are none left in the supply
    printf("\n ======= TESTING 'buyCard()' WITH EMPTY SUPPLY ======= \n")
    for(i = 0; i < 27; i++){
        if(buyCard(i, &testGame) == -1){
            printf("PASSED: supply pos %d is empty, unable to purchase\n", i);
        }else{
            printf("FAILED: should not be able to purchase at supply pos %d \n", i);
        }
    }

    return 0;
}
