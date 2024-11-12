#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

int main(int argc, char *argv[]) {
	/* 1. Declare variables here */
	FILE* fileIn;
	RouteRecord* records = NULL;
	int numRecords;
	char fileName[MAX];
	char input[MAX];
	char searchKey[MAX];
	int quit = 0;

	/* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */
	if(argc < 2) {
		printf("ERROR: Missing file name\n");
		return 1;
	}

	/* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */
	strcpy(fileName, argv[1]);
	printf("Opening %s...\n", fileName);
	fileIn = fopen(fileName, "r");

	/* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
	if(fileIn == NULL) {
		printf("ERROR: Could not open file\n");
		return 1;
	}

	// 5. Do the following to load the records into an array of RouteRecords
	
	//5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.
	records = createRecords(fileIn);
	
	//5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
	numRecords = fillRecords(records, fileIn);
	
	//5.3 Close the the file.
	fclose(fileIn);

	//6. Create an infinite loop that will do the following:
	while(!quit) {

		//6.1 Call printMenu()
		printMenu();

		//6.2 Ask the user to input a value for the menu
		printf("Enter selection: ");
		fgets(input, MAX, stdin);

		//6.3 Handle the case w/non-integer value 
		int selection = atoi(input);

		//6.4 Create a switch/case statement for menu
			//6.4.1 Each option requires the user to enter a search key
		switch(selection) {
		
			case 1:
				printf("Enter route: ");
				fgets(input, MAX, stdin);
				input[strcspn(input, "\n")] = '\0';
				searchRecords(records, numRecords, input, NULL, ROUTE);
				break;
			case 2:
				printf("Enter origin airport code: ");
				fgets(input, MAX, stdin);
				input[strcspn(input, "\n")] = '\0';
				searchRecords(records, numRecords, input, NULL, ORIGIN);
				break;
			case 3:
				printf("Enter destination airport code: ");
				fgets(input, MAX, stdin);
				input[strcspn(input, "\n")] = '\0';
				searchRecords(records, numRecords, input, NULL, DESTINATION);
				break;
			case 4:
				printf("Enter the airline name: ");
				fgets(searchKey, MAX, stdin);
				//remove newline
				searchKey[strcspn(searchKey, "\n")] = 0;
				searchRecords(records, numRecords, searchKey, NULL, AIRLINE);
				break;
			//6.4.2 Quit needs to free the array
			case 5:
				printf("Quitting...\n");
				free(records); //free memory 
				exit(0);
				break;
			default:
				printf("Invalid choice. Please enter a number between 1 and 4.\n");
		}
	}

	return 0;
}

