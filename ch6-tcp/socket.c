#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int socket(int domain, int type, int protocol);
// struct sockaddr_in : structure pour les adresses internet : 
 //-sin_family: famille d'adresse (AF_INET)
 // sin_port
 // sin_addr: pour stocker l'adresse IP
 // sin_zero 

struct hostent *gethostbyname(const char *name); // pour des hotes distants
// retourne des infos sur un hôte en particulier h_name, h_aliases, h_addrtype, h_length, h_addr_list

// locally, on utilise INADDR_ANY ouvre le socket sur toutes les interfaces
// INADDR_LOOPBACK pour le loopback: SOCKET accepte les connexions locales
int getsockname(int s, struct sockaddr *name, socklen_t *namelen); // retourne l'adresse locale du socket
// port est dans sin_port de sockaddr_in
#include <netinet/in.h>
#include <arpa/inet.h>
char *inet_ntoa(struct in_addr in);