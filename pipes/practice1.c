#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pipefd[2];
    pid_t pid;

    char msg[] = "Hello from parent";
    char recv_msg[100];

    if(pipe(pipefd) == -1)
    {
        perror("Pipe failed!\n");
        return 1;
    }

    pid = fork();

    if(pid == -1)
    {
        perror("Fork failed!\n");
        return 1;
    }

    if( pid == 0)
    {
        close(pipefd[1]);
        read(pipefd[0], recv_msg, sizeof(recv_msg));

        printf("\nChild process received: %s\n\n", recv_msg);
        close(pipefd[0]);
    }
    else
    {
        close(pipefd[0]);
        write(pipefd[1], msg, sizeof(msg));
        close(pipefd[1]);
    }
    return 0;
}