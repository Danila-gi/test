#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>

int main() {
    // Устанавливаем политику и приоритет в родительском процессе ДО fork()
    struct sched_param param;
    param.sched_priority = 50;

    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Дочерний процесс
        struct sched_param child_param;
        if (sched_getparam(0, &child_param) == -1) {
            perror("sched_getparam failed in child");
            exit(EXIT_FAILURE);
        }

        printf("Child PID: %d\n", getpid());
        printf("Child scheduling policy: %d\n", sched_getscheduler(0));
        printf("Child priority: %d\n", child_param.sched_priority);
    } else {
        // Родительский процесс
        struct sched_param parent_param;
        if (sched_getparam(0, &parent_param) == -1) {
            perror("sched_getparam failed in parent");
            exit(EXIT_FAILURE);
        }

        printf("Parent PID: %d\n", getpid());
        printf("Parent scheduling policy: %d\n", sched_getscheduler(0));
        printf("Parent priority: %d\n", parent_param.sched_priority);
    }

    return 0;
}
