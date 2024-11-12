#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flights.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR NO ARGS\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("ERROR FILE NOT OPEN\n");
        return 1;
    }

    Flight *flights = (Flight*) malloc(NUM_FLIGHTS * sizeof(Flight));
    int i;
    for (i = 0; i < NUM_FLIGHTS; i++) {
        fscanf(file, "%[^,],%[^,],%[^,],%d", flights[i].origin, flights[i].destination, flights[i].airline, &flights[i].passengers);
        fgetc(file); // Consume the newline character
    }

    char airline_code[3];
    printf("Enter a two letter airline code: ");
    scanf("%2s", airline_code);

    int flights_count = 0;
    int passengers_count = 0;
    for (i = 0; i < NUM_FLIGHTS; i++) {
        if (strcmp(flights[i].airline, airline_code) == 0) {
            flights_count++;
            passengers_count += flights[i].passengers;
        }
    }

    printf("airline: %s\n", airline_code);
    printf("flights: %d\n", flights_count);
    printf("passengers: %d\n", passengers_count);

    fclose(file);
    free(flights);

    return 0;
}

