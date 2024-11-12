#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "heap.h"
#include "priority_queue.h"

#define SIZE 3
int nodeCounts[SIZE] = {1000, 10000, 100000};

double time_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
}

void test_enqueue(Queue *q, Heap *h, int nodes) {
    struct timespec start, end;
    int i;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(i = 0; i < nodes; i++){
        enqueue(q, i, rand() % 100);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    printf("Priority queue enqueue of %d nodes took %.2f seconds\n", nodes, time_diff(start, end));

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(i = 0; i < nodes; i++){
        insert_heap(h, i, rand() % 100);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    printf("Heap enqueue of %d nodes took %.2f seconds\n", nodes, time_diff(start, end));
}

int main(int argc, char *argv[]){
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        Queue *q = init_queue();
        Heap *h = init_heap();
        test_enqueue(q, h, nodeCounts[i]);
        destroy(q);
        free(h->array);
        free(h);
    }

    return 0;
}
