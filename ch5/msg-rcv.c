#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 100

// structure for message queue
struct tampon
{
    long msg_type;
    char msg_text[MAX];
} message;
int encore = 1;
int main()
{
    key_t key = ftok("progfile", 65); // ftok to generate unique key
    int msgid = msgget(key, 0666 | IPC_CREAT); // msgget creates a message queue and returns identifier

    while (encore)
    {
        int l;
        struct tampon msg;
        l = msgrcv(msgid, (struct msgbuf *) &msg, sizeof(msg.msg_text), 0, 0);
        printf("Message of typ%ld:  %s \n", msg.msg_type, msg.msg_text);
    }
    exit(EXIT_SUCCESS);

    return 0;
}