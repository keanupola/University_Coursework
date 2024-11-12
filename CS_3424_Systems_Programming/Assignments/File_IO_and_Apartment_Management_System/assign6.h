#ifndef ASSIGN6_H
#define ASSIGN6_H

#define FILENAME "apartments.dat"
#define MAX_APARTMENTS 100

typedef struct {
    char firstName[32];
    char lastName[32];
    char leaseStart[16];
    char leaseEnd[16];
    int balance;
} Apartment;

#endif
