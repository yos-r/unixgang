#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int nsig[_NSIG]; // array to count signals

// signal handler function
void handler(int signum)
{
    printf("Signal reçu %d pour la %d ème fois\n", signum, ++nsig[signum]);
}

int main()
{
    // initialize signal counters
    for (int i = 0; i < _NSIG; i++)
    {
        // Some signals like SIGKILL and SIGSTOP can't be caught or ignored, so we skip those
        if (signal(i, handler) == SIG_ERR)
            continue;
        nsig[i] = 0;
    }

    // wait for signals indefinitely
    while (1)
        pause(); // suspend the program until a signal is received

    return 0;
}
