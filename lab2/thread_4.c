#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/syscall.h>

#define STACK_SIZE (1024 * 1024)

pthread_t t1;

int shared_variable = 0;

void* thread1(void* arg) {
    int tid = syscall(SYS_gettid);
    int pid = getpid();
    printf("Thread_1 with thread id = %d and pid = %d is started\n", tid, pid);
    sleep(300);
    shared_variable++;
    printf("Thread_1 with thread id = %d and pid = %d is finished. New shared_variable=%d\n", tid, pid, shared_variable);
    return NULL;
}

int thread2(void* arg) {
    int tid = syscall(SYS_gettid);
    int pid = getpid();
    printf("Thread_2 with thread id = %d and pid = %d is started\n", tid, pid);
    sleep(500);
    shared_variable++;
    printf("Thread_2 with thread id = %d and pid = %d is finished. New shared_variable=%d\n", tid, pid, shared_variable);
    return 0;
}

int main() {
    // Создание потока_1 через pthread_create
    pthread_create(&t1, NULL, thread1, NULL);
    
    
    // Создание потока_2 через clone
    void* stack = malloc(STACK_SIZE);
    if (stack == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int flags = CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD;
    pid_t tid2 = clone(thread2, stack + STACK_SIZE, flags, NULL);
    if (tid2 == -1) {
        perror("clone");
        free(stack);
        exit(EXIT_FAILURE);
    }
    
    system("ps -eLf | grep ./thread > threads.txt");

    // Ожидаем завершения потоков
    pthread_join(t1, NULL);
    sleep(6);

    printf("Main thread: all thread has finished. Final shared_variable=%d\n", shared_variable);

    free(stack);
    return 0;
}
