#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();  // Создаем дочерний процесс

    if (pid == 0) {
        // Код, выполняемый в процессе-потомке
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());

        // Заменяем образ дочернего процесса на программу son
        execl("./son", "son", NULL);

        // Если execl() завершился с ошибкой
        perror("execl failed");
        exit(1);
    } else if (pid > 0) {
        // Код, выполняемый в родительском процессе
        printf("Parent Process: PID = %d, PPID = %d\n", getpid(), getppid());

        // Фиксируем состояние таблицы процессов
        system("ps -l > processes.txt");

	// Ждем завершения дочернего процесса
        wait(NULL);

        printf("Parent Process: Child process finished.\n");
    } else {
        // Ошибка при создании дочернего процесса
        perror("fork failed");
        exit(1);
    }

    return 0;
}
