#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

#define MAX 10

//routerecord struct
typedef struct {

	char origin[MAX]; 
	char destination[MAX];
	char airline[MAX];
	int passengers[6]; //6 months

} RouteRecord;

//searchtype enum
typedef enum SearchType {
	ROUTE, //origin & destination
	ORIGIN,
	DESTINATION,
	AIRLINE
} SearchType;

//declare functions
RouteRecord* createRecords(FILE* fileIn);
int fillRecords(RouteRecord *r, FILE* fileIn);
int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);
void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st);
void printMenu();

#endif
