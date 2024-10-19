#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h> // For time()

// Global variable to count received signals
volatile int signal_count = 0;
time_t start_time;  // Variable to store the start time

// Signal handler
void signal_handler(int signo) {
    signal_count++;
    printf("Signal %d reçu (Total: %d)\n", signo, signal_count);
    
    // Exit after receiving 5 signals
    if (signal_count >= 5) {
        printf("5 signaux reçus. Arrêt du programme.\n");
        exit(0);
    }

    // Reset the alarm each time a signal is received
    alarm(15);  // Reset the 15 seconds timeout
}

int main() {
    // Store the start time of the program
    start_time = time(NULL);
    
    struct sigaction sa;
    sa.sa_handler = signal_handler; // Set the signal handler
    sigemptyset(&sa.sa_mask);       // Clear the signal mask
    sa.sa_flags = 0;                 // No special flags

    // Configure the signal handler for all signals
    for (int i = 1; i < NSIG; i++) {
        // Exclude certain signals that cannot be caught
        if (i != SIGKILL && i != SIGSTOP) {
            if (sigaction(i, &sa, NULL) == -1) {
                perror("Error setting up signal handler");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    // Set the initial alarm for 15 seconds
    alarm(15);
    
    printf("Programme démarré. En attente de signaux...\n");
    
    // Main loop
    while (1) {
        printf("Toujours actif...\n");
        sleep(3);  // Pause for 3 seconds

        // Check for timeout
        if (signal_count == 0 && (time(NULL) - start_time) >= 15) {
            printf("Timeout de 15 secondes atteint. Arrêt du programme.\n");
            exit(0);
        }
    }
    
    return 0;
}
