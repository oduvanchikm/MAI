#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define PHIL 5
#define KEY 1234

void forks(int phil)
{
    int sem_id = semget(KEY, PHIL, IPC_CREAT | 0666);

    int left_fork = phil;
    int right_fork = (phil + 1) % PHIL;

    struct sembuf sem_left_lock = {left_fork, +1, 0};
    struct sembuf sem_right_lock = {right_fork, +1, 0};

    semop(sem_id, &sem_left_lock, 1);
    semop(sem_id, &sem_right_lock, 1);
}

void phils(int phil)
{
    int sem_id = semget(KEY, PHIL, IPC_CREAT | 0666);
    int left = phil;
    int right = (phil + 1) % PHIL;

    struct sembuf sem_left_lock = {left, -1, 0};
    struct sembuf sem_right_lock = {right, -1, IPC_NOWAIT};
    struct sembuf sem_left_unlock = {left, +1, 0};
    int poel = 0;
    printf("The philosopher %d is hungry\n", phil + 1);
    while(!poel)
    {
        if (semop(sem_id, &sem_left_lock, 1) == 0)
    {
        if (semop(sem_id, &sem_right_lock, 1) == 0)
        {
            printf("The philosopher %d is eating\n", phil + 1);
            sleep(3);
            forks(phil);
            poel = 1;
        }

        else 
        {
            semop(sem_id, &sem_left_unlock, 1);
            printf("The philosopher %d is thinking\n", phil + 1);
            sleep(3);
        }
    }

    else 
    {
        //semop(sem_id, &sem_left_unlock, 1);
        printf("The philosopher %d is thinking\n", phil + 1);
        sleep(3);
    }
    }
    

    printf("The philosopher %d is thinking\n", phil + 1);
    //exit(0);
}

int main()
{
    pid_t phil[PHIL];
    int sem_id = semget(KEY, PHIL, IPC_CREAT | 0666);

    if (sem_id == -1)
    {
        perror("semget");
        exit(1);
    }

    for (int i = 0; i < PHIL; i++)
    {
        semctl(sem_id, i, SETVAL, 1);
    }

    for (int i = 0; i < PHIL; i++)
    {
        phil[i] = fork();

        if (phil[i] == -1)
        {
            perror("fork");
            exit(1);
        }

        else if (phil[i] == 0)
        {
            phils(i);
            return 0;
        }
    }
    for (int i = 0; i < PHIL; i++)
    {
        waitpid(phil[i], NULL, 0);
    }

    semctl(sem_id, 0, IPC_RMID);

    return 0;
}