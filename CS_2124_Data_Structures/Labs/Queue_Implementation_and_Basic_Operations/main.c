#include <stdio.h>
#include "queue.h"



int main(int argc, char *argv[]){

	Queue *q = init();


	enqueue(q, 5);
	printf("enqueued: 5\n");
	enqueue(q,8);
	printf("enqueued: 8\n");
	enqueue(q,11);
	printf("enqueued: 11\n");
	printf("dequeued: %d\n", dequeue(q));
	printf("dequeued: %d\n", dequeue(q));
	enqueue(q,13);
	printf("enqueued: 13\n");
	printf("dequeued: %d\n", dequeue(q));

	enqueue(q,4);
	printf("enqueued: 4\n");
	enqueue(q,2);
	printf("enqueued: 2\n");
	enqueue(q,5);
	printf("enqueued: 5\n");
	enqueue(q,1);
	printf("enqueued: 1\n");
	enqueue(q,9);
	printf("enqueued: 9\n");

	while(!isEmpty(q)){
		printf("dequeued: %d\n", dequeue(q));
	}

	destroy(q);


}
