#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* worker(void* arg)
{
    size_t stack_size = *(size_t*)arg;
    printf("Thread with stack size %zu KB started\n", stack_size / 1024);
    sleep(5);
    printf("Thread with stack size %zu KB finished\n", stack_size / 1024);
    return NULL;
}

int main()
{
    pthread_t t1, t2, t3;
    pthread_attr_t attr;
    size_t sizes[3] = {512 * 1024, 1024 * 1024, 2048 * 1024}; 

    pthread_attr_init(&attr);

    pthread_attr_setstacksize(&attr, sizes[0]);
    pthread_create(&t1, &attr, worker, &sizes[0]);

    pthread_attr_setstacksize(&attr, sizes[1]);
    pthread_create(&t2, &attr, worker, &sizes[1]);

    pthread_attr_setstacksize(&attr, sizes[2]);
    pthread_create(&t3, &attr, worker, &sizes[2]);

    pthread_attr_destroy(&attr);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("All threads finished.\n");
    return 0;
}
