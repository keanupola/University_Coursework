#include <stdlib.h>
#include <stdio.h>
#include "stack.h"








Stack *init(){
	Stack *toReturn;

	toReturn = malloc(sizeof(Stack));

	if(toReturn == NULL){
		perror("error allocating stack");
		exit(1);
	}

	toReturn -> data = malloc(START_CAP * sizeof(char));

	if(toReturn->data == NULL){
		perror("error allocating stack");
		exit(1);
	}


	toReturn -> size = 0;
	toReturn -> cap = START_CAP;

	return toReturn;

}

void destroy(Stack *s){
	free(s->data);
	free(s);
}


int isEmpty(Stack *s){
	if(s->size == 0){
		return 1;
	}
	return 0;
}


void push(Stack *s, char c){
	if(s->size == s->cap){//need to resize
		s->cap *= 1.5;
		s->data = realloc(s->data, s->cap * sizeof(char));
		if(s->data == NULL){
			perror("error reallocating stack");
			exit(1);
		}
	}



	s->data[s->size] = c;
	s->size++;


}

char pop(Stack *s){

	if(s->size == 0){
		fprintf(stderr, "tried popping an empty stack\n");
		exit(1);
	}

	s->size--;
	char toReturn = s->data[s->size];



	if(s->size <= s->cap/4 && s->cap > START_CAP){//make smaller
		s->cap = s->cap/2 > START_CAP ? s->cap/2 : START_CAP;
		s->data = realloc(s->data, s->cap * sizeof(char));
		if(s->data == NULL){
			perror("error reallocating stack");
			exit(1);
		}
	}

	return toReturn;
}




char peek(Stack *s){
	if(s->size == 0){
		fprintf(stderr, "tried peeking an empty stack\n");
		exit(1);
	}

	return s->data[s->size-1];

}

















