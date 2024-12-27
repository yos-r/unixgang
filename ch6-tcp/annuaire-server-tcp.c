// TCP Version with parallel server
// server_tcp.c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);// socket(domain, type, protocol) returns a file descriptor
    struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(8083)};

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));// assign the address in struct server to the socket sockfd
    listen(sockfd, 5); // listen for incoming connections on sockfd, with a maximum of 5 pending connections

    while (1)
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int clientfd = accept(sockfd, (struct sockaddr *)&client, &len); // accept a connection on sockfd, return a new file descriptor
        // générer copie
        if (fork() == 0)
        {
            close(sockfd); // close the listening socket
            // handle_client(clientfd);
            char name[100]; // input buffer
            char phone[20]; // output buffer
            read(clientfd, name, sizeof(name)); // read from clientfd into name
            if (Recherche(name, phone))
            {
                write(clientfd, phone, strlen(phone) + 1);
            }
            else
            {
                write(clientfd, "Not found", 10);
            }

            close(clientfd);// close the client socket
            exit(0);
        }
        close(clientfd);
    }
}

// structure for phone directory entries
struct Entry
{
    char name[100];
    char phone[20];
};

// Sample directory data
struct Entry directory[] = {
    {"Katz", "123-456-7890"},
    {"JaneSmith", "234-567-8901"},
    {"BobWilson", "345-678-9012"},
    {"\0", "\0"} // end marker
};

int Recherche(char *Abonne, char *telephone)
{
    int i = 0;

    while (directory[i].name[0] != '\0')
    {
        if (strcmp(directory[i].name, Abonne) == 0)
        {
            strcpy(telephone, directory[i].phone);
            return 1;
        }
        i++;
    }

    return 0;
}