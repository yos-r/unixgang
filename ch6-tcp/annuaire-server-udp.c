// UDP Version
// server_udp.c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

extern int Recherche(char *Abonne, char *telephone);

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Create a server socket
    struct sockaddr_in server = { // Create a server address
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY, // Accept connections on all interfaces
        .sin_port = htons(8081)
    };
    
    bind(sockfd, (struct sockaddr*)&server, sizeof(server)); // Bind the socket to the server address
    
    while(1) {
        char name[100]; //the input buffer
        char phone[20]; // the output buffer
        // ways to identify the client
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        
        recvfrom(sockfd, name, sizeof(name), 0, (struct sockaddr*)&client, &len);
        
        if(Recherche(name, phone)) {
            sendto(sockfd, phone, strlen(phone)+1, 0, (struct sockaddr*)&client, len);
        } else {
            sendto(sockfd, "Not found", 10, 0, (struct sockaddr*)&client, len);
        }
    }
}
// structure for phone directory entries
struct Entry {
    char name[100];
    char phone[20];
};

// Sample directory data
struct Entry directory[] = {
    {"Katz", "123-456-7890"},
    {"Jane Smith", "234-567-8901"},
    {"Bob Wilson", "345-678-9012"},
    {"\0", "\0"}  // end marker
};

int Recherche(char *Abonne, char *telephone) {
    int i = 0;
    
    while(directory[i].name[0] != '\0') {
        if(strcmp(directory[i].name, Abonne) == 0) {
            strcpy(telephone, directory[i].phone);
            return 1;
        }
        i++;
    }
    
    return 0;
}