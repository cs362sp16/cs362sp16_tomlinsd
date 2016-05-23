#include "dominion.h"

// Testing Adventurer

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
	int x,y,z,Players,before,after,failed,r1;
	int numberPassed = 0;
	int numberFailed = 0;
	int tests = 0;
	struct gameState g,reset;
	int k[10] ={adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	for( x=0; x < 100; x++)
	{
		Players = 2 + (rand() % (int)(MAX_PLAYERS - 2 + 1));
		//printf("	Round %d with Players: %d\n",i,Players);
		initializeGame(Players, k, seed, &g);

		for(z=0; z< 50; z++)
		{

			for (y = 0; y < Players; y++)
			{
				r1 = rand()%2;
				before=after=0;

				before=g.handCount[y];
				adventurerCard(&g, y, 0, 0);

				after=g.handCount[y];
				endTurn(&g);
				failed=myassert( ((before-after) == 1) ||((after - before) == 2) ||((after - before) == 1)||((after - before) == 0));
				if(r1)
				{
					// This case will help to bring the total branch coverage to 100%
					g.deckCount[y]=0;
				}
				if(failed)
				{
					numberFailed = numberFailed + 1;
				}
				else
				{
					numberPassed = numberPassed + 1;
				}
				tests = tests + 1;


			}
		}
		memcpy ( &g, &reset, sizeof(struct gameState) );
	}
	printf("Passed: %d, Failed: %d\n",numberPassed,numberFailed);
	checkasserts();
	
	return 0;
}