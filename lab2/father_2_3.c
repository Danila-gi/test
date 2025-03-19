#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    // Массив аргументов для execv и execvp
    char *args[] = {"./son", "arg1", "arg2", NULL};

    // Переменные окружения для execle
    char *env[] = {"ENV_VAR1=value1", "ENV_VAR2=value2", NULL};

    // Создаем дочерний процесс
    pid = fork();

    if (pid == 0) {
        // Дочерний процесс
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());

        // Использование execl
        /*printf("Using execl:\n");
        if (execl("./son", "son", "arg1", "arg2", NULL) == -1) {
            perror("execl failed");
        }

        // Использование execv
        printf("Using execv:\n");
        if (execv("./son", args) == -1) {
            perror("execv failed");
        }

        // Использование execle
        printf("Using execle:\n");
        if (execle("./son", "son", "arg1", "arg2", NULL, env) == -1) {
            perror("execle failed");
        }*/

        // Использование execvp
        printf("Using execvp:\n");
        if (execvp("son", args) == -1) {
            perror("execvp failed");
        }

        // Если все exec-функции завершились с ошибкой
        printf("All exec functions failed.\n");
        exit(1);
    } else if (pid > 0) {
        // Родительский процесс
        printf("Parent Process: PID = %d, PPID = %d\n", getpid(), getppid());

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
