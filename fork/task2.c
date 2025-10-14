#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid1, pid2;

    pid1 = fork();

    if(pid1 == -1)
    {
        printf("Fork1 failed\n");
        return 1;
    }

    if(pid1 == 0)
    {
        printf("Child 1 process with PID(%d) and PPID(%d)\n", getpid(), getppid());

        pid2 = fork();

        if(pid2 == -1)
        {
            printf("Fork2 failed\n");
            return 1;
        }

        if(pid2 == 0)
        {
            printf("Child 2 with PID(%d) and PPID(%d)\n", getpid(), getppid());
        }
        else
        {
            printf("Child 1 PID(%d) created Child 2 PID(%d)\n", getpid(), pid2);
        }
    }
    else
    {
        printf("Parent with PID(%d) created Child 1 with PID(%d)\n", getpid(), pid1);
    }

    return 0;
}