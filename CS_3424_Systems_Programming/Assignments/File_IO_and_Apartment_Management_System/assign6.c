#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "assign6.h"

// Function declarations
void createApartment();
void readApartment();
void updateApartment();
void deleteApartment();

int main() {
    char choice;
    char inputLine[100];

    while (1) {
        // 1. Upon running your program, the user should be presented with the following menu
        printf("\nApartment Management System\n");
        printf("----------------------------\n");
        printf("C: Create a new apartment record\n");
        printf("R: Read an existing apartment record\n");
        printf("U: Update an existing apartment record\n");
        printf("D: Delete an existing apartment record\n");
        printf("Q: Quit\n");

        // 2. The user then enters a one-character action (upper or lowercase)
        printf("\nEnter your choice (C/R/U/D/Q): ");
        if (fgets(inputLine, sizeof(inputLine), stdin) == NULL) {
            break; // Exit if EOF is reached or error occurs
        }
        if (sscanf(inputLine, " %c", &choice) != 1) {
            printf("ERROR: Invalid input.\n");
            continue; // Skip the rest of the loop if input is invalid
        }
        // Menu logic
        if (choice == 'Q' || choice == 'q') {
            printf("Exiting program.\n");
            break;
        }

        switch (choice) {
            case 'C':
            case 'c':
                createApartment();
                break;
            case 'R':
            case 'r':
                readApartment();
                break;
            case 'U':
            case 'u':
                updateApartment();
                break;
            case 'D':
            case 'd':
                deleteApartment();
                break;
            default:
                printf("ERROR: Invalid choice.\n");
        }
    }

    return 0;
}


// C: an apartment record is created
void createApartment() {
    // Open file r+w, create if DNE
    int fd = open(FILENAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        printf("Error opening file");
        return;
    }

    char inputBuffer[100];
    Apartment newApartment;
    int aptNumber;


    // (a) From the terminal, read the following one at a time
    // i. Apartment number (zero-indexed integer)
    printf("\nEnter apartment number: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%d", &aptNumber);

    // Position file pointer and check if record already exists
    lseek(fd, aptNumber * sizeof(Apartment), SEEK_SET);
    read(fd, &newApartment, sizeof(Apartment));
    if (strlen(newApartment.firstName) > 0) {
        // (c) ERROR: apartment already exists
        printf("\nERROR: apartment already exists\n");
        close(fd);
        return;
    }

    // ii. First name
    printf("\nEnter first name: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%s", newApartment.firstName);
    // iii. Last name
    printf("\nEnter last name: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%31[^\n]", newApartment.lastName);
    // iv. Lease start date (string with slashes)
    printf("\nEnter lease start date (MM/DD/YYYY): ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%15s", newApartment.leaseStart);
    // v. Lease end date (string with slashes)
    printf("\nEnter lease end date (MM/DD/YYYY): \n");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%15s", newApartment.leaseEnd);
    // (b) Write binary structure to file. Starting balance: 900
    newApartment.balance = 900;
    lseek(fd, aptNumber * sizeof(Apartment), SEEK_SET);
    write(fd, &newApartment, sizeof(Apartment));

    close(fd);
}

// R: read an existing apartment’s information
void readApartment() {
    // Open file r
    int fd = open(FILENAME, O_RDONLY);
    if (fd < 0) {
        printf("Error opening file");
        return;
    }

    int aptNumber;
    char inputBuffer[100];

    // (a) Prompt the user for an apartment number: Enter an apartment number:
    printf("\nEnter apartment number: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%d", &aptNumber);
    Apartment apt;
    lseek(fd, aptNumber * sizeof(Apartment), SEEK_SET);
    read(fd, &apt, sizeof(Apartment));

    if (strlen(apt.firstName) > 0) {
        // (c) Print apartment information
        printf("Apartment Number: %d\n", aptNumber);
        printf("Tenant Name: %s, %s\n", apt.lastName, apt.firstName);
        printf("Lease Start: %s\n", apt.leaseStart);
        printf("Lease End: %s\n", apt.leaseEnd);
        printf("Current Balance: %d\n", apt.balance);
    } else {
        // (d) ERROR: apartment not found
        printf("ERROR: apartment not found\n");
    }

    close(fd);
}


// U: update an existing apartment record
void updateApartment() {
    // Open file r+w
    int fd = open(FILENAME, O_RDWR);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    int aptNumber;
    char inputBuffer[100];
    Apartment apt;

    // (a) Prompt the user for the following one at a time
    // i. Apartment number (zero-indexed integer)
    printf("\nEnter apartment number: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%d", &aptNumber);

    lseek(fd, aptNumber * sizeof(Apartment), SEEK_SET);
    read(fd, &apt, sizeof(Apartment));

    if (strlen(apt.firstName) == 0) {
        // (d) ERROR: apartment not found
        printf("ERROR: apartment not found\n");
        close(fd);
        return;
    }

    // ii. First name
    printf("\nEnter first name (or press enter to skip): ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    if (strcmp(inputBuffer, "\n") != 0) {
        sscanf(inputBuffer, "%31s", apt.firstName);
    }
    // iii. Last name
    printf("\nEnter last name (or press enter to skip): ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, " %[^\n]s", apt.lastName);

    // iv. Lease start date (string with slashes)
    printf("\nEnter lease start date (MM/DD/YYYY) (or press enter to skip): ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%s", apt.leaseStart);

    // v. Lease end date (string with slashes)
    printf("\nEnter lease end date (MM/DD/YYYY) (or press enter to skip): ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%s", apt.leaseEnd);

    // vi. Balance (integer)
    printf("\nEnter balance (or press enter to skip): \n");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    if (strcmp(inputBuffer, "\n") != 0) {
        sscanf(inputBuffer, "%d", &apt.balance);
    }
    // (b) Locate the specified apartment using the apartment number.
    // (c) Update each of the corresponding fields based on user input.
    lseek(fd, aptNumber * sizeof(Apartment), SEEK_SET);
    write(fd, &apt, sizeof(Apartment));

    close(fd);
}



// D: delete an existing apartment record
void deleteApartment() {
    // Open file r+w
    int fd = open(FILENAME, O_RDWR);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    int aptNumber;
    char inputBuffer[100];

    // (a) Prompt the user for an apartment number: Enter an apartment number:
    printf("\nEnter apartment number: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%d", &aptNumber);

    // Position file pointer to the apartment record
    lseek(fd, aptNumber * sizeof(Apartment), SEEK_SET);

    Apartment apt;
    read(fd, &apt, sizeof(Apartment));

    // Check if the apartment exists
    if (strlen(apt.firstName) == 0) {
        // (d) If the apartment is not found, print the following error instead
        printf("ERROR: apartment not found\n");
        close(fd);
        return;
    }

    // Prepare an empty Apartment structure to overwrite the existing one
    Apartment emptyApartment;
    memset(&emptyApartment, 0, sizeof(Apartment));

    // Write the empty structure to the file, effectively deleting the record
    lseek(fd, aptNumber * sizeof(Apartment), SEEK_SET);
    write(fd, &emptyApartment, sizeof(Apartment));

    // (c) Print success message: Record apt_number was successfully deleted.
    printf("Record %d was successfully deleted.\n", aptNumber);

    close(fd);
}

