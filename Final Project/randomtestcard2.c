#include "dominion.h"

// Testing Embargo

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
	SelectStream(3);
	PutSeed(seed);
	int i,j,Players,failed;
	int numberPassed = 0;
	int numberFailed = 0;
	int tests = 0;
	int choice1,choice2,choice3;
	int bonus[1],resetbonus[1];
	int beforeCoinsCount,afterCoinsCount;

	struct gameState g,reset;
	int k[10] ={adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	for( i=0; i < 100; i++)
	{
		// makes a random amount of players from 2 to MAX_PLAYERS
		Players = 2 + (rand() % (int)(MAX_PLAYERS - 2 + 1));
		initializeGame(Players, k, seed, &g);


		for (j = 0; j < Players; j++)
		{
			
			beforeCoinsCount= 0;
			afterCoinsCount = 0;

			beforeCoinsCount = g.coins;
			cardEffect(embargo,choice1, choice2, choice3, &g, 0, bonus);

			afterCoinsCount = g.coins;
			endTurn(&g);
			
			//+2 coins
			failed = myassert((afterCoinsCount - beforeCoinsCount) == 2);

			if(failed)
			{
				numberFailed = numberFailed + 1;
			}
			else
			{
				numberPassed = numberPassed + 1;
			}
			tests = tests + 1;
			// reset bonus
			memcpy ( bonus, resetbonus, sizeof(bonus) );

		}
		// reset gameState struct
		memcpy ( &g, &reset, sizeof(struct gameState) );
	}

	printf("Passed: %d, Failed: %d\n",numberPassed,numberFailed);
	checkasserts();

	return 0;
}