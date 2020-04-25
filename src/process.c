#include "process.h"

#define UNIT_OF_TIME { volatile unsigned long i; for (i=0;i<1000000UL;i++); }

int cmp(const void *_a, const void *_b) {
    struct PCB *a = (struct PCB *) a;
    struct PCB *b = (struct PCB *) b;
    if (a->r < b->r)
        return -1;
    if (a->r > b->r)
        return 1;
    if (a->i < b->i)
        return -1;
    if (a->i > b->i)
        return 1;
    return 0;
}

void setCPU(pid_t pid, int i) {
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(i, &mask);
    if (sched_setaffinity(pid, sizeof(mask), &mask) == -1) {
        fprintf(stderr, "Error: cannot set cpu");
        exit(1);
    }
}

void setPriority(pid_t pid, int p) {

}

void forkChild(struct PCB *p) {

}