// C1.c
#include <stdio.h>

int main() {
    char name[] = "Keanu";
    char filename[20];
	
	// print header
	printf("DS Assignment-1, Summer 2023,\n Keanu Anderson-Pola, Tro893\n");
	
    // dynamically generate filename
    sprintf(filename, "%s.txt", name);
    FILE *file = fopen(filename, "w"); 
    
    if (file == NULL) {
        printf("Failed to create file.\n");
        return 1;
    }
    // add name to have something to read in C3
    fprintf(file, "Keanu Anderson-Pola\n");

    fclose(file);
    printf("File created.\n");
    return 0;
}
