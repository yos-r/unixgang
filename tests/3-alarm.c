#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define LINE_MAX 128
#define DELAY 10

void beep(int sig) { 
    printf("\ntrop tard !\n"); 
    exit(EXIT_SUCCESS);
}

int main()
{
    struct  sigaction sa;
    char answer[LINE_MAX];
    
    memset(&sa, 0, sizeof(sa));3
    sa.sa_handler = beep;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }
    
    printf("Reponse ? ");
    fflush(stdout);
    
    alarm(DELAY);
    
    if (fgets(answer, LINE_MAX, stdin)) {
        alarm(0);
        printf("ok\n");
    }
    
    return EXIT_SUCCESS;
}