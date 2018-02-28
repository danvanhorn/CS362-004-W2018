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
	int cardDrawn;
	int cardDrawn1;
	int handSize;
	int randNum;
	int fail = 0;
	int i;
	int loop = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	printf("TEST: ADVENTURER CARD\n"); 
	printf("INITIALIZING HAND TO ALL ADVENTURERS (7)\n");
	handSize = rand () % 30 + 1;
	for(i = 0; i < handSize; i++){
		G.hand[0][i] = adventurer;
	}
	while(1){
		initializeGame(2, k, 69, &G); //player 0's turn
		randNum = rand() % 100;
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~TESTING PLAYER 1~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		cardDrawn = G.hand[0][G.handCount[0]-1];
		cardDrawn1 = G.hand[0][G.handCount[0]-2];
		printf("TOP CARD IS %d\n", cardDrawn);
		printf("SECOND TO TOP CARD IS %d\n", cardDrawn1);

		printf("PLAYING ADVENTURER CARD\n");
		cardResult = cardEffect(adventurer, 0,0,0, &G, 0, 0);
		cardDrawn = G.hand[0][G.handCount[0]-1];
		cardDrawn1 = G.hand[0][G.handCount[0]-2];
		printf("GAME STATE SHOULD RETURN 0\n");
		if(cardResult == 0)
			printf("SUCCESS: Game state is 0! \n");
		else{
			printf("FAIL: Game state is not 0! \n");
			fail++;
		}

		printf("CHECKING DRAWN CARDS. TOP 2 SHOULD BE TREASURE (4, 5, or 6)\n");

		printf("TOP CARD IS %d\n", cardDrawn);
		printf("SECOND TO TOP CARD IS %d\n", cardDrawn1);

		if(cardDrawn == 4 || cardDrawn == 5 || cardDrawn == 6)
			printf("SUCCESS! TOP CARD IS A TREASURE!\n");
		else{
			printf("FAIL! TOP CARD IS NOT A TREASURE!\n");
			fail++;
		}
		if(cardDrawn1 == 4 || cardDrawn1 == 5 || cardDrawn1 == 6)
			printf("SUCCESS! SECOND TO TOP CARD IS A TREASURE!\n");

		else{
			printf("FAIL! SECOND TO TOP CARD IS NOT A TREASURE!\n");
			fail++;
		}
		loop++;
		if(randNum == 10)
			break;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~TESTING FOR PLAYER 2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	while(1){
		initializeGame(2, k, 69, &G); //player 0's turn
		randNum = rand() % 100;
		cardDrawn = G.hand[1][G.handCount[1]-1];
		cardDrawn1 = G.hand[1][G.handCount[1]-2];
		printf("TOP CARD IS %d\n", cardDrawn);
		printf("SECOND TO TOP CARD IS %d\n", cardDrawn1);

		printf("PLAYING ADVENTURER CARD\n");
		cardResult = cardEffect(adventurer, 0,0,0, &G, 0, 0);
		cardDrawn = G.hand[1][G.handCount[1]-1];
		cardDrawn1 = G.hand[1][G.handCount[1]-2];
		printf("GAME STATE SHOULD RETURN 0\n");
		if(cardResult == 0)
			printf("SUCCESS: Game state is 0! \n");
		else{
			printf("FAIL: Game state is not 0! \n");
			fail++;
		}

		printf("CHECKING DRAWN CARDS. TOP 2 SHOULD BE TREASURE (4, 5, or 6)\n");

		printf("TOP CARD IS %d\n", cardDrawn);
		printf("SECOND TO TOP CARD IS %d\n", cardDrawn1);

		if(cardDrawn == 4 || cardDrawn == 5 || cardDrawn == 6)
			printf("SUCCESS! TOP CARD IS A TREASURE!\n");
		else{
			printf("FAIL! TOP CARD IS NOT A TREASURE!\n");
			fail++;
		}
		if(cardDrawn1 == 4 || cardDrawn1 == 5 || cardDrawn1 == 6)
			printf("SUCCESS! SECOND TO TOP CARD IS A TREASURE!\n");

		else{
			printf("FAIL! SECOND TO TOP CARD IS NOT A TREASURE!\n");
			fail++;
		}
		loop++;
		if(randNum == 10)
			break;
	}
	printf("TEST COMPLETE. TEST RAN %d AND FAILED %d NUMBER OF TIMES\n", loop, fail);	
	return 0;
}

