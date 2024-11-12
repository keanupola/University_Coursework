#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


Heap * init_heap(){
	Heap *toReturn;

	toReturn = malloc(sizeof(Heap));
	if(toReturn == NULL){
		perror("error allocating heap");
		exit(1);
	}

	toReturn->array = malloc(START_CAP * sizeof(HeapEntry));
	if(toReturn->array == NULL){
		perror("error allocating heap");
		exit(1);
	}

	toReturn->num = 0;
	toReturn->cap = START_CAP;

	return toReturn;

}

void insert_heap(Heap *h, int data, int priority){
	if(h->num == h->cap){
		//need to make bigger
		h->cap *= 1.5;
		h->array = realloc(h->array, h->cap * sizeof(HeapEntry));
		if(h->array == NULL){
			perror("error reallocating heap");
			exit(1);
		}
	}



	int swimIdx = h->num;//we will "swim" this node up 
	h->num++;


	h->array[swimIdx].data = data;
	h->array[swimIdx].priority = priority;


	while(swimIdx > 0 && h->array[(swimIdx-1)/2].priority < h->array[swimIdx].priority){
		HeapEntry tmp = h->array[(swimIdx-1)/2];
		h->array[(swimIdx-1)/2] = h->array[swimIdx];
		h->array[swimIdx] = tmp;
		swimIdx = (swimIdx-1)/2;
	}



	if(DEBUG){
		int i;
		printf("after inserting data:%d priority:%d\n",data, priority);
		printf("num:%d cap:%d\n", h->num, h->cap);
		for(i = 0; i < h->num; i++){
			printf("%4d",h->array[i].priority);
		}
		printf("\n");
	}


}


int extract_max_heap(Heap *h){
	if(h->num == 0){
		fprintf(stderr,"tried extracting an empty heap\n");
		exit(1);
	}

	h->num--;
	int toReturn = h->array[0].data;//return the root data
	int toDebug = h->array[0].priority;//remember priority for debugging


	if(h->num <= h->cap/4 && h->cap > START_CAP){//make smaller
		h->cap = h->cap/2 > START_CAP ? h->cap/2 : START_CAP;
		h->array = realloc(h->array, h->cap * sizeof(HeapEntry));
		if(h->array == NULL){
			perror("error reallocating heap");
			exit(1);
		}
	}


	int sinkIdx = 0;
	h->array[0] = h->array[h->num];//take last HeapEntry, put at root, sink it down

	while(2*sinkIdx + 1 < h->num){//loop while we still have at least one child

		int cmpIdx;//index we will compare sinkIdx to
		if(2*sinkIdx + 2 < h->num){
			//have two children, find the larger one
			cmpIdx = h->array[2*sinkIdx+1].priority > h->array[2*sinkIdx+2].priority ? 2*sinkIdx+1:2*sinkIdx+2;

		}else{
			//have one child
			cmpIdx = 2*sinkIdx+1;
		}

		if(h->array[sinkIdx].priority < h->array[cmpIdx].priority){
			HeapEntry tmp = h->array[sinkIdx];
			h->array[sinkIdx] = h->array[cmpIdx];
			h->array[cmpIdx] = tmp;
			sinkIdx = cmpIdx;
		}else{
			break;
		}

	}


	if(DEBUG){
		int i;
		printf("after extracting data:%d with priority:%d\n",toReturn,toDebug);
		printf("num:%d cap:%d\n", h->num, h->cap);
		for(i = 0; i < h->num; i++){
			printf("%4d",h->array[i].priority);
		}
		printf("\n");
	}




	return toReturn;


}


int is_empty_heap(Heap *h){
	return h->num == 0;
}



