#include <stdio.h>
#include <pthread.h>

int num1 = 10;
int num2 = 5;
int sum_result, mul_result, sub_result, div_result;

void* sum(void* arg)
{
    sum_result = num1 + num2;
    printf("Sum of two number is %d\n", sum_result);

    return NULL;
}

void* sub(void* arg)
{
    sub_result = num1 - num2;
    printf("Subtraction of two number is %d\n", sub_result);

    return NULL;
}

void* mul(void* arg)
{
    mul_result = num1 * num2;
    printf("Product of two number is %d\n", mul_result);

    return NULL;
}

void* div(void* arg)
{
    div_result = num1 / num2;
    printf("Division of two number is %d\n", div_result);

    return NULL;
}

int main()
{
    pthread_t thread1, thread2, thread3, thread4;

    pthread_create(&thread1, NULL, sum, NULL);
    pthread_create(&thread2, NULL, sub, NULL);
    pthread_create(&thread3, NULL, mul, NULL);
    pthread_create(&thread4, NULL, div, NULL);

    pthread_join(thread1, NULL);   
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
}