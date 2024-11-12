// C9.c
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char last_name[] = "Anderson-Pola";
    int len = strlen(last_name);
	// print header
	printf("DS Assignment-1, Summer 2023,\n Keanu Anderson-Pola, Tro893\n");
    int i;
    for(i = 0; i < len; i++) {
        last_name[i] = tolower(last_name[i]);
    }
    
    printf("Lowercase string: %s\n", last_name);
    return 0;
}
