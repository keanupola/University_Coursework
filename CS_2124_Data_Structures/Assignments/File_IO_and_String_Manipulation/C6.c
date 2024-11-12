// C6.c
#include <stdio.h>
#include <string.h>

int main() {
    char first_name[] = "Keanu";
    char copied_name[20];
	// print header
	printf("DS Assignment-1, Summer 2023,\n Keanu Anderson-Pola, Tro893\n");
    // compute length then copy
    int length = strlen(first_name);
    strcpy(copied_name, first_name);
    
    printf("String Length: %d\n", length);
    printf("Copied string: %s\n", copied_name);
    return 0;
}
