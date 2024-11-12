#include <stdio.h>

int main() {
    // Define 2D array to store 100 integers, 10X10
    int numbers[10][10];
    FILE *file;

    // Open data.txt in read mode
    file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1; // Return with error
    }

    // Read integers from data.txt and store them in the 2D array
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            fscanf(file, "%d", &numbers[i][j]);
        }
    }

    // Close
    fclose(file);

    // Print 2D array
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", numbers[i][j]);
        }
        printf("\n"); 
    }

    return 0;
}
