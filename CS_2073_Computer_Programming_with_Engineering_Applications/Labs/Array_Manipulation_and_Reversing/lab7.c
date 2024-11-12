#include <stdio.h>

// Function to reverse array elements leaving null elements at end
// First we move all non-null elements to the beginning,
// then we reverse those specific elements
void reverseArray(int arr[], int length) {
    int non_zero_count = 0; // Count of non-zero elements

    // Move all non-zero elements to the beginning of the array
    for (int i = 0; i < length; i++) {
        if (arr[i] != 0) {
            arr[non_zero_count] = arr[i];
            non_zero_count++;
        }
    }

    // Fill the rest with zeroes
    for (int i = non_zero_count; i < length; i++) {
        arr[i] = 0;
    }

    int start = 0;
    int end = non_zero_count - 1;  // This ensures only non-zeros are swapped
    int temp;

    while (start < end) {
        temp = arr[start]; // Hold start of array in temp
        arr[start] = arr[end]; // Put end at start
        arr[end] = temp; // Put temp (start) at end
        // increment and decrement
        start++;
        end--;
    }
}

// Test driver
int main() {
    // Test with an even number of elements
    int arr1[] = {1, 0, 3, 4, 0, 6};
    int len1 = 6;
    printf("Array with even number of elements: ");
    for (int i = 0; i < len1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    reverseArray(arr1, len1);
    printf("Reversed array with even number of elements: ");
    for (int i = 0; i < len1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    // Test with an odd number of elements
    int arr2[] = {1, 2, 0, 4, 5, 0, 7};
    int len2 = 7;
    printf("Array with odd number of elements: ");
    for (int i = 0; i < len2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    reverseArray(arr2, len2);
    printf("Reversed array with odd number of elements: ");
    for (int i = 0; i < len2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    return 0;
}
