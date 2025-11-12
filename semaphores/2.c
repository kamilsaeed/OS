#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int buffer;          
sem_t sem_produce;
sem_t sem_consume;

void* producer(void* arg) 
{
    for (int i = 0; i < 5; i++) 
    {
        sem_wait(&sem_produce);   
        buffer = rand() % 100;    
        printf("Producer produced: %d\n", buffer);
        sem_post(&sem_consume);   
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) 
{
    for (int i = 0; i < 5; i++) 
    {
        sem_wait(&sem_consume);   
        printf("Consumer consumed: %d\n", buffer);
        sem_post(&sem_produce);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&sem_produce, 0, 1);  
    sem_init(&sem_consume, 0, 0);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&sem_produce);
    sem_destroy(&sem_consume);

    return 0;
}
