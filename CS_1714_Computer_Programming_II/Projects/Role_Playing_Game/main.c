#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "champion.h"

int main(int argc, char *argv[]) {
	//argc error
	if (argc != 2) {
		printf("Error: Please provide the number of starting Champions as a command line argument.\n");
		return 1;
	}
	int num_champions = atoi(argv[1]); //int conversion
	//nonpositive int error
	if (num_champions <= 0) {
		printf("Error: The number of starting Champions must be a positive integer.\n");
		return 1;
	}

	srand(time(NULL)); //RNG seed

	//lists creation
	Champion *player1Head = buildChampionList(num_champions);
	Champion *player2Head = buildChampionList(num_champions);

	//game loop
	int round = 1;
	printf("============= PLAYER 1 V PLAYER 2 SHOWDOWN ============\n\n");
	while (player1Head != NULL && player2Head != NULL) {
		printf("----- ROUND %d -----\n", round);
		printf("Player 1: ");
		printChampionList(player1Head);
		printf("Player 2: ");
		printChampionList(player2Head);
		printf("Player 1 is a %s and Player 2 is a %s\n", roleToString(player1Head->role), roleToString(player2Head->role));

		playRound(&player1Head, &player2Head);

		printf("\n");
		round++;
	}
	printf("============ GAME OVER  =============\n");
	
	if (player1Head == NULL && player2Head == NULL) {
		printf("The game ends in a tie!\n");
	} else if (player1Head != NULL) {
		printf("Player 1 wins!\n");
	} else {
		printf("Player 2 wins!\n");
	}

	destroyChampionList(player1Head);
	destroyChampionList(player2Head);

	return 0;
}

