#include <stdio.h>
#include <assert.h>
#include "../include/scheduler.h"

void test_fifo() {

    printf("\n=== TEST FIFO ===\n");

    Scheduler* scheduler =
        scheduler_create_fifo();

    Process p1 = {1, 10, 10, 1, 100, READY};
    Process p2 = {2, 20, 20, 1, 100, READY};
    Process p3 = {3, 30, 30, 1, 100, READY};

    scheduler_add_process(scheduler, p1);
    scheduler_add_process(scheduler, p2);
    scheduler_add_process(scheduler, p3);

    Process* p;

    p = scheduler_next(scheduler);
    printf("PID ejecutado: %d\n", p->pid);
    assert(p->pid == 1);

    p = scheduler_next(scheduler);
    printf("PID ejecutado: %d\n", p->pid);
    assert(p->pid == 2);

    p = scheduler_next(scheduler);
    printf("PID ejecutado: %d\n", p->pid);
    assert(p->pid == 3);

    assert(scheduler_next(scheduler) == NULL);

    scheduler_destroy(scheduler);

    printf("FIFO OK\n");
}

void test_sjf() {

    printf("\n=== TEST SJF ===\n");

    Scheduler* scheduler =
        scheduler_create_sjf();

    Process p1 = {1, 30, 30, 1, 100, READY};
    Process p2 = {2, 10, 10, 1, 100, READY};
    Process p3 = {3, 20, 20, 1, 100, READY};

    scheduler_add_process(scheduler, p1);
    scheduler_add_process(scheduler, p2);
    scheduler_add_process(scheduler, p3);

    Process* p;

    p = scheduler_next(scheduler);
    printf("PID ejecutado: %d\n", p->pid);
    assert(p->pid == 2);

    p = scheduler_next(scheduler);
    printf("PID ejecutado: %d\n", p->pid);
    assert(p->pid == 3);

    p = scheduler_next(scheduler);
    printf("PID ejecutado: %d\n", p->pid);
    assert(p->pid == 1);

    assert(scheduler_next(scheduler) == NULL);

    scheduler_destroy(scheduler);

    printf("SJF OK\n");
}

void test_round_robin() {

    printf("\n=== TEST ROUND ROBIN ===\n");

    Scheduler* scheduler =
        scheduler_create_round_robin(2);

    Process p1 = {1, 5, 5, 1, 100, READY};
    Process p2 = {2, 4, 4, 1, 100, READY};

    scheduler_add_process(scheduler, p1);
    scheduler_add_process(scheduler, p2);

    Process* p;

    p = scheduler_next(scheduler);
    printf("PID %d -> remaining=%d\n",
           p->pid,
           p->remaining_time);

    assert(p->pid == 1);
    assert(p->remaining_time == 3);

    p = scheduler_next(scheduler);
    printf("PID %d -> remaining=%d\n",
           p->pid,
           p->remaining_time);

    assert(p->pid == 2);
    assert(p->remaining_time == 2);

    p = scheduler_next(scheduler);
    printf("PID %d -> remaining=%d\n",
           p->pid,
           p->remaining_time);

    assert(p->pid == 1);
    assert(p->remaining_time == 1);

    p = scheduler_next(scheduler);
    printf("PID %d -> remaining=%d\n",
           p->pid,
           p->remaining_time);

    assert(p->pid == 2);
    assert(p->remaining_time == 0);
    assert(p->state == FINISHED);

    p = scheduler_next(scheduler);
    printf("PID %d -> remaining=%d\n",
           p->pid,
           p->remaining_time);

    assert(p->pid == 1);
    assert(p->remaining_time == 0);
    assert(p->state == FINISHED);

    scheduler_destroy(scheduler);

    printf("ROUND ROBIN OK\n");
}

int main() {

    test_fifo();

    test_sjf();

    test_round_robin();

    printf("\n=============================\n");
    printf("TODOS LOS TESTS PASARON\n");
    printf("=============================\n");

    return 0;
}