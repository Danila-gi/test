#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t son1, son2;

    son1 = fork();
    if (son1 == 0) {
        printf("son1: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(2);
        exit(0);
    }

    son2 = fork();
    if (son2 == 0) {
        printf("son2: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(5);
        exit(0);
    }

    // Ожидаем завершения son1 через wait
    int status;
    pid_t pid = wait(&status);
    if (WIFEXITED(status)) {
	printf("son1 %d exited with status %d\n", pid, WEXITSTATUS(status));
    }

    // Ожидаем завершения son2 через waitpid
    waitpid(son2, &status, 0);
    if (WIFEXITED(status)) {
        printf("son2 %d exited with status %d\n", son2, WEXITSTATUS(status));
    }

    return 0;
}
