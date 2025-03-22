#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>
#include <sys/resource.h>
#include <time.h>

// Функция для нагрузки на CPU
void cpu_load() {
    volatile unsigned long long x = 0; // volatile, чтобы компилятор не оптимизировал цикл
    for (int i = 0; i < 1000000000ULL; i++){
        x++;    
    }
}

int main(int argc, char* argv[]) {
    int min_priority = sched_get_priority_min(SCHED_RR);
    int max_priority = sched_get_priority_max(SCHED_RR);
    printf("Min priority: %d, Max priority: %d\n", min_priority, max_priority);
    struct timespec interval;
    if (sched_rr_get_interval(getpid(), &interval) == 0) {
        printf("Quantum: %ld ns\n", interval.tv_nsec);
    }
    
    int id = (argc > 1) ? atoi(argv[1]) : 0;
    
    struct sched_param param;
    param.sched_priority = id; // Приоритет для SCHED_RR
    if (sched_setscheduler(getpid(), SCHED_RR, &param) == -1) {
        perror("sched_setscheduler failed for Child 1");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        cpu_load();
        printf("Procces PID: %d, Priority: %d\n", getpid(), param.sched_priority);
    }
    return 0;
}
