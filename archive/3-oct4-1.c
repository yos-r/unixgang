// Tubes sans snom
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//  *** EXERCICE: ECRIRE UN PROG C EQUIVALENT À PS -AUX | WC -L ****
// CREER PIPE, FAIRE FORK,
// DESIGNER LE PRODUCTEUR/PERE , ICI C'EST PS , DESIGNER LE CONSOMMATEUR/FILS ICI C'EST WC,
// POUR PERE/FILS:  FERMER une extremite du PIPE , faire DUP2 pour remplacer soit l'entree standard soit la sortie standard, fermer une autre extremite
// FAIRE COMMUTATION D'IMAGE

int main(int argc, char const *argv[])
{
    int p[2];

    // create pipe
    if (pipe(p) == -1)
    {
        perror("pipe failed");
        return 1;
    }

    int n = fork();
    if (n == 0)
    {                                  // processus pere producteur ps
        close(p[0]);                   // fermer l'extremité de lecture
        dup2(p[1], 1);                 // standard output now is fed into the tube instead of the screen
        close(p[1]);                   // fermer l'extremité d'ecriture du pipe
        execlp("ps", "ps", "-aux", 0); // commutation d'image
    }
    else if (n > 0)
    {
        close(p[1]);   // fermer l extremite d'ecriture du pipe
        dup2(p[0], 0); // standard input to the proc is coming from reading extremity of the pipe
        close(p[0]);   // fermer extremite de lecture du pipe
        execlp("wc", "wc", "-l", 0);
    }
    else
    {
        perror("fork failed");
        return 1;
    }

    return 0;
}
