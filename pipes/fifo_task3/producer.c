#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define fifo_name "myfifo"

int main(int argc, char *argv[])
{
    int fd;
    char message[100];

    if(argc < 2)
    {
        printf("Usage: %s <ProducerID>\n", argv[0]);
        exit(1);
    }

    fd = open(fifo_name, O_WRONLY);

    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    sprintf(message, "Producer %s: Hello from producer\n", argv[1]);
    write(fd, message, strlen(message) + 1);

    printf("Producer %s: Message sent\n", argv[1]);

    close(fd);
    return 0;
}