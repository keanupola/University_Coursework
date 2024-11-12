#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <stdio.h>

typedef struct Flight {
    char origin[4];
    char destination[4];
    char airline[3];
    int passengers;
} Flight;

#define NUM_FLIGHTS 200

#endif // FLIGHTS_H

