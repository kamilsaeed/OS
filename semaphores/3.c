#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 10
#define THREADS 2

int arr[SIZE] = {1,2,3,4,5,6,7,8,9,10};
int total_sum = 0;
sem_t sem;  

void* partial_sum(void* arg) 
{
    int index = *(int*)arg;
    int start = index * (SIZE / THREADS);
    int end = start + (SIZE / THREADS);
    int local_sum = 0;

    for (int i = start; i < end; i++)
    {
        local_sum += arr[i];
    }

    sem_wait(&sem);          
    total_sum += local_sum;
    printf("Thread %d partial sum: %d\n", index + 1, local_sum);
    sem_post(&sem);           

    
    return NULL;
}

int main() 
{
    pthread_t tid[THREADS];
    int indices[THREADS];

    sem_init(&sem, 0, 1); 

    for (int i = 0; i < THREADS; i++) 
    {
        indices[i] = i;
        pthread_create(&tid[i], NULL, partial_sum, &indices[i]);
    }

    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    printf("Total Sum = %d\n", total_sum);

    sem_destroy(&sem);
    return 0;
}
