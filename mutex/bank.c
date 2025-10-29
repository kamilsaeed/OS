#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int acc1 = 1000, acc2 = 1000;
pthread_mutex_t lock1, lock2;

void* transfertoB(void* arg) 
{
    pthread_mutex_lock(&lock1);
    printf("Thread 1 locked Account 1\n");
    sleep(1);
    pthread_mutex_lock(&lock2);
    printf("Thread 1 locked Account 2\n");

    acc1 -= 100;
    acc2 += 100;

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

void* transfertoA(void* arg) 
{
    pthread_mutex_lock(&lock1);
    printf("Thread 2 locked Account 1\n");
    sleep(1);
    pthread_mutex_lock(&lock2);
    printf("Thread 2 locked Account 2\n");

    acc2 -= 50;
    acc1 += 50;

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

int main() 
{
    pthread_t t1, t2;
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, transfertoB, NULL);
    pthread_create(&t2, NULL, transfertoA, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Balances: Account 1 = %d Account 2 = %d\n", acc1, acc2);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    return 0;
}
