#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    printf("Son: Received signal %d\n", sig);
}

int main() {
    // Восстанавливаем обработчик сигнала SIGUSR1
    signal(SIGUSR1, handler);
    printf("son1: PID = %d, PPID = %d\n", getpid(), getppid());
    while (1) {
        sleep(1);
    }
    return 0;
}
