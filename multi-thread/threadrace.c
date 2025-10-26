#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int X = 0, Y = 0;

void *f1(void *p) 
{
    X = 1;
    
    if (Y == 0)
    {
        sleep(1);
    }

    printf("T1 ");
    Y = 2;
    return NULL;
}

void *f2(void *p) 
{
    if (X == 0)
    {
        Y = 1;
    }

    printf("T2 ");
    X = 2;
    return NULL;
}

int main() 
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, f1, NULL);
    pthread_create(&t2, NULL, f2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main ");
    return 0;
}
