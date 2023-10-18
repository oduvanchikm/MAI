#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 

int main() {
    pid_t pid = getpid(); 
    pid_t ppid = getppid();
    pid_t pgid = getpgrp(); 
    uid_t uid = getuid(); 
    gid_t gid = getgid(); 
    uid_t euid = geteuid(); 
    gid_t egid = getegid(); 

    printf("Идентификатор текущего процесса: %d\n", pid);
    printf("Идентификатор родительского процесса: %d\n", ppid);
    printf("Идентификатор группы вызывающего процесса: %d\n", pgid);
    printf("Реальный идентификатор владельца: %d\n", uid);
    printf("Реальный идентификатор группы владельца: %d\n", gid);
    printf("Эффективный идентификатор владельца: %d\n", euid);
    printf("Эффективный идентификатор группы владельца: %d\n", egid);

    return 0;
}