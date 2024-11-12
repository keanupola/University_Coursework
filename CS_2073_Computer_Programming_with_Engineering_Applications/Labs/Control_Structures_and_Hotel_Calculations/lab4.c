#include <stdio.h>

double calc_discount(int age, double cost) {
    if (age > 65) {
        return cost * 0.10;
    }
    return 0;
}

double calc_total(int num_nights, double room_cost, double discount) {
    return (room_cost * num_nights) - discount;
}

int main()
{
    int num_people, num_nights;
    int age_oldest;
    double room_cost = 0;
    double total_cost = 0;
    char* room_type;
    
    printf("Enter number of people on the reservation: \n");
    scanf("%d", &num_people);
    printf("Enter number of nights: \n");
    scanf("%d", &num_nights);
    printf("Enter age of oldest visitor: \n");
    scanf("%d", &age_oldest);
    
    // switch to meet lab reqs, if 5+ program ends
    switch(num_people) {
        // 1-2 tier
        case 1:
        case 2:
            room_type = "King and sofa bed";
            room_cost = 100;
            break;
        // 3-4 tier
        case 3:
        case 4:
            room_type = "Two queens";
            room_cost = 130;
            break;
        // 5+ tier and edge case statement
        default:
            printf("\nToo many people or invalid number, please try again or book separately\n");
            return 0;
    }
    // Calc total before discount
    total_cost = room_cost * num_nights;
    double discount = calc_discount(age_oldest, total_cost);
    // Update total cost based on discount
    total_cost = calc_total(num_nights, room_cost, discount);
    
    printf("\nType of room: \n%s\n", room_type);
    printf("\nTotal cost of reservation based on discount, type of room, # of nights: \n$%.2lf", total_cost);
    
    return 0;
}
