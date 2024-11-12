#include <stdlib.h>
#include <stdio.h>
#include "queue.h"




Queue *init(){

	Queue *toReturn = malloc(sizeof(Queue));
	if(toReturn == NULL){
		perror("error allocating queue");
		exit(1);
	}

	toReturn->head = NULL;
	toReturn->tail = NULL;



	return toReturn;
}


void destroy(Queue *q){
	while(!isEmpty(q)){
		dequeue(q);
	}
	free(q);
}


void enqueue(Queue *q, int data){

	// Allocate space for the new node struct using malloc
	Node *newNode = (Node *)malloc(sizeof(Node));
	
	// Check to see if malloc failed
	if(newNode == NULL){
		fprintf(stderr, "Failed to allocate memory for new node!\n");
		exit(0);
	}

	// Initialize member of new node struct
	newNode->data = data;
	newNode->next = NULL;

	// If q is empty
	if(isEmpty(q)){
		// Set head and tail to point to new struct
		q->head = newNode;
		q->tail = newNode;
	}else{
		// Set tail's next to point to new node, and then
		q->tail->next = newNode;

		// Set tail to point to new node
		q->tail = newNode;
	}
}


int dequeue(Queue *q){
	if(isEmpty(q)){
		fprintf(stderr,"tried dequeueing an empty queue!\n");
		exit(0);
	}


	Node *toFree = q->head;
	int toReturn = q->head->data;

	if(q->head == q->tail){
		//only one node in queue
		q->head = NULL;
		q->tail = NULL;
	}else{
		q->head = q->head->next;
	}



	free(toFree);
	return toReturn;

}


int peek(Queue *q){
	if(isEmpty(q)){
		fprintf(stderr,"tried peeking an empty queue!\n");
		exit(0);
	}

	return q->head->data;

}

int isEmpty(Queue *q){
	return q->head == NULL;
}





