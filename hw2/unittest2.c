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
  int i = numHandCards(&g);
  
  printf("%d\n",i);
  
  myassert(i == 5);
  
  if (!failed) {
    printf("TEST SUCCESSFULLY COMPLETED\n");
  }
  
  
  return 0;
}