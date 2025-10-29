#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

pthread_mutex_t lock1, lock2;

void* thread1_func(void* arg) {
    printf("Thread 1: Trying to lock mutex1...\n");
    pthread_mutex_lock(&lock1);
    printf("Thread 1: Locked mutex1.\n");

    sleep(1);

    printf("Thread 1: Trying to lock mutex2...\n");
    pthread_mutex_lock(&lock2);
    printf("Thread 1: Acquired both locks.\n");

    printf("Thread 1: Executing critical section.\n");
    sleep(1);

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

void* thread2_func(void* arg) {
    printf("Thread 2: Trying to lock mutex2...\n");
    pthread_mutex_lock(&lock2);
    printf("Thread 2: Locked mutex2.\n");

    sleep(1);
    printf("Thread 2: Trying to lock mutex1 (with simulated timeout)...\n");

    int tries = 0, result;
    while ((result = pthread_mutex_trylock(&lock1)) != 0 && tries < 10) {
        printf("Thread 2: Waiting for mutex1... (%d)\n", tries + 1);
        usleep(300000); // 0.3s delay
        tries++;
    }

    if (result == 0) {
        printf("Thread 2: Acquired both locks.\n");
        printf("Thread 2: Executing critical section.\n");
        pthread_mutex_unlock(&lock1);
        printf("Thread 2: Releasing locks.\n");
    } else {
        printf("Thread 2: *** Timed out waiting for mutex1! ***\n");
        printf("Thread 2: Backing off and releasing mutex2 to resolve deadlock.\n");
    }

    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_create(&t2, NULL, thread2_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    return 0;
}
