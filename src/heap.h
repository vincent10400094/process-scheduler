#ifndef _HEAP_H
#define _HEAP_H

#include "process.h"

#define MAX_N 32

struct Heap {
    int size;
    struct PCB *arr[MAX_N];
};

void init_heap(struct Heap *h);

void push(struct Heap *h, struct PCB *p);
struct PCB *top(struct Heap *h);
struct PCB *pop(struct Heap *h);

void heapify_bottom_top(struct Heap *h, int index);
void heapify_top_bottom(struct Heap *h, int parent);

#endif