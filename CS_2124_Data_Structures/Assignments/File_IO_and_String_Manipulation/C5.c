// C5.c
#include <stdio.h>

int main() {
    char name[] = "Keanu";
    char filename[20];
	// print header
	printf("DS Assignment-1, Summer 2023,\n Keanu Anderson-Pola, Tro893\n");
    
    sprintf(filename, "%s.txt", name);
    FILE *file = fopen(filename, "r+");
    
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }
    // move file pointer to EOF
    fseek(file, 0, SEEK_END);
    fclose(file);
    printf("Successfully moved to EOF.\n");
    return 0;
}
