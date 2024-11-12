#include <stdio.h>

int main()
{
    // declare vars
    int i;
    int fib1, fib2, fib3;

    // get fibonacci numbers from user
    printf("Enter first Fibonacci number: ");
    scanf("%d", &fib1);

    printf("Enter second Fibonacci number: ");
    scanf("%d", &fib2);

    // iterate to get next 3 numbers
    for (i=0; i<3; i++) {
        fib3 = fib1 + fib2; // sum = next Fibonacci number
        printf("%d\n", fib3);

        // update values for next loop
        fib1 = fib2;
        fib2 = fib3;
    }

    return 0;
}

