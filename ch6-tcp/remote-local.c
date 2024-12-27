#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
// creer des adresses socket destinées a soit etre
// Create a local socket address: takes in a port only
struct sockaddr_in create_local_address(int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // local address
    addr.sin_addr.s_addr = INADDR_ANY; 
    return addr;
}

// Create a remote socket address: takes in a hostname and port
struct sockaddr_in create_remote_address(const char *hostname, int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // Resolve hostname to IP address
    struct hostent *host= gethostbyname(hostname);
    addr.sin_addr = *(struct in_addr *)host->h_addr; // h_addr is the first address in h_addr_list
    return addr;
}