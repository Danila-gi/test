#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    printf("Son Process: PID = %d, PPID = %d\n", getpid(), getppid());

    sleep(3);

    printf("Son Process: Finished.\n");
    return 0;
}
