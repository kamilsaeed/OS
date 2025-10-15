#include <stdio.h>
#include <pthread.h>
#include <math.h>


void* calc_square(void* arg) 
{
    double* num_ptr = (double*)arg;        
    double square = (*num_ptr) * (*num_ptr);
    printf("\nSquare thread: %.2f\n", square);

    return NULL;
}


void* calc_sqrt(void* arg) 
{
    double* num_ptr = (double*)arg;       
    double root = sqrt(*num_ptr);
    printf("Square root thread: %.2f\n\n", root);
    
    return NULL;
}

int main() 
{
    pthread_t square_thread, sqrt_thread;
    double num;

    num = 25;

    pthread_create(&square_thread, NULL, calc_square, &num);
    pthread_create(&sqrt_thread, NULL, calc_sqrt, &num);

    pthread_join(square_thread, NULL);
    pthread_join(sqrt_thread, NULL);

    return 0;
}
