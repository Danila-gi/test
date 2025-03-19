#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    printf("son2: PID = %d, PPID = %d\n", getpid(), getppid());
    signal(SIGUSR1, SIG_IGN);
    while (1) {
        sleep(1);
    }
    return 0;
}
