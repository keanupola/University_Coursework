#include <stdio.h>
#include "heap.h"



int main(){
	Heap *myHeap = init_heap();

	//extract_max commented out in case
	//you want to run the code before implementing extract_max

	insert(myHeap, 4);
	insert(myHeap, 2);
	insert(myHeap, 3);
	insert(myHeap, 9);
	insert(myHeap, 8);
	if(!is_empty(myHeap)){
		//extract_max(myHeap);
	}
	insert(myHeap, 14);
	insert(myHeap, 42);
	insert(myHeap, 45);
	insert(myHeap, 24);
	if(!is_empty(myHeap)){
		//extract_max(myHeap);
	}
	if(!is_empty(myHeap)){
		//extract_max(myHeap);
	}
	insert(myHeap, 32);
	insert(myHeap, 17);
	if(!is_empty(myHeap)){
		//extract_max(myHeap);
	}
	insert(myHeap, 12);
	insert(myHeap, 1);
	if(!is_empty(myHeap)){
		//extract_max(myHeap);
	}
	insert(myHeap, 7);
	insert(myHeap, 4);
	/*while(!is_empty(myHeap)){
		extract_max(myHeap);
	}*/
	
}
