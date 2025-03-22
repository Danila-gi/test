#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("testfile.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Дочерний процесс
        write(fd, "Child\n", 6);
    } else {
        // Родительский процесс
        write(fd, "Parent\n", 7);
    }

    close(fd);
    return 0;
}
