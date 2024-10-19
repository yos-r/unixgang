#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// La commande complète ps aux | grep root | wc -l donne le nombre total de processus en cours d'exécution sur le système qui sont détenus par l'utilisateur "root".
int main()
{
    int p[2];  // Premier pipe
    int p1[2]; // Deuxième pipe

    // Créer le premier pipe
    if (pipe(p) == -1)
    {
        perror("pipe failed");
        return 1;
    }

    pid_t n = fork();
    if (n == -1)
    {
        perror("fork failed");
        return 1;
    }

    if (n == 0)
    {                              // Processus parent (ps -aux)
        close(p[0]);               // Ferme l'extrémité de lecture du pipe
        dup2(p[1], STDOUT_FILENO); // Redirige la sortie standard vers l'extrémité d'écriture du pipe
        close(p[1]);               // Ferme l'extrémité d'écriture

        execlp("ps", "ps", "-aux", NULL); // Exécute `ps -aux`
        perror("execlp failed");          // Si execlp échoue
        exit(1);
    }

    // Créer le deuxième pipe
    if (pipe(p1) == -1)
    {
        perror("pipe failed");
        return 1;
    }

    pid_t n1 = fork();
    if (n1 == -1)
    {
        perror("fork failed");
        return 1;
    }

    if (n1 == 0)
    {                             // Processus intermédiaire (grep root)
        close(p[1]);              // Fermer l'extrémité d'écriture du premier pipe
        dup2(p[0], STDIN_FILENO); // Rediriger l'entrée standard vers l'extrémité de lecture du premier pipe
        close(p[0]);              // Fermer l'extrémité de lecture du premier pipe

        close(p1[0]);               // Fermer l'extrémité de lecture du deuxième pipe
        dup2(p1[1], STDOUT_FILENO); // Rediriger la sortie standard vers l'extrémité d'écriture du deuxième pipe
        close(p1[1]);               // Fermer l'extrémité d'écriture du deuxième pipe

        execlp("grep", "grep", "root", NULL); // Exécute `grep root`
        perror("execlp failed");              // Si execlp échoue
        exit(1);
    }
    else // Processus final (wc -l)
    {
        close(p[0]);               // Fermer l'extrémité de lecture du premier pipe
        close(p[1]);               // Fermer l'extrémité d'écriture du premier pipe
        close(p1[1]);              // Fermer l'extrémité d'écriture du deuxième pipe
        dup2(p1[0], STDIN_FILENO); // Rediriger l'entrée standard vers l'extrémité de lecture du deuxième pipe
        close(p1[0]);              // Fermer l'extrémité de lecture du deuxième pipe
        execlp("wc", "wc", "-l", NULL); // Exécute `wc -l`
        perror("execlp failed");        // Si execlp échoue}

        return 1;
    }
}
