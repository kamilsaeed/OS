#include <stdio.h>
#include <pthread.h>

void* modify_local(void* arg) 
{
    int* local_var_ptr = (int*) arg;

    *local_var_ptr += 10;

    printf("Thread: local_var = %d\n", *local_var_ptr); 
    return NULL;
}

int main() 
{
    pthread_t thread;
    int local_var = 20;

    printf("Before thread: local_var = %d\n", local_var);

    pthread_create(&thread, NULL, modify_local, (void*)&local_var);
    pthread_join(thread, NULL);   

    printf("After thread: local_var = %d\n", local_var);
    return 0;
}