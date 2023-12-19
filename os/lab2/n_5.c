#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int men_count = 0;
int women_count = 0;
int max;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void woman_wants_to_enter()
{
    int flag = 0;
    pthread_mutex_lock(&mutex);

    printf("A women wants to enter\n");

    if (men_count == 0 && women_count < max)
    {
        printf("A women entered\n");

        women_count++;
        printf("Women: %d\n", women_count);
        flag = 1;

        pthread_mutex_unlock(&mutex);
    }
    else
    {
        printf("A women cannot enter, either men in bathroom or bathroom is full\n");

        pthread_mutex_unlock(&mutex);
        while(!flag)
        {
            pthread_mutex_lock(&mutex);

            if (men_count == 0 && women_count < max)
            {
                printf("A women entered\n");

                women_count++;
                printf("Women: %d\n", women_count);
                flag = 1;

                pthread_mutex_unlock(&mutex);
            }

            else
            {
                pthread_mutex_unlock(&mutex);
            }
        }
    }
}

void man_wants_to_enter()
{
    int flag = 0;
    pthread_mutex_lock(&mutex);

    printf("A man wants to enter\n");

    if (women_count == 0 && men_count < max)
    {
        printf("A man entered\n");

        men_count++;
        printf("Men: %d\n", men_count);
        flag = 1;

        pthread_mutex_unlock(&mutex);
    }
    else
    {
        printf("A man cannot enter, either women in bathroom or bathroom is full\n");

        pthread_mutex_unlock(&mutex);

        while(!flag)
        {
            pthread_mutex_lock(&mutex);

            if (women_count == 0 && men_count < max)
            {
                printf("A man entered\n");

                men_count++;
                printf("Men: %d\n", men_count);
                flag = 1;

                pthread_mutex_unlock(&mutex);
            } 

            else
            {
                pthread_mutex_unlock(&mutex);
            }
        }
    }
}

void woman_leaves()
{
    pthread_mutex_lock(&mutex);

    if (women_count > 0)
    {
        women_count--;
        printf("A woman leaves the bathroom. Women in the bathroom: %d\n", women_count);

    }
    pthread_mutex_unlock(&mutex);
}

void man_leaves()
{
    pthread_mutex_lock(&mutex);

    if (men_count > 0)
    {
        men_count--;
        printf("A man leaves the bathroom. Men in the bathroom: %d\n", men_count);
    }

    pthread_mutex_unlock(&mutex);
}

void *woman(void *arg)
{
    woman_wants_to_enter();
    sleep(3);
    woman_leaves();
    return NULL;
}

void *man(void *arg)
{
    man_wants_to_enter();
    sleep(3);
    man_leaves();
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error with number of arguments\n");
        return 1;
    }

    int n = atoi(argv[1]);

    max = n;

    pthread_t women_threads[n];
    pthread_t men_threads[n];

    for (int i = 0; i < n; i++)
    {
        pthread_create(&women_threads[i], NULL, woman, NULL);
        pthread_create(&men_threads[i], NULL, man, NULL);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(women_threads[i], NULL);
        pthread_join(men_threads[i], NULL);
    }

    return 0;
}


