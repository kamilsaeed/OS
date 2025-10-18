#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Before execl()\n");

    execl("/bin/ps", "ps", NULL);

    perror("Error, execl() failed");
    return 1;
}