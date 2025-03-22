#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        // Дочерний процесс 1
        while (1) {
            sleep(1);
            printf("Child 1 PID: %d\n", getpid());
        }
    } else {
        pid_t pid2 = fork();
        if (pid2 == 0) {
            // Дочерний процесс 2
            while (1) {
                sleep(1);
                printf("Child 2 PID: %d\n", getpid());
            }
        } else {
            // Родительский процесс
            while (1) {
                sleep(1);
                printf("Parent PID: %d\n", getpid());
            }
        }
    }
    return 0;
}
