#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Global counters for different signals
int sigint_count = 0;
int sigterm_count = 0;

// Signal handler function
void signal_handler(int signal) {
    if (signal == SIGINT) {
        sigint_count++;
        printf("SIGINT received. Count: %d\n", sigint_count);
    } else if (signal == SIGTERM) {
        sigterm_count++;
        printf("SIGTERM received. Count: %d\n", sigterm_count);
    }
}

int main() {
    struct sigaction sa;

    // Clear the sigaction struct
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = signal_handler;

    // Register SIGINT handler
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error handling SIGINT");
        exit(EXIT_FAILURE);
    }

    // Register SIGTERM handler
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Error handling SIGTERM");
        exit(EXIT_FAILURE);
    }

    // Infinite loop to keep the program running and receiving signals
    while (1) {
        // Pause the program until a signal is received
        pause();
    }

    return 0;
}
