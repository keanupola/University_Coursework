// C8.c
#include <stdio.h>
#include <string.h>

int main() {
    char last_name1[] = "Anderson-Pola";
    char last_name2[] = "Reeves";
	// print header
	printf("DS Assignment-1, Summer 2023,\n Keanu Anderson-Pola, Tro893\n");
    printf("First String: %s\n", last_name1);
	printf("Second String: %s\n", last_name2);
    if (strcmp(last_name1, last_name2) == 0) {
        printf("The strings match.\n");
    } else {
        printf("The strings do not match.\n");
    }
    
    return 0;
}
