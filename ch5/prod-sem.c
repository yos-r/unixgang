#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

typedef int SEMAPHORE;

struct donnees { // Structure that's shared?
    int nb;
    int total;
};

SEMAPHORE creer_sem(key_t key, int val) { // Create a semaphore with a given key and value
    SEMAPHORE sem = semget(key, 1, IPC_CREAT | 0666); // Create one semaphore with the given key
    semctl(sem, 0, SETVAL, val); // Set the value of the first sem to val
    return sem;
}

void P(SEMAPHORE sem) {
    struct sembuf sb = {0, -1, 0}; // wait operation
    semop(sem, &sb, 1);
}

void V(SEMAPHORE sem) {
    struct sembuf sb = {0, 1, 0}; // signal operation
    semop(sem, &sb, 1);
}

void detruire_sem(SEMAPHORE sem) {
    semctl(sem, 0, IPC_RMID, 0);
}

int main(void) {
    key_t cle = ftok(getenv("HOME"), 'a');
    int id = shmget(cle, sizeof(struct donnees), IPC_CREAT | 0666);
    struct donnees *shared = (struct donnees *)shmat(id, NULL, SHM_R | SHM_W); // Attach the shared memory segment

    // create semaphore initialized to 1 for mutual exclusion
    SEMAPHORE sem = creer_sem(cle, 1); 

    shared->total = 0;
    shared->nb = 0;
    int reponse;

    while (1) {
        printf("Enter a number: ");
        scanf("%d", &reponse);

        // Lock the semaphore (P operation)
        P(sem); // Decrement the semaphore

        shared->total += reponse;
        shared->nb++;
        printf("Producer updated: sous-total %d = %d\n", shared->nb, shared->total);

        V(sem);// Increment the semaphore
    }

    shmdt((char *)shared); // libérer le segment 
    shmctl(id, IPC_RMID, NULL); // détruire le segment
    detruire_sem(sem);

    return 0;
}
