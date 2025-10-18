#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Before execvp()\n");

    char *args[] = {"echo", "Hello from exec family\n", NULL};      //NULL is important
    execvp("echo", args);

    printf("Error, execvp() failed");
    return 1;
}