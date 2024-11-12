#include <stdio.h>

// Calculate discount based on age of oldest visitor
double calc_discount(int age, double cost) {
    if (age > 65) {
        return cost * 0.10;
    }
    return 0;
}

// Calculate total based on room cost * number of nights - discount
double calc_total(int num_nights, double room_cost, double discount) {
    return (room_cost * num_nights) - discount;
}

int main() {
    int num_groups, num_people, num_nights, age_oldest;
    double room_cost = 0;
    double total_cost = 0;
    double total_cost_all_groups = 0;
    char* room_type;
    
    // Get number of groups which determines for loop iterations
    printf("Enter the number of groups on reservation, each group may have between 1 and 4 guests: \n");
    scanf("%d", &num_groups);
    
    // Main program logic
    for (int i = 0; i < num_groups; i++) {
        // Use do ... while loops to use post test logic and re-run if there's invalid input
        do {
            printf("Enter number of guests (1-4): \n");
            scanf("%d", &num_people);
            if (num_people < 1 || num_people > 4) {
                printf("Invalid input. Please enter a number between 1 and 4.\n");
            }
        } while (num_people < 1 || num_people > 4);
        
        do {
            printf("Enter number of nights (1-30): \n");
            scanf("%d", &num_nights);
            if (num_nights < 1 || num_nights > 30) {
                printf("Invalid input. Please enter a number between 1 and 30.\n");
            }
        } while (num_nights < 1 || num_nights > 30);
        
        do {
            printf("Enter age of oldest visitor (18-100): \n");
            scanf("%d", &age_oldest);
            if (age_oldest < 18 || age_oldest > 100) {
                printf("Invalid input. Please enter an age between 18 and 100.\n");
            }
        } while (age_oldest < 18 || age_oldest > 100);
        
        // switch to find room type based on number of people
        switch(num_people) {
            case 1:
            case 2:
                room_type = "King and sofa bed";
                room_cost = 100;
                break;
            case 3:
            case 4:
                room_type = "Two queens";
                room_cost = 130;
                break;
            default:
                printf("\nInvalid number of people. Please try again.\n");
                return 0;
        }
        
        // Calc total before discount
        total_cost = room_cost * num_nights;
        double discount = calc_discount(age_oldest, total_cost);
        // Update total cost based on discount
        total_cost = calc_total(num_nights, room_cost, discount);
        // Update total cost for all groups on each loop
        total_cost_all_groups += total_cost;
        
        // List group number, room type, and total cost of room
        printf("\nGroup #%d:", i+1);
        printf("\nType of room: \n%s", room_type);
        printf("\nTotal cost of reservation based on discount, type of room, # of nights: \n$%.2lf\n", total_cost);
    }
    
    // List total and mean cost for all groups
    printf("\nTotal cost for all groups: $%.2lf", total_cost_all_groups);
    printf("\nMean room cost per group: $%.2lf", total_cost_all_groups/num_groups);
    
    return 0;
}

