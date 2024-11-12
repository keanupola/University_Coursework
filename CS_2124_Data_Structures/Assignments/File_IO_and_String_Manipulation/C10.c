// C10.c
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
        last_name[i] = toupper(last_name[i]);
    }
    
    printf("Uppercase string: %s\n", last_name);
    return 0;
}
