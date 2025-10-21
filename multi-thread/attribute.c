#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* joinable_thread(void* arg)
{
    printf("Joinable thread: running...\n");
    sleep(1);
    printf("Joinable thread: finished!\n");
    return NULL;
}

void* detached_thread(void* arg)
{
    printf("Detached thread: running...\n");
    sleep(2);
    printf("Detached thread: finished!\n");
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    pthread_attr_t attr;

    pthread_create(&t1, NULL, joinable_thread, NULL);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&t2, &attr, detached_thread, NULL);
    pthread_attr_destroy(&attr);

    printf("Main: joining joinable thread...\n");
    pthread_join(t1, NULL);
    printf("Main: successfully joined joinable thread.\n");

    printf("\nMain: trying to join detached thread...\n");
    int ret = pthread_join(t2, NULL);
    if (ret != 0)
    {
        printf("Main: cannot join detached thread (error code %d)\n", ret);
    }

    printf("\nMain: exiting.\n");
    return 0;
}
