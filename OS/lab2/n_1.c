// #define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 

int main() {
    pid_t pid = getpid(); // Идентификатор текущего процесса
    pid_t ppid = getppid(); // Идентификатор родительского процесса
    pid_t pgid = getpgrp(); // Идентификатор группы вызывающего процесса
    uid_t uid = getuid(); // Реальный идентификатор владельца
    gid_t gid = getgid(); // Реальный идентификатор группы владельца
    uid_t euid = geteuid(); // Эффективный идентификатор владельца
    gid_t egid = getegid(); // Эффективный идентификатор группы владельца

    printf("Идентификатор текущего процесса (PID): %d\n", pid);
    printf("Идентификатор родительского процесса (PPID): %d\n", ppid);
    printf("Идентификатор группы вызывающего процесса (PGID): %d\n", pgid);
    printf("Реальный идентификатор владельца (UID): %d\n", uid);
    printf("Реальный идентификатор группы владельца (GID): %d\n", gid);
    printf("Эффективный идентификатор владельца (EUID): %d\n", euid);
    printf("Эффективный идентификатор группы владельца (EGID): %d\n", egid);

    return 0;
}