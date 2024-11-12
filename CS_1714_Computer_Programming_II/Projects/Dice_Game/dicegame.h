#ifndef DICEGAME_H
#define DICEGAME_H

//Create enum ROUNDTYPE for three round types:BONUS, DOUBLE, REGULAR
typedef enum  {
    BONUS, DOUBLE, REGULAR
} ROUNDTYPE ;

//function prototypes, self explanatory

int getRandomNumber(int min, int max);

ROUNDTYPE getRoundType();

int getRoundPoints(ROUNDTYPE roundtype);

void printPlayerPoints(int p1, int p2);

void printRoundInfo(ROUNDTYPE t, int dice, int points);



#endif
