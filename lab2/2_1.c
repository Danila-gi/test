#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Создаем процесс-потомок

    if (pid == 0) {
        // Код, выполняемый в процессе-потомке
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());
    } else if (pid > 0) {
        // Код, выполняемый в родительском процессе
        printf("Parent Process: PID = %d, PPID = %d\n", getpid(), getppid());
	wait(NULL);
    } else {
        // Обработка ошибки
        fprintf(stderr, "Fork failed!\n");
        return 1;
    }

    // Общий код для обоих процессов
    printf("Process with PID = %d is finishing.\n", getpid());

    return 0;
}
