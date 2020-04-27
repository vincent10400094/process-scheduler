#include "scheduler.h"

int getPolicy() {
    char policy[5];
    scanf("%s", policy);
    if (strcmp(policy, "FIFO") == 0)
        return FIFO;
    if (strcmp(policy, "RR") == 0)
        return RR;
    if (strcmp(policy, "SJF") == 0)
        return SJF;
    if (strcmp(policy, "PSJF") == 0)
        return PSJF;
    fprintf(stderr, "Error: unknown policy\n");
    exit(1);
}

int main() {

    int S = getPolicy();

    int N;
    scanf("%d", &N);

    struct PCB ps[N];

    for (int i = 0; i < N; i++) {
        scanf("%s %d %d", ps[i].name, &ps[i].r, &ps[i].t);
        ps[i].i = i;
        ps[i].ready = ps[i].running = false;
    }

    /* sort processes by ready time */
    qsort(ps, N, sizeof(struct PCB), cmp);

    /* assign scheduler to cpu 0 */
    setCPU(getpid(), 0);
    setPriority(getpid(), 99);

    /* assign scheduler */
    if (S == FIFO) {
        fifo(ps, N);
    } else if (S == RR) {
        rr(ps, N);
    } else if (S == SJF) {

    } else if (S == PSJF) {

    }

    qsort(ps, N, sizeof(struct PCB), cmp_i);
    for (int i = 0; i < N; i++)
        printf("%s %d\n", ps[i].name, ps[i].pid);
    fflush(stdout);

    return 0;
}