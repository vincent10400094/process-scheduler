#include "fifo.h"

void fifo(struct PCB *ps, int N) {
    int current = 0, ready = 0;
    for (int time = 0; ; time++) {

        /* if time >= process's ready time, set the process's ready state to true */
        for (; ready < N && time >= ps[ready].r; ready++) {
            forkChild(&ps[ready]);
            ps[ready].ready = true;
            ps[ready].running = false;
        }

        /* set the running job with highest priority */
        if (ps[current].ready && !ps[current].running) {
            setPriority(ps[current].pid, 99);
            ps[current].running = true;
        }

        UNIT_OF_TIME

        if (ps[current].running && ps[current].t > 0) {
            ps[current].t -= 1;
        }

        /* a job is finished */
        if (ps[current].running && ps[current].t == 0) {
            
            wait(NULL);

            /* all jobs are finished */
            if (current == N-1) {
                return;
            }

            /* do next job */
            current += 1;
        }

    }
}