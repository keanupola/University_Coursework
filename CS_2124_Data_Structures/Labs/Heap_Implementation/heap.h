#ifndef HEAP_H
#define HEAP_H


#define START_CAP 8
#define DEBUG 1

typedef struct heap{

	int *array;//array storing the heap
	int num;//number of items in heap
	int cap;//capacity of heap

}Heap;

Heap * init_heap();

void insert(Heap *h, int toInsert);//inserts toInsert into the heap

//extracts the root node from the heap 
int extract_max(Heap *h);


int is_empty(Heap *h);







#endif
