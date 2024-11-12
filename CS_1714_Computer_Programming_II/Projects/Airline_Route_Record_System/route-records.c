#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

//creates the array of RouteRecord’s and initializes it
RouteRecord* createRecords(FILE* fileIn) {

	int recordCount = 0;
	char buffer[256];

	//count the number of records in the CSV file (-header)
	while (fgets(buffer, sizeof(buffer), fileIn) != NULL) {
	recordCount++;
	}
    
	//exclude the header from the record count
	recordCount--;

	//dynamically allocate memory for RouteRecords array
	RouteRecord* records = (RouteRecord*) malloc(recordCount * sizeof(RouteRecord));

	//initialize each RouteRecord's passenger counts to 0
	for (int i = 0; i < recordCount; i++) {
		for (int j = 0; j < 6; j++) {
			records[i].passengers[j] = 0;
		}
	}

	//rewind the file pointer
	rewind(fileIn);

	//return the pointer to dynamically allocated array
	return records;
}

//finds record with same origin/destination airport, & airline
int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx) {

	//check for null pointers
	if (r == NULL || origin == NULL || destination == NULL || airline == NULL) {
		return -1;
	}	

	//base case 1: not found
	if (curIdx >= length) {
		return -1;
	}

	//base case 2: origin, destination, and airline match
	if (strcmp(r[curIdx].origin, origin) == 0 && strcmp(r[curIdx].destination, destination) == 0 && strcmp(r[curIdx].airline, airline) == 0) {
		return curIdx;
	}

	//recursive case:
	return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1);

}


//fill array with csv
int fillRecords(RouteRecord* r, FILE* fileIn) {
	char* line = malloc(256 * sizeof(char)); //avoid stack overflow
	int recordsUsed = 0;
	int uniqueRoutes = 0;
	RouteRecord routes[10000]; //big array to avoid running out of space (large csv)
	
	//"line" check
	if (line == NULL) {
		printf("Error allocating memory for line buffer.\n");
		exit(1);
	}

	//skip/store header line
	fgets(line, 256, fileIn);

	while (fgets(line, 256, fileIn)) {
		char origin[4], destination[4], airline[8], type[16];
		int month, passengers;

        	//parse the record
	        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d", &month, origin, destination, airline, type, &passengers);

        	//find route in the array
	        int index = findAirlineRoute(r, recordsUsed, origin, destination, airline, 0);

        	//route found case, add passengers for month
	        if (index != -1) {
        	    r[index].passengers[month - 1] += passengers;
        	}
	        //route not found case, add new route
        	else {
			strcpy(r[recordsUsed].origin, origin);
			strcpy(r[recordsUsed].destination, destination);
			strcpy(r[recordsUsed].airline, airline);
			memset(r[recordsUsed].passengers, 0, sizeof(r[recordsUsed].passengers));
			r[recordsUsed].passengers[month - 1] = passengers;
			recordsUsed++;

 		}	
	}
	
	//check if route is unique
	for (int i = 0; i < recordsUsed; i++) {
		//create "route" strings for current record
		char route[12];
		snprintf(route, sizeof(route), "%s-%s-%s", r[i].airline, r[i].origin, r[i].destination);
		int found = 0;
		//create "existing" route 
		for (int j = 0; j < uniqueRoutes; j++) {
			char existingRoute[12];
			snprintf(existingRoute, sizeof(existingRoute), "%s-%s-%s", routes[j].airline, routes[j].origin, routes[j].destination);
			//found = flag for uniqueness
			if (strcmp(route, existingRoute) == 0) {
				found = 1;
				break;
			}
		}
		//case for when not found
		if (!found) {
			strcpy(routes[uniqueRoutes].origin, r[i].origin);
			strcpy(routes[uniqueRoutes].destination, r[i].destination);
			strcpy(routes[uniqueRoutes].airline, r[i].airline);
			uniqueRoutes++;
		}
	}

	printf("Unique routes: %d\n", uniqueRoutes);
	free(line);

	return recordsUsed;
}

//search RouteRecord array and prints results
void searchRecords(RouteRecord *r, int length, const char *key1, const char *key2, SearchType st) {
	int totalPassengers = 0;
	int monthlyPassengers[6] = {0};
	int matchingRecords = 0;

	printf("\nSearch results:\n");
	
	for (int i = 0; i < length; i++) {
		int match = 0;
		//match RouteRecorde based on SearchType
		switch (st) {
			case ROUTE:
				match = (strcmp(r[i].origin, key1) == 0 && strcmp(r[i].destination, key2) == 0);
				break;
			case ORIGIN:
				match = (strcmp(r[i].origin, key1) == 0);
				break;
			case DESTINATION:
				match = (strcmp(r[i].destination, key1) == 0);
				break;
			case AIRLINE:
				match = (strcmp(r[i].airline, key1) == 0);
				break;
		}
		//match found
		if (match) {
			matchingRecords++;
			printf("Airline: %s, Route: %s-%s\n", r[i].airline, r[i].origin, r[i].destination);
			//update the monthly and total passenger counts
			for (int j = 0; j < 6; j++) {
			monthlyPassengers[j] += r[i].passengers[j];
			totalPassengers += r[i].passengers[j];
			}
		}

	}
	//no matches
	if (matchingRecords == 0) {
		printf("No matching records found.\n");
		return;
	}
	
	printf("\nTotal passengers: %d\n", totalPassengers);
	
	printf("Monthly passengers:\n");
	for (int i = 0; i < 6; i++) {
		printf("Month %d: %d\n", i + 1, monthlyPassengers[i]);
	}

	printf("Average passengers per month:\n");
	for (int i = 0; i < 6; i++) {
		printf("Month %d: %.2f\n", i + 1, (double)monthlyPassengers[i] / matchingRecords);
	}
}

//print menu
void printMenu() {

	printf("\n\n######### Airline Route Records Database MENU #########\n");
	printf("1. Search by Route\n");
	printf("2. Search by Origin Airport\n");
	printf("3. Search by Destination Airport\n");
	printf("4. Search by Airline\n");
	printf("5. Quit\n");
	printf("Enter your selection: ");
}

