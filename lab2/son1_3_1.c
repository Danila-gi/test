#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    printf("son1: PID = %d, PPID = %d\n", getpid(), getppid());
    while (1) {
        sleep(1);
    }
    return 0;
}
