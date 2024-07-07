#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main() {

    int pid = fork();
    int x = 0;

    if(pid < 0) {
        // wait();
        printf("\nError");
    }
    else if(pid == 0) {
        x++;
        printf("\nChild succeeded x= %d\n", x);
        printf("%d\n", pid);
        printf("current: %d\n", getpid());
        printf("parent: %d\n", getppid());
    }
    else {
        // wait();
        x--;
        printf("\nParent succeeded x= %d\n", x);
        printf("%d\n", pid);
        printf("current: %d\n", getpid());
        printf("parent: %d\n", getppid());
    }

    return 0;
}