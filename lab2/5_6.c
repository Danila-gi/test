#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>

void* thread_function(void* arg) {
    const char* policy_name = (const char*)arg;
    printf("Thread with %s policy started\n", policy_name);

    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);
    printf("Thread %s: policy = %d, priority = %d\n", policy_name, policy, param.sched_priority);

    time_t start = time(NULL);
    while (time(NULL) - start < 5) {
        // Активное ожидание
    }

    printf("Thread with %s policy finished\n", policy_name);
    return NULL;
}

void set_thread_policy(pthread_t thread, int policy, int priority) {
    struct sched_param param;
    param.sched_priority = priority;
    if (pthread_setschedparam(thread, policy, &param) != 0) {
        perror("pthread_setschedparam");
    }
}

int main() {
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, thread_function, (void*)"SCHED_FIFO (Prio 50)");
    pthread_create(&thread2, NULL, thread_function, (void*)"SCHED_FIFO (Prio 70)");
    //pthread_create(&thread3, NULL, thread_function, (void*)"SCHED_RR (Prio 50)");

    set_thread_policy(thread1, SCHED_FIFO, 50);
    set_thread_policy(thread2, SCHED_FIFO, 70);
    //set_thread_policy(thread3, SCHED_RR, 50);


    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    //pthread_join(thread3, NULL);

    printf("All threads finished\n");
    return 0;
}
