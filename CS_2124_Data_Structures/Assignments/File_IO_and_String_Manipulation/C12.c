// C12.c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int* numbers = (int*)calloc(3, sizeof(int));
	// print header
	printf("DS Assignment-1, Summer 2023,\n Keanu Anderson-Pola, Tro893\n");

    if (numbers == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter last 3 digits of your abc separated by newline: ");
    int i;
    for (i = 0; i < 3; i++) {
        scanf("%d", &numbers[i]);
    }

    printf("You entered: ");
    for (i = 0; i < 3; i++) {
        printf("%d ", numbers[i]);
    }

    free(numbers);
    return 0;
}
