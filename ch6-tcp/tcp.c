// UDP Server
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

// TCP Server
int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //socket(domain, type, protocol) returns a file descriptor
    struct sockaddr_in server = {
        .sin_family = AF_INET, // AF_INET: address family for IPv4
        .sin_addr.s_addr = INADDR_ANY, // INADDR_ANY: accept connections on all interfaces
        .sin_port = htons(8080) // htons: host to network short
    }; // struct sockaddr_in: structure for internet addresses
    
    bind(sockfd, (struct sockaddr*)&server, sizeof(server)); // assign the address in struct server to the socket sockfd
    listen(sockfd, 5); // listen for incoming connections on sockfd, with a maximum of 5 pending connections
    
    struct sockaddr_in client; // struct sockaddr_in: structure for internet addresses
    socklen_t len = sizeof(client);
    int clientfd = accept(sockfd, (struct sockaddr*)&client, &len); // accept a connection on sockfd, return a new file descriptor
    
    char buffer[1024];
    read(clientfd, buffer, sizeof(buffer)); // read from clientfd into buffer
    write(clientfd, buffer, sizeof(buffer));
    
    close(clientfd);
    close(sockfd);
}

// TCP Client
int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //socket(domain, type, protocol) returns a file descriptor
    //which server does client wish to connect to?
    struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_port = htons(8080)
    };
    inet_aton("127.0.0.1", &server.sin_addr); // inet_aton: convert an IPv4 address in string format to a struct in_addr
    
    connect(sockfd, (struct sockaddr*)&server, sizeof(server)); // connect to the server at the address in struct server
    
    write(sockfd, "Hello", 6);
    
    char buffer[1024];
    read(sockfd, buffer, sizeof(buffer));
    
    close(sockfd);
}