#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* download(void* arg)
{
    int file_num = *(int*)arg;
    printf("Downloading file %d...\n", file_num);
    sleep(2); 
    printf("File %d done!\n", file_num);
    return NULL;
}

int main()
{
    pthread_t threads[3];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    int file_nums[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&threads[i], &attr, download, &file_nums[i]);
    }

    pthread_attr_destroy(&attr);

    printf("All downloads started!\n");

    pthread_exit(NULL);
    return 0;
}
