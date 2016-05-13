#include "dominion.h"
#include "interface.h"

int failed = 0; 

void myassert(int bool) {
  if (!bool) {
    printf ("YOU HAVE FAILED ME.\n");
    failed = 1;
  }

}
int main() {
	struct gameState g;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
		  
	initializeGame(2, k, 5, &g);
	
	addCardToHand(0, 14, &g);
	playCard(5, 0, 0, 0, &g);
	
	int i = numHandCards(&g);
		
	myassert(i == 6);
	
	if (!failed) {
		printf("Correct village card behavior\n");
	}
	
	return 0;
}