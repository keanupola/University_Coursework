#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// function declaration
int binarySearchIterative(int array[], int x, int low, int high);

int main() {
    printf("<Summer 2023>\n");
    printf("Keanu Anderson-Pola, tro893\n");
    
    int i;
    int n = 5;
    int array[5], key;
    
    printf("Binary Search (iterative approach)\n");
    printf("Enter 5 elements:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    printf("Enter key element to search:\n");
    scanf("%d", &key);

    clock_t start_time = clock(); // time start
    int result = binarySearchIterative(array, key, 0, n - 1);
    clock_t end_time = clock(); // time end

    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }
    // calc time taken
    double time_taken = ((double)end_time - start_time) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU (End Time - Start Time) /clock per_sec: %f\n", time_taken);

    return 0;
}

// implement iterative BS
int binarySearchIterative(int array[], int x, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (array[mid] == x) { // found
            return mid;
        }
        if (array[mid] < x) { // right half
            low = mid + 1;
        }
        else { // left half
            high = mid - 1;
        }
    }
    return -1;
}
