#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main () {

	srand(time(NULL));
	int i, n, handCount, num_players;
	int fail;
	int loop = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	printf("RANDOMLY TESTING SMITHY, TEST WILL FINISH WHEN HANDCOUNT IS SIZE 169\n");
	sleep(3);
	struct gameState G;
	while(1){
		num_players = rand() % MAX_PLAYERS + 1;
		printf("PLAYING GAME WITH %d NUMBER OF PLAYERS\n", num_players);
		initializeGame(num_players, k, 69, &G);
		handCount = rand() % 200;
		printf("RANDOMLY ASSIGNING HAND SIZE... SIZE = %d\n", handCount);
		for (n = 0; n < num_players; n++){
			G.whoseTurn = n;
			G.handCount[n] = handCount;
			for(i = 0; i < handCount; i ++){
				G.hand[n][i] = smithy;
				printf("TEST: Player %d is playing smithy from hand position %d\n", n, i);
				cardEffect(smithy, 0,0,0, &G, i, 0);
				if(G.handCount[n] == handCount + 2){
					printf("SUCCESS! Player %d has 2 more cards after playing Smithy!\n", n);
				}	   
				else{
					printf("FAIL! Player %d has not gained 2 cards after playing Smithy!\n", n); 
					fail++;
				}
		}
	}
	loop++;
	if(handCount == 169)
		break;
	}
	printf("TEST COMPLETE. TEST RAN %d TIMES, AND FAILED %d TIMES.\n", loop, fail);
	return 0;
}
