// program that counts the signals it receives and displays those counts.
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

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
    // Register the signal handlers
    signal(SIGINT, signal_handler);   // Handle Ctrl+C (SIGINT)
    signal(SIGTERM, signal_handler);  // Handle termination (SIGTERM)

    // Infinite loop to keep the program running and receiving signals
    while (1) {
        // Pause the program until a signal is received
        pause();
    }

    return 0;
}
