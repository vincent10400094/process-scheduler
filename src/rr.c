#include "rr.h"

struct Queue *new_node(struct PCB *p) {
    struct Queue *new = malloc(sizeof(struct Queue));
    new->p = p;
    new->next = NULL;
    return new;
}

void rr(struct PCB *ps, int N) {
    struct Queue *head = NULL, *tail = NULL;
    int ready = 0, quantum = 500;
    for (int time = 0; ; time++) {

        /* a job is finished */
        if (head && head->p->t == 0) {

            wait(NULL);

            struct Queue *tmp = head;
            if (head->next)
                head = head->next;
            else
                head = tail = NULL;

            free(tmp);
            if (ready == N && !head)
                return;
        }

        /* if time >= process's ready time, set the process's ready state to true */
        for (; ready < N && time >= ps[ready].r; ready++) {
            forkChild(&ps[ready]);
            ps[ready].ready = true;
            ps[ready].running = false;

            fprintf(stderr, "%s ready\n", ps[ready].name);

            if (head == NULL) {
                head = tail = new_node(&ps[ready]);
            } else {
                tail->next = new_node(&ps[ready]);
                tail = tail->next;
            }
        }

        /* quantum expired, switch to next job */
        if (head && quantum == 0) {
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
            fprintf(stderr, "switch to %s\n", head->p->name);
        }

        if (head && !head->p->running) {
            setPriority(head->p->pid, 99);
            head->p->running = true;
        }

        UNIT_OF_TIME

        /* there is a job running */
        if (head) {
            quantum -= 1;
            head->p->t -= 1;
        }
    }
}