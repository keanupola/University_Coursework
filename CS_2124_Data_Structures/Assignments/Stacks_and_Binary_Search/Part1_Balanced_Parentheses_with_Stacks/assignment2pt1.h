#ifndef ASSIGNMENT2PT1_H
#define ASSIGNMENT2PT1_H

#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 6 // EXPRESSION MAX

// Stack struct
typedef struct Stack {
    int top;
    char arr[MAX_SIZE];
} Stack;

// Function declarations
Stack* createStack();
int isFull(Stack* s);
int isEmpty(Stack* s);
void push(Stack* s, char item);
char pop(Stack* s);
char peek(Stack* s);
int isBalanced(char exp[]);

#endif
