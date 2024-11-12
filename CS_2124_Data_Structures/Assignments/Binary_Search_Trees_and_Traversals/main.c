#include <stdio.h>
#include "tree.h"

int main() {
    Node* root = NULL;
    int values[10];  // Array to hold user input
    int input_status;
    int i;

    printf("Enter Numbers (Max Ten numbers):\n");
    for (i = 0; i < 10; i++) {
        printf("%d: ", i);
        input_status = scanf("%d", &values[i]);

        // Check if the input is valid.
        if (input_status != 1) {
            printf("Invalid input. Please enter a number.\n");
            return -1;
        }

        root = insert(root, values[i]);
    }

    printf("User input: ");
    for (i = 0; i < 10; i++)
        printf("%d ", values[i]);
    printf("\n");

    printf("In order: ");
    printInOrder(root);
    printf("\n");

    printf("Pre order: ");
    printPreOrder(root);
    printf("\n");

    printf("Post order: ");
    printPostOrder(root);
    printf("\n");

    return 0;
}

