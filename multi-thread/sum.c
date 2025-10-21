#include <stdio.h>
#include <pthread.h>

#define size 20

int arr[size];
int sum1 = 0, sum2 = 0;

void* first_sum (void* arg)
{
    for(int i = 0; i < 10; i++)
    {
        sum1 += arr[i];
    }

    printf("Thread 1 (1-10) sum = %d\n", sum1);
    return 0;
}

void* second_sum (void* arg)
{
    for(int i = 10; i < 20; i++)
    {
        sum2 += arr[i];
    }

    printf("Thread 2 (11-20) sum = %d\n", sum2);
    return 0;
}

int main()
{
    for(int i = 0; i < size; i++)
    {
        arr[i] = i + 1;
    }

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, first_sum, NULL);
    pthread_create(&thread2, NULL, second_sum, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    int total_sum = sum1 + sum2;
    printf("Main thread: total sum = %d\n", total_sum);

    return 0;
}