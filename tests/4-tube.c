#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int tube[2];
    char buffer[256];
    int i;

    fprintf(stdout, "Création du tube\n");
    if (pipe(tube) != 0)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 256; i++)
        buffer[i] = i;

    fprintf(stdout, "Écriture dans le tube\n");
    if (write(tube[1], buffer, 256) != 256)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Lecture dans le tube\n");
    if (read(tube[0], buffer, 256) != 256)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Vérification\n");
    for (i = 0; i < 256; i++)
    {
        if (buffer[i] != i)
        {
            fprintf(stdout, "Erreur i = %d et buffer = %d\n", i, buffer[i]);
        }
    }

    fprintf(stdout, "Vérification terminée.\n");

    return EXIT_SUCCESS;
}
