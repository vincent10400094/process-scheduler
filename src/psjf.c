#include "psjf.h"

void psjf(struct PCB *ps, int N) {
    int finish = 0, ready = 0;
    struct PCB *now = NULL;
    struct Heap h;
    init_heap(&h);
    for (int time = 0; ; time++) {

        /* if time >= process's ready time, set the process's ready state to true */
        for (; ready < N && time >= ps[ready].r; ready++) {
            forkChild(&ps[ready]);
            ps[ready].ready = true;
            ps[ready].running = false;
            push(&h, &ps[ready]);
        }

        /* if there is a job running, check whether switch to shorter job */
        if (now) {
            struct PCB *p = top(&h);
            if (p->t < now->t) {
                setPriority(now->pid, 1);
                push(&h, now);
                now = NULL;
            }
        }

        /* run the shortest job */
        if (!now && h.size > 0) {
            now = pop(&h);
            // fprintf(stderr, "start running %s\n", now->name);
            if (!now->isstart) {
                syscall(333, &now->start);
                now->isstart = true;
            }
            setPriority(now->pid, 99);
            now->running = true;
        }

        UNIT_OF_TIME

        if (now && now->t > 0) {
            now->t -= 1;
        }

        /* a job is finished */
        if (now && now->t == 0) {
            
            syscall(333, &now->end);
            syscall(334, now->pid, now->start.tv_sec, now->start.tv_nsec, now->end.tv_sec, now->end.tv_nsec);
            printf("%s %d\n", now->name, now->pid);
            fflush(stdout);

            wait(NULL);
            // fprintf(stderr, "%s finish\n", now->name);
            finish += 1;

            /* all jobs are finished */
            if (finish == N) {
                return;
            }
            now = NULL;
        }

    }
}