#include <stdio.h>

#define ARRAY_SIZE 10

// Struct with one int, one float, and one array
typedef struct {
    int myInt;
    float myFloat;
    int myArray[ARRAY_SIZE];
} TestStruct;

// A function that receives one of the struct elements and modifies the 
// values stored in that element

void editStruct(TestStruct *structPointer) {
    // Using the -> operator to access and modify the attributes of the struct
    structPointer->myInt *= 2;
    structPointer->myFloat *= 3;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        structPointer->myArray[i] *= 4;
    }
}

// Function to print struct element values
void printStructElement(TestStruct structInstance) {
    printf("Int: %d\nFloat: %.2f\nArray: ", structInstance.myInt, structInstance.myFloat);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", structInstance.myArray[i]);
    }
    printf("\n\n");
}

int main() {
    // Create array of struct with 10 elements
    TestStruct structArray[10];

    // loop to populate the array with data
    for (int i = 0; i < 10; i++) {
        structArray[i].myInt = i;
        structArray[i].myFloat = i * 1.5;
        for (int j = 0; j < ARRAY_SIZE; j++) {
            structArray[i].myArray[j] = (j + 2);
        }
    }

    // Print values stored in the struct element prior to modification 
    // and after
    
    printf("Values prior to modification:\n");
    printStructElement(structArray[4]);

    // Modification of element function call
    editStruct(&structArray[4]);

    printf("Values after modification:\n");
    printStructElement(structArray[4]);

    return 0;
}
