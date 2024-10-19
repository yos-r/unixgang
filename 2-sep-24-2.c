#include <stdio.h>
#include <signal.h>
#include <unistd.h>
// Écrire un programme qui lit au clavier une chaîne de caractères.
// Le programme affiche une erreur si l’utilisateur n’a pas entré la chaîne 
de caractères au bout de 10 secondes.

void handler(int signum) {
    printf("\nErreur: Temps écoulé, aucune entrée fournie.\n");
    _exit(1);  // Exit the program when time is up
}

int main() {
    char input[100];

    // Set up the signal handler for timeout
    signal(SIGALRM, handler);

    // Set the alarm for 10 seconds
    alarm(10);

    printf("Veuillez entrer une chaîne de caractères dans les 10 secondes: \n");

    // Get user input
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Cancel the alarm if input is provided
        alarm(0);
        printf("Vous avez entré: %s", input);
    }

    return 0;
}
