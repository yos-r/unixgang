#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
/*
3 Ce programme affiche périodiquement le contenu de la
4 mémoire partagée. Arrêt par Contrôle-C
5 */
#define SHM_KEY 0x1234
#define SHM_SIZE 1024
#define DELAI 2
struct donnees // structure stockée dans le segment
{
    int nb;
    int total;
};
int encore;
void arret(int signal)
{
    encore = 0;
}

/**
 
 * This file likely contains the implementation of a shared memory consumer process.
 * The consumer process typically reads data from a shared memory segment created by a producer process.
 */
// 
int main()
{
    key_t cle = ftok(getenv("HOME"), 'a'); // génération de la clé
    int id = shmget(cle, sizeof(struct donnees), 0); // accès au segment existant car flag = 0
    struct donnees *shared = (struct donnees *)shmat(id, NULL, SHM_R); // attachement du segment et recup addresse
    encore = 1;

    struct sigaction action; // structure pour traiter les signaux
    action.sa_handler = arret; // fonction de traitement du signal lors de l'arrêt par Contrôle-C
    sigemptyset(&action.sa_mask); // vide le masque
    action.sa_flags = 0; // pas de flags
    sigaction(SIGINT, &action, NULL);// installation du traitement du signal SIGINT

    while (encore)
    {
        printf("sous-total %d= %d\n", shared->nb, shared->total); // affichage du sous-total
        sleep(DELAI); // attente de DELAI secondes
    }

    shmdt((char *)shared); // libération du segment
    shmctl(id, IPC_RMID, NULL); // destruction du segment


    
    return 0;
}