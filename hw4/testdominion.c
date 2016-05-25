#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "math.h"
#include <time.h>

#define TEST_NUM 100


void randomChoice(struct gameState *g, int card, int* choice1, int* choice2, int* choice3){
	if(card==mine || card==remodel){
		*choice1 = rand()%(numHandCards(g));
		*choice2 = rand()%(numHandCards(g));
		*choice3 = -1;
	}
	else if(card==feast){
		*choice1 = rand()%27;
		*choice2 = -1;
		*choice3 = -1;		
	}
	else if(card==baron){
		*choice1 = rand()%2;
		*choice2 = -1;	
		*choice3 = -1;
		
	}
	else if(card==minion){
		*choice1 = rand()%2;
		if(*choice1==1)
			*choice2 = 0;
		else
			*choice2 = 1;
		 *choice3 = -1;
	}
	else if(card==steward){
		*choice1 = rand()%3;
		*choice2 = 0;
		*choice3 = 0;
	}
	else if(card==embargo){
		*choice1 = rand()%10;
		*choice2 = 1;
		*choice3 = 0;
	}
	else if(card==cutpurse){
		*choice1 = rand()%27;
		*choice2 = -1;
		*choice3 = -1;
	}
	else if(card==salvager){
		*choice1 = rand()%2;
		*choice2 = -1;
		*choice3 = -1;
	}
	else{
		*choice1 = -1;
		*choice2 = -1;
		*choice3 = -1;
	}
}

int checkNumAction(struct gameState *g){
	int i, num=0, whose;
	whose = g->whoseTurn;

	for(i=0; i<numHandCards(g); i++)
		if(g->hand[whose][i] >= adventurer && g->hand[whose][i] <= treasure_map)
				num++;

	return num;
}

int checkKingdomcard(int *kingdomcards, int i){
	int j;
	for(j=0; j<i; j++){
		 if(kingdomcards[i]==kingdomcards[j])
				return 1;
	}
	return 0;
}


int checkMoney(struct gameState *g){
	int i, money=0;
	for(i = 0; i < numHandCards(g); i++){			
    	if(handCard(i, g)==copper)
   	 		money++;
   	   	else if(handCard(i, g)==silver)
    		money += 2;
    	else if(handCard(i, g)==gold)
    		money += 3;
    	else
   	 		money += 0;
   	}
   	return money;
}


int main(int argc, char* argv[]){
	int i,j,l,k, seed;
	
	srand(time(NULL));
	if(argv[1]!=NULL)
		seed = atoi(argv[1]);
	else
		seed = rand()%10 + 1;
	
	for(i=0; i<TEST_NUM; i++) {
		struct gameState g;

		int numPlayer, kingdomcards[10];

		SelectStream(1);
		PutSeed(seed);

		numPlayer = rand()%2+2;
		kingdomcards[0]=rand()%(treasure_map - 7 + 1) + 7;
	
		for(k=1; k<10; k++){
			do{
				kingdomcards[k]=rand()%(treasure_map - 7 + 1) + 7; 
			}
			while(checkKingdomcard(kingdomcards, k));
		}
		
		initializeGame(numPlayer, kingdomcards, seed, &g);
		
		printf("\n******Information of Game********\n");
	
		printf("The seed is %d\n", seed);
		printf("Number of Player: %d\n", g.numPlayers);
		printf("Kingdom Cards: \n");
		for(l=0; l<5; l++)
			printf("%d ", kingdomcards[l]);
		printf("\n");
		for(l=5; l<10; l++)
        printf("%d ", kingdomcards[l]);
		printf("\n");
	
		printf("*********Game Begins**********\n");	
		while(!isGameOver(&g)){
			int x, index;
			int handPos=0, gainCard, result=1;
			int handCount = numHandCards(&g);
			int choice1, choice2, choice3;
	
			if(checkNumAction(&g)>0){
			do{
				handPos = rand()%handCount;
				gainCard = g.hand[g.whoseTurn][handPos];
				if(gainCard >= adventurer && gainCard <= treasure_map) 
					result = 0;
				}while(result==1);
	
			randomChoice(&g, gainCard, &choice1, &choice2, &choice3);		
			playCard(handPos, choice1, choice2, choice3, &g);
			printf("Player %d: played %d\n", g.whoseTurn+1, gainCard);
			}

			else
				printf("Player %d: skip play phase\n", g.whoseTurn+1);
			int size=0, money=checkMoney(&g);
			int remain_supply[treasure_map+1];

	
			for(x=0; x<treasure_map+1; x++){
				if(money >= getCost(x) && supplyCount(x, &g)>0){
					remain_supply[size] = x;
					size++;
				}
			}

			if(size>0){
				index = rand()%size;
				gainCard = remain_supply[index];

				if(buyCard(gainCard, &g)==0)
					printf("Player %d: bought %d\n", g.whoseTurn+1, gainCard);
			}
			printf("Player %d: end turn\n", g.whoseTurn+1);
			endTurn(&g);
		}
		printf("\n********Game Over**********\n");

	for(j=0; j<g.numPlayers; j++)
		printf("Player %d: %d\n", j+1, scoreFor(j, &g));
	int players[g.numPlayers];
	getWinners(players, &g);
	
	for(j=0; j<g.numPlayers; j++)
		if(players[j]==1)
			printf("Player %d is the winner\n", j+1);
	}
	
	return 0;
}