#include <stdio.h>
#include <stdlib.h>
#include "employee.h"

int main() {
    int arraySize;
    Employee *data = readData("a6-input.txt", &arraySize);

    if (data == NULL) {
        printf("Error reading file.\n");
        return 1;
    }

    Employee bestEmployee = getBestEmployee(data, arraySize);
    writeData("a6-output.txt", bestEmployee);

    free(data);
    return 0;
}

