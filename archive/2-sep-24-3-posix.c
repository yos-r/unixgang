#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h> 

volatile int signal_count = 0;
time_t start_time;  

void signal_handler(int signo) {
    signal_count++;
    printf("Signal %d reçu (Total: %d)\n", signo, signal_count);
    
    if (signal_count >= 5) {
        printf("5 signaux reçus. Arrêt du programme.\n");
        exit(0);
    }

    alarm(15);  
}

int main() {
    start_time = time(NULL);
    
    struct sigaction sa;
    sa.sa_handler = signal_handler; 
    sigemptyset(&sa.sa_mask);       
    sa.sa_flags = 0;                 

    for (int i = 1; i < NSIG; i++) {
        if (i != SIGKILL && i != SIGSTOP) {
            if (sigaction(i, &sa, NULL) == -1) {
                perror("Error setting up signal handler");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    alarm(15);
    
    printf("Programme démarré. En attente de signaux...\n");
    
    while (1) {
        printf("Toujours actif...\n");
        sleep(3);  

        if (signal_count == 0 && (time(NULL) - start_time) >= 15) {
            printf("Timeout de 15 secondes atteint. Arrêt du programme.\n");
            exit(0);
        }
    }
    
    return 0;
}
