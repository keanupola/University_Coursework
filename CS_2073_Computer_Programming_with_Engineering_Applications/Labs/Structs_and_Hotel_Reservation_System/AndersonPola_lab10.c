#include <stdio.h>
#include <string.h>

// Define constants
#define MAX_ROOMS 50
#define DAYS_IN_MONTH 30
#define ROOM_TYPE_LENGTH 20
#define ROOM_STATUS_LENGTH 10

// struct for the Room
struct Room {
    char Room_type[ROOM_TYPE_LENGTH]; // King, Queen, etc.
    char Status[DAYS_IN_MONTH][ROOM_STATUS_LENGTH]; // Array for each day of the month
};

/* Function Declarations */

// Handle user input
int getUserInput(int* num_people, int* num_nights, int* age_oldest, int* start_date);

// Validate user input for values
int isValidInput(int num_people, int num_nights, int start_date);

// Initialize rooms
void initializeRooms(struct Room rooms[MAX_ROOMS]);

// Calculate discount based on age
float calculateDiscount(int age);

// Calculate the total cost of the reservation
float calculateTotal(int nights, float cost, float discount);

// Make reservation
void makeReservation(struct Room rooms[MAX_ROOMS], char* room_type_choice, int start_date, int num_nights);

// Show available rooms
void showAvailableRooms(struct Room rooms[MAX_ROOMS], int start_date, int num_nights);

int main() {
    struct Room rooms[MAX_ROOMS]; // Represents 50 rooms for a month, 25 King, 25 Queens
    int menu_choice;
    int num_people, num_nights, age_oldest, start_date;
    float room_cost, total_cost;
    char room_type_choice[ROOM_TYPE_LENGTH];

    // Initialize all rooms to "available"
    initializeRooms(rooms);

    // Menu loop
    do {
        printf("Enter your choice: \n1. Make reservation\n2. View available rooms\n3. Exit\n");
        scanf("%d", &menu_choice);

        switch (menu_choice) {
            case 1: // Make reservation
		if (!getUserInput(&num_people, &num_nights, &age_oldest, &start_date)) {
			printf("Invalid input. Please try again.\n");
			continue; // Skip to next iteration
		}

                // Room selection based on the number of people
                switch (num_people) {
                    case 1:
                    case 2:
                        strcpy(room_type_choice, "King and sofa bed");
                        room_cost = 100.0;
                        break;
                    case 3:
                    case 4:
                        strcpy(room_type_choice, "Two queens");
                        room_cost = 130.0;
                        break;
                    default:
                        printf("Error: Too many or few people\n");
                        continue; // Skip to next iteration
                }

                total_cost = calculateTotal(num_nights, room_cost, calculateDiscount(age_oldest));
                printf("Type of room: %s\nTotal cost: %.2f\n", room_type_choice, total_cost);

                makeReservation(rooms, room_type_choice, start_date, num_nights);
                break;

            case 2: // View available rooms
                printf("Enter the desired start date and number of nights:\n");
                if (scanf("%d %d", &start_date, &num_nights) != 2) {
                    printf("Invalid input. Please try again.\n");
                    continue;
                }
                showAvailableRooms(rooms, start_date, num_nights);
                break;


            case 3: // Exit
                printf("Exiting the application.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (menu_choice != 3);

    return 0;
}

/* Function Definitions */

void initializeRooms(struct Room rooms[MAX_ROOMS]) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        // Ternary to make rooms 0-24 King, and 25-49 Queens
        strcpy(rooms[i].Room_type, (i < 25) ? "King and sofa bed" : "Two queens");
        for (int j = 0; j < DAYS_IN_MONTH; j++) {
            strcpy(rooms[i].Status[j], "available"); // Copy "available" to room status to keep track
        }
    }
}

float calculateDiscount(int age) {
    if (age > 65) {
        return 0.10;
    }
    return 0;
}

float calculateTotal(int nights, float cost, float discount) {
    float total = nights * cost;
    return total - (total * discount);
}

void makeReservation(struct Room rooms[MAX_ROOMS], char* room_type_choice, int start_date, int num_nights) {
    // Loop through each room to find a room that matches the type.
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (strcmp(rooms[i].Room_type, room_type_choice) == 0) {
            int available = 1; // 1 = available, 0 = not available
            // Check availability for the required days
            for (int day = 0; day < num_nights; day++) {
                int dateIndex = start_date + day - 1; // Adjust for 0 index 
                if (dateIndex < DAYS_IN_MONTH) {
                    // Check if the room is already reserved
                    if (strcmp(rooms[i].Status[dateIndex], "reserved") == 0) {
                        available = 0; 
                        break;
                    }
                } else {
                    printf("Reservation exceeds month.\n");
                    return; 
                }
            }
            // If available for all dates, reserve room
            if (available) {
                for (int day = 0; day < num_nights; day++) {
                    int dateIndex = start_date + day - 1;
                    if (dateIndex < DAYS_IN_MONTH) {
                        strcpy(rooms[i].Status[dateIndex], "reserved");
                    }
                }
                // Prompt, success
                printf("Reservation made for a %s room.\n", room_type_choice);
                return; // Exit
            }
        }
    }
    // No room available for range
    printf("No available rooms for the selected dates.\n");
}


void showAvailableRooms(struct Room rooms[MAX_ROOMS], int start_date, int num_nights) {
    // Initialiaze counters
    int availableKings = 0;
    int availableQueens = 0;

    for (int i = 0; i < MAX_ROOMS; i++) {
        int available = 1; // Available

        for (int day = 0; day < num_nights; day++) {
            int dateIndex = start_date + day - 1; // 0 index
            if (dateIndex < DAYS_IN_MONTH) {
                if (strcmp(rooms[i].Status[dateIndex], "reserved") == 0) {
                    available = 0; // Not available
                    break;
                }
            } else {
                available = 0; // Exceeds month (30)
                break;
            }
        }
	// increment counters if available for more digestible format
        if (available) {
            if (strcmp(rooms[i].Room_type, "King and sofa bed") == 0) {
                ++availableKings;
            } else if (strcmp(rooms[i].Room_type, "Two queens") == 0) {
                ++availableQueens;
            }
        }
    }

    printf("We have %d \"King and Sofa\" and %d \"Double Queens\" available for these dates.\n", availableKings, availableQueens);
}



int getUserInput(int* num_people, int* num_nights, int* age_oldest, int* start_date) {
    printf("Enter the number of people, number of nights, age of the oldest visitor, and the start date:\n");
    if (scanf("%d %d %d %d", num_people, num_nights, age_oldest, start_date) != 4) {
        // Invalid
        return 0;
    }
    // Validate the input
    if (!isValidInput(*num_people, *num_nights, *start_date)) {
        // Invalid
        return 0;
    }
    return 1; // Valid
}


int isValidInput(int num_people, int num_nights, int start_date) {
    if (num_people < 1 || num_people > 4) {
        printf("Invalid number of people (1-4).\n");
        return 0; // Invalid
    }
    if (num_nights < 1 || num_nights > DAYS_IN_MONTH) {
        printf("Invalid number of nights (1-30).\n");
        return 0; // Invalid
    }
    if (start_date < 1 || start_date > DAYS_IN_MONTH) {
        printf("Invalid start date number (1-30).\n");
        return 0; // Invalid
    }
    if (start_date + num_nights - 1 > DAYS_IN_MONTH) {
        printf("Sorry, you can't stay past the 30th. Please enter a date and number of nights that won't exceed a month.\n");
        return 0; // Invalid
    }
    return 1; // Valid
}