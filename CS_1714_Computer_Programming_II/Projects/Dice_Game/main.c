// Add all the includes for the required header files
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "dicegame.h"

int main(void){

	// Initialize the srand() to start the random generator
	unsigned int seed = (unsigned int) time(NULL);
	srand(seed);
	
	//vvar init
	int p1_points = 0, p2_points = 0;
	int current_player, rounds, dice, points, winner;	
	int i = 0;	
	ROUNDTYPE type;

	//user prmpt
	printf("How many rounds would you like to play?\n");
	scanf("%d", &rounds);
	printPlayerPoints(p1_points, p2_points);

	// Set up the loop to go through all the rounds one at a time
	current_player = getRandomNumber(1, 2);
	
	for (i = 0; i < rounds; i++) {
		
		printf("\nROUND %d\n", (i + 1));
		printf("--------\n");
		printf("Player\t: %d\n", current_player);
		
		//initialize round vars
		dice = getRandomNumber(1, 6);
		type = getRoundType(); 		points = getRoundPoints(type);

		printRoundInfo(type, dice, points);

		// MAIN GAME LOGIC		
		if (current_player == 1) {
			if ((dice % 2) != 0) {
				p1_points += points;
			}
			else {
				p1_points -= points;
				current_player = 2;
			}
		}
		else {
			if (((dice % 2) == 0)) {
				p2_points += points;
			}
			else {
				p2_points -= points;
				current_player = 1;
			}	
		}	
		printPlayerPoints(p1_points, p2_points);
	}
	printf("\nGAME OVER!!\n");
	
	//calc winner	
	if (p1_points > p2_points) {
    		printf("P1 Won\n\n");
	}
	else if (p2_points > p1_points) {
    		printf("P2 Won\n\n");
	} 
	else {
    		printf("Tie\n\n");
	}


	return 0;
}

