#include <stdio.h>
#include <stdlib.h>
#include "employee.h"

Employee* readData(const char *filename, int *arraySize) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    *arraySize = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            (*arraySize)++;
        }
    }
    // Account for the last line (if it doesn't end with a newline character)
    if (ch != '\n') {
        (*arraySize)++;
    }

    Employee *data = (Employee *) malloc((*arraySize) * sizeof(Employee));

    rewind(file);
    int i;
    for (i = 0; i < *arraySize; i++) {
        fscanf(file, "%10s %d %lf", data[i].name, &data[i].id, &data[i].salary);
    }

    fclose(file);
    return data;
}

Employee getBestEmployee(Employee *data, int arraySize) {
    Employee bestEmployee = data[0];
    int i;
    for (i = 1; i < arraySize; i++) {
        if (data[i].salary > bestEmployee.salary) {
            bestEmployee = data[i];
        }
    }
    return bestEmployee;
}

void writeData(const char *filename, Employee bestEmployee) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        return;
    }

    fprintf(file, "%s %d %.0lf", bestEmployee.name, bestEmployee.id, bestEmployee.salary);
    fclose(file);
}
