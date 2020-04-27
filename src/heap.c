#include "heap.h"

void init_heap(struct Heap *h) {
    h->size = 0;
}

void push(struct Heap *h, struct PCB *p) {
    h->arr[h->size] = p;
    heapify_bottom_top(h, h->size);
    h->size += 1;
}

struct PCB *top(struct Heap *h) {
    return h->arr[0];
}

struct PCB *pop(struct Heap *h) {
    struct PCB *top = h->arr[0];
    h->arr[0] = h->arr[h->size-1];
    h->size -= 1;
    heapify_top_bottom(h, 0);
    return top;
}

void heapify_bottom_top(struct Heap *h, int index) {
    int parent = (index-1)/2;
    if (h->arr[parent]->t > h->arr[index]->t) {
        struct PCB *tmp = h->arr[parent];
        h->arr[parent] = h->arr[index];
        h->arr[index] = tmp;
        heapify_bottom_top(h, parent);
    }
}

void heapify_top_bottom(struct Heap *h, int parent) {
    int l = parent * 2 + 1, r = parent * 2 + 2, min;

    if (l >= h->size)
        l = -1;
    if (r >= h->size)
        r = -1;
    
    if (l != -1 && h->arr[l]->t < h->arr[parent]->t)
        min = l;
    else
        min = parent;
    if (r != -1 && h->arr[r]->t < h->arr[min]->t)
        min = r;

    if (min != parent) {
        struct PCB *tmp = h->arr[parent];
        h->arr[parent] = h->arr[min];
        h->arr[min] = tmp;
        heapify_top_bottom(h, min);
    }
}