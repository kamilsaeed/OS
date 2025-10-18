#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Before execlp()\n");
    execlp("ls", "ls", "-l", NULL);

    perror("Error, execlp failed");
    return 1;
}