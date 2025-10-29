#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
FILE *file;

void* write_log(void* arg) 
{
    int id = *(int*)arg;
    for (int i = 1; i <= 5; i++) 
    {
        pthread_mutex_lock(&lock);
        fprintf(file, "Thread %d: log message %d\n", id, i);
        fflush(file);
        pthread_mutex_unlock(&lock);
        usleep(100000);
    }
    return NULL;
}

int main() 
{
    pthread_t t[3];
    int ids[3] = {1, 2, 3};
    pthread_mutex_init(&lock, NULL);

    file = fopen("log.txt", "w");
    if (!file) 
    {
        perror("fopen");
        return 1;
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&t[i], NULL, write_log, &ids[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(t[i], NULL);
    }

    fclose(file);
    pthread_mutex_destroy(&lock);
    return 0;
}
