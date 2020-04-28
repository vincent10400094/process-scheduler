#include "rr.h"

struct Queue *new_node(struct PCB *p) {
    struct Queue *new = malloc(sizeof(struct Queue));
    new->p = p;
    new->next = NULL;
    return new;
}

void rr(struct PCB *ps, int N) {
    struct Queue *head = NULL, *tail = NULL;
    int finish = 0, ready = 0, quantum = 500;
    for (int time = 0; ; time++) {

        /* if time >= process's ready time, set the process's ready state to true */
        for (; ready < N && time >= ps[ready].r; ready++) {
            forkChild(&ps[ready]);
            ps[ready].ready = true;
            ps[ready].running = false;

            // fprintf(stderr, "%s ready\n", ps[ready].name);

            if (head == NULL) {
                head = tail = new_node(&ps[ready]);
            } else {
                tail->next = new_node(&ps[ready]);
                tail = tail->next;
            }
        }

        /* quantum expired, switch to next job */
        if (head && head->p->running && quantum == 0) {
            setPriority(head->p->pid, 1);
            head->p->running = false;
            quantum = 500;              // reset time quantum
            if (head->next) {           // move the current node to the end of the queue
                struct Queue *tmp = head;
                head = head->next;
                tail->next = tmp;
                tail = tail->next;
                tail->next = NULL;
            }
        }

        if (head && !head->p->running) {
            if (!head->p->isstart) {
                syscall(333, &head->p->start);
                head->p->isstart = true;
            }
            setPriority(head->p->pid, 99);
            head->p->running = true;
            quantum = 500;
            // fprintf(stderr, "switch to %s\n", head->p->name);
        }

        UNIT_OF_TIME

        /* there is a job running */
        if (head && head->p->running) {
            quantum -= 1;
            head->p->t -= 1;
        }

        /* a job is finished */
        if (head && head->p->t == 0) {

            syscall(333, &head->p->end);
            syscall(334, head->p->pid, head->p->start.tv_sec, head->p->start.tv_nsec, head->p->end.tv_sec, head->p->end.tv_nsec);
            printf("%s %d\n", head->p->name, head->p->pid);
            fflush(stdout);
            wait(NULL);

            // fprintf(stderr, "%s finish\n", head->p->name);
            struct Queue *tmp = head;
            if (head->next)
                head = head->next;
            else
                head = tail = NULL;
            free(tmp);

            finish += 1;

            if (finish == N)
                return;
        }
    }
}