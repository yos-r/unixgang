#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>  // For time()

// Variable globale pour compter les signaux reçus
volatile int signal_count = 0;
time_t start_time;  // Variable to store the start time

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
    // Stocker le temps de démarrage du programme
    start_time = time(NULL);
    
    // Configuration du gestionnaire pour tous les signaux
    for (int i = 1; i < 32; i++) {
        // On exclut certains signaux qu'on ne peut pas intercepter
        if (i != SIGKILL && i != SIGSTOP) {
            signal(i, signal_handler);
        }
    }
    
    printf("Programme démarré. En attente de signaux...\n");
    
    // Boucle principale
    while (1) {
        printf("Toujours actif...\n");
        sleep(3);  // Pause de 3 secondes
        
        // Vérification du timeout (15 secondes sans réception de signal)
        if (signal_count == 0 && (time(NULL) - start_time) >= 15) {
            printf("Timeout de 15 secondes atteint. Arrêt du programme.\n");
            exit(0);
        }
    }
    
    return 0;
}
