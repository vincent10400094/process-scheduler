#ifndef _PROCESS_H
#define _PROCESS_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <sys/syscall.h>
#include <sys/wait.h>

struct PCB {
    char name[32];
    int r;              // ready time
    int t;              // execute time
    int i;              // i-th process
    pid_t pid;
};

int cmp(const void *a, const void *b);

void setCPU(pid_t pid, int i);
void setPriority(pid_t pid, int p);
void forkChild(struct PCB *p);

#endif