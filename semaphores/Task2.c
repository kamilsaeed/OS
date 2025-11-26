#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READER_COUNT 5
#define WRITER_COUNT 2
#define WRITES_PER_WRITER 5

int sharedData = 0;
int readerCount = 0;
int writerWaiting = 0;

sem_t readerLock;
sem_t writeLock;
sem_t readerCountLock;
sem_t writerWaitingLock;

int finishedWriters = 0;

void* reader(void* arg) {
    int id = *(int*)arg;

    while (1) {
        sem_wait(&readerLock);
        sem_wait(&writerWaitingLock);

        if (writerWaiting > 0) {
            sem_post(&writerWaitingLock);
            sem_post(&readerLock);
            usleep(2000);
            continue;
        }

        sem_post(&writerWaitingLock);
        sem_wait(&readerCountLock);

        readerCount++;
        if (readerCount == 1) {
            sem_wait(&writeLock);
        }

        sem_post(&readerCountLock);
        sem_post(&readerLock);

        printf("Reader %d: read value %d (readers=%d)\n", id, sharedData, readerCount);

        sem_wait(&readerCountLock);
        readerCount--;
        if (readerCount == 0) {
            sem_post(&writeLock);
        }
        sem_post(&readerCountLock);

        if (finishedWriters == WRITER_COUNT) break;
        usleep(2000);
    }

    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < WRITES_PER_WRITER; i++) {
        sem_wait(&writerWaitingLock);
        writerWaiting++;
        sem_post(&writerWaitingLock);

        sem_wait(&writeLock);

        sharedData++;
        printf("Writer %d: wrote value %d\n", id, sharedData);

        sem_post(&writeLock);

        sem_wait(&writerWaitingLock);
        writerWaiting--;
        sem_post(&writerWaitingLock);

        usleep(3000);
    }

    finishedWriters++;
    return NULL;
}

int main() {
    pthread_t r[READER_COUNT], w[WRITER_COUNT];
    int rID[READER_COUNT], wID[WRITER_COUNT];

    sem_init(&readerLock, 0, 1);
    sem_init(&writeLock, 0, 1);
    sem_init(&readerCountLock, 0, 1);
    sem_init(&writerWaitingLock, 0, 1);

    for (int i = 0; i < WRITER_COUNT; i++) {
        wID[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &wID[i]);
    }

    for (int i = 0; i < READER_COUNT; i++) {
        rID[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &rID[i]);
    }

    for (int i = 0; i < WRITER_COUNT; i++) {
        pthread_join(w[i], NULL);
    }

    for (int i = 0; i < READER_COUNT; i++) {
        pthread_join(r[i], NULL);
    }

    sem_destroy(&readerLock);
    sem_destroy(&writeLock);
    sem_destroy(&readerCountLock);
    sem_destroy(&writerWaitingLock);

    printf("\nAll writers finished. Readers stopped.\n");
    return 0;
}
