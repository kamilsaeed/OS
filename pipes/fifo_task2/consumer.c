#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

// #define fifo_name "myfifo"

int main()
{
    int fd;
    char buff[100];
    char *fifo = "myfifo";

    // if(mkfifo(fifo_name, 0666) == -1)
    // {
    //     perror("fifo");
    //     return 1;
    // }

    fd = open(fifo, O_RDONLY | O_NONBLOCK);

    while(1)
    {
        int read_byte = read(fd, buff, sizeof(buff));

        if(read_byte == -1)
        {
            perror("\nNo data available (NON-BLOCK)\n");
        }
        else if (read_byte > 0)
            {
                printf("\nRead: %s\n", buff);
            }
            else
            {
                printf("EOF");
            }
        
        sleep(1);
    }
    close(fd);
    return 0;
}