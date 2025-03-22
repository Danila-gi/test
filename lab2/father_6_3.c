#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig) {
    printf("Parent: Received signal %d\n", sig);
}

int main() {
    pid_t son;

    signal(SIGUSR1, handler);

    son = fork();
    if (son == -1) {
        perror("fork failed");
        return 1;
    }

    if (son == 0) {
        printf("Child: Sending SIGUSR1 to myself before exec()\n");
        raise(SIGUSR1);
        
        execl("./son", "son", NULL);
        perror("execl failed");
        exit(EXIT_FAILURE);
    }

    sleep(2);

    printf("Parent: Sending SIGUSR1 to myself\n");
    raise(SIGUSR1);

    printf("Parent: Sending SIGUSR1 to son (PID: %d)\n", son);
    kill(son, SIGUSR1);

    return 0;
}
