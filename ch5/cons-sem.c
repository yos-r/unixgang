#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

typedef int SEMAPHORE;

struct donnees {
    int nb;
    int total;
};

SEMAPHORE obtenir_sem(key_t key) {
    return semget(key, 1, 0); // Access existing semaphore
}

void P(SEMAPHORE sem) {
    struct sembuf sb = {0, -1, 0}; // sembuf has 3 fields: sem_num, sem_op: ajouté à la valeur courante semval du semaphore, block the result if negative , sem_flg
    semop(sem, &sb, 1);
}

void V(SEMAPHORE sem) {
    struct sembuf sb = {0, 1, 0}; // Signal operation
    semop(sem, &sb, 1);
}

int encore = 1;

void arret(int signal) {
    encore = 0;
}

int main() {
    key_t cle = ftok(getenv("HOME"), 'a');
    int id = shmget(cle, sizeof(struct donnees), 0);
    struct donnees *shared = (struct donnees *)shmat(id, NULL, SHM_R);

    // Access the existing semaphore
    SEMAPHORE sem = obtenir_sem(cle);

    struct sigaction action;
    action.sa_handler = arret;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

    while (encore) {
        // Lock the semaphore (P operation)
        P(sem);

        printf("Consumer read: sous-total %d = %d\n", shared->nb, shared->total);

        // Unlock the semaphore (V operation)
        V(sem);

        sleep(2); // Wait for DELAI seconds
    }

    shmdt((char *)shared);
    return 0;
}
