#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dicegame.h"

//random num generator (RNG)
int getRandomNumber(int min, int max) {
	int rand_num;
	//logic
	rand_num = (rand() % (max - min + 1)) + min;
	
	return rand_num;
}

//calc type of round based on RNG
ROUNDTYPE getRoundType() {
	int chance = getRandomNumber(0, 9);
	
	if (chance < 2) { // 20% chance 
		return BONUS;
	}
	else if (chance < 5) { // 30% chance
		return DOUBLE;
	}
	else { // 50% chance
		return REGULAR;
	}
	return -1;
}

//allocate points by RNG and then change according to the type of round 
int getRoundPoints(ROUNDTYPE roundtype) {
	int points = 10 * getRandomNumber(1, 10);
	
	switch(roundtype) {
		case 0: //BONUS
			points = 200;
			return points;
		case 1: //DOUBLE
			return (points * 2);
		case 2: //REGULAR
			return points;
		default:
			printf("ERROR IN ROUNDPOINTS");
			return -1;
		}
}

//printfunc
void printPlayerPoints(int p1, int p2) {
	
	printf("P1: %d\n", p1);
	printf("P2: %d\n", p2);

	return;
}

//printfunc
void printRoundInfo(ROUNDTYPE t, int dice, int points) {
	char t_string[10];
	//put t -> t_string to print ROUNDTYPE string
	switch(t) {
		case 0:
			strcpy(t_string, "BONUS");
			break;
		case 1:
			strcpy(t_string, "DOUBLE");
			break;
		case 2:
			strcpy(t_string, "REGULAR");
			break;
		default:
			printf("ERROR IN PRINTROUNDINFO");
			return;
	}

	printf("Type\t: %s\n", t_string);
	printf("Dice\t: %d\n", dice);
	printf("Points\t: %d\n", points);

	return;
}

