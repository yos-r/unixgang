#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

int main() {
    pid_t pid_fils;
    int status; 

    // Création du processus fils
    pid_fils = fork();

    if (pid_fils < 0) {
        // Erreur lors du fork
        perror("Erreur lors du fork");
        exit(EXIT_FAILURE);
    }

    if (pid_fils == 0) {
        // Processus fils
        printf("Processus fils: fork=%d, pid=%d, ppid=%d\n", pid_fils, getpid(), getppid());
        sleep(3);  // Blocage pendant 3 secondes
        exit(2);   // Terminaison avec un code de retour égal à 2
    } else {
        // Processus père
        printf("Processus père: fork=%d, pid=%d, ppid=%d\n", pid_fils, getpid(), getppid());

        // Attente de la fin du processus fils
        waitpid(pid_fils, &status, 0); // ou bien wait(&s)

        // Affichage du code de retour du processus fils
        if (WIFEXITED(status)) {
            printf("Le processus fils s'est terminé avec le code: %d\n", WEXITSTATUS(status));
        }

        // Exécution d'un programme C qui imprime le PID courant et liste les processus actifs
        execlp("ps", "ps", "-e", NULL); // Remplace le processus courant par 'ps -e' pour lister les processus actifs

        // Si execlp échoue
        perror("Erreur lors de l'exécution de 'ps'");
        exit(EXIT_FAILURE);
    }

    return 0;
}
