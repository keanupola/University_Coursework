#ifndef STACK_H
#define STACK_H



#define START_CAP 20 //starting capacity of stack




typedef struct stack{
	char *data;
	int size;
	int cap;//capacity
}Stack;


Stack *init();
void destroy(Stack *s);



int isEmpty(Stack *s);//should check this before popping
void push(Stack *s, char c);//pushes c onto the stack
char pop(Stack *s);
char peek(Stack *s);//returns the top character on the stack without popping
















#endif
