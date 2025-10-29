#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0, count = 0;

pthread_mutex_t lock;
pthread_cond_t not_full, not_empty;

void* producer(void* arg) 
{
    int item = 1;
    while (item <= 10) 
    {
        pthread_mutex_lock(&lock);
        while (count == SIZE)
        {
            pthread_cond_wait(&not_full, &lock);
        }

        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % SIZE;
        count++;

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&lock);
        item++;
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) 
{
    for (int i = 0; i < 10; i++) 
    {
        pthread_mutex_lock(&lock);
        while (count == 0)
        {
            pthread_cond_wait(&not_empty, &lock);
        }

        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % SIZE;
        count--;

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&lock);
        sleep(2);
    }
    return NULL;
}

int main() 
{
    pthread_t prod, cons;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    return 0;
}
