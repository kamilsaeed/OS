#include<stdio.h>
#include<unistd.h>

int main()
{
    pid_t pid;
    
    pid = fork();
    
    if(pid == -1)
    {
        printf("Fork failed");
        return 1;
    }

    if(pid == 0)
    {
        printf("\nIn child process with pid: %d\n", getpid());
    }
    else
    {
        printf("In parent process with pid: %d, Child pid: %d", getpid(), pid);
    }

    return 0;
}