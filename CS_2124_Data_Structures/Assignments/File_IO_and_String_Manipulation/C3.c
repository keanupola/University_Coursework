// C3.c
#include <stdio.h>

int main() {
    char name[] = "Keanu";
    char filename[20];
	// print header
	printf("DS Assignment-1, Summer 2023,\n Keanu Anderson-Pola, Tro893\n");
    
    sprintf(filename, "%s.txt", name);
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }
    
    char c;
    printf("Reading file:\n");
    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
    }
    
    fclose(file);
    return 0;
}
