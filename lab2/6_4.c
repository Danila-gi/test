#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int child_func(void *arg) {
    printf("Child PID: %d\n", getpid());
    return 0;
}

int main() {
    char stack[1024 * 1024];  // Стек для нового процесса

    pid_t pid = clone(child_func, stack + sizeof(stack), CLONE_VM | CLONE_FS | CLONE_FILES, NULL);
    if (pid == -1) {
        perror("clone");
        return 1;
    }

    printf("Parent PID: %d\n", getpid());
    waitpid(pid, NULL, 0);
    return 0;
}
