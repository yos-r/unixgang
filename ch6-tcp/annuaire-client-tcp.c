// client_tcp.c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //
    struct sockaddr_in server = { 
        .sin_family = AF_INET,
        .sin_port = htons(8083)
    };
    inet_aton("127.0.0.1", &server.sin_addr);
    
    connect(sockfd, (struct sockaddr*)&server, sizeof(server)); // connect to the server at the address in struct server
    
    printf("Enter name to search: ");
    char name[100];
    scanf("%s", name);
    write(sockfd, name, strlen(name)+1);
    char response[100];
    read(sockfd, response, sizeof(response));
    printf("Result: %s\n", response);
    close(sockfd);
}