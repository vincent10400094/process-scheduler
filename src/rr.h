#ifndef _RR_H
#define _RR_H

#include "process.h"

struct Queue {
    struct PCB *p;
    struct Queue *next;
};

void rr(struct PCB *ps, int N);

#endif