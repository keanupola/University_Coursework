#include stdio.h

STRUCT Room:
    Room_type      // King, Queen, etc.
    Status[30]     // Array for each day of the month. "available" or "reserved"

/* Function Declarations */

initializeRooms(Room rooms[50][30]):
    FOR each room in rooms:
        IF room index <= 25:
            room.Room_type = "King and sofa bed"
        ELSE:
            room.Room_type = "Two queens"
        FOR each date in 30 days:
            room.Status[date] = "available"

float calculateDiscount(age):
    IF age > 65:
        RETURN 0.10
    ELSE:
        RETURN 0

float calculateTotal(nights, cost, discount):
    RETURN nights * cost * (1 - discount)

makeReservation(rooms[50][30], room_type_choice, start_date, num_nights):
    FOR each room in rooms:
        IF room.Room_type == room_type_choice:
            isAvailable = TRUE // temp var to check if room is available on the range of dates
            FOR (i=0; i<num_nights, i++):
                IF room.Status[start_date + i] != "available":
                    isAvailable = FALSE
                    BREAK
            IF isAvailable:
                FOR i from 0 to num_nights-1:
                    room.Status[start_date + i] = "reserved"
                RETURN
    PRINT "No rooms of this type are available on the chosen dates."

showAvailableRooms(rooms[50][30], desired_date, num_nights):
    FOR each room in rooms:
        isAvailable = TRUE // temp var to check if room is available on the range of dates
        FOR (i=0; i<num_nights, i++):
            IF room.Status[desired_date + i] != "available":
                isAvailable = FALSE
                BREAK
        IF isAvailable:
            PRINT room.Room_type, "is available from", desired_date, "for", num_nights, "nights."


/* End of Function Declarations */

int main():
    Room rooms[50][30]  // Represents 50 rooms for a month
    initializeRooms(rooms)
    // Menu start
    WHILE user doesn't exit:
        SCAN userchoice
        SWITCH userchoice:
            CASE "make reservation":
                SCAN num_people, num_nights, age_oldest, desired_date

                // Validating user input
                DO:
                    IF input not valid:
                        PRINT error message
                        SCAN again
                WHILE input not valid

                SWITCH num_people:
                    CASE 1 or 2:
                        room_type_choice = "King and sofa bed"
                        room_cost = 100
                    CASE 3 or 4:
                        room_type_choice = "Two queens"
                        room_cost = 130
                    DEFAULT:
                        PRINT "Groups of 5+ are not able to stay at the hotel."
                        RETURN to main menu

                total_cost = calculateTotal(num_nights, room_cost, calculateDiscount(age_oldest))
                PRINT type of room, total cost

                makeReservation(rooms, room_type_choice, desired_date, num_nights)

            CASE "view available rooms":
                SCAN desired_date, num_nights
                showAvailableRooms(rooms, desired_date, num_nights)

            CASE "exit":
                EXIT the application

END
