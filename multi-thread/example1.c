#include <stdio.h>
#include <pthread.h>

int global_counter = 0;

void* increment_global(void* arg)
{
    for (int i = 0; i < 5; i++) 
    {
        global_counter++;
        printf("Thread incrementing global: %d\n", global_counter);
    }
    return NULL;
}

int main() 
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, increment_global, NULL);
    pthread_create(&thread2, NULL, increment_global, NULL);

    pthread_join(thread1, NULL);   
    pthread_join(thread2, NULL);

    printf("Final global counter: %d\n", global_counter);
    return 0;
}