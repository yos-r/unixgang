#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    printf("! Signal %d received\n", sig);
}

void handler_alarm(int sig) {
    printf("hello\n");
    alarm(3);  // Set alarm to go off again in 3 seconds
}

int main() {
    // Register a generic handler for signals
    for (int i = 1; i < NSIG; i++) {
        signal(i, handler);
    }

    // Set handler for SIGALRM
    signal(SIGALRM, handler_alarm);  
    alarm(3);  // Set initial alarm to go off in 3 seconds

    // Wait for signals
    for (int i = 0; i < 5; i++) {
        pause();  // Wait for signal to be delivered
    }

    return 0;
}
