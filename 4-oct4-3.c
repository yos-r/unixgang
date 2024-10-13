#include <sys/types.h> // types
#include <unistd.h>
#include <stdio.h>
#include <string.h>     // Pour strlen


// Ecrire un programme en C qui crée un tube de communication entre un
// processus et son fils le flux de données passe du fils au père.
#define R 0
#define W 1

int main() {
    int fd[2];
    char message[100];
    int nboctets;
    const char *phrase = "message envoyé au père par le fils"; // Utiliser const char*

    if (pipe(fd) == -1) { 
        perror("pipe");
        return 1;
    }

    if (fork() == 0) { 
        close(fd[R]);
        
        write(fd[W], phrase, strlen(phrase) + 1);
        
        close(fd[W]);
    } else {
        close(fd[W]);
        
        nboctets = read(fd[R], message, sizeof(message));
        printf("Lecture %d octets : %s\n", nboctets, message);
        
        close(fd[R]);
    }

    return 0;
}
