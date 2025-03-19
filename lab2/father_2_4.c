#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

// Функция для запуска процесса-сына
void run_son(int delay_son, int delay_father) {
    pid_t pid = fork();

    if (pid == 0) {
        // Дочерний процесс (сын)
        printf("Son Process: PID = %d, PPID = %d\n", getpid(), getppid());
        
        // Фиксируем состояние процессов
        system("ps -o pid,ppid,stat,comm > processes.txt");
        
        sleep(delay_son);  // Имитация работы процесса-сына
        
        printf("Son Process: Finished.\n");
        exit(0);
    } else if (pid > 0) {
        // Родительский процесс (отец)
        printf("Father Process: PID = %d, PPID = %d\n", getpid(), getppid());

        if (delay_father > 0) {
            sleep(delay_father);  // Имитация работы процесса-отца
        }

        if (delay_father == 0) {
            // Отец завершается сразу после запуска сына
            printf("Father Process: Exiting without waiting for son.\n");
            exit(0);
        } else {
            // Отец ждет завершения сына
            wait(NULL);
            printf("Father Process: Son process finished.\n");
        }
        

    } else {
        perror("fork failed");
        exit(1);
    }
}

int main() {
    printf("Situation a\n");
    run_son(2, 5);

    /*printf("Situation b\n");
    run_son(5, 0);*/

    /*printf("Situation c\n");
    run_son(2, 5);*/

    return 0;
}
