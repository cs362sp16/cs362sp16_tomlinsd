#include "dominion.h"

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
  int i = supplyCount(3,&g);

  myassert(i > 0);
  
  if(!failed){
	  printf("Card count works\n");
  }
  
  return 0;
}