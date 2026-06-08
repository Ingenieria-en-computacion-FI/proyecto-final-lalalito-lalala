#include <stdio.h>
#include <assert.h>
#include "../include/memory_manager.h"

void test_first_fit() {

    printf("Ejecutando test_first_fit...\n");

    MemoryManager* mm = mm_create(1024);

    assert(mm != NULL);

    int pid1 = mm_allocate_first_fit(mm, 100);
    int pid2 = mm_allocate_first_fit(mm, 200);

    assert(pid1 >= 0);
    assert(pid2 >= 0);

    printf("PID1 = %d\n", pid1);
    printf("PID2 = %d\n", pid2);

    mm_free(mm, pid1);

    int pid3 = mm_allocate_first_fit(mm, 50);

    assert(pid3 >= 0);

    printf("PID3 = %d\n", pid3);

    mm_destroy(mm);

    printf("test_first_fit OK\n\n");
}

void test_create_destroy() {

    printf("Ejecutando test_create_destroy...\n");

    MemoryManager* mm = mm_create(512);

    assert(mm != NULL);
    assert(mm->total_memory == 512);

    mm_destroy(mm);

    printf("test_create_destroy OK\n\n");
}

int main() {

    test_create_destroy();

    test_first_fit();

    printf("=================================\n");
    printf("TODOS LOS TESTS PASARON\n");
    printf("=================================\n");

    return 0;
}
