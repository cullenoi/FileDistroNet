
#ifndef Server_h
#define Server_h

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
 
 int sockfd, connfd, len;
 struct sockaddr_in servaddr, cli;
 
int ServerCreate( int * sockfd,int* connfd,int* len,sockaddr_in* servaddr,sockaddr_in*  cli);
#endif //Server_h