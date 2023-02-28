#ifndef PublicDef_h
#define PublicDef_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <strings.h> // bzero()
#include <netinet/in.h>
#include <unistd.h> // read(), write(), close()
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>

// #define PORT "3490"  // the port users will be connecting to
// #define PORTC "3490"
#define _SS_PAD1SIZE 3000
#define BACKLOG 10   // how many pending connections queue will hold
#define MAX 80
#define SA struct sockaddr
/////////server side//
int sockfd =99, talkfd =99;//SOCKET FILE DESCRIPTOR returns -1 on errno
    struct addrinfo hints, *res, *p;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
/// @brief CLIENT SIDE/////
int Csockfd =99;//SOCKET FILE DESCRIPTOR returns -1 on errno
    struct addrinfo Chints, *Cres;
    char s[INET6_ADDRSTRLEN];
    int yes =99;
	int rv = 99,rz =99;

char usrname[20];
int PORT;
// #define MAX 80 Defined in server




    


#endif 