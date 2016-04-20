#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);
int adventurer(struct gameState *state, int z, int currentPlayer,
			int nextPlayer, int drawntreasure, int cardDrawn, int tempHand[]);
int council_room(int i, int currentPlayer, struct gameState *state, int handPos);
int feast(struct gameState *state, int i, int x, int currentPlayer, int temphand[], int choice1);
int mine(struct gameState *state, int j, int i, int choice1, int choice2, int currentPlayer);
int remodel(struct gameState *state, int j, int i, int choice1, int choice2, int currentPlayer);
#endif