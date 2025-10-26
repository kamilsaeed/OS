#include <stdio.h>
#include <unistd.h>

int main() {
    printf("A");

    if (fork() || fork() && fork()) {
        fork();
        printf("B");
    } else {
        if (fork() && fork() || fork()) {
            printf("C");
        }
    }

    printf("D");
    return 0;
}
