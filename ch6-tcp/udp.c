// UDP Server
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);// socket(domain, type, protocol) returns a file descriptor
    struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,// INADDR_ANY: accept connections on all interfaces
        .sin_port = htons(8080)// htons: host to network short
    };
    
    bind(sockfd, (struct sockaddr*)&server, sizeof(server)); // assign the address in struct server to the socket sockfd
    
    char buffer[1024];
    struct sockaddr_in client;
    socklen_t len = sizeof(client);    
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len); // read from client into buffer
    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, len); // send buffer to client
    
    close(sockfd); // close the socket writing and reading
}

// UDP Client
int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server = { // struct sockaddr_in: structure for internet addresses
        .sin_family = AF_INET,
        .sin_port = htons(8080)
    };
    inet_aton("127.0.0.1", &server.sin_addr); 
    
    sendto(sockfd, "Hello", 6, 0, (struct sockaddr*)&server, sizeof(server)); // send "Hello" to server
    
    char buffer[1024];
    recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL); // read from server into buffer
    
    close(sockfd);
}