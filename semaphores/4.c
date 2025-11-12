#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 10
#define THREADS 2

int arr[SIZE] = {12, 5, 8, 19, 3, 25, 7, 2, 10, 6};
int global_min;
sem_t sem;  

void* find_min(void* arg) 
{
    int index = *(int*)arg;
    int start = index * (SIZE / THREADS);
    int end = start + (SIZE / THREADS);

    int local_min = arr[start];
    for (int i = start + 1; i < end; i++) 
    {
        if (arr[i] < local_min)
        {
            local_min = arr[i];
        }
    }

    sem_wait(&sem);  
    if (local_min < global_min)
    {
        global_min = local_min;
    }

    sem_post(&sem);  
    printf("Thread %d local minimum: %d\n", index + 1, local_min);
    return NULL;
}

int main() 
{
    pthread_t tid[THREADS];
    int indices[THREADS];

    sem_init(&sem, 0, 1);
    global_min = arr[0];   

    for (int i = 0; i < THREADS; i++) 
    {
        indices[i] = i;
        pthread_create(&tid[i], NULL, find_min, &indices[i]);
    }

    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    printf("Global Minimum = %d\n", global_min);

    sem_destroy(&sem);
    return 0;
}
