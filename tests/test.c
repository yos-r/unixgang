#include <stdio.h>
#include <pthread.h>

// Fonction pour afficher les nombres de 1 à 50
void* afficher1_50(void* arg) {
    for (int i = 1; i <= 50; i++) {
        printf("%d ", i);
    }
    return NULL;
}

// Fonction pour afficher les nombres de 51 à 100
void* afficher51_100(void* arg) {
    for (int i = 51; i <= 100; i++) {
        printf("%d ", i);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Création des deux threadsd
    pthread_create(&thread1, NULL, afficher1_50, NULL);
    pthread_create(&thread2, NULL, afficher51_100, NULL);

    // Attente de la fin des threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\n");
    return 0;
}
