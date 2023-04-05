#ifndef PublicDef_h
#define PublicDef_h
#include <stdio.h>
#include <stdlib.h>
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
#include <sys/select.h>

#include "Node/Node.h"
#include "Node/Tracker.h"




#define _SS_PAD1SIZE 3000
#define BACKLOG 10   // how many pending connections queue will hold
#define MAX 100
#define SA struct sockaddr
/////////server side//

void Recieve(unsigned address, dataset * data_file, int * map);

/// @brief CLIENT SIDE///// These could be made simply as called in function noneeed fr global

int ClientCreate(int PORT_server,char *buffer);

void FileDistro(dataset * file, int address, node * node_list, int * map);

NodeInfo PortParser(char *buff);
void SendBack(int NUM,int port, char* IP ,int fileid,char* msg);




#endif 