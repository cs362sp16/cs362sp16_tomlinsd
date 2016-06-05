#include "dominion.h"

// Testing Council_room

int failed = 0;

int myassert(int b) {
  if (b == 0) {
    failed = 1;
    return failed;
  }
  return 0;
}

void checkasserts() {
  if (!failed) {
    printf ("TEST SUCCESSFULLY COMPLETED.\n");
  }
}

int main(int argc ,char** argv) {

	int seed = atoi(argv[1]);
	SelectStream(1);
	PutSeed(seed);
	int x,y,z,Players,before,after,failed;
	int numberPassed = 0;
	int numberFailed = 0;
	int numberTests = 0;

	struct gameState g,reset;
	int k[10] ={adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	//Tests if player got +4 cards
	for( x = 0; x < 100; x++)
	{
		//players between 2 and Max_players
		Players = 2 + (rand() % (int)(MAX_PLAYERS - 2 + 1));
		initializeGame(Players, k, seed, &g);


		for (y = 0; y < Players; y++)
		{
			before = 0;
			after = 0;
			before = g.handCount[y];
			council_roomCard(y, &g, 0);
			after = g.handCount[y];
			endTurn(&g);
			failed = myassert((after - before) == 3);
			
			if(failed)
			{
				numberFailed = numberFailed + 1;
			}
			else
			{
				numberPassed = numberPassed + 1;
			}
			numberTests = numberTests + 1;

		}

		memcpy ( &g, &reset, sizeof(struct gameState) );
	}
	//Test if numBuys increased
	for( x=0; x < 100; x++)
	{
		//players between 2 and Max_players
		Players = 2 + (rand() % (int)(MAX_PLAYERS - 2 + 1));
		initializeGame(Players, k, seed, &g);


		for (y = 0; y < Players; y++)
		{
			before = 0;
			after = 0;
			z = rand()%2;
			
			// randomly set numBuys to random number or leave as it is
			if(z)
			{
				g.numBuys =  2 + (rand() % (int)(100 - 2 + 1));;
			}

			before=g.numBuys;
			council_roomCard(y,&g,0);
			
			after=g.numBuys;
			endTurn(&g);
			failed = myassert((after - before) == 1);
			if(failed)
			{
				numberFailed = numberFailed + 1;
			}
			else
			{
				numberPassed = numberPassed + 1;
			}
			numberTests = numberTests + 1;

		}

		memcpy ( &g, &reset, sizeof(struct gameState) );
	}
	
	printf("Passed: %d, Failed: %d\n", numberPassed, numberFailed);
	checkasserts();
	
	return 0;
}