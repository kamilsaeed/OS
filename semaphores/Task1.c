#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define PRODUCER_COUNT 3
#define CONSUMER_COUNT 3
#define ITEMS_PER_PRODUCER 20
#define TOTAL_ITEMS (PRODUCER_COUNT * ITEMS_PER_PRODUCER)

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t emptySlots;
sem_t filledSlots;
sem_t bufferLock;
sem_t producerPrepLock;
sem_t consumerProcessLock;

int consumed = 0;
int finishFlag = 0;

pthread_mutex_t countLock;

void* producer(void* arg) {
    int id = *(int*)arg;

    for (int i = 1; i <= ITEMS_PER_PRODUCER; i++) {

        sem_wait(&producerPrepLock);
        int item = id * 100 + i;
        printf("Producer %d: prepared item %d\n", id, item);
        sem_post(&producerPrepLock);

        sem_wait(&emptySlots);
        sem_wait(&bufferLock);

        buffer[in] = item;
        printf("Producer %d: inserted %d at index %d\n", id, item, in);

        in = (in + 1) % BUFFER_SIZE;

        sem_post(&bufferLock);
        sem_post(&filledSlots);
    }

    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;

    while (1) {

        sem_wait(&filledSlots);
        sem_wait(&bufferLock);

        pthread_mutex_lock(&countLock);
        if (finishFlag && consumed >= TOTAL_ITEMS) {
            pthread_mutex_unlock(&countLock);
            sem_post(&bufferLock);
            break;
        }
        pthread_mutex_unlock(&countLock);

        int item = buffer[out];
        printf("Consumer %d: removed %d from index %d\n", id, item, out);

        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_lock(&countLock);
        consumed++;
        if (consumed >= TOTAL_ITEMS) {
            finishFlag = 1;
        }
        pthread_mutex_unlock(&countLock);

        sem_post(&bufferLock);
        sem_post(&emptySlots);

        sem_wait(&consumerProcessLock);
        printf("Consumer %d: processed %d\n", id, item);
        sem_post(&consumerProcessLock);
    }

    return NULL;
}

int main() {
    pthread_t prod[PRODUCER_COUNT], cons[CONSUMER_COUNT];
    int prodID[PRODUCER_COUNT], consID[CONSUMER_COUNT];

    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&filledSlots, 0, 0);
    sem_init(&bufferLock, 0, 1);
    sem_init(&producerPrepLock, 0, 1);
    sem_init(&consumerProcessLock, 0, 1);

    pthread_mutex_init(&countLock, NULL);

    for (int i = 0; i < PRODUCER_COUNT; i++) {
        prodID[i] = i + 1;
        pthread_create(&prod[i], NULL, producer, &prodID[i]);
    }

    for (int i = 0; i < CONSUMER_COUNT; i++) {
        consID[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, &consID[i]);
    }

    for (int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_join(prod[i], NULL);
    }

    for (int i = 0; i < CONSUMER_COUNT; i++) {
        sem_post(&filledSlots);
    }

    for (int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_join(cons[i], NULL);
    }

    sem_destroy(&emptySlots);
    sem_destroy(&filledSlots);
    sem_destroy(&bufferLock);
    sem_destroy(&producerPrepLock);
    sem_destroy(&consumerProcessLock);
    pthread_mutex_destroy(&countLock);

    printf("\nAll items produced and consumed.\n");
    return 0;
}
