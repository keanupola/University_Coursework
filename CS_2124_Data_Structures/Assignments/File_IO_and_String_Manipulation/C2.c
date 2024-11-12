// C2.c
#include <stdio.h>

int main() {
    char name[] = "Keanu";
    char filename[20];
	
	// print header
	printf("DS Assignment-1, Summer 2023,\n Keanu Anderson-Pola, Tro893\n");
	
    // same convention as C1, continues throughout
    sprintf(filename, "%s.txt", name);
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }
    
    fclose(file);
    printf("File opened and closed successfully.\n");
    return 0;
}
