#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    // Créer le premier fils (il ne se termine jamais)
    if ((pid1 = fork()) == 0) {
        while (1);  // Boucle infinie pour ne jamais se terminer
    }

    // Créer le deuxième fils
    if ((pid2 = fork()) == 0) {
        printf("Fils 2: Mon PID est %d et mon PPID est %d\n", getpid(), getppid());
        sleep(10);  // Attendre 10 secondes
        exit(0);    // Se termine
    }

    // Le père attend la fin du deuxième fils
    waitpid(pid2, NULL, 0);
    printf("Père: Le PID du fils que j'ai attendu est %d\n", pid2);
    
    return 0;
}
