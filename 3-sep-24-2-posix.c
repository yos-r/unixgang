#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

// Flag to check if input was received on time
volatile sig_atomic_t input_received = 0;

// Signal handler for SIGALRM
void handle_alarm(int sig) {
    if (sig == SIGALRM) {
        printf("\nTime's up! No input received within 10 seconds.\n");
        _exit(EXIT_FAILURE); // Exit the program immediately
    }
}

int main() {
    struct sigaction sa;

    // Set up the alarm signal handler
    memset(&sa, 0, sizeof(sa)); // Clear the struct
    sa.sa_handler = handle_alarm; // Set the handler function
    sigemptyset(&sa.sa_mask); // Clear the signal mask
    sa.sa_flags = 0; // No special flags

    // Install the handler for SIGALRM
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("Error setting up SIGALRM handler");
        exit(EXIT_FAILURE);
    }

    // Set an alarm to go off after 10 seconds
    alarm(10);

    // Prompt the user for input
    printf("Enter a string within 10 seconds: ");

    // Read user input
    char input[100];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // If input is received, disable the alarm
        alarm(0);
        input_received = 1;
        printf("You entered: %s\n", input);
    }

    if (!input_received) {
        printf("No input received on time.\n");
    }

    return 0;
}
