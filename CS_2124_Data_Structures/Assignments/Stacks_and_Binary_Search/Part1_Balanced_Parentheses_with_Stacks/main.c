#include <stdio.h>
#include "assignment2pt1.h"

int main() {
    printf("<Summer 2023>\n");
    printf("Keanu Anderson-Pola, tro893\n");
    
    int i;
    for (i = 0; i < 2; i++) {
        char exp[MAX_SIZE + 1]; // store expression
        printf("Enter a string of 6 parenthesis (Program Run %d of 2):\n", i+1);
        scanf("%6s", exp); // Get expression
        int result = isBalanced(exp);
        if (result == 1) {
            printf("Valid Parenthesis Expression\n");
        }
        else if (result == 0) {
            printf("Invalid Parenthesis Expression\n");
        }
        else {
            printf("Invalid input.\n");
        }
    }
    printf("<Exit Program>\n");
    return 0;
}
