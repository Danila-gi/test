#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    pid_t son1, son2, son3;

    // Создаем три дочерних процесса
    son1 = fork();
    if (son1 == 0) {
        execl("./son1", "son1", NULL);
    }

    son2 = fork();
    if (son2 == 0) {
        execl("./son2", "son2", NULL);
    }

    son3 = fork();
    if (son3 == 0) {
        execl("./son3", "son3", NULL);
    }

    sleep(2);

    // Отправляем сигналы дочерним процессам
    kill(son1, SIGUSR1);
    kill(son2, SIGUSR1);
    kill(son3, SIGUSR1);

    // Ждем завершения дочерних процессов
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
