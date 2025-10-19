#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define fifo_name "myfifo"

int main()
{
    int fd;
    char buff[100];

    if(mkfifo(fifo_name, 0666) == -1)
    {
        perror("mkfifo");
    }

    fd = open(fifo_name, O_RDONLY);

    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    read(fd, buff, sizeof(buff));
    printf("\n Message from producer is: %s\n", buff);
    close(fd);

    unlink(fifo_name);

    return 0;
}