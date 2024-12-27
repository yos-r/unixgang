// client_udp.c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);// server socket
    struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_port = htons(8081)
    };
    inet_aton("127.0.0.1", &server.sin_addr);
    
    printf("Enter name to search: ");
    char name[100];
    scanf("%s", name);
    // send name to server
    sendto(sockfd, name, strlen(name)+1, 0, (struct sockaddr*)&server, sizeof(server));
    
    char response[100];
    // receive from server and store in response
    recvfrom(sockfd, response, sizeof(response), 0, NULL, NULL);
    printf("Result: %s\n", response);
    
    close(sockfd);
}