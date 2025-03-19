#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int sig) {
    printf("son3: Received signal %d\n", sig);
    
    // Анализируем таблицу процессов
    system("ps -s >> processes.txt");
}

int main() {
    printf("son3: PID = %d, PPID = %d\n", getpid(), getppid());
    signal(SIGUSR1, signal_handler);
    while (1) {
        sleep(1);
    }
    return 0;
}
