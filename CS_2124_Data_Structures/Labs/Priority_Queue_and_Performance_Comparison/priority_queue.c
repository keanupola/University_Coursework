#include <stdlib.h>
#include <stdio.h>
#include "priority_queue.h"




Queue *init_queue(){

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
	while(!is_empty_queue(q)){
		dequeue(q);
	}
	free(q);
}


void enqueue(Queue *q, int data, int priority){

	Node *toInsert = malloc(sizeof(Node));
	if(toInsert == NULL){
		perror("error allocating node");
		exit(1);
	}

	toInsert->data = data;
	toInsert->priority = priority;
	toInsert->next = NULL;


	if(is_empty_queue(q)){
		//queue empty!
		q->head = toInsert;
		q->tail = toInsert;
	}else{
		Node *cur = q->head;
		Node *prev = NULL;
		while(cur !=  NULL){
			if(cur->priority <= toInsert->priority){
				break;
			}
			prev = cur;
			cur = cur->next;
		}
		if(prev == NULL){
			//toInsert is going at the head of the list
			toInsert->next = q->head;
			q->head = toInsert;
		}else{
			if(cur == NULL){
				//toInsert is going at the end of the list
				q->tail = toInsert;
			}
			toInsert->next = cur;
			prev->next = toInsert;
		}
	}

}

int dequeue(Queue *q){
	if(is_empty_queue(q)){
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
	if(is_empty_queue(q)){
		fprintf(stderr,"tried peeking an empty queue!\n");
		exit(0);
	}

	return q->head->data;

}

int is_empty_queue(Queue *q){
	return q->head == NULL;
}





