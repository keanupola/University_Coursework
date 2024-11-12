#include <stdio.h>

int count_character(char *string, char cc);

int main() {
    char input[100];
    char cc;  // Character to be counted
    int count;

    // Get string input 
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    // Get character input
    printf("What character would you like to search for? ");
    scanf("%c", &cc);

    // Count character occurrences
    count = count_character(input, cc);
    printf("The character '%c' occurs %d times in the string.\\n", cc, count);

    return 0;
}

// Function to count occurrences of a character in a string
int count_character(char *string, char cc) {
    int count = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == cc) {
            count++;
        }
    }
    return count;
}
