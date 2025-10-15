#include <stdio.h>
#include <pthread.h>

void* increment_local(void* arg) 
{
    int local_counter = 0;

    for (int i = 0; i < 5; i++) 
    {
        local_counter++;
        printf("Thread incrementing global: %d\n", local_counter);
    }
return NULL;
}

int main() 
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, increment_local, NULL);
    pthread_create(&thread2, NULL, increment_local, NULL);

    pthread_join(thread1, NULL);   
    pthread_join(thread2, NULL);

    return 0;
}