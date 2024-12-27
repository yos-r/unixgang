// Client (client.c)
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Create a client socket
    // Server address
    struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_port = htons(8080)
    };
    inet_aton("127.0.0.1", &server.sin_addr);
    
    char message[1024];
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    // send message to server
    sendto(sockfd, message, strlen(message)+1, 0, (struct sockaddr*)&server, sizeof(server));
    
    char response[1024];
    recvfrom(sockfd, response, sizeof(response), 0, NULL, NULL);
    printf("Server response: %s\n", response);
    close(sockfd);
}