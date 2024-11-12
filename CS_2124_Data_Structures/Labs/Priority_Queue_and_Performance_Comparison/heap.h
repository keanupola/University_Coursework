#ifndef HEAP_H
#define HEAP_H


#define START_CAP 8
#define DEBUG 0


typedef struct heapEntry{
	int data;//whatever data we want to store in the heap
	int priority;//priority this entry has
}HeapEntry;


typedef struct heap{

	HeapEntry *array;//array storing the heap
	int num;//number of items in heap
	int cap;//capacity of heap

}Heap;

Heap * init_heap();

void insert_heap(Heap *h, int data, int priority);//inserts toInsert into the heap

//extracts the root node from the heap 
int extract_max_heap(Heap *h);


int is_empty_heap(Heap *h);







#endif
