#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd[2];
    pid_t pid;

    if(pipe(fd) == -1)
    {
        perror("Pipe failed\n");
    }

    pid = fork();

    if(pid == -1)
    {
        perror("Fork failed");
    }

    if(pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        printf("Message to parent\n");
        fflush(stdout);
    }
    else
    {
        close(fd[1]);
        char buff[100];

        int byte_read = read(fd[0], buff, sizeof(buff) - 1);
        buff[byte_read] = '\0';

        printf("Message received from child: %s\n", buff);
        close(fd[0]);
    }

    return 0;
}