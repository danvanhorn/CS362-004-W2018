#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

int main () {

	srand(time(NULL));
	struct gameState G;
	int cardResult;
	int fail = 0;
	int i;
	int randNum;
	int loop;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	while(1){
		randNum = rand () % 100;
		initializeGame(2, k, 69, &G); //player 0's turn
		printf("TEST: GARDENS CARD\n"); 
		for(i = 0; i < 100; i++){
			G.hand[0][i] = smithy;
		}
		G.hand[0][randNum] = gardens;

		printf("PLAYING GARDENS CARD FROM RANDOM POSITION %d\n", randNum);
		cardResult = cardEffect(gardens, 0,0,0, &G, randNum, 0);
		printf("TEST: CARD EFFECT OF GARDENS CARD IS TO RETURN 0\n");
		if(cardResult == 0)
			printf("SUCCESS! GARDENS CARD WORKED AS EXPECTED\n");
		else{
			printf("FAIL! GARDENS CARD DID NOT WORK AS EXPECTED\n");
			fail ++;
		}
		printf("TEST COMPLETE! THE TEST RAN WITH %d FAILURES\n", fail);
		loop++;
		if (randNum == 32)
			break;
	}
	printf("TEST COMPLETE. TEST RAN %d TIMES, AND FAILED %d TIMES.\n", loop, fail);
	return 0;
}



