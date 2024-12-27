#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>  

volatile int signal_count = 0;
time_t start_time;  

// Gestionnaire de signal
void signal_handler(int signo) {
    signal_count++;
    printf("Signal %d reçu (Total: %d)\n", signo, signal_count);
    
    if (signal_count >= 5) {
        printf("5 signaux reçus. Arrêt du programme.\n");
        exit(0);
    }
}

int main() {
    start_time = time(NULL);
    
    for (int i = 1; i < 32; i++) {
        if (i != SIGKILL && i != SIGSTOP) {
            signal(i, signal_handler);
        }
    }
    
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
