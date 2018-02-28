#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct gameState gameState;

// testing the isGameOver() function
int main()
{
    int i;
    gameState game;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
    srand(time(NULL));
    initializeGame(1, k, rand(), &game);

    

    // test if the game is over with no remaining province cards
    printf("\n ======= TESTING: 'isGameOver()' WITH NO REMAINING PROVINCE CARDS ======= \n");
    game.supplyCount[province] = 0;
    if(isGameOver(&game) == 1){
        printf("PASSED: game is over, no more provinces \n");
    }else{
        printf("FAILED: game needs to end with no provinces \n");
    }


    printf("\n ======= TESTING: 'isGameOver()' WITH 3 EMPTY SUPPLY PILES ======= \n");
    game.supplyCount[province] = 6;
    game.supplyCount[adventurer] = 0;
    game.supplyCount[treasure_map] = 0;
    game.supplyCount[embargo] = 0;
    if(isGameOver(&game) == 1){
        printf("PASSED: game is over, three empty supply piles \n");
    }else{
        printf("FAILED: there are three empty supply piles, game should be over \n");
    }

    printf("\n ======= TESTING: 'isGameOver()' WITH GAME THAT IS NOT OVER ======= \n");
    for(i = 0; i < 26; i++){
        game.supplyCount[i] = 10;
    }
    if(isGameOver(&game) == 0){
        printf("PASSED: game is not over \n");
    }else{
        printf("FAILED: game should be not over \n");
    }

    return 0;
}