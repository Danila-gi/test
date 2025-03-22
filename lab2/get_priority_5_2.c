#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    int priority = getpriority(PRIO_PROCESS, pid);
    printf("Priority of process %d: %d\n", pid, priority);
    return 0;
}
