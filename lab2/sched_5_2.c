#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
    int id = (argc > 1) ? atoi(argv[1]) : 0;
    for (int i = 0; i < 100000; ++i) {
        printf("%d", id);
        fflush(stdout);      // Сбрасывает буфер вывода
    }
    printf("\n");
    return 0;
}
