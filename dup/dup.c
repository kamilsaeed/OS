#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("error.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    
    close(2);
    dup(fd);
    close(fd);

    fprintf(stderr, "Simulated error message\n");
    printf("Check file for error\n");

    return 0;
}