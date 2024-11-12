#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment2pt1.h"


// init stack
Stack* createStack() {
    Stack* s = malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

// check stack full
int isFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

// check stack empty
int isEmpty(Stack* s) {
    return s->top == -1;
}

// push to stack
void push(Stack* s, char item) {
    if (isFull(s)) {
        return;
    }
    s->arr[++s->top] = item;
}

// pop stack
char pop(Stack* s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->arr[s->top--];
}

// peek stack
char peek(Stack* s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->arr[s->top];
}

// check if expression is balanced
int isBalanced(char exp[]) {
    int i;
    // init stack
    Stack* s = createStack();
    for (i = 0; i < strlen(exp); i++) {
        if (exp[i] == '{') {
            push(s, exp[i]);
        }
        else if (exp[i] == '}') {
            if (isEmpty(s)) {
                return 0;
            }
            pop(s);
        }
        else {
            return -1; // Invalid
        }
    }
    int balanced = isEmpty(s);
    if (!isEmpty(s)) {
        printf("Stack full, last value entered (stack top): %c\n", peek(s));
    }
    free(s);
    return balanced;
}
