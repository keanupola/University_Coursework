// C7.c
#include <stdio.h>
#include <string.h>

int main() {
    char first_name[] = "Keanu";
    char last_name[] = "Anderson-Pola";
    char full_name[40];
	// print header
	printf("DS Assignment-1, Summer 2023,\n Keanu Anderson-Pola, Tro893\n");
    
    strcpy(full_name, first_name);
    strcat(full_name, " "); // add space
    strcat(full_name, last_name);
    
    printf("Concatenated string: %s\n", full_name);
    return 0;
}
