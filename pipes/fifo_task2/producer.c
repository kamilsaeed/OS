#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define fifo_name "myfifo"

int main()
{
    int fd;
    char *message = "Hello from producer\n";

    if(mkfifo(fifo_name, 0666) == -1 )
    {
        perror("Error mkfifo\n");
        return 1;
    }

    fd = open(fifo_name, O_WRONLY);

    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    write(fd, message, strlen(message) + 1);
    printf("\nProducer: Message written to pipe\n");
    close(fd);

    unlink(fifo_name);

    return 0;
}