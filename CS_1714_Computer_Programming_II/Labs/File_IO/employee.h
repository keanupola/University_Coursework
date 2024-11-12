#ifndef EMPLOYEE_H
#define EMPLOYEE_H

typedef struct {
    char name[11];
    int id;
    double salary;
} Employee;

Employee* readData(const char *filename, int *arraySize);
Employee getBestEmployee(Employee *data, int arraySize);
void writeData(const char *filename, Employee bestEmployee);

#endif

