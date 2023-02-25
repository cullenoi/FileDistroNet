#ifndef Client_h
#define Client_h 

#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define PORT 8080
#define SA struct sockaddr


int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

int ClientCreate(int* sockfd,int * connfd,sockaddr_in *servaddr,sockaddr_in* cli);

#endif