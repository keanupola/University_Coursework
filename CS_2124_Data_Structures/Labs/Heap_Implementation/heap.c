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

	toReturn->array = malloc(START_CAP * sizeof(int));
	if(toReturn->array == NULL){
		perror("error allocating heap");
		exit(1);
	}

	toReturn->num = 0;
	toReturn->cap = START_CAP;

	return toReturn;

}

void insert(Heap *h, int toInsert){
	//need to make bigger
	if(h->num == h->cap){
		h->cap *= 1.5;
		h->array = realloc(h->array, h->cap * sizeof(int));
		if(h->array == NULL){
			perror("error reallocating heap");
			exit(1);
		}
	}



	int swimIdx = h->num;//we will "swim" this node up 
	h->num++;


	h->array[swimIdx] = toInsert;

	while(swimIdx > 0 && h->array[(swimIdx-1)/2] < h->array[swimIdx]){
		int tmp = h->array[(swimIdx-1)/2];
		h->array[(swimIdx-1)/2] = h->array[swimIdx];
		h->array[swimIdx] = tmp;
		swimIdx = (swimIdx-1)/2;
	}



	if(DEBUG){
		int i;
		printf("after inserting %d\n",toInsert);
		printf("num:%d cap:%d\n", h->num, h->cap);
		for(i = 0; i < h->num; i++){
			printf("%4d",h->array[i]);
		}
		printf("\n");
	}


}


int extract_max(Heap *h){
	if(h->num == 0){
		fprintf(stderr,"tried extracting an empty heap\n");
		exit(1);
	}

	h->num--;
	int toReturn = h->array[0];//return the root


	if(h->num <= h->cap/4 && h->cap > START_CAP){//make smaller
		h->cap = h->cap/2 > START_CAP ? h->cap/2 : START_CAP;
		h->array = realloc(h->array, h->cap * sizeof(int));
		if(h->array == NULL){
			perror("error reallocating stack");
			exit(1);
		}
	}


	int sinkIdx = 0;
	h->array[0] = h->array[h->num];//take last int, put at root, sink it down



	int extract_max(Heap *h){
	if(h->num == 0){
		fprintf(stderr,"tried extracting an empty heap\n");
		exit(1);
	}

	int toReturn = h->array[0];//return the root
	h->array[0] = h->array[--h->num];//take last int, put at root, sink it down

	// sink down operation
	int sinkIdx = 0;
	while (2*sinkIdx + 1 < h->num) {
		int child = 2*sinkIdx + 1; // left child
		// check if right child exists and is larger
		if(child + 1 < h->num && h->array[child] < h->array[child+1]) {
			child++; // right child
		}
		// stop if parent is larger than the largest child
		if(h->array[sinkIdx] >= h->array[child]) break;

		// swap parent and the largest child
		int temp = h->array[sinkIdx];
		h->array[sinkIdx] = h->array[child];
		h->array[child] = temp;

		// move to the next level
		sinkIdx = child;
	}

	// reduce the size if necessary
	if(h->num <= h->cap/4 && h->cap > START_CAP){//make smaller
		h->cap = h->cap/2 > START_CAP ? h->cap/2 : START_CAP;
		h->array = realloc(h->array, h->cap * sizeof(int));
		if(h->array == NULL){
			perror("error reallocating stack");
			exit(1);
		}
	}

	if(DEBUG){
		int i;
		printf("after extracting %d\n",toReturn);
		printf("num:%d cap:%d\n", h->num, h->cap);
		for(i = 0; i < h->num; i++){
			printf("%4d",h->array[i]);
		}
		printf("\n");
	}

	return toReturn;
}







	if(DEBUG){
		int i;
		printf("after extracting %d\n",toReturn);
		printf("num:%d cap:%d\n", h->num, h->cap);
		for(i = 0; i < h->num; i++){
			printf("%4d",h->array[i]);
		}
		printf("\n");
	}




	return toReturn;


}


int is_empty(Heap *h){
	return h->num == 0;
}



