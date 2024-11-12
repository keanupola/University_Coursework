// C4.c
#include <stdio.h>

int main() {
    char name[] = "Keanu";
    char number[] = "893";
    char filename[20];
	// print header
	printf("DS Assignment-1, Summer 2023,\n Keanu Anderson-Pola, Tro893\n");
    
    sprintf(filename, "%s.txt", name);
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }
    //write the 3 digits to file
    fprintf(file, "%s", number);
    fclose(file);
    printf("Successfully wrote to file.\n");
    return 0;
}
