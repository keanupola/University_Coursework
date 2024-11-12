#include <stdio.h>

int main()
{
    int i;
    int num[9];  // declare array to store 9 ints
    
    printf("Input, separate each int with newline:\n");
    
    // fill array
    for(i = 0; i < 9; i++) {
        scanf("%d", &num[i]);
    }

    for(i = 0; i < 9; i++) {
        printf("%d", num[i]);

        if (i % 3 == 2) { // newline after 3 numbers
            printf("\n");
        } else {
            printf(", "); // print comma and space if %3 is not = 0
        }
    }

    return 0;
}
