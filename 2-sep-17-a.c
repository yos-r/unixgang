#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    fork(); 

    printf("fork 1 pid: %d\n", getpid());
    
    fork();
    
    printf("fork 2 pid: %d\n", getpid());
    
    fork();
    
    printf("fork 3 pid: %d\n", getpid());

    return 0;
}
