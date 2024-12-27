#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAXTEXTE 1000
struct tampon // structure pour le message
{
    long mtype; // type tels que 1, 2, 3
    char mtext[MAXTEXTE]; // texte du message
};
int main()
{
    key_t cle = ftok(getenv("HOME"), 'a');
    int id = msgget(cle, IPC_CREAT | 0666);
    struct tampon message; 
    message.mtype = 1;

    while(1){
        fgets(message.mtext, MAXTEXTE, stdin); // Read message from user
        msgsnd(id, (struct msgbuf *) &message, sizeof(message.mtext), 0) ;
    } 
    return 0;
}