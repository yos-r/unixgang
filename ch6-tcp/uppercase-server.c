#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void to_uppercase(char *str)
{
    while (*str)
    {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Create socket
    struct sockaddr_in servaddr = {
        .sin_family = AF_INET,         // IPv4
        .sin_addr.s_addr = INADDR_ANY, // Accept connections on all interfaces
        .sin_port = htons(PORT)};      // Port
    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)); // Bind socket
    // what you need, client, buffer and its length?
    char buffer[BUFFER_SIZE];
    struct sockaddr_in cliaddr; // client info
    socklen_t len; // client address length
    while (1) //wait for client calls
    {
        len = sizeof(cliaddr);

        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len); // Receive message
        printf("Client : %s\n", buffer);
    
        to_uppercase(buffer);  // Convert to uppercase
        sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len); // Send response
    }

    close(sockfd);
    return 0;
}
