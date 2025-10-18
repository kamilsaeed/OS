#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {"date", NULL};
    execvp("date", args);

    perror("Error, Execvp() failed");
    return 1;
}