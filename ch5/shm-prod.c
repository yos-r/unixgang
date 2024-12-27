/* prod.c */ /*
3 Ce programme lit une suite de nombres, et effectue le cumul dans une
4 variable en mémoire partagée. */
#include <sys/ipc.h> // pour les constantes IPC_CREAT, IPC_RMID, etc.
#include <sys/shm.h> // pour shmget, shmat, shmdt, shmctl
#include <sys/types.h> 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
struct donnees // structure stockée dans le segment
{
    int nb;
    int total;
};
int main(void)
{
    key_t cle = ftok(getenv("HOME"), 'a'); // génération de la clé
    int id = shmget(cle, sizeof(struct donnees), IPC_CREAT | 0666);// création du segment
    struct donnees *shared = (struct donnees *)shmat(id, NULL, SHM_R | SHM_W);// attachement du segment
    shared->total = 0;
    shared->nb = 0;
    int reponse;
    while (1)
    {
        scanf("%d", &reponse);//
        shared->total += reponse;// ajout de la valeur lue
        shared->nb++; // incrémentation du nombre de valeurs
        printf("sous-total %d= %d\n", shared->nb, shared->total); // affichage du sous-total
    }
    shmdt((char*) shared);// libération du segment
    shmctl(id, IPC_RMID, NULL); // destruction du segment
    

}