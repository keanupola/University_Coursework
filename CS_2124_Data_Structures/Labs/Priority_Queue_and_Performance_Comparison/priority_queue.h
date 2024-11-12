#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H



typedef struct node{
	int data;
	int priority;
	struct node *next;
}Node;


typedef struct queue{
	Node *head;//dequeue and enqueue from the head
	Node *tail;
}Queue;


Queue *init_queue();
void destroy(Queue *q);

void enqueue(Queue *q, int data, int priority);
int dequeue(Queue *q);
int peek(Queue *q);
int is_empty_queue(Queue *q);








#endif
