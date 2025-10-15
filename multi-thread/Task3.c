#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) 
{
    pthread_attr_t* attr = (pthread_attr_t*)arg;
    size_t stacksize;
    int policy;

    pthread_attr_getstacksize(attr, &stacksize);
    pthread_attr_getschedpolicy(attr, &policy);

    printf("Thread is running with ID: %lu\n", pthread_self());
    printf("Stack size: %zu bytes\n", stacksize);
    

    if (policy == SCHED_OTHER)
        printf("Scheduling Policy: SCHED_OTHER (default)\n");
    else if (policy == SCHED_RR)
        printf("Scheduling Policy: SCHED_RR (Round Robin)\n");
    else if (policy == SCHED_FIFO)
        printf("Scheduling Policy: SCHED_FIFO (First In First Out)\n");
    else
        printf("Scheduling Policy: Unknown (%d)\n", policy);
    
    return NULL;
}

int main() 
{
    pthread_t thread;
    pthread_attr_t attr;
    size_t stacksize;

    pthread_attr_init(&attr);

    stacksize = 1024 * 1024;
    pthread_attr_setstacksize(&attr, stacksize);
    pthread_attr_setschedpolicy(&attr, SCHED_OTHER);

    pthread_create(&thread, &attr, thread_function, (void*)&attr);

    pthread_join(thread, NULL);
    pthread_attr_destroy(&attr);

    printf("Thread completed.\n");
    return 0;
}