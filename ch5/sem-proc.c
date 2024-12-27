#include <sys/types.h>
#include <sys/ipc.h> // pour les constantes IPC_CREAT, IPC_RMID, etc.
#include <sys/sem.h> // pour semget, semctl, semop qui manipulent les sémaphores 
#include <unistd.h> // pour fork, getpid, etc.
#include <stdio.h> // pour printf, perror, etc.
#include <stdlib.h> 
#include <ctype.h>
typedef int SEMAPHORE;

// int semget(key_t key, int nsems, int semflg ) // Création ou accès à un ensemble de sémaphores,

// int semop(int semid, struct sembuf *sops, unsigned nsops) // Opération sur un ensemble de sémaphores, sops = tableau de structures sembuf, une structure sembuf par sémaphore 
/**
 * The sembuf structure contains the following fields:
 * - `unsigned short sem_num`: The index of the semaphore within the semaphore set.
 * - `short sem_op`: The operation to be performed on the semaphore. It can be:
 *   - A positive value to increment the semaphore.
 *   - A negative value to decrement the semaphore.
 *   - Zero to wait until the semaphore value is zero.
 * sembuf is used in conjunction with the semop() system call to perform atomic operations on semaphores,
 * which are useful for process synchronization and ensuring mutual exclusion.
 */
// int semctl(int semid, int semnum, int cmd, union semun arg ) // Contrôle d'un ensemble de sémaphores, cmd = commande à exécuter

SEMAPHORE creer_sem(key_t key, int val)
{
	SEMAPHORE sem;
	int r;
	sem = semget(key, 1, IPC_CREAT | 0666);// Création de l'ensemble de sémaphores
	r = semctl(sem, 0, SETVAL, val); // Initialisation du sémaphore avec commande SETVAL et la valeur val
	return sem;
}
void changer_sem(SEMAPHORE sem, int val)
{
	struct sembuf sb[1]; // tableau de 1 structure sembuf
	sb[0].sem_num = 0; // sémaphore 0
	sb[0].sem_op = val; // opération sur le sémaphore si val > 0 incrémenter, si val < 0 décrémenter, si val = 0 attendre
	sb[0].sem_flg = 0; // flags
    semop(sem, sb, 1); // semop fait l'opération sur le sémaphore
}


void P(SEMAPHORE sem)
{
	changer_sem(sem, -1); // décrémenter le sémaphore
}
void V(SEMAPHORE sem)
{
	changer_sem(sem, 1); // incrémenter le sémaphore
}
void detruire_sem(SEMAPHORE sem)
{
    semctl(sem, 0, IPC_RMID, 0); // cmd = IPC_RMID qui détruit l'ensemble de sémaphores, semnum = 0 car un seul sémaphore
}
